#ifndef _ASPRITE_
#define _ASPRITE_

//#include "Graphics.h"
//#include "../game/cGame.h"
#include "../config_version.h"
#include "cGame.h"

//Add by SangHo - 충돌 체크 영역을 보고싶을때
#define VIEW_CONTECT_CHECK 

#define BLEND_CUSTOM_NOT 0
#define BLEND_CUSTOM_ZERO 1
#define BLEND_CUSTOM_OVER 2



class cGame;
class CGraphics;
class CImage;

extern cGame* g_pGame;

const static int TEMP_BUFFER_SIZE = 15 * 1024;
const static bool USE_MODULE_MAPPINGS		= !true;  

const static bool USE_HYPER_FM				= true;  

const static bool USE_INDEX_EX_FMODULES		= true;  
const static bool USE_INDEX_EX_AFRAMES		= true;  

const static bool USE_PRECOMPUTED_FRAME_RECT =true;//SangHo - 미리 계산된 Rect 값을 쓴다 (프레임의 시작,너비,높이값이 BSprite 안에 들어있음)

const static bool ALWAYS_BS_FRAME_RECTS		= true;//(충돌체크-Conflict Check) all sprites are exported with BS_FRAME_RECTS

const static bool ALWAYS_BS_NFM_1_BYTE		= false;  
const static bool ALWAYS_BS_SKIP_FRAME_RC	= false;  
const static bool ALWAYS_BS_FRAME_COLL_RC	= false;  
const static bool ALWAYS_BS_NAF_1_BYTE		= false;  

const static bool USE_PIXEL_FORMAT_8888		= true;
const static bool USE_PIXEL_FORMAT_4444		= true;
const static bool USE_PIXEL_FORMAT_1555		= true;
const static bool USE_PIXEL_FORMAT_0565		= true;

const static bool USE_ENCODE_FORMAT_I2		= true;
const static bool USE_ENCODE_FORMAT_I4		= true;
const static bool USE_ENCODE_FORMAT_I16		= true;
const static bool USE_ENCODE_FORMAT_I256		= true;
const static bool USE_ENCODE_FORMAT_I64RLE	= true;
const static bool USE_ENCODE_FORMAT_I127RLE	= true;
const static bool USE_ENCODE_FORMAT_I256RLE	= true;

const static int MAX_SPRITE_PALETTES			= 16;
const static int MAX_MODULE_MAPPINGS			= 16;

//70/!!!!!!!!!!!!!!!!!!1y.h.kang 071228
//const static int MAX_ANIMATION_INSTANCES		= 10;//52;  



const static short BSPRITE_v003	= (short)0x03DF;  



const static int BS_MODULES			= (1 << 0);
const static int BS_MODULES_XY		= (1 << 1);
const static int BS_MODULES_IMG		= (1 << 2);
const static int BS_FRAMES			= (1 << 8);
const static int BS_FM_OFF_SHORT	= (1 << 10);     
const static int BS_NFM_1_BYTE		= (1 << 11);     
const static int BS_SKIP_FRAME_RC	= (1 << 12);     
const static int BS_FRAME_COLL_RC   = (1 << 13);
const static int BS_FM_PALETTE		= (1 << 14);	// 프레임안의 모듈에 팔렛트를 지정해주는 옵션
const static int BS_FRAME_RECTS		= (1 << 15);	//(충돌체크-Conflict Check)
const static int BS_ANIMS			= (1 << 16);
const static int BS_AF_OFF_SHORT	= (1 << 18);     
//const static int BS_NAF_1_BYTE		= (1 << 19);     
const static int BS_MODULE_IMAGES	= (1 << 24);
const static int BS_PNG_CRC			= (1 << 25);
const static int BS_KEEP_PAL		= (1 << 26);
const static int BS_TRANSP_FIRST	= (1 << 27);
const static int BS_TRANSP_LAST		= (1 << 28);

