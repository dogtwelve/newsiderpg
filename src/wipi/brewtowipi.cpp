#include "brewtowipi.h"
#include "DeviceInfo.h"
#include "stdarg.h"

#define FILENUM    30

ISoundPlayer * mpISoundPlayer = NULL;
// extern MC_FileInfo fi;
MC_GrpFrameBuffer pdis;
//ISoundPlayer * pISoundPlayer = NULL;
M_Int32 framecolor,fillcolor;
//////////////////////////////////////////////////////////////////////////
///////////       File          //////////  
//////////////////////////////////////////////////////////////////////////
MC_FileInfo fi;
MC_GrpDisplayInfo dif;
M_Int32 resFileSize[FILENUM] , resMemId[FILENUM] , *mid[FILENUM] ,fdCurPos[FILENUM], fd[FILENUM];
M_Int32 saveFile = -1;
int  current_num = 0;
bool issavefunc;
M_Int32 g_ScreenOffset_y = 0;
M_Int32 g_ScreenOffset_x = 0;
M_Int32  g_memSize = 0;
M_Int32  g_spaceSize = 0;

char * STRUPPER(char *c)	//hw++
{	//hw++
	char *ret = c;	//hw++

	while (*c != '\0')	//hw++
	{	//hw++
		if (*c >= 'a' && *c <= 'z')	//hw++
			*c -= 32;	//hw++
		++c;	//hw++
	}	//hw++

	return ret;	//hw++
}	//hw++ ^

char * STRLOWER(char *c)	//hw++ v
{	//hw++
	char *ret = c;	//hw++

	while (*c != '\0')	//hw++
	{	//hw++
		if (*c >= 'A' && *c <= 'Z')	//hw++
			*c += 32;	//hw++
		++c;	//hw++
	}	//hw++

	return ret;	//hw++
}	//hw++ ^

//void* operator new(unsigned int size)
//{
//	// we need to store the id necessary to free the allocated memory
//	// so alloc 4 bytes more, and store it at start, then return the pointer + 4 bytes
//	signed long memID;
//	memID = MC_knlAlloc( size + 4 + 4);
//	if (memID == 0)
//		return NULL;
//	signed long * ptr = (signed long *)MC_GETDPTR(memID);
//	g_memSize += size;
//	g_spaceSize += size;
//	DBGPRINTF("new %d\t%d\n", g_spaceSize, size);
//	int __size = MC_knlGetSharedBufSize( ptr );
//	
//	*ptr = memID;
//	*(ptr+1) = size;
//	memset(ptr + 2,0 ,size);
//	return (ptr + 2);
//}
//
//void operator delete(void *ptr)
//{
//	//from MM
//	//	we need to get the memory ID in WIPI
//	if (ptr != NULL)
//	{
//		signed long size = *((signed long *)ptr - 1);
//		signed long memID = *((signed long *)ptr - 2);
//		g_spaceSize -= size;
//
//		DBGPRINTF("delete %d\t%d\n", g_spaceSize, size);
//
//		MC_knlFree(memID);
//	}
//	//from MM
//}

//void*  WIPI_new(unsigned int size)
//{
//	// we need to store the id necessary to free the allocated memory
//	// so alloc 4 bytes more, and store it at start, then return the pointer + 4 bytes
//	signed long memID;
//	memID = MC_knlAlloc( size + 4 );
//	if (memID == 0)
//		return NULL;
//	signed long * ptr = (signed long *)MC_GETDPTR(memID);
//	*ptr = memID;
//
//	memset(ptr + 1,0 ,size);
//	return (ptr + 1);
//}

//void  WIPI_delete(void *ptr)
//{
//	//from MM
//	//	we need to get the memory ID in WIPI
//	if (ptr != NULL)
//	{
//		signed long memID = *((signed long *)ptr - 1);
//		MC_knlFree(memID);
//	}
//	//from MM
//}
uint32 IFILE_Seek(IFile _file,int type ,int pos)
{
	int __i;
	
	for( __i=0; __i<FILENUM; __i++ )
	{
		if( _file==fd[__i] )
			break;
	}

    if( _file == saveFile )
	{	
		long result;
		switch(type)
		{
		case _SEEK_CURRENT:
			result = MC_fsSeek(_file, pos, MC_FILE_SEEK_CUR);
			break;
		case _SEEK_START:
			result = MC_fsSeek(_file, pos, MC_FILE_SEEK_SET);
			break;
		case _SEEK_END:
			result = MC_fsSeek(_file, pos, MC_FILE_SEEK_END);
			break;
		default:
			break;
		}
		switch(result)
		{
		case M_E_ERROR :
		case M_E_BADFD:
		case M_E_INVALID:
		case M_E_BADSEEKPOS:
			return 0;
		default:
			return 1;
		}
	}
	else
	{
		switch(type)
		{
		case _SEEK_CURRENT:
	//		result = MC_fsSeek(_file, pos, MC_FILE_SEEK_CUR);
			if (_file + pos > fdCurPos[__i] + resFileSize[__i] )
				return FALSE;
			fdCurPos[__i] += pos;
			return fdCurPos[__i]-fd[__i];
			break;
		case _SEEK_START:
	//		result = MC_fsSeek(_file, pos, MC_FILE_SEEK_SET);
			if (_file + pos > fd[__i] + resFileSize[__i] )
				return FALSE;
			fdCurPos[__i] = fd[__i] + pos;
			return fdCurPos[__i];
			break;
		case _SEEK_END:
	//		result = MC_fsSeek(_file, pos, MC_FILE_SEEK_END);
			fdCurPos[__i] = fd[__i] + resFileSize[__i];
			if (fdCurPos[__i] - pos < fd[__i])
				return FALSE;
			fdCurPos[__i] += pos;
			return fdCurPos[__i];
			break;
		default:
			return 0;
		}
		return 0;
	}
}

