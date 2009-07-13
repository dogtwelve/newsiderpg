#ifndef _DEFINES_
#define _DEFINES_
#pragma warning(disable:4819) //한글 주석을 달때 생기는 특수한 경고메세지");
//#include "header/c/Data.hpp"
//#include "header/c/LocalisationText.hpp"

#include "Data.h"
#include "TEXT.h"
#include "TALK.h"
#include "SPRITE_DESC.h"
#include "Keypad.h"



//***************************************************************************
//** Text field Defines
//***************************************************************************
#define AUTOMATA_NUM1			  3  

#define TEXTFIELD_NEWNAME_X				10
#define TEXTFIELD_NEWNAME_Y				-30
#define TEXTFIELD_NEWNAME_WIDTH			60
#define TEXTFIELD_NEWNAME_HEIGHT		17



#define TEXTFELDMAXSIZE			8

	typedef enum
	{
		AUTOMATA_EN_SMALL,
		AUTOMATA_NUMBER,
		AUTOMATA_KR
	}_automateType;

//***************************************************************************
//** Screen Defines
//***************************************************************************
//#define DBG_FPS
//#define DBG_HEAPTEST
#define HAS_SOUND

//#define DEBUG_MESSAGE_EVENT

//***************************************************************************
//** Screen Defines
//***************************************************************************

#define SCREEN_HALF_WIDTH						(SCREEN_WIDTH >> 1)
#define SCREEN_HALF_HEIGHT						(SCREEN_HEIGHT >> 1)

//***************************************************************************
//** Main loop Defines
//***************************************************************************
#define GAME_STATUS_RUNNING						0
#define GAME_STATUS_SUSPENDED					1

//***************************************************************************
//** Game State Defines
//***************************************************************************
#define STATE_LOAD                              0
#define STATE_UNLOAD                            1
#define STATE_LOAD_COMMON						2
#define STATE_GAMELOFT                          3
#define STATE_GAMEGRADE                         4
#define STATE_SELECTSOUND						5
#define STATE_SPLASH                            6
#define STATE_MENU_MAIN                         7
//#define STATE_IGP								8

#define STATE_MAIN_MENU                         9//SangHo - 임시

#define STATE_NET								16
#define STATE_DOWNNET							17
#define STATE_PAYNET							18

//#define STATE_DRAW_MAP							22
#define STATE_DRAW_OPENNING						27
#define STATE_DRAW_HOUSE						28
#define STATE_DRAW_MAP1							29	
#define STATE_DRAW_CHAPTER						30

//***************************************************************************
//** Map Mode Defines (map_kind)
//***************************************************************************
#define HOUSE_MYHOME				0
#define WORLD_MAP1					1
#define CHAPTER_1					2

//***************************************************************************
//** Game Mode Defines
//***************************************************************************

#define DIRECT_NULL					0
#define DIRECT_LEFT					1
#define DIRECT_RIGHT				2

#define DIRECT_UP					3
#define DIRECT_DOWN					4

#define DIRECT_CENTER				5
#define DIRECT_LEFTTORIGHT			6
#define DIRECT_RIGHTTOLEFT			7

#define DIRECT_0					10
#define DIRECT_1					11
#define DIRECT_2					12
#define DIRECT_3					13
#define DIRECT_4					14
#define DIRECT_5					15
#define DIRECT_6					16
#define DIRECT_7					17
#define DIRECT_8					18
#define DIRECT_9					19


//***************************************************************************
//** INVEN SLOT DEFINES
//***************************************************************************
#define INVEN_ITEM_KIND_MAX					2
#define INVEN_ITEM_SOLT_MAX					20

#define INVEN_BAG_TOOL						0
#define INVEN_BAG_FRUIT						2		
#define INVEN_BAG_ANIMAL					3
#define INVEN_BAG_FISHNET					1

//***************************************************************************
//** Message Defines
//***************************************************************************

#define MESSAGE_INIT	                                    0
#define MESSAGE_UPDATE                                      1
#define MESSAGE_PAINT                                       2
#define MESSAGE_EXIT                                        3
#define MESSAGE_SHOWNOTIFY                                  4


//***************************************************************************
//** ActorsData Defines
//***************************************************************************

//basic param
#define ACTOR_GTSID					0
#define	ACTOR_GAMEID				1
#define	ACTOR_POSX					2
#define	ACTOR_POSY					3

#define	ACTOR_ANIID					4
#define ACTOR_FLAGS					5
#define ACTOR_COUNT					6


#define ACTOR_PATROL_X1				6
#define ACTOR_PATROL_X2				7
#define ACTOR_PATROL_Y1				8
#define ACTOR_PATROL_Y2				9

#define ACTOR_VELOCITY				10			 

#define ACTOR_ARROW_STRINGTYPE		6
#define ACTOR_ARROW_ACTIVE			7


