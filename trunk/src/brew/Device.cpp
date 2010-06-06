#include "Device.h"
#include "../common/Engine.h"
#include "../common/Image.h"
#include "../common/Keypad.h"
//#include "common/MemoryPool.h"
#include "../common/Memory.h"
#include "..\game\cGame.h" //++sj
#include "../wipi/brewtowipi.h" //++sj;
//#define WIPIC

const uint32 PID_LGVX6000 = 1014;	//from pid table of Qualcomm

CDevice::CDevice():
	m_fileMgr(NULL),
	m_heap(NULL),
	m_pDeviceBitmap(NULL),
	m_screenImage(NULL)
{
}

CDevice::~CDevice()
{
	Close();
}

bool CDevice::Open()
{		
	//create brew components
	//IShell *pIShell = GetGameApp()->a.m_pIShell; --sj
	IShell *pIShell = GetGameApp()->a->m_pIShell;  //++sj
	if(ISHELL_CreateInstance(pIShell, AEECLSID_FILEMGR, (void **)&m_fileMgr) != SUCCESS)
	{
		return FALSE;
	}
	
	if(ISHELL_CreateInstance(pIShell, AEECLSID_HEAP, (void **)&m_heap) != SUCCESS)
	{
		return FALSE;
	}

#ifdef WIPIC

	MC_GrpDisplayInfo di;
	//ZeroMemory( &tem );
	MC_grpGetDisplayInfo(0, &di);
	di.m_width = SCREEN_WIDTH;
	di.m_height = SCREEN_HEIGHT;
	m_screenWidth = di.m_width;
	m_screenHeight = di.m_height;
	m_totalRAM = MC_knlGetSharedBufSize( 0 );

#else
	AEEDeviceInfo di;
	di.wStructSize = sizeof(AEEDeviceInfo);
	ISHELL_GetDeviceInfo(pIShell, &di);

	m_screenWidth = di.cxScreen;
	m_screenHeight = di.cyScreen;

	//Total RAM installed (RAM). 
	m_totalRAM = di.dwRAM;

	m_dwPlatformID = di.dwPlatformID;
#endif

#if BREW_OS == 1

#ifdef AEE_SIMULATOR
	int sizeHeader = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	sizeHeader = (sizeHeader + 3) & ~3;
	m_screenPitch = (di.cxScreen + 3) & ~3;
	unsigned char *p = GL_NEW/*(GetMemoryType(this))*/ unsigned char[sizeHeader + m_screenPitch * di.cyScreen];
	m_pDeviceBitmap = (BITMAPFILEHEADER*)p;
	m_pDeviceBitmap->bfType = 'MB';
	m_pDeviceBitmap->bfSize = sizeHeader + m_screenPitch * di.cyScreen;
	m_pDeviceBitmap->bfOffBits = sizeHeader;
	m_pDeviceBitmap->bfReserved1 = m_pDeviceBitmap->bfReserved2 = 0;
	
	BITMAPINFOHEADER *pinfohdr = (BITMAPINFOHEADER*)(p + sizeof(BITMAPFILEHEADER));
	pinfohdr->biSize = sizeof(BITMAPINFOHEADER);
	pinfohdr->biWidth = di.cxScreen;
	pinfohdr->biHeight = di.cyScreen;
	pinfohdr->biPlanes = 1;
	pinfohdr->biBitCount = 8;
	pinfohdr->biCompression = 0;//BI_BITFIELDS;
	pinfohdr->biSizeImage = di.cxScreen * di.cyScreen;
	pinfohdr->biXPelsPerMeter = 0;
	pinfohdr->biYPelsPerMeter = 0;
	pinfohdr->biClrUsed = 256;
	pinfohdr->biClrImportant = 256;
	RGBQUAD *pPal = (RGBQUAD*)((char*)pinfohdr + sizeof(BITMAPINFOHEADER));
	int r, g, b;
	for (r = 0; r < 8; r++)
		for (g = 0; g < 8; g++)
			for (b = 0; b < 4; b++)
			{
				pPal->rgbRed = (r*255)/7;
				pPal->rgbGreen = (g*255)/7;
				pPal->rgbBlue = (b*255)/3;
				pPal->rgbReserved = 0;
				pPal++;
			}
	m_pScreenPixelData = p + sizeHeader;
	m_screenImage = GL_NEW/*(GetMemoryType(this))*/ CMutableImage(di.cxScreen, di.cyScreen, NATIVE_COLOR_DEPTH, GetMemoryType(this));
#else	
	m_pDeviceBitmap = GL_NEW/*(GetMemoryType(this))*/ NativeImage;
	m_screenImage = GL_NEW/*(GetMemoryType(this))*/ CMutableImage(di.cxScreen, di.cyScreen, NATIVE_COLOR_DEPTH, GetMemoryType(this));

#if DEVICE == DEVICE_N3589i
	const int WINDOWS_BMP_HEADER_SIZE = 54;
	const int NATIVE_BMP_HEADER_SIZE = 40;
	static const uint8 WINDOWS_BMP_HEADER[WINDOWS_BMP_HEADER_SIZE] = { 
		0x42, 0x4D, // Magic number (BM)
		0x38, 0x34, 0x00, 0x00, // File size
		0x00, 0x00, 0x00, 0x00, // Reserved
		0x36, 0x04, 0x00, 0x00, // Offset
		0x28, 0x00, 0x00, 0x00, // Struct size
		0x00, 0x00, 0x00, 0x00, // Width (temp)
		0x00, 0x00, 0x00, 0x00, // Height (temp)
		0x01, 0x00, // Planes
		0x08, 0x00, // Bpp
		0x00, 0x00, 0x00, 0x00, // Compression
		0x00, 0x00, 0x00, 0x00, // Image size
		0x12, 0x0B, 0x00, 0x00, // Horz resolution
		0x12, 0x0B, 0x00, 0x00,  // Vert resolution
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};

	int w = di.cxScreen;
	int h = di.cyScreen;

	int len = (w * h * 2) + NATIVE_BMP_HEADER_SIZE;
	unsigned char* pByte = NEW_TOP unsigned char[len];
	if(!pByte)
	{
		Close();
		return false;
	}
	MEMCPY(pByte, WINDOWS_BMP_HEADER, WINDOWS_BMP_HEADER_SIZE);
	
	// set width
	pByte[18] = w;
	pByte[19] = w >> 8;
	pByte[20] = w >> 16;
	pByte[21] = w >> 24;
	
	// set height  
	pByte[22] = h;
	pByte[23] = h >> 8;
	pByte[24] = h >> 16;
	pByte[25] = h >> 24;
	
	AEEImageInfo pInfo;
	boolean bRealloc;
	
	void *pNativeBmpTmp = CONVERTBMP(pByte, &pInfo, &bRealloc);
	
	//pNativeBmpTmp[29] = 0x0c;
	if(pNativeBmpTmp != NULL)
	{
		MEMCPY(m_pDeviceBitmap->_head, pNativeBmpTmp, NATIVE_BMP_HEADER_SIZE);
		m_pDeviceBitmap->_head[2] = (dword) (m_screenImage->GetPixelData());
		if(bRealloc)
			SYSFREE(pNativeBmpTmp);
	}
	else
	{
		SAFE_DELETE_ARRAY(pByte);
		Close();
		return false;
	}
	SAFE_DELETE_ARRAY(pByte);

#elif DEVICE == DEVICE_Z800 || DEVICE == DEVICE_KZ810
#error Not implemented
#else 
		((dword*)m_pDeviceBitmap->_head)[0] = di.cyScreen;
		((dword*)m_pDeviceBitmap->_head)[1] = di.cxScreen;
		((dword*)m_pDeviceBitmap->_head)[2] = (dword) (m_screenImage->GetPixelData());
#endif
#endif

#else // BREW_OS == 13

#ifdef WIPIC
	
	IDISPLAY_GetDeviceBitmap(GetGameApp()->a->m_pIDisplay, (IBitmap**)&m_pDeviceBitmap);
	IDIB* p1 = (IDIB*)m_pDeviceBitmap;

	int pitch;	
	if(di.m_depth == 8)	
		pitch = 1;	
	else if(di.m_depth <= 16)	
		pitch = 2;	
	else if(di.m_depth <= 32)
		pitch = 4;
	else
	{	
		ASSERT(false);
		pitch = 0;
	}
	pitch *= di.m_width;

	M_Char szAnnuInfoBuf[30];
	OEMC_grpGetAnnunciatorInfo(0, (M_Char*)"HEIGHT", szAnnuInfoBuf, 30);
	for(int i=0; szAnnuInfoBuf[i] != '\0'; i++)
	{
		m_nAnnunciator_Height *= 10;
		m_nAnnunciator_Height += szAnnuInfoBuf[i] - '0';
	}
#ifdef _WIN32
#if defined W240H320
		m_nAnnunciator_Height = 24;
#elif defined W320H240
		m_nAnnunciator_Height = 22;
#elif defined W176H220
		m_nAnnunciator_Height = 16;
#elif defined W128H160
		m_nAnnunciator_Height = 16;
#endif
#endif


	m_screenImage = GL_NEW/*(GetMemoryType(this))*/ CMutableImage(OS_SCREEN_W, OS_SCREEN_H - m_nAnnunciator_Height, pitch, di.m_depth,((char*)m_pDeviceBitmap) + m_nAnnunciator_Height * pitch);	//hw++
	//m_screenImage->GetGraphics().Translate(0, g_pGame->a->m_nAnnunciator_Height);	//hw++
	//g_pGame->g = &g_pGame->m_device->GetScreenImage().GetGraphics();

#else


	IDISPLAY_GetDeviceBitmap(GetGameApp()->a.m_pIDisplay, (IBitmap**)&m_pDeviceBitmap);
	IDIB* p1 = (IDIB*)m_pDeviceBitmap;

	if(p1->nColorScheme == NATIVE_COLOR_DEPTH)
	{
		m_screenImage = (GL_NEW/*(GetMemoryType(this))*/ CMutableImage(p1->cx, p1->cy, p1->nPitch, p1->nColorScheme, p1->pBmp));
	}
	else
	{
		m_screenImage = (GL_NEW/*(GetMemoryType(this))*/ CMutableImage(p1->cx, p1->cy, NATIVE_COLOR_DEPTH, GetMemoryType(this)));
	}

#endif

#endif //BREW_OS == 1
	return true;
}

