#include "cGame.h"

#include "Defines.h"

#include "cENTITY.h"
#include "ASprite.h"
#include "../wipi/Small_Font.h"
//#include "cMiniGame.h"
#include "../common/Image.h"
#include "../common/Stream.h"
#include "../common/Graphics.h"

#include "cui.h"
//#include "../common/Engine.h"
#include "../common/Keypad.h"
#include "../common/ResourceManager.h"
//#include "../game/header/resources.h"

#include "ENTITY.h"
//#include "USER_House.h"
//#include "MINI_Puzzle.h"
//#include "MINI_Fishing.h"
//#include "MINI_Pasture.h"
//#include "USER_Map.h"

#include "UI_Menu.h"

#include "GAME.h"
#include "../common/Common.h"
#include "DEF.h"
#include "macro.h"
//#include "Module_Mascot.h"

//#include "Module_Inventory.h"
//#include "Module_MainUI.h"
//#include "Module_Quest.h"
#include "Module_Utility.h"

#include "ASpriteInstance.h"
//#include "Module_Bank.h"
#include "Module_SoftKey.h"
#include "Module_Date.h"
#include "../common/Vector1.h"
#include "../common/Engine.h"
#include "../wipi/Calendar.h"
#include "../common/KeyPad.h"


//GuanHao. IGP
#include "..\igp_wipi\wipiigp.h"

const byte cGame::s_clockPrecalc[] =
{	
	0, -1,	
	1,  0,	
	0,  1,	
	-1,  0, 
};

const static int COIN_1[] = {8000,20000,46000,100000,210000,450000};
const static int MONEY_1[] = {50,100,200,500,1000,2000};//Bank Charge

#define	GetSendEventNumParams(cmd)	(((cmd - CCMD_BASIC_OBJEVENT1) % 3) + 1)


//***************************************************************************
//** cGame()
//**
//** Constructor
//***************************************************************************

cGame* g_pGame;

//void cGame::RankingKeyCode()
//{
//	if( game_keyPressedSingle & GAME_KEY_SOFTKEY_LEFT )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_SOFTL);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_SOFTKEY_RIGHT )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_SOFTR);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_UP )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_UP);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_DOWN )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_DOWN);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_LEFT )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_LEFT);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_RIGHT )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_RIGHT);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_CLICK )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_FIRE);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_CLEAR )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_CLR);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_STAR )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_STAR);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_POUND )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_POUND);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_1 )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_NUM_1);
//	}
//	else if( game_keyPressedSingle & GAME_KEY_2 )
//	{
//		cXPlayerMenus::getInstance()->keyEvent(cXPlayerMenus::KEY_NUM_2);
//	}
//}


cGame::~cGame()
{
	SAFE_DEL(pAppMain);
	SUTIL_FreeInstance();
	

	Free_GameRes();


	SAFE_DEL_ARRAY(s_math_cosTable);
	SAFE_DEL_ARRAY(s_math_tanTable);
	SAFE_DEL(m_pStrArray);
//	SAFE_DEL_ARRAY(Weather_Posx);
//	SAFE_DEL_ARRAY(Weather_Posy);
//	SAFE_DEL_ARRAY(Weather_Direct);
//	SAFE_DEL_ARRAY(Weather_Speed);
//	SAFE_DEL_ARRAY(Weather_type);

//	SAFE_DEL(weather_sprite);


	if(m_sound)
	{
		for(int i=0; i<50; i++)
		{
			SAFE_DEL_ARRAY(m_sound->m_pData[i]);
		}
	}

	
	SAFE_DEL_ARRAY(m_tileBB);
	SAFE_DEL_ARRAY(s_cinematicsFrameTime);
#ifdef USE_DRAWRGB_FOR_TILES	
	for(int i=0; i<TILE_LAYER::k_id_cnt; i++)
	{
		SAFE_DEL(m_sprTileset[i])		
	}
	SAFE_DEL_ARRAY(m_sprTileset);

#else
	for(int i=0; i<TILE_LAYER::k_id_cnt; i++)
	{
		if(m_tileSet && m_tileSet[i])
		{
			delete[] m_tileSet[i];
			m_tileSet[i] = NULL;
		}
	}
	SAFE_DEL_ARRAY(m_tileSet);

	for(int i=0; i<100; i++)
	{
		SAFE_DEL(mapSprites[i]);
	}
	resetMapSprite();
#endif	
	
	SAFE_DEL_ARRAY(s_currentFramePos_sub_length);


	SAFE_DEL_ARRAY(cEntity::s_zones);
	SAFE_DEL_ARRAY_OBJ(m_entEntities, m_entEntities_length);
	SAFE_DEL(_actorDrawVector);

	//m_tileSet = GL_NEW CImage**[TILE_LAYER::k_id_cnt];
	//text_array = GL_NEW byte**[5];
	
	SAFE_DEL_ARRAY_ARRAY(m_tileMapLayer, TILE_LAYER::k_id_cnt);
	SAFE_DEL_ARRAY(m_tileMapLayer_sub_length);

	SAFE_DEL_ARRAY_ARRAY(m_tileFlipLayer, TILE_LAYER::k_id_cnt);
	SAFE_DEL_ARRAY(m_tileFlipLayer_sub_length);

	SAFE_DEL_ARRAY(record_buffData);
	SAFE_DEL_ARRAY(record_mapUserData);
	
	//SAFE_DEL_ARRAY_ARRAY(mapUser_Data,MAP_MAX_ENTITY);


	for(int i=0; i<text_array_length; i++)
	{
		SAFE_DEL_ARRAY_ARRAY( text_array[i], text_array_sub_length[i] );
	}
	SAFE_DEL_ARRAY_ARRAY(text_array, text_array_length);


//	SAFE_DEL(s_cUI);
//	SAFE_DEL(s_cMiniGame);

	SAFE_DEL(jFont);
	SAFE_DEL_ARRAY(s_data_offset);
	SAFE_DEL_ARRAY(s_data_sizes);
	SAFE_DEL_ARRAY(load_commonSpriteList);

	SAFE_DEL_ARRAY_OBJ(load_spriteArray, load_spriteArray_length);
	SAFE_DEL_ARRAY_OBJ(load_commonSpriteArray, load_commonSpriteArray_length);
	SAFE_DEL_ARRAY_OBJ(load_bgSpriteArray,load_bgSpriteArray_length);
	for(int i=0; i<m_bSprite_length; i++)
	{
		SAFE_DEL(m_bSprite[i]);
	}

//	SAFE_DEL(s_cUI);
	SAFE_DEL(s_data_is);
	
	SAFE_DEL_ARRAY(s_data_skipBuffer);
	SAFE_DEL_ARRAY(load_spriteList);
	SAFE_DEL(m_imgBB);

	SAFE_DEL_ARRAY(backbuffpix);
		

	for(int i=0; i<s_cinematics_length; i++)
	{
		SAFE_DEL_ARRAY_ARRAY(s_cinematics[i], s_cinematics_sub_length[i]);
	}
	SAFE_DEL_ARRAY(s_cinematics);
	SAFE_DEL_ARRAY(s_cinematics_sub_length);
	SAFE_DEL_ARRAY_ARRAY(s_cinematics_sub_sub_length,100);



	SAFE_DEL_ARRAY(s_cinematicsId);
	SAFE_DEL_ARRAY_ARRAY(s_currentFramePos,s_currentFramePos_length);
	SAFE_DEL_ARRAY_ARRAY(s_runningCinematicTrackActors, s_runningCinematicTrackActors_length);
	SAFE_DEL_ARRAY(s_runningCinematicTrackActors_sub_length);


	SAFE_DEL_ARRAY_ARRAY(m_tileFlipLayer, m_tileFlipLayer_length);
	SAFE_DEL_ARRAY(load_gmaeSpriteList);
	SAFE_DEL_ARRAY(m_mapCol);

	SAFE_DEL_ARRAY(m_mapUserCol);
	
	SAFE_DEL_ARRAY(load_gmaeList);

	//if(ts)
	//	ts->delModules = false;
	//SAFE_DEL(ts);
	
	//GuanHao. IGP. del
	//SAFE_DEL(m_pIgp);

	//for (int i = 0; i <5 ; ++i)
	//{
	//	for (int j = 0; j < 2 ; ++j)
	//	{	
	//		SAFE_DEL_ARRAY(q_string[i][j]);
	//
	//	}
	//}

	
	
	//SAFE_DEL_ARRAY_ARRAY(m_Item_Info, m_Item_Info_length);
	SAFE_DEL_ARRAY_ARRAY(gauge_color, gauge_color_length);

	SAFE_DEL_ARRAY(text_array_sub_length);

}

void cGame::gameInit()
{
	SUtil::GetInstance()->pGame = this;
	SUtil::GetInstance()->g = this->g;

	pAppMain = GL_NEW AppMain();

	//_use_alphabet_pad = false;
	m_pStrArray = GL_NEW cTempStrArray;

	game_appStatus = GAME_STATUS_RUNNING;

	//game_frameCounter = 0;

	game_currentState = STATE_LOAD;
	game_nextState = -1;
//	load_nextState = STATE_GAMELOFT;
	load_nextState = STATE_MAIN_MENU;//SangHo - 임시 셋팅

	game_bEnterNextState = true;
	game_bExitCurrentState = false;

	game_currentSubState = -1;

	//s_cEngine = NULL;
	//s_cUI = NULL;
	//s_cMiniGame = NULL;

	//		if(s_cEngine == NULL)
	s_cEngine = this;

//	m_keypad = s_cEngine->m_keypad;

	//		if(s_cUI == NULL)
//	s_cUI = GL_NEW cUI();


	//		if(s_cMiniGame == NULL)
//	s_cMiniGame = GL_NEW cMiniGame();

//	hero_mosX = 300*TILE_W/20;
//	hero_mosY = 295*TILE_W/20;

	//GuanHao. IGP
	//if( !g_pGame->m_pIgp )
	//{
	//	g_pGame->m_pIgp = GL_NEW CWipiIgp(g_pGame);
	//}


	//load_delay_from_game = false;
	//pushState(STATE_LOAD_COMMON, true);	  

	
	//MEMSET( _bAutomata, 0, sizeof( _bAutomata ) );

	//_bAutomata[0] = AEE_TM_ENGLISH_US;
	//_bAutomata[1] = AEE_TM_NUMBERS;
	//_bAutomata[2] = AEE_TM_HANGUL;
}


void cGame::OnSuspend()
{
//	keyReSet( );
	SOUND_STOP();//612

}

void cGame::OnResume()
{
//	keyReSet( );
}



#define GAME_SPEED				60;
void cGame::paint(CGraphics*  g)
{
			
        //M_Int64 temp = s_game_timeWhenFrameStart;

		m_runtime = m_speed/**GAME_SPEED*/;

		///// GET GAME TIME  //////////////////////

        s_game_timeWhenFrameStart = GETTIMEMS();//MC_knlCurrentTime();

		game_currentTime = s_game_timeWhenFrameStart;
      
        // calculate this frame DT
		s_game_frameDT = s_game_timeWhenFrameStart - s_game_frameDTTimer;
		if (s_game_frameDT < 0 || s_game_frameDTTimer == 0)
		{
		    s_game_frameDT = 1000 / 25;
		}
		s_game_frameDTTimer = s_game_timeWhenFrameStart;
			
		gamePaint(g);

}

void cGame::Update()
{
	
	// << Brew only
	bool bExit = false;

	if ( bExit ) 
	{
		Terminate();
	} 
	else 
	{
		paint(g);
	}

	GetDevice().FlushToSystemBuffer();	

#if PLATFORM==PLATFORM_BREW
	int maxYDevice = CDevice::GetScreenHeight() - 1;
	//IDISPLAY_SetColor(GetGameApp()->a.m_pIDisplay, CLR_USER_LINE, MAKE_RGB(0xFF,0xFF,0xFF));
	//while(maxYDevice >= kScreen::SCREEN_H)
	//	IDISPLAY_DrawHLine( GetGameApp()->a.m_pIDisplay, 0, maxYDevice--, kScreen::SCREEN_H);
#endif


#ifdef SUPPORT_KR_INPUT
	cXPlayerMenus *pMe = cXPlayerMenus::getInstance();

	if( pMe && pMe->GetInputState() )
	{
		if( (pMe->_bDrawBackPaint & REPAINT_ALL) != 0 )
		{
			pMe->_bDrawBackPaint &= ~REPAINT_ALL;

			GetDevice().UpdateToScreen();
		}

		if( (pMe->_bDrawBackPaint & REPAINT_UI) != 0 )
		{
			pMe->_bDrawBackPaint &= ~REPAINT_UI;

			//MC_GrpFrameBuffer      screenBuffer;
			//MC_GrpContext gc;

			//MC_grpInitContext(&gc);

			//screenBuffer = MC_grpGetScreenFrameBuffer(0);

			//if( pMe->getUiCom() )
			//{
			//	ITEXTCTL_Redraw(pMe->getUiCom());
			//}

			//MC_grpFlushLcd(0, screenBuffer, 0, 22, SCREEN_WIDTH, SCREEN_HEIGHT); 
		}
	}
	else
	{
		GetDevice().UpdateToScreen();
		
		//if( _cText )
		//{
		//	ITEXTCTL_Redraw(_cText);
		//}
	}
#else
	GetDevice().UpdateToScreen();
#endif

	CEngine::Update();
}



////***************************************************************************
////** processKeyPress()
////**
////** Process single and held key presses
////***************************************************************************
//void cGame::processKeyPress( int key )
//{
//	game_keyPressedSingle = key;
//
//	if( game_lastKeyPressed != -1 )
//	{
//		game_keyRepeatCount++;
//		if(game_keyRepeatCount > 0)
//		{
//			game_keyPressedHeld = game_lastKeyPressed;
//		}
//		else
//		{
//			game_keyPressedHeld = 0;
//		}
//	}
//	else
//	{
//		game_keyRepeatCount = 0;
//		game_keyPressedHeld = 0;
//	}
//
//	if(game_keyPressedSingle==GAME_KEY_SOFTKEY_LEFT)        	
//	{        		
//		// GloftTheFarm.s_game.keyReleased(GAME_KEY_SOFTKEY_LEFT);        		
//		// return;        	
//	}        
//
//	if(game_keyPressedSingle==GAME_KEY_SOFTKEY_RIGHT)        	
//	{   
//		//  GloftTheFarm.s_game.keyReleased(GAME_KEY_SOFTKEY_RIGHT);   
//		// return;      
//	}
//}
//
//
//
////***************************************************************************
////** keyPressed()
////** 
////** Called when a key is pressed
////***************************************************************************
//void cGame::keyPressed(int keyCode)
//{
//	//int key = getKeyMask(keyCode);
//	//game_keyPressed |= key;
//	//game_lastKeyPressed = key;
//
//	//<<612
//	int key = getKeyMask(keyCode);
//
//	//Robust, side key control
//	if(g_pGame->m_sound)
//	{
//		switch(key){
//			case GAME_KEY_VOL_UP:
//				g_pGame->setVolSideKey(1);
//				break;
//			case GAME_KEY_VOL_DOWN:
//				g_pGame->setVolSideKey(-1);
//				break;
//		}
//		
//	}
//
////	game_keyPressed |= key;
//	game_keyPressed = key;//  liu kun peng
//	game_lastKeyPressed = key;
//
//	game_keyPressedCount++;
//
//	game_netKeyPressed = keyCode;		
//
//	if ( (ABS(game_keyPressedCount-game_keyReleasedCount)) > -1 )
//	{
//		game_keyPressedCount = game_keyReleasedCount+1;
//	}
//	//612>>
//
//}
//
//
//
//void cGame::keyReSet( )
//{
//	game_lastKeyPressed = -1;
//	game_keyPressedCount = game_keyReleasedCount = 0;
//	game_netKeyPressed = 0;	
//}
//
////***************************************************************************
////** keyReleased()
////** 
////** Called when a key is released.
////***************************************************************************
//void cGame::keyReleased(int keyCode)
//{
//	int key = getKeyMask(keyCode);
//	
//	//GuanHao. key
//	//game_keyReleased |= key;
//	////game_lastKeyPressed = -1;
//	//game_keyReleasedCount++;
//
//	//if ( game_keyPressedCount == game_keyReleasedCount)
//	//{
//	//	game_lastKeyPressed = -1;
//	//	game_keyPressedCount = game_keyReleasedCount = 0;
//	//}
////	game_keyReleased |= key;
//	game_keyReleased = key;//liu kun peng
//	game_lastKeyPressed = -1;
//
//}
//
//
////***************************************************************************
////** keyReleased()
////** 
////** Called when a key is repeated.
////***************************************************************************
//void cGame::keyRepeated(int keyCode)
//{
//}
//
////***************************************************************************
////** getKeyMask()
////**
////** Translates the phone's key code into our coding scheme
////***************************************************************************
//
//int cGame::getKeyMask( int keyCode )
//{
//
//#define KEYCODE_NUM0	MH_KEY_0
//#define KEYCODE_NUM1	MH_KEY_1
//#define KEYCODE_NUM2	MH_KEY_2
//#define KEYCODE_NUM3	MH_KEY_3
//#define KEYCODE_NUM4	MH_KEY_4
//#define KEYCODE_NUM5	MH_KEY_5
//#define KEYCODE_NUM6	MH_KEY_6
//#define KEYCODE_NUM7	MH_KEY_7
//#define KEYCODE_NUM8	MH_KEY_8
//#define KEYCODE_NUM9	MH_KEY_9
//#define KEYCODE_STAR	MH_KEY_ASTERISK
//#define KEYCODE_POUND	MH_KEY_POUND
//#define KEYCODE_UP	MH_KEY_UP
//#define KEYCODE_DOWN	MH_KEY_DOWN
//#define KEYCODE_LEFT	MH_KEY_LEFT
//#define KEYCODE_RIGHT	MH_KEY_RIGHT
//#define KEYCODE_FIRE	MH_KEY_SELECT
//#define KEYCODE_SOFT_MENU_LEFT	MH_KEY_SOFT1
//#define KEYCODE_SOFT_MENU_RIGHT	MH_KEY_SOFT2
//#define KEYCODE_CLEAR	MH_KEY_CLEAR
///////////////////////////////////////////////
//#define KEYCODE_VOL_UP		MH_KEY_SIDE_UP
//#define KEYCODE_VOL_DOWN	MH_KEY_SIDE_DOWN
//
//
//	switch( keyCode )
//	{			
//#ifdef _KEY_EMU
//	case KEYCODE_NUM0:					return GAME_KEY_0;
//	case KEYCODE_NUM1:					return GAME_KEY_7;
//	case KEYCODE_NUM2:					return GAME_KEY_8;
//	case KEYCODE_NUM3:					return GAME_KEY_9;
//	case KEYCODE_NUM4:					return GAME_KEY_4;
//	case KEYCODE_NUM5:					return GAME_KEY_5;
//	case KEYCODE_NUM6:					return GAME_KEY_6;
//	case KEYCODE_NUM7:					return GAME_KEY_1;
//	case KEYCODE_NUM8:					return GAME_KEY_2;
//	case KEYCODE_NUM9:					return GAME_KEY_3;
//#else//_KEY_EMU
//	case KEYCODE_NUM0:					return GAME_KEY_0;
//	case KEYCODE_NUM1:					return GAME_KEY_1;
//	case KEYCODE_NUM2:					return GAME_KEY_2;
//	case KEYCODE_NUM3:					return GAME_KEY_3;
//	case KEYCODE_NUM4:					return GAME_KEY_4;
//	case KEYCODE_NUM5:					return GAME_KEY_5;
//	case KEYCODE_NUM6:					return GAME_KEY_6;
//	case KEYCODE_NUM7:					return GAME_KEY_7;
//	case KEYCODE_NUM8:					return GAME_KEY_8;
//	case KEYCODE_NUM9:					return GAME_KEY_9;
//#endif//_KEY_EMU
//
//#ifdef SUSPEND_DEBUG
//	case KEYCODE_STAR:					MC_grpPostEvent(MC_knlGetCurProgramID(), MV_FOREG_EVENT, 1, 0);return GAME_KEY_STAR;
//	case KEYCODE_POUND:					MC_grpPostEvent(MC_knlGetCurProgramID(), MV_BACKG_EVENT, 1, 0);return GAME_KEY_POUND;
//#else
//	case KEYCODE_STAR:					return GAME_KEY_STAR;
//	case KEYCODE_POUND:					return GAME_KEY_POUND;
//#endif
//
//	case KEYCODE_UP:					return GAME_KEY_UP;
//	case KEYCODE_DOWN:					return GAME_KEY_DOWN;
//	case KEYCODE_LEFT:					return GAME_KEY_LEFT;
//	case KEYCODE_RIGHT:					return GAME_KEY_RIGHT;
//
//	case KEYCODE_FIRE:					return GAME_KEY_CLICK;
//
//	case KEYCODE_SOFT_MENU_LEFT:		return GAME_KEY_SOFTKEY_LEFT;
//	case KEYCODE_SOFT_MENU_RIGHT:		return GAME_KEY_SOFTKEY_RIGHT;
//
//	case KEYCODE_CLEAR:					return GAME_KEY_CLEAR;
//
//	case KEYCODE_VOL_UP:				return GAME_KEY_VOL_UP;
//	case KEYCODE_VOL_DOWN:				return GAME_KEY_VOL_DOWN;
//
//	default:							return GAME_KEY_NULL;
//	}	
//			
//}

	// //////////////////////////////////////////////////////////////////////////
	// Key Process
	/*
	/**
	* Check if a game key is hold currently->
	* //-@@param gameKey int the game key to be checked
	* //-@@return bool the checked result
	*/
	bool cGame::IsKeyHold(int gameKey) 
	{
		int deviceKey = m_keypad->GetCurrentKey();
		if (s_keyHold != deviceKey)
		{
			s_keyHoldFrame = -1;
		}

		if (s_keyHold != 0)
		{
			s_keyHoldFrame++;
		}

		s_keyHold = deviceKey;

		return m_keypad->IsKeyHold(gameKey);//(_keyCurrent & gameKey) != 0;
	}


	bool cGame::IsKeyOnlyHold(int gameKey)
	{
		int deviceKey = m_keypad->GetCurrentKey();
		if (s_keyHold != deviceKey)
		{
			s_keyHoldFrame = -1;
		}

		if (s_keyHold != 0)
		{
			s_keyHoldFrame++;
		}

		s_keyHold = deviceKey;

		return m_keypad->IsKeyHold(gameKey) && (s_keyHold & ~gameKey) == 0;//(s_keyHold & gameKey) != 0 && (s_keyHold & ~gameKey) == 0;
	}
	/**
	* Check if a game key is pressed currently->
	* //-@@param gameKey int the game key to be checked
	* //-@@return bool the checked result
	*/
	bool cGame::IsKeyPressed(int gameKey)
	{
		bool b = m_keypad->IsKeyPressed(gameKey);
		return b;//(_keyPressed & gameKey) != 0;
	}

	/**
	* Check if a game key is released currently->
	* //-@@param gameKey int the game key to be checked
	* //-@@return bool the checked result
	*/
	bool cGame::IsKeyReleased(int gameKey) 
	{
		return m_keypad->IsKeyReleased(gameKey);//(_keyReleased & gameKey) != 0;
	}

	/**
	* Check if a game key is double pressed currently->
	* //-@@param gameKey int the game key to be checked
	* //-@@return bool the checked result
	*/
	bool cGame::IsKeyDoublePressed(int gameKey)
	{
		return m_keypad->IsKeyDoublePressed(gameKey);
		//	int deviceKey;
		//	for (int i = 0; i < DEVICE_KEY_COUNT; i++) {
		//		deviceKey = 1 << i;
		//		if ((deviceKey & gameKey) != 0 && IsKeyPressed(deviceKey)) {
		//			return _pressInterval[i] < DKey::DOUBLE_PRESS_INTERVAL;
		//		}
		//	}
		//	return false;
	}

	/**
	* Check if any key is hold currently->
	* //-@@return bool the checked result
	*/
	bool cGame::IsAnyKeyHold() 
	{
		return m_keypad->IsAnyKeyHold();//m_keypad->GetCurrentKey() != 0;
	}


	/**
	* Check if any key is pressed currently->
	* //-@@return bool the checked result
	*/
	bool cGame::IsAnyKeyPressed() 
	{
		return m_keypad->IsAnyKeyPressed();//_keyPressed != 0;
	}
	/**
	* Clear all stored keys-> It is used when resuming from interrupt->
	*/
	void cGame::ClearKey()
	{
		s_cEngine->m_keypad->ClearKey();

	//	m_keypad->ClearKey();

	//	s_cEngine->m_keypad->ClearKey();

	//	CEngine::m_keypad->ClearKey();


		//  s_keyCurrent 		= 0;
		//	s_keyHold 			= 0;
		//	s_keyPressed 		= 0;
		//	s_keyReleased 		= 0;
		//	s_keyPressedRT 		= 0;
		//	s_keyReleasedRT 	= 0;
		//	s_keyPressedInStore = 0;
	}

	// Key Process

//******************************************************************
//** Source Addition
//******************************************************************	

//GuanHao. global static veriable ? 
//static long aaaaaaaaaaa;
void cGame::gamePaint(CGraphics*  _g)
{

	g = _g;	
	pAppMain->Update();

	//	processKeyPress(game_keyPressed);
	//	game_keyReleased = 0;
	//	game_keyPressed = 0;

//	s_cUI->getKeyrelease();//SangHo - Key 이벤트 임시구현
//	s_cUI->getKeypress();//SangHo - Key 이벤트 임시구현


/*	
	if(game_bEnterNextState)
	{
		sendMessage(MESSAGE_INIT);
		game_bEnterNextState = false;
	}

	if(m_fadeOut > 11 || m_fadeOut < 1 )
	{
		if (game_currentState != STATE_NET)
		sendMessage(MESSAGE_UPDATE);
	}

	sendMessage(MESSAGE_PAINT);

	if(m_popCnt > 0)
	{
		//draw_MainPopup();
		m_popCnt ++;
		if(m_popCnt > 30)
		{
			m_popCnt = 0;
		}
	}

	drawFadeOut(g);

	if( game_bExitCurrentState )
	{
		sendMessage(MESSAGE_EXIT);

		game_bEnterNextState = true;
		game_bExitCurrentState = false;

		game_currentState = game_nextState;
		game_nextState = -1;
	}

*/
	game_counter++;
	if ( game_counter > 5000 )
	{
		game_counter = 0;
	}

	//Check_Hpstate();

#ifdef DBG_FPS
	drawFpsSpeed(g);
#endif

#ifdef DBG_HEAPTEST
	drawHeapMemory(g);
#endif

}



void cGame::pushState(int stateID, bool pushLoad )
{
	//System.out.println("stateID  "+stateID + ":::::pushLoad  "+pushLoad );

	if(pushLoad)
	{
#ifndef USE_DRAWRGB_FOR_TILES
		resetMapSprite();
#endif
		game_nextState = STATE_LOAD;
		load_nextState = stateID;
	}
	else
	{
		game_nextState = stateID;
	}	

	if(game_nextState == STATE_MENU_MAIN)
	{
		//SOUND_PLAY(INTRO_SOUND_01,true);
	}
	game_bExitCurrentState = true;

	//if ( stateID >= STATE_DRAW_MAP )
	//{
	//	Save_Game( true );
	//}
}

void cGame::sendMessage( int message )
{
	switch(game_currentState)
	{
		case STATE_MAIN_MENU:
			//s_cUI->process_Main_Test(message);
			break;
		case STATE_GAMELOFT :					//s_cUI->process_UI_GameWG(message);/*DBGPRINTF("STATE_GAMELOFT");*/	
			//s_cUI->process_UI_Test(message);/*DBGPRINTF("STATE_GAMELOFT");*/	
			break;//게임 테스트 구현	




//		case STATE_DRAW_MAP1:					s_cUI->process_USER_Map1(message);
//			break;//미니팜 구현부
//		case STATE_GAMEGRADE :					s_cUI->process_UI_GameGrade(message);/*DBGPRINTF("STATE_GAMEGRADE");*/	
//			break;
//		case STATE_SPLASH :						s_cUI->process_UI_Splash(message);/*DBGPRINTF("STATE_SPLASH");*/
//			break;
//	
//		case STATE_SELECTSOUND :				s_cUI->process_UI_SelectSound(message);/*DBGPRINTF("STATE_SELECTSOUND");*/
//			break;
//
//		case STATE_MENU_MAIN:					s_cUI->process_UI_Menu(message);/*DBGPRINTF("STATE_MENU_MAIN");*/		
//			break;	
//
//		case STATE_LOAD_COMMON:					process_State_Load_Common(message);	/*DBGPRINTF("STATE_LOAD_COMMON");*/	
//			break;
//
////		case STATE_NET :						s_cUI->process_UI_Net(message);/*	DBGPRINTF("STATE_NET");	*/		
////			break;
//
//		case STATE_DRAW_OPENNING:				s_cUI->process_USER_Openning(message);
//			break;
//
//		case STATE_DRAW_HOUSE:					s_cUI->process_USER_House(message);
//			break;
//
//
//		case STATE_DRAW_CHAPTER:				s_cUI->process_USER_Chapter(message);
//			break;


		case STATE_LOAD:						process_State_Load(message);/*DBGPRINTF("STATE_LOAD");*/			
			break;
			

		default: break;			
			
	}
	/*if (message == MESSAGE_PAINT && game_currentState > STATE_GAMELOFT)
	{
		g_pGame->g->SetClip(0, 0, SCREEN_WIDTH, OS_SCREEN_H);
		if (g_pGame->_use_alphabet_pad)
			softButtonAlphabe_Sprite->PaintFrame(g_pGame->g, 0, 100, SCREEN_HEIGHT, 0, 0, 0);
		else
		softButton_Sprite->PaintFrame(g_pGame->g, 0, 0, SCREEN_HEIGHT, 0, 0, 0);
	}*/
}

//***************************************************************************
//** loadResource()
//** 
//** 
//***************************************************************************
//
//byte* cGame::loadResource(int res, boolean close_file)//612
//{
//
//	return loadResourceStream(res, close_file);
//
//}



//***************************************************************************
//** loadResourceStream()
//** 
//** 
//***************************************************************************
//hoon 1122 add this method
//
//byte* cGame::loadResourceStream(int res, bool close_file) {//612
//	int category = resources_getPackageIndex(res);
//	int offset = resources_getResourceOffset(res);
//	int size = resources_getResourceSize(res);
//
//	if(game_currentResourceCategory != category)
//	{
//		if(game_resourceStream != NULL)
//		{
//			closeFileStream();
//		}
//		game_currentResourceCategory = category;
//	}
//
//	if(game_resourceStream == NULL)
//	{			
//		//game_resourceStream = GloftTheFarm.s_game.getClass().getResourceAsStream("/"+resources_getPackageFileName(res));
//		//game_resourceStream.mark(0);
//		char temp[128];
//		MEMSET(temp, 0, 128);
//		SPRINTF((char*)temp, "/%s", resources_getPackageFileName(res));	//hw#
//		SAFE_DEL(game_resourceStream);
//		game_resourceStream = GetResourceManager().GetResourceAsStream((char*)temp);
//
//		game_curResOff = 0;
//	}
//
//	int skip_value = offset - game_curResOff;
//
//	if(skip_value >= 0)
//	{
//		//			try
//		{				
//			game_resourceStream->Skip(skip_value);
//			byte* resData = GL_NEW byte[size];			
//			//game_resourceStream.read(resData, 0, size);
//			game_resourceStream->Read(resData,/* 0, */size);
//
//
//			if(close_file)
//			{
//				closeFileStream();
//			}
//			else
//			{
//				game_curResOff += (skip_value + size);
//			}
//
//			//game_resourceStream = NULL;
//			SAFE_DEL(game_resourceStream);
//
//			return resData;
//		}
//		//catch( Exception e )
//		//{      
//		//}
//	}
//
//	return NULL;
//}



//***************************************************************************
//** closeFileStream()
//** 
//** 
//***************************************************************************

void cGame::closeFileStream()
{
	//		try
	//		{
	game_resourceStream->Close();
	//		}
	//		catch( Exception e )
	//		{

	//		}

	SAFE_DEL(game_resourceStream);
	//game_resourceStream = NULL;
	game_curResOff = 0;
#ifdef DBG_HEAPTEST

	public static void drawHeapMemory(Graphics g)
	{
		g.setClip(0,0,150,13);	
		g->SetColor(0);
		g->FillRect(0, 0, 150, 13);
		g->SetColor(0xffffff);
		g.drawString( (Runtime.getRuntime().totalMemory()/1000) +","+( (Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory()) / 1000) + "," + (Runtime.getRuntime().freeMemory() / 1000), 0, 0, CGraphics::LEFT | CGraphics::TOP);
	}

#endif

}

#ifdef DBG_FPS

void cGame::_drawDebugStrings(
							  CGraphics* g, char* msg, int separator,
							  int x, int y, bool bScreenCoords,
							  int textColor, int bgcolor )
{
	/*
	//@#if DEBUG_MODE
	Font font = Font.getFont( Font.FACE_SYSTEM, Font.STYLE_PLAIN, Font.SIZE_SMALL );



	int[] from_pos = GL_NEW int[20];
	from_pos[0] = 0;
	int   count_strings = 0;
	int   max_width = 0;

	while ( count_strings < 20 - 1 )
	{
	int from = from_pos[ count_strings ];
	int to = msg.indexOf( separator, from );
	if ( to < 0 )
	to = msg.length();

	int w = font.substringWidth ( msg, from, to - from );
	if ( w > max_width )
	max_width = w;

	from_pos[ ++ count_strings ] = to + 1;
	if ( to >= msg.length() )
	break;
	}

	int width = max_width + 6;
	int line_height = font.getHeight();
	int height = line_height * count_strings;

	g->SetClip( x, y, width + 1, height + 1 );
	g->SetColor( bgcolor );
	g->FillRect( x, y, width, height );
	g->SetColor( 0 );
	g->DrawRect( x, y, width, height );

	g->SetColor ( textColor );
	g.setFont ( font );

	x += 3;
	for ( int str_id = 0; str_id < count_strings; ++ str_id )
	{
	int len = from_pos [ str_id + 1 ] - 1 - from_pos [ str_id ];
	if( len > 0 )
	{
	g.drawSubstring( msg, from_pos [ str_id ], len, x, y, 0 );
	}
	y += line_height;
	}
	//@#endif
	*/
}

void cGame::drawFpsSpeed(Graphics g)
{
	int fps_limit = 1000 / 66; //FRAME_INTERVAL
	int color;
	if ( fps_limit <= m_nGameFPS )
	{
		color = 0x008800;
	}
	else
	{
		color = 0xff0000;
	}   
	_drawDebugStrings( g, "fps: " + m_nGameFPS, '~', SCREEN_WIDTH - 80, 0, true, color, 0xffff00 );
}


#endif

void cGame::drawFadeOut(CGraphics* g)
{

	// softKey
	//DBG("m_fadeOut === " + m_fadeOut);
	if(m_fadeOut > 0 && m_fadeOut < 11)
	{
#ifdef KR_WIPI_VERSION
		g.setAlpha(25 * m_fadeOut );
		g->SetColor(0x000000);
		g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
		g.setAlpha(255);
#else
		g->SetColor(0x000000);
		for(int i = 0; i < 20/*12*/; i++)
		{
			g->FillRect(i*20*TILE_W/20 ,0,m_fadeOut*2 ,SCREEN_HEIGHT);	
		}
#endif

		m_fadeOut += (m_fadeIndex)?1:-1;		
	}
	else if(m_fadeOut == 11)
	{
		//setSleep(m_setsleep_index);
		m_fadeOut++;
		g->SetColor(0x000000);
		g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	}
}



#ifdef DBG_HEAPTEST

void cGame::drawHeapMemory(CGraphics* g)
{/*
 g->SetClip(0,0,150,13);	
 g->SetColor(0);
 g->FillRect(0, 0, 150, 13);
 g->SetColor(0xffffff);
 g.DrawString( (Runtime.getRuntime().totalMemory()/1000) +","+( (Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory()) / 1000) + "," + (Runtime.getRuntime().freeMemory() / 1000), 0, 0, CGraphics::LEFT | CGraphics::TOP);
 */}

#endif