IFile IFILEMGR_OpenFile(IFileMgr *pIFileMgr, const char *_pack_file, unsigned int i)
{
	int ret;

	if(strstr(_pack_file,".loft") != 0)
	{
		//issavefunc = TRUE; 
		if( i == _OFM_READ)
		{
			if(MC_fsIsExist((signed char *)_pack_file,MC_DIR_PRIVATE_ACCESS) != M_E_SUCCESS)
				return 0;
			ret = MC_fsOpen((signed char *)_pack_file,MH_FILE_OPEN_RDONLY,MC_DIR_PRIVATE_ACCESS);
		}
		else if(i == _OFM_READWRITE)
		{
			//if(MC_fsIsExist((signed char *)_pack_file,MC_DIR_PRIVATE_ACCESS) != M_E_SUCCESS)	//hw-
			//	return 0;	//hw-
			ret = MC_fsOpen((signed char *)_pack_file,MC_FILE_OPEN_RDWR,MC_DIR_PRIVATE_ACCESS);
		}
		else if(i == _OFM_CREATE)
		{
			ret = MC_fsOpen((signed char *)_pack_file, MC_FILE_OPEN_RDWR, MC_DIR_PRIVATE_ACCESS);
		}
		else
		{
			ret = MC_fsOpen((signed char *)_pack_file,MC_FILE_OPEN_RDWR,MC_DIR_PRIVATE_ACCESS);
		}
		
		saveFile = ret;
		MC_fsFileAttribute((signed char *)_pack_file, &fi, MC_DIR_PRIVATE_ACCESS);

		return (ret > 0)?(ret):(0);	//hw++
		//if(  ret>0)	//hw--
		//	return ret;	//hw--
		//else	//hw--
		//	return 0;	//hw--
	}
	else
	{

		issavefunc = FALSE;
		M_Int32 tmpSize = 0;
		long resID = MC_knlGetResourceID ((signed char *)_pack_file, &tmpSize);

		//assert(current_num < 8);
		int index = 0;		
		while (index < FILENUM) //resFileSize[current_num]
		{
			if (resFileSize[index] == tmpSize)  //has been opened before
			{
				current_num = index;
				break;
			}
			else if (resFileSize[index] == 0){
				current_num = index;
				break;
			}
			index++;
		}
		resFileSize[current_num] = tmpSize;
		//current_num = index;

		if (resID != M_E_NOENT)
		{
			resMemId[current_num] = MC_knlCalloc(resFileSize[current_num]+4);
			MC_knlGetResource(resID, (void*)resMemId[current_num], resFileSize[current_num]);
			fd[current_num] = fdCurPos[current_num] = resMemId[current_num];

			return fd[current_num];
		}
		fd[current_num] = fdCurPos[current_num] = NULL;
		return 0;

		//issavefunc = FALSE;
		//long resID = MC_knlGetResourceID((signed char *)_pack_file, &resFileSize[current_num]);
		//if (resID != M_E_NOENT)
		//{
		//	resMemId[current_num] = MC_knlCalloc(resFileSize[current_num]+4);
		//	MC_knlGetResource(resID, (void *)resMemId[current_num], resFileSize[current_num]);
		//	fd[current_num] = fdCurPos[current_num] = resMemId[current_num];

		//	return fd[current_num++];
		//}
		//fd[current_num] = fdCurPos[current_num] = NULL;
		////SAFE_DEL(fd[current_num]);
		////SAFE_DEL(fdCurPos[current_num]);
		//return 0;
	}
}

int32 IFILE_Read(IFile _file,void *buf,int len)
{
	int __i;

	for( __i=0; __i<FILENUM; __i++ )
	{
		if( _file==fd[__i] )
			break;
	}
		
	if( _file == saveFile )
		return (int32)MC_fsRead(_file, (M_Byte *)buf, len);
	else
	{
		if(_file < 0 )
			return -1;
		if (len <= fd[__i] + resFileSize[__i] - fdCurPos[__i])
		{
			memcpy((char*)buf, (char*)(fdCurPos[__i]+4), len);
			fdCurPos[__i] += len;
			return len;
		}
		return -1;
	}
} 

int32 IFILE_Write(IFile _file,const void *buf,int len)
{
	if( _file == saveFile )
		return (int32)MC_fsWrite(_file, (M_Byte *)buf, len);
	return 0;
} 

