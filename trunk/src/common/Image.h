// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Common.h"

enum {
	BBM_PALETTE = 0x01,		//Has palette data
	BBM_COLOR_KEY = 0x02,	//has color key (the transparent color)
	BBM_ALPHA = 0x04,		//has alpha data
	BBM_HAS_MODULE = 0x08,	//has module data
	
	BBM_COMPRESSION_RLE = 0x10,	//the pixel data is compressed by RLE. If has module, it's compressed per module.

	BBM_NIGHTALPHA = 0x20
};

/*
//BBM file format
typedef struct {
	unsigned char bpp;				//bit per pixel
	unsigned char flag;				//bit 0-2: palette location; bit 3-7: bit flag

	unsigned short width;
	unsigned short height;

#if (flag & BBM_COLOR_KEY)
	unsigned int colorKey;			//for indexed pixel, it's the entry in palette; for RGB pixel, it's the RGB number
#endif

#if (flag & BBM_PALETTE_MASK) == BBM_PALETTE_IN_SELF
	unsigned short paletteEntryNumber;	//number of palette entry
	unsigned char paletteEntryData[paletteEntryNumber][3];
#elif (flag & BBM_PALETTE_MASK) == BBM_PALETTE_IN_POOL
	unsigned short paletteIndexNumber;	//number of palette
	unsigned short paletteIndexData[paletteIndexNumber];	//palette index in palette pool
#endif

#if (flag & BBM_HAS_MODULE)
	unsigned short moduleNumber;	//number of module
	unsigned short moduleData[moduleNumber][4];	//module data
#endif

#if (flag & BBM_COMPRESSION_RLE)
	#if (flag & BBM_HAS_MODULE)
		unsigned short moduleRleDataSize[moduleNumber]; //size of each RLE module data
	#else
		unsigned int rleDataSize;
	#endif
#endif

	unsigned char pixelData[width * height * 8 / bpp];

}BBM;*/

class CGraphics;
class CStream;

/// @brief This class is used to hold graphical image data.
///
/// This class provide a set of functions similar to Image class in J2ME.
class CImage
{
public:
	/// @brief Image type
	enum ImageType {
		/// This is an indexed image and can be casted to CIndexedImage.
		TYPE_INDEXED,
		/// The is an image that hold RGB format pixel data and can be casted to CRgbImage. 
		TYPE_RGB,
		/// The is an image that can be changed.
		TYPE_MUTABLE,
		/// The is an image that hold pixel data compressed by RLE and can be casted to CRleImage. 
		TYPE_RLE,

		TYPE_ZDS
	};

	enum {
		TRANSPARENT_COLOR_565 = 0xF81F,
		TRANSPARENT_COLOR_444 = 0x0F0F,
	};

	virtual ~CImage(){}

	/// @brief Creates an immutable image from the named resource.
	///	@param[in]	pResName	the name of the image resource.
	/// @param[in]	memType		the type of memory to hold created image object. Default value is POOL_BOTTOM.
	/// @return The created image. NULL if failed.
	static CImage* CreateImage(const char *pResName, MemoryType memType = POOL_BOTTOM);

	/// @brief Creates an immutable image from a stream.
	///	@param[in]	stream		the stream that containing the image data.
	/// @param[in]	memType		the type of memory to hold created image object. Default value is POOL_BOTTOM.
	/// @return The created image. NULL if failed.
	static CImage* CreateImage(CStream &stream, MemoryType memType = POOL_BOTTOM);

	/// @brief Get the color key of the image.
	///
	/// Color key indicate the color to be used for transparent or translucent effects.
	/// It is RGB value for non-indexed image and palette entry index for indexed image and RLE image.
	/// @return The value of the current color key.
	/// @warning Color key effect is always disabled for image with alpha channel
	unsigned int GetColorKey() const { return m_colorKey; }

	/// @brief Set the color key of the image.
	///
	/// Color key indicate the color to be used for transparent or translucent effects.
	/// It is RGB value for non-indexed image and palette entry index for indexed image and RLE image.
	/// @param key The value of the color key to set.
	/// @warning Color key effect is always disabled for image with alpha channel
	void SetColorKey(unsigned int key) { m_colorKey = key; }

