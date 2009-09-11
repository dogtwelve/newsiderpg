#include "SUtil.h"
#include "ASprite.h"
#include "ASpriteInstance.h"
#include "Character.h"
#include "Quest.h"

#ifndef		__POPUP_UI_H_
#define		__POPUP_UI_H_

//parameter
#define	SEX_WOMAN	0
#define	SEX_MAN		1
#define	SEX_HUMAN	2

#define POPUP_PAGE_STATES		(1)
#define POPUP_PAGE_EQUIP		(2)
#define POPUP_PAGE_INVENTORY	(3)
#define POPUP_PAGE_SKILL		(4)
#define POPUP_PAGE_HOBBY		(5)
#define POPUP_PAGE_QUEST		(6)
#define POPUP_PAGE_SYSTEM		(7)
#define POPUP_PAGE_MAX		(7)

#define POPUP_PAGE_ITEMSHOP		(10)
#define POPUP_PAGE_MIX			(11)

#define GAGE_RED		0
#define GAGE_BLUE		1
#define GAGE_YELLOW		2
#define GAGE_GREEN		3

#define XPOS		(SCREEN_WIDTH/2)
#define YPOS		(SCREEN_HEIGHT/2)

//////////////////////////////////////////////////////////////////////////////////////


#define ITEM_BAG		1

#define ITEM_POTION		2

#define ITEM_MONEY		3

#define ITEM_MIX_BOOK	6//조합서

#define ITEM_UP_STONE	7//강화석

#define ITEM_GEM_STONE	8//보석


#define ITEM_SWORD		10
//#define ITEM_AXE		11
#define ITEM_GUN		12
//#define ITEM_OEB		13
#define ITEM_HEAD		14
#define ITEM_CHEST		15
#define ITEM_LEG		16
#define ITEM_GLOVE		17
#define ITEM_NECK		18
#define ITEM_RING		19

#define ITEM_MAINQUEST		90//메인 퀘스트템



#define INVENTORY_POPUP_QUICK		0
#define INVENTORY_POPUP_EQUIP		1
#define INVENTORY_POPUP_USE			2
#define INVENTORY_POPUP_DEFAULT		3

#define INVENTORY_POPUP_BAGCHANGE	10

#define INVENTORY_TEXT_POPUP__NOT_ENOUGH	0
#define INVENTORY_TEXT_POPUP__ABANDON		1
#define INVENTORY_TEXT_POPUP__EQUIPDEL		2



#define ITEMSHOP_POPUP_BUY				0
#define ITEMSHOP_POPUP_SELL				1
#define ITEMSHOP_POPUP_BUY_COUNT		2
#define ITEMSHOP_POPUP_SELL_COUNT		3
#define ITEMSHOP_POPUP_NOT_SPACE		4
#define ITEMSHOP_POPUP_NO_MONEY			5
#define ITEMSHOP_POPUP_NOT_SELL			6


#define MIX_POPUP_QUESTION				1
#define MIX_POPUP_NO_MATERIAL			2
#define MIX_POPUP_NO_SPACE				3

#define SMITHY_POPUP_NUM				1
#define SMITHY_POPUP_QUESTION			2
#define SMITHY_POPUP_ING				3
#define SMITHY_POPUP_RESULT				4
#define SMITHY_UP_COST				    1




#define ALL_DEL					-1

#define Q_ITEM_MAX(a)				((a)		%100)
#define Q_ITEM_NOW(a)				((a)/100	%100)
#define Q_ITEM_ID(a)				((a)/10000	%10000)




//장착인덱스(2),스프라이트인덱스(2), 팔레트(1), 아이템ID(4)
#define ITEM_ID					Data0			%10000
#define ITEM_INDEX				Data0			%100
#define ITEM_KIND				Data0/100		%100
#define ITEM_PALETTE			Data0/10000		%10
#define ITEM_SPRITE				Data0/100000	%100
#define ITEM_EQUIP				Data0/10000000	%100