bool IFILE_GetInfo(IFile _file,FileInfo *info)
{
	int __i;
	
	for( __i=0; __i < FILENUM; __i++ )
	{
		if( _file == fd[__i] )
			break;
	}
	
	if(!issavefunc)
	{
		if(resFileSize[__i] > 0)
			info->dwSize = resFileSize[__i];
		else 
			return FALSE;
		return TRUE;//just for test
	}
	else
	{
 		extern MC_FileInfo fi;
		if(fi.size >= 0)
		{
			info->dwSize = fi.size;
			return TRUE;
 		}
		return FALSE;
	}
}

int32 IFILEMGR_Remove(IFileMgr * pIFileMgr, const char * pszName)
{
	if(issavefunc)
		return (int32)MC_fsRemove((M_Char*)pszName, MC_DIR_PRIVATE_ACCESS);
	return 0;
}
//bool IFILEMGR_GetInfo(IFileMgr pIFileMgr, const char * pszName, FileInfo * pInfo) 
//{
//	MC_FileInfo fileinfo;
//		 MC_fsFileAttribute((signed char *)pszName, &fileinfo, MC_DIR_PRIVATE_ACCESS);
//
//		 	if(fileinfo.size >= 0)
//	{
//		pInfo->dwSize = fileinfo.size;
//		return TRUE;
// 	}else return FALSE;
//}
uint32 IFILE_Release(IFile  pIFile)
{
	int __i;
	
	for( __i=0; __i<FILENUM; __i++ )
	{
		if( pIFile==fd[__i] )
			break;
	}
	
	if( saveFile == pIFile )
	{
		issavefunc = FALSE;
		saveFile = -1;
		return MC_fsClose(pIFile);
	}
	else
	{
		if(resMemId[__i] > 0)
		{
			MC_knlFree(resMemId[__i]);
			pIFile = 0;
		}
		return 0;
	}
}


///////////////////////////////////////////////////////////////////
//
//Graphic
//
////////////////////////////////////////////////////////////////////
MC_GrpContext gc;
#include "..\game\cGame.h"
//
void IDISPLAY_Update(MC_GrpFrameBuffer pIDis)
{
	int rec[4];
	rec[0] = 0;
	rec[1] = 0;
	rec[2] = dif.m_width;
	rec[3] = dif.m_height;
	//for(int i=0; i<240*320*2; i++)
	//{
	//	//g_pGame->_ddb_buffer[i] = (char)i%255;
	//	g_pGame->g->m_buffer[i] = (char)i%255;
	//}
	

	MC_grpSetContext(&gc, MC_GRP_CONTEXT_CLIP_IDX, (void *)rec); 
	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void *)MC_grpGetPixelFromRGB(1,1,1));
	MC_grpFillRect(pIDis, 0, 0,dif.m_width, g_ScreenOffset_y, &gc);
	MC_grpFillRect(pIDis, 0, dif.m_height - g_ScreenOffset_y-1 ,dif.m_width, g_ScreenOffset_y+1, &gc);
	MC_grpFillRect(pIDis, 0, 0,g_ScreenOffset_x, dif.m_height, &gc);
	MC_grpFillRect(pIDis, OS_SCREEN_W + g_ScreenOffset_x, 0,g_ScreenOffset_x+1, dif.m_height, &gc);
	MC_grpFlushLcd( 0, pIDis, 0, 0, dif.m_width, dif.m_height );
}
//void IDISPLAY_SetClipRect(MC_GrpFrameBuffer m_pIDis, AEERect* r)
//{
//	if (r == NULL) return;
//	int rec[4];
//	rec[0] = r->x +g_ScreenOffset_x;
//	rec[1] = r->y + g_ScreenOffset_y;
//	rec[2] = r->x + r->dx +g_ScreenOffset_x;
//	rec[3] = r->y + r->dy + g_ScreenOffset_y;
//
//	MC_grpSetContext(&gc, MC_GRP_CONTEXT_CLIP_IDX, (void*)rec); 
//}
//void IDISPLAY_DrawRect(MC_GrpFrameBuffer m_pIDis, AEERect* r, RGBVAL framecolor, RGBVAL fillcolor, uint32 flag)
//{
//    if (r == NULL) return;
//	int xp[4];
//	int yp[4];
//	uint8 b1 = (framecolor >> 8 & 0xFF);
//	uint8 g1 = ((framecolor >> 16) & 0xFF);
//	uint8 r1 = ((framecolor >> 24) & 0xFF);
//	IGRAPHICS_SetColor(&m_pIDis, r1, g1, b1, 0);
//	b1 = (fillcolor >> 8 & 0xFF);
//	g1 = ((fillcolor >> 16) & 0xFF);
//	r1 = ((fillcolor >> 24) & 0xFF);
//	IGRAPHICS_SetFillColor(&m_pIDis, r1, g1, b1, 0);
//	xp[0] = xp[3] = (r->x +g_ScreenOffset_x);
//	yp[0] = yp[1] = (r->y + g_ScreenOffset_y);
//	xp[1] = xp[2] = (r->x +r->dx+g_ScreenOffset_x );
//	yp[2] = yp[3] = (r->y + r->dy+g_ScreenOffset_y);
//	MC_grpDrawPolygon(m_pIDis, (M_Int32*)xp, (M_Int32*)yp, 4, &gc);
//}
//Robust, modify
//int IDISPLAY_GetDeviceBitmap(  MC_GrpFrameBuffer& GFB, IBitmap **pb)
int IDISPLAY_GetDeviceBitmap(  MC_GrpFrameBuffer& GFB, IBitmap **pb)
{
	int ret = 0;
	MC_GrpFrameBuffer *bufptr = NULL;
	struct _MC_GrpFrameBuffer *buf = NULL;

	if(MC_grpGetDisplayInfo(0, &dif))
	{
		GFB = MC_grpCreateOffScreenFrameBuffer(OS_SCREEN_W, OS_SCREEN_H);
	}
	dif.m_width = OS_SCREEN_W;
	dif.m_height = OS_SCREEN_H;
	pdis = GFB;
	buf = (struct _MC_GrpFrameBuffer *)(MC_GETDPTR(GFB));
	if(!buf)  return ret;
    
	*pb = (IBitmap*)MC_GETDPTR(buf->frameBufID);
    MEMSET(*pb,0,OS_SCREEN_W*OS_SCREEN_H*sizeof(short));
	if(*pb) 
		ret = SUCCESS;
	MC_grpInitContext( &gc );
	MC_grpSetContext( &gc, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(0,0,0) );
	return ret;
}

