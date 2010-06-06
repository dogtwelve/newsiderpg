#include "MainMenu.h"


//--------------------------------------------------------------------------
MainMenu::MainMenu()
//--------------------------------------------------------------------------
{
	MAINMENU_PAGE = PAGE_GAMELOFT;//0;
	pCLRPOPUP_Text = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_CLRMENU_TEXT);//텍스트 팩 로드
}


//--------------------------------------------------------------------------
MainMenu::~MainMenu()
//--------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------
void MainMenu::Initialize(int nDummy1, int nDummy2)
//--------------------------------------------------------------------------
{
		_spr_gameloft = SUTIL_LoadSprite(PACK_SPRITE_MAINMENU, SPRITE_MAINMENU_GAMELOFT);
}


//--------------------------------------------------------------------------
void MainMenu::Release()
//--------------------------------------------------------------------------
{
		SUTIL_FreeTextPack(pCLRPOPUP_Text);

		SUTIL_FreeSprite(_spr_gameloft);
		SUTIL_FreeSprite(_spr_title);
		SUTIL_FreeSprite(_spr_MainMenu);
		SUTIL_FreeSprite(_spr_MCselect);
		SUTIL_FreeSprite(_spr_MC_Face);

		SUTIL_FreeSprite(_spr_TalkBox);

		SUTIL_FreeSpriteInstance(_ins_Wing);
		SUTIL_FreeSpriteInstance(_ins_Wing_After);
		SUTIL_FreeSpriteInstance(_ins_Arrow);
		SUTIL_FreeSpriteInstance(_ins_Light);

		SUTIL_FreeSpriteInstance(_ins_faceFront);
		SUTIL_FreeSpriteInstance(_ins_faceBack);
		SUTIL_FreeSpriteInstance(_ins_Pattern);
		SUTIL_FreeSpriteInstance(_ins_Center);
		SUTIL_FreeSpriteInstance(_ins_Right);
		SUTIL_FreeSpriteInstance(_ins_Left);
		SUTIL_FreeSpriteInstance(_ins_SideArrow);
}
//--------------------------------------------------------------------------
void MainMenu::KeyEvent(int m_keyNum, int m_keyRepeat)
//--------------------------------------------------------------------------
{
	if(m_keyRepeat)return ;//키릴리즈에 반응하지않는다.
	int m_keyCode = m_keyNum;
	if(m_keyCode == MH_KEY_4)m_keyCode=MH_KEY_LEFT;		//값대치
	if(m_keyCode == MH_KEY_6)m_keyCode=MH_KEY_RIGHT;	//값대치
	if(m_keyCode == MH_KEY_2)m_keyCode=MH_KEY_UP;		//값대치
	if(m_keyCode == MH_KEY_8)m_keyCode=MH_KEY_DOWN;		//값대치
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//값대치


	switch(MAINMENU_PAGE){
		case PAGE_GO_QUEST:
			{
				switch(m_keyNum)
				{
					case MH_KEY_CLEAR:	{MAINMENU_PAGE=PAGE_MAINMENU;Init_int();	break;}
					case MH_KEY_UP:		{if(GO_QUEST_NOW_Y>0)GO_QUEST_NOW_Y--;		break;}
					case MH_KEY_DOWN:	{if(GO_QUEST_NOW_Y<1)GO_QUEST_NOW_Y++;		break;}
					case MH_KEY_SELECT:
						{//바로가기
							SAVELOAD_sex		= GO_QUEST_SEX;
							//SAVELOAD_MainStyle	= 1;
							GET_MAINQUEST_IDX() = GO_QUEST_NUM;
							int MapNum = 801;
							switch(GO_QUEST_NUM){
								case MAIN_QUEST_findOpen	:MapNum = 202;	break;
								case MAIN_QUEST_openDoor	:MapNum = 201;	break;	
								case MAIN_QUEST_findKail	:MapNum = 801;	break;	
								case MAIN_QUEST_oldMedal	:MapNum = 800;	break;	
								case MAIN_QUEST_callKail	:MapNum = 800;	break;	
								case MAIN_QUEST_goKaien		:MapNum = 800;	break;
								case MAIN_QUEST_goCitizen1	:MapNum = 805;	break;
								case MAIN_QUEST_goCitizen2	:MapNum = 803;	break;
								case MAIN_QUEST_goCitizenK	:MapNum = 805;	break;
								case MAIN_QUEST_findCrystal	:MapNum = 803;	break;
								case MAIN_QUEST_returnKaien	:MapNum = 803;	break;
								case MAIN_QUEST_goScholar	:MapNum = 805;	break;
								case MAIN_QUEST_findDiary	:MapNum = 803;	break;
								case MAIN_QUEST_goSmallTown	:MapNum = 203;	break;
								case MAIN_QUEST_findSiz1	:MapNum = 0;	break;	
								case MAIN_QUEST_findSiz2	:MapNum = 0;	break;	
							}
							AppMain::ResvNextState(MS_GAME_FIELD, MapNum, 0);

						}
						break;
				}

				if(GO_QUEST_NOW_Y==0){
					switch(m_keyNum)
					{
					case MH_KEY_LEFT :  {if(GO_QUEST_NUM>0)GO_QUEST_NUM--;	break;}		
					case MH_KEY_RIGHT:	{GO_QUEST_NUM++;					break;}
					case MH_KEY_0:		{GO_QUEST_NUM=GO_QUEST_NUM*10+0;	break;}
					case MH_KEY_1:		{GO_QUEST_NUM=GO_QUEST_NUM*10+1;	break;}
					case MH_KEY_2:		{GO_QUEST_NUM=GO_QUEST_NUM*10+2;	break;}
					case MH_KEY_3:		{GO_QUEST_NUM=GO_QUEST_NUM*10+3;	break;}
					case MH_KEY_4:		{GO_QUEST_NUM=GO_QUEST_NUM*10+4;	break;}
					case MH_KEY_5:		{GO_QUEST_NUM=GO_QUEST_NUM*10+5;	break;}
					case MH_KEY_6:		{GO_QUEST_NUM=GO_QUEST_NUM*10+6;	break;}
					case MH_KEY_7:		{GO_QUEST_NUM=GO_QUEST_NUM*10+7;	break;}
					case MH_KEY_8:		{GO_QUEST_NUM=GO_QUEST_NUM*10+8;	break;}
					case MH_KEY_9:		{GO_QUEST_NUM=GO_QUEST_NUM*10+9;	break;}
					}
					if(GO_QUEST_NUM>MAIN_QUEST_goSmallTown){GO_QUEST_NUM = MAIN_QUEST_goSmallTown;}
				}else if(GO_QUEST_NOW_Y==1){
					switch(m_keyNum)
					{
					case MH_KEY_LEFT :		
					case MH_KEY_RIGHT:		
						{GO_QUEST_SEX= (!GO_QUEST_SEX);break;}
					}
				}

				break;
			}


		case PAGE_SOUNDONOFF:
			switch(m_keyCode)
			{
			case MH_KEY_SELECT:	{if(MAINMENU_ANI){MAINMENU_PAGE=PAGE_TITLE;Init_int();}break;}
			case MH_KEY_LEFT:	{SOUNDONOFF_SELECT = 0;SOUNDONOFF_TARGET_X=-115;break;}
			case MH_KEY_RIGHT:	{SOUNDONOFF_SELECT = 1;SOUNDONOFF_TARGET_X=+3;break;}
			}
			break;

		case PAGE_TITLE:
			{
				if(m_keyCode){
					MAINMENU_PAGE=PAGE_MAINMENU_INTRO;
					_spr_MainMenu->SetBlendCustom(false,false,0,0);
					MAINMENU_ANI = 0;
				}
			}
			break;

		case PAGE_MAINMENU:
			//------------------------------------------------------------
			{
				if(MAINMENU_WING_STATE != 0){return;}
				switch(m_keyCode)
				{

				case MH_KEY_SOFT1:
					{//바로가기
						SAVELOAD_sex	= 0;//여자
						//SAVELOAD_MainStyle	= 0;
						//GET_MAINQUEST_IDX() = MAIN_QUEST_openDoor;
						AppMain::ResvNextState(MS_GAME_FIELD, 400, 0);
					
					}
					break;

				case MH_KEY_SEND:	{Init_int();MAINMENU_PAGE = PAGE_GO_QUEST;GO_QUEST_SEX=0;break;}

				case MH_KEY_SELECT:	{Init_int();MAINMENU_PAGE = PAGE_SELECT_SEX;SELECT_SEX_ACTION_START=true; _spr_title->workPal(true,0,-20);break;}
				case MH_KEY_UP:		{MAINMENU_WING_STATE=1;_ins_Wing->SetAnim(ANIM_MAINMENU_ROTATEUP);			break;}
				case MH_KEY_DOWN:	{MAINMENU_WING_STATE=2;_ins_Wing->SetAnim(ANIM_MAINMENU_ROTATEDOWN);		break;}
				}

				break;
			}
		case PAGE_SELECT_SEX:
			{
				if(MAINMENU_ANI<10)return;
				switch(m_keyCode)
				{ 
				case MH_KEY_SELECT:	{Init_int();MAINMENU_PAGE = PAGE_SELECT_STYLE;SELECT_STYLE_ACTION_START=true;SELECT_STYLE_SELECT=1;break;}
				case MH_KEY_CLEAR:	{Init_int();MAINMENU_PAGE = PAGE_MAINMENU; _spr_title->workPal(false,0,0);break;}
				case MH_KEY_LEFT:	{SELECT_SEX_SELECT=(SELECT_SEX_SELECT+1)%2;SELECT_SEX_ACTION_START=true;break;}
				case MH_KEY_RIGHT:	{SELECT_SEX_SELECT=(SELECT_SEX_SELECT+1)%2;SELECT_SEX_ACTION_START=true;break;}
				}
			}
			break;
		case PAGE_SELECT_STYLE:
			{
				if(MAINMENU_ANI<10)return;
				switch(m_keyCode)
				{
				case MH_KEY_SELECT:	{Init_int();MAINMENU_PAGE = PAGE_SELECT_SLOT;break;}
				case MH_KEY_CLEAR:	{Init_int();MAINMENU_PAGE = PAGE_SELECT_SEX;SELECT_SEX_SELECT=s_NC.Sex;break;}
				case MH_KEY_LEFT:	{SELECT_STYLE_ACTION_START=true;SELECT_STYLE_ACTION_RIGHT=false;break;}
				case MH_KEY_RIGHT:	{SELECT_STYLE_ACTION_START=true;SELECT_STYLE_ACTION_RIGHT=true;break;}
				}
			}
			break;
		case PAGE_SELECT_SLOT:
			{
				if(MAINMENU_ANI<10)return;
				switch(m_keyCode)
				{
				case MH_KEY_SELECT:	
					{

						SAVELOAD_Slot	= s_NC.Slot;
						SAVELOAD_sex	= s_NC.Sex;
						//SAVELOAD_MainStyle	= s_NC.Style;

					Init_int();
					SET_EVENT(1);
					AppMain::ResvNextState(MS_GAME_FIELD, 100, 0);
					break;
									
					}
				case MH_KEY_CLEAR:	{Init_int();MAINMENU_PAGE = PAGE_SELECT_STYLE;break;}
				case MH_KEY_UP:		{SELECT_SLOT_SELECT=(SELECT_SLOT_SELECT+2)%3;break;}
				case MH_KEY_DOWN:	{SELECT_SLOT_SELECT=(SELECT_SLOT_SELECT+1)%3;break;}
				}
			}
			break;


	}
}
//--------------------------------------------------------------------------
void MainMenu::Process()
//--------------------------------------------------------------------------
{
	switch(MAINMENU_PAGE){
		case PAGE_MAINMENU:
			{
				if(MAINMENU_ACTION_END){
					MAINMENU_ACTION_END = 0;
					_ins_Wing->SetFrame(FRAME_MAINMENU_ROTATE_NORMAL);
					_ins_Wing_After->SetAnim(ANIM_MAINMENU_ROTATE_AFTER);

					switch(MAINMENU_WING_STATE){
						case 1://UP
							for(int xx = 1;xx< MAX_LINE;xx++){//모듈 교체
								_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_MENU_00,xx+MODULE_MAINMENU_MENU_00);
							}
							MAINMENU_NOW++;
							break;
						case 2://DOWN
							for(int xx = MAX_LINE-1;xx>0;xx--){//모듈 교체
								_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_MENU_00,xx+MODULE_MAINMENU_MENU_00);
							}
							MAINMENU_NOW--;
							break;
					}
					MAINMENU_NOW = (MAINMENU_NOW+MAX_LINE)%MAX_LINE;//오버플로방지

					MAINMENU_WING_STATE = 0;
				}
				


				if(MAINMENU_WING_STATE){
					MAINMENU_ACTION_END = !_ins_Wing->UpdateSpriteAnim();
				}
				_ins_Arrow->UpdateSpriteAnim();//케릭터 에니메이션 업데이트 실행
				_ins_Light->UpdateSpriteAnim();//케릭터 에니메이션 업데이트 실행
				_ins_Wing_After->UpdateSpriteAnim();//케릭터 에니메이션 업데이트 실행
			}
			break;
		case PAGE_SELECT_SEX: 
			if(SELECT_SEX_ACTION_START){
				SELECT_SEX_ACTION_START = false;
				if(SELECT_SEX_SELECT==0){//남자면
					s_NC.Sex = 0;
					_ins_faceFront->SetAnim(ANIM_MCSELECT_FACE_A_MAN_SELECT);
					_ins_faceBack->SetFrame(FRAME_MCSELECT_FACE_WOMAN_UNSELECT);
				}else{//여자면
					s_NC.Sex = 1;
					_ins_faceFront->SetAnim(ANIM_MCSELECT_FACE_A_WOMAN_SELECT);
					_ins_faceBack->SetFrame(FRAME_MCSELECT_FACE_MAN_UNSELECT);
				}
			}

			_ins_faceFront->UpdateSpriteAnim();
			break;
		case PAGE_SELECT_STYLE:

			SELECT_STYLE_ACTION_COUNT++;

			if(SELECT_STYLE_ACTION_START){
				SELECT_STYLE_ACTION_START = false;
				SELECT_STYLE_ACTION_COUNT = 0;
				switch(SELECT_STYLE_SELECT){
					case 0://검사
						if(SELECT_STYLE_ACTION_RIGHT){
							SELECT_STYLE_SELECT=s_NC.Style = 1;//건너
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_LEFT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_LEFT_01);
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_LEFT_02);
						}else{
							SELECT_STYLE_SELECT=s_NC.Style = 2;//위져드
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_RIGHT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_RIGHT_01);
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_RIGHT_02);
						}
						
						break;
					case 2://위져드
						if(SELECT_STYLE_ACTION_RIGHT){
							SELECT_STYLE_SELECT=s_NC.Style = 0;//검사
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_LEFT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_LEFT_01);
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_LEFT_02);
						}else{
							SELECT_STYLE_SELECT=s_NC.Style = 1;//건너
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_RIGHT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_RIGHT_01);
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_RIGHT_02);
						}

						break;
					case 1://건너
						if(SELECT_STYLE_ACTION_RIGHT){
							SELECT_STYLE_SELECT=s_NC.Style = 2;//위져드
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_LEFT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_LEFT_01);
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_LEFT_02);
						}else{
							SELECT_STYLE_SELECT=s_NC.Style = 0;//검사
							_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_RIGHT);
							_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_RIGHT_01);
							_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_RIGHT_02);
						}

						break;
				}
			}

			if(SELECT_STYLE_ACTION_COUNT==5){
				switch(SELECT_STYLE_SELECT){
					case 0://검사
						_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S);
						_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_01);
						_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_S_02);
						break;
					case 2://위져드
						_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O);
						_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_01);
						_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_O_02);
						break;
					case 1://건너
						_ins_Left->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G);
						_ins_Right->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_01);
						_ins_Center->SetAnim((s_NC.Sex*27)+ANIM_MCSELECT_A_MAN_G_02);
						break;
				}
			}	
			
			

			_ins_Pattern->UpdateSpriteAnim();
			_ins_Right->UpdateSpriteAnim();
			_ins_Left->UpdateSpriteAnim();
			_ins_Center->UpdateSpriteAnim();

			_ins_SideArrow->UpdateSpriteAnim();
			break;
		case PAGE_SELECT_SLOT:
			int target = 0;
			switch(SELECT_SLOT_SELECT){
				case 0://0번 슬롯-30
					target = -30;
					SELECT_SLOT_NOW_Y = target+(SELECT_SLOT_NOW_Y-target)/2;
					break;
				case 1://1번 슬롯
					target = 0;
					SELECT_SLOT_NOW_Y = target+(SELECT_SLOT_NOW_Y-target)/2;
					break;
				case 2://2번 슬롯+30
					target = 30;
					SELECT_SLOT_NOW_Y = target+(SELECT_SLOT_NOW_Y-target)/2;
					break;
			}
			break;


	}
}

