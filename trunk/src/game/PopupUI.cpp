#include "PopupUi.h"


Page PopupUi::s_Page;
ItemList PopupUi::s_ItemList[5];
PlayMessage PopupUi::s_PlayMessage;
AreaMessage PopupUi::s_AreaMessage;
_TEXT_PACK* PopupUi::pCLRPOPUP_Text;
bool PopupUi::GemOpen;
bool PopupUi::MixOpen;
int PopupUi::MixNum;
Popup_Sharp PopupUi::s_Popup_Sharp;

PopupUi::PopupUi(void* s__ASpriteSet/*,ASprite* _Hero*/)
{
	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // �׸���,ȿ�� ����Ʈ ��������Ʈ�� ������
	//m_pHeroAs = _Hero;

	pCLRPOPUP_Text = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_CLRMENU_TEXT);//�ؽ�Ʈ �� �ε�
	pMAIN_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_MAIN_QUEST_TEXT);//���� ����Ʈ �� �ε�
	pSUB_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_SUB_QUEST_TEXT);//���� ����Ʈ �� �ε�
	pITEM_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_ITEM_TEXT);//����Ʈ �� �ε�
	s_Page.PageNum = 1;//ù ������

	//s_Quest.MainHave = 0;
	s_Quest.Max_Num = 0;
	ShopLevel = 10;
	/*s_Quest.SubHave[0] = 2;
	s_Quest.SubHave[1] = 3;
	s_Quest.SubHave[2] = 4;
	s_Quest.SubHave[3] = 5;
	s_Quest.SubHave[4] = 6;
	s_Quest.SubHave[5] = 7;
	s_Quest.SubHave[6] = 8;*/

	Character::s_Status[Character::s_HeroTag.SEX].MONEY = 10000;


	Character::s_ItemSlot[0].Data0 = 103;
	Character::s_ItemSlot[1].Data0 = 102;
	Character::s_ItemSlot[2].Data0 = 101;
	Character::s_ItemSlot[3].Data0 = 100;

	Character::s_ItemBag[0][0].Data0 = 201;
	Character::s_ItemBag[0][0].Data1 = 55;//1000000055;
	Character::s_ItemBag[0][1].Data0 = 204;
	Character::s_ItemBag[0][1].Data1 = 55;
	Character::s_ItemBag[0][2].Data0 = 102;

	Character::s_ItemBag[0][3].Data0 = 600;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][3].Data1 = 0;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][3].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][4].Data0 = 601;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][4].Data1 = 0;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][4].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][5].Data0 = 700;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][5].Data1 = 50;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][5].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][6].Data0 = 701;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][6].Data1 = 50;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][6].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][7].Data0 = 702;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][7].Data1 = 50;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][7].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][8].Data0 = 700;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][8].Data1 = 20;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][8].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)



	Character::s_ItemBag[0][10].Data0 = 1024;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][10].Data1 = 10101033+1000000000;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][10].Data2 = 230109;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][11].Data0 = 1019;
	Character::s_ItemBag[0][11].Data1 = 101022;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][11].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][12].Data0 = 1014;
	Character::s_ItemBag[0][12].Data1 = 101022;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][12].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][13].Data0 = 1009;
	Character::s_ItemBag[0][13].Data1 = 101022;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][13].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][14].Data0 = 1224;
	Character::s_ItemBag[0][14].Data1 = 1031;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][14].Data2 = 231111;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)


	Character::s_ItemBag[0][19].Data0 = 1424;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][19].Data1 = 10101033+1000000000;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][19].Data2 = 230109;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][20].Data0 = 1424;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][20].Data1 = 10101033;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][20].Data2 = 230109;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][21].Data0 = 1419;
	Character::s_ItemBag[0][21].Data1 = 101022;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][21].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][22].Data0 = 1414;
	Character::s_ItemBag[0][22].Data1 = 101022;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][22].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][23].Data0 = 1509;
	Character::s_ItemBag[0][23].Data1 = 22+1000000000;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][23].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][24].Data0 = 1524;
	Character::s_ItemBag[0][24].Data1 = 1031+1000000000;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][24].Data2 = 231111;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)


	Character::s_ItemBag[1][0].Data0 = 800;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][0].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][0].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][1].Data0 = 801;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][1].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][1].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][2].Data0 = 802;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][2].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][2].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][3].Data0 = 803;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][3].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][3].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][4].Data0 = 804;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][4].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][4].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][5].Data0 = 805;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][5].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][5].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][6].Data0 = 806;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][6].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][6].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][7].Data0 = 807;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][7].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][7].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][8].Data0 = 808;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][8].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][8].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][9].Data0 = 809;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][9].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][9].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][10].Data0 = 810;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][10].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][10].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][11].Data0 = 811;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][11].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][11].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][12].Data0 = 812;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][12].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][12].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][13].Data0 = 813;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][13].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][13].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][14].Data0 = 814;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][14].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][14].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][15].Data0 = 815;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][15].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][15].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][16].Data0 = 816;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][16].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][16].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][17].Data0 = 817;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][17].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][17].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[1][18].Data0 = 818;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[1][18].Data1 = 10;	//��������(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[1][18].Data2 = 0;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

}




PopupUi::~PopupUi()
{
	SUTIL_FreeTextPack(pCLRPOPUP_Text);
	SUTIL_FreeTextPack(pMAIN_QUEST_Text);//��������Ʈ ��
	SUTIL_FreeTextPack(pSUB_QUEST_Text);//���� ����Ʈ ��
	SUTIL_FreeTextPack(pITEM_Text);//������ ��
//	SUTIL_FreeSprite(m_pWorldMapAs);

}

bool PopupUi::KeyEvent(int m_keyCode, int m_keyRepeat)
{	
	if(m_keyRepeat){ 
		if(!(s_Page.PageNum == POPUP_PAGE_SKILL && SELECT_SKILL_Y==2)){
			return true;
		}
	}
	if(m_keyCode == MH_KEY_4)m_keyCode=MH_KEY_LEFT;		//����ġ
	if(m_keyCode == MH_KEY_6)m_keyCode=MH_KEY_RIGHT;	//����ġ
	if(m_keyCode == MH_KEY_2)m_keyCode=MH_KEY_UP;		//����ġ
	if(m_keyCode == MH_KEY_8)m_keyCode=MH_KEY_DOWN;		//����ġ
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//����ġ
	if(m_keyCode == MH_KEY_ASTERISK){//�ɸ��ͺ�ȯ
		//������ ��Ȳ�� ��ȯ�ȴ�
		if(s_Page.PageNum == POPUP_PAGE_STATES	&& SELECT_STATES_Y	<= 1)s_Page.Woman_Man = (s_Page.Woman_Man+1)%2;
		if(s_Page.PageNum == POPUP_PAGE_EQUIP	&& SELECT_EQUIP_Y	<= 1)s_Page.Woman_Man = (s_Page.Woman_Man+1)%2;
		if(s_Page.PageNum == POPUP_PAGE_SKILL	&& SELECT_SKILL_Y	<= 2)s_Page.Woman_Man = (s_Page.Woman_Man+1)%2;
	}


	if(GameOver){//���� �����϶�
		Key_GAMEOVER(m_keyCode, m_keyRepeat);
		return GameOver;
	}
	
	if(ShopOpen){//����ȣ��
		Key_ITEMSHOP(m_keyCode, m_keyRepeat);
		return ShopOpen;
	}

	if(SmithyOpen){//���尣ȣ��
		Key_SMITHY(m_keyCode, m_keyRepeat);
		return SmithyOpen;
	}

	if(GemOpen){//���尣ȣ��
		Key_GEM(m_keyCode, m_keyRepeat);
		return GemOpen;
	}
	



	if(m_keyCode == MH_KEY_CLEAR && !s_Page.Focus && !s_Page.Ly1_sel && !MixOpen)//������ �˾� ����
		return false;


	if(m_keyCode == MH_KEY_POUND){
		s_Popup_Sharp.View = !s_Popup_Sharp.View;
		s_Popup_Sharp.Line = 0;
	}
	if(s_Popup_Sharp.View){
		if(m_keyCode == MH_KEY_3)s_Popup_Sharp.Line--;	
		if(m_keyCode == MH_KEY_9)s_Popup_Sharp.Line++;	
		if(s_Popup_Sharp.Line<0)s_Popup_Sharp.Line=0;	
		if(s_Popup_Sharp.LineMAX > 0 && s_Popup_Sharp.Line>s_Popup_Sharp.LineMAX) s_Popup_Sharp.Line = s_Popup_Sharp.LineMAX;
	}


	switch(s_Page.PageNum){//���α������
		case POPUP_PAGE_STATES		: Key_STATES(m_keyCode, m_keyRepeat)	; break;
		case POPUP_PAGE_EQUIP		: Key_EQUIP(m_keyCode, m_keyRepeat)		; break;
		case POPUP_PAGE_INVENTORY	: if(MixOpen){ Key_MIX(m_keyCode, m_keyRepeat); }else{ Key_INVENTORY(m_keyCode, m_keyRepeat)	; }break; 
		case POPUP_PAGE_SKILL		: Key_SKILL(m_keyCode, m_keyRepeat)		; break;
		case POPUP_PAGE_HOBBY		: Key_HOBBY(m_keyCode, m_keyRepeat)		; break;
		case POPUP_PAGE_QUEST		: Key_QUEST(m_keyCode, m_keyRepeat)		; break;
		case POPUP_PAGE_SYSTEM		: Key_SYSTEM(m_keyCode, m_keyRepeat)	; break;

		//case POPUP_PAGE_ITEMSHOP	: Paint_ITEMSHOP(m_keyCode, m_keyRepeat); return;
	}
	return true;
}


void PopupUi::Paint()
{
	if(GameOver){//���� �����϶�
		Paint_GAMEOVER();
		return;
	}

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CANCLE, XPOS,YPOS,0);//���
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CANCLE_BASE, XPOS,YPOS,0);//������
	_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����


	if(ShopOpen){//����ȣ��
		Paint_ITEMSHOP();
		_SUTIL->g->SetColor(0xff0000);
		_SUTIL->g->DrawRect(XPOS,YPOS,1,1);
		return;
	}

	if(SmithyOpen){//���尣ȣ��
		Paint_SMITHY();
		_SUTIL->g->SetColor(0xff0000);
		_SUTIL->g->DrawRect(XPOS,YPOS,1,1);
		return;
	}

	if(GemOpen){//���� ����âȣ��
		Paint_GEM();
		_SUTIL->g->SetColor(0xff0000);
		_SUTIL->g->DrawRect(XPOS,YPOS,1,1);
		return;
	}




	switch(s_Page.PageNum){//���α������
		case POPUP_PAGE_STATES		: Paint_STATES()	; break;
		case POPUP_PAGE_EQUIP		: Paint_EQUIP()		; break;
		case POPUP_PAGE_INVENTORY	: if(MixOpen){ Paint_MIX(); }else{ Paint_INVENTORY(); }break;
		case POPUP_PAGE_SKILL		: Paint_SKILL()		; break;
		case POPUP_PAGE_HOBBY		: Paint_HOBBY()		; break;
		case POPUP_PAGE_QUEST		: Paint_QUEST()		; break;
		case POPUP_PAGE_SYSTEM		: Paint_SYSTEM()	; break;
	}

	if (s_Page.Ly1_sel==0)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_TAP, XPOS + 18*(s_Page.PageNum - 1),YPOS-92,0);//�� Ŀ��

	_SUTIL->g->SetColor(0xff0000);
	_SUTIL->g->DrawRect(XPOS,YPOS,1,1);

	/*_SUTIL->pFont->drawScroll(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TESTTEXT], XPOS-51, YPOS-80,80,75,2, CGraphics::HCENTER);
	_SUTIL->pFont->drawLines(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TESTTEXT], XPOS-51, YPOS+40,120,4,3, CGraphics::HCENTER);*/

//	SUTIL_Paint_Frame(m_pWorldMapAs, 0, 200, 200,0); //���
}


void PopupUi::Process()
{
}





void PopupUi::Key_STATES(int m_keyCode, int m_keyRepeat)	
{
	if(s_Page.Focus == 0){
		switch(SELECT_STATES_Y){
			case 0://ž�޴�
				if(m_keyCode == MH_KEY_LEFT){
					s_Page.PageNum = POPUP_PAGE_MAX;
					Page_init();
				}else if(m_keyCode == MH_KEY_RIGHT){
					s_Page.PageNum++;
					Page_init();
				}else if(m_keyCode == MH_KEY_SELECT){
					SELECT_STATES_Y++;
				}
				break;
			case 1://Ÿ��Ʋ
				if(m_keyCode == MH_KEY_SELECT){

				}
				break;
			case 2://��
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability[s_Page.Woman_Man].POINT>0){
						Character::s_Ability[s_Page.Woman_Man].POINT--;
						Character::s_Ability[s_Page.Woman_Man].STR++;
					}
				}
				break;
			case 3://��ø
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability[s_Page.Woman_Man].POINT>0){
						Character::s_Ability[s_Page.Woman_Man].POINT--;
						Character::s_Ability[s_Page.Woman_Man].DEX++;
					}
				}
				break;
			case 4://ü��
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability[s_Page.Woman_Man].POINT>0){
						Character::s_Ability[s_Page.Woman_Man].POINT--;
						Character::s_Ability[s_Page.Woman_Man].CON++;
					}
				}
				break;
			case 5://����
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability[s_Page.Woman_Man].POINT>0){
						Character::s_Ability[s_Page.Woman_Man].POINT--;
						Character::s_Ability[s_Page.Woman_Man].INT++;
					}
				}
				break;
		}

		if(m_keyCode == MH_KEY_UP){
			if(SELECT_STATES_Y>0)SELECT_STATES_Y--;
			if(PAGE_STATES_point[0]-Character::s_Ability[s_Page.Woman_Man].POINT > 0)SELECT_STATES_Y = MAX(SELECT_STATES_Y,2);
		}else if(m_keyCode == MH_KEY_DOWN){
			if(SELECT_STATES_Y<5)SELECT_STATES_Y++;
		}else if(m_keyCode == MH_KEY_CLEAR){//������ �˾� ȣ��
			if(PAGE_STATES_point[0]-Character::s_Ability[s_Page.Woman_Man].POINT > 0 && SELECT_STATES_Y>1){
				s_Page.Focus = 1;
				s_Page.Ly2_sel = 1;//yes
			}else{
				SELECT_STATES_Y=0;
			}
		}


		//������ ���������
		if(SELECT_STATES_Y >1 && PAGE_STATES_point[0]> 0 && Character::s_Ability[s_Page.Woman_Man].POINT ==0){//Ȯ�� �˾� ȣ��
			s_Page.Focus = 1;
			s_Page.Ly2_sel = 1;//yes
		}

		Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���

	}else if(s_Page.Focus == 1){// �˾� - �������ͽ� ���� ���� Ȯ��
		if(m_keyCode == MH_KEY_RIGHT){
			s_Page.Ly2_sel = 1;//No
		}else if(m_keyCode == MH_KEY_LEFT){
			s_Page.Ly2_sel = 0;//Yes
		}else if(m_keyCode == MH_KEY_SELECT){//�ø� ���� ����

			s_Page.Focus = 0;//�˾�����
			SELECT_STATES_Y=0;

			if(s_Page.Ly2_sel){//No - �ǵ�����
				 Character::s_Ability[s_Page.Woman_Man].POINT=PAGE_STATES_point[0];
				 Character::s_Ability[s_Page.Woman_Man].STR  =PAGE_STATES_point[1];
				 Character::s_Ability[s_Page.Woman_Man].DEX  =PAGE_STATES_point[2];
				 Character::s_Ability[s_Page.Woman_Man].CON  =PAGE_STATES_point[3];
				 Character::s_Ability[s_Page.Woman_Man].INT  =PAGE_STATES_point[4];
			}else{//Yes - ���� ���¸� ���
				PAGE_STATES_point[0] = Character::s_Ability[s_Page.Woman_Man].POINT;
				PAGE_STATES_point[1] = Character::s_Ability[s_Page.Woman_Man].STR;
				PAGE_STATES_point[2] = Character::s_Ability[s_Page.Woman_Man].DEX;
				PAGE_STATES_point[3] = Character::s_Ability[s_Page.Woman_Man].CON;
				PAGE_STATES_point[4] = Character::s_Ability[s_Page.Woman_Man].INT;
			}
			

		}else if(m_keyCode == MH_KEY_CLEAR){//�ø� ���� ���

			s_Page.Focus = 0;//�˾�����

			Character::s_Ability[s_Page.Woman_Man].POINT=PAGE_STATES_point[0];
			Character::s_Ability[s_Page.Woman_Man].STR  =PAGE_STATES_point[1];
			Character::s_Ability[s_Page.Woman_Man].DEX  =PAGE_STATES_point[2];
			Character::s_Ability[s_Page.Woman_Man].CON  =PAGE_STATES_point[3];
			Character::s_Ability[s_Page.Woman_Man].INT  =PAGE_STATES_point[4];

		}

	}

}
void PopupUi::Key_EQUIP(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){

		switch(SELECT_EQUIP_Y){
			case 0://ž�޴�
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_EQUIP_Y++;SELECT_EQUIP_JAB_BACUP = Character::s_HeroTag.SEX/*Character::s_Status[Character::s_HeroTag.SEX].ELEMENTAL*/;break;
				}
				break;
			case 1://��� ����
				switch(m_keyCode){ 
					case MH_KEY_RIGHT:SELECT_EQUIP_POS=(SELECT_EQUIP_POS+1)%7;break;
					case MH_KEY_LEFT:SELECT_EQUIP_POS=(SELECT_EQUIP_POS+6)%7;break;
					case MH_KEY_DOWN:
					case MH_KEY_UP:if(SELECT_EQUIP_POS!=3){SELECT_EQUIP_POS+=4;SELECT_EQUIP_POS%=8;}break;
						
					case MH_KEY_CLEAR:
						SELECT_EQUIP_Y = 0;
						//Character::s_Status[Character::s_HeroTag.SEX].ELEMENTAL = SELECT_EQUIP_JAB_BACUP;
						break;
					case MH_KEY_SELECT:
						if(SELECT_EQUIP_LIST_MAX>0)
							SELECT_EQUIP_Y = 2;
						break;

				}
				
				
				break;
			case 2://��� ������ ����
				switch(m_keyCode){
					case MH_KEY_RIGHT:
						SELECT_EQUIP_LIST_NOW++;
						if(SELECT_EQUIP_LIST_MAX)SELECT_EQUIP_LIST_NOW %= SELECT_EQUIP_LIST_MAX;
						break;
					case MH_KEY_LEFT:
						SELECT_EQUIP_LIST_NOW+=(SELECT_EQUIP_LIST_MAX-1);
						if(SELECT_EQUIP_LIST_MAX)SELECT_EQUIP_LIST_NOW %= SELECT_EQUIP_LIST_MAX;
						break;
					case MH_KEY_CLEAR:
						SELECT_EQUIP_Y = 1;
						SELECT_EQUIP_LIST_NOW = 0;
						break;
					case MH_KEY_SELECT:
						if(SELECT_EQUIP_LIST_NOW_BAG >=0 &&SELECT_EQUIP_LIST_NOW_SLOT>=0){//�̹� ������ �������� �ƴ϶��

							EQUIP_item(SELECT_EQUIP_POS,&Character::s_ItemBag[SELECT_EQUIP_LIST_NOW_BAG][SELECT_EQUIP_LIST_NOW_SLOT]);
							//if(SELECT_EQUIP_POS == 6 && Character::s_ItemEquip[6].Data0 == 0)SELECT_EQUIP_POS=5; //�˻繫�� 2nd ���Կ� �������� ������ �����̵�
						}
						SELECT_EQUIP_Y = 1;
						SELECT_EQUIP_LIST_NOW = 0;
						break;
				}
				break;

			
		}
	}
}
void PopupUi::Key_INVENTORY(int m_keyCode, int m_keyRepeat)	
{
	if(s_Page.Focus == 0){
		switch(SELECT_INVENTORY_Y){
			case 0://ž�޴�
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_INVENTORY_Y++;break;
				}
				break;
			case 1://���� ��
				{
					int rightBag = (SELECT_INVENTORY_BAG+1)%4;
					int leftBag = (SELECT_INVENTORY_BAG+3)%4;
					switch(m_keyCode){
						case MH_KEY_CLEAR:
						case MH_KEY_UP:
							if(Character::s_ItemPick.ITEM_KIND==0){//Ŀ���� �������� �پ������ʾƾ� �Ѵ�
								SELECT_INVENTORY_Y=0;
							}
							break;
						case MH_KEY_SELECT:
						case MH_KEY_DOWN:SELECT_INVENTORY_Y++;SELECT_INVENTORY_INSIDE=0;break;
						case MH_KEY_RIGHT:if(Character::s_ItemSlot[rightBag].ITEM_KIND) SELECT_INVENTORY_BAG=rightBag;break;
						case MH_KEY_LEFT:if(Character::s_ItemSlot[leftBag].ITEM_KIND) SELECT_INVENTORY_BAG=leftBag;break;
					}
				}
				break;
			case 2://�κ����� ��
				switch(m_keyCode){
					case MH_KEY_CLEAR:SELECT_INVENTORY_Y = 1;break;
					case MH_KEY_SELECT:

						if(Character::s_ItemPick.ITEM_KIND){//����ִ� �������� �ִٸ�
							MOVE_item();//Ŀ���� �κ��� ������ ��ü
						}else if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data0){//Ŀ���� ����Ű�� �������� ���ٸ� �˾��� �׸����ʴ´�
							
							s_Page.Focus = 1;//�˾�ȣ��
							SELECT_INVENTORY_POPUP_Y=0;

							switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//������ ������ ��ȭ
								case ITEM_POTION://4
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_QUICK;
									break;

								case ITEM_BAG	:
								case ITEM_SWORD	:
								//case ITEM_AXE	:
								case ITEM_GUN	:
								//case ITEM_OEB	:
								case ITEM_HEAD	:
								case ITEM_CHEST	:
								case ITEM_LEG	:
								case ITEM_GLOVE	:
								case ITEM_NECK	:
								case ITEM_RING	://3
									if((Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_SOCKET_1==1 ||
										Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_SOCKET_2==1 ||
										Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_SOCKET_3==1) &&
										Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_EQUIP==0
										){//�� ������ �ִٸ� && �������� �ƴ϶�� 
										SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_EQUIP2;
									}else{//���� �� ������ ���ٸ�
										SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_EQUIP;
									}
									
									break;
								case ITEM_MAINQUEST://����Ҽ����� �Ϲ��ۿ� �޼���
								case ITEM_UP_STONE:
								case ITEM_GEM_STONE:
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_DEFAULT;
									break;
								default://����Ҽ� ������ ����� �ȵǴ��ۿ� �޼���
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_USE;
									break;

							}
						}
						break;
					case MH_KEY_UP:
						if(SELECT_INVENTORY_INSIDE<8){
							SELECT_INVENTORY_Y--;
						}else{
							SELECT_INVENTORY_INSIDE-=8;
						}
						break;
					case MH_KEY_DOWN:SELECT_INVENTORY_INSIDE+=8;break;
					case MH_KEY_LEFT:SELECT_INVENTORY_INSIDE--;break;
					case MH_KEY_RIGHT:SELECT_INVENTORY_INSIDE++;break;
				}
				switch(Character::s_ItemSlot[SELECT_INVENTORY_BAG].Data0){//���� ������ Kind Num�� 1�̴�
					case 100:SELECT_INVENTORY_INSIDE +=  8;SELECT_INVENTORY_INSIDE %=  8;break;
					case 101:SELECT_INVENTORY_INSIDE += 16;SELECT_INVENTORY_INSIDE %= 16;break;
					case 102:SELECT_INVENTORY_INSIDE += 24;SELECT_INVENTORY_INSIDE %= 24;break;
					case 103:SELECT_INVENTORY_INSIDE += 32;SELECT_INVENTORY_INSIDE %= 32;break;
				}

		}
	}else if(s_Page.Focus == 1){// �˾� - �����ۺ� ���� �˾�ȣ��

		
		switch(m_keyCode){
			case MH_KEY_CLEAR:
				if(SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){
					SELECT_INVENTORY_BAG = 0;
				}
				s_Page.Focus = 0;
				break;
			case MH_KEY_SELECT:
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_QUICK:
						if(SELECT_INVENTORY_POPUP_Y==0){//���
							USE_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}else if(SELECT_INVENTORY_POPUP_Y==1){//������
							SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_SLOT;//���԰���
							SELECT_INVENTORY_POPUP_Y=0;
						}else if(SELECT_INVENTORY_POPUP_Y==2){//����
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==3){//�̵�
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
					case INVENTORY_POPUP_SLOT:
						QSLOT_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE],SELECT_INVENTORY_POPUP_Y);
						s_Page.Focus = 0;
					
						break;
					case INVENTORY_POPUP_EQUIP:
					case INVENTORY_POPUP_EQUIP2:
						if(SELECT_INVENTORY_POPUP_Y==0){//����
							int xx;
							switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//������ ������ ��ȭ
								case ITEM_BAG	:
									MOVE_item();
									s_Page.Focus = 1;//�˾�ȣ��
									SELECT_INVENTORY_Y=1;//���� ���� ������ �̵�
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_BAGCHANGE;//���� ���� ����
									return;//������ �߰�UI�� �����Ƿ� ��Ż�Ѵ�
								
								case ITEM_HEAD	:xx = 0;break;
								case ITEM_CHEST	:xx = 1;break;
								case ITEM_LEG	:xx = 2;break;
								case ITEM_GLOVE	:xx = 3;break;
								case ITEM_NECK	:xx = 4;break;
								case ITEM_RING	:xx = 5;break;
								case ITEM_SWORD	:xx = 6;break;
							}

							EQUIP_item(xx,&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}
						if(SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_EQUIP){
							if(SELECT_INVENTORY_POPUP_Y==1){//����
								DEL_item();
							}else if(SELECT_INVENTORY_POPUP_Y==2){//�̵�
								MOVE_item();
								s_Page.Focus = 0;
							}
						}else{
							if(SELECT_INVENTORY_POPUP_Y==1){//����
								USE_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							}else if(SELECT_INVENTORY_POPUP_Y==2){//����
								DEL_item();
							}else if(SELECT_INVENTORY_POPUP_Y==3){//�̵�
								MOVE_item();
								s_Page.Focus = 0;
							}
						}
						break;
					case INVENTORY_POPUP_USE:
						if(SELECT_INVENTORY_POPUP_Y==0){//���
							USE_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}else if(SELECT_INVENTORY_POPUP_Y==1){//����
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==2){//�̵�
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
					case INVENTORY_POPUP_BAGCHANGE://���� ��ü �Ǵ� ����
						MOVE_item();//�κ� ����� ��ü
						break;
					case INVENTORY_POPUP_DEFAULT:
						if(SELECT_INVENTORY_POPUP_Y==0){//����
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==1){//�̵�
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
				}
				
				break;
			case MH_KEY_UP:
				SELECT_INVENTORY_POPUP_Y--;
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_QUICK:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=3;break;
					case INVENTORY_POPUP_SLOT:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=1;break;
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=2;break;
					case INVENTORY_POPUP_EQUIP2:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=3;break;
					case INVENTORY_POPUP_USE:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=2;break;
					case INVENTORY_POPUP_DEFAULT:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=1;break;
				}
				break;
			case MH_KEY_DOWN:
				SELECT_INVENTORY_POPUP_Y++;
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_QUICK:if(SELECT_INVENTORY_POPUP_Y>3)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_SLOT:if(SELECT_INVENTORY_POPUP_Y>1)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y>2)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_EQUIP2:if(SELECT_INVENTORY_POPUP_Y>3)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_USE:if(SELECT_INVENTORY_POPUP_Y>2)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_DEFAULT:if(SELECT_INVENTORY_POPUP_Y>1)SELECT_INVENTORY_POPUP_Y=0;break;
				}
				break;
			case MH_KEY_LEFT:
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_BAGCHANGE:
						int leftBag = (SELECT_INVENTORY_BAG+3)%4;
						
						if(Character::s_ItemSlot[leftBag].ITEM_KIND){ SELECT_INVENTORY_BAG=leftBag;}
						else{
							for (int xx = 0;xx<4;xx++){
								if(Character::s_ItemSlot[xx].ITEM_KIND==0){
									SELECT_INVENTORY_BAG = xx;break;
								}
							}
						}
						break;
				}
				break;
			case MH_KEY_RIGHT:
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_BAGCHANGE:
						int rightBag = (SELECT_INVENTORY_BAG+1)%4;
						if(Character::s_ItemSlot[rightBag].ITEM_KIND) {SELECT_INVENTORY_BAG=rightBag;}
						else{
							for (int xx = 0;xx<4;xx++){
								if(Character::s_ItemSlot[xx].ITEM_KIND==0){
									SELECT_INVENTORY_BAG = xx;break;
								}
							}
						}
						break;
				}
				break;

		}
		
	}else if(s_Page.Focus == 2){// ����˾� - �Ұ����� ��ü, �����⸦ ������ ��� ����
		switch(SELECT_INVENTORY_POPUP_TEXT_KIND){//�˾��� ����
			case INVENTORY_TEXT_POPUP__NOT_ENOUGH:
				switch(m_keyCode){
					case MH_KEY_SELECT:s_Page.Focus = 1;break;
				}
				break;
			case INVENTORY_TEXT_POPUP__ABANDON:
				switch(m_keyCode){
					case MH_KEY_SELECT:
						if(SELECT_INVENTORY_POPUP_TEXT_YESNO){//no
							s_Page.Focus = 0;
						}else{//yes
							DEL_item();
						}
						break;
					case MH_KEY_LEFT:
						SELECT_INVENTORY_POPUP_TEXT_YESNO = 0;break;
					case MH_KEY_RIGHT:
						SELECT_INVENTORY_POPUP_TEXT_YESNO = 1;break;
				}
				break;
			case INVENTORY_TEXT_POPUP__EQUIPDEL:
				switch(m_keyCode){
					case MH_KEY_SELECT:s_Page.Focus = 0;break;
				}
				break;


				
		}
	}
}
void PopupUi::Key_SKILL(int m_keyCode, int m_keyRepeat)		
{

	if(s_Page.Focus == 0){
		switch(SELECT_SKILL_Y){
			case 0://ž�޴�
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:
						SELECT_SKILL_Y++;	
						break;
				}
				break;
			case 1://��Ƽ�� �нú� ����
				switch(m_keyCode){
					case MH_KEY_LEFT:
					case MH_KEY_RIGHT:
						SELECT_SKILL_ACT_PAS = (SELECT_SKILL_ACT_PAS+1)%2;	break;
					case MH_KEY_CLEAR:
					case MH_KEY_UP:SELECT_SKILL_Y--;	break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:
						SELECT_SKILL_Y++;SELECT_SKILL_SLOT=0;SELECT_SKILL_KIND=0;SELECT_SKILL_KIND=0;	
						SELECT_SKILL_C_X = -64;
						SELECT_SKILL_C_Y = -18;
						break;
				}
				break;
			case 2://��ų ����
				{


					
					int Target_X =0;
					int Target_Y =0;


					switch(m_keyCode)
					{
						case MH_KEY_RIGHT:	{SELECT_SKILL_ACC_X=+12;SELECT_SKILL_ACC_Y*=2;SELECT_SKILL_ACC_Y/=3; break;}
						case MH_KEY_LEFT:	{SELECT_SKILL_ACC_X=-12;SELECT_SKILL_ACC_Y*=2;SELECT_SKILL_ACC_Y/=3; break;}
						case MH_KEY_DOWN:	{SELECT_SKILL_ACC_Y=+12;SELECT_SKILL_ACC_X*=2;SELECT_SKILL_ACC_X/=3; break;}
						case MH_KEY_UP:		{SELECT_SKILL_ACC_Y=-12;SELECT_SKILL_ACC_X*=2;SELECT_SKILL_ACC_X/=3; break;}

						case MH_KEY_CLEAR:	
							{
								if(m_keyRepeat)return;
								SELECT_SKILL_Y=1;
								break;
							}
						case MH_KEY_SELECT: 
							{
								if(m_keyRepeat)return;
								SELECT_SKILL_Y=3;
								SELECT_SKILL_KIND = s_Page.Woman_Man*7 + SELECT_SKILL_KIND;
								break;
							}

						case MH_KEY_ASTERISK:if(m_keyRepeat)return; s_Page.Woman_Man = (s_Page.Woman_Man+1)%2;
						case 0://Ű������ ���� ����� ����Ʈ�� ã�´�
							{
								SELECT_SKILL_ACC_X*=2; 
								SELECT_SKILL_ACC_Y*=2;
								SELECT_SKILL_ACC_X/=3; 
								SELECT_SKILL_ACC_Y/=3;
								if(SELECT_SKILL_ACC_X||SELECT_SKILL_ACC_Y)break;








								for(int xx = 0,length_MAX =1000000;xx<7;xx++){
									//���̺�
									int length_NOW;

										length_NOW= 
											((s_X[s_Page.Woman_Man][xx] - SELECT_SKILL_C_X)*(s_X[s_Page.Woman_Man][xx] - SELECT_SKILL_C_X)) + 
											((s_Y[s_Page.Woman_Man][xx] - SELECT_SKILL_C_Y)*(s_Y[s_Page.Woman_Man][xx] - SELECT_SKILL_C_Y));

									if(length_NOW < length_MAX){
										SELECT_SKILL_KIND = xx;
 										length_MAX = length_NOW;
	// 									Target_Name = Town_Buffer[xx][Sp_NAME];
	// 									Target_Num = Town_Buffer[xx][Sp_ID];
										Target_X = s_X[s_Page.Woman_Man][xx];
										Target_Y = s_Y[s_Page.Woman_Man][xx];
	// 									MC_posX = Town_Buffer[xx][Set_PosX];
	// 									MC_derection = Town_Buffer[xx][Set_Dir];
									}

								}
								if((SELECT_SKILL_C_X-Target_X)>(10*2)){ 
									SELECT_SKILL_C_X -= 10; 
								}else if((SELECT_SKILL_C_X-Target_X)<-(10*2)){
									SELECT_SKILL_C_X -= -10; 
								}else{
									int xx = SELECT_SKILL_C_X-Target_X;
									if(ABS(xx) == 1){
										SELECT_SKILL_C_X = Target_X; 
									}else{
										SELECT_SKILL_C_X -= (xx)/2; 
									}
								}
								if((SELECT_SKILL_C_Y-Target_Y)>(10*2)){
									SELECT_SKILL_C_Y -= 10; 
								}else if((SELECT_SKILL_C_Y-Target_Y)<-(10*2)){
									SELECT_SKILL_C_Y -= -10; 
								}else{
									int yy = SELECT_SKILL_C_Y-Target_Y;
									if(ABS(yy) == 1){
										SELECT_SKILL_C_Y = Target_Y; 
									}else{
										SELECT_SKILL_C_Y -= (yy)/2; 
									}
								}


								break;
							}



					}

					SELECT_SKILL_C_X += SELECT_SKILL_ACC_X;
					SELECT_SKILL_C_Y += SELECT_SKILL_ACC_Y;

					if(SELECT_SKILL_C_X >  66)SELECT_SKILL_C_X =   66;
					if(SELECT_SKILL_C_X <- 80)SELECT_SKILL_C_X = - 80;
					if(SELECT_SKILL_C_Y >  27)SELECT_SKILL_C_Y =   27;
					if(SELECT_SKILL_C_Y <- 30)SELECT_SKILL_C_Y = - 30;

					
// 					int skill_Max=0;
// 					if(SELECT_SKILL_ACT_PAS){//�нú�
// 
// 						for(int xx = 0;xx<7;xx++){
// 							switch(SELECT_SKILL_TYPE_NOW){
// 								case 0:if(Character::s_Skill.Level_P[xx])skill_Max++;break;//Į �нú� ��ų����
// 								case 1:if(Character::s_Skill.Level_P[7+xx])skill_Max++;break;//�� �нú� ��ų����
// 								case 2:if(Character::s_Skill.Level_P[14+xx])skill_Max++;break;//�� �нú� ��ų����
// 								case 3:if(Character::s_Skill.Level_P[21+xx])skill_Max++;break;//�� �нú� ��ų����
// 							}
// 						}
// 						
// 					}else{//��Ƽ��
// 
// 						skill_Max = 7;
// // 						for(int xx = 0;xx<7;xx++){
// // 							switch(SELECT_SKILL_TYPE_NOW){
// // 								case 0:if(Character::s_Skill.Level_A[xx])skill_Max++;break;//Į �нú� ��ų����
// // 								case 1:if(Character::s_Skill.Level_A[7+xx])skill_Max++;break;//�� �нú� ��ų����
// // 								//case 2:if(Character::s_Skill.Level_A[14+xx])skill_Max++;break;//�� �нú� ��ų����
// // 							}
// // 						}
// 					}
// 					switch(m_keyCode){
// 						case MH_KEY_SELECT://��ġ�� ����� �ִٸ� -1(����) �� ���ش�
// 							if(SELECT_SKILL_ACT_PAS){//�нú�
// 								for(int xx = 0;xx<9;xx++){
// 									if(SELECT_SKILL_KIND == Character::s_Skill.Equip_P[xx])Character::s_Skill.Equip_P[xx]=-1;
// 								}
// 								Character::Set_state_calculate();//����� �������ͽ� ����(�����Ȱ��� �� ���� ����)
// 							}else{//��Ƽ��
// 								SkillChange_A = true;
// 								for(int xx = 0;xx<3;xx++)//���� ��ų�� ����
// 									if(SELECT_SKILL_KIND == Character::s_Skill.Equip_A[Character::s_HeroTag.SEX][xx])
// 										Character::s_Skill.Equip_A[Character::s_HeroTag.SEX][xx]=-1;
// 							}
// 
// 							SELECT_SKILL_Y=3;
// 							
// 							
// 							break;
// 						case MH_KEY_LEFT:if(SELECT_SKILL_KIND==0)SELECT_SKILL_Y--;
// 							SELECT_SKILL_KIND+=skill_Max-1;
// 							break;
// 						case MH_KEY_RIGHT:SELECT_SKILL_KIND++;		break;
// 						case MH_KEY_UP:if(0 <= (SELECT_SKILL_KIND-4))	SELECT_SKILL_KIND-=4;break;
// 						case MH_KEY_DOWN:if(skill_Max > (SELECT_SKILL_KIND+4))	SELECT_SKILL_KIND+=4;break;
// 						case MH_KEY_CLEAR:SELECT_SKILL_Y--;		break;
// 					}
// 					if(skill_Max)SELECT_SKILL_KIND%=skill_Max;//���ε���̽� �ͼ��� �߻����ɼ�����
				}
				break;

///////////////////////////////////////////////////////////////

			case 3://���� ����
				if(SELECT_SKILL_ACT_PAS){//�нú�

					
					switch(m_keyCode){
						case MH_KEY_LEFT:SELECT_SKILL_SLOT+=8;	break;
						case MH_KEY_RIGHT:SELECT_SKILL_SLOT++;	break;
						case MH_KEY_UP:
							(SELECT_SKILL_SLOT<3?SELECT_SKILL_Y--:SELECT_SKILL_SLOT-=3);
							break;
						case MH_KEY_DOWN:SELECT_SKILL_SLOT+=3;	break;
						case MH_KEY_SELECT:
							if(SELECT_SKILL_KIND>=0){
								SkillChange_A = true;
								int xx = Character::s_Skill.Equip_P[SELECT_SKILL_SLOT];
								Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]=SELECT_SKILL_KIND;
								SELECT_SKILL_KIND = xx;
								Character::Set_state_calculate();//����� �������ͽ� ����
							}else{
								SELECT_SKILL_Y++;	
							}
							break;
						case MH_KEY_CLEAR:
							if(SELECT_SKILL_KIND>=0){
								//SELECT_SKILL_KIND_NOW=0;
								Character::Set_state_calculate();//����� �������ͽ� ����(�����Ȱ��� �� ���� ����)
							}else{
								SELECT_SKILL_Y--;		
							}
							break;
					}
					SELECT_SKILL_SLOT%=9;
				}else{//��Ƽ��
				
					switch(m_keyCode){
						case MH_KEY_LEFT:SELECT_SKILL_SLOT+=2;	break;
						case MH_KEY_RIGHT:SELECT_SKILL_SLOT++;	break;
						case MH_KEY_UP:SELECT_SKILL_Y--;		break;
						case MH_KEY_SELECT:
							{
							//if(SELECT_SKILL_KIND_NOW>=0){
								SkillChange_A = true; 
								int xx = Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + SELECT_SKILL_SLOT];
								Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + SELECT_SKILL_SLOT]=SELECT_SKILL_KIND;
								SELECT_SKILL_KIND = xx;
							//}else{
								// SELECT_SKILL_Y--;	
							//}
							}break;
						case MH_KEY_CLEAR:
// 							if(SELECT_SKILL_KIND_NOW>=0){
// 								//SELECT_SKILL_KIND_NOW=-1;
// 							}else{ 
								SELECT_SKILL_KIND %=7;
								SELECT_SKILL_Y--;		
							//}
							break;
					}
					SELECT_SKILL_SLOT%=3;
				}
				break;