//소켓3(2),소켓2(2),소켓1(2),접두사(2),등급(1)
#define ITEM_GRADE				Data1			%10
#define ITEM_HEADTEXT			Data1/10		%100
#define ITEM_SOCKET_1			Data1/1000		%100
#define ITEM_SOCKET_2			Data1/100000	%100
#define ITEM_SOCKET_3			Data1/10000000	%100
#define ITEM_SEX				Data1/1000000000%10
#define ITEM_STACK_COUNT		Data1			%100
#define ITEM_MONEY_COUNT		Data1

//스크롤레벨(3),스탯스크롤(2),강화(2)
#define ITEM_UPGRADE			Data2			%100
#define ITEM_SCROLL_STATE		Data2/100		%100
#define ITEM_SCROLL_LV			Data2/10000		%1000


//////////////////////////////////////////////////////////////////////////////////////

struct Page{//공용 스프라이트 묶음
	int PageNum;
	int Woman_Man;
	int Focus;
	int Ly1_sel;
	int Ly2_sel;
	int Ly3_sel;
	int Ly4_sel;
	int Ly5_sel;
	int Ly6_sel;
	int Ly7_sel;
	int Ly8_sel;
	int Ly9_sel;
	int Ly10_sel;
	int Ly11_sel;
	int Ly12_sel;
};
struct ItemList{//공용 스프라이트 묶음
	int Color;//보유퀘스트목록
	int Kind;//아이템 인덱스
	int Index;//아이템 번호
	int Head;//접두사
	int LifeTime;//표시 지속시간
	int QUEST_now;//퀘템 현재보유량
	int QUEST_max;//퀘템 목표보유량

};
struct PlayMessage{//공용 스프라이트 묶음
	int MSG;//접두사
	int LifeTime;//표시 지속시간
};
struct AreaMessage{//지역명 메세지
	char str[30];//지역명
	int LifeTime;//표시 지속시간
};
struct Popup_Sharp{// 상세정보 팝업창
	bool View;//상세정보창의 보여지는 유무	
	int Line;//Y 스크롤
	int LineMAX;//Y 끝라인
	int posX;//X
	int posY;//Y
};




#include "PopupTable.h" //아이템 정보 테이블

const short s_X[2][7] = {{-34,56,-34,26, 26,-64,-4},{-34,56,-64,26,-64, -4,-4}};
const short s_Y[2][7] = {{-18, 0, 20,20,-18,  0, 0},{  0, 0, 20, 0,-18,-18,20}};

class PopupUi
{
public:
	PopupUi(void* s__ASpriteSet/*,ASprite* _Hero*/);
	~PopupUi();

	struct ASpriteSet{//공용 스프라이트 묶음
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	struct Quest{//공용 스프라이트 묶음
		//int MainHave;//메인 퀘스트목록
		int SubHave[20];//보유퀘스트목록
		int Max_Num;//메인퀘를 제외한 퀘스트보유갯수
	};Quest s_Quest;

	short MixBuffer[7];//조합 레시피 임시저장
	static ItemList s_ItemList[5];
	static PlayMessage s_PlayMessage;
	static AreaMessage s_AreaMessage;

	





