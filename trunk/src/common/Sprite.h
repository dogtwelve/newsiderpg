// Sprite.h: interface for the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__A92545D9_C5F6_4B10_80E4_6FCF52A0864A__INCLUDED_)
#define AFX_SPRITE_H__A92545D9_C5F6_4B10_80E4_6FCF52A0864A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game/CGame.h"
//#include "Game/const.h"
#include "Common/Image.h"
#include "Common/Engine.h"
#include "Common/Stream.h"
//////////////////////////////////////////////////
// Set these switches to best suite your game!
// Unused code will be removed by the obfuscator!

const bool USE_MODULE_MAPPINGS	= !true; // use Module Mappings ?
const bool USE_GC_IN_MINMEMCALLS	= !true; // use Module Mappings ?

const bool USE_HYPER_FM			= true; // use Hyper Frame Modules ?

const bool USE_INDEX_EX_FMODULES	= !true; // true|false . max. 1024|256 modules refs. from a FModule
const bool USE_INDEX_EX_AFRAMES	= !true; // true|false . max. 1024|256 frames refs. from an Anim


const bool USE_PRECOMPUTED_FRAME_RECT = !true;

const bool ALWAYS_BS_FRAME_RECTS	= true; 	// all sprites are exported with BS_FRAME_RECTS
const bool ALWAYS_BS_NFM_1_BYTE		= false; // all sprites are exported with BS_NFM_1_BYTE
const bool ALWAYS_BS_SKIP_FRAME_RC	= true; // all sprites are exported with BS_SKIP_FRAME_RC
const bool ALWAYS_BS_NAF_1_BYTE		= false; // all sprites are exported with BS_NAF_1_BYTE


const bool USE_PIXEL_FORMAT_8888		= false;
const bool USE_PIXEL_FORMAT_4444		= true;
const bool USE_PIXEL_FORMAT_1555		= true;
const bool USE_PIXEL_FORMAT_0565		= false;


const bool USE_ENCODE_FORMAT_I2		= true;
const bool USE_ENCODE_FORMAT_I4		= true;
const bool USE_ENCODE_FORMAT_I16		= true;
const bool USE_ENCODE_FORMAT_I256		= true;
const bool USE_ENCODE_FORMAT_I64RLE	= true;
const bool USE_ENCODE_FORMAT_I127RLE	= true;
const bool USE_ENCODE_FORMAT_I256RLE	= true;

const int MAX_SPRITE_PALETTES = 16;
const int MAX_MODULE_MAPPINGS = 16;

//////////////////////////////////////////////////

const short BSPRITE_v003	= (short)0x03DF; // supported version

//////////////////////////////////////////////////
// BSprite flags

const int BS_MODULES			= (1 << 0);
const int BS_MODULES_XY		= (1 << 1);
const int BS_MODULES_IMG		= (1 << 2);
const int BS_MODULES_XY_SHORT		= (1 << 5);		// export x, y for each module as short
const int BS_FRAMES			= (1 << 8);
const int BS_FM_OFF_SHORT	= (1 << 10);    // export fm offsets as shorts
const int BS_NFM_1_BYTE		= (1 << 11);    // export nfm as char
const int BS_SKIP_FRAME_RC	= (1 << 12);    // do not export frame rect
const int BS_ANIMS			= (1 << 16);
const int BS_AF_OFF_SHORT	= (1 << 18);    // export af offsets as shorts
const int BS_NAF_1_BYTE		= (1 << 19);    // export naf as char
const int BS_MODULE_IMAGES	= (1 << 24);
const int BS_PNG_CRC			= (1 << 25);
const int BS_KEEP_PAL		= (1 << 26);
const int BS_TRANSP_FIRST	= (1 << 27);
const int BS_TRANSP_LAST		= (1 << 28);

const int BS_DEFAULT_DOJA	= (BS_MODULES | BS_FRAMES | BS_ANIMS);
const int BS_DEFAULT_MIDP2	= (BS_MODULES | BS_FRAMES | BS_ANIMS | BS_MODULE_IMAGES);
const int BS_DEFAULT_NOKIA	= BS_DEFAULT_MIDP2;
const int BS_DEFAULT_MIDP1	= (BS_MODULES | BS_MODULES_XY | BS_FRAMES | BS_ANIMS);
const int BS_DEFAULT_MIDP1b	= (BS_MODULES | BS_FRAMES | BS_ANIMS | BS_MODULE_IMAGES | BS_PNG_CRC);

//////////////////////////////////////////////////