void CDevice::Close()
{
	SAFE_DELETE(m_screenImage);
#if BREW_OS == 1
	SAFE_DELETE(m_pDeviceBitmap);
#else
	if(m_pDeviceBitmap)
	{
		IBITMAP_Release(m_pDeviceBitmap);
		m_pDeviceBitmap = NULL;
	}
#endif
	if(m_heap)
	{
		IHEAP_Release(m_heap);
		m_heap = NULL;
	}
	if(m_fileMgr)
	{
		IFILEMGR_Release(m_fileMgr);
		m_fileMgr = NULL;
	}
}

void CDevice::SendShutDownMessage()
{
	ISHELL_CloseApplet(GetGameApp()->a.m_pIShell, FALSE);
}

#ifdef TICK_PER_FRAME_WHEN_LOADING
// added by wubin, to speed up loading progress
void CDevice::SendLoadResourceMessage( bool loading )
{
	GetGameApp()->m_bLoading = loading;
}
#endif

void CDevice::FlushToSystemBuffer(Rect16 *rect)
{
#ifndef WIPIC
#ifdef WIPIC
	//IDisplay pIDisplay = GetGameApp()->a->m_pIDisplay;
	IDisplay pIDisplay = g_pGame->m_pIDisplay;
#else
	IDisplay* pIDisplay = GetGameApp()->a.m_pIDisplay;
#endif

#if BREW_OS == 1
#ifdef AEE_SIMULATOR
	if(m_screenImage->GetBitsPerPixel() == 16)
	{
		ConvertRGB565ToRGB332FlipY((unsigned short*)m_screenImage->GetPixelData(), m_pScreenPixelData,
			m_screenImage->GetWidth(), m_screenImage->GetHeight(), m_screenImage->GetPitch(), m_screenPitch);
	}
	else if(m_screenImage->GetBitsPerPixel() == 12)
	{
		ConvertRGB444ToRGB332FlipY((unsigned short*)m_screenImage->GetPixelData(), m_pScreenPixelData,
			m_screenImage->GetWidth(), m_screenImage->GetHeight(), m_screenImage->GetPitch(), m_screenPitch);
	}
	else
		ASSERT(false);
	AEEImageInfo info;
	boolean b;
	void *p = CONVERTBMP(m_pDeviceBitmap, &info, &b);

	IDISPLAY_BitBlt (pIDisplay, 0, 0, m_screenImage->GetWidth(), m_screenImage->GetHeight(), p, 0, 0,  AEE_RO_COPY);
	if(b)
		SYSFREE(p);
#else
	IDISPLAY_BitBlt (pIDisplay, 0, 0, m_screenImage->GetWidth(), m_screenImage->GetHeight(), m_pDeviceBitmap, 0, 0,  AEE_RO_COPY);
#endif
#else
	IDIB* p1 = (IDIB*)m_pDeviceBitmap;
	if(p1->nColorScheme != NATIVE_COLOR_DEPTH)
	{
		if(NATIVE_COLOR_DEPTH == 24)
		{
			if(p1->nColorScheme == IDIB_COLORSCHEME_565)
			{
				ConvertRGB888ToRGB565((unsigned int*)m_screenImage->GetPixelData(),
					(unsigned short*)p1->pBmp, p1->cx, p1->cy, m_screenImage->GetPitch(), p1->nPitch);
			}
			else
				ASSERT(false);
		}
		else if(NATIVE_COLOR_DEPTH == 16)
		{
			if(p1->nColorScheme == 18)
			{
				ConvertRGB565ToRGB666((unsigned short*)m_screenImage->GetPixelData(),
					(unsigned int*)p1->pBmp, p1->cx, p1->cy, m_screenImage->GetPitch(), p1->nPitch);
			}
			else
				ASSERT(false);
		}
		else
			ASSERT(false);
	}
#endif

#endif //WIPIC
}


