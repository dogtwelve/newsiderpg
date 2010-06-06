#ifndef BREW_TO_WIPI
#define BREW_TO_WIPI
///////////////////////////////////////////////////////////////////////////////
#include "WIPI.h"
#include "DeviceInfo.h"
///////////////////////////////////////////////////////////////////////////////
//#define WIPIC

#define uint8	unsigned char
typedef unsigned char byte;
#define uint16  unsigned short
#define uint32  unsigned int
#define int32   int	
#define int8	char
#define int16   short		
#define boolean bool
#define int64   M_Int64
#define FALSE	0
#define TRUE	1

#define AECHAR      uint16
#define IApplet		cGame
#define AEEApplet	cGame
#define IHeap		byte 
#define IShell		byte
#define IModule		byte
#define IDisplay	MC_GrpFrameBuffer
#define IFileMgr	byte	//no use in wipi sdk
#define IFile		M_Int32
#define IFILEMGR_GetLastError(a)	0
// #define IFILE_GetInfo(_file, info) ((_file) >= (0))
#define EFAILED		0
// #define IFILE_Release MC_fsClose
#define GETAPPINSTANCE() g_apGame
#define MyImage_565Touint32(x) (((x) & 0x1f)<<27 | (((x) & 0x07e0) << 13) | ((x) & 0xf800) )
#define MyImage_uint32To565(bgra)   (((bgra &0xf8000000)>>27) | ((bgra &0x00fc0000)>>13) |((bgra &0x0000f800)))//( ((bgra >>19) &0x1f) | ((bgra >>11) &0x7e0)|((bgra ) &0xf8))//((((bgra >> 16) & 0xf800)>>6) | ((bgra >> 13) & 0x7e0) | (((bgra >> 11) & 0x1f)<<6))
#define IBITMAP_RGBToNative(a, color) MyImage_uint32To565(color)
#define IBITMAP_NativeToRGB(a, color) MyImage_565Touint32(color)//is not ok ;
#define IDF_RECT_FRAME 0
#define MEMSET	memset
#define STRLEN	strlen
#define MEMCPY	memcpy
#define MEMMOVE memmove
#define STRCPY	strcpy
#define STRNCPY strncpy
#define STRCMP	strcmp
#define STRCAT	strcat
#define STRCHR  strchr
#define STRSTR  strstr
char * STRUPPER(char *c);	//hw++
char * STRLOWER(char *c);	//hw++
#define ATOI	atoi
#define ABS(VAL) (((VAL)>0)?(VAL):(-(VAL)))

typedef int	AEEOpenFileMode;
typedef int	FileSeekType;
#define _OFM_READ		MC_FILE_OPEN_RDONLY
#define _OFM_READWRITE  MC_FILE_OPEN_RDWR
#define _OFM_CREATE     MC_FILE_OPEN_RESERVE
#define _OFM_APPEND     MC_FILE_OPEN_RESERVE

#ifndef MAX
   #define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef MIN
   #define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

#define  PER( x, y ) (((x)*(y))/100)

typedef uint32 NativeColor;

//#define FileInfo int
//#define MAX_FILE_NAME 30
enum FILESEEKTYPE
{
	_SEEK_CURRENT,
	_SEEK_START,
	_SEEK_END
};


//#define OS_SCREEN_W	SCREEN_WIDTH 
//#define OS_SCREEN_H	SCREEN_HEIGHT


typedef enum
{
   AEE_RO_OR,
   AEE_RO_XOR,
   AEE_RO_COPY,
   AEE_RO_NOT,
   AEE_RO_OLDMASK,    // same as TRANSPARENT in v1.0; not supported in IBitmap
   AEE_RO_MERGENOT,
   AEE_RO_ANDNOT,
   AEE_RO_TRANSPARENT,
   AEE_RO_MASK,
   AEE_RO_TOTAL
} AEERasterOp;

typedef struct _FileInfo
{
//FileAttrib attrib;
uint32 dwCreationDate;
uint32 dwSize;
//char szName[MAX_FILE_NAME];
} FileInfo;


uint32 IFILE_Seek(IFile _file,int type ,int pos);

IFile IFILEMGR_OpenFile(IFileMgr *pIFileMgr, const char *_pack_file, unsigned int i);

