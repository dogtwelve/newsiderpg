#include "Defines.h"

#include "../common/Engine.h"
#include "../common/Image.h"
#include "../common/Stream.h"
#include "../common/Graphics.h"
#include "ASprite.h"
#include "../wipi/Small_Font.h"

#include "cui.h"
#include "ENTITY.h"
#include "Command_Def.h"
#include "USER_Map.h"
#include "Module_Move.h"
#include "UI_Gameloft.h"
#include "UI_Splash.h"
#include "UI_Menu.h"
#include "cEntity.h"


#include "DEF.h"
#include "GAME.h"
#include "cGAME.h"
#include "..\Config\version.h"

//GuanHao. IGP
#include "..\igp_wipi\wipiigp.h"
//USER_MAP.hpp
#include "macro.h"
//#include ".\NetSource\Common\cKRConvert.h"
#include "cKRConvert.h"


//#include "maincharacter.h"

extern cGame* g_pGame;

//MainMenu* mainUI;//mainUI
//MainGame* gameUI;//gameUI



//void cUI::pursuit_object_auto(int _id , int _map_kind , boolean bID)
//{
//	int temp = 0;
//	char _map_kindA = -32;
//	char _map_kindB = -32;
//	char _map_kindC = -32;
//	char _index_ID = 0;
//	char _index_posX = 0;	
//	char _index_posY = 0;	
//	char _index_charposY = 0;
//
//	if(_map_kind == MAP_WORLD)
//	{
//		_map_kindB = (byte)MAP_TOWN;
//		_map_kindC = (byte)MAP_SQUARE;
//	}
//	else if(_map_kind == MAP_TOWN)
//	{
//		_index_ID = (byte)39;	
//		_map_kindA = (byte)MAP_WORLD;
//		_map_kindC = (byte)MAP_SQUARE;
//		_index_posX = (byte)5;
//		_index_posY = (byte)22;
//	}
//	else if(_map_kind == MAP_SQUARE)
//	{
//		_index_ID = (byte)78;	
//		_map_kindA = (byte)MAP_WORLD;
//		_map_kindB = (byte)MAP_TOWN;
//		_index_posY = (byte)20;
//	}
//
//	if(g_pGame->m_map_kind == _map_kind)
//	{
//		if(!bID)
//		{
//			temp = g_pGame->getEntityNumber(_id);
//			_index_charposY -= (byte)34;
//		}
//		else
//		{
//			temp = g_pGame->getEntityGameID(_id);
//		}
//
//		if(temp != -1)
//		{	
//			if(bID)
//			{
//				g_pGame->getEntity(temp)->m_flags = 0;
//			}
//			g_pGame->pursuit_object(g_pGame->getEntity(temp)->m_posX ,g_pGame->getEntity(temp)->m_posY + _index_charposY);
//		}
//
//	}
//	else if(g_pGame->m_map_kind == _map_kindA)
//	{
//		temp = g_pGame->getEntityGameID(_index_ID);
//		if(temp != -1)
//		{
//			g_pGame->getEntity(temp)->m_flags = 0;
//			g_pGame->pursuit_object(g_pGame->getEntity(temp)->m_posX - _index_posX ,g_pGame->getEntity(temp)->m_posY + _index_posY);
//		}
//	}
//	else if(g_pGame->m_map_kind == _map_kindB)
//	{
//		temp = g_pGame->getEntityGameID(21);
//		if(temp != -1)
//		{
//			g_pGame->getEntity(temp)->m_flags = 0;
//			g_pGame->pursuit_object(g_pGame->getEntity(temp)->m_posX + 5 ,g_pGame->getEntity(temp)->m_posY + 22);
//		}
//	}
//	else if(g_pGame->m_map_kind == _map_kindC)
//	{
//		temp = g_pGame->getEntityGameID(27);
//		if(temp != -1)
//		{
//			g_pGame->getEntity(temp)->m_flags = 0;
//			g_pGame->pursuit_object(g_pGame->getEntity(temp)->m_posX ,g_pGame->getEntity(temp)->m_posY - 15);
//		}
//
//	}
//}

//================================================================

/// INIT GAME CHEAT

//================================================================

void cUI::init_Cheat( )
{

	Cheat_Data = NULL;
	Cheat_Input = NULL;
	Cheat_Data = GL_NEW int[CHEAT_MAX_COUNT];
	Cheat_Input = GL_NEW int[CHEAT_MAX_COUNT];

	Cheat_Data[0] = CHEAT_DATA1;
	Cheat_Data[1] = CHEAT_DATA2;
	Cheat_Data[2] = CHEAT_DATA3;
	Cheat_Data[3] = CHEAT_DATA4;
	Cheat_Data[4] = CHEAT_DATA5;
	Cheat_Data[5] = CHEAT_DATA6;
	Cheat_Data[6] = CHEAT_DATA7;
	Cheat_Data[7] = CHEAT_DATA8;

	cheat_samecount  = 0; 
	cheat_intputcount  = 0; 

//	g_pGame->m_SetDebuglevel = 6;

	cheat_money = 0;
	//g_pGame->Init_Bank();

	
}

//================================================================

/// DRAW CHEAT

//================================================================

void cUI::Draw_Cheat( )
{

}


//================================================================

/// PROCESS KEY CHEAT

//================================================================
void cUI::key_Cheat( )
{

}
#define EVENING_TIME   1080//CLOCK::k_minute * 18
#define MONING_TIME   420//CLOCK::k_minute * 7
#define NIGHT_ALPHA		150


void cUI::draw_Start_Channel()
{
	/////////////////
	int _time = g_pGame->getClock();
	//if( _time > 1080 || _time < MONING_TIME) // #define EVENING_TIME   1080//CLOCK::k_minute * 18
	{
		
		_time = (_time < MONING_TIME) ? (MONING_TIME - _time) : (_time - EVENING_TIME);	
		_time = _time - (_time % 10);
		if(_time > NIGHT_ALPHA)
		{
			_time = NIGHT_ALPHA;
		}
		if(_time < 1)
		{

			return;
		}
		g->SetChannel(CHANNEL_NIGHT); 
		//MEMSET(g->m_buffPixel, _time, SCREEN_WIDTH * SCREEN_HEIGHT);
		MEMSET(g_pGame->backbuffpix, _time, SCREEN_WIDTH * SCREEN_HEIGHT);
		
		//g->SetOpacity(_time);
		//g->SetColor(0x000000);//ADD
		//
		//g->EnableBlackAlphaEffect(_time , 0);

		//int x = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposX;
		//int y = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposY;

		//g->SetChannel(1); 
		////g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

		//g_pGame->load_spriteArray[0]->PaintFrame(g, 0, x, y, 0,  0, 0);

		//g->SetChannel(0); 

		//g->SetARGBColor(0xFFFFFFFF);//ADD
	}
	
}
void cUI::draw_End_Channel()
{
	//if( (g->GetChannel()&CHANNEL_NIGHT ) != CHANNEL_NIGHT)
	//{
	//	//g->SetARGBColor(0xb1000000);
	//	//g->FillRect(0,0,240,320);
	//	//g->SetARGBColor(0xff000000);	
	//	return;
	//}
	//



	//int x = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposX;
	//int y = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposY;

	//
	//g_pGame->load_spriteArray[0]->PaintFrame(g, 0, x, y, 0,  0, 0);

	//g->UnSetChannel(CHANNEL_NIGHT); 

	//g->EnableBlackAlphaEffect(0 , 0);
	

}


void cUI::process_USER_Openning( int message )
{

	if( message == MESSAGE_INIT)
	{
		
		TIME_PAUSE_OFF();

		//g_pGame->Stop_FireWork();//485
		game_sub_state = GAME_STATE_MAP;

		m_lastTileX = -1;
		m_lastTileY = -1;
		m_oldLevelX = -1;
		m_oldLevelY = -1;	

		g_pGame->m_mapX	=  0;
		g_pGame->m_mapY	=  -10;


		g_pGame->ResetCinematic( 0 );
		g_pGame->StartCinematic ( 0 );

		g_pGame->Text_freeText( TEXT_INDEX_GAME );
////		g_pGame->Text_loadTextPack( PACK_TEXT, TEXT_OPENING, TEXT_INDEX_GAME );

//		STRCPY( g_pGame->mascot_currentText, GET_STRING( OPENING_SYNOP_1, TEXT_INDEX_GAME ));

		SPRITE_INIT_PAGE();

		menu_strscroll_count = 0;

		mascot_hide();

		softkey_init(SOFTKEY_SYMBOL_MENU,SOFTKEY_SYMBOL_EMPTY);

	}
	else if( message == MESSAGE_UPDATE)
	{

		g_pGame->UpdateCinematic();

		int _direct  = 0;

		if ( !g_pGame->IsCinematicActive() || KEY_PRESSED(GAME_KEY_POUND) )
		{
		//	g_pGame->EndCinematic(ANIMATION_OPENING);
			g_pGame->goto_map( STATE_DRAW_HOUSE );
			m_StateStory = STORY_OPENNING_END;
		}

		//DBGPRINTF("game_sub_state = %d",game_sub_state);
	}
	else if( message == MESSAGE_PAINT)
	{	

		g->SetColor(0x000000);
		g->FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		g_pGame->drawViewTop();

		SET_STRING_COLOR(0xFFFFFF);
		if ( SPRITE_DRAW_PAGE(g, g_pGame->mascot_currentText, SCREEN_HALF_WIDTH, 145, SCREEN_WIDTH-70, SCREEN_HEIGHT-170, menu_strscroll_count, CGraphics::HCENTER ) )
		{
			menu_strscroll_count++;
		}
	//	else
	//	{
	//		menu_strscroll_count = 0;
	//	}

//		OPENNIG_IMOTICON->PaintFrame( g, FRAME_IMOTICON_SKIP , SCREEN_WIDTH, SCREEN_HEIGHT-5, 0,0,0 ) ;

	}
	else if( message == MESSAGE_EXIT)
	{

		g_pGame->Text_freeText( TEXT_INDEX_GAME );

		SOUND_STOP( );

		FREE_GAMERES();
	}
}



void cUI::process_USER_House( int message )
{

//	if( message == MESSAGE_INIT)
//	{
//		
//		TIME_PAUSE_OFF();
//
//		//g_pGame->Stop_FireWork();//485
//		game_sub_state = GAME_STATE_MAP;
//
//		m_lastTileX = -1;
//		m_lastTileY = -1;
//		m_oldLevelX = -1;
//		m_oldLevelY = -1;	
//
//		Set_Camera_Position(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );
//
//	//	if ( m_StateStory == STORY_OPENNING_END )
//	//	{
//	//		g_pGame->ResetCinematic(0);
//	//		g_pGame->StartCinematic ( 0 );
//	//	}
//
//		b_show_Entity = true;
//
//		g_pGame->Text_freeText( TEXT_INDEX_GAME );
//		g_pGame->Text_loadTextPack( PACK_TEXT, TEXT_OPENING, TEXT_INDEX_GAME );
//
//#ifdef hasShine
//		g_pGame->InitShine();
//#endif
//		mascot_hide();
//
//	//	SET_STRING_COLOR(0x000000);
//
//		softkey_init(SOFTKEY_SYMBOL_MENU,SOFTKEY_SYMBOL_EMPTY);
//
//	}
//	else if( message == MESSAGE_UPDATE)
//	{
//
//		g_pGame->UpdateCinematic();
//
//		if ( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) != NULL)
//		{
//			int _direct  = 0;
//
//			if ( g_pGame->IsCinematicActive() )
//			{
//				if ( !g_pGame->IsCinematicRunning() )
//				{
//					mascot_Keyupdate();
//				}
//			}
//			else 
//			{
//				if ( b_show_Entity )
//				{
//					m_StateStory = STORYL_HOUSEOPENNING_END;
//					// m_StateStory = STORYL_HOUSEBUG_END;
//					Update_Entity_ShowLayer(  );
//					b_show_Entity = false;
//				}
//
//				_direct = Set_KeyEvent();
//				Update_Entity( );
//			}
//						
//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->set_direct(_direct);
//
//			set_move( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , 0 );
//
//			if ( !g_pGame->IsCinematicActive() )
//			{
//				Set_FollowEntity( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , g_pGame->getEntity(GAMESPRITE_CHICK) );
//			}
//
//			Set_Camera_Position(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );
//
//			//update_Zone();
//		}
//
//		//DBGPRINTF("game_sub_state = %d",game_sub_state);
//	}
//	else if( message == MESSAGE_PAINT)
//	{	
//		draw_Start_Channel();
//		g_pGame->updateAndDrawViewTop();		
//		draw_End_Channel();
//		g_pGame->drawClock ();
//		
//		//popup_paint();
//
//		mascot_paint();
//
//	}
//	else if( message == MESSAGE_EXIT)
//	{
//
//	//	SAFE_DEL(Boy_Object);
//
//		g_pGame->Text_freeText( TEXT_INDEX_GAME );
//
//	//	g_pGame->Text_freeText( TEXT_INDEX_MAP );
//
//		SOUND_STOP( );
//
//		FREE_GAMERES();
//
//	}
}



