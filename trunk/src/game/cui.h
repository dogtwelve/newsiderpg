#ifndef _UI_
#define _UI_


//#include "./NetSource/cXPlayerMenus.h"
#include "ASpriteInstance.h"

//#include "MainMenu.h"//SangHo - 임시
//#include "MainGAME.h"//SangHo - 임시

//#include "cObject_bird.h"
//#include "cObject_Character.h"
//#include "..\common\Image.h"
//class cObject_Character;
//class cObject_bird;

#include "UI_Map.h"

class CImage;
class cGame;


extern int keyCodePress;//SangHo - Key 이벤트 임시구현
extern int keyCodeRelease;//SangHo - Key 이벤트 임시구현
extern bool keyLife;//SangHo - Key 이벤트 임시구현

#define BSPRITE(x) g_pGame->load_spriteArray[x]

class cUI {
public:

//	cXPlayerMenus* player ;

	cUI();
	//{
	//	moveState = 1 ;		
	//	stackA = -1;	
	//	stackCnt = 0;	
	//	stackB = -1;
	//	change_active = false;
	//	change_size = 0;	
	//	change_direct = 0;	
	//	change_Maxsize = 0;	
	//	change_count = 0;	
	//	change_replay = 0;

	//	displayResetInfo = false;

	//	player = GL_NEW cXPlayerMenus(g_pGame,g_pGame->jFont);

	//	if(player)
	//	{
	//		MC_knlCreateSharedBuf( (const M_Char *)"pXPlayer", sizeof(cXPlayerMenus*) );

	//		//player = new cXPlayerMenus( instance_, cKFont_ );

	//		*(cXPlayerMenus**)MC_GETDPTR((void*)MC_knlGetSharedBuf((const M_Char *)"pXPlayer")) = player;
	//	}
	//}

	~cUI();

	int keyCodeCui;//SangHo - Key 이벤트 임시구현

	int select_point;

	int mon_AI[2];//SangHo - 임시Ai변수


//	bool displayResetInfo;
//	cObject_Character* Boy_Object;
	int*	Cheat_Data;
	int*	Cheat_Input;
	int		Cheat_count;
	int		cheat_samecount; 
	int		cheat_intputcount; 
	int		cheat_money; 
	int		cheat_state; 
//	int		chicken_run_cnt ;
//	int		char_run_cnt;

	
	CImage*					img_Gamegrade;
	CImage*					img_splash;
	CImage*					img_GgeMark;

	//CImage*					img_New;

//	int	auto_move;	
		
//	int attack_dog_cnt;	
	int moveState;// = 1 ;		
	int stackA;// = -1;	
	int stackCnt;// = 0;	
	int stackB;// = -1;	
	
	int	menu_State; 	

//	int* menu_List;	
	int	menu_Maxcount;	
	int	menu_count;	
	int	menu_Str_count;	

	int	menu_Next_cursor;	
	int	menu_cur_cursor;	
	int	menu_Before_cursor;	
	int	menu_Pointer;	
	int	menu_Before_Pointer;	

	//612. +
	int	menu_NamePointer;


	int	popup_rectposX;	
	int	popup_rectposY;	
	int	popup_rectsizeX;	
	int	popup_rectsizeY;	

//	int	title_frame;	
//	int	title_Nextframe;	
//	int	title_posX;	
//	int	title_posY;	

	//612. +
	//bool			key_Active ;


//	bool change_active;// = false;	
	//bool* data_save;	
//	bool data_save;

//	int	change_replay;

//	int	change_size;// = 0;	
//	int	change_direct;// = 0;	
//	int	change_Maxsize;// = 0;	
//	int	change_count;// = 0;	

//	cObject_Character** npc_Object;
//	int npc_Object_length;
//	int*	Draw_Order;	
//	int*	temp_Order;		


	//CImage* img_mainmenu;	
	//612. +
	//CImage*  img_infocreate;	

	char** menu_str;	
	char* str_version;

	int	menu_strscroll_count;	

	bool bClock;	
	//byte item_max;	
	//byte market_menu;

	//int popup_ListposX;

	//===================================================================
	#define FISH_BALL_EA	5 
	#define FISH_BALL_MAX_SPEED		10
	#define FISH_BALL_MIN_SPEED		5
	
	#define FISH_BALL_SIZEW			20

	int vel;
	int f_firePos; //
	int f_ballPos[2*FISH_BALL_EA];
	int f_ballVel[FISH_BALL_EA];
	
	//// aaa	
	int f_BallPos;
	int f_BallVel;
	int f_fireVel;
	////////
	
	byte isFire;
	int fish_Catch;
	byte setBall_cnt;

	byte sp_BFishing;

	//===================================================================



	bool b_show_Entity;



	//================================================================

	///// VARIABLE OF BUILD MODE

	//================================================================

	int			build_state_mode;			// 0.NOMAL, 1.BUILD MODE
	int			build_staet_type;			// BUILD TYPE 


	int			build_posX;			// BUILD POSITION X 
	int			build_posY;			// BUILD POSITION Y 


	#define BUILD_MODE_INIT							0

	#define BUILD_MODE_MENU							1

	#define BUILD_MODE_ACTIVE						2
	


	//================================================================

	///// VARIABLE of UI_Ending.h

	//================================================================

	//int				end_mode;			// 0.HAPPY, 1.BAD ENDING
	//int				end_state;	

