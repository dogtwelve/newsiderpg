#define GAME_STATE_MAP	            0


//#define GAME_STATE_POPUP			1
//#define GAME_STATE_INVENTORY		2
//#define GAME_STATE_POPUP_MAIL		3//485
//#define GAME_STATE_POPUP_MARKET		4
//#define GAME_STATE_POPUP_PRESENT	5
//#define GAME_STATE_MEMOPOPUP		6
//#define GAME_STATE_QUEST_START		7
//#define GAME_STATE_MINI_FESTIVAL	8
//#define GAME_STATE_POPUP_SLEEP		9

//#define GAME_STATE_BANK				11

//#define GAME_STATE_END				10

//#define GAME_STATE_QUEST_RESTART	12


///////////////  CHEAT DEFINE /////////////////////////////

	#define CHEAT_MAX_COUNT		        8 //( ##9137** )

	#define CHEAT_DATA1					GAME_KEY_POUND	//( ##9137** )
	#define CHEAT_DATA2					GAME_KEY_POUND	//( ##9137** )

#ifdef USE_KEY_PONE
	#define CHEAT_DATA3					GAME_KEY_9		//( ##9137** )
	#define CHEAT_DATA4					GAME_KEY_1		//( ##9137** )
	#define CHEAT_DATA5					GAME_KEY_3		//( ##9137** )
	#define CHEAT_DATA6					GAME_KEY_7		//( ##9137** )
#else
	#define CHEAT_DATA3					GAME_KEY_3		//( ##3791** )
	#define CHEAT_DATA4					GAME_KEY_7		//( ##3791** )
	#define CHEAT_DATA5					GAME_KEY_9		//( ##3791** )
	#define CHEAT_DATA6					GAME_KEY_1		//( ##3791** )
#endif

	#define CHEAT_DATA7					GAME_KEY_STAR	//( ##9137** )
	#define CHEAT_DATA8					GAME_KEY_STAR	//( ##9137** )

//PUBLIC_STATIC ASprite Boy_Sprite;