const static int BS_DEFAULT_DOJA	= (BS_MODULES | BS_FRAMES | BS_ANIMS);
const static int BS_DEFAULT_MIDP2	= (BS_MODULES | BS_FRAMES | BS_ANIMS | BS_MODULE_IMAGES);
const static int BS_DEFAULT_NOKIA	= BS_DEFAULT_MIDP2;
const static int BS_DEFAULT_MIDP1	= (BS_MODULES | BS_MODULES_XY | BS_FRAMES | BS_ANIMS);
const static int BS_DEFAULT_MIDP1b	= (BS_MODULES | BS_FRAMES | BS_ANIMS | BS_MODULE_IMAGES | BS_PNG_CRC);


const static int PIXEL_FORMAT_8888		= (int)0x8888;
const static int PIXEL_FORMAT_4444		= (int)0x4444;
const static int PIXEL_FORMAT_1555		= (int)0x5515;
const static int PIXEL_FORMAT_0565		= (int)0x6505;



const static int ENCODE_FORMAT_I2			= 0x0200;
const static int ENCODE_FORMAT_I4			= 0x0400;

const static int ENCODE_FORMAT_I16		= 0x1600;




const static int ENCODE_FORMAT_I256		= 0x5602;

const static int ENCODE_FORMAT_I64RLE		= 0x64F0;
const static int ENCODE_FORMAT_I127RLE	= 0x27F1;
const static int ENCODE_FORMAT_I256RLE	= 0x56F2;





const static byte FLAG_FLIP_X	= 0x01;
const static byte FLAG_FLIP_Y	= 0x02;
const static byte FLAG_ROT_90	= 0x04;

const static byte FLAG_USER0	= 0x10;  
const static byte FLAG_USER1	= 0x20;  

const static int FLAG_USER2		= 0x40;  
const static int FLAG_USER3		= 0x80;  
const static int FLAG_USER4		= 0x100;  


const static byte FLAG_HYPER_FM	= 0x10;  


const static int FLAG_INDEX_EX_MASK = 0xC0;  
const static int INDEX_MASK			= 0x03FF;  
const static int INDEX_EX_MASK		= 0x0300;
const static int INDEX_EX_SHIFT 	= 2;


const static byte FLAG_OFFSET_FM = 0x10;
const static byte FLAG_OFFSET_AF = 0x20;


const static int STACK_SIZE = 200;  



const static byte FLAGS_MASK    = FLAG_FLIP_X |FLAG_FLIP_Y;

static const int TRANS_NONE = 0;
static const int TRANS_MIRROR_ROT180 = 1;
static const int TRANS_MIRROR = 2;
static const int TRANS_ROT180 = 3;
static const int TRANS_MIRROR_ROT270 = 4;
static const int TRANS_ROT90 = 5;
static const int TRANS_ROT270 = 6;
static const int TRANS_MIRROR_ROT90 = 7;





class CASpriteImage: public CRleImage {
public:
	//#if defined SUPER_VERSION
	//	CASpriteImage(int bpp, int flag, int dataFormat, uint_8 *pWidth, uint_8 *pHeight, int colorKey, int paletteEntryNumber,
	//				int nPalettes, PalettePixel **paletteData, int nModules, int_8 *modulesData, int *modulesDataOffset);
	//#else
	CASpriteImage(int bpp, int flag, int dataFormat, unsigned char *pWidth, unsigned char *pHeight, int colorKey, int paletteEntryNumber,
		int nPalettes, PalettePixel **paletteData, int nModules, char *modulesData, int *modulesDataOffset);
	//#endif
	virtual ~CASpriteImage();

	//	void SetCurrentData(int paletteID, int moduleID, PalettePixel* p= NULL);
	void SetCurrentData(int paletteID_2, bool bI64RLE, int paletteEntryNumber, int moduleID, PalettePixel* p= NULL);

	void SetAlphaFlag() { m_flag |= BBM_ALPHA; }

	void SetNightAlphaFlag() { m_flag |= BBM_NIGHTALPHA; }

	void SetScaleData(unsigned char* pixeldata, int width = 0, int height = 0);// { m_pixel = pixeldata; SetSize(width, height, width * ((m_bpp + 7) / 8));}



