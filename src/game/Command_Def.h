#ifndef __COMMAND_DEF_H__
#define __COMMAND_DEF_H__


#ifndef _UN_REPLACE_
	//***************************************************************************
	//** Methods
	//***************************************************************************

	#define g											g_pGame->g

	//#define loadResource								g_pGame->loadResource
	#define game_currentSubState						g_pGame->game_currentSubState
	#define game_currentState							g_pGame->game_currentState
	//#define game_keyRepeatCount							g_pGame->game_keyRepeatCount
	#define game_bExitCurrentState						g_pGame->game_bExitCurrentState
	#define game_nextState								g_pGame->game_nextState
	#define pushState(id,bload)							g_pGame->pushState(id,bload)

	//#define drawInventory()								g_pGame->drawInventory()
	//#define Keypressed_inventory()						g_pGame->Keypressed_inventory()

	#define drawbox										g_pGame->drawbox
	#define draw_result_popup							g_pGame->draw_result_popup

	//#define m_DogChangeBoy								g_pGame->m_DogChangeBoy

	#define game_sub_state								g_pGame->game_sub_state
	#define game_save_state								g_pGame->game_save_state
	//#define goto_map									g_pGame->goto_map

	#define	softkey_update								g_pGame->softkey_update
	#define	softkey_init								g_pGame->softkey_init
	#define	softkey_paint								g_pGame->softkey_paint

	#define	Set_talk									g_pGame->Set_talk
	#define	mascot_paint								g_pGame->mascot_paint
	#define	mascot_Keyupdate								g_pGame->mascot_Keyupdate
	#define	mascot_hide									g_pGame->mascot_hide
	#define	mascot_show									g_pGame->mascot_show

	#define	popup_paint									g_pGame->popup_paint
	#define	popup_update								g_pGame->popup_update
	#define	popup_hide									g_pGame->popup_hide
	#define	popup_show									g_pGame->popup_show

	//#define set_MapMove_Popup							g_pGame->set_MapMove_Popup
	//#define	updatge_MapMove_Popup						g_pGame->updatge_MapMove_Popup

	//#define update_chrPopup								g_pGame->update_chrPopup
	//#define update_MarketPopup							g_pGame->update_MarketPopup

	#define Get_Emotion									g_pGame->Get_Emotion
	#define Get_Emotion_Ani								g_pGame->Get_Emotion_Ani
	#define Set_Emotion									g_pGame->Set_Emotion
	#define Set_FreeEmotion								g_pGame->Set_FreeEmotion

	#define m_StateStory								g_pGame->m_StateStory
	//#define m_AnimationNum								g_pGame->m_AnimationNum
	//#define m_Npc_tc									g_pGame->m_Npc_tc
	//#define m_Quest										g_pGame->m_Quest

	//#define set_Inven_Item							g_pGame->set_Inven_Item
	//#define get_Inven_item_Durability					g_pGame->get_Inven_item_Durability
	//#define get_Inven_Item_ea							g_pGame->get_Inven_Item_ea
	//#define get_Item_price								g_pGame->get_Item_price
	//#define get_Item_ea									g_pGame->get_Item_ea
	//#define SetGroupGift								g_pGame->SetGroupGift
	//#define get_Inven_Item_Level						g_pGame->get_Inven_Item_Level
	//#define set_Inven_Item_Repair						g_pGame->set_Inven_Item_Repair
	//#define set_Inven_fish								g_pGame->set_Inven_fish
	//#define get_Item_kind								g_pGame->get_Item_kind
	//#define get_Inven_fruit_ea							g_pGame->get_Inven_fruit_ea
	//#define get_Inven_empty_ea							g_pGame->get_Inven_empty_ea


	//#define set_money									g_pGame->set_money
	//#define add_money									g_pGame->add_money
	//#define get_money									g_pGame->get_money
	
	//#define m_characterHp								g_pGame->m_characterHp
	//#define add_Character_Hp							g_pGame->add_Character_Hp
	//#define check_Character_Hp_Date						g_pGame->check_Character_Hp_Date

	//#define setSleep									g_pGame->setSleep	
	
	//#define m_max_CowSheep								g_pGame->m_max_CowSheep

	//#define m_dayWorking								g_pGame->m_dayWorking
	//#define m_oneObject									g_pGame->m_oneObject
	//#define get_DayWorking								g_pGame->get_DayWorking
	//#define set_MainPopup								g_pGame->set_MainPopup

	//#define m_bDogRed										g_pGame->m_bDogRed
	//#define m_pasture_level								g_pGame->m_pasture_level
	//#define m_fish_level									g_pGame->m_fish_level

	//#define m_charLove									g_pGame->m_charLove

	//#define menu_str									g_pGame->menu_str

	//#define m_CameraX									g_pGame->m_CameraX
	//#define m_CameraY									g_pGame->m_CameraY
	//#define auto_move									g_pGame->auto_move


#endif //_UN_REPLACE_
	////***************************************************************************
	////** Graphics Defines
	////***************************************************************************

	//#define ANCHOR_TOP									Graphics.TOP
	//#define ANCHOR_LEFT									Graphics.LEFT
	//#define ANCHOR_VCENTER								Graphics.VCENTER
	//#define ANCHOR_HCENTER								Graphics.HCENTER
	//#define ANCHOR_BOTTOM								Graphics.BOTTOM
	//#define ANCHOR_RIGHT								Graphics.RIGHT
	//#define ANCHOR_BASELINE								Graphics.BASELINE


	//***************************************************************************
	//** Type Defines
	//***************************************************************************
	//#define PUBLIC_STATIC 								public static 

	//#define VOID_TYPE		 								void
	//#define NULL		 									null

	//#define BOOLEAN_TYPE	 								boolean
	//#define INT_TYPE	 									int


	//***************************************************************************
	//** Variable
	//***************************************************************************