void CDevice::UpdateToScreen(Rect16 *rect)
{
#ifdef WIPIC
	IDisplay pIDisplay = g_pGame->m_pIDisplay;	//hw++
	IDisplay aapIDisplay = GetGameApp()->a->m_pIDisplay;	//hw++
	IDISPLAY_Update(pIDisplay);	//hw++
#else

	IDisplay* pIDisplay = GetGameApp()->a.m_pIDisplay;

	AEERect r1, r2;
	if(rect)
	{
		r1.x = rect->x;
		r1.y = rect->y;
		r2.x = rect->x + rect->w - 1;
		r2.y = rect->y + rect->y - 1;
	}
	else
	{
		r1.x = 0;
		r1.y = 0;
		r2.x = m_screenImage->GetWidth() - 1;
		r2.y = m_screenImage->GetHeight() - 1;
	}
	r1.dx = 1;
	r1.dy = 1;
	r2.dx = 1;
	r2.dy = 1;
	IDISPLAY_InvertRect(pIDisplay, &r1);
	IDISPLAY_InvertRect(pIDisplay, &r1);
	IDISPLAY_InvertRect(pIDisplay, &r2);
	IDISPLAY_InvertRect(pIDisplay, &r2);
	IDISPLAY_UpdateEx(pIDisplay, FALSE);
#endif
}

