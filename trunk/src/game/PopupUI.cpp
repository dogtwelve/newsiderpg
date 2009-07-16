#include "PopupUi.h"


Page PopupUi::s_Page;
ItemList PopupUi::s_ItemList[5];
PlayMessage PopupUi::s_PlayMessage;
AreaMessage PopupUi::s_AreaMessage;
_TEXT_PACK* PopupUi::pCLRPOPUP_Text;

PopupUi::PopupUi(void* s__ASpriteSet,ASprite* _Hero)
{
	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // �׸���,ȿ�� ����Ʈ ��������Ʈ�� ������
	m_pHeroAs = _Hero;

	pCLRPOPUP_Text = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_CLRMENU_TEXT);//�ؽ�Ʈ �� �ε�
	pMAIN_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_MAIN_QUEST_TEXT);//���� ����Ʈ �� �ε�
	pSUB_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_SUB_QUEST_TEXT);//���� ����Ʈ �� �ε�
	pITEM_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_ITEM_TEXT);//����Ʈ �� �ε�
	s_Page.PageNum = 1;//ù ������

	//s_Quest.MainHave = 0;
	
	s_Quest.Max_Num = 0;
	/*s_Quest.SubHave[0] = 2;
	s_Quest.SubHave[1] = 3;
	s_Quest.SubHave[2] = 4;
	s_Quest.SubHave[3] = 5;
	s_Quest.SubHave[4] = 6;
	s_Quest.SubHave[5] = 7;
	s_Quest.SubHave[6] = 8;*/



	Character::s_ItemSlot[0].Data0 = 103;

	Character::s_ItemBag[0][0].Data0 = 201;
	Character::s_ItemBag[0][0].Data1 = 55;//1000000055;
	Character::s_ItemBag[0][1].Data0 = 204;
	Character::s_ItemBag[0][1].Data1 = 55;