void cUI::process_USER_Map1( int message )
{

//	if( message == MESSAGE_INIT)
//	{
//		TIME_PAUSE_OFF();
//
//		game_sub_state = GAME_STATE_MAP;
//
//		m_lastTileX = -1;
//		m_lastTileY = -1;
//		m_oldLevelX = -1;
//		m_oldLevelY = -1;
//
//	//	g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posX = 100;
//	//	g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posY = 140;
//
//		Set_Camera_Position(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );
//
//		softkey_init(SOFTKEY_SYMBOL_MENU,SOFTKEY_SYMBOL_EMPTY);
//
//		FISHING_EFF->SetCurrentAnimation(0,ANIM_FISHING_EFF_UI_2, true);
//		FISHING_EFF->SetCurrentAnimation(1,ANIM_FISHING_EFF_EFF, false);
//		
//		while( !FISHING_EFF->Is_animDone(1) )
//		{
//			FISHING_EFF->UpdateAnimation(1);
//		}
//
//		for(int i = 0 ; i < FISH_BALL_EA ; i++)
//		{
//			f_ballPos[FISH_BALL_EA + i] = -1;
//		}
//		//////////////
//		//vel = FISH_BALL_MIN_SPEED + ( 40 / 40 ) * (FISH_BALL_MAX_SPEED-FISH_BALL_MIN_SPEED);
//		//f_firePos = 47 + 8; // RND(0,3); 47
//		//f_firePos -= f_firePos%vel;
//		//set_Ball();
//
//		
//
//	}
//	else if( message == MESSAGE_UPDATE)
//	{
////		mascot_Keyupdate();
//		popup_update();
//
////		g_pGame->UpdateCinematic();
//
//		if ( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) != NULL)
//		{
//			int _direct  = 0;
//
//			if ( g_pGame->IsCinematicActive() )
//			{
//				if ( !g_pGame->IsCinematicRunning() )
//				{
//					if( KEY_PRESSED(GAME_KEY_ALL_ACTION))
//					{
//						g_pGame->ResumeCinematics();
//					}
//				}
//			}
//			else 
//			{
//
//				_direct = Set_KeyEvent();
//			}
//			if( fish_Catch <= 0)
//			{
//
//				g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->set_direct(_direct);
//		
//				set_move( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , 0 );
//			}
//
//			if ( !g_pGame->IsCinematicActive() )
//			{
//				Set_FollowEntity( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , g_pGame->getEntity(GAMESPRITE_CHICK) );
//			}
//
//			Set_Camera_Position(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );
//
//			//update_Zone();
//
//			Update_Entity( );
//
//			if(sp_BFishing == 1)
//			{
//				if(KEY_PRESSED(GAME_KEY_1))
//				{
//					sp_BFishing = 2;
//
//					int setAniNumber = ANIM_MAINCHARACTER_FISHING_BASIC_DOWN ;//+ g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_dirBefore-1;				
//					g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_boby,setAniNumber);	
//					CHAR_PAUSE_OFF();
//				}
//				else if(KEY_PRESSED(GAME_KEY_2))
//				{
//					sp_BFishing = 3;
//
//					int setAniNumber = ANIM_MAINCHARACTER_NET_BASIC_DOWN ;//+ g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_dirBefore-1;				
//
//					g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_boby,setAniNumber);	
//					CHAR_PAUSE_OFF();
//				}
//				else if(KEY_PRESSED(GAME_KEY_3))
//				{
//					sp_BFishing = 0;
//					CHAR_PAUSE_OFF();
//					SET_FLAG(g_pGame->m_CharAbility, CHAR_RAPID_FOOD);
//					
//				}
//				else if(KEY_PRESSED(GAME_KEY_4))
//				{
//					sp_BFishing = 0;
//					CHAR_PAUSE_OFF();
//				}
//				//if( KEY_PRESSED(GAME_KEY_ALL_UP) )
//				//{
//
//				//}
//				//else if( KEY_PRESSED(GAME_KEY_ALL_DOWN) )
//				//{
//
//				//}
//				//else if( KEY_PRESSED(GAME_KEY_MENU_ALL_ACTION) )
//				//{
//				//	sp_BFishing = 2;
//
//				//	int setAniNumber = ANIM_MAINCHARACTER_FISHING_BASIC_DOWN ;//+ g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_dirBefore-1;				
//
//				//	g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_boby,setAniNumber);	
//				//	g_pGame->m_chrMove_pause = false;
//				//}
//
//			}
//			else if(sp_BFishing == 2 || sp_BFishing == 3)
//			{
//				if ( ! (g_pGame->m_colMap_water > 0)  )
//				{
//					sp_BFishing = 0;
//				}
//			}
//			else if(sp_BFishing == 4)
//			{
//				if ( ! (g_pGame->m_colMap_water > 0)  )
//				{
//					sp_BFishing = 0;
//				} 
//				if( !g_pGame->getEntity(17)->isAnimOver(0) )
//				{				
//					switch(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->getCurrentAnim(CHARSLOT::k_slot_boby))
//					{
//						case ANIM_MAINCHARACTER_NET_BASIC_DOWN:
//						case ANIM_MAINCHARACTER_NET_BASIC_DOWN+4: 
//							g_pGame->getEntity(17)->m_posY += 4;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_UP:
//						case ANIM_MAINCHARACTER_NET_BASIC_UP+4: 
//							g_pGame->getEntity(17)->m_posY -= 4;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_RIGHT:
//						case ANIM_MAINCHARACTER_NET_BASIC_RIGHT+4: 
//							g_pGame->getEntity(17)->m_posX += 4;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_LEFT:
//						case ANIM_MAINCHARACTER_NET_BASIC_LEFT+4: 
//							g_pGame->getEntity(17)->m_posX -= 4;
//							break;
//					}
//				}
//				else
//				{
//					sp_BFishing = 5;				
//					
//					//g_pGame->getEntity(17)->setAniLoop(0,false);
//				}
//				if(g_pGame->getEntity(17)->m_OFFposX < 0 || g_pGame->getEntity(17)->m_OFFposX > SCREEN_WIDTH
//					|| g_pGame->getEntity(17)->m_OFFposY < 0 || g_pGame->getEntity(17)->m_OFFposY > SCREEN_HEIGHT )
//				{
//					sp_BFishing = 5;	
//					g_pGame->s_cUI->fish_Catch = -1;
//				}
//
//
//			}
//			
//
//			if (sp_BFishing == 0 && g_pGame->m_colMap_water > 0  )
//			{
//				if( KEY_PRESSED(GAME_KEY_MENU_ALL_ACTION) )
//				{
//					sp_BFishing = 1; 
//					CHAR_PAUSE_ON();
//				}
//			}
//			else if(sp_BFishing == 3 && g_pGame->m_colMap_water > 0 )
//			{
//				if(KEY_PRESSED_OR_HELD(GAME_KEY_MENU_ALL_ACTION))
//				{
//					
//
//				}
//				
//				if(KEY_RELEASE(GAME_KEY_MENU_ALL_ACTION) )
//				{
//					CHAR_PAUSE_ON();
//					sp_BFishing = 4;
//					
//					g_pGame->getEntity(17)->unsetSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
//
//					g_pGame->getEntity(17)->m_posX = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posX;
//					g_pGame->getEntity(17)->m_posY = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posY;
//
//					switch(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->getCurrentAnim(CHARSLOT::k_slot_boby))
//					{
//						case ANIM_MAINCHARACTER_NET_BASIC_DOWN:
//						case ANIM_MAINCHARACTER_NET_BASIC_DOWN+4: 
//							g_pGame->getEntity(17)->m_posY += 25;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_UP:
//						case ANIM_MAINCHARACTER_NET_BASIC_UP+4: 
//							g_pGame->getEntity(17)->m_posY -= 25;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_RIGHT:
//						case ANIM_MAINCHARACTER_NET_BASIC_RIGHT+4: 
//							g_pGame->getEntity(17)->m_posX += 25;
//							break;
//						case ANIM_MAINCHARACTER_NET_BASIC_LEFT:
//						case ANIM_MAINCHARACTER_NET_BASIC_LEFT+4: 
//							g_pGame->getEntity(17)->m_posX -= 25;
//					}
//					VIBRATE(500);
//					g_pGame->getEntity(17)->setAniLoop(0,false);
//					g_pGame->getEntity(17)->setAnim(0,0);					
//				}
//			}			
//
//			FISHING_EFF->UpdateAnimation(0);	
//			if( !FISHING_EFF->Is_animDone(1) )
//			{
//				FISHING_EFF->UpdateAnimation(1);
//			}
//
//		}
//
//
//	}
//	else if( message == MESSAGE_PAINT)
//	{	
//			
//		draw_Start_Channel();
//
//		g_pGame->updateAndDrawViewTop();
//		
//		//g->EnableGrayEffect();
//		
//		draw_End_Channel();
//		
//		
//
//		if(sp_BFishing == 1)
//		{
//			//g->SetARGBColor(0xB4000000);
//			//g->SetARGBColor(0xff000000);	
//			
//			g->SetColor(0x8c6d00);	
//			g->DrawRect(SCREEN_HALF_WIDTH-50,SCREEN_HALF_HEIGHT - 60,100,120);
//			g->SetColor(0xffc600);	
//			g->FillRect(SCREEN_HALF_WIDTH-50 + 1,SCREEN_HALF_HEIGHT - 60 + 1,100 - 1,120 - 1);
//
//			//g->SetARGBColor(0xffffffff);
//			DRAW_KORSTR(g,"1 . NET", SCREEN_HALF_WIDTH-40, SCREEN_HALF_HEIGHT - 50, Graphics::TOP | Graphics::LEFT, 0xffffff);
//			DRAW_KORSTR(g,"2 . casting net", SCREEN_HALF_WIDTH-40, SCREEN_HALF_HEIGHT - 50 + 20, Graphics::TOP | Graphics::LEFT, 0xffffff);
//			DRAW_KORSTR(g,"3 . Rapid Walk", SCREEN_HALF_WIDTH-40, SCREEN_HALF_HEIGHT - 50 + 40, Graphics::TOP | Graphics::LEFT, 0xffffff);
//			DRAW_KORSTR(g,"4 . EXIT", SCREEN_HALF_WIDTH-40, SCREEN_HALF_HEIGHT - 50 + 60, Graphics::TOP | Graphics::LEFT, 0xffffff);
//		}
//		
//		
//		if ( fish_Catch > 0 && g_pGame->m_colMap_water > 0  )
//		{
//			
//
//			int x = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposX;
//			int y = g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_OFFposY - 50;
//			if(x < 60)
//			{
//				x += (60-x); 
//			}
//			else if(x > SCREEN_WIDTH-60)
//			{
//				x -= (60 - (SCREEN_WIDTH - x));
//			}
//
//			//drawFishing(x,y);			
//			
//			fish_Game(x,y);			
//			
//
//		}
//		else if(fish_Catch == -1)
//		{
//			fish_Catch = 0;
//			sp_BFishing = 3;
//			g_pGame->getEntity(17)->setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
//			CHAR_PAUSE_OFF();
//		}
//
//		g_pGame->Draw_MainUI();
//
//		g_pGame->drawClock ();
//
//		softkey_paint(false);
//		
//
//	}
//	else if( message == MESSAGE_EXIT)
//	{
//
//	//	SAFE_DEL(Boy_Object);
//
//		SOUND_STOP( );
//
//		FREE_GAMERES();
//
//	}
}







