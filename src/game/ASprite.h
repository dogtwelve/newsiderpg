#ifndef _ASPRITE_
#define _ASPRITE_

//#include "Graphics.h"
//#include "../game/cGame.h"
#include "../config_version.h"
#include "cGame.h"

//Add by SangHo - �浹 üũ ������ ���������
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

const static bool USE_PRECOMPUTED_FRAME_RECT =true;//SangHo - �̸� ���� Rect ���� ���� (�������� ����,�ʺ�,���̰��� BSprite �ȿ� �������)

const static bool ALWAYS_BS_FRAME_RECTS		= true;//(�浹üũ-Conflict Check) all sprites are exported with BS_FRAME_RECTS

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
const static int BS_FM_PALETTE		= (1 << 14);	// �����Ӿ��� ��⿡ �ȷ�Ʈ�� �������ִ� �ɼ�
const static int BS_FRAME_RECTS		= (1 << 15);	//(�浹üũ-Conflict Check)
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

	int			_nModules;	//��� �Ѱ���
	int			_nFrames;	//������ �Ѱ���

	int _m_blendCustom;//SangHo - Blend - ������ �߿��� ���� ���� �������� �ִ� �� Define ��
	int _m_blendFrame;//SangHo - Blend - ������ �߿��� ���� ���� �������� �ִ� �� Define ��
	unsigned char m_Blend_Kind,m_Blend_C_Kind;//SangHo - Blend - �̹����� ����
	unsigned int m_Blend_Percent,m_Blend_C_Percent;//SangHo - Blend - ������ ����(0~32�� ����) (���İ� �ƴ϶�� �� ��ġ�� ���� 0�̴�)

	

	byte*		_modules_w;//SangHo - ������ ���� �ʺ�			 
	byte*		_modules_h;//SangHo - ������ ���� ����			 			 

	byte*		_rectM_w;
	byte*		_rectM_h;
	int*		_rectMColors;

	// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////��0/4
	char *_frames_rects;			//SangHo - (�浹üũ-Conflict Check) - Rect ������ ���� ���� 4�迭[rect ����*4]
	short *_frames_rects_start;		//SangHo - (�浹üũ-Conflict Check) - �����Ӻ� Rect������ ����index(*4 �ؼ� ����Ѵ�) 1�迭[�����Ӱ���+1]
	int _frames_rects_start_length;	//SangHo - (�浹üũ-Conflict Check) - Rect������ �� ��(�����Ӱ���+1)

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
	PalettePixel** _pal_Copy;//SangHo - ������ �ȷ�Ʈ ������� 2��������
	PalettePixel** _pal_Back;//SangHo - ���� �ȷ�Ʈ ������ �ӽ������
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
	int*		_modules_data_off;	// �� ����� ���� �ɼ� 
	char*		_modules_data_pal;	// �� ����� ���� �ɼ� 
	
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


	int				m_nowAniX;			//SangHo - Flag ��ȯ�� ����� AFrame �� ������ X��ǥ
	int				m_nowAniZ;			//SangHo - Flag ��ȯ�� ����� AFrame �� ������ Z��ǥ
	int				m_nowFlag;

	int				Fast_Ani_Num;//�ν��Ͻ������� �ʿ���� ������ Ani ���� ����
	int				Fast_Frm_Num;//�ν��Ͻ������� �ʿ���� ������ AF ���� ����

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
/*SangHo - ���ʿ��ϴٰ� �Ǵ�
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
	void Get_AFrameXY(int* tmpXY, int anim, int aframe, int posX, int posY, int flags, int hx, int hy);//�׸��� ���� ��ǥȮ���� �ʿ��Ҷ�
	








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
	// SangHo - Blend - ���Ƿ� ������ �������� �ʿ䰡 ������
	//�� ����� ���� ���� ���� �����Ͽ�, ������ ������� �������� �������� �۵��� ��Ų��.
	void SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent);
	
	// Added by LeeSangHo,2008, 12, 05
	// SangHo - Blend - PaintModule�� ������ ���踦 ������ �ִ� ���
	//�� ����� ���� ������ ���� �������� �ѹ��� �˷��ִ°��� ����
	void SetBlendFrame(int blendFrame);

	// Added by LeeSangHo,2008, 12, 05
	// SangHo - Blend - ���� ���� ó���� ���� �κ�
	//�� ����� module�� ������ ���� ��� ������� �ƴ����� �Ǵ��Ѵ� ��ȯ���� m_Blend_Kind, m_Blend_Percent �̴�
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

	void ModuleExchange(int mA, int mB);//�������� �����ϴ� ����� ����� ��� �������� ������� mA�� mB�� ��ü�Ѵ�

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
	boolean workPal(boolean Work, int Pal_Kind, int percent);//SangHo - ���� �ȷ�Ʈ�� �ӽ÷� ������ �ȷ�Ʈ�� �ٲ�ġ���Ѵ� percent�� 0~200
	

public:
	~ASprite();

};



#endif //_ASPRITE__ASPRITE_