	unsigned char *m_modulesPixel;
	int *m_modulesPixelOffset;
protected:
	int m_nModules;
	int m_nPalettes;
	unsigned char *m_modulesWidth;
	unsigned char *m_modulesHeight;
	PalettePixel **m_paletteDataAll;
	int m_nColors;
	

	
};


class ASprite
{
#ifdef WIN32
	static int spriteCounter; 
#endif
	int SCROLL_DELAY_TIME;// = 3;

	
public:
	//	nams 090519 
	int uniqueIdx;

	int palLen; 
	//void ClearAnimation(int animIndex,bool loop = false);

	int			_nModules;	//모듈 총갯수
	int			_nFrames;	//프레임 총갯수

	int _m_blendCustom;//SangHo - Blend - 프레임 중에는 블랜딩 정보 프레임이 있다 그 Define 값
	int _m_blendFrame;//SangHo - Blend - 프레임 중에는 블랜딩 정보 프레임이 있다 그 Define 값
	unsigned char m_Blend_Kind,m_Blend_C_Kind;//SangHo - Blend - 이미지의 종류
	unsigned int m_Blend_Percent,m_Blend_C_Percent;//SangHo - Blend - 블랜딩의 정도(0~32값 가능) (알파가 아니라면 이 수치는 전부 0이다)

	

	byte*		_modules_w;//SangHo - 모듈들의 가로 너비			 
	byte*		_modules_h;//SangHo - 모듈들의 세로 높이			 			 

	byte*		_rectM_w;
	byte*		_rectM_h;
	int*		_rectMColors;

	// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////■0/4
	char *_frames_rects;			//SangHo - (충돌체크-Conflict Check) - Rect 데이터 저장 영역 4배열[rect 갯수*4]
	short *_frames_rects_start;		//SangHo - (충돌체크-Conflict Check) - 프레임별 Rect데이터 시작index(*4 해서 써야한다) 1배열[프레임갯수+1]
	int _frames_rects_start_length;	//SangHo - (충돌체크-Conflict Check) - Rect데이터 끝 값(프레임갯수+1)

	byte*		_frames_nfm;		 

	short*		_frames_fm_start;	 
	char*		_frames_rc;			 
	char*		_frames_coll;		 

	char*		_fmodules;			 

	//nams
	byte*		_fmodules_palette;


	byte*		_anims_naf;			 

	short*		_anims_af_start;	 


	char*		_aframes;			 

	int**		_map; 				 

	int	_cur_map;			 

#if NATIVE_COLOR_DEPTH== 16
	PalettePixel** _pal;
	PalettePixel** _pal_Copy;//SangHo - 복제한 팔렛트 저장공간 2중포인터
	PalettePixel** _pal_Back;//SangHo - 원본 팔렛트 포인터 임시저장소
	//unsigned short** _pal;
#else	//converted to 8888
	int**		_pal;
#endif	
	
	
	int			_palettes;			 
	int			_colors;
	int			_crt_pal;			 
	bool		_alpha;	
	//int*		_pal_alpha;


	//short 		_data_format;
	int 		_data_format;
	int			_i64rle_color_mask;	 
	int			_i64rle_color_bits;	 

	byte*		_modules_data;		 
	int*		_modules_data_off;	// 각 모듈의 시작 옵셋 
	char*		_modules_data_pal;	// 각 모듈의 시작 옵셋 
	
#ifdef USE_DIRECT_DRAW
	CASpriteImage*	_modules_image;		// cache image for each module / with each palette
#else
	CImage**	_modules_image;			// cache image for each module / with each palette
#endif
	int			_modules_image_length;


	//int         _current_animation[MAX_ANIMATION_INSTANCES];
	//int         _current_frame[MAX_ANIMATION_INSTANCES];
	//int         _current_frame_time[MAX_ANIMATION_INSTANCES];
	//bool     _is_looping[MAX_ANIMATION_INSTANCES];