// trigger param
#define ACTOR_TRIGGER_WIDTH			4
#define ACTOR_TRIGGER_HEIGHT		5
#define ACTOR_TRIGGER_EVENT			6
#define ACTOR_TRIGGER_PARAM			7
#define ACTOR_TRIGGER_RESULT1		8
#define ACTOR_TRIGGER_RESULT2		9
#define ACTOR_TRIGGER_RESULT3		10
#define ACTOR_TRIGGER_FLAGS			11   // 0=always, 1=once, 2=hint

#define ACTOR_MAX					15

#define ACTOR_MAPOBJECT_MAX				7

//***************************************************************************
//** TEXT Defines
//***************************************************************************
#define TEXT_INDEX_COMMON				0
#define	TEXT_INDEX_MENU					1
#define TEXT_INDEX_GAME					2
#define TEXT_INDEX_MAP					3
#define TEXT_INDEX_ITEM					4


//***************************************************************************
//** TEXT Defines
//***************************************************************************



//***************************************************************************
//** Keycode Defines
//***************************************************************************

#ifdef USE_KEY_PONE
	#define GAME_KEY_0								    	CKeypad::DK_NUM0
	#define GAME_KEY_1								    	CKeypad::DK_NUM1
	#define GAME_KEY_2								    	CKeypad::DK_NUM2
	#define GAME_KEY_3								    	CKeypad::DK_NUM3
	#define GAME_KEY_4								    	CKeypad::DK_NUM4
	#define GAME_KEY_5									   	CKeypad::DK_NUM5
	#define GAME_KEY_6									   	CKeypad::DK_NUM6
	#define GAME_KEY_7						    			CKeypad::DK_NUM7
	#define GAME_KEY_8						    			CKeypad::DK_NUM8
	#define GAME_KEY_9							    		CKeypad::DK_NUM9
#else
	#define GAME_KEY_0								    	CKeypad::DK_NUM0
	#define GAME_KEY_7								    	CKeypad::DK_NUM7
	#define GAME_KEY_8								    	CKeypad::DK_NUM8
	#define GAME_KEY_9								    	CKeypad::DK_NUM9
	#define GAME_KEY_4								    	CKeypad::DK_NUM4
	#define GAME_KEY_5									   	CKeypad::DK_NUM5
	#define GAME_KEY_6									   	CKeypad::DK_NUM6
	#define GAME_KEY_1						    			CKeypad::DK_NUM1
	#define GAME_KEY_2						    			CKeypad::DK_NUM2
	#define GAME_KEY_3							    		CKeypad::DK_NUM3
#endif


#define GAME_KEY_NULL							 		    0x00000000
#define GAME_KEY_POUND						    			CKeypad::DK_POUND
#define GAME_KEY_STAR						    			CKeypad::DK_STAR
#define GAME_KEY_SOFTKEY_LEFT				    			CKeypad::DK_SOFT_LEFT
#define GAME_KEY_SOFTKEY_RIGHT				    			CKeypad::DK_SOFT_RIGHT
#define GAME_KEY_UP						   					CKeypad::DK_PAD_UP
#define GAME_KEY_LEFT						    			CKeypad::DK_PAD_LEFT
#define GAME_KEY_RIGHT										CKeypad::DK_PAD_RIGHT
#define GAME_KEY_DOWN				    					CKeypad::DK_PAD_DOWN
#define GAME_KEY_CLICK				    					CKeypad::DK_PAD_MIDDLE
///////////////////////////////////////////////////////////////////////
#define GAME_KEY_VOL_UP										0x01000000
#define GAME_KEY_VOL_DOWN									0x02000000
///////////////////////////////////////////////////////////////////////
#ifdef KR_WIPI_VERSION
	#define GAME_KEY_CLEAR					    				CKeypad::DK_CLEAR
#else
	#define GAME_KEY_CLEAR					    				CKeypad::DK_CLEAR
#endif


//#define GAME_KEY_END						        		0x00100000
//#define GAME_KEY_RESET      								0x01000000

#define GAME_KEY_SIDE_UP									0x00200000
#define GAME_KEY_SIDE_DOWN									0x00400000

#define GAME_KEY_ALL_DOWN				    				(GAME_KEY_DOWN | GAME_KEY_8)
#define GAME_KEY_ALL_UP					    				(GAME_KEY_UP | GAME_KEY_2)
#define GAME_KEY_ALL_LEFT				    				(GAME_KEY_LEFT | GAME_KEY_4)
#define GAME_KEY_ALL_RIGHT					    			(GAME_KEY_RIGHT | GAME_KEY_6)
#define GAME_KEY_ALL_ACTION						    		(GAME_KEY_CLICK | GAME_KEY_5)
#define GAME_KEY_ALL_1						    			(GAME_KEY_1)
#define GAME_KEY_ALL_3						    			(GAME_KEY_3)
#define GAME_KEY_ALL_7						    			(GAME_KEY_7)
#define GAME_KEY_ALL_9						    			(GAME_KEY_9)