// 			case 4://���� ����
// 
// 				if(SELECT_SKILL_ACT_PAS){//�нú�
// 					int jab_Max = 1+Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE+Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN+Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC;
// 					switch(m_keyCode){
// 						case MH_KEY_SELECT:
// 						case MH_KEY_RIGHT:SELECT_SKILL_Y++;SELECT_SKILL_KIND=0;	break;
// 						case MH_KEY_UP:SELECT_SKILL_TYPE+=jab_Max-1;	break;
// 						case MH_KEY_DOWN:SELECT_SKILL_TYPE++;	break;
// 						case MH_KEY_CLEAR:SELECT_SKILL_Y--;/*SELECT_SKILL_KIND_NOW=-1;*/	break;
// 					}
// 					SELECT_SKILL_TYPE%=jab_Max;
// 				}else{//��Ƽ��
// 					int jab_Max = Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE+Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN+Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC;
// 					switch(m_keyCode){
// 						case MH_KEY_SELECT:
// 						case MH_KEY_RIGHT:SELECT_SKILL_Y++;SELECT_SKILL_KIND=0;	break;
// 						case MH_KEY_UP:SELECT_SKILL_TYPE+=jab_Max-1;	break;
// 						case MH_KEY_DOWN:SELECT_SKILL_TYPE++;	break;
// 						case MH_KEY_CLEAR:SELECT_SKILL_Y--;/*SELECT_SKILL_KIND_NOW=-1;*/	break;
// 					}
// 					SELECT_SKILL_TYPE%=jab_Max;
// 				}
// 				break;
			
		}
	}
	//else if(s_Page.Focus == 1){//�˾�
	//	if(SELECT_SKILL_ACT_PAS){//�нú�

	//	}else{//��Ƽ��

	//	}
	//}
}
void PopupUi::Key_HOBBY(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){
		switch(s_Page.Ly1_sel){
			case 0://ž�޴�
				if(m_keyCode == MH_KEY_LEFT){
					s_Page.PageNum--;
					Page_init();
				}else if(m_keyCode == MH_KEY_RIGHT){
					s_Page.PageNum++;
					Page_init();
				}
				break;
		}
		/*if(m_keyCode == MH_KEY_UP){
		if(s_Page.Ly1_sel>0)s_Page.Ly1_sel--;
		}else if(m_keyCode == MH_KEY_DOWN){
		if(s_Page.Ly1_sel<5)s_Page.Ly1_sel++;
		}*/
	}
}
void PopupUi::Key_QUEST(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){
		if(SELECT_QUEST_Y == 0){//ž�޴�
			switch(m_keyCode){
				case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
				case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
				case MH_KEY_SELECT:
				case MH_KEY_DOWN:SELECT_QUEST_Y++;break;
			}
		}else{
			switch(m_keyCode){
				case MH_KEY_UP:
					if(SELECT_QUEST_Y>2){
						SELECT_QUEST_Y--;
					}else if(SELECT_QUEST_Y>0){
						if(SELECT_QUEST_SUB_Y>0){
							SELECT_QUEST_SUB_Y--;
						}else{
							SELECT_QUEST_Y--;
						}
					}
					break;
				case MH_KEY_DOWN:
					if(SELECT_QUEST_Y < MIN(6,s_Quest.Max_Num+1)){
						SELECT_QUEST_Y++;
					}else if(SELECT_QUEST_Y == MIN(6,s_Quest.Max_Num)){
						if((SELECT_QUEST_Y-1)+SELECT_QUEST_SUB_Y < s_Quest.Max_Num){
							SELECT_QUEST_SUB_Y++;
						}
					}
					break;
				case MH_KEY_SELECT:
					s_Page.Focus=1;
					SELECT_QUEST_DESC_Y=0;
					SELECT_QUEST_DESC_X=0;
					break;
				case MH_KEY_CLEAR:
					SELECT_QUEST_Y = 0;
					break;
			}
		}
	}else if(s_Page.Focus==1){//���� ���� ������
		switch(m_keyCode){
			case MH_KEY_LEFT:SELECT_QUEST_DESC_X=0;break;
			case MH_KEY_RIGHT:SELECT_QUEST_DESC_X=1;break;
			case MH_KEY_UP:
				if(SELECT_QUEST_DESC_Y>0)SELECT_QUEST_DESC_Y--;
				break;
			case MH_KEY_DOWN:
				if(SELECT_QUEST_DESC_Y_MAX-(QUEST_DESC+SELECT_QUEST_DESC_Y)>0)SELECT_QUEST_DESC_Y++;
				break;

			case MH_KEY_SELECT:
			case MH_KEY_CLEAR:
				s_Page.Focus=0;
				break;
		}

	}
}
void PopupUi::Key_SYSTEM(int m_keyCode, int m_keyRepeat)	
{
	if(s_Page.Focus == 0){

		if(SELECT_SYSTEM_CHEAT>=0 && m_keyCode){
			switch(SELECT_SYSTEM_CHEAT){
				case 0:SELECT_SYSTEM_CHEAT=(m_keyCode == MH_KEY_ASTERISK?1:-1);break;
				case 1:SELECT_SYSTEM_CHEAT=(m_keyCode == MH_KEY_9?2:-1);break;
				case 2:SELECT_SYSTEM_CHEAT=(m_keyCode == MH_KEY_7?3:-1);break;
				case 3:SELECT_SYSTEM_CHEAT=(m_keyCode == MH_KEY_3?4:-1);break;
				case 4:SELECT_SYSTEM_CHEAT=(m_keyCode == MH_KEY_POUND?5:-1);break;
				case 5:
					if(m_keyCode==MH_KEY_POUND){
						s_Page.Focus=10;
					}else{
						SELECT_SYSTEM_CHEAT=-1;
					}
					break;
			}
		}


		if(SELECT_SYSTEM_Y== 0){//ž�޴�
			switch(m_keyCode){
				case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
				case MH_KEY_RIGHT:s_Page.PageNum = POPUP_PAGE_STATES;Page_init();break;
				case MH_KEY_SELECT:
				case MH_KEY_DOWN:SELECT_QUEST_Y++;break;
			}
		}else{
			switch(m_keyCode){
				case MH_KEY_CLEAR:SELECT_SYSTEM_Y = 0;;break;
				case MH_KEY_UP:if(SELECT_SYSTEM_Y>0)SELECT_SYSTEM_Y--;break;
				case MH_KEY_DOWN:if(SELECT_SYSTEM_Y<5)SELECT_SYSTEM_Y++;break;
				case MH_KEY_SELECT:break;
			}
		}
	}
	if(s_Page.Focus == 10){
		switch(m_keyCode){
			case MH_KEY_1:
				Character::s_Status[Character::s_HeroTag.SEX].LEVEL++;
				Character::s_Ability[Character::s_HeroTag.SEX].POINT += 3;
				Character::s_Ability[Character::s_HeroTag.SEX].STR+=2;
				Character::s_Ability[Character::s_HeroTag.SEX].DEX+=2;
				Character::s_Ability[Character::s_HeroTag.SEX].CON+=2;
				Character::s_Ability[Character::s_HeroTag.SEX].INT+=2;
				Character::Set_state_calculate();
				Character::s_Status[Character::s_HeroTag.SEX].LIFE = Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX;
				Character::s_Status[Character::s_HeroTag.SEX].MANA = Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX;
				break;
			case MH_KEY_UP:Character::s_Status[Character::s_HeroTag.SEX].LIFE=99999999;break;//������
			case MH_KEY_3:Character::s_Status[Character::s_HeroTag.SEX].MANA=99999999;break;
			case MH_KEY_LEFT:
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[0]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[0]=0;
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[1]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[1]=0;
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[2]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[2]=0;
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[3]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[3]=0;
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[4]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[4]=0;
				Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeMax[5]=0;Character::s_Skill_Set[Character::s_HeroTag.SEX].Cool_TimeNow[5]=0;
				break;//������																						 
			case MH_KEY_CLEAR:s_Page.Focus=0;break;
			case MH_KEY_SELECT:
				Character::s_Ability[Character::s_HeroTag.SEX].STR=9999;
				Character::s_Ability[Character::s_HeroTag.SEX].DEX=9999;
				Character::s_Ability[Character::s_HeroTag.SEX].CON=9999;
				Character::s_Ability[Character::s_HeroTag.SEX].INT=9999;
				Character::Set_state_calculate();
				Character::s_Status[Character::s_HeroTag.SEX].LIFE = Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX;
				Character::s_Status[Character::s_HeroTag.SEX].MANA = Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX;

				for(int xx = 0;xx<21;xx++){
					Character::s_Skill.Level_A[xx]=1;	//��Ƽ�� ��ų����
				}
// 				Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE	=true;	//�˻� - ���� ���� �����ϴٸ� true
// 				Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN	=true;	//�ѻ� - ���� ���� �����ϴٸ� true
// 				Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC	=true;	//���� - ���� ���� �����ϴٸ� true


				break;//������
		}
	}
}




void PopupUi::Key_GAMEOVER(int m_keyCode, int m_keyRepeat)	
{
	switch(SELECT_SKILL_Y){
		case 0:
			if(m_keyCode == MH_KEY_SELECT){//��Ȱ
				GameOver = false;
				Character::s_Status[Character::s_HeroTag.SEX].LIFE = Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX;
				Character::s_Status[Character::s_HeroTag.SEX].MANA = Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX;
				for(int xx =0 ;xx<3;xx++){
					Character::s_Skill_Set[0].Cool_TimeNow[xx]=0;
					Character::s_Skill_Set[1].Cool_TimeNow[xx]=0;
				}
			}
			break;
	}
	if(m_keyCode == MH_KEY_UP){
		if(SELECT_SKILL_Y>0)SELECT_SKILL_Y--;
		if(PAGE_STATES_point[0]-Character::s_Ability[Character::s_HeroTag.SEX].POINT > 0)s_Page.Ly1_sel = MAX(s_Page.Ly1_sel,2);
	}else if(m_keyCode == MH_KEY_DOWN){
		if(SELECT_SKILL_Y<3)SELECT_SKILL_Y++;
	}
}

void PopupUi::Key_ITEMSHOP(int m_keyCode, int m_keyRepeat)	
{
	if(s_Page.Focus == 0){ 
		switch(SELECT_ITEMSHOP_Y){
			case 0://ž�޴�
				switch(m_keyCode){
					case MH_KEY_LEFT: SELECT_ITEMSHOP_X+=6;SELECT_ITEMSHOP_X%=7;MakeShop(SELECT_ITEMSHOP_X,ShopLevel);break;
					case MH_KEY_RIGHT:SELECT_ITEMSHOP_X+=1;SELECT_ITEMSHOP_X%=7;MakeShop(SELECT_ITEMSHOP_X,ShopLevel);break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_ITEMSHOP_Y=2;SELECT_ITEMSHOP_INSIDE=0;break;
					case MH_KEY_CLEAR:ShopOpen = false;break;
				}
				break;
			case 1://���� ��
				{
					int rightBag = (SELECT_ITEMSHOP_BAG+1)%4;
					int leftBag = (SELECT_ITEMSHOP_BAG+3)%4;
					switch(m_keyCode){
						case MH_KEY_CLEAR:
						case MH_KEY_UP:
							if(Character::s_ItemPick.ITEM_KIND==0){//Ŀ���� �������� �پ������ʾƾ� �Ѵ�
								SELECT_ITEMSHOP_Y=0;
							}
							break;
						case MH_KEY_SELECT:
						case MH_KEY_DOWN:SELECT_ITEMSHOP_Y++;SELECT_ITEMSHOP_INSIDE=0;break;
						case MH_KEY_RIGHT:if(Character::s_ItemSlot[rightBag].ITEM_KIND) SELECT_ITEMSHOP_BAG=rightBag;break;
						case MH_KEY_LEFT:if(Character::s_ItemSlot[leftBag].ITEM_KIND) SELECT_ITEMSHOP_BAG=leftBag;break;
					}
				}
				break;
			case 2://�κ����� ��

				if(SELECT_ITEMSHOP_FOCUS_R_L){//�κ��� 
					switch(m_keyCode){
						case MH_KEY_CLEAR:SELECT_ITEMSHOP_Y = 1;break;
						case MH_KEY_SELECT:

							if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data0){//Ŀ���� ����Ű�� �������� ���ٸ� �˾��� �׸����ʴ´�

								s_Page.Focus = 1;//�˾�ȣ��

								switch(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//������ ������ ��ȭ
									case ITEM_BAG	:
									case ITEM_SWORD	:
									case ITEM_GUN	:
									case ITEM_HEAD	:
									case ITEM_CHEST	:
									case ITEM_LEG	:
									case ITEM_GLOVE	:
									case ITEM_NECK	:
									case ITEM_RING	://������ �������ʰ� �ȸ��� ������
										SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_SELL;
										SELECT_ITEMSHOP_COUNT = 0;
										break;
									case ITEM_MAINQUEST://�ǸźҰ� - ����Ҽ����� �Ϲ��ۿ� �޼���
										SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_NOT_SELL;
										break;
									default://������ ���� Ȯ���ؾ��ϴ� ������
										SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_SELL_COUNT;
										SELECT_ITEMSHOP_COUNT = 1;
										break;
								}
							}
							break;
						case MH_KEY_UP:
							if(SELECT_ITEMSHOP_INSIDE<4){
								SELECT_ITEMSHOP_Y--;
							}else{
								SELECT_ITEMSHOP_INSIDE-=4;
							}
							break;
						case MH_KEY_DOWN:SELECT_ITEMSHOP_INSIDE+=4;break;
						case MH_KEY_LEFT:
							if(0 == SELECT_ITEMSHOP_INSIDE%4){//�� ������ �̵�
								SELECT_ITEMSHOP_FOCUS_R_L = 0;
								SELECT_ITEMSHOP_INSIDE += (3- SELECT_ITEMSHOP_R_SCROLL*4 + SELECT_ITEMSHOP_L_SCROLL*4);
							}else{
								SELECT_ITEMSHOP_INSIDE--;
							}
							break;
						case MH_KEY_RIGHT:
							if(3 == SELECT_ITEMSHOP_INSIDE%4){//�� ������ �̵�
								SELECT_ITEMSHOP_FOCUS_R_L = 0;
								SELECT_ITEMSHOP_INSIDE += (1- SELECT_ITEMSHOP_R_SCROLL*4 + SELECT_ITEMSHOP_L_SCROLL*4);
							}else{
								SELECT_ITEMSHOP_INSIDE++;
							}
							break;
					}
				}else{//������
					switch(m_keyCode){
						case MH_KEY_CLEAR:SELECT_ITEMSHOP_Y = 0;break;
							case MH_KEY_SELECT:

							if(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].Data0){//Ŀ���� ����Ű�� �������� ���ٸ� �˾��� �׸����ʴ´�

								s_Page.Focus = 1;//�˾�ȣ��

								switch(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//������ ������ ��ȭ
									case ITEM_BAG	:
									case ITEM_SWORD	:
									case ITEM_GUN	:
									case ITEM_HEAD	:
									case ITEM_CHEST	:
									case ITEM_LEG	:
									case ITEM_GLOVE	:
									case ITEM_NECK	:
									case ITEM_RING	://������ �������ʰ� �ȸ��� ������
										SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_BUY;
										SELECT_ITEMSHOP_COUNT = 0;
										break;
									default://������ ���� Ȯ���ؾ��ϴ� ������
										SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_BUY_COUNT;
										SELECT_ITEMSHOP_COUNT = 1;
										break;
								}
							}
							break;
						case MH_KEY_UP:
							if(SELECT_ITEMSHOP_INSIDE<4){
								SELECT_ITEMSHOP_Y=0;
							}else{
								SELECT_ITEMSHOP_INSIDE-=4;
							}
							break;
						case MH_KEY_DOWN:SELECT_ITEMSHOP_INSIDE+=4;break;
						case MH_KEY_LEFT:
							if(0 == SELECT_ITEMSHOP_INSIDE%4){//�� ������ �̵�
								SELECT_ITEMSHOP_FOCUS_R_L = 1;
								SELECT_ITEMSHOP_INSIDE += (-1+ SELECT_ITEMSHOP_R_SCROLL*4 - SELECT_ITEMSHOP_L_SCROLL*4);
							}else{
								SELECT_ITEMSHOP_INSIDE--;
							}
							break;
						case MH_KEY_RIGHT:
							if(3 == SELECT_ITEMSHOP_INSIDE%4){//�� ������ �̵�
								SELECT_ITEMSHOP_FOCUS_R_L = 1;
								SELECT_ITEMSHOP_INSIDE += (-3+ SELECT_ITEMSHOP_R_SCROLL*4 - SELECT_ITEMSHOP_L_SCROLL*4);
							}else{
								SELECT_ITEMSHOP_INSIDE++;
							}
							break;
					}
				}

				if(SELECT_ITEMSHOP_FOCUS_R_L){//�κ��� 
					switch(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG].Data0){//���� ������ Kind Num�� 1�̴�
						case 100:SELECT_ITEMSHOP_INSIDE +=  8;SELECT_ITEMSHOP_INSIDE %=  8;break;
						case 101:SELECT_ITEMSHOP_INSIDE += 16;SELECT_ITEMSHOP_INSIDE %= 16;break;
						case 102:SELECT_ITEMSHOP_INSIDE += 24;SELECT_ITEMSHOP_INSIDE %= 24;break;
						case 103:SELECT_ITEMSHOP_INSIDE += 32;SELECT_ITEMSHOP_INSIDE %= 32;break;
					}
				}else{
					SELECT_ITEMSHOP_INSIDE += 24;SELECT_ITEMSHOP_INSIDE %= 24;break;
				}

				

		}
	}else if(s_Page.Focus == 1){// �˾� - �����ۺ� ���� �˾�ȣ��

		switch(m_keyCode){
			case MH_KEY_CLEAR:s_Page.Focus = 0;break;
		}

		switch(SELECT_ITEMSHOP_POPUP_KIND){//�������� Ŭ���� ��ġ, �������� ���������� �ٸ� �˾��̶��
			case ITEMSHOP_POPUP_BUY			://�춧
				switch(m_keyCode){
					case MH_KEY_LEFT:
						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 0;
						break;
					case MH_KEY_RIGHT:
						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 1;
						break;
					case MH_KEY_SELECT:
						if(SELECT_ITEMSHOP_POPUP_TEXT_YESNO){//�Ǹ���� 
							s_Page.Focus = 0;
						}else{
							int ItemCost = (SELECT_ITEMSHOP_COUNT? CalkCost(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE])*SELECT_ITEMSHOP_COUNT : CalkCost(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE]) );

							if(Character::s_Status[Character::s_HeroTag.SEX].MONEY <  ItemCost){
								SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_NO_MONEY;//�����ݾ��� ����Ѱ�?
								return;
							}
							
							SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_NOT_SPACE;//������ ����Ѱ�?

							//������� �ִ°�?
							for(int yy = 0;yy<get_BagMax(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG]);yy++){
								if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][yy].ITEM_KIND == 0){//����ִ½����� ������

									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][yy].Data0 = Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].Data0;
									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][yy].Data1 = Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].Data1;
									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][yy].Data2 = Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].Data2;

									Character::s_Status[Character::s_HeroTag.SEX].MONEY -= ItemCost;//�ݾ� ����
									s_Page.Focus = 0;//�˾�����
									return;
								}
							}
							


						}
						break;
				}
				break;
			case ITEMSHOP_POPUP_SELL		://�ȶ�
				switch(m_keyCode){
					case MH_KEY_LEFT:
						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 0;
						break;
					case MH_KEY_RIGHT:
						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 1;
						break;
					case MH_KEY_SELECT:
						if(SELECT_ITEMSHOP_POPUP_TEXT_YESNO){//�Ǹ����
							s_Page.Focus = 0;
						}else{
							if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_EQUIP){
								SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_NOT_SELL;//������� �������� �ƴѰ�?
								return;
							}

							if(CalkCost(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]) == 0){
								SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_NOT_SELL;//�� �� ���� ��ǰ�� �ƴѰ�?
								return;
							}

							

							//ī��Ʈ�� 0�̸� ������ 1�̻��̸� �ش� ������ŭ�� ������ �Ѵ�
							if(SELECT_ITEMSHOP_COUNT){//���� ��

								Character::s_Status[Character::s_HeroTag.SEX].MONEY += CalkCost(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE])*SELECT_ITEMSHOP_COUNT;//�ݾ� �߰�
								s_Page.Focus = 0;//�˾�����

								Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data1 -= SELECT_ITEMSHOP_COUNT;
								if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_STACK_COUNT == 0){//������ ����
									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data0 = 0;
									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data1 = 0;
									Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data2 = 0;
								}
							}else{//��� �������� �ܼ� ��

								Character::s_Status[Character::s_HeroTag.SEX].MONEY += CalkCost(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);//�ݾ� �߰�
								s_Page.Focus = 0;//�˾�����

								Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data0 = 0;
								Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data1 = 0;
								Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data2 = 0;
							}
						}
						
						break;
				}
				break;
			case ITEMSHOP_POPUP_BUY_COUNT	://�찹��
				switch(m_keyCode){
					case MH_KEY_LEFT:
						SELECT_ITEMSHOP_COUNT--;
						break;
					case MH_KEY_RIGHT:
						SELECT_ITEMSHOP_COUNT++;
						break;
					case MH_KEY_UP:
						SELECT_ITEMSHOP_COUNT+=10;
						break;
					case MH_KEY_DOWN:
						SELECT_ITEMSHOP_COUNT-=10;
						break;
					case MH_KEY_SELECT:SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_BUY;break;
				}
				SELECT_ITEMSHOP_COUNT = (SELECT_ITEMSHOP_COUNT>99 ? 99: (SELECT_ITEMSHOP_COUNT<1 ? 1: SELECT_ITEMSHOP_COUNT));
				break;
			case ITEMSHOP_POPUP_SELL_COUNT	:{//�Ȱ���
				switch(m_keyCode){
					case MH_KEY_LEFT:
						SELECT_ITEMSHOP_COUNT--;
						break;
					case MH_KEY_RIGHT:
						SELECT_ITEMSHOP_COUNT++;
						break;
					case MH_KEY_UP:
						SELECT_ITEMSHOP_COUNT+=10;
						break;
					case MH_KEY_DOWN:
						SELECT_ITEMSHOP_COUNT-=10;
						break;
					case MH_KEY_SELECT:SELECT_ITEMSHOP_POPUP_KIND = ITEMSHOP_POPUP_SELL;break;
				}
				int max_Num = Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_STACK_COUNT;
				SELECT_ITEMSHOP_COUNT = (SELECT_ITEMSHOP_COUNT>max_Num ? max_Num: (SELECT_ITEMSHOP_COUNT<1 ? 1: SELECT_ITEMSHOP_COUNT));

				}break;
			case ITEMSHOP_POPUP_NOT_SPACE://���� ��������
				switch(m_keyCode){
					case MH_KEY_SELECT:s_Page.Focus = 0;break;
				}
				break;
			case ITEMSHOP_POPUP_NO_MONEY://��� ����
				switch(m_keyCode){
					case MH_KEY_SELECT:s_Page.Focus = 0;break;
				}
				break;
			case ITEMSHOP_POPUP_NOT_SELL://�ǸźҰ� ��
				switch(m_keyCode){
					case MH_KEY_SELECT:s_Page.Focus = 0;break;
				}
				break;
		}