//int IBITMAP_CreateCompatibleBitmap(IBitmap* ibitmapsrc, IBitmap **  ibitmapdes,uint16 w,uint16 h)
//{
//	int ret = 0;
//
//	*ibitmapdes = (IBitmap*)new byte[dif.m_depth*w*h];
//	*ibitmapdes+= g_ScreenOffset_y*(dif.m_depth/8)*dif.m_width;	
//	if(*ibitmapdes) ret = SUCCESS;
//	return ret;
//
//
//}
				
int IBITMAP_QueryInterface(IBitmap* x, int i, void** idib)
{
	int ret = 1;
	*idib =  GL_NEW IDIB;
	IDIB *pB = (IDIB *)(*idib);
	
	//MC_GrpDisplayInfo dif;
	//if(MC_grpGetDisplayInfo(0, &dif))
	//{	//hw--
		//pB->nPitch = OS_SCREEN_W*2;//dif.m_bpl;	//hw--
		pB->nPitch = OS_SCREEN_W << 1;	//hw++
		pB->nDepth = dif.m_depth ;

		pB->cy = OS_SCREEN_H;	
		pB->cx = OS_SCREEN_W;//DEF_SCR_W;
		//g_ScreenOffset_y = (dif.m_height - OS_SCREEN_H)/2;	//hw--
		//g_ScreenOffset_x = (dif.m_width - OS_SCREEN_W)/2;	//hw--
		g_ScreenOffset_y = (dif.m_height - OS_SCREEN_H) >> 1;	//hw++
		g_ScreenOffset_x = (dif.m_width - OS_SCREEN_W) >> 1;	//hw++
		pB->cx = OS_SCREEN_W + g_ScreenOffset_x;
		//pB->pBmp = x + g_ScreenOffset_y*(dif.m_depth/8)*dif.m_width;	//hw--
		pB->pBmp = x + g_ScreenOffset_y * (dif.m_depth >> 3) * dif.m_width;	//hw++
		//ret = 0;
	//}	//hw--

	return ret;
}
//void IBITMAP_BltIn(IBitmap* buffer, int x,int  y,int  w,int  h,IBitmap* src_buffer, int x1,int  y1, AEERasterOp)
//{
//	if(!(buffer && src_buffer))return;
//	if(x < 0 ) x =0;
//	if(y < 0 ) y =0;
//	if(w < 0 ) w =0;
//	if(h < 0 ) h =0;
//	if(x1 < 0 ) x1 =0;
//	if(y1 < 0 ) y1 =0;
//	uint16* des = (uint16*)buffer;
//	uint16* src = (uint16*)src_buffer;
//
//}
//void IBITMAP_FillRect(void *pIBitmap,const AEERect *prc,NativeColor color,AEERasterOp rop)
//{
//	uint8 r1 = ((color >> 11 & 0xFF) << 3);
//	uint8 g1 = (((color >> 5) & 0xFF) << 2);
//	uint8 b1 = (((color ) & 0xFF) << 3);
//	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void*)MC_grpGetPixelFromRGB(r1,g1,b1));
//	MC_grpFillRect(pdis, prc->x +g_ScreenOffset_x, prc->y+ g_ScreenOffset_y,prc->dx, prc->dy, &gc);
//}
//
//RGBVAL IGRAPHICS_SetColor(IGraphics * pIGraphics,uint8 r,uint8 g,uint8 b,uint8 alpha)
//{
//	
//	framecolor = MC_grpGetPixelFromRGB(r,g,b);
//	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void*)framecolor);
//	return 0;
//}
//RGBVAL IGRAPHICS_SetFillColor(IGraphics * pIGraphics,uint8 r,uint8 g,uint8 b,uint8 alpha)
//{
//	fillcolor = MC_grpGetPixelFromRGB(r,g,b);
////	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void*)fillcolor);
//	return 0;
//}