const short PIXEL_FORMAT_8888		= (short)0x8888;
const short PIXEL_FORMAT_4444		= (short)0x4444;
const short PIXEL_FORMAT_1555		= (short)0x5515;
const short PIXEL_FORMAT_0565		= (short)0x6505;

//////////////////////////////////////////////////

const short ENCODE_FORMAT_I2			= 0x0200;
const short ENCODE_FORMAT_I4			= 0x0400;
//	const short ENCODE_FORMAT_I8			= 0x0800;
const short ENCODE_FORMAT_I16		= 0x1600;
//	const short ENCODE_FORMAT_I16MP		= 0x16??;
//	const short ENCODE_FORMAT_I32		= 0x3200;
//	const short ENCODE_FORMAT_I64		= 0x6400;
//	const short ENCODE_FORMAT_I128		= 0x2801;
const short ENCODE_FORMAT_I256		= 0x5602;
//	const short ENCODE_FORMAT_I127_		= 0x2701;
const short ENCODE_FORMAT_I64RLE		= 0x64F0;
const short ENCODE_FORMAT_I127RLE	= 0x27F1;
const short ENCODE_FORMAT_I256RLE	= 0x56F2;

//////////////////////////////////////////////////
// Frames/Anims flags...

const char FLAG_FLIP_X	= 0x01;
const char FLAG_FLIP_Y	= 0x02;
const char FLAG_ROT_90	= 0x04;
const char FLAG_ROT_270 = 0x08;

const char FLAG_USER0	= 0x10; // user flag 0
const char FLAG_USER1	= 0x20; // user flag 1

const char FLAG_HYPER_FM	= 0x10; // Hyper FModule, used by FModules

// Index extension...
const int FLAG_INDEX_EX_MASK = 0xC0; // 11000000, bits 6, 7
const int INDEX_MASK			= 0x03FF; // max 1024 values
const int INDEX_EX_MASK		= 0x0300;
const int INDEX_EX_SHIFT 	= 2;

//////////////////////////////////////////////////
// flags passed as params...

const char FLAG_OFFSET_FM = 0x10;
const char FLAG_OFFSET_AF = 0x20;

const bool k_UseEscapeCharacter = true;
const char k_EscapeCharacterPrefix = '^';

#ifdef SPRITE_LAGER_THAN_64K
typedef int _modules_data_off_t;
const int kModuleDataOffsetMask = 0xFFFFFFFF;
#else
typedef short _modules_data_off_t;
const int kModuleDataOffsetMask = 0xFFFF;
#endif
class CGame;
class CSprite  
{
public:
	CSprite();
	virtual ~CSprite();
	CGame * m_pGame;
	int resID;
	// temporar buffer...
	// Redimension it depending on the max size of the modules!
	//todo
	//static int temp[] = new int[DEF.nDecodeBufferSize];
	
	// Used for reusing data from the temp buffer.
	
	
	//////////////////////////////////////////////////
	
	// Modules...
	int			_nModules;			// number of modules
	//	  char[]		_modules_x;			// x  for each module [BS_MODULES_XY]
	//	  char[]		_modules_y;			// y  for each module [BS_MODULES_XY]
	char*		_modules_w;			// width for each module
	char*		_modules_h;			// height for each module
	int			_modules_id_cache;	// cache of the module id
	int			_modules_pal_cache; // cache of the previous palette

	//bool		m_bWiseModule;
	
	// Frames...
	char*		_frames_nfm;		// number of FModules (max 256 FModules/Frame)
	int			_frames_nfm_length;
	//	  short[]		_frames_nfm;		// number of FModules (max 65536 FModules/Frame)
	short*		_frames_fm_start;	// index of the first FModule
	short*		_frames_rc_start;	// index of frame rects
	char*		_frames_rc;			// frame bound rect (x y width height)
	// FModules...
	char*		_fmodules;			// 4 bytes for each FModule
	//	  char[]		_fmodules_module;		// 0 : module index
	//	  char[]		_fmodules_ox;			// 1 : ox
	//	  char[]		_fmodules_oy;			// 2 : oy
	//	  char[]		_fmodules_flags;		// 3 : flags
	
	// Anims...
	char*		_anims_naf;			// number of AFrames (max 256 AFrames/Anim)
	int			_anims_naf_length;
	//	  short[]		_anims_naf;			// number of AFrames (max 65536 AFrames/Anim)
	short*		_anims_af_start;	// index of the first AFrame
	// AFrames...
	char*		_aframes;			// 5 bytes for each AFrame
	//	  char[]		_aframes_frame;			// 0 : frame index
	//	  char[]		_aframes_time;			// 1 : time
	//	  char[]		_aframes_ox;			// 2 : ox
	//	  char[]		_aframes_oy;			// 3 : oy
	//	  char[]		_aframes_flags;			// 4 : flags
	