// 			case INVENTORY_TEXT_POPUP__NOT_ENOUGH:
// 				switch(m_keyCode){
// 					case MH_KEY_SELECT:s_Page.Focus = 1;break;
// 				}
// 				break;
// 			case INVENTORY_TEXT_POPUP__ABANDON:
// 				switch(m_keyCode){
// 					case MH_KEY_SELECT:
// 						if(SELECT_ITEMSHOP_POPUP_TEXT_YESNO){//no
// 							s_Page.Focus = 0;
// 						}else{//yes
// 							DEL_item();
// 						}
// 						break;
// 					case MH_KEY_LEFT:
// 						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 0;break;
// 					case MH_KEY_RIGHT:
// 						SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 1;break;
// 				}
// 				break;
// 			case INVENTORY_TEXT_POPUP__EQUIPDEL:
// 				switch(m_keyCode){
// 			case MH_KEY_SELECT:s_Page.Focus = 0;break;
// 				}
// 				break;
//		}


	}
}
void PopupUi::Key_SMITHY(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){

		switch(SELECT_SMITHY_Y){
			case 0://��� ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	SmithyOpen = false;break;
					case MH_KEY_RIGHT:	SELECT_SMITHY_Y = 1;break;
					case MH_KEY_DOWN:	SELECT_SMITHY_Y = 2;break;
					case MH_KEY_SELECT:	
						SELECT_SMITHY_ITEM_SLOT = false;
						SELECT_SMITHY_LIST_NOW = 0;
						s_Page.Focus = 1;
						break;
				}
				break;

			case 1://��ȭ�� ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	
					case MH_KEY_LEFT:	SELECT_SMITHY_Y = 0;break;
					case MH_KEY_DOWN:	SELECT_SMITHY_Y = 2;break;
					case MH_KEY_SELECT:
						SELECT_SMITHY_STONE_SLOT = false;
						SELECT_SMITHY_LIST_NOW = 0;
						s_Page.Focus = 1;
				}
				break;

			case 2://��� ������ ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	
					case MH_KEY_UP:	SELECT_SMITHY_Y = 1;break;
						break;
					case MH_KEY_SELECT://��ȭ����
						if(SELECT_SMITHY_STONE_SLOT && SELECT_SMITHY_ITEM_SLOT && (Character::s_Status[Character::s_HeroTag.SEX].MONEY >= SMITHY_UP_COST)){
							s_Page.Focus = 2;//�˾� Ȱ��
							SELECT_SMITHY_POPUP_TEXT_YESNO = 0;
							SELECT_SMITHY_POPUP_KIND = SMITHY_POPUP_QUESTION;
						}
						break;
				}
				break;


		}
	}else if(s_Page.Focus == 1){
		switch(SELECT_SMITHY_Y){
			case 0://��� ����
				switch(m_keyCode){ 
					case MH_KEY_RIGHT:
						SELECT_SMITHY_LIST_NOW++;
						if(SELECT_SMITHY_LIST_MAX)SELECT_SMITHY_LIST_NOW %= SELECT_SMITHY_LIST_MAX;
						break;
					case MH_KEY_LEFT:
						SELECT_SMITHY_LIST_NOW+=(SELECT_SMITHY_LIST_MAX-1);
						if(SELECT_SMITHY_LIST_MAX)SELECT_SMITHY_LIST_NOW %= SELECT_SMITHY_LIST_MAX;
						break;
					case MH_KEY_CLEAR:
						s_Page.Focus = 0;
						break;
					case MH_KEY_SELECT:s_Page.Focus = 0;SELECT_SMITHY_ITEM_SLOT = true;break;
						break;

				}
				break;

			case 1://��ȭ�� ����
				switch(m_keyCode){
					case MH_KEY_RIGHT:
						SELECT_SMITHY_LIST_NOW++;
						if(SELECT_SMITHY_LIST_MAX)SELECT_SMITHY_LIST_NOW %= SELECT_SMITHY_LIST_MAX;
						break;
					case MH_KEY_LEFT:
						SELECT_SMITHY_LIST_NOW+=(SELECT_SMITHY_LIST_MAX-1);
						if(SELECT_SMITHY_LIST_MAX)SELECT_SMITHY_LIST_NOW %= SELECT_SMITHY_LIST_MAX;
						break;
					case MH_KEY_CLEAR:
						s_Page.Focus = 0;
						break;
					case MH_KEY_SELECT: 
						s_Page.Focus = 2; 
						SELECT_SMITHY_POPUP_TEXT_YESNO = 1;
						SELECT_SMITHY_POPUP_KIND = SMITHY_POPUP_NUM;
						break;
				}
		}

	}else if(s_Page.Focus == 2){// �˾� - ���¿� ���� �˾� ȣ��
		switch(SELECT_SMITHY_POPUP_KIND){
			case SMITHY_POPUP_NUM		:
				switch(m_keyCode){
					case MH_KEY_RIGHT:
						int MAX;
						if(702 == Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT].ITEM_ID){
							MAX = 1;
						}else{
							MAX = MIN(10,Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT].ITEM_STACK_COUNT);
						}
						if(SELECT_SMITHY_POPUP_TEXT_YESNO < MAX)
							{SELECT_SMITHY_POPUP_TEXT_YESNO++;}
						break;
					case MH_KEY_LEFT:
						if(SELECT_SMITHY_POPUP_TEXT_YESNO > 1)
							{SELECT_SMITHY_POPUP_TEXT_YESNO--;}
						break;
					case MH_KEY_CLEAR:
						s_Page.Focus = 1;
						break;
					case MH_KEY_SELECT:
						SELECT_SMITHY_USE_STONE_NUM = SELECT_SMITHY_POPUP_TEXT_YESNO;
						SELECT_SMITHY_STONE_SLOT = true;
						s_Page.Focus = 0;
						break;
				}

				break;
			case SMITHY_POPUP_QUESTION	:
				switch(m_keyCode){
					case MH_KEY_LEFT:
						SELECT_SMITHY_POPUP_TEXT_YESNO=0;
						break;
					case MH_KEY_RIGHT:
						SELECT_SMITHY_POPUP_TEXT_YESNO=1;
						break;
					case MH_KEY_SELECT://������ �������� ������ ������� Ȯ���Ѵ�.
						if(SELECT_SMITHY_POPUP_TEXT_YESNO == 0){
							SELECT_SMITHY_POPUP_KIND = SMITHY_POPUP_ING;
							SELECT_SMITHY_POPUP_TEXT_YESNO = 0;
						}else{
							s_Page.Focus=0;
						}
						break;
					case MH_KEY_CLEAR:
						s_Page.Focus=0;
						break;
				}
				break;
			case SMITHY_POPUP_ING		:
					SELECT_SMITHY_POPUP_TEXT_YESNO++;
					if(SELECT_SMITHY_POPUP_TEXT_YESNO>20){ 
						s_Page.Focus = 2; 
						Character::s_Status[Character::s_HeroTag.SEX].MONEY -= SMITHY_UP_COST;
						REMOVE_Item(Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT].ITEM_ID,SELECT_SMITHY_USE_STONE_NUM,SELECT_MIX_SEX);	//��ȭ�� ����
						//������ ��ȭ
						int add_Per,success_Per,stop_Per,minuss_Per;
						switch(Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT].ITEM_UPGRADE){
							case 0:success_Per = 90;stop_Per =100;minuss_Per =  0;break;
							case 1:success_Per = 80;stop_Per =100;minuss_Per =  0;break;
							case 2:success_Per = 70;stop_Per = 90;minuss_Per =  7;break;
							case 3:success_Per = 50;stop_Per = 80;minuss_Per = 15;break;
							case 4:success_Per = 40;stop_Per = 50;minuss_Per = 25;break;
							case 5:success_Per = 20;stop_Per = 25;minuss_Per = 25;break;
							case 6:success_Per = 10;stop_Per = 20;minuss_Per = 20;break;
							case 7:success_Per =  5;stop_Per = 18;minuss_Per = 18;break;
							case 8:success_Per = -3;stop_Per = 16;minuss_Per = 16;break;
							case 9:success_Per = -7;stop_Per = 14;minuss_Per = 14;break;
						}
						switch(Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT].ITEM_INDEX){
							case 0:add_Per = SELECT_SMITHY_USE_STONE_NUM;break;
							case 1:add_Per = SELECT_SMITHY_USE_STONE_NUM*2;break;
							case 2:add_Per = 40;break;
						}

						SELECT_SMITHY_POPUP_KIND = SMITHY_POPUP_RESULT;
						if((success_Per+add_Per) > RND(0,100)){//����Ȯ��
							SELECT_SMITHY_POPUP_TEXT_YESNO = 0;
							Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT].Data2++;
						}else{
							int per = RND(0,100);
							if(stop_Per > per){//�̻���� Ȯ��
								SELECT_SMITHY_POPUP_TEXT_YESNO = 1;
							}else if(minuss_Per > per-stop_Per){//�ϰ� Ȯ��
								SELECT_SMITHY_POPUP_TEXT_YESNO = 2;
								Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT].Data2--;
							}else{//���� Ȯ��
								SELECT_SMITHY_POPUP_TEXT_YESNO = 3;
								Del_Item(&Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT]);
							}
						}

					}
					
				break;
			case SMITHY_POPUP_RESULT	:	
				switch(m_keyCode){
					case MH_KEY_SELECT://������ �������� ������ ������� Ȯ���Ѵ�.
						s_Page.Focus = 0;
						SELECT_SMITHY_ITEM_SLOT = SELECT_SMITHY_STONE_SLOT = false;
						break;
				}
				break;
		}

	}
}
void PopupUi::Key_GEM(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){

		switch(SELECT_GEM_Y){
			case 0://��� ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	GemOpen = false;break;
					case MH_KEY_RIGHT:	SELECT_GEM_Y = 1;break;
					case MH_KEY_SELECT:	
						if(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_3==1){//�󽽷�
							SELECT_GEM_LIST_NOW = 0;
							s_Page.Focus = 1;
						}
						break;
				}
				break;

			case 1://��ȭ�� ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	GemOpen = false;break;
					case MH_KEY_LEFT:	SELECT_GEM_Y = 0;break;
					case MH_KEY_RIGHT:	SELECT_GEM_Y = 2;break;
					case MH_KEY_SELECT:
						if(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_2==1){//�󽽷�
							SELECT_GEM_LIST_NOW = 0;
							s_Page.Focus = 1;
						}
				}
				break;

			case 2://��� ������ ����
				switch(m_keyCode){
					case MH_KEY_CLEAR:	GemOpen = false;break;
					case MH_KEY_LEFT:	SELECT_GEM_Y = 1;break;
					case MH_KEY_SELECT:
						if(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_1==1){//�󽽷�
							SELECT_GEM_LIST_NOW = 0;
							s_Page.Focus = 1;
						}
				}
				break;


		}
	}else if(s_Page.Focus == 1){
		//switch(SELECT_GEM_Y){
		switch(m_keyCode){ 
			case MH_KEY_RIGHT:
				SELECT_GEM_LIST_NOW++;
				if(SELECT_GEM_LIST_MAX)SELECT_GEM_LIST_NOW %= SELECT_GEM_LIST_MAX;
				break;
			case MH_KEY_LEFT:
				SELECT_GEM_LIST_NOW+=(SELECT_GEM_LIST_MAX-1);
				if(SELECT_GEM_LIST_MAX)SELECT_GEM_LIST_NOW %= SELECT_GEM_LIST_MAX;
				break;
			case MH_KEY_CLEAR:
				s_Page.Focus = 0;
				break;
			case MH_KEY_SELECT://�뽺�� ���� 
				s_Page.Focus = 0;

				int data1 = Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].Data1;
				int gam_Num =1 + Character::s_ItemBag[SELECT_GEM_USE_STONE_BAG][SELECT_GEM_USE_STONE_SLOT].ITEM_INDEX;

				switch (SELECT_GEM_Y) {
					case 0:data1 += gam_Num*10000000;break;
					case 1:data1 += gam_Num*100000;break;
					case 2:data1 += gam_Num*1000;break;
				} 
				Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].Data1 = data1;

				REMOVE_Item(Character::s_ItemBag[SELECT_GEM_USE_STONE_BAG][SELECT_GEM_USE_STONE_SLOT].ITEM_ID,1);	//���� ����
				//������ ��ȭ

				break;

		}

	}else if(s_Page.Focus == 2){// �˾� - ���¿� ���� �˾� ȣ��
		switch(SELECT_GEM_POPUP_KIND){
			case GEM_POPUP_RESULT	:	
				switch(m_keyCode){
					case MH_KEY_SELECT://������ �������� ������ ������� Ȯ���Ѵ�.
						s_Page.Focus = 0;
						break;
				}
				break;
		}

	}
}
void PopupUi::Key_MIX(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){ 
		switch(m_keyCode){//���� ��� ����
			case MH_KEY_UP:
				if(SELECT_MIX_SELECT > 0){
					SELECT_MIX_SELECT--;
				}
				break;
			case MH_KEY_DOWN:
				if(SELECT_MIX_SELECT < SELECT_MIX_MAX_NUM-1){
					SELECT_MIX_SELECT++;
				}
				break;
			case MH_KEY_SELECT:
				//�ƽ�����ŷ ���� üũ
				if(MixBuffer[1] && MixBuffer[2]){
					SELECT_MIX_MAKE_MAX = GET_Count(MixBuffer[1],SELECT_MIX_SEX) / MixBuffer[2];
					if(MixBuffer[3] && MixBuffer[4]){
						int max2 = GET_Count(MixBuffer[3],SELECT_MIX_SEX) / MixBuffer[4]; 
						SELECT_MIX_MAKE_MAX = MIN(SELECT_MIX_MAKE_MAX,max2);
						if(MixBuffer[5] && MixBuffer[6]){
							int max3 = GET_Count(MixBuffer[5],SELECT_MIX_SEX) / MixBuffer[6]; 
							SELECT_MIX_MAKE_MAX = MIN(SELECT_MIX_MAKE_MAX,max3);
						}
					}
				}

				SELECT_MIX_MAKE_NUM = SELECT_MIX_MAKE_MAX;


				s_Page.Focus=1;
				break;
			case MH_KEY_CLEAR:
				MixOpen = false;
				Page_init();
				break;
		}
	}else if(s_Page.Focus==1){//���� ���� ������
		if(SELECT_MIX_POPUP_KIND){//�˾��� ������
			switch(SELECT_MIX_POPUP_KIND){
				case MIX_POPUP_QUESTION				://���տ��� ����
					switch(m_keyCode){
						case MH_KEY_LEFT:
							SELECT_MIX_POPUP_YESNO=0;
							break;
						case MH_KEY_RIGHT:
							SELECT_MIX_POPUP_YESNO=1;
							break;
						case MH_KEY_SELECT://������ �������� ������ ������� Ȯ���Ѵ�.
							if(SELECT_MIX_POPUP_YESNO){
								SELECT_MIX_POPUP_KIND=0;
							}else{
								SELECT_MIX_POPUP_KIND=0;
								for(int xx = 0;xx<SELECT_MIX_MAKE_NUM;xx++){//������ ���� ������ŭ �ݺ��Ѵ�
									if(GET_Count(0)){//����� ������ 1���̻� �ִٸ�
										SELECT_MIX_MAKE_MAX--;

										if(MixBuffer[1] && MixBuffer[2]){
											REMOVE_Item(MixBuffer[1],MixBuffer[2],SELECT_MIX_SEX);	
											if(MixBuffer[3] && MixBuffer[4]){
												REMOVE_Item(MixBuffer[3],MixBuffer[4],SELECT_MIX_SEX);	
												if(MixBuffer[5] && MixBuffer[6]){
													REMOVE_Item(MixBuffer[5],MixBuffer[6],SELECT_MIX_SEX);	
												}
											}
										}

										ItemBag tmpBag;
										if(MixBuffer[0]>=1000 && MixBuffer[0]<2000 ){//������̶��

											tmpBag.Data0 = MixBuffer[0];
											tmpBag.Data1 = 0;
											tmpBag.Data2 = 0;
										}else{//������� �ƴ϶��

											tmpBag.Data0 = MixBuffer[0];
											tmpBag.Data1 = 1;
											tmpBag.Data2 = 0;
										}

										GET_item(&tmpBag);

									}else{//�󽽷��� ������ �����ߴ�
										SELECT_MIX_POPUP_KIND=MIX_POPUP_NO_SPACE;
										break;
									}
								}
							}
							break;
						case MH_KEY_CLEAR:
							SELECT_MIX_POPUP_KIND=0;
							break;
					}
					break;

				case MIX_POPUP_NO_MATERIAL			://��� ����
				case MIX_POPUP_NO_SPACE				://���� ��������
					switch(m_keyCode){
						case MH_KEY_SELECT://������ �������� ������ ������� Ȯ���Ѵ�.
						case MH_KEY_CLEAR:
							SELECT_MIX_POPUP_KIND=0;
							break;
					}
					break;
			}
		}else{
			switch(m_keyCode){ 
				case MH_KEY_LEFT:
					SELECT_MIX_MAKE_NUM--;
					break;
				case MH_KEY_RIGHT:
					SELECT_MIX_MAKE_NUM++;
					break;
				case MH_KEY_UP:
					SELECT_MIX_MAKE_NUM+=10;
					break;
				case MH_KEY_DOWN:
					SELECT_MIX_MAKE_NUM-=10;
					break;
				case MH_KEY_SELECT:
					if(SELECT_MIX_MAKE_MAX==0){//������ �Ұ����ϴٸ� 
						SELECT_MIX_POPUP_KIND = MIX_POPUP_NO_MATERIAL;
					}else{//���� ���� Ȯ��
						SELECT_MIX_POPUP_KIND = MIX_POPUP_QUESTION;
						SELECT_MIX_POPUP_YESNO = 0;
					}
					break;

				case MH_KEY_CLEAR:
					s_Page.Focus=0;
					break;
			}

			if(SELECT_MIX_MAKE_MAX){
				SELECT_MIX_MAKE_NUM = (SELECT_MIX_MAKE_NUM>SELECT_MIX_MAKE_MAX ? SELECT_MIX_MAKE_MAX: (SELECT_MIX_MAKE_NUM<1 ? 1: SELECT_MIX_MAKE_NUM));
			}else{
				SELECT_MIX_MAKE_NUM = 0;
			}
		}


	}



}

void PopupUi::Paint_STATES()	
{
	
	
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_1, XPOS, YPOS, 0);//CLRMENU 
	

//���� ���
	if (SELECT_STATES_Y==0){
		PAGE_STATES_point[0] = Character::s_Ability[s_Page.Woman_Man].POINT;
		PAGE_STATES_point[1] = Character::s_Ability[s_Page.Woman_Man].STR;
		PAGE_STATES_point[2] = Character::s_Ability[s_Page.Woman_Man].DEX;
		PAGE_STATES_point[3] = Character::s_Ability[s_Page.Woman_Man].CON;
		PAGE_STATES_point[4] = Character::s_Ability[s_Page.Woman_Man].INT;
	}

//Ŀ��
	if (SELECT_STATES_Y==1)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_4, XPOS+13, YPOS-53, 0);//ȣĪ Ŀ��
	if (SELECT_STATES_Y>=2)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_1, XPOS-74, YPOS+30 + (13*(SELECT_STATES_Y-2)), 0);//���� Ŀ��

//�ɸ��� ���ż� �����ֱ�
	_SUTIL->g->SetClip(XPOS-79,YPOS-74,56,77);	
	switch(s_Page.Woman_Man){
		case 0:
			SUTIL_Paint_Ani(Character::_spr_Hero_W ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-55, YPOS-5, 0);//�ɸ���
			break;
		case 1:
			SUTIL_Paint_Ani(Character::_spr_Hero_M ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-55, YPOS-5, 0);//�ɸ���
			break;
	}
	_SUTIL->g->ResetClip();

//�Ӽ�
	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs,MODULE_UI_ELEMENTAL_00+s_Page.Woman_Man/*Character::s_Status[s_Page.Woman_Man].ELEMENTAL*/, XPOS-9, YPOS-54,0,0);
 
	// char hp
	PaintGage(GAGE_RED, 58,4, XPOS+15, YPOS-26, Character::s_Status[s_Page.Woman_Man].LIFE, Character::s_Status[s_Page.Woman_Man].LIFE_MAX);
	// char mp
	PaintGage(GAGE_BLUE, 58,4, XPOS+15, YPOS-12, Character::s_Status[s_Page.Woman_Man].MANA, Character::s_Status[s_Page.Woman_Man].MANA_MAX);
	// char exp
	PaintGage(GAGE_YELLOW, 58,4, XPOS+15, YPOS+2, Character::s_Status[s_Page.Woman_Man].EXP, Character::s_Status[s_Page.Woman_Man].EXP_MAX);


	int _STR=0,_DEX=0,_CON=0,_INT=0;
	for (int slot = 0 ; slot<7 ; slot++){
		_STR +=Character::s_ItemAbil[s_Page.Woman_Man][slot].STR;
		_DEX +=Character::s_ItemAbil[s_Page.Woman_Man][slot].DEX;
		_CON +=Character::s_ItemAbil[s_Page.Woman_Man][slot].CON;
		_INT +=Character::s_ItemAbil[s_Page.Woman_Man][slot].INT;
	}
	for(int xx = 0, ABIL = 0;xx<4;xx++){
		ABIL = (xx == 0 ? Character::s_Ability[s_Page.Woman_Man].STR :(xx == 1 ? Character::s_Ability[s_Page.Woman_Man].DEX :(xx == 2 ? Character::s_Ability[s_Page.Woman_Man].CON :Character::s_Ability[s_Page.Woman_Man].INT)));
		_SUTIL->pFont->setColor(0xab9a77);

 		if(xx == (SELECT_STATES_Y-2)){
 			_SUTIL->pFont->setColor(0x000000);
// 			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TEXT_STR+xx], XPOS-68, YPOS+81, 0);//Text
 		}

		if(PAGE_STATES_point[xx+1] - ABIL)
			_SUTIL->pFont->setOutlineColor((xx == (SELECT_STATES_Y-2)? 0xffc708: 0xad0408));//������ ���̸� �ƿ������� ���

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_POWER+xx], XPOS-69, YPOS+41 + (13*xx), CGraphics::BOTTOM);//��//��ø//ü��//����
		ABIL += (xx == 0 ? _STR :(xx == 1 ? _DEX :(xx == 2 ? _CON :_INT)));//�������ġ 
		_SUTIL->pFont->DrawText(_SUTIL->g, ABIL, XPOS-12, YPOS+41 + (13*xx), CGraphics::RIGHT|CGraphics::BOTTOM);//��//��ø//ü��//����

		_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����
	} 

	//ȣĪ
	_SUTIL->pFont->setColor(0xf8e6cb);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TITLETEMP], XPOS+47, YPOS-51, CGraphics::HCENTER);//ȣĪ

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status[s_Page.Woman_Man].LIFE,  XPOS+43, YPOS-34, 1 , CGraphics::RIGHT);//HP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status[s_Page.Woman_Man].LIFE_MAX,  XPOS+69, YPOS-34, 1 , CGraphics::RIGHT);//HP MAX

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status[s_Page.Woman_Man].MANA,  XPOS+43, YPOS-20, 1 , CGraphics::RIGHT);//MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status[s_Page.Woman_Man].MANA_MAX,  XPOS+69, YPOS-20, 1 , CGraphics::RIGHT);//MP MAX

	//EXP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status[s_Page.Woman_Man].EXP_MAX-Character::s_Status[s_Page.Woman_Man].EXP,  XPOS+69, YPOS-6, 1 , CGraphics::RIGHT);//HP,MP,EXP MAX

	//LV
	//SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_LEVEL, XPOS-30,YPOS-77,0);//�˾� ������ ����
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM, Character::s_Status[s_Page.Woman_Man].LEVEL,  XPOS, YPOS-72, 0 , 0);


	
	
	//��ġ,//����Ʈ
	_SUTIL->pFont->setColor(0xf8e6cb);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_POINTS], XPOS-69, YPOS+15, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_REPUTATION], XPOS+6, YPOS+15, 0);
	_SUTIL->pFont->setColor(0xffc708);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Ability[s_Page.Woman_Man].POINT, XPOS-11, YPOS+15, CGraphics::RIGHT);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Ability[s_Page.Woman_Man].FAM, XPOS+67, YPOS+15, CGraphics::RIGHT);
	
	
	_SUTIL->pFont->setColor(0xffc000);
	//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"ATT", XPOS+6, YPOS+41 + (13*0), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].ATTACK_MAX, XPOS+67, YPOS+41 + (13*0), CGraphics::RIGHT|CGraphics::BOTTOM);
	//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"DEF", XPOS+6, YPOS+41 + (13*1), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].DEFENSE, XPOS+67, YPOS+41 + (13*1), CGraphics::RIGHT|CGraphics::BOTTOM);
	//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"CRI", XPOS+6, YPOS+41 + (13*2), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"%", XPOS+59, YPOS+41 + (13*2), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].CRITICAL, XPOS+57, YPOS+41 + (13*2), CGraphics::RIGHT|CGraphics::BOTTOM);
	//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"AGI", XPOS+6, YPOS+41 + (13*3), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"%", XPOS+59, YPOS+41 + (13*3), CGraphics::BOTTOM);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].AVOID, XPOS+57, YPOS+41 + (13*3), CGraphics::RIGHT|CGraphics::BOTTOM);

	if(s_Page.Focus == 1){// �˾� - �������ͽ� ���� ���� Ȯ��
		//_SUTIL->g->blandBlur();
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + s_Page.Ly2_sel, XPOS,YPOS-30,0);//�˾� ������ ����

		_SUTIL->pFont->setColor(0xf8e6cb);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q1], XPOS, YPOS-30+15, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
	}

}

void PopupUi::Paint_EQUIP()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_2, XPOS,YPOS,0);