#ifndef _UN_REPLACE_

	//#define m_item_slot								g_pGame->m_item_slot
	//#define drawInventory()							g_pGame->drawInventory()
	#define game_counter								g_pGame->game_counter
	
	//#define set_market_item							g_pGame->set_market_item

	//***************************************************************************
	//** COMMON_SPRITE Methods
	//***************************************************************************
	#define COMMON_SPRITE_EMOTION                   g_pGame->load_commonSpriteArray[4]	

	//***************************************************************************
	//** Methods
	//***************************************************************************
		
	#define GET_RANDOM(min, max)							g_pGame->random(min,max)	
	#define Draw_Number( a, b, c , d , e , f ,gg )           g_pGame->Draw_Number( a, b, c  , d , e , f ,gg )
	
	#define DRAW_IMAGE(g, img, x, y, anchor)				g->DrawImage(img, x, y, anchor)
	#define DRAW_STR( g, str , x, y, anchor)				g->DrawString( str, x, y, anchor )
	
	#define DRAW_LINE(x,y,dx,dy)							g->DrawLine(x,y,dx,dy)
	#define FILL_RECT(x,y,dx,dy)							g->FillRect(x,y,dx,dy)
	#define DRAW_RECT(x,y,dx,dy)							g->DrawRect(x,y,dx,dy)
	#define SET_CLIP(x,y,dx,dy)								g->SetClip(x,y,dx,dy)

	#define SET_COLOR(color)			 					g->SetColor(color)
	#define GC()			 								System.gc()
	#define FREE_GAMERES()			 						g_pGame->Free_GameRes();

	#define SAVE_DATA( save )			 					g_pGame->SaveLoadRecord( save )
	#define GET_INT_DBDATA(data, index )			 			g_pGame->GetRecordDataInt(data, index )
	#define SET_INT_DBDATA(data, index , value )				g_pGame->SetRecordDataInt(data, index , value )
	
	#define GET_SHORT_DBDATA(data, index )			 			g_pGame->GetRecordDataShort(data, index )
	#define SET_SHORT_DBDATA(data, index , value )			 	g_pGame->SetRecordDataShort(data, index , value )
	
	#define GET_BYTE_DBDATA(data, index )			 			g_pGame->GetRecordDataByte(data, index )
	#define SET_BYTE_DBDATA(data, index , value )				g_pGame->SetRecordDataByte(data, index , value )

	//#define	SET_BYTE_ITEM									g_pGame->SetRecordItem
	//#define GET_BYTE_ITEM									g_pGame->GetRecordItem

	#define DRAW_GAUGEW(x,y,h,c,m,g,color)			 			g_pGame->Draw_GaugeW(x,y,h,c,m,g,color)

	// Function
	//#define NEW_ASPRITE( id, close )						GL_NEW ASprite(loadResource(##id, close), 0)
	#define MAP_TOTALSIZEX									g_pGame->m_tileMapW*DEF.TILE_W
	#define MAP_TOTALSIZEY									g_pGame->m_tileMapH*DEF.TILE_H
#endif
	
	// --- debug	

    //***************************************************************************
    //** Color data
    //***************************************************************************

    #define COLOR_BLACK					                     (0x000000)
    #define COLOR_RED					                     (0xff0000)
    #define COLOR_GREEN					                     (0x00ff00)
	#define COLOR_STONE					                     (0xC8A545)
    #define COLOR_BLUE					                     (0x0000ff)
    #define COLOR_WHITE					                     (0xffffff)
    #define COLOR_YELLOW				                     (0xffff00)

	#define COLOR_RESULT				                     (0xbcc269)

	#define COLOR_WATER					                     (0x42b5ef)
	#define COLOR_STONE					                     (0xC8A545)
	#define COLOR_DIE					                     (0x346453)
	#define COLOR_WEED					                     (0xAAAAAA)
	#define COLOR_BUG					                     (0x64574A)
	#define COLOR_FRUIT					                     (0x22f022)
	#define COLOR_LEVEL					                     (0x88ff88)
	#define COLOR_POPUP					                     (0x00ADAF)
	#define COLOR_POPUP_TEXT			                     (0X007B9A)
	#define COLOR_POPUP1_TEXT			                     (0X790009)
	//#define COLOR_POPUP2_TEXT			                     (0X050505)


	//***************************************************************************
	//** BackBuffer Defines
	//***************************************************************************
#ifndef _UN_REPLACE_

	#define m_lastTileX  g_pGame->m_lastTileX
	#define m_lastTileY  g_pGame->m_lastTileY
	#define m_oldLevelX  g_pGame->m_oldLevelX
	#define m_oldLevelY  g_pGame->m_oldLevelY
	#define m_imgBB g_pGame->m_imgBB
	#define m_gBB g_pGame->m_gBB


#define number_Sprite					g_pGame->load_commonSpriteArray[8]
#endif //_UN_REPLACE_


#include "Module_SoftKey.h"
#include "Module_SaveLoad.h"


#endif // #ifndef __COMMAND_DEF_H__