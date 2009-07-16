#include "PopupUi.h"


Page PopupUi::s_Page;
ItemList PopupUi::s_ItemList[5];
PlayMessage PopupUi::s_PlayMessage;
AreaMessage PopupUi::s_AreaMessage;
_TEXT_PACK* PopupUi::pCLRPOPUP_Text;

PopupUi::PopupUi(void* s__ASpriteSet,ASprite* _Hero)
{
	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // 그림자,효과 이펙트 스프라이트의 포인터
	m_pHeroAs = _Hero;

	pCLRPOPUP_Text = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_CLRMENU_TEXT);//텍스트 팩 로드
	pMAIN_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_MAIN_QUEST_TEXT);//메인 퀘스트 팩 로드
	pSUB_QUEST_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_SUB_QUEST_TEXT);//서브 퀘스트 팩 로드
	pITEM_Text =  _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_ITEM_TEXT);//퀘스트 팩 로드
	s_Page.PageNum = 1;//첫 페이지

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
	Character::s_ItemBag[0][0].Data0 = 1024;			//장착인덱스(2),스프라이트인덱스(2), 팔레트(1), 아이템ID(4)
	Character::s_ItemBag[0][0].Data1 = 10101033;	//장비여부(1),소켓3(2),소켓2(2),소켓1(2),접두사(2),등급(1)    -소켓은 뚫린소켓은 1, 2이상은 잼 넘버
	Character::s_ItemBag[0][0].Data2 = 230109;			//스크롤레벨(3),스탯스크롤(2),강화(2)

	Character::s_ItemBag[0][1].Data0 = 1124;
	Character::s_ItemBag[0][1].Data1 = 101022;	//장비여부(1),소켓3(2),소켓2(2),소켓1(2),접두사(2),등급(1)    -소켓은 뚫린소켓은 1, 2이상은 잼 넘버
	Character::s_ItemBag[0][1].Data2 = 230710;			//스크롤레벨(3),스탯스크롤(2),강화(2)

	Character::s_ItemBag[0][2].Data0 = 1224;
	Character::s_ItemBag[0][2].Data1 = 1031;	//장비여부(1),소켓3(2),소켓2(2),소켓1(2),접두사(2),등급(1)    -소켓은 뚫린소켓은 1, 2이상은 잼 넘버
	Character::s_ItemBag[0][2].Data2 = 231111;			//스크롤레벨(3),스탯스크롤(2),강화(2)
*/
}




PopupUi::~PopupUi()
{
	SUTIL_FreeTextPack(pCLRPOPUP_Text);
	SUTIL_FreeTextPack(pMAIN_QUEST_Text);//메인퀘스트 팩
	SUTIL_FreeTextPack(pSUB_QUEST_Text);//서브 퀘스트 팩
	SUTIL_FreeTextPack(pITEM_Text);//아이템 팩
//	SUTIL_FreeSprite(m_pWorldMapAs);

}

bool PopupUi::KeyEvent(int m_keyCode, int m_keyRepeat)
{	
	if(m_keyRepeat)return true;
	if(m_keyCode == MH_KEY_4)m_keyCode=MH_KEY_LEFT;		//값대치
	if(m_keyCode == MH_KEY_6)m_keyCode=MH_KEY_RIGHT;	//값대치
	if(m_keyCode == MH_KEY_2)m_keyCode=MH_KEY_UP;		//값대치
	if(m_keyCode == MH_KEY_8)m_keyCode=MH_KEY_DOWN;		//값대치
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//값대치



	if(GameOver){//게임 오버일때
		Key_GAMEOVER(m_keyCode, m_keyRepeat);
		return GameOver;
	}



	if(m_keyCode == MH_KEY_CLEAR && !s_Page.Focus && !s_Page.Ly1_sel)//게임중 팝업 끄기
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


	switch(s_Page.PageNum){//내부구성요소
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
	if(GameOver){//게임 오버일때
		Paint_GAMEOVER();
		return;
	}

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CANCLE, XPOS,YPOS,0);//배경
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CANCLE_BASE, XPOS,YPOS,0);//프레임

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_TOP_TAP, XPOS,YPOS,0);//탭
//	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_TOP_ICON_00 + (s_Page.PageNum - 1), XPOS-61 + 18*(s_Page.PageNum - 1),YPOS-82,0,0);//탭 아이콘
	SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_TITLE_00 + (s_Page.PageNum - 1), XPOS,YPOS-98,0,CGraphics::HCENTER);//탭 아이콘


	_SUTIL->pFont->setOutlineColor(-1);//아웃 라인을 사용하지 않음
	switch(s_Page.PageNum){//내부구성요소
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
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_TAP, XPOS-62 + 18*(s_Page.PageNum - 1),YPOS-83,0);//탭 커서

	_SUTIL->g->SetColor(0xff0000);
	_SUTIL->g->DrawRect(XPOS,YPOS,1,1);

	/*_SUTIL->pFont->drawScroll(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TESTTEXT], XPOS-51, YPOS-80,80,75,2, CGraphics::HCENTER);
	_SUTIL->pFont->drawLines(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TESTTEXT], XPOS-51, YPOS+40,120,4,3, CGraphics::HCENTER);*/

//	SUTIL_Paint_Frame(m_pWorldMapAs, 0, 200, 200,0); //배경
}


void PopupUi::Process()
{
}