	static Page s_Page;

#define SELECT_STATES_Y				(s_Page.Ly1_sel)



#define SELECT_EQUIP_Y				(s_Page.Ly1_sel)
#define SELECT_EQUIP_POS			(s_Page.Ly2_sel)
#define SELECT_EQUIP_LIST			(s_Page.Ly3_sel)
#define SELECT_EQUIP_LIST_MAX			(s_Page.Ly4_sel)
#define SELECT_EQUIP_LIST_NOW			(s_Page.Ly5_sel)
#define SELECT_EQUIP_LIST_NOW_BAG			(s_Page.Ly6_sel)
#define SELECT_EQUIP_LIST_NOW_SLOT			(s_Page.Ly7_sel)
#define SELECT_EQUIP_JAB_BACUP					(s_Page.Ly8_sel)

//#define SELECT_EQUIP_POS_Y			(s_Page.Ly3_sel)
//#define SELECT_EQUIP_KIND			(s_Page.Ly4_sel)
//#define SELECT_EQUIP_POPUP_KIND		(s_Page.Ly5_sel)
//#define SELECT_EQUIP_POPUP_X			(s_Page.Ly6_sel)
//#define SELECT_EQUIP_POPUP_Y			(s_Page.Ly7_sel)



#define SELECT_INVENTORY_Y				(s_Page.Ly1_sel)
#define SELECT_INVENTORY_BAG			(s_Page.Ly2_sel)
#define SELECT_INVENTORY_INSIDE			(s_Page.Ly3_sel)
#define SELECT_INVENTORY_KIND			(s_Page.Ly4_sel)
#define SELECT_INVENTORY_POPUP_KIND		(s_Page.Ly5_sel)
#define SELECT_INVENTORY_POPUP_X			(s_Page.Ly6_sel)
#define SELECT_INVENTORY_POPUP_Y			(s_Page.Ly7_sel)

#define SELECT_INVENTORY_POPUP_TEXT_KIND			(s_Page.Ly8_sel)
#define SELECT_INVENTORY_POPUP_TEXT_YESNO			(s_Page.Ly9_sel)
//#define SELECT_INVENTORY_CURSOR_ID		(s_Page.Ly4_sel)
//#define SELECT_INVENTORY_CURSOR_DATA1	(s_Page.Ly5_sel)
//#define SELECT_INVENTORY_CURSOR_DATA2	(s_Page.Ly6_sel)


#define SELECT_SKILL_Y				(s_Page.Ly1_sel)
#define SELECT_SKILL_ACT_PAS		(s_Page.Ly2_sel)
#define SELECT_SKILL_SLOT			(s_Page.Ly3_sel)
#define SELECT_SKILL_TYPE			(s_Page.Ly4_sel)
#define SELECT_SKILL_KIND			(s_Page.Ly6_sel)

#define SELECT_SKILL_SELECT			(s_Page.Ly8_sel)

#define SELECT_SKILL_ACC_X			(s_Page.Ly9_sel)
#define SELECT_SKILL_ACC_Y			(s_Page.Ly10_sel)
#define SELECT_SKILL_C_X			(s_Page.Ly11_sel)
#define SELECT_SKILL_C_Y			(s_Page.Ly12_sel)

#define QUEST_DESC					(8)//출력 줄 수
#define SELECT_QUEST_Y				(s_Page.Ly1_sel)
#define SELECT_QUEST_SUB_Y			(s_Page.Ly2_sel)
#define SELECT_QUEST_DESC_Y			(s_Page.Ly3_sel)
#define SELECT_QUEST_DESC_Y_MAX		(s_Page.Ly4_sel)
#define SELECT_QUEST_DESC_X			(s_Page.Ly5_sel)

#define SELECT_SYSTEM_Y				(s_Page.Ly1_sel)
#define SELECT_SYSTEM_CHEAT				(s_Page.Ly9_sel)
#define SELECT_SYSTEM_CHEAT_CHECKER				(s_Page.Ly10_sel)

#define SELECT_GAMEOVER_Y			(s_Page.Ly1_sel)

#define SELECT_MIX_Y_SCROLL				(s_Page.Ly1_sel)
#define SELECT_MIX_MAX_NUM			(s_Page.Ly2_sel)
#define SELECT_MIX_SEX				(s_Page.Ly3_sel)
#define SELECT_MIX_SELECT			(s_Page.Ly4_sel)
#define SELECT_MIX_MAKE_NUM			(s_Page.Ly5_sel)
#define SELECT_MIX_MAKE_MAX			(s_Page.Ly6_sel)
#define SELECT_MIX_POPUP_KIND		(s_Page.Ly7_sel)
#define SELECT_MIX_POPUP_YESNO		(s_Page.Ly8_sel)


#define SELECT_ITEMSHOP_X				(s_Page.Ly1_sel)
#define SELECT_ITEMSHOP_Y				(s_Page.Ly2_sel)
#define SELECT_ITEMSHOP_BAG				(s_Page.Ly3_sel)
#define SELECT_ITEMSHOP_FOCUS_R_L		(s_Page.Ly4_sel)
#define SELECT_ITEMSHOP_INSIDE			(s_Page.Ly5_sel)
#define SELECT_ITEMSHOP_R_SCROLL		(s_Page.Ly6_sel)
#define SELECT_ITEMSHOP_L_SCROLL		(s_Page.Ly7_sel)
#define SELECT_ITEMSHOP_POPUP_KIND			(s_Page.Ly8_sel)
#define SELECT_ITEMSHOP_POPUP_TEXT_YESNO	(s_Page.Ly10_sel)
#define SELECT_ITEMSHOP_COUNT				(s_Page.Ly11_sel)


#define SELECT_SMITHY_Y					(s_Page.Ly1_sel)
#define SELECT_SMITHY_ITEM_SLOT			(s_Page.Ly3_sel)
#define SELECT_SMITHY_STONE_SLOT		(s_Page.Ly4_sel)
#define SELECT_SMITHY_LIST_MAX			(s_Page.Ly5_sel)
#define SELECT_SMITHY_LIST_NOW			(s_Page.Ly6_sel)
#define SELECT_SMITHY_LIST_ITEM_BAG			(s_Page.Ly7_sel)
#define SELECT_SMITHY_LIST_ITEM_SLOT			(s_Page.Ly8_sel)
#define SELECT_SMITHY_USE_STONE_BAG				(s_Page.Ly9_sel)
#define SELECT_SMITHY_USE_STONE_SLOT					(s_Page.Ly10_sel)

#define SELECT_SMITHY_USE_STONE_NUM					(s_Page.Ly2_sel)


#define SELECT_SMITHY_POPUP_KIND		(s_Page.Ly11_sel)
#define SELECT_SMITHY_POPUP_TEXT_YESNO	(s_Page.Ly12_sel)



