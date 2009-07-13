// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite.h"
#include "MemoryPool.h"
// Sprite.java - Aurora Sprite - MIDP 2.0 version
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Author(s): Ionut Matasaru (ionut.matasaru@gameloft.com)
//
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Implementation for sprites exported by AuroraGT editor.
//  Contains methods to handle displaying of strings.
//
//  History:
//		28.09.2003, created
//				03.10.2003, I16, I127
//				12.11.2003, I2, I4, I256
//				24.11.2003, Draw String System
//				22.12.2003, MIDP 2.0 version
//				23.04.2004, I256 bug fixed (&0xFF)
//				12.05.2004, modular version, 8888 pixel format
//				15.06.2004, improved (flip X, flip Y, flip XY)
//			    24.06.2004, 4 bits extension for FModules . module index => 4+8=12 bits => max. 4096 modules
//                          4 bits extension for AFrames  . frame index  => 4+8=12 bits => max. 4096 frames
//				06.07.2004, Nokia API version
//				23.08.2004, BSprite v3
//				10.09.2004, HyperFrames/HyperFModules, module mappings
//				15.09.2005, updated
//				19.09.2005, new data format: I256RLE; new pixel formats: _1555, _0565 (AuroraGT v053)
//		20.09.2005, _nModules, _modules_w[], _modules_h[] instead of _modules[]
//		14.12.2005, new data format: I64RLE (AuroraGT v056)
//
//  Features:
//		* use ".bsprite" files (BSPRITE_v003, exported by AuroraGT v0.5.4 - SpriteEditor v0.6.4 or later)
//				* BSprite flags: BS_DEFAULT_MIDP2
//				* pixel formats supported:
//					8888	- A8 R8 G8 B8
//					4444	- A4 R4 G4 B4
//					1555	- A1 R5 G5 B5
//					0565	- R5 G6 B5
//				* data formats supported:
//					I2		- 8 pixels/char encoding (max 2 colors)
//					I4		- 4 pixels/char encoding (max 4 colors)
//					I16		- 2 pixels/char encoding (max 16 colors)
//			I64RLE	- variable RLE compression (max 64 colors)
//			I127RLE	- fixed RLE compression (max 127 colors)
//			I256	- 1 pixel/char encoding (max 256 colors)
//			I256RLE	- fixed RLE compression (max 256 colors)
//
//  Note:
//		If you want to use the Draw String System, first init the "_map_char" for each font sprite.
//		It should contain a 256 char array with the mapping between ASCII codes and FModules.
//		You could use FontTable.exe to generate it.
//
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define TURN_OFF_DBGPRINTF_IN_SPRITE

#if (DEBUG_LEVEL != 3 && defined(DBGPRINTF)) || (defined(TURN_OFF_DBGPRINTF_IN_SPRITE))
#pragma message("Turnning off DBGPRINTF in CSprite")
#undef DBGPRINTF
#define DBGPRINTF
#endif

CSprite::CSprite()
//:_line_spacing(0)
{
	m_pGame = (CGame*)GetGameApp()->m_engine;
}