void PopupUi::Key_STATES(int m_keyCode, int m_keyRepeat)	
{
	if(s_Page.Focus == 0){
		switch(s_Page.Ly1_sel){
			case 0://탑메뉴
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
			case 1://타이틀
				if(m_keyCode == MH_KEY_SELECT){

				}
				break;
			case 2://힘
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.STR++;
					}
				}
				break;
			case 3://민첩
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.DEX++;
					}
				}
				break;
			case 4://체력
				if(m_keyCode == MH_KEY_SELECT){
					if(Character::s_Ability.POINT>0){
						Character::s_Ability.POINT--;
						Character::s_Ability.CON++;
					}
				}
				break;
			case 5://지능
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
		}else if(m_keyCode == MH_KEY_CLEAR){//게임중 팝업 호출
			if(PAGE_STATES_point[0]-Character::s_Ability.POINT > 0 && s_Page.Ly1_sel>1){
				s_Page.Focus = 1;
				s_Page.Ly2_sel = 1;//yes
			}else{
				s_Page.Ly1_sel=0;
			}
		}

		if(PAGE_STATES_point[0]> 0 && Character::s_Ability.POINT ==0){//확인 팝업 호출
			s_Page.Focus = 1;
			s_Page.Ly2_sel = 1;//yes
		}

		Character::Set_state_calculate();//변화된 능력치 계산

	}else if(s_Page.Focus == 1){// 팝업 - 스테이터스 적용 여부 확인
		if(m_keyCode == MH_KEY_RIGHT){
			s_Page.Ly2_sel = 1;//No
		}else if(m_keyCode == MH_KEY_LEFT){
			s_Page.Ly2_sel = 0;//Yes
		}else if(m_keyCode == MH_KEY_SELECT){//올린 스탯 적용

			s_Page.Focus = 0;//팝업해제
			s_Page.Ly1_sel=0;

			if(s_Page.Ly2_sel){//No - 되돌리기
				 Character::s_Ability.POINT=PAGE_STATES_point[0];
				 Character::s_Ability.STR  =PAGE_STATES_point[1];
				 Character::s_Ability.DEX  =PAGE_STATES_point[2];
				 Character::s_Ability.CON  =PAGE_STATES_point[3];
				 Character::s_Ability.INT  =PAGE_STATES_point[4];
			}else{//Yes - 현재 상태를 백업
				PAGE_STATES_point[0] = Character::s_Ability.POINT;
				PAGE_STATES_point[1] = Character::s_Ability.STR;
				PAGE_STATES_point[2] = Character::s_Ability.DEX;
				PAGE_STATES_point[3] = Character::s_Ability.CON;
				PAGE_STATES_point[4] = Character::s_Ability.INT;
			}
			

		}else if(m_keyCode == MH_KEY_CLEAR){//올린 스탯 취소

			s_Page.Focus = 0;//팝업해제

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
			case 0://탑메뉴
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_EQUIP_Y++;SELECT_EQUIP_JAB_BACUP = Character::s_Status.ELEMENTAL;break;
				}
				break;
			case 1://장비 선택
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
			case 2://대상 아이템 선택
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
						if(SELECT_EQUIP_LIST_NOW_BAG >=0 &&SELECT_EQUIP_LIST_NOW_SLOT>=0){//이미 착용한 아이템이 아니라면

							EQUIP_item(SELECT_EQUIP_POS,&Character::s_ItemBag[SELECT_EQUIP_LIST_NOW_BAG][SELECT_EQUIP_LIST_NOW_SLOT]);
							//if(SELECT_EQUIP_POS == 6 && Character::s_ItemEquip[6].Data0 == 0)SELECT_EQUIP_POS=5; //검사무기 2nd 슬롯에 선장착시 앞으로 강제이동
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
			case 0://탑메뉴
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_INVENTORY_Y++;break;
				}
				break;
			case 1://가방 탭
				{
					int rightBag = (SELECT_INVENTORY_BAG+1)%4;
					int leftBag = (SELECT_INVENTORY_BAG+3)%4;
					switch(m_keyCode){
						case MH_KEY_CLEAR:
						case MH_KEY_UP:
							if(Character::s_ItemPick.ITEM_KIND==0){//커서에 아이템이 붙어있지않아야 한다
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
			case 2://인벤내부 탭
				switch(m_keyCode){
					case MH_KEY_CLEAR:SELECT_INVENTORY_Y = 1;break;
					case MH_KEY_SELECT:

						if(Character::s_ItemPick.ITEM_KIND){//들고있는 아이템이 있다면
							MOVE_item();//커서와 인벤의 아이템 교체
						}else if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data0){//커서가 가리키는 아이템이 없다면 팝업을 그리지않는다
							
							s_Page.Focus = 1;//팝업호출
							SELECT_INVENTORY_POPUP_Y=0;

							switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//아이템 종류별 분화
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
									//사용할수없는 일반템용 메세지
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
				switch(Character::s_ItemSlot[SELECT_INVENTORY_BAG].Data0){//가방 고유의 Kind Num은 1이다
					case 100:SELECT_INVENTORY_INSIDE +=  8;SELECT_INVENTORY_INSIDE %=  8;break;
					case 101:SELECT_INVENTORY_INSIDE += 16;SELECT_INVENTORY_INSIDE %= 16;break;
					case 102:SELECT_INVENTORY_INSIDE += 24;SELECT_INVENTORY_INSIDE %= 24;break;
					case 103:SELECT_INVENTORY_INSIDE += 32;SELECT_INVENTORY_INSIDE %= 32;break;
				}

		}
	}else if(s_Page.Focus == 1){// 팝업 - 아이템별 차등 팝업호출

		
		switch(m_keyCode){
			case MH_KEY_CLEAR:
				if(SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){
					SELECT_INVENTORY_BAG = 0;
				}
				s_Page.Focus = 0;
				break;
			case MH_KEY_SELECT:
				switch(SELECT_INVENTORY_POPUP_KIND){//팝업의 종류
					case INVENTORY_POPUP_QUICK:
						if(SELECT_INVENTORY_POPUP_Y==0){//사용
							USE_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}else if(SELECT_INVENTORY_POPUP_Y==1){//퀵슬롯
							QSLOT_item(&Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
							s_Page.Focus = 0;
						}else if(SELECT_INVENTORY_POPUP_Y==2){//버림
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==3){//이동
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
					case INVENTORY_POPUP_EQUIP:
						if(SELECT_INVENTORY_POPUP_Y==0){//장착
							int xx;
							switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//아이템 종류별 분화
								case ITEM_BAG	:
									MOVE_item();
									s_Page.Focus = 1;//팝업호출
									SELECT_INVENTORY_Y=1;//가방 선택 탭으로 이동
									SELECT_INVENTORY_POPUP_KIND = INVENTORY_POPUP_BAGCHANGE;//가방 착용 선택
									return;//가방은 추가UI가 있으므로 이탈한다
								case ITEM_SWORD	:
								case ITEM_AXE	:
									if(Character::s_ItemEquip[5].ITEM_KIND){//5번 슬롯이 차있다면 무조건 6번 슬롯을 채운다
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
						}else if(SELECT_INVENTORY_POPUP_Y==1){//버림
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==2){//이동
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
					case INVENTORY_POPUP_BAGCHANGE://가방 교체 또는 장착
						MOVE_item();//인벤 가방과 교체
						break;
					case INVENTORY_POPUP_DEFAULT:
						if(SELECT_INVENTORY_POPUP_Y==0){//버림
							DEL_item();
						}else if(SELECT_INVENTORY_POPUP_Y==1){//이동
							MOVE_item();
							s_Page.Focus = 0;
						}
						break;
				}
				
				break;
			case MH_KEY_UP:
				SELECT_INVENTORY_POPUP_Y--;
				switch(SELECT_INVENTORY_POPUP_KIND){//팝업의 종류
					case INVENTORY_POPUP_QUICK:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=3;break;
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=2;break;
					case INVENTORY_POPUP_DEFAULT:if(SELECT_INVENTORY_POPUP_Y<0)SELECT_INVENTORY_POPUP_Y=1;break;
				}
				break;
			case MH_KEY_DOWN:
				SELECT_INVENTORY_POPUP_Y++;
				switch(SELECT_INVENTORY_POPUP_KIND){//팝업의 종류
					case INVENTORY_POPUP_QUICK:if(SELECT_INVENTORY_POPUP_Y>3)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_EQUIP:if(SELECT_INVENTORY_POPUP_Y>2)SELECT_INVENTORY_POPUP_Y=0;break;
					case INVENTORY_POPUP_DEFAULT:if(SELECT_INVENTORY_POPUP_Y>1)SELECT_INVENTORY_POPUP_Y=0;break;
				}
				break;
			case MH_KEY_LEFT:
				switch(SELECT_INVENTORY_POPUP_KIND){//팝업의 종류
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
				switch(SELECT_INVENTORY_POPUP_KIND){//팝업의 종류
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
		
	}else if(s_Page.Focus == 2){// 경고팝업 - 불가능한 교체, 버리기를 진행할 경우 띄운다
		switch(SELECT_INVENTORY_POPUP_TEXT_KIND){//팝업의 종류
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
			case 0://탑메뉴
				switch(m_keyCode){
					case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
					case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
					case MH_KEY_SELECT:
					case MH_KEY_DOWN:SELECT_SKILL_Y++;	break;
				}
				break;
			case 1://액티브 패시브 선택
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
			case 2://슬롯 선택
				if(SELECT_SKILL_ACT_PAS){//패시브

					
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
								Character::Set_state_calculate();//변경된 스테이터스 적용
							}else{
								SELECT_SKILL_Y++;	
							}
							break;
						case MH_KEY_CLEAR:
							if(SELECT_SKILL_KIND_NOW>=0){
								SELECT_SKILL_KIND_NOW=-1;
								Character::Set_state_calculate();//변경된 스테이터스 적용(장착된것을 뺄 수도 있음)
							}else{
								SELECT_SKILL_Y--;		
							}
							break;
					}
					SELECT_SKILL_SLOT%=9;
				}else{//액티브
				
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
			case 3://직업 선택

				if(SELECT_SKILL_ACT_PAS){//패시브
					int jab_Max = 1+Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
					switch(m_keyCode){
						case MH_KEY_SELECT:
						case MH_KEY_RIGHT:SELECT_SKILL_Y++;SELECT_SKILL_KIND=0;	break;
						case MH_KEY_UP:SELECT_SKILL_TYPE+=jab_Max-1;	break;
						case MH_KEY_DOWN:SELECT_SKILL_TYPE++;	break;
						case MH_KEY_CLEAR:SELECT_SKILL_Y--;SELECT_SKILL_KIND_NOW=-1;	break;
					}
					SELECT_SKILL_TYPE%=jab_Max;
				}else{//액티브
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
			case 4://스킬 선택
				int skill_Max=0;
				if(SELECT_SKILL_ACT_PAS){//패시브

					for(int xx = 0;xx<7;xx++){
						switch(SELECT_SKILL_TYPE_NOW){
							case 0:if(Character::s_Skill.Level_P[xx])skill_Max++;break;//칼 패시브 스킬갯수
							case 1:if(Character::s_Skill.Level_P[7+xx])skill_Max++;break;//총 패시브 스킬갯수
							case 2:if(Character::s_Skill.Level_P[14+xx])skill_Max++;break;//마 패시브 스킬갯수
							case 3:if(Character::s_Skill.Level_P[21+xx])skill_Max++;break;//마 패시브 스킬갯수
						}
					}
					
				}else{//액티브

					for(int xx = 0;xx<7;xx++){
						switch(SELECT_SKILL_TYPE_NOW){
							case 0:if(Character::s_Skill.Level_A[xx])skill_Max++;break;//칼 패시브 스킬갯수
							case 1:if(Character::s_Skill.Level_A[7+xx])skill_Max++;break;//총 패시브 스킬갯수
							case 2:if(Character::s_Skill.Level_A[14+xx])skill_Max++;break;//마 패시브 스킬갯수
						}
					}
				}
				switch(m_keyCode){
					case MH_KEY_SELECT://겹치는 기술이 있다면 -1(해제) 로 해준다
						if(SELECT_SKILL_ACT_PAS){//패시브
							for(int xx = 0;xx<9;xx++){
								if(SELECT_SKILL_KIND_NOW == Character::s_Skill.Equip_P[xx])Character::s_Skill.Equip_P[xx]=-1;
							}
							Character::Set_state_calculate();//변경된 스테이터스 적용(장착된것을 뺄 수도 있음)
						}else{//액티브
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
				if(skill_Max)SELECT_SKILL_KIND%=skill_Max;//제로디바이스 익셉션 발생가능성있음
				break;
		}
	}
	//else if(s_Page.Focus == 1){//팝업
	//	if(SELECT_SKILL_ACT_PAS){//패시브

	//	}else{//액티브

	//	}
	//}
}
void PopupUi::Key_HOBBY(int m_keyCode, int m_keyRepeat)		
{
	if(s_Page.Focus == 0){
		switch(s_Page.Ly1_sel){
			case 0://탑메뉴
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
		if(SELECT_QUEST_Y == 0){//탑메뉴
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
	}else if(s_Page.Focus==1){//세부 설명 페이지
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


		if(SELECT_SYSTEM_Y== 0){//탑메뉴
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
			case MH_KEY_UP:Character::s_Status.LIFE=99999999;break;//수정요
			case MH_KEY_3:Character::s_Status.MANA=99999999;break;
			case MH_KEY_LEFT:
				Character::s_Skill_Set.Cool_TimeMax[0]=0;Character::s_Skill_Set.Cool_TimeNow[0]=0;
				Character::s_Skill_Set.Cool_TimeMax[1]=0;Character::s_Skill_Set.Cool_TimeNow[1]=0;
				Character::s_Skill_Set.Cool_TimeMax[2]=0;Character::s_Skill_Set.Cool_TimeNow[2]=0;
				Character::s_Skill_Set.Cool_TimeMax[3]=0;Character::s_Skill_Set.Cool_TimeNow[3]=0;
				Character::s_Skill_Set.Cool_TimeMax[4]=0;Character::s_Skill_Set.Cool_TimeNow[4]=0;
				Character::s_Skill_Set.Cool_TimeMax[5]=0;Character::s_Skill_Set.Cool_TimeNow[5]=0;
				break;//수정요
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
					Character::s_Skill.Level_A[xx]=1;	//액티브 스킬레벨
				}
				Character::s_Ability.JAB_KNIFE	=true;	//검사 - 직업 선택 가능하다면 true
				Character::s_Ability.JAB_GUN	=true;	//총사 - 직업 선택 가능하다면 true
				Character::s_Ability.JAB_MAGIC	=true;	//술사 - 직업 선택 가능하다면 true


				break;//수정요
		}
	}
}




void PopupUi::Key_GAMEOVER(int m_keyCode, int m_keyRepeat)	
{
	switch(SELECT_SKILL_Y){
		case 0:
			if(m_keyCode == MH_KEY_SELECT){//부활
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
			case 0://탑메뉴
				switch(m_keyCode){
			case MH_KEY_LEFT:s_Page.PageNum--;Page_init();break;
			case MH_KEY_RIGHT:s_Page.PageNum++;Page_init();break;
			case MH_KEY_SELECT:
			case MH_KEY_DOWN:SELECT_ITEMSHOP_Y++;break;
				}
				break;
			case 1://가방 탭
				{
					int rightBag = (SELECT_ITEMSHOP_BAG+1)%4;
					int leftBag = (SELECT_ITEMSHOP_BAG+3)%4;
					switch(m_keyCode){
			case MH_KEY_CLEAR:
			case MH_KEY_UP:
				if(Character::s_ItemPick.ITEM_KIND==0){//커서에 아이템이 붙어있지않아야 한다
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
			case 2://인벤내부 탭
				switch(m_keyCode){
			case MH_KEY_CLEAR:SELECT_ITEMSHOP_Y = 1;break;
			case MH_KEY_SELECT:

				if(Character::s_ItemPick.ITEM_KIND){//들고있는 아이템이 있다면
					MOVE_item();//커서와 인벤의 아이템 교체
				}else if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].Data0){//커서가 가리키는 아이템이 없다면 팝업을 그리지않는다

					s_Page.Focus = 1;//팝업호출
					SELECT_ITEMSHOP_POPUP_Y=0;

					switch(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//아이템 종류별 분화
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
				//사용할수없는 일반템용 메세지
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
				switch(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG].Data0){//가방 고유의 Kind Num은 1이다
			case 100:SELECT_ITEMSHOP_INSIDE +=  8;SELECT_ITEMSHOP_INSIDE %=  8;break;
			case 101:SELECT_ITEMSHOP_INSIDE += 16;SELECT_ITEMSHOP_INSIDE %= 16;break;
			case 102:SELECT_ITEMSHOP_INSIDE += 24;SELECT_ITEMSHOP_INSIDE %= 24;break;
			case 103:SELECT_ITEMSHOP_INSIDE += 32;SELECT_ITEMSHOP_INSIDE %= 32;break;
				}

		}
	}else if(s_Page.Focus == 1){// 팝업 - 아이템별 차등 팝업호출


		switch(m_keyCode){
			case MH_KEY_CLEAR:
				if(SELECT_ITEMSHOP_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){
					SELECT_ITEMSHOP_BAG = 0;
				}
				s_Page.Focus = 0;
				break;
			case MH_KEY_SELECT:
				switch(SELECT_ITEMSHOP_POPUP_KIND){//팝업의 종류
			case INVENTORY_POPUP_QUICK:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//사용
					USE_item(&Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
					s_Page.Focus = 0;
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//퀵슬롯
					QSLOT_item(&Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
					s_Page.Focus = 0;
				}else if(SELECT_ITEMSHOP_POPUP_Y==2){//버림
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==3){//이동
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
			case INVENTORY_POPUP_EQUIP:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//장착
					int xx;
					switch(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//아이템 종류별 분화
			case ITEM_BAG	:
				MOVE_item();
				s_Page.Focus = 1;//팝업호출
				SELECT_ITEMSHOP_Y=1;//가방 선택 탭으로 이동
				SELECT_ITEMSHOP_POPUP_KIND = INVENTORY_POPUP_BAGCHANGE;//가방 착용 선택
				return;//가방은 추가UI가 있으므로 이탈한다
			case ITEM_SWORD	:
			case ITEM_AXE	:
				if(Character::s_ItemEquip[5].ITEM_KIND){//5번 슬롯이 차있다면 무조건 6번 슬롯을 채운다
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
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//버림
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==2){//이동
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
			case INVENTORY_POPUP_BAGCHANGE://가방 교체 또는 장착
				MOVE_item();//인벤 가방과 교체
				break;
			case INVENTORY_POPUP_DEFAULT:
				if(SELECT_ITEMSHOP_POPUP_Y==0){//버림
					DEL_item();
				}else if(SELECT_ITEMSHOP_POPUP_Y==1){//이동
					MOVE_item();
					s_Page.Focus = 0;
				}
				break;
				}

				break;
			case MH_KEY_UP:
				SELECT_ITEMSHOP_POPUP_Y--;
				switch(SELECT_ITEMSHOP_POPUP_KIND){//팝업의 종류
			case INVENTORY_POPUP_QUICK:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=3;break;
			case INVENTORY_POPUP_EQUIP:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=2;break;
			case INVENTORY_POPUP_DEFAULT:if(SELECT_ITEMSHOP_POPUP_Y<0)SELECT_ITEMSHOP_POPUP_Y=1;break;
				}
				break;
			case MH_KEY_DOWN:
				SELECT_ITEMSHOP_POPUP_Y++;
				switch(SELECT_ITEMSHOP_POPUP_KIND){//팝업의 종류
			case INVENTORY_POPUP_QUICK:if(SELECT_ITEMSHOP_POPUP_Y>3)SELECT_ITEMSHOP_POPUP_Y=0;break;
			case INVENTORY_POPUP_EQUIP:if(SELECT_ITEMSHOP_POPUP_Y>2)SELECT_ITEMSHOP_POPUP_Y=0;break;
			case INVENTORY_POPUP_DEFAULT:if(SELECT_ITEMSHOP_POPUP_Y>1)SELECT_ITEMSHOP_POPUP_Y=0;break;
				}
				break;
			case MH_KEY_LEFT:
				switch(SELECT_ITEMSHOP_POPUP_KIND){//팝업의 종류
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
				switch(SELECT_ITEMSHOP_POPUP_KIND){//팝업의 종류
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

	}else if(s_Page.Focus == 2){// 경고팝업 - 불가능한 교체, 버리기를 진행할 경우 띄운다
		switch(SELECT_ITEMSHOP_POPUP_TEXT_KIND){//팝업의 종류
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
	

//상태 백업
	if (s_Page.Ly1_sel==0){
		PAGE_STATES_point[0] = Character::s_Ability.POINT;
		PAGE_STATES_point[1] = Character::s_Ability.STR;
		PAGE_STATES_point[2] = Character::s_Ability.DEX;
		PAGE_STATES_point[3] = Character::s_Ability.CON;
		PAGE_STATES_point[4] = Character::s_Ability.INT;
	}

//커서
	if (s_Page.Ly1_sel==1)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_4, XPOS+7, YPOS-64, 0);//호칭 커서
	if (s_Page.Ly1_sel>=2)
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_1, XPOS-71, YPOS+21 + (13*(s_Page.Ly1_sel-2)), 0);//스탯 커서

//케릭터 전신샷 보여주기
	_SUTIL->g->SetClip(XPOS-70,YPOS-64,49,64);	
	switch(Character::s_Status.ELEMENTAL){
		case 0:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//케릭터
			break;
		case 1:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//케릭터
			break;
		case 2:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-46, YPOS-5, 0);//케릭터
			break;
	}
	_SUTIL->g->ResetClip();

//속성
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
			_SUTIL->pFont->setOutlineColor((xx == (s_Page.Ly1_sel-2)? 0x003e9a: 0x202020));//증가된 값이면 아웃라인을 사용

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_POWER+xx], XPOS-66, YPOS+33 + (13*xx), CGraphics::BOTTOM);//힘//민첩//체력//지력
		_SUTIL->pFont->DrawText(_SUTIL->g, ABIL, XPOS-9, YPOS+33 + (13*xx), CGraphics::RIGHT|CGraphics::BOTTOM);//힘//민첩//체력//지력

		_SUTIL->pFont->setOutlineColor(-1);//아웃 라인을 사용하지 않음
	} 

	//호칭
	_SUTIL->pFont->setColor(0xf8e6cb);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_TITLETEMP], XPOS+37, YPOS-61, CGraphics::HCENTER);//호칭

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.LIFE,  XPOS+33, YPOS-46, 1 , CGraphics::RIGHT);//HP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.LIFE_MAX,  XPOS+59, YPOS-46, 1 , CGraphics::RIGHT);//HP MAX

	//HP,MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.MANA,  XPOS+33, YPOS-34, 1 , CGraphics::RIGHT);//MP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.MANA_MAX,  XPOS+59, YPOS-34, 1 , CGraphics::RIGHT);//MP MAX

	//EXP
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_S_NUM, Character::s_Status.EXP_MAX-Character::s_Status.EXP,  XPOS+59, YPOS-46+2*12, 1 , CGraphics::RIGHT);//HP,MP,EXP MAX

	//LV
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_LEVEL, XPOS-18,YPOS-8,0);//팝업 프레임 지정
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM, Character::s_Status.LEVEL,  XPOS-5, YPOS-8, 0 , 0);


	
	
	//명성치,//포인트
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

	if(s_Page.Focus == 1){// 팝업 - 스테이터스 적용 여부 확인
		//_SUTIL->g->blandBlur();
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + s_Page.Ly2_sel, XPOS,YPOS,0);//팝업 프레임 지정

		_SUTIL->pFont->setColor(0xf8e6cb);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q1], XPOS, YPOS+15, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
	}

}

void PopupUi::Paint_EQUIP()		
{
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_2, XPOS,YPOS,0);

//케릭터 전신샷 보여주기
	_SUTIL->g->SetClip(XPOS-36,YPOS-61,49,64);	
	switch(Character::s_Status.ELEMENTAL){
		case 0:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//케릭터
			break;
		case 1:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//케릭터
			break;
		case 2:
			SUTIL_Paint_Ani(m_pHeroAs ,ANIM_WOMAN_BODY_A_S_STAND, XPOS-12, YPOS-2, 0);//케릭터
			break;
	}
	_SUTIL->g->ResetClip();



	int Scroll_x = (SELECT_EQUIP_LIST_NOW-6 > 0?SELECT_EQUIP_LIST_NOW-6:0);

	SELECT_EQUIP_LIST_MAX = 0;

	for(int xx=0, Xpos=0, Ypos=0;xx<10;xx++){
		switch(xx){//해당 직업이 있으면 슬롯을 그려주고 만약 없다면 스킵한다.
			case 0:Xpos=-58	;Ypos=-62	;break;
			case 1:Xpos=20	;Ypos=-62	;break;
			case 2:Xpos=42	;Ypos=-62	;break;
			case 3:Xpos=-58	;Ypos=-44	;break;
			case 4:Xpos=-58	;Ypos=-26	;break;
			case 5:Xpos=20	;Ypos=-26	;
				if(Character::s_Ability.JAB_KNIFE){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//빈 슬롯  아이콘
				}else{continue;}break;
			case 6:Xpos=42	;Ypos=-26	;
				if(Character::s_Ability.JAB_KNIFE){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//빈 슬롯  아이콘
				}else{continue;}break;
			case 7:Xpos=-58	;Ypos=-8	;break;
			case 8:Xpos=20	;Ypos=-8	;
				if(Character::s_Ability.JAB_GUN){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//빈 슬롯  아이콘
				}else{continue;}break;
			case 9:Xpos=42	;Ypos=-8	;
				if(Character::s_Ability.JAB_MAGIC){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTYBOX, XPOS+Xpos-2,YPOS+Ypos-1,0,0);//빈 슬롯  아이콘
				}else{continue;}break;
		}

		//커서 그리기
		if(xx == SELECT_EQUIP_POS && SELECT_EQUIP_Y>0){
			if(SELECT_EQUIP_Y == 1){
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS+Xpos, YPOS+Ypos,0);//커서
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5,XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+17,0);//비활성 커서
				s_Popup_Sharp.posX = XPOS+Xpos;
				s_Popup_Sharp.posY = YPOS+Ypos;

			}else{
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS+Xpos, YPOS+Ypos,0);//비활성 커서
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3,XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17), YPOS+17,0);//커서
				s_Popup_Sharp.posX = XPOS-59+((SELECT_EQUIP_LIST_NOW-Scroll_x)*17);
				s_Popup_Sharp.posY = YPOS+17;
			}




			if(Character::s_ItemEquip[xx].ITEM_KIND){//아이템이 있다면

				if (Scroll_x==0){//스크롤이 일어나지 않았을때만 그려준다
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

		//아이콘그리기
		if(Character::s_ItemEquip[xx].ITEM_KIND){//아이템이 있다면
			paint_ICON(Character::s_ItemEquip[xx],XPOS+Xpos, YPOS+Ypos,false);
		}else{//아이템이 없다면
			SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EMPTY_00+(xx>5?xx-1:xx), XPOS+Xpos,YPOS+Ypos,0,0);//빈 슬롯  아이콘
		}

	}

	



	
	if(SELECT_EQUIP_Y>0){//커서가 내려와 있으면


	//장착 가능한 장비가 있으면 리스트형으로 열거해준다
		int Type;
		switch(SELECT_EQUIP_POS){//커서가 있는 슬롯이 무슨 아이템인지를 치환한다
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

		//장착되지않은 아이템을 순서대로 보여준다
		for(int xx = 0;xx<4;xx++){
			for(int yy = 0;yy<32;yy++){//가방을 돌면서 대상이 되는 아이템을 수집한다.

				if(Character::s_ItemBag[xx][yy].ITEM_EQUIP == 0){// 장비하지 않은 아이템중에
					int Kind = (Character::s_ItemBag[xx][yy].ITEM_KIND == ITEM_AXE ? ITEM_SWORD : Character::s_ItemBag[xx][yy].ITEM_KIND);

					if(Kind == Type){
						if((SELECT_EQUIP_LIST_MAX-Scroll_x)>=0 && (SELECT_EQUIP_LIST_MAX-Scroll_x)<=6){
							paint_ICON(Character::s_ItemBag[xx][yy],XPOS-59+((SELECT_EQUIP_LIST_MAX-Scroll_x)*17), YPOS+17,true);
						}
						if(SELECT_EQUIP_LIST_NOW == SELECT_EQUIP_LIST_MAX){
							
							SELECT_EQUIP_LIST_NOW_BAG = xx;//현재 선택된 아이템의 정보를 저장
							SELECT_EQUIP_LIST_NOW_SLOT = yy;//현재 선택된 아이템의 정보를 저장


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

	if(SELECT_EQUIP_LIST_MAX == 0){//만약 그리지 못했으면 그리준다
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
		if(Character::s_ItemSlot[xx].ITEM_KIND)//가방이 존재하면
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

	//소지금액 그리기
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status.MONEY,  XPOS+66, YPOS-58 , 1 , CGraphics::RIGHT);//MONEY


	//가방 커서 
	if(SELECT_INVENTORY_Y==1){
		if(Character::s_ItemPick.ITEM_KIND){//커서에 아이템을 들고있다면 그려준다
			if(!(s_Page.Focus == 1 && SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE)){//가방을 바꿀때 는 가방 커서가 없다
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//가방 선택
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68+(SELECT_INVENTORY_BAG*17)	+6, 
				YPOS-61								-4,0);//커서
			//아이콘
			paint_ICON(Character::s_ItemPick,XPOS-68+(SELECT_INVENTORY_BAG*17)+6, YPOS-61-4,true);
		}else{
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//가방 선택 ANI
		}
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_INVENTORY_BAG*17),YPOS-61,0);//가방 선택
	}



	//인벤 커서
	if(SELECT_INVENTORY_Y==2){//인벤내의 아이템을 선택
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//아이템이 없다면 그리지않는다
			itemTEXT(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]);
		}
		if(Character::s_ItemPick.ITEM_KIND == 0){//커서에 아이템이 없어야 그린다
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17), YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17),0);
			s_Popup_Sharp.posX = XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17);
			s_Popup_Sharp.posY = YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17);
		}
	}

	//가방내 아이템을 그리기 
	for(int xx = 0,MaxSlot = get_BagMax(Character::s_ItemSlot[SELECT_INVENTORY_BAG]);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx].ITEM_KIND){//아이템이 없다면 그리지않는다
			paint_ICON(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx], XPOS-68 + ((xx%8)*17), YPOS-40 + ((xx/8)*17),true);
		}
	}

	//인벤 커서
	if(SELECT_INVENTORY_Y==2){//인벤내의 아이템을 선택
		if(Character::s_ItemPick.ITEM_KIND){//커서에 아이템을 들고있다면 그려준다
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17)+6, 
				YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,0);//커서
			//아이콘
			paint_ICON(Character::s_ItemPick,XPOS-68 + ((SELECT_INVENTORY_INSIDE%8)*17)+6,YPOS-40 + ((SELECT_INVENTORY_INSIDE/8)*17)-4,true);
		}
	}


	if(s_Page.Focus == 1){// 팝업 그리기 - 아이템별 차등 팝업호출


		int Px = -68 + ((SELECT_INVENTORY_INSIDE%8)*17) + (((SELECT_INVENTORY_INSIDE%8)<4) ? 24 : -49);
		int Py = -40 + ((SELECT_INVENTORY_INSIDE/8)*17);

		

		switch(SELECT_INVENTORY_POPUP_KIND){//아이템 종류별 분화
			case INVENTORY_POPUP_QUICK://4개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_2,XPOS+Px,YPOS+Py,0);//4개짜리 팝업창

				for(int xx = 0;xx<4;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_USE:(xx==1?CLRMENU_QSLOT:(xx==2?CLRMENU_BAN:CLRMENU_MOVE)))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_EQUIP	://3개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3개짜리 팝업창

				for(int xx = 0;xx<3;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_DEFAULT : //2개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_4,XPOS+Px,YPOS+Py,0);//3개짜리 팝업창

				for(int xx = 0;xx<2;xx++){
					if(SELECT_INVENTORY_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_BAN:CLRMENU_MOVE)], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

				break;

			case INVENTORY_POPUP_BAGCHANGE	://가방 슬롯에 끼기
				int ss = 0;
				break;
		}
	}

	if(s_Page.Focus == 2){// 경고 팝업 그리기


		switch(SELECT_INVENTORY_POPUP_TEXT_KIND){//팝업의 종류
			case INVENTORY_TEXT_POPUP__NOT_ENOUGH://가방 공간부족
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//팝업 프레임 버튼

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q5], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+37, CGraphics::HCENTER);
				break;
			case INVENTORY_TEXT_POPUP__ABANDON://아이템 버리기 확인창
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_INVENTORY_POPUP_TEXT_YESNO, XPOS,YPOS,0);//팝업 프레임 지정

				_SUTIL->pFont->setColor(0xf8e6cb);
				{
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q4], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
				}break;
			case INVENTORY_TEXT_POPUP__EQUIPDEL://장착아이템 버리기불가
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//팝업 프레임 버튼

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
//배경
	int jab_Max;
	int Type[4];//3직업+1 갯수만큼의 배열이 생성된다.
	int xx=0;