    static Popup_Sharp s_Popup_Sharp;

	

	int PAGE_STATES_point[5];//포인트//힘//민첩//체력//지력
	//class ASprite* m_pHeroAs;
	static struct _TEXT_PACK*	pCLRPOPUP_Text;//텍스트 팩
	struct _TEXT_PACK*	pMAIN_QUEST_Text;//메인 퀘스트 팩
	struct _TEXT_PACK*	pSUB_QUEST_Text;//서브 퀘스트 팩
	struct _TEXT_PACK*	pITEM_Text;//아이템 팩
	//int** p_ReceiveData;
	
	


	int ani_Num;
	bool SkillChange_A;//스킬의 교환이 일어나면 True 로 활성화된다
	//bool SkillChange_P;//스킬의 교환이 일어나면 True 로 활성화된다
	bool GameOver;//게임오버로 인한 ui 호출시 활성화
	bool ShopOpen;//상점이 열렸을때 샵이 활성화된다
	bool SmithyOpen;//대장간이 열렸을때 활성화된다
	int ShopLevel;//상점이 열렸을때 나올 아이템 수준을 참조
	static bool MixOpen;//조합 창이 활성화된다
	static int MixNum;//조합 창이 활성화된다



	bool KeyEvent(int m_keyCode, int m_keyRepeat);
	void Process();
	void Paint();


	
	
	
	
	
	void Key_STATES(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업
	void Key_EQUIP(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업
	void Key_INVENTORY(int m_keyCode, int m_keyRepeat)	;//취소키를 누르면 호출되는 팝업
	void Key_SKILL(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업
	void Key_HOBBY(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업
	void Key_QUEST(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업
	void Key_SYSTEM(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업	
	void Key_GAMEOVER(int m_keyCode, int m_keyRepeat)		;//취소키를 누르면 호출되는 팝업	
	void Key_ITEMSHOP(int m_keyCode, int m_keyRepeat)		;//마을상점 키 이벤트
	void Key_SMITHY(int m_keyCode, int m_keyRepeat)			;//마을대장간 키 이벤트
	void Key_MIX(int m_keyCode, int m_keyRepeat)			;//조합서 키 이벤트


	void Paint_STATES()		;//취소키를 누르면 호출되는 팝업
	void Paint_EQUIP()		;//취소키를 누르면 호출되는 팝업
	void Paint_INVENTORY()	;//취소키를 누르면 호출되는 팝업
	void Paint_SKILL()		;//취소키를 누르면 호출되는 팝업
	void Paint_HOBBY()		;//취소키를 누르면 호출되는 팝업
	void Paint_QUEST()		;//취소키를 누르면 호출되는 팝업
	void Paint_SYSTEM()		;//취소키를 누르면 호출되는 팝업
	void Paint_GAMEOVER()		;//주인공이 죽으면 호출되는 팝업
	void Paint_ITEMSHOP()		;//마을NPC와의 대화로 열수있는 아이템 구입페이지
	void Paint_SMITHY()			;//마을NPC와의 대화로 열수있는 아이템 강화페이지
	void Paint_MIX()			;//조합서를 사용하면 뜨는 인벤토리 서브페이지


	struct ItemBag MakeItem(int nMontype, int nMonLevel, int nHeroSex, int mapIdx);		//성별man:0,girl:1
	void  MakeShop(int ShopKind, int ShopLevel);		//샵내 존재하는 아이템을 생성
	int  CalkCost(struct ItemBag _item);		//아이템의 가치를 산정한다
	static bool GET_item(struct ItemBag* _item);//아이템을 넣었으면 True를 인벤이 부족해 먹지 못한경우에는False 를 리턴한다
	static int itemICON(struct ItemBag _item)	;//낱개의 아이템의 아이콘 인덱스를 넘겨주는 부분
	static void USE_item(struct ItemBag *_item);//아이템 사용
	static void  Del_Item(struct ItemBag *_item);
private:
	void PaintPopup_Sharp(struct ItemBag _item);
	void PaintPopup_Sharp(int Skill_Num);
	void PaintNumber(ASprite* pAsIns, int numImgIdx, int value, int x, int y, int gap , int position);
	void PaintGage(int gageType, int gagewidth,int gageheight, int x, int y, int nowvalue, int maxvalue);
	int itemNAME(int m_Kind, int m_Index)	;//낱개의 아이템의 텍스트 인덱스를 넘겨주는 부분
	void itemTEXT(struct ItemBag _item,int L1,int L2,int L3,int L4)	;//낱개의 아이템의 텍스트 인덱스를 넘겨주는 부분



	void QSLOT_item(struct ItemBag *_item);//퀵슬롯 
	void QSLOT_find();
	void EQUIP_item(int slot,struct ItemBag *_item);//아이템 착용
	void DEL_item();//아이템 버리기
	void MOVE_item();//아이템 이동

	void SORTING_bag(int bagNum);//가방 정렬
	bool INPUT_bag(int bagNum, struct ItemBag _item);//가방에 빈공간이 없다면 리턴 False
	int get_BagMax(struct ItemBag _item);
	void paint_ICON(struct ItemBag _item, int x, int y,bool full);
	
	void Del_Slot(int sex,int slot);
	
	
	void  equipTEXT(int sex,int slot,struct ItemBag _item);
	void  Set_Item(struct ItemAbility *_abil,struct ItemBag *_item);
	

public:
	static void  Page_init();
	static int GET_Count(int itemID,int SEX = SEX_HUMAN);
	int REMOVE_Item(int itemID,int counter,int SEX = SEX_HUMAN);

	static int  Set_QUEST(int itemID,int MainQuest);//해당하는 퀘스트가 만약 아이템 수집의뢰라면 아이템ID 와 현재갯수,맥스갯수를 리턴한다
	static void  AddItemList(struct ItemBag _item);
	void  PaintItemList();
	static void  AddMessage(int m_MSG);
	void  PaintMessage();
	static void  AddAreaMessage(char *c_AreaName);
	void  PaintAreaMessage();

//	class ASprite* m_pWorldMapAs;
};

#endif
