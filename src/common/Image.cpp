// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "Common.h"
#include "Image.h"
#include "Graphics.h"
#include "ResourceManager.h"
#include "Stream.h"
#include "Engine.h"
#include "../game/cGame.h"
#include "Memory.h"

CImage* CImage::CreateImage(CStream &stream, MemoryType memType)
{
	unsigned int pos = stream.GetPosition();
	unsigned char bpp = stream.ReadUByte();
	unsigned char flag = stream.ReadUByte();

	stream.SetPosition(pos);
	if(flag & BBM_PALETTE)
	{
		if(flag & BBM_COMPRESSION_RLE)
		{
			//not implemented
			ASSERT(false);
		}
		else
			return (GL_NEW/*(memType)*/ CIndexedImage(stream));
	}
	else
	{
		ASSERT(!(flag & BBM_COMPRESSION_RLE)); //not allowed
		return (GL_NEW/*(memType)*/ CRgbImage(stream));
	}
	ASSERT(false);
	return NULL;
}

CImage* CImage::CreateImage(const char *pResName, MemoryType memType)
{
	if(memType != POOL_BOTTOM){
		int fgfg=3;
	}
	CStream *stream = GetResourceManager().GetResourceAsStream(pResName,
		memType == POOL_BOTTOM ? POOL_TOP : POOL_BOTTOM);
	CImage *image = CreateImage(*stream, memType);
	stream->Close();
	SAFE_DEL(stream);
	return image;
}

void CImage::SetSize(int width, int height, int pitch)
{
	m_width = width;
	m_height = height;
	m_pitch = pitch;
	if(((pitch - 1) & pitch) == 0 && ((height - 1) & height) == 0)
	{
		//Todo: optimize the following in ARM with CLZ instruction
		int i, wshift;
		for(i = 0; i < sizeof(m_pitch) * 8; i++)
		{
			if(pitch & (1 << i))
			{
				wshift = i;
				break;
			}
		}
		int hshift;
		for(i = 0; i < sizeof(m_height) * 8; i++)
		{
			if(height & (1 << i))
			{
				hshift = i;
				break;
			}
		}
		//If wshift == 15 && hshift == 15, m_sizeShift = 255,
		//but 255 is used to mean that width&height is not power of 2.
		ASSERT(wshift < 15 && hshift < 15);
		m_sizeShift = (hshift << 4) | wshift;
	}
	else
		m_sizeShift = 255;
}

typedef struct _BBM_HEADER{
	unsigned char bpp;
	unsigned char flag;
	short width;
	short height;
	int	colorKey;
	short nColors;
}BBM_HEADER;

CIndexedImage::CIndexedImage(CStream &stream)
{
	m_type = TYPE_INDEXED;

	BBM_HEADER h;

	stream.Read(&h, sizeof(h));
#ifdef BIGENDIAN
	h.width = ConvertLD2BE(h.width);
	h.height = ConvertLD2BE(h.height);
	h.colorKey = ConvertLD2BE(h.colorKey);
	h.nColors = ConvertLD2BE(h.nColors);
#endif
	m_bpp = h.bpp;
	ASSERT(m_bpp == 8);

	m_flag = h.flag;
	int width = h.width;
	int height = h.height;

	SetSize(width, height, width * ((m_bpp + 7) / 8));
	
	if(m_flag & BBM_COLOR_KEY)
	{
		EnableColorKey(true);

#if NATIVE_COLOR_DEPTH == 12
		h.colorKey = Convert564To444(h.colorKey);
#endif 
		SetColorKey(h.colorKey);
	}
	m_paletteEntryNumber = h.nColors;

	ASSERT(sizeof(NativePixel) == 2);
	
	m_paletteData = (GL_NEW/*(GetMemoryType(this))*/ PalettePixel[m_paletteEntryNumber]);

	for(int i = 0; i < m_paletteEntryNumber; i++)
	{
		int col = stream.ReadShortLE() | 0xFF000000 ;

#if NATIVE_COLOR_DEPTH == 12
		m_paletteData[i] = Convert564To444(col);
#else
		m_paletteData[i] = col;
#endif
	}

	unsigned int pixelDataSize = GetPitch() * GetHeight();

	m_pixel = (GL_NEW/*(GetMemoryType(this))*/ unsigned char[pixelDataSize]);

	stream.Read(m_pixel, pixelDataSize);
}

CIndexedImage::~CIndexedImage()
{
//	SAFE_DELETE_ARRAY( m_pixel);  ///seongjin---081031 no memory_del because MEMID
//	SAFE_DELETE_ARRAY(m_paletteData);  ///seongjin---081031 no memory_del because MEMID
}