//보유한 총 직업을 추출
	if(Character::s_Ability.JAB_KNIFE){
		Type[xx] = 1;xx++;
	}
	if(Character::s_Ability.JAB_GUN){
		Type[xx] = 2;xx++;
	}
	if(Character::s_Ability.JAB_MAGIC){
		Type[xx] = 3;xx++;
	}

	if(SELECT_SKILL_ACT_PAS){//패시브
		Type[xx] = 4;//공용
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1, XPOS,YPOS,0);

		if(true){//패시브 슬롯을 돈주고 샀으면
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1AFTER, XPOS,YPOS,0);
		}else{
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_1BEFORE, XPOS,YPOS,0);
		}

		jab_Max = 1+Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
	}else{//액티브
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2, XPOS,YPOS,0);
		jab_Max = Character::s_Ability.JAB_KNIFE+Character::s_Ability.JAB_GUN+Character::s_Ability.JAB_MAGIC;
	}

//커서와 텍스트를 뿌려줌
	_SUTIL->pFont->setColor(0xfbac29);//액티브,패시브
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_ACTIVE + SELECT_SKILL_ACT_PAS], XPOS, YPOS-59, CGraphics::HCENTER);

	for(int zz = 0;zz < MIN((jab_Max-1),2);zz++)
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI3, XPOS-63,YPOS+37+(zz*17),0);//비선택 직업창

	_SUTIL->pFont->setColor(0xb4fa1e);

	for(int yy = 0, findNum;yy < MIN(3,jab_Max);yy++){// 직업 텍스트
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
	SELECT_SKILL_TYPE_NOW = Type[(SELECT_SKILL_TYPE) % jab_Max]-1;//현재 선택된 직업

	//아이콘 뿌려주기 - 슬롯
	if(SELECT_SKILL_ACT_PAS){//패시브
		for(int xx = 0;xx<9;xx++){
			if(Character::s_Skill.Equip_P[xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00+Character::s_Skill.Equip_P[xx],
					XPOS-25 + ((xx%3)*18), 
					YPOS-37 + ((xx/3)*17),0);//비선택 직업창
		}
	}else{//액티브
		for(int xx = 0;xx<5;xx++){
			if(Character::s_Skill.Equip_A[xx] > -1)
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1+Character::s_Skill.Equip_A[xx],
				XPOS-63 + (xx*28), 
				YPOS-20, 0);
		}
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_4_2COVER, XPOS,YPOS,0);//스킬액자
	}


	int skill_Max=0;//아이콘 뿌려주기 - 스킬
	if(SELECT_SKILL_ACT_PAS){//패시브

		for(int xx = 0;xx<7;xx++){
			switch(SELECT_SKILL_TYPE_NOW){
				case 0:if(Character::s_Skill.Level_P[xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_S_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx;		skill_Max++;}break;//칼 패시브 스킬갯수
				case 1:if(Character::s_Skill.Level_P[7+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_G_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+7;	skill_Max++;}break;//총 패시브 스킬갯수
				case 2:if(Character::s_Skill.Level_P[14+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_O_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+14;	skill_Max++;}break;//마 패시브 스킬갯수
				case 3:if(Character::s_Skill.Level_P[21+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_PASSIVE_N_00 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+21;	skill_Max++;}break;//마 패시브 스킬갯수
			}
		}
	}else{//액티브

		for(int xx = 0;xx<7;xx++){
			switch(SELECT_SKILL_TYPE_NOW){ 
				case 0:if(Character::s_Skill.Level_A[xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx;		skill_Max++;}break;//칼 패시브 스킬갯수
				case 1:if(Character::s_Skill.Level_A[7+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_G_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+7;	skill_Max++;}break;//총 패시브 스킬갯수
				case 2:if(Character::s_Skill.Level_A[14+xx]){
							SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_O_1 + xx, 
							XPOS-13 + ((skill_Max%4)*18),YPOS+37 + ((skill_Max/4)*17),0);	
							if(skill_Max==SELECT_SKILL_KIND&&SELECT_SKILL_Y == 4)SELECT_SKILL_KIND_NOW=xx+14;	skill_Max++;}break;//마 패시브 스킬갯수
			}
		}
	}


	


//커서
	if(s_Page.Focus == 0){
		switch(SELECT_SKILL_Y){
			case 1://액티브 패시브 선택
				SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_2, XPOS-28, YPOS-62, 0);
				break;
			case 2://슬롯 선택
				if(SELECT_SKILL_ACT_PAS){//패시브
					if(SELECT_SKILL_KIND_NOW>=0){//커서에 아이콘을 들고있다면 그려준다
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
					
				}else{//액티브
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
			case 4://스킬 선택
					SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
						XPOS-14 + ((SELECT_SKILL_KIND%4)*18), 
						YPOS+36 + ((SELECT_SKILL_KIND/4)*17), 						0);
					s_Popup_Sharp.posX = XPOS-14 + ((SELECT_SKILL_KIND%4)*18);
					s_Popup_Sharp.posY = YPOS+36 + ((SELECT_SKILL_KIND/4)*17);
			case 3:
				if(SELECT_SKILL_ACT_PAS){//패시브
					SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, 
						XPOS-26 + ((SELECT_SKILL_SLOT%3)*18), 
						YPOS-38 + ((SELECT_SKILL_SLOT/3)*17), 						0);
				}else{//액티브
					SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI13, 
						XPOS-64 + (SELECT_SKILL_SLOT*28), 
						YPOS-21, 						0);
				}
				break;
		}
	}else if(s_Page.Focus == 0){
	}


	//하단에 기술명 ,레벨
	_SUTIL->pFont->setColor(0xffffff);
	if(SELECT_SKILL_Y == 2 || SELECT_SKILL_Y == 4){
		char str[30];//제목 최대크기
		int SkillNum;
		if(SELECT_SKILL_ACT_PAS){//패시브
			
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
			if(SELECT_SKILL_ACT_PAS){//패시브
				if(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT]>=0)
					PaintPopup_Sharp(Character::s_Skill.Equip_P[SELECT_SKILL_SLOT] + SKILL_P_S_swordMaster);
			}else{
				if(Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]>=0)
					PaintPopup_Sharp(Character::s_Skill.Equip_A[SELECT_SKILL_SLOT]);
			}
			
		}
		if(SELECT_SKILL_Y == 4){
			if(SELECT_SKILL_ACT_PAS){//패시브
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

		//메인 
		_SUTIL->pFont->setColor(0xfbab29);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MAIN], XPOS, YPOS-59, CGraphics::HCENTER);
		//서브
		_SUTIL->pFont->setColor(0xb4fa1e);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SUB], XPOS, YPOS-6, CGraphics::HCENTER);


		//메인퀘
		_SUTIL->pFont->setColor((SELECT_QUEST_Y==1 ?0xffda00 :0x748799)); 
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[GET_MAINQUEST_IDX()*2], XPOS-64, YPOS-38, 0); 

		//서브퀘
		for (int xx = 0; xx<MIN(5,s_Quest.Max_Num); xx++)
		{
			_SUTIL->pFont->setColor((SELECT_QUEST_Y==xx+2 ?0xffda00 :0x748799));
			if(s_Quest.SubHave[xx + SELECT_QUEST_SUB_Y]>=0){
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[s_Quest.SubHave[xx + SELECT_QUEST_SUB_Y]*2], XPOS-64, YPOS+16 + (15*xx), 0);
			}
		}

		//커서
		if(SELECT_QUEST_Y==1){//메인
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_7, XPOS-69,YPOS-41,0);
		}else if(SELECT_QUEST_Y>1){//서브
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_8, XPOS-69,YPOS+13+(SELECT_QUEST_Y-2)*15,0);
		}

		//스크롤바
		_SUTIL->g->SetColor(0xff6e00);
		if(s_Quest.Max_Num > 5){//바가 줄어야 함
			int Bar_height = MAX(30, (74 - (s_Quest.Max_Num-5)*10) );
			int yy = ((74 - Bar_height)*SELECT_QUEST_SUB_Y)/(s_Quest.Max_Num-5);
			_SUTIL->g->FillRect( XPOS+64, YPOS+14+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+64, YPOS+14,4,74);
		}

	}else if(s_Page.Focus==1){//세부 설명 페이지
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_6_2, XPOS,YPOS,0);

		int titleNum;
		if(SELECT_QUEST_Y==1){//메인퀘스트
			titleNum = GET_MAINQUEST_IDX()*2;
		}else{
			titleNum = s_Quest.SubHave[SELECT_QUEST_Y-2 + SELECT_QUEST_SUB_Y]*2;
		}

		//아이템 수집 현황
		char str[31];//아이템 텍스트
		int Num = Set_QUEST(NULL,GET_MAINQUEST_IDX());
		if(Q_ITEM_ID(Num)){
			_SUTIL->pFont->setOutlineColor(0X000000);//아웃 라인을 사용
			if(Q_ITEM_NOW(Num) < Q_ITEM_MAX(Num)){//퀘스트 갯수미달
				_SUTIL->pFont->setColor(0xFF5E39);
				SPRINTF(str, "%s (%d/%d)",
					(char*)pITEM_Text->nText[itemNAME(Q_ITEM_ID(Num)/100,Q_ITEM_ID(Num)%100)],
					Q_ITEM_NOW(Num),
					Q_ITEM_MAX(Num)); 
			}else{//퀘스트 완료
				_SUTIL->pFont->setColor(0x00FF00);
				SPRINTF(str, "%s (%s)",
					(char*)pITEM_Text->nText[itemNAME(Q_ITEM_ID(Num)/100,Q_ITEM_ID(Num)%100)],
					(char*)pITEM_Text->nText[ITEM_CLEAR]); 	
			}
			_SUTIL->pFont->DrawText(_SUTIL->g, str,XPOS, YPOS-44, CGraphics::HCENTER);
			_SUTIL->pFont->setOutlineColor(-1);//아웃 라인을 사용하지 않음
		}
		


		//퀘스트명
		_SUTIL->pFont->setColor(0x93abc0);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[titleNum], XPOS, YPOS-62, CGraphics::HCENTER);
		
		//퀘스트 설명
		_SUTIL->pFont->setColor(0xFFFFFF);
		_SUTIL->pFont->setLineSpace(3);

		_SUTIL->pFont->Dry_Wrap_Width(134);
		_SUTIL->pFont->Dry_StartLine_Max(SELECT_QUEST_DESC_Y,QUEST_DESC);
		SELECT_QUEST_DESC_Y_MAX = _SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMAIN_QUEST_Text->nText[titleNum+1], XPOS-74, YPOS-29, CGraphics::LEFT);



		//스크롤바
		_SUTIL->g->SetColor(0xff6e00);
		if(SELECT_QUEST_DESC_Y_MAX > QUEST_DESC){//바가 줄어야 함
			int Bar_height = MAX(30, (102 - (SELECT_QUEST_DESC_Y_MAX-QUEST_DESC)*10) );
			int yy = ((102 - Bar_height)*SELECT_QUEST_DESC_Y)/(SELECT_QUEST_DESC_Y_MAX-QUEST_DESC);
			_SUTIL->g->FillRect( XPOS+66, YPOS-37+yy,4,Bar_height);			
		}else{
			_SUTIL->g->FillRect( XPOS+66, YPOS-37,4,102);
		}

		//버튼
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_QUEST_DESC_X, XPOS,YPOS+40,0);//팝업 프레임 지정
		_SUTIL->pFont->setColor(0xf8e6cb);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_CLOSE], XPOS-31, YPOS+77, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_DISCARD], XPOS+31, YPOS+77, CGraphics::HCENTER);
	}


}