int32 IFILE_Read(IFile _file,void *buf,int len);

int32 IFILE_Write(IFile _file,const void *buf,int len);

int32 IFILEMGR_Remove(IFileMgr * pIFileMgr, const char * pszName);

bool IFILE_GetInfo(IFile _file,FileInfo *info);
#define IFILEMGR_GetFreeSpace(p,i)  MC_fsAvailable()
uint32 IFILE_Release(IFile  pIFile);


#define ISHELL_CreateInstance(p, o, i)  true
#define ISOUNDPLAYER_RegisterNotify(t, s, p) FALSE
#define IFILEMGR_Test(p ,i)  SUCCESS
//bool IFILEMGR_GetInfo(IFileMgr *pIFileMgr, const char * pszName, FileInfo * pInfo) ;
///////////////////////////////////////////////////////////////////////////////
//
//Graphic
//
///////////////////////////////////////////////////////////////////////////////
#define MAKE_RGB(r,g,b) (((((uint32)r) & 0xFF) << 8) |		\
							((((uint32)g) & 0xFF) << 16) |  \
							((((uint32)b) & 0xFF) << 24))
#define IBitmap unsigned char
typedef struct _IDIB
{
	int nPitch;
	int nDepth;
	int cy;
	int cx;
	IBitmap * pBmp;
}IDIB;
typedef struct 
{
   signed short	x,y;
   signed short	dx, dy;
} AEERect;
typedef struct _triangle {
   int16 x0, y0;     // First point
   int16 x1, y1;     // Second point
   int16 x2, y2;     // Third point
} AEETriangle;
typedef struct _ellipse {
   int16 cx, cy;     // center of ellipse
   int16 wx;         // semimajor/minor axis along x-axis
   int16 wy;         // semimajor/minor axis along y-axis
                     // which is major or minor depends on the relative values of wx and wy
} AEEEllipse;
typedef uint32 RGBVAL;
//void IDISPLAY_SetClipRect(MC_GrpFrameBuffer m_pIDis, AEERect* r);
//void IDISPLAY_DrawRect(MC_GrpFrameBuffer m_pIDis, AEERect* r, RGBVAL framecolor, RGBVAL fillcolor, uint32 flag);
#define IDISPLAY_DrawText(p, w, e, r, t, y, u, i)//is not ok
//#define IDIB (struct _MC_GrpFrameBuffer)
#define IDISPLAY_UpdateEx(x,y) IDISPLAY_Update(x)
void IDISPLAY_Update(MC_GrpFrameBuffer pIDis);
int IDISPLAY_GetDeviceBitmap(MC_GrpFrameBuffer& m_pIDisplay, IBitmap** pb);
//int IBITMAP_CreateCompatibleBitmap(IBitmap* ibitmapsrc, IBitmap **  ibitmapdes,uint16 w,uint16 h);
//void IBITMAP_FillRect(void *pIBitmap,const AEERect *prc,NativeColor color,AEERasterOp rop);
#define IDISPLAY_FillRect(A,B,C)
#define IDISPLAY_Backlight(a,b)
/*
void IDISPLAY_FillRect
(
IDisplay * pIDisplay,
AEERect * pRect,
RGBVAL clrFill
)*/
#define IGraphics M_Int32
int IBITMAP_QueryInterface(IBitmap* x, int i, void** idib);