	//bool	  _is_aniDone[MAX_ANIMATION_INSTANCES];	 
	//bool	  _is_anisuspend[MAX_ANIMATION_INSTANCES];	 

#ifndef USE_DIRECT_DRAW
	int*           _precalc_stack;
	int           _precalc_stack_index;
	int           _precalc_stack_max;
#endif

	bool m_bWiseModule;// = true;
	int drawMode;


	bool _scaleImage;
	int _scaleFactor1;
	int _scaleFactor2;


	int				m_nowAniX;			//SangHo - Flag 변환이 적용된 AFrame 의 마지막 X좌표
	int				m_nowAniZ;			//SangHo - Flag 변환이 적용된 AFrame 의 마지막 Z좌표
	int				m_nowFlag;

	int				Fast_Ani_Num;//인스턴스생성이 필요없는 간단한 Ani 저장 변수
	int				Fast_Frm_Num;//인스턴스생성이 필요없는 간단한 AF 저장 변수

MC_GrpContext gc;

public:
	ASprite();

	ASprite(byte* file, int offset);	
	
public:
	void setDrawMode(int mode);
#ifndef USE_DIRECT_DRAW
	CImage* GetModuleImage(int pal, int module);
#endif
	void Load(byte* file, int offset);

public:
	void ClearCompressedImageData ();

	//static void ClearTemporaryBuffer ();
	void ClearTemporaryBuffer ();

	void BuildCacheImages(int pal, int m1, int m2, int pal_copy);

	


public:
	static void drawRegion(CGraphics* _g, CImage* img, int srcX, int srcY, int width, int height, int flag, int destX, int destY, int anchor)
	{
		_g->DrawRegion(img,srcX,srcY,width,height,flag,destX,destY,anchor,0);
	}
	void enablePrecalcImage_PalLoading( int palNumber , bool useStack);


	void enablePrecalcImage( int palTag, bool useStack );

	void clearPrecalcImage();

	void MODULE_MAPPING___() {}

	void SetModuleMapping(int map, byte* mmp);

	void ApplyModuleMapping(int dst_pal, int src_pal, byte* mmp);

	void SetCurrentMMapping(int map);

	int GetCurrentMMapping();

	void ___MODULE_MAPPING();

public:
	int GetAFrameTime(int anim, int aframe);

	int GetAFrames(int anim);

	int GetFModules(int frame);

	int GetModuleWidth(int module);

	int GetModuleHeight(int module);


	int GetFrameX(int frame);

	int GetFrameY(int frame);

	int GetFrameWidth(int frame);

	int GetFrameHeight(int frame);

	int GetFrameCollisionLeft(int frame);

	int GetFrameCollisionTop(int frame);

	int GetFrameCollisionRight(int frame);

	int GetFrameCollisionBottom(int frame);

	int GetFrameModuleX(int frame, int fmodule);

	int GetFrameModuleY(int frame, int fmodule);

	int GetFrameModuleWidth(int frame, int fmodule);

	int GetFrameModuleHeight(int frame, int fmodule);

	int GetAnimFrame(int anim, int aframe);

	void GetAFrameRect(int* rc, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);

	void GetFrameRect(int* rc, int frame, int posX, int posY, int flags, int hx, int hy);

	void GetFModuleRect(int* rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy);

	void GetModuleRect(int* rc, int module, int posX, int posY);
/*SangHo - 불필요하다고 판단
	void SetCurrentAnimation(int anim, bool loop);

public:
	//void SetCurrentAnimation(int animIndex, int anim, bool loop);
	//void SetCurrentAnimationEX(int animIndex, int anim, bool loop);

	int GetCurrentAnimation();

	int GetCurrentAnimation(int animIndex);

	int GetCurrentAnimationFrame();

	int GetCurrentAnimationFrame(int animIndex);

	int PaintAndUpdateCurrentAnimation(CGraphics* _g, int posX, int posY, int flags, int hx, int hy);

	int PaintAndUpdateCurrentAnimation(CGraphics* _g, int animIndex, int posX, int posY, int flags, int hx, int hy);

	int GetCurrentAnimationFrameNum();

	int GetCurrentAnimationFrameNum(int animIndex);

	bool IsAnimationDone();

	bool IsAnimationDone(int animIndex);
	
public:


	int UpdateAnimation( int _animIndex );


	void setAnimStop( int _animIndex );

	bool Is_animDone( int _animIndex );

public:
	void Is_animSuspend( int _animIndex );

	void Is_animResume( int _animIndex );


	int getAnimFrameMax( int _animIndex );

	int  SetCurrentAnimationFrameNum(int _animIndex , int _index );

*/
	void Get_AFrameXY(int* tmpXY, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);//그리기 전에 좌표확인이 필요할때
	