//--------------------------------------------------------------------------
void MainMenu::Paint()
//--------------------------------------------------------------------------
{

	switch(MAINMENU_PAGE){
		case PAGE_GO_QUEST:
			{
				int YY = YPOS-50;

				SUTIL_SetColor(0x000000);
				SUTIL_FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				SUTIL_SetColor(0x222222);
				SUTIL_FillRect(0,YY-10+ 40*GO_QUEST_NOW_Y,SCREEN_WIDTH,40);  


				
				_SUTIL->pFont->setColor(0xFFFFFF);
				_SUTIL->pFont->setOutline(true);
				_SUTIL->pFont->setOutlineColor(0x550000);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"Choice MainQuest Number", XPOS, YY, CGraphics::HCENTER);//메인퀘스트 넘버고르기
				_SUTIL->pFont->setOutlineColor(0x000000);
				_SUTIL->pFont->DrawText(_SUTIL->g, GO_QUEST_NUM , XPOS-25, YY+=15, CGraphics::HCENTER);//메인퀘스트 넘버
				switch(GO_QUEST_NUM){
					case MAIN_QUEST_findOpen	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findOpen", 5);		break;
					case MAIN_QUEST_openDoor	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"openDoor", 5);		break;	
					case MAIN_QUEST_findKail	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findKail", 5);		break;	
					case MAIN_QUEST_oldMedal	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"oldMedal", 5);		break;	
					case MAIN_QUEST_callKail	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"callKail", 5);		break;	
					case MAIN_QUEST_goKaien		:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goKaien", 5);		break;
					case MAIN_QUEST_goCitizen1	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goCitizen1", 5);	break;
					case MAIN_QUEST_goCitizen2	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goCitizen2", 5);	break;
					case MAIN_QUEST_goCitizenK	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goCitizenK", 5);	break;
					case MAIN_QUEST_findCrystal	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findCrystal", 5);	break;
					case MAIN_QUEST_returnKaien	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"returnKaien", 5);	break;
					case MAIN_QUEST_goScholar	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goScholar", 5);		break;
					case MAIN_QUEST_findDiary	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findDiary", 5);		break;
					case MAIN_QUEST_goSmallTown	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"goSmallTown", 5);	break;
					case MAIN_QUEST_findSiz1	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findSiz1", 5);		break;	
					case MAIN_QUEST_findSiz2	:_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"findSiz2", 5);		break;	
				}

				_SUTIL->pFont->setOutlineColor(0x550000);
				_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"Choice MALE or FEMALE", XPOS, YY+=25, CGraphics::HCENTER);//메인퀘스트 넘버고르기
				_SUTIL->pFont->setOutlineColor(0x000000);
				if(GO_QUEST_SEX){
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"FEMALE" , XPOS, YY+=15, CGraphics::HCENTER);
				}else{
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"MALE" , XPOS, YY+=15, CGraphics::HCENTER);
				}

				break;
			}
			
		case PAGE_GAMELOFT:
			{
				MAINMENU_ANI++;
				

				SUTIL_SetColor(0xFFFFFF);
				SUTIL_FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				SUTIL_Paint_Frame(_spr_gameloft,FRAME_GAMELOFT_LOGO,XPOS,YPOS,0);
				
				if(MAINMENU_ANI>20){
					MAINMENU_PAGE=PAGE_2558NATE;
					Init_int();
				}
				break;
			}
		case PAGE_2558NATE:
			{

				if(MAINMENU_ANI==0)SUTIL_Init_Ani(_spr_gameloft);
				MAINMENU_ANI++;

				

				if(MAINMENU_ANI<12){
					SUTIL_SetColor(0xFFFFFF);
					SUTIL_FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
					SUTIL_Paint_Ani(_spr_gameloft,ANIM_GAMELOFT_NATE,XPOS,YPOS,0);
				}
				
				if(MAINMENU_ANI>20){
					MAINMENU_PAGE=PAGE_SOUNDONOFF;
					Init_int();
					SOUNDONOFF_NOW_X=-115;
					SOUNDONOFF_TARGET_X=-115;
				}
				break;
			}
		case PAGE_SOUNDONOFF:
			{
				if(MAINMENU_ANI==0){//실제 메인에뉴에서 사용될 이미지를 딜레이 타임동안에 로드한다.
					MAINMENU_ANI++;
					SUTIL_FreeSprite(_spr_gameloft)
					_spr_title = SUTIL_LoadSprite(PACK_SPRITE_MAINMENU, SPRITE_MAINMENU_TITLE);
					_spr_MainMenu = SUTIL_LoadSprite(PACK_SPRITE_MAINMENU, SPRITE_MAINMENU_MAINMENU);
					_spr_TalkBox = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_TALK_UI);//대사창
					_spr_MainMenu->SetBlendFrame(FRAME_MAINMENU_BLEND);
					_spr_TalkBox->SetBlendFrame(FRAME_TALKBOX_BLEND);

					_spr_MCselect = SUTIL_LoadSprite(PACK_SPRITE_MAINMENU, SPRITE_MAINMENU_MCSELECT);
					_spr_MC_Face = SUTIL_LoadSprite(PACK_SPRITE_MAINMENU, SPRITE_MAINMENU_MC_FACE);
					_spr_MCselect->SetBlendFrame(FRAME_MCSELECT_BLEND);


					_ins_Wing		= GL_NEW ASpriteInstance(_spr_MainMenu, XPOS, YPOS, NULL);//가운데 돌아가는 애니
					_ins_Wing_After = GL_NEW ASpriteInstance(_spr_MainMenu, XPOS, YPOS, NULL);//가운데 돌아가는 애니
					_ins_Arrow		= GL_NEW ASpriteInstance(_spr_MainMenu, XPOS, YPOS, NULL);//가운데 돌아가는 애니
					_ins_Light		= GL_NEW ASpriteInstance(_spr_MainMenu, XPOS, YPOS, NULL);//가운데 불꽃 애니

					_ins_faceFront		= GL_NEW ASpriteInstance(_spr_MC_Face, XPOS, YPOS, NULL);//남자일러스트
					_ins_faceBack		= GL_NEW ASpriteInstance(_spr_MC_Face, XPOS, YPOS, NULL);//여자 일러스트
					_ins_Pattern		= GL_NEW ASpriteInstance(_spr_MCselect, XPOS, YPOS, NULL);//장판
					_ins_Center		= GL_NEW ASpriteInstance(_spr_MCselect, XPOS, YPOS, NULL);//가운데 케릭터
					_ins_Right		= GL_NEW ASpriteInstance(_spr_MCselect, XPOS, YPOS, NULL);//오른쪽 케릭터
					_ins_Left		= GL_NEW ASpriteInstance(_spr_MCselect, XPOS, YPOS, NULL);//왼쪽 케릭터
					_ins_SideArrow		= GL_NEW ASpriteInstance(_spr_MCselect, XPOS, YPOS, NULL);//화살표



					_ins_Wing->SetFrame(FRAME_MAINMENU_ROTATE_NORMAL);
					_ins_Arrow->SetAnim(ANIM_MAINMENU_TRIANGLE);
					_ins_Light->SetAnim(ANIM_MAINMENU_BLUELIGHT);

					_ins_Wing->SetAniLoop(false);
					_ins_Arrow->SetAniLoop(true);
					_ins_Light->SetAniLoop(true);
					_ins_Wing_After->SetAniLoop(false);



					_ins_Pattern->SetAnim(ANIM_MCSELECT_A_MAGICCIRCLE);

					_ins_SideArrow->SetAnim(ANIM_MCSELECT_A_ARROW);

					_ins_faceFront->SetAniLoop(false);
					_ins_faceBack->SetAniLoop(true);
					_ins_Pattern->SetAniLoop(true);
					_ins_Left->SetAniLoop(true);
					_ins_Right->SetAniLoop(true);		
					_ins_Center->SetAniLoop(true);	
					_ins_SideArrow->SetAniLoop(true);	


					_ins_faceFront->SetAniMoveLock(true);
					_ins_faceBack->SetAniMoveLock(true);
					_ins_Pattern->SetAniMoveLock(true);
					_ins_Left->SetAniMoveLock(true);
					_ins_Right->SetAniMoveLock(true);		
					_ins_Center->SetAniMoveLock(true);	
					_ins_SideArrow->SetAniMoveLock(true);



					//세이브 파일을 로드해서 사운드가 꺼져있지않다면 다음으로 넘어간다

				}else{
					SUTIL_Paint_Frame(_spr_title,FRAME_TITLE_TITLEBACK,XPOS,127,0);
					SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_UI_SOUNDSELECT,XPOS,YPOS,0);

					SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_CURSOR_SAVESLOT_NORMAL,XPOS+SOUNDONOFF_NOW_X,YPOS+30,0);
					SOUNDONOFF_NOW_X = SOUNDONOFF_TARGET_X+(SOUNDONOFF_NOW_X-SOUNDONOFF_TARGET_X)/2;

					_SUTIL->pFont->setColor(0xFFFFFF);
					_SUTIL->pFont->setOutline(true);
					_SUTIL->pFont->setOutlineColor(0x000000);
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_Q0], XPOS, YPOS-23, CGraphics::HCENTER);//소리를 켜시겠습니까?
					_SUTIL->pFont->setColor((SOUNDONOFF_SELECT?0x777777:0xFFFFFF));
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-60, YPOS+26, CGraphics::HCENTER);//예
					_SUTIL->pFont->setColor((SOUNDONOFF_SELECT?0xFFFFFF:0x777777));
					_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+60, YPOS+26, CGraphics::HCENTER);//아니오

				 
				}
				break;
			}
		case PAGE_TITLE:
			{
				MAINMENU_ANI+=2;

				SUTIL_Paint_Frame(_spr_title,FRAME_TITLE_TITLEBACK,XPOS,127,0);

				int ani_Num = MAINMENU_ANI%62;

				if(ani_Num < 32){
					_spr_MainMenu->SetBlendCustom(true,true,1,MAINMENU_ANI%62);
				}else{
					_spr_MainMenu->SetBlendCustom(true,true,1,62 - MAINMENU_ANI%62);
				}
				
				SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_PRESS,XPOS,SCREEN_HEIGHT,0);
				//SUTIL_Paint_Ani(_spr_MainMenu,ANIM_MAINMENU_A_PRESSANYKEYS,XPOS,SCREEN_HEIGHT,0,true);
				break;
			}
		case PAGE_MAINMENU_INTRO:
			{
				if(MAINMENU_ANI==0)SUTIL_Init_Ani(_spr_MainMenu);
				MAINMENU_ANI++;

				SUTIL_Paint_Frame(_spr_title,FRAME_TITLE_TITLEBACK,XPOS,127,0);
				SUTIL_Paint_Ani(_spr_MainMenu,ANIM_MAINMENU_INTRO_START,XPOS,YPOS,0);

				if(MAINMENU_ANI>6){
					MAINMENU_PAGE=PAGE_MAINMENU;
					MAINMENU_ANI=0;

					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_00,MODULE_MAINMENU_MENU_00);
					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_01,MODULE_MAINMENU_MENU_01);
					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_02,MODULE_MAINMENU_MENU_02);
					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_03,MODULE_MAINMENU_MENU_03);
					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_04,MODULE_MAINMENU_MENU_04);
					_spr_MainMenu->ModuleExchange(MODULE_MAINMENU_POINT_05,MODULE_MAINMENU_MENU_05);
				}								 
				break;
			}
		case PAGE_MAINMENU:
			{

				SUTIL_Paint_Frame(_spr_title,FRAME_TITLE_TITLEBACK,XPOS,127,0);
		  		SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_INTRO6_END,XPOS,YPOS,0);
 
				SUTIL_PaintAsprite(_ins_Arrow,S_NOT_INCLUDE_SORT);
				SUTIL_PaintAsprite(_ins_Wing,S_NOT_INCLUDE_SORT);
				SUTIL_PaintAsprite(_ins_Light,S_NOT_INCLUDE_SORT);

				if(MAINMENU_WING_STATE == 0){
					SUTIL_PaintAsprite(_ins_Wing_After,S_NOT_INCLUDE_SORT);
 					SUTIL_Paint_Module(_spr_MainMenu,MODULE_MAINMENU_BACK_00+MAINMENU_NOW,XPOS-24,YPOS-5,0,0);
				}


				break;
			}
		case PAGE_SELECT_SEX:
		case PAGE_SELECT_STYLE:
		case PAGE_SELECT_SLOT:
			{
				MAINMENU_ANI++;
				if(MAINMENU_ANI<7){ 
					if(MAINMENU_ANI==6){
						_SUTIL->g->SetColor(0x000000);
						_SUTIL->g->FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
					}else{
						_SUTIL->g->blandBlur(); 
					}
					break;
				}

				SUTIL_Paint_Frame(_spr_title,FRAME_TITLE_TITLEBACK,XPOS,127,0);
				SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_SUB_NAME,XPOS,0,0);
				SUTIL_Paint_Module(_spr_MainMenu,MODULE_MAINMENU_M_TAB + MAINMENU_PAGE - PAGE_SELECT_SEX + 4,XPOS,8,0,CGraphics::HCENTER | CGraphics::TOP);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				switch(MAINMENU_PAGE){
					case PAGE_SELECT_SEX:
						{
							_spr_MC_Face->workPal(true,0,-15);
							SUTIL_PaintAsprite(_ins_faceBack,S_NOT_INCLUDE_SORT);
							_spr_MC_Face->workPal(false,0,0);
							
							
							SUTIL_PaintAsprite(_ins_faceFront,S_NOT_INCLUDE_SORT);


							SUTIL_Paint_Frame(_spr_TalkBox ,FRAME_TALKBOX_SELECT_BOX, XPOS, SCREEN_HEIGHT, 0);//텍스트 영역

							int text_Num = CLRMENU_MAINMENU_NAMEM+SELECT_SEX_SELECT;
							_SUTIL->pFont->Dry_StartLine_Max(0,1);//이름
							_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[text_Num], 40, SCREEN_HEIGHT-61, CGraphics::HCENTER);
							_SUTIL->pFont->setColor(0xFFFFFF);
							_SUTIL->pFont->Dry_Wrap_Width(200);
							_SUTIL->pFont->Dry_StartLine_Max(1,2);
							_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[text_Num], 20, SCREEN_HEIGHT-44, 0);
						}
						break;

					case PAGE_SELECT_STYLE: 
						{
							
							SUTIL_PaintAsprite(_ins_Pattern,S_NOT_INCLUDE_SORT);  

							_spr_MCselect->workPal(true,0,-15);
							SUTIL_PaintAsprite(_ins_Right,S_NOT_INCLUDE_SORT); 
							SUTIL_PaintAsprite(_ins_Left,S_NOT_INCLUDE_SORT);
							_spr_MCselect->workPal(false,0,0);
							SUTIL_PaintAsprite(_ins_Center,S_NOT_INCLUDE_SORT);

							SUTIL_PaintAsprite(_ins_SideArrow,S_NOT_INCLUDE_SORT);

							SUTIL_Paint_Frame(_spr_MC_Face,(s_NC.Sex==0?FRAME_MCSELECT_FACE_MAN_SELECTED:FRAME_MCSELECT_FACE_WOMAN_SELECTED),XPOS,SCREEN_HEIGHT,0);

							SUTIL_Paint_Frame(_spr_TalkBox ,FRAME_TALKBOX_SELECT_BOX, XPOS, SCREEN_HEIGHT, 0);//텍스트 영역

							int text_Num = CLRMENU_MAINMENU_TYPE1+SELECT_STYLE_SELECT;
							_SUTIL->pFont->Dry_StartLine_Max(0,1);//이름
							_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[text_Num], 40, SCREEN_HEIGHT-61, CGraphics::HCENTER);
							_SUTIL->pFont->setColor(0xFFFFFF);
							_SUTIL->pFont->Dry_Wrap_Width(200);
							_SUTIL->pFont->Dry_StartLine_Max(1,2);
							_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[text_Num], 20, SCREEN_HEIGHT-44, 0);
						}
						break;

					case PAGE_SELECT_SLOT:
						{
							SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_UI_SAVESLOT,XPOS,YPOS,0);
							SUTIL_Paint_Frame(_spr_MC_Face,(s_NC.Sex==0?FRAME_MCSELECT_FACE_MAN_SELECTED:FRAME_MCSELECT_FACE_WOMAN_SELECTED),XPOS,SCREEN_HEIGHT,0);



							SUTIL_Paint_Frame(_spr_MainMenu,FRAME_MAINMENU_CURSOR_SAVESLOT_NORMAL,XPOS,YPOS+SELECT_SLOT_NOW_Y,0);

							_SUTIL->pFont->setOutline(true);
							_SUTIL->pFont->setOutlineColor(0x000000);

							for(int xx = 0;xx<3;xx++){
								if(SELECT_SLOT_SELECT==xx){
									_SUTIL->pFont->setColor(0xFFFFFF);
								}else{
									_SUTIL->pFont->setColor(0x777777);
								}
								_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pCLRPOPUP_Text->nText[CLRMENU_MAINMENU6], XPOS+55, YPOS-34+xx*30, CGraphics::HCENTER);//소리를 켜시겠습니까?

							}

							SUTIL_Paint_Frame(_spr_TalkBox ,FRAME_TALKBOX_SELECT_BOX, XPOS, SCREEN_HEIGHT, 0);//텍스트 영역
						}
						break;
				}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				SUTIL_Paint_Frame(_spr_MainMenu ,FRAME_MAINMENU_SUB_OKSELECT, XPOS, SCREEN_HEIGHT, 0);

				if(MAINMENU_ANI<10){
					for(int xx = 0;xx<10-MAINMENU_ANI;xx++){ 
						_SUTIL->g->blandBlur();
					}
				}
				break;
			}
			
	}
}




void MainMenu::Init_int()
//--------------------------------------------------------------------------
{
	s_Page.Focus = 0;
	s_Page.Ly1_sel = 0;
	s_Page.Ly2_sel = 0;
	s_Page.Ly3_sel = 0;
	s_Page.Ly4_sel = 0;
	s_Page.Ly5_sel = 0;
}