//int IGRAPHICS_DrawRoundRectangle(IGraphics *pIGraphics,AEERect *pRect,int16 arcWidth,int16 arcHeight)
//{
//	MC_grpDrawRect(pdis, pRect->x+ g_ScreenOffset_x, pRect->y+ g_ScreenOffset_y,pRect->dx, pRect->dy, &gc);
//	///maybe MC_grpDrawArc will do better
//	return 0;
//}

//bool IGRAPHICS_SetFillMode(IGraphics * pIGraphics, bool fFill)
//{
//	if(!fFill)
//		MC_grpSetContext(&gc,MC_GRP_CONTEXT_BG_PIXEL_IDX,(void*)MC_grpGetPixelFromRGB(0,0,0));
//	return 0;
//}

//int IGRAPHICS_DrawTriangle(IGraphics * pIGraphics,AEETriangle * pTriangle)
//{
////	MC_grpDrawLine(pdis,pTriangle->x0,pTriangle->y0,pTriangle->x1,pTriangle->y1);
////	MC_grpDrawLine(pdis,pTriangle->x1,pTriangle->y1,pTriangle->x2,pTriangle->y2);
////	MC_grpDrawLine(pdis,pTriangle->x2,pTriangle->y2,pTriangle->x0,pTriangle->y0);
//	if(!pTriangle) return -1;
//	int x[3],y[3];
//	x[0] = pTriangle->x0 + g_ScreenOffset_x;
//	y[0] = pTriangle->y0 + g_ScreenOffset_y;
//	x[1] = pTriangle->x1 + g_ScreenOffset_x;
//	y[1] = pTriangle->y1 + g_ScreenOffset_y;
//	x[2] = pTriangle->x2 + g_ScreenOffset_x;
//	y[2] = pTriangle->y2 + g_ScreenOffset_y;
//	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void*)framecolor);
//	MC_grpDrawPolygon(pdis, (M_Int32*)x, (M_Int32*)y, 3, &gc);
//	MC_grpSetContext(&gc,MC_GRP_CONTEXT_FG_PIXEL_IDX,(void*)fillcolor);
//	MC_grpFillPolygon(pdis, (M_Int32*)x, (M_Int32*)y, 3, &gc);
//	return 0;
//}
//
//int IGRAPHICS_DrawEllipse(IGraphics * pIGraphics,AEEEllipse * pEllipse)
//{
//	MC_grpDrawArc(pdis,pEllipse->cx - pEllipse->wx + g_ScreenOffset_x,pEllipse->cy - pEllipse->wy + g_ScreenOffset_y,(pEllipse->wx + g_ScreenOffset_x) * 2,(pEllipse->wy+ g_ScreenOffset_y) * 2,0,360,&gc);
//	MC_grpFillArc(pdis,pEllipse->cx - pEllipse->wx + g_ScreenOffset_x,pEllipse->cy - pEllipse->wy + g_ScreenOffset_y,(pEllipse->wx + g_ScreenOffset_x)* 2,(pEllipse->wy + g_ScreenOffset_y)* 2 + 1,0,360,&gc);
//	return 0;
//}

///////////////////////////////////////////////////////////////////////////////
//
//System
//
///////////////////////////////////////////////////////////////////////////////
int vsprintf(char *buf, const char *fmt, va_list args);

int SPRINTF(char *buf,char *format,...)
{
	va_list args;

	va_start(args, format);
	return vsprintf(buf, format, args);
	va_end(args);
}

void PRINTF(char *format,...)
{
	char buf[512];
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);
	MC_knlPrintk((M_Char *)buf, format, args);
}

#define is_digit(c)   ((c) >= '0' && (c) <= '9') 

#define ZEROPAD   1      /* pad with zero */ 
#define _SIGN   2      /* unsigned/signed long */ 
#define PLUS   4      /* show plus */ 
#define SPACE   8      /* space if plus */ 
#define LEFT   16      /* left justified */ 
#define SPECIAL   32      /* 0x */ 
#define SMALL   64      /* use 'abcdef' instead of 'ABCDEF' */ 

static int skip_atoi(const char **s) 
{
   int i=0;

   while (is_digit(**s))
      //i = i*10 + *((*s)++) - '0';	//hw--
	  i = (i << 3) + (i << 1) + *((*s)++) - '0';	//hw++
   return i;
}

static byte do_div(int *num, int base)
{
    byte d;
    d = (*num) % base;
    (*num) = (*num) / base;
    return d;
}