void CDevice::ConvertRGB444ToRGB332FlipY(unsigned short *ps, unsigned char *pd, int w, int h, int spitch, int dpitch)
{
	int s_inc = spitch - w * 2;
	int d_inc = - (dpitch + w);
	pd += dpitch * (h - 1);
	do
	{
		unsigned char *end = pd + w;
		while(pd != end)
		{
			unsigned int s = *ps++;
			*pd++ = ((s >> 4) & 0xE0) | ((s >> 3) & 0x1C) | ((s >> 2) & 0x3);
		}
		pd += d_inc;
		ps = (unsigned short*)((char*)ps + s_inc);
	}while(--h != 0);
}

void CDevice::ConvertRGB565ToRGB332FlipY(unsigned short *ps, unsigned char *pd, int w, int h, int spitch, int dpitch)
{
	int s_inc = spitch - w * 2;
	int d_inc = - (dpitch + w);
	pd += dpitch * (h - 1);
	do
	{
		unsigned char *end = pd + w;
		while(pd != end)
		{
			unsigned int s = *ps++;
			*pd++ = ((s >> 8) & 0xE0) | ((s >> 6) & 0x1C) | ((s >> 3) & 0x3);
		}
		pd += d_inc;
		ps = (unsigned short*)((char*)ps + s_inc);
	}while(--h != 0);
}