#define	IBITMAP_DrawPixel(buffer, y, u, c, AEE_RO_COPY) 
#define	IBITMAP_GetPixel(buffer, u, i, o) 
//RGBVAL IGRAPHICS_SetColor(IGraphics * pIGraphics,uint8 r,uint8 g,uint8 b,uint8 alpha);
//RGBVAL IGRAPHICS_SetFillColor(IGraphics * pIGraphics,uint8 r,uint8 g,uint8 b,uint8 alpha);
//int IGRAPHICS_DrawRoundRectangle(IGraphics *pIGraphics,AEERect *pRect,int16 arcWidth,int16 arcHeight);
//bool IGRAPHICS_SetFillMode(IGraphics * pIGraphics, bool fFill);
//int IGRAPHICS_DrawTriangle(IGraphics * pIGraphics,AEETriangle * pTriangle);
//int IGRAPHICS_DrawEllipse(IGraphics * pIGraphics,AEEEllipse * pEllipse);
#define IBITMAP_Release(pIBitmap) 
#define IDIB_TO_IBITMAP(m_pIDIB)  m_pIDIB
#define IDISPLAY_DrawHLine(i,u,y,t) // is not ok
#define IGRAPHICS_Release(a) 
///////////////////////////////////////////////////////////////////////////////
//
//System
//
///////////////////////////////////////////////////////////////////////////////
#define SUCCESS			1
#define ENOMEMORY		0
#define AEECLSID_CORE	1
#define AEECLSID_DIB	0
//#define SPRINTF MC_knlSprintk
#define SYSFREE(p)
int SPRINTF(char * buf,char *format,...);
void PRINTF(char *format,...);
#define ISHELL_CloseApplet(m_pIShell, FALSE)  MC_knlExit(FALSE)
#define DBGPRINTF	PRINTF


#define PFNNOTIFY    

extern MCTimer  *g_pTimer;
#define ISHELL_SetTimer(x, wipi_time, y, honest)  MC_knlSetTimer(g_pTimer, wipi_time, honest)
////////////////////is not ok//////////////////////////////////////
#define	IHEAP_Release(m_pIHeap)
#define	IFILEMGR_Release(m_pIFileMgr)

#define	IDIB_Release(m_pIDIB) {if (m_pIDIB) delete []m_pIDIB; m_pIDIB = NULL;}
#define ISHELL_BrowseURL(a, b)	OEMC_knlExecuteEx((signed char*)"NGB", 2, "URL", b);
//void destoryWipi();
///////////////////////////////////////////////////////////////////////////////
//
//Time
//
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
uint16 wYear;
uint16 wMonth;
uint16 wDay;
uint16 wHour;
uint16 wMinute;
uint16 wSecond;
uint16 wWeekDay;
} JulianType;
#define ISHELL_GetUpTimeMS(m_pIShell)  MC_knlCurrentTime()
#define GETTIMEMS MC_knlCurrentTime
#define GETUPTIMEMS	MC_knlCurrentTime
#define GETTIMESECONDS MC_knlCurrentTime
void GETJULIANDATE(time_t mod, JulianType* jt);
#define JULIANTOSECONDS(pDate) 1021524
///////////////////////////////////////////////////////////////////////////////
//
//sound
//
///////////////////////////////////////////////////////////////////////////////
#define AEESoundPlayerInput M_Int32
#define ISound ISoundPlayer
#define ISOUND_RegisterNotify(a,b,c) TRUE
#define IMEDIA_RegisterNotify(a,b,c) TRUE
#define IMedia ISoundPlayer
typedef struct
{
	AEESoundPlayerInput eInput;
	void * pData;
	uint32 dwSize;
} AEESoundPlayerInfo;

#define SOUND_LOOPMUSIC		1
#define SOUND_END		2
#define SOUND_SILENT		4
#define SOUND_PLAYING		8
#define SOUND_INQUEUE		16

#define AEE_MAX_VOLUME 100
#define ISoundPlayer MC_MdaClip
#define AEEMediaData  AEESoundPlayerInfo
#define _IMedia ISoundPlayer 
#define _ISound ISoundPlayer 
#define AEE_SUCCESS 0
#define SDT_BUFFER 0
enum{EIDLE = 0,EITEMBUSY};
#define AEESoundInfo M_Int32
//void ISOUNDPLAYER_Stop(ISoundPlayer * pISoundPlayer);
void ISOUNDPLAYER_Release(ISoundPlayer * pISoundPlayer);
//int ISOUNDPLAYER_GetVolume(ISoundPlayer * pISoundPlayer);
//int ISOUND_GetVolume(ISoundPlayer * pISoundPlayer);
void ISOUNDPLAYER_SetVolume(ISoundPlayer * pISoundPlayer,uint16 wVolume);
void ISOUNDPLAYER_Play(ISoundPlayer * pISoundPlayer, int flag=SOUND_PLAYING);
//int ISOUNDPLAYER_GetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo);
//int ISOUNDPLAYER_SetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo);
#define IMEDIA_Stop  MC_mdaStop
#define IMEDIA_Release MC_mdaClipFree