void PopupUi::Paint_SYSTEM()	
{
	if(s_Page.Focus==0){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_7, XPOS,YPOS,0);

		//텍스트
		for (int xx = 0; xx<5; xx++)
		{
			_SUTIL->pFont->setColor((SELECT_SYSTEM_Y-1==xx ?0xffda00 :0x546779));
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_SYSTEM_0+xx], XPOS,YPOS-39 + (xx*24), CGraphics::HCENTER);
		}
 
		//커서
		if(SELECT_SYSTEM_Y>0){
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_6, XPOS-44,YPOS-45 + ((SELECT_SYSTEM_Y-1)*24),0);
		}
		
	}

	if(s_Page.Focus == 10){// 팝업 - 스테이터스 적용 여부 확인
//		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_UI_TRAFFIC, XPOS,YPOS-50,0);//팝업 프레임 지정
		
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
		if(Character::s_ItemSlot[xx].ITEM_KIND)//가방이 존재하면
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

	//소지금액 그리기
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_MONEY, Character::s_Status.MONEY,  XPOS+66, YPOS-58 , 1 , CGraphics::RIGHT);//MONEY


	//가방 커서 
	if(SELECT_ITEMSHOP_Y==1){
		if(Character::s_ItemPick.ITEM_KIND){//커서에 아이템을 들고있다면 그려준다
			if(!(s_Page.Focus == 1 && SELECT_ITEMSHOP_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE)){//가방을 바꿀때 는 가방 커서가 없다
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//가방 선택
			}
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68+(SELECT_ITEMSHOP_BAG*17)	+6, 
				YPOS-61								-4,0);//커서
			//아이콘
			paint_ICON(Character::s_ItemPick,XPOS-68+(SELECT_ITEMSHOP_BAG*17)+6, YPOS-61-4,true);
		}else{
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//가방 선택 ANI
		}
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI5, XPOS-68+(SELECT_ITEMSHOP_BAG*17),YPOS-61,0);//가방 선택
	}



	//인벤 커서
	if(SELECT_ITEMSHOP_Y==2){//인벤내의 아이템을 선택
		if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE].ITEM_KIND){//아이템이 없다면 그리지않는다
			itemTEXT(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][SELECT_ITEMSHOP_INSIDE]);
		}
		if(Character::s_ItemPick.ITEM_KIND == 0){//커서에 아이템이 없어야 그린다
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17), YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17),0);
			s_Popup_Sharp.posX = XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17);
			s_Popup_Sharp.posY = YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17);
		}
	}

	//가방내 아이템을 그리기 
	for(int xx = 0,MaxSlot = get_BagMax(Character::s_ItemSlot[SELECT_ITEMSHOP_BAG]);xx<MaxSlot;xx++){
		if(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx].ITEM_KIND){//아이템이 없다면 그리지않는다
			paint_ICON(Character::s_ItemBag[SELECT_ITEMSHOP_BAG][xx], XPOS-68 + ((xx%8)*17), YPOS-40 + ((xx/8)*17),true);
		}
	}

	//인벤 커서
	if(SELECT_ITEMSHOP_Y==2){//인벤내의 아이템을 선택
		if(Character::s_ItemPick.ITEM_KIND){//커서에 아이템을 들고있다면 그려준다
			SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_CURSOR_3, 
				XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17)+6, 
				YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17)-4,0);//커서
			//아이콘
			paint_ICON(Character::s_ItemPick,XPOS-68 + ((SELECT_ITEMSHOP_INSIDE%8)*17)+6,YPOS-40 + ((SELECT_ITEMSHOP_INSIDE/8)*17)-4,true);
		}
	}


	if(s_Page.Focus == 1){// 팝업 그리기 - 아이템별 차등 팝업호출


		int Px = -68 + ((SELECT_ITEMSHOP_INSIDE%8)*17) + (((SELECT_ITEMSHOP_INSIDE%8)<4) ? 24 : -49);
		int Py = -40 + ((SELECT_ITEMSHOP_INSIDE/8)*17);



		switch(SELECT_ITEMSHOP_POPUP_KIND){//아이템 종류별 분화
			case INVENTORY_POPUP_QUICK://4개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_2,XPOS+Px,YPOS+Py,0);//4개짜리 팝업창

				for(int xx = 0;xx<4;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_USE:(xx==1?CLRMENU_QSLOT:(xx==2?CLRMENU_BAN:CLRMENU_MOVE)))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_EQUIP	://3개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_3,XPOS+Px,YPOS+Py,0);//3개짜리 팝업창

				for(int xx = 0;xx<3;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_EQUIP:(xx==1?CLRMENU_BAN:CLRMENU_MOVE))], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

			case INVENTORY_POPUP_DEFAULT : //2개
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_4,XPOS+Px,YPOS+Py,0);//3개짜리 팝업창

				for(int xx = 0;xx<2;xx++){
					if(SELECT_ITEMSHOP_POPUP_Y == xx){
						_SUTIL->pFont->setColor(0xcfeef4);
						SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2,XPOS+Px,YPOS+Py+(19*xx),0);//선택커서
					}else{
						_SUTIL->pFont->setColor(0x3a444d);

					}
					_SUTIL->pFont->DrawText(_SUTIL->g, 
						(char*)pCLRPOPUP_Text->nText[(xx==0?CLRMENU_BAN:CLRMENU_MOVE)], 
						XPOS+Px+20, YPOS+Py+5+(19*xx), CGraphics::HCENTER);
				}
				break;

				break;

			case INVENTORY_POPUP_BAGCHANGE	://가방 슬롯에 끼기
				int ss = 0;
				break;
		}
	}

	if(s_Page.Focus == 2){// 경고 팝업 그리기


		switch(SELECT_ITEMSHOP_POPUP_TEXT_KIND){//팝업의 종류
			case INVENTORY_TEXT_POPUP__NOT_ENOUGH://가방 공간부족
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//팝업 프레임 버튼

				_SUTIL->pFont->setColor(0xf8e6cb);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q5], XPOS, YPOS+15, CGraphics::HCENTER);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_IDENTIFY], XPOS, YPOS+37, CGraphics::HCENTER);
				break;
			case INVENTORY_TEXT_POPUP__ABANDON://아이템 버리기 확인창
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + SELECT_ITEMSHOP_POPUP_TEXT_YESNO, XPOS,YPOS,0);//팝업 프레임 지정

				_SUTIL->pFont->setColor(0xf8e6cb);
				{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q4], XPOS, YPOS+15, CGraphics::HCENTER);
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
				}break;
			case INVENTORY_TEXT_POPUP__EQUIPDEL://장착아이템 버리기불가
				_SUTIL->g->blandBlur();
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CURSOR_UI2, XPOS-20,YPOS+33,0);//팝업 프레임 버튼

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

	if(posX + WIDTH > SCREEN_WIDTH){//스크린 영역을 벗어난다면
		posX-= (posX + WIDTH)-SCREEN_WIDTH;
	}
	if(posY + HEIGHT > SCREEN_HEIGHT){//스크린 영역을 벗어난다면 
		posY-= HEIGHT;
	}else{
		posY+=15;
	}



	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_6, posX,posY,0);//반투명 프레임

	int head =		_item.ITEM_HEADTEXT;
	int upgrade =	_item.ITEM_UPGRADE;
	int socket1 =	_item.ITEM_SOCKET_1;
	int socket2 =	_item.ITEM_SOCKET_2;
	int socket3 =	_item.ITEM_SOCKET_3;
	char str[31];//int 최대크기



	switch(_item.ITEM_KIND){//아이템 종류별 분화
		case ITEM_BAG	:
			//아이템 이름
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//아이템 설명
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "%d SLOT",8);break;
				case 1:SPRINTF(str, "%d SLOT",16);break;
				case 2:SPRINTF(str, "%d SLOT",24);break;
				case 3:SPRINTF(str, "%d SLOT",32);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//스크롤바
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;

		case ITEM_POTION:

			//아이템 이름
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//아이템 설명
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "Hp + %d%",15);break;
				case 1:SPRINTF(str, "Hp + %d%",40);break;
				case 2:SPRINTF(str, "Hp + %d%",65);break;

				case 3:SPRINTF(str, "Mp + %d%",5);break;
				case 4:SPRINTF(str, "Mp + %d%",15);break;
				case 5:SPRINTF(str, "Mp + %d%",20);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//스크롤바
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;
		case ITEM_MAINQUEST:
			//아이템 이름
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], posX+START_X, posY+START_Y, 0);

			//아이템 설명
			SPRINTF(str, "Quest Item",15);
			_SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y+GAP_Y, 0);

			//스크롤바
			_SUTIL->g->SetColor(0x76aebf);
			_SUTIL->g->FillRect( posX+109, posY+16,5,30);
			break;

		default://장비류
			s_Popup_Sharp.LineMAX = 1;
			if(s_Popup_Sharp.Line == 0){
				//아이템 색상
				switch(_item.ITEM_GRADE){
					case 0:_SUTIL->pFont->setColor(0xffffff);break;
					case 1:_SUTIL->pFont->setColor(0x72fa28);break;
					case 2:_SUTIL->pFont->setColor(0x52c4ff);break;
					case 3:_SUTIL->pFont->setColor(0x916aff);break;
					case 4:_SUTIL->pFont->setColor(0xff6c32);break;
				}


				//아이템 이름

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

				//등급
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_G_NORMAL + _item.ITEM_GRADE], posX+START_X, posY+START_Y+GAP_Y, 0);

				


				

				//성별
				_SUTIL->pFont->setColor(0xffffff);//성별안되면 빨간색으로 바꿔주기 추후구현
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_HUMAN + _item.ITEM_SEX], posX+START_X + 40, posY+START_Y+GAP_Y, 0);

				//레벨 제한
				_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
				SPRINTF(str, "%s%d", "Lv",
					(((_item.ITEM_KIND) == ITEM_NECK)||((_item.ITEM_KIND) == ITEM_RING)? deco_Table[_item.ITEM_INDEX][D_T_LV]: equip_Table[_item.ITEM_INDEX][E_T_LV])); 	
				_SUTIL->pFont->DrawText(_SUTIL->g, str,posX+START_X+95, posY+START_Y+GAP_Y, Graphics::RIGHT);


				

				//ATT DEF
				switch(_item.ITEM_KIND){//아이템 종류별 분화
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

				//능력치
				int scroll_Kind = (_item.Data2/100)%100; //스크롤 종류
				if(scroll_Kind){
					int UP = (((_item.Data2/10000) %1000) /3) +1; //스크롤 상승치
					switch(scroll_Kind){//스크롤 종류
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

				//스크롤바
				_SUTIL->g->SetColor(0x76aebf);
				_SUTIL->g->FillRect( posX+109, posY+16,5,15);
			}else{
				int Line_Y = 0;

				//소켓 없을때

				


				if(socket1){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//소켓이미지
					Line_Y+=17;
				}else{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO_SOCKET], posX+START_X, posY+START_Y+Line_Y, 0);
				}
				if(socket2){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//소켓이미지
					Line_Y+=17;
				}
				if(socket3){
					SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_SOCKET, posX+START_X, posY+START_Y+Line_Y,0,0);//소켓이미지
					Line_Y+=17;
				}
					
		
				//스크롤바
				_SUTIL->g->SetColor(0x76aebf);
				_SUTIL->g->FillRect( posX+109, posY+16+15,5,15);


			}

			

			



			
			break;

	}

	////스크롤바
	//_SUTIL->g->SetColor(0xff6e00);
	//if(s_Quest.Max_Num > 5){//바가 줄어야 함
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

	if(posX + WIDTH > SCREEN_WIDTH){//스크린 영역을 벗어난다면
		posX-= (posX + WIDTH)-SCREEN_WIDTH;
	}
	if(posY + HEIGHT > SCREEN_HEIGHT){//스크린 영역을 벗어난다면 
		posY-= HEIGHT+2;
	}else{
		posY+=15;
	}



	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_6, posX,posY,0);//반투명 프레임



	char str[600];//int 최대크기
	int Line_Max = 0;


	//텍스트를 합쳐서 한줄로 뽑아낸다
	if(Skill_Num<SKILL_P_S_swordMaster){//액티브 스킬

		int Skill_Lv = Character::s_Skill.Level_A[Skill_Num];//스킬 레벨

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

		_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
		s_Popup_Sharp.LineMAX = _SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y, 0) - 5;

	}else{//패시브 스킬
		Skill_Num -= SKILL_P_S_swordMaster;

		int Skill_Lv = Character::s_Skill.Level_P[Skill_Num];//스킬 레벨

		SPRINTF(str, "%s LV%d||%s",
			(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (Skill_Num*2)],
			Skill_Lv,
			(char*)pCLRPOPUP_Text->nText[CLRMENU_PASSIVE_S_1 + (Skill_Num*2)+1]); 	


		_SUTIL->pFont->Dry_Wrap_Width(100);
		_SUTIL->pFont->Dry_StartLine_Max(s_Popup_Sharp.Line,5);

		_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
		char Num[10];//int 최대크기
		SPRINTF(Num, "%d",a_Passive_Table[Skill_Num*5 + (Skill_Lv-1)][0]); 	
		s_Popup_Sharp.LineMAX = _SUTIL->pFont->DrawText(_SUTIL->g, str, posX+START_X, posY+START_Y, 0,Num ) - 5;


	}

	


	//스크롤바
	_SUTIL->g->SetColor(0xff6e00);
	if(s_Popup_Sharp.LineMAX > 0){//바가 줄어야 함
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
    int FullSpace = 0;//숫자의 자릿수
	int wordsize = pAsIns->GetModuleWidth(numImgIdx);//1글자 폭
	int decimal =0;//자릿수
	int tmpcount = value;

	for(int xx = 0;xx<20 ;xx++)
	{//자릿수 구하기
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
	{//숫자그리기
		SUTIL_Paint_Module(pAsIns,numImgIdx + (value%10),x - xx*(wordsize+gap),y,0,position & (CGraphics::TOP|CGraphics::VCENTER|CGraphics::BOTTOM))	;//끝자리부터 하나씩 그려준다
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
{//아이템 아이콘을 뿌려줄때
	switch(_item.ITEM_KIND)
	{//아이템 종류별 분화
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
					return MODULE_ITEM_SPIRITSTONE_05;//자수정
				case ITEM_CALL_diary:
					return MODULE_ITEM_SKILLBOOK_03;//일지
				default:
					return MODULE_ITEM_QUESTITEM;
			}
	}
	return 0;
}

int PopupUi::itemNAME(int m_Kind, int m_Index)
{//아이템 이름을 뿌려줄때
	
		switch(m_Kind)
		{//아이템 종류별 분화
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
{//아이템 이름을 뿌려줄때


	int head =		_item.ITEM_HEADTEXT;
	int upgrade =	_item.ITEM_UPGRADE;
	int socket1 =	_item.ITEM_SOCKET_1;
	int socket2 =	_item.ITEM_SOCKET_2;
	int socket3 =	_item.ITEM_SOCKET_3;
	char str[31];//int 최대크기
	


	switch(_item.ITEM_KIND){//아이템 종류별 분화
		case ITEM_BAG	:
			//아이템 이름
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);

			//아이템 설명
			switch(_item.ITEM_INDEX){
				case 0:SPRINTF(str, "%d SLOT",8);break;
				case 1:SPRINTF(str, "%d SLOT",16);break;
				case 2:SPRINTF(str, "%d SLOT",24);break;
				case 3:SPRINTF(str, "%d SLOT",32);break;
			}	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+67, 0);
			break;

		case ITEM_POTION:

		//아이템 이름
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);

		//아이템 설명
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
			//아이템 이름
			_SUTIL->pFont->setColor(0xffaaaa);//레벨안되면 빨간색으로 바꿔주기 추후구현
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pITEM_Text->nText[itemNAME(_item.ITEM_KIND,_item.ITEM_INDEX)], XPOS-64, YPOS+37, 0);


			break;

		default://장비류


		//아이템 색상
			switch(_item.ITEM_GRADE){
				case 0:_SUTIL->pFont->setColor(0xffffff);break;
				case 1:_SUTIL->pFont->setColor(0x72fa28);break;
				case 2:_SUTIL->pFont->setColor(0x52c4ff);break;
				case 3:_SUTIL->pFont->setColor(0x916aff);break;
				case 4:_SUTIL->pFont->setColor(0xff6c32);break;
			}


		//아이템 이름
			
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
			

		//소켓
			if(socket1 + socket2 + socket3){
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,
					FRAME_UI_UI_3_1SOCKET + (socket2?(socket3?2:1):0)
					, XPOS,YPOS,0);//가방 선택
			}


		//레벨 제한
			_SUTIL->pFont->setColor(0xffffff);//레벨안되면 빨간색으로 바꿔주기 추후구현
			SPRINTF(str, "%s %d",
				"Lv",
				(((_item.ITEM_KIND) == ITEM_NECK)||((_item.ITEM_KIND) == ITEM_RING)? deco_Table[_item.ITEM_INDEX][D_T_LV]: equip_Table[_item.ITEM_INDEX][E_T_LV])); 	
			_SUTIL->pFont->DrawText(_SUTIL->g, str, XPOS-64, YPOS+55, 0);

		//ATT DEF
			switch(_item.ITEM_KIND){//아이템 종류별 분화
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

		//능력치
			int scroll_Kind = (_item.Data2/100)%100; //스크롤 종류
			if(scroll_Kind){
				int UP = (((_item.Data2/10000) %1000) /3) +1; //스크롤 상승치
				switch(scroll_Kind){//스크롤 종류
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

		//인포
			SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_INFO, XPOS+44,YPOS+83,0,0);


		break;
			
	}

	

}




void PopupUi::USE_item(struct ItemBag *_item){//아이템 사용

	switch(_item->ITEM_KIND){
		case ITEM_POTION://물약

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
				case 0://소물약
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,15);
					break;
				case 1://중물약
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,40);
					break;
				case 2://대물약
					Character::s_Status.LIFE += PER(Character::s_Status.LIFE_MAX,65);
					break;
				case 3://소마나
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,5);
					break;
				case 4://중마나
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,15);
					break;
				case 5://대마나
					Character::s_Status.MANA += PER(Character::s_Status.MANA_MAX,20);
					break;
			}
			if(Character::s_Status.LIFE>Character::s_Status.LIFE_MAX)Character::s_Status.LIFE=Character::s_Status.LIFE_MAX;
			if(Character::s_Status.MANA>Character::s_Status.MANA_MAX)Character::s_Status.MANA=Character::s_Status.MANA_MAX;
			break;
	}

}
void PopupUi::QSLOT_item(struct ItemBag *_item){//퀵슬롯
	if(_item->ITEM_EQUIP){// 이미 장비한 아이템이면 반응하지않는다
		return;
	}


		for(int xx = 0;xx<4;xx++){//모든 인벤을 돌면서 기존의 Equip장비를 찾아 풀어준다
			for(int yy = 0;yy<32;yy++){
				if(Character::s_ItemBag[xx][yy].ITEM_EQUIP){//장비템 중에
					switch(Character::s_ItemBag[xx][yy].ITEM_KIND){//퀵슬롯템을 해제시킨다
						case ITEM_POTION://물약
							Character::s_ItemBag[xx][yy].Data0 %= 10000000;//장비해제
							xx = 4;yy = 32;//이탈
							break;
					}
				}
			}
		}

	//switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){//아이템 종류별 분화
	//							case ITEM_POTION:

	_item->Data0  = (_item->Data0 %= 10000000) + 10000000;
	Character::s_Status.Qslot[0] = SELECT_INVENTORY_BAG;
	Character::s_Status.Qslot[1] = SELECT_INVENTORY_INSIDE;
}