void CDevice::ConvertRGB888ToRGB565(unsigned int *ps, unsigned short *pd, int w, int h, int spitch, int dpitch)
{
	int s_inc = spitch - w * 4;
	int d_inc = dpitch - w * 2;
	do
	{
		unsigned short *end = pd + w;
		while(pd != end)
		{
			unsigned int s = *ps++;
			*pd++ = ((s >> 8) & 0xF800) | ((s >> 5) & 0x7E0) | ((s >> 3) & 0x1F);
		}
		pd = (unsigned short*)((char*)pd + d_inc);
		ps = (unsigned int*)((char*)ps + s_inc);
	}while(--h != 0);
}

void CDevice::ConvertRGB565ToRGB666(unsigned short *ps, unsigned int *pd, int w, int h, int spitch, int dpitch)
{
	int s_inc = spitch - w * 2;
	int d_inc = dpitch - w * 4;
	do
	{
		unsigned int *end = pd + w;
		while(pd != end)
		{
			unsigned int s = *ps++;
			*pd++ = ((s & 0xF800) << 2) | ((s & 0x7E0) << 1) | ((s & 0x1F) << 1);
		}
		pd = (unsigned int*)((char*)pd + d_inc);
		ps = (unsigned short*)((char*)ps + s_inc);
	}while(--h != 0);
}
//////////////////////////////////////////////////////////////////////////
//File System
//////////////////////////////////////////////////////////////////////////
unsigned int CDevice::GetFreeSpace()
{
	return IFILEMGR_GetFreeSpace((IFileMgr*)m_fileMgr,NULL);
}

unsigned int CDevice::GetFileSize(const char *fn)
{
#ifdef WIPIC
	MC_FileInfo fileinfo;	//hw++
	MC_fsFileAttribute((signed char *)fn, &fileinfo, MC_DIR_PRIVATE_ACCESS);	//hw++

	return (fileinfo.size >= 0)?(fileinfo.size):(0);	//hw++
#else
	FileInfo fi;
	IFILEMGR_GetInfo((IFileMgr*)m_fileMgr, fn, &fi);
	return fi.dwSize;
#endif
}

bool CDevice::IsFileReadOnly(const char *fn)
{
#ifdef WIPIC
	return false;
#else
	FileInfo fi;
	IFILEMGR_GetInfo((IFileMgr*)m_fileMgr, fn, &fi);
	return (fi.attrib == _FA_READONLY);
#endif
}

bool CDevice::RemoveFile(const char *fn)
{
	return (SUCCESS == IFILEMGR_Remove((IFileMgr*)m_fileMgr, fn));
}


bool CDevice::IsFileExist(const char *fn)
{
	return (SUCCESS == IFILEMGR_Test((IFileMgr*)m_fileMgr, fn));
}


//////////////////////////////////////////////////////////////////////////
//Memory
//////////////////////////////////////////////////////////////////////////
unsigned int CDevice::GetTotalRAM()
{
	return m_totalRAM;
}

unsigned int CDevice::GetFreeRAM()
{
#ifdef WIPIC
	return 2;
#else
	return m_totalRAM - IHEAP_GetMemStats((IHeap*)m_heap);
#endif
}

unsigned int CDevice::GetLargestRAMBlock()
{
#ifdef WIPIC
	return 0;
#else
	unsigned long total, m;
	GETRAMFREE(&total, &m);
	return m;
#endif
}

void CDevice::GetModuleVersion(AECHAR* buf, int size)
{
#ifndef WIPIC
	int aa = ISHELL_GetAppVersion(GetGameApp()->a.m_pIShell, (AECHAR*)buf, size); 
	ASSERT(aa != 0);
#endif
}