//GuanHao. IGP
#define GAME_KEY_MENU_ALL_ACTION						    (GAME_KEY_CLICK | GAME_KEY_5 | GAME_KEY_SOFTKEY_RIGHT)
#define GAME_KEY_MENU_PRE_ACTION						    (GAME_KEY_SOFTKEY_LEFT | GAME_KEY_CLEAR)

#define GAME_KEY_NUMERIC                                    (GAME_KEY_0 | GAME_KEY_1 | GAME_KEY_2 | GAME_KEY_3 | GAME_KEY_4 | GAME_KEY_5 | GAME_KEY_6 | GAME_KEY_7 | GAME_KEY_8 | GAME_KEY_9)
#define GAME_KEY_0_5                                        (GAME_KEY_0 | GAME_KEY_1 | GAME_KEY_2 | GAME_KEY_3 | GAME_KEY_4 | GAME_KEY_5)


//#define ANY_KEY_PRESS()										((g_pGame->game_keyPressedSingle) != 0)
//#define ANY_KEY_PRESSED()                                   ((g_pGame->game_keyPressedSingle | g_pGame->game_keyPressedHeld) != 0)
//#define KEY_PRESSED(key)                                    ((g_pGame->game_keyPressedSingle & (key)) != 0)
//#define KEY_NOT_PRESSED(key)                                ((g_pGame->game_keyPressedSingle & (key)) == 0)
//#define KEY_HELD(key)                                       ((g_pGame->game_keyPressedHeld & (key)) != 0)
//#define KEY_NOT_HELD(key)                                   ((g_pGame->game_keyPressedHeld & (key)) == 0)
//#define KEY_PRESSED_OR_HELD(key)                            (((g_pGame->game_keyPressedSingle | g_pGame->game_keyPressedHeld) & (key)) != 0)
//#define KEY_NOT_PRESSED_OR_HELD(key)                        (((g_pGame->game_keyPressedSingle | g_pGame->game_keyPressedHeld) & (key)) == 0)
//#define KEY_RELEASE(key)									((g_pGame->game_keyPressedSingle & (key)) != 0 && g_pGame->game_keyRepeatCount > 0)


#define ANY_KEY_PRESS()										g_pGame->IsAnyKeyPressed()
#define ANY_KEY_PRESSED()                                   g_pGame->IsAnyKeyPressed()
#define KEY_PRESSED(key)                                    g_pGame->IsKeyPressed(key)
//#define KEY_NOT_PRESSED(key)                                g_pGame->game_keyPressedSingle & (key)) == 0)
#define KEY_HELD(key)                                       g_pGame->IsKeyHold(key)
//#define KEY_NOT_HELD(key)                                   g_pGame->game_keyPressedHeld & (key)) == 0)
#define KEY_PRESSED_OR_HELD(key)                            (g_pGame->IsKeyHold(key) || g_pGame->IsKeyPressed(key) )
//#define KEY_NOT_PRESSED_OR_HELD(key)                        g_pGame->game_keyPressedSingle | g_pGame->game_keyPressedHeld) & (key)) == 0)
#define KEY_RELEASE(key)									g_pGame->IsKeyReleased(key)



//#define TOUCHRELEASE										g_pGame->TouchRelease()
//#define TOUCHDOWNANY											(g_pGame->TouchDownHere(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
//#define TOUCHANY											(g_pGame->TouchHere(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
//#define TOUCHHERE(x, y, w, h)								(g_pGame->TouchHere(x, y, w, h))
//#define TOUCHDOWNHERE(x, y, w, h)							(g_pGame->TouchDownHere(x, y, w, h))
//#define TOUCHCLEAR											(g_pGame->TouchClear())
//#define TOUCHSOFTL											(g_pGame->TouchSoftL())
//#define TOUCHSOFTR											(g_pGame->TouchSoftR())
//#define TOUCHX												g_pGame->TouchX()
//#define TOUCHY												g_pGame->TouchY()

#define STARTY		42
#define STARTX		32
#define START0		0
#define RANGE0		48
#define START1		(48-1)
#define RANGE1		32
#define START2		(START1 + RANGE1 -1)
#define RANGE2		40
#define START3		(START2 + RANGE2 - 1)
#define RANGE3		50
#define BAR_WIDTH_IGM (START3 + RANGE3)
#define BAR_HEIGHT_IGM 18

#if USE_GC
	#define DO_GC()							System.gc(); Thread.yield();
#else
	#define DO_GC()							;
#endif
	#define DI_GC()							System.gc(); Thread.yield();
	
// --- math fixed point
#define F2I(a)						((a)>>FIXED_PRECISION)//cGame.Math_fixedPointToInt(a)
#define I2F(a)						((a)<<FIXED_PRECISION)//cGame.Math_intToFixedPoint(a)