void cGame::process_State_Load( int message )
{
	if( message == MESSAGE_INIT)
	{
		//dump_memory();
		load_reset();
		// Specify the data to load

		switch(load_nextState)
		{
		case STATE_MAIN_MENU:
			{
////				Text_loadTextPack( PACK_TEXT, TEXT_COMMON, TEXT_INDEX_COMMON );
				//	Text_loadTextPack( PACK_TEXT, TEXT_MAP, TEXT_INDEX_MAP );

				load_spriteListSize = 1;
				//load_spriteList = GL_NEW int[]
				//{										
				//	GAMELOFT_LOGO_GAMELOFT_RES_GLOBAL_INDEX, 0x01,										
				//};

				load_spriteList_length = load_spriteListSize*2;
				load_spriteList = GL_NEW int[load_spriteList_length];

				int temp[2]={
					//패키지 내에서 #define 넘버 번째 스프라이트 파일을 해당 배열에 로드한뒤 
					//실사용시엔 배열번호#define 으로쓴다   (GAMELOFT_SPRITE_LOGO)
//					SPRITE_MAIN_MENU, 0x01
				};

				MEMCPY(load_spriteList, temp, load_spriteList_length*sizeof(int));


				load_bShowProgressBar = false;
				load_gamefile = false;

				//Sound_Load();
				break;
			}
			break;
		case STATE_GAMELOFT:
			{
//				Text_loadTextPack( PACK_TEXT, TEXT_COMMON, TEXT_INDEX_COMMON );//
			//	Text_loadTextPack( PACK_TEXT, TEXT_MAP, TEXT_INDEX_MAP );

				load_spriteListSize = 9;
				//load_spriteList = GL_NEW int[]
				//{										
				//	GAMELOFT_LOGO_GAMELOFT_RES_GLOBAL_INDEX, 0x01,										
				//};

				load_spriteList_length = load_spriteListSize*2;
				load_spriteList = GL_NEW int[load_spriteList_length];
				
//				int temp[18]={
//					SPRITE_CAVE, 0x01,
//					SPRITE_SHADOW, 0x01,
//					SPRITE_WOMAN_BODY, 0x01,
//					SPRITE_WOMAN_S3, 0x01,
//					SPRITE_WOMAN_S6, 0x01,
//					SPRITE_WOMAN_G1, 0x01,
//					SPRITE_WOMAN_G3, 0x01,
//					SPRITE_WOMAN_O4, 0x01,
//					//SPRITE_MONSTER_SLIME, 0x01,
//							};
//
//				MEMCPY(load_spriteList, temp, load_spriteList_length*sizeof(int));


				load_bShowProgressBar = false;
				load_gamefile = false;

				//Sound_Load();
				break;
			}
//		case STATE_LOAD_COMMON:
//			{
//				load_commonSpriteListSize = 3;
//				
//
//				load_commonSpriteList_length = load_commonSpriteListSize*2;
//				load_commonSpriteList = GL_NEW int[load_commonSpriteList_length];
//				int temp[6]=
//				{
//					SPRITE_LOADING, 0x01,
//					SPRITE_SOFTKEY, 0x01,
//					SPRITE_NUMBER, 0x01,
//					//SPRITE_MAINUI, 0x01
//				};
//				MEMCPY(load_commonSpriteList, temp, load_commonSpriteList_length*sizeof(int));
//
//
//				load_bShowProgressBar = true;
//				load_gamefile = false;
//
//				break;
//			}
//
//		case STATE_MENU_MAIN:
//			{
//
//				load_spriteListSize = 0;
//				//load_spriteList = GL_NEW int[]
//				//{	
//				//	-1, 0x01,
//				//		MAINMENU_RES_MENU_RES_GLOBAL_INDEX, 0x01,									   										
//				//		WORLD_SPRITE_DUCKNDACK_GLOBAL_INDEX, 0x01,	
//				//		WORLD_SPRITE_BUTTERFLY_GLOBAL_INDEX, 0x01	
//				//};
//				load_spriteList_length = load_spriteListSize*2;
//				load_spriteList = GL_NEW int[load_spriteList_length];
//				
//				int temp[2]=
//				{
//					-1, 0x01,
////					MAINMENU_RES_MENU_RES_GLOBAL_INDEX, 0x01,									   										
////					WORLD_SPRITE_DUCKNDACK_GLOBAL_INDEX, 0x01,	
////					WORLD_SPRITE_BUTTERFLY_GLOBAL_INDEX, 0x01
//				};
//
//				MEMCPY(load_spriteList, temp, load_spriteList_length*sizeof(int));
//
//				load_bShowProgressBar = false;
//				load_gamefile = false;
//				break;
//
//			}

		//case STATE_DRAW_OPENNING:
		//	{

		//		load_spriteListSize = 2;
		//		load_spriteList_length = load_spriteListSize*2;
		//		load_spriteList = GL_NEW int[load_spriteList_length];
		//		int temp[4] = 
		//		{										
		//			SPRITE_EFFECT_ALPHA_2, 0x01,
		//			SPRITE_E_IMOTICON, 0x01,
		//		};

		//		MEMCPY(load_spriteList,temp, load_spriteList_length*sizeof(int));

		//		load_gamefile = true;
		//		load_gmaeList_length = 13;
		//		SAFE_DEL_ARRAY(load_gmaeList);
		//		load_gmaeList  = GL_NEW int[load_gmaeList_length ];

		//		int maptemp[13] = 
		//		{						
		//			MAP_OPENNING_LAYER0_RAW,
		//			MAP_OPENNING_LAYER0_FLIP,
		//			MAP_OPENNING_ACTORS,
		//			MAP_OPENNING_CINEMATICS,
		//			COLMAP_OPENNING,
		//			MAP_OPENNING_LAYER1_RAW,
		//			MAP_OPENNING_LAYER1_FLIP,
		//			MAP_OPENNING_LAYER2_RAW,
		//			MAP_OPENNING_LAYER2_FLIP,
		//			MAP_OPENNING_LAYER3_RAW,
		//			MAP_OPENNING_LAYER3_FLIP,
		//			MAP_OPENNING_LAYER4_RAW,
		//			MAP_OPENNING_LAYER4_FLIP
		//		};

		//		MEMCPY(load_gmaeList, maptemp, load_gmaeList_length*sizeof(int));
		//		load_gameTileList = PACK_OPENNING;

		//		load_bShowProgressBar = false;
		//		break;

		//	}
		//	
		//case STATE_DRAW_HOUSE:
		//	{
		//		load_spriteListSize = 1;
		//		load_spriteList_length = load_spriteListSize*2;
		//		load_spriteList = GL_NEW int[load_spriteList_length];
		//		int temp[2] = 
		//		{										
		//			SPRITE_EFFECT_ALPHA_2, 0x01
		//	//		HOUSE_OBJECT_RES_LETTER_FLOOR_GLOBAL_INDEX, 0x01,
		//	//		HOUSE_OBJECT_RES_STAR_EFFECT_GLOBAL_INDEX, 0x01
		//		};

		//		MEMCPY(load_spriteList,temp, load_spriteList_length*sizeof(int));

		//		load_gamefile = true;
		//		switch(m_map_kind)
		//		{

		//		case HOUSE_MYHOME:
		//			{
		//				load_gmaeList_length = 13;
		//				SAFE_DEL_ARRAY(load_gmaeList);
		//				load_gmaeList  = GL_NEW int[load_gmaeList_length ];
		//				int temp[13] = 
		//				{						
		//					MAP_HOME_LAYER0_RAW,
		//					MAP_HOME_LAYER0_FLIP,
		//					MAP_HOME_ACTORS,
		//					MAP_HOME_CINEMATICS,
		//					COLMAP_MYHOME,
		//					MAP_HOME_LAYER1_RAW,
		//					MAP_HOME_LAYER1_FLIP,
		//					MAP_HOME_LAYER2_RAW,
		//					MAP_HOME_LAYER2_FLIP,
		//					MAP_HOME_LAYER3_RAW,
		//					MAP_HOME_LAYER3_FLIP,
		//					MAP_HOME_LAYER4_RAW,
		//					MAP_HOME_LAYER4_FLIP
		//				};

		//				MEMCPY(load_gmaeList, temp, load_gmaeList_length*sizeof(int));
		//				load_gameTileList = PACK_MAPSPRITE;

		//				break;
		//			}
		//		}

		//		load_bShowProgressBar = false;

		//		break;
		//	}

		//case STATE_DRAW_MAP1:
		//	{
		//		load_spriteListSize = 3;
		//		load_spriteList_length = load_spriteListSize*2;
		//		load_spriteList = GL_NEW int[load_spriteList_length];
		//		int temp[6] = 
		//		{										
		//			SPRITE_EFFECT_ALPHA_2, 0x01,
		//			SPRITE_FISHING_EFF, 0x01,
		//			SPRITE_FONT_EFF, 0x01
		//	//		HOUSE_OBJECT_RES_LETTER_FLOOR_GLOBAL_INDEX, 0x01,
		//	//		HOUSE_OBJECT_RES_STAR_EFFECT_GLOBAL_INDEX, 0x01
		//		};

		//		MEMCPY(load_spriteList,temp, load_spriteList_length*sizeof(int));

		//		load_gamefile = true;
		//		switch(m_map_kind)
		//		{

		//		case WORLD_MAP1:
		//			{
		//				load_gmaeList_length = 13;
		//				SAFE_DEL_ARRAY(load_gmaeList);
		//				load_gmaeList  = GL_NEW int[load_gmaeList_length ];
		//				int temp[13] = 
		//				{						
		//					MAP_MAP1_LAYER0_RAW,
		//					MAP_MAP1_LAYER0_FLIP,
		//					MAP_MAP1_ACTORS,
		//					MAP_MAP1_CINEMATICS,
		//					COLMAP_MAP1,
		//					MAP_MAP1_LAYER1_RAW,
		//					MAP_MAP1_LAYER1_FLIP,
		//					MAP_MAP1_LAYER2_RAW,
		//					MAP_MAP1_LAYER2_FLIP,
		//					MAP_MAP1_LAYER3_RAW,
		//					MAP_MAP1_LAYER3_FLIP,
		//					MAP_MAP1_LAYER4_RAW,
		//					MAP_MAP1_LAYER4_FLIP
		//				};
		//				MEMCPY(load_gmaeList, temp, load_gmaeList_length*sizeof(int));
		//				load_gameTileList = PACK_MAP1;

		//				break;
		//			}
		//		}

		//		load_bShowProgressBar = true;

		//		break;
		//	}


		//case STATE_DRAW_CHAPTER:
		//	{
		//		load_spriteListSize = 1;
		//		load_spriteList_length = load_spriteListSize*2;
		//		load_spriteList = GL_NEW int[load_spriteList_length];
		//		int temp[6] = 
		//		{										
		//			SPRITE_BUILDING, 0x01,
		//	//		SPRITE_FISHING_EFF, 0x01,
		//	//		SPRITE_FONT_EFF, 0x01
		//	//		HOUSE_OBJECT_RES_LETTER_FLOOR_GLOBAL_INDEX, 0x01,
		//	//		HOUSE_OBJECT_RES_STAR_EFFECT_GLOBAL_INDEX, 0x01
		//		};

		//		MEMCPY(load_spriteList,temp, load_spriteList_length*sizeof(int));

		//		load_gamefile = true;
		//		switch(m_map_kind)
		//		{

		//		case CHAPTER_1:
		//			{
		//				load_gmaeList_length = 13;
		//				SAFE_DEL_ARRAY(load_gmaeList);
		//				load_gmaeList  = GL_NEW int[load_gmaeList_length ];
		//				int temp[13] = 
		//				{						
		//					 MAP_CHAPTER1_LAYER0_RAW ,
		//					 MAP_CHAPTER1_LAYER0_FLIP,
		//					 MAP_CHAPTER1_ACTORS,
		//					 MAP_CHAPTER1_CINEMATICS,
		//					 COLMAP_CHAPTER1,
		//					 MAP_CHAPTER1_LAYER1_RAW,
		//					 MAP_CHAPTER1_LAYER1_FLIP,
		//					 MAP_CHAPTER1_LAYER2_RAW,
		//					 MAP_CHAPTER1_LAYER2_FLIP,
		//					 MAP_CHAPTER1_LAYER3_RAW,
		//					 MAP_CHAPTER1_LAYER3_FLIP,
		//					 MAP_CHAPTER1_LAYER4_RAW,
		//					 MAP_CHAPTER1_LAYER4_FLIP
		//				};
		//				MEMCPY(load_gmaeList, temp, load_gmaeList_length*sizeof(int));
		//				load_gameTileList = PACK_CHAPTER1;

		//				break;
		//			}
		//		}
		//		load_bShowProgressBar = true;

		//		break;
		//	}

		}

		if(load_bShowProgressBar)
		{
			//Loading_Sprite->SetCurrentAnimation(ANIINDEX_LOADING_OBJECT,MINI_UI_RES_LOADING_ANI_INDEX , true);

			if ( load_bShowProgressBar )
			{

				//System.out.println("=111111111111111111111=");
				//game_counter = 0;
				//if( load_sprite != NULL)
				//{
				//	load_sprite->ClearCompressedImageData();
				//	load_sprite = NULL;
				//}
				//if( load_sprite == NULL)
				//{
				//	load_sprite = GL_NEW ASprite(loadResource(WORLD_SPRITE_DUCKNDACK_GLOBAL_INDEX, true), 0); //Load Sprite.
				//	load_sprite.enablePrecalcImage(1, false);
				//}
				//System.out.println("=222222222222222222222222=");
			}			
		}

		//if (  load_nextState > STATE_MENU_MAIN )
		//{
		//	/**/init_Popup( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, false, false);
		//}

		//if ( load_nextState >= STATE_DRAW_MAP-2 )
		//{
		//	m_Popup_str = GET_STRING(COMMON_MAINPOP_SAVE,TEXT_INDEX_COMMON);	
		//	g_pGame->load_commonSpriteArray[7]->SetCurrentAnimation(0,POPUP_RES_CHECK_ANI_INDEX, true);
		//}


	}
	else if( message == MESSAGE_UPDATE)
	{

		if (  load_nextState > STATE_MENU_MAIN )
		{
			/**/Process_Popup( );	
		}
		
		if(load_update())
		{
			pushState(load_nextState,false);			
		}

	}
	else if( message == MESSAGE_PAINT)
	{	
//		if (  load_nextState > STATE_MENU_MAIN )
//		{
//			/**/Draw_Popup( 0 );
//		}
		//softkey_init(SOFTKEY_SYMBOL_EMPTY, SOFTKEY_SYMBOL_EMPTY);
		load_paint(g);
	}
	else if( message == MESSAGE_EXIT)
	{
		//m_actorsData = NULL;

		//for ( int i = 0;  load_spriteArray  != NULL && i <  load_spriteArray_length; i++ )
		//{
		//	if ( load_spriteArray [i] != NULL)  load_spriteArray[i]->_modules_image = NULL;
		//}
		////load_spriteArray  = NULL ;
		//SAFE_DEL_ARRAY_OBJ(load_spriteArray, load_spriteArray_length);
		
		
		
		//load_spriteList  = NULL ;
		SAFE_DEL_ARRAY(load_spriteList);


		SAFE_DEL_ARRAY(m_actorsData);
		SAFE_DEL_ARRAY(m_cinematicData);


		if ( load_bShowProgressBar )
		{
			//	System.out.println("5555555555555555555555555=");
			//if( load_sprite != NULL)
			//{
			//	load_sprite->ClearCompressedImageData();
			//	load_sprite = NULL;
			//}
			//	System.out.println("666666666666666666666666666");
		}	

	}
}


void cGame::load_paint(CGraphics* g)
{
#ifdef SHOW_LOADING
	load_bShowProgressBar=true;
#endif

	if(load_bShowProgressBar)
	{
		int total_steps = load_totalSteps;

		if(total_steps <= 0)
		{
			total_steps = load_currentStep + 4;
		}

		//   int percent = load_currentStep * 100 / total_steps;
		//		drawProcessBar(g, percent > 100?100:percent);
		//if( load_nextState == STATE_LOAD_COMMON)
		//{
		//	drawProcessBarNoImage(g, load_currentStep , total_steps );
		//}
		//else
		//{
			
			if(load_commonSpriteArray[0])
			{
				if(load_currentStep == 1 || ( load_nextState == STATE_LOAD_COMMON && load_currentStep == 2) )
				{
//					load_commonSpriteArray[0]->SetCurrentAnimation(0,0, true);	
				}
				else if(load_currentStep > 0)
				{
//					load_commonSpriteArray[0]->PaintAndUpdateCurrentAnimation(g, 0, SCREEN_WIDTH-30, SCREEN_HEIGHT-30, 0, 0, 0);
				}
			}

			//drawProcessBar(g, load_currentStep , total_steps );
		//}
	}

}

void cGame::drawProcessBarNoImage(CGraphics* g, int _current, int _total)
{
	//int _percent = _current * 100 / _total;
	//int _posx = SCREEN_HALF_WIDTH;
	//int _posy = SCREEN_HALF_HEIGHT-50;


	g->SetColor(0xFFFFFF);
	g->FillRect(0, 0, SCREEN_WIDTH, OS_SCREEN_H);

	Draw_GaugeW( SCREEN_HALF_WIDTH-60 , SCREEN_HEIGHT-20 , 4 , _current , _total  , 120 , 0xff9236);

}



void cGame::drawProcessBar(CGraphics* g, int _current, int _total)
{

	int _percent = _current * 100 / _total;
	int _posx = SCREEN_HALF_WIDTH;
	int _posy = SCREEN_HALF_HEIGHT-50;

	g->SetClip(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	Draw_RectinPopup( 0 , SCREEN_HALF_HEIGHT-50 , SCREEN_WIDTH , 100 );



//	Draw_Number( number_Sprite, SCREEN_WIDTH-30 , SCREEN_HEIGHT-35  , _percent , NUMBER_RES_BEST_SMALL_MOD_INDEX ,DIRECT_RIGHT , 0);
//	number_Sprite->PaintModule( g, NUMBER_RES_BEST_SMALL_PERCENT_MOD_INDEX , SCREEN_WIDTH-26 , SCREEN_HEIGHT-35, 0) ; 
//	Draw_GaugeW( SCREEN_WIDTH-100 , SCREEN_HEIGHT-20 , 4 , _current , _total  , 80 , 0xff9236);


//	DRAW_KORSTR(g_pGame->g, GET_STRING(COMMON_TIP ,TEXT_INDEX_COMMON), _posx,_posy+10, CGraphics::TOP|CGraphics::HCENTER, 0x00ADAF);

	SPRITE_DRAW_PAGE(g, GET_STRING(load_Tip_str ,TEXT_INDEX_COMMON), _posx,_posy+50, SCREEN_WIDTH-40, 50, 0, CGraphics::TOP|CGraphics::HCENTER);	


	//if ( load_nextState >= STATE_DRAW_MAP-2 )
	//{
	//	//draw_MainPopup();
	//}
	//DRAW_KORSTR(g, GET_STRING(COMMON_MAINPOP_SAVE,TEXT_INDEX_COMMON), SCREEN_WIDTH - 10,SCREEN_HALF_HEIGHT + 60, Graphics.TOP|Graphics.RIGHT, 0x000000);

}

void cGame::load_reset()
{
	m_popCnt = 0;
	//if(load_nextState != STATE_MENU_MAIN)
	//{
	//	//SOUND_STOP();
	//}

	SPRITE_INIT_PAGE();
//	load_Tip_str = /**/random( COMMON_TIP1, COMMON_TIP14 );
	

	// Free previous state data 
	//for(int i = 0 ; i < load_spriteArray_length ; i++)  //todo
	//{
	//	if( load_spriteArray[i] != NULL){

	//		load_spriteArray[i]->ClearCompressedImageData();			
	//		SAFE_DEL(load_spriteArray[i]);
	//	}
	//}

	//for ( int i = 0;  load_spriteArray  != NULL && i <  load_spriteArray_length; i++ )
	//{
	//	if ( load_spriteArray [i] != NULL)  load_spriteArray[i]->_modules_image = NULL;
	//}

	SAFE_DEL_ARRAY_OBJ(load_spriteArray,load_spriteArray_length);


	SAFE_DEL_ARRAY(load_spriteList);

	// Do garbage collection
	
	load_spriteArray_length = 0;
	// Reset variables

	load_currentStep = 0;
	load_commonSpriteListSize = 0;
	load_bgSpriteListSize = 0;
	load_spriteListSize = 0;
	//load_commonDataListSize = 0;
	//load_dataListSize = 0;


	load_gamefile = false;

	//load_gmaeList = NULL;
	//load_gmaeSpriteList = NULL;
	//load_gameTileList = NULL;

	SAFE_DEL_ARRAY(load_gmaeList);
	SAFE_DEL_ARRAY(load_gmaeSpriteList)
//	SAFE_DEL_ARRAY(load_gameTileList);    ///seongjin---081031 no memory_del because MEMID
//	SAFE_DEL_ARRAY(load_gmaeSpriteList);
//	SAFE_DEL_ARRAY(load_gameTileList);

	load_bShowProgressBar = true;

}


void cGame::process_State_Load_Common( int message )
{
	if( message == MESSAGE_INIT)
	{
		//ADD Seong 2007.8.22
//		Math_init(PACK_MATH, MATH_COS, MATH_TAN, -1);

		////ADD Seong 2007.12.07
//		Data_init(PACK_ARRAY);
//		Data_open(ARRAY_INTARRAY);

		///*cGame.*/SaveLoadRecord( false );
			
		//m_Item_Info = (int**) Mem_ReadArray();
		//m_Item_Info_length = Mem_ReadArray_rtn_length;
		//m_DogChangeBoy = BOY_ORDER;

		//Data_open(DATABASE_GAUGE_COLOR);	
		//gauge_color = (int**) Mem_ReadArray();
		//gauge_color_length = Mem_ReadArray_rtn_length;

		Data_free();

		//reset_Inven_Item();
		//Set_Quest_str0();


//#ifdef KR_WIPI_VERSION
//		pushState( STATE_SELECTSOUND, false );
//#else // USE_MIDP10
//
//
////#ifdef EVALUATION
////		g_pGame->m_sndVol = 2;
////		pushState( STATE_SPLASH, false);
////#else
////		pushState( STATE_SELECTSOUND, false );
////#endif
//
//#ifdef LGT_VERSION
//		pushState( STATE_SPLASH, false );		
//#else
		//pushState( STATE_SELECTSOUND, false );

	//	pushState( STATE_SPLASH, false );

	//	goto_map( STATE_DRAW_CHAPTER );
		goto_map( STATE_DRAW_MAP1 );

		

//#endif // LGT_VERSION
//
//
//#endif
		setClock(7,0);


	}
	else if( message == MESSAGE_PAINT)
	{
		
	}
	else if(message == MESSAGE_EXIT)
	{

	}
}




//void cGame::Set_Quest_str0( )
//{
//	//char* _chrstr = NULL;	
//	//char* _strtmp0 = NULL;
//	//char* _strtmp1 = NULL;	
//
//	/*cGame.*/Text_freeText(3);	
//	/*cGame.*/Text_loadTextPack (PACK_TEXT, TEXT_QUEST, 3);	
//
//	SAFE_DEL_ARRAY(q_string[0][0]);
//	SAFE_DEL_ARRAY(q_string[0][1]);
//	char* tempStr = GET_STRING(QUEST_QUEST_00 ,3);
//	q_string[0][0] = GL_NEW char[(StrLen(tempStr)+1)];
//	SPRINTF( q_string[0][0], "%s", tempStr );
//
//	tempStr = GET_STRING(QUEST_QUEST_01 ,3);
//	q_string[0][1] = GL_NEW char[(StrLen(tempStr)+1)];
//	SPRINTF( q_string[0][1], "%s", tempStr );
//
//	/*cGame.*/Text_freeText(3);	
//}


void cGame::Text_loadTextPack (char* filename, int index , int text_index) //todo
{
	Text_freeText(text_index);
	Data_init(filename);
	Data_open(index);

	// get nb of string in text pack
	int nb_str 		= Data_readS32();
	//int offset[] 	= GL_NEW int[nb_str+1];
	int* offset = GL_NEW int [nb_str+1];

	// read text array offsets
	for (int i = 1; i < nb_str+1; i++)
	{
		offset[i] = Data_readS32();
	}


	//text_array[text_index] = GL_NEW byte[nb_str][];
	SAFE_DEL_ARRAY_ARRAY(text_array[text_index], text_array_sub_length[text_index] );
	SAFE_DEL_ARRAY_ARRAY(text_array[text_index], text_array_sub_length[text_index]);
	text_array[text_index] = GL_NEW byte*[nb_str];
	text_array_sub_length[text_index] = nb_str;
#if STREAM_READ_TEXT
	//text_array1 = GL_NEW String[nb_str];
	//DataInputStream dis = NULL;
	//InputStream     in  = NULL;
	//for (int i = 0; i < nb_str; i++)
	//{
	//	int size = offset[i+1] - offset[i];
	//	text_array[i] = GL_NEW byte[size];
	//	Data_read(text_array[i]);
	//	tmp[0] = (byte) (text_array[i].length >> 8);
	//	tmp[1] = (byte) (text_array[i].length);
	//	System.arraycopy(text_array[i], 0, tmp, 2, text_array[i].length);
	//	in = GL_NEW ByteArrayInputStream( tmp);
	//	dis = GL_NEW DataInputStream(in);
	//	text_array1[i] = dis.readUTF();
	//}

	text_array1 = char*[nb_str];
	CStream* dis = NULL;
	CStream*     in  = NULL;
	for (int i = 0; i < nb_str; i++)
	{
		int size = offset[i+1] - offset[i];
		text_array[i] = GL_NEW byte[size+1];
		Data_read(text_array[i]);
		tmp[0] = (byte) (text_array[i].length >> 8);
		tmp[1] = (byte) (text_array[i].length);
		System.arraycopy(text_array[i], 0, tmp, 2, text_array[i].length);
		in = GL_NEW ByteArrayInputStream( tmp);
		dis = GL_NEW DataInputStream(in);
		text_array1[i] = dis.readUTF();
	}

	text_array = NULL;

#else
	for (int i = 0; i < nb_str; i++)
	{
		//int size = offset[i+1] - offset[i];
		//text_array[text_index][i] = GL_NEW byte[size];
		//Data_read(text_array[text_index][i], size);
		int size = offset[i+1] - offset[i];
		text_array[text_index][i] = GL_NEW byte[size+1];
		MEMSET((char*)text_array[text_index][i], 0, size+1);
		Data_read(text_array[text_index][i], size);

	}
#endif//STREAM_READ_TEXT
	Data_free();
	SAFE_DEL_ARRAY(offset);

}

char* cGame::Text_getString (int index,int text_index)// //todo
{
	//	try
	{
#if STREAM_READ_TEXT
		return text_array1[index];
#else	
		//return GL_NEW String(text_array[text_index][index])
		if(index>=text_array_sub_length[text_index])
		{
			mascot_s_sceneState |= MASCOT_SENCE_STATE_END;
			return	NULL;
		}else
			return (char*)text_array[text_index][index];	
#endif//STREAM_READ	TEXT
	}
	//	catch (Exception e)
	//	{
	//	}

	return NULL;

}

void cGame::Text_freeText (int text_index)  //todo
{

#if STREAM_READ_TEXT
	if (text_array1 != NULL)
	{
		for (int i = 0; i < text_array1.length; i++)
		{
			text_array1[i] = NULL;
		}
		text_array1 = NULL;
		DO_GC();
	}
}
#else
	if (text_array[text_index] != NULL)
	{
	//	//for (int i = 0; i < text_array[text_index].length; i++)
	//	for (int i = 0; i < text_array_length; i++)
	//	{
	//		text_array[text_index][i] = NULL;
	//	}
	//	text_array[text_index] = NULL;
	//	DO_GC();
		//for(int i=0; i<text_array_sub_length[text_index]; i++)
		//{
		//	SAFE_DEL_ARRAY(text_array[text_index][i]);
		//}
		//text_array[text_index] = NULL;
		SAFE_DEL_ARRAY_ARRAY(text_array[text_index],text_array_sub_length[text_index])
	}
}
#endif //STREAM_READ_TEXT

void cGame::SetSubString(int i1, int i2)
{
	_index1 = i1;
	_index2 = i2;
}




void cGame::InitPage(char* s, int width)
{
	int len = StrLen(s);


	int * off = s_drawPageOffset;

	char* str = s;
	int lineIndex = 1;
	
	//int lastToken;
	int lastToken = 0;

	off[0] = 0;
	char tempStr[1000];

	// Wrap text in multiple lines depending on the value of width and height
	for(int i=0; i<len; i++)
	{

		if (str[i] == '|' )
		{
			MEMSET(tempStr, 0, 1000);
			MEMCPY(tempStr, (str + off[lineIndex-1]), (i - off[lineIndex-1]));
			if(jFont->getKStrWidth(tempStr) > width)
			{
				if (off[lineIndex - 1] != lastToken)
				{
					off[lineIndex++] = lastToken;
				}
				off[lineIndex++] = i+1;				
				lastToken = i+1;
			}
			else
			{
				off[lineIndex++] = i+1;
				lastToken = i+1;
			}
		}
		else
		{
			if (str[i] == ' ' || i == len-1)
			{
				MEMSET(tempStr, 0, 1000);
				MEMCPY(tempStr, (str + off[lineIndex-1]), (i - off[lineIndex-1]));

				if(jFont->getKStrWidth(tempStr) > width)
				{
					off[lineIndex++] = lastToken;
						
					if (i == len -1)
					{
						off[lineIndex] = len+1;
						s_drawPage_nLine = lineIndex;
						break;
					}					
					i= lastToken-1;
				}
				else
				{
					lastToken = i+1;
				}
			}
		}
		if(len-1 == i)
		{
			off[lineIndex] = len+1;
			s_drawPage_nLine = lineIndex;
		}
	}
}

int cGame::DrawPage_Bold(CGraphics* g, char* s, int x, int y, int width, int height, int scroll, int anchor, bool auto_scroll)
{
	if (!s_isDrawPageInit)
	{
		s_isDrawPageInit = true;
		InitPage(s, width);
	}


	int scroll_delay;
	if (auto_scroll)
		scroll_delay = 30;
	else
		scroll_delay = 0;


	int x_left =0 ;
	int y_top = 0 ;

	if((anchor & CGraphics::LEFT) != 0)
	{
		x_left = x;			
	}
	else if((anchor & CGraphics::RIGHT) != 0)
	{
		x_left = x + width;			
	}
	else if((anchor & CGraphics::HCENTER) != 0)
	{
		x_left = x - (width >> 1);
	}

	y_top = y - (height >> 1);

	int lines = s_drawPage_nLine;
	//int[] off = s_drawPageOffset;
	int* off = s_drawPageOffset;

	int th = 0;

	// Save previous clip values and set GL_NEW clip
	g->SetClip(x_left-3, y_top-1, width+5, height+2);//612

	// Get line distances
	// 20070214 Joobong Kim		Make fit line spacing for korean
	th = _line_spacing + jFont->stringHeight()/*(_modules_h[0] & 0xFF)*/;	

	// calculate y offset

	int total_height = th * lines - _line_spacing;

	if(total_height >= height)
	{
		y -= height >> 1;
	}
	else
	{
		y -= total_height >> 1;
	}

	// Apply scrolling to the y coordinate

	if ( auto_scroll )
	{
		if(total_height >= height)
		{
			if (scroll >= total_height - height + scroll_delay)
				y -= total_height - height;
			else if (scroll >= scroll_delay)
				y -= scroll-scroll_delay;
		}
	}
	else 
	{
		y -= scroll;
	}


	// Draw the text lines

	//for (int j=0; j<lines + 1; j++)
	//{
	//	_index1 = (j > 0) ? off[j - 1] + 1 : 0;
	//	_index2 = off[j];

	//	if(y >= y_top - th && y < y_top + height)
	//	{
	//		char tempStr[400];
	//		MEMSET( (char*)tempStr, 0, 400 );
	//		MEMCPY( (void*)tempStr, s+_index1, _index2-_index1 );
	//		jFont->DrawString(g, tempStr, x, y, anchor, true);
	//		jFont->DrawString(g, tempStr, x+1, y, anchor, true);
	//		/*SAFE_DEL_ARRAY( tempStr );*/

	//		//jFont->DrawString(g, s->substring(_index1, _index2), x, y, anchor, true);
	//		//jFont->DrawString(g, s->substring(_index1, _index2), x+1, y, anchor, true);
	//	}
	//	y += th;
	//}

	
	for (int j=0; j<lines; j++)
	{
		_index1 = off[j];
		_index2 = off[j+1]-1;

		if(y >= y_top - th && y < y_top + height)
		{
			//	jFont.setOutline(false);
			//    jFont.setOutlineColor(0x000000);//_pal[_crt_pal][1]);
			//jFont->SetColor(0xffffff);
			char* tempStr = GL_NEW char[ _index2-_index1 + 1];
			MEMSET( (char*)tempStr, 0, (_index2-_index1 + 1) );
			MEMCPY( (void*)tempStr, (void*)(s+_index1), _index2-_index1 );
			//jFont->DrawString(g, tempStr, x, y, anchor, true);//0xffffff);//_pal[_crt_pal][0]/*FONT_PAL[_crt_pal][0]*/);
			//jFont->DrawString(g, tempStr, x+1, y, anchor, true);
			SAFE_DEL_ARRAY(tempStr);

			//jFont->DrawString(g, s->substring(_index1, _index2), x, y, anchor, true);//0xffffff);//_pal[_crt_pal][0]/*FONT_PAL[_crt_pal][0]*/);	
			//	g.DrawString(s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//				DrawString(g, s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//            	DrawPage(g, s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//////DBG("text :::: "+s.substring(_index1, _index2)  );
		}

		y += th;
	}

	// Reset substring feature

	_index1 = -1;
	_index2 = -1;

	// Restore clip to old value
	g->SetClip(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT);
	// Return number pixel left in the scroll
	if (!auto_scroll)
	{
		return (total_height - (scroll+28) );
	}

	if (total_height >= height +4 && scroll >= scroll_delay)//need scroll
	{
		return (total_height - height - scroll + (scroll_delay<<1));
	}
	else
	{
		return (total_height - height);
	}

}


int cGame::DrawPage( CGraphics* g, char* s, int x, int y, int width, int height, int scroll, int anchor, bool auto_scroll )
{

	if (!s_isDrawPageInit)
	{
		s_isDrawPageInit = true;
		InitPage(s, width);
	}


	int scroll_delay;
	if (auto_scroll)
		scroll_delay = 30;
	else
		scroll_delay = 0;


	int x_left =0 ;
	int y_top = 0 ;
	y_top = y;

	if((anchor & CGraphics::LEFT) != 0)
	{
		x_left = x;			
	}
	else if((anchor & CGraphics::RIGHT) != 0)
	{
		x_left = x + width;			
	}
	else if((anchor & CGraphics::HCENTER) != 0)
	{
		x_left = x - (width >> 1);
	}
	
	if((anchor & CGraphics::VCENTER) != 0)
	{
		y_top = y - (height >> 1);
	}

	int lines = s_drawPage_nLine;
	//int[] off = s_drawPageOffset;
	int* off = s_drawPageOffset;

	int th = 0;


	// Save previous clip values and set GL_NEW clip
	g->SetClip(0, y_top-1, SCREEN_WIDTH, height+2);


	// Get line distances
	// 20070214 Joobong Kim		Make fit line spacing for korean
	th = _line_spacing + jFont->stringHeight()/*(_modules_h[0] & 0xFF)*/;	

	// calculate y offset

	int total_height = th * lines - _line_spacing;


	if((anchor & CGraphics::VCENTER) != 0)
	{
		if(total_height >= height)
		{
			y -= height >> 1;
		}
		else
		{
			y -= total_height >> 1;
		}
		anchor &= ~CGraphics::VCENTER;		
	}

	// Apply scrolling to the y coordinate
	if ( auto_scroll )
	{
		if(total_height >= height)
		{
			if (scroll >= total_height - height + scroll_delay)
				y -= total_height - height;
			else if (scroll >= scroll_delay)
				y -= scroll-scroll_delay;
		}
	}
	else 
	{
		y -= scroll;
	}


	// Draw the text lines
	for (int j=0; j<lines; j++)
	{
		_index1 = off[j];
		_index2 = off[j+1]-1;

		if(y >= y_top - th && y < y_top + height)
		{
			//	jFont.setOutline(false);
			//    jFont.setOutlineColor(0x000000);//_pal[_crt_pal][1]);
			//jFont->SetColor(0xffffff);

			char* tempStr = GL_NEW char[ _index2-_index1 + 1];
			MEMSET( (char*)tempStr, 0, (_index2-_index1 + 1) );

			MEMCPY( (void*)tempStr, (void*)(s+_index1), _index2-_index1 );

			//jFont->DrawString(g, tempStr, x, y, anchor, true);//0xffffff);//_pal[_crt_pal][0]/*FONT_PAL[_crt_pal][0]*/);
			SAFE_DEL_ARRAY(tempStr);

			//jFont->DrawString(g, s->substring(_index1, _index2), x, y, anchor, true);//0xffffff);//_pal[_crt_pal][0]/*FONT_PAL[_crt_pal][0]*/);	
			//	g.DrawString(s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//				DrawString(g, s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//            	DrawPage(g, s, x, y, CGraphics::HCENTER | CGraphics::TOP);
			//////DBG("text :::: "+s.substring(_index1, _index2)  );
		}

		y += th;
	}

	// Reset substring feature

	_index1 = -1;
	_index2 = -1;

	// Restore clip to old value

	g->SetClip(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT);

	// Return number pixel left in the scroll

	if (!auto_scroll)
	{
		return (total_height - (scroll+MASCOT_CHMASCOT_PAGEY) );
	}

	if (total_height >= height +4 && scroll >= scroll_delay)//need scroll
	{
		return (total_height - height - scroll + (scroll_delay<<1));
	}
	else
	{
		return (total_height - height);
	}
}


//static StringBuffer strbuff = GL_NEW	StringBuffer();
char* cGame::stringChange(char* strIndex , int strAdd, char** strRtn) //todo
{		
//	char* rtnStr = new char[1000];
	char* rtnStr = *strRtn;//m_pStrArray->getStr();
	//int cIndex = strIndex.indexOf("YYY")	;
	int cIndex = STRSTR(strIndex, "YYY")-strIndex;
	if(cIndex<0)
	{
		SPRINTF((char*)rtnStr, strIndex);
	}
	else
	{
		char str1[600];
		char str2[600];
		MEMCPY((char*)str1, strIndex,cIndex );
		str1[cIndex] = 0;
		SPRINTF((char*)str2, "%s", &strIndex[cIndex+3] );

		SPRINTF(rtnStr,
			"%s%d%s",
			str1,
			strAdd,
			str2);

	}
	return rtnStr;
}

//sec.
char* cGame::stringChange(char* strIndex , char* strAdd, char** strRtn)
{		
	//char* rtnStr = new char[1000];
	char* rtnStr = *strRtn;
	//int cIndex = strIndex.indexOf("YYY")	;
 	char* temp = STRSTR(strIndex, "YYY");
	int cIndex = temp - strIndex;
	if(cIndex<0)
	{
		SPRINTF((char*)rtnStr, strIndex);
	}
	else
	{
		char str1[2000];
		//char str2[600];
		MEMCPY((char*)str1, strIndex,cIndex );
		str1[cIndex] = 0;
		//SPRINTF((char*)str2, "%s", &strIndex[cIndex+3] );

		SPRINTF(rtnStr,
			"%s%s%s",
			str1,
			strAdd,
			(strIndex + cIndex + 3));


	}
	return rtnStr;
}