//�ɸ��� ���ż� �����ֱ�
	_SUTIL->g->SetClip(XPOS-79,YPOS-74,56,77);	


	switch(s_Page.Woman_Man){
		case 0:
			SUTIL_Paint_Ani(Character::_spr_Hero_W ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-55, YPOS-5, 0);//�ɸ���
			break;
		case 1:
			SUTIL_Paint_Ani(Character::_spr_Hero_M ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-55, YPOS-5, 0);//�ɸ���
			break;
// 		case 2:
// 			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//�ɸ���
// 			break;
	}
	_SUTIL->g->ResetClip();



	int Scroll_x = (SELECT_EQUIP_LIST_NOW-6 > 0?SELECT_EQUIP_LIST_NOW-6:0);

	SELECT_EQUIP_LIST_MAX = 0; 

	for(int xx=0, Xpos=0, Ypos=0;xx<7;xx++){
		switch(xx){//�ش� ������ ������ ������ �׷��ְ� ���� ���ٸ� ��ŵ�Ѵ�.
			case 0:Xpos=-11	;Ypos=-45	;break;
			case 1:Xpos=10	;Ypos=-45	;break;
			case 2:Xpos=31	;Ypos=-45	;break;
			case 3:Xpos=52	;Ypos=-45	;break;
			case 4:Xpos=-11	;Ypos=-16	;break;
			case 5:Xpos=10	;Ypos=-16	;break;
			case 6:Xpos=31	;Ypos=-16	;break;
// 			case 7:Xpos=-58	;Ypos=-8	;break;
// 			case 8:Xpos=20	;Ypos=-8	;break;
// 			case 9:Xpos=42	;Ypos=-8	;break;
		}

		//Ŀ�� �׸���
		if(xx == SELECT_EQUIP_POS && SELECT_EQUIP_Y>0){ 
			if(SELECT_EQUIP_Y == 1){
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+Xpos, YPOS+Ypos,0);//Ŀ��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5,XPOS-67+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+8,0);//��Ȱ�� Ŀ��
				s_Popup_Sharp.posX = XPOS+Xpos;
				s_Popup_Sharp.posY = YPOS+Ypos;

			}else{
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS+Xpos, YPOS+Ypos,0);//��Ȱ�� Ŀ��
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-67+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+8,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17);
				s_Popup_Sharp.posY = YPOS+17;
			}




			if(Character::s_ItemEquip[s_Page.Woman_Man][xx].ITEM_KIND){//�������� �ִٸ�

				if (Scroll_x==0){//��ũ���� �Ͼ�� �ʾ������� �׷��ش�
					paint_ICON(Character::s_ItemEquip[s_Page.Woman_Man][xx],XPOS-67, YPOS+8,true);
					if(SELECT_EQUIP_LIST_NOW == 0){
						equipTEXT(s_Page.Woman_Man,SELECT_EQUIP_POS,Character::s_ItemEquip[s_Page.Woman_Man][xx]);
						SELECT_EQUIP_LIST_NOW_BAG = -1;
						SELECT_EQUIP_LIST_NOW_SLOT = -1;
					}
				}
				SELECT_EQUIP_LIST_MAX++;
				
			}
		}

		//�����ܱ׸���
		if(Character::s_ItemEquip[s_Page.Woman_Man][xx].ITEM_KIND){//�������� �ִٸ�
			paint_ICON(Character::s_ItemEquip[s_Page.Woman_Man][xx],XPOS+Xpos, YPOS+Ypos,false);
		}
// 		else{//�������� ���ٸ�
// 			SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTY_00+xx, XPOS+Xpos,YPOS+Ypos,0,0);//�� ����  ������
// 		}

	}

	



	
	if(SELECT_EQUIP_Y>0){//Ŀ���� ������ ������


	//���� ������ ��� ������ ����Ʈ������ �������ش�
		int Type;
		switch(SELECT_EQUIP_POS){//Ŀ���� �ִ� ������ ���� ������������ ġȯ�Ѵ�
			case 0:Type=ITEM_HEAD	;break;
			case 1:Type=ITEM_CHEST	;break;
			case 2:Type=ITEM_GLOVE 	;break;
			case 3:Type=ITEM_LEG	;break;
			case 4:Type=ITEM_NECK	;break;
			case 5:Type=ITEM_RING	;break;
			case 6:Type=ITEM_SWORD	;break;
// 			case 7:Type=ITEM_LEG	;break;
// 			case 8:Type=ITEM_GUN	;break;
// 			case 9:Type=ITEM_OEB	;break;
		}

		//������������ �������� ������� �����ش�
		for(int xx = 0;xx<4;xx++){
			for(int yy = 0;yy<32;yy++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.

				if(Character::s_ItemBag[xx][yy].ITEM_EQUIP == 0){// ������� ���� �������߿�
					int Kind = Character::s_ItemBag[xx][yy].ITEM_KIND;///*(Character::s_ItemBag[xx][yy].ITEM_KIND == ITEM_AXE ? ITEM_SWORD : Character::s_ItemBag[xx][yy].ITEM_KIND)*/;
					int Sex =  Character::s_ItemBag[xx][yy].ITEM_SEX;
					if(Kind == Type && Sex == s_Page.Woman_Man){
						if((SELECT_EQUIP_LIST_MAX-Scroll_x)>=0 && (SELECT_EQUIP_LIST_MAX-Scroll_x)<=6){
							paint_ICON(Character::s_ItemBag[xx][yy],XPOS-67+((SELECT_EQUIP_LIST_MAX-Scroll_x)*17), YPOS+8,true);
						}
						if(SELECT_EQUIP_LIST_NOW == SELECT_EQUIP_LIST_MAX){
							
							SELECT_EQUIP_LIST_NOW_BAG = xx;//���� ���õ� �������� ������ ����
							SELECT_EQUIP_LIST_NOW_SLOT = yy;//���� ���õ� �������� ������ ����


							equipTEXT(s_Page.Woman_Man,SELECT_EQUIP_POS , Character::s_ItemBag[xx][yy]);

							/*if(SELECT_EQUIP_LIST_NOW==5)
								Character::Set_state_calculate(5,Character::s_ItemBag[xx][yy].Data0,Character::s_ItemBag[xx][yy].Data1,Character::s_ItemBag[xx][yy].Data2);*/
						}
						SELECT_EQUIP_LIST_MAX++;
					}
				}


			}
		}

	
	}

	if(SELECT_EQUIP_LIST_MAX == 0){//���� �׸��� �������� �׸��ش�
		equipTEXT(s_Page.Woman_Man,SELECT_EQUIP_POS,Character::s_ItemEquip[s_Page.Woman_Man][SELECT_EQUIP_POS]);
	}




	if(s_Popup_Sharp.View && SELECT_EQUIP_Y > 0){
		if(SELECT_EQUIP_Y == 1 || (SELECT_EQUIP_LIST_NOW_BAG == -1&&SELECT_EQUIP_LIST_NOW_SLOT == -1)){
			PaintPopup_Sharp(Character::s_ItemEquip[s_Page.Woman_Man][SELECT_EQUIP_POS]);
		}else if(SELECT_EQUIP_Y == 2){
			PaintPopup_Sharp(Character::s_ItemBag[SELECT_EQUIP_LIST_NOW_BAG][SELECT_EQUIP_LIST_NOW_SLOT]);
		}
	}


	
}

void PopupUi::Paint_INVENTORY()	
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_3, XPOS,YPOS,0); 

	for(int xx = 0;xx<4;xx++){
		if(Character::s_ItemSlot[xx].ITEM_KIND)//������ �����ϸ�
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_BAG_00+(Character::s_ItemSlot[xx].ITEM_INDEX), XPOS-77+(xx*18),YPOS-73,0,0);
	}

	_SUTIL->g->SetColor(0x4a3429); 
	switch(Character::s_ItemSlot[SELECT_INVENTORY_BAG].Data0){
		case 100:
			_SUTIL->g->FillRect(XPOS-71,YPOS-39,143,51);
			break;
		case 101:
			_SUTIL->g->FillRect(XPOS-71,YPOS-22,143,34);
			break;
		case 102:
			_SUTIL->g->FillRect(XPOS-71,YPOS-5 ,143,17);
			break;
		case 103:

			break;
	}

	//�����ݾ� �׸���
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status[Character::s_HeroTag.SEX].MONEY,  XPOS+70, YPOS-68 , 1 , CGraphics::RIGHT);//MONEY


	//���� Ŀ�� 
	if(SELECT_INVENTORY_Y==1){
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			if(!(s_Page.Focus == 1 && SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE)){//������ �ٲܶ� �� ���� Ŀ���� ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-77+(SELECT_INVENTORY_BAG*18),YPOS-73,0);//���� ����
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-77+(SELECT_INVENTORY_BAG*18)	+6, 
				YPOS-73								-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-77+(SELECT_INVENTORY_BAG*18)+6, YPOS-73-4,true);
		}else{
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-77+(SELECT_INVENTORY_BAG*18),YPOS-73,0);//���� ���� ANI
		}
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-77+(SELECT_INVENTORY_BAG*18),YPOS-73,0);//���� ����
	}



	//�κ� Ŀ��
	if(SELECT_INVENTORY_Y==2){//�κ����� �������� ����
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			itemTEXT(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE],23,41,53,66);
		}
		if(Character::s_ItemPick.ITEM_KIND == 0){//Ŀ���� �������� ����� �׸���
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-70 + ((SELECT_INVENTORY_INSIDE%8)*18), YPOS-55 + ((SELECT_INVENTORY_INSIDE/8)*17),0);
			s_Popup_Sharp.posX = XPOS-70 + ((SELECT_INVENTORY_INSIDE%8)*18);
			s_Popup_Sharp.posY = YPOS-55 + ((SELECT_INVENTORY_INSIDE/8)*17);
		}
	}

	//���泻 �������� �׸��� 
	for(int xx = 0,MaxSlot = get_BagMax(Character::s_ItemSlot[SELECT_INVENTORY_BAG]);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			paint_ICON(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx], XPOS-70 + ((xx%8)*18), YPOS-55 + ((xx/8)*17),true);
		}
	}

	//�κ� Ŀ��
	if(SELECT_INVENTORY_Y==2){//�κ����� �������� ����
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-70 + ((SELECT_INVENTORY_INSIDE%8)*18)+6, 
				YPOS-55 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-70 + ((SELECT_INVENTORY_INSIDE%8)*18)+6,YPOS-55 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,true);
		}
	}


	if(s_Page.Focus == 1){// �˾� �׸��� - �����ۺ� ���� �˾�ȣ��


		int Px = -68 + ((SELECT_INVENTORY_INSIDE%8)*18) + (((SELECT_INVENTORY_INSIDE%8)<4) ? 24 : -49);
		int Py = -40 + ((SELECT_INVENTORY_INSIDE/8)*17);

		

		switch(SELECT_INVENTORY_POPUP_KIND){//������ ������ ��ȭ
			case INVENTORY_POPUP_QUICK://4��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_2,XPOS+Px,YPOS+Py,0);//4��¥�� �˾�â

				for(int xx = 0;xx<4;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_USE:(xx==1?CLRMENU_QSLOT:(xx==2?CLRMENU_BAN:CLRMENU_MOVE)))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;
			case INVENTORY_POPUP_SLOT : //2�� - ���� ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_4,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<2;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_SLOT_0:CLRMENU_SLOT_1)], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_EQUIP	://3��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<3;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_EQUIP){//������̸�
						_SUTIL->pFont->DrawText(_SUTIL->g, 
							(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_UNEQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
							XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
					}else{//������� �������� �ƴϸ�
						_SUTIL->pFont->DrawText(_SUTIL->g, 
							(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
							XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
					}
				}
				break;

			case INVENTORY_POPUP_EQUIP2://4��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_2,XPOS+Px,YPOS+Py,0);//4��¥�� �˾�â

				for(int xx = 0;xx<4;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_JAMSTONE:(xx==2?CLRMENU_BAN:CLRMENU_MOVE)))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;


			case INVENTORY_POPUP_USE	://3��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<3;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_USE:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_DEFAULT : //2��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_4,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<2;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_BAN:CLRMENU_MOVE)], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;
			

			case INVENTORY_POPUP_BAGCHANGE	://���� ���Կ� ����
				int ss = 0;
				break;
		}
	}

	if(s_Page.Focus == 2){// ��� �˾� �׸���


		switch(SELECT_INVENTORY_POPUP_TEXT_KIND){//�˾��� ����
			case INVENTORY_TEXT_POPUP__NOT_ENOUGH://���� ��������
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q5], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+37, CGraphics::HCENTER);
				break;
			case INVENTORY_TEXT_POPUP__ABANDON://������ ������ Ȯ��â
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_INVENTORY_POPUP_TEXT_YESNO, XPOS,YPOS,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);
				{
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q4], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
				}break;
			case INVENTORY_TEXT_POPUP__EQUIPDEL://���������� ������Ұ�
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q6], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+37, CGraphics::HCENTER);
				break;
		}
	}
	if(s_Popup_Sharp.View){ 
		if(SELECT_INVENTORY_Y == 2 && Character::s_ItemPick.ITEM_KIND==0 && s_Page.Focus == 0){
			PaintPopup_Sharp(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
		}
	}
}

void PopupUi::Paint_SKILL()		
{
//���
	int jab_Max;
	int Type[4];//3����+1 ������ŭ�� �迭�� �����ȴ�.
	int xx=0;

//������ �� ������ ����
// 	if(Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE){
// 		Type[xx] = 1;xx++;
// 	}
// 	if(Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN){
// 		Type[xx] = 2;xx++;
// 	}
// 	if(Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC){
// 		Type[xx] = 3;xx++;
// 	}


	if(SELECT_SKILL_ACT_PAS){//�нú�
		Type[xx] = 4;//����
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1, XPOS,YPOS,0);

		if(true){//�нú� ������ ���ְ� ������
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1AFTER, XPOS,YPOS,0);
		}else{
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1BEFORE, XPOS,YPOS,0);
		}

		//jab_Max = 1+Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE+Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN+Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC;
	}else{//��Ƽ��
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2, XPOS,YPOS,0);
		//jab_Max = Character::s_Ability[Character::s_HeroTag.SEX].JAB_KNIFE+Character::s_Ability[Character::s_HeroTag.SEX].JAB_GUN+Character::s_Ability[Character::s_HeroTag.SEX].JAB_MAGIC;
	}

//Ŀ���� �ؽ�Ʈ�� �ѷ���
 	_SUTIL->pFont->setColor(0xfbac29);//��Ƽ��,�нú�
 	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ACTIVE + SELECT_SKILL_ACT_PAS], XPOS, YPOS-67, CGraphics::HCENTER);
// 
// 	for(int zz = 0;zz < MIN((jab_Max-1),2);zz++)
// 		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI3, XPOS-63,YPOS+37+(zz*17),0);//���� ����â
// 
// 	_SUTIL->pFont->setColor(0xb4fa1e);
// 
// 	for(int yy = 0, findNum;yy < MIN(3,jab_Max);yy++){// ���� �ؽ�Ʈ
// 		if(SELECT_SKILL_Y==3 && !yy){
// 			_SUTIL->pFont->setOutline(true);
// 			_SUTIL->pFont->setOutlineColor((++ani_Num)%2?0x537a00:0x304a00);
// 		}
// 		findNum = (SELECT_SKILL_TYPE + yy) % jab_Max;
// 		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SWORD+Type[findNum]-1], XPOS-65+(yy?7:0), YPOS+23+(17*yy), 0);
// 		if(!yy) _SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ACTIVE + SELECT_SKILL_ACT_PAS],5);  //DrawString(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SWORD+Type[findNum]-1], XPOS-65+(yy?7:0), YPOS+23+(17*yy), 0, true);
// 		_SUTIL->pFont->setOutline(false);
// 		_SUTIL->pFont->setColor(0x546779);
// 	}
	//SELECT_SKILL_TYPE_NOW = Type[(SELECT_SKILL_TYPE) % jab_Max]-1;//���� ���õ� ����

	//������ �ѷ��ֱ� - ����
	if(SELECT_SKILL_ACT_PAS){//�нú�
		for(int xx = 0;xx<8;xx++){
			if(Character::s_Skill.Equip_P[xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00+Character::s_Skill.Equip_P[xx],
					XPOS-25 + ((xx%3)*18), 
					YPOS-37 + ((xx/3)*17),0);//���� ����â
		}
	}else{//��Ƽ��
		for(int xx = 0;xx<3;xx++){
			if(Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + xx],
				XPOS-37 + (xx*30), 
				YPOS+65, 0);
		}
		//SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,Character::Check_sex(FRAME_UI_UI_4_2WOMAN,FRAME_UI_UI_4_2MAN), XPOS,YPOS,0);//��ų����
	}


	int skill_Max=0;//������ �ѷ��ֱ� - ��ų
	if(SELECT_SKILL_ACT_PAS){//�нú�

		for(int xx = 0;xx<7;xx++){
			switch(s_Page.Woman_Man){
				case 0:if(Character::s_Skill.Level_P[xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND=xx;		skill_Max++;}break;//Į �нú� ��ų����
				case 1:if(Character::s_Skill.Level_P[7+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_G_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND=xx+7;	skill_Max++;}break;//�� �нú� ��ų����
				case 2:if(Character::s_Skill.Level_P[14+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_O_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND=xx+14;	skill_Max++;}break;//�� �нú� ��ų����
				case 3:if(Character::s_Skill.Level_P[21+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_N_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND=xx+21;	skill_Max++;}break;//�� �нú� ��ų����
			}
		}
	}else{//��Ƽ��

		
			switch(s_Page.Woman_Man){  
				case 0:
					{ 
						for(int xx = 0;xx<7;xx++){
							if(Character::s_Skill.Level_A[xx]==0){s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,8,0);}//�׷��� ������
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+xx,XPOS+s_X[s_Page.Woman_Man][xx],YPOS+s_Y[s_Page.Woman_Man][xx],0);
							s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,8,0);//�׷��� ������ ����
						}

						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2WOMAN,XPOS,YPOS,0);
						//if(skill_Max==SELECT_SKILL_KIND)
							//SELECT_SKILL_KIND=SELECT_SKILL_KIND;
					}break;//��ĳ �нú� ��ų����
				case 1:
					{ 
						for(int xx = 0;xx<7;xx++){
							if(Character::s_Skill.Level_A[xx]==0){s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,8,0);}//�׷��� ������
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_G_1+xx,XPOS+s_X[s_Page.Woman_Man][xx],YPOS+s_Y[s_Page.Woman_Man][xx],0);
							s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,8,0);//�׷��� ������ ����
						}

						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2MAN,XPOS,YPOS,0);
						//if(skill_Max==SELECT_SKILL_KIND)
							//SELECT_SKILL_KIND=SELECT_SKILL_KIND+7;
					}break;//��ĳ �нú� ��ų����
// 				case 2:if(Character::s_Skill.Level_A[14+xx]){
// 							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_O_1 + xx, 
// 							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
// 							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+14;	skill_Max++;}break;//�� �нú� ��ų����
			}
		
	}


	


//Ŀ��
	if(s_Page.Focus == 0){
		switch(SELECT_SKILL_Y){
			case 1://��Ƽ�� �нú� ����
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_2, XPOS-27, YPOS-70, 0);
				break;
			case 3://���� ����
				if(SELECT_SKILL_ACT_PAS){//�нú�
					if(SELECT_SKILL_KIND>=0){//Ŀ���� �������� ����ִٸ� �׷��ش�
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00+SELECT_SKILL_KIND,
							XPOS-26+6 + ((SELECT_SKILL_SLOT%3)*18), 
							YPOS-38-4 + ((SELECT_SKILL_SLOT/3)*17), 						0);
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
							XPOS-26+5 + ((SELECT_SKILL_SLOT%3)*18), 
							YPOS-38-5 + ((SELECT_SKILL_SLOT/3)*17), 						0);
					}else{
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
							XPOS-26 + ((SELECT_SKILL_SLOT%3)*18), 
							YPOS-38 + ((SELECT_SKILL_SLOT/3)*17), 						0);
					}
					s_Popup_Sharp.posX = XPOS-26 + ((SELECT_SKILL_SLOT%3)*18);
					s_Popup_Sharp.posY = YPOS-38 + ((SELECT_SKILL_SLOT/3)*17);
					
				}else{//��Ƽ��
					if(SELECT_SKILL_KIND>=0){
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+SELECT_SKILL_KIND,
							XPOS-37+6 + (SELECT_SKILL_SLOT*30), 
							YPOS+65-4, 						0);
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
							XPOS-37+5 + (SELECT_SKILL_SLOT*30), 
							YPOS+65-5, 						0);
					}else{
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_5, 
							XPOS-37 + (SELECT_SKILL_SLOT*30), 
							YPOS+65, 						0);
					}
					s_Popup_Sharp.posX = XPOS-64 + (SELECT_SKILL_SLOT*28);
					s_Popup_Sharp.posY = YPOS-21;
				}

				
				break;
			case 2://��ų ����
					SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
						/*XPOS-14 + ((SELECT_SKILL_KIND%4)*18)*/ XPOS+SELECT_SKILL_C_X, 
						/*YPOS+36 + ((SELECT_SKILL_KIND/4)*17)*/ YPOS+SELECT_SKILL_C_Y,	0);
// 					s_Popup_Sharp.posX = XPOS-14 + ((SELECT_SKILL_KIND%4)*18);
// 					s_Popup_Sharp.posY = YPOS+36 + ((SELECT_SKILL_KIND/4)*17);
					break;
			case 4:
				if(SELECT_SKILL_ACT_PAS){//�нú�
					SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, 
						XPOS-26 + ((SELECT_SKILL_SLOT%3)*18), 
						YPOS-38 + ((SELECT_SKILL_SLOT/3)*17), 						0);
				}else{//��Ƽ��
					SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI13, 
						XPOS-64 + (SELECT_SKILL_SLOT*28), 
						YPOS-21, 						0);
				}
				break;
		}
	}else if(s_Page.Focus == 0){
	}


	//�ϴܿ� ����� ,����
	_SUTIL->pFont->setColor(0xffffff);
	if(SELECT_SKILL_Y == 2){
		char str[30];//���� �ִ�ũ��
		int SkillNum;
		if(SELECT_SKILL_ACT_PAS){//�нú�
			
// 			if(SELECT_SKILL_Y == 2){
// 				SkillNum = Character::s_Skill.Equip_P[SELECT_SKILL_SLOT];
// 			}else if(SELECT_SKILL_Y == 4){
			SkillNum = SELECT_SKILL_KIND+(s_Page.Woman_Man?7:0);
//			}

			if(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0){
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_P[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS, YPOS+45, Graphics::HCENTER);
			}
		}else{
			
// 			if(SELECT_SKILL_Y == 2){
// 				SkillNum = Character::s_Skill.Equip_A[Character::s_HeroTag.SEX][SELECT_SKILL_SLOT];
// 			}else if(SELECT_SKILL_Y == 4){
			SkillNum = SELECT_SKILL_KIND+(s_Page.Woman_Man?7:0);
//			}

			if(Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + SELECT_SKILL_SLOT]>=0){	
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_SKILL_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_A[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS, YPOS+45, Graphics::HCENTER);
			}
		}
	}else if(SELECT_SKILL_Y == 3){
		char str[30];//���� �ִ�ũ��
		int SkillNum;
		if(SELECT_SKILL_ACT_PAS){//�нú�

			// 			if(SELECT_SKILL_Y == 2){
			// 				SkillNum = Character::s_Skill.Equip_P[SELECT_SKILL_SLOT];
			// 			}else if(SELECT_SKILL_Y == 4){
			SkillNum = SELECT_SKILL_KIND+(s_Page.Woman_Man?7:0);
			//			}

			if(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0){
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_P[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS, YPOS+45, Graphics::HCENTER);
			}
		}else{
			SkillNum = Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + SELECT_SKILL_SLOT];

			if(Character::s_Skill.Equip_A[s_Page.Woman_Man*3 + SELECT_SKILL_SLOT]>=0){	
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_SKILL_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_A[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS, YPOS+45, Graphics::HCENTER);
			}
		}
	}

	if(s_Popup_Sharp.View){ 
// 		if(SELECT_SKILL_Y == 2){
// 			if(SELECT_SKILL_ACT_PAS){//�нú�
// 				if(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0)
// 					PaintPopup_Sharp(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT] + SKILL_P_S_swordMaster);
// 			}else{
// 				if(Character::s_Skill.Equip_A[Character::s_HeroTag.SEX][SELECT_SKILL_SLOT]>=0)
// 					PaintPopup_Sharp(Character::s_Skill.Equip_A[Character::s_HeroTag.SEX][SELECT_SKILL_SLOT]);
// 			}
// 			
// 		}
		if(SELECT_SKILL_Y == 2){
			if(SELECT_SKILL_ACT_PAS){//�нú�
				PaintPopup_Sharp(SELECT_SKILL_KIND + SKILL_P_W_CriUp);
			}else{
				PaintPopup_Sharp(SELECT_SKILL_KIND);
			}
		}
	}
}

void PopupUi::Paint_HOBBY()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_5, XPOS,YPOS,0);

	//���� 
	_SUTIL->pFont->setColor(0xEEEEEE); 
	for (int xx = 0;xx<4;xx++){
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_GEM_0+xx], XPOS-68, YPOS-39+xx*12, CGraphics::HCENTER);
	}

	int SUM_0=0,SUM_1=0,SUM_2=0,SUM_3=0;
	for (int xx = 0;xx<7;xx++){
		if(Character::s_ItemAbil[s_Page.Woman_Man][xx].DDANG)_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_ItemAbil[s_Page.Woman_Man][xx].DDANG, XPOS-48+xx*16, YPOS-38   , CGraphics::HCENTER);
		if(Character::s_ItemAbil[s_Page.Woman_Man][xx].MUL  )_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_ItemAbil[s_Page.Woman_Man][xx].MUL  , XPOS-48+xx*16, YPOS-38+12, CGraphics::HCENTER);
		if(Character::s_ItemAbil[s_Page.Woman_Man][xx].BUL  )_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_ItemAbil[s_Page.Woman_Man][xx].BUL  , XPOS-48+xx*16, YPOS-38+24, CGraphics::HCENTER);
		if(Character::s_ItemAbil[s_Page.Woman_Man][xx].BARAM)_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_ItemAbil[s_Page.Woman_Man][xx].BARAM, XPOS-48+xx*16, YPOS-38+36, CGraphics::HCENTER);
		SUM_0 += Character::s_ItemAbil[s_Page.Woman_Man][xx].DDANG;
		SUM_1 += Character::s_ItemAbil[s_Page.Woman_Man][xx].MUL  ;
		SUM_2 += Character::s_ItemAbil[s_Page.Woman_Man][xx].BUL  ;
		SUM_3 += Character::s_ItemAbil[s_Page.Woman_Man][xx].BARAM;
	}

	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_GEM_SUM], XPOS+69, YPOS-54, CGraphics::HCENTER);//�հ�
	_SUTIL->pFont->DrawText(_SUTIL->g, SUM_0, XPOS+69, YPOS-38   , CGraphics::HCENTER);
	_SUTIL->pFont->DrawText(_SUTIL->g, SUM_1, XPOS+69, YPOS-38+12, CGraphics::HCENTER);
	_SUTIL->pFont->DrawText(_SUTIL->g, SUM_2, XPOS+69, YPOS-38+24, CGraphics::HCENTER);
	_SUTIL->pFont->DrawText(_SUTIL->g, SUM_3, XPOS+69, YPOS-38+36, CGraphics::HCENTER);


}

void PopupUi::Paint_QUEST()		
{//GET_MAINQUEST_IDX()
	if(s_Page.Focus==0){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_6_1, XPOS,YPOS,0);

		//���� 
		_SUTIL->pFont->setColor(0xfbab29);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MAIN], XPOS-40, YPOS-64, CGraphics::HCENTER);
		//����
		_SUTIL->pFont->setColor(0xb4fa1e);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SUB], XPOS-40, YPOS-18, CGraphics::HCENTER);


		//������
		_SUTIL->pFont->setColor((SELECT_QUEST_Y==1 ?0xffda00 :0x748799)); 
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[GET_MAINQUEST_IDX()*2], XPOS-72, YPOS-46, 0); 

		//������
		for (int xx = 0; xx<MIN(5,s_Quest.Max_Num); xx++)
		{
			_SUTIL->pFont->setColor((SELECT_QUEST_Y==xx+2 ?0xffda00 :0x748799));
			if(s_Quest.SubHave[xx + SELECT_QUEST_SUB_Y]>=0){
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[s_Quest.SubHave[xx + SELECT_QUEST_SUB_Y]*2], XPOS-64, YPOS+16 + (15*xx), 0);
			}
		}

		//Ŀ��
		if(SELECT_QUEST_Y==1){//����
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_7, XPOS-77,YPOS-49,0);
		}else if(SELECT_QUEST_Y>1){//����
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_8, XPOS-77,YPOS+13+(SELECT_QUEST_Y-2)*15,0);
		}

		//��ũ�ѹ�
		_SUTIL->g->SetColor(0xff6e00);
		if(s_Quest.Max_Num > 5){//�ٰ� �پ�� ��
			int Bar_height = MAX(30, (74 - (s_Quest.Max_Num-5)*10) );
			int yy = ((74 - Bar_height)*SELECT_QUEST_SUB_Y)/(s_Quest.Max_Num-5);
			_SUTIL->g->FillRect( XPOS+70, YPOS+2+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+70, YPOS+2,4,74);
		}

	}else if(s_Page.Focus==1){//���� ���� ������
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_6_2, XPOS,YPOS,0);

		int titleNum;
		if(SELECT_QUEST_Y==1){//��������Ʈ
			titleNum = GET_MAINQUEST_IDX()*2;
		}else{
			titleNum = s_Quest.SubHave[SELECT_QUEST_Y-2 + SELECT_QUEST_SUB_Y]*2;
		}

		//������ ���� ��Ȳ
		char str[31];//������ �ؽ�Ʈ
		int Num = Set_QUEST(NULL,GET_MAINQUEST_IDX());
		if(Q_ITEM_ID(Num)){
			_SUTIL->pFont->setOutlineColor(0X000000);//�ƿ� ������ ���
			if(Q_ITEM_NOW(Num) < Q_ITEM_MAX(Num)){//����Ʈ �����̴�
				_SUTIL->pFont->setColor(0xFF5E39);
				SPRINTF(str, "%s (%d/%d)",
					(char*)pITEM_Text->nText[itemNAME(Q_ITEM_ID(Num)/100,Q_ITEM_ID(Num)%100)],
					Q_ITEM_NOW(Num),
					Q_ITEM_MAX(Num)); 
			}else{//����Ʈ �Ϸ�
				_SUTIL->pFont->setColor(0x00FF00);
				SPRINTF(str, "%s (%s)",
					(char*)pITEM_Text->nText[itemNAME(Q_ITEM_ID(Num)/100,Q_ITEM_ID(Num)%100)],
					(char*)pITEM_Text->nText[ITEM_CLEAR]); 	
			}
			_SUTIL->pFont->DrawText(_SUTIL->g, str,XPOS, YPOS-45, CGraphics::HCENTER);
			_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����
		}
		


		//����Ʈ��
		_SUTIL->pFont->setColor(0x93abc0);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[titleNum], XPOS, YPOS-68, CGraphics::HCENTER);
		
		//����Ʈ ����
		_SUTIL->pFont->setColor(0xFFFFFF);
		_SUTIL->pFont->setLineSpace(3);

		_SUTIL->pFont->Dry_Wrap_Width(134);
		_SUTIL->pFont->Dry_StartLine_Max(SELECT_QUEST_DESC_Y,QUEST_DESC);
		SELECT_QUEST_DESC_Y_MAX = _SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[titleNum+1], XPOS-74, YPOS-29, CGraphics::LEFT);



		//��ũ�ѹ�
		_SUTIL->g->SetColor(0xff6e00);
		if(SELECT_QUEST_DESC_Y_MAX > QUEST_DESC){//�ٰ� �پ�� ��
			int Bar_height = MAX(30, (102 - (SELECT_QUEST_DESC_Y_MAX-QUEST_DESC)*10) );
			int yy = ((102 - Bar_height)*SELECT_QUEST_DESC_Y)/(SELECT_QUEST_DESC_Y_MAX-QUEST_DESC);
			_SUTIL->g->FillRect( XPOS+73, YPOS-47+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+73, YPOS-47,4,109);
		}

		//��ư
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_QUEST_DESC_X, XPOS-1,YPOS+31,0);//�˾� ������ ����
		_SUTIL->pFont->setColor(0xf8e6cb);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CLOSE], XPOS-32, YPOS+68, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DISCARD], XPOS+30, YPOS+68, CGraphics::HCENTER);
	}


}