#define SPRITE_INIT_PAGE()                                                          g_pGame->s_isDrawPageInit = false 

#define SPRITE_DRAW_PAGE(g, string, x, y, width, height, scroll, anchor)			g_pGame->DrawPage(g, string, x, y, width, height, scroll, anchor, true)

#define SPRITE_DRAW_STATIC_PAGE(g, string, x, y, width, height, scroll, anchor)		g_pGame->DrawPage(g, string, x, y, width, height, scroll ,anchor, false)

#define SPRITE_DRAWBOLD_PAGE(g, string, x, y, width, height, scroll, anchor)			g_pGame->DrawPage_Bold(g, string, x, y, width, height, scroll, anchor, true)

#define SPRITE_DRAWBOLD_STATIC_PAGE(g, string, x, y, width, height, scroll, anchor)		g_pGame->DrawPage_Bold(g, string, x, y, width, height, scroll ,anchor, false)


#define SPRITE_KRINIT_PAGE()														 g_pGame->jFont->isInitalizedPage = false 

#define DRAW_KOR_PAGE(g, str, x, y, width, height, arg, autoscroll)					g_pGame->jFont->drawPage(g, str, x, y, width, height, arg, autoscroll )

#define GET_KOR_STRWIDTH( str )														g_pGame->jFont->stringWidth( str )

#define DRAW_KORSTR( g, str , x, y, anchor , color )								g_pGame->jFont->setColor(color);g_pGame->jFont->DrawString(g, str , x, y, anchor, false)//color);

#define DRAW_KORSTR_LINE( g, str , x, y, anchor , color ,color1)					g_pGame->jFont->setOutline(true);g_pGame->jFont->setOutlineColor(color);g_pGame->jFont->setColor(color1);g_pGame->jFont->DrawString(g, str , x, y, anchor, false);g_pGame->jFont->setOutlineColor(-1);g_pGame->jFont->setOutline(false)//color1);

#define DRAW_KORSTR_ORG( g, str , x, y, anchor , newline )							g_pGame->jFont->DrawString(g, str , x, y, anchor, newline)

#define DRAW_KORSTR_BOLD( g, str , x, y, anchor , newline )							g_pGame->jFont->drawString_bold(g, str , x, y, anchor, newline)

#define SET_STRING_OUT_LINE(index)													g_pGame->jFont->setOutline(index)
#define SET_STRING_OUT_LINE_COLOR(index)											g_pGame->jFont->setOutlineColor(index)
#define SET_STRING_COLOR(index)														g_pGame->jFont->setColor(index)

#define STRING_CONCAT( FRONT_STR, END_STR )		                                    ( FRONT_STR + END_STR )
#define GET_STRING(index,text_index)                                                 g_pGame->Text_getString(index, text_index)

#define NEW(ptr,type)					{ptr = GL_NEW type;}
#define DELETE(ptr)						{ptr = NULL;}



//#define COS(a)						g_pGame->s_math_cosTable[(a) & 0xFF]
//#define SIN(a)						COS(64 - a) //cGame.Math_sin(a)
//#define TAN(a)						g_pGame->Math_tan(a)
#define ATAN(a,b)					g_pGame->Math_atan(a,b)
#define RND(a,b)					g_pGame->random(a,b) //a에서 b까지
#define SQRT(a)						g_pGame->Math_sqrt(a)




#define SOUND_MULTYPLAY(id,loop)	g_pGame->playMultySound(id,loop)
#define FREE_MULTYSOUND()			g_pGame->freeMultySound()

#define INIT_MULTYSOUND(a)			g_pGame->initMultySound(a)
#define LOAD_MULTYSOUND(list,id)	g_pGame->loadMultySound(list,id)

#define SOUND_PLAY(id,loop)			g_pGame->playSound(id,loop)
#define SOUND_STOP()				g_pGame->stopSound()

#define VIBRATE(time)				g_pGame->setVib(time)

#define	SET_NUMBER_SMALL(variable , number)				if( variable < 	number ) 	variable = number
#define	SET_NUMBER_LARGE(variable , number)				if( variable > 	number ) 	variable = number
#define	SET_NUMBER_SMALL1(variable , number1 , number2)	if( variable < 	number1 ) 	variable = number2
#define	SET_NUMBER_LARGE1(variable , number1 , number2)	if( variable > 	number1 ) 	variable = number2
	
//#define ABS(x)											(((x) < 0) ? -(x) : (x))					// 절대값 
#define SIGN(x)											((x) > 0 ? 1 : ((x) == 0 ? 0: (-1)))	// 양수:1, 0, 음:-1 
//#define MAX( a, b )										( a > b ? a : b )
//#define MIN( a, b )										( a < b ? a : b )

//***************************************************************************
//** Aurora
//***************************************************************************

