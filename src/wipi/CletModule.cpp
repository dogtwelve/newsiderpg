/*
** ===========================================================================
**
** Project: 
**     WIPI
**
** File:
**     CletModule.c
**
** Description: 
**     Application Skeleton 
**
** ===========================================================================
*/



/* 
**----------------------------------------------------------------------------
**  INCLUDE FILES FOR MODULE
**---------------------------------------------------------------------------- 
*/

//For Using WIPI API
#include	"WIPIheader.h"
#include "../common/memory.h"



/* 
**----------------------------------------------------------------------------
**  VARIABLES FOR MODULE
**---------------------------------------------------------------------------- 
*/


/* 
**----------------------------------------------------------------------------
**  FUCTION PROTOTYPES
**---------------------------------------------------------------------------- 
*/


/* 
**----------------------------------------------------------------------------
**   LAYOUTS FOR MODULE
**---------------------------------------------------------------------------- 
*/
//#define USE_XPLAYER
#include "..\game\cGame.h"
#ifdef USE_XPLAYER
	#include "../game/NetSource/cXPlayerMenus.h"
#endif
class cGame;
//cGame *g_pGame;
CEngine* g_pCEngine;
//cUI* g_pcUI;//SangHo - Ű�̺�Ʈ �ӽ� ����
MCTimer *g_pTimer;
#define FPS_LIMIT 67

bool isPause = false;
bool bCallEventCome = false;

int keyCodePress = 0;//SangHo - Key �̺�Ʈ �ӽñ���
int keyCodeRelease = 0;//SangHo - Key �̺�Ʈ �ӽñ���
bool keyLife = false;//SangHo - Key �̺�Ʈ �ӽñ���
bool keyRepeat=false;//SangHo - Key �̺�Ʈ �ӽñ���

GameApp* g_apGame;