	//int				rect_size;			// FADE OUT SIZE


	//CImage*				img_backending;
	//CImage*				img_ending;


	//int				end_fade_state;
	//int				end_fade_cur;
	//int				end_fade_Max;

	//int				end_text_Direct;
	//int				end_text_posY;
	//int				end_text_MaxposY;
	//int				end_text_count;

	//int				end_Select_Point;
	//int				old_Select_Point;


////////////////////////////////////////////////




/////////////////////////
	//UI_Net.h
//	int* scoreArray;

   //612. +
#define COMPANY_SKT						0
#define COMPANY_KTF						1
#define COMPANY_LGT						2

#define GGI_SKT							0
#define GGI_KTF							4
#define GGI_LGT							7

#define GGI_SIZE_120					120
#define GGI_SIZE_176					176
#define GGI_SIZE_240					240
#define GGI_SIZE_320					320


#define NET_MENU_MAX					3

#define CHARGE_ORIGIN					0
#define CHARGE_EXPANT_GOGAME			1
#define CHARGE_EXPANT_GOMENU			2

	int   sel_point;

    bool  down_success;

#define Netpopup_Sprite					g_pGame->load_commonSpriteArray[5]

///////////////////
public:

	void set_move( cEntity* _obj , int _auto_move);

	int check_move( cEntity* _obj,int _posX  ,int _posY  );

	int Set_Keypressed_Direct( );
	//int Set_touch_Direct( cObject_Character* _obj , int step_run_next );
		
	int Set_Keyrepeate_Direct(  );	
	int Set_Keyreleased_Direct(  );
	
	int Set_KeyEvent();

	//void Set_EscapeEntity( cEntity* _obj , cEntity* _target );

	void Set_FollowEntity( cEntity* _obj , cEntity* _target );	


	void Set_Entity( cEntity* _target, int _direct , int _movestate );
	//void set_moveing_reset();
		
	//void set_move_reset();

	//612
	//void set_moveing_reset_dog(cObject_Character* _obj);
		
	void Set_Camera_Position( cEntity* _obj );

	void Set_Camera_Position( int _x , int _y );


	void Update_Entity(  );

	void Update_Entity_ShowLayer (  );
		
	void Entity_Update(  cEntity* _obj, int _moveX, int _moveY );
		
	//void set_snake_move(int _direct , int posX , int posY ,  int _moveX , int _moveY);
		

		
	//bool check_snake_ID();
	//SangHo - S - Temp
	void process_Main_Test(int message);
	void process_UI_Test(int message);
	//SangHo - E - Temp



	void process_UI_GameWG( int message );
		
	void process_UI_SelectSound( int message );
	 	
	void process_UI_Splash( int message );

	//GuanHao. IGP
	//void process_UI_IGP(int message);	

	void process_UI_GameGrade( int message );

	void process_UI_Menu( int message );

	void update_KeyMenu();

	void draw_Menu();

	void draw_Start_Channel();
	void draw_End_Channel();

	void process_USER_Openning( int message );

	void process_USER_House( int message );

	void process_USER_Map1( int message );

	void process_USER_Chapter( int message );

	//void other_paint();
	
	//void tutorial_start_init();
	
	//void draw_sleep_popup();
	
	//void set_Quest();
	
	//void process_USER_Map( int message );
	
	//void updatge_game_state_Popup();
	
	//612. +
	//void updatge_game_state_Popup_CLR();

	//void update_game_state_market();
	
	//void update_game_state_present();
	
	//void update_game_state_map();
	
	//612. +
	//void Set_Inventory(int _state );

	void update_Zone();

	void Set_Chage_map( int _collnum );
	
	//void draw_arrow_map( );

	//void pursuit_object_auto(int _id , int _map_kind , bool bID);//485

	//void draw_TIME_LAP(int index);//485

	//void Set_Sound_Pasure( int _state, boolean _loop);//485

	////////UI_Ending.hpp
	//void process_MINI_Ending( int message );//485

	//void Draw_Ending( );//485

	//void Process_Ending( );//485

	//void Set_Fade( );//485

    //void Process_BadEnd( );//485

    //void Process_Select( );//485



	void draw_Interface();
	///////////////////////////////////////////////////////////
	//** fish
	///////////////////////////////////////////////////////////
	void fish_Game(int _x , int _y)	;
	void fish_Game1(int _x , int _y)	;
	void set_init_Ball();
	void set_Ball();
	bool isInFireZone(int index);


	//////////////////////Key Event/////////////////////////////////////
	void getKeyrelease();//SangHo - Key 이벤트 임시구현
	void getKeypress();//SangHo - Key 이벤트 임시구현
	//////////////////////Key Event/////////////////////////////////////


	///////////////////////////////
	//////////////UI_Net.hpp
	//void process_UI_Net( int message );

	//612. +
	//void process_UI_NetDown( int message );
	//void process_UI_NetPay( int message );
	void Set_Net_NextState( byte _state );

	void keyProcess();

	void logicProcess();

	int Set_GGI();

	/////////////////////////////////////
		
	//GuanHao. reset
	void resetGame(bool autoOpen);

	void init_Cheat( );
	
	void Draw_Cheat( );
	
	void key_Cheat( );	
	
	//void process_Opening( int message );

	//void Set_GameStart( int _state );//485

	//void Set_ReplayFlag( );

};	

#endif//_UI_
