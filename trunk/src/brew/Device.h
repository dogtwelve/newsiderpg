#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "../common/Common.h"
#include "../common/Graphics.h"
//#include "Game/Static.h"
#include "Sound.h"

class cGame;  //++sj
class CEngine; //++sj
struct CObjectStatic;
struct CGameStatic;
extern CEngine* g_pCEngine;
extern cGame* g_pGame; //++sj


struct GameApp
{
	//AEEApplet a; --sj
	AEEApplet* a; //++sj
	CEngine *m_engine;
	int m_lastError;
	CObjectStatic* m_objectStatic;
	
	//AEEEvent m_eCode;  //--sj
	//uint16 m_wParam;   //--sj
	//uint32 m_dwParam ;  //--sj
#ifdef TICK_PER_FRAME_WHEN_LOADING
	bool m_bLoading;
#endif
};

extern GameApp* g_apGame;  //++sj

inline GameApp* GetGameApp() {
	return (GameApp*)GETAPPINSTANCE();
}

inline CEngine& GetEngine() {
	return *GetGameApp()->m_engine;
}

inline CObjectStatic& SObject()
{
	return *GetGameApp()->m_objectStatic;
}

class CDevice
{
public:
#if BREW_OS == 1
	#pragma pack(push, 1)
	typedef struct tagBITMAPFILEHEADER1 {
		short	bfType;
		long	bfSize;
		short   bfReserved1;
		short   bfReserved2;
		long	bfOffBits;
	} BITMAPFILEHEADER;
	
	typedef struct tagBITMAPINFOHEADER{
		long    biSize;
		long    biWidth;
		long    biHeight;
		short   biPlanes;
		short   biBitCount;
		long    biCompression;
		long    biSizeImage;
		long    biXPelsPerMeter;
		long    biYPelsPerMeter;
		long    biClrUsed;
		long    biClrImportant;
	} BITMAPINFOHEADER;
	
	typedef struct tagRGBQUAD {
		unsigned char	rgbBlue;
		unsigned char   rgbGreen;
		unsigned char   rgbRed;
		unsigned char   rgbReserved;
	} RGBQUAD;

	#pragma pack(pop)

	typedef struct
	{
	#if DEVICE == DEVICE_N3589i
		dword			_head[10];
	#elif DEVICE == DEVICE_Z800
		byte			_head[5];
	#elif DEVICE == DEVICE_KZ810
		dword			_head[7*4];
	#else
		byte			_head[12];
	#endif
		char			_data[4];
	} NativeImage;
#endif

	CDevice();
	virtual ~CDevice();

	bool Open();
	void Close();

	void SendShutDownMessage();
	void SendLoadResourceMessage( bool loading );

	//Memory
	unsigned int GetTotalRAM();
	unsigned int GetFreeRAM();
	unsigned int GetLargestRAMBlock();

	void GetModuleVersion(AECHAR* buf, int size);
	void GetModuleVersion(char* buf, int size);


	//File
	unsigned int GetFreeSpace();
	bool IsFileReadOnly(const char *fn);
	bool IsFileExist(const char *fn);
	bool RemoveFile(const char *fn);
	unsigned int GetFileSize(const char *fn);

	void FlushToSystemBuffer(Rect16 *rect = NULL);
	void UpdateToScreen(Rect16 *rect = NULL);
	CMutableImage& GetScreenImage() { return *m_screenImage; }

	static int KeyIndexFromDeviceKey(unsigned int code);

	//void SetSysTextColor(int r, int g, int b) { --sj
	//	IDISPLAY_SetColor(GetGameApp()->a.m_pIDisplay, CLR_USER_TEXT, MAKE_RGB(r, g, b));  --sj
	//} --sj

	void DrawSysText(const char *str, int x, int y);

	static int GetScreenWidth();
	static int GetScreenHeight();

	IFileMgr *m_fileMgr;
protected:
	static void ConvertRGB444ToRGB332FlipY(unsigned short *ps, unsigned char *pd, int w, int h, int spitch, int dpitch);
	static void ConvertRGB565ToRGB332FlipY(unsigned short *ps, unsigned char *pd, int w, int h, int spitch, int dpitch);
	static void ConvertRGB888ToRGB565(unsigned int *ps, unsigned short *pd, int w, int h, int spitch, int dpitch);
	static void ConvertRGB565ToRGB666(unsigned short *ps, unsigned int *pd, int w, int h, int spitch, int dpitch);
	IHeap *m_heap;
#if BREW_OS == 1
#ifdef AEE_SIMULATOR
	BITMAPFILEHEADER *m_pDeviceBitmap;
	unsigned char *m_pScreenPixelData;
	int m_screenPitch;
#else //#ifdef AEE_SIMULATOR
	NativeImage *m_pDeviceBitmap;
#endif //#ifdef AEE_SIMULATOR
#else //#if BREW_OS == 1
	IBitmap *m_pDeviceBitmap;
#endif //#if BREW_OS == 1
	uint32 m_totalRAM;

	CMutableImage *m_screenImage;
	int m_screenWidth;
	int m_screenHeight;
	int m_nAnnunciator_Height;

	uint32 m_dwPlatformID;
};

class CRawFile
{
public:
	enum AccessMode{
		MODE_READ	= 0x01,
		MODE_WRITE	= 0x02,
		MODE_CREATE	= 0x04,
		MODE_APPEND	= 0x08
	};

	enum SeekMode{
		FSEEK_BEGIN	= 0,
		FSEEK_CURRENT,
		FSEEK_END
	};

	CRawFile();
	virtual ~CRawFile();
	bool Open(const char *fn, int mode);
	void Close();
	
	bool Seek(int moveDistance, int seekMode);
	unsigned int GetLength();
	unsigned int GetPosition() {
		return IFILE_Seek(m_file, _SEEK_CURRENT, 0);
	}
	unsigned int Write(const void *buf, unsigned int size){
		return IFILE_Write(m_file, buf, size);
	}
	unsigned int Read(void *buf, unsigned int size){
		return IFILE_Read(m_file, buf, size);
	}
	
protected:
	//IFile *m_file; //--sj
	IFile m_file; //++sj
};

#endif // !defined(AFX_DEVICE_H__82EAC272_16E8_4E0D_B6A2_F56064F79A70__INCLUDED_)