void PopupUi::Paint_SYSTEM()	
{
	if(s_Page.Focus==0){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_7, XPOS,YPOS,0);

		//�ؽ�Ʈ
		for (int xx = 0; xx<3; xx++)
		{
			_SUTIL->pFont->setColor((SELECT_SYSTEM_Y-1==xx ?0xffda00 :0x546779));
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SYSTEM_0+xx], XPOS,YPOS-48 + (xx*24), CGraphics::HCENTER);
		}
 
		//Ŀ��
		if(SELECT_SYSTEM_Y>0){
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_6, XPOS-38,YPOS-51 + ((SELECT_SYSTEM_Y-1)*24),0);
		}
		
	}

	if(s_Page.Focus == 10){// �˾� - �������ͽ� ���� ���� Ȯ��
//		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_TRAFFIC, XPOS,YPOS-50,0);//�˾� ������ ����
		
		_SUTIL->pFont->setColor(0xFF0000);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"CHEAT PAGE", XPOS, YPOS-60, CGraphics::HCENTER);

		_SUTIL->pFont->setColor(0x000055);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"1. Level Up", XPOS, YPOS	+15+(12*0)-50, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"2. God's Hp", XPOS, YPOS	+15+(12*1)-50, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"3. God's Mp", XPOS, YPOS	+15+(12*2)-50, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"4. No Cooltime", XPOS, YPOS+15+(12*3)-50, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"5. Super Man", XPOS, YPOS+15+(12*4)-50, CGraphics::HCENTER);
	}

}



void PopupUi::Paint_GAMEOVER()	
{
	
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_GAMEOVER, XPOS,YPOS,0);
	
	for(int xx = 0; xx<4;xx++){
		if(xx==SELECT_GAMEOVER_Y)
			_SUTIL->pFont->setColor(0xfbab29);
		else
			_SUTIL->pFont->setColor(0x3a444d);


		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_USE_LIFESTONE+xx], XPOS, YPOS+2+(xx*24), CGraphics::HCENTER);
	}
	SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_6, XPOS-44,YPOS-4+(SELECT_GAMEOVER_Y*24),0);//
	
}


void PopupUi::Paint_ITEMSHOP()	
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_SHOP, XPOS,YPOS,0); 

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_WEAPONSHOP_TAB_1+SELECT_ITEMSHOP_X, XPOS,YPOS,0); 

	for(int xx = 0;xx<4;xx++){
		if(Character::s_ItemSlot[xx].ITEM_KIND)//������ �����ϸ�
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_BAG_00+(Character::s_ItemSlot[xx].ITEM_INDEX), XPOS+4+(xx*18),YPOS-73,0,0);
	}

	int Y_size = 59;
	_SUTIL->g->SetColor(0x4a3429);   
	switch(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG].Data0){
		case 100:
			_SUTIL->g->FillRect(XPOS+4,YPOS-22,66,31);
			break;
		case 101:
			break;
		case 102://�ش簡���� 4X5 ǥ�������� �Ѵ´� - ��ũ�ѹ�  ǥ��
			Y_size = 43;
			break;
		case 103://�ش簡���� 4X5 ǥ�������� �Ѵ´� - ��ũ�ѹ�  ǥ��
			Y_size = 27;
			break; 
	}

	if(SELECT_ITEMSHOP_FOCUS_R_L){
		if(SELECT_ITEMSHOP_INSIDE>=16 && SELECT_ITEMSHOP_R_SCROLL==0)
			SELECT_ITEMSHOP_R_SCROLL=1;
		if(SELECT_ITEMSHOP_INSIDE>=20 && SELECT_ITEMSHOP_R_SCROLL==1)
			SELECT_ITEMSHOP_R_SCROLL=2;
		if(SELECT_ITEMSHOP_INSIDE>=24 && SELECT_ITEMSHOP_R_SCROLL==2)
			SELECT_ITEMSHOP_R_SCROLL=3;
		if(SELECT_ITEMSHOP_INSIDE>=28 && SELECT_ITEMSHOP_R_SCROLL==3)
			SELECT_ITEMSHOP_R_SCROLL=4;


		if(SELECT_ITEMSHOP_INSIDE<16 && SELECT_ITEMSHOP_R_SCROLL==4)
			SELECT_ITEMSHOP_R_SCROLL=3;
		if(SELECT_ITEMSHOP_INSIDE<12 && SELECT_ITEMSHOP_R_SCROLL==3)
			SELECT_ITEMSHOP_R_SCROLL=2;
		if(SELECT_ITEMSHOP_INSIDE<8 && SELECT_ITEMSHOP_R_SCROLL==2)
			SELECT_ITEMSHOP_R_SCROLL=1;
		if(SELECT_ITEMSHOP_INSIDE<4 && SELECT_ITEMSHOP_R_SCROLL==1)
			SELECT_ITEMSHOP_R_SCROLL=0;
	}else{
		if(SELECT_ITEMSHOP_INSIDE>=16 && SELECT_ITEMSHOP_L_SCROLL==0)
			SELECT_ITEMSHOP_L_SCROLL=1;
		if(SELECT_ITEMSHOP_INSIDE>=20 && SELECT_ITEMSHOP_L_SCROLL==1)
			SELECT_ITEMSHOP_L_SCROLL=2;
// 		if(SELECT_ITEMSHOP_INSIDE>=24 && SELECT_ITEMSHOP_L_SCROLL==2)
// 			SELECT_ITEMSHOP_L_SCROLL=3;
// 		if(SELECT_ITEMSHOP_INSIDE>=28 && SELECT_ITEMSHOP_L_SCROLL==3)
// 			SELECT_ITEMSHOP_L_SCROLL=4;


// 		if(SELECT_ITEMSHOP_INSIDE<16 && SELECT_ITEMSHOP_L_SCROLL==4)
// 			SELECT_ITEMSHOP_L_SCROLL=3;
// 		if(SELECT_ITEMSHOP_INSIDE<12 && SELECT_ITEMSHOP_L_SCROLL==3)
// 			SELECT_ITEMSHOP_L_SCROLL=2;
		if(SELECT_ITEMSHOP_INSIDE<8 && SELECT_ITEMSHOP_L_SCROLL==2)
			SELECT_ITEMSHOP_L_SCROLL=1;
		if(SELECT_ITEMSHOP_INSIDE<4 && SELECT_ITEMSHOP_L_SCROLL==1)
			SELECT_ITEMSHOP_L_SCROLL=0;
	}


	_SUTIL->g->SetColor(0xe3deaa);
	_SUTIL->g->FillRect( XPOS+74, YPOS-52 + SELECT_ITEMSHOP_R_SCROLL*8,2,Y_size);
	_SUTIL->g->FillRect( XPOS-7, YPOS-52 + SELECT_ITEMSHOP_L_SCROLL*8,2,43);


	//�����ݾ� �׸���
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status[Character::s_HeroTag.SEX].MONEY,  XPOS-6, YPOS-69 , 1 , CGraphics::RIGHT);//MONEY

	//������ ���� �׸��� 
	_SUTIL->pFont->setColor(0x83695b);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_GOLD],XPOS+75, YPOS+73 ,CGraphics::RIGHT);
	if(SELECT_ITEMSHOP_FOCUS_R_L){
		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, CalkCost(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]),  XPOS+50, YPOS+74 , 1 , CGraphics::RIGHT);//MONEY
	}else{
		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, CalkCost(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE]),  XPOS+50, YPOS+74 , 1 , CGraphics::RIGHT);//MONEY
	}
	

	

	//���� Ŀ�� 

	

	if(SELECT_ITEMSHOP_Y==0){
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_TAP, XPOS + 18*SELECT_ITEMSHOP_X,YPOS-92,0);//�� Ŀ��
	}else if(SELECT_ITEMSHOP_Y==1){
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+4+(SELECT_ITEMSHOP_BAG*18),YPOS-73,0);//���� ���� ANI
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS+4+(SELECT_ITEMSHOP_BAG*18),YPOS-73,0);//���� ����
	



		//�κ� Ŀ��
		if(SELECT_ITEMSHOP_FOCUS_R_L){ 
			if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
				itemTEXT(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE],19,34,45,56);
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+4 + ((SELECT_ITEMSHOP_INSIDE%4)*17), YPOS-54 + ((SELECT_ITEMSHOP_INSIDE/4 - SELECT_ITEMSHOP_R_SCROLL)*16),0);
			s_Popup_Sharp.posX = XPOS+4 + ((SELECT_ITEMSHOP_INSIDE%4)*17);
			s_Popup_Sharp.posY = YPOS-54 + ((SELECT_ITEMSHOP_INSIDE/4 - SELECT_ITEMSHOP_R_SCROLL)*16);
				
		}else{
			if(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
				itemTEXT(Character::s_ItemShop[SELECT_ITEMSHOP_INSIDE],19,34,45,56);
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-77 + ((SELECT_ITEMSHOP_INSIDE%4)*17), YPOS-54 + ((SELECT_ITEMSHOP_INSIDE/4 - SELECT_ITEMSHOP_L_SCROLL)*16),0);
			s_Popup_Sharp.posX = XPOS-77 + ((SELECT_ITEMSHOP_INSIDE%4)*17);
			s_Popup_Sharp.posY = YPOS-54 + ((SELECT_ITEMSHOP_INSIDE/4 - SELECT_ITEMSHOP_R_SCROLL)*16);
		}
	}
	//���泻 �������� �׸��� 
	for(int xx = 0,MaxSlot = MIN(get_BagMax(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG]),16);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx+SELECT_ITEMSHOP_R_SCROLL*4].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			paint_ICON(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx+SELECT_ITEMSHOP_R_SCROLL*4], XPOS+4 + ((xx%4)*17), YPOS-54 + ((xx/4)*16),true);
		}
	}
	//������ �������� �׸���
	for(int xx = 0;xx<16;xx++){
		if(Character::s_ItemShop[xx+SELECT_ITEMSHOP_L_SCROLL*4].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			paint_ICON(Character::s_ItemShop[xx+SELECT_ITEMSHOP_L_SCROLL*4], XPOS-77 + ((xx%4)*17), YPOS-54 + ((xx/4)*16),true);
		}
	}


	if(s_Page.Focus == 1){// �˾� �׸��� - �����ۺ� ���� �˾�ȣ��


// 		int Px = -68 + ((SELECT_ITEMSHOP_INSIDE%4)*17) + (((SELECT_ITEMSHOP_INSIDE%8)<4) ? 24 : -49);
// 		int Py = -40 + ((SELECT_ITEMSHOP_INSIDE/4)*16);



		switch(SELECT_ITEMSHOP_POPUP_KIND){//�������� Ŭ���� ��ġ, �������� ���������� �ٸ� �˾��̶��

			case ITEMSHOP_POPUP_BUY			://�춧
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_ITEMSHOP_POPUP_TEXT_YESNO, XPOS,YPOS-30,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);

				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q7], XPOS, YPOS-30+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
				break;
			case ITEMSHOP_POPUP_SELL		://�ȶ�
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_ITEMSHOP_POPUP_TEXT_YESNO, XPOS,YPOS-30,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);

				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q8], XPOS, YPOS-30+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
				break;
			case ITEMSHOP_POPUP_BUY_COUNT	://�찹��
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_COUNT, XPOS,YPOS-30,0);//�˾� ������ ����
				PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, SELECT_ITEMSHOP_COUNT,  XPOS, YPOS-16 , 1 , CGraphics::HCENTER);//����
				PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, SELECT_ITEMSHOP_COUNT*CalkCost(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG]),  XPOS+28, YPOS+8 , 1 , CGraphics::RIGHT);//����
				break;
			case ITEMSHOP_POPUP_SELL_COUNT	://�Ȱ���
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_COUNT, XPOS,YPOS-30,0);//�˾� ������ ����
				PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, SELECT_ITEMSHOP_COUNT,  XPOS, YPOS-16 , 1 , CGraphics::HCENTER);//����
				PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, SELECT_ITEMSHOP_COUNT*CalkCost(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]),  XPOS+28, YPOS+8 , 1 , CGraphics::RIGHT);//����
				break;

			case ITEMSHOP_POPUP_NOT_SPACE://���� ��������
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q5], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;
			case ITEMSHOP_POPUP_NO_MONEY://��� ����
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q9], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;
			case ITEMSHOP_POPUP_NOT_SELL://�ǸźҰ� ��
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q9], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;

		}
	}

	
	if(s_Popup_Sharp.View){ 
		if(SELECT_ITEMSHOP_Y == 2 && s_Page.Focus == 0){
			if(SELECT_ITEMSHOP_FOCUS_R_L){
				PaintPopup_Sharp(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
			}else{
				
			}
			
		}
	}
}

void PopupUi::Paint_SMITHY()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_FORGE, XPOS,YPOS,0);

	

	int Scroll_x = (SELECT_SMITHY_LIST_NOW-7 > 0?SELECT_SMITHY_LIST_NOW-7:0);

	SELECT_SMITHY_LIST_MAX = 0; 






	

	// ���������ʰ� ���� ������ ��� ������ ����Ʈ������ �������ش�
	for(int xx = 0;xx<4;xx++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.
		for(int yy = 0;yy<32;yy++){
			switch(SELECT_SMITHY_Y){ 
				case 0:
					if(Character::s_ItemBag[xx][yy].ITEM_UPGRADE < 10 && Character::s_ItemBag[xx][yy].ITEM_EQUIP == 0 && Character::s_ItemBag[xx][yy].ITEM_KIND>=10 && Character::s_ItemBag[xx][yy].ITEM_KIND<20){// ������� ���� �������߿�
						if((SELECT_SMITHY_LIST_MAX-Scroll_x)>=0 && (SELECT_SMITHY_LIST_MAX-Scroll_x)<=7){
							paint_ICON(Character::s_ItemBag[xx][yy],XPOS-67+((SELECT_SMITHY_LIST_MAX-Scroll_x)*17), YPOS-5,true);
						}
						if((s_Page.Focus == 1) && (SELECT_SMITHY_LIST_NOW == SELECT_SMITHY_LIST_MAX)){
							SELECT_SMITHY_LIST_ITEM_BAG = xx;//���� ���õ� �������� ������ ����
							SELECT_SMITHY_LIST_ITEM_SLOT = yy;//���� ���õ� �������� ������ ����
							//equipTEXT(s_Page.Woman_Man,SELECT_SMITHY_POS , Character::s_ItemBag[xx][yy]);
						}
						SELECT_SMITHY_LIST_MAX++;
					}
					break;
				case 1:
					if(Character::s_ItemBag[xx][yy].ITEM_KIND == ITEM_UP_STONE){// ��ȭ�� ���ΰ˻�
						if((SELECT_SMITHY_LIST_MAX-Scroll_x)>=0 && (SELECT_SMITHY_LIST_MAX-Scroll_x)<=7){
							paint_ICON(Character::s_ItemBag[xx][yy],XPOS-67+((SELECT_SMITHY_LIST_MAX-Scroll_x)*17), YPOS-5,true);
						}
						if((s_Page.Focus == 1) && (SELECT_SMITHY_LIST_NOW == SELECT_SMITHY_LIST_MAX)){
							SELECT_SMITHY_USE_STONE_BAG = xx;//���� ���õ� �������� ������ ����
							SELECT_SMITHY_USE_STONE_SLOT = yy;//���� ���õ� �������� ������ ����
							//equipTEXT(s_Page.Woman_Man,SELECT_SMITHY_POS , Character::s_ItemBag[xx][yy]);
						}
						SELECT_SMITHY_LIST_MAX++;
					}
					break;
			}

			

		}
	} 

	if(s_Page.Focus == 0){//Ŀ���� ���� ������
		//Ŀ�� �׸���
		switch(SELECT_SMITHY_Y){
			case 0:
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-27, YPOS-52,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS-27;
				s_Popup_Sharp.posY = YPOS-52;
				break;
			case 1:
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+33, YPOS-52,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS+33;
				s_Popup_Sharp.posY = YPOS-52;
				break;
			case 2:
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_FORGE, XPOS+22, YPOS-31,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS+22;
				s_Popup_Sharp.posY = YPOS-31;
				break;
		}
	}else if(s_Page.Focus >= 1){//Ŀ���� ������ ������
		switch(SELECT_SMITHY_Y){
			case 0:
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-27, YPOS-52,0);//��Ȱ�� Ŀ��
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-67+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17), YPOS-5,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS-67+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17);
				s_Popup_Sharp.posY = YPOS-5;
				itemTEXT(Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT],23,41,53,66);
				break;
			case 1:
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS+33, YPOS-52,0);//��Ȱ�� Ŀ��
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-67+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17), YPOS-5,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS-67+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17);
				s_Popup_Sharp.posY = YPOS-5;
				itemTEXT(Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT],23,41,53,66);
				break;
		}
	}

	if(SELECT_SMITHY_ITEM_SLOT)	{//��� �׸��� 
		paint_ICON(Character::s_ItemBag[SELECT_SMITHY_LIST_ITEM_BAG][SELECT_SMITHY_LIST_ITEM_SLOT],XPOS-27, YPOS-52,false);
	}
	if(SELECT_SMITHY_STONE_SLOT){//��ȭ�� �׸���
		SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_UPSTONE_00 + Character::s_ItemBag[SELECT_SMITHY_USE_STONE_BAG][SELECT_SMITHY_USE_STONE_SLOT].ITEM_INDEX, XPOS+33, YPOS-52,0,0);//������
		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_SKILL_NUM, SELECT_SMITHY_USE_STONE_NUM,  XPOS+33+16, YPOS-52+9, -1 , CGraphics::RIGHT);//������ ����
	}


	_SUTIL->pFont->setColor(0xf8e6cb); 
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[Character::s_HeroTag.SEX].MONEY, XPOS+72, YPOS-70, CGraphics::RIGHT);
	_SUTIL->pFont->DrawText(_SUTIL->g, SMITHY_UP_COST, XPOS-12, YPOS-27, CGraphics::RIGHT);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_UP_0], XPOS-50, YPOS-49, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_UP_1], XPOS, YPOS-49, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_UP_2], XPOS-62, YPOS-28, 0);

	if(SELECT_SMITHY_STONE_SLOT && SELECT_SMITHY_ITEM_SLOT && (Character::s_Status[Character::s_HeroTag.SEX].MONEY >= SMITHY_UP_COST)){
		_SUTIL->pFont->setColor(0xf8e6cb);
	}else{//���� �����ϸ�
		_SUTIL->pFont->setColor(0xf80000);
	}
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_UP_3], XPOS+35, YPOS-28, 0);



	if(s_Page.Focus == 2){//�˾��� ���ִٸ�
		switch(SELECT_SMITHY_POPUP_KIND){
			case SMITHY_POPUP_NUM		:
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_5,XPOS-78+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17), YPOS+15,0);//3��¥�� �˾�â
				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, SELECT_SMITHY_POPUP_TEXT_YESNO,XPOS-60+((SELECT_SMITHY_LIST_NOW-Scroll_x)*17), YPOS+17, Graphics::HCENTER);//����
				break;
			case SMITHY_POPUP_QUESTION	:
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_SMITHY_POPUP_TEXT_YESNO, XPOS,YPOS-30,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);

				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q11], XPOS, YPOS-30+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
				break;
			case SMITHY_POPUP_ING		:
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_FORGING,XPOS,YPOS-30,0);//Ŀ��

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q12], XPOS+10, YPOS-10, CGraphics::HCENTER);
				switch(SELECT_SMITHY_POPUP_TEXT_YESNO%5){
					case 0:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)".", XPOS+40, YPOS-10, 0);break;
					case 1:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"..", XPOS+40, YPOS-10, 0);break;
					case 2:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"...", XPOS+40, YPOS-10, 0);break;
					case 3:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"....", XPOS+40, YPOS-10, 0);break;
					case 4:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)".....", XPOS+40, YPOS-10, 0);break;
				}
				break;
			case SMITHY_POPUP_RESULT	:	
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q13+SELECT_SMITHY_POPUP_TEXT_YESNO], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;
		}
	}


	

	






	if(s_Popup_Sharp.View && SELECT_SMITHY_Y > 0){
// 		if(SELECT_SMITHY_Y == 1 || (SELECT_SMITHY_LIST_NOW_BAG == -1&&SELECT_SMITHY_LIST_NOW_SLOT == -1)){
// 			PaintPopup_Sharp(Character::s_ItemEquip[s_Page.Woman_Man][SELECT_SMITHY_POS]);
// 		}else if(SELECT_SMITHY_Y == 2){
// 			PaintPopup_Sharp(Character::s_ItemBag[SELECT_SMITHY_LIST_NOW_BAG][SELECT_SMITHY_LIST_NOW_SLOT]);
// 		}
	}



}
void PopupUi::Paint_GEM()		
{
SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_3_ADDJEWEL, XPOS,YPOS,0);

	

	int Scroll_x = (SELECT_GEM_LIST_NOW-7 > 0?SELECT_GEM_LIST_NOW-7:0);

	SELECT_GEM_LIST_MAX = 0; 



	//��� ������
	_SUTIL->pFont->setColor(0xffffff);
	int head =		Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_HEADTEXT;
	int upgrade =	Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_UPGRADE;
	char str[31];//int �ִ�ũ��
	if(upgrade){
		SPRINTF(str, "%s %s %s%d",
			(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
			(char*)pITEM_Text->nText[itemNAME(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_KIND,Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_INDEX)],	"+",	upgrade); 	
	}else{
		SPRINTF(str, "%s %s",
			(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
			(char*)pITEM_Text->nText[itemNAME(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_KIND,Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_INDEX)]); 	
	}
	_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-37, YPOS-48, 0);//�̸�

	paint_ICON(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT],XPOS-58, YPOS-51,true);//������



	for(int xx = 0;xx<3;xx++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.
		int slot;
		switch(xx){//�󽽷�
			case 0:slot = Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_3;break;
			case 1:slot = Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_2;break;
			case 2:slot = Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT].ITEM_SOCKET_1;break;
		}
		switch(slot){//�󽽷�
			case 0:
				SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs,MODULE_UI_NO_SOCKET,XPOS + 22 * xx, YPOS-29,0,0);
				break;
			case 1:break;
			default:
				SUTIL_Paint_Module(s_ASpriteSet->pItemAs,MODULE_ITEM_JEWEL_EARTH_00 + slot -2,XPOS + 22 * xx, YPOS-29,0,0);
				break;

		}
	}

	

	for(int xx = 0;xx<4;xx++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.
		for(int yy = 0;yy<32;yy++){
			if(Character::s_ItemBag[xx][yy].ITEM_KIND == ITEM_GEM_STONE){// ���� ���ΰ˻�
				if((SELECT_GEM_LIST_MAX-Scroll_x)>=0 && (SELECT_GEM_LIST_MAX-Scroll_x)<=7){
					paint_ICON(Character::s_ItemBag[xx][yy],XPOS-67+((SELECT_GEM_LIST_MAX-Scroll_x)*17), YPOS-5,true);
				}
				if((s_Page.Focus == 1) && (SELECT_GEM_LIST_NOW == SELECT_GEM_LIST_MAX)){
					SELECT_GEM_USE_STONE_BAG = xx;//���� ���õ� �������� ������ ����
					SELECT_GEM_USE_STONE_SLOT = yy;//���� ���õ� �������� ������ ����
					//equipTEXT(s_Page.Woman_Man,SELECT_GEM_POS , Character::s_ItemBag[xx][yy]);
				}
				SELECT_GEM_LIST_MAX++;
			}
		}
	} 

	if(s_Page.Focus == 0){//Ŀ���� ���� ������
		//Ŀ�� �׸���
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS + 22*SELECT_GEM_Y, YPOS-29,0);//Ŀ��
		s_Popup_Sharp.posX = XPOS-27;
		s_Popup_Sharp.posY = YPOS-52;
		itemTEXT(Character::s_ItemBag[SELECT_GEM_ITEM_BAG][SELECT_GEM_ITEM_SLOT],23,41,53,66);

	}else if(s_Page.Focus >= 1){//Ŀ���� ������ ������
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS + 22*SELECT_GEM_Y, YPOS-29,0);//��Ȱ�� Ŀ��
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-67+((SELECT_GEM_LIST_NOW-Scroll_x)*17), YPOS-5,0);//Ŀ��
		s_Popup_Sharp.posX = XPOS-67+((SELECT_GEM_LIST_NOW-Scroll_x)*17);
		s_Popup_Sharp.posY = YPOS-5;
		itemTEXT(Character::s_ItemBag[SELECT_GEM_USE_STONE_BAG][SELECT_GEM_USE_STONE_SLOT],23,41,53,66);
	}

// 	if(SELECT_GEM_ITEM_SLOT)	{//��� �׸��� 
// 		paint_ICON(Character::s_ItemBag[SELECT_GEM_LIST_ITEM_BAG][SELECT_GEM_LIST_ITEM_SLOT],XPOS-27, YPOS-52,false);
// 	}
// 	if(SELECT_GEM_STONE_SLOT){//��ȭ�� �׸���
// 		SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_UPSTONE_00 + Character::s_ItemBag[SELECT_GEM_USE_STONE_BAG][SELECT_GEM_USE_STONE_SLOT].ITEM_INDEX, XPOS+33, YPOS-52,0,0);//������
// 		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_SKILL_NUM, SELECT_GEM_USE_STONE_NUM,  XPOS+33+16, YPOS-52+9, -1 , CGraphics::RIGHT);//������ ����
// 	}



	_SUTIL->pFont->setColor(0xf8e6cb); 
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[Character::s_HeroTag.SEX].MONEY, XPOS+72, YPOS-70, CGraphics::RIGHT);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_JAMSTONE], XPOS-42, YPOS-28, 0);





	if(s_Page.Focus == 2){//�˾��� ���ִٸ�
		switch(SELECT_GEM_POPUP_KIND){
			case GEM_POPUP_RESULT	:	
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q13+SELECT_GEM_POPUP_TEXT_YESNO], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;
		}
	}


	

	






	if(s_Popup_Sharp.View && SELECT_GEM_Y > 0){
// 		if(SELECT_GEM_Y == 1 || (SELECT_GEM_LIST_NOW_BAG == -1&&SELECT_GEM_LIST_NOW_SLOT == -1)){
// 			PaintPopup_Sharp(Character::s_ItemEquip[s_Page.Woman_Man][SELECT_GEM_POS]);
// 		}else if(SELECT_GEM_Y == 2){
// 			PaintPopup_Sharp(Character::s_ItemBag[SELECT_GEM_LIST_NOW_BAG][SELECT_GEM_LIST_NOW_SLOT]);
// 		}
	}
}