/*
	Character::s_ItemBag[0][0].Data0 = 1024;			//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)
	Character::s_ItemBag[0][0].Data1 = 10101033;	//��񿩺�(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][0].Data2 = 230109;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][1].Data0 = 1124;
	Character::s_ItemBag[0][1].Data1 = 101022;	//��񿩺�(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][1].Data2 = 230710;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)

	Character::s_ItemBag[0][2].Data0 = 1224;
	Character::s_ItemBag[0][2].Data1 = 1031;	//��񿩺�(1),����3(2),����2(2),����1(2),���λ�(2),���(1)    -������ �ո������� 1, 2�̻��� �� �ѹ�
	Character::s_ItemBag[0][2].Data2 = 231111;			//��ũ�ѷ���(3),���Ƚ�ũ��(2),��ȭ(2)
*/
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
	if(m_keyRepeat)return true;
	if(m_keyCode == MH_KEY_4)m_keyCode=MH_KEY_LEFT;		//����ġ
	if(m_keyCode == MH_KEY_6)m_keyCode=MH_KEY_RIGHT;	//����ġ
	if(m_keyCode == MH_KEY_2)m_keyCode=MH_KEY_UP;		//����ġ
	if(m_keyCode == MH_KEY_8)m_keyCode=MH_KEY_DOWN;		//����ġ
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//����ġ



	if(GameOver){//���� �����϶�
		Key_GAMEOVER(m_keyCode, m_keyRepeat);
		return GameOver;
	}



	if(m_keyCode == MH_KEY_CLEAR && !s_Page.Focus && !s_Page.Ly1_sel)//������ �˾� ����
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
		case POPUP_PAGE_INVENTORY	: Key_INVENTORY(m_keyCode, m_keyRepeat)	; break;
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

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_TOP_TAP, XPOS,YPOS,0);//��
//	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_TOP_ICON_00 + (s_Page.PageNum - 1), XPOS-61 + 18*(s_Page.PageNum - 1),YPOS-82,0,0);//�� ������
	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_TITLE_00 + (s_Page.PageNum - 1), XPOS,YPOS-98,0,CGraphics::HCENTER);//�� ������


	_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����
	switch(s_Page.PageNum){//���α������
		case POPUP_PAGE_STATES		: Paint_STATES()	; break;
		case POPUP_PAGE_EQUIP		: Paint_EQUIP()		; break;
		case POPUP_PAGE_INVENTORY	: Paint_INVENTORY()	; break;
		case POPUP_PAGE_SKILL		: Paint_SKILL()		; break;
		case POPUP_PAGE_HOBBY		: Paint_HOBBY()		; break;
		case POPUP_PAGE_QUEST		: Paint_QUEST()		; break;
		case POPUP_PAGE_SYSTEM		: Paint_SYSTEM()	; break;

		case POPUP_PAGE_ITEMSHOP	: Paint_ITEMSHOP()	; break;
	}

	if (s_Page.Ly1_sel==0)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_TAP, XPOS-62 + 18*(s_Page.PageNum - 1),YPOS-83,0);//�� Ŀ��

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
		switch(s_Page.Ly1_sel){
			case 0://ž�޴�
				if(m_keyCode == MH_KEY_LEFT){
					s_Page.PageNum = POPUP_PAGE_MAX;
					Page_init();
				}else if(m_keyCode == MH_KEY_RIGHT){
					s_Page.PageNum++;
					Page_init();
				}else if(m_keyCode == MH_KEY_SELECT){
					s_Page.Ly1_sel++;
				}
				break;
			case 1://Ÿ��Ʋ
				if(m_keyCode == MH_KEY_SELECT){

				}
				break;
			case 2://��
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.STR++;
					}
				}
				break;
			case 3://��ø
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.DEX++;
					}
				}
				break;
			case 4://ü��
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.CON++;
					}
				}
				break;
			case 5://����
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.INT++;
					}
				}
				break;
		}
		if(m_keyCode == MH_KEY_UP){
			if(s_Page.Ly1_sel>0)s_Page.Ly1_sel--;
			if(PAGE_STATES_point[0]-Character::s_Ability.POINT > 0)s_Page.Ly1_sel = MAX(s_Page.Ly1_sel,2);
		}else if(m_keyCode == MH_KEY_DOWN){
			if(s_Page.Ly1_sel<5)s_Page.Ly1_sel++;
		}else if(m_keyCode == MH_KEY_CLEAR){//������ �˾� ȣ��
			if(PAGE_STATES_point[0]-Character::s_Ability.POINT > 0 && s_Page.Ly1_sel>1){
				s_Page.Focus = 1;
				s_Page.Ly2_sel = 1;//yes
			}else{
				s_Page.Ly1_sel=0;
			}
		}

		if(PAGE_STATES_point[0]> 0 && Character::s_Ability.POINT ==0){//Ȯ�� �˾� ȣ��
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
			s_Page.Ly1_sel=0;

			if(s_Page.Ly2_sel){//No - �ǵ�����
				 Character::s_Ability.POINT=PAGE_STATES_point[0];
				 Character::s_Ability.STR  =PAGE_STATES_point[1];
				 Character::s_Ability.DEX  =PAGE_STATES_point[2];
				 Character::s_Ability.CON  =PAGE_STATES_point[3];
				 Character::s_Ability.INT  =PAGE_STATES_point[4];
			}else{//Yes - ���� ���¸� ���
				PAGE_STATES_point[0] = Character::s_Ability.POINT;
				PAGE_STATES_point[1] = Character::s_Ability.STR;
				PAGE_STATES_point[2] = Character::s_Ability.DEX;
				PAGE_STATES_point[3] = Character::s_Ability.CON;
				PAGE_STATES_point[4] = Character::s_Ability.INT;
			}
			

		}else if(m_keyCode == MH_KEY_CLEAR){//�ø� ���� ���

			s_Page.Focus = 0;//�˾�����

			Character::s_Ability.POINT=PAGE_STATES_point[0];
			Character::s_Ability.STR  =PAGE_STATES_point[1];
			Character::s_Ability.DEX  =PAGE_STATES_point[2];
			Character::s_Ability.CON  =PAGE_STATES_point[3];
			Character::s_Ability.INT  =PAGE_STATES_point[4];

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
					case MH_KEY_DOWN:SELECT_EQUIP_Y++;SELECT_EQUIP_JAB_BACUP = Character::s_Status.ELEMENTAL;break;
				}
				break;
			case 1://��� ����
				switch(m_keyCode){
					case MH_KEY_RIGHT:
						switch(SELECT_EQUIP_POS){
							case 4:
								if(Character::s_Ability.JAB_KNIFE){SELECT_EQUIP_POS=5;}else{SELECT_EQUIP_POS=7;}
								break;
							case 7:
								if(Character::s_Ability.JAB_GUN	){
									SELECT_EQUIP_POS=8;
								}else if(Character::s_Ability.JAB_MAGIC){
									SELECT_EQUIP_POS=9;
								}else{
									SELECT_EQUIP_POS=0;
								}
								break;			
							case 8:
								if(Character::s_Ability.JAB_MAGIC){
									SELECT_EQUIP_POS=9;
								}else{
									SELECT_EQUIP_POS=0;
								}
								break;	
							case 9:SELECT_EQUIP_POS=0;break;
							default:SELECT_EQUIP_POS++;break;
						}
						Character::s_Status.ELEMENTAL = (SELECT_EQUIP_POS==5? 0 :(SELECT_EQUIP_POS==6? 0 :(SELECT_EQUIP_POS==8? 1 :(SELECT_EQUIP_POS==9? 2 :Character::s_Status.ELEMENTAL))));
						break;
					case MH_KEY_LEFT:
						switch(SELECT_EQUIP_POS){
							case 7:
								if(Character::s_Ability.JAB_KNIFE){SELECT_EQUIP_POS=6;}else{SELECT_EQUIP_POS=4;}
								break;
							case 0:
								if(Character::s_Ability.JAB_MAGIC){
									SELECT_EQUIP_POS=9;
								}else if(Character::s_Ability.JAB_GUN){
									SELECT_EQUIP_POS=8;
								}else{
									SELECT_EQUIP_POS=7;
								}
								break;						
							default:SELECT_EQUIP_POS--;break;
						}
						Character::s_Status.ELEMENTAL = (SELECT_EQUIP_POS==5? 0 :(SELECT_EQUIP_POS==6? 0 :(SELECT_EQUIP_POS==8? 1 :(SELECT_EQUIP_POS==9? 2 :Character::s_Status.ELEMENTAL))));
						break;
					case MH_KEY_DOWN:
						switch(SELECT_EQUIP_POS){
							case 0:SELECT_EQUIP_POS=3;break;
							case 1:
								if(Character::s_Ability.JAB_KNIFE){
									SELECT_EQUIP_POS=5;
								}else if(Character::s_Ability.JAB_GUN){
									SELECT_EQUIP_POS=8;
								}
								break;
							case 2:
								if(Character::s_Ability.JAB_KNIFE){
									SELECT_EQUIP_POS=6;
								}else if(Character::s_Ability.JAB_MAGIC){
									SELECT_EQUIP_POS=9;
								}
								break;
							case 3:SELECT_EQUIP_POS=4;break;
							case 4:SELECT_EQUIP_POS=7;break;
							case 5:
								if(Character::s_Ability.JAB_GUN){SELECT_EQUIP_POS=8;}else{SELECT_EQUIP_POS=1;}
								break;
							case 6:
								if(Character::s_Ability.JAB_MAGIC){SELECT_EQUIP_POS=9;}else{SELECT_EQUIP_POS=2;}
								break;
							case 7:SELECT_EQUIP_POS=0;break;
							case 8:SELECT_EQUIP_POS=1;break;
							case 9:SELECT_EQUIP_POS=2;break;
						}
						Character::s_Status.ELEMENTAL = (SELECT_EQUIP_POS==5? 0 :(SELECT_EQUIP_POS==6? 0 :(SELECT_EQUIP_POS==8? 1 :(SELECT_EQUIP_POS==9? 2 :Character::s_Status.ELEMENTAL))));
						break;
					case MH_KEY_UP:
						switch(SELECT_EQUIP_POS){
							case 0:SELECT_EQUIP_POS=7;break;
							case 1:
								if(Character::s_Ability.JAB_GUN){
									SELECT_EQUIP_POS=8;
								}else if(Character::s_Ability.JAB_KNIFE){
									SELECT_EQUIP_POS=5;
								}
								break;
							case 2:
								if(Character::s_Ability.JAB_MAGIC){
									SELECT_EQUIP_POS=9;
								}else if(Character::s_Ability.JAB_KNIFE){
									SELECT_EQUIP_POS=6;
								}
								break;
							case 3:SELECT_EQUIP_POS=0;break;
							case 4:SELECT_EQUIP_POS=3;break;
							case 5:SELECT_EQUIP_POS=1;break;
							case 6:SELECT_EQUIP_POS=2;break;
							case 7:SELECT_EQUIP_POS=4;break;
							case 8:
								if(Character::s_Ability.JAB_KNIFE){SELECT_EQUIP_POS=5;}else{SELECT_EQUIP_POS=1;}
								break;
							case 9:
								if(Character::s_Ability.JAB_KNIFE){SELECT_EQUIP_POS=6;}else{SELECT_EQUIP_POS=2;}
								break;
						}
						Character::s_Status.ELEMENTAL = (SELECT_EQUIP_POS==5? 0 :(SELECT_EQUIP_POS==6? 0 :(SELECT_EQUIP_POS==8? 1 :(SELECT_EQUIP_POS==9? 2 :Character::s_Status.ELEMENTAL))));
						break;
					case MH_KEY_CLEAR:
						SELECT_EQUIP_Y = 0;
						Character::s_Status.ELEMENTAL = SELECT_EQUIP_JAB_BACUP;
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
								case ITEM_AXE	:
								case ITEM_GUN	:
								case ITEM_OEB	:
								case ITEM_HEAD	:
								case ITEM_CHEST	:
								case ITEM_LEG	:
								case ITEM_GLOVE	:
								case ITEM_NECK	:
								case ITEM_RING	://3
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_EQUIP;
									break;
								case ITEM_MAINQUEST:
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_DEFAULT;
									//����Ҽ����� �Ϲ��ۿ� �޼���
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
							QSLOT_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}else if(SELECT_INVENTORY_POPUP_Y==2){//����
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==3){//�̵�
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
					case INVENTORY_POPUP_EQUIP:
						if(SELECT_INVENTORY_POPUP_Y==0){//����
							int xx;
							switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//������ ������ ��ȭ
								case ITEM_BAG	:
									MOVE_item();
									s_Page.Focus = 1;//�˾�ȣ��
									SELECT_INVENTORY_Y=1;//���� ���� ������ �̵�
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_BAGCHANGE;//���� ���� ����
									return;//������ �߰�UI�� �����Ƿ� ��Ż�Ѵ�
								case ITEM_SWORD	:
								case ITEM_AXE	:
									if(Character::s_ItemEquip[5].ITEM_KIND){//5�� ������ ���ִٸ� ������ 6�� ������ ä���
										xx = 6;
									}else{
										xx = 5;
									}
									break;
								case ITEM_GUN	:xx = 8;break;
								case ITEM_OEB	:xx = 9;break;
								case ITEM_HEAD	:xx = 0;break;
								case ITEM_CHEST	:xx = 3;break;
								case ITEM_LEG	:xx = 7;break;
								case ITEM_GLOVE	:xx = 4;break;
								case ITEM_NECK	:xx = 1;break;
								case ITEM_RING	:xx = 2;break;
							}

							EQUIP_item(xx,&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
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
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=2;break;
					case INVENTORY_POPUP_DEFAULT:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=1;break;
				}
				break;
			case MH_KEY_DOWN:
				SELECT_INVENTORY_POPUP_Y++;
				switch(SELECT_INVENTORY_POPUP_KIND){//�˾��� ����
					case INVENTORY_POPUP_QUICK:if(SELECT_INVENTORY_POPUP_Y>3)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y>2)SELECT_INVENTORY_POPUP_Y=0;break;
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
					case MH_KEY_DOWN:SELECT_SKILL_Y++;	break;
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
					case MH_KEY_DOWN:SELECT_SKILL_Y++;SELECT_SKILL_SLOT=0;SELECT_SKILL_KIND_NOW=-1;SELECT_SKILL_KIND=-1;	break;
				}
				break;
			case 2://���� ����
				if(SELECT_SKILL_ACT_PAS){//�нú�

					
					switch(m_keyCode){
						case MH_KEY_LEFT:SELECT_SKILL_SLOT+=8;	break;
						case MH_KEY_RIGHT:SELECT_SKILL_SLOT++;	break;
						case MH_KEY_UP:
							(SELECT_SKILL_SLOT<3?SELECT_SKILL_Y--:SELECT_SKILL_SLOT-=3);
							break;
						case MH_KEY_DOWN:SELECT_SKILL_SLOT+=3;	break;
						case MH_KEY_SELECT:
							if(SELECT_SKILL_KIND_NOW>=0){
								int xx = Character::s_Skill.Equip_P[SELECT_SKILL_SLOT];
								Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]=SELECT_SKILL_KIND_NOW;
								SELECT_SKILL_KIND_NOW = xx;
								Character::Set_state_calculate();//����� �������ͽ� ����
							}else{
								SELECT_SKILL_Y++;	
							}
							break;
						case MH_KEY_CLEAR:
							if(SELECT_SKILL_KIND_NOW>=0){
								SELECT_SKILL_KIND_NOW=-1;
								Character::Set_state_calculate();//����� �������ͽ� ����(�����Ȱ��� �� ���� ����)
							}else{
								SELECT_SKILL_Y--;		
							}
							break;
					}
					SELECT_SKILL_SLOT%=9;
				}else{//��Ƽ��
				
					switch(m_keyCode){
						case MH_KEY_LEFT:SELECT_SKILL_SLOT+=4;	break;
						case MH_KEY_RIGHT:SELECT_SKILL_SLOT++;	break;
						case MH_KEY_UP:SELECT_SKILL_Y--;		break;
						case MH_KEY_DOWN:SELECT_SKILL_Y++;		break;
						case MH_KEY_SELECT:
							if(SELECT_SKILL_KIND_NOW>=0){
								int xx = Character::s_Skill.Equip_A[SELECT_SKILL_SLOT];
								Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]=SELECT_SKILL_KIND_NOW;
								SELECT_SKILL_KIND_NOW = xx;
							}else{
								SELECT_SKILL_Y++;	
							}
							break;
						case MH_KEY_CLEAR:
							if(SELECT_SKILL_KIND_NOW>=0){
								SELECT_SKILL_KIND_NOW=-1;
							}else{
								SELECT_SKILL_Y--;		
							}
							break;
					}
					SELECT_SKILL_SLOT%=5;
				}
				break;
			case 3://���� ����

				if(SELECT_SKILL_ACT_PAS){//�нú�
					int jab_Max = 1+Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
					switch(m_keyCode){
						case MH_KEY_SELECT:
						case MH_KEY_RIGHT:SELECT_SKILL_Y++;SELECT_SKILL_KIND=0;	break;
						case MH_KEY_UP:SELECT_SKILL_TYPE+=jab_Max-1;	break;
						case MH_KEY_DOWN:SELECT_SKILL_TYPE++;	break;
						case MH_KEY_CLEAR:SELECT_SKILL_Y--;SELECT_SKILL_KIND_NOW=-1;	break;
					}
					SELECT_SKILL_TYPE%=jab_Max;
				}else{//��Ƽ��
					int jab_Max = Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
					switch(m_keyCode){
						case MH_KEY_SELECT:
						case MH_KEY_RIGHT:SELECT_SKILL_Y++;SELECT_SKILL_KIND=0;	break;
						case MH_KEY_UP:SELECT_SKILL_TYPE+=jab_Max-1;	break;
						case MH_KEY_DOWN:SELECT_SKILL_TYPE++;	break;
						case MH_KEY_CLEAR:SELECT_SKILL_Y--;SELECT_SKILL_KIND_NOW=-1;	break;
					}
					SELECT_SKILL_TYPE%=jab_Max;
				}
				break;
			case 4://��ų ����
				int skill_Max=0;
				if(SELECT_SKILL_ACT_PAS){//�нú�

					for(int xx = 0;xx<7;xx++){
						switch(SELECT_SKILL_TYPE_NOW){
							case 0:if(Character::s_Skill.Level_P[xx])skill_Max++;break;//Į �нú� ��ų����
							case 1:if(Character::s_Skill.Level_P[7+xx])skill_Max++;break;//�� �нú� ��ų����
							case 2:if(Character::s_Skill.Level_P[14+xx])skill_Max++;break;//�� �нú� ��ų����
							case 3:if(Character::s_Skill.Level_P[21+xx])skill_Max++;break;//�� �нú� ��ų����
						}
					}
					
				}else{//��Ƽ��

					for(int xx = 0;xx<7;xx++){
						switch(SELECT_SKILL_TYPE_NOW){
							case 0:if(Character::s_Skill.Level_A[xx])skill_Max++;break;//Į �нú� ��ų����
							case 1:if(Character::s_Skill.Level_A[7+xx])skill_Max++;break;//�� �нú� ��ų����
							case 2:if(Character::s_Skill.Level_A[14+xx])skill_Max++;break;//�� �нú� ��ų����
						}
					}
				}
				switch(m_keyCode){
					case MH_KEY_SELECT://��ġ�� ����� �ִٸ� -1(����) �� ���ش�
						if(SELECT_SKILL_ACT_PAS){//�нú�
							for(int xx = 0;xx<9;xx++){
								if(SELECT_SKILL_KIND_NOW == Character::s_Skill.Equip_P[xx])Character::s_Skill.Equip_P[xx]=-1;
							}
							Character::Set_state_calculate();//����� �������ͽ� ����(�����Ȱ��� �� ���� ����)
						}else{//��Ƽ��
							SkillChange_A = true;
							for(int xx = 0;xx<5;xx++)
								if(SELECT_SKILL_KIND_NOW == Character::s_Skill.Equip_A[xx])Character::s_Skill.Equip_A[xx]=-1;
						}

						SELECT_SKILL_Y=2;
						
						
						break;
					case MH_KEY_LEFT:if(SELECT_SKILL_KIND==0)SELECT_SKILL_Y--;
						SELECT_SKILL_KIND+=skill_Max-1;
						break;
					case MH_KEY_RIGHT:SELECT_SKILL_KIND++;		break;
					case MH_KEY_UP:if(0 <= (SELECT_SKILL_KIND-4))	SELECT_SKILL_KIND-=4;break;
					case MH_KEY_DOWN:if(skill_Max > (SELECT_SKILL_KIND+4))	SELECT_SKILL_KIND+=4;break;
					case MH_KEY_CLEAR:SELECT_SKILL_Y--;		break;
				}
				if(skill_Max)SELECT_SKILL_KIND%=skill_Max;//���ε���̽� �ͼ��� �߻����ɼ�����
				break;
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
				Character::s_Status.LEVEL++;
				Character::s_Ability.POINT += 3;
				Character::s_Ability.STR+=2;
				Character::s_Ability.DEX+=2;
				Character::s_Ability.CON+=2;
				Character::s_Ability.INT+=2;
				Character::Set_state_calculate();
				Character::s_Status.LIFE = Character::s_Status.LIFE_MAX;
				Character::s_Status.MANA = Character::s_Status.MANA_MAX;
				break;
			case MH_KEY_UP:Character::s_Status.LIFE=99999999;break;//������
			case MH_KEY_3:Character::s_Status.MANA=99999999;break;
			case MH_KEY_LEFT:
				Character::s_Skill_Set.Cool_TimeMax[0]=0;Character::s_Skill_Set.Cool_TimeNow[0]=0;
				Character::s_Skill_Set.Cool_TimeMax[1]=0;Character::s_Skill_Set.Cool_TimeNow[1]=0;
				Character::s_Skill_Set.Cool_TimeMax[2]=0;Character::s_Skill_Set.Cool_TimeNow[2]=0;
				Character::s_Skill_Set.Cool_TimeMax[3]=0;Character::s_Skill_Set.Cool_TimeNow[3]=0;
				Character::s_Skill_Set.Cool_TimeMax[4]=0;Character::s_Skill_Set.Cool_TimeNow[4]=0;
				Character::s_Skill_Set.Cool_TimeMax[5]=0;Character::s_Skill_Set.Cool_TimeNow[5]=0;
				break;//������
			case MH_KEY_CLEAR:s_Page.Focus=0;break;
			case MH_KEY_SELECT:
				Character::s_Ability.STR=9999;
				Character::s_Ability.DEX=9999;
				Character::s_Ability.CON=9999;
				Character::s_Ability.INT=9999;
				Character::Set_state_calculate();
				Character::s_Status.LIFE = Character::s_Status.LIFE_MAX;
				Character::s_Status.MANA = Character::s_Status.MANA_MAX;

				for(int xx = 0;xx<21;xx++){
					Character::s_Skill.Level_A[xx]=1;	//��Ƽ�� ��ų����
				}
				Character::s_Ability.JAB_KNIFE	=true;	//�˻� - ���� ���� �����ϴٸ� true
				Character::s_Ability.JAB_GUN	=true;	//�ѻ� - ���� ���� �����ϴٸ� true
				Character::s_Ability.JAB_MAGIC	=true;	//���� - ���� ���� �����ϴٸ� true


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
				Character::s_Status.LIFE = Character::s_Status.LIFE_MAX;
				Character::s_Status.MANA = Character::s_Status.MANA_MAX;
				for(int xx =0 ;xx<5;xx++)Character::s_Skill_Set.Cool_TimeNow[xx]=0;
			}
			break;
	}
	if(m_keyCode == MH_KEY_UP){
		if(SELECT_SKILL_Y>0)SELECT_SKILL_Y--;
		if(PAGE_STATES_point[0]-Character::s_Ability.POINT > 0)s_Page.Ly1_sel = MAX(s_Page.Ly1_sel,2);
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
			case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
			case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
			case MH_KEY_SELECT:
			case MH_KEY_DOWN:SELECT_ITEMSHOP_Y++;break;
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
				switch(m_keyCode){
			case MH_KEY_CLEAR:SELECT_ITEMSHOP_Y = 1;break;
			case MH_KEY_SELECT:

				if(Character::s_ItemPick.ITEM_KIND){//����ִ� �������� �ִٸ�
					MOVE_item();//Ŀ���� �κ��� ������ ��ü
				}else if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data0){//Ŀ���� ����Ű�� �������� ���ٸ� �˾��� �׸����ʴ´�

					s_Page.Focus = 1;//�˾�ȣ��
					SELECT_ITEMSHOP_POPUP_Y=0;

					switch(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//������ ������ ��ȭ
			case ITEM_POTION://4
				SELECT_ITEMSHOP_POPUP_KIND = INVENTORY_POPUP_QUICK;
				break;

			case ITEM_BAG	:
			case ITEM_SWORD	:
			case ITEM_AXE	:
			case ITEM_GUN	:
			case ITEM_OEB	:
			case ITEM_HEAD	:
			case ITEM_CHEST	:
			case ITEM_LEG	:
			case ITEM_GLOVE	:
			case ITEM_NECK	:
			case ITEM_RING	://3
				SELECT_ITEMSHOP_POPUP_KIND = INVENTORY_POPUP_EQUIP;
				break;
			case ITEM_MAINQUEST:
				SELECT_ITEMSHOP_POPUP_KIND = INVENTORY_POPUP_DEFAULT;
				//����Ҽ����� �Ϲ��ۿ� �޼���
				break;

					}
				}
				break;
			case MH_KEY_UP:
				if(SELECT_ITEMSHOP_INSIDE<8){
					SELECT_ITEMSHOP_Y--;
				}else{
					SELECT_ITEMSHOP_INSIDE-=8;
				}
				break;
			case MH_KEY_DOWN:SELECT_ITEMSHOP_INSIDE+=8;break;
			case MH_KEY_LEFT:SELECT_ITEMSHOP_INSIDE--;break;
			case MH_KEY_RIGHT:SELECT_ITEMSHOP_INSIDE++;break;
				}
				switch(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG].Data0){//���� ������ Kind Num�� 1�̴�
			case 100:SELECT_ITEMSHOP_INSIDE +=  8;SELECT_ITEMSHOP_INSIDE %=  8;break;
			case 101:SELECT_ITEMSHOP_INSIDE += 16;SELECT_ITEMSHOP_INSIDE %= 16;break;
			case 102:SELECT_ITEMSHOP_INSIDE += 24;SELECT_ITEMSHOP_INSIDE %= 24;break;
			case 103:SELECT_ITEMSHOP_INSIDE += 32;SELECT_ITEMSHOP_INSIDE %= 32;break;
				}

		}
	}else if(s_Page.Focus == 1){// �˾� - �����ۺ� ���� �˾�ȣ��


		switch(m_keyCode){
			case MH_KEY_CLEAR:
				if(SELECT_ITEMSHOP_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){
					SELECT_ITEMSHOP_BAG = 0;
				}
				s_Page.Focus = 0;
				break;
			case MH_KEY_SELECT:
				switch(SELECT_ITEMSHOP_POPUP_KIND){//�˾��� ����
			case INVENTORY_POPUP_QUICK:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//���
					USE_item(&Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
					s_Page.Focus = 0;
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//������
					QSLOT_item(&Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
					s_Page.Focus = 0;
				}else if(SELECT_ITEMSHOP_POPUP_Y==2){//����
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==3){//�̵�
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
			case INVENTORY_POPUP_EQUIP:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//����
					int xx;
					switch(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//������ ������ ��ȭ
			case ITEM_BAG	:
				MOVE_item();
				s_Page.Focus = 1;//�˾�ȣ��
				SELECT_ITEMSHOP_Y=1;//���� ���� ������ �̵�
				SELECT_ITEMSHOP_POPUP_KIND = INVENTORY_POPUP_BAGCHANGE;//���� ���� ����
				return;//������ �߰�UI�� �����Ƿ� ��Ż�Ѵ�
			case ITEM_SWORD	:
			case ITEM_AXE	:
				if(Character::s_ItemEquip[5].ITEM_KIND){//5�� ������ ���ִٸ� ������ 6�� ������ ä���
					xx = 6;
				}else{
					xx = 5;
				}
				break;
			case ITEM_GUN	:xx = 8;break;
			case ITEM_OEB	:xx = 9;break;
			case ITEM_HEAD	:xx = 0;break;
			case ITEM_CHEST	:xx = 3;break;
			case ITEM_LEG	:xx = 7;break;
			case ITEM_GLOVE	:xx = 4;break;
			case ITEM_NECK	:xx = 1;break;
			case ITEM_RING	:xx = 2;break;
					}

					EQUIP_item(xx,&Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
					s_Page.Focus = 0;
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//����
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==2){//�̵�
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
			case INVENTORY_POPUP_BAGCHANGE://���� ��ü �Ǵ� ����
				MOVE_item();//�κ� ����� ��ü
				break;
			case INVENTORY_POPUP_DEFAULT:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//����
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//�̵�
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
				}

				break;
			case MH_KEY_UP:
				SELECT_ITEMSHOP_POPUP_Y--;
				switch(SELECT_ITEMSHOP_POPUP_KIND){//�˾��� ����
			case INVENTORY_POPUP_QUICK:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=3;break;
			case INVENTORY_POPUP_EQUIP:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=2;break;
			case INVENTORY_POPUP_DEFAULT:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=1;break;
				}
				break;
			case MH_KEY_DOWN:
				SELECT_ITEMSHOP_POPUP_Y++;
				switch(SELECT_ITEMSHOP_POPUP_KIND){//�˾��� ����
			case INVENTORY_POPUP_QUICK:if(SELECT_ITEMSHOP_POPUP_Y>3)SELECT_ITEMSHOP_POPUP_Y=0;break;
			case INVENTORY_POPUP_EQUIP:if(SELECT_ITEMSHOP_POPUP_Y>2)SELECT_ITEMSHOP_POPUP_Y=0;break;
			case INVENTORY_POPUP_DEFAULT:if(SELECT_ITEMSHOP_POPUP_Y>1)SELECT_ITEMSHOP_POPUP_Y=0;break;
				}
				break;
			case MH_KEY_LEFT:
				switch(SELECT_ITEMSHOP_POPUP_KIND){//�˾��� ����
			case INVENTORY_POPUP_BAGCHANGE:
				int leftBag = (SELECT_ITEMSHOP_BAG+3)%4;

				if(Character::s_ItemSlot[leftBag].ITEM_KIND){ SELECT_ITEMSHOP_BAG=leftBag;}
				else{
					for (int xx = 0;xx<4;xx++){
						if(Character::s_ItemSlot[xx].ITEM_KIND==0){
							SELECT_ITEMSHOP_BAG = xx;break;
						}
					}
				}
				break;
				}
				break;
			case MH_KEY_RIGHT:
				switch(SELECT_ITEMSHOP_POPUP_KIND){//�˾��� ����
			case INVENTORY_POPUP_BAGCHANGE:
				int rightBag = (SELECT_ITEMSHOP_BAG+1)%4;
				if(Character::s_ItemSlot[rightBag].ITEM_KIND) {SELECT_ITEMSHOP_BAG=rightBag;}
				else{
					for (int xx = 0;xx<4;xx++){
						if(Character::s_ItemSlot[xx].ITEM_KIND==0){
							SELECT_ITEMSHOP_BAG = xx;break;
						}
					}
				}
				break;
				}
				break;

		}

	}else if(s_Page.Focus == 2){// ����˾� - �Ұ����� ��ü, �����⸦ ������ ��� ����
		switch(SELECT_ITEMSHOP_POPUP_TEXT_KIND){//�˾��� ����
			case INVENTORY_TEXT_POPUP__NOT_ENOUGH:
				switch(m_keyCode){
			case MH_KEY_SELECT:s_Page.Focus = 1;break;
				}
				break;
			case INVENTORY_TEXT_POPUP__ABANDON:
				switch(m_keyCode){
			case MH_KEY_SELECT:
				if(SELECT_ITEMSHOP_POPUP_TEXT_YESNO){//no
					s_Page.Focus = 0;
				}else{//yes
					DEL_item();
				}
				break;
			case MH_KEY_LEFT:
				SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 0;break;
			case MH_KEY_RIGHT:
				SELECT_ITEMSHOP_POPUP_TEXT_YESNO = 1;break;
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
void PopupUi::Paint_STATES()	
{
	
	
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_1, XPOS, YPOS, 0);//CLRMENU
	

//���� ���
	if (s_Page.Ly1_sel==0){
		PAGE_STATES_point[0] = Character::s_Ability.POINT;
		PAGE_STATES_point[1] = Character::s_Ability.STR;
		PAGE_STATES_point[2] = Character::s_Ability.DEX;
		PAGE_STATES_point[3] = Character::s_Ability.CON;
		PAGE_STATES_point[4] = Character::s_Ability.INT;
	}

//Ŀ��
	if (s_Page.Ly1_sel==1)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_4, XPOS+7, YPOS-64, 0);//ȣĪ Ŀ��
	if (s_Page.Ly1_sel>=2)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_1, XPOS-71, YPOS+21 + (13*(s_Page.Ly1_sel-2)), 0);//���� Ŀ��

//�ɸ��� ���ż� �����ֱ�
	_SUTIL->g->SetClip(XPOS-70,YPOS-64,49,64);	
	switch(Character::s_Status.ELEMENTAL){
		case 0:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//�ɸ���
			break;
		case 1:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//�ɸ���
			break;
		case 2:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//�ɸ���
			break;
	}
	_SUTIL->g->ResetClip();

//�Ӽ�
	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs,MODULE_UI_ELEMENTAL_00+Character::s_Status.ELEMENTAL, XPOS-12, YPOS-63,0,0);

	// char hp
	PaintGage(GAGE_RED, 58, XPOS+5, YPOS-40, Character::s_Status.LIFE, Character::s_Status.LIFE_MAX);
	// char mp
	PaintGage(GAGE_BLUE, 58, XPOS+5, YPOS-28, Character::s_Status.MANA, Character::s_Status.MANA_MAX);
	// char exp
	PaintGage(GAGE_YELLOW, 58, XPOS+5, YPOS-16, Character::s_Status.EXP, Character::s_Status.EXP_MAX);

	for(int xx = 0, ABIL = 0;xx<4;xx++){
		ABIL = (xx == 0 ? Character::s_Ability.STR :(xx == 1 ? Character::s_Ability.DEX :(xx == 2 ? Character::s_Ability.CON :Character::s_Ability.INT)));
		_SUTIL->pFont->setColor(0x93abc0);

		if(xx == (s_Page.Ly1_sel-2)){
			_SUTIL->pFont->setColor(0x00c9fc);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TEXT_STR+xx], XPOS-68, YPOS+81, 0);//Text
		}

		if(PAGE_STATES_point[xx+1] - ABIL)
			_SUTIL->pFont->setOutlineColor((xx == (s_Page.Ly1_sel-2)? 0x003e9a: 0x202020));//������ ���̸� �ƿ������� ���

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_POWER+xx], XPOS-66, YPOS+33 + (13*xx), CGraphics::BOTTOM);//��//��ø//ü��//����
		_SUTIL->pFont->DrawText(_SUTIL->g, ABIL, XPOS-9, YPOS+33 + (13*xx), CGraphics::RIGHT|CGraphics::BOTTOM);//��//��ø//ü��//����

		_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����
	} 

	//ȣĪ
	_SUTIL->pFont->setColor(0xf8e6cb);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TITLETEMP], XPOS+37, YPOS-61, CGraphics::HCENTER);//ȣĪ

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.LIFE,  XPOS+33, YPOS-46, 1 , CGraphics::RIGHT);//HP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.LIFE_MAX,  XPOS+59, YPOS-46, 1 , CGraphics::RIGHT);//HP MAX

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.MANA,  XPOS+33, YPOS-34, 1 , CGraphics::RIGHT);//MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.MANA_MAX,  XPOS+59, YPOS-34, 1 , CGraphics::RIGHT);//MP MAX

	//EXP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.EXP_MAX-Character::s_Status.EXP,  XPOS+59, YPOS-46+2*12, 1 , CGraphics::RIGHT);//HP,MP,EXP MAX

	//LV
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_LEVEL, XPOS-18,YPOS-8,0);//�˾� ������ ����
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM, Character::s_Status.LEVEL,  XPOS-5, YPOS-8, 0 , 0);


	
	
	//��ġ,//����Ʈ
	_SUTIL->pFont->setColor(0xf8e6cb);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_POINTS], XPOS-67, YPOS+7, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_REPUTATION], XPOS+6, YPOS+7, 0);
	_SUTIL->pFont->setColor(0xffc708);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Ability.POINT, XPOS-9, YPOS+7, CGraphics::RIGHT);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Ability.FAM, XPOS+67, YPOS+7, CGraphics::RIGHT);
	
	
	_SUTIL->pFont->setColor(0xffc000);
	//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ATT1 + Character::s_Status.ELEMENTAL], XPOS+6, YPOS+21, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL], XPOS+67, YPOS+21, CGraphics::RIGHT);
	
	_SUTIL->pFont->setColor(0x93abc0);
	//Att2
	bool jab_check[3] = {Character::s_Ability.JAB_KNIFE,Character::s_Ability.JAB_GUN,Character::s_Ability.JAB_MAGIC};
	if(jab_check[(Character::s_Status.ELEMENTAL+1)%3]){
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ATT1 + (Character::s_Status.ELEMENTAL+1)%3], XPOS+6, YPOS+32, 0);
		_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.ATTACK_MAX[(Character::s_Status.ELEMENTAL+1)%3], XPOS+67, YPOS+32, CGraphics::RIGHT);
	}else if(jab_check[(Character::s_Status.ELEMENTAL+2)%3]){
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ATT1 + (Character::s_Status.ELEMENTAL+2)%3], XPOS+6, YPOS+32, 0);
		_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.ATTACK_MAX[(Character::s_Status.ELEMENTAL+2)%3], XPOS+67, YPOS+32, CGraphics::RIGHT);
	}
	//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DEF], XPOS+6, YPOS+43, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.DEFENSE, XPOS+67, YPOS+43, CGraphics::RIGHT);
	//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CRI], XPOS+6, YPOS+54, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_PERCENT], XPOS+59, YPOS+54, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.CRITICAL, XPOS+57, YPOS+54, CGraphics::RIGHT);
	//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_AGI], XPOS+6, YPOS+65, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_PERCENT], XPOS+59, YPOS+65, 0);
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.AVOID, XPOS+57, YPOS+65, CGraphics::RIGHT);

	if(s_Page.Focus == 1){// �˾� - �������ͽ� ���� ���� Ȯ��
		//_SUTIL->g->blandBlur();
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//�˾� ������ ����
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + s_Page.Ly2_sel, XPOS,YPOS,0);//�˾� ������ ����

		_SUTIL->pFont->setColor(0xf8e6cb);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q1], XPOS, YPOS+15, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
	}

}