CRgbImage::CRgbImage(CStream &stream)
{
	m_type = TYPE_RGB;
	m_bpp = stream.ReadUByte();
	m_flag = stream.ReadUByte();
	int width = stream.ReadUShortLE();
	int height = stream.ReadUShortLE();
	SetSize(width, height, width * ((m_bpp + 7) / 8));
	if(m_flag & BBM_COLOR_KEY)
		m_colorKey = stream.ReadUIntLE();
	unsigned int pixelDataSize = GetPitch() * GetHeight();
	m_pixel = (GL_NEW/*(GetMemoryType(this))*/ unsigned char[pixelDataSize]);
	stream.Read(m_pixel, pixelDataSize);

	m_needFreePixel = 1;
}
CRgbImage::CRgbImage(unsigned int w, unsigned int h, unsigned int pitch, int bpp, void* pixel)
{
	m_type = TYPE_RGB;
	SetSize(w, h, pitch);
	m_bpp = bpp;
	m_flag = 0;
	if (bpp > 24)
		m_flag |= BBM_ALPHA;
	m_colorKey = ~0;//use non-exist color
	m_pixel = (unsigned char*)pixel;
	m_needFreePixel = 0;
}

CRgbImage::~CRgbImage()
{
	if(m_needFreePixel && m_pixel )
	{
		SAFE_DELETE_ARRAY( m_pixel);
	}		
}

CMutableImage::CMutableImage(unsigned int w, unsigned int h, unsigned int pitch, int bpp, void* pixel)
{
	m_type = TYPE_MUTABLE;
	SetSize(w, h, pitch);
//	ASSERT(bpp == COLOR_DEPTH);
	m_bpp = bpp;
	m_flag = 0;
	m_colorKey = ~0;//use non-exist color
	m_pixel = (unsigned char*)pixel;
	m_needFreePixel = 0;
	m_graphics = NULL;
#ifdef GRAPHICS_ENABLE_RGB8
	if(bpp == 8)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned char, 8>());
#endif
#ifdef GRAPHICS_ENABLE_RGB12
	if(bpp == 12)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned short, 12>());
#endif
#ifdef GRAPHICS_ENABLE_RGB16
	if(bpp == 16)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned short, 16>());
#endif
#ifdef GRAPHICS_ENABLE_RGB24
	if(bpp == 24)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned int, 24>());
#endif
	ASSERT(m_graphics != NULL);

	m_graphics->SetImage(this);
}

CMutableImage::~CMutableImage()
{
	SAFE_DELETE(m_graphics);
	SAFE_DEL_ARRAY(m_pixel); //--sj memory_del;;;;
}

CMutableImage::CMutableImage(unsigned int w, unsigned int h, int bpp, MemoryType memType)
{
	m_type = TYPE_MUTABLE;
	m_bpp = bpp;
	int pitch;
	if(bpp == 8)
		pitch = 1;
	else if(bpp <= 16)
		pitch = 2;
	else if(bpp <= 32)
		pitch = 4;
	else
	{
		ASSERT(false);
		pitch = 0;
	}

	pitch *= w;
	SetSize(w, h, pitch);
	m_flag = 0;
	m_colorKey = ~0;//use non-exist color
	m_pixel = (GL_NEW/*(memType)*/ unsigned char[pitch * h]);
	m_needFreePixel = 1;
	m_graphics = NULL;
#ifdef GRAPHICS_ENABLE_RGB8
	if(bpp == 8)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned char, 8>());
#endif
#ifdef GRAPHICS_ENABLE_RGB12
	if(bpp == 12)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned short, 12>());
#endif
#ifdef GRAPHICS_ENABLE_RGB16
	if(bpp == 16)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned short, 16>());
#endif
#ifdef GRAPHICS_ENABLE_RGB24
	if(bpp == 24)
		m_graphics = (GL_NEW/*(GetMemoryType(this))*/ CGraphicsT<unsigned int, 24>());
#endif
	ASSERT(m_graphics != NULL);

	m_graphics->SetImage(this);
}

int CRleImage::CalculateBits(int colorCount)
{
	int clrs = colorCount - 1;
	int bits = 0;//1;
	while (clrs != 0)
	{
		clrs >>= 1;
		bits++;
	}
	return bits;
}