void PopupUi::QSLOT_find(){//퀵슬롯

	for(int xx = 0;xx<4;xx++){//모든 인벤을 돌면서 기존의 Equip장비를 찾아 풀어준다
		for(int yy = 0;yy<32;yy++){
			if(Character::s_ItemBag[xx][yy].ITEM_EQUIP){//장비템 중에
				switch(Character::s_ItemBag[xx][yy].ITEM_KIND){//퀵슬롯템 위치를 갱신한다
						case ITEM_POTION://물약
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
	if(_item->ITEM_EQUIP){// 이미 장비한 아이템이면 반응하지않는다
		return;
	}

	

	if(Character::s_ItemEquip[slot].ITEM_EQUIP){//장착 해야할 슬롯에 아이템이 이미존재한다면
		for(int xx = 0;xx<4;xx++){//모든 인벤을 돌면서 기존의 Equip장비를 찾아 풀어준다
			for(int yy = 0;yy<32;yy++){
				if(Character::s_ItemEquip[slot].Data0 ==  Character::s_ItemBag[xx][yy].Data0){//ID가 종일한 아이템중에 - 동일 계열
					//if(Character::s_ItemEquip[slot].Data1 ==  Character::s_ItemBag[xx][yy].Data1){
						Character::s_ItemBag[xx][yy].Data0 %= 10000000;//장비해제
						xx = 4;yy = 32;//이탈
						//기존 장비 기록 삭제
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
	Character::Set_state_calculate();//변화된 능력치 계산


	int index = _item->ITEM_INDEX;

	
	int Axe = 0;
	int HeadText = 0;
	int SW_AX = (_item->ITEM_KIND == ITEM_SWORD?C_T_SW:C_T_AX);

	if(_item->ITEM_KIND == ITEM_AXE){
		Axe = (SPRITE_COSTUME_HUMAN_0_AXE - SPRITE_COSTUME_HUMAN_0_SWORD);
	}
	
	HeadText = head_Table[_item->ITEM_HEADTEXT][H_T_COSUME];

	SUTIL_LoadAspritePack(PACK_SPRITE_COSTUME);//팩열기
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
	SUTIL_ReleaseAspritePack();//팩닫기

}//아이템 착용
void PopupUi::DEL_item(){//아이템 버리기
	if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_EQUIP){// 이미 장비한 아이템이면 반응하지않는다
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
void PopupUi::MOVE_item(){//아이템 이동 및 합치기

	if(s_Page.Focus == 1 && SELECT_INVENTORY_POPUP_KIND == INVENTORY_POPUP_BAGCHANGE){//가방을 바꿀때

		int targetBag = get_BagMax(Character::s_ItemSlot[SELECT_INVENTORY_BAG]);
		int cursorBag = get_BagMax(Character::s_ItemPick);

		if(targetBag > cursorBag){//교체할 가방이 더 작은 가방이라면 
			int Bag_interNum = 0;
			for(int xx = 0;xx<targetBag;xx++)//아이템 갯수체크
				if(Character::s_ItemBag[SELECT_INVENTORY_BAG][xx].Data0)
					Bag_interNum++;//빈칸이 아니면 아이템 갯수 증가


			if(Bag_interNum > cursorBag){//가방 공간이 기존아이템을 수용할 수 없다면
				//경고 팝업창
				s_Page.Focus = 2;//가방이 충분하지않습니다 경고창 뜨기
				SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__NOT_ENOUGH;
				return;
			}else if(Bag_interNum == cursorBag){//가방이 교체칸과 딱 맞다면 다른가방에 빈슬롯이 존재하는지 검색해야한다
				bool freeSlot = false;

				for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 빈공간을 찾아낸다
					if(SELECT_INVENTORY_BAG != xx){
						switch(Character::s_ItemSlot[xx].Data0){
							case 100:MaxSlot= 8;break;
							case 101:MaxSlot= 16;break;
							case 102:MaxSlot= 24;break;
							case 103:MaxSlot= 32;break;
							default:MaxSlot= 0;break;
						}
						for(int yy = 0;yy<MaxSlot;yy++){
							if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//비어있는슬롯이 있으면
								freeSlot = true;
							}
						}
					}
				}

				if(freeSlot){
					SORTING_bag(SELECT_INVENTORY_BAG);
					QSLOT_find();//퀵슬롯 위치가 바뀌었으므로 재갱신한다
				}else{
					//경고 팝업창
					s_Page.Focus = 2;//가방이 충분하지않습니다 경고창 뜨기
					SELECT_INVENTORY_POPUP_TEXT_KIND = INVENTORY_TEXT_POPUP__NOT_ENOUGH;
					return;
				}

			}else{//수용 가능하다면 아이템을 앞으로 정렬
				SORTING_bag(SELECT_INVENTORY_BAG);
				QSLOT_find();//퀵슬롯 위치가 바뀌었으므로 재갱신한다
			}
		}
		

		struct ItemBag temp = Character::s_ItemSlot[SELECT_INVENTORY_BAG];
		Character::s_ItemSlot[SELECT_INVENTORY_BAG]=Character::s_ItemPick;
		Character::s_ItemPick = temp;

		s_Page.Focus = 0;//팝업 해제
	}else{// 아이템 위치를 바꿀때
		if((Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_INDEX==Character::s_ItemPick.ITEM_INDEX) && (Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND==Character::s_ItemPick.ITEM_KIND))
		{//만약 동일 아이템 & 스택 아이템일 경우에 아래쪽으로 풀스택을 먼저 채운다
			int MaxStack = 99;//개까지 스택가능
			switch(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_KIND){
				case ITEM_MAINQUEST://10개 겹치는 아이템
					MaxStack = 10;
				case ITEM_POTION://99개 스택
					if(Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT < MaxStack){//풀스택 아님
						int Sum = Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT+Character::s_ItemPick.ITEM_STACK_COUNT;

						if(Sum > MaxStack){//풀스택 오버 플로
							Character::s_ItemPick.Data1 -= MaxStack-Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].ITEM_STACK_COUNT;
							Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1 = MaxStack + ((Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE].Data1/100)*100);
						}else{//하나로 합쳐짐
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
		
		//템 교체
		struct ItemBag temp = Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE];
		Character::s_ItemBag[SELECT_INVENTORY_BAG][SELECT_INVENTORY_INSIDE]=Character::s_ItemPick;
		Character::s_ItemPick = temp;
		QSLOT_find();
	}

	
}

void PopupUi::SORTING_bag(int bagNum){//가방속을 앞으로 정렬

	struct ItemBag temp;

	int SlotMax = get_BagMax(Character::s_ItemSlot[bagNum]);

	for(int xx = 0;xx<SlotMax;xx++){
		if(Character::s_ItemBag[bagNum][xx].ITEM_KIND == 0){//빈공간 발견
			for(int yy = xx+1;yy<SlotMax;yy++){
				if(Character::s_ItemBag[bagNum][yy].ITEM_KIND){//비어있지 않은 공간 발견
					temp = Character::s_ItemBag[bagNum][xx];
					Character::s_ItemBag[bagNum][xx] = Character::s_ItemBag[bagNum][yy];
					Character::s_ItemBag[bagNum][yy] = temp;
					break;
				}
				if(yy==(SlotMax-1) && Character::s_ItemBag[bagNum][yy].ITEM_KIND == 0){//마지막칸까지 아이템이 있는 칸이 없을때(종료)
					return;
				}
			}
		}
	}
	
}
bool PopupUi::INPUT_bag(int bagNum, struct ItemBag _item){//가방 정렬
	return false;
}

int PopupUi::get_BagMax(struct ItemBag _item){//가방 인벤갯수 리턴
	switch(_item.Data0){
		case 100:return 8;
		case 101:return 16;
		case 102:return 24;
		case 103:return 32;
		default:return 0;
	}
}
void PopupUi::paint_ICON(struct ItemBag _item, int x, int y,bool full){//아이템의 갯수를 표시한다
	if(_item.ITEM_KIND == 0)return;

	SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,itemICON(_item),x, y,0,0);//아이콘
	if(full){
		//스택이 되는 아이템의 경우 숫자로 표시를 한다
		switch(_item.ITEM_KIND){//갯수가 표시될 아이템
			case ITEM_POTION:
			case ITEM_MAINQUEST:
				if(_item.Data1>1){
					PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_SKILL_NUM, _item.ITEM_STACK_COUNT,  x+16, y+9, -1 , CGraphics::RIGHT);//아이템 갯수
				}
				break;
		}

		switch(_item.ITEM_KIND){//장비 여부가 표시될 아이템  DATA1 의 최상위자릿수가 0이면 비장착 1이면 장착
			case ITEM_POTION://쿽슬롯
			case ITEM_SWORD	:
			case ITEM_AXE	:
			case ITEM_GUN	:
			case ITEM_OEB	:
			case ITEM_HEAD	:
			case ITEM_CHEST	:
			case ITEM_LEG	:
			case ITEM_GLOVE	:
			case ITEM_NECK	:
			case ITEM_RING	://장비 장착
				if(_item.ITEM_EQUIP)SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_EQUIP,x, y,0,0);//아이콘
				break;
		}
	}
}
void PopupUi::Del_Item(struct ItemBag *_item){//아이템 삭제
	_item->Data0 = 0;
	_item->Data1 = 0;
	_item->Data2 = 0;
}
void PopupUi::Del_Slot(int slot){//가방 인벤갯수 리턴
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
ItemBag PopupUi::MakeItem(int nMontype, int nMonLevel, int nHeroSex, int mapIdx)		//성별man:0,girl:1
//--------------------------------------------------------------------------
{
	ItemBag tmpBag;
	tmpBag.Data0 = 0;

	//	퀘스트 처리
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


	//	드랍되는 아이템의 종류	
	const short drop_type_Table[4][5]=
	{
		//			  장비아이템, 소비아이템,	  돈,	스탯스크롤
		{		20	,		50	,		100	,	100	,		50	},
		{		40	,		45	,		106	,	104	,		45	},
		{		60	,		43	,		106	,	108	,		43	},
		{		999	,		37	,		112	,	114	,		37	},
	};


	//	드랍되는 아이템의 사용성별	//0번째는 여자테이블	1번째는 남자테이블
	const short man_girl_Table[2][3]=
	{
		//	남자,	  여자,		공용
		{		20	,		40	,		40},
		{		40	,		20	,		40},
	};

	//	감정탬(일반템, 감정템)
	const short judgment_Table[2]=	{80, 20};

	//	드랍되는 아이템의 종류	
	const short drop_level_Table[5][6]=
	{
		//렙제		노멀,		매직,		레어,	유니크,		스페셜
		{ 0,		220	,		80	,		 0	,	0	,		0	},
		{16,		210	,		80	,		10	,	0	,		0	},
		{26,		202	,		82	,		12	,	4	,		0	},
		{40,		199	,		82	,		14	,	3	,		2	},
		{55,		189	,		82	,		17	,	8	,		4	},
	};

	//	소켓 확률(없음 확률)(일반템, 감정템)
	const short socket_Table[2]=	{80, 50};

	//	접두사 확률(없음 확률)(일반템, 감정템)
	const short hedertext_Table[2]=	{80, 50};


	int loop = 0;
	int dice = 0;
	int temp = 0;
	short tableidx_b = 0;	//	종류
	short tableidx_c = 0;	//	성별
	short tableidx_d = 0;	//	판정템
	short tableidx_e = 0;	//	아이템 레벨
	short tableidx_f = 0;	//	아이템 등급
	short tableidx_g = 0;	//	소켓의 종류
	short tableidx_h = 0;	//	접두사가 붙을 확률
	short tableidx_j = 0;	//	아이템 인덱스

	int tableidx_ex_1 = 0;		//	장비의 종류
	//	아이템이 떨어질 확률	///////////////////////////////
	dice = SUTIL_GetRandom()%100;
	if(50 > dice)	{return tmpBag;}

	//	테이블 결정	///////////////////////////////////////////
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
			//	어떤장비인지 결정 ///////////////////////////
			tableidx_ex_1 = SUTIL_GetRandom()%(E_D_RING+1);

			//	성별 결정	////////////////////////////////////////////
			dice = SUTIL_GetRandom()%100;

			tableidx_c = 0;
			while(dice > man_girl_Table[nHeroSex][tableidx_c])
			{
				dice -= man_girl_Table[nHeroSex][tableidx_c];
				tableidx_c++;
			}

			//	판정탬 결정	////////////////////////////////////////////
			dice = SUTIL_GetRandom()%100;

			tableidx_d = 0;
			while(dice > judgment_Table[tableidx_d])
			{
				dice -= judgment_Table[tableidx_d];
				tableidx_d++;
			}

			//	아이템 레벨 결정	////////////////////////////////////////////
			tableidx_e = nMonLevel-5 + (SUTIL_GetRandom()%10);
			if(1 > tableidx_e)	{tableidx_e = 1;}

			//	아이템 등급 결정	////////////////////////////////////////////
			temp = 0;
			while(nMonLevel > drop_level_Table[temp][0])	{temp++;}

			dice = SUTIL_GetRandom()%300;

			tableidx_f = 0;
			while(dice > drop_level_Table[temp][tableidx_f+1])
			{	
				dice -= drop_level_Table[temp][tableidx_f+1];
				tableidx_f++;
			}

			//	소켓의 갯수 결정	/////////////////////////////////////////////
			if(DG_NORMAL < tableidx_f)
			{
				tableidx_g = 0;
				for(loop = 0; loop < 3; loop++)
				{
					if(socket_Table[tableidx_d] < (SUTIL_GetRandom()%100))	{tableidx_g++;}
				}
			}

			//	접두사 붙을 확률	/////////////////////////////////////////////////
			if(hedertext_Table[tableidx_d] < (SUTIL_GetRandom()%100))
			{
				tableidx_h = (SUTIL_GetRandom()%7)+1;		
			}

			//	아이템 인덱스 결정
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

			//	소켓적용
			if(tableidx_g>0){
				tmpBag.Data1 += 1000;
				if(tableidx_g>1){
					tmpBag.Data1 += 100000;
					if(tableidx_g>2){
						tmpBag.Data1 += 10000000;
					}			
				}			
			}			
			tmpBag.Data1 += tableidx_h * 10;			//	아이템의 접두사 포함

			tmpBag.Data1 += (tableidx_f);		//	아이템의 등급 포함
			break;
		}
	}

	return tmpBag;
}


bool PopupUi::GET_item(struct ItemBag* _item)
{
	int StackMAX = 99;


	switch(_item->ITEM_KIND){
		case ITEM_MONEY://인벤 슬롯을 먹지않는 아이템
			Character::s_Status.MONEY+=_item->ITEM_STACK_COUNT;
			if(Character::s_Status.MONEY>999999999)Character::s_Status.MONEY = 999999999;
			AddItemList(*_item);
			return true;

		case ITEM_MAINQUEST://10개 겹치는 아이템
			StackMAX = 10;
		case ITEM_POTION://99개 겹치는아이템
			{



				struct ItemBag _itemTemp = *_item;
				for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 동일한 아이템을 찾아낸다
					switch(Character::s_ItemSlot[xx].Data0){
						case 100:MaxSlot= 8;break;
						case 101:MaxSlot= 16;break;
						case 102:MaxSlot= 24;break;
						case 103:MaxSlot= 32;break;
						default:MaxSlot= 0;break;
					}
					for(int yy = 0;yy<MaxSlot;yy++){
						if(Character::s_ItemBag[xx][yy].ITEM_KIND == _item->ITEM_KIND 
							&& Character::s_ItemBag[xx][yy].ITEM_INDEX == _item->ITEM_INDEX){//동일한 아이템이라면

							int Sum = Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT+_item->ITEM_STACK_COUNT;

							if(Sum<=StackMAX){//아이템 합치기
								Character::s_ItemBag[xx][yy].Data1 = ((Character::s_ItemBag[xx][yy].Data1 / 100) * 100) +Sum;
								AddItemList(_itemTemp);
								return true;
							}else{//아이템 합치고 남는경우
								Character::s_ItemBag[xx][yy].Data1 = ((Character::s_ItemBag[xx][yy].Data1 / 100) * 100) +StackMAX;
								_item->Data1 =((_item->Data1 / 100) * 100) + ((Sum) - StackMAX) ;
							}
						}
					}
				}
				//풀스택을 채우고도 남았을 경우
				for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 빈공간을 찾아낸다
					switch(Character::s_ItemSlot[xx].Data0){
						case 100:MaxSlot= 8;break;
						case 101:MaxSlot= 16;break;
						case 102:MaxSlot= 24;break;
						case 103:MaxSlot= 32;break;
						default:MaxSlot= 0;break;
					}
					for(int yy = 0;yy<MaxSlot;yy++){
						if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//비어있는슬롯이 있으면
							Character::s_ItemBag[xx][yy] = *_item;

							AddItemList(_itemTemp);
							return true;
						}
					}
				}
			}
			break;
		default://겹치지않는아이템

			for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 빈공간을 찾아낸다
				switch(Character::s_ItemSlot[xx].Data0){
					case 100:MaxSlot= 8;break;
					case 101:MaxSlot= 16;break;
					case 102:MaxSlot= 24;break;
					case 103:MaxSlot= 32;break;
					default:MaxSlot= 0;break;
				}
				for(int yy = 0;yy<MaxSlot;yy++){
					if(Character::s_ItemBag[xx][yy].ITEM_KIND == 0){//비어있는슬롯이 있으면
						Character::s_ItemBag[xx][yy] = *_item;

						AddItemList(*_item);
						return true;
					}
				}
			}
			break;
	}
	
	return false;
	
}//아이템을 획득했을때
int PopupUi::GET_Count(int itemID)
{//모든 인벤을 돌면서 동일한 아이템의 갯수를 체크한다
	int counter = 0;
	for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 동일한 아이템을 찾아낸다
		switch(Character::s_ItemSlot[xx].Data0){
				case 100:MaxSlot= 8;break;
				case 101:MaxSlot= 16;break;
				case 102:MaxSlot= 24;break;
				case 103:MaxSlot= 32;break;
				default:MaxSlot= 0;break;
		}
		for(int yy = 0;yy<MaxSlot;yy++){
			if(itemID == Character::s_ItemBag[xx][yy].ITEM_ID){
				if(Character::s_ItemBag[xx][yy].ITEM_KIND >= 10 && Character::s_ItemBag[xx][yy].ITEM_KIND <= 19 ){//장비
					counter++;
				}else{
					counter += Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT;
				}
			}
		}
	}
	return counter;

}//아이템 소지 갯수 체크 할때
int PopupUi::REMOVE_Item(int itemID,int counter)
{//모든 인벤을 돌면서 갯수만큼 아이템을 제거한다
	
	for(int xx = 0,MaxSlot=0;xx<4;xx++){//모든 인벤을 돌면서 동일한 아이템을 찾아낸다
		switch(Character::s_ItemSlot[xx].Data0){
				case 100:MaxSlot= 8;break;
				case 101:MaxSlot= 16;break;
				case 102:MaxSlot= 24;break;
				case 103:MaxSlot= 32;break;
				default:MaxSlot= 0;break;
		}
		for(int yy = 0;yy<MaxSlot;yy++){
			if(itemID == Character::s_ItemBag[xx][yy].ITEM_ID){
				if(Character::s_ItemBag[xx][yy].ITEM_KIND < 10 || Character::s_ItemBag[xx][yy].ITEM_KIND > 19 ){//장비가 아님
					if(Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT){
						if(counter==ALL_DEL){//동일 아이템 전부 삭제
							Character::s_ItemBag[xx][yy].Data0 = 0;
							Character::s_ItemBag[xx][yy].Data1 = 0;
							Character::s_ItemBag[xx][yy].Data2 = 0;
						}else if(counter >= Character::s_ItemBag[xx][yy].ITEM_STACK_COUNT){//없애줄 갯수보다 슬롯의 아이템이 모자랄떄
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
						counter --; // 실질적인 버그상황 아이템의 갯수가 0인 상태이다
						Character::s_ItemBag[xx][yy].Data0 = 0;
						Character::s_ItemBag[xx][yy].Data1 = 0;
						Character::s_ItemBag[xx][yy].Data2 = 0;
					}
					
				}
				//else{
					//장비는 이 메소드로 지울 수 없다
					//같은 아이디라고 해도 다를 수 있다
				//}
			}
		}
	}
	return counter;

}//아이템 소지 갯수 체크 할때

void PopupUi::equipTEXT(int slot,struct ItemBag _item){//선택 아이템에 대한 정보
	//장착 가능한 장비를 착용했을경우 변화하는 능력치를 보여준다



	ItemAbility TempAbil = Character::s_ItemAbil[slot]; 
	ItemBag TempEquip = Character::s_ItemEquip[slot];


	int temp_Amax = Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL];
	int temp_Def  = Character::s_Status.DEFENSE;
	int temp_Cri  = Character::s_Status.CRITICAL;
	int temp_Agi  = Character::s_Status.AVOID;
	int temp_Life = Character::s_Status.LIFE_MAX;
	int temp_Mana = Character::s_Status.MANA_MAX;


	Character::s_ItemEquip[slot] = _item;//임시장착
	Set_Item(&Character::s_ItemAbil[slot],&Character::s_ItemEquip[slot]);
	Character::Set_state_calculate();//변화된 능력치 계산


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


//업 다운 아이콘
	if(temp_Amax < Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL]){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+39,0,0);//UP아이콘
	}else if(temp_Amax > Character::s_Status.ATTACK_MAX[Character::s_Status.ELEMENTAL]){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+39,0,0);//DOWN아이콘
	}
	if(temp_Def  < Character::s_Status.DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+55,0,0);//UP아이콘
	}else if(temp_Def  > Character::s_Status.DEFENSE){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+55,0,0);//DOWN아이콘
	}
	if(temp_Cri  < Character::s_Status.CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS-15,YPOS+71,0,0);//UP아이콘
	}else if(temp_Cri  > Character::s_Status.CRITICAL){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS-15,YPOS+71,0,0);//DOWN아이콘
	}
	if(temp_Agi  < Character::s_Status.AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+39,0,0);//UP아이콘
	}else if(temp_Agi  > Character::s_Status.AVOID){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+39,0,0);//DOWN아이콘
	}
	if(temp_Life < Character::s_Status.LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+55,0,0);//UP아이콘
	}else if(temp_Life > Character::s_Status.LIFE_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+55,0,0);//DOWN아이콘
	}
	if(temp_Mana < Character::s_Status.MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_UP, XPOS+56,YPOS+71,0,0);//UP아이콘
	}else if(temp_Mana > Character::s_Status.MANA_MAX){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_ICON_DOWN, XPOS+56,YPOS+71,0,0);//DOWN아이콘
	}




	Character::s_ItemAbil[slot] = TempAbil;//원상복구
	Character::s_ItemEquip[slot] = TempEquip;//원상복구
	Character::Set_state_calculate();//변화된 능력치 계산


	
}