	/// @brief Enable or disable the color key effect of the image.
	///
	/// Color key indicate the color to be used for transparent or translucent effects.
	/// It is RGB value for non-indexed image and palette entry index for indexed image and RLE image.
	/// When color key is disabled, the pixel with the color value of color key is treated as normal one.
	/// @param isEnabled Use true to enable color key, false to disable.
	/// @warning Color key effect is always disabled for image with alpha channel
	void EnableColorKey(bool isEnabled) {
		if(isEnabled)
			m_flag |= BBM_COLOR_KEY;
		else
			m_flag &= ~BBM_COLOR_KEY;
	}
	
	/// @brief Get the number of bit per pixel.
	/// @return The number of bit per pixel.
	int GetBitsPerPixel() const { return m_bpp; }

	/// @brief Get the width of the image in pixels.
	/// @return Width of the image.
	int GetWidth() const { return m_width; }

	/// @brief Get the height of the image in pixels.
	/// @return Height of the image.
	int GetHeight() const {	return m_height; }

	/// @brief Get the distance in bytes to the start of next line
	/// @return Distance in bytes to the start of next line.
	/// @warning Pitch value has no meaning for RLE image
	int GetPitch() const { return m_pitch; }

	/// @brief Check whether the pitch&height is power of 2.
	///
	/// Useful if the image is used as texture in 3D graphics engine.
	/// @return ture if the pitch and height is power of 2, else false.
	bool IsSizePowerOf2() const {return m_sizeShift != 255;}
	
	/// @brief Get the pitch in power of 2.
	///
	/// Useful if the image is used as texture in 3D graphics engine.
	/// If IsSizePowerOf2() returns true, then (1 << GetPitchShift()) == GetPitch().
	/// @return Pitch in power of 2 if IsSizePowerOf2() returns true, else 15.
	unsigned int GetPitchShift() const {return m_sizeShift >> 4;}

	/// @brief Get the height in power of 2.
	///
	/// Useful if the image is used as texture in 3D graphics engine.
	/// If IsSizePowerOf2() returns true, then (1 << GetHeightShift()) == GetHeight().
	/// @return Pitch in power of 2 if IsSizePowerOf2() returns true, else 15.
	unsigned int GetHeightShift() const {return m_sizeShift & 0xf;}

	/// @brief Get the type of image
	/// @return Type of the image define in ImageType.
	int GetType() const { return m_type; }
	
	/// @brief Get the pointer to image pixel data
	/// @return Pointer to the image pixel data.
	unsigned char* GetPixelData() const { return m_pixel; }
	
	unsigned int GetFlag() { return m_flag; }
	//void getRGB(int** rgbData,int offset,int scanlength,int x,int y,int width, int height);

	CImage() {}
	void SetSize(int width, int height, int pitch);
	unsigned char m_type;
	unsigned char m_bpp;				//bit per pixel
	unsigned char m_flag;				//bit 0-2: palette location; bit 3-7: bit flag
	unsigned char m_sizeShift;

	//Transparent color. it's RGB for non-indexed image and palette entry index for indexed image
	unsigned int m_colorKey;

	unsigned char *m_pixel;

	void SetWidth(int width) {
		m_width = width;
	};

	void SetHeight(int height){
		m_height = height;
	};

	void SetPitch(int pitch){
		m_pitch = pitch;
	}
	//CImage& operator=(const CImage& rhs);
private:
	
	unsigned short m_width;
	unsigned short m_height;
	unsigned short m_pitch;				//y pitch in byte
};

/// @brief Represent an indexed image.
class CIndexedImage: public CImage {
public:
	CIndexedImage() {}
	CIndexedImage(CStream &stream);
	virtual ~CIndexedImage();

	/// @brief Get the number of palette entry
	/// @return The number of palette entry
	unsigned int GetPaletteEntryNumber() {
		return m_paletteEntryNumber;
	}

	/// @brief Get the palette data in native pixel format.
	/// @return Pointer to palette data.
	PalettePixel* GetPaletteData() {
		return m_paletteData;
	}