#define SPRITE_PAINT_FRAME(sprite, g, frame, x, y, flags, hx, hy)                   sprite->PaintFrame(g, frame, x, y, flags, hx, hy)
#define SPRITE_PAINT_MODULE(sprite, g, module, x, y, flags)                         sprite->PaintModule(g, module, x, y, flags)



// ANIM ----------------------------------------------------------------- general
#define ANIM_EMPTY					-1
#define	ANIM_EXIT					-2
#define ANIM_DEFAULT				0

#define getSprite(sprID)				m_bSprite[sprID]
#define getEntity(entID)				m_entEntities[entID]


// --- misc optimization
#define getFlags()						m_flags
#define setFlag(flag)					m_flags |= flag
#define unsetFlag(flag)					m_flags &= ~flag

#define SET_FLAG(dest, flag)		dest |= (flag)
#define RESET_FLAG(dest, flag)		dest &= (~(flag))
#define TEST_FLAG(dest, flag)		(((dest) & (flag)) != 0)
#define RESETALL_FLAG(dest)			dest = 0
#define ENUM_TO_MASK(enumValue)		(1 << (enumValue))




//#define DBG(str)			 							System.out.println(str);
#define DBG(str)			 							

#define TRACE_CINEMATIC(msg)							 DBG("CINEMATIC : " + msg); 

	//---------------------------------------------------------------------------
	/// Type Defines
	//---------------------------------------------------------------------------
	#define PUBLIC_STATIC 								public static 
	#define STATIC_TYPE 								static
	#define PUBLIC										public

	#define VOID_TYPE		 							void
	#define BOOLEAN_TYPE	 							boolean
	#define INT_TYPE	 								int
	#define BYTE_TYPE	 								byte
	#define SHORT_TYPE									short
	#define FINAL										final


	//---------------------------------------------------------------------------
	/// Type Defines
	//---------------------------------------------------------------------------

	#define POPUP_SELECT_COLOR						0x44d49c

	#define POPUP_SELECT_FONT_LINE_COLOR			0x25992B
	#define POPUP_SELECT_FONT_COLOR					0xffffff

	#define POPUP_DESC_TITLE_FONT_COLOR				0x353F10
	#define POPUP_DESC_FONT_COLOR					0x000000

	//---------------------------------------------------------------------------
	/// Graphics Defines
	//---------------------------------------------------------------------------

	#define ANCHOR_TOP									CGraphics::TOP
	#define ANCHOR_LEFT									CGraphics::LEFT
	#define ANCHOR_VCENTER								CGraphics::VCENTER
	#define ANCHOR_HCENTER								CGraphics::HCENTER
	#define ANCHOR_BOTTOM								CGraphics::BOTTOM
	#define ANCHOR_RIGHT								CGraphics::RIGHT
	#define ANCHOR_BASELINE								CGraphics::BASELINE
	#define ANCHOR_TOPLEFT								CGraphics::TOP|CGraphics::LEFT
	#define ANCHOR_TOPCENTER							CGraphics::TOP|CGraphics::HCENTER
	
//---------------------------------------------------------------------------
/// Generic flag variable get/set, etc.
//---------------------------------------------------------------------------



#define NONE_SLOT					0



//---------------------------------------------------------------------------
/// 캐릭터 적용 옵션들
//---------------------------------------------------------------------------
#define CHAR_RAPID_FOOD				1

//---------------------------------------------------------------------------
/// CHARACTER object define
//---------------------------------------------------------------------------

#define CHARACTER_HPMAX					108000			

#define CHARACTER_MINUS					(CHARACTER_HPMAX/7)
#define CHARACTER_HP_BASIC_USE			-12
//minhdang -20
#define CHARACTER_HP_RUN_USE			-3
//minhdang -6
#define CHARACTER_HP_WORK_USE			-6
#define CHARACTER_HP_HALF_FELL_USE		-40

#define	GAME_PAUSE_OFF()				g_pGame->m_game_pause = false
#define	GAME_PAUSE_ON()					g_pGame->m_game_pause = true
#define	TIME_PAUSE_OFF()				g_pGame->m_time_pause = false
#define	TIME_PAUSE_ON()					g_pGame->m_time_pause = true
#define CHAR_PAUSE_ON()					g_pGame->m_chrMove_pause = true
#define CHAR_PAUSE_OFF()				g_pGame->m_chrMove_pause = false

//---------------------------------------------------------------------------
/// DOG object define
//---------------------------------------------------------------------------

//#define	BOY_ORDER						1
//#define	DOG_ORDER						2
//
//
//#define DOG_ACTION_NONE								0
//#define DOG_ACTION_BARK								1
//#define DOG_ACTION_ATTACK							2
//#define DOG_ACTION_BARK_ON							4					


//---------------------------------------------------------------------------
/// CHARTER TALK define
//---------------------------------------------------------------------------
#define EMOTION_TYPEA					1		
#define EMOTION_TYPEB					2
#define EMOTION_TYPEC					3
#define EMOTION_TYPED					4
#define EMOTION_TYPEF					1
#define EMOTION_TYPEQ					5