static const int SPEED[] = {50,30,19};//Chen Shoutian, fixed bug 	1476556
extern "C"
{


	void BrewMain_OnTimer(MCTimer * tm, void *pData)
	{
		GameApp *pMe = (GameApp *)pData;
		CGame* m_pGame = (CGame*)pMe->m_engine;
		unsigned int frameStartTick = MC_knlCurrentTime();

		if(pMe->m_lastError == CEngine::E_SUCCESS)
		{
			pMe->m_engine->OnTimer();
		} 
		else
		{
#ifndef  _WINDOWS

			//ShowErrorMsg(pMe->m_lastError);
#endif
		}

		int frameEndTick = MC_knlCurrentTime();

		int delayTick = (1000/SPEED[g_pGame->m_speed]) - (frameEndTick - frameStartTick);

		//if (delayTick < MIN_TIMER_INVERVAL)
		{
			delayTick = MIN_TIMER_INVERVAL;
		}

		MC_knlSetTimer(tm, delayTick, pMe);

		//ISHELL_SetTimer(pMe->a.m_pIShell, delayTick, BrewMain_OnTimer, pMe);


		/*M_Int64 frameStartTick = MC_knlCurrentTime();

		g_pGame->OnTimer();

		M_Int64 frameEndTick = MC_knlCurrentTime();
		
		M_Int64 delayTick = (1000/SPEED[g_pGame->m_speed]) - (frameEndTick - frameStartTick);

		if (delayTick < MIN_TIMER_INVERVAL)
			delayTick = MIN_TIMER_INVERVAL;

		if(!isPause){
			ISHELL_SetTimer(pMe->a.m_pIShell, delayTick, BrewMain_OnTimer, g_pGame);
		}*/





		//cGame* pGame = g_pGame;
		//if (pGame->s_game_isPaused)return;

		//M_Int64 _lastUpdateExTIME = GETUPTIMEMS() - pGame->mOldTime;	


		//
		//M_Int64 diff = GETUPTIMEMS();

		//pGame->run();

		//diff = (GETUPTIMEMS() - diff) + _lastUpdateExTIME;	
		//
		//// restart timer
		//if (diff < FPS_LIMIT)
		//{		
		//	pGame->_frameTime = FPS_LIMIT;
		//	diff = FPS_LIMIT - diff;		
		//}
		//else
		//{				
		//	pGame->_frameTime = diff;
		//	diff = 1;				
		//}	

		////ISHELL_SetTimer(pGame->m_pIShell, diff, BrewMain_OnTimer, pGame);
		//MC_knlSetTimer(g_pTimer, diff, g_pGame);
		//pGame->mOldTime = GETUPTIMEMS() + diff;

	}

	/* �̺�Ʈ�� ó���ϴ� �Լ��̴�.*/
#define RESUME_TICK 500
	void handleCletEvent( int type, int param1, int param2 ) 
	{
#ifdef USE_XPLAYER
		cXPlayerMenus *cRk_ = cXPlayerMenus::getInstance();	
		if( cRk_ && cRk_->GetInputState() )
		{
			MC_uicHandleEvent( cRk_->_cText, type, param1, param2 );

			if( param1 != MH_KEY_SELECT && param1 != MH_KEY_SOFT1 && param1 != MH_KEY_SOFT2 && param1 != MH_KEY_SOFT3 )
			{
				cRk_->_bDrawBackPaint |= REPAINT_UI;
				return;
			}
		}
#endif
		switch( type )
		{
			// Key press
		case MV_KEY_PRESS_EVENT:
			{
				keyCodeRelease = 0;//SangHo - RELEASE �� PRESS �� ����ȣ��Ǹ� PRESS�� �켱���Ѵ� 

				keyCodePress = param1;//SangHo - Key �̺�Ʈ �ӽñ���
				keyLife = true;
				keyRepeat=false;

				//SangHo - Key �̺�Ʈ �ӽ� ��
				//if(GetGameApp()->m_lastError == CEngine::E_SUCCESS)
				//{
				//	GetGameApp()->m_engine->OnKeyEvent(param1, true);
				//}
				
				break;
			}
		case MV_KEY_RELEASE_EVENT:
			{	

				keyCodeRelease = param1;//SangHo - �ӽñ���
				keyRepeat=false;
				
				//SangHo - Key �̺�Ʈ �ӽ� ��
				//GetGameApp()->m_engine->OnKeyEvent(param1, FALSE);
				//break;
			}
			break;
		case MV_BACKG_EVENT:
		case MV_PLTBACKG_EVENT:
			if(!isPause)
			{
				isPause = true;
				if(GetGameApp()->m_lastError == CEngine::E_SUCCESS) 
				{
					GetGameApp()->m_engine->OnSuspend();
				}
#ifdef USE_XPLAYER
				cXPlayerMenus *ptr = cXPlayerMenus::getInstance();
				if( ptr )
				{
					ptr->XPlayer_pause();
				}
#endif
				//g_pGame->s_cEngine->setPauseState();
			}
			break;
		case MV_FOREG_EVENT:
		case MV_PLTFOREG_EVENT:
			if(isPause)
			{
				isPause = false;
				if(GetGameApp()->m_lastError == CEngine::E_SUCCESS)
				{
					GetGameApp()->m_engine->OnResume();
					BrewMain_OnTimer(NULL, g_pGame);
				}
				//ISHELL_SetTimer(pMe->a.m_pIShell, RESUME_TICK, BrewMain_OnTimer, g_pGame);
			}
			break;
		case MV_CALL_EVENT:
			bCallEventCome = !bCallEventCome;
			if( bCallEventCome && !isPause)
			{
				isPause = true;
				if(GetGameApp()->m_lastError == CEngine::E_SUCCESS) 
				{
					GetGameApp()->m_engine->OnSuspend();
				}
				//g_pGame->s_cEngine->setPauseState();
#ifdef USE_XPLAYER
				cXPlayerMenus *ptr = cXPlayerMenus::getInstance();
				if( ptr )
				{
					ptr->XPlayer_pause();
				}
#endif
			}
			else if(isPause)
			{
				isPause = false;
				if(GetGameApp()->m_lastError == CEngine::E_SUCCESS)
				{
					GetGameApp()->m_engine->OnResume();
					BrewMain_OnTimer(NULL, g_pGame);
				}
				//ISHELL_SetTimer(pMe->a.m_pIShell, RESUME_TICK, BrewMain_OnTimer, g_pGame);
			}
			break;
		}
		//MC_knlPrintk( "param1 = %d, param2 = %d\n", param1, param2 );
	}

	/* ���α׷��� ���۵� �� �Ҹ��� �Լ��̴�. */
	void startClet( int argc, char *argv[] )
	{	
		MC_miscBackLight(0, MC_LIGHT_ALWAYS_ON , 0xffffffff, 1000);//�����Ʈ
		MC_mdaSetMuteState(MC_MDA_VOLTYPE_KEYTONE, TRUE);//Ű�� ����
		OEMC_grpShowAnnunciator(0, TRUE);//��� ǥ������
		
		if (g_apGame == NULL)
		{	
			g_apGame = GL_NEW GameApp();
			g_apGame->m_engine = GL_NEW cGame();
			g_apGame->a = (cGame*)g_apGame->m_engine;
			//DBGPRINTF("game created");
#ifdef TICK_PER_FRAME_WHEN_LOADING
			g_apGame->m_bLoading = false;
#endif
		}
		
		if(!g_apGame->m_engine)
		{
			g_apGame->m_lastError = CEngine::E_INSUFFICIENT_MEMORY;
		}
		else
		{			
			g_apGame->m_lastError = g_apGame->m_engine->Initialize();
		}

		g_pGame->tttt();
		

		if(g_pTimer == NULL)
		{
			g_pTimer = GL_NEW MCTimer;
		}

		MC_knlDefTimer(g_pTimer, BrewMain_OnTimer);
		MC_knlSetTimer(g_pTimer, 13, g_apGame);

	}


	/* ���α׷��� ��� ���߾� ���� �� �Լ��� ȣ���� �ش�.*/
	void pauseClet( void )
	{
#ifdef USE_XPLAYER
		cXPlayerMenus *ptr = cXPlayerMenus::getInstance();
		if( ptr )
		{
			ptr->XPlayer_pause();
		}
#endif
	}

	/* ���α׷��� �簳�� �� �� �Լ��� ȣ���� �ش�. */
	void resumeClet( void )
	{
#ifdef USE_XPLAYER
		cXPlayerMenus *ptr = cXPlayerMenus::getInstance();
		if( ptr )
		{
			ptr->XPlayer_resume();
		}
#endif
	}


	/* ���α׷��� ����� �� �Ҹ���. */
	void destroyClet( void )
	{
#ifdef USE_XPLAYER
		cXPlayerMenus *ptr = cXPlayerMenus::getInstance();
		if ( ptr )
		{
			ptr->ReleaseNetRes();
		}
#endif
		MC_miscBackLight(0, MC_LIGHT_DEFAULT , 0xffffffff, 1000);	//For SKT rules
		//g_pGame->sendMessage(3/*MESSAGE_EXIT*/);

		//Robust, crash when push RED-KEY when state STATE_GAMELOFT
		//if( /*STATE_GAMELOFT*/3 != g_pGame->game_currentState )
		//fixed buu 1478708
		//if((g_pGame->m_map_kind == 4/*HOUSE_MYHOME*/ && g_pGame->game_currentState == 0) || g_pGame->game_currentState >= 22/*STATE_SPLASH*/)// Chen Shoutian, fixed bug 1442668. 
		//	///////////On the GAMELOFT LOGO screen, press END key, will refresh the data 
		//{
		//	//g_pGame->Save_Game(true);
		//	if(g_pGame)
		//	{
		//		g_pGame->Finalize();
		//	}
		//}



		if(g_apGame->m_engine)
		{
			g_apGame->m_engine->Finalize();
			delete g_apGame->m_engine;
			g_apGame->m_engine = NULL;
		}

		



		if(g_pTimer)
			SAFE_DEL(g_pTimer);
//		SAFE_DEL(g_pGame);
		SAFE_DEL(g_apGame);
		//FreeResources();
#ifdef  WIN32
		dump_memory();
#endif
		
	}




	/*ȭ���� �Ϻκ��� �ٽ� ĥ�ؾ� �ϴ� ��쿡 �Ҹ��� �Լ��̴�./ */
	void paintClet( int x, int y, int w, int h )
	{
	}
}