void PopupUi::Paint_MIX()		
{//GET_MAINQUEST_IDX()




		if(5 + SELECT_MIX_Y_SCROLL <= SELECT_MIX_SELECT){
			SELECT_MIX_Y_SCROLL = SELECT_MIX_SELECT - 4;
		}
		if(SELECT_MIX_Y_SCROLL > SELECT_MIX_SELECT){
			SELECT_MIX_Y_SCROLL--;
		}
		


	if(s_Page.Focus==0){
		const short *MIX_ID = 0;//�ּҰ� ����Ű�� ���� �����Ѵ�

		switch (MixNum){//���ռ� ��ȣ
			case 0:SELECT_MIX_SEX = SEX_WOMAN;MIX_ID = &MixBook_600[0][0];SELECT_MIX_MAX_NUM  = sizeof(MixBook_600)/(sizeof(short)*7);break;/*�ϱ� Ȱ ���ռ�*/
			case 1:SELECT_MIX_SEX = SEX_WOMAN;MIX_ID = &MixBook_601[0][0];SELECT_MIX_MAX_NUM  = sizeof(MixBook_601)/(sizeof(short)*7);break;/*�߱� Ȱ ���ռ�*/
			case 2:SELECT_MIX_SEX = SEX_WOMAN;MIX_ID = &MixBook_602[0][0];SELECT_MIX_MAX_NUM  = sizeof(MixBook_602)/(sizeof(short)*7);break;/*��� Ȱ ���ռ�*/
			case 3:SELECT_MIX_SEX = SEX_WOMAN;MIX_ID = &MixBook_603[0][0];SELECT_MIX_MAX_NUM  = sizeof(MixBook_603)/(sizeof(short)*7);break;/*��� Ȱ ���ռ�*/
		}

		MIX_ID += (SELECT_MIX_Y_SCROLL*7);//SELECT_MIX_Y_SCROLL�� ��ŭ ������ �̵�

		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_3_ITEMMIX_1, XPOS,YPOS,0);

		//���ռ� ���� 
		_SUTIL->pFont->setColor(0xfbab29);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[ITEM_MIX_0+MixNum], XPOS, YPOS-71, CGraphics::HCENTER);

		//���� ����Ʈ
		for (int xx = 0; xx<MIN(5,SELECT_MIX_MAX_NUM); xx++, MIX_ID+=7)
		{
			_SUTIL->pFont->setColor(0xffda00);//�������� �ִ�

			for(int yy = 1;yy<6;yy+=2){
				if(*(MIX_ID+yy) && GET_Count(*(MIX_ID+yy),SELECT_MIX_SEX) < *(MIX_ID+yy+1)){//�������� �ְ� �ش� �����۰����� 0�϶�
					_SUTIL->pFont->setColor(0x748799);//�������� ���ڸ���
				}
			}

			if(xx == SELECT_MIX_SELECT-SELECT_MIX_Y_SCROLL){//���� ������ �������� �����Ǹ� ���ۿ� �����صд�
				arraycopy((short*)MIX_ID, 0, (short*)MixBuffer, 0, 7);
			}

			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(*MIX_ID/100 , *MIX_ID%100)],XPOS-70, YPOS-53 + (13*xx), 0);
		}

		//Ŀ��
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_8, XPOS-77,YPOS-56+ (SELECT_MIX_SELECT-SELECT_MIX_Y_SCROLL)*13,0);

		//��ũ�ѹ�
		_SUTIL->g->SetColor(0xff6e00);
		if(SELECT_MIX_MAX_NUM > 5){//�ٰ� �پ�� �� 
			int Bar_height = MAX(30, (58 - (SELECT_MIX_MAX_NUM-5)*10) );
			int yy = ((58 - Bar_height)*SELECT_MIX_Y_SCROLL)/(SELECT_MIX_MAX_NUM-5);
			_SUTIL->g->FillRect( XPOS+74, YPOS-51+yy,2,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+74, YPOS-51,2,58);
		}

		//������ ���� �ؽ�Ʈ

	}else if(s_Page.Focus==1){//���� ���� ������
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_3_ITEMMIX_2, XPOS,YPOS,0);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(MixBuffer[0]/100 , MixBuffer[0]%100)],XPOS, YPOS-69, Graphics::HCENTER);

		ItemBag temp;
		_SUTIL->pFont->setColor(0xf8e6cb);


		_SUTIL->pFont->setColor(0xf8e6cb);//�������� �ִ�
		if(GET_Count(MixBuffer[1],SELECT_MIX_SEX) < MixBuffer[2])//�������� �ְ� �ش� �����۰����� 0�϶�
			_SUTIL->pFont->setColor(0xff0000);//�������� ���ڸ���

		temp.Data0 = MixBuffer[1];
		paint_ICON(temp,XPOS-63, YPOS-47,true);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(MixBuffer[1]/100 , MixBuffer[1]%100)],XPOS-40, YPOS-44, 0);//�ʿ� �����۸�
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NEEDNUM], XPOS+3, YPOS-28, 0);//�ʿ����
		_SUTIL->pFont->DrawText(_SUTIL->g, MixBuffer[2],XPOS+60, YPOS-28, Graphics::RIGHT);//����

		if(MixBuffer[3]){
			_SUTIL->pFont->setColor(0xf8e6cb);//�������� �ִ�
			if(GET_Count(MixBuffer[3],SELECT_MIX_SEX) < MixBuffer[4])//�������� �ְ� �ش� �����۰����� 0�϶�
				_SUTIL->pFont->setColor(0xff0000);//�������� ���ڸ���

			temp.Data0 = MixBuffer[3];
			paint_ICON(temp,XPOS-63, YPOS-11,true);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(MixBuffer[3]/100 , MixBuffer[3]%100)],XPOS-40, YPOS-8, 0);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NEEDNUM], XPOS+3, YPOS+8, 0);//�ʿ����
			_SUTIL->pFont->DrawText(_SUTIL->g, MixBuffer[4],XPOS+60, YPOS+8, Graphics::RIGHT);//����
		}

		if(MixBuffer[5]){
			_SUTIL->pFont->setColor(0xf8e6cb);//�������� �ִ�
			if(GET_Count(MixBuffer[5],SELECT_MIX_SEX) < MixBuffer[6])//�������� �ְ� �ش� �����۰����� 0�϶�
				_SUTIL->pFont->setColor(0xff0000);//�������� ���ڸ���

			temp.Data0 = MixBuffer[5];
			paint_ICON(temp,XPOS-63, YPOS+25,true);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(MixBuffer[5]/100 , MixBuffer[5]%100)],XPOS-40, YPOS+28, 0);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NEEDNUM], XPOS+3, YPOS+44, 0);//�ʿ����
			_SUTIL->pFont->DrawText(_SUTIL->g, MixBuffer[6],XPOS+60, YPOS+44, Graphics::RIGHT);//����
		}


		
		_SUTIL->pFont->setColor(0xf8e6cb);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MIX], XPOS-60, YPOS+66, 0);//����
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MAKENUM], XPOS-40, YPOS+66, 0);//����
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MIX], XPOS+34, YPOS+66, 0);//����

		_SUTIL->pFont->DrawText(_SUTIL->g, SELECT_MIX_MAKE_NUM,XPOS+1, YPOS+66, Graphics::HCENTER);//����


		switch(SELECT_MIX_POPUP_KIND){//�������� Ŭ���� ��ġ, �������� ���������� �ٸ� �˾��̶��

			case MIX_POPUP_QUESTION				://���տ��� ����
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_MIX_POPUP_YESNO, XPOS,YPOS-30,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);

				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q10], XPOS, YPOS-30+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
				break;

			case MIX_POPUP_NO_MATERIAL			://��� ����
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_MIX_POPUP_YESNO, XPOS,YPOS-30,0);//�˾� ������ ����

				_SUTIL->pFont->setColor(0xf8e6cb);

				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q11], XPOS, YPOS-30+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS-30+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS-30+37, CGraphics::HCENTER);
				break;

			case MIX_POPUP_NO_SPACE				://���� ��������
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS-30,0);//�˾� ������ ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+3,0);//�˾� ������ ��ư

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q5], XPOS, YPOS-15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+7, CGraphics::HCENTER);
				break;
		}
	}




}


void PopupUi::PaintPopup_Sharp(ItemBag _item)
{
	if(_item.ITEM_KIND == 0){return;}
	int posX = s_Popup_Sharp.posX-2; 
	int posY = s_Popup_Sharp.posY+1;

#define START_X	6
#define START_Y	8
#define GAP_Y	13
#define WIDTH	118
#define HEIGHT	70

	if(posX + WIDTH > SCREEN_WIDTH){//��ũ�� ������ ����ٸ�
		posX-= (posX + WIDTH)-SCREEN_WIDTH;
	}
	if(posY + HEIGHT > SCREEN_HEIGHT){//��ũ�� ������ ����ٸ� 
		posY-= HEIGHT;
	}else{
		posY+=15;
	}



	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_6, posX,posY,0);//������ ������

	int head =		_item.ITEM_HEADTEXT;
	int upgrade =	_item.ITEM_UPGRADE;
	int socket1 =	_item.ITEM_SOCKET_1;
	int socket2 =	_item.ITEM_SOCKET_2;
	int socket3 =	_item.ITEM_SOCKET_3;
	char str[31];//int �ִ�ũ��



	switch(_item.ITEM_KIND){//������ ������ ��ȭ
		case ITEM_BAG	:
			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "%d SLOT",8);break;
				case 1:SPRINTF(str, "%d SLOT",16);break;
				case 2:SPRINTF(str, "%d SLOT",24);break;
				case 3:SPRINTF(str, "%d SLOT",32);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//��ũ�ѹ�
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;

		case ITEM_POTION:

			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "Hp + %d%",15);break;
				case 1:SPRINTF(str, "Hp + %d%",40);break;
				case 2:SPRINTF(str, "Hp + %d%",65);break;

				case 3:SPRINTF(str, "Mp + %d%",5);break;
				case 4:SPRINTF(str, "Mp + %d%",15);break;
				case 5:SPRINTF(str, "Mp + %d%",20);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//��ũ�ѹ�
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;
		case ITEM_MAINQUEST:
			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//������ ����
			SPRINTF(str, "Quest Item",15);
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//��ũ�ѹ�
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;

		default://����
			s_Popup_Sharp.LineMAX = 1;
			if(s_Popup_Sharp.Line == 0){
				//������ ����
				switch(_item.ITEM_GRADE){
					case 0:_SUTIL->pFont->setColor(0xffffff);break;
					case 1:_SUTIL->pFont->setColor(0x72fa28);break;
					case 2:_SUTIL->pFont->setColor(0x52c4ff);break;
					case 3:_SUTIL->pFont->setColor(0x916aff);break;
					case 4:_SUTIL->pFont->setColor(0xff6c32);break;
				}


				//������ �̸�

				if(upgrade){
					SPRINTF(str, "%s %s %s%d",
						(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
						(char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)],				"+",				upgrade); 	
				}else{
					SPRINTF(str, "%s %s",
						(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
						(char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)]); 	
				}
				_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y, 0);

				//���
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_G_NORMAL + _item.ITEM_GRADE], posX+START_X, posY+START_Y+GAP_Y, 0);

				


				

				//����
				_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_WOMEN + _item.ITEM_SEX], posX+START_X + 40, posY+START_Y+GAP_Y, 0);

				//���� ����
				_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
				SPRINTF(str, "%s%d", "Lv",
					(((_item.ITEM_KIND) == ITEM_NECK)||((_item.ITEM_KIND) == ITEM_RING)? deco_Table[_item.ITEM_INDEX][D_T_LV]: equip_Table[_item.ITEM_INDEX][E_T_LV])); 	
				_SUTIL->pFont->DrawText(_SUTIL->g, str,posX+START_X+95, posY+START_Y+GAP_Y, Graphics::RIGHT);


				

				//ATT DEF
				switch(_item.ITEM_KIND){//������ ������ ��ȭ
					case ITEM_SWORD	:
						SPRINTF(str, "ATT %d ~ %d",
							equip_Table[_item.ITEM_INDEX][E_T_SW_MIN],
							equip_Table[_item.ITEM_INDEX][E_T_SW_MAX]);
						break;													 
// 					case ITEM_AXE	:											 
// 						SPRINTF(str, "ATT %d ~ %d",
// 							equip_Table[_item.ITEM_INDEX][E_T_AX_MIN],
// 							equip_Table[_item.ITEM_INDEX][E_T_AX_MAX]);
// 						break;													 
					case ITEM_GUN	:											 
						SPRINTF(str, "ATT %d ~ %d",
							equip_Table[_item.ITEM_INDEX][E_T_GU_MIN],
							equip_Table[_item.ITEM_INDEX][E_T_GU_MAX]);
						break;													 
// 					case ITEM_OEB	:											 
// 						SPRINTF(str, "ATT %d ~ %d",
// 							equip_Table[_item.ITEM_INDEX][E_T_OR_MIN],
// 							equip_Table[_item.ITEM_INDEX][E_T_OR_MAX]);
// 						break;


					case ITEM_HEAD	:
						SPRINTF(str, "DEF %d",equip_Table[_item.ITEM_INDEX][E_T_HE]);
						break;
					case ITEM_CHEST	:
						SPRINTF(str, "DEF %d",equip_Table[_item.ITEM_INDEX][E_T_CH]);
						break;
					case ITEM_LEG	:
						SPRINTF(str, "DEF %d",equip_Table[_item.ITEM_INDEX][E_T_LE]);
						break;
					case ITEM_GLOVE	:
						SPRINTF(str, "DEF %d",equip_Table[_item.ITEM_INDEX][E_T_GL]);
						break;


					case ITEM_NECK	:
						SPRINTF(str, "DEF %d",deco_Table[_item.ITEM_INDEX][D_T_NE_DE]);
						break;
					case ITEM_RING	:
						SPRINTF(str, "ATT %d  DEF %d",deco_Table[_item.ITEM_INDEX][D_T_RI_AT],deco_Table[_item.ITEM_INDEX][D_T_RI_DE]);
						break;
				}
				_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y*2, 0);

				//�ɷ�ġ
				int scroll_Kind = (_item.Data2/100)%100; //��ũ�� ����
				if(scroll_Kind){
					int UP = (((_item.Data2/10000) %1000) /3) +1; //��ũ�� ���ġ
					switch(scroll_Kind){//��ũ�� ����
						case 1:SPRINTF(str, "STR+%d DEX+%d",UP,UP);break;
						case 2:SPRINTF(str, "STR+%d CON+%d",UP,UP);break;
						case 3:SPRINTF(str, "STR+%d INT+%d",UP,UP);break;
						case 4:SPRINTF(str, "DEX+%d CON+%d",UP,UP);break;
						case 5:SPRINTF(str, "DEX+%d INT+%d",UP,UP);break;
						case 6:SPRINTF(str, "CON+%d INT+%d",UP,UP);break;
						case 7:	SPRINTF(str, "STR+%d",UP*4/3+1);break;
						case 8:	SPRINTF(str, "DEX+%d",UP*4/3+1);break;
						case 9:	SPRINTF(str, "CON+%d",UP*4/3+1);break;
						case 10:SPRINTF(str, "INT+%d",UP*4/3+1);break;
						case 11:SPRINTF(str, "ALL+%d",MAX(1,UP/2));break;
					}
					_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y*3, 0);
				}

				//��ũ�ѹ�
				_SUTIL->g->SetColor(0x76aebf);
				_SUTIL->g->FillRect( posX+109, posY+16,5,15);
			}else{
				int Line_Y = 0;

				//���� ������

				


				if(socket1){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//�����̹���
					Line_Y+=17;
				}else{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO_SOCKET], posX+START_X, posY+START_Y+Line_Y, 0);
				}
				if(socket2){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//�����̹���
					Line_Y+=17;
				}else{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO_SOCKET], posX+START_X, posY+START_Y+Line_Y, 0);
				}
				if(socket3){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//�����̹���
					Line_Y+=17;
				}else{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO_SOCKET], posX+START_X, posY+START_Y+Line_Y, 0);
				}
					
		
				//��ũ�ѹ�
				_SUTIL->g->SetColor(0x76aebf);
				_SUTIL->g->FillRect( posX+109, posY+16+15,5,15);


			}

			

			



			
			break;

	}

	////��ũ�ѹ�
	//_SUTIL->g->SetColor(0xff6e00);
	//if(s_Quest.Max_Num > 5){//�ٰ� �پ�� ��
	//	int Bar_height = MAX(15, (30 - (s_Quest.Max_Num-5)*5) );
	//	int yy = ((30 - Bar_height)*SELECT_QUEST_SUB_Y)/(s_Quest.Max_Num-5);
	//	_SUTIL->g->FillRect( XPOS+109, YPOS+19+yy,5,Bar_height);			
	//}else{
	//	_SUTIL->g->SetColor(0xff6e00);
	//	_SUTIL->g->FillRect( XPOS+109, YPOS+16,5,30);
	//}

}

void PopupUi::PaintPopup_Sharp(int Skill_Num)
{
	if(Skill_Num < 0){return;}

	int posX = s_Popup_Sharp.posX-2; 
	int posY = s_Popup_Sharp.posY+1;

#define START_X	6
#define START_Y	8
#define GAP_Y	13
#define WIDTH	118
#define HEIGHT	70

	if(posX + WIDTH > SCREEN_WIDTH){//��ũ�� ������ ����ٸ�
		posX-= (posX + WIDTH)-SCREEN_WIDTH;
	}
	if(posY + HEIGHT > SCREEN_HEIGHT){//��ũ�� ������ ����ٸ� 
		posY-= HEIGHT+2;
	}else{
		posY+=15;
	}



	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_6, posX,posY,0);//������ ������



	char str[600];//int �ִ�ũ��
	int Line_Max = 0;


	//�ؽ�Ʈ�� ���ļ� ���ٷ� �̾Ƴ���
	if(Skill_Num<SKILL_P_W_CriUp){//��Ƽ�� ��ų

		int Skill_Lv = Character::s_Skill.Level_A[Skill_Num];//��ų ����

		SPRINTF(str, "%s LV%d||%s|ATT +%d%s|%s %d|%s %d",
			(char*)pCLRPOPUP_Text->nText[CLRMENU_SKILL_S_1 + (Skill_Num*2)],
			Skill_Lv,
			(char*)pCLRPOPUP_Text->nText[CLRMENU_SKILL_S_1 + (Skill_Num*2)+1],
			a_Skill_Table[Skill_Num * 10 + (Skill_Lv-1)][0],
			(char*)"%",
			(char*)pCLRPOPUP_Text->nText[CLRMENU_USEMANA],
			a_Skill_Table[Skill_Num * 10 + (Skill_Lv-1)][4],
			(char*)pCLRPOPUP_Text->nText[CLRMENU_COOLTIME],
			a_Skill_Table[Skill_Num * 10 + (Skill_Lv-1)][2]); 	


		_SUTIL->pFont->Dry_Wrap_Width(100);
		_SUTIL->pFont->Dry_StartLine_Max(s_Popup_Sharp.Line,5);

		_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
		s_Popup_Sharp.LineMAX = _SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y, 0) - 5;

	}else{//�нú� ��ų
		Skill_Num -= SKILL_P_W_CriUp;

		int Skill_Lv = Character::s_Skill.Level_P[Skill_Num];//��ų ����

		SPRINTF(str, "%s LV%d||%s",
			(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (Skill_Num*2)],
			Skill_Lv,
			(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (Skill_Num*2)+1]); 	


		_SUTIL->pFont->Dry_Wrap_Width(100);
		_SUTIL->pFont->Dry_StartLine_Max(s_Popup_Sharp.Line,5);

		_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
		char Num[10];//int �ִ�ũ��
		SPRINTF(Num, "%d",a_Passive_Table[Skill_Num*5 + (Skill_Lv-1)][0]); 	
		s_Popup_Sharp.LineMAX = _SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y, 0,Num ) - 5;


	}

	


	//��ũ�ѹ�
	_SUTIL->g->SetColor(0xff6e00);
	if(s_Popup_Sharp.LineMAX > 0){//�ٰ� �پ�� ��
		int Bar_height = MAX(15, (30 - (s_Popup_Sharp.LineMAX)*5) );
		int yy = ((30 - Bar_height)*s_Popup_Sharp.Line)/(s_Popup_Sharp.LineMAX);
		_SUTIL->g->FillRect( posX+109, posY+16+yy,5,Bar_height);			
	}else{
		_SUTIL->g->SetColor(0xff6e00);
		_SUTIL->g->FillRect( posX+109, posY+16,5,30);
	}

}


void PopupUi::PaintNumber(ASprite* pAsIns, int numImgIdx, int value, int x, int y, int gap , int position)
{
    int FullSpace = 0;//������ �ڸ���
	int wordsize = pAsIns->GetModuleWidth(numImgIdx);//1���� ��
	int decimal =0;//�ڸ���
	int tmpcount = value;

	for(int xx = 0;xx<20 ;xx++)
	{//�ڸ��� ���ϱ�
		decimal ++;
		tmpcount /= 10;
		if(0 >= tmpcount) break;
	}

	FullSpace = wordsize*decimal + gap*(decimal-1); // width 


	//tmpcount = value;

	if(position & CGraphics::RIGHT)
		x -= wordsize;
	else if(position & CGraphics::HCENTER)
		x += (FullSpace/2-wordsize);
	else
		x += (FullSpace-wordsize);

	for(int xx = 0;xx<decimal ;xx++,value/=10)
	{//���ڱ׸���
		SUTIL_Paint_Module(pAsIns,numImgIdx + (value%10),x - xx*(wordsize+gap),y,0,position & (CGraphics::TOP|CGraphics::VCENTER|CGraphics::BOTTOM))	;//���ڸ����� �ϳ��� �׷��ش�
	}

}

void PopupUi::PaintGage(int gageType, int gagewidth,int gageheight, int x, int y, int nowvalue, int maxvalue)
//--------------------------------------------------------------------------
{
	if(nowvalue>maxvalue){nowvalue = maxvalue;}
	int color[4];
	switch(gageType)
	{
	case GAGE_RED:
		{
			color[0] = 0xFD0305;
			color[1] = 0xBC0F0D;
			color[2] = 0x6A352E;
			color[3] = 0x361012;
			break;
		}
	case GAGE_BLUE:
		{
			color[0] = 0x00B1FF;
			color[1] = 0x0A8CCC;
			color[2] = 0x1D586B;
			color[3] = 0x033A40;
			break;
		}
	case GAGE_YELLOW:
		{
			color[0] = 0xFFDA02;
			color[1] = 0xF9A51F;
			color[2] = 0x3F4545;
			color[3] = 0x22292E;
			break;
		}
	case GAGE_GREEN:
		{
			color[0] = 0x00FFB1;
			color[1] = 0x0ACC8C;
			color[2] = 0x1D6B58;
			color[3] = 0x03403A;
			break;
		}
	}
	if(maxvalue){
		int curgage = ((nowvalue*gagewidth)/maxvalue);

		//	yellow gage(remain hp)
		SUTIL_SetColor(color[0]);
		SUTIL_FillRect(x, y, (curgage), (gageheight-1));
		SUTIL_SetColor(color[1]);
		SUTIL_FillRect(x, y+(gageheight-1), (curgage), 1);

		//	max gage(max hp)
		SUTIL_SetColor(color[2]);
		SUTIL_FillRect(x+curgage, y, (gagewidth-curgage), 1);
		SUTIL_SetColor(color[3]);
		SUTIL_FillRect(x+curgage, y+1, (gagewidth-curgage), (gageheight-1));
	}
}



int PopupUi::itemICON(struct ItemBag _item)
{//������ �������� �ѷ��ٶ�
	switch(_item.ITEM_KIND)
	{//������ ������ ��ȭ
		case ITEM_BAG		:return MODULE_ITEM_BAG_00+(_item.ITEM_INDEX);
		case ITEM_POTION	:return MODULE_ITEM_HP_00+(_item.ITEM_INDEX);
		case ITEM_MONEY		:return MODULE_ITEM_MONEY;
		case ITEM_MIX_BOOK	:return MODULE_ITEM_RECIPE;
		case ITEM_UP_STONE	:return MODULE_ITEM_UPSTONE_00+(_item.ITEM_INDEX);
		case ITEM_GEM_STONE	:return MODULE_ITEM_JEWEL_EARTH_00+(_item.ITEM_INDEX);


		case ITEM_SWORD		:return MODULE_ITEM_BOW_00/*MODULE_ITEM_SWORD_00*/+((_item.ITEM_INDEX)/5);
//		case ITEM_AXE		:return MODULE_ITEM_AXE_00+((_item.ITEM_INDEX)/5);
		case ITEM_GUN		:return MODULE_ITEM_CLAW_00/*MODULE_ITEM_GUN_00*/+((_item.ITEM_INDEX)/5);
//		case ITEM_OEB		:return MODULE_ITEM_ORB_00+((_item.ITEM_INDEX)/5);
		case ITEM_HEAD		:return MODULE_ITEM_HAT_00+((_item.ITEM_INDEX)/5);
		case ITEM_CHEST		:return MODULE_ITEM_JACKET_00+((_item.ITEM_INDEX)/5);
		case ITEM_LEG		:return MODULE_ITEM_PANTS_00+((_item.ITEM_INDEX)/5);
		case ITEM_GLOVE		:return MODULE_ITEM_GLOBE_00+((_item.ITEM_INDEX)/5);
		case ITEM_NECK		:return MODULE_ITEM_NECKLACE_00+((_item.ITEM_INDEX)/5);
		case ITEM_RING		:return MODULE_ITEM_RING_00+((_item.ITEM_INDEX)/5);
		case ITEM_MAINQUEST	:
			switch(_item.ITEM_ID){
				case ITEM_CALL_crystal:
					return MODULE_ITEM_SPIRITSTONE_05;//�ڼ���
				case ITEM_CALL_diary:
					return MODULE_ITEM_SKILLBOOK_01;//����
				default:
					return MODULE_ITEM_QUESTITEM;
			}
	}
	return 0;
}

int PopupUi::itemNAME(int m_Kind, int m_Index)
{//������ �̸��� �ѷ��ٶ�
	
		switch(m_Kind)
		{//������ ������ ��ȭ
			case ITEM_BAG	:return ITEM_BAG_0+m_Index;
			case ITEM_POTION:return ITEM_POTION_0+m_Index;
			case ITEM_MONEY		:return ITEM_GOLD;
			case ITEM_MIX_BOOK	:return ITEM_MIX_0+m_Index;
			case ITEM_UP_STONE	:return ITEM_UP_STONE_0+m_Index;
			case ITEM_GEM_STONE	:return ITEM_GEM_STONE_0+m_Index;

			case ITEM_SWORD	:return ITEM_SWORD_0+m_Index;
//			case ITEM_AXE	:return ITEM_AXE_0+m_Index;
			case ITEM_GUN	:return ITEM_GUN_0+m_Index;
//			case ITEM_OEB	:return ITEM_ORB_0+m_Index;
			case ITEM_HEAD	:return Character::Check_sex(ITEM_W_HEAD_0,ITEM_M_HEAD_0)+m_Index;
			case ITEM_CHEST	:return Character::Check_sex(ITEM_W_CHEST_0,ITEM_M_CHEST_0)+m_Index;
			case ITEM_LEG	:return Character::Check_sex(ITEM_W_LEG_0,ITEM_M_LEG_0)+m_Index;
			case ITEM_GLOVE	:return Character::Check_sex(ITEM_W_GLOVES_0,ITEM_M_GLOVES_0)+m_Index;
			case ITEM_NECK	:return ITEM_NECKLACE_0+m_Index;
			case ITEM_RING	:return ITEM_RING_0+m_Index;


			case ITEM_MAINQUEST	:return ITEM_MAINQUEST_0+m_Index;
		}

	/*if(returnType == ITEM_RETURN_GRADE){}
	if(returnType == ITEM_RETURN_prefix){}
	if(returnType == ITEM_RETURN_TEXT){}
	if(returnType == ITEM_RETURN_TEXT){}*/


	return 0;

}
void PopupUi::itemTEXT(struct ItemBag _item,int L1,int L2,int L3,int L4)
{//������ �̸��� �ѷ��ٶ�



	char str[31];//int �ִ�ũ��
	


	switch(_item.ITEM_KIND){//������ ������ ��ȭ
		case ITEM_BAG	:
			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+L1, 0);

			//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "%d SLOT",8);break;
				case 1:SPRINTF(str, "%d SLOT",16);break;
				case 2:SPRINTF(str, "%d SLOT",24);break;
				case 3:SPRINTF(str, "%d SLOT",32);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-74, YPOS+L3, 0);
			break;

		case ITEM_POTION:

		//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-74, YPOS+L1, 0);

		//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "Hp + %d%",15);break;
				case 1:SPRINTF(str, "Hp + %d%",40);break;
				case 2:SPRINTF(str, "Hp + %d%",65);break;

				case 3:SPRINTF(str, "Mp + %d%",5);break;
				case 4:SPRINTF(str, "Mp + %d%",15);break;
				case 5:SPRINTF(str, "Mp + %d%",20);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-74, YPOS+L3, 0);
			break;

		case ITEM_MIX_BOOK:

		//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-74, YPOS+L1, 0);
			break;
		case ITEM_UP_STONE:

			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-74, YPOS+L1, 0);
			break;
		case ITEM_GEM_STONE:

			//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-74, YPOS+L1, 0);

			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)" ", XPOS-74 -9, YPOS+L2, 0);
			if(gem_Table[_item.ITEM_INDEX][G_T_E_DDANG	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_GEM_0			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_E_DDANG]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_E_DDANG	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_E_MUL	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_GEM_1			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_E_MUL  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_E_MUL	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_E_BUL	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_GEM_2			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_E_BUL  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_E_BUL	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_E_BARAM	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_GEM_3			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_E_BARAM]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_E_BARAM	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_A_CON	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_STAMINA		], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_A_CON  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_A_CON	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_A_INT	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_INTELLIGENCE	], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_A_INT  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_A_INT	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_A_STR	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_POWER			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_A_STR  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_A_STR	], 0);}
			if(gem_Table[_item.ITEM_INDEX][G_T_A_DEX	]){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_AGILE			], 9);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(gem_Table[_item.ITEM_INDEX][G_T_A_DEX  ]>0?"+":""), 3);	_SUTIL->pFont->DrawText(_SUTIL->g, gem_Table[_item.ITEM_INDEX][G_T_A_DEX	], 0);}


			break;

		case ITEM_MAINQUEST:
			//������ �̸�
			_SUTIL->pFont->setColor(0xffaaaa);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-74, YPOS+L1, 0);

			break;

		default:{//����
			int head =		_item.ITEM_HEADTEXT;
			int upgrade =	_item.ITEM_UPGRADE;
			int socket1 =	_item.ITEM_SOCKET_1;
			int socket2 =	_item.ITEM_SOCKET_2;
			int socket3 =	_item.ITEM_SOCKET_3;

		//������ ����
			switch(_item.ITEM_GRADE){
				case 0:_SUTIL->pFont->setColor(0xffffff);break;
				case 1:_SUTIL->pFont->setColor(0x72fa28);break;
				case 2:_SUTIL->pFont->setColor(0x52c4ff);break;
				case 3:_SUTIL->pFont->setColor(0x916aff);break;
				case 4:_SUTIL->pFont->setColor(0xff6c32);break;
			}


		//������ �̸�
			
			if(upgrade){
				SPRINTF(str, "%s %s %s%d",
					(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
					(char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)],	"+",	upgrade); 	
			}else{
				SPRINTF(str, "%s %s",
					(head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+head]:""),
					(char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)]); 	
			}
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-74, YPOS+L1, 0);
			

		//����
			if(socket1 + socket2 + socket3){
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,
					FRAME_UI_UI_3_1SOCKET + (socket2?(socket3?2:1):0)
					, XPOS,YPOS+L1-20,0);//������ �ִٸ� �׷��ش�
			}

			for(int xx = 0;xx<3;xx++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.
				int slot;
				switch(xx){//�󽽷�
					case 0:slot = _item.ITEM_SOCKET_3;break;
					case 1:slot = _item.ITEM_SOCKET_2;break;
					case 2:slot = _item.ITEM_SOCKET_1;break;
				}
				if(slot > 1){
					SUTIL_Paint_Module(s_ASpriteSet->pItemAs,MODULE_ITEM_JEWEL_EARTH_00 + slot -2,XPOS+30 + 16 * xx, YPOS+L1-3,0,0);
				}
			}




		//���� ����
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			SPRINTF(str, "%s %d",
				"Lv",
				(((_item.ITEM_KIND) == ITEM_NECK)||((_item.ITEM_KIND) == ITEM_RING)? deco_Table[_item.ITEM_INDEX][D_T_LV]: equip_Table[_item.ITEM_INDEX][E_T_LV])); 	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-74, YPOS+L2, 0);


		//���� 
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_WOMEN + _item.ITEM_SEX],XPOS+75, YPOS+L2, CGraphics::RIGHT);


		//ATT DEF
			ItemAbility Temp_Abil;//���� �������� �ɷ�
			Set_Item(&Temp_Abil,&_item);
			switch(_item.ITEM_KIND){//������ ������ ��ȭ
				case ITEM_SWORD	:
				case ITEM_GUN	:											 
					SPRINTF(str, "ATT %d ~ %d",Temp_Abil.ATT_MIN,Temp_Abil.ATT_MAX);
					break;		

				case ITEM_HEAD	:
				case ITEM_CHEST	:
				case ITEM_LEG	:
				case ITEM_GLOVE	:
				case ITEM_NECK	:
					SPRINTF(str, "DEF %d",Temp_Abil.DEF);
					break;
				
				case ITEM_RING	:
					SPRINTF(str, "ATT %d  DEF %d",Temp_Abil.ATT_MAX,Temp_Abil.DEF);
					break;
			}
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-74, YPOS+L3, 0);

		//�ɷ�ġ
			
				_SUTIL->pFont->DrawText(_SUTIL->g, "", XPOS-74-9, YPOS+L4, 0);
				if(Temp_Abil.STR){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_POWER			], 6);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(Temp_Abil.STR>0?"+":""), 0);	_SUTIL->pFont->DrawText(_SUTIL->g, Temp_Abil.STR, 0);}
				if(Temp_Abil.DEX){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_AGILE			], 6);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(Temp_Abil.DEX>0?"+":""), 0);	_SUTIL->pFont->DrawText(_SUTIL->g, Temp_Abil.DEX, 0);}
				if(Temp_Abil.CON){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_STAMINA		], 6);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(Temp_Abil.CON>0?"+":""), 0);	_SUTIL->pFont->DrawText(_SUTIL->g, Temp_Abil.CON, 0);}
				if(Temp_Abil.INT){	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_INTELLIGENCE	], 6);	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)(Temp_Abil.INT>0?"+":""), 0);	_SUTIL->pFont->DrawText(_SUTIL->g, Temp_Abil.INT, 0);}


			

		//����
			//SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_INFO, XPOS+44,YPOS+83,0,0);


		}
		break;
			
	}

	

}




