/*===========================================================================

FILE: BrewMain.c
===========================================================================*/


/*===============================================================================
INCLUDES AND VARIABLE DEFINITIONS
=============================================================================== */
#include "AEEModGen.h"          // Module interface definitions
#include "AEEAppGen.h"          // Applet interface definitions
#include "AEEShell.h"           // Shell interface definitions
#include "Device.h"
#include "Common/Engine.h"
#include "Game\cGame.h"

#include "game.bid"

#ifdef _MSC_VER
// VC2005 can not compile code like : static const AECHAR szNoMem[8][21] = ...;
static const wchar_t szNoMem0[] = L"Memory low!";
static const wchar_t szNoMem1[] = L"Restart the phone";
static const wchar_t szNoMem2[] = L"and try again.";
static const wchar_t szNoMem3[] = L"If you see this";
static const wchar_t szNoMem4[] = L"info again, please";
static const wchar_t szNoMem5[] = L"contact support@";
static const wchar_t szNoMem6[] = L"gameloft.com";
static const AECHAR* szNoMem[8] = 
{ 
	(const AECHAR *)szNoMem0,
	(const AECHAR *)szNoMem1,
	(const AECHAR *)szNoMem2,
	(const AECHAR *)szNoMem3,
	(const AECHAR *)szNoMem4,
	(const AECHAR *)szNoMem5,
	(const AECHAR *)szNoMem6,
};

static const wchar_t szNoDisk0[] = L"Not enough space";
static const wchar_t szNoDisk1[] = L"Free some space";
static const wchar_t szNoDisk2[] = L"and try again.";
static const wchar_t szNoDisk3[] = L"If you see this";
static const wchar_t szNoDisk4[] = L"info again, please";
static const wchar_t szNoDisk5[] = L"contact support@";
static const wchar_t szNoDisk6[] = L"gameloft.com";
static const AECHAR* szNoDisk[8] = 
{ 
	(const AECHAR *)szNoDisk0,
	(const AECHAR *)szNoDisk1,
	(const AECHAR *)szNoDisk2,
	(const AECHAR *)szNoDisk3,
	(const AECHAR *)szNoDisk4,
	(const AECHAR *)szNoDisk5,
	(const AECHAR *)szNoDisk6,
};
#else
static const AECHAR szNoMem[8][21] = 
{ 
	L"Memory low!",
	L"Restart the phone",
	L"and try again.",
	L"If you see this",
	L"info again, please",
	L"contact support@",
	L"gameloft.com"
};
static const AECHAR szNoDisk[8][21] = 
{ 
	L"Not enough space",
	L"Free some space",
	L"and try again.",
	L"If you see this",
	L"info again, please",
	L"contact support@",
	L"gameloft.com"
};

#endif
CEngine* g_pCEngine;
#define MY_EVT_PEN_DOWN   1
#define MY_EVT_PEN_UP   0
#define MY_EVT_PEN_MOVE   2
#define NONE_VALUE_CLICK   -100

static bool BrewMain_HandleEvent(GameApp * pi, AEEEvent eCode, 
                                      uint16 wParam, uint32 dwParam);

static void FreeResources(IApplet *pIApp)
{
	GameApp *pMe = (GameApp *)pIApp;
	if(pMe->m_engine)
	{
		pMe->m_engine->Finalize();
		delete pMe->m_engine;
		pMe->m_engine = NULL;
	}
	//minh_dang dump_memory();
}

int AEEClsCreateInstance(AEECLSID ClsId,IShell * pIShell,IModule * po,void ** ppObj)
{
	*ppObj = NULL;
	
	if(ClsId == AEECLSID_GAME){
		if(AEEApplet_New(sizeof(GameApp), ClsId, pIShell, po, (IApplet**)ppObj,
			(AEEHANDLER)BrewMain_HandleEvent, FreeResources)
			== TRUE)
		{
			return (AEE_SUCCESS);
		}
	}
	return (EFAILED);
}