void PopupUi::Paint_EQUIP()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_2, XPOS,YPOS,0);

//�ɸ��� ���ż� �����ֱ�
	_SUTIL->g->SetClip(XPOS-36,YPOS-61,49,64);	
	switch(Character::s_Status.ELEMENTAL){
		case 0:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//�ɸ���
			break;
		case 1:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//�ɸ���
			break;
		case 2:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//�ɸ���
			break;
	}
	_SUTIL->g->ResetClip();



	int Scroll_x = (SELECT_EQUIP_LIST_NOW-6 > 0?SELECT_EQUIP_LIST_NOW-6:0);

	SELECT_EQUIP_LIST_MAX = 0;

	for(int xx=0, Xpos=0, Ypos=0;xx<10;xx++){
		switch(xx){//�ش� ������ ������ ������ �׷��ְ� ���� ���ٸ� ��ŵ�Ѵ�.
			case 0:Xpos=-58	;Ypos=-62	;break;
			case 1:Xpos=20	;Ypos=-62	;break;
			case 2:Xpos=42	;Ypos=-62	;break;
			case 3:Xpos=-58	;Ypos=-44	;break;
			case 4:Xpos=-58	;Ypos=-26	;break;
			case 5:Xpos=20	;Ypos=-26	;
				if(Character::s_Ability.JAB_KNIFE){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//�� ����  ������
				}else{continue;}break;
			case 6:Xpos=42	;Ypos=-26	;
				if(Character::s_Ability.JAB_KNIFE){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//�� ����  ������
				}else{continue;}break;
			case 7:Xpos=-58	;Ypos=-8	;break;
			case 8:Xpos=20	;Ypos=-8	;
				if(Character::s_Ability.JAB_GUN){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//�� ����  ������
				}else{continue;}break;
			case 9:Xpos=42	;Ypos=-8	;
				if(Character::s_Ability.JAB_MAGIC){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//�� ����  ������
				}else{continue;}break;
		}

		//Ŀ�� �׸���
		if(xx == SELECT_EQUIP_POS && SELECT_EQUIP_Y>0){
			if(SELECT_EQUIP_Y == 1){
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+Xpos, YPOS+Ypos,0);//Ŀ��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5,XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+17,0);//��Ȱ�� Ŀ��
				s_Popup_Sharp.posX = XPOS+Xpos;
				s_Popup_Sharp.posY = YPOS+Ypos;

			}else{
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS+Xpos, YPOS+Ypos,0);//��Ȱ�� Ŀ��
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+17,0);//Ŀ��
				s_Popup_Sharp.posX = XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17);
				s_Popup_Sharp.posY = YPOS+17;
			}




			if(Character::s_ItemEquip[xx].ITEM_KIND){//�������� �ִٸ�

				if (Scroll_x==0){//��ũ���� �Ͼ�� �ʾ������� �׷��ش�
					paint_ICON(Character::s_ItemEquip[xx],XPOS-59, YPOS+17,true);
					if(SELECT_EQUIP_LIST_NOW == 0){
						equipTEXT(SELECT_EQUIP_POS,Character::s_ItemEquip[xx]);
						SELECT_EQUIP_LIST_NOW_BAG = -1;
						SELECT_EQUIP_LIST_NOW_SLOT = -1;
					}
				}
				SELECT_EQUIP_LIST_MAX++;
				
			}
		}

		//�����ܱ׸���
		if(Character::s_ItemEquip[xx].ITEM_KIND){//�������� �ִٸ�
			paint_ICON(Character::s_ItemEquip[xx],XPOS+Xpos, YPOS+Ypos,false);
		}else{//�������� ���ٸ�
			SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTY_00+(xx>5?xx-1:xx), XPOS+Xpos,YPOS+Ypos,0,0);//�� ����  ������
		}

	}

	



	
	if(SELECT_EQUIP_Y>0){//Ŀ���� ������ ������


	//���� ������ ��� ������ ����Ʈ������ �������ش�
		int Type;
		switch(SELECT_EQUIP_POS){//Ŀ���� �ִ� ������ ���� ������������ ġȯ�Ѵ�
			case 0:Type=ITEM_HEAD	;break;
			case 1:Type=ITEM_NECK	;break;
			case 2:Type=ITEM_RING	;break;
			case 3:Type=ITEM_CHEST	;break;
			case 4:Type=ITEM_GLOVE	;break;
			case 5:Type=ITEM_SWORD	;break;
			case 6:Type=ITEM_SWORD	;break;
			case 7:Type=ITEM_LEG	;break;
			case 8:Type=ITEM_GUN	;break;
			case 9:Type=ITEM_OEB	;break;
		}

		//������������ �������� ������� �����ش�
		for(int xx = 0;xx<4;xx++){
			for(int yy = 0;yy<32;yy++){//������ ���鼭 ����� �Ǵ� �������� �����Ѵ�.

				if(Character::s_ItemBag[xx][yy].ITEM_EQUIP == 0){// ������� ���� �������߿�
					int Kind = (Character::s_ItemBag[xx][yy].ITEM_KIND == ITEM_AXE ? ITEM_SWORD : Character::s_ItemBag[xx][yy].ITEM_KIND);

					if(Kind == Type){
						if((SELECT_EQUIP_LIST_MAX-Scroll_x)>=0 && (SELECT_EQUIP_LIST_MAX-Scroll_x)<=6){
							paint_ICON(Character::s_ItemBag[xx][yy],XPOS-59+((SELECT_EQUIP_LIST_MAX-Scroll_x)*17), YPOS+17,true);
						}
						if(SELECT_EQUIP_LIST_NOW == SELECT_EQUIP_LIST_MAX){
							
							SELECT_EQUIP_LIST_NOW_BAG = xx;//���� ���õ� �������� ������ ����
							SELECT_EQUIP_LIST_NOW_SLOT = yy;//���� ���õ� �������� ������ ����


							equipTEXT(SELECT_EQUIP_POS , Character::s_ItemBag[xx][yy]);

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
		equipTEXT(SELECT_EQUIP_POS,Character::s_ItemEquip[SELECT_EQUIP_POS]);
	}




	if(s_Popup_Sharp.View && SELECT_EQUIP_Y > 0){
		if(SELECT_EQUIP_Y == 1 || (SELECT_EQUIP_LIST_NOW_BAG == -1&&SELECT_EQUIP_LIST_NOW_SLOT == -1)){
			PaintPopup_Sharp(Character::s_ItemEquip[SELECT_EQUIP_POS]);
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
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_BAG_00+(Character::s_ItemSlot[xx].ITEM_INDEX), XPOS-68+(xx*17),YPOS-61,0,0);
	}

	_SUTIL->g->SetColor(0x5a657b);
	switch(Character::s_ItemSlot[SELECT_INVENTORY_BAG].Data0){
		case 100:
			_SUTIL->g->FillRect(XPOS-70,YPOS-24,138,51);
			break;
		case 101:
			_SUTIL->g->FillRect(XPOS-70,YPOS- 7,138,34);
			break;
		case 102:
			_SUTIL->g->FillRect(XPOS-70,YPOS+10,138,17);
			break;
		case 103:

			break;
	}

	//�����ݾ� �׸���
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status.MONEY,  XPOS+66, YPOS-58 , 1 , CGraphics::RIGHT);//MONEY


	//���� Ŀ�� 
	if(SELECT_INVENTORY_Y==1){
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			if(!(s_Page.Focus == 1 && SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE)){//������ �ٲܶ� �� ���� Ŀ���� ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//���� ����
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68+(SELECT_INVENTORY_BAG*17)	+6, 
				YPOS-61								-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-68+(SELECT_INVENTORY_BAG*17)+6, YPOS-61-4,true);
		}else{
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//���� ���� ANI
		}
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//���� ����
	}



	//�κ� Ŀ��
	if(SELECT_INVENTORY_Y==2){//�κ����� �������� ����
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			itemTEXT(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
		}
		if(Character::s_ItemPick.ITEM_KIND == 0){//Ŀ���� �������� ����� �׸���
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17), YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17),0);
			s_Popup_Sharp.posX = XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17);
			s_Popup_Sharp.posY = YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17);
		}
	}

	//���泻 �������� �׸��� 
	for(int xx = 0,MaxSlot = get_BagMax(Character::s_ItemSlot[SELECT_INVENTORY_BAG]);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			paint_ICON(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx], XPOS-68 + ((xx%8)*17), YPOS-40 + ((xx/8)*17),true);
		}
	}

	//�κ� Ŀ��
	if(SELECT_INVENTORY_Y==2){//�κ����� �������� ����
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17)+6, 
				YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17)+6,YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,true);
		}
	}


	if(s_Page.Focus == 1){// �˾� �׸��� - �����ۺ� ���� �˾�ȣ��


		int Px = -68 + ((SELECT_INVENTORY_INSIDE%8)*17) + (((SELECT_INVENTORY_INSIDE%8)<4) ? 24 : -49);
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

			case INVENTORY_POPUP_EQUIP	://3��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<3;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
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
	if(Character::s_Ability.JAB_KNIFE){
		Type[xx] = 1;xx++;
	}
	if(Character::s_Ability.JAB_GUN){
		Type[xx] = 2;xx++;
	}
	if(Character::s_Ability.JAB_MAGIC){
		Type[xx] = 3;xx++;
	}

	if(SELECT_SKILL_ACT_PAS){//�нú�
		Type[xx] = 4;//����
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1, XPOS,YPOS,0);

		if(true){//�нú� ������ ���ְ� ������
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1AFTER, XPOS,YPOS,0);
		}else{
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1BEFORE, XPOS,YPOS,0);
		}

		jab_Max = 1+Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
	}else{//��Ƽ��
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2, XPOS,YPOS,0);
		jab_Max = Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
	}