#define TEST_AND_DELETE( p ) if(p) { SAFE_DELETE((p)); }
#define TEST_AND_DELETE_ARRAY( p ) if(p) { SAFE_DELETE_ARRAY(p); }//MF
CSprite::~CSprite()
{/*
	TEST_AND_DELETE( _modules_data );
	TEST_AND_DELETE( _modules_data_off );
	if ( m_b_palette_loaded )
	{
		for (int p = _palettes-1; p >=0; p-- )
		{
			TEST_AND_DELETE( _pal[p] );
		}
	}
	TEST_AND_DELETE( _pal_alpha );
	if ( m_b_palette_loaded ) TEST_AND_DELETE( _pal );
	TEST_AND_DELETE( _anims_af_start );
	TEST_AND_DELETE( _anims_naf );
	TEST_AND_DELETE( _aframes );
	TEST_AND_DELETE( _frames_fm_start );
	TEST_AND_DELETE( _frames_nfm );
	TEST_AND_DELETE( _fmodules );
	TEST_AND_DELETE( _modules_h );
	TEST_AND_DELETE( _modules_w );*/

	TEST_AND_DELETE_ARRAY( _modules_data );
	TEST_AND_DELETE_ARRAY( _modules_data_off );
	if ( m_b_palette_loaded )
	{
		for (int p = _palettes-1; p >=0; p-- )
		{
			TEST_AND_DELETE_ARRAY( _pal[p] );
		}
	}
	TEST_AND_DELETE_ARRAY( _pal_alpha );
	if ( m_b_palette_loaded ) TEST_AND_DELETE_ARRAY( _pal );
	TEST_AND_DELETE_ARRAY( _anims_af_start );
	TEST_AND_DELETE_ARRAY( _anims_naf );
	TEST_AND_DELETE_ARRAY( _aframes );
	TEST_AND_DELETE_ARRAY( _frames_rc_start );
	TEST_AND_DELETE_ARRAY( _frames_fm_start );
	TEST_AND_DELETE_ARRAY( _frames_nfm );
    TEST_AND_DELETE_ARRAY(_frames_rc);
	TEST_AND_DELETE_ARRAY( _fmodules );
	TEST_AND_DELETE_ARRAY( _modules_h );
	TEST_AND_DELETE_ARRAY( _modules_w );

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

int CSprite::getFmoduleData(int moduleIndex, int pos)
{
	if (m_bFmOffShort)
	{
		const int basepos = moduleIndex * 6;
		switch(pos)
		{
		case 0 : return _fmodules[basepos]&0xFF;
		case 1 : return (_fmodules[basepos+1]&0xFF) + ((_fmodules[basepos+2])<<8);
		case 2 : return (_fmodules[basepos+3]&0xFF) + ((_fmodules[basepos+4])<<8);
		case 3 : return _fmodules[basepos+5]&0xFF;
		default : return 0;
		}
	}
	else
	{
		return _fmodules[(moduleIndex<<2)+pos];
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////


	// simple stream wrapper to support Aurora's char orders
	// and keep track of the read position.
/*	static final class StreamWrapper
	{
		int         m_pos;
		int         m_initialSize;
		InputStream m_stream;

		StreamWrapper(InputStream stream, int size)
		{
			m_stream = stream;
			m_initialSize = size;
			m_pos = 0;
		}

		long read(char[] b, int off, int len) throws IOException
		{
			m_pos += len;
            return m_stream.read(b,off,len);
		}

		char readByte() throws IOException
		{
			m_pos++;
			return (char)m_stream.read();
		}

		short readShort() throws IOException
		{
			m_pos += 2;
			return (short)((m_stream.read()&0xFF) + ((m_stream.read()&0xFF)<<8));
		}

		int readInt() throws IOException
		{
			m_pos += 4;
			return  ((m_stream.read()&0xFF)    ) +
					((m_stream.read()&0xFF)<< 8) +
					((m_stream.read()&0xFF)<<16) +
					((m_stream.read()&0xFF)<<24);
		}

		void skip(int count) throws IOException
		{
			m_pos += count;
			m_stream.skip(count);
		}

		int remaining()
		{
			return m_initialSize - m_pos;
		}

	}
*/

// Wrapper for backwards compatibility
//void CSprite::Load(char* data, int offset, int data_length, MemoryType memoryType)
//{
//	CMemoryStream* temp = GL_NEW(memoryType==POOL_TOP?POOL_BOTTOM:POOL_TOP) CMemoryStream(data, data_length);
//	Load( temp, offset, data_length - offset,  memoryType);
//	SAFE_DELETE(temp);
//}


void CSprite::Load(CMemoryStream* data, int offset, int dataSize, bool load_pal, MemoryType memoryType)
{
	m_b_palette_loaded = load_pal;
	data->Skip(offset);	
	
	short bs_version = data->ReadShortLE();
	
	
	int bs_flags = data->ReadIntLE();
	
	
	m_bFmOffShort = (bs_flags & BS_FM_OFF_SHORT) != 0;
	
	
	//////////////////////////////
	
	// Modules...
	_nModules = data->ReadShortLE();
	ASSERT(_nModules>=0);
	if (_nModules > 0)
	{
		_modules_w  = (GL_NEW(memoryType) char[_nModules]);
		_modules_h  = (GL_NEW(memoryType) char[_nModules]);
		DBGPRINTF("CSprite.Load : Alloc _modules_w %x", _modules_w);
		DBGPRINTF("CSprite.Load : Alloc _modules_h %x", _modules_h);
		for (int i = 0; i < _nModules; i++)
		{
			_modules_w[i] = data->ReadByte();
			_modules_h[i] = data->ReadByte();
		}		
	}
	
	//////////////////////////////
	
	// FModules...
	int nFModules = data->ReadShortLE();
	ASSERT(nFModules>=0);
	if (nFModules > 0)
	{
		
		int _fmodules_length(0);
		if (m_bFmOffShort)
		{
			_fmodules_length = nFModules * 6;
		}
		else
		{
			_fmodules_length = nFModules<<2;
		}
		
		_fmodules = (GL_NEW(memoryType) char[_fmodules_length]);
		DBGPRINTF("CSprite.Load : Alloc _fmodules %x", _fmodules);
		data->Read(_fmodules, _fmodules_length);		
	}

	if (ALWAYS_BS_FRAME_RECTS)
	{
		int nFRects = data->ReadShortLE();
		if (nFRects > 0)
		{
			_frames_rc = (GL_NEW(memoryType) char[nFRects << 2]);
			data->Read(_frames_rc, nFRects << 2);
		}
	}

	// Frames...
	int nFrames = data->ReadShortLE();
	ASSERT(nFrames>=0);
	if (nFrames > 0)
	{
		_frames_nfm      = (GL_NEW(memoryType)  char[nFrames]);
		DBGPRINTF("CSprite.Load : Alloc _frames_nfm %x", _frames_nfm);
		_frames_nfm_length = nFrames;
		_frames_fm_start = (GL_NEW(memoryType) short[nFrames]);
		DBGPRINTF("CSprite.Load : Alloc _frames_fm_start %x", _frames_fm_start);
		
		short indexFRect = 0;
		if (ALWAYS_BS_FRAME_RECTS)
		{
			_frames_rc_start = (GL_NEW(memoryType) short[nFrames + 1]);
			_frames_rc_start[0] = indexFRect;
		}
		
		for (int i = 0; i < nFrames; i++)
		{
			_frames_nfm[i]      = data->ReadByte(); 
			if (!ALWAYS_BS_NFM_1_BYTE) { data->Skip(1); }
			_frames_fm_start[i] = data->ReadShortLE();
			if (ALWAYS_BS_FRAME_RECTS)
			{
				indexFRect += data->ReadByte();
				_frames_rc_start[i+1] = indexFRect;
			}
		}
		
		if (!ALWAYS_BS_SKIP_FRAME_RC)
		{
			if (USE_PRECOMPUTED_FRAME_RECT)
			{
				// Bound rect for each frame...
				int nFrames4 = nFrames<<2;
				_frames_rc = (GL_NEW(memoryType) char[nFrames4]);
				DBGPRINTF("CSprite.Load : Alloc _frames_rc %x", _frames_rc);
				for (int i = 0; i < nFrames4; i++)
				{
					_frames_rc[i] = data->ReadByte();
				}
			}
			else
			{
				data->Skip(nFrames<<2);
				
			}
		}
		else
		{
			if (USE_PRECOMPUTED_FRAME_RECT)
			{
				// TODO: precompute frame rc
			}
		}
	}
	
	//////////////////////////////
	
	// AFrames...
	int nAFrames = data->ReadShortLE();
	ASSERT(nAFrames>=0);
	if (nAFrames > 0)
	{
		int _aframes_length(0);
		_aframes_length = nAFrames*5;
		_aframes = (GL_NEW(memoryType) char[_aframes_length]);
		DBGPRINTF("CSprite.Load : Alloc _aframes %x", _aframes);
		data->Read(_aframes , _aframes_length);
	}
	
	// Anims...
	int nAnims = data->ReadShortLE();
	ASSERT(nAnims>=0);
	if (nAnims > 0)
	{
		_anims_naf      = (GL_NEW(memoryType) char[nAnims]);
		DBGPRINTF("CSprite.Load : Alloc _anims_naf %x", _anims_naf);
		_anims_naf_length = nAnims;
		_anims_af_start = (GL_NEW(memoryType) short[nAnims]);
		DBGPRINTF("CSprite.Load : Alloc _anims_af_start %x", _anims_af_start);
		for (int i = 0; i < nAnims; i++)
		{
			_anims_naf[i]      = data->ReadByte(); 
			if (!ALWAYS_BS_NAF_1_BYTE) { data->Skip(1); }
			_anims_af_start[i] = data->ReadShortLE();
		}
	}
	
	//////////////////////////////
	
	if (_nModules <= 0)
	{
		return;
	}
	
	
	//////////////////////////////
	
	// Pixel format (must be one of supported SPRITE_FORMAT_xxxx)...
	short _pixel_format = data->ReadShortLE();
	
	// Number of palettes...
	_palettes = data->ReadByte()&0xFF;		
	
	// Number of colors...
	_colors_cnt = data->ReadByte()&0xFF;
	
	if (USE_ENCODE_FORMAT_I256)
		if (_colors_cnt == 0) _colors_cnt = 256;
		
		// Palettes...
		if( load_pal )
		{
#if NATIVE_COLOR_DEPTH == 16
			_pal = (GL_NEW(memoryType) unsigned short*[_palettes]);//[MAX_SPRITE_PALETTES];
#else
			_pal = (GL_NEW(memoryType) int*[_palettes]);//[MAX_SPRITE_PALETTES];
#endif
		}

		_pal_alpha = (GL_NEW(memoryType) int[_palettes]);//[MAX_SPRITE_PALETTES];
		DBGPRINTF("CSprite.Load : Alloc _pal %x", _pal);
		DBGPRINTF("CSprite.Load : Alloc _pal_alpha %x", _pal_alpha);
		for (int p = 0; p < _palettes; p++)
		{
			if( load_pal )
			{
#if NATIVE_COLOR_DEPTH == 16
				_pal[p] = (GL_NEW(memoryType) unsigned short[_colors_cnt]);
#else
				_pal[p] = (GL_NEW(memoryType) int[_colors_cnt]);
#endif
			}			
			
			// HINT: Sort these pixel formats regarding how often are used by your game!
			if ((_pixel_format == PIXEL_FORMAT_8888) && USE_PIXEL_FORMAT_8888)
			{
				for (int c = 0; c < _colors_cnt; c++)
				{
					int _8888 = data->ReadIntLE();
					
					if ((_8888 & 0xFF000000) != 0xFF000000)
						_alpha = true;
					
					if( load_pal ) 
						_pal[p][c] = _8888;
				}
			}
			else if ((_pixel_format == PIXEL_FORMAT_4444) && USE_PIXEL_FORMAT_4444)
			{
				for (int c = 0; c < _colors_cnt; c++)
				{
					int _4444 = data->ReadShortLE();
					

					
					// 4444 . 8888
#if NATIVE_COLOR_DEPTH == 16
					int pal8888 = ((_4444 & 0xF000) << 16) | ((_4444 & 0xF000) << 12) |	// A
						((_4444 & 0x0F00) << 12) | ((_4444 & 0x0F00) <<  8) |	// R
						((_4444 & 0x00F0) <<  8) | ((_4444 & 0x00F0) <<  4) |	// G
						((_4444 & 0x000F) <<  4) | ((_4444 & 0x000F)      );	// B

					if( load_pal ) 
						_pal[p][c] = CNativeGraphics::ToNativeColorS(pal8888);
#else
					_pal[p][c] = ((_4444 & 0xF000) << 16) | ((_4444 & 0xF000) << 12) |	// A
						((_4444 & 0x0F00) << 12) | ((_4444 & 0x0F00) <<  8) |	// R
						((_4444 & 0x00F0) <<  8) | ((_4444 & 0x00F0) <<  4) |	// G
						((_4444 & 0x000F) <<  4) | ((_4444 & 0x000F)      );	// B
#endif
					
					if ((_4444 & 0xF000) != 0xF000)
					{
						_alpha = true;
						_pal_alpha[p] = CNativeGraphics::ToNativeColorS(pal8888);
					}
				}
			}
			else if ((_pixel_format == PIXEL_FORMAT_1555) && USE_PIXEL_FORMAT_1555)
			{
				for (int c = 0; c < _colors_cnt; c++)
				{
					int _1555 = data->ReadShortLE();
					
					//int a = 0xFF000000;
					if ((_1555 & 0x8000) != 0x8000)
					{
						//a = 0;
						_alpha = true;
						_pal_alpha[p] = ((_1555 & 0x7C00)<<1) | ((_1555 & 0x03E0)<<1) | (_1555 & 0x001F);

					}
					
					// 1555 . 8888
//					_pal[p][c] = a |						// A
//						((_1555 & 0x7C00) << 9) |	// R
//						((_1555 & 0x03E0) << 6) |	// G
//						((_1555 & 0x001F) << 3);	// B
					if( load_pal ) 
						_pal[p][c] = ((_1555 & 0x7C00)<<1) | ((_1555 & 0x03E0)<<1) | (_1555 & 0x001F);
				}
			}
			else if ((_pixel_format == PIXEL_FORMAT_0565) && USE_PIXEL_FORMAT_0565)
			{
				for (int c = 0; c < _colors_cnt; c++)
				{
					int _0565 = data->ReadShortLE();
					
					int a = 0xFF000000;
					if (_0565 == 0xF81F)
					{
						a = 0;
						_alpha = true;
						_pal_alpha[p] = _0565;
					}
					
					// 0565 . 8888
//					_pal[p][c] = a |						// A
//						((_0565 & 0xF800) << 8) |	// R
//						((_0565 & 0x07E0) << 5) |	// G
//						((_0565 & 0x001F) << 3);	// B
					if( load_pal ) 
						_pal[p][c] = _0565;
				}
			}
		}
		
		//////////////////////////////
		
		// Data format (must be one of supported ENCODE_FORMAT_xxxx)...
		_data_format = data->ReadShortLE();
				
		if ((_data_format == ENCODE_FORMAT_I64RLE) && USE_ENCODE_FORMAT_I64RLE)
		{
			int clrs = _colors_cnt - 1;
			_i64rle_color_mask = 1;
			_i64rle_color_bits = 0; //1; //jrobinson, fixing a crash with I64RLE sprites. we had 1 bit too many here.
			while (clrs != 0)
			{
				clrs >>= 1;
				_i64rle_color_mask <<= 1;
				_i64rle_color_bits++;
			}
			_i64rle_color_mask--;
		}
		
		// Graphics data...
		if (_nModules > 0)
		{
			_modules_data_off = (GL_NEW(memoryType) _modules_data_off_t[_nModules]);
			DBGPRINTF("CSprite.Load : Alloc _modules_data_off %x", _modules_data_off);
			
			const int len = data->GetLength()- data->GetPosition() - (_nModules<<1);
			
			_modules_data = (GL_NEW(memoryType) char[len]);
			DBGPRINTF("CSprite.Load : Alloc _modules_data %x", _modules_data);
			int modulePos = 0;
			for (int m = 0; m < _nModules; m++)
			{
				int size = data->ReadShortLE();
				_modules_data_off[m] = (_modules_data_off_t)modulePos;
				
				data->Read((char*)(_modules_data+(_modules_data_off[m]&kModuleDataOffsetMask)), size);
				modulePos += size;
			}
			
		}
		
		//////////////////////////////
		// module mappings
		
		if (USE_MODULE_MAPPINGS)
		{
			_map = (GL_NEW(memoryType) int*[MAX_MODULE_MAPPINGS]);
			DBGPRINTF("CSprite.Load : Alloc _map %x", _map);
			//	_mappings = 0;
			_cur_map = -1;
		}
		
		//////////////////////////////
		
		//if (DEF::bDbgS) System.out.println("--- ok");
		//if ( DEF::bAutoGc ) System.gc();
}


//	static int temp_max_size = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
// pal = palette to be initailized
// m1 = first module
// m2 = last module (-1 . to end)
// pal_copy = mapping to another palette (-1 . build)


void CSprite::BuildCacheImages(int pal, int m1, int m2, int pal_copy, MemoryType memoryType)
{
	
	
	if (_nModules == 0) return;
	
	if (m2 == -1)
		m2 = _nModules - 1;
	
	if (_modules_image == NULL)
	{
		_modules_image = (GL_NEW(memoryType) CImage**[_palettes]);
		DBGPRINTF("CSprite.BuildCacheImages : Alloc _modules_image %x", _modules_image);
	}
	
	if (_modules_image[pal] == NULL)
	{
		_modules_image[pal] = (GL_NEW(memoryType) CImage*[_nModules]);
		DBGPRINTF("CSprite.BuildCacheImages : Alloc _modules_image[%d] %x", pal, _modules_image[pal]);
	}
	
	if (pal_copy >= 0)
	{
		for (int i = m1; i <= m2; i++)
			_modules_image[pal][i] = _modules_image[pal_copy][i];
	}
	else
	{
		for (int i = m1; i <= m2; i++)
		{
			BuildCacheModule(pal, i, memoryType);
		}
	}
}

void CSprite::UnCacheImages()
{
	if (_modules_image != NULL)
	{
/*		for(int i = 0; i < _modules_image.length; ++i)
		{
			Image[] modules_image_i = _modules_image[i];
			if (modules_image_i != NULL)
			{
				for(int j = 0; j < modules_image_i.length; ++j)
				{
					modules_image_i[j] = NULL;
				}
			}
		}
*/
		_modules_image = NULL;
	}
}

void CSprite::BuildCacheModule(int pal, int module, MemoryType memoryType)
{
	if (_nModules == 0) return;
	
	if (_modules_image == NULL)
	{
		_modules_image = (GL_NEW(memoryType) CImage**[_palettes]);
		DBGPRINTF("CSprite.BuildCacheModule : Alloc _modules_image %x", _modules_image);
	}
	
	if (_modules_image[pal] == NULL)
	{
		_modules_image[pal] = (GL_NEW(memoryType) CImage*[_nModules]);
		DBGPRINTF("CSprite.BuildCacheModule : Alloc _modules_image[%d] %x", _modules_image[pal]);
	}
	
	if (_modules_image[pal][module] != NULL)
		return; // already cached
	
	int sizeX = _modules_w[module]&0xFF;
	int sizeY = _modules_h[module]&0xFF;
	ASSERT(!(sizeX < 0 || sizeY < 0));
	if (sizeX <= 0 || sizeY <= 0) 
		return;
	
	int old_pal = _crt_pal;
	_crt_pal = pal;
	char* image_data_temp = (GL_NEW(memoryType) char[sizeX * sizeY * 2]);
	DBGPRINTF("CSprite.BuildCacheModule : Alloc image_data_temp %x", image_data_temp);
	CImage* image_data = (CImage*)DecodeImage(module, 0, &image_data_temp, memoryType, true);
	DBGPRINTF("CSprite.BuildCacheModule : Alloc image_data %x", image_data);
	_crt_pal = old_pal;
	
	if(image_data != NULL && _alpha/*_pal_alpha[_crt_pal] != 0*/ )
	{
		image_data->EnableColorKey(true);
		//image_data->SetColorKey(_pal_alpha[_crt_pal]);
		image_data->SetColorKey(_pal_alpha[0]);
	}
	else if (image_data == NULL) 
	{
		DBGPRINTF("CSprite.BuildCacheModule : Dealloc image_data_temp %x", image_data_temp);
		SAFE_DELETE(image_data_temp);		
		return ;
	}
	
/*	bool bAlpha = false;
	int size = sizeX * sizeY;
	for (int ii = 0; ii < size; ii++)
	{
		if ((image_data[ii] & 0xFF000000) != 0xFF000000)
		{
			bAlpha = true;
			break;
		}
	}
	_modules_image[pal][module] = Image.createRGBImage(image_data, sizeX, sizeY, bAlpha);
	image_data = NULL;
*/
	_modules_image[pal][module] = image_data;
}

void CSprite::BuildCacheFrame(int pal, int frame, MemoryType memoryType)
{
	int nfm = GetFModules(frame);
	for(int fmodule = 0; fmodule < nfm; ++fmodule)
	{
		
		int off = (_frames_fm_start[frame] + fmodule) ;
		int module = getFmoduleData(off, 0);
		int fm_flags = getFmoduleData(off, 3);
		
		
		if ((fm_flags & FLAG_HYPER_FM) != 0)
		{
			BuildCacheFrame(pal, module, memoryType);
		}
		else
		{
			BuildCacheModule(pal, module, memoryType);
		}
	}
}

void CSprite::BuildCacheAnim(int pal, int anim, MemoryType memoryType)
{
	int naf = GetAFrames(anim);
	for(int aframe = 0; aframe < naf; ++aframe)
	{
		int off = (_anims_af_start[anim] + aframe) * 5;
		int frame = _aframes[off]&0xFF;
		if (USE_INDEX_EX_AFRAMES)
			frame |= ((_aframes[off+4]&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
		
		BuildCacheFrame(pal, frame, memoryType);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
char* toString()
{
	if(Specs.IsDebug)
	{
		int currentMemoryUsage = 0;
		
		if(_modules_image != NULL)
		{
			for (int pal = 0; pal < _modules_image.length; pal++)
			{
				if(_modules_image[pal] == NULL)
					continue;
				
				for(int i = 0; i < _modules_image[pal].length; i++)
				{
					if(_modules_image[pal][i] != NULL)
					{
						currentMemoryUsage += 2 * _modules_image[pal][i].getWidth() * _modules_image[pal][i].getHeight();
					}
				}
			}
		}
		
		String str = "raw/full: ";
		
		if(_modules_data != NULL)
			str += _modules_data->length + "/" + currentMemoryUsage;
		else
			str += "0/" + currentMemoryUsage;
		
		return str;
	}
	else
	{
		return "";
	}
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
// Module Mapping...

//private void MODULE_MAPPING___() {}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::SetModuleMapping(int map, char* mmp, int mmp_length, MemoryType memoryType)
{
	//	if (DEF::bASSERT) DBG.ASSERT(map >= 0 && map < _mappings, "map >= 0 && map < _mappings");
	if (_map[map] == NULL)
	{
		_map[map] = (GL_NEW(memoryType) int[_nModules]);
		for (int i = 0; i < _nModules; i++)
			_map[map][i] = i;
	}
	if (mmp == NULL) return;
	int off = 0;
	while (off < mmp_length)
	{
		int i1 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
		int i2 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
		_map[map][i1] = i2;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::ApplyModuleMapping(int dst_pal, int src_pal, char* mmp, int mmp_length)
{
	int off = 0;
	while (off < mmp_length)
	{
		int i1 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
		int i2 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
		_modules_image[dst_pal][i1] = _modules_image[src_pal][i2];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

//private void ___MODULE_MAPPING() {}

// ... Module Mapping
////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::GetAFrameRect(int* rc, int anim, int aframe, int posX, int posY, int flags, int hx, int hy)
{
	ASSERT( 0 <= anim && anim < GetAnims() );
	ASSERT( 0 <= aframe && aframe < GetAFrames(anim) );
	//	System.out.println("GetAFrameRect(rc, "+anim+", "+aframe+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
	int off = (_anims_af_start[anim] + aframe) * 5;
	int frame = _aframes[off]&0xFF;
	if (USE_INDEX_EX_AFRAMES)
		frame |= ((_aframes[off+4]&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
	if ((flags & FLAG_OFFSET_AF) != 0)
	{
		if ((flags & FLAG_FLIP_X) != 0)	hx += _aframes[off+2];
		else							hx -= _aframes[off+2];
		if ((flags & FLAG_FLIP_Y) != 0)	hy += _aframes[off+3];
		else							hy -= _aframes[off+3];
	}
	//	if ((flags & FLAG_FLIP_X) != 0)	hx += _frames_w[frame]&0xFF;
	//	if ((flags & FLAG_FLIP_Y) != 0)	hy += _frames_h[frame]&0xFF;
	GetFrameRect(rc, frame, posX, posY, flags ^ (_aframes[off+4]&0x0F), hx, hy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::GetFrameRect(int* rc, int frame, int posX, int posY, int flags, int hx, int hy)
{
	//	System.out.println("GetFrameRect(rc, "+frame+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
	
	if (USE_PRECOMPUTED_FRAME_RECT)
	{
		int frame4 = frame<<2;
		int fx = _frames_rc[frame4++];
		int fy = _frames_rc[frame4++];
		int fw = _frames_rc[frame4++]&0xFF;
		int fh = _frames_rc[frame4++]&0xFF;
		
		if ((flags & FLAG_FLIP_X) != 0)	hx += fx + fw;
		else							hx -= fx;
		if ((flags & FLAG_FLIP_Y) != 0)	hy += fy + fh;
		else							hy -= fy;
		
		rc[0] = posX - (hx << FIXED_PRECISION);
		rc[1] = posY - (hy << FIXED_PRECISION);
		rc[2] = rc[0] + (fw << FIXED_PRECISION);
		rc[3] = rc[1] + (fh << FIXED_PRECISION);
	}
	else
	{
		int fx = (255 << FIXED_PRECISION);
		int fy = (255 << FIXED_PRECISION);
		int fw = 0;
		int fh = 0;
		
		int nFModules = _frames_nfm[frame]&0xFF;
		//	int nFModules = _frames_nfm[frame]&0xFFFF;
		for (int fmodule = 0; fmodule < nFModules; fmodule++)
		{
			GetFModuleRect(rc, frame, fmodule, posX, posY, flags, hx, hy);
			if (rc[0] < fx)			fx = rc[0];
			if (rc[1] < fy)			fy = rc[1];
			if (rc[2] > fx + fw)	fw = rc[2] - fx;
			if (rc[3] > fy + fh)	fh = rc[3] - fy;
		}
		
		hx <<= FIXED_PRECISION;
		hy <<= FIXED_PRECISION;
		
		if ((flags & FLAG_FLIP_X) != 0)	hx += fx + fw;
		else							hx -= fx;
		if ((flags & FLAG_FLIP_Y) != 0)	hy += fy + fh;
		else							hy -= fy;
		
		rc[0] = posX - hx;
		rc[1] = posY - hy;
		rc[2] = rc[0] + fw;
		rc[3] = rc[1] + fh;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::GetFModuleRect(int* rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy)
{
	//	System.out.println("GetFModuleRect(rc, "+frame+", "+fmodule+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
	
	// TODO:...
	//if (DEF::bASSERT) DBG.ASSERT(false, "NOT IMPLEMENTED");
	
	// ADDED BY JP, 
	// cut & pasted this shit from somewhere else
	// Seems to work, but there is probably 1000 special cases that are not handled correctly.
	//  Fix 1 : Added support for HyperFrame !
	//
	
	
	int off = (_frames_fm_start[frame] + fmodule) ;		
	int fm_flags = getFmoduleData(off,3);
	int index = getFmoduleData(off,0);
	
	
	if (USE_INDEX_EX_FMODULES)
		index |= ((fm_flags&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
	
	
	int frameOffsetX = getFmoduleData(off,1) << FIXED_PRECISION ;
	int frameOffsetY = getFmoduleData(off,2) << FIXED_PRECISION ;
	
	
	if(USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0))
	{
		//index == frameIndex, just call FrameRectFunction
		GetFrameRect(rc, index, 0, 0, flags ^ (fm_flags&0x0F), hx, hy);
		//Add position of the HF to the frame position ...
		rc[0] = posX + frameOffsetX + rc[0];
		rc[1] = posY + frameOffsetY + rc[1];
		rc[2] = posX + frameOffsetX + rc[2];
		rc[3] = posY + frameOffsetY + rc[3];
	}
	else
	{
		GetModuleRect(rc, index, posX + frameOffsetX, posY + frameOffsetY, fm_flags);
	}
	// END ADDED BY JP.
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::GetModuleRect(int* rc, int module, int posX, int posY, int flags)
{
	//	System.out.println("GetModuleRect(rc, "+module+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+")");
	rc[0] = posX;
	rc[1] = posY;
	rc[2] = posX + ((_modules_w[module]&0xFF) << FIXED_PRECISION);
	rc[3] = posY + ((_modules_h[module]&0xFF) << FIXED_PRECISION);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::PaintAFrame(CGraphics* g, int anim, int aframe, int posX, int posY, int flags, int hx, int hy)
{
	//	System.out.println("PaintAFrame(g, "+anim+", "+aframe+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
	ASSERT( 0 <= anim && anim < GetAnims() );
	ASSERT( 0 <= aframe && aframe < GetAFrames(anim) );
	int off = (_anims_af_start[anim] + aframe) * 5;
	int frame = _aframes[off]&0xFF;
	if (USE_INDEX_EX_AFRAMES)
		frame |= ((_aframes[off+4]&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
	//	if ((flags & FLAG_OFFSET_AF) != 0)
	if ((flags & FLAG_DONTAPPLY_OFFSETS) == 0)
	{
		if ((flags & FLAG_FLIP_X) != 0)	hx += _aframes[off+2];
		else							hx -= _aframes[off+2];
		if ((flags & FLAG_FLIP_Y) != 0)	hy += _aframes[off+3];
		else							hy -= _aframes[off+3];
	}
	//	if ((flags & FLAG_FLIP_X) != 0)	hx += _frames_w[frame]&0xFF;
	//	if ((flags & FLAG_FLIP_Y) != 0)	hy += _frames_h[frame]&0xFF;
	PaintFrame(g, frame, posX-hx, posY-hy, flags ^ (_aframes[off+4]&0x0F), hx, hy);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::PaintFrame(CGraphics* g, int frame, int posX, int posY, int flags, int hx, int hy)
{
	//System.out.println("PaintFrame(g, "+frame+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
	int nFModules = _frames_nfm[frame]&0xFF;
	//	int nFModules = _frames_nfm[frame]&0xFFFF;
	for (int fmodule = 0; fmodule < nFModules; fmodule++)
	{
		PaintFModule(g, frame, fmodule, posX, posY, flags, hx, hy);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::PaintFModule(CGraphics* g, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy)
{
	
	int off = (_frames_fm_start[frame] + fmodule);
	int fm_flags = getFmoduleData(off,3);
	int index = getFmoduleData(off,0)&0xFF;
	if (USE_INDEX_EX_FMODULES)
		index |= ((fm_flags&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
	
	if ((flags & FLAG_DONTAPPLY_OFFSETS) != 0)
	{
		//must apply the offset of the first frame (since it might not be at origin...)
		off = (_frames_fm_start[0] + fmodule) << 2;
	}

	//	if ((flags & FLAG_OFFSET_FM) != 0)
	{
		if ((flags & FLAG_FLIP_X) != 0)	posX -= getFmoduleData(off,1);
		else							posX += getFmoduleData(off,1);
		if ((flags & FLAG_FLIP_Y) != 0)	posY -= getFmoduleData(off,2);
		else							posY += getFmoduleData(off,2);
	}
	
	
	if (USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0))
	{
		//	if ((flags & FLAG_FLIP_X) != 0)	posX -= _frames[(index<<?)  ]&0xFF; // pF.w
		//	if ((flags & FLAG_FLIP_Y) != 0)	posY -= _frames[(index<<?)+1]&0xFF; // pF.h
		
		PaintFrame(g, index, posX, posY, flags ^ (fm_flags&0x0F), hx, hy);
	}
	else
	{
		if ((flags & FLAG_FLIP_X) != 0)	posX -= _modules_w[index]&0xFF;
		if ((flags & FLAG_FLIP_Y) != 0)	posY -= _modules_h[index]&0xFF;
		
		PaintModule(g, index, posX, posY, flags ^ (fm_flags&0x0F));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::PaintModule(CGraphics* g, int module, int posX, int posY, int flags)
{
		
	if(m_bMinimalMemoryDrawing && (module != _modules_id_cache || _modules_pal_cache != _crt_pal))
	{
		if ((_modules_image != NULL) && (_modules_image[_crt_pal] != NULL))
		{
			_modules_image[_modules_pal_cache] = NULL;
			
			if (USE_GC_IN_MINMEMCALLS)
			{
				//System.gc();
			}
		}
	}
	
	if (USE_MODULE_MAPPINGS)
	{
		if (_cur_map >= 0)
		{
			module = _map[_cur_map][module];
		}
	}
	
	ASSERT(module >= 0);
	ASSERT(module < _nModules);
	int sizeX = _modules_w[module]&0xFF;
	int sizeY = _modules_h[module]&0xFF;
	if (sizeX <= 0 || sizeY <= 0) return;

	int cx = g->GetClipX();
	int cy = g->GetClipY();
	int cw = g->GetClipWidth();
	int ch = g->GetClipHeight();
	
	// Fast visibility test...
	if (posX + sizeX < cx ||
		posY + sizeY < cy ||
		posX >= cx + cw ||
		posY >= cy + ch)
	{
		//	System.out.println("outside clip rect");
#ifdef BREW_DEBUG
		m_pGame->cilpnum++;
#endif
		return;
	}
	
	CImage* img = NULL;
	bool bneedFreeImg = false;
	// Try to use cached images...
	if ((_modules_image != NULL) &&
		//	(_crt_pal < _modules_image.length) &&
		(_modules_image[_crt_pal] != NULL))
	{
		img = _modules_image[_crt_pal][module];
	}
	// Build RGB image...
	char* img_temp = NULL;
	if (img == NULL)
	{
		bneedFreeImg = true;
		/*if(m_bMinimalMemoryDrawing && ((flags & (FLAG_FLIP_X | FLAG_FLIP_Y)) != 0))
		{
			BuildCacheImages(_crt_pal, module, module, -1);
			img = _modules_image[_crt_pal][module];
			
			_modules_id_cache = module;
			_modules_pal_cache = _crt_pal;
		}
		else if(m_bUseLazyCaching && !m_bMinimalMemoryDrawing)
		{
			BuildCacheImages(_crt_pal, module, module, -1);
			img = _modules_image[_crt_pal][module];
		}
		else
		{*/	
			img_temp = (GL_NEW(POOL_TOP) char[1024]);
			img = (CImage*)DecodeImage(module, flags, &img_temp, POOL_BOTTOM);
			if (img == NULL)
			{
				SAFE_DELETE(img_temp);
				ASSERT(false);
				return;
			}
			if(/*_pal_alpha[_crt_pal] != 0*/ _alpha)
			{
				img->EnableColorKey(true);
				//img->SetColorKey(_pal_alpha[_crt_pal]);
				img->SetColorKey(_pal_alpha[0]);
			}
			
			
			//g.drawRGB(image_data, 0, sizeX, posX, posY, sizeX, sizeY, _alpha);
			//return;
		//}
		
		//img = Image.createRGBImage(image_data, sizeX, sizeY, _alpha);
	}
	
	// if decode image fails
	//if (img == NULL) { return; }
	
	sizeX = img->GetWidth();
	sizeY = img->GetHeight();
	
	
	const int x = 0;
	const int y = 0;
	//		if (posY < cy)			{ y = cy - posY; sizeY -= y; posY = cy; if (sizeY <= 0) return; }
	//		if (posY+sizeY > cy+ch)	{ sizeY = cy+ch - posY; if (sizeY <= 0) return; }
	
	// Draw...
	if ((flags & FLAG_FLIP_X) != 0)
	{
		if ((flags & FLAG_FLIP_Y) != 0)
		{
			// TODO: clip...
			g->DrawRegion(img, x, y, sizeX, sizeY, CGraphics::TRANS_ROT180, posX, posY, 0);
		}
		else
		{
			//	if (posX < cx)			{ sizeX -= cx - posX; posX = cx; }
			//	if (posX+sizeX > cx+cw)	{ x = cx+cw - posX; sizeX -= x; }
			g->DrawRegion(img, x, y, sizeX, sizeY, CGraphics::TRANS_MIRROR, posX, posY, 0);
		}
	}
	else if ((flags & FLAG_FLIP_Y) != 0)
	{
		// TODO: clip...
		g->DrawRegion(img, x, y, sizeX, sizeY, CGraphics::TRANS_MIRROR_ROT180, posX, posY, 0);
	}
	else
	{
		//	if (posX < cx)			{ x = cx - posX; sizeX -= x; posX = cx; }
		//	if (posX+sizeX > cx+cw)	{ sizeX = cx+cw - posX; }
		g->DrawRegion(img, x, y, sizeX, sizeY, CGraphics::TRANS_NONE, posX, posY, 0);
	}
	
	//	System.out.println("...PaintModule(_crt_pal = "+_crt_pal+")");
	//	System.out.println("...PaintModule(g, "+module+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+")");
	if(bneedFreeImg)
	{
		SAFE_DELETE(img_temp);
		SAFE_DELETE(img);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////


CMutableImage* CSprite::DecodeImage(int module, int flags, char** temp, MemoryType memoryType, bool isBuildModule)
{
	//	System.out.println("DecodeImage("+module+", 0x"+Integer.toHexString(flags)+")...");
	
	if (_modules_data == NULL ||
		_modules_data_off == NULL) return NULL;
		
	// Use last decodeImage if it's the same data
//	if ( (DEF::bCacheDecodeimages) && (module == last_module) && (hashCode() == last_sprite) )
//	{
//		last_module = module;
//		last_sprite = hashCode();
//		return temp;
//	}
	
	int sizeX = _modules_w[module]&0xFF;
	int sizeY = _modules_h[module]&0xFF;
	ASSERT(!(sizeX <= 0 || sizeY <= 0));
	

	
	int bpp = NATIVE_COLOR_DEPTH;
	int pitch;
	if(bpp == 8)
	{
		pitch = 1;
	}
	else if(bpp <= 16)
	{
		pitch = 2;
	}
	else if(bpp <= 32)
	{
		pitch = 4;
	}
	else
	{
		ASSERT(false);
		pitch = 0;
	}
	pitch *= sizeX;

	//-565 only
	unsigned short* img_data;
	if(*temp == NULL)
	{	
		*temp = (GL_NEW(memoryType==POOL_BOTTOM?POOL_TOP:POOL_BOTTOM) char[pitch * sizeY]);
	}
	else if(!isBuildModule && (pitch * sizeY > 1024))
	{
		SAFE_DELETE(*temp);
		*temp = (GL_NEW(memoryType==POOL_BOTTOM?POOL_TOP:POOL_BOTTOM) char[pitch * sizeY]);
	}
	img_data = (unsigned short*)*temp;
	//	if (flags == 1)
	//		img_data = new short[sizeX * sizeY + 7];
	
	// Choose palette...
#if NATIVE_COLOR_DEPTH == 16
	unsigned short* pal = _pal[_crt_pal ];
#else
	int* pal = _pal[_crt_pal ];
#endif
	if (pal == NULL)
	{
		ASSERT(false);
		return NULL;
	}
	
	// Build displayable...
	char* image = _modules_data;
	int si = _modules_data_off[module]&kModuleDataOffsetMask;
	int di = 0;
	int ds = sizeX * sizeY;
	
	// HINT: Sort these encoders regarding how often are used by your game!
	if ((_data_format == ENCODE_FORMAT_I64RLE) && USE_ENCODE_FORMAT_I64RLE)
	{
		// variable RLE compression, max 64 colors...
		while (di < ds)
		{
			int c = image[si++]&0xFF;
			int clr = pal[c & _i64rle_color_mask];
			c >>= _i64rle_color_bits;
			while (c-- >= 0)
				img_data[di++] = clr;
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I127RLE) && USE_ENCODE_FORMAT_I127RLE)
	{
		// fixed RLE compression, max 127 colors...
		while (di < ds)
		{
			int c = image[si++]&0xFF;
			if (c > 127)
			{
				int c2 = image[si++]&0xFF;
				int clr = pal[c2];
				c -= 128;
				while (c-- > 0)
					img_data[di++] = clr;
			}
			else
				img_data[di++] = pal[c];
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I256RLE) && USE_ENCODE_FORMAT_I256RLE)
	{
		// fixed RLE compression, max 256 colors...
		while (di < ds)
		{
			int c = image[si++]&0xFF;
			if (c > 127)
			{
				c -= 128;
				while (c-- > 0)
					img_data[di++] = pal[image[si++]&0xFF];
			}
			else
			{
				int clr = pal[image[si++]&0xFF];
				while (c-- > 0)
					img_data[di++] = clr;
			}
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I16) && USE_ENCODE_FORMAT_I16)
	{
		// 2 pixels/char, max 16 colors...
		while (di < ds)
		{
			img_data[di++] = pal[(image[si] >> 4) & 0x0F];
			img_data[di++] = pal[(image[si]     ) & 0x0F];
			si++;
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I4) && USE_ENCODE_FORMAT_I4)
	{
		// 4 pixels/char, max 4 colors...
		while (di < ds)
		{
			img_data[di++] = pal[(image[si] >> 6) & 0x03];
			img_data[di++] = pal[(image[si] >> 4) & 0x03];
			img_data[di++] = pal[(image[si] >> 2) & 0x03];
			img_data[di++] = pal[(image[si]     ) & 0x03];
			si++;
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I2) && USE_ENCODE_FORMAT_I2)
	{
		// 8 pixels/char, max 2 colors...
		while (di < ds)
		{
			img_data[di++] = pal[(image[si] >> 7) & 0x01];
			img_data[di++] = pal[(image[si] >> 6) & 0x01];
			img_data[di++] = pal[(image[si] >> 5) & 0x01];
			img_data[di++] = pal[(image[si] >> 4) & 0x01];
			img_data[di++] = pal[(image[si] >> 3) & 0x01];
			img_data[di++] = pal[(image[si] >> 2) & 0x01];
			img_data[di++] = pal[(image[si] >> 1) & 0x01];
			img_data[di++] = pal[(image[si]     ) & 0x01];
			si++;
		}
	}
	else if ((_data_format == ENCODE_FORMAT_I256) && USE_ENCODE_FORMAT_I256)
	{
		// 1 pixel/char, max 256 colors...
		while (di < ds)
			img_data[di++] = pal[image[si++]&0xFF];
		//	for (int ii = sizeX * sizeY - 1; ii >= 0; ii--)
		//		img_data[ii] = pal[image[ii]&0xFF];
	}
	
	//	System.out.println("...DecodeImage("+module+", 0x"+Integer.toHexString(flags)+")");
	return (GL_NEW(memoryType)CMutableImage(sizeX, sizeY, pitch, bpp, img_data));
}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void SetColor(int index, short color)
{
//	_font_color =
_pal[_crt_pal][index] = color;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

	void SetColor(int index, int color)
	{
	//	_font_color =
		_pal[_crt_pal][index] = (short)(((((color & 0xFF000000)>>24) & 0xF0)<<8) |
	   						  			((((color & 0x00FF0000)>>16) & 0xF0)<<4) |
							  			((((color & 0x0000FF00)>>8 ) & 0xF0)   ) |
							 			((((color & 0x000000FF)    ) & 0xF0)>>4));
	}

////////////////////////////////////////////////////////////////////////////////////////////////////

	void SetColor(int index, int a, int r, int g, int b)
	{
	//	_font_color =
		_pal[_crt_pal][index] = (short)(((a & 0xF0)<<8) |
	   						  			((r & 0xF0)<<4) |
							  			((g & 0xF0)   ) |
							 			((b & 0xF0)>>4));
	}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
// Draw String System...

//private void DRAW_STRINGS_SYSTEM___() {}

////////////////////////////////////////////////////////////////////////////////////////////////////

	//	_modules_w[0] . w  . width of the space character (' ')
	//	_modules_h[0] . h  . height of a text line
	//	_fmodules[0*4+1] . ox . space between two adiacent chars
	//	_fmodules[0*4+2] . oy . base line offset

	// Used to gather dimensions of a string...
	// (call UpdateStringSize() to update these values)

////////////////////////////////////////////////////////////////////////////////////////////////////
// To define before include:
// STRING_TYPE
// STRING_LENGTH(s)
// STRING_CHARAT(s,i)

////////////////////////////////////////////////////////////////////////////////////////////////////

//void CSprite::UpdateStringSize(char* s, bool interpretSpecialChar)
//{
//	//	if (DEF::bASSERT) DBG.ASSERT(_map_char != NULL, "_map_char != NULL");
//
//
//	const int spacing = getFmoduleData(0,1);
//
//
//	m_pGame->_text_w = 0;
//	m_pGame->_text_h = (_modules_h[0]&0xFF);
//	
//	int index1 = ((m_pGame->_index1 >= 0) ? m_pGame->_index1 : 0);
//	int index2 = ((m_pGame->_index2 >= 0) ? m_pGame->_index2 : STRLEN(s));
//	int tw = GetStringSize(s, index1, index2, interpretSpecialChar, true);
//	if (tw > m_pGame->_text_w) m_pGame->_text_w = tw;
//	if (m_pGame->_text_w > 0) m_pGame->_text_w -= spacing;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////

// NOTE : If you set interpretNewLine at True, this will change global height and probably scrap  
//        all draw text that using this variable.
//		  So, if you only want to get string width, don't enable this parameter.

//int CSprite::GetStringSize(char* s, int index1, int index2, bool interpretSpecialChar, bool interpretNewLine)
//{
//	
//	const int spacing = getFmoduleData(0,1);
//	
//	
//	int tw = 0;
//	index1 = (index1 >= 0 ? index1 : 0);
//	index2 = (index2 >= 0 ? index2 : STRLEN(s));
//	
//	for (int i = index1; i < index2; i++)
//	{
//		int c = s[i];
//		
//		
//		if (c == '^') // (^)(char)(Text)
//		{
//			i++;
//			if(interpretSpecialChar)
//			{
//				InterpretStringSpecialChar((char)s[i]);
//			}						
//			continue;
//		}
//		if (c > 32)
//		{
//			if (DEF::bErr)
//			{
//				if (c > 255)
//				{
//					//System.out.println("Unknown char: " + c);
//					ASSERT(false);
//					c = 0;
//				}
//				if (_map_char == NULL)
//				{
//					ASSERT(false);
//					//System.out.println("ERROR: _map_char is NULL !!!");
//					break;
//				}
//			}
//			c = _map_char[c]&0xFF;
//		}
//		else if (c == ' ')
//		{
//			tw += (_modules_w[0]&0xFF) + spacing;
//			continue;
//		}
//		else if (c == '\n')
//		{
//			if( interpretNewLine )
//			{
//				if (tw > m_pGame->_text_w) m_pGame->_text_w = tw;
//				tw = 0;
//				m_pGame->_text_h += _line_spacing + (_modules_h[0]&0xFF);
//			}
//			continue;
//		}
//		else // if (c < 32)
//		{
//			// TO REMOVE IF UNUSED !!!!!!!
//			if (c == 0x0001) // auto change current palette
//			{
//				i++;
//				//	_crt_pal = STRING_CHARAT(s,i);
//				continue;
//			}
//			else if (c == 0x0002) // select fmodule
//			{
//				i++;
//				c = s[i];
//			}
//			else continue;
//			// TO REMOVE IF UNUSED !!!!!!!
//		}
//		
//		if (DEF::bErr)
//		{
//			if (c >= GetFModules(0))
//			{
//				//System.out.println("Character not available: c = "+c);
//				ASSERT(false);
//				c = 0;
//			}
//		}
//		
//		
//		int m = getFmoduleData(c,0);
//		
//		
//		if (DEF::bErr)
//		{
//			if (m >= _nModules)
//			{
//				//	System.out.println("Character module not available: c = "+c+"  m = "+m);
//				m = 0;
//				c = 0;
//			}
//		}		
//		tw += (_modules_w[m]&0xFF) - getFmoduleData(c,1) + spacing;	
//	}
//	return tw;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////

//void CSprite::DrawString(CGraphics* g, char* s, int x, int y, int anchor)
//{
//	//	if (DEF::bASSERT) DBG.ASSERT(_map_char != NULL, "_map_char != NULL");
//
//	const int spacing = getFmoduleData(0,1);
//	y -= getFmoduleData(0,2);
//	
//	
//	if ((anchor & (CGraphics::RIGHT | CGraphics::HCENTER | CGraphics::BOTTOM | CGraphics::VCENTER)) != 0)
//	{
//		UpdateStringSize(s, false);
//		if ((anchor & CGraphics::RIGHT)   != 0)	x -= m_pGame->_text_w;
//		else if ((anchor & CGraphics::HCENTER) != 0)	x -= m_pGame->_text_w>>1;
//		if ((anchor & CGraphics::BOTTOM)  != 0)	y -= m_pGame->_text_h;
//		else if ((anchor & CGraphics::VCENTER) != 0)	y -= m_pGame->_text_h>>1;
//	}
//	
//	int xx = x;
//	int yy = y;
//	
//	int old_pal = _crt_pal;
//	
//	int index1 = ((m_pGame->_index1 >= 0) ? m_pGame->_index1 : 0);
//	int index2 = ((m_pGame->_index2 >= 0) ? m_pGame->_index2 : STRLEN(s));
//	
//	
//	for (int i = index1; i < index2; i++)
//	{
//		
//		
//		int c = s[i];
//		
//		if (c > 32)
//		{
//			
//			if (c == '^') // (^)(char)(Text)
//			{
//				i++;
//				InterpretStringSpecialChar((char)s[i]);					
//				continue;
//			}
//			
//			
//			if (DEF::bErr)
//			{
//				if (c > 255)
//				{
//					//System.out.println("Unknown char: " + c);
//					c = 0;
//				}
//				if (_map_char == NULL)
//				{
//					//System.out.println("ERROR: _map_char is NULL !!!");
//					break;
//				}
//			}
//			//            System.out.print("car = " + (char)c + " : " + c);     //  to help looking for missing/bad characters in sprite
//			c = _map_char[c]&0xFF;
//			//            System.out.println(" => " + c);                       //  to help looking for missing/bad characters in sprite
//		}
//		else if (c == ' ')
//		{
//			xx += (_modules_w[0]&0xFF) + spacing;
//			continue;
//		}
//		else if (c == '\n')
//		{
//			
//			
//			xx = x;
//			yy += _line_spacing + (_modules_h[0]&0xFF);
//			continue;
//		}
//		else // if (c < 32)
//		{
//			// TO REMOVE IF UNUSED !!!!!!!
//			if (c == 0x0001) // auto change current palette ^number
//			{
//				i++;
//				_crt_pal = s[i];
//				continue;
//			}
//			else if (c == 0x0002) // select fmodule
//			{
//				i++;
//				c = s[i];
//			}
//			else continue;
//			// TO REMOVE IF UNUSED !!!!!!!
//		}
//		
//		if (DEF::bErr)
//		{
//			if (c >= GetFModules(0))
//			{
//				//System.out.println("Character not available: c = "+c);
//				c = 0;
//			}
//		}
//		
//		
//        int fmodule = c;	//	default is no hyperframe FModule
//		if( (getFmoduleData(c,3) & FLAG_HYPER_FM) != 0 )
//		{
//			//	this FModule is an hyperframe (one hyperframe level permitted only)
//			fmodule = _frames_fm_start[getFmoduleData(c, 0)];
//		}
//		int m = getFmoduleData(fmodule,0);
//		
//		
//		if (DEF::bErr)
//		{
//			if (m >= _nModules)
//			{
//                //System.out.println("Character module not available: c = "+c+"  m = "+m);
//				m = 0;
//				c = 0;
//			}
//		}
//		
//		PaintFModule(g, 0, c, xx, yy, 0, 0, 0);
//		
//		
//		xx += (_modules_w[m]&0xFF) - getFmoduleData(c,1) + spacing; 
//		
//		
//	}
//	
//	
//	_crt_pal = old_pal;
//}

//int CSprite::DrawPage(CGraphics* g, char* s, int x, int y, int anchor)
//{
//	// Count lines...
//	int lines = 0;
//	int len = STRLEN(s);
//	int* off = GL_NEW(POOL_TOP) int[100];
//	MEMSET(off, 0, 100*sizeof(int));
//	
//	int th = _line_spacing + (_modules_h[0]&0xFF);
//	int textHeight = 0;
//
//	for (int i = 0; i < len; i++)
//	{
//		if (s[i] == '\n')
//		{
//			off[lines++] = i;
//			textHeight += th;
//		}
//	}
//	off[lines++] = len;
//
//	if ((anchor & CGraphics::BOTTOM)  != 0)	y -= textHeight;
//	else if ((anchor & CGraphics::VCENTER) != 0)	y -= (textHeight >> 1);
//
//	// Draw each line...
//	for (int j = 0; j < lines; j++)
//	{
//		m_pGame->_index1 = (j > 0) ? off[j-1]+1 : 0;
//		m_pGame->_index2 = off[j];
//		DrawString(g, s, x, y, anchor);
//		y += th;
//	}
//	SAFE_DELETE(off);
//	// Disable substring...
//	m_pGame->_index1 = -1;
//	m_pGame->_index2 = -1;
//	return lines;
//}


// To define before include:
// STRING_TYPE
// STRING_LENGTH(s)
// STRING_CHARAT(s,i)

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void CSprite::UpdateStringSize(char* s, bool interpretSpecialChar)
{
	const int spacing = getFmoduleData(0,1);


	_text_w = 0;
	_text_h = (_modules_h[0]&0xFF);
	
	int index1 = ((_index1 >= 0) ? _index1 : 0);
	int index2 = ((_index2 >= 0) ? _index2 : STRLEN(s));
	int tw = GetStringSize(s, index1, index2, interpretSpecialChar, true);
	if (tw > _text_w) _text_w = tw;
	if (_text_w > 0) _text_w -= spacing;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// NOTE : If you set interpretNewLine at True, this will change global height and probably scrap  
//        all draw text that using this variable.
//		  So, if you only want to get string width, don't enable this parameter.

int CSprite::GetStringSize(char* s, int index1, int index2, bool interpretSpecialChar, bool interpretNewLine)
{
	
	const int spacing = getFmoduleData(0,1);
	
	
	int tw = 0;
	index1 = (index1 >= 0 ? index1 : 0);
	index2 = (index2 >= 0 ? index2 : s.length);
	
	for (int i = index1; i < index2; i++)
	{
		int c = (s[i]&0xFF);
		
		
		if (c == '^') // (^)(char)(Text)
		{
			i++;
			if(interpretSpecialChar)
			{
				InterpretStringSpecialChar((char)(s[i]&0xFF));
				
				
			}						
			continue;
		}
		
		
		if (c > 32)
		{
			if (DEF::bErr)
			{
				if (c > 255)
				{
					//System.out.println("Unknown char: " + c);
					c = 0;
				}
				if (_map_char == NULL)
				{
					//System.out.println("ERROR: _map_char is NULL !!!");
					break;
				}
			}
			c = _map_char[c]&0xFF;
		}
		else if (c == ' ')
		{
			tw += (_modules_w[0]&0xFF) + spacing;
			continue;
		}
		else if (c == '\n')
		{
			if( interpretNewLine )
			{
				if (tw > _text_w) _text_w = tw;
				tw = 0;
				_text_h += _line_spacing + (_modules_h[0]&0xFF);
			}
			continue;
		}
		else // if (c < 32)
		{
			// TO REMOVE IF UNUSED !!!!!!!
			if (c == 0x0001) // auto change current palette
			{
				i++;
				//	_crt_pal = STRING_CHARAT(s,i);
				continue;
			}
			else if (c == 0x0002) // select fmodule
			{
				i++;
				c = (s[i]&0xFF);
			}
			else continue;
			// TO REMOVE IF UNUSED !!!!!!!
		}
		
		if (DEF::bErr)
		{
			if (c >= GetFModules(0))
			{
				//System.out.println("Character not available: c = "+c);
				c = 0;
			}
		}
		
		
		int m = getFmoduleData(c,0);
		
		
		if (DEF::bErr)
		{
			if (m >= _nModules)
			{
				//System.out.println("Character module not available: c = "+c+"  m = "+m);
				m = 0;
				c = 0;
			}
		}
		
		
		tw += (_modules_w[m]&0xFF) - getFmoduleData(c,1) + spacing;
		
		
	}
	
	return tw;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CSprite::DrawString(CGraphics* g, char* s, int x, int y, int anchor)
{
	//	if (DEF::bASSERT) DBG.ASSERT(_map_char != NULL, "_map_char != NULL");


	const int spacing = getFmoduleData(0,1);
	y -= getFmoduleData(0,2);


	if ((anchor & (CGraphics::RIGHT | CGraphics::HCENTER | CGraphics::BOTTOM | CGraphics::VCENTER)) != 0)
	{
		UpdateStringSize(s, false);
				if ((anchor & CGraphics::RIGHT)   != 0)	x -= _text_w;
		else if ((anchor & CGraphics::HCENTER) != 0)	x -= _text_w>>1;
				if ((anchor & CGraphics::BOTTOM)  != 0)	y -= _text_h;
		else if ((anchor & CGraphics::VCENTER) != 0)	y -= _text_h>>1;
	}

	int xx = x;
	int yy = y;

	int old_pal = _crt_pal;

	int index1 = ((_index1 >= 0) ? _index1 : 0);
	int index2 = ((_index2 >= 0) ? _index2 : STRLEN(s));

	
	for (int i = index1; i < index2; i++)
	{
		

		int c = (s[i]&0xFF);

		if (c > 32)
		{
			
				if (c == '^') // (^)(char)(Text)
				{
					i++;
					

					InterpretStringSpecialChar((char)(s[i]&0xFF));					
					
					
					continue;
				}


			if (DEF::bErr)
			{
				if (c > 255)
				{
					//System.out.println("Unknown char: " + c);
					ASSERT(false);
					c = 0;
				}
				if (_map_char == NULL)
				{
					System.out.println("ERROR: _map_char is NULL !!!");
					break;
				}
			}
//            System.out.print("car = " + (char)c + " : " + c);     //  to help looking for missing/bad characters in sprite
			c = _map_char[c]&0xFF;
//            System.out.println(" => " + c);                       //  to help looking for missing/bad characters in sprite
		}
		else if (c == ' ')
		{
			xx += (_modules_w[0]&0xFF) + spacing;
			continue;
		}
		else if (c == '\n')
		{
			

			xx = x;
			yy += _line_spacing + (_modules_h[0]&0xFF);
			continue;
		}
		else // if (c < 32)
		{
			// TO REMOVE IF UNUSED !!!!!!!
			if (c == 0x0001) // auto change current palette ^number
			{
				i++;
				_crt_pal = (s[i]&0xFF);
				continue;
			}
			else if (c == 0x0002) // select fmodule
			{
				i++;
				c = (s[i]&0xFF);
			}
			else continue;
			// TO REMOVE IF UNUSED !!!!!!!
		}

		if (DEF::bErr)
		{
			if (c >= GetFModules(0))
			{
				//System.out.println("Character not available: c = "+c);
				c = 0;
			}
		}


        int fmodule = c;	//	default is no hyperframe FModule
		if( (getFmoduleData(c,3) & FLAG_HYPER_FM) != 0 )
		{
			//	this FModule is an hyperframe (one hyperframe level permitted only)
			fmodule = _frames_fm_start[getFmoduleData(c, 0)];
		}
		int m = getFmoduleData(fmodule,0);


		if (DEF::bErr)
		{
			if (m >= _nModules)
			{
                //System.out.println("Character module not available: c = "+c+"  m = "+m);
				m = 0;
				c = 0;
			}
		}

		PaintFModule(g, 0, c, xx, yy, 0, 0, 0);


		xx += (_modules_w[m]&0xFF) - getFmoduleData(c,1) + spacing; 


	}

	
	_crt_pal = old_pal;
}

int DrawPage(CGraphics* g, char* s, int x, int y, int anchor)
{
	// Count lines...
	int lines = 0;
	int len = s.length;
	int* off = GL_NEW(POOL_TOP) int[100];
	MEMSET(off, 0, 100*sizeof(int));

	int th = _line_spacing + (_modules_h[0]&0xFF);
	int textHeight = 0;

	for (int i = 0; i < len; i++)
	{
		if ((s[i]&0xFF) == '\n')
		{
			off[lines++] = i;
			textHeight += th;
		}
	}
	off[lines++] = len;

	if ((anchor & CGraphics::BOTTOM)  != 0)	y -= textHeight;
	else if ((anchor & CGraphics::VCENTER) != 0)	y -= (textHeight >> 1);

	// Draw each line...
	for (int j = 0; j < lines; j++)
	{
		_index1 = (j > 0) ? off[j-1]+1 : 0;
		_index2 = off[j];
		DrawString(g, s, x, y, anchor);


		y += th;


	}
	SAFE_DELETE(off);
	// Disable substring...
	_index1 = -1;
	_index2 = -1;

	
	return lines;
}

*/
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// EXTENDED STRING FUNCTIONNALITIES.
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// NOTE : The sprite_string.jpp is "templated" and defines function for both String and char[]...
//        Some of the function defined here  could use the same "template" system to support both types.
//		  But as of now, I don't see a good reason to include BOTH version, so the char[] is defined here directly.
//

////////////////////////////////////////////////////////////////////////////////////////////////////
// Space between two characters...


////////////////////////////////////////////////////////////////////////////////////////////////////


// TODO : Add switch to include or not the extended string functionnalities in game2d code...

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// This GetCharWidth function is mostly a cut & paste of code UpdateStringSize() and DrawString() of sprite_string.jpp...
// TODO : sprite_string.jpp function should use this function ?
//int CSprite::GetCharWidth(int c)
//{
//	if (DEF::bErr)
//	{
//		if (c > 255)
//		{
//			//System.out.println("Unknown char: " + c);
//			c = 0;
//		}
//		
//		if (_map_char == NULL)
//		{
//			//System.out.println("ERROR: _map_char is NULL !!!");
//			return 0;
//		}
//		
//		if (c >= GetFModules(0))
//		{
//			//System.out.println("Character not available: c = "+c);
//			return 0;
//		}
//	}
//	
//	if (c > 32)
//	{
//		c = _map_char[c]&0xFF;	
//		
//		
//		int m = getFmoduleData(c,0);		//	module index for this char
//		
//		if (DEF::bErr)
//		{
//			if (m >= _nModules)
//			{
//				//System.out.println("Character module not available: c = "+c+"  m = "+m);
//				m = 0;
//				c = 0;
//			}
//		}
//		
//		return (_modules_w[m]&0xFF) - getFmoduleData(c,1) + getFmoduleData(0,1);
//	}
//	else if (c == ' ')
//	{
//		return (_modules_w[0]&0xFF) + getFmoduleData(0,1);	
//	}
//
//
//	return 0;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//int CSprite::GetCharHeight(int c)
//{
//	if (DEF::bErr)
//	{
//		if (c > 255)
//		{
//			//System.out.println("Unknown char: " + c);
//			c = 0;
//		}
//
//		if (_map_char == NULL)
//		{
//			//System.out.println("ERROR: _map_char is NULL !!!");
//			return 0;
//		}
//
//		if (c >= GetFModules(0))
//		{
//			//System.out.println("Character not available: c = "+c);
//			return 0;
//		}
//	}
//
//	if (c > 32)
//	{		
//		c = _map_char[c]&0xFF;		
//		int m = (_fmodules[c<<2]&0xFF);
//
//		if (DEF::bErr)
//		{
//			if (m >= _nModules)
//			{
//				//System.out.println("Character module not available: c = "+c+"  m = "+m);
//				m = 0;
//				c = 0;
//			}
//		}
//
//		return (_modules_h[m]&0xFF) - _fmodules[(c<<2)+1] + _fmodules[1];	
//	}
//	else if (c == ' ')
//	{
//		return (_modules_h[0]&0xFF) + _fmodules[1];	
//	}
//	
//	return 0;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//int CSprite::GetCharOY(int c)
//{
//	if (DEF::bErr)
//	{
//		if (c > 255)
//		{
//			//System.out.println("Unknown char: " + c);
//			c = 0;
//		}
//
//		if (_map_char == NULL)
//		{
//			//System.out.println("ERROR: _map_char is NULL !!!");
//			return 0;
//		}
//
//		
//		if (c >= GetFModules(0))
//		{
//			//System.out.println("Character not available: c = "+c);
//			return 0;
//		}
//		
//	}
//
//	if (c > 32)
//	{		
//		c = _map_char[c]&0xFF;		
//		int m = (_fmodules[c<<2]&0xFF);
//
//		if (DEF::bErr)
//		{
//			if (m >= _nModules)
//			{
//				//System.out.println("Character module not available: c = "+c+"  m = "+m);
//				m = 0;
//				c = 0;
//			}
//		}
//
//		return (_fmodules[(c<<2)+2] + _fmodules[1]);	
//	}
//	else if (c == ' ')
//	{
//		return (_modules_h[0]&0xFF) + _fmodules[1];	
//	}
//	
//	return 0;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//int CSprite::GetSubStringWidth(char* text, int startIndex, int endIndex)
//{
//	int i1 = m_pGame->_index1;
//	int i2 = m_pGame->_index2;
//	int tw = m_pGame->_text_w;
//	int width = 0;
//	
//	SetSubString(startIndex, endIndex+1);
//	UpdateStringSize(text, true);
//	
//	width = m_pGame->_text_w;
//	m_pGame->_index1 = i1;
//	m_pGame->_index2 = i2;
//	m_pGame->_text_w = tw;
//	
//	
//	const int spacing = getFmoduleData(0,1);
//	
//	
//	width += spacing;
//	return width;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//int CSprite::FindWordEnd(char* text, int startOffset)
//{
//	int text_length = STRLEN(text);
//	if( startOffset >= text_length)
//	{
//		return -1;
//	}
//
//	while(startOffset < text_length)
//	{
//		if(text[startOffset] == ' ' || text[startOffset] == '\n')
//		{
//			return startOffset-1;
//		}
//		startOffset++;
//	}
//	
//	return text_length - 1;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//int CSprite::WrapText(char* text, int maxWidth)
//{
//    return WrapText(text, maxWidth, true);
//}
    
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//	#define WrapText_DEBUG

//int CSprite::WrapText(char* text, int maxWidth, bool unwrap)
//{
//
//	int text_length = STRLEN(text);
//    if( unwrap )
//    {
//		UnwrapText(text);
//    }
//	int wordEnd, wordWidth;
//	int lineWidth = 0;
//	int numLine   = 1;
//	
//    int currentIndex = 0;
//    while( currentIndex < text_length )
//    {
//        char c = text[currentIndex];
//        if( c == '\n' )
//        {
//			lineWidth = 0;
//			++numLine;
//            currentIndex++;     //  skip newline char
//        }
//        else if( c == ' ' )
//        {
//            //  we assume that spaces can't fit a whole line
//            lineWidth += GetCharWidth(' ');
//            currentIndex++;     //  skip space char
//        }
//        else
//        {
//			wordEnd = FindWordEnd(text, currentIndex);
//			wordWidth = GetSubStringWidth(text, currentIndex, wordEnd);
//			
//			if( wordEnd == text_length - 1)	//	do not add letter spacing at end of text
//			{
//				wordWidth -= _fmodules[1];
//				
//
//			}
//
//		    lineWidth += wordWidth;
//		    if(lineWidth > maxWidth)
//		    {
//
//
//				if(currentIndex > 0)	//	can't wrap on first word...
//				{
//					text[currentIndex - 1] = '\n';
//					lineWidth = wordWidth;
//					++numLine;
//				}
//		    }
//            currentIndex = wordEnd + 1;     //  skip word
//        }
//    }
//	return numLine;
//}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//void CSprite::UnwrapText(char* text)
//{
//	for(int i = 0; i < (int)STRLEN(text); ++i)
//	{
//		if(text[i] == '\n')
//		{
//			text[i] = ' ';
//		}
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

//private void ___DRAW_STRINGS_SYSTEM() {}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Palette generation based on other palette...

// -1 - original colors
//  0 - invisible (the sprite will be hidden)
//  1 - red-yellow
//  2 - blue-cyan
//  3 - green
//  4 - grey

//int* CSprite::GenPalette(int type, int* pal, int pal_length, int**new_pal, MemoryType memoryType)
//{
//	if (type <  0) return pal;	// original
//	if (type == 0) return NULL; // invisible
//	
//	if(*new_pal == NULL)
//	{
//		*new_pal = GL_NEW(memoryType) int[pal_length];
//		MEMSET(*new_pal, 0, sizeof(int)*pal_length);
//	}
//	switch (type)
//	{
//	/*			case 1: // red - yellow
//				for (int i = 0; i < pal.length; i++)
//				new_pal[i] = (pal[i] | 0x00FF3300) & 0xFFFFFF00;
//				break;
//				
//				  case 2: // blue - cyan
//				  for (int i = 0; i < pal.length; i++)
//				  new_pal[i] = (pal[i] | 0x000033FF) & 0xFF00FFFF;
//				  break;
//				  
//					case 3: // green
//					for (int i = 0; i < pal.length; i++)
//					new_pal[i] = (pal[i] | 0x00000000) & 0xFF00FF00;
//					break;
//		*/
//	case 4: // grey (desaturate)
//		for (int i = 0; i < pal_length; i++)
//		{
//			int a = (pal[i] & 0xFF000000);
//			int r = (pal[i] & 0x00FF0000) >> 16;
//			int g = (pal[i] & 0x0000FF00) >> 8;
//			int b = (pal[i] & 0x000000FF);
//			int l = ((r + b + g) / 3) & 0x000000FF;
//			*new_pal[i] = ((l << 16) | (l << 8) | l | a);
//		}
//		break;
//		/*
//		case 5: // blend with black 50%
//		for (int i = 0; i < pal.length; i++)
//		{
//		int a = (pal[i] & 0xFF000000);
//		int r = (pal[i] & 0x00FC0000) >> 2;
//		int g = (pal[i] & 0x0000FC00) >> 2;
//		int b = (pal[i] & 0x000000FC) >> 2;
//		new_pal[i] = (a | r | g | b);
//		}
//		break;
//		*/		
//	}
//		
//	return *new_pal;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprite lib...
/*
static Sprite[] _sprites;

////////////////////////////////////////////////////////////////////////////////////////////////////

	static Sprite Lib_GetSprite(int index)
	{
		if (index < 0 || index >= _sprites.length)
		return NULL;
		return _sprites[index];
		}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//void CSprite::InterpretStringSpecialChar(char specialChar)
//{		
//	// 0 to 9 ==> switch to palette 0 to 9 (if possible)...
//	if(specialChar >= '0' && specialChar <= '9')
//	{
//		int palette = specialChar - '0';
//		if( palette < _palettes )
//		{
//			_crt_pal = palette;
//		}
//		else
//		{
//			//If palette not available, take the last one ?
//			_crt_pal = _palettes - 1;
//		}
//	}
//	else if(specialChar == 'H') //highlight start
//	{
//		
//	}
//	else if(specialChar == 'h') //highlight end
//	{
//		
//	}
//
//}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//void CSprite::PaintAFrameSafe (CGraphics* g, int anim, int aframe, int posX, int posY)
//{
//	if ( anim < _anims_naf_length )
//	{
//		const int maxFrame = ( _anims_naf[anim] & 0xFF ) - 1;
//		PaintAFrame(g, anim, (aframe <= maxFrame) ? aframe : maxFrame, posX, posY, 0,0,0);
//	}
//}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//void CSprite::PaintFrameSafe (CGraphics* g, int frame, int posX, int posY)
//{
//	if ( frame < _frames_nfm_length )
//	{
//		PaintFrame(g, frame, posX, posY, 0,0,0);
//	}
//}

//void CSprite::SetSubString(int i1, int i2)
//{
//	m_pGame->_index1 = i1;
//	m_pGame->_index2 = i2;
//}

int CSprite::GetAnimFrameOffsetX(int anim, int aframe)
{
	return _aframes[((_anims_af_start[anim] + aframe) * 5) + 2];
}

int CSprite::GetAnimFrameOffsetY(int anim, int aframe)
{
	return _aframes[((_anims_af_start[anim] + aframe) * 5) + 3];
}

int CSprite::Str_GetCharModule(int c)
{	
	if (c < 0)
	{
		c = (c & 0xFF);
	}
	
	if( c < 0 || c >= _map_char_length)
	{			
		c = ' ';
	}
	
	if(_map_char[c] < 0 )
	{			
		c = ' ';
	}
	c = _map_char[c];
	return GetFrameZeroModule(c);
}

int CSprite::GetFrameZeroModule(int index)
{
	//NOTE : THIS IS HOW THE FORMER AURORA IMPLEMENTATION 
	// FOUND THE CHARACTER MODULE...
	//

    int fmodule = index;	//	default is no hyperframe FModule
	if( (_fmodules[(index<<2) + 3] & FLAG_HYPER_FM) != 0 )
	{
		//	this FModule is an hyperframe (one hyperframe level permitted only)
		fmodule = _frames_fm_start[_fmodules[index<<2]&0xFF];
	}
	int m = _fmodules[fmodule<<2]&0xFF;

	return m;
}

void CSprite::Str_Init()
{
	//Harcoded initilization.
	m_nStrCharSpacing	= 1;
	m_nStrSpaceSize		= GetModuleWidth(0);
	m_nStrLineSpacing	= Str_GetFontHeight();

	if(k_UseEscapeCharacter)
	{//MF here 3 pointer redefine so memory leak 
		m_pGame->s_DigitString = (GL_NEW(GLOBAL_TOP) char[SpriteStringConfig::EscapeDigitsMaxDigits + 1]);
		m_pGame->s_DigitValues = (GL_NEW(GLOBAL_TOP) int [SpriteStringConfig::MaxEscapedDigits]);
		m_pGame->s_StringIDs = (GL_NEW(GLOBAL_TOP) int [SpriteStringConfig::MaxEscapedStrings]);
	}
	if (m_fontType == FontType::Frames)
	{
		PreCalculateAllFrameRects();
	}
}

void CSprite::Str_SetEscapedStringID(int strID, int index)
{
	USE_m_pGAME;
	m_pGame->s_StringIDs[index] = strID;
	m_pGame->m_nCurrentlyEscapeString = 0;	//if you call this it means you will draw a string with escaped digit, reset this...
}

int CSprite::Str_GetFontHeight()
{
	//fix this.
	return GetModuleHeight(0);
}

int CSprite::Str_DrawString(CGraphics& g, char* str, int x, int y, int flags)
{
	return Str_DrawSubString(g, str, x, y, flags, 0, Str_GetStringLen(str));	
}

int CSprite::Str_DrawSubString(CGraphics& g, char* str, int x, int y, int flags, int firstIndex, int size)
{
	//ADD ASSERT HERE.
	int endIndex = firstIndex + size;
	 ;
	 ;

	char curChar, nextChar;
	int curOffsetX;
	int curX = x;
	int curY = y;

	//ANCHOR STUFF
	if ((flags & (SpriteStringFlags::Right | SpriteStringFlags::HCenter)) != 0)
	{
		int strW = Str_GetSubStringWidth(str, firstIndex, size);		
		if ((flags & SpriteStringFlags::Right)   != 0)	
		{
			curX -= strW;
		}
		else// if ((flags & SpriteStringFlags::HCenter) != 0)	
		{
			curX -= (strW>>1);
		}
	}
	
	//ANCHOR STUFF
	if((flags & (SpriteStringFlags::Bottom | SpriteStringFlags::VCenter)) != 0)		
	{
		int strH = Str_GetFontHeight();
		if ((flags & SpriteStringFlags::Bottom)  != 0)	
		{
			curY -= strH;
		}
		else// if ((flags & SpriteStringFlags::VCenter) != 0)	
		{
			curY -= (strH>>1);
		}
	}

	for(;firstIndex < endIndex; firstIndex++)
	{
		curChar = str[firstIndex];
		
		if(k_UseEscapeCharacter)
		{			
			if(curChar == k_EscapeCharacterPrefix)
			{
				nextChar = str[++firstIndex];
				if( InterpretSpecialCharacter( nextChar ) )
				{					
					//Reset substring anchor flags to Top, Left since we allready did the transformation for parent string.
					char* str1 = GetSpecialCharacterString( nextChar);
					curX += Str_DrawString(g, str1, curX, curY, SpriteStringFlags::Left | SpriteStringFlags::Top);
				}
				continue;
			}
		}
		
		curOffsetX = Str_GetCharacterWidth( curChar );
		if(curOffsetX > 0)	//width <= 0 ==> don't need to draw anything!
		{		
			if (m_fontType == FontType::Frames)
			{
				PaintFrame(&g, Str_GetCharFrame(curChar), curX, curY, 0, 0, 0);
			}
			else
			{
				PaintModule( &g, Str_GetCharModule( curChar ), curX, curY, 0);
			}
			curX += curOffsetX + m_nStrCharSpacing;
		}	
	}

	return curX - x;
}

int CSprite::Str_GetCharacterWidth(int c)
{	
	//Special cases character.
	if(c == ' ')
	{
		return m_nStrSpaceSize;
	}
	else if(c == '\n')
	{
		return 0;
	}
	else if(k_UseEscapeCharacter && c == k_EscapeCharacterPrefix)
	{
		//FIX ME
		//The escape character value will still be counter in the string width.
		return 0;
	}
	
	//Normal case
	const int k_nInvalidCharacterMapping = -1;
	if (m_fontType == FontType::Frames)
	{
		int frame = Str_GetCharFrame(c);
		return (frame == k_nInvalidCharacterMapping) ? 0 : (_frames_rc[frame*4 + 2]&0xFF)/*GetFrameWidth(frame)*/;
	}
	else
	{	
		int module = Str_GetCharModule(c);		
		return (module == k_nInvalidCharacterMapping) ? 0 : GetModuleWidth(module);
	}
}

int CSprite::Str_GetSubStringWidth(char* str, int firstIndex, int size)
{
	//add assert here.
	int strSize = 0;
	int endIndex = firstIndex + size;
	int tempStringPtr = m_pGame->m_nCurrentlyEscapeString;
	int tempDigitPtr = m_pGame->m_nCurrentlyEscapeDigit;

	while(firstIndex < endIndex)
	{
		strSize += (Str_GetCharacterWidth( str[firstIndex] ) + m_nStrCharSpacing);
		
		if(k_UseEscapeCharacter)
		{			
			if(str[firstIndex] == k_EscapeCharacterPrefix)
			{
				char nextChar = str[++firstIndex];
				if( InterpretSpecialCharacter( nextChar ) )
				{
					strSize += Str_GetStringWidth(GetSpecialCharacterString( nextChar) );
				}
			}
		}
		firstIndex++;
	}

	m_pGame->m_nCurrentlyEscapeString = tempStringPtr;
	m_pGame->m_nCurrentlyEscapeDigit = tempDigitPtr;

	return strSize - m_nStrCharSpacing;
}

bool CSprite::InterpretSpecialCharacter(char c)
{
	//Remove case sensitiveness.
	int code = (c >= 'a') ? c - 'a' + 'A' : c;
	
	//special cases
	if(code >= '0' && code <= '9')
	{
		//Digit ==> Palette Switch
		SetCurrentPalette(code - '0');
		return false;
	}
	else
	{
		//all the other can be used for game specific replacements
		return true;
	}	
}

void CSprite::SetNumberString(int value)
{
	USE_m_pGAME;
	//TODO: support negative if needed.?

	//Make sure the last byte is the null character so it is interpreted as null-terminated string when drawed...
	// << todo : double check
	//s_DigitString[s_DigitString.length - 1] = '\0';
	// >>

	//special case.
	if(value == 0)
	{
		m_pGame->s_DigitString[0] = '0';
		m_pGame->s_DigitString[1] = '\0';
		return;
	}

	int numDigits = 0;
	while(value > 0)
	{
		m_pGame->s_DigitString[numDigits++]	= (char) ('0' + (value % 10));
		value = value / 10;
	}

	m_pGame->s_DigitString[numDigits] = '\0';
	int middle = numDigits / 2;
	char swapDigit;
	for(int i = 0; i < middle; i++)
	{
		numDigits--;
		swapDigit = m_pGame->s_DigitString[numDigits];
		m_pGame->s_DigitString[numDigits] = m_pGame->s_DigitString[i];
		m_pGame->s_DigitString[i] = swapDigit;		
	}	
	//DBG(" number str result " + new String(s_DigitString));
}

char* CSprite::GetGameSpecificSpecialCharacterString( char c )
{
	//None so far.
	return NULL;
}

char* CSprite::GetSpecialCharacterString( char c )
{
	//Global Special Character interpreting
	if ( ( c == 'd' ) || (c == 'D') )
	{
		SetNumberString( m_pGame->s_DigitValues[m_pGame->m_nCurrentlyEscapeDigit] );
		m_pGame->m_nCurrentlyEscapeDigit++;		
		return m_pGame->s_DigitString;
	}
	else if ( (c == 's') || (c == 'S') )
	{
		//byte [] str;
		char* str = NULL;
		if( m_pGame->s_StringIDs[m_pGame->m_nCurrentlyEscapeString] == EscapedStringSpecialID::VersionNumber)
		{
			//str = cGame.s_midlet.getAppProperty("MIDlet-Version").getBytes();	
			MEMSET( m_pGame->s_SpecialStringBuffer, 0, ARRAY_SIZE(m_pGame->s_SpecialStringBuffer) );

			GetDevice().GetModuleVersion( m_pGame->s_SpecialStringBuffer, ARRAY_SIZE(m_pGame->s_SpecialStringBuffer) );

			str = &(m_pGame->s_SpecialStringBuffer[0]);
		}
		else
		{
			str = m_pGame->GetString( m_pGame->s_StringIDs[m_pGame->m_nCurrentlyEscapeString] );
		}

		m_pGame->m_nCurrentlyEscapeString++;
		return str;
	}
	else if ( (c == 'b') || (c == 'B') )
	{
		return m_pGame->GetString(GLOBAL_SPACE_CHAR);
	}
	else
	{
		return GetGameSpecificSpecialCharacterString(c);
	}
}

int CSprite::Str_GetStringLen( char* str)
{
	DBGPRINTF("double check Str_GetStringLen");
	// todo : double,double check
	return STRLEN(str);
//	 ;
//
//	int len = str.length;
//
//	if(str[len - 1] == '\0')
//	{
//		//loop
//		len = 0;
//		while((len < str.length) && str[len] != '\0')
//		{
//			len++;
//		}
//	}
//
//	return len;
}

int CSprite::Str_GetStringWidth(char* str)
{	
	return Str_GetSubStringWidth(str, 0, Str_GetStringLen(str) ); 
}

int CSprite::Str_DrawText( CGraphics& g, char* str, int x, int y, int flags, int w, int firstLine, int numLines)
{
	int curY = y;
	int strLen = Str_GetStringLen(str);


	int totalLines;

	if((flags & SpriteStringFlags::Wrap) != 0)
	{
		totalLines = Str_WrapText(str, 0 , strLen - 1, w, m_pGame->s_linesBuffer);
	}
	else
	{
		totalLines = StringTokenize(str, 0, strLen - 1, '\n', m_pGame->s_linesBuffer);
	}

	int endLine = (numLines <= 0) ? totalLines : firstLine + numLines;
	 ;

	int lineStartIndex;
	int numLinesToDraw = endLine - firstLine;

	//ANCHOR STUFF
	int totalY;
	if ((flags & SpriteStringFlags::Bottom)  != 0)	
	{
		curY -= (Str_GetLineSpacing() * numLinesToDraw);
	}
	else if ((flags & SpriteStringFlags::VCenter) != 0 && numLinesToDraw > 1)	
	{	
		totalY = (Str_GetLineSpacing() * (numLinesToDraw - 1)) + Str_GetFontHeight();
		curY -= (totalY >> 1);		
		curY += (Str_GetFontHeight() >> 1);
	}

	while(firstLine < endLine)
	{	
		Str_DrawSubString(g, str, x, curY, flags, m_pGame->s_linesBuffer[firstLine] + 1, m_pGame->s_linesBuffer[firstLine+1] - m_pGame->s_linesBuffer[firstLine]);
		curY += m_nStrLineSpacing;
		firstLine++;
	}

	return numLinesToDraw;
}

int CSprite::Str_WrapText(char* str, int index1, int index2, int width, int* indices)
{
	int lines = 0;
	indices[0] = index1 - 1;
	int currentLineW = 0;
	int currentWordW = 0;
	int currentCharW = 0;
	int lastPossibleWrapPos = -1;
	char curChar, nextChar;

	int tempStringPtr = m_pGame->m_nCurrentlyEscapeString;
	int tempDigitPtr = m_pGame->m_nCurrentlyEscapeDigit;

	for (int i = index1; i < index2; i++)
	{
		curChar = str[i];
		currentCharW = Str_GetCharacterWidth(curChar) + m_nStrCharSpacing;

		if(k_UseEscapeCharacter)
		{			
			if(curChar == k_EscapeCharacterPrefix)
			{
				nextChar = str[++i];
				if( InterpretSpecialCharacter( nextChar ) )
				{
					//	If we are replacing a special character with another word
					//  Just try to put the entire "dynamic" text on that line.
					//	Note : This constrains the "dynamic" text to have only 1 word
					//  so the wrap text has expected results.
					//	Since the usage of "dynamic" text is usually for 1 word stuff, (character name, number, etc.)
					//	I believe this should be ok.
					//
					currentCharW = Str_GetStringWidth( GetSpecialCharacterString( nextChar ) );
				}
			}
		}

		currentWordW += currentCharW;
		currentLineW += currentCharW;

		// Test where we can add a line break. (currently only space ...)  
		// Could loop in a array of symbol defined by user.
		if (curChar == ' ')
		{
			lastPossibleWrapPos = i;
			currentWordW = 0;
		}

		//The test lastPossibleWrapPos != -1 is to continue to loop if the first word
		//on the line is larger then the allowed width.  As of now we do not allow wrapping within word so...
		if ( (currentLineW >= width) && (lastPossibleWrapPos != -1))
		{		
			indices[++lines] = lastPossibleWrapPos;			

			//Common resets.
			currentLineW = currentWordW;			
			lastPossibleWrapPos = -1;
		}
		else if(curChar == '\n')
		{
			currentWordW = 0;
			indices[++lines] = i;	

			//Common resets...
			currentLineW = currentWordW;
			lastPossibleWrapPos = -1;
		}
	}

	m_pGame->m_nCurrentlyEscapeString = tempStringPtr;
	m_pGame->m_nCurrentlyEscapeDigit = tempDigitPtr;

	indices[++lines] = index2;
	return lines /*- 1*/;
}

int CSprite::StringTokenize(char* str, int index1, int index2, char token, int* indices)
{
	int lines = 0;
	indices[0] = index1 - 1;
	for (int i = index1; i < index2; i++)
		if (str[i] == token)
			indices[++lines] = i;
	indices[++lines] = index2;
	return lines;
}

void CSprite::Str_SetEscapedDigitValue(int value, int index)
{
	USE_m_pGAME;
	m_pGame->s_DigitValues[index] = value;
	m_pGame->m_nCurrentlyEscapeDigit = 0;	//if you call this it means you will draw a string with escaped digit, reset this...
}

int CSprite::GetAnimTotalTime(int anim)
{
	int numFrames = GetAFrames(anim);
	int timeCounter = 0;
	for(int i = 0; i < numFrames; i++)
	{
		timeCounter += GetAFrameTime(anim, i);
	}
	return timeCounter;
}

int CSprite::Str_GetCharFrame(int c)
{
	if (c < 0)
	{
		c = (c & 0xFF);
	}
	
	if( c < 0 || c >= _map_char_length)
	{			
		c = ' ';
	}
	
	if(_map_char[c] < 0 )
	{			
		c = ' ';
	}
	c = _map_char[c];

	return c;
}

void CSprite::PreCalculateAllFrameRects()
{
	const MemoryType mt = GLOBAL_TOP;
	if( _frames_rc == NULL )
	{
		int numFrames = GetNumFrames();
		_frames_rc = (GL_NEW(mt) char[numFrames*4]);
		int cpt = 0;
		int frameRect[4];
		for (int i = 0; i < numFrames; i++)
		{
			GetFrameRect(frameRect, i, 0, 0, 0, 0, 0);
			for(int j = 0; j < 4; ++j)
			{
				_frames_rc[cpt++] = (char) (frameRect[j] >> FIXED_PRECISION);
			}			
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//not really specific to string but had to code it for them...
int CSprite::GetNumFrames()
{
	return _frames_nfm_length;
}