static char * number(char *str, int num, int base, int size, int precision,int type) 
{ 
   char c, sign, tmp[36];
   const char *digits="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int i;

   if (type&SMALL) digits="0123456789abcdefghijklmnopqrstuvwxyz"; 
   if (type&LEFT) type &= ~ZEROPAD; 
   if (base < 2 || base > 36)
      return 0;
   c = (type & ZEROPAD) ? '0' : ' ' ;
   if (type&_SIGN && num<0) {
      sign='-';
      num = -num;
   } else
      sign=(type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);
   if (sign) size--;
   if (type&SPECIAL)
      if (base == 16) size -= 2;
      else if (base == 8) size--;
   i=0;
   if (num == 0)
      tmp[i++] = '0';
   else while (num != 0)
      tmp[i++]=digits[do_div(&num,base)];
   if (i > precision) precision = i;
   size -= precision;
   if (!(type&(ZEROPAD+LEFT))) 
      while(size-->0) 
         *str++ = ' '; 
   if (sign)
      *str++ = sign; 
   if (type&SPECIAL) 
      if (base==8) 
         *str++ = '0'; 
      else if (base==16) { 
         *str++ = '0'; 
         *str++ = digits[33]; 
      } 
   if (!(type&LEFT)) 
      while(size-->0) 
         *str++ = c; 
   while(i<precision--) 
      *str++ = '0'; 
   while(i-->0) 
      *str++ = tmp[i]; 
   while(size-->0) 
      *str++ = ' '; 
   return str; 
} 

int vsprintf(char *buf, const char *fmt, va_list args)
{
        int len;
        int i;
        char * str;
        char *s;
        int *ip;

        int flags;                //flags to number()

        int field_width;        //width of output field
        int precision;                //min. # of digits for integers; max number of chars for from string
        int qualifier;                //'h', 'l', or 'L' for integer fields

        for (str=buf ; *fmt ; ++fmt) {
                if (*fmt != '%') {
                        *str++ = *fmt;
                        continue;
                }
                        
                //process flags
                flags = 0;
                repeat:
                        ++fmt;                //this also skips first '%'
                        switch (*fmt) {
                                case '-': flags |= LEFT; goto repeat;
                                case '+': flags |= PLUS; goto repeat;
                                case ' ': flags |= SPACE; goto repeat;
                                case '#': flags |= SPECIAL; goto repeat;
                                case '0': flags |= ZEROPAD; goto repeat;
                                }
                
                //get field width
                field_width = -1;
                if (is_digit(*fmt))
                        field_width = skip_atoi(&fmt);
                else if (*fmt == '*') {
                        //it's the next argument
                        field_width = va_arg(args, int);
                        if (field_width < 0) {
                                field_width = -field_width;
                                flags |= LEFT;
                        }
                }

                //get the precision
                precision = -1;
                if (*fmt == '.') {
                        ++fmt;        
                        if (is_digit(*fmt))
                                precision = skip_atoi(&fmt);
                        else if (*fmt == '*') {
                                //it's the next argument
                                precision = va_arg(args, int);
                        }
                        if (precision < 0)
                                precision = 0;
                }

                //get the conversion qualifier
                qualifier = -1;
                if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
                        qualifier = *fmt;
                        ++fmt;
                }

                switch (*fmt)
				{
                case 'c':
                        if (!(flags & LEFT))
                                while (--field_width > 0)
                                        *str++ = ' ';
                        *str++ = (unsigned char) va_arg(args, int);
                        while (--field_width > 0)
                                *str++ = ' ';
                        break;
                case 's':
                        s = va_arg(args, char *);
                        len = strlen(s);
                        if (precision < 0)
                                precision = len;
                        else if (len > precision)
                                len = precision;

                        if (!(flags & LEFT))
                                while (len < field_width--)
                                        *str++ = ' ';
                        for (i = 0; i < len; ++i)
                                *str++ = *s++;
                        while (len < field_width--)
                                *str++ = ' ';
                        break;
                case 'o':
                        str = number(str, va_arg(args, unsigned long), 8,
                                field_width, precision, flags);
                        break;
                case 'p':
                        if (field_width == -1)
						{
                            field_width = 8;
                            flags |= ZEROPAD;
                        }
                        str = number(str,
                                (unsigned long) va_arg(args, void *), 16,
                                field_width, precision, flags);
                        break;
                case 'x':
                        flags |= SMALL;
                case 'X':
                        str = number(str, va_arg(args, unsigned long), 16,
                                field_width, precision, flags);
                        break;
                case 'd':
                case 'i':
                        flags |= _SIGN;
                case 'u':
                        str = number(str, va_arg(args, unsigned long), 10,
                                field_width, precision, flags);
                        break;
                case 'n':
                        ip = va_arg(args, int *);
                        *ip = (str - buf);
                        break;
                default:
                        if (*fmt != '%')
                                *str++ = '%';
                        if (*fmt)
                                *str++ = *fmt;
                        else
                                --fmt;
                        break;
                }
        }
        *str = '\0';
        return str-buf;
}

#define time		WIPI_PLT_STD_INVOC_FUNCTION (time)
void GETJULIANDATE(time_t mod, JulianType* jt)
{
   time_t tval;
   struct tm *now;
 
   //Get current date and wipi_time
   tval = time(NULL);
   if(mod == 0)
       now = localtime(&tval);
   else
	   now = localtime(&mod);
   jt->wDay = now->tm_mday;
   jt->wYear = now->tm_year + 1900;//modified by wu nuo the t_m time is a little different
   jt->wMonth = now->tm_mon + 1;
   jt->wHour = now->tm_hour;
   jt->wWeekDay = now->tm_wday;
}
#undef  time
//////////////////////////////
/////Sound     ///////////////
//////////////////////////////