void cUI::process_USER_Chapter( int message )
{
	//if( message == MESSAGE_INIT)
	//{
	//	
	//	TIME_PAUSE_OFF();

	//	//g_pGame->Stop_FireWork();//485
	//	//game_sub_state = GAME_STATE_MAP;

	//	m_lastTileX = -1;
	//	m_lastTileY = -1;
	//	m_oldLevelX = -1;
	//	m_oldLevelY = -1;	

	//	Set_Camera_Position(g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );



	////	g_pGame->SaveLoad_MapRecord(0, false );
	//	g_pGame->Get_UserMapRecord( 0 );
	//	


	////	if ( m_StateStory == STORY_OPENNING_END )
	////	{
	////		g_pGame->ResetCinematic(0);
	////		g_pGame->StartCinematic ( 0 );
	////	}

	////	g_pGame->Text_freeText( TEXT_INDEX_GAME );
	////	g_pGame->Text_loadTextPack( PACK_TEXT, TEXT_OPENING, TEXT_INDEX_GAME );

	////	g_pGame->InitShine();	


	//	build_state_mode = BUILD_MODE_INIT;


	//	mascot_hide();

	////	SET_STRING_COLOR(0x000000);

	//	softkey_init(SOFTKEY_SYMBOL_MENU,SOFTKEY_SYMBOL_EMPTY);

	//}
	//else if( message == MESSAGE_UPDATE)
	//{

	//	g_pGame->UpdateCinematic();

	//	if ( build_state_mode == BUILD_MODE_INIT )
	//	{
	//		int _direct  = 0;
	//		_direct = Set_KeyEvent();
	//		Update_Entity( );

	//		g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->set_direct(_direct);
	//		set_move( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , 0 );
	//	
	//		Set_FollowEntity( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) , g_pGame->getEntity(GAMESPRITE_CHICK) );
	//	
	//		Set_Camera_Position( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR) );


	//			if ( KEY_PRESSED(GAME_KEY_MENU_PRE_ACTION) )
	//			{
	//				build_state_mode = BUILD_MODE_MENU;
	//				build_staet_type = 0;
	//			}

	//	}
	//	else if ( build_state_mode == BUILD_MODE_MENU )
	//	{
	//			if( KEY_PRESSED(GAME_KEY_ALL_UP) )
	//			{
	//				build_staet_type++;	
	//				if ( build_staet_type > 8 )
	//				{
	//					build_staet_type = 0;
	//				}
	//			}
	//			else if( KEY_PRESSED(GAME_KEY_ALL_DOWN) )
	//			{
	//				build_staet_type--;

	//				if ( build_staet_type < 0 )
	//				{
	//					build_staet_type = 8;
	//				}
	//			}
	//			else if ( KEY_PRESSED(GAME_KEY_MENU_ALL_ACTION) )
	//			{
	//				build_state_mode = BUILD_MODE_ACTIVE;

	//				build_posX = (g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posX);
	//				build_posY = (g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_posY);

	//			}
	//			else if ( KEY_PRESSED(GAME_KEY_MENU_PRE_ACTION) )
	//			{
	//				build_state_mode = BUILD_MODE_INIT;
	//			}
	//	}
	//	else if ( build_state_mode == BUILD_MODE_ACTIVE )
	//	{

	//			if( KEY_PRESSED(GAME_KEY_ALL_LEFT) )
	//			{
	//				build_posX -= TILE_W;
	//			}
	//			else if( KEY_PRESSED(GAME_KEY_ALL_RIGHT) )
	//			{
	//				build_posX += TILE_W;
	//			}
	//			else if( KEY_PRESSED(GAME_KEY_ALL_UP) )
	//			{
	//				build_posY -= TILE_H;
	//			}
	//			else if( KEY_PRESSED(GAME_KEY_ALL_DOWN) )
	//			{
	//				build_posY += TILE_H;
	//			}

	//			if ( build_posX < 0 ) build_posX = 0;
	//			else if ( build_posX > (g_pGame->m_tileMapW*16) ) build_posX = (g_pGame->m_tileMapW*16);
	//			if ( build_posY < 0 ) build_posY = 0;
	//			else if ( build_posY > (g_pGame->m_tileMapH*16) ) build_posY = (g_pGame->m_tileMapH*16);

	//			Set_Camera_Position( build_posX, build_posY );

	//			if ( KEY_PRESSED(GAME_KEY_MENU_PRE_ACTION) )
	//			{
	//				build_state_mode = BUILD_MODE_INIT;
	//			}
	//			else if ( KEY_PRESSED(GAME_KEY_MENU_ALL_ACTION) )
	//			{

	//				if ( ENTITY::k_max > g_pGame->m_actorsMax_count )
	//				{
	//					short*  params= GL_NEW short[ACTOR_MAPOBJECT_MAX];

	//					params[ACTOR_GTSID] = GAMESPRITE_BUILDING;
	//					params[ACTOR_GAMEID] = 0;			//STATE
	//					params[ACTOR_POSX]	= build_posX;//<<4;//TILE_W;
	//					params[ACTOR_POSY]	= build_posY;//<<4;//TILE_H;
	//					params[ACTOR_ANIID] = build_staet_type;
	//					params[ACTOR_FLAGS] = 0;
	//					params[ACTOR_COUNT] = g_pGame->m_actorsNew_count;

	//					g_pGame->Add_UserEntity( params, true ) ;

	//			//		SAFE_DEL(g_pGame->getEntity(g_pGame->m_actorsMax_count));
	//			//		g_pGame->getEntity(g_pGame->m_actorsMax_count) = GL_NEW cEntity( params[ACTOR_GTSID], 1 );

	//			//		g_pGame->getEntity(g_pGame->m_actorsMax_count++)->init(params[ACTOR_FLAGS], params[ACTOR_POSX], params[ACTOR_POSY], params, ACTOR_MAPOBJECT_MAX);

	//			//		g_pGame->m_actorsNew_count ++;

	//					SAFE_DEL_ARRAY(params);
	//				}
	//				else 
	//				{
	//					build_state_mode = BUILD_MODE_INIT;
	//				}
	//			}

	//			
	//			
	//	}


	//}
	//else if( message == MESSAGE_PAINT)
	//{	

	//	g_pGame->updateAndDrawViewTop();
	//	
	//	if ( build_state_mode == BUILD_MODE_MENU )
	//	{

	//		g->SetColor(0x8c6d00);	
	//		g->DrawRect(SCREEN_HALF_WIDTH-50,SCREEN_HALF_HEIGHT - 60,100,120);
	//		g->SetColor(0xffc600);	
	//		g->FillRect(SCREEN_HALF_WIDTH-50 + 1,SCREEN_HALF_HEIGHT - 60 + 1,100 - 1,120 - 1);
	//		
	//		RES_BUILD->PaintFrame( g, build_staet_type , SCREEN_HALF_WIDTH , SCREEN_HALF_HEIGHT+20, 0, 0, 0);
	//	}
	//	else if ( build_state_mode == BUILD_MODE_ACTIVE )
	//	{

	////	si->m_posX = (m_posX - ox) + x;
	////	si->m_posY = (m_posY - oy) + y;

	//		RES_BUILD->PaintFrame( g, build_staet_type , build_posX-g_pGame->m_mapX, build_posY-g_pGame->m_mapY, 0, 0, 0);


	//		//	Set_Camera_Position( build_posX*20, build_posY*20 );
	//	}


	////	g_pGame->drawClock ();
	////	draw_Channel();
	//	//popup_paint();

	////	mascot_paint();

	//}
	//else if( message == MESSAGE_EXIT)
	//{

	////	SAFE_DEL(Boy_Object);

	////	g_pGame->Text_freeText( TEXT_INDEX_GAME );

	////	g_pGame->Text_freeText( TEXT_INDEX_MAP );

	//	SOUND_STOP( );

	//	FREE_GAMERES();

	//}
}


void cUI::draw_Interface()
{
	int pos_x = 0;
	int pos_y = 0;
	Draw_Number(g_pGame->COMMON_SPRITE_NUMBER,10,pos_y,15,0,DIRECT_LEFT,4);

}




void cUI::fish_Game(int _x , int _y)
{
	int i;
	for(i = 0 ; i < 2 ; i++)
	{
		f_ballPos[i] += f_ballVel[i];

		if(f_ballPos[i] < 0)
		{
			f_ballVel[i] = vel/(2-i);
		}
		else if(f_ballPos[i] > 47<<1 )
		{
			f_ballVel[i] = -vel/(2-i);
		}
	}

	if( KEY_PRESSED(GAME_KEY_ALL_ACTION) )
	{
		if(isInFireZone(1))
		{
//			FISHING_EFF->ClearAnimation(1,false);	
			f_ballVel[1] = 0;
			f_ballVel[0] = 0;

//			FONT_EFF->SetCurrentAnimation(0,ANIM_FONT_EFFECT_GOOD_1 + g_pGame->random(0,1), true);

			isFire = 1;
		}
		else
		{
			f_ballVel[0] = 0;
			f_ballVel[1] = 0;

//			FONT_EFF->SetCurrentAnimation(0,ANIM_FONT_EFFECT_BAD_1 + g_pGame->random(0,1), true);
			isFire = 2;
		}
	}
	
	if( !(isFire == 2 || (isFire == 1 /*&& FISHING_EFF->Is_animDone(1)*/) ) )
	{
//		FISHING_EFF->PaintFrame(g, FRAME_FISHING_EFF_BG, _x  , _y, 0,  0, 0);
//		FISHING_EFF->PaintFrame(g, FRAME_FISHING_EFF_FIRE, _x - 47 + f_ballPos[0]  , _y, 0,  0, 0);
			
			//if(f_ballVel[1] != 0) 
			if( isFire == 0 )
			{
//				FISHING_EFF->PaintFrame(g, FRAME_FISHING_EFF_ARROW_LEFT, _x - 47  + f_ballPos[1] , _y , 0,  0, 0);

			}	
		

//		if( !FISHING_EFF->Is_animDone(1) )
		{
			//FISHING_EFF->PaintAnimation(g, 1, _x - 47  + f_ballPos[0] , _y, 0, 0, 0);	
		}

		//FISHING_EFF->PaintAnimation(g, 0, _x, _y, 0, 0, 0);	
	}

//	if(!FONT_EFF->Is_animDone(0))
	{
//		FONT_EFF->UpdateAnimation(0);
//		FONT_EFF->PaintAnimation(g, 0, _x , _y - 30 , 0, 0, 0);	
		setBall_cnt++;
		if(setBall_cnt > 25)
		{
			fish_Catch = 0;
//			FONT_EFF->setAnimStop(0);
			if(sp_BFishing == 5)
			{				
				g_pGame->getEntity(17)->setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
				sp_BFishing = 3;
				CHAR_PAUSE_OFF();
			}
		}
	}
}




