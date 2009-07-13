#ifndef __STATE_MENU_H__
#define __STATE_MENU_H__

///////////////  MENU SATTE DEFINE /////////////////////////////

	#define MENU_STATE_NULL		        -1
	#define MENU_STATE_TOP		        0
	#define MENU_STATE_START			(MENU_STATE_TOP+1)
//612. *
	//#define MENU_STATE_OPTION			(MENU_STATE_START+1)
#ifdef IGP_SET
   #define MENU_STATE_IGP				(MENU_STATE_START+1)
   #define MENU_STATE_OPTION			(MENU_STATE_IGP+1)
#else // NO IGP
   #define MENU_STATE_OPTION			(MENU_STATE_START+1)
#endif

	#define MENU_STATE_INFO				(MENU_STATE_OPTION+1)
	#define MENU_STATE_NETWORK			(MENU_STATE_INFO+1)


#ifndef REMOVE_STATE_PRESENT_ZONE
//GuanHao. present&zone
    #define MENU_STATE_PRESENT			(MENU_STATE_NETWORK+1)
    #define MENU_STATE_ZONE			(MENU_STATE_PRESENT+1)
//GuanHao. present&zone
	//#define MENU_STATE_EXIT				(MENU_STATE_NETWORK+1)
    #define MENU_STATE_EXIT				(MENU_STATE_ZONE+1)
#else
	#define MENU_STATE_EXIT				(MENU_STATE_NETWORK+1)
#endif  


	#define MENU_STATE_NEW				(MENU_STATE_EXIT+1)
	#define MENU_STATE_CONTINUE			(MENU_STATE_NEW+1)
	#define MENU_STATE_GOTOTOP			(MENU_STATE_CONTINUE+1)

	#define MENU_STATE_VIBRATION		(MENU_STATE_GOTOTOP+1)
	#define MENU_STATE_SOUND			(MENU_STATE_VIBRATION+1)
	#define MENU_STATE_SPEED			(MENU_STATE_SOUND+1)
//GuanHao. reset. menu
    #define MENU_STATE_RESET			(MENU_STATE_SPEED+1)
    #define MENU_STATE_RESET_COMPLETE			(MENU_STATE_RESET+1)

//GuanHao. reset. menu	
	//#define MENU_STATE_COMPANAY			(MENU_STATE_SPEED+1	)
    #define MENU_STATE_COMPANAY			(MENU_STATE_RESET_COMPLETE+1	)

	#define MENU_STATE_GAMEINFO			(MENU_STATE_COMPANAY+1)	

	//#define MENU_STATE_IGP				(MENU_STATE_GAMEINFO+1)//485
	#define MENU_STATE_PRICE			(MENU_STATE_GAMEINFO+1)

   #define MENU_STATE_GAMEGRADE		(MENU_STATE_PRICE+1)
   #define MENU_STATE_GAMEEND			(MENU_STATE_GAMEGRADE+1)



	//#define MENU_STATE_GAMEEND			(MENU_STATE_IGP+1)

	#define MENU_STATE_DATASEL_NEW		(MENU_STATE_GAMEEND+1)
    #define MENU_STATE_DATASEL_NAME		(MENU_STATE_DATASEL_NEW+1)

	
	//#define MENU_STATE_DATASEL_REPLAY	(MENU_STATE_DATASEL_NEW+1)//485
	//#define MENU_STATE_DATARESET		(MENU_STATE_DATASEL_REPLAY+1)//485

	//#define MENU_STATE_IGP				MENU_STATE_PRICE//485

	#define MENU_STATE_SUB		        50
	#define MENU_STATE_GAMESTART	    51 
	#define MENU_STATE_GAMEBUY			52 
	#define MENU_STATE_CHARATERINFO		53
	#define MENU_STATE_RANK				54
	#define MENU_STATE_OTHER			55

//612. *
//#define MENU_TOP_COUNT		        5
#ifdef IGP_SET
	#ifdef LGT_VERSION	
	#define MENU_TOP_COUNT		        6
	#else
	#define MENU_TOP_COUNT		        8
	#endif
#else // NO IGP
#ifdef REMOVE_STATE_PRESENT_ZONE	
	#define MENU_TOP_COUNT		        5
#else
    #define MENU_TOP_COUNT		        7
#endif
#endif

	//#define MENU_START_COUNT		    2

//GuanHao. reset
    //#define MENU_OPTION_COUNT		    3	
    //#define MENU_OPTION_COUNT		    4

	//#define MENU_INFO_COUNT				3//Chen Shoutian, fixed bug 	1466236
	//#define MENU_PRICE_COUNT			2//485
	//#define MENU_NEXTWORK_COUNT			2	
	//#define MENU_EXIT_COUNT				2
	//#define MENU_SUB_COUNT		        4
	//#define MENU_DATASEL_COUNT		    2
//GuanHao. reset
    //#define MENU_RESET_COUNT		    2
    //#define MENU_RESET_COMPLETE_COUNT		    2
//GuanHao. present&zone
    //#define MENU_PRESENT_COUNT		    2
    //#define MENU_ZONE_COUNT		    2

	//#define MENU_COMPANY_COUNT		    2
	
//612. *
    //#define MENU_GAMEINFO_COUNT		    6
    //#define MENU_GAMEINFO_COUNT		    32//21  //GuanHao. help
    //#define MENU_NAME_COUNT				10


	#define MENU_IMG					"/mainmenubg111666.bbm"
   //612. +
    #define INFOCREATE_IMG				"/gamegrade1.bbm"


	///////////////  MENU DRAW POSITION /////////////////////////////

//	#define MENU_GAPX					50
	//#define MENU_YESNO_GAPX				60
	//#define MENU_GAPY					25

 //  #define MENU_NAME_GAPX				35
 //  #define MENU_NAME_GAPY				17

	#define TOP_POPUP_POSX				19+5
	#define TOP_POPUP_POSY				0

	#define TOP_POPUP_SIZEX				76
	#define TOP_POPUP_SIZEY				SCREEN_HEIGHT

	#define TOP_MENU_POSX				TOP_POPUP_POSX+(TOP_POPUP_SIZEX>>1)
	#define TOP_MENU_POSY				20
	//
	//#define TOP_SUB_SIZEX				( SCREEN_WIDTH - TOP_POPUP_SIZEX - (TOP_POPUP_POSX*2) )

	////#define TOP_START_POSY				67
	////#define TOP_MENU_GAPY				46

	//#define GAME_NEW					0
	//#define	GAME_CONTINUE				1

 //   #define	GAME_REPLAY					2


///////////////  DEFINE SPRITE /////////////////////////////

	#define menu_Sprite					g_pGame->m_bSprite[1]
	#define animal_Sprite				g_pGame->m_bSprite[2]
	#define butterfly_Sprite			g_pGame->m_bSprite[3]

	#define ui_Sprite					g_pGame->load_commonSpriteArray[0]
	#define popup_Sprite				g_pGame->load_commonSpriteArray[7]

	#define softButton_Sprite		g_pGame->load_commonSpriteArray[9]
	#define softButtonAlphabe_Sprite		g_pGame->load_commonSpriteArray[11]

//612. +
#define GAMEGRADE_IMG				"/gamegrade.bbm"
#define GRAD_PASS_TIME				50

#endif //__STATE_MENU_H__