static void ShowErrorMsg(GameApp *pMe)
{
	AEEDeviceInfo info;
	int i, y;
	int pnAscent, pnDescent;
	int height;
	int nLine = 0;
#ifdef _MSC_VER
	const AECHAR** pMsg = NULL;
#else
	AECHAR const (*pMsg)[21] = NULL;
#endif
	switch(pMe->m_lastError)
	{
	case CEngine::E_SUCCESS:
	case CEngine::E_OTHERS:
		return;
	case CEngine::E_INSUFFICIENT_MEMORY:
		pMsg = szNoMem;
		nLine = 8;
		break;
	case CEngine::E_INSUFFICIENT_STORAGE:
		pMsg = szNoDisk;
		nLine = 8;
		break;
	}

	height = IDISPLAY_GetFontMetrics(pMe->a.m_pIDisplay, AEE_FONT_NORMAL, &pnAscent, &pnDescent);
	
	info.wStructSize = sizeof(info);
	ISHELL_GetDeviceInfo(pMe->a.m_pIShell, &info);
	y = (info.cyScreen - nLine * (height + 1)) / 2;
	
	IDISPLAY_SetColor(pMe->a.m_pIDisplay, CLR_USER_BACKGROUND, RGB_WHITE);
	IDISPLAY_ClearScreen(pMe->a.m_pIDisplay);
	IDISPLAY_SetColor(pMe->a.m_pIDisplay, CLR_USER_TEXT, RGB_BLACK);
	for(i = 0; i < nLine; i++)
	{
		IDISPLAY_DrawText(pMe->a.m_pIDisplay,    // Display instance
			AEE_FONT_NORMAL,       // Use BOLD font
			pMsg[i],              // Text - Normally comes from resource
			-1,                  // -1 = Use full string length
			0,                   // Ignored - IDF_ALIGN_CENTER
			y,                   // Ignored - IDF_ALIGN_MIDDLE
			NULL,                // No clipping
			IDF_ALIGN_CENTER);
		y += height + 1;
	}
	IDISPLAY_Update (pMe->a.m_pIDisplay);
}

static void BrewMain_OnTimer(void *pData)
{
	GameApp *pMe = (GameApp *)pData;
	unsigned int frameStartTick = GetTimeMS();

	if(pMe->m_lastError == CEngine::E_SUCCESS)
		pMe->m_engine->OnTimer();
	else
	{
		ShowErrorMsg(pMe);
	}

	int delayTick;
#ifdef TICK_PER_FRAME_WHEN_LOADING
	if ( pMe->m_bLoading)
	{
		delayTick = TICK_PER_FRAME_WHEN_LOADING - (GetTimeMS() - frameStartTick);
		//DBGPRINTF("*** delayTick == %d", delayTick );
	}
	else
#endif
	delayTick = TICK_PER_FRAME - (GetTimeMS() - frameStartTick);
	
	if (delayTick < MIN_TIMER_INVERVAL)
		delayTick = MIN_TIMER_INVERVAL;
	ISHELL_SetTimer(pMe->a.m_pIShell, delayTick, BrewMain_OnTimer, pMe);
}