char** cGame::String_phase(char* str)  //todo
{

//DBGPRINTF("String_phase  : str = %s",str);

#define TEMP_LENGTH	200

	char* tempStr;
	tempStr = GL_NEW char[TEMP_LENGTH];
	MEMSET((char*)tempStr, '\0', TEMP_LENGTH);

	int charCnt=0;
	int arrayCnt = 0;	
	char** _str = GL_NEW char*[4];
	MEMSET(	_str, 0 , 4*sizeof(_str[0]) );

	for (int i = 0; i < StrLen(str); i++)
	{
		if( i == StrLen(str) - 1) 
		{
			tempStr[StrLen(tempStr)] = str[i];

			TRIM(tempStr);
			_str[arrayCnt++] = tempStr;
			break;
		}

		if ( str[i] == '|' )
		{
			charCnt = 0;
			TRIM(tempStr);
			_str[arrayCnt++] = tempStr;
			tempStr = GL_NEW char[TEMP_LENGTH];
			MEMSET((char*)tempStr, '\0', TEMP_LENGTH);
		} 
		else
		{
			if(str[i] == ' ' && charCnt == 0) 
			{
				continue;
			}			
			tempStr[charCnt] = str[i];
			charCnt++;
		}
	}

	mascot_s_sceneState = 0;
	mascot_currentImage = -1;
	mascot_currentState = MASCOT_STATE_HIDDEN;

	MEMSET(mascot_currentImageName, 0, 100);

	emotion_m_type[EMOTION_TYPEA] = -1;

//DBGPRINTF("String_phase  : str[0] = %s",_str[0]);
//DBGPRINTF("String_phase  : str[1] = %s",_str[1]);
//DBGPRINTF("String_phase  : str[2] = %s",_str[2]);

	//if( _str[0] != NULL ) // TYPE VIEW 
	//{
	//	if ( !STRCMP(_str[0],"00") )
	//	{
	//		mascot_currentState = MASCOT_STATE_SHOW_CHMASCOT;
	//		mascot_currentImage_Sprite = m_bSprite[GAMESPRITE_E_IMOTICON];
	//	}
	//	else if ( !STRCMP(_str[0],"11") )
	//	{
	//		mascot_currentState = MASCOT_STATE_SHOW_MASCOT;
	//	}
	//	else if ( !STRCMP(_str[0],"12") )
	//	{
	//		mascot_currentState = MASCOT_STATE_SHOW_POPUP;
	//	}
	//}


	//if( _str[1] != NULL )	// CHARATER CONFIRM
	//{
	//	if ( mascot_currentState == MASCOT_STATE_SHOW_CHMASCOT )
	//	{
	//		if(!STRCMP(_str[1],"00"))
	//		{
	//			mascot_currentImage = GAMESPRITE_MAIN_CHAR;
	//		}
	//		else if(!STRCMP(_str[1],"01"))
	//		{
	//			mascot_currentImage = GAMESPRITE_CHICK;
	//		}
	//	}
	//}

	if(_str[2] != NULL && !STRCMP(_str[2],"99") )
	{
		mascot_s_sceneState |= MASCOT_SENCE_STATE_END;
	}

	SAFE_DEL_ARRAY_ARRAY(_str, 4);
	return _str;
}





char** cGame::String_phase_Quest(char* str)  //todo
{
	char* tempStr = GL_NEW char[1000];
	MEMSET( (char*)tempStr, '\0', 1000 );
	int charCnt=0;
	int arrayCnt = 0;
	//String _str[] = GL_NEW String[10];
	char** _str=GL_NEW char*[10];
	for (int i = 0; i < StrLen(str)/*str.length()*/; i++) 
	{
		if( i == StrLen(str)/*str.length() */- 1) {
			//_str[arrayCnt++] = (tempStr+str.charAt(i)).trim();
			tempStr[StrLen(tempStr)] = str[i];
			TRIM(tempStr);
			_str[arrayCnt++] = tempStr;
			break;
		}

		//if (str.charAt(i) == '|')
		if ( str[i] == '|')
		{
			charCnt = 0;
			//_str[arrayCnt++] = tempStr.trim();
			TRIM(tempStr);
			_str[arrayCnt++] = tempStr;
			tempStr = GL_NEW char[1000];
			MEMSET((char*)tempStr, '\0', 1000);
		} else {
			//if(str.charAt(i) == ' ' && charCnt == 0) {
			if(str[i] == ' ' && charCnt == 0) {
				continue;
			}
			//tempStr += str.charAt(i);
			tempStr[charCnt] = str[i];
			charCnt++;
		}
	}

	return _str;
}



void cGame::Set_Emotion(int _slot , int _chr , int _index)
{
	//emotion_m_type[_slot] = (byte)_chr;
	//load_commonSpriteArray[4]->SetCurrentAnimation(_slot,_index, true);
	//<<612
	if(_slot == EMOTION_TYPEQ)
	{
		int q_temp = get_Quest_EntityToNpc(_chr);
		if(q_temp > -1){
			emotion_m_type[ q_temp + 5 ] = (byte)(_chr);	

//			load_commonSpriteArray[4]->SetCurrentAnimation( q_temp + 5,_index, true);
		}
	}
	else
	{
		emotion_m_type[_slot] = (byte)_chr;
//		load_commonSpriteArray[4]->SetCurrentAnimation(_slot,_index, true);
	}
	
}



#ifdef USE_MAP_EMOTION
	void cGame::Set_Emotion_Pos(int _slot , int _posX , int _posY , int _index)
	{

		load_commonSpriteArray[4]->SetCurrentAnimation(_slot,_index, true);

	}
#endif



void cGame::Set_FreeEmotion(int _slot, int _chr)
{
	/*emotion_m_type[_slot] = -1;*/
	if(_slot == EMOTION_TYPEQ)
	{
		if(_chr == -1)
		{
			for(int i = 5 ; i < emotion_m_type_length ; i++ )
			{
				emotion_m_type[i] = -1;
			}
		}
		else
		{
			int q_temp = get_Quest_EntityToNpc(_chr);
			if(q_temp > -1)
				emotion_m_type[ q_temp + 5 ] = -1;
		}
	}
	else
	{
		emotion_m_type[_slot] = -1;
	}

}

void cGame::Set_ALLFreeEmotion()
{

	for(int i = 0 ; i<emotion_m_type_length ; i++ )
	{
		emotion_m_type[i] = -1;
	}
}


char cGame::Get_Emotion(int _slot, int _chr)
{
	/*return emotion_m_type[_slot];*/
	//<<612
	char temp = (byte)-1;
	if(_slot == EMOTION_TYPEQ)
	{
		int q_temp = get_Quest_EntityToNpc(_chr);
		if(q_temp > -1 && q_temp < 7)
			temp = emotion_m_type[ q_temp + 5 ];
	}
	else
	{
		temp = emotion_m_type[_slot];
	}
	return temp;
	//612>>

}

int cGame::Get_Emotion_Ani(int _slot, int _chr)
{
	/*return load_commonSpriteArray[4]->GetCurrentAnimation(_slot);*/
	//<<612
	int temp = -1;
	if(_slot == EMOTION_TYPEQ)
	{
		int q_temp = get_Quest_EntityToNpc(_chr);
//		if(q_temp > -1 && q_temp < 7)
//			temp = load_commonSpriteArray[4]->GetCurrentAnimation( q_temp + 5 );
	}
	else
	{
//		temp = load_commonSpriteArray[4]->GetCurrentAnimation(_slot);
	}
	return temp;
	//612>>
}


//================================================================
/// SET TALK DATA
//================================================================

void cGame::Set_talk(int _param, int _slot)
{

	char* _str = NULL;
	char* _strhead = NULL;
	//String _strtmp = NULL;

	talk_cnt = _param;

	_strhead = GET_STRING((_param-1),_slot);
	//DBG("_strhead == "+_strhead );
	String_phase( _strhead );		

	_str = GET_STRING(_param ,_slot);
//	char* strTemp = m_pStrArray->getStr();

	//DBG("str  == " + _str);
	if((mascot_s_sceneState & MASCOT_SENCE_STATE_POPUP) != 0)
	{
		popup_show(0, _str);
	}
	else
	{
		mascot_show(0, _str);
	}	

//	m_pStrArray->releaseStr(strTemp);
}



bool cGame::Data_init (char* filename)
{
	// if we are opening an already opened data file, return imediately
	if ((s_data_filename != NULL) && (STRCMP(filename, s_data_filename) == 0) && s_data_is != NULL)
	{			
		return true;
	}

	// if a data file was previously opened, close it
	if (s_data_is != NULL)
	{
		s_data_is->Close();
	}

	// open data file
	s_data_filename 	= filename;
	
	SAFE_DEL(s_data_is);
	s_data_is = GetResourceManager().GetResourceAsStream(s_data_filename);

	if (s_data_is == NULL)
	{
		return false;
	}

	s_data_curOffset 	= 0;

	s_data_nbData = Data_readS32();
	s_data_start  = 4;

	///@note the array s_data_offset and s_data_sizes are re-allocated
	/// each time we open a GL_NEW data file. an optimisation could be to allocate
	/// those to the biggest value possible for the data pack, and never reallocate
	/// them after
	SAFE_DEL_ARRAY(s_data_offset);
	SAFE_DEL_ARRAY(s_data_sizes);
	s_data_offset = GL_NEW int[s_data_nbData+1];
	s_data_sizes = GL_NEW int[s_data_nbData];

	// get offset to each data inside pack, and data size
	s_data_offset[0] = 0;
	for (int i = 0; i < s_data_nbData; i++)
	{
		s_data_offset[i+1] = Data_readS32();
		s_data_start += 4;
		s_data_sizes[i]	= s_data_offset[i+1] - s_data_offset[i] - 1;
	}

	return true;
}

//--------------------------------------------------------------------------
/// @brief open a data file to a given data index
///
/// @param index index in the data to seek in the data file
/// @throw Exception if an error occured
//--------------------------------------------------------------------------
void cGame::Data_open (int index)
{
	int offsetToData = (s_data_offset[index] + s_data_start);

	// if the current offset is already at the correct position -> return imediately
	if (s_data_curOffset == offsetToData)
	{		
		// get data type
		s_data_lastDataOpenType = Data_read();
		return;
	}

	// if the current offset is past the destination offset
	if (s_data_curOffset > offsetToData)
	{
		// reset the current offset
		if (s_data_is != NULL)
		{
			s_data_is->Close();			
		}

		SAFE_DEL(s_data_is);

		s_data_is = GetResourceManager().GetResourceAsStream(s_data_filename);
		
		if (s_data_is == NULL)
		{
			//System.out.println("================== 2222 NULL NULL NULL ");
		}

		s_data_curOffset = 0;
	}
	// current offset is before the destination offset
	else
	{
		// calculate the nb of byte to skip
		offsetToData -= s_data_curOffset;
	}

	// skip directly to the correct offset
	Data_skip(offsetToData);

	// get data type
	s_data_lastDataOpenType = Data_read();
}

//--------------------------------------------------------------------------
/// @brief skip in data file (move current offset in data file)
///
/// @param nb nb of byte to skip in data file
/// @throw Exception if error occured
//--------------------------------------------------------------------------
void cGame::Data_skip (int nb)
{
	// if no skipbuffer should be use, use the regular java.io.InputStream.skip() function
	if (k_data_skipbufferSize == 0)
	{	
		s_data_is->Skip(nb);		
		s_data_curOffset += nb;
	}
	// if skipbuffer should be use, skip using java.io.InputStream.read()
	else
	{
		// allocate skip buffer the first time
		if (s_data_skipBuffer == NULL)
		{
			s_data_skipBuffer = GL_NEW byte[k_data_skipbufferSize];
		}

		//skip multiple of k_data_skipbufferSize bytes
		while (nb > k_data_skipbufferSize)
		{
			Data_readFully(s_data_skipBuffer, 0, k_data_skipbufferSize);
			nb -= k_data_skipbufferSize;
		}

		// skip remaining bytes
		if (nb > 0)
		{
			Data_readFully(s_data_skipBuffer, 0, nb);
		}
	}
}

//--------------------------------------------------------------------------
/// @brief close a data file
//--------------------------------------------------------------------------
void cGame::Data_close ()
{
	// well ... nothing to do
}

//--------------------------------------------------------------------------
/// @brief close the data input stream and free it.
//--------------------------------------------------------------------------
void cGame::Data_free ()
{
	if (s_data_filename != NULL)
	{
		if (s_data_is != NULL)
		{
			
			s_data_is->Close();
			//s_data_is = NULL;
			//SAFE_DEL(s_data_is);
			
		}

		//s_data_offset = NULL;
		//s_data_sizes = NULL;
		SAFE_DEL_ARRAY(s_data_offset);
		SAFE_DEL_ARRAY(s_data_sizes);
		//Add seongjin
		SAFE_DEL_ARRAY(s_data_skipBuffer);

		//TRACE_MEM("after " + s_data_filename + " pack close");

		s_data_curOffset 	= -1;
		s_data_filename = NULL;
		//DI_GC();
	}
}

//--------------------------------------------------------------------------
/// @brief read a single byte in the data file
///
/// @return one byte as a int, or -1 if EOF
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_read ()
{
	int read = 0;

	char temp = 0;	
	read = s_data_is->Read( (void*)(&temp) ,1);	

	if (read >= 0)	// we read something
	{
		s_data_curOffset++;
	}
	return (int)temp/*read*/;
}

//--------------------------------------------------------------------------
/// @brief read in array
///
/// @param array -> array to store data read, array must be initialized
/// @return nb of byte read, should be array.length, or less, or exception
/// @throw Exception if error occured
/// @note modified to used Data_readFully instead
//--------------------------------------------------------------------------
int cGame::Data_read (byte* _array, int length)
{	
	return Data_readFully(_array, length);
}

//--------------------------------------------------------------------------
/// @brief read in array
///
/// @param array array to store data read, array must be initialized
/// @param off offset to store byte in array
/// @param len nb of byte to read
/// @return nb of byte read, should be len, or less, or exception
/// @throw Exception if error occured
/// @note modified to used Data_readFully instead
//--------------------------------------------------------------------------
int cGame::Data_read (byte* _array, int off, int len)
{	
	return Data_readFully(_array, off, len);
}


//--------------------------------------------------------------------------
/// @brief read in array
///
/// @param array -> array to store data read, array must be initialized
/// @return nb of byte read, must be array.length or exception
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readFully(byte* _array, int length)
{
	return Data_readFully(_array, 0, length);
}

//--------------------------------------------------------------------------
/// @brief read in array
///
/// @param array array to store data read, array must be initialized
/// @param off offset to store byte in array
/// @param len nb of byte to read
/// @return nb of byte read, must be len or exception
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readFully(byte* _array,int offset,int length)
{
	int off = offset;
	int len = length;
	int read = 0;
	
	while (len > 0)
	{ 
		read = s_data_is->Read(_array/*, off*/, len);//Robust removed
		len -= read;
		off += read;
	}

	s_data_curOffset += length;
	return length;
}


//--------------------------------------------------------------------------
/// @brief read all the data inside a datafile at a given index
///
/// @param index index of data to read
/// @return return a ptr to buffer containing all the data read
/// @throw Exception if error occured
/// @note if index is invalid it return NULL, not an exception
//--------------------------------------------------------------------------
byte* cGame::Data_readAll (int index)
{
	if (index < 0 || index >= s_data_nbData)
	{		
		return NULL;
	}
	
	byte* buffer = NULL;

	Data_open(index);

	buffer = GL_NEW byte[s_data_sizes[index]];
	Data_readAll_rtn_length = s_data_sizes[index];

	Data_readFully(buffer, s_data_sizes[index]);

	return buffer;
}

//--------------------------------------------------------------------------
/// @brief read one byte from the currently open Data file
///
/// @return return byte value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readU8 ()
{
	return (Data_read() & 0xFF);
}

//--------------------------------------------------------------------------
/// @brief read one unsigned short from the currently open Data file
///
/// @return return unsigned short value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readU16 ()
{
	return Data_readU16LittleEndian();
}

//--------------------------------------------------------------------------
/// @brief read one unsigned short from the currently open Data file (LittleEndian Format)
///
/// @return return unsigned short value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readU16LittleEndian ()
{
	return ((Data_read() & 0xFF) | ((Data_read() & 0xFF) << 8));
}

//--------------------------------------------------------------------------
/// @brief read one unsigned short from the currently open Data file (BigEndian Format)
///
/// @return return unsigned short value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readU16BigEndian ()
{
	return ( ((Data_read() & 0xFF) << 8) | (Data_read() & 0xFF) );
}

//--------------------------------------------------------------------------
/// @brief read one long from the currently open Data file (BigEndian Format)
///
/// @return return long value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readS32 ()
{
	return Data_readS32LittleEndian();
}

//--------------------------------------------------------------------------
/// @brief read one long from the currently open Data file (LittleEndian Format)
///
/// @return return long value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readS32LittleEndian ()
{
	return (((Data_read() & 0xFF) | ((Data_read() & 0xFF) << 8)) | (((Data_read() & 0xFF) << 16) | ((Data_read() & 0xFF) << 24)));
}