void PopupUi::USE_item(struct ItemBag *_item){//������ ���

	switch(_item->ITEM_KIND){
		case ITEM_POTION:{//����

			int xx = _item->Data1%100 -1;
			if(xx < 0) xx = 0;

			_item->Data1 = 
				(_item->Data1/100) *100 + xx;


			if(_item->Data1%100<1){
				Del_Item(_item);
// 				Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]=-1;
// 				Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]=-1;
			}

			switch(_item->ITEM_INDEX){
				case 0://�ҹ���
					Character::s_Status[Character::s_HeroTag.SEX].LIFE += PER(Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX,15);
					break;
				case 1://�߹���
					Character::s_Status[Character::s_HeroTag.SEX].LIFE += PER(Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX,40);
					break;
				case 2://�빰��
					Character::s_Status[Character::s_HeroTag.SEX].LIFE += PER(Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX,65);
					break;
				case 3://�Ҹ���
					Character::s_Status[Character::s_HeroTag.SEX].MANA += PER(Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX,5);
					break;
				case 4://�߸���
					Character::s_Status[Character::s_HeroTag.SEX].MANA += PER(Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX,15);
					break;
				case 5://�븶��
					Character::s_Status[Character::s_HeroTag.SEX].MANA += PER(Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX,20);
					break;
			}
			if(Character::s_Status[Character::s_HeroTag.SEX].LIFE>Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX)Character::s_Status[Character::s_HeroTag.SEX].LIFE=Character::s_Status[Character::s_HeroTag.SEX].LIFE_MAX;
			if(Character::s_Status[Character::s_HeroTag.SEX].MANA>Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX)Character::s_Status[Character::s_HeroTag.SEX].MANA=Character::s_Status[Character::s_HeroTag.SEX].MANA_MAX;
			}break;
		case ITEM_MIX_BOOK:
			Page_init();
			switch(_item->ITEM_INDEX){
				case 0://�ϱ� Ȱ ���ռ�
					MixOpen=true;
					MixNum=0;
					break;
				case 1://�߱� Ȱ ���ռ�
					MixOpen=true;
					MixNum=1;
					break;
				case 2://��� Ȱ ���ռ�
					MixOpen=true;
					MixNum=2;
					break;
				case 3://��� Ȱ ���ռ�
					MixOpen=true;
					MixNum=3;
					break;
			}
			break;
		case ITEM_SWORD	:
		case ITEM_GUN	:
		case ITEM_HEAD	:
		case ITEM_CHEST	:
		case ITEM_LEG	:
		case ITEM_GLOVE	:
		case ITEM_NECK	:
		case ITEM_RING	:
			int xx = SELECT_INVENTORY_BAG;
			int yy = SELECT_INVENTORY_INSIDE;

			Page_init();
			GemOpen=true;

			SELECT_GEM_ITEM_BAG = xx;
			SELECT_GEM_ITEM_SLOT = yy;
			break;
	}

}
void PopupUi::QSLOT_item(struct ItemBag *_item,int slot){//������
	if(_item->ITEM_EQUIP){// �̹� ����� �������̸� ���������ʴ´�
		return;
	}


		for(int xx = 0;xx<4;xx++){//��� �κ��� ���鼭 ������ Equip��� ã�� Ǯ���ش�
			for(int yy = 0;yy<32;yy++){
				if(Character::s_ItemBag[xx][yy].ITEM_EQUIP){//����� �߿�
					switch(Character::s_ItemBag[xx][yy].ITEM_KIND){//���������� ������Ų��
						case ITEM_POTION://����
							Character::s_ItemBag[xx][yy].Data0 %= 10000000;//�������
							xx = 4;yy = 32;//��Ż
							break;
					}
				}
			}
		}

	//switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//������ ������ ��ȭ
	//							case ITEM_POTION:

	_item->Data0  = (_item->Data0 %= 10000000) + 10000000*(slot+1);
	Character::s_Potion_Tag.Qslot[slot][0] = SELECT_INVENTORY_BAG;
	Character::s_Potion_Tag.Qslot[slot][1] = SELECT_INVENTORY_INSIDE;
}

void PopupUi::QSLOT_find(){//������

	Character::s_Potion_Tag.Qslot[0][0]=-1;
	Character::s_Potion_Tag.Qslot[0][1]=-1;
	Character::s_Potion_Tag.Qslot[1][0]=-1;
	Character::s_Potion_Tag.Qslot[1][1]=-1;

	for(int xx = 0;xx<4;xx++){//��� �κ��� ���鼭 ������ Equip��� ã�� Ǯ���ش�
		for(int yy = 0;yy<32;yy++){
			if(Character::s_ItemBag[xx][yy].ITEM_EQUIP){//����� �߿�
				int slot = Character::s_ItemBag[xx][yy].ITEM_EQUIP -1;
				switch(Character::s_ItemBag[xx][yy].ITEM_KIND){//�������� ��ġ�� �����Ѵ�
						case ITEM_POTION://����
							Character::s_Potion_Tag.Qslot[slot][0]=xx;
							Character::s_Potion_Tag.Qslot[slot][1]=yy;
							break;;
				}
			}
		}
	}
	

}

void PopupUi::EQUIP_item(int slot,struct ItemBag *_item){

	int Sex = _item->ITEM_SEX;

	if(_item->ITEM_EQUIP){// �̹� ����� �������̸� ��� �����Ѵ�
		_item->Data0 %= 10000000;//�������
		//���� ��� ��� ����
		Del_Slot(Sex,slot);
	}else{
		if(Character::s_ItemEquip[Sex][slot].ITEM_EQUIP){//���� �ؾ��� ���Կ� �������� �̹������Ѵٸ�
			for(int xx = 0;xx<4;xx++){//��� �κ��� ���鼭 ������ Equip��� ã�� Ǯ���ش�
				for(int yy = 0;yy<32;yy++){
					if(Character::s_ItemEquip[Sex][slot].Data0 ==  Character::s_ItemBag[xx][yy].Data0 && Character::s_ItemEquip[Sex][slot].Data1 ==  Character::s_ItemBag[xx][yy].Data1){//ID, ������ ������ �������߿� - ���� �迭
						Character::s_ItemBag[xx][yy].Data0 %= 10000000;//�������
						xx = 4;yy = 32;//��Ż
						//���� ��� ��� ����
						Del_Slot(Sex,slot);
						//}
					}
				}
			}
		}
		_item->Data0 = (_item->Data0 %= 10000000) + 10000000*(slot+1);
		Character::s_ItemEquip[Sex][slot] = *_item;
		Set_Item(&Character::s_ItemAbil[Sex][slot],&Character::s_ItemEquip[Sex][slot]);
	}

	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���



	int index = _item->ITEM_INDEX;
	int HeadText = 0;
	HeadText = head_Table[_item->ITEM_HEADTEXT][H_T_COSUME];

	SUTIL_LoadAspritePack(PACK_SPRITE_COSTUME);//�ѿ���
	switch(slot){
		case 0:Character::ChangeCostume(Character::_spr_Hero_W,PAL_HEAD	,(HeadText?HeadText:costume_Table[index][C_T_HE]),_item->ITEM_GRADE); break;
		case 3:Character::ChangeCostume(Character::_spr_Hero_W,PAL_BODY	,(HeadText?HeadText:costume_Table[index][C_T_CH]),_item->ITEM_GRADE); break;
		case 4:Character::ChangeCostume(Character::_spr_Hero_W,PAL_ARM	,(HeadText?HeadText:costume_Table[index][C_T_LE]),_item->ITEM_GRADE); break;
		case 7:Character::ChangeCostume(Character::_spr_Hero_W,PAL_LEG	,(HeadText?HeadText:costume_Table[index][C_T_GL]),_item->ITEM_GRADE); break;

		//case 5:Character::ChangeCostume(PAL_KNIFE2	,costume_Table[index][SW_AX]/10+Axe,costume_Table[index][SW_AX]%10);break;
		//case 6:Character::ChangeCostume(PAL_CLAW	,costume_Table[index][SW_AX]/10+Axe,costume_Table[index][SW_AX]%10);break;
		case 8:Character::ChangeCostume(Character::_spr_Hero_W,PAL_BOW	,costume_Table[index][C_T_GU]/10,costume_Table[index][C_T_GU]%10);break;
		//case 9:Character::ChangeCostume(PAL_ORB		,costume_Table[index][C_T_OR]/10,costume_Table[index][C_T_OR]%10);break;
	}
	SUTIL_ReleaseAspritePack();//�Ѵݱ�

}//������ ����
void PopupUi::DEL_item(){//������ ������
	if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_EQUIP){// �̹� ����� �������̸� ���������ʴ´�
		s_Page.Focus = 2;
		SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__EQUIPDEL;
		return;
	}


	if(s_Page.Focus != 2){
		s_Page.Focus = 2;
		SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__ABANDON;
	}else{
		Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data0 = 0;
		Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1 = 0;
		Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data2 = 0;
		s_Page.Focus = 0;
	}
}
void PopupUi::MOVE_item(){//������ �̵� �� ��ġ��

	if(s_Page.Focus == 1 && SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){//������ �ٲܶ�

		int targetBag = get_BagMax(Character::s_ItemSlot[SELECT_INVENTORY_BAG]);
		int cursorBag = get_BagMax(Character::s_ItemPick);

		if(targetBag > cursorBag){//��ü�� ������ �� ���� �����̶�� 
			int Bag_interNum = 0;
			for(int xx = 0;xx<targetBag;xx++)//������ ����üũ
				if(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx].Data0)
					Bag_interNum++;//��ĭ�� �ƴϸ� ������ ���� ����


			if(Bag_interNum > cursorBag){//���� ������ ������������ ������ �� ���ٸ�
				//��� �˾�â
				s_Page.Focus = 2;//������ ��������ʽ��ϴ� ���â �߱�
				SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__NOT_ENOUGH;
				return;
			}else if(Bag_interNum == cursorBag){//������ ��üĭ�� �� �´ٸ� �ٸ����濡 �󽽷��� �����ϴ��� �˻��ؾ��Ѵ�
				bool freeSlot = false;

				for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������� ã�Ƴ���
					if(SELECT_INVENTORY_BAG != xx){
						switch(Character::s_ItemSlot[xx].Data0){
							case 100:MaxSlot= 8;break;
							case 101:MaxSlot= 16;break;
							case 102:MaxSlot= 24;break;
							case 103:MaxSlot= 32;break;
							default:MaxSlot= 0;break;
						}
						for(int yy = 0;yy<MaxSlot;yy++){
							if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//����ִ½����� ������
								freeSlot = true;
							}
						}
					}
				}

				if(freeSlot){
					SORTING_bag(SELECT_INVENTORY_BAG);
					QSLOT_find();//������ ��ġ�� �ٲ�����Ƿ� �簻���Ѵ�
				}else{
					//��� �˾�â
					s_Page.Focus = 2;//������ ��������ʽ��ϴ� ���â �߱�
					SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__NOT_ENOUGH;
					return;
				}

			}else{//���� �����ϴٸ� �������� ������ ����
				SORTING_bag(SELECT_INVENTORY_BAG);
				QSLOT_find();//������ ��ġ�� �ٲ�����Ƿ� �簻���Ѵ�
			}
		}
		

		struct ItemBag temp = Character::s_ItemSlot[SELECT_INVENTORY_BAG];
		Character::s_ItemSlot[SELECT_INVENTORY_BAG]=Character::s_ItemPick;
		Character::s_ItemPick = temp;

		s_Page.Focus = 0;//�˾� ����
	}else{// ������ ��ġ�� �ٲܶ�
		if((Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_INDEX==Character::s_ItemPick.ITEM_INDEX) && (Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND==Character::s_ItemPick.ITEM_KIND))
		{//���� ���� ������ & ���� �������� ��쿡 �Ʒ������� Ǯ������ ���� ä���
			int MaxStack = 99;//������ ���ð���
			switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){
				case ITEM_MAINQUEST://10�� ��ġ�� ������
					MaxStack = 10;
				
				case ITEM_POTION://99�� ����
				case ITEM_UP_STONE:
				case ITEM_GEM_STONE:
					if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT < MaxStack){//Ǯ���� �ƴ�
						int Sum = Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT+Character::s_ItemPick.ITEM_STACK_COUNT;

						if(Sum > MaxStack){//Ǯ���� ���� �÷�
							Character::s_ItemPick.Data1 -= MaxStack-Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT;
							Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1 = MaxStack + ((Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1/100)*100);
						}else{//�ϳ��� ������
							Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1 += Character::s_ItemPick.ITEM_STACK_COUNT;
							Character::s_ItemPick.Data0 = 0;
							Character::s_ItemPick.Data1 = 0;
							Character::s_ItemPick.Data2 = 0;
						}
						return;
					}
					break;


			}
		}
		
		//�� ��ü
		struct ItemBag temp = Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE];
		Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]=Character::s_ItemPick;
		Character::s_ItemPick = temp;
		QSLOT_find();
	}

	
}

void PopupUi::SORTING_bag(int bagNum){//������� ������ ����

	struct ItemBag temp;

	int SlotMax = get_BagMax(Character::s_ItemSlot[bagNum]);

	for(int xx = 0;xx<SlotMax;xx++){
		if(Character::s_ItemBag[bagNum][xx].ITEM_KIND == 0){//����� �߰�
			for(int yy = xx+1;yy<SlotMax;yy++){
				if(Character::s_ItemBag[bagNum][yy].ITEM_KIND){//������� ���� ���� �߰�
					temp = Character::s_ItemBag[bagNum][xx];
					Character::s_ItemBag[bagNum][xx] = Character::s_ItemBag[bagNum][yy];
					Character::s_ItemBag[bagNum][yy] = temp;
					break;
				}
				if(yy==(SlotMax-1) && Character::s_ItemBag[bagNum][yy].ITEM_KIND == 0){//������ĭ���� �������� �ִ� ĭ�� ������(����)
					return;
				}
			}
		}
	}
	
}
bool PopupUi::INPUT_bag(int bagNum, struct ItemBag _item){//���� ����
	return false;
}

int PopupUi::get_BagMax(struct ItemBag _item){//���� �κ����� ����
	switch(_item.Data0){
		case 100:return 8;
		case 101:return 16;
		case 102:return 24;
		case 103:return 32;
		default:return 0;
	}
}
void PopupUi::paint_ICON(struct ItemBag _item, int x, int y,bool full){//�������� ������ ǥ���Ѵ�
	if(_item.ITEM_KIND == 0)return;

	SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,itemICON(_item),x, y,0,0);//������
	if(full){
		//������ �Ǵ� �������� ��� ���ڷ� ǥ�ø� �Ѵ�
		switch(_item.ITEM_KIND){//������ ǥ�õ� ������
			case ITEM_POTION:
			case ITEM_UP_STONE:
			case ITEM_GEM_STONE:
			case ITEM_MAINQUEST:
				if(_item.Data1>1){
					PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_SKILL_NUM, _item.ITEM_STACK_COUNT,  x+16, y+9, -1 , CGraphics::RIGHT);//������ ����
				}
				break;
		}

		switch(_item.ITEM_KIND){//��� ���ΰ� ǥ�õ� ������  DATA1 �� �ֻ����ڸ����� 0�̸� ������ 1�̸� ����
			case ITEM_POTION://�o����
			case ITEM_SWORD	:
//			case ITEM_AXE	:
			case ITEM_GUN	:
//			case ITEM_OEB	:
			case ITEM_HEAD	:
			case ITEM_CHEST	:
			case ITEM_LEG	:
			case ITEM_GLOVE	:
			case ITEM_NECK	:
			case ITEM_RING	://��� ����
				if(_item.ITEM_EQUIP)SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EQUIP,x, y,0,0);//������
				break;
		}
	}
}
void PopupUi::Del_Item(struct ItemBag *_item){//������ ����
	_item->Data0 = 0;
	_item->Data1 = 0;
	_item->Data2 = 0;
}
void PopupUi::Del_Slot(int sex,int slot){//���� �κ����� ����
		Character::s_ItemEquip[sex][slot].Data0 = 0;	
		Character::s_ItemEquip[sex][slot].Data1 = 0;
		Character::s_ItemEquip[sex][slot].Data2 = 0;

		Character::s_ItemAbil[sex][slot].ATT_MIN	= 0;
		Character::s_ItemAbil[sex][slot].ATT_MAX	= 0;
		Character::s_ItemAbil[sex][slot].DEF		= 0;

		Character::s_ItemAbil[sex][slot].CRI		= 0; 
		Character::s_ItemAbil[sex][slot].AGI		= 0; 
		Character::s_ItemAbil[sex][slot].HP			= 0; 
		Character::s_ItemAbil[sex][slot].MP			= 0;
							 
		Character::s_ItemAbil[sex][slot].STR		= 0;
		Character::s_ItemAbil[sex][slot].DEX		= 0; 
		Character::s_ItemAbil[sex][slot].CON		= 0; 
		Character::s_ItemAbil[sex][slot].INT 		= 0; 

		Character::s_ItemAbil[sex][slot].DDANG		= 0;
		Character::s_ItemAbil[sex][slot].MUL		= 0; 
		Character::s_ItemAbil[sex][slot].BUL		= 0; 
		Character::s_ItemAbil[sex][slot].BARAM		= 0; 
}

//--------------------------------------------------------------------------
ItemBag PopupUi::MakeItem(int nMontype, int nMonLevel, int nHeroSex, int mapIdx)		//����man:0,girl:1
//--------------------------------------------------------------------------
{
	ItemBag tmpBag;
	tmpBag.Data0 = 0;
/*
	//	����Ʈ ó��
	if(MAIN_QUEST_openDoor == GET_MAINQUEST_IDX())
	{
		if(MON_IDX_BARREL == nMontype)
		{
			if(201 == mapIdx || 202 == mapIdx || 203 == mapIdx)
			{
				if(40 > SUTIL_GetRandom()%100)
				{
					tmpBag.Data0 = ITEM_CALL_tntBoom;
					tmpBag.Data1 = 1;
					tmpBag.Data2 = 0;
					return tmpBag;
				}
			}
		}
	}

	if(MAIN_QUEST_oldMedal == GET_MAINQUEST_IDX())
	{
		if(MON_IDX_BEAR == nMontype)
		{
			if(100 == mapIdx || 101 == mapIdx)
			{
				if(60 > SUTIL_GetRandom()%100)
				{
					tmpBag.Data0 = ITEM_CALL_medal;
					tmpBag.Data1 = 1;
					tmpBag.Data2 = 0;
					return tmpBag;
				}
			}
		}
	}


	if(MAIN_QUEST_findCrystal == GET_MAINQUEST_IDX())
	{
//		if(MON_IDX_WATER_ELE == MonBaseStet[nMontype][STET_BASE])
//		{
//			if(100 == mapIdx || 101 == mapIdx)
//			{
				if(30 > SUTIL_GetRandom()%100)
				{
					tmpBag.Data0 = ITEM_CALL_crystal;
					tmpBag.Data1 = 1;
					tmpBag.Data2 = 0;
					return tmpBag;
				}
//			}
//		}
	}
*/

	//switch(tableidx_b)
	//{

	//	case DT_QUEST00_MEDAL:
	//		tmpBag.Data0 = 9000;
	//		tmpBag.Data1 = 1;
	//		tmpBag.Data2 = 0;
 //			break;
	//	case DT_QUEST00_BOMB:
	//		tmpBag.Data0 = 9000;
	//		tmpBag.Data1 = 1;
	//		tmpBag.Data2 = 0;
 //			break;


	//	����Ǵ� �������� ����	
	const short drop_type_Table[4][5]=
	{
		//			  ��������, �Һ������,	  ��,	���Ƚ�ũ��
		{		20	,		50	,		100	,	100	,		50	},
		{		40	,		45	,		106	,	104	,		45	},
		{		60	,		43	,		106	,	108	,		43	},
		{		999	,		37	,		112	,	114	,		37	},
	};


	//	����Ǵ� �������� ��뼺��	//0��°�� �������̺�	1��°�� �������̺�
	const short man_girl_Table[2][3]=
	{
		//	����,	  ����,		����
		{		20	,		40	,		40},
		{		40	,		20	,		40},
	};

	//	������(�Ϲ���, ������)
	const short judgment_Table[2]=	{80, 20};

	//	����Ǵ� �������� ����	
	const short drop_level_Table[5][6]=
	{
		//����		���,		����,		����,	����ũ,		�����
		{ 0,		220	,		80	,		 0	,	0	,		0	},
		{16,		210	,		80	,		10	,	0	,		0	},
		{26,		202	,		82	,		12	,	4	,		0	},
		{40,		199	,		82	,		14	,	3	,		2	},
		{55,		189	,		82	,		17	,	8	,		4	},
	};

	//	���� Ȯ��(���� Ȯ��)(�Ϲ���, ������)
	const short socket_Table[2]=	{80, 50};

	//	���λ� Ȯ��(���� Ȯ��)(�Ϲ���, ������)
	const short hedertext_Table[2]=	{80, 50};


	int loop = 0;
	int dice = 0;
	int temp = 0;
	short tableidx_b = 0;	//	����
	short tableidx_c = 0;	//	����
	short tableidx_d = 0;	//	������
	short tableidx_e = 0;	//	������ ����
	short tableidx_f = 0;	//	������ ���
	short tableidx_g = 0;	//	������ ����
	short tableidx_h = 0;	//	���λ簡 ���� Ȯ��
	short tableidx_j = 0;	//	������ �ε���

	int tableidx_ex_1 = 0;		//	����� ����
	//	�������� ������ Ȯ��	///////////////////////////////
	dice = SUTIL_GetRandom()%100;
	if(50 > dice)	{return tmpBag;}

	//	���̺� ����	///////////////////////////////////////////
	temp = 0;
	while(nMonLevel > drop_type_Table[temp][0])	{temp++;}

	dice = SUTIL_GetRandom()%300;
	tableidx_b = 0;
	while(dice > drop_type_Table[temp][tableidx_b+1])
	{	
		dice -= drop_type_Table[temp][tableidx_b+1];
		tableidx_b++;
	}

	switch(tableidx_b)
	{
		case DT_SPEND:
			tmpBag.Data0 = 200;
			tmpBag.Data1 = SUTIL_GetRandom()%3+1;
			tmpBag.Data2 = 0;
 			break;
		case DT_SCROLL:/*
					   tmpBag.Data0 = 300;
					   tmpBag.Data1 = nMonLevel/3+1;
					   tmpBag.Data2 = 0;
					   break;*/
		case DT_MONEY:
 			tmpBag.Data0 = 300;
 			tmpBag.Data1 = (nMonLevel/3) + (SUTIL_GetRandom()%(nMonLevel/15 + 1)) + 1;
 			tmpBag.Data2 = 0;
 			break;

		case DT_EQUIP:
		//---------------------------------------------------------------
		{
			//	�������� ���� ///////////////////////////
			tableidx_ex_1 = SUTIL_GetRandom()%(E_D_RING+1);

			//	���� ����	////////////////////////////////////////////
			dice = SUTIL_GetRandom()%100;

			tableidx_c = 0;
			while(dice > man_girl_Table[nHeroSex][tableidx_c])
			{
				dice -= man_girl_Table[nHeroSex][tableidx_c];
				tableidx_c++;
			}

			//	������ ����	////////////////////////////////////////////
			dice = SUTIL_GetRandom()%100;

			tableidx_d = 0;
			while(dice > judgment_Table[tableidx_d])
			{
				dice -= judgment_Table[tableidx_d];
				tableidx_d++;
			}

			//	������ ���� ����	////////////////////////////////////////////
			tableidx_e = nMonLevel-5 + (SUTIL_GetRandom()%10);
			if(1 > tableidx_e)	{tableidx_e = 1;}

			//	������ ��� ����	////////////////////////////////////////////
			temp = 0;
			while(nMonLevel > drop_level_Table[temp][0])	{temp++;}

			dice = SUTIL_GetRandom()%300;

			tableidx_f = 0;
			while(dice > drop_level_Table[temp][tableidx_f+1])
			{	
				dice -= drop_level_Table[temp][tableidx_f+1];
				tableidx_f++;
			}

			//	������ ���� ����	/////////////////////////////////////////////
			if(DG_NORMAL < tableidx_f)
			{
				tableidx_g = 0;
				for(loop = 0; loop < 3; loop++)
				{
					if(socket_Table[tableidx_d] < (SUTIL_GetRandom()%100))	{tableidx_g++;}
				}
			}

			//	���λ� ���� Ȯ��	/////////////////////////////////////////////////
			if(hedertext_Table[tableidx_d] < (SUTIL_GetRandom()%100))
			{
				tableidx_h = (SUTIL_GetRandom()%7)+1;		
			}

			//	������ �ε��� ����
			if(E_D_NECKLACE > tableidx_ex_1)	
			{
				for(tableidx_j = 0; tableidx_j < 25; tableidx_j++)
				{
					if(tableidx_e < equip_Table[tableidx_j][0])	{break;}
				}
			}
			else								
			{
				for(tableidx_j = 0; tableidx_j < 25; tableidx_j++)
				{
					if(tableidx_e < deco_Table[tableidx_j][0])		{break;}
				}
			}

			tableidx_j--;
			if(0 > tableidx_j)	{tableidx_j = 0;}
			tableidx_j = 1000 + (100*tableidx_ex_1) + tableidx_j;

			tmpBag.Data0 = tableidx_j;
			tmpBag.Data2 = 0;

			tmpBag.Data1 = 0;

			//	��������
			if(tableidx_g>0){
				tmpBag.Data1 += 1000;
				if(tableidx_g>1){
					tmpBag.Data1 += 100000;
					if(tableidx_g>2){
						tmpBag.Data1 += 10000000;
					}			
				}			
			}			
			tmpBag.Data1 += tableidx_h * 10;			//	�������� ���λ� ����

			tmpBag.Data1 += (tableidx_f);		//	�������� ��� ����
			break;
		}
	}

	return tmpBag;
}



#define LEVELGAP	10
#define SHOPMAX		24
void PopupUi::MakeShop(int ShopKind, int ShopLevel)		//���� �����ϴ� �������� ����
//--------------------------------------------------------------------------
{
	for(int xx = 0;xx<SHOPMAX;xx++){
		Character::s_ItemShop[xx].Data0 = Character::s_ItemShop[xx].Data1 = Character::s_ItemShop[xx].Data2 = 0;
	}
	switch(ShopKind){
		case 0://����
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1000+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1200+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 1://�Ӹ�
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1400+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1400+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 2://����
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1500+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1500+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 3://��
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1700+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1700+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 4://�ٸ�
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1600+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1600+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 5://�����
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1800+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1800+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;
		case 6://����
			for(int xx = 0,index = 0;xx<25 && index<SHOPMAX;xx++){//25���� ��� �˻��ϸ鼭 ������ �´°�?
				if(equip_Table[xx][0] <= ShopLevel+LEVELGAP && equip_Table[xx][0] >= ShopLevel-LEVELGAP){
					Character::s_ItemShop[index].Data0 = 1900+xx;
					Character::s_ItemShop[index].Data1 = 0;
					index++;
					Character::s_ItemShop[index].Data0 = 1900+xx;
					Character::s_ItemShop[index].Data1 = 1000000000;
					index++;
				}
			}
			break;

		case 7://����
			break;
		case 8://����
			break;
	}

}