static bool BrewMain_HandleEvent(GameApp * pi, AEEEvent eCode, uint16 wParam, uint32 dwParam)
{
	GameApp *pMe = (GameApp *)pi;
	//DBGPRINTF("BrewMain_HandleEvent %d",eCode);
	switch (eCode)
	{
	case EVT_APP_START:
		if (pMe->m_engine == NULL)
		{			
			pMe->m_engine = new cGame();
			//DBGPRINTF("game created");
#ifdef TICK_PER_FRAME_WHEN_LOADING
			pMe->m_bLoading = false;
#endif
		}
		
		if(!pMe->m_engine)
		{
			pMe->m_lastError = CEngine::E_INSUFFICIENT_MEMORY;
		}
		else
		{			
			pMe->m_lastError = pMe->m_engine->Initialize();
		}

		g_pGame->tttt();
		
		BrewMain_OnTimer(pMe);
		
		return(TRUE);
	
	case EVT_APP_STOP:
		if(pMe->m_lastError == CEngine::E_SUCCESS)
		{
			pMe->m_engine->Terminate();
		}		
		ISHELL_CancelTimer(pMe->a.m_pIShell, BrewMain_OnTimer, pMe);
		///on brew 2.0.0 emulator, FreeResources will crash in the app clean-up callback because
		///GETAPPINSTANCE() returns NULL in the callback, so FreeResources must be called here
		///to run correctly.
		///But on some KDDI device, EVT_APP_STOP may not be called if the app is closed by
		///ISHELL_CloseApplet(), so the FreeResources must be call as app clean-up callback.
		FreeResources((IApplet *)pMe);
		return TRUE;

	case EVT_KEY:
		//DBGPRINTF("EVT_KEY");
		GetGameApp()->m_eCode = eCode ;
		GetGameApp()->m_wParam = wParam ;
		GetGameApp()->m_dwParam = dwParam ;
		if(pMe->m_lastError == CEngine::E_SUCCESS)
			return pMe->m_engine->OnKeyEvent(wParam, true) ? TRUE : FALSE;
		else if(wParam != AVK_SEND)
		{
			ISHELL_CloseApplet(pMe->a.m_pIShell, FALSE);
			return TRUE;
		}
		return FALSE;

	case EVT_KEY_RELEASE:
		//DBGPRINTF("EVT_KEY_RELEASE");
		GetGameApp()->m_eCode = eCode ;
		GetGameApp()->m_wParam = wParam ;
		GetGameApp()->m_dwParam = dwParam ;
		if(pMe->m_lastError == CEngine::E_SUCCESS)
			return pMe->m_engine->OnKeyEvent(wParam, false) ? TRUE : FALSE;
		return FALSE;
	case EVT_PEN_DOWN:               //dwParam = position: signed x in upper 16 bits, y in lower
		/*pMe->m_engine->pos_touch_x = dwParam >> 16;
		pMe->m_engine->pos_touch_y = (dwParam & 0xFFFF);
		pMe->m_engine->pos_touch_status = MY_EVT_PEN_DOWN;
		return TRUE;*/
	//case EVT_PEN_STALE_MOVE:
	case EVT_PEN_MOVE:               //dwParam = position: signed x in upper 16 bits, y in lower
	//	pMe->m_engine->pos_touch_x = dwParam >> 16;
	//	pMe->m_engine->pos_touch_y = (dwParam & 0xFFFF);
	//	pMe->m_engine->pos_touch_status = MY_EVT_PEN_MOVE;
	//	return TRUE;
	case EVT_PEN_UP:				//dwParam = position: signed x in upper 16 bits, y in lower
		//pMe->m_engine->pos_touch_x = NONE_VALUE_CLICK;
		//pMe->m_engine->pos_touch_y = NONE_VALUE_CLICK;
		//pMe->m_engine->pos_touch_status = MY_EVT_PEN_UP;
	//	g_pGame->OnTouchEvent((eCode == EVT_PEN_DOWN || eCode == EVT_PEN_MOVE), dwParam >> 16 , dwParam & 0xFFFF);
		return TRUE;

    case EVT_APP_SUSPEND:
	case EVT_ALARM:
		//DBGPRINTF("EVT_APP_SUSPEND");
		if(pMe->m_lastError == CEngine::E_SUCCESS)
		{
			pMe->m_engine->OnSuspend();
			ISHELL_CancelTimer(pMe->a.m_pIShell, BrewMain_OnTimer, pMe);
		}
      	return TRUE;

    case EVT_APP_RESUME:
		//DBGPRINTF("EVT_APP_RESUME");
		if(pMe->m_lastError == CEngine::E_SUCCESS)
		{
			pMe->m_engine->OnResume();
			BrewMain_OnTimer(pMe);
		}
      	return(TRUE);


	case EVT_NOTIFY:
		/*if( ((AEENotify*)dwParam)->pData == AEEBATTERY_STATUS_POWERDOWN )
		{
		pMe->m_engine->OnSuspend();
		pMe->m_engine->OnResume();
		}*/
		return TRUE;


	case EVT_FLIP:
		if(pMe->m_lastError == CEngine::E_SUCCESS)
		{
			pMe->m_engine->Terminate();
			if ( ISHELL_CloseApplet(pMe->a.m_pIShell, TRUE) != SUCCESS )
			{
				ISHELL_CloseApplet(pMe->a.m_pIShell, FALSE);
			}
		}
		return TRUE;

	case EVT_APP_MESSAGE:
		return TRUE;


		//for phones like samsung u420, it pass keyguard. 
	case EVT_KEYGUARD:
		if(wParam == TRUE)
		{
			if ( ISHELL_CloseApplet(pMe->a.m_pIShell, TRUE) != SUCCESS )
			{
				ISHELL_CloseApplet(pMe->a.m_pIShell, FALSE);
			}
			//we handle the key, so the system don't need handle
			return TRUE; 
		}
		return FALSE;
		break;

	case EVT_LOCKED:
	//case EVT_KEYGUARD:
	case EVT_PEN_STALE_MOVE:
		break;


	default:

		//#ifdef DEBUG_MESSAGE_EVENT
		//g_pGame->OnTouchEvent( eCode,  wParam,  dwParam);
		//#endif


		break;
	}
	return FALSE;
}