void PopupUi::Set_Item(struct ItemAbility *_abil,struct ItemBag *_item){//가방 인벤갯수 리턴

	
	int gradePER[5] = {100,110,115,120,130};//등급
	int grade = gradePER[_item->Data1%10];
	int head = 100 + head_Table[(_item->Data1/10)%100][ (_item->ITEM_KIND<ITEM_HEAD? 0:5) ]; //무기냐 방어구냐에따라 옵이바뀐다


//접두사
	_abil->CRI		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 1:6)];
	_abil->AGI		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 2:7)];
	_abil->HP		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 3:8)];
	_abil->MP		= head_Table[(_item->Data1/10)%100][(_item->ITEM_KIND<ITEM_HEAD? 4:9)];


//스크롤
	_abil->STR		= 0; 
	_abil->DEX		= 0;
	_abil->CON		= 0;
	_abil->INT		= 0;

	int scroll_Kind = (_item->Data2/100)%100; //스크롤 종류
	int UP = (((_item->Data2/10000) %1000) /3) +1; //스크롤 상승치

	switch(scroll_Kind){//스크롤 종류
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

	

	switch(_item->ITEM_KIND){//아이템 종류별 분화  
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
	switch(itemID){//특정 아이템은 퀘스트에따라서 보유량이 표시되어야 할 수 도 있음
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
	if(s_ItemList[ITEMLIST_MAX-1].LifeTime>7) s_ItemList[ITEMLIST_MAX-1].LifeTime = 7;//마지막 라인은 일단 사라진다

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

			char str[60];//아이템 텍스트
			_SUTIL->pFont->setColor(s_ItemList[xx].Color);

			switch(s_ItemList[xx].Kind){
				case ITEM_MONEY://골드 라면 골드갯수표시
					SPRINTF(str, "%d %s",
						s_ItemList[xx].Head,
						(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)]); 	
					break;
				case ITEM_POTION://포션의 경우
				case ITEM_MAINQUEST:
					if(s_ItemList[xx].QUEST_max == 0){//퀘스트중인 아이템이 아닐때
						SPRINTF(str, "%s x%d",
							(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
							s_ItemList[xx].Head); 	
					}else{
						if(s_ItemList[xx].QUEST_now < s_ItemList[xx].QUEST_max){//퀘스트 갯수미달
							SPRINTF(str, "%s ^1(%d/%d)^0",
								(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
								s_ItemList[xx].QUEST_now,
								s_ItemList[xx].QUEST_max); 	
						}else{//퀘스트 완료
							SPRINTF(str, "%s ^2(%s)^0",
								(char*)pITEM_Text->nText[itemNAME(s_ItemList[xx].Kind,s_ItemList[xx].Index)],
								(char*)pITEM_Text->nText[ITEM_CLEAR]); 	
						}
					}
					
					break;


				default://장비
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

	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_RESULTS, XPOS, MESSAGE_LOCATE_Y, 0);//메세지 프레임 그리기

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
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_1, XPOS, AREA_LOCATE_Y, 0);//메세지 프레임 그리기
			break;
		case 2:
		case AREA_DELAY-1:
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_2, XPOS, AREA_LOCATE_Y, 0);//메세지 프레임 그리기
			_SUTIL->pFont->setColor(0x888888);
			_SUTIL->pFont->DrawText(_SUTIL->g, s_AreaMessage.str, XPOS, AREA_LOCATE_Y-4, CGraphics::HCENTER);
			
			break;
		default:
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_FIELDNAME_3, XPOS, AREA_LOCATE_Y, 0);//메세지 프레임 그리기
			_SUTIL->pFont->setColor(0xffffff);
			_SUTIL->pFont->DrawText(_SUTIL->g, s_AreaMessage.str, XPOS, AREA_LOCATE_Y-4, CGraphics::HCENTER);
			break;

	}
	_SUTIL->pFont->setOutline(false);


	s_AreaMessage.LifeTime--;
}
































