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

#define ITEM_MIX_BOOK	6//���ռ�

#define ITEM_UP_STONE	7//��ȭ��

#define ITEM_GEM_STONE	8//����


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

#define ITEM_MAINQUEST		90//���� ����Ʈ��



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




//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
#define ITEM_ID					Data0			%10000
#define ITEM_INDEX				Data0			%100
#define ITEM_KIND				Data0/100		%100
#define ITEM_PALETTE			Data0/10000		%10
#define ITEM_SPRITE				Data0/100000	%100
#define ITEM_EQUIP				Data0/10000000	%100

//����3(2),����2(2),����1(2),���λ�(2),���(1)
#define ITEM_GRADE				Data1			%10
#define ITEM_HEADTEXT			Data1/10		%100
#define ITEM_SOCKET_1			Data1/1000		%100
#define ITEM_SOCKET_2			Data1/100000	%100
#define ITEM_SOCKET_3			Data1/10000000	%100
#define ITEM_SEX				Data1/1000000000%10
#define ITEM_STACK_COUNT		Data1			%100
#define ITEM_MONEY_COUNT		Data1

//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)
#define ITEM_UPGRADE			Data2			%100
#define ITEM_SCROLL_STATE		Data2/100		%100
#define ITEM_SCROLL_LV			Data2/10000		%1000


//////////////////////////////////////////////////////////////////////////////////////

struct Page{//���� ��������Ʈ ����
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
struct ItemList{//���� ��������Ʈ ����
	int Color;//��������Ʈ���
	int Kind;//������ �ε���
	int Index;//������ ��ȣ
	int Head;//���λ�
	int LifeTime;//ǥ�� ���ӽð�
	int QUEST_now;//���� ���纸����
	int QUEST_max;//���� ��ǥ������

};
struct PlayMessage{//���� ��������Ʈ ����
	int MSG;//���λ�
	int LifeTime;//ǥ�� ���ӽð�
};
struct AreaMessage{//������ �޼���
	char str[30];//������
	int LifeTime;//ǥ�� ���ӽð�
};
struct Popup_Sharp{// ������ �˾�â
	bool View;//������â�� �������� ����	
	int Line;//Y ��ũ��
	int LineMAX;//Y ������
	int posX;//X
	int posY;//Y
};




#include "PopupTable.h" //������ ���� ���̺�

const short s_X[2][7] = {{-34,56,-34,26, 26,-64,-4},{-34,56,-64,26,-64, -4,-4}};
const short s_Y[2][7] = {{-18, 0, 20,20,-18,  0, 0},{  0, 0, 20, 0,-18,-18,20}};

class PopupUi
{
public:
	PopupUi(void* s__ASpriteSet/*,ASprite* _Hero*/);
	~PopupUi();

	struct ASpriteSet{//���� ��������Ʈ ����
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	struct Quest{//���� ��������Ʈ ����
		//int MainHave;//���� ����Ʈ���
		int SubHave[20];//��������Ʈ���
		int Max_Num;//�������� ������ ����Ʈ��������
	};Quest s_Quest;

	short MixBuffer[7];//���� ������ �ӽ�����
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

#define QUEST_DESC					(8)//��� �� ��
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

	

	int PAGE_STATES_point[5];//����Ʈ//��//��ø//ü��//����
	//class ASprite* m_pHeroAs;
	static struct _TEXT_PACK*	pCLRPOPUP_Text;//�ؽ�Ʈ ��
	struct _TEXT_PACK*	pMAIN_QUEST_Text;//���� ����Ʈ ��
	struct _TEXT_PACK*	pSUB_QUEST_Text;//���� ����Ʈ ��
	struct _TEXT_PACK*	pITEM_Text;//������ ��
	//int** p_ReceiveData;
	
	


	int ani_Num;
	bool SkillChange_A;//��ų�� ��ȯ�� �Ͼ�� True �� Ȱ��ȭ�ȴ�
	//bool SkillChange_P;//��ų�� ��ȯ�� �Ͼ�� True �� Ȱ��ȭ�ȴ�
	bool GameOver;//���ӿ����� ���� ui ȣ��� Ȱ��ȭ
	bool ShopOpen;//������ �������� ���� Ȱ��ȭ�ȴ�
	bool SmithyOpen;//���尣�� �������� Ȱ��ȭ�ȴ�
	int ShopLevel;//������ �������� ���� ������ ������ ����
	static bool MixOpen;//���� â�� Ȱ��ȭ�ȴ�
	static int MixNum;//���� â�� Ȱ��ȭ�ȴ�



	bool KeyEvent(int m_keyCode, int m_keyRepeat);
	void Process();
	void Paint();


	
	
	
	
	
	void Key_STATES(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_EQUIP(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_INVENTORY(int m_keyCode, int m_keyRepeat)	;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_SKILL(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_HOBBY(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_QUEST(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Key_SYSTEM(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�	
	void Key_GAMEOVER(int m_keyCode, int m_keyRepeat)		;//���Ű�� ������ ȣ��Ǵ� �˾�	
	void Key_ITEMSHOP(int m_keyCode, int m_keyRepeat)		;//�������� Ű �̺�Ʈ
	void Key_SMITHY(int m_keyCode, int m_keyRepeat)			;//�������尣 Ű �̺�Ʈ
	void Key_MIX(int m_keyCode, int m_keyRepeat)			;//���ռ� Ű �̺�Ʈ


	void Paint_STATES()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_EQUIP()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_INVENTORY()	;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_SKILL()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_HOBBY()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_QUEST()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_SYSTEM()		;//���Ű�� ������ ȣ��Ǵ� �˾�
	void Paint_GAMEOVER()		;//���ΰ��� ������ ȣ��Ǵ� �˾�
	void Paint_ITEMSHOP()		;//����NPC���� ��ȭ�� �����ִ� ������ ����������
	void Paint_SMITHY()			;//����NPC���� ��ȭ�� �����ִ� ������ ��ȭ������
	void Paint_MIX()			;//���ռ��� ����ϸ� �ߴ� �κ��丮 ����������


	struct ItemBag MakeItem(int nMontype, int nMonLevel, int nHeroSex, int mapIdx);		//����man:0,girl:1
	void  MakeShop(int ShopKind, int ShopLevel);		//���� �����ϴ� �������� ����
	int  CalkCost(struct ItemBag _item);		//�������� ��ġ�� �����Ѵ�
	static bool GET_item(struct ItemBag* _item);//�������� �־����� True�� �κ��� ������ ���� ���Ѱ�쿡��False �� �����Ѵ�
	static int itemICON(struct ItemBag _item)	;//������ �������� ������ �ε����� �Ѱ��ִ� �κ�
	static void USE_item(struct ItemBag *_item);//������ ���
	static void  Del_Item(struct ItemBag *_item);
private:
	void PaintPopup_Sharp(struct ItemBag _item);
	void PaintPopup_Sharp(int Skill_Num);
	void PaintNumber(ASprite* pAsIns, int numImgIdx, int value, int x, int y, int gap , int position);
	void PaintGage(int gageType, int gagewidth,int gageheight, int x, int y, int nowvalue, int maxvalue);
	int itemNAME(int m_Kind, int m_Index)	;//������ �������� �ؽ�Ʈ �ε����� �Ѱ��ִ� �κ�
	void itemTEXT(struct ItemBag _item,int L1,int L2,int L3,int L4)	;//������ �������� �ؽ�Ʈ �ε����� �Ѱ��ִ� �κ�



	void QSLOT_item(struct ItemBag *_item);//������ 
	void QSLOT_find();
	void EQUIP_item(int slot,struct ItemBag *_item);//������ ����
	void DEL_item();//������ ������
	void MOVE_item();//������ �̵�

	void SORTING_bag(int bagNum);//���� ����
	bool INPUT_bag(int bagNum, struct ItemBag _item);//���濡 ������� ���ٸ� ���� False
	int get_BagMax(struct ItemBag _item);
	void paint_ICON(struct ItemBag _item, int x, int y,bool full);
	
	void Del_Slot(int sex,int slot);
	
	
	void  equipTEXT(int sex,int slot,struct ItemBag _item);
	void  Set_Item(struct ItemAbility *_abil,struct ItemBag *_item);
	

public:
	static void  Page_init();
	static int GET_Count(int itemID,int SEX = SEX_HUMAN);
	int REMOVE_Item(int itemID,int counter,int SEX = SEX_HUMAN);

	static int  Set_QUEST(int itemID,int MainQuest);//�ش��ϴ� ����Ʈ�� ���� ������ �����Ƿڶ�� ������ID �� ���簹��,�ƽ������� �����Ѵ�
	static void  AddItemList(struct ItemBag _item);
	void  PaintItemList();
	static void  AddMessage(int m_MSG);
	void  PaintMessage();
	static void  AddAreaMessage(char *c_AreaName);
	void  PaintAreaMessage();

//	class ASprite* m_pWorldMapAs;
};

#endif