//---------------------------------------------------------------------------
/// SLEEP define
//---------------------------------------------------------------------------
//#define SLEEP_FULL						0		
//#define SLEEP_HALF_CLOCK10				1
//#define SLEEP_HALF						2
//#define SLEEP_80						3
//#define SLEEP_80_CLOCK8					4

//---------------------------------------------------------------------------
/// QUEST define
//---------------------------------------------------------------------------
//#define QUEST_INVEN_STATE					0
//#define QUEST_INVEN_ITEM_NUMBER_Y			1
//#define QUEST_INVEN_REQUIRE					2
//#define QUEST_INVEN_RETENTION				3
//#define QUEST_INVEN_EVENT_TUTORIAL			4
//#define QUEST_INVEN_ITEM_NUMBER				5
//#define QUEST_INVEN_RESULT_A				6
//#define QUEST_INVEN_RESULT_B				7
//---------------------------------------------------------------------------
/// Quest define
//---------------------------------------------------------------------------
//#define QUEST_ING_NUMBER				0
//#define QUEST_STATE						1
//#define QUEST_NPC_ENTITY				2
//
////#define QUEST_STATE
//#define QUEST_STATE_READY				1
//#define QUEST_STATE_START				2
//#define QUEST_STATE_ING					3
//#define QUEST_STATE_COMPLETE			4
//#define QUEST_STATE_COMPLETE2			5
//#define QUEST_STATE_END					0


//
//interface NPC
//{
//	final static int NPC_TC_1       = 0; //도구 점_캐릭터_1 (농장 상점=== farm)
//	final static int NPC_TC_2		= 1; //촌장_캐릭터_2		
//	final static int NPC_TC_3		= 2; //도박장_캐릭터_3		
//	final static int NPC_TC_4		= 3; //레스토랑_캐릭터_3		
//	final static int NPC_TC_5		= 4; //낚시가게_캐릭터_4		
//	final static int NPC_TC_6		= 5; //꽃집_캐릭터_5		
//	final static int NPC_TC_7		= 6; //자동차상점_캐릭터_6
//	final static int NPC_TC_8		= 7; //목공소 wood_man
//
//}

//---------------------------------------------------------------------------
/// MASCOT STATE define
//---------------------------------------------------------------------------

#define MASCOT_SENCE_STATE_POPUP					0x00000002  
#define MASCOT_SENCE_STATE_END						0x00000001   //0x01

//#define MASCOT_SENCE_STATE_QUEST_START				0x00000004	//0x03
//#define MASCOT_SENCE_STATE_QUEST_END				0x00000008
//
//#define MASCOT_SENCE_STATE_HEALTH_END				0x00000010
//#define MASCOT_SENCE_STATE_CLOCK_END				0x00000020
//#define MASCOT_SENCE_STATE_NPC_TALK_END				0x00000040
//#define MASCOT_SENCE_STATE_NPC_TALK2_END			0x00000080
//#define MASCOT_SENCE_STATE_NPC_TALK3_END			0x00000100
//#define MASCOT_SENCE_STATE_NPC_TALK4_END			0x00000200
//#define MASCOT_SENCE_STATE_QUEST_RESTART			0x00000400
//#define MASCOT_SENCE_STATE_NPC_END_END				0x00000800
//#define MASCOT_SENCE_STATE_GAME_OVER				0x00001000	
//#define MASCOT_SENCE_STATE_POPUP_SOUND				0x00002000
//#define MASCOT_SENCE_STATE_GAME_HAPPYEND			0x00004000
//#define MASCOT_SENCE_STATE_DOG_DIE					0x00008000
//#define MASCOT_SENCE_STATE_REPLAY					0x00010000
////#define MASCOT_SENCE_STATE_NPC_QEND_END				0x00010000
//#define MASCOT_SENCE_STATE_YYY_NO1					0x00100000
//#define MASCOT_SENCE_STATE_YYY_NO2					0x00200000
//#define MASCOT_SENCE_STATE_YYY_NO3					0x00400000
//#define MASCOT_SENCE_STATE_POPUPEND 				3

// The mascot states

#define MASCOT_STATE_HIDDEN                             0
#define MASCOT_STATE_SHOW_CHMASCOT                      1
#define MASCOT_STATE_SHOW_MASCOT                        2
#define MASCOT_STATE_SHOW_POPUP	                        3
#define MASCOT_STATE_SHOW_TEXT                          4


#define MASCOT_CHMASCOT_PAGEY                          28+14

#define CHMASCOT_SHOW_RIGHT                          70