//Ŀ���� �ؽ�Ʈ�� �ѷ���
	_SUTIL->pFont->setColor(0xfbac29);//��Ƽ��,�нú�
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ACTIVE + SELECT_SKILL_ACT_PAS], XPOS, YPOS-59, CGraphics::HCENTER);

	for(int zz = 0;zz < MIN((jab_Max-1),2);zz++)
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI3, XPOS-63,YPOS+37+(zz*17),0);//���� ����â

	_SUTIL->pFont->setColor(0xb4fa1e);

	for(int yy = 0, findNum;yy < MIN(3,jab_Max);yy++){// ���� �ؽ�Ʈ
		if(SELECT_SKILL_Y==3 && !yy){
			_SUTIL->pFont->setOutline(true);
			_SUTIL->pFont->setOutlineColor((++ani_Num)%2?0x537a00:0x304a00);
		}
		findNum = (SELECT_SKILL_TYPE + yy) % jab_Max;
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SWORD+Type[findNum]-1], XPOS-65+(yy?7:0), YPOS+23+(17*yy), 0);
		if(!yy) _SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ACTIVE + SELECT_SKILL_ACT_PAS],5);  //DrawString(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SWORD+Type[findNum]-1], XPOS-65+(yy?7:0), YPOS+23+(17*yy), 0, true);
		_SUTIL->pFont->setOutline(false);
		_SUTIL->pFont->setColor(0x546779);
	}
	SELECT_SKILL_TYPE_NOW = Type[(SELECT_SKILL_TYPE) % jab_Max]-1;//���� ���õ� ����

	//������ �ѷ��ֱ� - ����
	if(SELECT_SKILL_ACT_PAS){//�нú�
		for(int xx = 0;xx<9;xx++){
			if(Character::s_Skill.Equip_P[xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00+Character::s_Skill.Equip_P[xx],
					XPOS-25 + ((xx%3)*18), 
					YPOS-37 + ((xx/3)*17),0);//���� ����â
		}
	}else{//��Ƽ��
		for(int xx = 0;xx<5;xx++){
			if(Character::s_Skill.Equip_A[xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+Character::s_Skill.Equip_A[xx],
				XPOS-63 + (xx*28), 
				YPOS-20, 0);
		}
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2COVER, XPOS,YPOS,0);//��ų����
	}


	int skill_Max=0;//������ �ѷ��ֱ� - ��ų
	if(SELECT_SKILL_ACT_PAS){//�нú�

		for(int xx = 0;xx<7;xx++){
			switch(SELECT_SKILL_TYPE_NOW){
				case 0:if(Character::s_Skill.Level_P[xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx;		skill_Max++;}break;//Į �нú� ��ų����
				case 1:if(Character::s_Skill.Level_P[7+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_G_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+7;	skill_Max++;}break;//�� �нú� ��ų����
				case 2:if(Character::s_Skill.Level_P[14+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_O_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+14;	skill_Max++;}break;//�� �нú� ��ų����
				case 3:if(Character::s_Skill.Level_P[21+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_N_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+21;	skill_Max++;}break;//�� �нú� ��ų����
			}
		}
	}else{//��Ƽ��

		for(int xx = 0;xx<7;xx++){
			switch(SELECT_SKILL_TYPE_NOW){ 
				case 0:if(Character::s_Skill.Level_A[xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx;		skill_Max++;}break;//Į �нú� ��ų����
				case 1:if(Character::s_Skill.Level_A[7+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_G_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+7;	skill_Max++;}break;//�� �нú� ��ų����
				case 2:if(Character::s_Skill.Level_A[14+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_O_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+14;	skill_Max++;}break;//�� �нú� ��ų����
			}
		}
	}


	


//Ŀ��
	if(s_Page.Focus == 0){
		switch(SELECT_SKILL_Y){
			case 1://��Ƽ�� �нú� ����
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_2, XPOS-28, YPOS-62, 0);
				break;
			case 2://���� ����
				if(SELECT_SKILL_ACT_PAS){//�нú�
					if(SELECT_SKILL_KIND_NOW>=0){//Ŀ���� �������� ����ִٸ� �׷��ش�
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00+SELECT_SKILL_KIND_NOW,
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
					if(SELECT_SKILL_KIND_NOW>=0){
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+SELECT_SKILL_KIND_NOW,
							XPOS-64+6 + (SELECT_SKILL_SLOT*28), 
							YPOS-21-4, 						0);
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
							XPOS-64+5 + (SELECT_SKILL_SLOT*28), 
							YPOS-21-5, 						0);
					}else{
						SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_5, 
							XPOS-64 + (SELECT_SKILL_SLOT*28), 
							YPOS-21, 						0);
					}
					s_Popup_Sharp.posX = XPOS-64 + (SELECT_SKILL_SLOT*28);
					s_Popup_Sharp.posY = YPOS-21;
				}

				
				break;
			case 4://��ų ����
					SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
						XPOS-14 + ((SELECT_SKILL_KIND%4)*18), 
						YPOS+36 + ((SELECT_SKILL_KIND/4)*17), 						0);
					s_Popup_Sharp.posX = XPOS-14 + ((SELECT_SKILL_KIND%4)*18);
					s_Popup_Sharp.posY = YPOS+36 + ((SELECT_SKILL_KIND/4)*17);
			case 3:
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
	if(SELECT_SKILL_Y == 2 || SELECT_SKILL_Y == 4){
		char str[30];//���� �ִ�ũ��
		int SkillNum;
		if(SELECT_SKILL_ACT_PAS){//�нú�
			
			if(SELECT_SKILL_Y == 2){
				SkillNum = Character::s_Skill.Equip_P[SELECT_SKILL_SLOT];
			}else if(SELECT_SKILL_Y == 4){
				SkillNum = SELECT_SKILL_KIND_NOW;
			}

			if(SELECT_SKILL_Y == 4 || Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0){
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_P[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-65, YPOS+81, 0);
			}
		}else{
			
			if(SELECT_SKILL_Y == 2){
				SkillNum = Character::s_Skill.Equip_A[SELECT_SKILL_SLOT];
			}else if(SELECT_SKILL_Y == 4){
				SkillNum = SELECT_SKILL_KIND_NOW;
			}

			if(SELECT_SKILL_Y == 4 || Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]>=0){	
				SPRINTF(str, "%s LV%d",
					(char*)pCLRPOPUP_Text->nText[CLRMENU_SKILL_S_1 + (SkillNum*2)],
					Character::s_Skill.Level_A[SkillNum]);
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-65, YPOS+81, 0);
			}
		}
	}

	if(s_Popup_Sharp.View){ 
		if(SELECT_SKILL_Y == 2){
			if(SELECT_SKILL_ACT_PAS){//�нú�
				if(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0)
					PaintPopup_Sharp(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT] + SKILL_P_S_swordMaster);
			}else{
				if(Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]>=0)
					PaintPopup_Sharp(Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]);
			}
			
		}
		if(SELECT_SKILL_Y == 4){
			if(SELECT_SKILL_ACT_PAS){//�нú�
				PaintPopup_Sharp(SELECT_SKILL_KIND_NOW + SKILL_P_S_swordMaster);
			}else{
				PaintPopup_Sharp(SELECT_SKILL_KIND_NOW);
			}
		}
	}
}