//--------------------------------------------------------------------------
/// @brief read one long from the currently open Data file (BigEndian Format)
///
/// @return return long value as an int
/// @throw Exception if error occured
//--------------------------------------------------------------------------
int cGame::Data_readS32BigEndian ()
{
	return (((Data_read() & 0xFF) << 24) | ((Data_read() & 0xFF) << 16) | ((Data_read() & 0xFF) << 8) | ((Data_read() & 0xFF)));
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// LOAD ARRAY LOAD ARRAY LOAD ARRAY LOAD ARRAY LOAD ARRAY LOAD ARRAY
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//final private static int ARRAY_BYTE 	= 0;
//final private static int ARRAY_SHORT 	= 1;
//final private static int ARRAY_INT 		= 2;

int** cGame::Mem_ReadArray( )
{
	int** _array = NULL;		

	int ID = Data_read( );
	int nbComponent;
	int dataPadding = ID >> 4;

	int type = ID & 0x7;

	if ((ID & 0x8) != 0)
	{
		nbComponent = Data_readU16( );
	}
	else
	{
		nbComponent = Data_read( );
	}

	switch (type)
	{
	case ARRAY_BYTE:
		break;
		//{
		//	byte* array2 = new byte[nbComponent];
		//	for (int i=0; i<nbComponent; i++)
		//	{
		//		array2[i] = (byte) Data_read( );
		//	}
		//	_array = (Object) array2;
		//	break;
		//}
	case ARRAY_SHORT:
		break;
		//{
		//	short* array2 = new short[nbComponent];
		//	if (dataPadding == ARRAY_BYTE)
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (byte) Data_read( );
		//		}
		//	else
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (short) Data_readU16( );
		//		}
		//		_array = (Object) array2;
		//		break;
		//}
	case ARRAY_INT:
		break;
		//{
		//	int* array2 = new int[nbComponent];
		//	if (dataPadding == ARRAY_BYTE)
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (byte)Data_read( );
		//		}
		//	else if (dataPadding == ARRAY_SHORT)
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (short)Data_readU16( );
		//		}
		//	else
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = Data_readS32( );
		//		}
		//		_array = (Object) array2;
		//		break;
		//}

	default: 
		{
			int** genArray;
			//byte** arrayB;
			//short** arrayS;
			int** arrayI;
			//byte** arrayB2;
			//short** arrayS2;
			int** arrayI2;

			type &= 0x3;
			switch(type)
			{
			case ARRAY_BYTE:
				break;
				//{
				//	if (dataPadding == 2)
				//	{
				//		arrayB = new byte[nbComponent][];
				//		genArray = (Object[]) arrayB;
				//	}
				//	else
				//	{
				//		arrayB2 = new byte[nbComponent][][];
				//		genArray = (Object[]) arrayB2;
				//	}
				//}
				//break;
			case ARRAY_SHORT:
				break;
				//{
				//	if (dataPadding == 2)
				//	{
				//		arrayS = new short[nbComponent][];
				//		genArray = (Object[]) arrayS;
				//	}
				//	else
				//	{
				//		arrayS2 = new short[nbComponent][][];
				//		genArray = (Object[]) arrayS2;
				//	}
				//}
				//break;
			default:
				{
					if (dataPadding == 2)
					{
						arrayI = GL_NEW int*[nbComponent];
						genArray = arrayI;
					}
					else
					{
						arrayI2 = GL_NEW int*[nbComponent];
						genArray = arrayI2;
					}
				}
				break;
			}

			for (int i=0; i<nbComponent; i++)
			{
				genArray[i] = Mem_ReadArray2( );
			}
			_array = genArray;
			Mem_ReadArray_rtn_length = nbComponent;
			break;
		}
	}

	return _array;
}

int* cGame::Mem_ReadArray2( )
{
	int* _array = NULL;		

	int ID = Data_read( );
	int nbComponent;
	int dataPadding = ID >> 4;

	int type = ID & 0x7;

	if ((ID & 0x8) != 0)
	{
		nbComponent = Data_readU16( );
	}
	else
	{
		nbComponent = Data_read( );
	}

	switch (type)
	{
	case ARRAY_BYTE: 
		//{
		//	byte* array2 = new byte[nbComponent];
		//	for (int i=0; i<nbComponent; i++)
		//	{
		//		array2[i] = (byte) Data_read( );
		//	}
		//	_array = (Object) array2;
		//	break;
		//}
	case ARRAY_SHORT: 
		//{
		//	short* array2 = new short[nbComponent];
		//	if (dataPadding == ARRAY_BYTE)
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (byte) Data_read( );
		//		}
		//	else
		//		for (int i=0; i<nbComponent; i++)
		//		{
		//			array2[i] = (short) Data_readU16( );
		//		}
		//		_array = (Object) array2;
		//		break;
		//}
	case ARRAY_INT: 
		{
			int* array2 = GL_NEW int[nbComponent];
			if (dataPadding == ARRAY_BYTE)
				for (int i=0; i<nbComponent; i++)
				{
					array2[i] = Data_read( );
				}
			else if (dataPadding == ARRAY_SHORT)
				for (int i=0; i<nbComponent; i++)
				{
					array2[i] = Data_readU16( );
				}
			else
				for (int i=0; i<nbComponent; i++)
				{
					array2[i] = Data_readS32( );
				}
				_array = array2;
				break;
		}

	default: 
		{
			//int** genArray;
			//byte** arrayB;
			//short** arrayS;
			//int** arrayI;
			//byte** arrayB2;
			//short** arrayS2;
			//int** arrayI2;

			//type &= 0x3;
			//switch(type)
			//{
			//case ARRAY_BYTE:
			//	//{
			//	//	if (dataPadding == 2)
			//	//	{
			//	//		arrayB = new byte[nbComponent][];
			//	//		genArray = (Object[]) arrayB;
			//	//	}
			//	//	else
			//	//	{
			//	//		arrayB2 = new byte[nbComponent][][];
			//	//		genArray = (Object[]) arrayB2;
			//	//	}
			//	//}
			//	//break;
			//case ARRAY_SHORT:
			//	//{
			//	//	if (dataPadding == 2)
			//	//	{
			//	//		arrayS = new short[nbComponent][];
			//	//		genArray = (Object[]) arrayS;
			//	//	}
			//	//	else
			//	//	{
			//	//		arrayS2 = new short[nbComponent][][];
			//	//		genArray = (Object[]) arrayS2;
			//	//	}
			//	//}
			//	//break;
			//default:
			//	{
			//		if (dataPadding == 2)
			//		{
			//			arrayI = new int*[nbComponent];
			//			genArray = arrayI;
			//		}
			//		else
			//		{
			//			arrayI2 = new int*[nbComponent];
			//			genArray = arrayI2;
			//		}
			//	}
			//	break;
			//}

			//for (int i=0; i<nbComponent; i++)
			//{
			//	genArray[i] = Mem_ReadArray2( );
			//}
			//_array = genArray;
			//break;
		}
	}

	//return _array;
	return _array;
}
//{
//	int* arrayTemp = NULL;		
//
//	int ID = Data_read( );
//	int nbComponent;
//	int dataPadding = ID >> 4;
//
//	int type = ID & 0x7;
//
//	if ((ID & 0x8) != 0)
//	{
//		nbComponent = Data_readU16( );
//	}
//	else
//	{
//		nbComponent = Data_read( );
//	}
//
//	switch (type)
//	{
//	case ARRAY_BYTE: 
//		{
//			//byte* array2 = GL_NEW byte[nbComponent];
//			int* array2 = GL_NEW int[nbComponent];
//			for (int i=0; i<nbComponent; i++)
//			{
//				array2[i] = (int) Data_read( );
//			}
//			//arrayTemp = (Object) array2;
//			arrayTemp = array2;
//			break;
//		}
//	case ARRAY_SHORT: 
//		{
//			//short[] array2 = GL_NEW short[nbComponent];
//			int* array2 = GL_NEW int[nbComponent];
//			if (dataPadding == ARRAY_BYTE)
//				for (int i=0; i<nbComponent; i++)
//				{
//					array2[i] = (int) Data_read( );
//				}
//			else
//				for (int i=0; i<nbComponent; i++)
//				{
//					array2[i] = (int) Data_readU16( );
//				}
//				//arrayTemp = (Object) array2;
//				arrayTemp = array2;
//				break;
//		}
//	case ARRAY_INT: 
//		{
//			int* array2 = GL_NEW int[nbComponent];
//			if (dataPadding == ARRAY_BYTE)
//				for (int i=0; i<nbComponent; i++)
//				{
//					array2[i] = (int)Data_read( );
//				}
//			else if (dataPadding == ARRAY_SHORT)
//				for (int i=0; i<nbComponent; i++)
//				{
//					array2[i] = (int)Data_readU16( );
//				}
//			else
//				for (int i=0; i<nbComponent; i++)
//				{
//					array2[i] = Data_readS32( );
//				}
//				arrayTemp = /*(Object) */array2;
//				break;
//		}
//
//	default:   //todo
//		{
//			int** genArray; //Robust
//			//byte[][] arrayB;
//			//short[][] arrayS;
//			//int[][] arrayI;
//			//byte[][][] arrayB2;
//			//short[][][] arrayS2;
//			//int[][][] arrayI2;
//
//
//			int** arrayB;
//			int** arrayS;
//			int** arrayI;
//			int*** arrayB2;
//			int*** arrayS2;
//			int*** arrayI2;
//
//
//			type &= 0x3;
//			switch(type)
//			{
//			case ARRAY_BYTE:
//				{
//					if (dataPadding == 2)
//					{
//						//arrayB = GL_NEW byte[nbComponent][];
//						//genArray = (Object[]) arrayB;
//						arrayB = GL_NEW int*[nbComponent];
//						genArray = arrayB;
//					}
//					else
//					{
//						//arrayB2 = GL_NEW byte[nbComponent][][];
//						//genArray = (Object[]) arrayB2;
//						arrayB2 = GL_NEW int**[nbComponent];
//						genArray = arrayB2;
//					}
//				}
//				break;
//			case ARRAY_SHORT:
//				{
//					if (dataPadding == 2)
//					{
//						//arrayS = GL_NEW short[nbComponent][];
//						//genArray = (Object[]) arrayS;
//						arrayS = GL_NEW int*[nbComponent];
//						genArray = arrayS;
//					}
//					else
//					{
//						//arrayS2 = GL_NEW short[nbComponent][][];
//						//genArray = (Object[]) arrayS2;
//						arrayS2 = GL_NEW int**[nbComponent];
//						genArray = arrayS2;
//					}
//				}
//				break;
//			default:
//				{
//					if (dataPadding == 2)
//					{
//						//arrayI = GL_NEW int[nbComponent][];
//						//genArray = (Object[]) arrayI;
//						arrayI = GL_NEW int*[nbComponent];
//						genArray = arrayI;
//					}
//					else
//					{
//						//arrayI2 = GL_NEW int[nbComponent][][];
//						//genArray = (Object[]) arrayI2;
//						arrayI2 = GL_NEW int**[nbComponent];
//						genArray = arrayI2;
//					}
//				}
//				break;
//			}
//
//			for (int i=0; i<nbComponent; i++)
//			{
//				genArray[i] = Mem_ReadArray( );
//			}
//			arrayTemp = genArray;
//			break;
//		}
//	}
//
//	return arrayTemp;
//}



//void cGame::Process_Popup( )
//{
//	if ( bpopup_move )
//	{
//		if( game_counter%2 == 0)
//		{
//			if ( popup_MoveDirectX == DIRECT_LEFT )
//			{
//				popup_MoveposX--;
//			}
//			else if ( popup_MoveDirectX == DIRECT_RIGHT )
//			{
//				popup_MoveposX++;
//			}

//			if ( popup_MoveDirectY == DIRECT_UP )
//			{
//				popup_MoveposY--;
//			}
//			else if ( popup_MoveDirectY == DIRECT_DOWN )
//			{
//				popup_MoveposY++;
//			}
//		}
//	}

//	if ( popup_MoveposX <= -popup_imgsizeX )
//	{
//		popup_MoveposX +=popup_imgsizeX;
//	}
//	else if ( popup_MoveposX >= popup_imgsizeX )
//	{
//		popup_MoveposX -=popup_imgsizeX;
//	}

//	if ( popup_MoveposY <= -popup_imgsizeY )
//	{
//		popup_MoveposY +=popup_imgsizeY;
//	}
//	else if ( popup_MoveposY >= popup_imgsizeY )
//	{
//		popup_MoveposY -=popup_imgsizeY;
//	}

//}


//================================================================

/// DRAW FUNCTION

//================================================================


/*void cGame::Draw_Popup( int _plussize )
{

int _countx = ((popup_sizeX+_plussize)/popup_imgsizeX)+2;
int _county = (popup_sizeY/popup_imgsizeY)+2;
int _posx = popup_DrawposX+popup_MoveposX;
int _posy = popup_DrawposY+popup_MoveposY;

g->SetClip( popup_DrawposX, popup_DrawposY, (popup_sizeX+_plussize), popup_sizeY );

for ( int _x = -1 ;  _x < _countx ; _x++)
{
for ( int _y = -1 ;  _y < _county ; _y++)
{
popup_Sprite->PaintModule( g, POPUP_RES_PATTERN_MOD_INDEX , _posx + (_x*popup_imgsizeX) , _posy + (_y*popup_imgsizeY)  , 0) ;
}
}	

if( bpopup_line ) 
{
g->SetColor(0x000000);
g->FillRect(popup_DrawposX,popup_DrawposY,1, popup_sizeY);
g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1,popup_DrawposY, 1,  popup_sizeY);

g->SetColor(0x00ADAF);
g->FillRect(popup_DrawposX+1,popup_DrawposY, 4, popup_sizeY);
g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1-4,popup_DrawposY,  4, popup_sizeY);

g->SetColor(0xFFFFFF);
g->FillRect(popup_DrawposX+1+4,popup_DrawposY, 4, popup_sizeY);
g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1-8,popup_DrawposY,  4, popup_sizeY);
}

g->SetClip( 0,0,SCREEN_WIDTH, SCREEN_HEIGHT );

}*/



bool cGame::load_update()
{	
	//System.out.println("load_currentStep::"+load_currentStep);

	if(load_currentStep == 0)
	{
		load_totalSteps2 = 0;

		if(load_gamefile)
		{

			if(load_gmaeList_length > 5)
			{
				int _count = 0;
				for (int i=TILE_LAYER::k_id_ground2; i<TILE_LAYER::k_id_cnt; i++)
				{
					SAFE_DEL_ARRAY(m_tileMapLayer[i]);
					SAFE_DEL_ARRAY(m_tileFlipLayer[i]);	
				}

				for (int i=TILE_LAYER::k_id_ground2; i<TILE_LAYER::k_id_cnt; i++)
				{
					_count = 5+((i-1)*2);

					if(load_gmaeList_length > _count)
					{
						m_tileMapLayer[i] = loadTileMap(load_gmaeList[_count]);//TILEMAP_WORLD_LAYER1_RAW);
						m_tileMapLayer_sub_length[i] =  loadTileMap_rtn_length;
						
						m_tileFlipLayer[i] = Data_readAll(load_gmaeList[_count+1]);//TILEMAP_WORLD_LAYER1_FLIP);
						m_tileFlipLayer_sub_length[i] = Data_readAll_rtn_length;

						if(m_tileMapLayer_sub_length[i] == 0) 
						{
							m_tileMapLayer[i] = NULL;
						}  //todo
					}
				}
			}

			SAFE_DEL_ARRAY(m_tileMapLayer[TILE_LAYER::k_id_ground]);
			SAFE_DEL_ARRAY(m_tileFlipLayer[TILE_LAYER::k_id_ground]);

			m_tileMapLayer[TILE_LAYER::k_id_ground] = loadTileMap(load_gmaeList[0]);//TILEMAP_WORLD_LAYER0_RAW);
			m_tileMapLayer_sub_length[TILE_LAYER::k_id_ground] = loadTileMap_rtn_length;

			m_tileFlipLayer[TILE_LAYER::k_id_ground] = Data_readAll(load_gmaeList[1]);//TILEMAP_WORLD_LAYER0_FLIP);
			m_tileFlipLayer_sub_length[TILE_LAYER::k_id_ground] = Data_readAll_rtn_length;

			m_actorsData = Data_readAll(load_gmaeList[2]);//TILEMAP_WORLD_ACTORS);
			m_actorsData_length = Data_readAll_rtn_length;

			m_cinematicData = Data_readAll(load_gmaeList[3]);//TILEMAP_WORLD_CINEMATICS);

			SAFE_DEL_ARRAY(load_gmaeSpriteList);
			load_gmaeSpriteList = loadActorsDataSpriteList();

			if(load_gmaeSpriteList == NULL)
			{
				load_totalSteps2 = 3 + (TILE_LAYER::k_id_cnt ) ;
			}
			else
			{
				load_totalSteps2 = load_gmaeSpriteList_length + 3 + (TILE_LAYER::k_id_cnt ) ;
			}
		}


		load_totalSteps1 = load_commonSpriteListSize + load_bgSpriteListSize + load_spriteListSize; //+ //load_commonDataListSize ;
		load_totalSteps = load_totalSteps1 + load_totalSteps2 ;		

		if(load_commonSpriteListSize > 0)
		{
			SAFE_DEL_ARRAY_OBJ(load_commonSpriteArray,load_commonSpriteArray_length);
			load_commonSpriteArray = GL_NEW ASprite*[load_commonSpriteListSize];
			load_commonSpriteArray_length = load_commonSpriteListSize;
		}

		if(load_spriteListSize > 0)
		{
			SAFE_DEL_ARRAY_OBJ(load_spriteArray,load_spriteArray_length);
			load_spriteArray = GL_NEW ASprite*[load_spriteListSize];
			load_spriteArray_length = load_spriteListSize;

		}
	}
	else if(load_currentStep <= load_totalSteps1)
	{
		if(load_update1())
		{
			if(!load_gamefile)
			{
				return true;
			}
		}
	}
	else if(load_gamefile)
	{
		if(load_update2())
		{
			return true;
		}
	}

	load_currentStep++;
	return false;

}

bool cGame::load_update1()
{
	if(load_currentStep >= 0)
	{
		// Create total steps and storage if first step		

		bool bCloseStream = (load_currentStep == (load_totalSteps1 - 1));

		int offset;
		int resID;

		if(load_currentStep <= load_totalSteps1)
		{
			int* spriteList;
			ASprite** spriteArray;

			if(load_currentStep <= load_commonSpriteListSize)
			{
				offset = load_currentStep-1;
				spriteList = load_commonSpriteList;
				spriteArray = load_commonSpriteArray;
				//System.out.println("spriteList "+spriteList[0]);
			}
			else if(load_currentStep <= load_commonSpriteListSize + load_bgSpriteListSize)
			{
				offset = load_currentStep - 1 - load_commonSpriteListSize;
				spriteList = load_bgSpriteList;
				spriteArray = load_bgSpriteArray;
			}
			else
			{
				offset = load_currentStep - 1 - load_commonSpriteListSize - load_bgSpriteListSize;
				spriteList = load_spriteList;
				spriteArray = load_spriteArray;  //m_bSprite;				
			}


			resID = spriteList[offset << 1];     

			if (resID >= 0)
			{
				if (spriteArray[offset] != NULL)
				{
					return false;
				}

				byte* buf;

				Data_init(PACK_SPRITE);
								
				buf = Data_readAll(resID);

				SAFE_DEL(spriteArray[offset]);

				spriteArray[offset] = GL_NEW ASprite();
				spriteArray[offset]->Load(buf, 0);
				
				Data_free();
					
				SAFE_DELETE(buf);

				//m_bSprite
				spriteArray[offset]->enablePrecalcImage( 1, false);

//				if(resID == SPRITE_EFFECT_ALPHA_2)
//				{
//					ModifyPalette(spriteArray[offset], 0, 0);
	//			}
				

			}

		}

		if(load_currentStep >= load_totalSteps1)
		{			
			return true;
		}
	}
	return false;
}



bool cGame::load_update2()
{
	if(load_currentStep >= 0) 
	{        
		int offset;
		int resID;

		if(load_currentStep <= load_totalSteps1+1) // LOADCOLMAP, LOADCINEMATIC
		{
			//System.out.println("loadColMap");
			loadColMap(load_gmaeList[4]);
			LoadCinematics(m_cinematicData);

			m_gBB->SetColor(0x000000);
			m_gBB->FillRect(0, 0, BB::CDB_W, BB::CDB_H);

			SAFE_DEL_ARRAY(m_tileBB);
			m_tileBB	= GL_NEW short[BB::CDB_TW * BB::CDB_TH];

		}
		else if(load_currentStep <= load_totalSteps1+2) // LOAD FLIPLAYER
		{

#ifndef USE_DRAWRGB_FOR_TILES
			for(int x = TILE_LAYER::k_id_ground ; x < TILE_LAYER::k_id_cnt ; x++)
			{
				if(/**/m_tileFlipLayer[x] != NULL)
				{
					for(int i = 0 ; i < m_tileFlipLayer_sub_length[x] ; i++)
					{
						m_tileFlipLayer[x][i] = (byte)(
							((m_tileFlipLayer[x][i] & 1)   << 1) |
							((m_tileFlipLayer[x][i] & 2)   >> 1) |
							((m_tileFlipLayer[x][i] & 4)   << 1) |
							((m_tileFlipLayer[x][i] & 8)   >> 1) |
							((m_tileFlipLayer[x][i] & 16)  << 1) |
							((m_tileFlipLayer[x][i] & 32)  >> 1) |
							((m_tileFlipLayer[x][i] & 64)  << 1) |
							((m_tileFlipLayer[x][i] & 128) >> 1));	
					}
				}
			}
#endif		
			//loadTileSetA(load_gameTileList,TILE_LAYER::k_id_ground);
		}
		else if(load_currentStep <= load_totalSteps1+2+TILE_LAYER::k_id_cnt) // LOAD TILE SPRITE
		{

			//LOAD TILESET
			offset = load_currentStep-1-load_totalSteps1-2  ;			
			loadTileSetA(load_gameTileList,offset);

		}		
		else if(load_currentStep <= load_totalSteps-1) //LOAD ACTOR SPRITE
		{
			offset = load_currentStep-1-load_totalSteps1-2 - (TILE_LAYER::k_id_cnt );
			resID = load_gmaeSpriteList[offset];

			if (resID >= 0)
			{
				loadSprite(resID);
			}
		}
		else
		{
			//System.out.println("actordata");
			loadActorsData();
		}

		if(load_currentStep >= load_totalSteps)
		{			
			return true;
		}
	}

	return false;

}




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// LOAD TILEMAP LOAD TILEMAP LOAD TILEMAP LOAD TILEMAP LOAD TILEMAP
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// load a tilemap.
///
/// @brief load a tilemap (header+raw) from the tilemap's pack.
///
/// @param header_index	index of the header file in the pack
/// @param raw_index index of the raw file in the pack
//--------------------------------------------------------------------------
// TODO_LOLO => add some asserts in debug mode.
byte* cGame::loadTileMap (int raw_index)
{
	if (raw_index < 0 ) return NULL;
	//byte[] map;
	byte* map;


	// init pack.
//	Data_init(PACK_MAP);

	// open data at raw's index.
	Data_open(raw_index);

	m_tileMapW = Data_readU8();
	m_tileMapH = Data_readU8();

	//////DBG("m_tileMapW = " + m_tileMapW);
	//////DBG("m_tileMapH = " + m_tileMapH);

	// allocate tilemap.
	map = GL_NEW byte[m_tileMapW * m_tileMapH];
	loadTileMap_rtn_length = m_tileMapW * m_tileMapH;

	// read and convert tilemap.
	for (int i = 0; i < (m_tileMapW * m_tileMapH); i++)
	{
		map[i] = (byte)Data_readU8();
	}

	return map;
}




//--------------------------------------------------------------------------
/// loadActorsData
//--------------------------------------------------------------------------
void cGame::loadActorsData()
{
	if (m_actorsData != NULL)
	{
		int i = 0;
		int j;
		int paramNum;
		int slotAmount = 1;

		for(int _k = 0 ; _k < (ZONES::k_cnt * ZONES::k_data_size) ; _k++)
		{
			cEntity::s_zones[_k] = 0 ;  //todo
		}

		if (m_actorsData_length > 0)
		{
			short*  params= GL_NEW short[ACTOR_MAX]; //id,x,y, & params

			int id;
			int entityID = 0;
			int actorCnt = 0;
			//int zoneCnt = 0;
			//System.out.println("m_actorsData.length=-==>"+m_actorsData.length);
			while (i < m_actorsData_length)
			{
				paramNum = m_actorsData[i++];

				for (j = 0; j < paramNum; j++)
				{				
					params[j] = (m_actorsData[i++] & 0xFF);
					params[j] |=  (m_actorsData[i++] << 8);
				}
			
				//if (params[ACTOR_GTSID] >= 100 && params[ACTOR_GTSID] != 220)//ZONES.k_start) //LOAD ZOON
				if( params[ACTOR_GTSID] >= 200 && params[ACTOR_GTSID] != 220 )	// NOT SPRITE
				{
					//id = (params[ACTOR_GTSID] - ZONES.k_start) << 2;

					id = actorCnt << 2; 

					cEntity::s_zones[id++] = params[2];  //todo
					cEntity::s_zones[id++] = params[3];
					cEntity::s_zones[id++] = params[4];
					cEntity::s_zones[id  ] = params[5];

					actorCnt++;	
				}
				//else if (params[ACTOR_GTSID] >= 200)// HELPERS.k_start)
				//{
				//	id = getHelperId(params[ACTOR_GTSID]);
				//	cENTITY::s_helpers[id + 0] = params[1];
				//	cENTITY::s_helpers[id + 1] = params[2];

				//	if ((params[ACTOR_GTSID] >= HELPERS.k_attic_hide_spot_first) &&
				//		(params[ACTOR_GTSID] < HELPERS.k_attic_hide_spot_max))
				//	{
				//		m_atticHideSpotTopLayer[params[ACTOR_GTSID] - HELPERS.k_attic_hide_spot_first] = (params[3] != 0);
				//	}
				//}
				else
				{
					slotAmount = 1;
					//switch (params[ACTOR_GTSID])
					//{

					//case GAMESPRITE_MAIN_CHAR: //ENTITY::k_main_character:	
					//case GAMESPRITE_CHICK: //ENTITY::k_main_character:	
					//	slotAmount = 4;//DECKDOOR.k_slot_amount;						
					//	break;
			

					//case GAMESPRITE_FISH:
					//	slotAmount = 3;	
					//	break;

					//case ENTITY::K_SHINE:
					//	slotAmount = 0;
					//	break;
				
					//} // end switch (params[0])
					

					SAFE_DEL(getEntity(entityID));
					getEntity(entityID) = GL_NEW cEntity(params[ACTOR_GTSID], slotAmount);

					//if(params[ACTOR_GTSID] != ENTITY::k_trigger)
					//{
						getEntity(entityID++)->init(params[ACTOR_FLAGS], params[ACTOR_POSX], params[ACTOR_POSY], params, paramNum);
					//}
					//else
					//{
					//	getEntity(entityID++)->init(0, params[ACTOR_POSX], params[ACTOR_POSY], params);
					//}

				} // end if (params[0] >= ENTITY::k_type_helpers_start)

			} // end while (i < m_actorsData.length)
			SAFE_DEL_ARRAY(params);

			m_actorsMax_count = entityID;	// Max Entity Count

		}// end if (m_actorsData.length > 0)

	} // end if (m_actorsData != NULL)
}




int* cGame::loadActorsDataSpriteList()
{

	if (m_actorsData != NULL)
	{
		int i = 0;
		int j;
		int paramNum;
		int slotAmount = 1;
		int spriteList[100];
		int spriteList_length = 100;

		int spriteListLength = 0;
		int loadSprite = -1;

		for(int _i = 0 ; _i < spriteList_length; _i++)
		{
			spriteList[_i] = -1;
		}		

		if (m_actorsData_length > 0)
		{
			//short params[] = GL_NEW short[15]; //id,x,y, & params
			short params[15] ; //id,x,y, & params

			//int id;//Robust, not used
			int entityID = 0;

			while (i < m_actorsData_length)
			{
				paramNum = m_actorsData[i++];

				for (j = 0; j < paramNum; j++)
				{				
					params[j] = (m_actorsData[i++] & 0xFF);
					params[j] |= (m_actorsData[i++] << 8);
				}

				bool noSprite = false;

				loadSprite = params[ACTOR_GTSID];
				
				bool addElespritelist = true;
				for(int _i = 0 ; _i < spriteListLength ; _i++)
				{
					if(spriteList[_i] == loadSprite)
					{
						addElespritelist = false;
						break;
					}
				}

				if( loadSprite >= 200 )	// NOT SPRITE
				{
					noSprite = true;
				}

				if(addElespritelist && !noSprite)
				{
					spriteList[spriteListLength] = loadSprite;
					spriteListLength ++;
				}

			} // end while (i < m_actorsData.length)


			int* tempSpriteList = GL_NEW int[spriteListLength]; 
			load_gmaeSpriteList_length = spriteListLength;

			for(int _i = 0 ; _i < spriteListLength ; _i++)
			{
				tempSpriteList[_i] = spriteList[_i];
				//System.out.println("spriteList["+_i+"]"+spriteList[_i]);
			}

			
			return 	tempSpriteList;
		}// end if (m_actorsData.length > 0)

	} // end if (m_actorsData != NULL)

	return NULL;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// LOAD COLMAP LOAD COLMAP LOAD COLMAP LOAD COLMAP LOAD COLMAP LOAD COLMAP
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// loadColMap
///
/// @brief load a colmap from the collision map's pack.
///
/// @param col_index index of the header file in the pack
//--------------------------------------------------------------------------
//#define PACK_POS(x, y)		((y*/**/m_tileMapW)+x)

void cGame::loadColMap (int col_index)
{
	// init pack.
//	Data_init(PACK_COLMAP);

	Data_open(col_index);

	SAFE_DEL_ARRAY(m_mapCol);
	m_mapCol = GL_NEW char[m_tileMapH * m_tileMapW];
	MEMSET(m_mapCol, -1, m_tileMapH * m_tileMapW);

	for (int y = 0; y < m_tileMapH; y++)
	{
		for (int x = 0; x < m_tileMapW; x++)
		{
			m_mapCol[(y*m_tileMapW)+x] = (char)Data_readU8();				
		}
	}

	// close colmap pack.
	Data_free();
}


void cGame::LoadCinematics (byte* data)  //todo
{
/*
	//////DBG("cinematic data.length = " + data.length);

	s_specialCineCommand = 0;
	s_nextCinematic = -1;

	int pos = 0;
	// 씨네마틱 넘버
	short cin_nums = data[pos++];
	
	for(int i=0; i<s_cinematics_length; i++)
	{
		SAFE_DEL_ARRAY_ARRAY(s_cinematics[i], s_cinematics_sub_length[i]);
	}

	SAFE_DEL_ARRAY(s_cinematics);
	SAFE_DEL_ARRAY(s_cinematicsId);
	SAFE_DEL_ARRAY_ARRAY(s_currentFramePos,s_currentFramePos_length);
	SAFE_DEL_ARRAY_ARRAY(s_runningCinematicTrackActors, s_runningCinematicTrackActors_length);

	
	s_cinematics = GL_NEW byte**[cin_nums];
	s_cinematics_length = cin_nums;

	s_cinematicsId = GL_NEW short[cin_nums];
	s_cinematicsId_length = cin_nums;

	s_currentFramePos = GL_NEW int*[cin_nums];
	s_currentFramePos_length = cin_nums;

	s_runningCinematicTrackActors = GL_NEW int*[cin_nums];
	s_runningCinematicTrackActors_length = cin_nums;

	//////DBG("Loading " + cin_nums);
	for (int c = 0; c < cin_nums; c++)
	{
		s_cinematicsId[c] = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
		//////DBG("DATA = "+data[pos]+"::DATA2 "+data[pos+1]);
		pos += 2;

		byte tracks_nums = data[pos++];

		pos += 2; //skip cinematic_number_of_key_frames

		SAFE_DEL_ARRAY_ARRAY(s_cinematics[c], s_cinematics_sub_length[c]);
		s_cinematics[c] = GL_NEW byte*[tracks_nums];
		s_cinematics_sub_length[c] = tracks_nums;

		s_currentFramePos[c] = GL_NEW int[tracks_nums];
		s_currentFramePos_sub_length[c] = tracks_nums;

		s_runningCinematicTrackActors[c] = GL_NEW int[tracks_nums];
		s_runningCinematicTrackActors_sub_length[c] = tracks_nums;
		//////DBG("tracks_nums " + tracks_nums); 
		for (int t = 0; t < tracks_nums; t++)
		{
			int track_start = pos;
			byte track_type = data[pos++];
			pos++; //skip track_flags
			switch (track_type)
			{
			case CTRACK_BASIC:
			case CTRACK_CAMERA:				
				break;
			case CTRACK_OBJ_LAYER:
				int uid = (data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8);
				s_runningCinematicTrackActors[c][t] = uid;
				pos += 2; // skip track_object_layer_id
				break;
			}

			short key_frames_nums = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
			pos += 2;
			int keyframe_start = pos;
			//////DBG("key_frames_nums " + key_frames_nums+"::keyframe_start  "+ keyframe_start);
			for (int k = 0; k < key_frames_nums; k++)
			{
				pos += 2; //skip key_frame_time

				byte commands_nums = data[pos++];
				for (int l = 0; l < commands_nums; l++) {
					byte cmd_type = data[pos++];
					if(cmd_type >= CCMD_FIRST_CUSTOM)
					{
						//////DBG("READING CUSTOM PARAM" + cmd_type + " " + GetCustomCinematicCommandNumParams(cmd_type));
						//	pos += GetCustomCinematicCommandNumParams(cmd_type);
					}
					else
					{
						//////DBG("cmd_type " + cmd_type);
						switch (cmd_type)
						{
						case CCMD_CAMERA_SET_POS:
						case CCMD_CAMERA_CENTER_TO:
						case CCMD_OBJ_LAYER_SET_POS:
						case CCMD_BASIC_SET_POS:
						case CCMD_SI_SET_POS:
							pos += 2; //skip key_frame_cmd_x
							pos += 2; //skip key_frame_cmd_y
							break;
						case CCMD_CAMERA_FOCUS_ON:
							pos += 1;  //skip Thread to follow,
							pos += 2;  //skip OffsetY
							pos += 2;  //skip OffsetY
							break;									
						case CCMD_OBJ_LAYER_SET_ANIM:
						case CCMD_BASIC_SET_ACTION:
						case CCMD_SI_SET_ANIM:
							pos++; // skip key_frame_cmd_anim
							break;
						case CCMD_OBJ_LAYER_ADD_FLAGS:
						case CCMD_OBJ_LAYER_REMOVE_FLAGS:
						case CCMD_SI_ADD_FLAGS:
						case CCMD_SI_REMOVE_FLAGS:
							pos += 4; // skip key_frame_cmd_flags
							break;

						case CCMD_BASIC_OBJEVENT1:
						case CCMD_BASIC_OBJEVENT2:
						case CCMD_BASIC_OBJEVENT3:	
							// +2 obj id == short.
							pos += (GetSendEventNumParams(cmd_type) << 1) + 2;	//all shorts for now.
							break;
						case CCMD_BASIC_EVENT1:
						case CCMD_BASIC_EVENT2:
						case CCMD_BASIC_EVENT3:
							pos += (GetSendEventNumParams(cmd_type) << 1);	//all shorts for now.									
							break;
						default:
							////DBG("Unknown command type " + cmd_type);
							////DBG("Current pos " + pos);									
							break;
						}//End Switch
					}// End if(cmd_type)
				}//End for (int l = 0; l < commands_nums; l++) 
			}//End for (int k = 0; k < key_frames_nums; k++)
			int track_length = pos - track_start;
			SAFE_DEL_ARRAY(s_cinematics[c][t]);
			s_cinematics[c][t] = GL_NEW byte[track_length + 2]; //2 more byte to store pos for use when reset
			s_cinematics_sub_sub_length[c][t] = track_length + 2;


			s_currentFramePos[c][t] = keyframe_start - track_start; //start key frame offset to track data

			//System.rraycopy(data, track_start, s_cinematics[c][t], 0, track_length);
			MEMCPY(s_cinematics[c][t],data+track_start,track_length);

			s_cinematics[c][t][track_length] = (byte)(s_currentFramePos[c][t] & 0xFF);
			s_cinematics[c][t][track_length + 1] = (byte)((s_currentFramePos[c][t] >> 8) & 0xFF);
		}
	}

	SAFE_DEL_ARRAY(s_cinematicsFrameTime);
	s_cinematicsFrameTime = GL_NEW short[cin_nums];
	s_cinematicsFrameTime_length = cin_nums;
	ResetCinematics();
	//s_cinematicsFrameTime[0] = 30;
	//////DBG("s_cinematics[c]"+s_cinematics[0][1].length);
*/
}


// Cut and Pasted Stuff from ResetCinematics
void cGame::ResetCinematic(int id)   //todo
{
	byte** currentCinematic = s_cinematics[id];
	int currentCinematic_length = s_cinematics_sub_length[id];
	int* currentCinematic_sub_length = s_cinematics_sub_sub_length[id];
	for (int t = 0; t < currentCinematic_length; t++)
	{
		byte* data = currentCinematic[t];
		int data_length = currentCinematic_sub_length[t];
		s_currentFramePos[id][t] = (data[data_length - 2] & 0xFF) + ((data[data_length - 1] << 8)& 0xFF);
	}	
}

void cGame::ResetCinematics()  //todo
{
	//initial cinematic state
	s_cinematicsPause = false;
	for (int i = 0; i < s_cinematicsFrameTime_length; i++)
	{
		s_cinematicsFrameTime[i] = -1;
	}

#if Optimize_Cinematic
	s_ActiveCinematicCount = 0;
#endif

	//restore every track pos for when reset,
	//when need of not play cinema again, then remove these code
	for (int c = 0; c < s_cinematicsId_length; c++)
	{
		byte** currentCinematic = s_cinematics[c];
		int currentCinematic_length = s_cinematics_sub_length[c];
		int* currentCinematic_sub_length = s_cinematics_sub_sub_length[c];
		for (int t = 0; t < currentCinematic_length; t++)
		{
			byte* data = currentCinematic[t];
			int data_length = currentCinematic_sub_length[t];
			s_currentFramePos[c][t] = (data[data_length - 2] & 0xFF) + ((data[data_length - 1] << 8)& 0xFF);
		}
	}
}
void cGame::FreeCinematics()
{
	//s_cinematics = NULL;
	for(int i=0; i<s_cinematics_length; i++)
	{
		SAFE_DEL_ARRAY_ARRAY(s_cinematics[i],s_cinematics_sub_length[i]);
	}
	SAFE_DEL_ARRAY(s_cinematics);
	//s_cinematicsId = NULL;
	//s_cinematicsFrameTime = NULL;
	//s_currentFramePos = NULL;

	//s_runningCinematicTrackActors = NULL;


	SAFE_DEL_ARRAY(s_cinematicsId);
	SAFE_DEL_ARRAY(s_cinematicsFrameTime);
	SAFE_DEL_ARRAY_ARRAY(s_currentFramePos, s_currentFramePos_length);
	SAFE_DEL_ARRAY_ARRAY(s_runningCinematicTrackActors, s_runningCinematicTrackActors_length);

}
/*
void cGame::StartCinematic (int index)
{
//TRACE_CINEMATIC("STARTING CINEMATIC " + index);

#if Optimize_Cinematic

if ( s_cinematicsFrameTime[index] < 0 )
{
++ s_ActiveCinematicCount;
}

#endif

s_cinematicsFrameTime[index] = 0; //set start flag
}

public static bool TryToStartQueuedCinematic()
{
	if( !IsCinematicActive() )
	{
		if( s_nextCinematic >= 0)
		{
			//TRACE_CINEMATIC("Playing next cinematic " + s_nextCinematic);
			ResetCinematic(s_nextCinematic);	//to make sure cinematic will play. 
			//Cinematic triggered from triggerzone reset cinematic correctly allready
			//both for queued cinematic we systematicly do it before every execution.
			StartCinematic(s_nextCinematic);
			s_nextCinematic = -1;

			return true;
		}
	}	

return false;
}
*/
void cGame::EndCinematic (int index)
{	
#if Optimize_Cinematic
	if ( s_cinematicsFrameTime[index] >= 0 )
	{
		-- s_ActiveCinematicCount;
	}
#endif
	s_cinematicsFrameTime[index] = -2; // end flag


	//if ( index == ANIMATION_OPENING )
	//{
	//	m_StateStory = STORY_OPENNING_END;
	//}
	//else if ( index == ANIMATION_HOUSEOPENING )
	//{
	//	m_StateStory = STORYL_HOUSEOPENNING_END;
	//}


	//TRACE_CINEMATIC("ENDING CINEMATIC " + index);
	if( s_nextCinematic == -1)
	{
		//if ( TEST_FLAG(s_specialCineCommand, SpecialCinematicCommands.BlockedPlayer))
		//{
		//	UnBlockPlayer();
		//}

		//if( s_FreezeCamera && !s_smoothCinematicRestoreCamera ) 
		//{
		/**///Always set camera back to main actor			
		//}

		//s_FreezeCamera = false;
		//s_smoothCinematicRestoreCamera = false;
		//		
		//if( IsFlyingLevel(s_level)  )
		//{
		//	 s_playerPropertiesChanged = PlayerProperties.All;  //redraw all				 
		//}			
		//s_enableUserSkipCinematic = false;
		//s_specialCineCommand = 0;

		//if( s_savePlayerPositionAfterCinematic )
		//{
		//	s_player.CheckPointSaveAllInformation();
		//	s_savePlayerPositionAfterCinematic = false;
		//}
	}
}

void cGame::PauseCinematics ()
{
	s_cinematicsPause = true;
}


void cGame::ResumeCinematics ()
{		
	if( s_cinematicWaitType == WaitType::None)
	{
		s_cinematicsPause = false;
	}
}

int cGame::GetCinematicIndex (int id)   //todo
{
	//		for (int i = 0; i < s_cinematicsId.length; ++i) 
	for (int i = 0; i < s_cinematicsId_length; ++i) 

	{
		if (s_cinematicsId[i] == id) 
		{
			return i;
		}
	}
	return -1;
}




// -1 == no cinematic.
int cGame::GetActiveCinematicCurrentTime()
{
	if (s_cinematicsFrameTime != NULL)
	{
		//for (int c = 0; c < s_cinematicsFrameTime.length; c++)
		for (int c = 0; c < s_cinematicsFrameTime_length; c++)
		{
			if (s_cinematicsFrameTime[c] >= 0)	
				return s_cinematicsFrameTime[c];
		}
	}
	return -1;
}

#if Optimize_Cinematic

static int s_ActiveCinematicCount;

bool cGame::IsCinematicActive()
{
	return 	s_ActiveCinematicCount > 0;
}

#else

bool cGame::IsCinematicActive()
{
	if (s_cinematicsFrameTime != NULL)
	{
		//for (int c = 0; c < s_cinematicsFrameTime.length; c++)
		for (int c = 0; c < s_cinematicsFrameTime_length; c++)
		{
			if (s_cinematicsFrameTime[c] >= 0)	
				return true;
		}
	}
	return false;
}
#endif

bool cGame::IsCinematicRunning()
{
	if (s_cinematicsPause == true)
	{
		return false;
	}

	return IsCinematicActive();
}

/*	
public static bool IsActorInRunningCinematic( int uid )
{
#if Optimize_Cinematic
if ( s_ActiveCinematicCount <= 0 ) return false;
#endif
for ( int c = 0; c < s_cinematicsId.length; c++ )
{
if (s_cinematicsFrameTime[c] >= 0)
{
for ( int t = 0; t < s_cinematics[c].length; t++ )
{
if ( s_runningCinematicTrackActors[c][t] == uid )
{
return true;
}
}
}
}

return false;
}

public static bool IsActorInRunningCinematic( cActor obj )
{
return IsActorInRunningCinematic( obj.m_uniqueID );
}
*/


#define ReadCinematicDataShort(dest) dest = (data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8); pos += 2;

void cGame::EndCinematicWait()
{
	s_cinematicWaitType = WaitType::None;
	ResumeCinematics();
}

void cGame::EndAllCinematic()
{
	if(s_cinematics == NULL)
	{
		return;
	}

	//for (int c = 0; c < s_cinematicsId.length; c++)
	for (int c = 0; c < s_cinematicsId_length; c++)
	{
		if (s_cinematicsFrameTime[c] >= 0)
		{
			EndCinematic(c);
		}
	}
}

void cGame::UpdateCinematic()
{

}


cEntity*  cGame::GetActorByUID(int uid)  //todo
{
	//if (s_player != NULL && s_player.m_uniqueID == uid)
	//{
	//    return s_player;
	//}

	for(int i = 0; i < m_entEntities_length; i++)  //todo
	{
		if (m_entEntities[i] != NULL && m_entEntities[i]->m_gameId == uid)
		{
			return m_entEntities[i];
		}
	}

	return NULL;
}

void cGame::StartCinematic (int index)
{
	//TRACE_CINEMATIC("STARTING CINEMATIC " + index);

#if Optimize_Cinematic

	if ( s_cinematicsFrameTime[index] < 0 )
	{
		++ s_ActiveCinematicCount;
	}

#endif

	s_cinematicsFrameTime[index] = 0; //set start flag
}

void cGame::CinematicEvent(int param)
{

//	DBGPRINTF("param  : %d ",param);

	String_phase(  GET_STRING( (param-1), TEXT_INDEX_GAME )  );

	talk_cnt = param;

	if((mascot_s_sceneState & MASCOT_SENCE_STATE_POPUP) != 0)
	{
		popup_show( 0, GET_STRING(param ,TEXT_INDEX_GAME));
	}
	else
	{
		mascot_show( 0, GET_STRING(param ,TEXT_INDEX_GAME));
	}

}



//--------------------------------------------------------------------------
/// load a tileset.
///
/// @brief load a tileset in bsprite format from the tileset's pack and store it in an Image array.
///
/// @param pack_index	index of the bsprite file in the pack
//--------------------------------------------------------------------------
void cGame::loadTileSet (char* pack_index, int indexCnt_Num)
{
	//byte[] buf;
	byte* buf;

	// init pack.
	// tileset pack is splited, only load necessary tileset
	Data_init(/*PACK_TILESET1*/pack_index);

	// load data from pack index.
	buf = Data_readAll(0);

	// allocate tileset and load it.
	/*ASprite* */ts = GL_NEW ASprite();
	ts->Load(buf, 0);

	// close tileset pack and free it.
	Data_free();		

	int pal = 0;
#if USE_WEATHER
	//if (m_sceneData[SCENE_DATA_EXTERIOR] != 0)
	//{
	//	pal = m_weatherPal;
	//}
	if (m_sceneIdx == Data.SCENE_HOME || m_sceneIdx == Data.SCENE_BALCONY)
	{
		if (getWeather() != WEATHER.k_sunny	||
			(Build.k_enableCheatCode &&
			m_cheatStartDay > 1 &&
			(m_cheatDayScriptStep[m_cheatStartDay - 1] == SCRIPTING.k_third_day ||
			m_cheatDayScriptStep[m_cheatStartDay - 1] == SCRIPTING.k_seventh_day)))
		{
			////DBG("!!SETTING RAIN PALETTE!!");
			pal = 1;
		}
	}

	m_weatherPal = pal;
#endif //USE_WEATHER

#ifdef USE_DRAWRGB_FOR_TILES

	ts->m_bWiseModule = false;

	//if (m_sceneIdx == Data.SCENE_HOME || m_sceneIdx == Data.SCENE_BALCONY)
	//{
	//	if (pal > 0)
	//	{
	//		ts.ModifPalette(0, WEATHER.k_pal_cloudy_day_modif);
	//	}
	//	else
	//	{
	//		ts.ModifPalette(0, 0);
	//	}
	//}
	//else

	m_sprTileset[TILE_LAYER::k_id_ground] = ts;
#else

	ts->BuildCacheImages(pal, 0, -1, -1);
	ts->ClearCompressedImageData();

	// keep the tile's images only.

	//m_tileSet[TILE_LAYER::k_id_ground] = GL_NEW Image[ts->_nModules];
	if( m_tileSet && m_tileSet[TILE_LAYER::k_id_ground] )
	{
		//delete[] m_tileSet[TILE_LAYER::k_id_ground];
		m_tileSet[TILE_LAYER::k_id_ground] = NULL;
	}
	m_tileSet[TILE_LAYER::k_id_ground] = GL_NEW CImage*[ts->_nModules];

	for(int i = 0 ; i <= ts->_nModules-1 ; i++){
		m_tileSet[TILE_LAYER::k_id_ground][i] = ts->_modules_image[pal*ts->_nModules+i];
	}

	//ts = NULL;
	addMapSprite(ts);

#endif

	for(int j = TILE_LAYER::k_id_ground2 ; j < TILE_LAYER::k_id_cnt ; j++ )
	{
		if(m_tileMapLayer[j] == NULL){
			//System.out.println("dsdsdsdsd==="+j);
			continue;
		}
		Data_init(/*PACK_TILESET1*/pack_index);

		// load data from pack index.
		buf = Data_readAll(j);

		// allocate tileset and load it.
		ts = GL_NEW ASprite();
		
		ts->Load(buf, 0);

		// close tileset pack and free it.
		Data_free();

#ifdef USE_DRAWRGB_FOR_TILES

		ts->m_bWiseModule = false;
		//if (m_sceneIdx == Data.SCENE_HOME || m_sceneIdx == Data.SCENE_BALCONY)
		//{
		//	if (pal > 0)
		//	{
		//		ts.ModifPalette(0, WEATHER.k_pal_cloudy_day_modif);
		//	}
		//	else
		//	{
		//		ts.ModifPalette(0, 0);
		//	}
		//}
		//else

		m_sprTileset[j] = ts;
#else
		ts->BuildCacheImages(pal, 0, -1, -1);
		ts->ClearCompressedImageData();

		// keep the tile's images only.
		if( m_tileSet && m_tileSet[j] )
		{
			delete[] m_tileSet[j];
			m_tileSet[j] = NULL;
		}
		m_tileSet[j] = GL_NEW CImage*[ts->_nModules];
		for(int i = 0 ; i <= ts->_nModules-1 ; i++)
		{
			m_tileSet[j][i] = ts->_modules_image[pal*ts->_nModules+i];
		}

		//ts = NULL;
		addMapSprite(ts);
#endif
	}

}



void cGame::loadTileSetA (char* pack_index, int indexCnt_Num)
{

	if(m_tileMapLayer[indexCnt_Num] == NULL)
	{			
		if(indexCnt_Num == 4)
		{
			Data_free();
		}
		return;
	}

	byte* buf;

	// init pack.
	// tileset pack is splited, only load necessary tileset
	if(indexCnt_Num == 0)
	{
		Data_init(/*PACK_TILESET1*/pack_index);
	}

	// load data from pack index.
	buf = Data_readAll(indexCnt_Num);

	// allocate tileset and load it.
	ts = GL_NEW ASprite();

	ts->Load(buf, 0);

	// close tileset pack and free it.
	if(indexCnt_Num == 4)
	{
		Data_free();		
	}

	int pal = 0;

#if USE_WEATHER
	//if (m_sceneData[SCENE_DATA_EXTERIOR] != 0)
	//{
	//	pal = m_weatherPal;
	//}
	if (m_sceneIdx == Data.SCENE_HOME || m_sceneIdx == Data.SCENE_BALCONY)
	{
		if (getWeather() != WEATHER.k_sunny	||
			(Build.k_enableCheatCode &&
			m_cheatStartDay > 1 &&
			(m_cheatDayScriptStep[m_cheatStartDay - 1] == SCRIPTING.k_third_day ||
			m_cheatDayScriptStep[m_cheatStartDay - 1] == SCRIPTING.k_seventh_day)))
		{
			////DBG("!!SETTING RAIN PALETTE!!");
			pal = 1;
		}
	}

	m_weatherPal = pal;
#endif //USE_WEATHER


#ifdef USE_DRAWRGB_FOR_TILES

	//ts->m_bWiseModule = false;

	//if (m_sceneIdx == Data.SCENE_HOME || m_sceneIdx == Data.SCENE_BALCONY)
	//{
	//	if (pal > 0)
	//	{
	//		ts.ModifPalette(0, WEATHER.k_pal_cloudy_day_modif);
	//	}
	//	else
	//	{
	//		ts.ModifPalette(0, 0);
	//	}
	//}
	//else
	//{
	//	ts->SetCurrentPalette(pal);
	//}
	if( m_sprTileset[indexCnt_Num] )
	{	
		delete[] m_sprTileset[indexCnt_Num];
	}
	m_sprTileset[indexCnt_Num] = ts;
	
#else

	ts->BuildCacheImages(pal, 0, -1, -1);
	ts->ClearCompressedImageData();

	// keep the tile's images only.

	if( m_tileSet && m_tileSet[indexCnt_Num] )
	{
		delete[] m_tileSet[indexCnt_Num];
		m_tileSet[indexCnt_Num] = NULL;
	}
	m_tileSet[indexCnt_Num] = GL_NEW CImage*[ts->_nModules]; //todo
	for(int i = 0 ; i <= ts->_nModules-1 ; i++)
	{
		m_tileSet[indexCnt_Num][i] = ts->_modules_image[pal*ts->_nModules+i];
	}

	//ts = NULL;
	addMapSprite(ts);
	


#endif

	SAFE_DEL(buf);



}


//--------------------------------------------------------------------------
/// draw several tiles to the backbuffer.
//--------------------------------------------------------------------------
void cGame::BackBuffer_RefreshTiles (int minX, int minY, int maxX, int maxY)
{
	//System.out.println("minX="+minX+"minY="+minY+"maxX="+maxX+"maxY="+maxY);
	if (maxX > m_tileMapW)
	{
		maxX = m_tileMapW;
	}

	if (maxY > m_tileMapH)
	{
		maxY = m_tileMapH;
	}

	if (minX == maxX || minY == maxY)
	{
		return;
	}

	int tile;
	int x1,x2;
	int y1;
	int y2 = minY * m_tileMapW;
	int flip;
	int img_index0;
	int img_index1;
	int x, y, z;

	int left = minX * TILE_W;
	minY = minY * TILE_H;
	maxY = maxY * TILE_H;

	//m_gBB->SetClip(0, 0, BB::CDB_W, BB::CDB_H);


	for (y = minY; y < maxY; y+=TILE_H, y2 += m_tileMapW)
	{
		x2 = left;
		y1 = y % BB::CDB_H;

		for (x = minX; x < maxX; x++, x2 += TILE_W)
		{

			tile 	= x + y2;
			x1		= x2 % BB::CDB_W;
				
			m_gBB->SetColor(0x000000);
			m_gBB->FillRect(x1, y1, TILE_W, TILE_H);

			if(tile < 0) tile = 0 ;
			img_index0 = m_tileMapLayer[TILE_LAYER::k_id_ground][tile] & 0xFF;
			
			if( img_index0 != 255 )
			{
				flip	= (m_tileFlipLayer[TILE_LAYER::k_id_ground][(tile>>2)]);
				flip 	= (flip >> ( (3-(tile&0x3)) << 1) ) & 0x3;

#ifdef USE_DRAWRGB_FOR_TILES
				//m_sprTileset[TILE_LAYER::k_id_ground]->_alpha = false; // this might speed up the drawRGBs
				m_sprTileset[TILE_LAYER::k_id_ground]->PaintModule(m_gBB, img_index0, x1, y1, flip);
				//m_sprTileset[TILE_LAYER::k_id_ground]->_alpha = true; // set it back to true for the layer1 (needs transparency)
#else
				
				if( m_tileSet[TILE_LAYER::k_id_ground][img_index0]->m_pixel )
				{
					ASprite::drawRegion(m_gBB,m_tileSet[TILE_LAYER::k_id_ground][img_index0], /**/
						0,						// x coordinate in backbuffer
						0, 						// y coordinate in backbuffer
						TILE_W, 				// w of backbuffer's image.
						TILE_H, 				// h of backbuffer's image.
						flip, 					// no transfomation
						x1, 						// x coordinate in screen.
						y1, 						// y coordinate in screen.
						CGraphics::TOP | CGraphics::LEFT);//CGraphics::TOP | CGraphics::LEFT);
				}
#endif
			}			

			for(z = TILE_LAYER::k_id_ground2 ; z < TILE_LAYER::k_id_cnt ; z++)
			{
				if (m_tileMapLayer[z] != NULL)
				{
					img_index1 = m_tileMapLayer[z][tile] & 0xff;
					//System.out.println("img_index1====="+img_index1);
					//if(z == TILE_LAYER::k_id_ground3){
					//System.out.println("img_index1====="+img_index1);
					//}	
					if (img_index1 != 255)
					{
						flip	= (m_tileFlipLayer[z][(tile>>2)]);
						flip 	= (flip >> ((3-(tile&0x3)) << 1)) & 0x3;

#ifdef USE_DRAWRGB_FOR_TILES
						m_sprTileset[z]->PaintModule(m_gBB, img_index1, x1, y1, flip);
#else						

						if( m_tileSet[z][img_index1]->m_pixel )
						{
							ASprite::drawRegion(m_gBB, m_tileSet[z][img_index1], // backbuffer image  //todo
								0,						// x coordinate in backbuffer
								0, 						// y coordinate in backbuffer
								TILE_W, 				// w of backbuffer's image.
								TILE_H, 				// h of backbuffer's image.
								flip, 					// no transfomation
								x1, 						// x coordinate in screen.
								y1, 						// y coordinate in screen.
								CGraphics::TOP | CGraphics::LEFT);//graphics.top | graphics.left);

						}
#endif
					}					
					// End if (img_index1 != 255)
				}
			}// End for(z = TILE_LAYER::k_id_ground2 ; z < TILE_LAYER::k_id_cnt ; z++)


		}
	}// End for (y = minY; y < maxY; y+=TILE_H, y2 += m_tileMapW)
}

//--------------------------------------------------------------------------
/// update the backbuffer.
///
/// @brief this method looks for tiles that must be refreshed
///
/// @param x the x coordinate in the tilemap
/// @param y the y coordinate in the tilemap
//--------------------------------------------------------------------------

void cGame::BackBuffer_Update (int x, int y)
{
	int lx 	= PIXEL_TO_TILE(x);
	int ly 	= PIXEL_TO_TILE(y);


	if ((lx == m_lastTileX) && (ly == m_lastTileY))
	{
		// record level coords
		m_lastTileX = lx;
		m_lastTileY = ly;
		m_oldLevelX = x;
		m_oldLevelY = y;
		return;
	}

	int olx = PIXEL_TO_TILE(m_oldLevelX);
	int oly = PIXEL_TO_TILE(m_oldLevelY);
	if ((m_lastTileX == -1 && m_lastTileY == -1)	||
		(/*Math.*/abs(lx - olx) >= BB::CDB_TW) 				||
		(/*Math.*/abs(ly - oly) >= BB::CDB_TH))
	{
		BackBuffer_RefreshTiles(lx, ly, lx+BB::CDB_TW, ly+BB::CDB_TH);
	}
	else
	{
		int minX, maxX, minY, maxY;
		int x1, x2, y1, y2;

		minX = ((x >= m_oldLevelX) ? olx : lx);
		minY = ((y >= m_oldLevelY) ? oly : ly);
		maxX = lx + olx - minX;
		maxY = ly + oly - minY;

		// refresh columns
		x1 = (m_oldLevelX < x) ? (minX + BB::CDB_TW) : minX;
		x2 = (x1 - minX + maxX);

		if (x1 == x2)
		{
			if (x > m_oldLevelX)
			{
				x1--;
			}
			else if (x < m_oldLevelX)
			{
				x2++;
			}
		}

		y1 = (m_oldLevelY <= y) ? maxY : minY;
		y2 = y1 + BB::CDB_TH;

		BackBuffer_RefreshTiles(x1, y1, x2, y2);

		// refresh rows
		x1 = maxX;
		x2 = minX + BB::CDB_TW;

		y1 = (m_oldLevelY < y) ? (minY + BB::CDB_TH) : minY;
		y2 = (m_oldLevelY < y) ? (maxY + BB::CDB_TH) : maxY;

		if (y1 == y2)
		{
			if (y > m_oldLevelY)
			{
				y1--;
			}
			else if (y < m_oldLevelY)
			{
				y2++;
			}
		}

		BackBuffer_RefreshTiles(x1, y1, x2, y2);
	}

	// store current coords.
	m_lastTileX = lx;
	m_lastTileY = ly;
	m_oldLevelX = x;
	m_oldLevelY = y;
}

//--------------------------------------------------------------------------
/// redraw tiles dynamically to the screen.
//--------------------------------------------------------------------------
void cGame::BackBuffer_Redraw (byte* layer, byte* flipmap, int sx, int sy,int layer_length)
{

	int map_tx = PIXEL_TO_TILE(m_mapX);//>>4;
	int map_ty = PIXEL_TO_TILE(m_mapY);//>>4;
	int map_dx = m_mapX% G_TILE_W;//>>8 & 0x14;// % G_TILE_W;
	int map_dy = m_mapY% G_TILE_H;//>>8 & 0x14;// % G_TILE_H;

	map_dx = (map_dx*ZOOM_X)/ZOOM_X_DIV;
	map_dy = (map_dy*ZOOM_Y)/ZOOM_Y_DIV;

	int xx;
	int yy;
	int tile;
	int img;
	int flip;
	int baseX	= sx - map_dx;
	int x		= 0;
	int y		= sy - map_dy;
	int k		= 0;
	int yOff	= map_ty * m_tileMapW;
	//System.out.println("baseX = "+baseX+"::::::y = "+y);
	for (yy = 0; yy < BB::CDB_TH; yy++, y += TILE_H, yOff += m_tileMapW)
	{
		for (xx = 0, x = baseX; xx < BB::CDB_TW; xx++, x += TILE_W, k++)
		{
			if (m_tileBB[k] != 0)
			{
				tile = (xx + map_tx) + yOff;
				if(tile >= layer_length) continue;  //todo
				img	= layer[tile] & 0xFF;
				if (img == 255) continue;

				flip = (int)(flipmap[(tile>>2)]);
				flip = (flip >> ((3-(tile&0x3)) << 1)) & 0x3;

				//if ((flip & FLAG_FLIP_X) != 0)
				//{
				//	if ((flip & FLAG_FLIP_Y) != 0)
				//	{
				//		flip = Sprite.TRANS_ROT180;
				//	}
				//	else
				//	{
				//		flip = Sprite.TRANS_MIRROR;
				//	}
				//}
				//else if ((flip & FLAG_FLIP_Y) != 0)
				//{
				//	flip = Sprite.TRANS_MIRROR_ROT180;
				//}
#ifdef USE_DRAWRGB_FOR_TILES
				//m_sprTileset[TILE_LAYER::k_id_upper]->_alpha = false; // this might speed up the drawRGBs
				m_sprTileset[TILE_LAYER::k_id_upper]->PaintModule(g, img, x, y, flip);
				//m_sprTileset[TILE_LAYER::k_id_upper]->_alpha = true; // set it back to true for the layer1 (needs transparency)
#else
				if( m_tileSet[TILE_LAYER::k_id_upper][img]->m_pixel )
				{	
					ASprite::drawRegion(/**/g, m_tileSet[TILE_LAYER::k_id_upper][img],  	// backbuffer image  //todo
						0,				// x coordinate in backbuffer
						0, 				// y coordinate in backbuffer
						TILE_W, 		// w of backbuffer's image.
						TILE_H, 		// h of backbuffer's image.
						flip, 			// no transfomation
						x, 	 			// x coordinate in screen.
						y, 				// y coordinate in screen.
						CGraphics::TOP | CGraphics::LEFT);//CGraphics::TOP | CGraphics::LEFT);

				}
#endif
			}
		}
	}

}

//--------------------------------------------------------------------------
/// draw the backbuffer to the screen.
//--------------------------------------------------------------------------
void cGame::BackBuffer_Draw (int x, int y)
{
	int bb_pos_x = PIXEL_TO_TILE(F2I(m_mapX) * TILE_W) % BB::CDB_W;
	int bb_pos_y = PIXEL_TO_TILE(F2I(m_mapY) * TILE_H) % BB::CDB_H;

	int widthR	= (BB::CDB_W - bb_pos_x);
	int widthL	= (BB::CDB_W - widthR);
	int heightB	= (BB::CDB_H - bb_pos_y);
	int heightT	= (BB::CDB_H - heightB);

	// draw top left
	/**/// backbuffer image
	//			  bb_pos_x, 		// x coordinate in backbuffer
	//			  bb_pos_y, 		// y coordinate in backbuffer
	//			  widthR, 			// w of backbuffer's image.
	//			  heightB, 			// h of backbuffer's image.
	//			  0, 				// no transfomation
	//			  x+0, 				// x coordinate in screen.
	//			  y+0, 				// y coordinate in screen.
	//			  0);//CGraphics::TOP | CGraphics::LEFT);
	/**/g->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	/**/g->DrawImage(m_imgBB, (x+0) - (bb_pos_x), (y+0) - (bb_pos_y), CGraphics::TOP | CGraphics::LEFT); 

	// draw top right
	/**/ //backbuffer image
	//			  bb_pos_x-widthL,	// x coordinate in backbuffer
	//			  bb_pos_y, 		// y coordinate in backbuffer
	//			  widthL, 			// w of backbuffer's image.
	//			  heightB, 			// h of backbuffer's image.
	//			  0, 				// no transfomation
	//			  x+widthR, 		// x coordinate in screen.
	//			  y+0, 				// y coordinate in screen.
	//			  0);//CGraphics::TOP | CGraphics::LEFT);
	/**/g->DrawImage(m_imgBB, (x+widthR) - (bb_pos_x-widthL), (y+0) - (bb_pos_y), CGraphics::TOP | CGraphics::LEFT);

	// draw bottom left
	/**/ //backbuffer image
	//			  bb_pos_x,			// x coordinate in backbuffer
	//			  bb_pos_y-heightT, // y coordinate in backbuffer
	//			  widthR, 			// w of backbuffer's image.
	//			  heightT, 			// h of backbuffer's image.
	//			  0, 				// no transfomation
	//			  x, 				// x coordinate in screen.
	//			  y+heightB, 		// y coordinate in screen.
	//			  0);//CGraphics::TOP | CGraphics::LEFT);
	/**/g->DrawImage(m_imgBB, (x) - (bb_pos_x), (y+heightB) - (bb_pos_y-heightT), CGraphics::TOP | CGraphics::LEFT);

	// draw bottom right
	/**/ //backbuffer image
	//			  bb_pos_x-widthL,	// x coordinate in backbuffer
	//			  bb_pos_y-heightT, // y coordinate in backbuffer
	//			  widthL, 			// w of backbuffer's image.
	//			  heightT, 			// h of backbuffer's image.
	//			  0, 				// no transfomation
	//			  x+widthR, 		// x coordinate in screen.
	//			  y+heightB, 		// y coordinate in screen.
	//			  0);//CGraphics::TOP | CGraphics::LEFT);
	/**/g->DrawImage(m_imgBB, (x+widthR) - (bb_pos_x-widthL), (y+heightB) - (bb_pos_y-heightT), CGraphics::TOP | CGraphics::LEFT);

}

//--------------------------------------------------------------------------
/// only used in debug mode
//--------------------------------------------------------------------------
void cGame::BackBuffer_DebugRefresh (int sx, int sy)
{
#if !ONE_LAYER_BACKGROUND
	int map_tx = F2I(m_mapX) >> 4; // / G_TILE_W;
	int map_ty = F2I(m_mapY) >> 4; // / G_TILE_H;
	int map_dx = F2I(m_mapX) & 0xF;// % G_TILE_W;
	int map_dy = F2I(m_mapY) & 0xF;// % G_TILE_H;

	map_dx = SCALE_IN_X(map_dx);
	map_dy = SCALE_IN_Y(map_dy);

	g->SetColor(0xFF0000);
	for (int i = 0; i < BB::CDB_TW; i++)
	{
		for (int j = 0; j < BB::CDB_TH; j++)
		{
			int k = i + (j * BB::CDB_TW);

			if (m_tileBB[k] != 0)
			{
				int x = sx + (i*TILE_W) - map_dx;
				int y = sy + (j*TILE_H) - map_dy;

				g->FillRect(x, y, TILE_W, TILE_H);
			}
		}
	}
#endif //ONE_LAYER_BACKGROUND
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// GAME COLLISION GAME COLLISION GAME COLLISION GAME COLLISION
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// collision detection between two rectangles
///
/// @param rect1 first box to test.
/// @param rect2 second box to test.
//--------------------------------------------------------------------------

#define VAR_FIXED_TO_TILE(var)			var >>= (FIXED_PRECISION + 4)


bool cGame::collisionDetection (int* rect1, int* rect2)
{
	int top2 	= rect2[RECT::k_y];
	int bottom1 = rect1[RECT::k_y] + rect1[RECT::k_h];

	if (bottom1 < top2)
	{
		return false;
	}

	int top1 	= rect1[RECT::k_y];
	int bottom2 = rect2[RECT::k_y] + rect2[RECT::k_h];

	if (top1 > bottom2)
	{
		return false;
	}

	int left2 	= rect2[RECT::k_x];
	int right1 	= rect1[RECT::k_x] + rect1[RECT::k_w];

	if (right1 < left2)
	{
		return false;
	}

	int left1 	= rect1[RECT::k_x];
	int right2 	= rect2[RECT::k_x] + rect2[RECT::k_w];

	if (left1 > right2)
	{
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------
/// collision detection between a point and a rectangle
///
/// @param rect box to test.
/// @param x x-axis coordinate of the point to test.
/// @param y y-axis coordinate of the point to test.
//--------------------------------------------------------------------------
bool cGame::collisionDetection (int* rect, int x, int y)
{
	if (x < rect[RECT::k_x])
	{
		return false;
	}
	if (x > rect[RECT::k_x] + rect[RECT::k_w])
	{
		return false;
	}
	if (y < rect[RECT::k_y])
	{
		return false;
	}
	if (y > rect[RECT::k_y] + rect[RECT::k_h])
	{
		return false;
	}

	return true;
}

int cGame::canDropObject(int* rect, int posX, int posY)
{

		//rect[2] -= rect[0];
		//rect[0] = 0;
		//rect[3] -= rect[1];
		//rect[1] = 0;

		//rect[2] -= 10;
		//rect[0] -= 10;
		//rect[3] -= 5;
		//rect[1] -= 5;

	if (rect != NULL)
	{
		rect[0] += (posX);// + I2F(TILE_W / 2));
		rect[1] += (posY);// + I2F(TILE_H / 2));
		rect[2] += (posX);// + I2F(TILE_W / 2));
		rect[3] += (posY);// + I2F(TILE_H / 2));

		// make sure we have at lest 1 tile to process
		if (rect[2] < rect[0])
		{
			rect[2] = rect[0];
		}
		if (rect[3] < rect[1])
		{
			rect[3] = rect[1];
		}

		int x;
		int y;
		rect[0] = rect[0]/(20*TILE_W/20);
		rect[1] = rect[1]/(20*TILE_W/20);
		rect[2] = rect[2]/(20*TILE_W/20);
		rect[3] = rect[3]/(20*TILE_W/20);

		for ( y = rect[1]; y <= rect[3]; y++)
		{
			for (x = rect[0]; x <= rect[2]; x++)
			{
				if (((y)*m_tileMapW)+(x) >= m_tileMapH * m_tileMapW )
				{
					return COL_TILES::k_cant_move_wall;
				}
				else if( m_mapCol[((y)*m_tileMapW)+(x)] != COL_TILES::k_can_move )
				{	
					return m_mapCol[((y)*m_tileMapW)+(x)];
					//return false;
				}
			}
		}
	}

	return COL_TILES::k_can_move ;
}



void cGame::getCollisionRect(int * rect , cEntity * _obj)
{
	//int* rect_temp;

		rect[0] = 0;
		rect[1] = 0;
		rect[2] = 0;
		rect[3] = 0;

		//if( _obj->m_type == GAMESPRITE_MAIN_CHAR)
		//{
		//	rect_temp = _obj->GetAbsoluteRect(CHARSLOT::k_slot_boby);
		//}
		//else 
		//{
		//	rect_temp = _obj->GetAbsoluteRect(ETCSLOT::k_slot_boby);
		//}

		//rect[0] = rect_temp[0];
		//rect[1] = rect_temp[1];
		//rect[2] = rect_temp[2];
		//rect[3] = rect_temp[3];

		switch(_obj->m_dir)
		{
			case DIRECT_DOWN:
				rect[0] = -3;
				rect[1] = 0;
				rect[2] = 3;
				rect[3] = 5;
				break;
			case DIRECT_UP:
				rect[0] = -3;
				rect[1] = -5;
				rect[2] = 3;
				rect[3] = 0;
				break;

			case DIRECT_LEFT:
				rect[0] = -5;//-6
				rect[1] = 0;//5
				rect[2] = 0;
				rect[3] = 3;
				break;
			case DIRECT_RIGHT:
				rect[0] = 0;
				rect[1] = 0;
				rect[2] = 5;//6
				rect[3] = 3;
				break;
		}	
}



bool cGame::collideWithZone(int zoneID)
{
	//int id = getZoneId(zoneID);

	//int handPosX1 = getEntity(GAMESPRITE_MAIN_CHAR)->m_posX;
	//int handPosY1 = getEntity(GAMESPRITE_MAIN_CHAR)->m_posY;	

	////int[] handRect = m_entHand->m_renderer[OBJECT.k_slot_primary].GetAbsoluteRect(false);

	//if (handPosX1 < cEntity::s_zones[id + 0])
	//{
	//	return false;
	//}

	//if (handPosY1 < cEntity::s_zones[id + 1])
	//{
	//	return false;
	//}

	//if (handPosX1 > (cEntity::s_zones[id + 0] + cEntity::s_zones[id + 2]))
	//{
	//	return false;
	//}

	//if (handPosY1 > (cEntity::s_zones[id + 1] + cEntity::s_zones[id + 3]))
	//{
	//	return false;
	//}

	return true;
}


bool cGame::collideWithZone(int* rect)
{
	//int handPosX1 = getEntity(GAMESPRITE_MAIN_CHAR)->m_posX;
	//int handPosY1 = getEntity(GAMESPRITE_MAIN_CHAR)->m_posY;		

	////int[] handRect = m_entHand->m_renderer[OBJECT.k_slot_primary].GetAbsoluteRect(false);

	//if (handPosX1 < rect[RECT::k_x])
	//{
	//	return false;
	//}
	//if (handPosX1 > rect[RECT::k_x] + rect[RECT::k_w])
	//{
	//	return false;
	//}
	//if (handPosY1 < rect[RECT::k_y])
	//{
	//	return false;
	//}
	//if (handPosY1 > rect[RECT::k_y] + rect[RECT::k_h])
	//{
	//	return false;
	//}

	return true;
}



bool cGame::collideWithZoneAnimal(int zoneID, int _m_posX, int _m_posY)
{
	int id = getZoneId(zoneID);

	int handPosX1 = _m_posX;
	int handPosY1 = _m_posY;

	int handPosX2 = handPosX1;
	int handPosY2 = handPosY1;

	//int[] handRect = m_entHand->m_renderer[OBJECT.k_slot_primary].GetAbsoluteRect(false);

	if (handPosX2 < cEntity::s_zones[id + 0])
	{
		return false;
	}

	if (handPosY2 < cEntity::s_zones[id + 1])
	{
		return false;
	}

	if (handPosX1 > (cEntity::s_zones[id + 0] + cEntity::s_zones[id + 2]))
	{
		return false;
	}

	if (handPosY1 > (cEntity::s_zones[id + 1] + cEntity::s_zones[id + 3]))
	{
		return false;
	}

	return true;
}




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// LOAD SPRITE LOAD SPRITE LOAD SPRITE LOAD SPRITE LOAD SPRITE LOAD SPRITE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// loadSprite
///
/// @brief load a sprite from a pack and store it in a sprite poll.
///
/// @param index sprite's index in pack.
//--------------------------------------------------------------------------

//#define NEW_ASPRITE( id, close )						GL_NEW ASprite(loadResource(##id, close), 0)

void cGame::loadSprite (int index)
{
	if (m_bSprite[index] != NULL)
	{
		return;
	}

	// load data from pack index.
	// allocate sprite and load it.
	byte* buf;

	SAFE_DEL(m_bSprite[index]);

///	Data_init(PACK_GAMESPRITE);

	buf = Data_readAll(index);

	m_bSprite[index] = GL_NEW ASprite();
	m_bSprite[index]->Load(buf, 0);	

	Data_free();

	SAFE_DELETE(buf);

	//m_bSprite
	m_bSprite[index]->enablePrecalcImage(1, false);


}


//--------------------------------------------------------------------------
/// updateFx
//--------------------------------------------------------------------------
void cGame::updateFxDrawingArea ( )
{
//	int map_x = FIXED_TO_TILE(m_mapX);
//	int map_y = FIXED_TO_TILE(m_mapY);
//
//	int k;
//	int* rect2 = NULL;
//
//	short* tab = /**/m_tileBB;
//
//	ASpriteInstance* si;
//	int* rect;
//
//	for (int i = 0; i < g_pGame->m_actorsMax_count; i++)
////	for (int i = 0; i < ENTITY::k_max; i++)
//	{
//
//		if ( g_pGame->getEntity(i) == NULL )
//		{
//			continue;
//		}
//
//		switch (getEntity(i)->m_type)
//		{
//
//		case GAMESPRITE_MAIN_CHAR:
//		case GAMESPRITE_CHICK:
//			si = getEntity(i)->m_renderer[CHARSLOT::k_slot_boby];
//			rect = si->GetAbsoluteRect(false);
//
//			rect[0] -= 2;//x
//			rect[1] -= 2;//y
//			rect[2] += 2;//x+size
//			rect[3] += 2;//y+size
//			break;
//
//		case GAMESPRITE_BUG:
//		case GAMESPRITE_MOUSE:
//			si = getEntity(i)->m_renderer[ETCSLOT::k_slot_boby];
//			rect = si->GetAbsoluteRect(false);
//
//			rect[0] -= 15;//x
//			rect[1] -= 15;//y
//			rect[2] += 15;//x+size
//			rect[3] += 15;//y+size
//			break;
//
//		default:
//			si = NULL;			
//			break;
//		}
//
//		if ( si == NULL )
//		{
//			continue;
//		}
//
//		//	si = getEntity(_entityID)->m_renderer[ETCSLOT::k_slot_effect];
//		//si = getEntity(_entityID)->m_renderer[ETCSLOT::k_slot_effect];
//
//		// get RECT::
//		//int* rect = si->GetAbsoluteRect(false);
//
//		//rect[0] -= 15;//x
//		//rect[1] -= 15;//y
//		//rect[2] += 15;//x+size
//		//rect[3] += 15;//y+size
//
//		//rect[0] -= 2;//x
//		//rect[1] -= 2;//y
//		//rect[2] += 2;//x+size
//		//rect[3] += 2;//y+size
//
//		int pos_x = getEntity(i)->m_posX;
//		int pos_y = getEntity(i)->m_posY;
//
//		// get rect's top left point.
//		int rx1 = FIXED_TO_TILE(pos_x + rect[0]);
//		int ry1 = FIXED_TO_TILE(pos_y + rect[1]);
//
//		// get rect's bottom right point.
//		int rx2 = FIXED_TO_TILE(pos_x + rect[2]);
//		int ry2 = FIXED_TO_TILE(pos_y + rect[3]);
//
//		int bottom = (pos_y+rect[3]);// + rect[3]);
//		
//		// check for tiles to invalidate.
//		for (int x = rx1; x <= rx2; x++)
//		{
//			int tempCnt = ry2-ry1;
//			int bb_x = 0;
//			int bb_y = 0;
//
//			for (int y = ry1; y <= ry2; y++)
//			{
//				//tempCnt--;	
//				if (x < 0 || x >= m_tileMapW)
//				{
//					continue;
//				}
//
//				if (y < 0 || y >= m_tileMapH)
//				{
//					continue;
//				}
//
//				int j = x + (y * m_tileMapW);
//
//				if ((m_tileMapLayer[TILE_LAYER::k_id_upper][j] & 0xFF) == 255)
//				{
//					continue;
//				}
//
//				bb_x = (x - map_x);
//				bb_y = (y - map_y);
//
//				if (bb_x < 0 || bb_x >= BB::CDB_TW)
//				{
//					continue;
//				}
//
//				if (bb_y < 0 || bb_y >= BB::CDB_TH)
//				{
//					continue;
//				}
//
//				// M-O: Dont what was this check for... but by disabling it,
//				// it now works properly.
//				if ( bottom < TILE_TO_PIXEL(y+tempCnt))
//				{
//					k = bb_x + (bb_y * BB::CDB_TW);
//					tab[k-BB::CDB_TW] = 1;
//					tab[k] = 1;
//				}
//			}
//		}
//	}

}





bool cGame::DrawSort(cEntity* a, cEntity* b) 
{
	if (a->m_posY < b->m_posY) 
	{
		return true;
	} 
	else if (a->m_posY == b->m_posY) 
	{
		if (a->m_posZ < b->m_posZ)
			return true;
	}

	return false;
}

//--------------------------------------------------------------------------
/// update and draw the top view.
//--------------------------------------------------------------------------
//	static bool m_NeedUpdateViewTop = false;
//
void cGame::updateAndDrawViewTop ()
{
	//------------------- RESET TRANSPARENT TILE ----------------------

	if (m_tileMapLayer[TILE_LAYER::k_id_upper] != NULL)
	{
		for (int i = (BB::CDB_TW * BB::CDB_TH) - 1; i >= 0; i--)
		{
			m_tileBB[i] = 0;
		}

		//for (int i = 0; i < ENTITY::k_max; i++)
		for (int i = 0; i < g_pGame->m_actorsMax_count; i++)		
		//{			
		//	if ( g_pGame->getEntity(i) != NULL )//&& ((g_pGame->getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0))
		//	{
				updateFxDrawingArea( );
		////		updateFxDrawingArea( i );
		//	}
		//}

		
	}

	drawViewTop();

//	Process_wheather();
//	draw_wheather();

}


//--------------------------------------------------------------------------
/// draw top view
//--------------------------------------------------------------------------
//public static Vector _actorDrawVector = GL_NEW Vector();

void cGame::drawViewTop ()
{

	if(game_nextState == STATE_LOAD) //Chen Shoutian, fixed bug 1454020
		return;

	if (VIEWPORT::k_w == 0 || VIEWPORT::k_h == 0)
	{
		return;
	}

#ifdef USE_DRAWRGB_FOR_TILES
	if(m_sprTileset[TILE_LAYER::k_id_ground] == NULL) return;
#else
	if( m_tileSet[TILE_LAYER::k_id_ground] == NULL ) return;
#endif


	// ----------------------- DRAW MAP ------------------------------------
	_actorDrawVector->removeAllElements();
	int middle_start = 0;
	int top_start = 0;

	//System.out.println("m_mapX = "+m_mapX+":::m_mapY = "+m_mapY);
	int mx = m_mapX;//F2I(m_mapX);
	int my = m_mapY;//F2I(m_mapY);

//	int focus_x;
//	int focus_y;
//
//	if (m_viewTopFocus != NULL)
//	{
//		focus_x	= F2I(m_viewTopFocus->m_posX + m_viewTopFocusOffX);
//		focus_y	= F2I(m_viewTopFocus->m_posY + m_viewTopFocusOffY);
//
//		//if (m_camFollowsCat)
//		//{
//		//	focus_x += m_entCat->m_renderer[0].GetCurrentAFrameOff(false);
//		//	focus_y += m_entCat->m_renderer[0].GetCurrentAFrameOff(true);
//		//}
//	}
//	else
//	{
//		focus_x = F2I(m_viewTopFocusOffX);
//		focus_y = F2I(m_viewTopFocusOffY);
//	}
//
//	int ox 		= SCALE_IN_X(focus_x - mx) - (VIEWPORT::k_w>>1);
//	int oy 		= SCALE_IN_Y(focus_y - my) - (VIEWPORT::k_h>>1);
////	int ox_max 	= (m_offsetXMax - VIEWPORT::k_w);
////	int oy_max 	= (m_offsetYMax - VIEWPORT::k_h);
//
////	int ox_max 	= ( - VIEWPORT::k_w);
////	int oy_max 	= ( - VIEWPORT::k_h);
//
//	// clump values
//	//if (ox < 0)
//	//{
//	//	ox = 0;
//	//}
//	//else if (ox > ox_max)
//	//{
//	//	ox = ox_max;
//	//}
//
//	//if (oy < 0)
//	//{
//	//	oy = 0;
//	//}
//	//else if (oy > oy_max)
//	//{
//	//	oy = oy_max;
//	//}
//
//	SET_NUMBER_SMALL(ox , 0);
//	SET_NUMBER_SMALL(oy , 0);
//	SET_NUMBER_LARGE(ox , ox_max);
//	SET_NUMBER_LARGE(oy , oy_max);


	// set clip.
	g->SetClip(VIEWPORT::k_x, VIEWPORT::k_y, VIEWPORT::k_w, VIEWPORT::k_h);

	int dx = VIEWPORT::k_x;// - ox;
	int dy = VIEWPORT::k_y;// - oy;

	// update and draw tilemap.
	if(g != m_gBB)
	{
		BackBuffer_Update(mx, my);
		BackBuffer_Draw(0, 0);
		//BackBuffer_Draw(dx, dy);	
	}
	else
	{
		BackBuffer_Redraw(m_tileMapLayer[TILE_LAYER::k_id_ground], m_tileFlipLayer[TILE_LAYER::k_id_ground], dx, dy,m_tileMapLayer_sub_length[TILE_LAYER::k_id_ground]);
	}

	int vx = VIEWPORT::k_x;
	int vy = VIEWPORT::k_y;//zhao jian yun
	int sx = mx ;//+ SCALE_OUT_X(ox);
	int sy = my ;//+ SCALE_OUT_Y(oy);

	//int spriteOffX = -(I2F(sx));
	//int spriteOffY = -(I2F(sy - VIEWPORT::k_y));

	// update and draw object animations.
	//if(m_bNote)
	//{
	//	s_cUI->other_paint();
	//}
	//if (m_ballSmall != NULL)
	//{
	//	m_ballSmall.draw(vx, vy, sx, sy);
	//}


//	for (int i = 0; i < GAMESPRITE_MAX; i++)
	
	for (int i = 0; i < g_pGame->m_actorsMax_count; i++)
//	for (int i = 0; i < ENTITY::k_max; i++)
	{
		//if(  game_currentState == STATE_MINI_PASTURE && i == ENTITY::k_main_character)
		//{
		//	continue;
		//}

		//cEntity _a = getEntity(i);
		//if ( getEntity(i) != NULL && !((getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0)){

		//	getEntity(i)->update();
		//}

		int temp = 0;


		if ( getEntity(i) != NULL )
		{

			if(  getEntity(i)->m_renderer_length == 4)
			{
				temp = CHARSLOT::k_slot_boby;
			}
			
			if ( ( IsInCamera(getEntity(i)->GetRect(temp)) && !( (getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0) )
				|| (getEntity(i)->m_type == ENTITY::K_SHINE)		
				)
			{
				int posY = getEntity(i)->m_posY;

				if ((getEntity(i)->m_flags & DFLAGS::MAP_LAYER) != 0) 
				{
					getEntity(i)->draw(vx, vy, sx, sy);						
				}
				else if((getEntity(i)->m_flags & DFLAGS::TOP_LAYER) != 0)
				{
					int j = top_start;
					int actorDrCnt = _actorDrawVector->size();
					for (; j < actorDrCnt; ++j) 
					{
						if (posY < ((cEntity*)_actorDrawVector->elementAt(j))->m_posY) //todo
							break;
					}
					_actorDrawVector->insertElementAt(getEntity(i), j);
				}
				else if((getEntity(i)->m_flags & DFLAGS::BOTTOM_LAYER) != 0 )
				{
					int j = 0;
					for (; j < middle_start; ++j) 
					{
						cEntity* obj = (cEntity*)_actorDrawVector->elementAt(j);  //todo
						if (DrawSort(getEntity(i), obj)) 
						{
							break;
						}
					}
					_actorDrawVector->insertElementAt(getEntity(i), j);  //todo
					++middle_start;
					++top_start;
				}
				else
				{
					int j = middle_start; 
					for (; j < top_start; ++j) 
					{
						cEntity* obj = (cEntity*)_actorDrawVector->elementAt(j); //todo
						if (DrawSort(getEntity(i), obj)) 
						{
							break;
						}
					}
					_actorDrawVector->insertElementAt(getEntity(i), j);  //todo
					++top_start;
				}
			}
		}

	}


	int actorDrCnt = _actorDrawVector->size();
	for (int j = 0; j < actorDrCnt; ++j) 
	{	
		cEntity* temp = (cEntity*)(_actorDrawVector->elementAt(j));  //todo
		temp->draw(vx, vy, sx, sy);
	}

	BackBuffer_Redraw(m_tileMapLayer[TILE_LAYER::k_id_upper], m_tileFlipLayer[TILE_LAYER::k_id_upper], dx, dy,m_tileMapLayer_sub_length[TILE_LAYER::k_id_upper]);

}



bool cGame::IsInCamera (int* rect) 
{	
	if(rect == NULL)
	{
		return false;
	}
	if (rect[0] > m_mapX+SCREEN_WIDTH) return false;		
	if (rect[2] < m_mapX) return false;		
	if (rect[1] > m_mapY+SCREEN_HEIGHT) return false;
	if (rect[3] < m_mapY) return false;

	return true;
}


bool cGame::IsInCamera (int posX , int posY) {		

	if (posX > m_mapX+SCREEN_WIDTH) return false;		
	if (posX < m_mapX) return false;		
	if (posY > m_mapY+SCREEN_HEIGHT) return false;
	if (posY < m_mapY) return false;
	return true;
}


void cGame::Free_GameRes( )
{
	//m_mapCol = NULL;
	SAFE_DEL_ARRAY(m_mapCol);

#ifdef USE_DRAWRGB_FOR_TILES
	for (int i = TILE_LAYER::k_id_ground; i < /**/TILE_LAYER::k_id_cnt; i++) //todo
	{
		//m_sprTileset[i] = NULL;
		SAFE_DEL(m_sprTileset[i]);
	}
	
#else
	for(int i = TILE_LAYER::k_id_ground ; i < TILE_LAYER::k_id_cnt ; i++ )
	{
		//m_tileSet[i] = NULL;			// tile's image array.
		if( m_tileSet && m_tileSet[i] )
		{
			delete[] m_tileSet[i];
			m_tileSet[i] = NULL;
		}
	}
#endif	

	for(int i = 0 ; i < /**/m_entEntities_length ; i ++) //todo
	{
		if( i != 1 && /**/m_entEntities[i] != NULL){
			m_entEntities[i]->free();
			//m_entEntities[i] = NULL;
			SAFE_DEL(m_entEntities[i]);
		}
	}

	for(int i = 0 ; i < /**/m_bSprite_length ; i++)  //todo
	{
	//	if( i != BOY_GAME_BOY_GAME_GLOBAL_INDEX && /**/m_bSprite[i] != NULL){
		if(m_bSprite[i] != NULL)
		{		
	//		m_bSprite[i]->ClearCompressedImageData();
	//		//m_bSprite[i] = NULL;
			SAFE_DEL(m_bSprite[i]);
		}
	}


	//System.gc();


}


//*************************************************************************
//** Module_Mascot.hpp
//**
//** Copyright @ GameWG 2007
//** All rights reserved
//**
//** Please refer to ReadMe.rtf for a complete description of the project
//** structure
//**************************************************************************

bool cGame::mascot_isHidden()
{
	return ( mascot_currentState == MASCOT_STATE_HIDDEN );
}

//int cGame::mascot_getCurrentState()
//{
//	return mascot_currentState;
//}

//void cGame::mascot_setText(char* _str)
//{
//	if(_str)
//		STRCPY(mascot_currentText, _str);
//
//}

void cGame::mascot_show(int action, char* _string)
{

//	GAME_PAUSE_ON();
//	mascot_currentAction = action;
	//mascot_currentTextScroll = 0;
	//SPRITE_INIT_PAGE();

	//if(mascot_currentImage >= 0 && mascot_currentState == MASCOT_STATE_SHOW_CHMASCOT )
	//{
	//	int _slot = 0;
	//	int _posX = g_pGame->getEntity(mascot_currentImage)->m_OFFposX;
	//	int _posY = g_pGame->getEntity(mascot_currentImage)->m_OFFposY;
	//	//g_pGame->getEntity(mascot_currentImage)->GetAbsoluteRect();

	//	if ( mascot_currentImage == GAMESPRITE_MAIN_CHAR || mascot_currentImage == GAMESPRITE_CHICK )
	//	{
	//		_slot = CHARSLOT::k_slot_boby;
	//	}
	//	else 
	//	{
	//		_slot = ETCSLOT::k_slot_boby;
	//	}

	//	int* _rect = g_pGame->getEntity(mascot_currentImage)->GetAbsoluteRect(_slot);
	//	int _height  = ((mascot_currentImage_Sprite->GetFrameHeight(FRAME_IMOTICON_POPUP)>>1)-_rect[1])+5;

	//	mascot_currentDispY = _posY-_height;

	//	if ( _posX  < CHMASCOT_SHOW_RIGHT )
	//	{
	//		mascot_mascotDirect = DIRECT_RIGHT;
	//		mascot_currentDispX = _posX+_rect[2];
	//		mascot_currentImage_Sprite->SetCurrentAnimation( 1, ANIM_IMOTICON_DIALOGUE_RIGHT, true);
	//	}
	//	else 
	//	{
	//		mascot_mascotDirect = DIRECT_LEFT;
	//		mascot_currentDispX = _posX+_rect[0];
	//		mascot_currentImage_Sprite->SetCurrentAnimation( 1, ANIM_IMOTICON_DIALOGUE_LEFT, true);	
	//	}

	//	mascot_currentImage_Sprite->SetCurrentAnimation( 2, ANIM_IMOTICON_OK, true);
	//}

	//if(_string)
	//{
	//	MEMSET( mascot_currentText, 0, sizeof(mascot_currentText) );
	//	STRCPY( mascot_currentText, _string);
	//}


}

void cGame::mascot_hide(/*bool_TYPE isGradual*/)
{
	mascot_currentState = MASCOT_STATE_HIDDEN;
}


void cGame::mascot_Keyupdate()
{

	if(mascot_currentState != MASCOT_STATE_HIDDEN)
	{

		if( KEY_PRESSED(GAME_KEY_ALL_ACTION)  )
		{

			if(currentTextScroll != 0)
			{		
				mascot_currentTextScroll += MASCOT_CHMASCOT_PAGEY;				
			}
			else
			{	
				if((mascot_s_sceneState & MASCOT_SENCE_STATE_END) != 0 )
				{

					mascot_hide();
					ResumeCinematics();

	//				g_pGame->popup_hide();
	//				g_pGame->Text_freeText(4);
	//				g_pGame->m_chrMove_pause = false;

				}
				else
				{
					talk_cnt += 2;
					Set_talk(talk_cnt, 4 );
				}					
			}
		}

		if ( mascot_currentImage_Sprite != NULL )
		{
//			mascot_currentImage_Sprite->UpdateAnimation( 2 );
		}
	}

	
}

void cGame::mascot_paint()
{

	//SET_STRING_COLOR(0x000000);

	//if(mascot_currentState != MASCOT_STATE_HIDDEN)
	//{
	//	int _posX = 0, _posY = 0 ;
	//
	//	int _slot = 0;

	//	if ( mascot_currentState == MASCOT_STATE_SHOW_CHMASCOT )
	//	{

	//		if ( mascot_currentImage == GAMESPRITE_MAIN_CHAR || mascot_currentImage == GAMESPRITE_CHICK )
	//		{
	//			_slot = CHARSLOT::k_slot_boby;
	//		}
	//		else 
	//		{
	//			_slot = ETCSLOT::k_slot_boby;
	//		}

	//		int* _rect = g_pGame->getEntity(mascot_currentImage)->GetAbsoluteRect(_slot);
	//		int _height  = ((mascot_currentImage_Sprite->GetFrameHeight(FRAME_IMOTICON_POPUP)>>1)-_rect[1])+5;

	//		int _width = _rect[0];

	//		if ( mascot_mascotDirect == DIRECT_RIGHT )
	//		{
	//			_width = _rect[2];
	//		}

	//		_posX = g_pGame->getEntity(mascot_currentImage)->m_OFFposX+(_width);
	//		_posY = g_pGame->getEntity(mascot_currentImage)->m_OFFposY-(_height);

	//		//_posX = mascot_currentDispX;
	//		//_posY = mascot_currentDispY;

	//		mascot_currentImage_Sprite->PaintAnimation(g, 1, _posX, _posY, 0,  0, 0);
	//		mascot_currentImage_Sprite->PaintAnimation(g, 2, _posX, _posY, 0,  0, 0);			
	//	}

	//	if(SPRITE_DRAW_STATIC_PAGE(g, mascot_currentText, 
	//		_posX,_posY,
	//		70,	MASCOT_CHMASCOT_PAGEY, 
	//		mascot_currentTextScroll, CGraphics::HCENTER|CGraphics::VCENTER ) > 0)
	//	{			
	//		currentTextScroll = 1; 
	//	}
	//	else
	//	{
	//		currentTextScroll = 0;
	//	}
	//}

}


void cGame::popup_paint()
{

}

void cGame::popup_update()
{

}




int cGame::popup_getCurrentState()
{
	return popup_currentState;
}

void cGame::popup_show(int action, char* string)
{

}

void cGame::popup_hide(/*bool_TYPE isGradual*/)
{

}
void cGame::popup_end(/*bool_TYPE isGradual*/)
{

}


//bool cGame::updatge_MapMove_Popup()
//{
//	if(bMapMove_PopupShow)
//	{
//		//<<Chen Shoutian, fixed a bug:popup will not be closed until the user presses OK button
//		if(popup_currentState == POPUP_STATE_SHOW_TEXT)
//		{
//			if (game_counter % 60 ==0)
//			{
//				popup_end();
//			}
//		}
//		//>>
//		if(KEY_PRESSED(GAME_KEY_ALL_ACTION)
//
//			)
//		{
//			popup_end();
//		}
//		if(popup_isHidden())
//		{			
//			bMapMove_PopupShow =false;
//			GAME_PAUSE_OFF();
//			if(m_bNote)
//			{
//				m_bSprite[1]->SetCurrentAnimation(NONE_SLOT,LETTER_FLOOR_STAND_ANI_INDEX, true);
//				m_bSprite[2]->SetCurrentAnimation(NONE_SLOT,STAR_EFFECT_LEV1_ANI_INDEX, true);
//			}
//		}
//		return true;
//	}
//	return false;
//
//}



//*************************************************************************
//** Module_Date
//** structure
//**************************************************************************

void cGame::date_Initialize()
{
	Calendar* cal = GL_NEW Calendar();  //todo

	/*
	date_currentWeekDay = cal.get( Calendar.DAY_OF_WEEK );
	date_currentDay = cal.get( Calendar.DAY_OF_MONTH );
	date_currentYear = cal.get( Calendar.YEAR  );
	date_currentMonth = cal.get( Calendar.MONTH );
	date_currentHour = cal.get( Calendar.HOUR );
	*/

	date_currentDay = cal->m_CurDay;
	date_currentYear = cal->m_CurYear;
	date_currentMonth = cal->m_CurMonth;

	//date_currentHour = cal->m_CurHour;
	
	date_currentWeekDay = cal->m_JulianDate.wWeekDay;//cal->GetCurWeekDay();

	SAFE_DEL(cal);
	
	//	date_currentMinute = GET_CALENDAR_MINUTE();
	//  currentDate = date_getDateString();
	//	currentTime = date_getTimeString();
	//	date_AM_PM = cal.get( Calendar.AM_PM );
}


int cGame::date_getCurrentDay()
{
	return date_currentDay;
}

int cGame::date_getCurrentYear()
{
	return date_currentYear;
}


int cGame::date_getCurrentMonth()
{
	return date_currentMonth;
}

int cGame::date_getCurrentWeekDay()
{
	return date_currentWeekDay;
}

void cGame::update_setDay( )
{
	int dayPerMon[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (m_Year % 400 == 0 || ((m_Year % 100 !=0) && (m_Year % 4 == 0)) ) dayPerMon[1]=29;

	m_Day++;
	m_PlusDay++;
	m_WeekDay++;
	if ( m_WeekDay > 6 )
	{
		m_WeekDay = 0;
	}
	if ( dayPerMon[m_Month] < m_Day )
	{
		m_Day = 1;
		m_Month++;
		if( (m_Month+1) > 12 )
		{
			m_Year++;
			m_Month = 0;
		}	
	}
}



int cGame::Check_setDay( )
{
	int _date = 0;
	int _returndate = 0;
	int dayPerMon[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (m_Year % 400 == 0 || ((m_Year % 100 !=0) && (m_Year % 4 == 0)) ) dayPerMon[1]=29;

	if ( m_PlusDay == 0 )
	{
		_date = m_Day+ 7;
	}
	else if ( m_PlusDay%7 == 0 ) 
	{
		_date = m_Day;
	}
	else 
	{
		_date = m_Day+( 7-(m_PlusDay%7) );
	}

	_returndate = _date;

	if ( dayPerMon[m_Month] < _date )
	{
		_returndate = (_date-dayPerMon[m_Month]);
	}

	return _returndate; 
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// GAME CLOCK GAME CLOCK GAME CLOCK GAME CLOCK GAME CLOCK GAME CLOCK
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// TODO: Put in data file arrays.h to see if we save some space.
//static byte s_clockPrecalc[] = 	{
//	0, -1,	// hours ]0,  3]
//	1,  0,	// hours ]3,  6]
//	0,  1,	// hours ]6,  9]
//	-1,  0, // hours ]9, 12]
//};



//--------------------------------------------------------------------------
/// update clock
//--------------------------------------------------------------------------
void cGame::updateClock ()
{
	// init hours and minutes.		

	//m_clockH = (int)((s_game_timeSystem / (CLOCK::k_hour_ms) ) 	% (CLOCK::k_hour) );
	//m_clockM = (int)((s_game_timeSystem / (CLOCK::k_minute_ms) )	% (CLOCK::k_minute) );

	m_clockH = (int)( (m_worldClockM / CLOCK::k_minute) % CLOCK::k_hour);
	m_clockM = (int)( (m_worldClockM) % (CLOCK::k_minute) );


	//System.out.println("m_clockH===>"+m_clockH+"::::m_clockM====>"+m_clockM);
	// init hour position.
	int h_angle = (256 - ((m_clockH * 256) / (CLOCK::k_hour) )) + 64;

	while (h_angle > 256)
		h_angle -= 256;

	m_clockHPosX = /**/s_math_cosTable[( h_angle ) & 0xFF]  * (CLOCK::k_h_radius) ;
	m_clockHPosY = /**/s_math_cosTable[( 64 -  h_angle  ) & 0xFF]   * (CLOCK::k_h_radius) ;
	m_clockHPosY *= -1;

	m_clockHPosX = ( m_clockHPosX )>>8;//FIXED_PRECISION) ;
	m_clockHPosY = ( m_clockHPosY )>>8;//FIXED_PRECISION) ;

	// init minute position.
	int m_angle = (256 - ((m_clockM * 256) / (CLOCK::k_minute) )) + 64;

	while (m_angle > 256)
		m_angle -= 256;

	m_clockMPosX = /**/s_math_cosTable[( m_angle ) & 0xFF]  * (CLOCK::k_m_radius) ;
	m_clockMPosY = /**/s_math_cosTable[( 64 -  m_angle  ) & 0xFF]   * (CLOCK::k_m_radius) ;
	m_clockMPosY *= -1;

	m_clockMPosX = ( m_clockMPosX )>>8;//FIXED_PRECISION) ;
	m_clockMPosY = ( m_clockMPosY )>>8;//FIXED_PRECISION) ;


}

//--------------------------------------------------------------------------
/// draw clock
//--------------------------------------------------------------------------
//static int clock_color;
void cGame::drawClock ()
{
	// ------------------- UPDATE CLOCK ----------------------------------


	if( !m_game_pause && !m_time_pause )//612
	{

		if( m_clockCounter == 0 )
		{
			updateClock();
		}
		
		m_clockCounter++;
		if(m_clockCounter >= CLOCK_DELAY)
		{
			m_clockCounter = 0;
			m_worldClockM++;
			if(m_worldClockM > CLOCK::k_minute * 24)
			{
				m_worldClockM = 0;
			}
		}
		
	}

	// ------------------- DRAW CLOCK --------------------------------------
	//g->SetClip(  0 ,   0 ,   (SCREEN_WIDTH)  ,   (SCREEN_HEIGHT)  ) ;

	//// draw clock
	//g->SetColor(clock_color);

	////int x1, y1, x2, y2, dx, dy;
	//x1 =  (CLOCK::ck_x) + (CLOCK::k_center_x) ;
	//y1 =  (CLOCK::ck_y) + (CLOCK::k_center_y) ;

	////int i;
	//if (m_clockH > 0 && m_clockH <= 3)
	//{
	//	i = 0;
	//}
	//else if (m_clockH > 3 && m_clockH <= 6)
	//{
	//	i = 1;
	//}
	//else if (m_clockH > 6 && m_clockH <= 9)
	//{
	//	i = 2;
	//}
	//else
	//{
	//	i = 3;
	//}

	//dx = s_clockPrecalc[(i<<1) + 0];
	//dy = s_clockPrecalc[(i<<1) + 1];

	//x2 = x1 +  m_clockHPosX  ;
	//y2 = y1 +  m_clockHPosY  ;

	//// draw hours.
	//g->DrawLine(x1   , y1   , x2   , y2);
	//g->DrawLine(x1+dx, y1+dy, x2+dx, y2+dy);

	//x2 = x1 +  m_clockMPosX ;
	//y2 = y1 +  m_clockMPosY ;

	//// draw minutes.
	//g->DrawLine(x1, y1, x2, y2);

}

void cGame::setClock(int _hour, int _min)
{
	m_worldClockM = _min;
	m_worldClockM += CLOCK::k_minute * _hour;
	updateClock();//612
}

int cGame::getClock()
{
	return m_worldClockM;
}


void cGame::Draw_Time()
{
	int _clockH = (int)( m_worldClockM / CLOCK::k_minute );

	if (  5  < _clockH && 18  > _clockH )
	{
		clock_color = (CLOCK::k_color_day);
//		Main_Sprite->PaintFrame( g, MINI_UI_RES_CLOCK_DAY_FRM_INDEX , CLOCK_POSX, CLOCK_POSY, 0,0,0 ) ;
	}
	else 
	{
		clock_color = (CLOCK::k_color_night);
	//	Main_Sprite->PaintFrame( g, MINI_UI_RES_CLOCK_NIGHT_FRM_INDEX , CLOCK_POSX, CLOCK_POSY, 0,0,0 ) ;
	}

	/**/drawClock ();

	/////Draw Hero Energe ////////////////
	if(m_worldClockM >= CLOCK::k_minute * 24)
	{
	//	setClock(6,0);
		m_worldClockM = 0;
	}

}



void cGame::Draw_MainUI()
{
	////Draw Date&Month//////////////////

	
	//g->ResetClip();
	int pos_y = 0;
	
	Draw_Date(pos_y);
	Draw_Maingauge(pos_y);
	Draw_MainCount(pos_y);

	
}


void cGame::Draw_Maingauge(int pos_y)
{	
	int i = 0;

	//for(i = 0 ; i < 3 ; i++)
	//{	
	//	g->SetOpacity(100);
	//	COMMON_SPRITE_MAINUI->PaintModule( g, MODULE_MAIN_UI_HEART_WHITE , GAUGE_POSX + i*GAUGE_WIDTH , pos_y+ GAUGE_POSY, 0 ) ;
	//	g->SetOpacity(255);

	//	g->SetClip(GAUGE_POSX-1 , pos_y + GAUGE_POSY-1 , GAUGE_WIDTH + 2 , GAUGE_HEIGHT+2);
	//	COMMON_SPRITE_MAINUI->PaintModule( g, MODULE_MAIN_UI_HEART_RED , GAUGE_POSX - 1 + i*GAUGE_WIDTH , pos_y+ GAUGE_POSY-1, 0 ) ;
	//	g->ResetClip();
	//}
}

void cGame::Draw_MainCount(int pos_y)
{	

	//COMMON_SPRITE_MAINUI->PaintModule( g, MODULE_MAIN_UI_COIN , UI_COIN_POSX , pos_y+ UI_COIN_POSY - 2, 0 ) ;
		
	//COMMON_SPRITE_MAINUI->PaintModule( g, MODULE_MAIN_UI_PEOPLE , UI_PEOPLE_POSX , pos_y+ UI_PEOPLE_POSY - 4, 0 ) ;
	
	//COMMON_SPRITE_NUMBER->SetCurrentPalette(2);
	//Draw_Number(COMMON_SPRITE_NUMBER,  UI_COIN_POSX + 14 , pos_y+UI_COIN_POSY , 123351189 , MODULE_NUM_L_0 ,DIRECT_LEFT,9, true, true);
	//COMMON_SPRITE_NUMBER->SetCurrentPalette(1);
	//Draw_Number(COMMON_SPRITE_NUMBER,  UI_PEOPLE_POSX +18, pos_y+UI_PEOPLE_POSY , 328561 , MODULE_NUM_L_0 ,DIRECT_LEFT,6, true , true);
	//COMMON_SPRITE_NUMBER->SetCurrentPalette(0);
		
	
}

void cGame::Draw_Date(int pos_y)
{
	int _year = m_Year;
	int _month = m_Month + 1;
	int _day = m_Day;
	int _week = m_WeekDay % 7;
	if (_week == 6)
		_week = -1;
	//	Main_Sprite.PaintFrame( g, MINI_UI_RES_BG_TIME_FRM_INDEX  , DATE_POSX, DATE_POSY, 0,0,0 ) ;		


	//Draw year
	//Draw_Number(COMMON_SPRITE_NUMBER , pos_x + DATE_POSX , pos_y + DATE_POSY , _year , MODULE_NUM_L_0 ,DIRECT_LEFT,0);

	//Draw month&day
//	Draw_Number(COMMON_SPRITE_NUMBER,  DATE_POSX , pos_y+DATE_POSY , _month , MODULE_NUM_L_0 ,DIRECT_RIGHT,2);
//	Draw_Number(COMMON_SPRITE_NUMBER,  DATE_POSX + 6 , pos_y+DATE_POSY , _day , MODULE_NUM_L_0 ,DIRECT_LEFT,2);
	//Draw '/'
//	COMMON_SPRITE_NUMBER->PaintModule( g, MODULE_NUM_SLASH ,DATE_POSX, pos_y+  DATE_POSY+1, 0 ) ;

	//Draw week
//	Main_Sprite->PaintModule( g, (MINI_UI_RES_SUN_MOD_INDEX+_week + 1) , DATE_POSX, DATE_POSY+7, 0 ) ;

	///////Draw_time

	//int _clockH = (int)( m_worldClockM / CLOCK::k_minute );

	//if (  5  < _clockH && 18  > _clockH )
	//{
	//	clock_color = (CLOCK::k_color_day);
	//	//		Main_Sprite->PaintFrame( g, MINI_UI_RES_CLOCK_DAY_FRM_INDEX , CLOCK_POSX, CLOCK_POSY, 0,0,0 ) ;
	//}
	//else 
	//{
	//	clock_color = (CLOCK::k_color_night);
	//	//	Main_Sprite->PaintFrame( g, MINI_UI_RES_CLOCK_NIGHT_FRM_INDEX , CLOCK_POSX, CLOCK_POSY, 0,0,0 ) ;
	//}

	drawClock ();

	//Draw HOUR&MINUTE
//	Draw_Number(COMMON_SPRITE_NUMBER,  TIME_POSX , pos_y+DATE_POSY , m_clockH , MODULE_NUM_L_0 ,DIRECT_RIGHT,2);
//	Draw_Number(COMMON_SPRITE_NUMBER,  TIME_POSX + 4 , pos_y+DATE_POSY , m_clockM , MODULE_NUM_L_0 ,DIRECT_LEFT,2);
	//Draw ':'
//	COMMON_SPRITE_NUMBER->PaintFrame( g, FRAME_NUM_COLON , TIME_POSX, pos_y + DATE_POSY+1, 0, 0, 0);
	//PaintModule( g, MODULE_NUM_COLON , TIME_POSX, pos_y+DATE_POSY+1, 0 ) ;

		
	//draw clock image
//	COMMON_SPRITE_MAINUI->PaintModule( g, FRAME_MAIN_UI_CLOCK , TIME_IMG_POSX, pos_y + DATE_POSY-1, 0);

	/////Draw Hero Energe ////////////////
	if(m_worldClockM >= CLOCK::k_minute * 24)
	{
		//	setClock(6,0);
		m_worldClockM = 0;
	}


}


void cGame::set_fadeOut(int _index)
{
	m_fadeIndex = true;
	m_fadeOut = 1;

	m_setsleep_index = (byte)_index;

}
void cGame::set_fadeIn()
{
	m_fadeIndex = false;
	m_fadeOut = 10;
}


//void cGame::Keypressed_inventory()
//{
//
//}




/* -------------------------------------------------------
* Function Name : drawScroll(int x, int y, int w, int p , int pa)
* Description : 크 처 獨
* element	:  x= y= w= p= , pa= 
* return	:  
* Date	:  03/06 
* Modified	:	    
* author	:  Seongjin Bae	
* ------------------------------------------------------ */

int cGame::drawScrollY(int h, int p , int pa){ //

	////////////////////////////
	int fw = (h)/p;		
	if(fw*p < h){
		//fw += 1;//(((h-20)-(fw*p))/p);
		fw += (((h)-(fw*p))/p);
	} 	
	return fw;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////
// result popup
///////////////////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------------------------------
* Function Name : draw_result_popup(int kind)
* Description : drawing popup box 
* element	:  kind= popup state(define)
* return	:  
* Date	:  11/15 
* Modified	:	    
* author	:  Seongjin Bae	
* ------------------------------------------------------ */
//#define POPUP_KIND_MARKET						0
//#define POPUP_KIND_PRESENT						1
//#define POPUP_KIND_SEED							2
//#define POPUP_KIND_MENU							3
//#define POPUP_KIND_TALK							4
//#define POPUP_KIND_RESULT_MISSION				5
//#define POPUP_KIND_RESULT						6
//#define POPUP_KIND_FUND							7

void cGame::draw_result_popup(int kind , int select_index, int item_max_index)//int x, int y, int w, int h)
{
}




void cGame::selectBox(int x, int y, int w, int h)
{
//	PopUp_Sprite->PaintModule(g, RESULT_POPUP_SEL01_MOD_INDEX, x, y , 0);
//	PopUp_Sprite->PaintModule(g, RESULT_POPUP_SEL02_MOD_INDEX, x + w - 9, y , 0);
//	PopUp_Sprite->PaintModule(g, RESULT_POPUP_SEL03_MOD_INDEX, x, y + h - 9 , 0);
//	PopUp_Sprite->PaintModule(g, RESULT_POPUP_SEL04_MOD_INDEX, x + w - 9, y + h - 9 , 0);	

}


void cGame::fillRoundRect( int iX_, int iY_, int iWidth_, int iHeight_ )
{
	//g->FillRect( iX_ + 1, iY_ + 1, 1, iHeight_ - 2 );
	//g->FillRect( iX_ + 2, iY_, iWidth_ - 2, 1 );
	//g->FillRect( iX_ + iWidth_, iY_ + 1, 1, iHeight_ - 2);
	//g->FillRect( iX_ + 2, iY_ + iHeight_ - 1, iWidth_ - 2, 1);

	g->FillRect( iX_ + 1, iY_ + 1, iWidth_, iHeight_ - 2);
	g->FillRect( iX_ + 2, iY_, iWidth_ - 2, iHeight_);
}




void cGame::goto_map( int _state )
{
	switch( _state )
	{
	case STATE_DRAW_OPENNING:

		pushState(STATE_DRAW_OPENNING,true);
		break;

	case STATE_DRAW_HOUSE:

		m_map_kind = HOUSE_MYHOME;			
		pushState(STATE_DRAW_HOUSE,true);			
	//	hero_mosX = 139*TILE_W/20;
	//	hero_mosY = 150*TILE_H/20;
		break;

	case STATE_DRAW_MAP1:

		m_map_kind = WORLD_MAP1;			
		pushState(STATE_DRAW_MAP1,true);			
	//	hero_mosX = 139*TILE_W/20;
	//	hero_mosY = 150*TILE_H/20;
		break;

	case STATE_DRAW_CHAPTER:
		m_map_kind = CHAPTER_1;			
		pushState(STATE_DRAW_CHAPTER,true);		
		break;
	}	

//	GAME_PAUSE_OFF();
}





//========================================================

///	init_popup () :: INITIALIZE POPUP ANIMATION 

//========================================================

//void cGame::init_popup( )
//{
//	//	if ( !ResultPop_Sprite->IsAnimationDone(0) )
//	//	{
//	ResultPop_Sprite->SetCurrentAnimation( 0,RESULT_POPUP_OK_ANI_INDEX, true );
//	//	}
//
//}

#ifndef USE_DRAWRGB_FOR_TILES

void cGame::addMapSprite(ASprite* sp)
{
	mapSprites[mapSprites_len++] = sp;
}

void cGame::resetMapSprite()
{
	for(int i=0; i<mapSprites_len; i++)
	{
		SAFE_DEL(mapSprites[i]);
	}
	mapSprites_len = 0;
}

#endif



void cGame::draw_round_rect(int x, int y, int w, int h , int color, int color1)
{
	g->SetColor(color);//g->SetColor(0xffffff);
	g->FillRect(x+1,y+1,w-2,h-2);

	g->SetColor(color1);//g->SetColor(0x56502A);
	g->DrawLine(x+2,y,x+w-3,y);
	g->DrawLine(x+2,y+h-1,x+w-3,y+h-1);
	g->DrawLine(x,y+2,x,y+h-3);
	g->DrawLine(x+w-1,y+2,x+w-1,y+h-3);

	g->FillRect(x+1,y+1,1,1);
	g->FillRect(x+1,y+h-2,1,1);
	g->FillRect(x+w-2,y+1,1,1);
	g->FillRect(x+w-2,y+h-2,1,1);

}



char* cGame::getSoundName(int soundID)
{

	char* name = NULL ;

	//switch(soundID)
	//{

	//	//case BG_MAP_SOUND_01:				name = "bg_map_sound_01.mmf";				break;
	//	case BG_MAP_SOUND_02:				name = "bg_map_sound_02.mmf";				break;
	//	//case BG_MAP_SOUND_03:				name = "bg_map_sound_03.mmf";				break;

	//	//case EFFECT_CLOCK:					name = "effect_clock.mmf";					break;
	//	//case EFFECT_DOG_DAMAGE_01:			name = "effect_dog_damage_01.mmf";			break;	

	//	//case EFFECT_FARMING_BIRD_01:		name = "effect_farming_bird_01.mmf";			break;
	//	//case EFFECT_FARMING_BIRD_02:		name = "effect_farming_bird_02.mmf";			break;	

	//	//case EFFECT_FARMING_CULTIVATION_01:	name = "effect_farming_cultivation_01.mmf";	break;

	//	//case EFFECT_FARMING_FAIL_01:		name = "effect_farming_fail_01111.mmf";			break;
	//	case EFFECT_FARMING_SUCCESS_01:		name = "effect_farming_success_01.mmf";		break;

	//	//case EFFECT_FARMING_WATER_01:		name = "effect_farming_water_01.mmf";		break;
	//	//case EFFECT_FARMING_WATER_02:		name = "effect_farming_water_02.mmf";		break;
	//	//case EFFECT_FARMING_WORM_01:		name = "effect_farming_worm_01.mmf";			break;
	//	//case EFFECT_FISHING_START_01:		name = "effect_fishing_start_01.mmf";		break;
	//	//case EFFECT_FISHING_VS_01:			name = "effect_fishing_vs_01.mmf";			break;

	//	//case EFFECT_PUZZLE_BOOM:			name = "effect_puzzle_boom.mmf";				break;
	//	//case EFFECT_PUZZLE_DROP:			name = "effect_puzzle_dropAAA.mmf";				break;
	//	//case EFFECT_PUZZLE_SELECT:			name = "effect_puzzle_select.mmf";			break;

	////	case EFFECT_WOOL_01:				name = "effect_wool_01.mmf";					break;
	////	case EFFECT_WOOL_02:				name = "effect_wool_02.mmf";					break;

	//	case EFX_DOG_03:					name = "efx_dog_03.mmf";						break;
	//	case INTRO_SOUND_01:				name = "title.mmf";					break;

	////	case EFFECT_FISHING_FAIL_O1:		name = "effect_farming_fail_01111.mmf";			break;
	////	case EFFECT_FISHING_SUCCESS_O1:		name = "effect_farming_success_01.mmf";		break;

	//}

	return name;


}


/// MULTY SOUND/////////////////////////////////////////////////////////


void cGame::initMultySound(int _Maxsound)
{

	//MultysndBuff = NULL;
	//SAFE_DEL_ARRAY(MultysndBuff);
	//MultysndBuff = GL_NEW byte*[_Maxsound];

}

void cGame::loadMultySound( int _buffnum ,int soundID  )
{

	////try
	//{  	
	//	//InputStream is = getSoundName(soundID).getClass().getResourceAsStream(getSoundName(soundID));
	//	CStream* is = GetResourceManager().GetResourceAsStream(FILE_NAME_SOUNDS);
	//	MultysndBuff[_buffnum] = GL_NEW byte[is.available()]; 
	//	is->Read(MultysndBuff[_buffnum]); 
	//	is->Close(); 
	//	is = NULL;
	//}
	////catch (Exception e){}

}


void cGame::freeMultySound()
{
//
//	for ( int _i = 0 ; _i < MultysndBuff.length ; _i++)
//	{
//		MultysndBuff[_i] = NULL;
//	}
//	MultysndBuff = NULL;
//
//#ifdef KR_WIPI_VERSION
//
//	//if (sndClip != NULL)
//	//      {
//	//          sndClip = NULL;
//	//}
//
//#else
//	if (m_sounds != NULL)
//	{
//		m_sounds = NULL;
//	}
//#endif

}



void cGame::playMultySound(int _buffnum, bool loopflag) //todo
{
	playSound(_buffnum, loopflag);
}
//{
//
//#ifdef HAS_SOUND
//
//
//#ifdef KR_WIPI_VERSION
//
//	// if (m_soundOn)
//	if (m_sndVol > 0 )			
//	{
//		stopSound();
//
//		try{
//			if(cursound != _buffnum){							
//				sndClip = GL_NEW Clip("Yamaha_MA3", MultysndBuff[_buffnum] );				
//			}						
//			sndClip.setVolume(m_sndVol * (100/maxVol)); 
//			Player.play(sndClip, loopflag); 
//			cursound = _buffnum;
//
//		}
//		catch(Exception e){}	
//	}
//	curFlag = loopflag;
//
//#else    	
//
//
//	// if ( !m_soundOn )
//	if (m_sndVol <= 0 )	
//		return;
//	try
//	{           
//		InputStream bis = GL_NEW ByteArrayInputStream(MultysndBuff[_buffnum]);
//		m_sounds = javax.microedition.media.Manager.createPlayer(bis, "audio/x-wav");
//		m_sounds.realize();
//		bis = NULL;           
//	}
//	catch (Exception e){}
//
//	if (m_sounds == NULL || m_sounds.getState() == javax.microedition.media.Player.STARTED)
//		return;
//
//	try
//	{
//		stopSound();			
//		cursound = _buffnum;    
//
//		((javax.microedition.media.control.VolumeControl)
//			(m_sounds.getControl("VolumeControl")))
//			.setLevel(m_sndVol * (100/maxVol) );
//
//		m_sounds.start();
//		Thread.sleep(10);   // maybe this can help for sound problems
//	}
//	catch (Exception e){}
//
//#endif
//
//#endif
//
//}


/// SINGLE SOUND/////////////////////////////////////////////////////////


void cGame::freeSound()
{


//#ifdef KR_WIPI_VERSION
//
//	//if (sndClip != NULL)
//	//      {
//	//          sndClip = NULL;
//	//}
//
//#else
//	if (m_sounds != NULL)
//	{
//		m_sounds = NULL;
//	}
//#endif
}


void cGame::Sound_Load()
{
	if(m_sound->m_pData[0]) return;
	for(int i=0; i<25; i++) {
		if(i==6 || i == 23) continue;
		char* name = getSoundName(i);
		char fileName[64];
		MEMSET(fileName, 0, 64);
		SPRINTF(fileName, "/%s", name);	//hw#
		CStream *stream = GetResourceManager().GetResourceAsStream(fileName);

		m_sound->m_pDataSize[i] = stream->GetLength();
		m_sound->m_pData[i] = GL_NEW/*(memType) */unsigned char[m_sound->m_pDataSize[i]];

		if(m_sound->m_pData[i])
			stream->Read(m_sound->m_pData[i], m_sound->m_pDataSize[i]);

		SAFE_DELETE(stream);
	}

	int len = 0;
	for(int i=0; i < 23; i++) {
		len += m_sound->m_pDataSize[i];
	}
}


void cGame::playSound(int soundID, bool loopflag)
{
//	if(g_pGame->m_sndVol == 0) return;
	char* name = getSoundName(soundID);
	if(name == NULL) {
		return;
	}
	m_sound->PlaySound(soundID, true, loopflag);
}


void cGame::stopSound() 
{
	//GetSound().StopSound();
	m_sound->StopSound();
//#ifdef HAS_SOUND
//
//#ifdef KR_WIPI_VERSION
//
//	if (sndClip != NULL) {
//		try{		
//			Player.stop(sndClip);				 		 
//		}catch(Exception e){}					
//	}         
//#else
//
//	if (cursound ==-1|| m_sounds == NULL )
//	{
//		return;
//	}
//
//	if ( m_sounds != NULL )
//	{
//		//try{
//
//			if (m_sounds.getState() == javax.microedition.media.Player.STARTED)
//			{
//				m_sounds.stop();
//			}
//			//			m_sounds.close();
//			//			m_sounds = NULL;
//			//			m_sounds.deallocate();
//		//}catch(Exception e){}		
//	}
//#endif 
//#endif 
}



void cGame::setVib(int time)
{
	if( g_pGame->m_vibrateOn != 1 )
		return;
	MC_mdaVibrator(1, time);
	//(GetSound()).Vibrate(time);  --sj 임시
}



//add by Robust.
void cGame::setVolSideKey( int off )
{
#ifdef HAS_SOUND
	int _vol = m_sndVol + off;
	//m_sndVol = _vol % (maxVol+1) ; 
	if(off>0 && _vol>maxVol)
	{
		_vol = maxVol;
	}else if(off<0 && _vol<0){
		_vol = 0;
	}

	m_sndVol = _vol;
	m_sound->m_nVolume = _vol*10;

	//MC_mdaClipSetVolume(((CMediaPlayer*)m_sound)->m_pMediaPlayer, m_sound->m_nVolume);
	m_sound->SetVolume( m_sound->m_nVolume);
	
	if( game_currentState > STATE_SELECTSOUND && m_sound->m_curSound == -1)
	{
		//g_pGame->setVol( EFX_DOG_03 ,_vol);
	}
	if (game_currentState > STATE_SELECTSOUND)
	{
		SetRecordDataByte(record_buffData, RECORD_SOUND , /**/_vol );
		g_pGame->SaveLoadRecord(true);
	}	
	/*
	if ( s_cUI->menu_cur_cursor == MENU_STATE_OPTION || (s_cUI->menu_cur_cursor == MENU_STATE_START && m_game_pause == true))//fixed a bug 	1452013
	{
		if( s_cUI->menu_Pointer == 0 || s_cUI->menu_Pointer == 1 || s_cUI->menu_Pointer == 2)
		{
			g_pGame->setVol( EFX_DOG_03 ,_vol);					
		}
	}
	*/
#endif 
}

void cGame::setVol( int cursound ,  int _vol)
{
#ifdef HAS_SOUND
	if( _vol < 0 )
	{
		_vol = maxVol;
	}
	m_sndVol = _vol % (maxVol+1) ; 


//	m_sound->m_nVolume = _vol*10;
	m_sound->m_nVolume = m_sndVol*10;



	if(m_sndVol == 0)
	{
		stopSound();
	}else
	{

		playSound(cursound, false);
	}
#endif 
}


void cGame::changeVolume(int diff)
{
#ifdef HAS_SOUND
#ifdef KR_WIPI_VERSION

	m_sndVol = (m_sndVol+diff);//%(maxVol+1);	

	if ( m_sndVol < 0 )
	{
		m_sndVol = 0;
	}
	else if ( m_sndVol > maxVol )
	{
		m_sndVol = maxVol;
	}

	if(m_sndVol != 0)
	{
		if ( sndClip != NULL) 
		{
			sndClip.setVolume(m_sndVol * (100/maxVol) );
		}
	}
#endif
#endif 

}



void cGame::softkey_init(int leftText, int rightText, int centerText)
{
	softkey_leftText = leftText;
	softkey_rightText = rightText;
	softkey_centerText = centerText;
	softkey_currentSelection = SOFTKEY_NONE;


}

void cGame::softkey_init(int leftText, int rightText)
{

	softkey_leftText = leftText;
	softkey_rightText = rightText;
	softkey_centerText = 0;
	softkey_currentSelection = SOFTKEY_NONE;

}


int cGame::softkey_getCurrentSelection()
{
	return softkey_currentSelection;
}

byte cGame::softkey_update()
{
	if(ANY_KEY_PRESSED())
	{

#ifdef REVERSE_SOFTKEY 			

		if(KEY_PRESSED(GAME_KEY_SOFTKEY_LEFT))
		{
			softkey_currentSelection = SOFTKEY_RIGHT;
			return SOFTKEY_RIGHT;
		}
		else if(KEY_PRESSED(GAME_KEY_SOFTKEY_RIGHT))
		{
			softkey_currentSelection = SOFTKEY_LEFT;
			return SOFTKEY_LEFT;
		}

#else	

		if(KEY_PRESSED(GAME_KEY_SOFTKEY_LEFT))
		{
			softkey_currentSelection = SOFTKEY_LEFT;
			return SOFTKEY_LEFT;
		}
		else if(KEY_PRESSED(GAME_KEY_SOFTKEY_RIGHT))
		{
			softkey_currentSelection = SOFTKEY_RIGHT;
			return SOFTKEY_RIGHT;
		}

#endif
	}

	softkey_currentSelection = SOFTKEY_NONE;

	return SOFTKEY_NONE;
}



void cGame::softkey_paint(bool isFromNet)
{
	int upoffset=0;

	if(softkey_leftText > SOFTKEY_SYMBOL_EMPTY)
	{
#ifdef REVERSE_SOFTKEY
		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_leftText - 1, SCREEN_WIDTH - 1 - SOFTKEY_DISTANCE_FROM_CORNER - SOFTKEY_BACK_FRM_WIDTH, SOFTKEY_LEFT_POS_Y, 0, 0, 0);
#else		
		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_leftText - 1, SOFTKEY_DISTANCE_FROM_CORNER, SOFTKEY_LEFT_POS_Y, 0, 0, 0);
#endif
	}
//
//
	if(softkey_rightText > SOFTKEY_SYMBOL_EMPTY)	
	{
#ifdef REVERSE_SOFTKEY
		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_rightText - 1, SOFTKEY_DISTANCE_FROM_CORNER, SOFTKEY_RIGHT_POS_Y, 0, 0, 0);
#else
		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_rightText - 1, SOFTKEY_RIGHT_POS_X, SOFTKEY_RIGHT_POS_Y, 0, 0, 0);
#endif
	}


//	if(softkey_centerText == SOFTKEY_SYMBOL_EZI)
//	{
//#ifdef REVERSE_SOFTKEY
//		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_rightText - 1, SOFTKEY_DISTANCE_FROM_CORNER, SOFTKEY_RIGHT_POS_Y, 0, 0, 0);
//#else
//		SPRITE_PAINT_FRAME(COMMON_SPRITE_SOFTKEY, g, -softkey_centerText, SCREEN_HALF_WIDTH, SCREEN_HEIGHT, 0, 0, 0);
//#endif
//	}

}





void cGame::ResetRecord( StoreType _type )
{
	if( (_type & STORE_OPTION) == STORE_OPTION )
	{
		m_dataslot = STORE_OPTION;

		SetRecordDataByte(record_buffData,RECORD_SOUND,2);
		SetRecordDataByte(record_buffData,RECORD_SPEED,0);
		SetRecordDataByte(record_buffData,RECORD_VIBRATION,1);
		SetRecordDataByte(record_buffData,RECORD_SAVE1,0);
		
		SaveLoadRecord( true ) ;
	}
	
	if( (_type & STORE_SLOT1) == STORE_SLOT1 )
	{
		m_dataslot = STORE_SLOT1;
		//        SetRecordPlayerName(RECORD_USERINFO_NAME, "Game" );
		//SetRecordDataByte(RECORD_USERINFO_NAMEINDEX, 0 );
		//SetRecordDataShort(RECORD_USERINFO_LAST_YEAR,INIT_YEAR);
		//SetRecordDataByte(RECORD_USERINFO_LAST_MONTH,INIT_MONTH);
		//SetRecordDataByte(RECORD_USERINFO_LAST_DAY,INIT_DAY);
		//SetRecordDataByte(RECORD_USERINFO_LAST_WEEK,INIT_DAY);

		//SetRecordDataLong(RECORD_USERINFO_LAST_TIME,0);

		//SetRecordDataByte(RECORD_USERINFO_FIRST_DAY,INIT_DAY);
		//SetRecordDataByte(RECORD_USERINFO_PLUS_DAY,INIT_DAY);

		//SetRecordDataInt(RECORD_USERINFO_COIN,10000);
		//SetRecordDataInt(RECORD_USERINFO_LOANCOIN,5000000);
		//SetRecordDataInt(RECORD_USERINFO_MONTHLOANCOIN,100000);
		//SetRecordDataInt(RECORD_USERINFO_BANKCOIN,0);	
		//SetRecordDataByte(RECORD_USERINFO_LOANCOUNT,0);

		//SetRecordDataByte(RECORD_USERINFO_REPLAY,0);
		//SetRecordDataByte(RECORD_USERINFO_FARMLEVEL,0);
		//SetRecordDataByte(RECORD_USERINFO_PUZZLELEVEL,0);
		//SetRecordDataInt(RECORD_USERINFO_PUZZLERECORD,0);

		//SetRecordDataByte(RECORD_USERINFO_WOOLLEVEL,0);
		//SetRecordDataByte( RECORD_USERINFO_M_FISH_LEVEL,-5);
		//SetRecordDataByte( RECORD_USERINFO_BREEDING_LEVEL,0);

		//SetRecordDataInt(RECORD_USERINFO_OPENING_TUTORAIL,80);
		//SetRecordDataInt(RECORD_USERINFO_HP,CHARACTER_HPMAX);
		//SetRecordDataByte(RECORD_USERINFO_MP,100);	

		//SetRecordDataByte(RECORD_USERINFO_ITEM_INSECTICIDE,0);
		//SetRecordDataByte(RECORD_USERINFO_ITEM_SCARECROW,0);

	//	reset_Inven_Item();
	//	SetRecordItem(RECORD_USERINFO_ITEM);
	//	SetRecordLove(RECORD_USERINFO_CHAR_LOVE);
	//	SetRecordMail(RECORD_USERINFO_MAIL);
	//	SetRecordQuest(RECORD_USERINFO_QUEST);

		SaveLoadRecord( true ) ;
	}
	
	if( (_type & STORE_SLOT2) == STORE_SLOT2 )
	{
		m_dataslot = STORE_SLOT2;

		SaveLoadRecord( true ) ;
	}
}



void cGame::Save_AllGame( StoreType _type )
{

}



void cGame::SetStoreType(StoreType _type)
{
	m_dataslot = _type; 
}

StoreType cGame::GetStoreType()
{

	return m_dataslot;
}

#ifdef USE_CHECKSPACE

void cGame::CheckSpace(const char* dataBaseName, bool &canLoad, bool &canSave, int size , bool remove)
{
	CFileStream fs;

	canLoad = canSave = false;
	if ( !fs.Open( dataBaseName, CRawFile::MODE_READ )) //create file
	{		
		// file not exist,create it
		if ( fs.Open( dataBaseName, CRawFile::MODE_CREATE ) )
		{
			// write enough data to take place			
			char *buf = GL_NEW char[size];
			MEMSET(buf, 0, size);		
			int write = fs.Write(buf, size);
			fs.Close();

			if( write == size )
			{	
				canSave = true;
				if( fs.Open( dataBaseName, CRawFile::MODE_READ ) )
				{
					int readByte = 0;
					if (fs.SetPosition(0))
						readByte = fs.Read(buf, size);
					fs.Close();

					if( readByte == size )
					{
						canLoad = true;		
					}
					//if (SaveLoadRecord(true))//write
					//{
					//	canLoad = canSave = true;
					//}
				}							
			}

			if( !(canLoad && canSave ) )
			{
				GetDevice().RemoveFile(dataBaseName);
			}

			SAFE_DEL_ARRAY(buf);
		}
	}
	else
	{
		// file exist,ok
		char *bufs = GL_NEW char[size];
		int readByte = 0;
		if (fs.SetPosition(0))
			readByte = fs.Read(bufs, size);
		SAFE_DEL_ARRAY(bufs);
		fs.Close();

		if( readByte != size ) 
		{
			GetDevice().RemoveFile(dataBaseName);
			
			//GetDevice().m_fileMgr;
			if ( fs.Open( dataBaseName, CRawFile::MODE_CREATE ) )
			{
				char *buf = GL_NEW char[size];
				MEMSET(buf, 0, size);
				int write = fs.Write(buf, size);
				SAFE_DEL_ARRAY(buf);
			}
			fs.Close();
			//return;
		}

		canLoad = true;
		canSave = true;//SaveLoadRecord(true);//write
	}
	
	if(remove)
	{
		GetDevice().RemoveFile(dataBaseName);
	}
	
}

void cGame::UpdateNoSpace()
{
//	CleanBackground( 0 );
//
//	char* tmpStr = GL_NEW(POOL_BOTTOM) char[256];
//	STRCPY(tmpStr, STR_NO_SAVE_SPACE);
//
//	s_sprFont->DrawPage(s_g, tmpStr, DEF::SCREEN_WIDTH >> 1, DEF::SCREEN_HEIGHT>>1, CGraphics::HCENTER | CGraphics::VCENTER, DEF::CHAR_NUM_NORMAL, 0, -1);
//	//s_sprFont->DrawPage(s_g , tmpStr, DEF::SCREEN_WIDTH >> 1 , (DEF::SCREEN_HEIGHT>>1)  , CGraphics::HCENTER | CGraphics::VCENTER);
//	SAFE_DELETE(tmpStr);
//
//	DrawSelectOption(GetString(DATA::TEXT_MENU, TEXT::STR_MENU_EXIT_NO),
//		GetString(DATA::TEXT_MENU, TEXT::STR_MENU_EXIT_YES));
//
//	if( IsKeyPressed( STATE::GK_BACK ) )
//	{
//		s_gameState = STATE::EXIT;
//	}
//#ifdef USE_QWERTY//FOR BUG 1670014
//	else if ( IsKeyPressed( STATE::GK_CONFIRM) )
//#else
//	else if ( IsKeyPressed( STATE::GK_SELECT) )
//#endif
//	{
//		// Play game without saving
//		SetGameState( STATE::SOUND );
//	}
}
#endif//USE_CHECKSPACE




bool cGame::SaveLoad_MapRecord(int _mapindex, bool save )
{
	if (s_bSaveMode == false)
		return false;

	const char* pName;
	CFileStream rs;
	int processByte = 0;

	int _size = 0;
	int _offset = 0;

	byte* temp_buffData;

	temp_buffData = record_mapUserData;

	_size = MAP_ONE_SIZE;

	switch (_mapindex)
	{
		case 0: pName = RECORD_MAP_FILENAME1;	break;
		case 1: pName = RECORD_MAP_FILENAME2;	break;
		case 2: pName = RECORD_MAP_FILENAME3;	break;
		case 3: pName = RECORD_MAP_FILENAME4;	break;
		case 4: pName = RECORD_MAP_FILENAME5;	break;
	}	

	if (save)
	{
		if (rs.Open( pName, CRawFile::MODE_WRITE))
		{
			rs.Skip(_offset);
			processByte = rs.Write(temp_buffData, _size);
			rs.Close();
			if (processByte != _size)
				return false;

			return true;			
		}
	}
	else
	{
		if (rs.Open( pName, CRawFile::MODE_READ))
		{
			rs.Skip(_offset);
			processByte = rs.Read(temp_buffData, _size);
			rs.Close();
			if (processByte != _size)
				return false;
			
			return true;
		}
	}
	return false;
}


void cGame::Get_UserMapRecord(int _mapindex  ) 
{
	SaveLoad_MapRecord( _mapindex, false );


//	SaveLoad_MapRecord( _mapindex, false ) ;
	m_actorsNew_count = GetRecord_BigEndianShort(record_mapUserData,0);

//	m_actorsNew_count = GetRecordDataShort(record_mapUserData,0);

	//for( int _i = 0 ; _i< MAP_MAX_ENTITY ; _i++ )

	for( int _i = 0 ; _i< m_actorsNew_count ; _i++ )
	{
		for( int _j = 0 ; _j< MAP_MAX_DATA ; _j++ )
		{
			mapUser_Data[_i][_j] = GetRecord_BigEndianShort( record_mapUserData, (((MAP_MAX_DATA*2)*(_i))+(_j*2))+2 );
		}
	}

	for( int _j = 0 ; _j< m_actorsNew_count ; _j++ )
	{
		Add_UserEntity( mapUser_Data[_j],false ) ;
	}
}


void cGame::Set_UserMapRecord( int _count, int _index, short* _data, boolean _save )
{

//	SaveLoad_MapRecord( _mapindex, false ) ;
	if ( _save )
	{
		m_actorsNew_count = (short)_count;

		for( int _j = 0 ; _j< MAP_MAX_DATA ; _j++ )
		{
			mapUser_Data[_index][_j] = _data[_j];
		}

		SetRecord_BigEndianShort(record_mapUserData, 0, (short)m_actorsNew_count );

		for( int _j = 0 ; _j< MAP_MAX_DATA ; _j++ )
		{
			SetRecord_BigEndianShort(record_mapUserData, (((MAP_MAX_DATA*2)*(_index))+(_j*2))+2 , mapUser_Data[_index][_j] );
		}

		SaveLoad_MapRecord( 0 , true );
	}
}








void cGame::Add_UserEntity(short* params, boolean _save) 
{

	if( m_actorsNew_count < MAP_MAX_ENTITY )
	{
		SAFE_DEL( getEntity(m_actorsMax_count));
		getEntity(m_actorsMax_count) = GL_NEW cEntity( params[ACTOR_GTSID], 1 );
		getEntity(m_actorsMax_count++)->init(params[ACTOR_FLAGS], params[ACTOR_POSX], params[ACTOR_POSY], params, ACTOR_MAPOBJECT_MAX);

		if ( _save )
		{
			m_actorsNew_count++ ;
			Set_UserMapRecord( m_actorsNew_count, m_actorsNew_count-1, params, _save ) ;
		}
	}

}




bool cGame::SaveLoadRecord(bool save )  
{
	//0 option
	//1	slot1
	//2 slot2
	//3 slot3
	if (s_bSaveMode == false)
		return false;

	CFileStream rs;
	int processByte = 0;

	int _size = 0;
	int _offset = 0;

	byte* temp_buffData;
	temp_buffData = record_buffData;
	if(m_dataslot == STORE_OPTION)
	{
		_size = RECORD_OPTION_SIZE;
		_offset = 0;
	}
	else if(m_dataslot >= STORE_SLOT1)
	{
		_offset = RECORD_OPTION_SIZE + (RECORD_USERINFO_SIZE * (m_dataslot - 1) );
		_size = RECORD_USERINFO_SIZE ;
		temp_buffData += RECORD_OPTION_SIZE;
	}

	
	if (save)
	{
		if (rs.Open(RECORD_FILENAME, CRawFile::MODE_WRITE))
		{
			rs.Skip(_offset);
			processByte = rs.Write(temp_buffData, _size);
			rs.Close();
			if (processByte != _size)
				return false;

			return true;
			
		}
	}
	else
	{
		if (rs.Open(RECORD_FILENAME, CRawFile::MODE_READ))
		{
			rs.Skip(_offset);
			processByte = rs.Read(temp_buffData, _size);
			rs.Close();
			if (processByte != _size)
				return false;
			
			return true;
		}
	}

	return false;
}




void cGame::SetRecordDataByte(byte* buffData, int index, int value  )
{	
	buffData[index++] = (byte)value;
}

char cGame::GetRecordDataByte(byte* buffData, int index)
{
	return (char)buffData[index];
}

void cGame::SetRecordDataShort(byte* buffData,int index, int value)
{
	buffData[index++] = (byte)(value & 0x000000FF);
	buffData[index++] = (byte)((value>>8) & 0x000000FF);
}

short cGame::GetRecordDataShort(byte* buffData,int index)
{	
	return (SHORT_TYPE)((buffData[index++] & 0x000000FF) | ((buffData[index++] & 0x000000FF) << 8));
}

void cGame::SetRecord_BigEndianShort(byte* buffData,int index, int value)
{
	buffData[index] = (byte)((value>>8) & 0x000000FF);
	buffData[index+1] = (byte)(value & 0x000000FF);
}

short cGame::GetRecord_BigEndianShort(byte* buffData,int index)
{
	return (SHORT_TYPE)( ((buffData[index] & 0x000000FF)<<8) | (buffData[index+1] & 0x000000FF));
}


void cGame::SetRecordDataInt(byte* buffData, int index, int  value)
{	
	buffData[index++] = (byte)(value & 0x000000FF);
	buffData[index++] = (byte)((value>>8) & 0x000000FF);
	buffData[index++] = (byte)((value>>16) & 0x000000FF);
	buffData[index++] = (byte)((value>>24) & 0x000000FF);
}

int cGame::GetRecordDataInt(byte* buffData, int index)
{	
	return (buffData[index++] & 0x000000FF) |
		((buffData[index++] & 0x000000FF) << 8) |
		((buffData[index++] & 0x000000FF) << 16) |
		((buffData[index++] & 0x000000FF) << 24);
}

void cGame::SetRecordDataLong(byte* buffData, int index, M_Int64 value)
{	
	buffData[index++] = (byte)(value & 0x000000FF);
	buffData[index++] = (byte)((value>>8) & 0x000000FF);
	buffData[index++] = (byte)((value>>16) & 0x000000FF);
	buffData[index++] = (byte)((value>>24) & 0x000000FF);
	buffData[index++] = (byte)((value>>36) & 0x000000FF);
	buffData[index++] = (byte)((value>>48) & 0x000000FF);
}

M_Int64 cGame::GetRecordDataLong(byte* buffData, int index)
{	
	return (buffData[index++] & 0x000000FF) |
		((buffData[index++] & 0x000000FF) << 8) |
		((buffData[index++] & 0x000000FF) << 16) |
		((buffData[index++] & 0x000000FF) << 24)|
		((buffData[index++] & 0x000000FF) << 36)|
		((buffData[index++] & 0x000000FF) << 48);

}

int cGame::SetRecordDataArray(int dst_off, char* src ,int src_length)
{		
	arraycopy(src, 0, (char*)record_buffData, dst_off, src_length);

	return dst_off + src_length;
}

int cGame::GetRecordDataArray(int src_off, char* dst, int dst_length)
{	
	arraycopy((char*)record_buffData, src_off,  dst, 0, dst_length);

	return src_off + dst_length;
}




int cGame::get_Quest_EntityToNpc(int _index)
{
	int temp = -32;
	//switch(_index)
	//{
	//case ENTITY::k_chief:
	//	temp = NPC::NPC_TC_1;
	//	break;
	//case ENTITY::k_breeding_man:
	//	temp = NPC::NPC_TC_2;
	//	break;
	//case ENTITY::k_fisherman:
	//	temp = NPC::NPC_TC_3;
	//	break;
	//case ENTITY::k_flower_mother:
	//	temp = NPC::NPC_TC_4;
	//	break;
	//case ENTITY::k_restaurant_man:
	//	temp = NPC::NPC_TC_5;
	//	break;
	//case ENTITY::k_car_man:
	//	temp = NPC::NPC_TC_6;
	//	break;
	//case ENTITY::k_wood_man:
	//	temp = NPC::NPC_TC_7;
	//	break;

	//	////////////////////////////

	//case ENTITY::k_restaurant_daughter:
	//	temp = 7;
	//	break;
	//case ENTITY::k_car_daughter:
	//	temp = 8;
	//	break;
	//case ENTITY::k_animal_man:
	//	temp = 9;
	//	break;
	//case ENTITY::k_chief_daughter:
	//	temp = 10;
	//	break;
	//case ENTITY::k_flower_daughter:
	//	temp = 11;
	//	break;
	//case ENTITY::k_factory_man:
	//	temp = 12;
	//	break;
	//}


	return temp;
}


int cGame::random(int a, int b)//a에서 b까지
{
	int rnd;
	if (b != a)
	{
		rnd = s_math_random_nextInt();
		if (rnd < 0)
		{
			rnd *= -1;
		}
		return (a+(rnd%((b+1)-a)));
	}
	return b;
}


int cGame::random()
{
	return s_math_random_nextInt();
}



int cGame::except_random( int _a, int _b, int _expt )
{
	if ( _a > _expt || _b < _expt )
	{
		return 0;
	}

	int _count = 0;
	int _select = 0;
	int _Maxcount = (_b-_a);
	int* _random = GL_NEW int[_Maxcount];
	int _return = 0;
	
	for ( int _i = _a;  _i <= _b; _i++ )
	{
		if ( _i != _expt )
		{
			_random[_count] = _i; 
			_count++;
		}
	}

	_select = random(0, _Maxcount-1);

	_return = _random[_select];

	SAFE_DELETE_ARRAY(_random);

	return _return;
}



int cGame::abs( int _number )
{

	if ( _number < 0)
	{
		_number *= -1; 
	}
	return _number;

}

int cGame::smallValue(int _index)
{
	if(_index < 0)
	{
		_index = 0;
	}
	return _index;
}
int cGame::bigValue(int _index)
{
	if(_index > 1)
	{
		_index = 1;
	}
	return _index;
}


CImage* cGame::create_Image ( char* _str )
{	
	CImage*	_imgbuf = NULL;

	//try
	//{
	_imgbuf = CImage::CreateImage(_str);
	//}catch(Exception e){}

	return _imgbuf;

}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// MATH
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/// fixed point value for number 1
//static final int s_math_F_1		= 1 << 8;//Build.k_math_fixedPointBase;
/// fixed point value for number 0.5
//static final int s_math_F_05	= (s_math_F_1>>1);

/// random number generator
//static java.util.Random s_math_random;

//static int s_math_cosTable[];
//static int s_math_tanTable[];
//static int s_math_sqrtTable[];

//--------------------------------------------------------------------------
/// @brief init all math arrays
///
/// @param packName name of the pack witch contains math table
/// @param cos index of cosine table in the pack, -1 if no table -> all call to Math_cos will fail
/// @param tan index of tan table in the pack, -1 if no table -> all call to math_tan will fail
/// @param sqrt index of sqrt table in the pack, -1 if no table -> all call to Math_sqrt will fail
/// @returns true if everything went smoothly :)
//--------------------------------------------------------------------------
void cGame::Math_init (char* packName, int _cos, int _tan, int _sqrt)
{
	int i;
	Data_init(packName);

	if (_cos >= 0)
	{
		Data_open(_cos);
		if(s_math_cosTable == NULL)
			NEW(s_math_cosTable, int[256]);
		for (i=0; i< 256; i++)
		{
			s_math_cosTable[i] = Math_fixedPointAdjust( Data_readS32() );
		}
		Data_close();
	}

	if (_tan >= 0)
	{
		Data_open(_tan);
		if(s_math_tanTable == NULL)
			NEW(s_math_tanTable, int[256]);
		for (i=0; i< 256; i++)
		{
			s_math_tanTable[i] = Math_fixedPointAdjust( Data_readS32() );
		}
		Data_close();
	}

	if (_sqrt >= 0)
	{
		Data_open(_sqrt);
		NEW(s_math_sqrtTable, int[256]);
		for (i=0; i< 256; i++)
		{
			s_math_sqrtTable[i] = Data_readS32();
		}
		Data_close();
	}

	Data_free();
}

//--------------------------------------------------------------------------
/// free all math array
//--------------------------------------------------------------------------
void cGame::Math_quit ()
{
	DELETE(s_math_cosTable);
	DELETE(s_math_tanTable);
	DELETE(s_math_sqrtTable);
	//		DELETE(s_math_random);
}


//--------------------------------------------------------------------------
/// adjust a fixed point in base 8 to this fixed point base
//--------------------------------------------------------------------------
int cGame::Math_fixedPointAdjust (int a)
{
	//if (Build.k_math_fixedPointBase > 8)
	//{
	//	return a << (Build.k_math_fixedPointBase - 8);
	//}
	//else if (Build.k_math_fixedPointBase < 8)
	//{
	//	return a >> (8 - Build.k_math_fixedPointBase);
	//}
	//else
	//{
	return a;
	//}
}

//--------------------------------------------------------------------------
/// convert a fixed point value to an int value
//--------------------------------------------------------------------------
//#define Math_intToFixedPoint(a)		((a) << 8)//Build.k_math_fixedPointBase)
//static int Math_intToFixedPoint (int a)
//{
//	return a << Build.k_math_fixedPointBase;
//}

//--------------------------------------------------------------------------
/// convert a fixed point value to an int value
//--------------------------------------------------------------------------
int cGame::Math_fixedPointToInt (int a)
{
	return ((a + (s_math_F_1 / 2)) >> 8);//Build.k_math_fixedPointBase);
	//return (a >> Game.k_math_fixedPointBase);	// this one is faster but less accurate than the previous one
}


//--------------------------------------------------------------------------
/// true if 2 number have the same sign
//--------------------------------------------------------------------------
//#define Math_SameSign(a, b)				((a ^ b) > 0)
//static bool Math_SameSign (int a, int b)
//{
//	return ((a ^ b) > 0);
//}

//--------------------------------------------------------------------------
/// determinant of 2 2Dvector
//--------------------------------------------------------------------------
int cGame::Math_det (int x1, int y1, int x2, int y2)
{
	return ((x1 * y2) - (y1 * x2));
}

//--------------------------------------------------------------------------
/// dot product of 2 2D vector
//--------------------------------------------------------------------------
int cGame::Math_dotProduct (int x1, int y1, int x2, int y2)
{
	return ((x1 * x2) + (y1 * y2));
}

//--------------------------------------------------------------------------
/// pow of the norm of a vector
//--------------------------------------------------------------------------
#define Math_normPow(x1, y1)		((x1 * x1) + (y1 * y1))
//static int Math_normPow (int x1, int y1)
//{
//	return x1*x1 + y1*y1;
//}

//--------------------------------------------------------------------------
/// @brief norm following newton law approximation
///
/// sqrt(n) is provided by iteration of xk = (xk + n / xk) /2
/// the more iteration (k++), the better is the approximation
/// @param x,y x and y coordinate of vector to get the norm from
/// @param iter nb of iteration to perform -> more iteration gives a better result
///             however more iteration are more cpu intensive
/// @returns norm of vector (x,y)
//--------------------------------------------------------------------------
int cGame::Math_norm (int x, int y, int iter)
{
	int R = Math_normPow(x, y);
	int x_0 = 1;
	for (int i = iter; i != 0; i--)
	{
		// M-O: (x_0 + (R / x_0)) should always give a positive number
		// so a bitshift can be used instead of a division here
		x_0 = (x_0 + (R / x_0)) >> 1; // / 2;
	}
	return x_0;
}



//--------------------------------------------------------------------------
/// return a random int
//--------------------------------------------------------------------------
//static int Math_rand ()
//{
//	return s_math_random_nextInt();
//}

//--------------------------------------------------------------------------
/// sin
/// @param a angle in fixed point 0=0 256=360?
//--------------------------------------------------------------------------
//static int Math_sin (int a)
//{
//	ASSERT(s_math_cosTable != NULL, "!!ERROR!! Math_sin::s_math_cosTable is NULL");
//	return COS(64 - a);
//}

//--------------------------------------------------------------------------
/// cos
/// @param a angle in fixed point 0=0 256=360?
//--------------------------------------------------------------------------
//static int Math_cos (int a)
//{
//	ASSERT(s_math_cosTable != NULL, "!!ERROR!! Math_cos::s_math_cosTable is NULL");
//	return s_math_cosTable[ a & 0xFF ];
//}

//--------------------------------------------------------------------------
/// tan
/// @param a angle in fixed point 0=0 256=360?
//--------------------------------------------------------------------------
int cGame::Math_tan (int a)
{
	//ASSERT(s_math_tanTable != NULL, "!!ERROR!! math_tan::s_math_tanTable is NULL");

	//int tannn = COS(a);
	//if (tannn == 0)
	//{
	//	tannn = 0xFFFFFF;
	//}
	//else
	//{
	//	tannn = Math_intToFixedPoint(SIN(a)) / tannn;
	//}

	return s_math_tanTable[a & 0xFF];
}

//--------------------------------------------------------------------------
/// private function for atan calculation
//--------------------------------------------------------------------------
int cGame::Math_atan (int st, int end, int tang)
{
	// formula in radian
	//(|x|<=1)	atan(x) = x/(1+ 0.28*x^2)
	//(|x| >=1)	atan(x) = pi/2 - x/(x^2 + 0.28) or  pi/2 - atan(1/x)

	//ASSERT(tang >= 0, "Math_atan -> tang is < 0!!!!!");

	if (tang <= 256)
	{
		return st + ((tang << 8) / ((256 * 6) + ((6 * 72 * tang * tang) >> 16)));
	}
	else
	{
		return end - ((tang << 8) / (6 * 72 + ((tang * tang * 6) >> 8)));
	}
}

//--------------------------------------------------------------------------
/// atan
/// -> fastest method (max 2?of imprecision)
/// WARNING : this is not the real atan func as found in common device
/// eg-> it return an angle in [0, 2*PI[ and not in [0, PI/2]
/// @param dx,dy "slope" of the angle
//--------------------------------------------------------------------------
int cGame::Math_atan (int dx, int dy)
{
	if (dx > 0)  								// right
	{
		if (dy > 0) 							// up
		{
			return Math_atan(0, 64, (dy<<8) / dx);
		}
		else if (dy == 0)  						// horizontal
		{
			return 0;
		}
		else 									// down
		{
			return 256 - Math_atan(0, 64, -(dy * 256) / dx);
		}
	}
	else if (dx == 0) 							// vert
	{
		if (dy > 0)  							// up
		{
			return 64;
		}
		else if (dy == 0)  						// horizontal
		{
			return 0;
		}
		else  									// down
		{
			return 192;
		}
	}
	else 										// left
	{
		if (dy > 0)  							// up
		{
			return 128 - Math_atan(0, 64, -(dy<<8) / dx);
		}
		else if (dy == 0)  						// horizontal
		{
			return 128;
		}
		else 									// down
		{
			return Math_atan(128, 192, (dy * 256) / dx);
		}
	}
}

int cGame::Math_log (int index, int iter)
{
	int x = index;

	for (int i = iter; i != 0; i--)
	{		
		x = x >> 1;			
	}
	return x;
}

int cGame::FastDistance(int x, int y)
{
	if (x == 0 && y == 0)
		return 0;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	int m = x > y ? y : x;
	return x + y - (m >> 1) - (m >> 2) + (m >> 3);
}

	// the direction of point(x, y)
	// used in calc arrow path, aim and shoot
	// return value, is the dir to determine frame id
//
//const int TAN_20 = 90; // = tan(20) * 256
//const int TAN_40 = 215; // = tan(40) * 256
//const int TAN_60 = 443; // = tan(60) * 256
//
int cGame::DirTo(int x, int y)
{
	if (x < 0)
		x = -x;
	if (x == 0)
		return y > 0 ? 6 : 0;
	if (y == 0)
		return 3;
	int k = (y << 8) / x; // get the slope
	if (k < 0)
		k = -k;
	if (k <= 90) //TAN_20)
		return 3;
	if (k <= 215) //TAN_40)
		return y > 0 ? 4 : 2;
	if (k <= 443) //TAN_60)
		return y > 0 ? 5 : 1;
	return y > 0 ? 6 : 0;
}






void cGame::Draw_Number( ASprite* _asprite, int _positionx , int _positony  , int _number , int _startmodule , int _direct , int _maxcount , bool _bOneNum , bool _bComma)
{
	int _numbercount = 0;
	int _darwnumber = 0;
	int _buf_number = _number ;
	int _temp_number = 0;
	int _number_gap = 0;
	int _total_gap = 0;
	int _startpositioinx = 0;

	int _textsizex = _asprite->GetModuleWidth(_startmodule);
	if(_bComma)
	{
		_textsizex -= 1;
	}
	// CHECK NUMBER  SIZE 
	while ( _buf_number >= 0 )
	{
		_darwnumber = _buf_number%10;
		if ( _darwnumber == 1)
		{
			_number_gap = _textsizex-2;	
			if(_bOneNum)
			{
				_number_gap = _textsizex-1;
			}
		}else						_number_gap = _textsizex;
		

		_total_gap += (_number_gap);
		_numbercount++;

		_buf_number = (	_buf_number /10 );
		if ( _buf_number == 0 )		_buf_number = -1;
	}

	// DRAW 000000 EMPTY
	if ( _numbercount < _maxcount )
	{
		_total_gap +=  ((_maxcount-_numbercount)*_textsizex);
		_numbercount = _maxcount;		
	}


	// DRAW DIRECT START POSITONX
	if ( _direct == DIRECT_LEFT )
	{
		_startpositioinx = _positionx;
	}
	else if ( _direct == DIRECT_CENTER )
	{
		_startpositioinx = _positionx - (_total_gap>>1);
	}
	else if ( _direct == DIRECT_RIGHT )
	{
		_startpositioinx = _positionx - _total_gap;
	}


	// DRAW NUMBER
	_buf_number = _number ;
	_total_gap = 0;
	for ( int _i = _numbercount ; _i > 0 ; _i-- )
	{
		_temp_number = 1;

		for ( int _j = 0 ; _j < _i-1 ; _j++ )
		{
			_temp_number *= 10;
		}

		_darwnumber = _buf_number/_temp_number;
		if ( _darwnumber == 1)	
		{
			//GuanHao. number "11"
			_number_gap = _textsizex-2; 	
			if(_bOneNum)
			{	
				_number_gap = _textsizex-1;
				_startpositioinx++;
			}
		}

		else _number_gap = _textsizex;

		_asprite->PaintModule( g, _startmodule+_darwnumber , _startpositioinx+(_total_gap), _positony, 0 ) ;		
		_total_gap += _number_gap;
		_buf_number -= (_darwnumber*_temp_number );
		if(_bComma && (_i+2)%3 == 0 && _i > 1)
		{
			//_total_gap -= 1;
//			_asprite->PaintModule( g, MODULE_NUM_COMMA , _startpositioinx+(_total_gap), _positony + 7, 0 ) ;
			_total_gap += 5;
		}

	}
}




void cGame::Draw_GaugeW( int _x , int _y , int _height , int _currentgauge , int _max  ,int _gaugeMax , int _color)
{
	int _gauge = (_currentgauge*_gaugeMax)/_max;

	if( _gauge < 	0 ) 	_gauge = 0;
	else if( _gauge > 	_gaugeMax ) 	_gauge = _gaugeMax;

	g->SetColor(0x000000);
	g->FillRect( _x-2 , _y-1 , _gaugeMax+4 , _height+2 );
	g->FillRect( _x-1 , _y-2 , _gaugeMax+2 , _height+4 );

	g->SetColor( 0xF0F0F0 );//0xFF0000);
	g->FillRect( _x , _y , _gaugeMax , _height );

	g->SetColor(_color);//0xFF0000);
	g->FillRect( _x , _y , _gauge , _height );


}



int cGame::ConstraintToRange(int value, int min, int max)
{
	if(value < min)
	{
		value = min;
	}
	else if(value > max)
	{
		value = max;
	}
	return value;
}


//#define ABS(x)											(((x) < 0) ? -(x) : (x))	
int cGame::getEntityNumber(int index)
{

//	for(int i = 0; i < ENTITY::k_max; i++)
	for(int i = 0; i < g_pGame->m_actorsMax_count; i++)		
	{
		if ( getEntity(i) != NULL && !((getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0))
		{
			if(getEntity(i)->m_type == index)
			{
				return i;
			}
		}
	}

	return -1;

}

int cGame::getEntityGameID(int _gameId)
{	
//	for (int ja = 0; ja < ENTITY::k_max; ja++)
	for (int ja = 0; ja < g_pGame->m_actorsMax_count; ja++)
	{				
		if( getEntity(ja) != NULL && getEntity(ja)->m_gameId == _gameId)
		{
			return ja;			

		}
	}
	return -1;
}



void cGame::pursuit_object(int aimX , int aimY)
{
	int index_pos = 0;

//	int posX = (m_CameraX+SCREEN_HALF_WIDTH);
//	int posY = (m_CameraY+SCREEN_HALF_HEIGHT);

	int posX = (m_mapX+SCREEN_HALF_WIDTH);
	int posY = (m_mapY+SCREEN_HALF_HEIGHT);


	if(IsInCamera(aimX,aimY)) return;

	//if( ABS(  posX - aimX ) > ABS(  posY - aimY ) )
	//{
	//	if(posX > aimX)
	//	{
	//		//LEFT		
	//		//index_pos =  SCREEN_HALF_HEIGHT -  (   ((posY - aimY) * SCREEN_HALF_HEIGHT) / (m_tileMapH*20)  );			 
	//		index_pos = pursuit_index_pos(aimY,m_CameraY,SCREEN_HEIGHT);
	//		if(m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->IsAnimationDone(0)) 
	//			m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->SetCurrentAnimation(0, ARROW_LEFT_ANI_INDEX , true);

	//		m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->PaintAndUpdateCurrentAnimation(g, 0, 0, index_pos, 0, 0, 0);

	//	}
	//	else 
	//	{
	//		//RIGHT
	//		//index_pos =  SCREEN_HALF_HEIGHT -  (   ((posY - aimY) * SCREEN_HALF_HEIGHT) / (m_tileMapH*20)  );
	//		index_pos = pursuit_index_pos(aimY,m_CameraY,SCREEN_HEIGHT);
	//		if(m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->IsAnimationDone(1)) 
	//			m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->SetCurrentAnimation(1, ARROW_RIGHT_ANI_INDEX , true);

	//		m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->PaintAndUpdateCurrentAnimation(g, 1, SCREEN_WIDTH, index_pos, 0, 0, 0);			

	//	}
	//}
	//else 
	//{
	//	if(posY > aimY)
	//	{
	//		// UP				

	//		index_pos = pursuit_index_pos(aimX,m_mapX,SCREEN_WIDTH);

	//		if(m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->IsAnimationDone(2)) 	
	//			m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->SetCurrentAnimation(2, ARROW_UP_ANI_INDEX , true);

	//		m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->PaintAndUpdateCurrentAnimation(g, 2, index_pos, 30, 0, 0, 0);
	//	}
	//	else 
	//	{
	//		//DOWN			
	//		//index_pos =  SCREEN_HALF_WIDTH -  (   ((posX - aimX) * SCREEN_HALF_WIDTH) / (m_tileMapW*20)  );			 

	//		index_pos = pursuit_index_pos(aimX,m_mapX,SCREEN_WIDTH);

	//		if(m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->IsAnimationDone(3)) 
	//			m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->SetCurrentAnimation(3, ARROW_DOWN_ANI_INDEX , true);

	//		m_bSprite[WORLD_SPRITE_ARROW_GLOBAL_INDEX]->PaintAndUpdateCurrentAnimation(g, 3, index_pos, SCREEN_HEIGHT, 0, 0, 0);
	//	}
	//}
}

int cGame::pursuit_index_pos(int index, int _camera, int _screen )
{

	int index_pos = 0;
	int temp = (_screen == SCREEN_WIDTH)? 0 : 30 ;

	if(_camera+13 + temp < index && (_camera+_screen-13) > index)
	{
		index_pos = index - _camera ; 
	}
	else if(_camera+13 + temp >= index)
	{
		index_pos = 13 + temp;	
	}
	else
	{
		index_pos = _screen - 13;
	}
	return index_pos;

}



//========================================================

///	DRAW RAIN ( SPEED(5) , SIZE(30) ) 
/// _speed :: RAIN GRADIENT  
/// _size :: FREQUENCY PER AREA

//========================================================

void cGame::init_wheather( int _type , int _speed ,int _quantity )
{

	//cntRain = 0;		// RAIN VARIABLE
	//cntAniRain = 0;		// RAIN VARIABLE

	//if (weather_sprite == NULL)
	//{
	//	weather_sprite = GL_NEW ASprite(loadResource(COMMON_SPRITE_WEATHER_RES_GLOBAL_INDEX, true), 0); //Load Sprite.
	//	weather_sprite->enablePrecalcImage(1, false);
	//}

	//if ( _type == 0 )
	//{
	//	Weather_total = ANIINDEX_WEATHER_TOTAL;
	//	for( int _i = 0 ;  _i < Weather_total ; _i++ )
	//	{
	//		weather_sprite->setAnimStop( (ANIINDEX_WEATHER_ACTOR+_i) );
	//	}
	//}
	//else 
	//{
	//	Weather_total = ANIINDEX_WEATHER_TOTAL+20;
	//}

	//SAFE_DEL_ARRAY(Weather_Posx);
	//SAFE_DEL_ARRAY(Weather_Posy);
	//SAFE_DEL_ARRAY(Weather_Direct);
	//SAFE_DEL_ARRAY(Weather_Speed);
	//SAFE_DEL_ARRAY(Weather_type);

	//Weather_Posx = GL_NEW int[Weather_total];
	//Weather_Posy = GL_NEW int[Weather_total];
	//Weather_Direct = GL_NEW int[Weather_total];
	//Weather_Speed = GL_NEW int[Weather_total];
	//Weather_type = GL_NEW int[Weather_total];

	//Weather_areaposx = (SCREEN_WIDTH / _quantity )+1;	
	//Weather_areaposy = (SCREEN_HEIGHT /_quantity)+1;	

	//Weather_speed = -_speed;
	//Weather_areasize = _quantity;	
	//Weather_Active = true;
	//Weather_Active2 = false;

	//Weather_kind = _type; //0.rain 1.snow

}

void cGame::SET_wheather( bool _active )
{
//	Weather_Active2 = _active;
}

void cGame::SET_wheather( bool _active , int _speed , int _quantity )
{

	//Weather_areaposx = (SCREEN_WIDTH /_quantity)+1;	
	//Weather_areaposy = (SCREEN_HEIGHT /_quantity)+1;	

	//Weather_speed = -_speed;

	//Weather_areasize = _quantity;
	//Weather_Active = _active;
}

void cGame::SET_wheather(int m_map_kind)
{
	//////DBG("weather_position === " + weather_position);
	//////DBG("map_kind =========== " + map_kind);
	//////DBG("weather_sprite  ==== "+ weather_sprite);
	//if(weather_position == m_map_kind)
	//{
	//	SET_wheather(true);
	//}
	//else
	//{
	//	SET_wheather(false);
	//}

}

void cGame::free_wheather( )
{
	//if(weather_sprite != NULL ){
	//	weather_sprite->ClearCompressedImageData();
	//	//weather_sprite = NULL;
	//	SAFE_DEL(weather_sprite);
	//}
	////Weather_Posx = NULL;
	////Weather_Posy = NULL;
	////Weather_Direct = NULL;
	////Weather_Speed = NULL;
	////Weather_type = NULL;
	//SAFE_DEL_ARRAY(Weather_Posx);
	//SAFE_DEL_ARRAY(Weather_Posy);
	//SAFE_DEL_ARRAY(Weather_Direct);
	//SAFE_DEL_ARRAY(Weather_Speed);
	//SAFE_DEL_ARRAY(Weather_type);
	//Weather_Active = false;
}


void cGame::Process_wheather( )
{

	//if ( !Weather_Active || !Weather_Active2)
	//	return;

	//int _i, _j;
	//int _rainrandom;	// RAIN RANDOM 
	//int _exit;			// RAIN SET

	//for( _i = 0; _i < Weather_areaposx ; _i++ )    		
	//{
	//	if( Weather_kind == WEATHER_RAIN )
	//	{
	//		for( _j = 0; _j < Weather_areaposy ; _j++ )    		
	//		{
	//			_exit = random( 0, 10 );	

	//			if ( weather_sprite->Is_animDone( ANIINDEX_WEATHER_ACTOR+cntAniRain ) && _exit > 7 )
	//			{
	//				weather_sprite->SetCurrentAnimation(ANIINDEX_WEATHER_ACTOR+cntAniRain,WEATHER_RES_RAIN_ANI_INDEX, false );
	//				_rainrandom  = random( 0, Weather_areasize );
	//				Weather_Posx[cntAniRain] = -2+(Weather_areasize*_i)+_rainrandom;
	//				Weather_Posy[cntAniRain] = -2+(Weather_areasize*_j)+_rainrandom;

	//				cntAniRain++;
	//				if( cntAniRain >= Weather_total )
	//				{
	//					cntAniRain = 0;
	//				}
	//			}
	//		}
	//		cntRain++;
	//	}
	//	else 
	//	{

	//		_exit = random( 0, 100 );
	//		if ( Weather_type[cntAniRain] == 0 && _exit > 60  )				
	//		{
	//			Weather_Posx[cntAniRain] = random( 0, SCREEN_WIDTH );;
	//			//	System.out.println( " Weather_Posx["+cntAniRain+"] = " + Weather_Posx[cntAniRain] + " _i " + _i +" Weather_areaposx =  "+ Weather_areaposx );

	//			Weather_Posy[cntAniRain] = -5;
	//			Weather_type[cntAniRain] = random( 1, 4 );
	//			Weather_Speed[cntAniRain] = random( 2, 6 )+1;

	//			cntAniRain++;
	//			if( cntAniRain >= Weather_total )
	//			{
	//				cntAniRain = 0;
	//			}
	//		}
	//		else 
	//		{
	//			for(  _i = 0 ;  _i < Weather_total ; _i++ )
	//			{
	//				if ( Weather_type[_i] > 0 )
	//				{
	//					_exit = random( 0, 100 );

	//					Weather_Posx[_i] += (Weather_speed>>1);
	//					Weather_Posy[_i] += Weather_Speed[_i];

	//					if( _exit > 96 )
	//					{
	//						Weather_type[_i]--;
	//					}
	//					if( Weather_Posy[_i] > SCREEN_HEIGHT+10 || Weather_Posx[_i] < -5 || Weather_Posx[_i] > SCREEN_WIDTH+5 )
	//					{
	//						Weather_type[_i] = 0 ;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

}


void cGame::draw_wheather( )//int _speed , int _size )
{
	//if ( !Weather_Active || !Weather_Active2 )
	//	return;

	//int _i, _j;
	//int _rainrandom;	// RAIN RANDOM 
	//int _rainstartx;	// RAIN POSITIONX
	//int _rainstarty;	// RAIN POSITIONY

	//if( Weather_kind == WEATHER_RAIN )
	//{
	//	//if( cntRain >= 50 )
	//	//{
	//	//	cntRain = 0;    		
	//	//	g->SetColor(0xFFFFFF);
	//	//	g->FillRect(0, 0, SCREEN_WIDTH,SCREEN_HEIGHT) ;   		    		
	//	//}
	//	//else 
	//	{
	//		g->SetColor(0xc5efb8);

	//		for( _i = 0; _i < Weather_areaposx ; _i++ )    		
	//		{
	//			for( _j = 0; _j < Weather_areaposy ; _j++ )    		
	//			{
	//				_rainrandom  = random( 0, Weather_areasize );
	//				_rainstartx = -5+(Weather_areasize*_i)+_rainrandom;
	//				_rainstarty = -5+(Weather_areasize*_j)+_rainrandom;
	//				//		g->DrawLine( _rainstartx , _rainstarty , _rainstartx-(Weather_speed>>2) , _rainstarty+random(10,15) );
	//				g->DrawLine( _rainstartx , _rainstarty , _rainstartx-5 , _rainstarty+15);
	//			}
	//		}   

	//		for(  _i = 0 ;  _i < Weather_total ; _i++ )
	//		{
	//			if( !weather_sprite->Is_animDone( ANIINDEX_WEATHER_ACTOR+_i ))
	//			{
	//				weather_sprite->PaintAndUpdateCurrentAnimation( g, ANIINDEX_WEATHER_ACTOR+_i, Weather_Posx[_i], Weather_Posy[_i], 0, 0, 0);
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	int _drawframe = 0 ;
	//	for(  _i = 0 ;  _i < Weather_total ; _i++ )
	//	{
	//		if ( Weather_type[_i] > 0 )
	//		{	
	//			_drawframe = WEATHER_RES_SNOW_A_FRM_INDEX + Weather_type[_i] - 1;

	//			weather_sprite->PaintFrame( g, _drawframe, Weather_Posx[_i], Weather_Posy[_i], 0, 0, 0);						
	//		}
	//	}
	//}
}





void cGame::init_Popup( int _x, int _y, int _sizex, int _sizey, bool  _bmove, bool  _bline )
{
	popup_DrawposX = _x;
	popup_DrawposY = _y; 

	popup_MoveposX = 0;
	popup_MoveposY = 0;

	popup_sizeX = _sizex;
	popup_sizeY = _sizey;

	bpopup_move = _bmove;
	bpopup_line = _bline;

//	popup_imgsizeX = popup_Sprite->GetModuleWidth( POPUP_RES_PATTERN_MOD_INDEX );
//	popup_imgsizeY = popup_Sprite->GetModuleHeight( POPUP_RES_PATTERN_MOD_INDEX );

	if ( bpopup_move )
	{
		popup_MoveDirectX =  random( DIRECT_LEFT, DIRECT_RIGHT );
		popup_MoveDirectY =  random( DIRECT_DOWN, DIRECT_UP );
	}
	else 
	{
		popup_MoveDirectX =  DIRECT_NULL;
		popup_MoveDirectY =  DIRECT_NULL;
	}
}

//void cGame::OEMC_knlExecuteEx(   char*  url)
//{
//
//	//ISHELL_StartApplet()
//	//MEMSET(m_url, 0, k_URL_LENGTH);
//	//SPRINTF(m_url, "cmshop:ItemID=%d", m_pGameAds[m_adIndex]->GetShopId() );
//	ISHELL_BrowseURL(GetGameApp()->a.m_pIShell, url);
//
//}

void cGame::Process_Popup( )
{
	if ( bpopup_move )
	{
		if( game_counter%2 == 0)
		{
			if ( popup_MoveDirectX == DIRECT_LEFT )
			{
				popup_MoveposX--;
			}
			else if ( popup_MoveDirectX == DIRECT_RIGHT )
			{
				popup_MoveposX++;
			}

			if ( popup_MoveDirectY == DIRECT_UP )
			{
				popup_MoveposY--;
			}
			else if ( popup_MoveDirectY == DIRECT_DOWN )
			{
				popup_MoveposY++;
			}
		}
	}

	if ( popup_MoveposX <= -popup_imgsizeX )
	{
		popup_MoveposX +=popup_imgsizeX;
	}
	else if ( popup_MoveposX >= popup_imgsizeX )
	{
		popup_MoveposX -=popup_imgsizeX;
	}

	if ( popup_MoveposY <= -popup_imgsizeY )
	{
		popup_MoveposY +=popup_imgsizeY;
	}
	else if ( popup_MoveposY >= popup_imgsizeY )
	{
		popup_MoveposY -=popup_imgsizeY;
	}

}


//================================================================

/// DRAW FUNCTION

//================================================================



void cGame::Draw_Popup( int _plussize )
{

	int _countx = ((popup_sizeX+_plussize)/popup_imgsizeX)+2;
	int _county = (popup_sizeY/popup_imgsizeY)+2;
	int _posx = popup_DrawposX+popup_MoveposX;
	int _posy = popup_DrawposY+popup_MoveposY;

	g->SetClip( popup_DrawposX, popup_DrawposY, (popup_sizeX+_plussize), popup_sizeY );

	//for ( int _x = -1 ;  _x < _countx ; _x++)
	//{
	//	for ( int _y = -1 ;  _y < _county ; _y++)
	//	{
	//		popup_Sprite->PaintModule( g, POPUP_RES_PATTERN_MOD_INDEX , _posx + (_x*popup_imgsizeX) , _posy + (_y*popup_imgsizeY)  , 0) ;
	//	}
	//}	

	if( bpopup_line ) 
	{
		g->SetColor(0x000000);
		g->FillRect(popup_DrawposX,popup_DrawposY,1, popup_sizeY);
		g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1,popup_DrawposY, 1,  popup_sizeY);

		g->SetColor(0x00ADAF);
		g->FillRect(popup_DrawposX+1,popup_DrawposY, 4, popup_sizeY);
		g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1-4,popup_DrawposY,  4, popup_sizeY);

		g->SetColor(0xFFFFFF);
		g->FillRect(popup_DrawposX+1+4,popup_DrawposY, 4, popup_sizeY);
		g->FillRect(popup_DrawposX+(popup_sizeX+_plussize)-1-8,popup_DrawposY,  4, popup_sizeY);
	}

	g->SetClip( 0,0,SCREEN_WIDTH, SCREEN_HEIGHT );

}




void cGame::Draw_RectinPopup( int _x , int _y , int _dx , int _dy )
{

	g->SetColor(0xFFFFFF);
	g->FillRect(_x,_y,_dx,_dy);

	g->SetColor(0xC3FFB9);
	g->FillRect(_x,_y+1,_dx,_dy-2);

}


//================================================================
/// character hp FUNCTION
//================================================================


//void cGame::add_Character_Hp( int _index)
//{
//	if(!m_game_pause){
//		m_characterHp += _index;
//		if(m_characterHp < 0)
//			m_characterHp = 0;
//	}
//
//}




cGame::cGame()
{

	//isNetFromGame = false;//Chen Shoutian, Bank Charge
	have_save_file = false;
	//record_buffData = NULL;
	showIGPNew = false;
	/*touch_x = NONE_VALUE_CLICK; 
	touch_y =NONE_VALUE_CLICK; 
	touch_status = MY_EVT_PEN_UP;*/
#ifndef USE_DRAWRGB_FOR_TILES
	mapSprites_len = 0;
#endif
	
	g_pCEngine = this;
	
	s_cinematics = NULL;
	text_array_sub_length = GL_NEW int[20];
	MEMSET(text_array_sub_length, 0, 20*sizeof(int));

	s_cinematics_sub_length = GL_NEW int[100];
	s_cinematics_sub_sub_length = GL_NEW int*[100];

	for(int i=0; i<100; i++)
	{
		s_cinematics_sub_sub_length[i] = GL_NEW int[100];
	}

	s_currentFramePos_sub_length = GL_NEW int[100];
	s_runningCinematicTrackActors_sub_length = GL_NEW int[100];

	cEntity::s_zones = GL_NEW short[ZONES::k_cnt * ZONES::k_data_size];

	m_entEntities_length = ENTITY::k_max;
	m_entEntities = GL_NEW cEntity*[m_entEntities_length];
	MEMSET(m_entEntities, 0, sizeof(m_entEntities[0])*m_entEntities_length);
	
	//MEMSET(m_entEntities, 0, ENTITY::k_max*sizeof(m_entEntities[0]) );

	_actorDrawVector = GL_NEW Vector1();
	//k_data_dbgDataAccess = false;
	//k_data_skipbufferSize = 256;

#ifdef USE_DRAWRGB_FOR_TILES
	m_sprTileset = GL_NEW ASprite*[TILE_LAYER::k_id_cnt];
	MEMSET(m_sprTileset, 0, (TILE_LAYER::k_id_cnt) * sizeof(m_sprTileset[0]));
#else
	m_tileSet = GL_NEW CImage**[TILE_LAYER::k_id_cnt];
	MEMSET(m_tileSet, 0, (TILE_LAYER::k_id_cnt) * sizeof(m_tileSet[0]));
#endif
	
	//Robust, modify it length to 6, for net use.
	text_array = GL_NEW byte**[6];
	text_array_length = 6;	MEMSET(text_array,0,5*sizeof(int));
	s_isDrawPageInit = false;
	_index1 = -1;	
	_index2 = -1;	
	_line_spacing = 2;	
	_char_spacing = 0;
	s_nextCinematic = -1;
	mascot_currentState = 0 ;

//	mascot_currentAction = 0 ;
//	mascot_mascotDispX = 131 ;
//	mascot_barDispY = 52 ;

	mascot_mascotDirect = DIRECT_LEFT;
	popup_currentState = 0 ;	
	popup_currentAction = 0 ;	
	popup_mascotDispX = 131 ;	
	popup_barDispY = 65 ;

	//move_zip = 0;	
	//bmove_zip = false;	
	//maxMenuX = 4; 	
	//maxMenuY = 1;	
	//dipIndex = 0;	
	//menuIndex = 0;

	maxVol = 5;		
	curFlag = false;	
	m_sndVol		= 3;	
	m_vibrateOn	= 1; 
	m_speed		= 1; 
	m_runtime		= 0; 
	m_dataslot	= STORE_SLOT1; 
	m_tileMapLayer = GL_NEW byte*[TILE_LAYER::k_id_cnt];
	m_tileMapLayer_sub_length = GL_NEW int[TILE_LAYER::k_id_cnt];
	m_tileMapLayer_length = TILE_LAYER::k_id_cnt;

	m_tileFlipLayer = GL_NEW byte*[TILE_LAYER::k_id_cnt];
	m_tileFlipLayer_sub_length = GL_NEW int[TILE_LAYER::k_id_cnt];
	m_tileFlipLayer_length = TILE_LAYER::k_id_cnt;
	cntRain = 0;		
	cntAniRain = 0;	
	//s_math_F_1		= 1 << 8;
	//s_math_F_05	= (s_math_F_1>>1);
	//game_lastTime = 0;	
	//game_currentTime = 0;
	//game_FirstTime = 0;
	//game_timeDiff = 0;//612	

	m_sound = NULL;
	//////////////////////////////////////////////////////////////////////////
	s_game_frameDT = 50;
	s_cinematicWaitType = WaitType::None;

	record_buffData = GL_NEW byte[RECORD_BUFFDATA_SIZE];

	record_mapUserData = GL_NEW byte[MAP_ONE_SIZE];



	/////////////////////////////////////////////
	/// USER MAP DATA
	/////////////////////////////////////////////

	//mapUser_Data = GL_NEW short*[MAP_MAX_ENTITY];

	//for(int i=0; i<MAP_MAX_ENTITY; i++)
	//{
	//	mapUser_Data[i] = GL_NEW short[MAP_MAX_DATA];
	//}

	//		GL_NEW Thread ( this ).start();

}


CEngine::ERROR_TYPE  cGame::Initialize()
{
	g_pGame = this;
	CEngine::ERROR_TYPE err = CEngine::Initialize();
	if (err != E_SUCCESS)
		return err;

	
	#ifdef USE_CHECKSPACE

		s_bSaveMode = true;

		CheckSpace(RECORD_FILENAME, s_bCanLoad, s_bCanSave, RECORD_SIZE , false);

		//MAP DATA CHECK
		CheckSpace(RECORD_MAP_FILENAME1, s_bCanLoad, s_bCanSave, MAP_ONE_SIZE , false);
		CheckSpace(RECORD_MAP_FILENAME2, s_bCanLoad, s_bCanSave, MAP_ONE_SIZE , false);
		CheckSpace(RECORD_MAP_FILENAME3, s_bCanLoad, s_bCanSave, MAP_ONE_SIZE , false);
		CheckSpace(RECORD_MAP_FILENAME4, s_bCanLoad, s_bCanSave, MAP_ONE_SIZE , false);
		CheckSpace(RECORD_MAP_FILENAME5, s_bCanLoad, s_bCanSave, MAP_ONE_SIZE , false);

		//s_bCanLoad = false;
		//s_bCanSave = false;
		if ( !(s_bCanLoad && s_bCanSave) )
		{
			s_bSaveMode = false;
		}
	#endif

	CGraphics& _g = GetDevice().GetScreenImage().GetGraphics();
	g = &_g;

	//myFont = GL_NEW Mid_Font(SCREEN_WIDTH, SCREEN_HEIGHT);
	//	m_animPlayer = (GL_GL_NEW(GLOBAL_TOP) CActor());
	//	SwitchState( GameState::Initial );	

////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////

	return E_SUCCESS;
}


/////////////////////////////////////////////////////
// TEXT_FIELD
/////////////////////////////////////////////////////

//void cGame::set_textField( int _bAutomata_ )
//{
//	//byte _bAutomata[3]={AEE_TM_ENGLISH_US,AEE_TM_NUMBERS,AEE_TM_HANGUL};
//
//	if( _cText )
//	{
//		ITEXTCTL_Release(_cText);
//		_cText = NULL;
//	}	
//
//	ISHELL_CreateInstance(GetGameApp()->a.m_pIShell , AEECLSID_TEXTCTL ,(void **)&_cText);	
//	
//
//	AEERect  rect ;
//	rect.x = TEXTFIELD_NEWNAME_X ;
//	rect.y = TEXTFIELD_NEWNAME_Y ;
//	rect.dx = TEXTFIELD_NEWNAME_WIDTH ;
//	rect.dy = TEXTFIELD_NEWNAME_HEIGHT ;
//	ITEXTCTL_SetRect(_cText , &rect);
//
//	ITEXTCTL_SetMaxSize (_cText , TEXTFELDMAXSIZE);
//
//	ITEXTCTL_SetProperties(_cText , TP_FRAME) ;
//	ITEXTCTL_SetActive(_cText, TRUE);
//	ITEXTCTL_SetInputMode ( _cText , AEE_TM_NONE );
//	ITEXTCTL_SetInputMode ( _cText , _bAutomata[_bAutomata_] );
//	
//	//ITEXTCTL_Redraw (_cText);
//}
//
//
//#include "cKRConvert.h"
//int cGame::update_Key_textField( )
//{
//	if( KEY_PRESSED(GAME_KEY_SOFTKEY_LEFT) )
//	{
//		if( _cText )
//		{
// 			ITEXTCTL_Release(_cText);
//			_cText = NULL;
//		}
//		//ReleaseNetRes(m_RankingState);
//
//	}
//	else if( KEY_PRESSED(GAME_KEY_SOFTKEY_RIGHT) )
//	{
//		//char tmpBuf[32] = {0};
//		//AECHAR * temp = ITEXTCTL_GetTextPtr( _cText ) ;
//		//int iLen_ = 0;
//		//while( iLen_ < TEXTFELDMAXSIZE && temp[ iLen_ ] != '\0')
//		//{
//		//	tmpBuf[iLen_] =(char)temp[ iLen_ ];
//		//	iLen_++;
//		//}
//		//tmpBuf[iLen_] = '\0';
//
//		
//		m_automateType = (m_automateType + 1) % AUTOMATA_NUM1;
//		//byte _bAutomata[3]={AEE_TM_ENGLISH_US,AEE_TM_NUMBERS,AEE_TM_HANGUL};
//		ITEXTCTL_SetInputMode ( _cText , _bAutomata[m_automateType] );
//		//set_textField( _bKeyMove );
//		//ITEXTCTL_SetText( _cText,  ( AECHAR *)tmpBuf, STRLEN(tmpBuf));
//
//
//	}
//	else if( KEY_PRESSED(GAME_KEY_CLICK) )
//	{
//		char tmpBuf[16] = {0};
//		AECHAR * temp = ITEXTCTL_GetTextPtr( _cText ) ;
//		int iLen_ = 0;
//		while( iLen_ < TEXTFELDMAXSIZE && temp[ iLen_ ] != '\0')
//		{
//			tmpBuf[iLen_] =(char)temp[ iLen_ ];
//			iLen_++;
//		}
//		tmpBuf[iLen_] = '\0';
//
//		byte _bUTF16_[16]={0};
//		byte _bUTF8_[32]={0};
//
//		
//		iLen_ = ConvertKSC5601toUTF16( (byte*)tmpBuf, iLen_, _bUTF16_ );   
//		iLen_ = ConvertUTF16toUTF8( _bUTF16_, _bUTF8_, iLen_, CONVUTF_8 );	
//
//		MEMSET( textField_Name, 0, sizeof(textField_Name));
//		MEMCPY( textField_Name, _bUTF8_, iLen_ );
//
//		if( STRLEN(textField_Name) > 1 )
//		{
//			if( _cText )
//			{
//				 ITEXTCTL_Release(_cText);//MC_uicDestroy( _cText );
//				_cText = NULL;
//
//
//
//
//				return 1;
//			}
//		}
//
//	}
//	else if( !KEY_PRESSED(GAME_KEY_LEFT) )
//	{
//		if( _cText )
//		{		
//			if(GetGameApp()->m_eCode != 0)
//				ITEXTCTL_HandleEvent( _cText , GetGameApp()->m_eCode , GetGameApp()->m_wParam , GetGameApp()->m_dwParam);
//			GetGameApp()->m_eCode = 0 ;		
//
//		}
//	}
//	return 0;
//}
//
//char* cGame::getText(char** strRtn)
//{
//	
//	char* rtnStr = *strRtn;
//	
//	char tmpBuf[16] = {0};
//	AECHAR * temp = ITEXTCTL_GetTextPtr( _cText ) ;
//	int iLen_ = 0;
//	while( iLen_ < TEXTFELDMAXSIZE && temp[ iLen_ ] != '\0')
//	{
//		rtnStr[iLen_] =(char)temp[ iLen_ ];
//		iLen_++;
//	}
//	//rtnStr[iLen_] = '\0';
//
//		
//
//
//	return rtnStr;
//}

// ////////////////////////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////shine///////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef hasShine


void cGame::InitShine()
{
	
		_shineImgs = GL_NEW CImage*[SHINE::SHINE_COUNT];
		unsigned int * _shine_8888;
		{
			//if ()
			{    
				_shine_8888 = GL_NEW unsigned int[SHINE::SHINE_BIG_IMAGE_WIDTH * SHINE::SHINE_BIG_IMAGE_HEIGHT]; // 34 *121

				//tile 4
				Bresenham_Line_8888(0, 0, SHINE::SHINE_BIG_IMAGE_WIDTH, SHINE::SHINE_BIG_LINE_DY, 
					SHINE::SHINE_BIG_LINE_ALPHA0, SHINE::SHINE_BIG_LINE_ALPHA1, SHINE::SHINE_BIG_LINE_WIDTH,
					SHINE::SHINE_BIG_LINE_WIDTH2, _shine_8888, SHINE::SHINE_BIG_LINE_SCAN_LINE, 0x00009FFF);
				//			_shineImgs[0] = Image->createRGBImage(_shine_8888, DEF::SHINE_BIG_IMAGE_WIDTH, DEF::SHINE_BIG_IMAGE_HEIGHT, true);
				_shineImgs[0] = (CImage *)(GL_NEW CRgbImage(SHINE::SHINE_BIG_IMAGE_WIDTH, SHINE::SHINE_BIG_IMAGE_HEIGHT, NATIVE_COLOR_PITCH * 2 * SHINE::SHINE_BIG_IMAGE_WIDTH, NATIVE_COLOR_DEPTH * 2, _shine_8888));
				
				//tile 1
				Bresenham_Line_8888(0, 0, SHINE::SHINE_BIG_IMAGE_WIDTH, SHINE::SHINE_BIG_LINE_DY, 
					SHINE::SHINE_BIG_LINE_ALPHA0, SHINE::SHINE_BIG_LINE_ALPHA1, SHINE::SHINE_BIG_LINE_WIDTH,
					SHINE::SHINE_BIG_LINE_WIDTH2, _shine_8888, SHINE::SHINE_BIG_LINE_SCAN_LINE, 0x0032BEF7);
				//			_shineImgs[2] = Image->createRGBImage(_shine_8888, DEF::SHINE_BIG_IMAGE_WIDTH, DEF::SHINE_BIG_IMAGE_HEIGHT, true);
				_shineImgs[2] = (CImage *)(GL_NEW CRgbImage(SHINE::SHINE_BIG_IMAGE_WIDTH, SHINE::SHINE_BIG_IMAGE_HEIGHT, NATIVE_COLOR_PITCH * 2 * SHINE::SHINE_BIG_IMAGE_WIDTH, NATIVE_COLOR_DEPTH * 2, _shine_8888));
				//SAFE_DELETE(_shine_8888);
				//			_shine_8888 = new int[SHINE::SHINE_SMALL_IMAGE_WIDTH * SHINE::SHINE_SMALL_IMAGE_HEIGHT];	//21*73
				_shine_8888 = GL_NEW unsigned int[SHINE::SHINE_SMALL_IMAGE_WIDTH * SHINE::SHINE_SMALL_IMAGE_HEIGHT];	//21*73
				//tile 4
				Bresenham_Line_8888(0, 0, SHINE::SHINE_SMALL_IMAGE_WIDTH, SHINE::SHINE_SMALL_LINE_DY, 
					SHINE::SHINE_SMALL_LINE_ALPHA0, SHINE::SHINE_SMALL_LINE_ALPHA1, SHINE::SHINE_SMALL_LINE_WIDTH,
					SHINE::SHINE_SMALL_LINE_WIDTH2, _shine_8888, SHINE::SHINE_SMALL_LINE_SCAN_LINE, 0x00009FFF);
				//			_shineImgs[1] = Image->createRGBImage(_shine_8888, DEF::SHINE_SMALL_IMAGE_WIDTH, DEF::SHINE_SMALL_IMAGE_HEIGHT, true);
				_shineImgs[1] = (CImage *)(GL_NEW CRgbImage(SHINE::SHINE_SMALL_IMAGE_WIDTH, SHINE::SHINE_SMALL_IMAGE_HEIGHT, NATIVE_COLOR_PITCH * 2 * SHINE::SHINE_SMALL_IMAGE_WIDTH, NATIVE_COLOR_DEPTH * 2, _shine_8888));
				//tile 1
				Bresenham_Line_8888(0, 0, SHINE::SHINE_SMALL_IMAGE_WIDTH, SHINE::SHINE_SMALL_LINE_DY, 
					SHINE::SHINE_SMALL_LINE_ALPHA0, SHINE::SHINE_SMALL_LINE_ALPHA1, SHINE::SHINE_SMALL_LINE_WIDTH,
					SHINE::SHINE_SMALL_LINE_WIDTH2, _shine_8888, SHINE::SHINE_SMALL_LINE_SCAN_LINE, 0x0032BEF7);
				//			_shineImgs[3] = Image->createRGBImage(_shine_8888, DEF::SHINE_SMALL_IMAGE_WIDTH, DEF::SHINE_SMALL_IMAGE_HEIGHT, true);
				_shineImgs[3] = (CImage *)(GL_NEW CRgbImage(SHINE::SHINE_SMALL_IMAGE_WIDTH, SHINE::SHINE_SMALL_IMAGE_HEIGHT, NATIVE_COLOR_PITCH * 2 * SHINE::SHINE_SMALL_IMAGE_WIDTH, NATIVE_COLOR_DEPTH * 2, _shine_8888));
				//SAFE_DELETE(_shine_8888);
			}
			//                _shine_8888 = GL_NEW int[68 * 52];
			//                Bresenham_Line_8888(0, 0, 68, 32, 120, 0, 20,0, _shine_8888, 68); // 68*52
			//                _shineImgs[2] = Image->createRGBImage(_shine_8888, 68, 52, true);
			//                _shineImgs[3] = _shineImgs[1];
		}
		//            _shine_8888 = GL_NEW int[26 * 26];
		//            Bresenham_Line_8888(0, 0, 26, 26, 0, 250, 1, _shine_8888, 26); // 26*26
		//            _shineImgs[4] = Image->createRGBImage(_shine_8888, 26, 26, true);

		//if ( (s_level >DEF::LEVEL_WOLF_LEVEL && s_level<DEF::LEVEL_FAST_LEVEL) || (s_level>=DEF::LEVEL_FASTUP_LEVEL-1 && s_level<DEF::LEVEL_DRAGON_LEVEL))
		{    
			//#ifndef platform in ("SonyEricssonW810i")
#ifdef BIG_SCREEN
			_shine_8888 = GL_NEW unsigned int[14 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 14,0, _shine_8888, 14, 0x0001F3F9); // 24*72
			//_shineImgs[4] = Image.createRGBImage(_shine_8888, 14, 70, true); 
			_shineImgs[4] = (CImage *)(GL_NEW CRgbImage(14, 70, NATIVE_COLOR_PITCH * 2 * 14, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[12 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 12,0, _shine_8888, 12, 0x0001F3F9); // 24*72
			//_shineImgs[5] = Image.createRGBImage(_shine_8888, 12, 70, true);
			_shineImgs[5] = (CImage *)(GL_NEW CRgbImage(12, 70, NATIVE_COLOR_PITCH * 2 * 12, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[10 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 10,0, _shine_8888, 10, 0x0001F3F9); // 24*72
			//_shineImgs[6] = Image.createRGBImage(_shine_8888, 10, 70, true);
			_shineImgs[6] = (CImage *)(GL_NEW CRgbImage(10, 70, NATIVE_COLOR_PITCH * 2 * 10, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[8 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 8,0, _shine_8888, 8, 0x0001F3F9); // 24*72
			//_shineImgs[7] = Image.createRGBImage(_shine_8888, 8, 70, true);
			_shineImgs[7] = (CImage *)(GL_NEW CRgbImage(8, 70, NATIVE_COLOR_PITCH * 2 * 8, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[6 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 6,0, _shine_8888, 6, 0x0001F3F9); // 24*72
			//_shineImgs[8] = Image.createRGBImage(_shine_8888, 6, 70, true);
			_shineImgs[8] = (CImage *)(GL_NEW CRgbImage(6, 70, NATIVE_COLOR_PITCH * 2 * 6, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[4 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 4,0, _shine_8888, 4, 0x0001F3F9); // 24*72
			//_shineImgs[9] = Image.createRGBImage(_shine_8888, 4, 70, true);
			_shineImgs[9] = (CImage *)(GL_NEW CRgbImage(4, 70, NATIVE_COLOR_PITCH * 2 * 4, NATIVE_COLOR_DEPTH * 2, _shine_8888));

			_shine_8888 = GL_NEW unsigned int[4 * 70];
			Bresenham_Line_8888(0, 0, 0, 70, 0, 250, 4,0, _shine_8888, 4, 0x0001F3F9); // 24*72
			//_shineImgs[10] = Image.createRGBImage(_shine_8888, 4, 70, true);
			_shineImgs[10] = (CImage *)(GL_NEW CRgbImage(4, 70, NATIVE_COLOR_PITCH * 2 * 4, NATIVE_COLOR_DEPTH * 2, _shine_8888));
#else
			_shine_8888 = GL_NEW unsigned int[20 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 20,0, _shine_8888, 20, 0x0001F3F9); // 24*72
			//		_shineImgs[4] = Image->createRGBImage(_shine_8888, 20, 102, true); 
			_shineImgs[4] = (CImage *)(GL_NEW CRgbImage(20, 102, NATIVE_COLOR_PITCH * 2 * 20, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[16 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 16,0, _shine_8888, 16, 0x0001F3F9); // 24*72
			//		_shineImgs[5] = Image->createRGBImage(_shine_8888, 16, 102, true);
			_shineImgs[5] = (CImage *)(GL_NEW CRgbImage(16, 102, NATIVE_COLOR_PITCH * 2 * 16, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[12 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 12,0, _shine_8888, 12, 0x0001F3F9); // 24*72
			//		_shineImgs[6] = Image->createRGBImage(_shine_8888, 12, 102, true);
			_shineImgs[6] = (CImage *)(GL_NEW CRgbImage(12, 102, NATIVE_COLOR_PITCH * 2 * 12, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[9 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 9,0, _shine_8888, 9, 0x0001F3F9); // 24*72
			//		_shineImgs[7] = Image->createRGBImage(_shine_8888, 9, 102, true);
			_shineImgs[7] = (CImage *)(GL_NEW CRgbImage(9, 102, NATIVE_COLOR_PITCH * 2 * 9, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[6 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 6,0, _shine_8888, 6, 0x0001F3F9); // 24*72
			//		_shineImgs[8] = Image->createRGBImage(_shine_8888, 6, 102, true);
			_shineImgs[8] = (CImage *)(GL_NEW CRgbImage(6, 102, NATIVE_COLOR_PITCH * 2 * 6, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[4 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 4,0, _shine_8888, 4, 0x0001F3F9); // 24*72
			//		_shineImgs[9] = Image->createRGBImage(_shine_8888, 4, 102, true);
			_shineImgs[9] = (CImage *)(GL_NEW CRgbImage(4, 102, NATIVE_COLOR_PITCH * 2 * 4, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);

			_shine_8888 = GL_NEW unsigned int[2 * 102];
			Bresenham_Line_8888(0, 0, 0, 101, 0, 250, 2,0, _shine_8888, 2, 0x0001F3F9); // 24*72
			//		_shineImgs[10] = Image->createRGBImage(_shine_8888, 2, 102, true);
			_shineImgs[10] = (CImage *)(GL_NEW CRgbImage(2, 102, NATIVE_COLOR_PITCH * 2 * 2, NATIVE_COLOR_DEPTH * 2, _shine_8888));
			//SAFE_DELETE(_shine_8888);
#endif			
			_shine_8888 = NULL;
		}
	
}

void cGame::Bresenham_Line_4444(int x0, int y0, int x1, int y1, int alpha0, int alpha1, int width, unsigned short* dest, int scan_line)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int e = dx > 0 ? -dx : dx;
	int step = dx > 0 ? 1 : -1;
	int x = x0;
	int y = y0;
	int index = y0 * scan_line + x0;
	alpha0 <<= 8;
	alpha1 <<= 8;
	int a = (alpha1 - alpha0) / dx;
	for (int i = 0; i < dx; i++)
	{
		int pos = index;
		unsigned short c = (unsigned short) ((alpha0) | 0x0FFA);
		int k = 0;
		for (; k < width; ++k)
		{
			dest[pos] = c;
			pos += scan_line;
		}
		alpha0 += a;
		x += step;
		index += step;
		e += dy << 1;
		if (e >= 0)
		{
			y++;
			index += scan_line;
			e -= dx << 1;
		}
	}
}

void cGame::Bresenham_Line_8888(int x0, int y0, int x1, int y1, int alpha0, int alpha1, int width, int width2, unsigned int* dest, int scan_line, int color)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int dw = width2 -width;
	if (dx == 0)
	{
		int index = y0 * scan_line + x0;
		alpha0 <<= 8;
		alpha1 <<= 8;
		int a = (alpha1 - alpha0) / dy;
		for (int i = 0; i < dy; i++)
		{
			int pos = index;
			int k = 0;
			unsigned int c;
			for (; k < 4; ++k)
			{
				c = ((((alpha0 / 5 * (k + 1)) & 0xFF00) << 16) | color);
				dest[pos] = c;
				++pos;
			}
			c = (((alpha0 & 0xFF00) << 16) | color);
			for (; k < width - 4; ++k)
			{
				dest[pos] = c;
				++pos;
			}
			for (; k < width; ++k)
			{
				c = (((((alpha0 / 5 * (width - k))) & 0xFF00) << 16) | color);
				dest[pos] = c;
				++pos;
			}

			if (i>dy*2/3)
				alpha0-=2*a;
			else
				alpha0 += a;
			index += scan_line;
		}
	}
	else
	{
		//         int e = dx > 0 ? -dx : dx;
		//         int step = dx > 0 ? 1 : -1;
		int ystep = (dy<<8)/dx;
		int wstep = (dw<<8)/dx;
		//            int x = x0;
		//            int y = y0;
		int index = y0 * scan_line + x0;
		int realwidth = width;
		alpha0 <<= 8;
		alpha1 <<= 8;
		int a = (alpha1 - alpha0) / dx;
		for (int i = 0; i < dx; i++)
		{   
			int alpv = alpha0;
			if (i==0)
			{
				alpv =alpha1;
			}    
			int pos = index;
			unsigned int c = (((alpv << 16)&0xFF000000) |color);
			int k = 0;
			realwidth = ((width<<8)+wstep*i)>>8;
			for (; k < realwidth; ++k)
			{
				dest[pos] = c;
				pos += scan_line;
			}
			alpha0 += a;
			index = (x0+i)+(((y0<<8)+ystep*i)>>8)* scan_line ;
			//                e += dy << 1;
			//                if (e >= 0)
			//                {
			//                    index += scan_line;
			//                    e -= dx << 1;
			//                }
		}
	}
}
#endif //hasShine

#ifdef USE_DIRECT_DRAW
void cGame::ModifyPalette(ASprite* sprite, int palNb, int color)
{

	//sprite->_alpha = true;
	sprite->_modules_image->SetAlphaFlag();
	sprite->_modules_image->SetNightAlphaFlag();

	{
		color = CNativeGraphics::ToNativeColorS(color);//  color & 0x00FFFFFF;
		for (int i = 0; i < sprite->_colors; i++)
		{			
			if (sprite->_pal[palNb][i] != (unsigned short)sprite->_modules_image->GetColorKey())
				sprite->_pal[palNb][i] = (((sprite->_pal[palNb][i]) << 27) | color);
		}
	}

}
#endif