	// Added by Chun, 12, 02
	//Chun

	void InitAnimation();
	void PaintAnimation(CGraphics* _g, int _animIndex, int posX, int posY, int flags, int hx, int hy/*, bool LOOP*/);
	void PaintAFrame(CGraphics* _g, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);
	void PaintFrame(CGraphics* _g, int frame, int posX, int posY);
	void PaintFrame(CGraphics* _g, int frame, int posX, int posY, int flags, int hx, int hy, int anchor);
	void PaintFrame(CGraphics* _g, int frame, int posX, int posY, int flags, int hx, int hy, bool isHyper = false);
	void PaintFModule(CGraphics* _g, int frame , int fmodule, int posX, int posY, int flags, int hx, int hy, bool isHyper = false);





	void PaintModule(CGraphics* g, int module, int posX, int posY, int flags, int anchor);
	
	// Added by LeeSangHo,2009, 02, 16
	// SangHo - Blend - 임의로 블랜딩을 지정해줄 필요가 있을때
	//주 기능은 블랜딩 정보 임의 조작하여, 별도의 해지명령 전까지는 지속적인 작동을 시킨다.
	void SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent);
	
	// Added by LeeSangHo,2008, 12, 05
	// SangHo - Blend - PaintModule과 밀접한 관계를 가지고 있는 모듈
	//주 기능은 블랜딩 정보를 담은 프레임의 넘버를 알려주는값을 저장
	void SetBlendFrame(int blendFrame);

	// Added by LeeSangHo,2008, 12, 05
	// SangHo - Blend - 동적 블랜딩 처리를 위한 부분
	//주 기능은 module번 보듈이 블랜딩 대상 모듈인지 아닌지를 판단한다 반환값은 m_Blend_Kind, m_Blend_Percent 이다
	void CheckBlendModule(int module,bool lighten);


	void PaintModule(CGraphics* _g, int module, int posX, int posY, int flags);


	void ScaleImage(int factor1, int factor2);
	void StopScaleImage();

	CImage* ScaleImage(CImage* src, int destWidth, int destHeight, MemoryType memType);
	//short* ScaleImage(int width , int height , int destWidth, int destHeight, short* pixel);
	unsigned char* ScaleImage(int width , int height , int destWidth, int destHeight, unsigned char* pixel);
	

	short* DecodeImage(int module, int flags);

public:
	void SetCurrentPalette(int pal);

	int GetCurrentPalette();

	void ModuleExchange(int mA, int mB);//프레임을 구성하는 요소인 모듈을 모든 프레임을 대상으로 mA와 mB를 교체한다

public:	
	
	static int* GenPalette(int type, int* pal);

	static void Gc();

	static void drawRGB(CGraphics* _g, int* data, int offset, int scanlength, int x, int y, int width, int height, bool processAlpha);
	
	//dongwan func
	#if NATIVE_COLOR_DEPTH== 16
		PalettePixel* getPal(); 
		void setPal(PalettePixel *pal); 
	#else	//converted to 8888
		int* getPal(); 
		void setPal(int *pal); 
	#endif	
	boolean changePal(int palIdx); 
	int getPalLen(); 
	boolean workPal(boolean Work, int Pal_Kind, int percent);//SangHo - 현재 팔렛트를 임시로 생성한 팔렛트로 바꿔치기한다 percent는 0~200
	

public:
	~ASprite();

};



#endif //_ASPRITE__ASPRITE_