void cUI::fish_Game1(int _x , int _y)
{
	int i;

	//#define FISH_BALL_EA	3 

	//f_firePos //
	//f_ballPos[2*FISH_BALL_EA]
	//f_ballVel[FISH_BALL_EA]
	
	//set_ball()
	
	isFire = -1;

	if( KEY_PRESSED(GAME_KEY_UP))
	{
//		isFire = FRAME_FISHING_EFF_ARROW_UP;
	}
	else if( KEY_PRESSED(GAME_KEY_DOWN) )
	{
//		isFire = FRAME_FISHING_EFF_ARROW_DOWN;
	}
	else if( KEY_PRESSED(GAME_KEY_LEFT) )
	{
//		isFire = FRAME_FISHING_EFF_ARROW_LEFT;
	}
	else if( KEY_PRESSED(GAME_KEY_RIGHT) )
	{
//		isFire = FRAME_FISHING_EFF_ARROW_RIGHT;
	}

	////////////////////////

	for(i = 0 ; i < FISH_BALL_EA ; i++)
	{
		if( f_ballPos[FISH_BALL_EA + i] > -1 )
		{	
			
			

			f_ballPos[i] += vel; //f_ballVel[i];
			//f_ballPos[1 + i*2] += f_ballVel[i];
			if(f_ballPos[i] == vel *  (8 + (10 - vel)* (2 - (vel/5))   ) ) // (12 + 10 - vel)
			{
				set_Ball();

			}	

			if(f_ballPos[i] > 94)
			{
				f_ballVel[i] = 0;	
				f_ballPos[FISH_BALL_EA + i] = -1;
				
			}
			if(isFire > -1 && f_ballVel[i] != 0 && isInFireZone(i) )
			{
				if(isFire == f_ballPos[FISH_BALL_EA + i])
				{
					f_ballVel[i] = 0;

//					FISHING_EFF->ClearAnimation(1,false);	
				}
			}
		}
		
	}


//	FISHING_EFF->PaintFrame(g, FRAME_FISHING_EFF_BG, _x - 47 + f_firePos  , _y, 0,  0, 0);
//	FISHING_EFF->PaintFrame(g, FRAME_FISHING_EFF_FIRE, _x - 47 + f_firePos  , _y, 0,  0, 0);
	for(i = 0 ; i < FISH_BALL_EA ; i++)
	{	
		if(f_ballVel[i] != 0) 
		{
			FISHING_EFF->PaintFrame(g, f_ballPos[FISH_BALL_EA + i], _x - 47  + f_ballPos[i] , _y , 0,  0, 0);
			
		}	
	}

//	if( !FISHING_EFF->Is_animDone(1) )
	{
//		FISHING_EFF->PaintAnimation(g, 1, _x - 47  + f_firePos , _y, 0, 0, 0);	
	}

//	FISHING_EFF->PaintAnimation(g, 0, _x, _y, 0, 0, 0);	
	
	


}
void cUI::set_init_Ball()
{
	vel = FISH_BALL_MIN_SPEED + ( fish_Catch / 40 ) * (FISH_BALL_MAX_SPEED-FISH_BALL_MIN_SPEED);
	f_firePos = 47 + 8; // RND(0,3); 47
	f_firePos -= f_firePos%vel;
	setBall_cnt = 0;
	set_Ball();
	/////aaa

	f_ballPos[0] = 47;
	
	f_ballVel[0]= -vel;
	f_ballVel[1]= vel;
	isFire = 0;
}

void cUI::set_Ball()
{
	int i;
	setBall_cnt++;
	if(setBall_cnt > 5)
	{
		fish_Catch = 0;
		return;
	}
	for(i = 0 ; i < FISH_BALL_EA ; i++)
	{
		if( f_ballPos[FISH_BALL_EA + i] == -1)
		{		
			f_ballPos[i] = 0;
//			f_ballPos[FISH_BALL_EA + i] = FRAME_FISHING_EFF_ARROW_LEFT+ RND(0,3) ;
			f_ballVel[i] = vel;

			break;
		}
	}
}

bool cUI::isInFireZone(int index)
{
	bool _temp = false;

	//if( f_ballPos[index] >= f_firePos - (FISH_BALL_SIZEW>>1) &&  f_ballPos[index] <= f_firePos + (FISH_BALL_SIZEW>>1))
	if(f_ballPos[index] >= f_ballPos[0] - (FISH_BALL_SIZEW>>1) - ABS(f_ballVel[1]) &&  f_ballPos[index] <= f_ballPos[0] + (FISH_BALL_SIZEW>>1) + ABS(f_ballVel[1]) )
	{
		_temp = true;
	}	

	return _temp;
}



void cUI::Set_Chage_map( int _collnum )
{
	
		switch(_collnum)
		{
			case COL_TILES::k_door0:

				if ( g_pGame->m_map_kind == WORLD_MAP1 )
				{
					g_pGame->goto_map( STATE_DRAW_HOUSE );
				}
				else if ( g_pGame->m_map_kind == HOUSE_MYHOME )
				{
					g_pGame->goto_map( STATE_DRAW_MAP1 );
				}
				else if ( g_pGame->m_map_kind == CHAPTER_1 )
				{
					g_pGame->goto_map( STATE_DRAW_MAP1 );
				}

			//	pushState(STATE_DRAW_MAP,true);
			//	g_pGame->hero_mosX = 380*TILE_W/20;
			//	g_pGame->hero_mosY = 500*TILE_W/20;
				break;

			case COL_TILES::k_door1:

				if ( g_pGame->m_map_kind == WORLD_MAP1 )
				{
					g_pGame->goto_map( STATE_DRAW_CHAPTER );
				}

			//	g_pGame->m_map_kind = MAP_WORLD;
			//	pushState(STATE_DRAW_MAP,true);
			//	g_pGame->hero_mosX = 716*TILE_W/20;
			//	g_pGame->hero_mosY = 491*TILE_W/20;
			//	g_pGame->goto_map( STATE_DRAW_HOUSE );

				break;
		}	
	
}




void cUI::update_Zone()
{
	for(int i = ZONES::k_start ; i < ZONES::k_max ; i++)
	{
		if(g_pGame->collideWithZone(i))
		{				
			switch(i)
			{
				case ZONES::k_door_0:

					if ( g_pGame->m_map_kind == WORLD_MAP1 )
					{
						g_pGame->goto_map( STATE_DRAW_HOUSE );
					}
					else if ( g_pGame->m_map_kind == HOUSE_MYHOME )
					{
						g_pGame->goto_map( STATE_DRAW_MAP1 );
					}
				//	pushState(STATE_DRAW_MAP,true);
				//	g_pGame->hero_mosX = 380*TILE_W/20;
				//	g_pGame->hero_mosY = 500*TILE_W/20;
					break;

				case ZONES::k_door_1:

					if ( g_pGame->m_map_kind == WORLD_MAP1 )
					{
						g_pGame->goto_map( STATE_DRAW_CHAPTER );
					}

				//	g_pGame->m_map_kind = MAP_WORLD;
				//	pushState(STATE_DRAW_MAP,true);
				//	g_pGame->hero_mosX = 716*TILE_W/20;
				//	g_pGame->hero_mosY = 491*TILE_W/20;
				//	g_pGame->goto_map( STATE_DRAW_HOUSE );

					break;
			}
		}
	}// End for(int i = ZONES::k_start ; i < ZONES::k_max ; i++){
}






//Module_Move.hpp
//int		m_CameraX;
//int		m_CameraY;
// Auto move variable
int		auto_move;

cUI::cUI()
{
	moveState = MOVESTATE_WALK ;		
	stackA = -1;	
	stackCnt = 0;	
	stackB = -1;
//	change_active = false;
//	change_size = 0;	
//	change_direct = 0;	
//	change_Maxsize = 0;	
//	change_count = 0;	
//	change_replay = 0;

//	displayResetInfo = false;

//	player = GL_NEW cXPlayerMenus(g_pGame,g_pGame->jFont);
	//if(player)
	//{
	//	//MC_knlCreateSharedBuf( (const M_Char *)"pXPlayer", sizeof(cXPlayerMenus*) );
	//	//player = new cXPlayerMenus( instance_, cKFont_ );
	//	//minh_dang *(cXPlayerMenus**)MC_GETDPTR((void*)MC_knlGetSharedBuf((const M_Char *)"pXPlayer")) = player;
	//	g_pGame->Xplayer_share_buff = (void *)player ;
	//}
}


cUI::~cUI()
{
//	SAFE_DEL_ARRAY(menu_List);
	SAFE_DEL_ARRAY(menu_str);
//	SAFE_DEL_ARRAY_OBJ(npc_Object,npc_Object_length);
//	SAFE_DEL_ARRAY(Draw_Order);
//	SAFE_DEL_ARRAY(temp_Order);
	SAFE_DEL_ARRAY(str_version);
//	cXPlayerMenus *vPtr = cXPlayerMenus::getInstance();
//	SAFE_DEL(vPtr);
//	SAFE_DEL(g_pGame->Xplayer_share_buff);
	//MC_knlDestroySharedBuf( (void*)MC_knlGetSharedBuf() ); 
}

int cUI::check_move( cEntity* _obj, int _posX, int _posY  )
{

	if(g_pGame->m_mapCol != NULL)
	{
		int rect[4];
		int temp_move_col;

		g_pGame->getCollisionRect(rect , _obj );

		temp_move_col = g_pGame->canDropObject(rect,_posX,_posY);

		return temp_move_col;
	}

	return COL_TILES::k_oob_null;
}