	// Module mappings...
	int**		_map; 				// all mappings
	//	  int			_mappings;			// number of mapings
	int	        _cur_map;			// current mapping
	
	// Palettes...
	//	  short 		_pixel_format;		// always converted to bpp
#if NATIVE_COLOR_DEPTH== 16
	unsigned short**		_pal; 				// all palettes
#else	//converted to 8888
	int**		_pal; 				// all palettes
#endif
	int* _pal_alpha;

	int			_palettes;			// number of palettes
	int	        _crt_pal;			// current palette
	bool		_alpha;				// has transparency ?
	   //	  int			_flags;				// transparency, etc.
	   
	   // Graphics data (for each module)...
	   //	  Image[]		_main_image;		// an image with all modules, for each palette
	short 		_data_format;
	int			_i64rle_color_mask;	// used by ENCODE_FORMAT_I64RLE
	int			_i64rle_color_bits;	// used by ENCODE_FORMAT_I64RLE
	char*		_modules_data;		// encoded image data for all modules

	//short*		_modules_data_off;	// offset for the image data of each module
	_modules_data_off_t*		_modules_data_off;	// offset for the image data of each module
 
	//	  int[][]		_modules_data2;		// cashe image data (decoded)
	CImage***	    _modules_image;		// cache image for each module / with each palette
	   //	  Image[]		_modules_image_fx;	// cache image for each module (flipped horizontally)
	   
	bool		m_bUseLazyCaching;
	bool		m_bMinimalMemoryDrawing;

	bool		m_b_palette_loaded;
	   
	bool       m_bFmOffShort;
	// Maps an ASCII char to a sprite FModule...
	char*	_map_char;// = new char[256]; NEEDS TO BE LOADED FROM RESOURCES !!!
	short	_map_char_length;
	// Space between two lines of text...
	//int _line_spacing;

	int _colors_cnt;

//////////////////////////////////////////////////////////////////////////
	int getFmoduleData(int moduleIndex, int pos);
//	void Load(char* data, int offset, int data_length, MemoryType memoryType);
	void Load(CMemoryStream* in_data, int offset, int dataSize, bool load_pal, MemoryType memoryType);
	void BuildCacheImages(int pal, int m1, int m2, int pal_copy, MemoryType memoryType);
	void UnCacheImages();
	void BuildCacheModule(int pal, int module, MemoryType memoryType);
	void BuildCacheFrame(int pal, int frame, MemoryType memoryType);
	void BuildCacheAnim(int pal, int anim, MemoryType memoryType);
	void SetModuleMapping(int map, char* mmp, int mmp_length, MemoryType memoryType);
	void ApplyModuleMapping(int dst_pal, int src_pal, char* mmp, int mmp_length);
	void GetAFrameRect(int* rc, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);
	void GetFrameRect(int* rc, int frame, int posX, int posY, int flags, int hx, int hy);
	void GetFModuleRect(int* rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy);
	void GetModuleRect(int* rc, int module, int posX, int posY, int flags);
	void PaintAFrame(CGraphics* g, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);
	void PaintFrame(CGraphics* g, int frame, int posX, int posY, int flags, int hx, int hy);
	void PaintFModule(CGraphics* g, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy);
	void PaintModule(CGraphics* g, int module, int posX, int posY, int flags);
	CMutableImage* DecodeImage(int module, int flags, char** temp, MemoryType memoryType, bool isBuildModule = false);
	//void UpdateStringSize(char* s, bool interpretSpecialChar);
	//int GetStringSize(char* s, int index1, int index2, bool interpretSpecialChar, bool interpretNewLine);
	//void DrawString(CGraphics* g, char* s, int x, int y, int anchor);
	//int DrawPage(CGraphics* g, char* s, int x, int y, int anchor);
//	void UpdateStringSize(char* s, bool interpretSpecialChar);
//	int GetStringSize(char* s, int index1, int index2, bool interpretSpecialChar, bool interpretNewLine);
//	void DrawString(CGraphics* g, char* s, int x, int y, int anchor);
	//int GetCharWidth(int c);
	//int GetCharHeight(int c);
	//int GetCharOY(int c);
	//int GetSubStringWidth(char* text, int startIndex, int endIndex);
	//int FindWordEnd(char* text, int startOffset);
	//int WrapText(char* text, int maxWidth);
	//int WrapText(char* text, int maxWidth, bool unwrap);
	//void UnwrapText(char* text);
	//void InterpretStringSpecialChar(char specialChar);
	//void PaintAFrameSafe (CGraphics* g, int anim, int aframe, int posX, int posY);
	//void PaintFrameSafe (CGraphics* g, int frame, int posX, int posY);
	//void SetSubString(int i1, int i2);
//////////////////////////////////////////////////////////////////////////
	//static int* GenPalette(int type, int* pal, int pal_length, int**new_pal, MemoryType memoryType);
//////////////////////////////////////////////////////////////////////////
	void SetCurrentMMapping(int map)	{ _cur_map = map; }
	int GetCurrentMMapping()			{ return _cur_map; }
	void SetCurrentPalette(int pal)		{ _crt_pal = pal; }
	int GetCurrentPalette()				{ return _crt_pal; }
	int GetAFrameTime(int anim, int aframe)
	{
		return _aframes[(_anims_af_start[anim] + aframe) * 5 + 1] & 0xFF;
	}
	int GetAFrames(int anim)
	{
		return _anims_naf[anim]&0xFF;
	}
	int GetFModules(int frame)
	{
		return _frames_nfm[frame]&0xFF;
	}
//	int  GetLineSpacing()				{ return _line_spacing; }
//	void SetLineSpacing(int spacing)	{ _line_spacing = spacing; }
//	void SetLineSpacingToDefault()		{ _line_spacing = ((_modules_h[0]&0xFF) >> 1); }
//	int GetHeight()
//	{
//		return _modules_h[0]&0xFF;
//	}
//	void SetCurrentPaletteSafe (int pal)
//	{
//		_crt_pal = (pal < _palettes) ? pal : 0 ;
//	}
	int GetAnims()
	{
		return _anims_naf_length;
	}