/* CGLI::CGLI():
	m_gliFrames(NULL)
	, m_bHasDeCompressed(false)
{
	m_type = TYPE_RLE;
	m_bpp = NATIVE_COLOR_DEPTH;
	m_needFreePixel = 1;

	EnableColorKey(false);

	if(m_bpp == 12)
		SetColorKey(TRANSPARENT_COLOR_444);
	else if(m_bpp == 16)
		SetColorKey(TRANSPARENT_COLOR_565);
}

CGLI::~CGLI()
{
	FreeMem();
}

void CGLI::FreeMem()
{
	SAFE_DELETE(m_gliFrameOffsets);
	if(m_gliBuf != NULL)
	{
		SAFE_DELETE(m_gliBuf);
	}
	m_pixel = NULL;
	if ((m_gliFlags & FLAG_REBUILD_SIZE) == 0) 
	{
		SAFE_DELETE(m_gliFrames);
	}
	SAFE_DELETE(m_gliImageData);
	SAFE_DELETE(m_pals);
}

void CGLI::Load(CStream &dis, bool bNeedGLIBuf , MemoryType memType)
{
	int i;

	m_gliFlags = dis.ReadIntBE();
	
	// image info
	m_frameCount = 0;

	if ((m_gliFlags & FLAG_REBUILD_SIZE) != 0) 
	{
		m_gliRebuildWidth = dis.ReadUByte();
		m_gliRebuildHeight = dis.ReadUByte();
		m_frameCount = dis.ReadUShortBE(); // map tile count can be 256
	}
	
	if ((m_gliFlags & MASK_USE_RLE) != 0) // use rle
	{	
		m_palBits = dis.ReadUByte();
	}
	else 
	{
		m_palBits = 8;
	}
	m_palMask = (1 << m_palBits) - 1;
	
	int imageSize = dis.ReadIntBE();
	
	// palette info
	int palCount = dis.ReadUByte();
	int palLen = dis.ReadUByte();
	
	if (palLen == 0) 
	{
		palLen = 0x100;
	}

	m_pals = GL_NEW(memType) unsigned short[palCount * palLen];
	m_pals_length = palCount;
	m_paletteEntryNumber = palLen;

	unsigned short *curpal = m_pals;

	for (i = 0; i < palCount; i++) 
	{
		for (int j = 0; j < palLen; j++) 
		{
			unsigned short pal = dis.ReadUShortBE();	

			if((m_gliFlags & FLAG_565_FORMAT) != 0)
			{
				if(pal == TRANSPARENT_COLOR_565)
					EnableColorKey(true);

				if(m_bpp == 16)
					*curpal = pal;
				else if(m_bpp == 12)
					*curpal = Convert564To444(pal);	
			}
			else
			{
				if((pal >> 12) > 0)
				{
					if(m_bpp == 16)
						*curpal = Convert444To565(pal);
					else if(m_bpp == 12)
						*curpal = pal;
				}
				else
				{
					if(m_bpp == 16)
						*curpal = TRANSPARENT_COLOR_565;
					else if(m_bpp == 12)
						*curpal = TRANSPARENT_COLOR_444;

					EnableColorKey(true);
				}	
			}

			++curpal;
		}
	}
	
	// load image data
	m_gliImageData = GL_NEW(memType)char[imageSize];
	dis.Read(m_gliImageData, imageSize);
	
	// load frames info
	if ((m_gliFlags & FLAG_REBUILD_SIZE) == 0) 
	{
		m_frameCount = dis.ReadUShortBE();
		m_gliFrames = GL_NEW(memType) unsigned char[m_frameCount * 2];
		dis.Read(m_gliFrames, m_frameCount * 2);
	}
	
	m_nMaxSize = 0;

	if(m_gliFrames != NULL)
	{
		for(i = 0; i < m_frameCount; ++i)
		{
			unsigned int size = m_gliFrames[i * 2] * m_gliFrames[i * 2 +1];

			if(m_nMaxSize < size)
				m_nMaxSize = size;
		}
	}
	else
	{
		m_nMaxSize = m_gliRebuildWidth * m_gliRebuildHeight;
	}

	if( bNeedGLIBuf )
	{
		m_gliBuf = GL_NEW(memType) unsigned short[m_nMaxSize];
	}	
	
	m_gliFrameOffsets = GL_NEW(memType) int[m_frameCount];

	if ((m_gliFlags & MASK_USE_RLE) != 0) 
	{
	
		int offset = 0;
	
		for (int i = 0; i < m_frameCount; i++) 
		{
			m_gliFrameOffsets[i] = offset;
			
			if ((m_gliFlags & FLAG_16BIT_4_LEN) != 0) 
			{
				offset += dis.ReadShortBE()&0xffff;
			}
			else 
			{
				offset += dis.ReadUByte();
			}
		}
	}
	else
	{
		int offset = 0;

		for (int i = 0; i < m_frameCount; i++) 
		{
			m_gliFrameOffsets[i] = offset;

			offset += m_gliRebuildWidth * m_gliRebuildHeight;
		}
	}
}

unsigned short *CGLI::DeCodeRLE(int frame, int palIndex)
{
	ASSERT(frame >= 0 && frame < m_frameCount);
	unsigned char *pS =(unsigned char *)(m_gliImageData + m_gliFrameOffsets[frame]);
	
	unsigned int size = GetWidth() * GetHeight();

	ASSERT(size <= m_nMaxSize);
	
	int count;
	unsigned int pos = 0;
	unsigned short *pal = m_pals + palIndex * m_paletteEntryNumber;

	unsigned short *buf = m_gliBuf;
	
	while (pos < size)
	{
		count = *pS >> m_palBits;
		
		unsigned short color = pal[*pS & m_palMask];

		while(count-- >= 0)	
		{
			buf[pos ++] = color;
		}
		
		++pS;
	}	

	return buf;
}

void CGLI::ReBuildSize(int modID)
{
	m_modID = modID;
	
	if (m_gliFrames == NULL) 
	{
		SetWidth(m_gliRebuildWidth);
		SetHeight(m_gliRebuildHeight);
	}
	else 
	{
		SetWidth(m_gliFrames[modID * 2]);
		SetHeight(m_gliFrames[modID * 2 + 1]);
	}

	SetPitch(GetWidth() * 2);
}

void CGLI::ReBuildData(int modID, int palIndex)
{ 
	if( m_bHasDeCompressed )
	{
		return;
	}
	m_pixel = (unsigned char*)DeCodeRLE(modID, palIndex);
}

void CGLI::Draw(CGraphics &g, int modID, int x, int y, int flag)
{
	Draw( g, modID, m_currentPal, x, y, flag );
}

void CGLI::Draw(CGraphics &g, int modID, int palIndex, int x, int y, int flag)
{
	m_type = TYPE_RLE;
	ReBuildSize(modID);

	bool hasDraw = g.DrawGLI(this, flag, x, y, palIndex);

	if(!hasDraw)
	{
		m_type = TYPE_RGB;
		ReBuildData(modID, palIndex);
		g.DrawRegion(this, 0, 0, GetWidth(), GetHeight(), flag, x, y, palIndex);	
	}
}

int CGLI::GetModuleWidth(int modID)
{
	if (m_gliFrames == NULL) 
	{
		return m_gliRebuildWidth;
	}

	return (m_gliFrames[modID * 2]);
}

int CGLI::GetModuleHeight(int modID)
{
	if (m_gliFrames == NULL) 
	{
		return m_gliRebuildHeight;
	}

	return (m_gliFrames[modID * 2 + 1]);
}

unsigned short* CGLI::GetPal(int id)
{
	if(id < 0 || id >= m_pals_length)
	{
//		ASSERT(0);
		return m_pals;
	}
	return m_pals + id * m_paletteEntryNumber;
}

unsigned char* CGLI::GetRLEData()
{
	ASSERT(m_modID >= 0 && m_modID < m_frameCount);
	return (unsigned char *)(m_gliImageData + m_gliFrameOffsets[m_modID]);	
}*/