void CDevice::GetModuleVersion(char* buf, int size)
{
	ASSERT(size < 30 * 2);
	AECHAR temp[30];	
	GetModuleVersion(temp, 30*2);
	WSTRTOSTR(temp, buf, size);
}


int CDevice::KeyIndexFromDeviceKey(unsigned int code)
{


#if DEVICE == DEVICE_LG9800
	switch(code)
	{
	case AVK_1:
		return CKeypad::DK_NUM1_INDEX;
	case AVK_0:
		return CKeypad::DK_NUM0_INDEX;
	case AVK_2:
		return CKeypad::DK_NUM2_INDEX;
	case AVK_3:
		return CKeypad::DK_NUM3_INDEX;
	case AVK_4:
		return CKeypad::DK_NUM4_INDEX;
	case AVK_5:
		return CKeypad::DK_NUM5_INDEX;
	case AVK_6:
		return CKeypad::DK_NUM6_INDEX;
	case AVK_7:
		return CKeypad::DK_NUM7_INDEX;
	case AVK_8:
		return CKeypad::DK_NUM8_INDEX;
	case AVK_9:
		return CKeypad::DK_NUM9_INDEX;
	case AVK_UP:
		return CKeypad::DK_PAD_UP_INDEX;
	case AVK_DOWN:
		return CKeypad::DK_PAD_DOWN_INDEX;
	case AVK_LEFT:
		return CKeypad::DK_PAD_LEFT_INDEX;
	case AVK_RIGHT:
		return CKeypad::DK_PAD_RIGHT_INDEX;
	case AVK_SELECT:
		return CKeypad::DK_PAD_MIDDLE_INDEX;
	case AVK_SOFT1:
		return CKeypad::DK_SOFT_LEFT_INDEX;
	case AVK_SOFT2:
		return CKeypad::DK_SOFT_RIGHT_INDEX;
	case AVK_CLR:
		return CKeypad::DK_CLEAR_INDEX;	
	default:
		return -1;*/
			case AVK_0:
		return CKeypad::DK_NUM0_INDEX;
#ifdef BREW_DEBUG1
	case 57408:	// Sym
		return CKeypad::DK_NUM5_INDEX;
	case AVK_2:
		return CKeypad::DK_NUM2_INDEX;
	case AVK_4:
		return CKeypad::DK_NUM4_INDEX;
	case AVK_5:
		return CKeypad::DK_NUM5_INDEX;
	case AVK_6:
		return CKeypad::DK_NUM6_INDEX;
	case AVK_7:
		return CKeypad::DK_NUM7_INDEX;
	case AVK_8:
		return CKeypad::DK_NUM8_INDEX;
	case AVK_9:
		return CKeypad::DK_NUM9_INDEX;
#endif
	case AVK_1:
		return CKeypad::DK_NUM1_INDEX;

	case AVK_3:
		return CKeypad::DK_NUM3_INDEX;	

	case AVK_UP:
		return CKeypad::DK_PAD_UP_INDEX;
	case AVK_DOWN:
		return CKeypad::DK_PAD_DOWN_INDEX;
	case AVK_LEFT:
		return CKeypad::DK_PAD_LEFT_INDEX;
	case AVK_RIGHT:
		return CKeypad::DK_PAD_RIGHT_INDEX;
	case AVK_SELECT:
		return CKeypad::DK_PAD_MIDDLE_INDEX;
	case AVK_SOFT1:
		return CKeypad::DK_SOFT_LEFT_INDEX;
	case AVK_SOFT2:
		return CKeypad::DK_SOFT_RIGHT_INDEX;
	case AVK_CLR:
		return CKeypad::DK_CLEAR_INDEX;	
	default:
		return -1;
	}
#endif

	switch(code)
	{
	case AVK_0:
		return CKeypad::DK_NUM0_INDEX;
	case AVK_1:
		return CKeypad::DK_NUM1_INDEX;
	case AVK_2:
		return CKeypad::DK_NUM2_INDEX;
	case AVK_3:
		return CKeypad::DK_NUM3_INDEX;
	case AVK_4:
		return CKeypad::DK_NUM4_INDEX;
	case AVK_5:
		return CKeypad::DK_NUM5_INDEX;
	case AVK_6:
		return CKeypad::DK_NUM6_INDEX;
	case AVK_7:
		return CKeypad::DK_NUM7_INDEX;
	case AVK_8:
		return CKeypad::DK_NUM8_INDEX;
	case AVK_9:
		return CKeypad::DK_NUM9_INDEX;

	case AVK_STAR:
		return CKeypad::DK_STAR_INDEX;
		
	case AVK_POUND:
		return CKeypad::DK_POUND_INDEX;
	
	case AVK_UP:
		return CKeypad::DK_PAD_UP_INDEX;
	case AVK_DOWN:
		return CKeypad::DK_PAD_DOWN_INDEX;
	case AVK_LEFT:
		return CKeypad::DK_PAD_LEFT_INDEX;
	case AVK_RIGHT:
		return CKeypad::DK_PAD_RIGHT_INDEX;
	case AVK_SELECT:
		return CKeypad::DK_PAD_MIDDLE_INDEX;
	case AVK_SOFT1:
		return CKeypad::DK_SOFT_RIGHT_INDEX;//return CKeypad::DK_SOFT_LEFT_INDEX;

	//case AVK_MENU:
	case AVK_SOFT2:
		return CKeypad::DK_SOFT_LEFT_INDEX;//return CKeypad::DK_SOFT_RIGHT_INDEX;
	case AVK_CLR:
		return CKeypad::DK_CLEAR_INDEX;	
	default:
		return -1;
	}
}