//
//int ISOUND_GetVolume(ISoundPlayer * pISoundPlayer)
//{
//	int value = MC_mdaClipGetVolume(pISoundPlayer);
//	return value;
//
//}
//
//int ISOUNDPLAYER_GetVolume(ISoundPlayer * pISoundPlayer)
//{
//	int value = MC_mdaGetVolume();
//	return value;
//}

void ISOUNDPLAYER_SetVolume(ISoundPlayer * pISoundPlayer,uint16 wVolume)
{
	MC_mdaClipSetVolume(pISoundPlayer, wVolume);
}
AEESoundPlayerInfo soundinfo;
void ISOUNDPLAYER_Play(ISoundPlayer * pISoundPlayer, int flag)
{
		if(pISoundPlayer == NULL)
			return ;
		MC_mdaPlay(pISoundPlayer, SOUND_PLAYING);
// 		nextMidi = -1; // sound will be played, clear the queue
}
//
//void NotifyProc(MC_MdaClip* clip, M_Int32 status)
//{
////	CSound *pSound = (CSound*)pUser;
//
////	if (pCmdNotify->nCmd == MM_CMD_PLAY)  // IMEDIA_Play/IMEDIA_Record events
////	{
////		switch (status)
//// 		{
////         case MC_MDA_STATUS_START:
////			m_pSoundCB->flag &= ~SOUND_MUSICEND;
////			m_pSoundCB->flag |= SOUND_PLAYING;
////			break;
////         case MC_MDA_STATUS_STOPPED:
////			m_pSoundCB->flag |= SOUND_MUSICEND;
////			m_pSoundCB->flag &= ~SOUND_PLAYING;
////		default:
////			break;
//// 		}
////	}
//}

//int ISOUNDPLAYER_GetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo)
//{
//	return 0;
//}
//
//int ISOUNDPLAYER_SetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo)
//{
//	soundinfo.dwSize = pInfo->dwSize;
//	soundinfo.eInput = pInfo->eInput;
//	soundinfo.pData = pInfo->pData;
//
//	if(NULL == soundinfo.pData)
//			return 1;
//		
//	//Free this one before we can play the next
//	if(NULL != pISoundPlayer)
//	{
//		MC_mdaStop(pISoundPlayer);
//		MC_mdaClipFree(pISoundPlayer);
//		pISoundPlayer = NULL;
//	}
//	pISoundPlayer = MC_mdaClipCreate ((signed char *)"Yamaha_SMAF", soundinfo.dwSize, NotifyProc);
//	if(pISoundPlayer != NULL)
//	{
//		MC_mdaClipPutData(pISoundPlayer, (unsigned char *)soundinfo.pData, soundinfo.dwSize);
//	}
//	return AEE_SUCCESS;
//}

//void ISOUNDPLAYER_Stop(ISoundPlayer * pISoundPlayer)
//{
//	if(pISoundPlayer)
//		MC_mdaStop(pISoundPlayer);
//}