#ifdef ENABLE_ZDS
CZDS::CZDS()
	: m_alpha(NULL)
	, m_renderState(ALPHA_BLEND)
{
	m_type = TYPE_ZDS;
	m_bpp = NATIVE_COLOR_DEPTH;
	m_needFreePixel = 1;

	EnableColorKey(false);

	if(m_bpp == 12)
	{
		SetColorKey(TRANSPARENT_COLOR_444);
	}
	else if(m_bpp == 16)
	{
		SetColorKey(TRANSPARENT_COLOR_565);
	}
}

CZDS::~CZDS()
{
	SAFE_DELETE(m_alpha);
}

void CZDS::Load(CStream &dis, MemoryType memType)
{
	char buf[4] = " ";

	dis.Read(buf, 3);

	SetWidth(dis.ReadUShortLE());
	SetHeight(dis.ReadUShortLE());
	SetPitch(GetWidth() * 2);

	m_alpha = (unsigned char*)GL_NEW/*(memType)*/ unsigned char[GetWidth() * GetHeight()];
	dis.Read(m_alpha, GetWidth() * GetHeight());

	m_pixel = (unsigned char*)GL_NEW/*(memType)*/ unsigned char[GetWidth() * GetHeight() * 2];
	dis.Read(m_pixel, GetWidth() * GetHeight() * 2);
}
#endif