void PopupUi::Paint_HOBBY()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_5, XPOS,YPOS,0);
}

void PopupUi::Paint_QUEST()		
{//GET_MAINQUEST_IDX()
	if(s_Page.Focus==0){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_6_1, XPOS,YPOS,0);

		//���� 
		_SUTIL->pFont->setColor(0xfbab29);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MAIN], XPOS, YPOS-59, CGraphics::HCENTER);
		//����
		_SUTIL->pFont->setColor(0xb4fa1e);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SUB], XPOS, YPOS-6, CGraphics::HCENTER);


		//������
		_SUTIL->pFont->setColor((SELECT_QUEST_Y==1 ?0xffda00 :0x748799)); 
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[GET_MAINQUEST_IDX()*2], XPOS-64, YPOS-38, 0); 

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
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_7, XPOS-69,YPOS-41,0);
		}else if(SELECT_QUEST_Y>1){//����
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_8, XPOS-69,YPOS+13+(SELECT_QUEST_Y-2)*15,0);
		}

		//��ũ�ѹ�
		_SUTIL->g->SetColor(0xff6e00);
		if(s_Quest.Max_Num > 5){//�ٰ� �پ�� ��
			int Bar_height = MAX(30, (74 - (s_Quest.Max_Num-5)*10) );
			int yy = ((74 - Bar_height)*SELECT_QUEST_SUB_Y)/(s_Quest.Max_Num-5);
			_SUTIL->g->FillRect( XPOS+64, YPOS+14+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+64, YPOS+14,4,74);
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
			_SUTIL->pFont->DrawText(_SUTIL->g, str,XPOS, YPOS-44, CGraphics::HCENTER);
			_SUTIL->pFont->setOutlineColor(-1);//�ƿ� ������ ������� ����
		}
		


		//����Ʈ��
		_SUTIL->pFont->setColor(0x93abc0);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[titleNum], XPOS, YPOS-62, CGraphics::HCENTER);
		
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
			_SUTIL->g->FillRect( XPOS+66, YPOS-37+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+66, YPOS-37,4,102);
		}

		//��ư
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_QUEST_DESC_X, XPOS,YPOS+40,0);//�˾� ������ ����
		_SUTIL->pFont->setColor(0xf8e6cb);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CLOSE], XPOS-31, YPOS+77, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DISCARD], XPOS+31, YPOS+77, CGraphics::HCENTER);
	}


}