void ISOUNDPLAYER_Release(ISoundPlayer * pISoundPlayer)
{
	if(pISoundPlayer)
		MC_mdaClipFree(pISoundPlayer);
}
//
//void GETRAND(unsigned char *buf,int len)
//{
//	for(int i = 0 ;i < len;i ++)
//	{
//		buf[i]  = (unsigned char)((1664525 * MC_knlCurrentTime() + 1013904223)>> 16) ; 
//	}
//}
//
////int writeUTF(const char* str,unsigned char *out)
////{
////	int strl = strlen(str);
////	int utflen = 0;
//// 	char* charr = new char[strl];
////	unsigned int count = 0;
////	byte c;
////
////	memcpy(charr,str,strl);
////	charr[strl] = '\0';
//// 
////	for (int i = 0; i < strl; i++) {
////	    c = charr[i];
////	    if ((c >= 0x0001) && (c <= 0x007F)) {
////		utflen++;
////	    } else if (c > 0x07FF) {
////		utflen += 3;
////	    } else {
////		utflen += 2;
////	    }
////	}
////
////	if (utflen > 65535)
////	    return -1;
////
////	byte* bytearr = out;
////	//bytearr[count++] = (byte) ((utflen >> 8) & 0xFF);
////	//bytearr[count++] = (byte) ((utflen >> 0) & 0xFF);
////	for (int i = 0; i < strl; i++) 
////	{
////	    c = charr[i];
////	    if ((c >= 1) && (c <= 127)) {
////		bytearr[count++] = (byte) c;
////	    } else if (c > 127) {
////		bytearr[count++] = (byte) (0xE0 | ((c >> 12) & 0x0F));
////		bytearr[count++] = (byte) (0x80 | ((c >>  6) & 0x3F));
////		bytearr[count++] = (byte) (0x80 | ((c >>  0) & 0x3F));
////	    } else {
////		bytearr[count++] = (byte) (0xC0 | ((c >>  6) & 0x1F));
////		bytearr[count++] = (byte) (0x80 | ((c >>  0) & 0x3F));
////	    }
////	}
////
////	delete []charr;
////
////	return utflen;
////}
//
//MC_GrpImage imgcorp = 0;
//void drawc(int x,int y,MC_GrpFrameBuffer dst)
//{
//	if(imgcorp == 0)
//	{
//	signed long tempMem; 
//	M_Int32 resFileSize;
//	long resID = MC_knlGetResourceID((M_Char *)"CORP", &resFileSize);
//	if (resID >= 0)
//	{
//		tempMem = MC_knlCalloc(resFileSize);
//		MC_knlGetResource(resID, (void*)tempMem, resFileSize);
//	}
//	
//	MC_grpCreateImage(&imgcorp,tempMem,0,resFileSize);
//	}
//	MC_grpDrawImage(dst, x-5,y-2, 12, 12,imgcorp,0,0,&gc);
////	MC_grpDestroyImage(imgcorp);
//	return;
//
//}
//void destoryWipi()
//{
//	if(imgcorp)
//	MC_grpDestroyImage(imgcorp);
//}
	float WIPI_sqrt( float number )
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = * ( long * ) &y; // evil floating point bit level hacking
		i = 0x5f3759df - ( i >> 1 ); // what the fuck?
		y = * ( float * ) &i;
		y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
				
		return 1/y;
	}

	M_Int64 RandomSeed = (1013904223 ^ 0x5deece66dul) & 0xfffffffffffful;
	
	void GETRAND(unsigned char *buf,int len)
	{
		for(int i = 0 ;i < len;i ++)
		{
            RandomSeed = RandomSeed * 0x5deece66dul + 11ul & 0xfffffffffffful;
            buf[i]  = (unsigned char)(RandomSeed>> 16) ; 
		}
	}

	void* MALLOC( long size ) // MC_knlAlloc
	{
		signed long memID;
		memID = MC_knlAlloc( size + 4 + 4);
		if (memID == 0)
			return NULL;
		signed long * ptr = (signed long *)MC_GETDPTR(memID);
		
		
		g_spaceSize += size;
		//DBGPRINTF("new %d\t%d\t%d \n", g_spaceSize, size , memID);


		*ptr = memID;
		*(ptr+1) = size;
		memset(ptr + 2,0 ,size);
		return (ptr + 2);

		//signed long memID;
		//memID = MC_knlCalloc(size);
		//if (memID == 0)
		//	return NULL;
		//signed long *ptr = (signed long*)MC_GETDPTR(memID);
		//return ptr;
	}

	void FREE( void *ptr)
	{
		if (ptr != NULL)
		{
			signed long size = *((signed long *)ptr - 1);
			signed long memID = *((signed long *)ptr - 2);
			g_spaceSize -= size;

			//DBGPRINTF("delete %d\t%d\t%d \n", g_spaceSize, size,memID);

			MC_knlFree(memID);
		}


		//if (ptr != NULL)
		//{
		//	signed long memID = (M_Uint32)((signed long*)ptr - 1);
		//	MC_knlFree(memID);
		//}
	}

	//void NotifyProc(MC_MdaClip* clip, M_Int32 status)
	//{
	//	//	CSound *pSound = (CSound*)pUser;

	//	//	if (pCmdNotify->nCmd == MM_CMD_PLAY)  // IMEDIA_Play/IMEDIA_Record events
	//	//	{
	//	//		switch (status)
	//	// 		{
	//	//         case MC_MDA_STATUS_START:
	//	//			m_pSoundCB->flag &= ~SOUND_MUSICEND;
	//	//			m_pSoundCB->flag |= SOUND_PLAYING;
	//	//			break;
	//	//         case MC_MDA_STATUS_STOPPED:
	//	//			m_pSoundCB->flag |= SOUND_MUSICEND;
	//	//			m_pSoundCB->flag &= ~SOUND_PLAYING;
	//	//		default:
	//	//			break;
	//	// 		}
	//	//	}
	//}

	//int ISOUNDPLAYER_SetInfo(ISoundPlayer * pISoundPlayer,AEESoundPlayerInfo * pInfo)
	//{
	//	soundinfo.dwSize = pInfo->dwSize;
	//	soundinfo.eInput = pInfo->eInput;
	//	soundinfo.pData = pInfo->pData;

	//	if(NULL == soundinfo.pData)
	//		return 1;

	//	//Free this one before we can play the next
	//	if(NULL != mpISoundPlayer)
	//	{
	//		MC_mdaStop(mpISoundPlayer);
	//		MC_mdaClipFree(mpISoundPlayer);
	//		mpISoundPlayer = NULL;
	//	}
	//	mpISoundPlayer = MC_mdaClipCreate ((signed char *)"Yamaha_SMAF", soundinfo.dwSize, NotifyProc);
	//	if(mpISoundPlayer != NULL)
	//	{
	//		MC_mdaClipPutData(mpISoundPlayer, (unsigned char *)soundinfo.pData, soundinfo.dwSize);
	//	}
	//	return AEE_SUCCESS;
	//}