	inline char GetPalMasks(){		
		return ((1 << m_palBits) - 1) & 0xFF;
	}

	inline char GetPalBits(){	//may be greater than 8, should be consider as 7 bit ENCODE_FORMAT_I64RLE
		return m_palBits;
	}

	int GetPaletteEntrySize() {
		return sizeof(PalettePixel);
		//return (sizeof(NativePixel) > 2 || (m_flag & BBM_ALPHA) != 0) ? 4 : 2;
	}

protected:
	unsigned short m_paletteEntryNumber;
	PalettePixel *m_paletteData;
	unsigned char m_palBits;

};

/// @brief Represent a RGB format image.
class CRgbImage: public CImage {
public:
	CRgbImage(CStream &stream);
	CRgbImage(unsigned int w, unsigned int h, unsigned int pitch, int bpp, void* pixel);
	virtual ~CRgbImage();
protected:
	// Should not call this default constructor directly because nothing is done here.
	// This default constructor is provided for derive class like CMutableImage
	CRgbImage(){}

	char m_needFreePixel;
};

/// @brief Represent a mutable image.
///
/// The CMutableImage subclass describes an CImage with an accessible buffer of image data.
/// A CMutableImage is comprised of a CGraphics and a CRgbImage of image data.
/// The location of pixel data can be a specified address passed by parameter, or can be allocated
/// in memory pool by constructor.
class CMutableImage: public CRgbImage {
public:
	/// @brief Create a CMutableImage and attach it to a buffer on given address.
	/// @param[in]	w	Width of the mutable image
	///	@param[in]	h	Height of the mutable image
	///	@param[in]	pitch	Distance in bytes to the start of next line.
	///	@param[in]	bpp	Bit per pixel of the pixel buffer
	///	@param[in]	pixel	Pointer to pixel data
	CMutableImage(unsigned int w, unsigned int h, unsigned int pitch, int bpp, void* pixel);

	/// @brief Create a CMutableImage on memory pool with given format.
	/// @param[in]	w	Width of the mutable image
	///	@param[in]	h	Height of the mutable image
	///	@param[in]	bpp	Bit per pixel of the pixel buffer
	///	@param[in]	memType	Memory type of the pixel data
	CMutableImage(unsigned int w, unsigned int h, int bpp, MemoryType memType = POOL_BOTTOM);
	virtual ~CMutableImage();

	/// @brief Get the Graphics object that renders to this image.
	///
	/// The newly created Graphics object has the following properties: 
	/// - the destination is this Image object; 
	/// - the clip region encompasses the entire Image; 
	/// - the current color is black; 
	/// - the origin of the coordinate system is located at the upper-left corner of the Image.
	///
	/// The lifetime of Graphics objects created using this method is the same as this image's.
	/// @warning Unlike the J2ME, this function get the attached Graphics object, instead of create a new one.
	/// @return The Graphics object attached to this image
	CGraphics& GetGraphics() { return *m_graphics; }

protected:
	CGraphics *m_graphics;
};

class CRleImage: public CIndexedImage {
public:
	CRleImage(CStream &stream) { ASSERT(false); }	//not implemented yet
	//	CRleImage(unsigned char bpp, unsigned int flag, unsigned int dataFormat, unsigned int width, unsigned int height,
	//		unsigned int colorKey, unsigned int paletteEntryNumber, PalettePixel *paletteData, unsigned char *pixel);

	static int CalculateBits(int colorCount);

	inline char GetPalMask(){
		int palBits = m_palBits > 8 ? 7 : m_palBits;	//consider values greater than 8 as 7, for old gli engine
		return ((1 << palBits) - 1) & 0xFF;
	}

	//inline char GetPalBits(){	//may be greater than 8, should be consider as 7 bit ENCODE_FORMAT_I64RLE
	//	return m_palBits;
	//}

protected:
	CRleImage() {}
	//unsigned char m_palBits;

};