void PopupUi::Paint_SYSTEM()	
{
	if(s_Page.Focus==0){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_7, XPOS,YPOS,0);

		//�ؽ�Ʈ
		for (int xx = 0; xx<5; xx++)
		{
			_SUTIL->pFont->setColor((SELECT_SYSTEM_Y-1==xx ?0xffda00 :0x546779));
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SYSTEM_0+xx], XPOS,YPOS-39 + (xx*24), CGraphics::HCENTER);
		}
 
		//Ŀ��
		if(SELECT_SYSTEM_Y>0){
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_6, XPOS-44,YPOS-45 + ((SELECT_SYSTEM_Y-1)*24),0);
		}
		
	}

	if(s_Page.Focus == 10){// �˾� - �������ͽ� ���� ���� Ȯ��
//		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_TRAFFIC, XPOS,YPOS-50,0);//�˾� ������ ����
		
		_SUTIL->pFont->setColor(0xFF0000);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"CHEAT PAGE", XPOS, YPOS+80-50, CGraphics::HCENTER);

		_SUTIL->pFont->setColor(0x777777);
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

	for(int xx = 0;xx<4;xx++){
		if(Character::s_ItemSlot[xx].ITEM_KIND)//������ �����ϸ�
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,MODULE_ITEM_BAG_00+(Character::s_ItemSlot[xx].ITEM_INDEX), XPOS-68+(xx*17),YPOS-61,0,0);
	}

	_SUTIL->g->SetColor(0x5a657b);
	switch(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG].Data0){
		case 100:
			_SUTIL->g->FillRect(XPOS-70,YPOS-24,138,51);
			break;
		case 101:
			_SUTIL->g->FillRect(XPOS-70,YPOS- 7,138,34);
			break;
		case 102:
			_SUTIL->g->FillRect(XPOS-70,YPOS+10,138,17);
			break;
		case 103:

			break;
	}

	//�����ݾ� �׸���
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status.MONEY,  XPOS+66, YPOS-58 , 1 , CGraphics::RIGHT);//MONEY


	//���� Ŀ�� 
	if(SELECT_ITEMSHOP_Y==1){
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			if(!(s_Page.Focus == 1 && SELECT_ITEMSHOP_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE)){//������ �ٲܶ� �� ���� Ŀ���� ����
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//���� ����
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68+(SELECT_ITEMSHOP_BAG*17)	+6, 
				YPOS-61								-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-68+(SELECT_ITEMSHOP_BAG*17)+6, YPOS-61-4,true);
		}else{
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//���� ���� ANI
		}
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//���� ����
	}



	//�κ� Ŀ��
	if(SELECT_ITEMSHOP_Y==2){//�κ����� �������� ����
		if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			itemTEXT(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
		}
		if(Character::s_ItemPick.ITEM_KIND == 0){//Ŀ���� �������� ����� �׸���
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17), YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17),0);
			s_Popup_Sharp.posX = XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17);
			s_Popup_Sharp.posY = YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17);
		}
	}

	//���泻 �������� �׸��� 
	for(int xx = 0,MaxSlot = get_BagMax(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG]);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx].ITEM_KIND){//�������� ���ٸ� �׸����ʴ´�
			paint_ICON(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx], XPOS-68 + ((xx%8)*17), YPOS-40 + ((xx/8)*17),true);
		}
	}

	//�κ� Ŀ��
	if(SELECT_ITEMSHOP_Y==2){//�κ����� �������� ����
		if(Character::s_ItemPick.ITEM_KIND){//Ŀ���� �������� ����ִٸ� �׷��ش�
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17)+6, 
				YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17)-4,0);//Ŀ��
			//������
			paint_ICON(Character::s_ItemPick,XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17)+6,YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17)-4,true);
		}
	}


	if(s_Page.Focus == 1){// �˾� �׸��� - �����ۺ� ���� �˾�ȣ��


		int Px = -68 + ((SELECT_ITEMSHOP_INSIDE%8)*17) + (((SELECT_ITEMSHOP_INSIDE%8)<4) ? 24 : -49);
		int Py = -40 + ((SELECT_ITEMSHOP_INSIDE/8)*17);



		switch(SELECT_ITEMSHOP_POPUP_KIND){//������ ������ ��ȭ
			case INVENTORY_POPUP_QUICK://4��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_2,XPOS+Px,YPOS+Py,0);//4��¥�� �˾�â

				for(int xx = 0;xx<4;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
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

			case INVENTORY_POPUP_EQUIP	://3��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<3;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//����Ŀ��
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_DEFAULT : //2��
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_4,XPOS+Px,YPOS+Py,0);//3��¥�� �˾�â

				for(int xx = 0;xx<2;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
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

				break;

			case INVENTORY_POPUP_BAGCHANGE	://���� ���Կ� ����
				int ss = 0;
				break;
		}
	}

	if(s_Page.Focus == 2){// ��� �˾� �׸���


		switch(SELECT_ITEMSHOP_POPUP_TEXT_KIND){//�˾��� ����
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
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_ITEMSHOP_POPUP_TEXT_YESNO, XPOS,YPOS,0);//�˾� ������ ����

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
		if(SELECT_ITEMSHOP_Y == 2 && Character::s_ItemPick.ITEM_KIND==0 && s_Page.Focus == 0){
			PaintPopup_Sharp(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
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
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_HUMAN + _item.ITEM_SEX], posX+START_X + 40, posY+START_Y+GAP_Y, 0);

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
					case ITEM_AXE	:											 
						SPRINTF(str, "ATT %d ~ %d",
							equip_Table[_item.ITEM_INDEX][E_T_AX_MIN],
							equip_Table[_item.ITEM_INDEX][E_T_AX_MAX]);
						break;													 
					case ITEM_GUN	:											 
						SPRINTF(str, "ATT %d ~ %d",
							equip_Table[_item.ITEM_INDEX][E_T_GU_MIN],
							equip_Table[_item.ITEM_INDEX][E_T_GU_MAX]);
						break;													 
					case ITEM_OEB	:											 
						SPRINTF(str, "ATT %d ~ %d",
							equip_Table[_item.ITEM_INDEX][E_T_OR_MIN],
							equip_Table[_item.ITEM_INDEX][E_T_OR_MAX]);
						break;


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
				}
				if(socket3){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//�����̹���
					Line_Y+=17;
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
	if(Skill_Num<SKILL_P_S_swordMaster){//��Ƽ�� ��ų

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
		Skill_Num -= SKILL_P_S_swordMaster;

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

void PopupUi::PaintGage(int gageType, int gagewidth, int x, int y, int nowvalue, int maxvalue)
{if(nowvalue>maxvalue){nowvalue = maxvalue;}
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
	}
	int curgage = ((nowvalue*gagewidth)/maxvalue);

	//	yellow gage(remain hp)
	SUTIL_SetColor(color[0]);
	SUTIL_FillRect(x, y, (curgage), 2);
	SUTIL_SetColor(color[1]);
	SUTIL_FillRect(x, y+2, (curgage), 1);

	//	max gage(max hp)
	SUTIL_SetColor(color[2]);
	SUTIL_FillRect(x+curgage, y, (gagewidth-curgage), 1);
	SUTIL_SetColor(color[3]);
	SUTIL_FillRect(x+curgage, y+1, (gagewidth-curgage), 2);
}



int PopupUi::itemICON(struct ItemBag _item)
{//������ �������� �ѷ��ٶ�
	switch(_item.ITEM_KIND)
	{//������ ������ ��ȭ
		case ITEM_BAG	:return MODULE_ITEM_BAG_00+(_item.ITEM_INDEX);
		case ITEM_POTION:return MODULE_ITEM_HP_00+(_item.ITEM_INDEX);
		case ITEM_MONEY:return MODULE_ITEM_MONEY;


		case ITEM_SWORD		:return MODULE_ITEM_SWORD_00+((_item.ITEM_INDEX)/5);
		case ITEM_AXE		:return MODULE_ITEM_AXE_00+((_item.ITEM_INDEX)/5);
		case ITEM_GUN		:return MODULE_ITEM_GUN_00+((_item.ITEM_INDEX)/5);
		case ITEM_OEB		:return MODULE_ITEM_ORB_00+((_item.ITEM_INDEX)/5);
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
					return MODULE_ITEM_SKILLBOOK_03;//����
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
			case ITEM_MONEY:return ITEM_GOLD;

			case ITEM_SWORD	:return ITEM_SWORD_0+m_Index;
			case ITEM_AXE	:return ITEM_AXE_0+m_Index;
			case ITEM_GUN	:return ITEM_GUN_0+m_Index;
			case ITEM_OEB	:return ITEM_ORB_0+m_Index;
			case ITEM_HEAD	:return Character::Check_sex(ITEM_M_HEAD_0,ITEM_W_HEAD_0)+m_Index;
			case ITEM_CHEST	:return Character::Check_sex(ITEM_M_CHEST_0,ITEM_W_CHEST_0)+m_Index;
			case ITEM_LEG	:return Character::Check_sex(ITEM_M_LEG_0,ITEM_W_LEG_0)+m_Index;
			case ITEM_GLOVE	:return Character::Check_sex(ITEM_M_GLOVES_0,ITEM_W_GLOVES_0)+m_Index;
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
void PopupUi::itemTEXT(struct ItemBag _item)
{//������ �̸��� �ѷ��ٶ�


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
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);

			//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "%d SLOT",8);break;
				case 1:SPRINTF(str, "%d SLOT",16);break;
				case 2:SPRINTF(str, "%d SLOT",24);break;
				case 3:SPRINTF(str, "%d SLOT",32);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+67, 0);
			break;

		case ITEM_POTION:

		//������ �̸�
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);

		//������ ����
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "Hp + %d%",15);break;
				case 1:SPRINTF(str, "Hp + %d%",40);break;
				case 2:SPRINTF(str, "Hp + %d%",65);break;

				case 3:SPRINTF(str, "Mp + %d%",5);break;
				case 4:SPRINTF(str, "Mp + %d%",15);break;
				case 5:SPRINTF(str, "Mp + %d%",20);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+67, 0);
			break;

		case ITEM_MAINQUEST:
			//������ �̸�
			_SUTIL->pFont->setColor(0xffaaaa);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);


			break;

		default://����


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
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+37, 0);
			

		//����
			if(socket1 + socket2 + socket3){
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,
					FRAME_UI_UI_3_1SOCKET + (socket2?(socket3?2:1):0)
					, XPOS,YPOS,0);//���� ����
			}


		//���� ����
			_SUTIL->pFont->setColor(0xffffff);//�����ȵǸ� ���������� �ٲ��ֱ� ���ı���
			SPRINTF(str, "%s %d",
				"Lv",
				(((_item.ITEM_KIND) == ITEM_NECK)||((_item.ITEM_KIND) == ITEM_RING)? deco_Table[_item.ITEM_INDEX][D_T_LV]: equip_Table[_item.ITEM_INDEX][E_T_LV])); 	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+55, 0);

		//ATT DEF
			switch(_item.ITEM_KIND){//������ ������ ��ȭ
				case ITEM_SWORD	:
					SPRINTF(str, "ATT %d ~ %d",
						equip_Table[_item.ITEM_INDEX][E_T_SW_MIN],
						equip_Table[_item.ITEM_INDEX][E_T_SW_MAX]);
					break;													 
				case ITEM_AXE	:											 
					SPRINTF(str, "ATT %d ~ %d",
						equip_Table[_item.ITEM_INDEX][E_T_AX_MIN],
						equip_Table[_item.ITEM_INDEX][E_T_AX_MAX]);
					break;													 
				case ITEM_GUN	:											 
					SPRINTF(str, "ATT %d ~ %d",
						equip_Table[_item.ITEM_INDEX][E_T_GU_MIN],
						equip_Table[_item.ITEM_INDEX][E_T_GU_MAX]);
					break;													 
				case ITEM_OEB	:											 
					SPRINTF(str, "ATT %d ~ %d",
						equip_Table[_item.ITEM_INDEX][E_T_OR_MIN],
						equip_Table[_item.ITEM_INDEX][E_T_OR_MAX]);
					break;


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
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+67, 0);

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
				_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+80, 0);
			}

		//����
			SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_INFO, XPOS+44,YPOS+83,0,0);


		break;
			
	}

	

}