void cUI::set_move( cEntity* _obj , int _auto_move)
{
//	if(g_pGame->m_chrMove_pause) return;
//	int _moveX  = 0, _moveY = 0;
//	int move_vel = (moveState == MOVESTATE_RUN)? 3:0 ;
//	int _col_tile = 0;
//
//	
//
//	if( moveState == MOVESTATE_STOP )
//	{
//		move_vel = -1;
//	}
//	else if ( g_pGame->m_colMap_water > 0 )
//	{
//		g_pGame->m_colMap_count++;
//		if ( g_pGame->m_colMap_count % (g_pGame->m_colMap_water+2) == 0)
//		{
//			g_pGame->m_colMap_count = 0;
//			move_vel = -1 ;
//		}
//		else 
//		{
//			move_vel = -2 ;
//		}
//	}
//	if( (g_pGame->m_CharAbility & CHAR_RAPID_FOOD) != 0)
//	{
//		move_vel += 1;
//	}
//
//	switch ( _obj->m_dir )
//	{
//		case DIRECT_LEFT: 			_moveX = -BOY_MOVE-move_vel;		break;
//		case DIRECT_RIGHT:			_moveX =  BOY_MOVE+move_vel;		break;
//		case DIRECT_UP:				_moveY = -BOY_MOVE-move_vel;		break;
//		case DIRECT_DOWN:			_moveY =  BOY_MOVE+move_vel;		break;
//	}
//
//
//	if ( _obj->m_posX+_moveX < MOVE_LIMITE_STARTX || _obj->m_posX + _moveX > MOVE_LIMITE_ENDX )
//	{
//		_moveX = 0;
//	}
//	else if ( _obj->m_posY+_moveY < MOVE_LIMITE_STARTY || _obj->m_posY+_moveY > MOVE_LIMITE_ENDY )
//	{
//		_moveY = 0;
//	}
//
//	_obj->m_posX += _moveX;
//	_obj->m_posY += _moveY;
//
//	_col_tile = check_move( _obj, _obj->m_posX, _obj->m_posY );
//
//	g_pGame->m_colMap_water = 0;
//
//	if( _col_tile != COL_TILES::k_oob_null)
//	{
//		if( _col_tile > COL_TILES::k_can_move && _col_tile < COL_TILES::k_door0 )
//		{
//			// check direction
//			_obj->m_posX -= _moveX;
//			_obj->m_posY -= _moveY;
//
//			g_pGame->m_colMap_hold = false;
//			
//			if( _col_tile == COL_TILES::k_cant_move_stop )
//			{
//				g_pGame->m_colMap_hold = true;
//			}
//			else 
//			{
//				if(_auto_move == 0)
//				{	
//					int tempx = 0;
//					int tempy = 0;
//					int _coltemp = 0;
//
//					_auto_move ++;
//
//					if(_moveX != 0)
//					{
//						for(int _i = 1 ; _i < 100 ; _i++)
//						{	
//							_coltemp = check_move( _obj, _obj->m_posX+_moveX, _obj->m_posY+_moveY+(2*_i));
//							//if(check_move( _obj, _obj->m_posX+_moveX, _obj->m_posY+_moveY+(2*_i) ) == COL_TILES::k_can_move)
//							if( _coltemp == COL_TILES::k_can_move || (_coltemp >= COL_TILES::k_door0 && _coltemp <= COL_TILES::k_door3) )
//							{								
//								_obj->m_dir = DIRECT_DOWN ;
//								break;
//							}
//
//							tempy = ((_obj->m_posY+_moveY-(2*_i)) < 0 )?0:(_obj->m_posY+_moveY-(2*_i));
//
//							_coltemp = check_move( _obj,_obj->m_posX+_moveX, tempy );
//							//if( check_move( _obj,_obj->m_posX+_moveX, tempy ) == COL_TILES::k_can_move )
//							if( _coltemp == COL_TILES::k_can_move || (_coltemp >= COL_TILES::k_door0 && _coltemp <= COL_TILES::k_door3) )
//							{
//								_obj->m_dir = DIRECT_UP ;
//								break;									
//							}							
//						}
//					}
//					else if(_moveY != 0)
//					{
//						for(int _i = 1 ; _i < 100 ; _i++)
//						{			
//							_coltemp = check_move( _obj, _obj->m_posX + _moveX + (2*_i), _obj->m_posY + _moveY );
//							//if(check_move( _obj, _obj->m_posX + _moveX + (2*_i), _obj->m_posY + _moveY ) == COL_TILES::k_can_move)
//							if( _coltemp == COL_TILES::k_can_move || (_coltemp >= COL_TILES::k_door0 && _coltemp <= COL_TILES::k_door3) )
//							{								
//								_obj->m_dir = DIRECT_RIGHT ;								
//								break;
//							}
//
//							tempx = ((_obj->m_posX+_moveX-(2*_i))< 0 )?0:(_obj->m_posX+_moveX-(2*_i));
//							_coltemp = check_move( _obj, tempx  ,_obj->m_posY + _moveY );
//							//if(check_move( _obj, tempx  ,_obj->m_posY + _moveY ) == COL_TILES::k_can_move)
//							if( _coltemp == COL_TILES::k_can_move || (_coltemp >= COL_TILES::k_door0 && _coltemp <= COL_TILES::k_door3) )
//							{
//								_obj->m_dir = DIRECT_LEFT ;
//								break;									
//							}
//						}
//					}
//					set_move(_obj , _auto_move);
//				}
//			}
//		}
//		else if ( _col_tile >= COL_TILES::k_door0 && _col_tile <= COL_TILES::k_door3 )
//		{
//				
//			_obj->setFlag(DFLAGS::HIDE_LAYER);
//			Set_Chage_map( _col_tile );
//			//return;
//		}
//		else if ( _col_tile >= COL_TILES::k_water1 )
//		{
//			g_pGame->m_colMap_water = _col_tile;
//			
//			//_obj->m_renderer[CHARSLOT::k_slot_etc]->m_posOffY = -((_col_tile-COL_TILES::k_water1)*2);
//
//			moveState = MOVESTATE_WALK;
//		}		
//
//		if(g_pGame->m_colMap_water > 0)
//		{
//			_obj->setSpriteLayer(CHARSLOT::k_slot_etc,   LAYER::k_inactive);
//		}
//		else
//		{
//			_obj->setSpriteLayer(CHARSLOT::k_slot_etc,   LAYER::k_hide);
//		}
//	}
//
////	if ( g_pGame->m_colMap_hold )
////	{
////		_obj->m_dir = DIRECT_NULL;
////	}
//
//	//if(moveState == MOVESTATE_WALK )//g_pGame->getEntity(GAMESPRITE_MAIN_CHAR).isAnimOver(CHARSLOT::k_slot_etc))
//	//{
//	//	switch ( _obj->m_dir )
//	//	{
//	//	case DIRECT_LEFT:
//	//		g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_etc,BOY_GAME_FACE_LEFT_BLINK_EYE_ANI_INDEX);
//	//		break;
//	//	case DIRECT_RIGHT:
//	//		g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_etc,BOY_GAME_FACE_RIGHT_BLINK_EYE_ANI_INDEX);
//	//		break;
//	//	case DIRECT_DOWN:
//	//		g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_etc,BOY_GAME_FACE_DOWN_BLINK_EYE_ANI_INDEX);
//	//		break;
//	//	case DIRECT_UP:
//	//		g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_etc,ANIM_EMPTY);
//	//		break;
//	//	}
//	//}
//	//else
//	//{
//	//	g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_etc,ANIM_EMPTY);
//	//}
//
//
//	if ( g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->isAnimOver(CHARSLOT::k_slot_boby) || (_obj->m_dirBefore !=  _obj->m_dir) )
//	{
//		int setAniNumber = 0;
//		switch ( _obj->m_dir )
//		{
//		case DIRECT_LEFT:
//
//			if(moveState == MOVESTATE_WALK)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_WALK_LEFT;
//				
//				if(sp_BFishing == 2 && g_pGame->m_colMap_water > 0)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_FISHING_BASIC_LEFT;
//					_obj->setAnim(CHARSLOT::k_slot_etc,ANIM_MAINCHARACTER_FISHINGEFFECT_LEFT_2);
//				}
//				else if(sp_BFishing == 3)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_NET_BASIC_LEFT;
//				}
//				
//			}
//			else if(moveState == MOVESTATE_RUN)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_RUN_LEFT;
//	//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_LEFT_ANI_INDEX);
//			}							
//
//			break;
//		case DIRECT_RIGHT:
//
//			if(moveState == MOVESTATE_WALK)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_WALK_RIGHT;
//
//				if(sp_BFishing == 2 && g_pGame->m_colMap_water > 0)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_FISHING_BASIC_LEFT;
//					_obj->setAnim(CHARSLOT::k_slot_etc,ANIM_MAINCHARACTER_FISHINGEFFECT_RIGHT_2);
//				}		
//				else if(sp_BFishing == 3)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_NET_BASIC_LEFT;
//				}
//			}
//			else if(moveState == MOVESTATE_RUN)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_RUN_RIGHT;
//	//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_RIGHT_ANI_INDEX);
//			}
//			break;
//
//		case DIRECT_UP:
//			if(moveState == MOVESTATE_WALK)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_WALK_UP ;
//
//				if(sp_BFishing == 2 && g_pGame->m_colMap_water > 0)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_FISHING_BASIC_LEFT;
//					_obj->setAnim(CHARSLOT::k_slot_etc,ANIM_MAINCHARACTER_FISHINGEFFECT_UP_2);
//				}
//				else if(sp_BFishing == 3)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_NET_BASIC_LEFT;
//				}
//			}
//			else if(moveState == MOVESTATE_RUN)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_RUN_UP;
//	//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_UP_ANI_INDEX);
//			}						
//
//			break;
//
//		case DIRECT_DOWN:
//			if(moveState == MOVESTATE_WALK)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_WALK_DOWN ;
//
//				//_obj->m_renderer[CHARSLOT::k_slot_etc]->m_nCrtModule = ANIM_MAINCHARACTER_FISHINGEFFECT_DOWN_2;
//				if(sp_BFishing == 2 && g_pGame->m_colMap_water > 0)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_FISHING_BASIC_LEFT;
//					_obj->setAnim(CHARSLOT::k_slot_etc,ANIM_MAINCHARACTER_FISHINGEFFECT_DOWN_2);
//				}
//				else if(sp_BFishing == 3)
//				{
//					setAniNumber += ANIM_MAINCHARACTER_NET_BASIC_LEFT;
//				}
//			}
//			else if(moveState == MOVESTATE_RUN)
//			{
//				setAniNumber = ANIM_MAINCHARACTER_RUN_DOWN;
//	//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_DOWN_ANI_INDEX);
//			}						
//			break;	
//		}
//
//		if(_obj->m_dir != DIRECT_NULL)
//		{
//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_boby,setAniNumber);
//		}
//	}
//
//
//	if(moveState == MOVESTATE_STOP)
//	{
//		int setAniNumber = 0;
//		switch ( _obj->m_dir )
//		{
//		case DIRECT_LEFT:					
//			setAniNumber = ANIM_MAINCHARACTER_STOP_LEFT;
//		//	g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_RIGHT_ANI_INDEX);
//			break;
//		case DIRECT_RIGHT:						
//			setAniNumber = ANIM_MAINCHARACTER_STOP_RIGHT;						
//		//	g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_LEFT_ANI_INDEX);
//			break;
//		case DIRECT_UP:
//			setAniNumber = ANIM_MAINCHARACTER_STOP_UP;						
//		//	g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_DOWN_ANI_INDEX);
//			break;
//		case DIRECT_DOWN:						
//			setAniNumber = ANIM_MAINCHARACTER_STOP_DOWN;
//		//	g_pGame->getEntity(ENTITY::k_main_character)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_UP_ANI_INDEX);
//			break;	
//		}		
//		g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_boby,setAniNumber);
//
//	}
//
//
//	if ( _obj->m_dir == DIRECT_NULL )
//	{
//		int setAniNumber = 0;	
//
//		if(_obj->m_dirBefore != 0)
//		{		
//			setAniNumber = ANIM_MAINCHARACTER_BASIC_LEFT + _obj->m_dirBefore -1;
//
//			if(sp_BFishing == 2)
//			{
//				setAniNumber += ANIM_MAINCHARACTER_FISHING_BASIC_LEFT;				
//			}
//			else if(sp_BFishing == 3)
//			{
//				setAniNumber += ANIM_MAINCHARACTER_NET_BASIC_LEFT;
//			}
//			_obj->setAnim(CHARSLOT::k_slot_boby,setAniNumber);		
//		}
//		_obj->m_renderer[CHARSLOT::k_slot_etc]->m_nCrtModule = ANIM_MAINCHARACTER_FISHINGEFFECT_BASIC_2;
//
//	}
//
//	_obj->m_dirBefore =  _obj->m_dir;

}


int cUI::Set_Keypressed_Direct(  )
{
	int _direct = DIRECT_NULL;

	if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_LEFT)) //_OR_HELD
	{
		_direct = DIRECT_LEFT;
	}
	else if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_RIGHT))
	{
		_direct = DIRECT_RIGHT;
	}
	else if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_UP))
	{
		_direct = DIRECT_UP;
	}
	else if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_DOWN))
	{
		_direct = DIRECT_DOWN;
	}
	else if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_ACTION))
	{
		_direct = DIRECT_CENTER;
	}
	else if(KEY_PRESSED_OR_HELD(GAME_KEY_ALL_1))
	{
		_direct = DIRECT_1;
	}
	

		
	
	//DBG("Set_Keypressed_Direct====="+_direct);	
	return	_direct;
}


int cUI::Set_Keyrepeate_Direct(    )
{
	int _direct = DIRECT_NULL;

	if(KEY_HELD(GAME_KEY_ALL_LEFT))
	{
		_direct = DIRECT_LEFT;
	}
	if(KEY_HELD(GAME_KEY_ALL_RIGHT))
	{
		_direct = DIRECT_RIGHT;
	}
	if(KEY_HELD(GAME_KEY_ALL_UP))
	{
		_direct = DIRECT_UP;
	}
	if(KEY_HELD(GAME_KEY_ALL_DOWN))
	{
		_direct = DIRECT_DOWN;
	}
	if(KEY_HELD(GAME_KEY_ALL_ACTION))
	{
		_direct = DIRECT_CENTER;
	}
	if(KEY_HELD(GAME_KEY_ALL_1))
	{
		_direct = DIRECT_1;
	}
			
	// DBG("Set_Keyrepeate_Direct====="+_direct);
	return	_direct;
}


static int moveState = MOVESTATE_WALK;

static int stackA = -1;
static int stackCnt = 0;
static int stackB = -1;


