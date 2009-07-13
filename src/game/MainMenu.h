#include "VBaseState.h"
#include "SUtil.h"
#include "EventManager.h"


#ifndef __MainMenu_
#define __MainMenu_



#define C_POSX		(SCREEN_WIDTH/2)
#define C_POSY		(SCREEN_HEIGHT/2)


#define PAGE_GAMELOFT				0
#define PAGE_2558NATE				1
#define PAGE_SOUNDONOFF				2
#define PAGE_TITLE					3
#define PAGE_MAINMENU_INTRO			4
#define PAGE_MAINMENU				5

#define PAGE_GAMESTART				10
#define PAGE_SELECT_SEX				11
#define PAGE_SELECT_STYLE			12
#define PAGE_SELECT_SLOT			13

#define PAGE_GO_QUEST				10000



#define MAX_LINE				(MODULE_MAINMENU_BACK_00-MODULE_MAINMENU_MENU_00)

class MainMenu : public VBaseState
{
public:

	MainMenu();
	~MainMenu();

	struct Page{//페이지 관련 변수
		int PageNum;
		int Focus;
		int Ly1_sel;
		int Ly2_sel;
		int Ly3_sel;
		int Ly4_sel;
		int Ly5_sel;
	};
	struct NewCharacter{//페이지 관련 변수
		int Sex;
		int Style;
		int Slot;
	};

	Page s_Page;
	NewCharacter s_NC;

	#define MAINMENU_PAGE				(s_Page.PageNum)
	#define MAINMENU_ANI				(s_Page.Focus)

	#define MAINMENU_WING_STATE			(s_Page.Ly1_sel)
	#define MAINMENU_ACTION_END			(s_Page.Ly2_sel)
	#define MAINMENU_NOW				(s_Page.Ly3_sel)

	#define SOUNDONOFF_SELECT			(s_Page.Ly1_sel)
	#define SOUNDONOFF_NOW_X			(s_Page.Ly2_sel)
	#define SOUNDONOFF_TARGET_X			(s_Page.Ly3_sel)

	#define SELECT_SEX_SELECT			(s_Page.Ly1_sel)
	#define SELECT_SEX_ACTION_START			(s_Page.Ly2_sel)

	#define SELECT_STYLE_SELECT			(s_Page.Ly1_sel)
	#define SELECT_STYLE_ACTION_START			(s_Page.Ly2_sel)
	#define SELECT_STYLE_ACTION_RIGHT			(s_Page.Ly3_sel)
	#define SELECT_STYLE_ACTION_COUNT			(s_Page.Ly4_sel)

	#define SELECT_SLOT_SELECT			(s_Page.Ly1_sel)
	#define SELECT_SLOT_ACTION_START			(s_Page.Ly2_sel)
	#define SELECT_SLOT_NOW_Y			(s_Page.Ly3_sel)

	#define GO_QUEST_NUM				(s_Page.Ly1_sel)
	#define GO_QUEST_SEX				(s_Page.Ly2_sel)
	#define GO_QUEST_NOW_Y				(s_Page.Ly3_sel)


	void Initialize(int nDummy1, int nDummy2);
	void Release();
	void Process();
	void Paint();
	void KeyEvent(int m_keyCode, int m_keyRepeat);
	void Init_int();

	struct _TEXT_PACK*	pCLRPOPUP_Text;//텍스트 팩

	class ASprite* _spr_gameloft;
	class ASprite* _spr_title;
	class ASprite* _spr_MainMenu;
	class ASprite* _spr_TalkBox;

	class ASprite* _spr_MCselect;
	class ASprite* _spr_MC_Face;

	
	class ASpriteInstance* _ins_Wing;
	class ASpriteInstance* _ins_Wing_After;
	class ASpriteInstance* _ins_Arrow;
	class ASpriteInstance* _ins_Light;


	class ASpriteInstance* _ins_faceFront;
	class ASpriteInstance* _ins_faceBack;
	class ASpriteInstance* _ins_Pattern;
	class ASpriteInstance* _ins_Left;
	class ASpriteInstance* _ins_Right;
	class ASpriteInstance* _ins_Center;
	class ASpriteInstance* _ins_SideArrow;



	
};

#endif	//__MainMenu

