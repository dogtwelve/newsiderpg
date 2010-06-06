#include "../common/Common.h"
#include "../common/Engine.h"
#include "../config_version.h"
#include "Device.h"

int StrLen(const char * str)
{
	ASSERT(str != NULL);

	int len = 0;
	//while(str[len] != '\0')	//--
	while(str != NULL && str[len] != '\0')	//++
	{
		len++;
	}
	return len;
}

int StrChr(const char * str, char c)
{
	const char* temp = str;
	int pos = 0;
	while(*temp != 0)
	{
		if(*temp == c) //equals
		{
			return pos;
		}
		pos++;
		temp++;
	}
	return -1;
}

unsigned int GetTimeMS()
{
	return GETTIMEMS();
}

int _rand(int min,int max)
{
	
	int random;
	int value;
	byte randbuffer[3] = {0};
	GETRAND(randbuffer, sizeof(randbuffer));
	random = randbuffer[0]*65536+randbuffer[1]*256+randbuffer[2];

	value = random;
	if (value < 0)
		value = -value;
	return ((value%(max - min + 1)) + min);
}
			
#ifdef DEBUG_N3589i
void MyDbgout(const char *str, int delay)
{
	CDevice &pDevice = GetDevice();

	IFile *DBGFILE = IFILEMGR_OpenFile (pDevice.m_fileMgr , "MyDbgout.txt", _OFM_CREATE);
		
	if(!DBGFILE)
		DBGFILE = IFILEMGR_OpenFile(pDevice.m_fileMgr, "MyDbgout.txt", _OFM_APPEND );
		
	if(DBGFILE != NULL)
	{
		char DBGTEXT[50];
		SPRINTF(DBGTEXT, "**** %s ****\n", str);
		IFILE_Write((IFile *)DBGFILE, DBGTEXT,  STRLEN(DBGTEXT));
		IFILE_Release(DBGFILE);
	}

	IDISPLAY_DrawHLine(GetGameApp()->a.m_pIDisplay, 0, 0, 1);
	IDISPLAY_DrawHLine(GetGameApp()->a.m_pIDisplay, DScreen::SCREEN_WIDTH - 2, DScreen::SCREEN_HEIGHT - 1, 2);

	AECHAR outText[100];

	STREXPAND((unsigned char*)str, STRLEN(str), outText,100);

	IDISPLAY_ClearScreen(GetGameApp()->a.m_pIDisplay);
	
	IDISPLAY_DrawText(	GetGameApp()->a.m_pIDisplay,		// Display instance
						AEE_FONT_BOLD,       // Use BOLD font
						outText,			 // Text - Normally comes from resource
						-1,                  // -1 = Use full string length
						0,                   // Ignored - IDF_ALIGN_CENTER
						25,					// Ignored - IDF_ALIGN_MIDDLE
						NULL,                // No clipping
						IDF_ALIGN_CENTER);
	
	IDISPLAY_UpdateEx(GetGameApp()->a.m_pIDisplay, false);

	int start = GETUPTIMEMS();
	int end = start;

	while(end - start < delay)
	{
		end = GETUPTIMEMS();
	}	
}
#endif

#ifdef BIGENDIAN
short ConvertLD2BE(short n)
{
	char *buf = (char*)&n;
	return buf[0] + (buf[1] << 8);
}

int ConvertLD2BE(int n)
{
	char *buf = (char*)&n;
	return buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
}
#endif


int Integer_ParseToInt(const char* str)
{
	return ATOI(str);
}

char* TRIM (char* str)
{
	if(str == "")return str;
	int len = StrLen(str);
	int head = 0 ;

	while( head < len && str[head] == ' ')head++ ;

	int tail = len - 1 ;

	while( tail > 0 && str[tail] == ' ')tail-- ;

	if(str[tail] == ' ')
	{
		str[0] = '\0';return str ;
	}	
	
	for(int i = head ; i <= tail ; i++ )
	{
		str[ i - head ] = str[i] ;
	}

	str[tail - head + 1 ] = '\0';

	return str;

}

int s_math_random_nextInt()
{
	return _rand(0, 0x7FFFFFFE);
}