void CDevice::DrawSysText(const char *str, int x, int y)
{
	AECHAR wstr[200];
	wstr[0] = 0;
#ifdef WIPIC
	IDISPLAY_DrawText(g_pGame->m_pIDisplay, AEE_FONT_NORMAL, wstr, -1, x, y, NULL, IDF_TEXT_TRANSPARENT);
#else
	STRTOWSTR(str, wstr, sizeof(wstr));
	IDISPLAY_DrawText(GetGameApp()->a.m_pIDisplay, AEE_FONT_NORMAL, wstr, -1, x, y, NULL, IDF_TEXT_TRANSPARENT);
#endif
}

CRawFile::CRawFile():
	m_file(NULL)
{
}

CRawFile::~CRawFile()
{
	Close();
}

bool CRawFile::Open(const char *fn, int mode)
{
	AEEOpenFileMode m; 
	if(mode & MODE_CREATE)
		m = _OFM_CREATE;
	else if(mode & MODE_WRITE)
		m = _OFM_READWRITE;
	else if(mode & MODE_APPEND)
		m = _OFM_APPEND;
	else
		m = _OFM_READ;

	m_file = IFILEMGR_OpenFile(GetDevice().m_fileMgr, fn, m);
	return m_file != NULL;
}

void CRawFile::Close()
{
	if(m_file)
	{
		IFILE_Release(m_file);
		m_file = NULL;
	}
}

bool CRawFile::Seek(int moveDistance, int seekMode)
{
	//FileSeekType t;
	if(seekMode == FSEEK_BEGIN)
	{
		//t = _SEEK_START;
		return IFILE_Seek(m_file, _SEEK_START, moveDistance) == SUCCESS;
	}
	else if(seekMode == FSEEK_CURRENT)
	{
		//t = _SEEK_CURRENT;
		return IFILE_Seek(m_file, _SEEK_CURRENT, moveDistance) == SUCCESS;
	}
	else if(seekMode == FSEEK_END)
	{	
		//t = _SEEK_END;
		return IFILE_Seek(m_file, _SEEK_END, moveDistance) == SUCCESS;
	}
	else
	{
		ASSERT(false);
		return false;
	}

	//if(t == _SEEK_CURRENT && moveDistance == 0)
	//	//in this case, IFILE_Seek just return the file position
	//	return true;
	//return IFILE_Seek(m_file, t, moveDistance) == SUCCESS;
}

unsigned int CRawFile::GetLength()
{
	FileInfo info;
	IFILE_GetInfo(m_file, &info);
	return info.dwSize;
}



int CDevice::GetScreenWidth()
{ 
	return  GetDevice().m_screenWidth; 
}

int CDevice::GetScreenHeight()
{ 
	return GetDevice().m_screenHeight; 
}