void PopupUi::USE_item(struct ItemBag *_item){//������ ���

	switch(_item->ITEM_KIND){
		case ITEM_POTION://����

			int xx = _item->Data1%100 -1;
			if(xx < 0) xx = 0;

			_item->Data1 = 
				(_item->Data1/100) *100 + xx;


			if(_item->Data1%100<1){
				Del_Item(_item);
				Character::s_Status.Qslot[0]=-1;
				Character::s_Status.Qslot[1]=-1;
			}

			switch(_item->ITEM_INDEX){
				case 0://�ҹ���
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,15);
					break;
				case 1://�߹���
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,40);
					break;
				case 2://�빰��
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,65);
					break;
				case 3://�Ҹ���
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,5);
					break;
				case 4://�߸���
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,15);
					break;
				case 5://�븶��
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,20);
					break;
			}
			if(Character::s_Status.LIFE>Character::s_Status.LIFE_MAX)Character::s_Status.LIFE=Character::s_Status.LIFE_MAX;
			if(Character::s_Status.MANA>Character::s_Status.MANA_MAX)Character::s_Status.MANA=Character::s_Status.MANA_MAX;
			break;
	}

}
void PopupUi::QSLOT_item(struct ItemBag *_item){//������
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

	_item->Data0  = (_item->Data0 %= 10000000) + 10000000;
	Character::s_Status.Qslot[0] = SELECT_INVENTORY_BAG;
	Character::s_Status.Qslot[1] = SELECT_INVENTORY_INSIDE;
}

void PopupUi::QSLOT_find(){//������

	for(int xx = 0;xx<4;xx++){//��� �κ��� ���鼭 ������ Equip��� ã�� Ǯ���ش�
		for(int yy = 0;yy<32;yy++){
			if(Character::s_ItemBag[xx][yy].ITEM_EQUIP){//����� �߿�
				switch(Character::s_ItemBag[xx][yy].ITEM_KIND){//�������� ��ġ�� �����Ѵ�
						case ITEM_POTION://����
							Character::s_Status.Qslot[0]=xx;
							Character::s_Status.Qslot[1]=yy;
							return;
				}
			}
		}
	}
	Character::s_Status.Qslot[0]=-1;
	Character::s_Status.Qslot[1]=-1;

}