//---------------------------------------------------------------------------
/// result Popup title define
//---------------------------------------------------------------------------
#define POPUP_NONE_TITLE						-1
#define POPUP_TITLE_PRESENT						0
#define POPUP_TITLE_SEED						1
#define POPUP_TITLE_MENU						2
#define POPUP_TITLE_RESULT						3
#define POPUP_TITLE_MARKET						4
#define POPUP_TITLE_TOTAL						5
#define POPUP_TITLE_SUCCESS						6
#define POPUP_TITLE_FAIL						7
#define POPUP_TITLE_MISSION						8
#define POPUP_TITLE_FUND						9


#define POPUP_KIND_MARKET						0
#define POPUP_KIND_PRESENT						1
#define POPUP_KIND_SEED							2
#define POPUP_KIND_MENU							3
#define POPUP_KIND_TALK							4
#define POPUP_KIND_RESULT_MISSION				5
#define POPUP_KIND_RESULT						6
#define	POPUP_KIND_FUND							7
#define POPUP_KIND_DOGBOY						8
#define POPUP_KIND_FISH							9




// -------------------------------------------------------- Item and Inventory
//#define ITEM_ID				0
//
//#define ITEM_GROUP			0
//#define ITEM_INVEN			1
//#define ITEM_KIND			2
//#define ITEM_SELL_EA		3
//#define ITEM_PRICE			4
//#define ITEM_ETC			5
//
//
//// ITEM_GROUP
//#define IT_GROUP_FARM		1
//#define IT_GROUP_FISH		2
//#define IT_GROUP_FLOWER		3
//#define IT_GROUP_ANIMAL		4
//#define IT_GROUP_FOOD		5
//#define IT_GROUP_HOUSE		6
//// ITEM_KIND
//#define IT_KIND_DURABILITY	0
//#define IT_KIND_UPGRADE		1	
//#define IT_KIND_FISHUPGRADE	2
//#define IT_KIND_EXHAUSTION	3
//#define IT_KIND_ACQUISITION 4
//#define IT_KIND_FOOD		10
//
////ITEM_PRICE
//#define IT_PRICE_BUY		0
//#define IT_PRICE_SELL		1
//#define IT_PRICE_REPAIR		2
//***************************************************************************
//** menu KEY Defines
//***************************************************************************
	
#define ONEDEPTH							0
#define TWODEPTH							1
#define THREEDEPTH							2
#define FOURDEPTH							3
#define FIVEDEPTH							4

//---------------------------------------------------------------------------
/// Item define
//---------------------------------------------------------------------------
//#define ITEM_WATERINGPOT_1						0
//#define ITEM_WATERINGPOT_2						1
//#define ITEM_WATERINGPOT_3						2
//#define ITEM_HAMMER_1							3	
//#define ITEM_HAMMER_2							4
//#define ITEM_HAMMER_3							5
//#define ITEM_INSECT_1							6
//#define ITEM_INSECT_2							7	
//#define ITEM_INSECT_3							8
//#define ITEM_SEED_1								9		
//#define ITEM_SEED_2								10
//#define ITEM_SEED_3								11
//#define ITEM_SLINGSHOT_1						12
//#define ITEM_SLINGSHOT_2						13	
//#define ITEM_SLINGSHOT_3						14	
//#define ITEM_WATERTANK_1						15
//#define ITEM_WATERTANK_2						16
//#define ITEM_WATERTANK_3						17
//#define ITEM_WATERTANK_4						18	
//#define ITEM_SCARECROW_1						19
//#define ITEM_SCARECROW_2						20
//#define ITEM_SCARECROW_3						21
//#define ITEM_STRAWBERRY_1						22
//#define ITEM_MELON_1							23
//#define ITEM_WATERMELON_1						24
//#define ITEM_TOMATO_1							25
//#define ITEM_STRAWBERRY_2						26
//#define ITEM_MELON_2							27
//#define ITEM_WATERMELON_2						28
//#define ITEM_TOMATO_2							29
//#define ITEM_STRAWBERRY_3						30
//#define ITEM_MELON_3							31	
//#define ITEM_WATERMELON_3						32	
//#define ITEM_TOMATO_3							33
//
//#define ITEM_ROD_1								34
//#define ITEM_ROD_2								35
//#define ITEM_ROD_3								36
//#define ITEM_LINE_1								37
//#define ITEM_LINE_2								38
//#define ITEM_LINE_3								39
//#define ITEM_BAIT_1								40	
//#define ITEM_BAIT_2								41
//#define ITEM_BAIT_3								42
//#define ITEM_FISHNET_1							43
//#define ITEM_FISHNET_2							44
//#define ITEM_FISHNET_3							45
//#define ITEM_FISH								46
//
//#define ITEM_ROSE								47
//#define ITEM_FORSYTHIA							48
//#define ITEM_DAISY								49	
//#define ITEM_LILY								50
//#define ITEM_AZALEA								51
//#define ITEM_LILAC								52
//#define ITEM_SULTAN								53
//#define ITEM_SUNFLOWER							54
//#define ITEM_ORCHID								55
//#define ITEM_COSMOS								56
//#define ITEM_CAKE_1								57
//#define ITEM_CAKE_2								58	
//#define ITEM_CAKE_3								59	
//
//
//#define ITEM_COW_1								60
//#define ITEM_COW_2								61
//#define ITEM_SHEEP_1							62
//#define ITEM_SHEEP_2							63
//#define ITEM_MILK_A								64
//#define ITEM_MILK_B								65
//#define ITEM_MILK_C								66
//#define ITEM_MILK_D								67
//#define ITEM_MILK_E								68
//#define ITEM_WOOL_A								69
//#define ITEM_WOOL_B								70
//#define ITEM_WOOL_C								71
//#define ITEM_WOOL_D								72
//#define ITEM_WOOL_E								73
//
//
//#define ITEM_RICERROLL							74
//#define ITEM_SUSHI								75
//#define ITEM_NOODLES							76	
//#define ITEM_RICE								77
//#define ITEM_CAN								78
//#define ITEM_WATER								79	
//#define ITEM_FRIEDRICE							80
//#define ITEM_FRIEDNOODLES						81
//
//#define ITEM_HOUSE_1							82
//#define ITEM_HOUSE_2							83
//#define ITEM_HOUSE_3							84
//#define ITEM_CUTTER_1							85
//#define ITEM_CUTTER_2							86
//#define ITEM_CUTTER_3							87