int PopupUi::CalkCost(struct ItemBag _item)
{//��� �κ��� ���鼭 ������ �������� ������ üũ�Ѵ�
	int cost = 0;
	switch(_item.ITEM_KIND){//������ ������ ��ȭ
		case ITEM_SWORD	:
		case ITEM_GUN	:
		case ITEM_HEAD	:
		case ITEM_CHEST	:
		case ITEM_LEG	:
		case ITEM_GLOVE	:
		case ITEM_NECK	:
		case ITEM_RING	://���� �������� ��ġ�� �Ű����� ������
			switch(_item.ITEM_GRADE){
				case 0:cost = equip_Table[_item.ITEM_INDEX][0]*8 /2+3; break;//���   ������ ���� *8 /2+3
				case 1:cost = equip_Table[_item.ITEM_INDEX][0]*9 /2+3; break;//����   ������ ���� *9 /2+3
				case 2:cost = equip_Table[_item.ITEM_INDEX][0]*10/2+3; break;//����   ������ ���� *10/2+3
				case 3:cost = equip_Table[_item.ITEM_INDEX][0]*11/2+3; break;//����ũ ������ ���� *11/2+3
				case 4:cost = equip_Table[_item.ITEM_INDEX][0]*12/2+3; break;//����� ������ ���� *12/2+3
			}
			break;
		case ITEM_MAINQUEST://�ǸźҰ� - ����Ҽ����� �Ϲ��ۿ� �޼���
			cost = 0;
			break;
		default:{//������� ��ġ�� �Ű����� ������
				int Gread = 0;
				for(int xx = 0,length = sizeof(H_Potion_Table)/(sizeof(short)*3) ; xx < length ;xx++){
					if(H_Potion_Table[xx][0] == _item.ITEM_ID){Gread = H_Potion_Table[xx][1];}
				}
				for(int xx = 0,length = sizeof(M_Potion_Table)/(sizeof(short)*3) ; xx < length ;xx++){
					if(M_Potion_Table[xx][0] == _item.ITEM_ID){Gread = M_Potion_Table[xx][1];}
				}
				for(int xx = 0,length = sizeof(Bag_Table)/(sizeof(short)*3) ; xx < length ;xx++){
					if(Bag_Table[xx][0] == _item.ITEM_ID){Gread = Bag_Table[xx][1];}
				}
				for(int xx = 0,length = sizeof(Enchant_Table)/(sizeof(short)*3) ; xx < length ;xx++){
					if(Enchant_Table[xx][0] == _item.ITEM_ID){Gread = Enchant_Table[xx][1];}
				}
				for(int xx = 0,length = sizeof(Book_Table)/(sizeof(short)*3) ; xx < length ;xx++){
					if(Book_Table[xx][0] == _item.ITEM_ID){Gread = Book_Table[xx][1];}
				}
				switch(Gread){
					//case 0:cost = Gread*6+2; break;//������ ���*6+2
					case 1:cost = Gread*7+2; break;//������ ���*7+2
					case 2:cost = Gread*9+2; break;//������ ���*9+2
					case 3:cost = Gread*11+2; break;//������ ���*11+2
					case 4:cost = Gread*13+2; break;//������ ���*13+2
					case 5:cost = Gread*18+2; break;//������ ���*18+2
					case 6:cost = Gread*25+2; break;//������ ���*25+2
					case 7:cost = Gread*35+2; break;//������ ���*35+2
				}				  
				
			}break;
	}
	return cost;
}//�������� ��ġ�� ����Ѵ�
bool PopupUi::GET_item(struct ItemBag* _item)
{
	int StackMAX = 99;


	switch(_item->ITEM_KIND){
		case ITEM_MONEY://�κ� ������ �����ʴ� ������
			Character::s_Status[Character::s_HeroTag.SEX].MONEY+=_item->ITEM_MONEY_COUNT;
			if(Character::s_Status[Character::s_HeroTag.SEX].MONEY>999999999)Character::s_Status[Character::s_HeroTag.SEX].MONEY = 999999999;
			AddItemList(*_item);
			return true;

		case ITEM_MAINQUEST://10�� ��ġ�� ������
			StackMAX = 10;
		case ITEM_POTION://99�� ��ġ�¾�����
		case ITEM_UP_STONE:
		case ITEM_GEM_STONE:
			{



				struct ItemBag _itemTemp = *_item;
				for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������ �������� ã�Ƴ���
					switch(Character::s_ItemSlot[xx].Data0){
						case 100:MaxSlot= 8;break;
						case 101:MaxSlot= 16;break;
						case 102:MaxSlot= 24;break;
						case 103:MaxSlot= 32;break;
						default:MaxSlot= 0;break;
					}
					for(int yy = 0;yy<MaxSlot;yy++){
						if(Character::s_ItemBag[xx][yy].ITEM_KIND == _item->ITEM_KIND 
							&& Character::s_ItemBag[xx][yy].ITEM_INDEX == _item->ITEM_INDEX){//������ �������̶��

							int Sum = Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT+_item->ITEM_STACK_COUNT;

							if(Sum<=StackMAX){//������ ��ġ��
								Character::s_ItemBag[xx][yy].Data1 = ((Character::s_ItemBag[xx][yy].Data1 / 100) * 100) +Sum;
								AddItemList(_itemTemp);
								return true;
							}else{//������ ��ġ�� ���°��
								Character::s_ItemBag[xx][yy].Data1 = ((Character::s_ItemBag[xx][yy].Data1 / 100) * 100) +StackMAX;
								_item->Data1 =((_item->Data1 / 100) * 100) + ((Sum) - StackMAX) ;
							}
						}
					}
				}
				//Ǯ������ ä��� ������ ���
				for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������� ã�Ƴ���
					switch(Character::s_ItemSlot[xx].Data0){
						case 100:MaxSlot= 8;break;
						case 101:MaxSlot= 16;break;
						case 102:MaxSlot= 24;break;
						case 103:MaxSlot= 32;break;
						default:MaxSlot= 0;break;
					}
					for(int yy = 0;yy<MaxSlot;yy++){
						if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//����ִ½����� ������
							Character::s_ItemBag[xx][yy] = *_item;

							AddItemList(_itemTemp);
							return true;
						}
					}
				}
			}
			break;
		default://��ġ���ʴ¾�����

			for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������� ã�Ƴ���
				switch(Character::s_ItemSlot[xx].Data0){
					case 100:MaxSlot= 8;break;
					case 101:MaxSlot= 16;break;
					case 102:MaxSlot= 24;break;
					case 103:MaxSlot= 32;break;
					default:MaxSlot= 0;break;
				}
				for(int yy = 0;yy<MaxSlot;yy++){
					if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//����ִ½����� ������
						Character::s_ItemBag[xx][yy] = *_item;

						AddItemList(*_item);
						return true;
					}
				}
			}
			break;
	}
	
	return false;
	
}//�������� ȹ��������
int PopupUi::GET_Count(int itemID,int SEX)//itemID �� 0���� �ѱ�� �󽽷��� ������ üũ����
{//��� �κ��� ���鼭 ������ �������� ������ üũ�Ѵ�
	int counter = 0;
	for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������ �������� ã�Ƴ���
		switch(Character::s_ItemSlot[xx].Data0){
				case 100:MaxSlot= 8;break;
				case 101:MaxSlot= 16;break;
				case 102:MaxSlot= 24;break;
				case 103:MaxSlot= 32;break;
				default:MaxSlot= 0;break;
		}
		for(int yy = 0;yy<MaxSlot;yy++){
			if(itemID == Character::s_ItemBag[xx][yy].ITEM_ID){
				if(Character::s_ItemBag[xx][yy].ITEM_KIND >= 10 && Character::s_ItemBag[xx][yy].ITEM_KIND <= 19 ){//���
					if(Character::s_ItemBag[xx][yy].ITEM_SEX == SEX || SEX_HUMAN==SEX){counter++;}
				}else{
					if(Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT){
						counter += Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT;
					}else{
						counter ++;
					}
					
				}
			}
		}
	}
	return counter;

}//������ ���� ���� üũ �Ҷ�
int PopupUi::REMOVE_Item(int itemID,int counter,int SEX)
{//��� �κ��� ���鼭 ������ŭ �������� �����Ѵ�
	
	for(int xx = 0,MaxSlot=0;xx<4;xx++){//��� �κ��� ���鼭 ������ �������� ã�Ƴ���
		switch(Character::s_ItemSlot[xx].Data0){
				case 100:MaxSlot= 8;break;
				case 101:MaxSlot= 16;break;
				case 102:MaxSlot= 24;break;
				case 103:MaxSlot= 32;break;
				default:MaxSlot= 0;break;
		}
		for(int yy = 0;yy<MaxSlot;yy++){
			if(itemID == Character::s_ItemBag[xx][yy].ITEM_ID){
				if(Character::s_ItemBag[xx][yy].ITEM_KIND < 10 || Character::s_ItemBag[xx][yy].ITEM_KIND > 19 ){//��� �ƴ�
					if(Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT){
						if(counter==ALL_DEL){//���� ������ ���� ����
							Character::s_ItemBag[xx][yy].Data0 = 0;
							Character::s_ItemBag[xx][yy].Data1 = 0;
							Character::s_ItemBag[xx][yy].Data2 = 0;
						}else if(counter >= Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT){//������ �������� ������ �������� ���ڶ���
							counter -= Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT;
							Character::s_ItemBag[xx][yy].Data0 = 0;
							Character::s_ItemBag[xx][yy].Data1 = 0;
							Character::s_ItemBag[xx][yy].Data2 = 0;
						}else{
							Character::s_ItemBag[xx][yy].Data1 -= counter;
							counter=0;
						}

						if(counter==0){
							return counter;
						}
						
					}else{
						counter --; // �������� ���׻�Ȳ �������� ������ 0�� �����̴�
						Character::s_ItemBag[xx][yy].Data0 = 0;
						Character::s_ItemBag[xx][yy].Data1 = 0;
						Character::s_ItemBag[xx][yy].Data2 = 0;
					}
					
				}else{//����� ����

					if(Character::s_ItemBag[xx][yy].ITEM_SEX == SEX || SEX_HUMAN==SEX){

						if(0 == Character::s_ItemBag[xx][yy].ITEM_EQUIP){ //������� ���� �������߿�
							if(counter==ALL_DEL){//���� ������ ���� ����
								Character::s_ItemBag[xx][yy].Data0 = 0;
								Character::s_ItemBag[xx][yy].Data1 = 0;
								Character::s_ItemBag[xx][yy].Data2 = 0;
							}else{//�������� 1�� ���� ���ڶ���
								counter--;
								Character::s_ItemBag[xx][yy].Data0 = 0;
								Character::s_ItemBag[xx][yy].Data1 = 0;
								Character::s_ItemBag[xx][yy].Data2 = 0;
							}

							if(counter==0){
								return counter;
							}

						}
					}
				}
			}
		}
	}
	return counter;

}//������ ���� ���� üũ �Ҷ�

void PopupUi::equipTEXT(int sex,int slot,struct ItemBag _item){//���� �����ۿ� ���� ����
	//���� ������ ��� ����������� ��ȭ�ϴ� �ɷ�ġ�� �����ش�



	ItemAbility TempAbil = Character::s_ItemAbil[sex][slot];  
	ItemBag TempEquip = Character::s_ItemEquip[sex][slot];


	int temp_Amax = Character::s_Status[s_Page.Woman_Man].ATTACK_MAX;
	int temp_Def  = Character::s_Status[s_Page.Woman_Man].DEFENSE;
	int temp_Cri  = Character::s_Status[s_Page.Woman_Man].CRITICAL;
	int temp_Agi  = Character::s_Status[s_Page.Woman_Man].AVOID;
	int temp_Life = Character::s_Status[s_Page.Woman_Man].LIFE_MAX;
	int temp_Mana = Character::s_Status[s_Page.Woman_Man].MANA_MAX;


	Character::s_ItemEquip[sex][slot] = _item;//�ӽ�����
	Set_Item(&Character::s_ItemAbil[sex][slot],&Character::s_ItemEquip[sex][slot]);
	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���


	_SUTIL->pFont->setColor(0x93abbf);  

	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ATT], XPOS-73, YPOS+37, 0);		//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DEF], XPOS-73, YPOS+53, 0);		//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CRI], XPOS-73, YPOS+69, 0);		//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_AGI], XPOS+6, YPOS+37, 0);		//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_HP], XPOS+6, YPOS+53, 0);		//HP
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MP], XPOS+6, YPOS+69, 0);		//MP

	_SUTIL->pFont->setColor(0xffcc00);

	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].ATTACK_MAX, XPOS-22, YPOS+37, CGraphics::RIGHT);//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].DEFENSE, XPOS-22, YPOS+53, CGraphics::RIGHT);	//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].CRITICAL, XPOS-22, YPOS+69, CGraphics::RIGHT);	//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].AVOID, XPOS+57, YPOS+37, CGraphics::RIGHT);		//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].LIFE_MAX, XPOS+57, YPOS+53, CGraphics::RIGHT);	//HP
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status[s_Page.Woman_Man].MANA_MAX, XPOS+57, YPOS+69, CGraphics::RIGHT);	//MP


//�� �ٿ� ������ 
	if(temp_Amax < Character::s_Status[s_Page.Woman_Man].ATTACK_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-18,YPOS+35,0,0);//UP������
	}else if(temp_Amax > Character::s_Status[s_Page.Woman_Man].ATTACK_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-18,YPOS+35,0,0);//DOWN������
	}
	if(temp_Def  < Character::s_Status[s_Page.Woman_Man].DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-18,YPOS+51,0,0);//UP������
	}else if(temp_Def  > Character::s_Status[s_Page.Woman_Man].DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-18,YPOS+51,0,0);//DOWN������
	}
	if(temp_Cri  < Character::s_Status[s_Page.Woman_Man].CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-18,YPOS+66,0,0);//UP������
	}else if(temp_Cri  > Character::s_Status[s_Page.Woman_Man].CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-18,YPOS+66,0,0);//DOWN������
	}

	if(temp_Agi  < Character::s_Status[s_Page.Woman_Man].AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+61,YPOS+35,0,0);//UP������
	}else if(temp_Agi  > Character::s_Status[s_Page.Woman_Man].AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+61,YPOS+35,0,0);//DOWN������
	}
	if(temp_Life < Character::s_Status[s_Page.Woman_Man].LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+61,YPOS+51,0,0);//UP������
	}else if(temp_Life > Character::s_Status[s_Page.Woman_Man].LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+61,YPOS+51,0,0);//DOWN������
	}
	if(temp_Mana < Character::s_Status[s_Page.Woman_Man].MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+61,YPOS+66,0,0);//UP������
	}else if(temp_Mana > Character::s_Status[s_Page.Woman_Man].MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+61,YPOS+66,0,0);//DOWN������
	}




	Character::s_ItemAbil[sex][slot] = TempAbil;//���󺹱�
	Character::s_ItemEquip[sex][slot] = TempEquip;//���󺹱�
	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���


	
}


void PopupUi::Set_Item(struct ItemAbility *_abil,struct ItemBag *_item){//���� �κ����� ����

	_abil->ATT_MIN	= 0;
	_abil->ATT_MAX	= 0;

	_abil->DEF		= 0;
	_abil->CRI		= 0;
	_abil->AGI		= 0;
	_abil->HP		= 0;
	_abil->MP		= 0;

	_abil->STR		= 0;
	_abil->DEX		= 0;
	_abil->CON		= 0;
	_abil->INT		= 0;

	_abil->DDANG	= 0;
	_abil->MUL		= 0;
	_abil->BUL		= 0;
	_abil->BARAM	= 0;


	
	int gradePER[5] = {100,110,115,120,130};//���
	int grade = gradePER[_item->Data1%10];
	int head = 100 + head_Table[(_item->Data1/10)%100][ (_item->ITEM_KIND<ITEM_HEAD? 0:5) ]; //����� ���Ŀ����� ���̹ٲ��


//���λ�
	_abil->CRI		+= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 1:6)];
	_abil->AGI		+= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 2:7)];
	_abil->HP		+= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 3:8)];
	_abil->MP		+= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 4:9)];

//�뽺��
	for(int xx = 0;xx<3;xx++){//���Կ� �����ִ� ������ ��ģ��
		int slot;
		switch(xx){//�󽽷�
			case 0:slot = _item->ITEM_SOCKET_3;break;
			case 1:slot = _item->ITEM_SOCKET_2;break;
			case 2:slot = _item->ITEM_SOCKET_1;break;
		}
		if(slot > 1){
			_abil->STR		+= gem_Table[slot-2][G_T_A_STR];
			_abil->DEX		+= gem_Table[slot-2][G_T_A_DEX];
			_abil->CON		+= gem_Table[slot-2][G_T_A_CON];
			_abil->INT		+= gem_Table[slot-2][G_T_A_INT];

			_abil->DDANG	+= gem_Table[slot-2][G_T_E_DDANG];
			_abil->MUL		+= gem_Table[slot-2][G_T_E_MUL	];
			_abil->BUL		+= gem_Table[slot-2][G_T_E_BUL	];
			_abil->BARAM	+= gem_Table[slot-2][G_T_E_BARAM];
		}

	
	}




//��ũ��
	int scroll_Kind = (_item->Data2/100)%100; //��ũ�� ����
	int UP = (((_item->Data2/10000) %1000) /3) +1; //��ũ�� ���ġ

	switch(scroll_Kind){//��ũ�� ����
		case 1:_abil->STR += UP; _abil->DEX += UP;break;
		case 2:_abil->STR += UP; _abil->CON += UP;break;
		case 3:_abil->STR += UP; _abil->INT += UP;break;
		case 4:_abil->DEX += UP; _abil->CON += UP;break;
		case 5:_abil->DEX += UP; _abil->INT += UP;break;
		case 6:_abil->CON += UP; _abil->INT += UP;break;
		case 7:	_abil->STR += UP*4/3+1;break;
		case 8:	_abil->DEX += UP*4/3+1;break;
		case 9:	_abil->CON += UP*4/3+1;break;
		case 10:_abil->INT += UP*4/3+1;break;
		case 11:_abil->STR += MAX(1,UP/2); _abil->DEX += MAX(1,UP/2); _abil->CON += MAX(1,UP/2); _abil->INT += MAX(1,UP/2);break;
	}

	

	switch(_item->ITEM_KIND){//������ ������ ��ȭ  
		case ITEM_SWORD	:
			_abil->ATT_MIN	+= PER(PER(equip_Table[_item->ITEM_INDEX][1],grade),head);
			_abil->ATT_MAX	+= PER(PER(equip_Table[_item->ITEM_INDEX][2],grade),head);
			break;
// 		case ITEM_AXE	:
// 			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][3],grade),head);
// 			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][4],grade),head);
// 			_abil->DEF		= 0;
// 			break;
		case ITEM_GUN	:
			_abil->ATT_MIN	+= PER(PER(equip_Table[_item->ITEM_INDEX][5],grade),head);
			_abil->ATT_MAX	+= PER(PER(equip_Table[_item->ITEM_INDEX][6],grade),head);
			break;
// 		case ITEM_OEB	:
// 			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][7],grade),head);
// 			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][8],grade),head);
// 			_abil->DEF		= 0;
// 			break;


		case ITEM_HEAD	:
			_abil->DEF		+= PER(PER(equip_Table[_item->ITEM_INDEX][9],grade),head);
			break;
		case ITEM_CHEST	:
			_abil->DEF		+= PER(PER(equip_Table[_item->ITEM_INDEX][10],grade),head);
			break;
		case ITEM_LEG	:
			_abil->DEF		+= PER(PER(equip_Table[_item->ITEM_INDEX][11],grade),head);
			break;
		case ITEM_GLOVE	:
			_abil->DEF		+= PER(PER(equip_Table[_item->ITEM_INDEX][12],grade),head);
			break;
		case ITEM_NECK	:
			_abil->DEF		+= PER(PER(deco_Table[_item->ITEM_INDEX][1],grade),head);
			break;
		case ITEM_RING	:
			_abil->ATT_MIN	+= PER(PER(deco_Table[_item->ITEM_INDEX][2],grade),head);
			_abil->ATT_MAX	+= PER(PER(deco_Table[_item->ITEM_INDEX][2],grade),head);
			_abil->DEF		+= PER(PER(deco_Table[_item->ITEM_INDEX][3],grade),head);
			break;
	}
	
}




void PopupUi::Page_init(){
	s_Page.Focus  =0;
	s_Page.Ly1_sel=0;
	s_Page.Ly2_sel=0;
	s_Page.Ly3_sel=0;
	s_Page.Ly4_sel=0;
	s_Page.Ly5_sel=0;
	s_Page.Ly6_sel=0;
	s_Page.Ly7_sel=0;
	s_Page.Ly8_sel=0;
	s_Page.Ly9_sel=0;
	s_Page.Ly10_sel=0;
	s_Page.Ly11_sel=0;
	s_Page.Ly12_sel=0;

	s_Popup_Sharp.View = false;
	s_Popup_Sharp.Line = 0;
	s_Popup_Sharp.LineMAX = 0;
}





int PopupUi::Set_QUEST(int itemID,int MainQuest)
{
	//s_ItemList[0].QUEST_now = 0;
	//s_ItemList[0].QUEST_max = 0;

	if(itemID == 0){
		itemID = MainQuest;
	}
	switch(itemID){//Ư�� �������� ����Ʈ������ �������� ǥ�õǾ�� �� �� �� ����
		case ITEM_CALL_tntBoom:	
			if(MAIN_QUEST_openDoor != GET_MAINQUEST_IDX()){return 0;}
		case MAIN_QUEST_openDoor:
			return (ITEM_CALL_tntBoom*10000)+ (GET_Count(ITEM_CALL_tntBoom)*100)+	MAX_tntBoom;
			
		case ITEM_CALL_medal:
			if(MAIN_QUEST_oldMedal != GET_MAINQUEST_IDX()){return 0;}
		case MAIN_QUEST_oldMedal:
			return (ITEM_CALL_medal*10000)+ (GET_Count(ITEM_CALL_medal)*100)+	MAX_medal;

		case ITEM_CALL_crystal:		
			if(MAIN_QUEST_findCrystal != GET_MAINQUEST_IDX()){return 0;}
		case MAIN_QUEST_findCrystal:
			return (ITEM_CALL_crystal*10000)+ (GET_Count(ITEM_CALL_crystal)*100)+	MAX_crystal;

		case ITEM_CALL_diary:		
			if(MAIN_QUEST_findDiary != GET_MAINQUEST_IDX()){return 0;}
		case MAIN_QUEST_findDiary:
			return (ITEM_CALL_diary*10000)+ (GET_Count(ITEM_CALL_diary)*100)+	MAX_diary;

	}

	return 0;
}


#define ITEMLIST_LOCATE_Y		(50)
#define ITEMLIST_LENGTH_X		(93)
#define ITEMLIST_DELAY		(40)
#define ITEMLIST_MAX		(5)
//--------------------------------------------------------------------------
void PopupUi::AddItemList(struct ItemBag _item)
{


	if(s_ItemList[0].LifeTime != 0){
		for(int xx = ITEMLIST_MAX-1;xx>0;xx--){
			s_ItemList[xx].Color	= s_ItemList[xx-1].Color	;
			s_ItemList[xx].Kind		= s_ItemList[xx-1].Kind		;
			s_ItemList[xx].Index	= s_ItemList[xx-1].Index	;
			s_ItemList[xx].Head		= s_ItemList[xx-1].Head		;
			s_ItemList[xx].LifeTime	= s_ItemList[xx-1].LifeTime	;
			s_ItemList[xx].QUEST_now	= s_ItemList[xx-1].QUEST_now;
			s_ItemList[xx].QUEST_max	= s_ItemList[xx-1].QUEST_max;
		}
	}
	if(s_ItemList[ITEMLIST_MAX-1].LifeTime>7) s_ItemList[ITEMLIST_MAX-1].LifeTime = 7;//������ ������ �ϴ� �������

	switch(_item.ITEM_KIND){
		case ITEM_MONEY:
			s_ItemList[0].Color = 0xffffff;
			s_ItemList[0].Kind=	_item.ITEM_KIND;
			s_ItemList[0].Index=_item.ITEM_INDEX;
			s_ItemList[0].Head=_item.ITEM_MONEY_COUNT;
			break;
		case ITEM_POTION:
			s_ItemList[0].Color = 0xffffff;
			s_ItemList[0].Kind=	_item.ITEM_KIND;
			s_ItemList[0].Index=_item.ITEM_INDEX;
			s_ItemList[0].Head=_item.ITEM_STACK_COUNT;
			break;
		case ITEM_MAINQUEST:
			s_ItemList[0].Color = 0xffaaaa;
			s_ItemList[0].Kind=	_item.ITEM_KIND;
			s_ItemList[0].Index=_item.ITEM_INDEX;
			s_ItemList[0].Head=_item.ITEM_STACK_COUNT;
			break;

		default:
			switch(_item.ITEM_GRADE){
				case 0:s_ItemList[0].Color = 0xffffff;break;
				case 1:s_ItemList[0].Color = 0x72fa28;break;
				case 2:s_ItemList[0].Color = 0x52c4ff;break;
				case 3:s_ItemList[0].Color = 0x916aff;break;
				case 4:s_ItemList[0].Color = 0xff6c32;break;
			}
			s_ItemList[0].Kind=	_item.ITEM_KIND;
			s_ItemList[0].Index=_item.ITEM_INDEX;
			s_ItemList[0].Head=	_item.ITEM_HEADTEXT;
			break;
	}
	s_ItemList[0].LifeTime=ITEMLIST_DELAY;

	int Num = Set_QUEST(_item.ITEM_ID,NULL);

	s_ItemList[0].QUEST_now=Q_ITEM_NOW(Num);
	s_ItemList[0].QUEST_max=Q_ITEM_MAX(Num);



	s_ItemList[0].QUEST_now = Q_ITEM_NOW(Num);
	s_ItemList[0].QUEST_max = Q_ITEM_MAX(Num);

}
void PopupUi::PaintItemList()
{ 
	if(s_ItemList[0].LifeTime == 0)	{return;}

	int width = 0;
	int slide = 0;

	for(int xx = 0;xx<ITEMLIST_MAX;xx++){
		if(xx == 1 && (ITEMLIST_DELAY-5 < s_ItemList[0].LifeTime)){
			slide = (4 + s_ItemList[0].LifeTime - ITEMLIST_DELAY) * 3;
		}
		if(s_ItemList[xx].LifeTime){
			
			switch(s_ItemList[xx].LifeTime){
				case 1:case ITEMLIST_DELAY-0:	width = ITEMLIST_LENGTH_X-64;break;
				case 2:case ITEMLIST_DELAY-1:	width = ITEMLIST_LENGTH_X-32;break;
				case 3:case ITEMLIST_DELAY-2:	width = ITEMLIST_LENGTH_X-16;break;
				case 4:case ITEMLIST_DELAY-3:	width = ITEMLIST_LENGTH_X-8;break;
				case 5:case ITEMLIST_DELAY-4:	width = ITEMLIST_LENGTH_X-4;break;
				case 6:case ITEMLIST_DELAY-5:	width = ITEMLIST_LENGTH_X-2;break;
				case 7:case ITEMLIST_DELAY-6:	width = ITEMLIST_LENGTH_X-1;break;
				default:		width = ITEMLIST_LENGTH_X;break;
			}
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_GET_ITEM,width, ITEMLIST_LOCATE_Y+(xx*14)-slide, 0);

			char str[60];//������ �ؽ�Ʈ
			_SUTIL->pFont->setColor(s_ItemList[xx].Color);

			switch(s_ItemList[xx].Kind){
				case ITEM_MONEY://��� ��� ��尹��ǥ��
					SPRINTF(str, "%d %s",
						s_ItemList[xx].Head,
						(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)]); 	
					break;
				case ITEM_POTION://������ ���
				case ITEM_MAINQUEST:
					if(s_ItemList[xx].QUEST_max == 0){//����Ʈ���� �������� �ƴҶ�
						SPRINTF(str, "%s x%d",
							(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
							s_ItemList[xx].Head); 	
					}else{
						if(s_ItemList[xx].QUEST_now < s_ItemList[xx].QUEST_max){//����Ʈ �����̴�
							SPRINTF(str, "%s ^1(%d/%d)^0",
								(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
								s_ItemList[xx].QUEST_now,
								s_ItemList[xx].QUEST_max); 	
						}else{//����Ʈ �Ϸ�
							SPRINTF(str, "%s ^2(%s)^0",
								(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
								(char*)pITEM_Text->nText[ITEM_CLEAR]); 	
						}
					}
					
					break;


				default://���
					SPRINTF(str, "%s %s",
						(s_ItemList[xx].Head?(char*)pITEM_Text->nText[(ITEM_SCROLL_0-1)+s_ItemList[xx].Head]:""),
						(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)]); 	
					break;

			}
			_SUTIL->pFont->DrawText(_SUTIL->g, str, width-5, ITEMLIST_LOCATE_Y+(xx*14)-slide+2, CGraphics::RIGHT);

			s_ItemList[xx].LifeTime--;
		}
	}
}


//--------------------------------------------------------------------------
#define MESSAGE_LOCATE_Y		(70)
#define MESSAGE_DELAY		(40)
void PopupUi::AddMessage(int m_MSG)
{
	s_PlayMessage.MSG = m_MSG;
	s_PlayMessage.LifeTime=MESSAGE_DELAY;
}
void PopupUi::PaintMessage()
{
	if(s_PlayMessage.LifeTime == 0)	{return;}

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_RESULTS, XPOS, MESSAGE_LOCATE_Y, 0);//�޼��� ������ �׸���

	switch(s_PlayMessage.MSG){
		case CLRMENU_Q5			:
			_SUTIL->pFont->setColor(0xff7e7e);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[s_PlayMessage.MSG], XPOS, MESSAGE_LOCATE_Y-1, CGraphics::HCENTER);
			break;
		case CLRMENU_TEXT_SAVED	:
			_SUTIL->pFont->setColor(0xffffff);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[s_PlayMessage.MSG], XPOS, MESSAGE_LOCATE_Y-1, CGraphics::HCENTER);
			break;
		case CLRMENU_MAIN_Q		:
			_SUTIL->pFont->setColor(0xc7ad00);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[GET_MAINQUEST_IDX()*2], XPOS, MESSAGE_LOCATE_Y-1, CGraphics::HCENTER);
			break;
		case CLRMENU_SUB_Q		:
			_SUTIL->pFont->setColor(0xc7ad00);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[s_PlayMessage.MSG], XPOS, MESSAGE_LOCATE_Y-1, CGraphics::HCENTER);
			break;

		default:s_PlayMessage.LifeTime = 0;return;
	}
	

	s_PlayMessage.LifeTime--;
}





#define AREA_LOCATE_Y		(70)
#define AREA_DELAY		(40)

void PopupUi::AddAreaMessage(char *c_AreaName)
{ 

	MEMSET(s_AreaMessage.str, NULL, ARRAY_SIZE(s_AreaMessage.str));
	SPRINTF(s_AreaMessage.str, "%s",(char*)c_AreaName);
	s_AreaMessage.LifeTime=AREA_DELAY+10;
					
	/*_SUTIL->pFont->DrawText(_SUTIL->g, str, width-5, ITEMLIST_LOCATE_Y+(xx*14)-slide+2, CGraphics::RIGHT);

	s_AreaMessage.MSG = m_MSG;*/
}
void PopupUi::PaintAreaMessage()
{
	if(s_AreaMessage.LifeTime <= 0)	{return;}
	if(s_AreaMessage.LifeTime > AREA_DELAY)	{s_AreaMessage.LifeTime--;return;}
	

	_SUTIL->pFont->setOutline(true);
	_SUTIL->pFont->setOutlineColor(0x000000);

	switch(s_AreaMessage.LifeTime){
		case 1:
		case AREA_DELAY:
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_1, XPOS, AREA_LOCATE_Y, 0);//�޼��� ������ �׸���
			break;
		case 2:
		case AREA_DELAY-1:
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_2, XPOS, AREA_LOCATE_Y, 0);//�޼��� ������ �׸���
			_SUTIL->pFont->setColor(0x888888);
			_SUTIL->pFont->DrawText(_SUTIL->g, s_AreaMessage.str, XPOS, AREA_LOCATE_Y-4, CGraphics::HCENTER);
			
			break;
		default:
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_3, XPOS, AREA_LOCATE_Y, 0);//�޼��� ������ �׸���
			_SUTIL->pFont->setColor(0xffffff);
			_SUTIL->pFont->DrawText(_SUTIL->g, s_AreaMessage.str, XPOS, AREA_LOCATE_Y-4, CGraphics::HCENTER);
			break;

	}
	_SUTIL->pFont->setOutline(false);


	s_AreaMessage.LifeTime--;
}
