void PopupUi::EQUIP_item(int slot,struct ItemBag *_item){
	if(_item->ITEM_EQUIP){// �̹� ����� �������̸� ���������ʴ´�
		return;
	}

	

	if(Character::s_ItemEquip[slot].ITEM_EQUIP){//���� �ؾ��� ���Կ� �������� �̹������Ѵٸ�
		for(int xx = 0;xx<4;xx++){//��� �κ��� ���鼭 ������ Equip��� ã�� Ǯ���ش�
			for(int yy = 0;yy<32;yy++){
				if(Character::s_ItemEquip[slot].Data0 ==  Character::s_ItemBag[xx][yy].Data0){//ID�� ������ �������߿� - ���� �迭
					//if(Character::s_ItemEquip[slot].Data1 ==  Character::s_ItemBag[xx][yy].Data1){
						Character::s_ItemBag[xx][yy].Data0 %= 10000000;//�������
						xx = 4;yy = 32;//��Ż
						//���� ��� ��� ����
						Del_Slot(slot);
					//}
				}
			}
		}
	}
	
	//_item->Data1 = (_item->Data1 %= 1000000000) + 1000000000;
	_item->Data0 = (_item->Data0 %= 10000000) + 10000000*(slot+1);
	Character::s_ItemEquip[slot] = *_item;
	Set_Item(&Character::s_ItemAbil[slot],&Character::s_ItemEquip[slot]);
	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���


	int index = _item->ITEM_INDEX;

	
	int Axe = 0;
	int HeadText = 0;
	int SW_AX = (_item->ITEM_KIND == ITEM_SWORD?C_T_SW:C_T_AX);

	if(_item->ITEM_KIND == ITEM_AXE){
		Axe = (SPRITE_COSTUME_HUMAN_0_AXE - SPRITE_COSTUME_HUMAN_0_SWORD);
	}
	
	HeadText = head_Table[_item->ITEM_HEADTEXT][H_T_COSUME];

	SUTIL_LoadAspritePack(PACK_SPRITE_COSTUME);//�ѿ���
	switch(slot){
		case 0:Character::ChangeCostume(PAL_HEAD	,(HeadText?HeadText:costume_Table[index][C_T_HE]),_item->ITEM_GRADE);  break;
		case 3:Character::ChangeCostume(PAL_BODY	,(HeadText?HeadText:costume_Table[index][C_T_CH]),_item->ITEM_GRADE);	 break;
		case 4:Character::ChangeCostume(PAL_ARM		,(HeadText?HeadText:costume_Table[index][C_T_LE]),_item->ITEM_GRADE);	 break;
		case 7:Character::ChangeCostume(PAL_LEG		,(HeadText?HeadText:costume_Table[index][C_T_GL]),_item->ITEM_GRADE);	 break;

		case 5:Character::ChangeCostume(PAL_KNIFE2	,costume_Table[index][SW_AX]/10+Axe,costume_Table[index][SW_AX]%10);break;
		case 6:Character::ChangeCostume(PAL_KNIFE1	,costume_Table[index][SW_AX]/10+Axe,costume_Table[index][SW_AX]%10);break;
		case 8:Character::ChangeCostume(PAL_BOW		,costume_Table[index][C_T_GU]/10,costume_Table[index][C_T_GU]%10);break;
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
			case ITEM_MAINQUEST:
				if(_item.Data1>1){
					PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_SKILL_NUM, _item.ITEM_STACK_COUNT,  x+16, y+9, -1 , CGraphics::RIGHT);//������ ����
				}
				break;
		}

		switch(_item.ITEM_KIND){//��� ���ΰ� ǥ�õ� ������  DATA1 �� �ֻ����ڸ����� 0�̸� ������ 1�̸� ����
			case ITEM_POTION://�o����
			case ITEM_SWORD	:
			case ITEM_AXE	:
			case ITEM_GUN	:
			case ITEM_OEB	:
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
void PopupUi::Del_Slot(int slot){//���� �κ����� ����
		Character::s_ItemEquip[slot].Data0 = 0;	
		Character::s_ItemEquip[slot].Data1 = 0;
		Character::s_ItemEquip[slot].Data2 = 0;

		Character::s_ItemAbil[slot].ATT_MIN	= 0;
		Character::s_ItemAbil[slot].ATT_MAX	= 0;
		Character::s_ItemAbil[slot].DEF		= 0;

		Character::s_ItemAbil[slot].CRI		= 0; 
		Character::s_ItemAbil[slot].AGI		= 0; 
		Character::s_ItemAbil[slot].HP		= 0; 
		Character::s_ItemAbil[slot].MP		= 0;

		Character::s_ItemAbil[slot].STR		= 0;
		Character::s_ItemAbil[slot].DEX		= 0; 
		Character::s_ItemAbil[slot].CON		= 0; 
		Character::s_ItemAbil[slot].INT 	= 0; 
}

//--------------------------------------------------------------------------
ItemBag PopupUi::MakeItem(int nMontype, int nMonLevel, int nHeroSex, int mapIdx)		//����man:0,girl:1
//--------------------------------------------------------------------------
{
	ItemBag tmpBag;
	tmpBag.Data0 = 0;

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
		if(MON_IDX_COBOLT == nMontype)
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


bool PopupUi::GET_item(struct ItemBag* _item)
{
	int StackMAX = 99;


	switch(_item->ITEM_KIND){
		case ITEM_MONEY://�κ� ������ �����ʴ� ������
			Character::s_Status.MONEY+=_item->ITEM_STACK_COUNT;
			if(Character::s_Status.MONEY>999999999)Character::s_Status.MONEY = 999999999;
			AddItemList(*_item);
			return true;

		case ITEM_MAINQUEST://10�� ��ġ�� ������
			StackMAX = 10;
		case ITEM_POTION://99�� ��ġ�¾�����
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
int PopupUi::GET_Count(int itemID)
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
					counter++;
				}else{
					counter += Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT;
				}
			}
		}
	}
	return counter;

}//������ ���� ���� üũ �Ҷ�
int PopupUi::REMOVE_Item(int itemID,int counter)
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
							counter=0;
							Character::s_ItemBag[xx][yy].Data1 -= counter;
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
					
				}
				//else{
					//���� �� �޼ҵ�� ���� �� ����
					//���� ���̵��� �ص� �ٸ� �� �ִ�
				//}
			}
		}
	}
	return counter;

}//������ ���� ���� üũ �Ҷ�

void PopupUi::equipTEXT(int slot,struct ItemBag _item){//���� �����ۿ� ���� ����
	//���� ������ ��� ����������� ��ȭ�ϴ� �ɷ�ġ�� �����ش�



	ItemAbility TempAbil = Character::s_ItemAbil[slot]; 
	ItemBag TempEquip = Character::s_ItemEquip[slot];


	int temp_Amax = Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL];
	int temp_Def  = Character::s_Status.DEFENSE;
	int temp_Cri  = Character::s_Status.CRITICAL;
	int temp_Agi  = Character::s_Status.AVOID;
	int temp_Life = Character::s_Status.LIFE_MAX;
	int temp_Mana = Character::s_Status.MANA_MAX;


	Character::s_ItemEquip[slot] = _item;//�ӽ�����
	Set_Item(&Character::s_ItemAbil[slot],&Character::s_ItemEquip[slot]);
	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���


	_SUTIL->pFont->setColor(0x93abbf);

	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ATT], XPOS-70, YPOS+41, 0);		//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DEF], XPOS-70, YPOS+57, 0);		//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CRI], XPOS-70, YPOS+73, 0);		//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_AGI], XPOS+1, YPOS+41, 0);		//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_HP], XPOS+1, YPOS+57, 0);		//HP
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MP], XPOS+1, YPOS+73, 0);		//MP

	_SUTIL->pFont->setColor(0xffcc00);

	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL], XPOS-19, YPOS+41, CGraphics::RIGHT);//Att1
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.DEFENSE, XPOS-19, YPOS+57, CGraphics::RIGHT);	//DEF
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.CRITICAL, XPOS-19, YPOS+73, CGraphics::RIGHT);	//CRI
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.AVOID, XPOS+52, YPOS+41, CGraphics::RIGHT);		//AGI
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.LIFE_MAX, XPOS+52, YPOS+57, CGraphics::RIGHT);	//HP
	_SUTIL->pFont->DrawText(_SUTIL->g, Character::s_Status.MANA_MAX, XPOS+52, YPOS+73, CGraphics::RIGHT);	//MP


//�� �ٿ� ������
	if(temp_Amax < Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL]){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+39,0,0);//UP������
	}else if(temp_Amax > Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL]){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+39,0,0);//DOWN������
	}
	if(temp_Def  < Character::s_Status.DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+55,0,0);//UP������
	}else if(temp_Def  > Character::s_Status.DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+55,0,0);//DOWN������
	}
	if(temp_Cri  < Character::s_Status.CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+71,0,0);//UP������
	}else if(temp_Cri  > Character::s_Status.CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+71,0,0);//DOWN������
	}
	if(temp_Agi  < Character::s_Status.AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+39,0,0);//UP������
	}else if(temp_Agi  > Character::s_Status.AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+39,0,0);//DOWN������
	}
	if(temp_Life < Character::s_Status.LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+55,0,0);//UP������
	}else if(temp_Life > Character::s_Status.LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+55,0,0);//DOWN������
	}
	if(temp_Mana < Character::s_Status.MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+71,0,0);//UP������
	}else if(temp_Mana > Character::s_Status.MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+71,0,0);//DOWN������
	}




	Character::s_ItemAbil[slot] = TempAbil;//���󺹱�
	Character::s_ItemEquip[slot] = TempEquip;//���󺹱�
	Character::Set_state_calculate();//��ȭ�� �ɷ�ġ ���


	
}


void PopupUi::Set_Item(struct ItemAbility *_abil,struct ItemBag *_item){//���� �κ����� ����

	
	int gradePER[5] = {100,110,115,120,130};//���
	int grade = gradePER[_item->Data1%10];
	int head = 100 + head_Table[(_item->Data1/10)%100][ (_item->ITEM_KIND<ITEM_HEAD? 0:5) ]; //����� ���Ŀ����� ���̹ٲ��


//���λ�
	_abil->CRI		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 1:6)];
	_abil->AGI		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 2:7)];
	_abil->HP		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 3:8)];
	_abil->MP		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 4:9)];


//��ũ��
	_abil->STR		= 0; 
	_abil->DEX		= 0;
	_abil->CON		= 0;
	_abil->INT		= 0;

	int scroll_Kind = (_item->Data2/100)%100; //��ũ�� ����
	int UP = (((_item->Data2/10000) %1000) /3) +1; //��ũ�� ���ġ

	switch(scroll_Kind){//��ũ�� ����
		case 1:_abil->STR = _abil->DEX = UP;break;
		case 2:_abil->STR = _abil->CON = UP;break;
		case 3:_abil->STR = _abil->INT = UP;break;
		case 4:_abil->DEX = _abil->CON = UP;break;
		case 5:_abil->DEX = _abil->INT = UP;break;
		case 6:_abil->CON = _abil->INT = UP;break;
		case 7:	_abil->STR = UP*4/3+1;break;
		case 8:	_abil->DEX = UP*4/3+1;break;
		case 9:	_abil->CON = UP*4/3+1;break;
		case 10:_abil->INT = UP*4/3+1;break;
		case 11:_abil->STR = _abil->DEX = _abil->CON = _abil->INT = MAX(1,UP/2);break;
	}

	

	switch(_item->ITEM_KIND){//������ ������ ��ȭ  
		case ITEM_SWORD	:
			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][1],grade),head);
			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][2],grade),head);
			_abil->DEF		= 0;
			break;
		case ITEM_AXE	:
			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][3],grade),head);
			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][4],grade),head);
			_abil->DEF		= 0;
			break;
		case ITEM_GUN	:
			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][5],grade),head);
			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][6],grade),head);
			_abil->DEF		= 0;
			break;
		case ITEM_OEB	:
			_abil->ATT_MIN	= PER(PER(equip_Table[_item->ITEM_INDEX][7],grade),head);
			_abil->ATT_MAX	= PER(PER(equip_Table[_item->ITEM_INDEX][8],grade),head);
			_abil->DEF		= 0;
			break;


		case ITEM_HEAD	:
			_abil->ATT_MIN	= 0;
			_abil->ATT_MAX	= 0;
			_abil->DEF		= PER(PER(equip_Table[_item->ITEM_INDEX][9],grade),head);
			break;
		case ITEM_CHEST	:
			_abil->ATT_MIN	= 0;
			_abil->ATT_MAX	= 0;
			_abil->DEF		= PER(PER(equip_Table[_item->ITEM_INDEX][10],grade),head);
			break;
		case ITEM_LEG	:
			_abil->ATT_MIN	= 0;
			_abil->ATT_MAX	= 0;
			_abil->DEF		= PER(PER(equip_Table[_item->ITEM_INDEX][11],grade),head);
			break;
		case ITEM_GLOVE	:
			_abil->ATT_MIN	= 0;
			_abil->ATT_MAX	= 0;
			_abil->DEF		= PER(PER(equip_Table[_item->ITEM_INDEX][12],grade),head);
			break;
		case ITEM_NECK	:
			_abil->ATT_MIN	= 0;
			_abil->ATT_MAX	= 0;
			_abil->DEF		= PER(PER(deco_Table[_item->ITEM_INDEX][1],grade),head);
			break;
		case ITEM_RING	:
			_abil->ATT_MIN	= PER(PER(deco_Table[_item->ITEM_INDEX][2],grade),head);
			_abil->ATT_MAX	= PER(PER(deco_Table[_item->ITEM_INDEX][2],grade),head);
			_abil->DEF		= PER(PER(deco_Table[_item->ITEM_INDEX][3],grade),head);
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
