	int GetAnimFrameOffsetX(int anim, int aframe);

	int GetAnimFrameOffsetY(int anim, int aframe);

	int GetModuleWidth(int nModule)
	{
		ASSERT( 0 <= nModule && nModule < _nModules );
		return _modules_w[nModule];
	}

	int GetModuleHeight(int nModule)
	{
		ASSERT( 0 <= nModule && nModule < _nModules );
		return _modules_h[nModule];
	}

	int Str_GetCharModule(int c);
	static  void Str_SetEscapedStringID(int strID, int index);
	void Str_Init();
	int m_nStrCharSpacing;
	int m_nStrLineSpacing;
	int m_nStrSpaceSize;
	int m_fontType;
	int Str_GetFontHeight();
	int Str_DrawString(CGraphics& g, char* str, int x, int y, int flags);
	int Str_DrawSubString(CGraphics& g, char* str, int x, int y, int flags, int firstIndex, int size);
	int Str_GetSubStringWidth(char* str, int firstIndex, int size);
	int Str_GetCharacterWidth(int c);
	bool InterpretSpecialCharacter(char c);
	static  void SetNumberString(int value);
	char* GetGameSpecificSpecialCharacterString( char c );
	char* GetSpecialCharacterString( char c );
	int Str_GetStringLen( char* str);
	int Str_GetStringWidth(char* str);
	int Str_DrawText( CGraphics& g, char* str, int x, int y, int flags, int w, int firstLine, int numLines);
	int Str_WrapText(char* str, int index1, int index2, int width, int* indices);
	static int StringTokenize(char* str, int index1, int index2, char token, int* indices);
	
	int Str_GetCharSpacing() {return m_nStrCharSpacing;}
	int Str_GetLineSpacing() {return m_nStrLineSpacing;}
	int Str_GetSpaceSize() {return m_nStrSpaceSize;}
	
	void Str_SetCharSpacing(int value) {m_nStrCharSpacing = value;}
	void Str_SetLineSpacing(int value) {m_nStrLineSpacing = value;}
	void Str_SetSpaceSize(int value) {m_nStrSpaceSize = value;}
	static  void Str_SetEscapedDigitValue(int value, int index);
	// static members are in CGame
//	static byte [] s_DigitString;
//	static int [] s_DigitValues;
//	static int [] s_StringIDs;
	int GetFrameZeroModule(int index);
	int GetAnimTotalTime(int anim);
	int Str_GetCharFrame(int c);
	void PreCalculateAllFrameRects();
	int GetNumFrames();
};

#endif // !defined(AFX_SPRITE_H__A92545D9_C5F6_4B10_80E4_6FCF52A0864A__INCLUDED_)