//#define ISOUND_Release	MC_mdaClipFree
#define ISOUND_Release(a)
//#define IMEDIA_SetMediaData  ISOUNDPLAYER_SetInfo
#define IMEDIA_SetVolume     MC_mdaClipSetVolume
#define IMEDIA_Play          ISOUNDPLAYER_Play
//void NotifyProc(MC_MdaClip* clip, M_Int32 status);
#define ISOUND_Set(p,o)   SUCCESS //is not ok
#define ISOUND_Get(p,o)     //is not ok
#define MAX_STR_LENTH 512
///////////////////////////////////////////////////////////////////////////////
//
//         key
//
///////////////////////////////////////////////////////////////////////////////
#define  AVK_LAST		100 //Robust
#define  AVK_UNDEFINED	200 //Robust
#define  AVK_FIRST		0   //Robust

#define  AVK_SOFT1       MH_KEY_SOFT1
//#define  AVK_SOFT2       MH_KEY_SOFT2
#define  AVK_SOFT3       MH_KEY_SOFT3

#define  AVK_UP          MH_KEY_UP
#define  AVK_LEFT        MH_KEY_LEFT
#define  AVK_RIGHT       MH_KEY_RIGHT
#define  AVK_DOWN        MH_KEY_DOWN
//#define  AVK_SELECT      MH_KEY_SELECT
#define  AVK_CLR         MH_KEY_CLEAR
#define  AVK_1           MH_KEY_1
#define  AVK_2           MH_KEY_2
#define  AVK_3			 MH_KEY_3
#define  AVK_4           MH_KEY_4
#define  AVK_5           MH_KEY_5
#define  AVK_6			 MH_KEY_6
#define  AVK_7           MH_KEY_7
#define  AVK_8           MH_KEY_8
#define  AVK_9			 MH_KEY_9
#define  AVK_STAR        MH_KEY_ASTERISK
#define  AVK_0           MH_KEY_0
#define  AVK_POUND       MH_KEY_POUND
#define  AVK_VOLUME_UP     MH_KEY_SIDE_UP  
#define  AVK_VOLUME_DOWN   MH_KEY_SIDE_DOWN
#define  AEE_INVALID_CODE  MH_KEY_INVALID
#ifdef   W176H220_R
	#define  AVK_SOFT2       MH_KEY_SELECT
	#define  AVK_SELECT      MH_KEY_SOFT2
#else
	#define  AVK_SOFT2       MH_KEY_SOFT2	
	#define  AVK_SELECT      MH_KEY_SELECT
#endif

#define  AVK_END		 MH_KEY_END
#define  AVK_FLIPDOWN		 MH_KEY_FLIPDOWN

///////////////////////////////////////////////////////////////////////////////
//
//math
//
///////////////////////////////////////////////////////////////////////////////

//void GETRAND(unsigned char *buf,int len);
///////////////////////////////////////////////////////////////////////////////
//
//string
//
///////////////////////////////////////////////////////////////////////////////
//int writeUTF(const char* str,unsigned char *out);
//void drawc(int x,int y,MC_GrpFrameBuffer dst);

	float WIPI_sqrt( float number );
//	void* operator new(unsigned int size);
//	void operator delete(void *ptr);

	//void*  WIPI_new(unsigned int size);
	//void WIPI_delete(void *ptr);

	void GETRAND(unsigned char *buf,int len);

	void* MALLOC( long size );// MC_knlAlloc
	void FREE(void *ptr);
//Robust del #define ERROR_TYPE  int

///////////////////////////////////////////////////////////////////////////////
#endif

int ISOUNDPLAYER_SetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo);


#ifdef USE_ALPHA
	#define T_PAL	int
#else
	#define T_PAL	short
#endif
#define ISOUND_Vibrate(a,b) {}]
#define IDISPLAY_GetFontMetrics(a,b,c,d) 13
#define IHEAP_CheckAvail(a,b) (true)
#define WSTRTOSTR(a, b, c)
#define WSTRCOMPRESS(a, b, c, d);





///////////////////////////////////////////////////////////////////////////////