int cUI::Set_KeyEvent()
{

	int temp_pressed = Set_Keypressed_Direct();
	int temp_repeate = Set_Keyrepeate_Direct();


	

	//DBGPRINTF("111temp_pressed = %d",temp_pressed);
	//DBGPRINTF("222temp_repeate = %d",temp_repeate);

	if(moveState == MOVESTATE_WALK)
	{
		if(temp_pressed > DIRECT_NULL)
		{
			if(stackA <= DIRECT_NULL)	//
			{
				stackA = temp_pressed;		
				stackCnt = 0;
			}
			else if(stackA == temp_repeate && stackCnt > 6 )	
			{
				moveState = MOVESTATE_RUN;
				stackB = temp_repeate;
				stackCnt = 0;
				return temp_repeate;
			}
			//else	// 
			//{
			//	stackA = -1;
			//}
			stackCnt++;
		}
		else 
		{
			stackA = -1;
			stackCnt = 0;
		}
	
	//	DBGPRINTF("3333 stackCnt = %d",stackCnt);

	//	if(stackCnt > 7)
	//	{
	//		stackA = -1;
	//		stackCnt = 0;
	//	}
		return temp_pressed;
	}
	else if(moveState == MOVESTATE_RUN )
	{

	//	DBGPRINTF("5555 stackCnt = %d",stackCnt);

		if(temp_pressed == DIRECT_NULL)
		{
			moveState = MOVESTATE_STOP;
			stackA = -1;
		}

		if(temp_repeate == DIRECT_NULL) return stackB;

		boolean bRunStop = false;
		switch(stackB)
		{
			case DIRECT_LEFT:
				if(temp_repeate == DIRECT_RIGHT)
				{
					//Stop
					bRunStop = true;
				}
				else
				{
					stackB = temp_repeate;
				}
				break;

			case DIRECT_RIGHT:
				if(temp_repeate == DIRECT_LEFT)
				{
					//Stop
					bRunStop = true;
				}
				else
				{
					stackB = temp_repeate;
				}
				break;

			case DIRECT_UP:
				if(temp_repeate == DIRECT_DOWN)
				{
					//Stop
					bRunStop = true;
				}
				else
				{
					stackB = temp_repeate;
				}
				break;

			case DIRECT_DOWN:
				if(temp_repeate == DIRECT_UP)
				{
					//Stop
					bRunStop = true;
				}
				else
				{
					stackB = temp_repeate;
				}
				break;
		}

		if(bRunStop)
		{
			moveState = MOVESTATE_STOP;
			stackA = -1;
			//g_pGame->getEntity(GAMESPRITE_MAIN_CHAR).setAnim(CHARSLOT::k_slot_effect,BOY_GAME_SMOG_UP_ANI_INDEX);
		}
		return stackB;
	}
	else if(moveState == MOVESTATE_STOP)
	{

		stackCnt++;
		if(stackCnt > 0)//5)
		{
			stackCnt = 0;
			moveState = MOVESTATE_WALK;
//			g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->setAnim(CHARSLOT::k_slot_effect,BOY_GAME_NONE_ANI_INDEX);
		}
	
		return stackB;
	}
	return DIRECT_NULL;
}




void cUI::Set_FollowEntity( cEntity* _obj , cEntity* _target )
{
	int _gapX,_gapY;
	int _ABSgapX,_ABSgapY;
	int _Maxgap;

	int _movestate = 0;
	int _Direct;
	int _ActiveRun ;
	int _ActiveWalk ;

	_gapX = _obj->m_posX - _target->m_posX;
	_gapY = _obj->m_posY - _target->m_posY;
	_ABSgapX = ABS(_gapX);
	_ABSgapY = ABS(_gapY);

	if ( _ABSgapX > (_ABSgapY+5) )
	{
		_Direct = ( _gapX < 0 )?DIRECT_LEFT:DIRECT_RIGHT;
	}
	else
	{
		_Direct = ( _gapY < 0 )?DIRECT_UP:DIRECT_DOWN;
	}

	_Maxgap = MAX(_ABSgapX,_ABSgapY);
	if ( _Direct == DIRECT_DOWN ||  _Direct == DIRECT_UP )
	{
		 _ActiveRun = 10;
		 _ActiveWalk = 5;
	}
	else 
	{
		 _ActiveRun = 30;
		 _ActiveWalk = 20;
	}

	if ( _Maxgap > _ActiveRun )
	{
		_movestate = MOVESTATE_RUN;
	}
	else if ( _Maxgap > _ActiveWalk )
	{
		_movestate = MOVESTATE_WALK;
	}
	else
	{
		_movestate = MOVESTATE_STAND;
	}

	if ( g_pGame->m_colMap_water > 0 )
	{
		_movestate = MOVESTATE_STAND;
	}


	Set_Entity( _target ,_Direct , _movestate );

	if ( _movestate != MOVESTATE_STAND )
	{
		int _col_tile = check_move( _target, _target->m_posX, _target->m_posY );
		if( _col_tile != COL_TILES::k_oob_null)
		{
			if(_col_tile > COL_TILES::k_can_move )
			{
				int _moveX  = 0, _moveY = 0;
				int move_vel = (_movestate == MOVESTATE_RUN)? (OBJECT_MOVE+2):OBJECT_MOVE ;

				switch ( _target->m_dir )
				{
					case DIRECT_LEFT: 			_moveX = -(move_vel);		break;
					case DIRECT_RIGHT:			_moveX =  (move_vel);		break;
					case DIRECT_UP:				_moveY = -(move_vel);		break;
					case DIRECT_DOWN:			_moveY =  (move_vel);		break;
				}

				// check direction
				_target->m_posX -= _moveX;
				_target->m_posY -= _moveY;

				if ( _ABSgapX > (_ABSgapY+5) )
				{
					_Direct = ( _gapY < 0 )?DIRECT_UP:DIRECT_DOWN;
				}
				else
				{
					_Direct = ( _gapX < 0 )?DIRECT_LEFT:DIRECT_RIGHT;
				}
				//_target->m_dir = _Direct;

				Set_Entity(  _target, _Direct, _movestate );
			}
		}
	}
}




void cUI::Set_Entity( cEntity* _target , int _direct , int _movestate)
{
	/*int _AniNumber = 0 ;
	int _moveX  = 0, _moveY = 0;
	int move_vel = (_movestate == MOVESTATE_RUN)? (OBJECT_MOVE+2):OBJECT_MOVE ;

	_target->m_dir =  _direct;

	switch ( _target->m_dir )
	{
		case DIRECT_LEFT: 			_moveX = -(move_vel);		break;
		case DIRECT_RIGHT:			_moveX =  (move_vel);		break;
		case DIRECT_UP:				_moveY = -(move_vel);		break;
		case DIRECT_DOWN:			_moveY =  (move_vel);		break;
	}

	if ( _movestate != MOVESTATE_STAND )
	{
		switch ( _target->m_dir )
		{
			case DIRECT_LEFT:
				_target->m_posX += _moveX;
				_AniNumber = ANIM_CHICK_BASIC_LEFT;
				break;

			case DIRECT_RIGHT:
				_target->m_posX += _moveX;
				_AniNumber = ANIM_CHICK_BASIC_RIGHT;
				break;

			case DIRECT_UP:
				_target->m_posY += _moveY;
				_AniNumber = ANIM_CHICK_BASIC_UP;
				break;

			case DIRECT_DOWN:
				_target->m_posY += _moveY;
				_AniNumber = ANIM_CHICK_BASIC_DOWN;
				break;
		}
		if ( _movestate != MOVESTATE_STAND )
		{
			_AniNumber += ANIM_CHICK_WALK_LEFT;
		}

		_target->setAnim( CHARSLOT::k_slot_boby,_AniNumber );
	}*/
}


void cUI::Set_Camera_Position( cEntity* _obj )
{
	int _cameraGapX = 0;
	int _cameraGapY = 0;

	_cameraGapX = SCR_W >> 1;
	_cameraGapY = (SCR_H >> 1);

	g_pGame->m_mapX	=  _obj->m_posX - _cameraGapX;
	g_pGame->m_mapY	=  _obj->m_posY - _cameraGapY;

	SET_NUMBER_SMALL(g_pGame->m_mapX , SV_X);
	SET_NUMBER_SMALL(g_pGame->m_mapY , SV_Y);

	SET_NUMBER_LARGE(g_pGame->m_mapX , g_pGame->m_tileMapW*TILE_W-SCR_W);
	SET_NUMBER_LARGE(g_pGame->m_mapY , g_pGame->m_tileMapH*TILE_H-SCR_H);

}



void cUI::Set_Camera_Position( int _x , int _y )
{
	int _cameraGapX = 0;
	int _cameraGapY = 0;

	_cameraGapX = SCR_W >> 1;
	_cameraGapY = (SCR_H >> 1);

	g_pGame->m_mapX	=  _x - _cameraGapX;
	g_pGame->m_mapY	=  _y - _cameraGapY;

	SET_NUMBER_SMALL(g_pGame->m_mapX , SV_X);
	SET_NUMBER_SMALL(g_pGame->m_mapY , SV_Y);

	SET_NUMBER_LARGE(g_pGame->m_mapX , g_pGame->m_tileMapW*TILE_W-SCR_W);
	SET_NUMBER_LARGE(g_pGame->m_mapY , g_pGame->m_tileMapH*TILE_H-SCR_H);

}