//---------------------------------------------------------------------------
/// Tutorial define
//---------------------------------------------------------------------------

#define STORY_OPENNING_END						1
#define STORYL_HOUSEOPENNING_END				2
#define STORYL_HOUSEBUG_END						3



//#define TUTORIAL_FARM2_START					10
//#define TUTORIAL_FISH_START					20
//#define TUTORIAL_BREEDING_START				30
//#define TUTORIAL_BREEDING2_START				35
//#define TUTORIAL_PUZZLE_START					50
//#define TUTORIAL_RESTO_START					60
//#define TUTORIAL_SLEEP_START					70
//#define TUTORIAL_BANK2_START					80
//#define TUTORIAL_BANK_START					90
//
//
//#define TUTORIAL_QUEST1_START					100
//#define TUTORIAL_QUEST2_START					110
//#define TUTORIAL_QUEST3_START					120
//#define TUTORIAL_QUEST4_START					130
//#define TUTORIAL_QUEST4_1_START				135
//#define TUTORIAL_QUEST5_START					140
//#define TUTORIAL_MAIL_START					180


#define ANIMATION_OPENING						0
#define ANIMATION_HOUSEOPENING					1


//---------------------------------------------------------------------------
/// Day working
//---------------------------------------------------------------------------

#define DAY_FARM								0x01	
#define DAY_FISH								0x02
#define DAY_BREEDING							0x04
#define DAY_PUZZLE								0x08	
#define DAY_FESTIVAL							0x10
#define DAY_WOOL								0x20



//---------------------------------------------------------------------------
/// Food Using
//---------------------------------------------------------------------------
#define USE_FOOD								0x01	
#define USE_DRINK								0x02



//---------------------------------------------------------------------------
/// One object
//---------------------------------------------------------------------------
//#define ITEM_DOG								0x00000001
//#define ITEM_SEED								0x00000002
//#define ITEM_G1									0x00000004
//#define ITEM_G2									0x00000008
//#define ITEM_G3									0x00000010
//#define ITEM_G4									0x00000020
//#define ITEM_G5									0x00000040
//#define ITEM_G6									0x00000080
//#define ITEM_G7									0x00000100
//#define ITEM_G8									0x00000200
//#define ITEM_G9									0x00000400
//#define ITEM_G10								0x00000800
//#define ITEM_Q1									0x00008000
//
//#define ITEM_DOG1								0x00010000
//#define ITEM_SEED1								0x00020000
//#define ITEM_G11								0x00040000
//#define ITEM_G21								0x00080000
//#define ITEM_G31								0x00100000
//#define ITEM_G41								0x00200000
//#define ITEM_G51								0x00400000
//#define ITEM_G61								0x00800000
//#define ITEM_G71								0x01000000
//#define ITEM_G81								0x02000000
//#define ITEM_G91								0x04000000
//#define ITEM_G101								0x08000000
//#define ITEM_Q11								0x80000000

//---------------------------------------------------------------------------
/// Sound define
//---------------------------------------------------------------------------
#define EFFECT_SWORD_A					0
#define EFFECT_SWORD_B					1
#define EFFECT_SWORD_C					2
#define EFFECT_SWORD_D					3
#define EFFECT_GUN_A					4
#define EFFECT_GUN_B					5
#define EFFECT_ORB_A					6
#define EFFECT_ORB_B					7
#define EFFECT_ORB_C					8
#define BGM_TEST_A					9








#endif