const int FLAG_16_COLORS = (1 << 0);
const int FLAG_8_COLORS = (1 << 1);
const int FLAG_RLE = (1 << 2);
const int FLAG_RLE_8BITS = (1 << 3);
const int FLAG_RLE_8BITS_FRAME = (1 << 4);
const int FLAG_RLE_8BITS_MODULE = (1 << 5);
const int FLAG_NO_RLE_8BITS_MODULE = (1 << 6);

const int FLAG_MULTIPALETTE = (1 << 8);
const int FLAG_REBUILD_FILE = (1 << 9);
const int FLAG_REBUILD_SIZE = (1 << 10);
const int FLAG_INCLUDE = (1 << 11);
const int FLAG_OPTIM_PAL = (1 << 12);
const int FLAG_EXACT_PAL = (1 << 13);
const int FLAG_4444_FORMAT = (1 << 14);
const int FLAG_565_FORMAT = (1 << 15);
const int FLAG_TRANSPARENT = (1 << 16);
const int FLAG_ALPHA = (1 << 17);
const int FLAG_REBUILD_SPRITE = (1 << 18);
const int FLAG_REBUILD_MODULE = (1 << 19);
const int FLAG_MERGE_PAL = (1 << 20);
const int FLAG_16BIT_4_LEN = (1 << 21);

const int FLAG_REBUILD_FONT = (1 << 29);
const int FLAG_OUTPUT_GLI = (1 << 30);
const int FLAG_OUTPUT_PAL = (1 << 31);

const int MASK_USE_RLE = FLAG_RLE | FLAG_RLE_8BITS | FLAG_RLE_8BITS_FRAME | FLAG_RLE_8BITS_MODULE;

class CGame;
/* 
class CGLI : public CRgbImage
{
public:
	enum
	{
		sf_frameSize = 2,
	};

	CGLI();
	virtual ~CGLI();

	//CGame *m_pGame;


protected:
	unsigned short *m_pals;
	int	m_currentPal;
	short m_pals_length;
	char m_palMask,m_palBits;
	
	int m_frameCount;
	int m_gliFlags;

	int m_gliRebuildWidth;
	int m_gliRebuildHeight;

	char *m_gliImageData;

	unsigned char *m_gliFrames;
	int *m_gliFrameOffsets;

	unsigned int m_nMaxSize;
	unsigned short *m_gliBuf;

	int m_modID;

	int m_paletteEntryNumber;

	void	FreeMem();

	bool	m_bHasDeCompressed;
public:
	void DeCompress();
	void Load(CStream &dis, bool bNeedGLIBuf = true, MemoryType memType = POOL_TOP);
	unsigned short *DeCodeRLE(int frame, int palIndex);

	void ReBuildSize(int modID);
	void ReBuildData(int modID, int palIndex);

	void SetPalette(int pal){ m_currentPal = pal;};
	int GetCurrentPalette(){ return m_currentPal;};

	// using m_currentPal.
	void Draw(CGraphics &g, int modID, int x, int y, int flag);
	
	void Draw(CGraphics &g, int modID, int palIndex, int x, int y, int flag);

	int GetModuleWidth(int modID);
	int GetModuleWidth(int modid, int nKeyColor);
	int GetModuleHeight(int modID);

	unsigned short *GetPal(int id);
	unsigned char *GetRLEData();

	inline char GetPalMask()
	{
		return m_palMask;
	}

	inline char GetPalBits()
	{
		return m_palBits;
	}

	inline int  GetFrameCount()
	{
		return m_frameCount;
	}
};*/

#ifdef ENABLE_ZDS
class CZDS : public CRgbImage
{
public:
	CZDS();
	virtual ~CZDS();

	enum RenderState
	{
		ALPHA_BLEND = 0,
		ADDITIVE,
	};

	void Load(CStream &dis, MemoryType memType = POOL_TOP);

	inline unsigned char * GetAlphaData(){
		return m_alpha;
	};
	
	inline void SetRenderState(RenderState state)
	{
		m_renderState = state;
	}

	inline RenderState GetRenderState()
	{
		return m_renderState;
	}

protected:
	unsigned char *m_alpha;
	RenderState m_renderState;
};
#endif

#endif