void cUI::Update_Entity(  )
{
	
//	for (int i = 0; i < ENTITY::k_max; i++)
	for (int i = 0; i < g_pGame->m_actorsMax_count; i++)
	{			
		if ( g_pGame->getEntity(i) != NULL && !((g_pGame->getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0))
		{
			g_pGame->getEntity(i)->update();
		}
	}
}



void cUI::Update_Entity_ShowLayer (  )
{
	
//	for (int i = 0; i < ENTITY::k_max; i++)
	for (int i = 0; i < g_pGame->m_actorsMax_count; i++)
	{			
		if ( g_pGame->getEntity(i) != NULL && ((g_pGame->getEntity(i)->m_flags & DFLAGS::HIDE_LAYER) != 0))
		{
			g_pGame->getEntity(i)->unsetFlag(DFLAGS::HIDE_LAYER);
		}
	}
}



void cUI::Entity_Update(  cEntity* _obj, int _moveX, int _moveY )
{
	

			
				
}













//*****************************************************************************************************************************************
//*S*************************************************************** MENU 테스트 **************************************************************
//*****************************************************************************************************************************************
void cUI::process_Main_Test(int message)
{
}
//*****************************************************************************************************************************************
//*E*************************************************************** MENU 테스트 **************************************************************
//*****************************************************************************************************************************************



//*****************************************************************************************************************************************
//*S*************************************************************** GAME 테스트 **************************************************************
//*****************************************************************************************************************************************
void cUI::process_UI_Test(int message)
{
}
//*****************************************************************************************************************************************
//*E*************************************************************** GAME 테스트 **************************************************************
//*****************************************************************************************************************************************
















//***************************************************************************
//** STATE_GAMELOFT (Implementation)
//**
//** Any variable declaration should go into UI_Gameloft.h
//***************************************************************************


void cUI::process_UI_Gameloft( int message )

{
//	if( message == MESSAGE_INIT)
//	{
//
//		g->SetClip(0, 0, SCREEN_WIDTH, OS_SCREEN_H);
//		GAMELOFT_SPRITE_LOGO->SetCurrentAnimation(0,0, false);
//		GAMELOFT_SPRITE_2588->SetCurrentAnimation(0,0, false);
//		//g->SetARGBColor(0X33000000);
//
//		//GAMELOFT_SPRITE_LOGO -> ScaleImage(10, 7);
//
//		//GAMELOFT_SPRITE_2588 -> ScaleImage(10, 6);
//
//		//g_pGame->SetStoreType(STORE_SLOT1);
//
//		//g_pGame->SetRecordDataArray(RECORD_USERINFO_NAME ,);
//
//		//g_pGame->SaveLoadRecord(false);
//
//	}
//	else if( message == MESSAGE_UPDATE)
//	{
//
//		//#ifdef EVALUATION
//		//		pushState( STATE_LOAD_COMMON, true );
//		//#else
//
//		if ( !GAMELOFT_SPRITE_LOGO->Is_animDone(0) )
//		{
//			GAMELOFT_SPRITE_LOGO->UpdateAnimation(0);	
//		}
//		else if ( !GAMELOFT_SPRITE_2588->Is_animDone(0) )
//		{
//			GAMELOFT_SPRITE_2588->UpdateAnimation(0);	
//		}
//		else
//		{
//
//
//			//#ifdef VIEW_GAMERATING
//			//			pushState( STATE_GAMEGRADE, false );
//			//#else
//			pushState( STATE_LOAD_COMMON, true );
//			//pushState( STATE_SELECTSOUND, false );	
//			//#endif
//			//			g_pGame->m_map_kind = HOUSE_MYHOME;
//			//			pushState(STATE_DRAW_HOUSE,true);
//
//			//	g_pGame->m_map_kind = WORLD_MAP1;
//			//	pushState(STATE_DRAW_MAP1,true);
//
//			//	g_pGame->goto_map( STATE_DRAW_HOUSE );
//
//			//	g_pGame->goto_map( STATE_DRAW_MAP1 );
//
//		}
//
//		//#endif//EVALUATION
//	}
//
//	else if( message == MESSAGE_PAINT)
//	{
//		g->SetColor(0xFFFFFF);		
//		g->FillRect(0, 0, SCREEN_WIDTH, OS_SCREEN_H);
//#ifdef EVALUATION
//		return;
//#endif
//		if ( !GAMELOFT_SPRITE_LOGO->Is_animDone(0) )
//		{
//
//
//
//			GAMELOFT_SPRITE_LOGO->PaintAnimation(g, 0, SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, 0, 0, 0);
//
//			//g->SetARGBColor(0X88FFFFff);
//			//GAMELOFT_SPRITE_2588->PaintAnimation(g, 0, SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, 0, 0, 0); 
//			//g->SetARGBColor(0xFFFFFFFF);//ADD
//			//int arc1 = 90;
//
//			//int s_superEffectX = (180 - 90) * 70 / 90;
//			//g->SetARGBColor(0X11FFFF00);
//			////g->SetColor(0x000000);
//			////g->FillRect(0,0,240,320);
//			//
//			//g->FillArc(100 - s_superEffectX / 2 - 10,
//			//			160 - 30 - 70 / 2 - 10, 
//			//			s_superEffectX, 70, arc1, 180);
//			//g->SetARGBColor(0xFFFFFFFF);//ADD
//
//
//		}else{
//			GAMELOFT_SPRITE_2588->PaintAnimation(g, 0, SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, 0, 0, 0); 
//
//		}	
//
//
//
//	}
//
//	else if( message == MESSAGE_EXIT)
//	{		
//		//SAFE_DEL(GAMELOFT_SPRITE_LOGO);
//		//SAFE_DEL(GAMELOFT_SPRITE_2588);
//
//		//SAFE_DEL(g_pGame->load_spriteArray);
//
//		//GAMELOFT_SPRITE_LOGO->StopScaleImage();
//		//GAMELOFT_SPRITE_2588->StopScaleImage();
//		g->SetARGBColor(0xFFFFFFFF);
//
//		//g_pGame->load_reset();
//
//	}
}	


//***************************************************************************
//** STATE_SELECTSOUND (Implementation)
//**
//** Any variable declaration should go into UI_SelectLSound.h
//** Gameloft, NYC.  November 13, 2007
//***************************************************************************

void cUI::process_UI_SelectSound( int message )
{

#ifdef EVALUATION
	if( message == MESSAGE_INIT)
	{
		g_pGame->m_sndVol = 2;
		menu_strscroll_count = 0;
		g_pGame->Text_loadTextPack (PACK_TEXT, TEXT_MAIN,4);
		if(g_pGame->have_save_file)
		{
			g_pGame->m_speed = GET_BYTE_DBDATA( RECORD_SPEED );
			g_pGame->m_vibrateOn = GET_BYTE_DBDATA( RECORD_VIBRATION );
		}		
	}
	else if( message == MESSAGE_UPDATE)
	{
		if( KEY_PRESSED(GAME_KEY_SOFTKEY_RIGHT) )
		{
			g_pGame->m_sndVol = GET_BYTE_DBDATA( RECORD_SOUND );
			if( g_pGame->m_sndVol < 1 )
			{
				g_pGame->m_sndVol = 2;
			}
			pushState( STATE_SPLASH, false );
		}
	}
	else if( message == MESSAGE_PAINT)
	{
		g->SetColor(0);
		g->FillRect(0,0,240,320);
		SPRITE_INIT_PAGE();
		SET_STRING_OUT_LINE(false);
		SET_STRING_COLOR(0xffffff);
		if(SPRITE_DRAW_PAGE(g, GET_STRING(MAIN_TEXT_INFO_IGP1 ,4), 5 , 10+(260>>1), 230, 235,
			menu_strscroll_count , Graphics::LEFT ) > 0 	)
		{
			menu_strscroll_count++;		
		}	
		else
		{
			menu_strscroll_count = 0;
		}
		DRAW_KORSTR(g,GET_STRING(MAIN_TEXT_INFO_IGP2, 4), 236, 286, Graphics::BOTTOM | Graphics::RIGHT, 0xffffff);

	}
	else if( message == MESSAGE_EXIT)
	{
	}
#else
	if( message == MESSAGE_INIT)
	{

		//softkey_init( SOFTKEY_SYMBOL_EMPTY, SOFTKEY_SYMBOL_OK);
		
		//SAVE_DATA ( false );
		
		//select_point = 0;
		select_point = 1;

		//GuanHao. save
		if(g_pGame->have_save_file)
		{
			g_pGame->m_speed = GET_BYTE_DBDATA(g_pGame->record_buffData, RECORD_SPEED );
		}
		g_pGame->m_vibrateOn = GET_BYTE_DBDATA(g_pGame->record_buffData, RECORD_VIBRATION );
	}
	else if( message == MESSAGE_UPDATE)//485
	{
		//if( KEY_PRESSED(GAME_KEY_ALL_UP) || KEY_PRESSED(GAME_KEY_ALL_DOWN) )
		if( KEY_PRESSED(GAME_KEY_ALL_LEFT) || KEY_PRESSED(GAME_KEY_ALL_RIGHT) )
		{
			select_point =  ((select_point==0)?1:0);
		}
		else if( KEY_PRESSED(GAME_KEY_ALL_ACTION))
		{
			if ( select_point == 0 )
			{
				g_pGame->m_sndVol = GET_BYTE_DBDATA(g_pGame->record_buffData, RECORD_SOUND );
				
				if( g_pGame->m_sndVol < 1 )
				{
					g_pGame->m_sndVol = 2;
				}
			}
			else 
			{
				g_pGame->m_sndVol = 0;	
			}

			pushState( STATE_SPLASH, false );
		}
		
	}
	else if( message == MESSAGE_PAINT)
	{

		g->SetColor(0x000000);
		g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

		//DRAW_KORSTR( g,  GET_STRING(COMMON_ENABLE_SOUND_QUESTION ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, Graphics::TOP|Graphics::HCENTER , 0xffffff );


		if ( select_point == 0 )
		{
//			DRAW_KORSTR_LINE( g, GET_STRING(COMMON_YES ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH-30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff, 0x000000  );
//			DRAW_KORSTR( g, GET_STRING(COMMON_NO ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH+30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff);

		}
		else 
		{
//			DRAW_KORSTR( g, GET_STRING(COMMON_YES ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH-30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff );
//			DRAW_KORSTR_LINE( g, GET_STRING(COMMON_NO ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH+30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff, 0x000000 );
		}
		//softkey_paint();
	}
	else if( message == MESSAGE_EXIT)
	{
	}
#endif
}


//================================================================

/// PROCESS GAMEGRADE

//================================================================


void cUI::process_UI_GameGrade( int message )
{
	if( message == MESSAGE_INIT)
	{
		img_Gamegrade = g_pGame->create_Image ( GAMEGRADE_IMG );
		game_counter = 0;

	}
	else if( message == MESSAGE_UPDATE)
	{

		if( (game_counter > GRAD_PASS_TIME) )
		{
			pushState( STATE_LOAD_COMMON, true );
			//	pushState( STATE_SELECTSOUND, false );
		}

	}
	else if( message == MESSAGE_PAINT)
	{

		g->SetColor(0x000000);
		g->FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		g->DrawImage(img_Gamegrade, SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, Graphics::HCENTER | Graphics::VCENTER);

	}
	else if( message == MESSAGE_EXIT)
	{
		//img_Gamegrade = null;
		SAFE_DEL(img_Gamegrade);
	}
}


//================================================================

/// PROCESS Splash

//================================================================

void cUI::process_UI_Splash( int message )
{
	if( message == MESSAGE_INIT)
	{
//#ifdef LGT_VERSION
//		//GuanHao. save
//		if(g_pGame->have_save_file)
//		{
//			g_pGame->m_speed = GET_BYTE_DBDATA( RECORD_SPEED );
//		}
//		g_pGame->m_vibrateOn = GET_BYTE_DBDATA( RECORD_VIBRATION );
//		g_pGame->m_sndVol = GET_BYTE_DBDATA( RECORD_SOUND );
//#endif
		
		img_splash = g_pGame->create_Image ( SPLASH_IMG );

		img_GgeMark = g_pGame->create_Image ( AGEMARK_IMG );

		//g_pGame->setVol( INTRO_SOUND_01 ,  (g_pGame->m_sndVol) );	

		//SOUND_PLAY(INTRO_SOUND_01,true);
	//	g_pGame->init_popup( );

	}
	else if( message == MESSAGE_UPDATE)
	{
		if((ANY_KEY_PRESS() && !KEY_PRESSED(GAME_KEY_VOL_UP) && !KEY_PRESSED(GAME_KEY_VOL_DOWN)))
		{
			//SOUND_STOP();
			pushState(STATE_MENU_MAIN,false);
		}


	}
	else if( message == MESSAGE_PAINT)
	{

		g->DrawImage(img_splash, SCREEN_HALF_WIDTH, 0, Graphics::HCENTER | Graphics::TOP);

		g->DrawImage(img_GgeMark, SCREEN_WIDTH, 0, Graphics::RIGHT | Graphics::TOP);

		////if(game_counter%10 <= 5)
		////	Splash_Sprite->PaintFrame(g, SPLASH_RES_PRESSANYKEY_FRM_INDEX, SCREEN_HALF_WIDTH, /*256*/SCREEN_HALF_HEIGHT+35, 0, 0, 0);

		//char tem[40];
		//SPRINTF(tem, "%s%s", "ver ",VERSION);		
		//
		//DRAW_KORSTR_LINE(g, tem , 3, 4, Graphics::TOP|Graphics::LEFT , 0x000000 ,0xffffff);

	}
	else if( message == MESSAGE_EXIT)
	{
		
        SAFE_DEL(img_splash);
		//img_splash = NULL;

		SAFE_DEL(img_GgeMark);


		//Splash_Sprite->ClearCompressedImageData();
		////Splash_Sprite = NULL;
		//SAFE_DEL(Splash_Sprite);

		//SOUND_STOP();
		

	}
}



//================================================================

/// PROCESS MENU

//================================================================

void cUI::process_UI_Menu( int message )
{
	if( message == MESSAGE_INIT)
	{
//		g_pGame->Text_freeText( TEXT_INDEX_MENU );
//		g_pGame->Text_loadTextPack( PACK_TEXT, TEXT_MENU, TEXT_INDEX_MENU );	


//		title_frame = MENU_RES_MENU_FRM_INDEX;
//		title_posX  = TOP_MENU_POSX;
//		title_posY  = TOP_MENU_POSY;
	
		//data_save = (g_pGame->GetRecordDataByte(RECORD_SAVE1)==1)?true:false ;
		//g_pGame->showIGPNew = (g_pGame->GetRecordDataByte(RECORD_IGP_NEW)==0)?true:false ;

		img_GgeMark = g_pGame->create_Image ( RATING_MARK_IMG );
		//img_New = g_pGame->create_Image ( IMG_NEW );
		
		select_point = 0;
		g_pGame->SetStoreType(STORE_SLOT1);
		g_pGame->SaveLoadRecord(false);
		//g_pGame->GetRecordDataArray( RECORD_USERINFO_NAME ,(char*)g_pGame->textField_Name, 16);
	}
	else if( message == MESSAGE_UPDATE)
	{

		update_KeyMenu( );

		//Process_Menu( );

	}
	else if( message == MESSAGE_PAINT)
	{
		g->SetColor(0xffffff);
		g->FillRect(0,0,240,320);

		draw_Menu( );

	}
	else if( message == MESSAGE_EXIT)
	{	
		SAFE_DEL(img_GgeMark);
		
		g_pGame->Text_freeText( TEXT_INDEX_MENU );

		

		//FREE_GAMERES();

	}
}

void cUI::update_KeyMenu()
{

	//if(g_pGame->_cText)
	//{
	//	if( g_pGame->update_Key_textField() == 1)
	//	{

	//		g_pGame->SetStoreType(STORE_SLOT1);

	//		g_pGame->SetRecordDataArray(RECORD_USERINFO_NAME ,GET_STRING( MENU_STORY_MODE+3 ,TEXT_INDEX_MENU) , 16);

	//		g_pGame->SaveLoadRecord(true);

	//	}
	//}
	//else
	//{
	//	if(KEY_PRESSED(GAME_KEY_ALL_UP) )
	//	{		
	//		select_point = (select_point+7-1)%7;
	//	}
	//	else if(KEY_PRESSED(GAME_KEY_ALL_DOWN) )
	//	{		
	//		select_point = (select_point+1)%7;
	//	}
	//	else if(KEY_PRESSED(GAME_KEY_ALL_ACTION) || softkey_update() == SOFTKEY_RIGHT )
	//	{
	//		if(select_point == 0)
	//		{
	//			g_pGame->set_textField( AUTOMATA_KR );
	//		}
	//	}

	//}

}
void cUI::draw_Menu()
{
	int i = 0;
	/*if(g_pGame->_cText)
	{
		
		DRAW_KORSTR_LINE(g, GET_STRING( MENU_STORY_MODE ,TEXT_INDEX_MENU)  , SCREEN_HALF_WIDTH , 50 , Graphics::TOP|Graphics::HCENTER , 0xff0000 ,0xffffff);

		byte _bUTF16_[16]={0};
		byte _bUTF8_[32]={0};
		char* str = g_pGame->m_pStrArray->getStr();
		

		g_pGame->getText(&str);
		int iLen_ = STRLEN(str);
		iLen_ = ConvertKSC5601toUTF16( (byte*)str, iLen_, _bUTF16_ );   
		iLen_ = ConvertUTF16toUTF8( _bUTF16_, _bUTF8_, iLen_, CONVUTF_8 );	
			
		DRAW_KORSTR_LINE(g, (char*)_bUTF8_  , SCREEN_HALF_WIDTH , 120, Graphics::TOP|Graphics::HCENTER , 0xff0000 ,0xffffff);
		
		g_pGame->m_pStrArray->releaseStr(str);
	
	}
	else
	{

		for(i = 0 ; i < 7 ;i++)
		{
			if(select_point == i)
			{
				DRAW_KORSTR_LINE(g, GET_STRING( MENU_STORY_MODE+i ,TEXT_INDEX_MENU)  , SCREEN_HALF_WIDTH , 50 + i*20, Graphics::TOP|Graphics::HCENTER , 0xff0000 ,0xffffff);
			}
			else
			{
				DRAW_KORSTR_LINE(g, GET_STRING( MENU_STORY_MODE+i ,TEXT_INDEX_MENU)  , SCREEN_HALF_WIDTH , 50 + i*20, Graphics::TOP|Graphics::HCENTER , 0x000000 ,0xffffff);
			}
		}
		DRAW_KORSTR_LINE(g, g_pGame->textField_Name  , SCREEN_HALF_WIDTH , 50 + i*20, Graphics::TOP|Graphics::HCENTER , 0x00ff00 ,0xffffff);
	}*/

}


////////////////////////////////
//UI_Net.hpp
//================================================================

/// PROCESS ENDING

//================================================================

//void cUI::process_UI_Net( INT_TYPE message )
//{
//	cXPlayerMenus::getInstance()->paint(g);
//}


////////////////////////////////////////////////////

void cUI::Set_Net_NextState( byte _state )
{
	g_pGame->state  = _state;
	switch (g_pGame->state )
	{
	case cGame::CAUTION_POPUP :
	case cGame::MENU:
	case cGame::REPLAY:

		sel_point = 0;
		g_pGame->jFont->isInitalizedPage = false;
		softkey_init(SOFTKEY_SYMBOL_BACK,SOFTKEY_SYMBOL_OK);

		break;

	case cGame::ALREADY_REPLAY:
	case cGame::NEEDLESS_REPLAY:
		g_pGame->jFont->isInitalizedPage = false;
		softkey_init(SOFTKEY_SYMBOL_EMPTY,SOFTKEY_SYMBOL_OK);
		break;
	}
}


void cUI::getKeyrelease()//SangHo - Key 이벤트 임시구현
{
	if (keyLife) return;
	if (keyCodeRelease) keyCodePress=keyCodeRelease=0;
}
void cUI::getKeypress()//SangHo - Key 이벤트 임시구현
{
	keyCodeCui = keyCodePress;
	keyLife = false;
}


void cUI::keyProcess()
{
	//612. +
	bool _bSelect = false ;

	switch (g_pGame->state)
	{
	case cGame::MENU:
		//612. +
		if(KEY_PRESSED(GAME_KEY_UP))
		{
			sel_point--;
			if ( sel_point < 0)
			{
				sel_point = NET_MENU_MAX;
			}
		}
		else if(KEY_PRESSED(GAME_KEY_DOWN))
		{
			sel_point++;
			if ( sel_point > NET_MENU_MAX)
			{
				sel_point = 0;
			}
		}
		else if(KEY_PRESSED(GAME_KEY_CLICK)|| softkey_update() == SOFTKEY_RIGHT	)
		{
			_bSelect = true;
		}
		else if(KEY_PRESSED( GAME_KEY_CLEAR ) ||  softkey_update() == SOFTKEY_LEFT 	)//SOFTKEY_RIGHT)
		{
			pushState(STATE_MENU_MAIN,true);
		}

		if(KEY_PRESSED(GAME_KEY_1))
		{
			//612. *
			/*g_pGame->jFont->isInitalizedPage = false;

			g_pGame->state = cGame::CAUTION_POPUP;*/
			sel_point = 0;
			_bSelect = true;

		}
		else if(KEY_PRESSED(GAME_KEY_2))
		{
			//612. *
			////GLWipiNetModule.makeCharge(g_pGame->application.s_game, g_pGame->jFont);//Chen Shoutian, to do 
			//g_pGame->state = cGame::CHARGE;
			sel_point = 1;
			_bSelect = true;

		}
		else if(KEY_PRESSED(GAME_KEY_3))
		{
			////GLWipiNetModule.makeDownload(g_pGame->application.s_game, g_pGame->jFont, "");//Chen Shoutian, to do

			// it will be downloaded files that the prefix is "MUSIC"... 
			//					//GLWipiNetModule.makeDownload(this, g_pGame->jFont, "MUSIC");
			//g_pGame->state = cGame::DOWNLOAD;
			sel_point = 2;
			_bSelect = true;

		}
		else if(KEY_PRESSED(GAME_KEY_4))
		{
			//	g_pGame->menu_Pointer = 4;
			//pushState(STATE_MENU_MAIN,true);

			sel_point = 3;
			_bSelect = true;
		}	
		break;

	case cGame::CAUTION_POPUP:


		//if(KEY_PRESSED(GAME_KEY_1))
		//{
		//	//					wipiNetwork = new WipiNetwork(this, g_pGame->jFont, new int[9]);

		//	////GLWipiNetModule.makeRanking(g_pGame->application.s_game, g_pGame->jFont, scoreArray);//Chen Shoutian, to do

		//	g_pGame->state = cGame::RANKING;
		//}
		//else if(KEY_PRESSED(GAME_KEY_2))
		//{
		//	g_pGame->state = cGame::MENU;
		//}
		//break;
		if(KEY_PRESSED(GAME_KEY_1))
		{
			sel_point = 0;
			_bSelect = true;
		}
		else if(KEY_PRESSED(GAME_KEY_2))
		{
			sel_point = 1;
			Set_Net_NextState(cGame::MENU);
		}

		if(KEY_PRESSED(GAME_KEY_UP)||KEY_PRESSED(GAME_KEY_DOWN))
		{
			sel_point = (sel_point==0)?1:0;
		}
		else if(KEY_PRESSED(GAME_KEY_CLICK) || softkey_update() == SOFTKEY_RIGHT)
		{
			_bSelect = true;
		}
		else if(KEY_PRESSED(GAME_KEY_CLEAR) || softkey_update() == SOFTKEY_LEFT )//SOFTKEY_RIGHT)//fixed bug 	1454551
		{
			Set_Net_NextState(cGame::MENU);
		}

		if ( _bSelect )
		{
			if(sel_point == 0)
			{
				//GLWipiNetModule.score_sending = XPlayer.SCORE_TYPE_POINTS; //SCORE_TYPE_POINTS = 1;  SCORE_TYPE_TIME = 2;
				//GLWipiNetModule.makeRanking(cGame.application.s_game, cGame.jFont, scoreArray);
				Set_Net_NextState(cGame::RANKING);
			}
			else if(sel_point == 1)
			{
				Set_Net_NextState(cGame::MENU);
			}

			_bSelect = false;
		}
		break;


	case cGame::REPLAY:

		break;

	case cGame::ALREADY_REPLAY:
	case cGame::NEEDLESS_REPLAY:

		if(KEY_PRESSED(GAME_KEY_CLICK) || softkey_update() == SOFTKEY_RIGHT	)
		{
			sel_point = 2;
			Set_Net_NextState(cGame::MENU);
		}
		break;



	case cGame::RANKING:
	case cGame::CHARGE:
	case cGame::DOWNLOAD:
		//				wipiNetwork.keyPressed(pressedKey);
		////GLWipiNetModule.instance.keyPressed(g_pGame->game_keyNet);//Chen Shoutian, to do

		break;
	}

	//612. *
	//g_pGame->game_keyNet = 0;
	//g_pGame->game_netKeyPressed = 0;

}



void cUI::logicProcess()
{
	switch (g_pGame->state)
	{
	//612. -
	//case cGame::MENU:

		//break;

	case cGame::RANKING:
	case cGame::CHARGE:
	case cGame::DOWNLOAD:
		//				wipiNetwork.logicProcess();
		//WipiNetwork.instance.logicProcess();//Chen Shoutian,to do
		break;
	}

	//	repaint();
}


//612. +
////////////////////////////////////////////////////

///	SET GGI (NET)

////////////////////////////////////////////////////

int cUI::Set_GGI()	// APPEND 2008-02-21 (Seungho.Han)
{
	int _ggi_index = 0;
	int _size_index = 0;
	int _company_index = COMPANY_KTF;

	if ( SCREEN_WIDTH <= GGI_SIZE_120 ) 
	{
		_size_index = 0;
	}
	else if ( SCREEN_WIDTH <= GGI_SIZE_176 ) 
	{
		_size_index = 1;
	}
	else if ( SCREEN_WIDTH <= GGI_SIZE_240 ) 
	{
		_size_index = 2;
	}
	else if ( SCREEN_WIDTH <= GGI_SIZE_320 ) 
	{
		_size_index = 3;
	}

	if ( _company_index == COMPANY_SKT ) 
	{
		_ggi_index = _size_index+GGI_SKT;
	}
	else if ( _company_index == COMPANY_KTF ) 
	{
		_size_index--;
		if ( _size_index < 0 )
		{
			_size_index = 0;
		}
		_ggi_index = _size_index+GGI_KTF;
	}
	else// if ( _company_index == COMPANY_LGT ) 
	{
		_ggi_index = _size_index+GGI_LGT;
	}
	return _ggi_index;
}



//GuanHao. reset
void cUI::resetGame(bool autoOpen)
{

}




//GuanHao. IGP. draw
//void cUI::process_UI_IGP(int message)
//{
//
//	//return;
//
//	if( message == MESSAGE_INIT)
//	{
//
//	}
//	else if( message == MESSAGE_UPDATE)
//	{
//            if(g_pGame->m_pIgp->Update())
//				pushState(STATE_MENU_MAIN,true);
//	}
//	else if( message == MESSAGE_PAINT)
//	{
//			g_pGame->m_pIgp->Draw();
//	}
//	else if( message == MESSAGE_EXIT)
//	{
//	}
//}
