#include "FieldUi.h"

//--------------------------------------------------------------------------
FieldUi::FieldUi(void* s__ASpriteSet)
//--------------------------------------------------------------------------
{

	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // 그림자,효과 이펙트 스프라이트의 포인터

	m_pFieldEftAsIns = GL_NEW ASpriteInstance(s_ASpriteSet->pDebuffAs, 0, 0, NULL);
	m_pFieldUiAsIns = GL_NEW ASpriteInstance(s_ASpriteSet->pFieldUiAs, 0, 0, NULL);

	m_pFieldUiDamageNumAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_DAMAGE_NUM_UI);
	m_pFieldUiDamageNumAs->SetBlendFrame(FRAME_DAMAGE_NUM_BLEND);
	m_pFieldUiDamageNumAsIns = GL_NEW ASpriteInstance(m_pFieldUiDamageNumAs, 0, 0, NULL);// 0번째 배열, 실사용시는 define 필요

	s_TalkBox._spr_TalkBox = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_TALK_UI);//대사창
	s_TalkBox._spr_TalkBox->SetBlendFrame(FRAME_TALKBOX_BLEND);

	pEftList = GL_NEW List2<SKILL_EFT*>();
	pMonEftList = GL_NEW List2<MON_VIEW_UI*>();
	pDamageNumList = GL_NEW List2<DAMAGE_NUM_EFT*>();
	m_nMonEftCurIdx = 0;

	pMonNameText = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_MON_TEXT);
	pTalkNameText = _SUTIL->LoadTextPack(PACK_DATA_TALK, DATA_TALK_FACE_NAME);//대화창을 사용하는 케릭터의 이름을 표현한다
	pTalkNpcNameText = _SUTIL->LoadTextPack(PACK_DATA_TALK, DATA_TALK_NPC_NAME);//NPC의 이름과 고유 넘버를 
}


////--------------------------------------------------------------------------
//FieldUi::FieldUi(ASpriteInstance* _pFieldAsIns)
////--------------------------------------------------------------------------
//{
//
//}


//--------------------------------------------------------------------------
FieldUi::~FieldUi()
//--------------------------------------------------------------------------
{

	SUTIL_FreeSprite(s_TalkBox._spr_TalkBox);
	SUTIL_FreeSprite(s_TalkBox.FaceNowAs);
	SUTIL_FreeSprite(s_TalkBox.FaceNextAs);
	SUTIL_FreeTextPack(s_TalkBox.pText);//대사



	SUTIL_FreeSpriteInstance(m_pFieldUiAsIns);

//	/*SUTIL_FreeSprite*/SAFE_DELETE(m_pFieldEftAs);
//	/*SUTIL_FreeSpriteInstance*/SAFE_DELETE(m_pFieldEftAsIns);

	SUTIL_FreeSprite(m_pFieldUiDamageNumAs);
	
	SUTIL_FreeSpriteInstance(m_pFieldUiDamageNumAsIns);



	MoveHead(pEftList);
	MoveNext(pEftList);
	while(NotEndList(pEftList))
	{
		SUTIL_FreeSpriteInstance(GetData(pEftList)->pSkillEftAsIns);
		SAFE_DELETE(GetData(pEftList));
		pEftList->Delete();
		//continue;
		//MoveNext(pEftList);
	}
	SAFE_DELETE(pEftList);

	//	monster eft ui
	MoveHead(pMonEftList);
	MoveNext(pMonEftList);
	while(NotEndList(pMonEftList))
	{
//		/*SUTIL_FreeSpriteInstance*/SAFE_DELETE(GetData(pEftList)->pSkillEftAsIns);
		SAFE_DELETE(GetData(pMonEftList));
		pMonEftList->Delete();
		//continue;
//		MoveNext(pMonEftList);
	}
	SAFE_DELETE(pMonEftList);

	//	damageNum
	MoveHead(pDamageNumList);
	MoveNext(pDamageNumList);
	while(NotEndList(pDamageNumList))
	{
		SAFE_DELETE(GetData(pDamageNumList));
		pDamageNumList->Delete();
		//continue;
//		MoveNext(pDamageNumList);
	}
	SAFE_DELETE(pDamageNumList);

	SUTIL_FreeTextPack(pMonNameText);
}


//--------------------------------------------------------------------------
void FieldUi::Paint()
//--------------------------------------------------------------------------
{
	//	switch(nState)
	//	{
	//		case 0:
	//		//------------------------------------------------------------
	//		{
	//					
	//			break;
	//		}
	//	}

	//목업
	//PaintCharInfo();
	//PaintMonsterInfo();
	//PaintSkillInfo();
	//PaintExpInfo();

	MoveHead(pEftList);
	MoveNext(pEftList);
	while(NotEndList(pEftList))
	{
		SUTIL_PaintAsprite(GetData(pEftList)->pSkillEftAsIns,S_NOT_INCLUDE_SORT);
		MoveNext(pEftList);
	}

	int tempIdx = 0;
	MoveHead(pMonEftList);
	MoveNext(pMonEftList);
	while(NotEndList(pMonEftList))
	{
		tempIdx++;
		if(m_nMonEftCurIdx <= tempIdx)		{break;}
		MoveNext(pMonEftList);
	}

	if(0 < tempIdx)
	{
		PaintMonsterInfo(GetData(pMonEftList)->name, GetData(pMonEftList)->level,
							GetData(pMonEftList)->nowHp, GetData(pMonEftList)->maxHp,
							GetData(pMonEftList)->elemental);
	}

	int off = 0;// off가 현재 애니메이션 프레임 인덱스
	int addx = 0;// addx 가 에니메이션 x 좌표
	int addy = 0;// addy 가 에니메이션 y 좌표
	int frame_Start = 0;//가 현재 프레임 모듈 인덱스
	int m_Num = 0;//모듈번호

	MoveHead(pDamageNumList);
	MoveNext(pDamageNumList);
	while(NotEndList(pDamageNumList))
	{
		
		
		
		off = (m_pFieldUiDamageNumAsIns->m_sprite->_anims_af_start[GetData(pDamageNumList)->start_ImgIndex] + (7-GetData(pDamageNumList)->lifeTime)) * 5;
		addx =  m_pFieldUiDamageNumAsIns->m_sprite->_aframes[off + 2];
		addy =  m_pFieldUiDamageNumAsIns->m_sprite->_aframes[off + 3];
		frame_Start = (m_pFieldUiDamageNumAsIns->m_sprite->_frames_fm_start[m_pFieldUiDamageNumAsIns->m_sprite->_aframes[off + 0]] << 2);
		m_Num = m_pFieldUiDamageNumAsIns->m_sprite->_fmodules[frame_Start];

		m_pFieldUiDamageNumAsIns->m_sprite->SetBlendFrame(-1);
		m_pFieldUiDamageNumAsIns->m_sprite->m_Blend_Kind = 1;
		m_pFieldUiDamageNumAsIns->m_sprite->m_Blend_Percent = (GetData(pDamageNumList)->lifeTime>3 ? 32: (GetData(pDamageNumList)->lifeTime)*8);


		if(GetData(pDamageNumList)->damageValue){
			PaintNumber(m_pFieldUiDamageNumAs,m_Num,
				//m_pFieldUiDamageNumAsIns->m_sprite->_aframes[off + 0],
				GetData(pDamageNumList)->damageValue,
				GetData(pDamageNumList)->x+addx + m_pFieldUiDamageNumAsIns->CameraX,
				GetData(pDamageNumList)->y+addy-10+
				GetData(pDamageNumList)->z,-5, CGraphics::HCENTER);
		}else{
			PaintNumber(m_pFieldUiDamageNumAs,
				MODULE_DAMAGE_NUM_MISS,
				0,
				GetData(pDamageNumList)->x+addx + m_pFieldUiDamageNumAsIns->CameraX,
				GetData(pDamageNumList)->y+addy-10+
				GetData(pDamageNumList)->z,-5, CGraphics::HCENTER);
		}
		
		
		
		



		off = (m_pFieldUiDamageNumAsIns->m_sprite->_anims_af_start[0] + (7-GetData(pDamageNumList)->lifeTime)) * 5;

		//	paint num
//		SUTIL_SetTypeFrameAsprite(m_pFieldUiDamageNumAsIns,0);
//		SUTIL_SetXPosAsprite(m_pFieldUiDamageNumAsIns, GetData(pDamageNumList)->x );
//		SUTIL_SetYPosAsprite(m_pFieldUiDamageNumAsIns, GetData(pDamageNumList)->y );
//		SUTIL_SetZPosAsprite(m_pFieldUiDamageNumAsIns, GetData(pDamageNumList)->z );

//		SUTIL_PaintAsprite(m_pFieldUiDamageNumAsIns,S_NOT_INCLUDE_SORT);
		MoveNext(pDamageNumList);
	}

	m_pFieldUiDamageNumAs->SetBlendFrame(FRAME_DAMAGE_NUM_BLEND);

	PaintCombo();

}


//--------------------------------------------------------------------------
void FieldUi::Process()
//--------------------------------------------------------------------------
{
	//	pEftList
	MoveHead(pEftList);
	MoveNext(pEftList);
	while(NotEndList(pEftList))
	{
		if(1 > GetData(pEftList)->lifeTime)
		{
			SUTIL_FreeSpriteInstance(GetData(pEftList)->pSkillEftAsIns);
			SAFE_DELETE(GetData(pEftList));
			pEftList->Delete();
			continue;
		}

		SUTIL_UpdateTimeAsprite(GetData(pEftList)->pSkillEftAsIns);
		GetData(pEftList)->lifeTime--;
		MoveNext(pEftList);
	}

	//	pMonEftList
	int tempIdx = 0;
	MoveHead(pMonEftList);
	MoveNext(pMonEftList);
	while(NotEndList(pMonEftList))
	{
		if(1 > GetData(pMonEftList)->lifeTime)
		{
			SAFE_DELETE(GetData(pMonEftList));
			pMonEftList->Delete();
			continue;
		}

		tempIdx++;
		GetData(pMonEftList)->lifeTime--;
		MoveNext(pMonEftList);
	}

	if(tempIdx > m_nMonEftCurIdx)	{m_nMonEftCurIdx++;}
	if(m_nMonEftCurIdx > tempIdx)	{m_nMonEftCurIdx = tempIdx;}

	//	pDamageNumList
	MoveHead(pDamageNumList);
	MoveNext(pDamageNumList);
	while(NotEndList(pDamageNumList))
	{
		if(2 > GetData(pDamageNumList)->lifeTime)
		{
			SAFE_DELETE(GetData(pDamageNumList));
			pDamageNumList->Delete();
			continue;
		}
		GetData(pDamageNumList)->lifeTime--;
		MoveNext(pDamageNumList);
	}

	ProcessCombo();
}


//--------------------------------------------------------------------------
void FieldUi::GetMessage()
//--------------------------------------------------------------------------
{

}



//--------------------------------------------------------------------------
void FieldUi::InsertdamageNum(int x, int y, int z, int damage, int type)
//--------------------------------------------------------------------------
{

	DAMAGE_NUM_EFT * tmpDamageNumEft = (DAMAGE_NUM_EFT*)MALLOC(sizeof(DAMAGE_NUM_EFT));

	x += (SUTIL_GetRandom()%20) - 10; 
	y += (SUTIL_GetRandom()%20);
	//z += (SUTIL_GetRandom()%20);

	

	tmpDamageNumEft->x = x;
	tmpDamageNumEft->y = y;
	tmpDamageNumEft->z = z;
	tmpDamageNumEft->lifeTime = 8;
	tmpDamageNumEft->damageValue = damage;

	switch(type){
		case MON_NUM: 
			tmpDamageNumEft->start_ImgIndex = ANIM_DAMAGE_NUM_NO_1;
			break;
		case MON_CRI_NUM: 
			tmpDamageNumEft->start_ImgIndex = ANIM_DAMAGE_NUM_NO_CRITICAL;
			break;
		case HERO_NUM: 
			tmpDamageNumEft->start_ImgIndex = ANIM_DAMAGE_NUM_NO_MC;
			break;
		case HERO_CRI_NUM: 
			tmpDamageNumEft->start_ImgIndex = ANIM_DAMAGE_NUM_NO_MC_CRITICAL;
			break;
		case HEAL_NUM: 
			tmpDamageNumEft->start_ImgIndex = ANIM_DAMAGE_NUM_NO_HEAL;
			break;

	}

	

	MoveTail(pDamageNumList);
	pDamageNumList->Insert_prev(tmpDamageNumEft);

}

//--------------------------------------------------------------------------
void FieldUi::InsertEffect(int x, int y, int z, int eftnum)
//--------------------------------------------------------------------------
{
	ASpriteInstance* tmpAsIns = NULL;
	tmpAsIns = GL_NEW ASpriteInstance(s_ASpriteSet->pDebuffAs, 0, 0, NULL);// 0번째 배열, 실사용시는 define 필요
	SUTIL_SetTypeAniAsprite(tmpAsIns,eftnum);
	
	SUTIL_SetLoopAsprite(tmpAsIns, false);

	SUTIL_SetXPosAsprite(tmpAsIns, x );
	SUTIL_SetYPosAsprite(tmpAsIns, y );
	SUTIL_SetZPosAsprite(tmpAsIns, z );

	SKILL_EFT * tmpSkillEft = (SKILL_EFT*)MALLOC(sizeof(SKILL_EFT));
	tmpSkillEft->pSkillEftAsIns = tmpAsIns;
	tmpSkillEft->lifeTime = s_ASpriteSet->pDebuffAs->GetAFrames(eftnum);

	MoveTail(pEftList);
	pEftList->Insert_prev(tmpSkillEft);

}
//--------------------------------------------------------------------------
void FieldUi::Insert_CrashEffect(int x, int y, int z, int eftnum)
//--------------------------------------------------------------------------
{
	ASpriteInstance* tmpAsIns = NULL;
	tmpAsIns = GL_NEW ASpriteInstance(s_ASpriteSet->pDebuffAs, 0, 0, NULL);// 0번째 배열, 실사용시는 define 필요
	SUTIL_SetTypeAniAsprite(tmpAsIns,eftnum+(SUTIL_GetRandom()%2));

	SUTIL_SetLoopAsprite(tmpAsIns, false);

	if(0 == SUTIL_GetRandom()%2)	{SUTIL_SetDirAsprite(tmpAsIns, SDIR_LEFT);}
	else							{SUTIL_SetDirAsprite(tmpAsIns, SDIR_RIGHT);}

	SUTIL_SetXPosAsprite(tmpAsIns, x );
	SUTIL_SetYPosAsprite(tmpAsIns, y );
	SUTIL_SetZPosAsprite(tmpAsIns, z );

	SKILL_EFT * tmpSkillEft = (SKILL_EFT*)MALLOC(sizeof(SKILL_EFT));
	tmpSkillEft->pSkillEftAsIns = tmpAsIns;
	tmpSkillEft->lifeTime = 4;

	MoveTail(pEftList);
	pEftList->Insert_prev(tmpSkillEft);

}
//--------------------------------------------------------------------------
void FieldUi::InsertMonsterInfo(int _idx, int _name, int _level, int _nowHp, int _maxHp, int _elemental)
//--------------------------------------------------------------------------
{
	//	기존의 데이타를 지워준다.
	MoveHead(pMonEftList);
	MoveNext(pMonEftList);
	while(NotEndList(pMonEftList))
	{
		if(_idx == GetData(pMonEftList)->idx)
		{
			SAFE_DELETE(GetData(pMonEftList));
			pMonEftList->Delete();
			break;;
		}
		MoveNext(pMonEftList);
	}

	//	데이타를 넣어준다.
	MON_VIEW_UI* tmpUiViewEft = (MON_VIEW_UI*)MALLOC(sizeof(MON_VIEW_UI));
	tmpUiViewEft->idx = _idx;
	tmpUiViewEft->name = _name;
	tmpUiViewEft->level = _level;
	tmpUiViewEft->nowHp = _nowHp;
	tmpUiViewEft->maxHp = _maxHp;
	tmpUiViewEft->lifeTime = 15;
	tmpUiViewEft->elemental = _elemental;
	

	MoveTail(pMonEftList);
	pMonEftList->Insert_prev(tmpUiViewEft);
	MoveHead(pMonEftList);
	MoveNext(pMonEftList);

	m_nMonEftCurIdx = 1;
}


#define GAGE_RED		0
#define GAGE_BLUE		1
#define GAGE_YELLOW		2
#define GAGE_GREEN		3
//--------------------------------------------------------------------------
void FieldUi::PaintGage(int gageType, int gagewidth,int gageheight, int x, int y, int nowvalue, int maxvalue)
//--------------------------------------------------------------------------
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


void FieldUi::PaintNumber(ASprite* pAsIns, int numImgIdx, int value, int x, int y, int gap , int position)
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
		SUTIL_Paint_Module(pAsIns,numImgIdx + (value%10),x - xx*(wordsize+gap) ,y,0,position & (CGraphics::TOP|CGraphics::VCENTER|CGraphics::BOTTOM))	;//끝자리부터 하나씩 그려준다
	}
}
//--------------------------------------------------------------------------
// void FieldUi::PaintNumber(ASpriteInstance* pAsIns, int numImgIdx, int x, int y, int z, int value, int wordsize, int bwave, int flag)
// //--------------------------------------------------------------------------
// {
// 	if(value == 0){//Miss
// 		SUTIL_SetTypeFrameAsprite(pAsIns,numImgIdx);
// 		SUTIL_SetXPosAsprite(pAsIns, x);
// 		if(1 == bwave)
// 		{
// 			SUTIL_SetYPosAsprite(pAsIns, y+(SUTIL_GetRandom()%5));
// 		}
// 		else
// 		{
// 			SUTIL_SetYPosAsprite(pAsIns, y);
// 		}
// 
// 		SUTIL_SetZPosAsprite(pAsIns, z);
// 		SUTIL_PaintAsprite(pAsIns,S_NOT_INCLUDE_SORT);
// 		return;
// 	}
// 
// 
// 	int count = 0;
// 	int tmpcount = value;
// 
// 	while(0 < tmpcount)
// 	{
// 		count++;
// 		tmpcount /= 10;
// 	}
// 
// 	int width = wordsize*count;
// 
// 	if(1 == flag)
// 	{
// //		x += (width/2);
// 	}
// 	else
// 	{
// 		x += (width/2);
// 	}
// 
// 	
// 
// 	count = 0;
// 	tmpcount = value;
// 	while(0 < tmpcount)
// 	{
// 		count = tmpcount % 10;
// 
// 		SUTIL_SetTypeFrameAsprite(pAsIns,numImgIdx+count);
// 		SUTIL_SetXPosAsprite(pAsIns, x);
// 		if(1 == bwave)
// 		{
// 			SUTIL_SetYPosAsprite(pAsIns, y+(SUTIL_GetRandom()%5));
// 		}
// 		else
// 		{
// 			SUTIL_SetYPosAsprite(pAsIns, y);
// 		}
// 		
// 		SUTIL_SetZPosAsprite(pAsIns, z);
// 		SUTIL_PaintAsprite(pAsIns,S_NOT_INCLUDE_SORT);
// 
// 		tmpcount /= 10;
// 		x -= wordsize;
// 	}
// }





/////////////////////////////////////////  TALK  /////////////////////////////////////////////////
/////////////////////////////////////////  TALK  /////////////////////////////////////////////////
void FieldUi::SetTalkBox(int Village, int index, int Scene)
//--------------------------------------------------------------------------
{
	s_TalkBox.View = true;
	s_Main.CENTER = false;
	s_Sub.Popup_Ready = false;
	s_Sub.Popup_Yes_No = false;

	s_TalkBox.EventNum = 0;//초기화
	s_TalkBox.Face_Now = -1;//초기화
	s_TalkBox.Face_Next = -1;//초기화
	s_TalkBox.Line=0;//초기화
	s_TalkBox.LineMAX=0;//초기화
	s_TalkBox.count=0;//초기화
	s_TalkBox.index=0;

	s_Sub.SameFAM = -1;//로테이션 텍스트 초기화
	s_Sub.SameFam_MAX = 0;//로테이션 텍스트 초기화

	//start line 파인더
	if(Scene>=0){//메인 이벤트 대화
		s_Main.Scene = Scene;
		if(s_TalkBox.pText == NULL)
			s_TalkBox.pText = _SUTIL->LoadTextPack(PACK_DATA_TALK, DATA_TALK_SCENE_00+Scene);

		int Max_Line = s_TalkBox.pText->nTextNum/2;

		if(Scene>=0){//단락번호(index) 를 줄넘버로 변환
			for(int xx = 0, yy = 0;xx<Max_Line;xx++){
				if(yy >= index){
					s_TalkBox.index = xx;
					break;
				}
				if(GetFlags(xx) == -1){
					yy++;
				}

			}
		}else{//명성치와 퀘스트 완료 여부를 기준으로 Index 산출
			s_TalkBox.index = index;
		}

		SetQuest(s_TalkBox.index);
		s_TalkBox.EventNum = GetFlags(s_TalkBox.index);//첫줄인데 바로 끝문장일때 처리해주어야함


		s_TalkBox.Face_Now = Load_Face(s_TalkBox.index);//현재 대사
		if(s_TalkBox.Face_Now>=0){
			SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//기존의 일러스트 삭제
			s_TalkBox.FaceNowAs = SUTIL_LoadSprite(PACK_SPRITE_FACE, s_TalkBox.Face_Now);//대사창
		}
	}else{//NPC 대화
		s_Sub.village = Village;
		if(s_TalkBox.pText == NULL)
			s_TalkBox.pText = _SUTIL->LoadTextPack(PACK_DATA_TALK, DATA_TALK_NPC_00+Village);
		
		s_TalkBox.index = Find_NpcStart(index);
		if(s_TalkBox.index >=0){
			s_TalkBox.EventNum = GetFlags(s_TalkBox.index);//첫줄인데 바로 끝문장일때 처리해주어야함
		}
		


		
	}
	
	


}
int FieldUi::Load_Face(int index){

	int nameLength = 0;
	for(int xx = 0;xx<20;xx++){//이름 잘라오기
		if(xx==19){//오류가 발생했다고 판단
			nameLength = -1;
			break;
		}
		if(s_TalkBox.pText->nText[index*2+1][xx] == '|'){
			break;
		}
		nameLength++;
	}



	for(int xx = 0 ; xx<NAME_END ; xx++){//등록된 이름을 돌면서 검색하여 동일한 이름이 있는지 검색한다
		int length = STRLEN((char*)pTalkNameText->nText[xx])-2 ;
		if(nameLength == length){
			for(int yy = 0 ; yy <length ; yy++){//길이만큼 비교
				if(pTalkNameText->nText[xx][yy+2] != s_TalkBox.pText->nText[index*2+1][yy])
					break;
				if(yy == length-1)
					return (pTalkNameText->nText[xx][0] - '0')*10 + (pTalkNameText->nText[xx][1] - '0');//일러스트 인덱스 리턴
			}
		}
	}
	if(	(s_TalkBox.pText->nText[index*2+1][0] == 'C') && 
		(s_TalkBox.pText->nText[index*2+1][1] == 'E') && 
		(s_TalkBox.pText->nText[index*2+1][2] == 'N') && 
		(s_TalkBox.pText->nText[index*2+1][3] == 'T') && 
		(s_TalkBox.pText->nText[index*2+1][4] == 'E') && 
		(s_TalkBox.pText->nText[index*2+1][5] == 'R')){//인트로 텍스트같은 특수 처리
			s_Main.CENTER = true;
	}
	return -1;
}
int FieldUi::Find_NpcStart(int NPC_ID){//NPC ID 로 NPC 이름을 찾아낸다

	s_Sub.NPC_Name = -1;

	for(int xx = 0, id = 0 ; xx<NPC_NAME_END ; xx++){//등록된 이름을 돌면서 검색하여 동일한 아이디가 있는지 검색한다
		id =	(pTalkNpcNameText->nText[xx][0] - '0')*1000+
				(pTalkNpcNameText->nText[xx][1] - '0')*100+
				(pTalkNpcNameText->nText[xx][2] - '0')*10+
				(pTalkNpcNameText->nText[xx][3] - '0');

		if(id == NPC_ID){
			s_Sub.NPC_Name = xx;
			break;
		}
	}

	if(s_Sub.NPC_Name == -1){//만약 찾는 NPC가 없다면
		s_TalkBox.View = false;
		SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//일러스트1
		SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//일러스트2
		SUTIL_FreeTextPack(s_TalkBox.pText);//대사
		return -1;
	}
	


	int Start_Line = 0;//문단의 시작지점
	int Max_Line = s_TalkBox.pText->nTextNum/2;

	bool End_Skip = false;//조건을 만족하지 않을때 뛰어넘도록 함
	bool End_keep = false;//아직 실행하지 않은 서브퀘스트의 경우 명성치만 맞다면 무조건 실행한다
	bool Find_Name = false;//아직 실행하지 않은 서브퀘스트의 경우 명성치만 맞다면 무조건 실행한다
	int Name_length = STRLEN((char*)pTalkNpcNameText->nText[s_Sub.NPC_Name])-4;

	for(int xx = 0;xx<Max_Line;xx++){

		if(!Find_Name){//지정된 이름이 나올때까지 내려간다
			for(int yy = 0 ; yy <Name_length ; yy++){//이름 길이만큼 비교
				if(pTalkNpcNameText->nText[s_Sub.NPC_Name][yy+4] != s_TalkBox.pText->nText[xx*2+1][yy])//혹시 글자가 틀리면 다음줄로
					break;
				
				if(yy == Name_length-1){
					Find_Name = true;//이름이 최초로 발견된지점
					Start_Line = xx;
					xx--;
					
				}
			}
			continue;
		}


		if(s_TalkBox.pText->nText[xx*2][10] == 'S'){//서브퀘스트 가 있는 문단이면
			int Q_Num = (s_TalkBox.pText->nText[xx*2][12] - '0')*100+
						(s_TalkBox.pText->nText[xx*2][13] - '0')*10+
						(s_TalkBox.pText->nText[xx*2][14] - '0');
			switch(s_TalkBox.pText->nText[xx*2][11]){
				case 's'://start
					if(SUBQUEST_IDX(Q_Num) == QUEST_NEW){
						End_keep = true;
					}else{
						End_Skip = true;
					}
					break;
				case 'm'://middle
					if(SUBQUEST_IDX(Q_Num) == QUEST_ING){
						End_keep = true;
					}else{
						End_Skip = true;
					}
					break;
				case 'e'://end
					if(SUBQUEST_IDX(Q_Num) == QUEST_FIN){
						End_keep = true; 
						SUBQUEST_IDX(Q_Num) = QUEST_END;
					}else{
						End_Skip = true;
					}
					break;

			}	
		}

		if(
			(s_TalkBox.pText->nText[xx*2][3] == 'E') && 
			(s_TalkBox.pText->nText[xx*2][4] == 'N') && 
			(s_TalkBox.pText->nText[xx*2][5] == 'D')
			){

				int fames = (s_TalkBox.pText->nText[xx*2][7] - '0')*10+
							(s_TalkBox.pText->nText[xx*2][8] - '0');//xx가 속한 단락의 요구명성치

				


				if(End_Skip){//이미 지나갔거나 상황에 맞지않는 서브퀘스트의 텍스트일경우
					s_Sub.SameFAM = -1;
					s_Sub.SameFam_MAX = 0;
				}else if(End_keep){//명성치만 맞다면 무조건적인 실행을 한다
					s_Sub.SameFAM = -1;
					s_Sub.SameFam_MAX = 0;
					if(Character::s_Ability[Character::s_HeroTag.SEX].FAM >= fames){//명성치 만족
						return Start_Line;
					}
				}else{//서브퀘스트 명령이 없으므로 명성치 체크를한다




					if(Character::s_Ability[Character::s_HeroTag.SEX].FAM < fames){//명성치가 부족하다면 바로 위의 END 값 반환을 한다

						int Up = 2 +(s_Sub.SameFam_MAX-1) - (s_Sub.Talk_Num % s_Sub.SameFam_MAX); 
						return Find_NpcRewind(2 , xx);
					}else{
						//텍스트 로테이션 MAX 갯수 체크부분 - 이부분이 없으면 대화 로테이션은 일어나지않고 마지막 텍스트만 출력된다
						if(s_Sub.SameFAM != fames){
							s_Sub.SameFAM = fames;
							s_Sub.SameFam_MAX = 1;
						}else{
							s_Sub.SameFam_MAX++;
						}


						if(xx+1 < Max_Line){//다음라인이 존재한다면
							for(int yy = 0 ; yy <Name_length ; yy++){//이름 길이만큼 비교
								if(pTalkNpcNameText->nText[s_Sub.NPC_Name][yy+4] != s_TalkBox.pText->nText[(xx+1)*2+1][yy]){//다음단락이 다른 NPC 대사라면
									return Find_NpcRewind(1 , xx);
								}
							}
						}else{//마지막 줄이면
							return Find_NpcRewind(1 , xx);
						}
					}
				}


				Start_Line = xx+1;
				End_keep = false;
				End_Skip = false;
				//Find_Name = false;//한 단락이 끝나면 이름은 다시 확인을 해야한다
		}
		



	}
	if(Start_Line >= Max_Line) Start_Line = Max_Line-1;

	if(!Find_Name){//끝까지 돌았으나 지정NPC의 대사가 없다면
		s_TalkBox.View = false;
		SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//일러스트1
		SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//일러스트2
		SUTIL_FreeTextPack(s_TalkBox.pText);//대사
		return -1;
	}
	return Start_Line;




}
int FieldUi::Find_NpcRewind(int Up , int Line){//다시 위로 올라와야 할 경우
	Up = Up +(s_Sub.SameFam_MAX-1) - (s_Sub.Talk_Num % s_Sub.SameFam_MAX);
	for(int yy = Line-1;yy>=0;yy--){
		if(
			(s_TalkBox.pText->nText[yy*2][3] == 'E') && 
			(s_TalkBox.pText->nText[yy*2][4] == 'N') && 
			(s_TalkBox.pText->nText[yy*2][5] == 'D')
			){
				Up--;

		}
		if(Up==0){
			return yy+1;
		}
	}
	return -1;
}


void FieldUi::Set_Next_Face(int NextFace){
	if(s_TalkBox.Face_Next != NextFace){
		SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//기존의 일러스트 삭제
		s_TalkBox.Face_Next = NextFace;
		if(NextFace>=0)
			s_TalkBox.FaceNextAs = SUTIL_LoadSprite(PACK_SPRITE_FACE, s_TalkBox.Face_Next);//새 일러스트 로드
	}
}
void FieldUi::PaintTalkBox()
//--------------------------------------------------------------------------
{
	if(!s_TalkBox.View)return;

	if(s_Main.CENTER){
		_SUTIL->pFont->setColor(0xFFFFFF);
		_SUTIL->pFont->Dry_Wrap_Width(200);
		_SUTIL->pFont->Dry_StartLine_Max(1,10);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)s_TalkBox.pText->nText[s_TalkBox.index*2+1], XPOS, YPOS-10, CGraphics::HCENTER|CGraphics::VCENTER);
		s_TalkBox.LineMAX = 1;
		s_TalkBox.count = 20;
		_SUTIL->pFont->setLineSpace(5);
		return;
	}else{
		_SUTIL->pFont->setLineSpace(2);
	}


	//Scene 가 null이면 NPC 와의 대화로 간주한다 ID로 누구와의 대화인지를 찾아낸다
 	if(s_TalkBox.Face_Now>=0)SUTIL_Paint_Frame(s_TalkBox.FaceNowAs ,FRAME_FACE_00_FACE+s_TalkBox.Emotion, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SUTIL_Paint_Frame(s_TalkBox._spr_TalkBox ,FRAME_TALKBOX_TALK_BOX, XPOS, SCREEN_HEIGHT, 0);


	_SUTIL->pFont->setColor(0xffd7ad);
	_SUTIL->pFont->setOutline(false);

	_SUTIL->pFont->Dry_StartLine_Max(0,1);//이름
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)s_TalkBox.pText->nText[s_TalkBox.index*2+1], 40, SCREEN_HEIGHT-49, CGraphics::HCENTER);

	_SUTIL->pFont->setColor(0xFFFFFF);
	_SUTIL->pFont->Dry_Wrap_Width(200);
	_SUTIL->pFont->Dry_StartLine_Max(1+s_TalkBox.Line,2);
	s_TalkBox.LineMAX = _SUTIL->pFont->DrawText(_SUTIL->g, (char*)s_TalkBox.pText->nText[s_TalkBox.index*2+1], 20, SCREEN_HEIGHT-30, 0);
	
	


	if((s_TalkBox.count<5)&&(_SUTIL->pFont->wPixel[1+s_TalkBox.Line] <= 40*s_TalkBox.count )){s_TalkBox.count = 5;}
	if((s_TalkBox.count<10)&&(_SUTIL->pFont->wPixel[1+s_TalkBox.Line+1] <= 40*(s_TalkBox.count-5) )){s_TalkBox.count = 10;}
	if(s_TalkBox.count<10){
		SUTIL_Paint_Frame(s_TalkBox._spr_TalkBox ,FRAME_TALKBOX_BLACK+s_TalkBox.count, XPOS, SCREEN_HEIGHT, 0);
	}
	if(s_TalkBox.count == 10 && s_TalkBox.EventNum!= -1){

		Set_Next_Face( Load_Face(s_TalkBox.index+1) );
		s_TalkBox.EventNum = 0;//사전 로딩은 이벤트값을 가져서는 안된다
	}



	s_TalkBox.count++;

	if(s_Sub.Popup_Yes_No){//서브 퀘스트를 받을것인가 아닌가에 대한 팝업창
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1, XPOS,YPOS,0);//팝업 프레임 지정
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_POPUP_1_LEFT + s_Sub.Yes_No, XPOS,YPOS,0);//팝업 프레임 지정

		_SUTIL->pFont->setColor(0xf8e6cb);

		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_Q1], XPOS, YPOS+15, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_YES], XPOS-31, YPOS+37, CGraphics::HCENTER);
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)PopupUi::pCLRPOPUP_Text->nText[CLRMENU_NO], XPOS+31, YPOS+37, CGraphics::HCENTER);
	}

}
int FieldUi::KeyTalkBox(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{
	if(m_keyRepeat)return 0;//키릴리즈에 반응하지않는다.
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//값대치



	if(s_Sub.Popup_Yes_No){// 팝업 - 서브퀘스트 수락여부
		if(m_keyCode == MH_KEY_RIGHT){
			s_Sub.Yes_No = 1;//No
			return 0;
		}else if(m_keyCode == MH_KEY_LEFT){
			s_Sub.Yes_No = 0;//Yes
			SUBQUEST_IDX(s_Sub.QuestNum) = QUEST_ING;
			return 0;
		}else if(m_keyCode == MH_KEY_SELECT){//올린 스탯 적용

			if(s_Sub.Yes_No){//No - 텍스트창 닫기
				s_TalkBox.View = false;
				SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//일러스트1
				SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//일러스트2
				SUTIL_FreeTextPack(s_TalkBox.pText);//대사
				return 0;
			}else{//Yes - 서브퀘스트 실행
				SUBQUEST_IDX(s_Sub.QuestNum) = QUEST_ING;//퀘스트 실행 상태로 진입
			}
			s_Sub.Popup_Yes_No = false;//팝업해제
			s_Sub.Yes_No=0;
		}
	}


	


	if(m_keyCode == MH_KEY_SELECT){
		if(s_TalkBox.count<8){
			s_TalkBox.count=8;
			return 0;
		}
		if(s_TalkBox.Line+1+2 < s_TalkBox.LineMAX){//더 출력할 줄이 남아있을때
			s_TalkBox.Line+=2;
			s_TalkBox.count=0;
		}else{
			if(s_Sub.Popup_Ready){//팝업 대기상태일때 키를 한번더 누르면 팝업창이 뜬다
				s_Sub.Popup_Yes_No = true;
				s_Sub.Popup_Ready = false;
				return 0;
			}

			if(s_TalkBox.EventNum!=0){// END 일때
				s_TalkBox.View = false;
				SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//일러스트1
				SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//일러스트2
				SUTIL_FreeTextPack(s_TalkBox.pText);//대사

				//	끝났을시 이벤트를 호출해준다.
				ADD_EVENT_MSG(EVT_TALK_ENDEVT, 0, s_TalkBox.EventNum);
				return 0;
			}



			s_TalkBox.count=0;
			s_TalkBox.Line=0;
			s_TalkBox.LineMAX=0;
			s_TalkBox.index++;

			SetQuest(s_TalkBox.index);
			s_TalkBox.EventNum = GetFlags(s_TalkBox.index);//이벤트 넘버할당

			Set_Next_Face(Load_Face(s_TalkBox.index));//현재 대사

			s_TalkBox.Emotion = 
				(s_TalkBox.pText->nText[s_TalkBox.index*2][0]-'0')*10 + 
				(s_TalkBox.pText->nText[s_TalkBox.index*2][1]-'0');//표정

			int temp = s_TalkBox.Face_Now;
			s_TalkBox.Face_Now = s_TalkBox.Face_Next;
			s_TalkBox.Face_Next = temp;

			ASprite* Temp = s_TalkBox.FaceNowAs;
			s_TalkBox.FaceNowAs = s_TalkBox.FaceNextAs;
			s_TalkBox.FaceNextAs = Temp;
		}


	}else if(m_keyCode == MH_KEY_POUND){

		//index+1 부터,   끝 또는 END 를 만날때까지 이벤트 관련 변수가 있는지 체크한다.
		int Max_Line = s_TalkBox.pText->nTextNum/2;
		if(GetFlags(s_TalkBox.index) != -1){//현재 줄이 마지막 줄이 아닐때
			for(int xx = s_TalkBox.index+1;xx<Max_Line;xx++){//끝라인 또는 END 를 만날때 까지 돌면서
				SetQuest(xx);
				if(GetFlags(xx) == -1){
					break;//중간에 END 를 만나면 퀘스트 찾기를 중단한다
				}

			}
		}


		//각종 해제
		s_TalkBox.View = false;
		SUTIL_FreeSprite(s_TalkBox.FaceNowAs);//일러스트1
		SUTIL_FreeSprite(s_TalkBox.FaceNextAs);//일러스트2
		SUTIL_FreeTextPack(s_TalkBox.pText);//대사

		//	끝났을시 이벤트를 호출해준다.
		s_TalkBox.EventNum = -1;
		ADD_EVENT_MSG(EVT_TALK_ENDEVT, 0, s_TalkBox.EventNum);
		return 0;
	}

	return 0;
}
void FieldUi::SetQuest(int index){	
	//퀘스트 넘버 찾기
	switch(s_TalkBox.pText->nText[index*2][10]){
		case 'M'://메인퀘
			//메인 퀘스트 넘버 증가
			INCREASE_MAINQUEST_IDX();
			PopupUi::AddMessage(CLRMENU_MAIN_Q);
			break;
		case 'm'://메인퀘
			//메인 퀘스트 넘버 증가
			INCREASE_MAINQUEST_IDX();
			break;
		case 'S'://서브퀘
			if(s_TalkBox.pText->nText[index*2][11] == 's'){
				s_Sub.QuestNum = 
					(s_TalkBox.pText->nText[index*2][12] - '0')*100 +
					(s_TalkBox.pText->nText[index*2][13] - '0')*10 + 
					(s_TalkBox.pText->nText[index*2][14] - '0');
				s_Sub.Popup_Ready = true;
			}
			
			//퀘스트 넘버 넘기기
			break;

	}
}
int FieldUi::GetFlags(int index){	
	//문장 문법 처리 END
	if(
		(s_TalkBox.pText->nText[index*2][3] == 'E') && 
		(s_TalkBox.pText->nText[index*2][4] == 'N') && 
		(s_TalkBox.pText->nText[index*2][5] == 'D')
		){
		return -1;
	}
	return 0;
}
/////////////////////////////////////////  TALK  /////////////////////////////////////////////////
/////////////////////////////////////////  TALK  /////////////////////////////////////////////////




#define CHARINFO_POS_X	(0)
#define CHARINFO_POS_Y	(0)

#define CHAR_HP_GAGE_SIZE	(52)
#define CHAR_HP_HEIGHT_SIZE	(4)
#define LEVEL_NUM_IMG_WIDTH		(5)

//--------------------------------------------------------------------------
void FieldUi::PaintCharInfo(int level, int NowHp, int MaxHp, int NowMp, int MaxMp, int elemental)
//--------------------------------------------------------------------------
{

//	int NowHp = 45642;
//	int MaxHp = 60000;
//	int NowMp = 25642;
//	int MaxMp = 60000;
//	int level = 8;
	//	base

	// char hp
	PaintGage(GAGE_RED, CHAR_HP_GAGE_SIZE,CHAR_HP_HEIGHT_SIZE, CHARINFO_POS_X+34, CHARINFO_POS_Y+12, NowHp, MaxHp);
	// char mp
	PaintGage(GAGE_BLUE, CHAR_HP_GAGE_SIZE,CHAR_HP_HEIGHT_SIZE, CHARINFO_POS_X+30, CHARINFO_POS_Y+21, NowMp, MaxMp);

	if(level<100){
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CHARINFO_1, CHARINFO_POS_X, CHARINFO_POS_Y, 0);
	}else{
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_CHARINFO_2, CHARINFO_POS_X, CHARINFO_POS_Y, 0);
	}

	//	face
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,Character::Check_sex(FRAME_UI_MC_HEAD_W,FRAME_UI_MC_HEAD_M), CHARINFO_POS_X, CHARINFO_POS_Y, 0);

	//	element
//	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_MC_ELE1+elemental, CHARINFO_POS_X, CHARINFO_POS_Y, 0);


	if(Character::s_Ability[Character::s_HeroTag.SEX].POINT){
		SUTIL_Paint_Ani(s_ASpriteSet->pFieldUiAs ,ANIM_UI_A_STAT_UP, CHARINFO_POS_X, CHARINFO_POS_Y, 0);
	}

	//	level
	/*for(int loop = 0; loop < 
		SUTIL_SetTypeFrameAsprite(m_pFieldUiAsIns,FRAME_UI_LEVEL_NUM+);
		SUTIL_SetXPosAsprite(m_pFieldUiAsIns, CHARINFO_POS_X+3);
	SUTIL_SetYPosAsprite(m_pFieldUiAsIns, CHARINFO_POS_Y+27);
	SUTIL_SetZPosAsprite(m_pFieldUiAsIns, 0);
	SUTIL_PaintAsprite(m_pFieldUiAsIns,S_NOT_INCLUDE_SORT);*/

	//	levelnum
	//PaintLevel(CHARINFO_POS_X+22, CHARINFO_POS_Y+28, level);
	if(level<100){
		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM,level, CHARINFO_POS_X+19, CHARINFO_POS_Y+28, 0, 0);
	}else{												
		PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM,level, CHARINFO_POS_X+17, CHARINFO_POS_Y+28, 0, 0);
	}




	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM,NowHp, CHARINFO_POS_X+79, CHARINFO_POS_Y+8, 0, CGraphics::RIGHT);
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM,NowMp, CHARINFO_POS_X+75, CHARINFO_POS_Y+17, 0, CGraphics::RIGHT);
}


#define LEVEL_1_TIME	 70
#define LEVEL_2_TIME	 90
#define LEVEL_3_TIME	110
#define LEVEL_4_TIME	130
#define LEVEL_5_TIME	170
//--------------------------------------------------------------------------
void FieldUi::PaintComboGage(int Combo)
//--------------------------------------------------------------------------
{
	if(m_nSaveComboMax >= 80 && m_nBuffComboLevel < 5){
		m_nBuffComboLevel = 5;
		m_nBuffComboTimer = LEVEL_5_TIME;
	}else if(m_nSaveComboMax >= 60 && m_nBuffComboLevel < 4){
		m_nBuffComboLevel = 4;
		m_nBuffComboTimer = LEVEL_4_TIME;
	}else if(m_nSaveComboMax >= 40 && m_nBuffComboLevel < 3){
		m_nBuffComboLevel = 3;
		m_nBuffComboTimer = LEVEL_3_TIME;
	}else if(m_nSaveComboMax >= 30 && m_nBuffComboLevel < 2){
		m_nBuffComboLevel = 2;
		m_nBuffComboTimer = LEVEL_2_TIME;
	}else if(m_nSaveComboMax >= 15 && m_nBuffComboLevel < 1){
		m_nBuffComboLevel = 1;
		m_nBuffComboTimer = LEVEL_1_TIME;
	}
	
	switch(m_nBuffComboLevel){ 
		case 1:
			_SUTIL->g->SetClip(CHARINFO_POS_X+10, CHARINFO_POS_Y+29,(6*1*LEVEL_1_TIME)/LEVEL_1_TIME,9);
			break;													   
		case 2:														   
			_SUTIL->g->SetClip(CHARINFO_POS_X+10, CHARINFO_POS_Y+29,(6*2*LEVEL_2_TIME)/LEVEL_2_TIME,9);
			break;													   
		case 3:														   
			_SUTIL->g->SetClip(CHARINFO_POS_X+10, CHARINFO_POS_Y+29,(6*3*LEVEL_3_TIME)/LEVEL_3_TIME,9);
			break;													   
		case 4:														   
			_SUTIL->g->SetClip(CHARINFO_POS_X+10, CHARINFO_POS_Y+29,(6*4*LEVEL_4_TIME)/LEVEL_4_TIME,9);
			break;													   
		case 5:														   
			_SUTIL->g->SetClip(CHARINFO_POS_X+10, CHARINFO_POS_Y+29,(6*5*m_nBuffComboTimer)/LEVEL_5_TIME,9);
			break;
	}

	if(m_nBuffComboLevel){
		SUTIL_Paint_Module(s_ASpriteSet->pFieldUiAs ,MODULE_UI_M_COMBO,CHARINFO_POS_X+10, CHARINFO_POS_Y+29,0,0);
		_SUTIL->g->ResetClip();
		m_nBuffComboTimer--;
		if(m_nBuffComboTimer <= 0){//콤보 버프종료
			m_nBuffComboLevel = 0;
		}

	}
	
}



#define MONINFO_POS_X			(SCREEN_WIDTH-90)
#define MONINFO_POS_Y			(3)
#define MONSTER_HP_GAGE_SIZE	(51)
//--------------------------------------------------------------------------
void FieldUi::PaintMonsterInfo(int MonName, int level, int NowHp, int MaxHp, int elemental)
//--------------------------------------------------------------------------
{
	//	base
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_MONSTERINFO, MONINFO_POS_X, MONINFO_POS_Y, 0);

	// monster hp
	PaintGage(GAGE_RED, MONSTER_HP_GAGE_SIZE,CHAR_HP_HEIGHT_SIZE, MONINFO_POS_X+34, MONINFO_POS_Y+19, NowHp, MaxHp);

	//	element
	SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_MON_ELE1+elemental, MONINFO_POS_X, MONINFO_POS_Y, 0);

	//	monster name
	_SUTIL->pFont->setColor(0xffffff);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pMonNameText->nText[MonName], MONINFO_POS_X+35, MONINFO_POS_Y+5, 0);
	
	
	//	levelnum
	//PaintLevel(MONINFO_POS_X+22, MONINFO_POS_Y+21, level);
	PaintNumber(s_ASpriteSet->pFieldUiAs, MODULE_UI_M_LEVEL_NUM,level, MONINFO_POS_X+17, MONINFO_POS_Y+21, 0,  0);

}


#define SKILL_SLOT_POS_X	(2)
#define SKILL_SLOT_POS_Y	(SCREEN_HEIGHT - 38)
#define SKILL_SLOT_SIZE		(30)
 
//--------------------------------------------------------------------------
void FieldUi::PaintSkillInfo(int* skill_id,int* coolMax,int* cooltime,int mana,int* needmana)
//--------------------------------------------------------------------------
{
	//	1379 skill   m_pFieldUiAs 

	for(int loop = 0; loop < 3; loop++){//아이콘
		
		if(skill_id[loop]>=0){//비설정 상태가 아니라면 
			if(cooltime[loop]>2){//쿨타임이 남아있다면
				s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,8,0);//그레이 스케일
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + skill_id[loop], SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6,0);
				for(int i = 0,f = (cooltime[loop]*13/coolMax[loop]);i<=f;i++){
					SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILL_COOL, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6+i,0);
				}
				cooltime[loop]--;
			}else if(cooltime[loop]==2){//쿨타임이 해제직전
				s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,7,42260);//60% 밝게
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + skill_id[loop], SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6,0);
				cooltime[loop]--;
			}else if(cooltime[loop]==1){//쿨타임이 해제직전
				s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,7,21130);//50% 밝게
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + skill_id[loop], SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6,0);
				cooltime[loop]=0;
			}else{

				if(mana < needmana[loop])//마나부족
					s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,8,0);//그레이 스케일
				else 
					s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,8,0);//그레이 스케일 해제

				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_S_1 + skill_id[loop], SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6,0);
			}


			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_BASE, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);//프레임
			if(cooltime[loop]==0)SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_1 + loop, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
			
		}else{
			s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,0,0);//비어있는 슬롯은 블랜딩을 해제한다

			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_EMPTY, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
			//프레임
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_BASE, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
			SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_1 + loop, SKILL_SLOT_POS_X+loop*SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
		}


		
	}

	
		

	
	if(Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]>=0 && Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]>=0){//비설정 상태가 아니라면 
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_EMPTY, SCREEN_WIDTH - SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);

		if(cooltime[5]>2){//쿨타임이 남아있다면

			s_ASpriteSet->pItemAs->SetBlendCustom(true,false,8,0);//그레이 스케일
			s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,8,0);//그레이 스케일
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,  
				PopupUi::itemICON(Character::s_ItemBag[Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]][Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]]), 
				SCREEN_WIDTH - SKILL_SLOT_SIZE + 5,SKILL_SLOT_POS_Y + 5,0,0);
			for(int i = 0,f = (cooltime[5]*13/coolMax[5]);i<=f;i++){
				SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILL_COOL, SCREEN_WIDTH - SKILL_SLOT_SIZE + 6,SKILL_SLOT_POS_Y + 6+i,0);
			}
			cooltime[5]--;
		}else if(cooltime[5]==2){//쿨타임이 해제직전

			s_ASpriteSet->pItemAs->SetBlendCustom(true,false,7,42260);//60% 밝게
			s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,7,42260);//60% 밝게
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,  
				PopupUi::itemICON(Character::s_ItemBag[Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]][Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]]), 
				SCREEN_WIDTH - SKILL_SLOT_SIZE + 5,SKILL_SLOT_POS_Y + 5,0,0);
			cooltime[5]--;
		}else if(cooltime[5]==1){//쿨타임이 해제직전

			s_ASpriteSet->pItemAs->SetBlendCustom(true,false,7,21130);//50% 밝게
			s_ASpriteSet->pFieldUiAs->SetBlendCustom(true,false,7,21130);//50% 밝게
			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,  
				PopupUi::itemICON(Character::s_ItemBag[Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]][Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]]), 
				SCREEN_WIDTH - SKILL_SLOT_SIZE + 5,SKILL_SLOT_POS_Y + 5,0,0);
			cooltime[5]=0;
		}else{

			s_ASpriteSet->pItemAs->SetBlendCustom(false,false,8,0);//그레이 스케일 해제
			s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,8,0);//그레이 스케일 해제

			SUTIL_Paint_Module(s_ASpriteSet->pItemAs ,  
				PopupUi::itemICON(Character::s_ItemBag[Character::s_Status[Character::s_HeroTag.SEX].Qslot[0]][Character::s_Status[Character::s_HeroTag.SEX].Qslot[1]]), 
				SCREEN_WIDTH - SKILL_SLOT_SIZE + 5,SKILL_SLOT_POS_Y + 5,0,0);
		}


		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_ITEMSLOT_BASE, SCREEN_WIDTH - SKILL_SLOT_SIZE ,SKILL_SLOT_POS_Y,0);//프레임
		if(cooltime[5]==0)SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_SHARP, SCREEN_WIDTH - SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);

	}else{
		s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,0,0);//비어있는 슬롯은 블랜딩을 해제한다

		//	pound key skill
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_EMPTY, SCREEN_WIDTH - SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);

		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_ITEMSLOT_BASE, SCREEN_WIDTH - SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
		SUTIL_Paint_Frame(s_ASpriteSet->pFieldUiAs ,FRAME_UI_SKILLSLOT_SHARP, SCREEN_WIDTH - SKILL_SLOT_SIZE,SKILL_SLOT_POS_Y,0);
	}

	s_ASpriteSet->pItemAs->SetBlendCustom(false,false,8,0);//그레이 스케일 해제
	s_ASpriteSet->pFieldUiAs->SetBlendCustom(false,false,8,0);//그레이 스케일 해제

	
}


#define EXP_GAGE_POS_X	(0)
#define EXP_GAGE_POS_Y	(SCREEN_HEIGHT - 0)
#define EXP_GAGE_SIZE	(183)
#define EXP_GAGE_HEIGHT	(4)

//--------------------------------------------------------------------------
void FieldUi::PaintExpInfo(int NowExp, int MaxExp)
//--------------------------------------------------------------------------
{ 
//	int NowExp = 45642;
//	int MaxExp = 60000;

//	int curgage = ((NowExp*EXP_GAGE_SIZE)/MaxExp);

	//	skill text
	SUTIL_SetTypeFrameAsprite(m_pFieldUiAsIns,FRAME_UI_GAGE_EXP_TEXT);
	SUTIL_SetXPosAsprite(m_pFieldUiAsIns, EXP_GAGE_POS_X);
	SUTIL_SetYPosAsprite(m_pFieldUiAsIns, EXP_GAGE_POS_Y);
	SUTIL_SetZPosAsprite(m_pFieldUiAsIns, 0);
	SUTIL_PaintAsprite(m_pFieldUiAsIns,S_NOT_INCLUDE_SORT); 

	//	yellow gage
	PaintGage(GAGE_GREEN, EXP_GAGE_SIZE,EXP_GAGE_HEIGHT, EXP_GAGE_POS_X+21, EXP_GAGE_POS_Y-9, NowExp, MaxExp);


}


#define COMBO_TEXT_LOCATE_X		(SCREEN_WIDTH - 53)
#define COMBO_TEXT_LOCATE_Y		(50)
//--------------------------------------------------------------------------
void FieldUi::PaintCombo()
//--------------------------------------------------------------------------
{
	if(0 == m_nSaveCombo)	{return;}

	//	블랜딩
	if(30 < m_nSaveComboTimer)
	{
		m_nSaveComboTimer--;
		m_nSaveCombo = 0;
		m_nSaveComboMax = 0;
	}
	if(m_nSaveComboTimer > 15){
		int SetAlpha = 62 -  (m_nSaveComboTimer*2);
		m_pFieldUiDamageNumAs->SetBlendCustom(true,false,1,SetAlpha);
	}
	
	//m_pFieldUiDamageNumAs->workPal(true, 0, 5);

	//	콤보
	if(0 == m_nSaveCombo%20)
	{
		switch(m_nSaveCombo/20)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			{
				//	이미지가 1부터 시작함
				SUTIL_Paint_Frame(m_pFieldUiDamageNumAs ,FRAME_DAMAGE_NUM_GOOD-1+(m_nSaveCombo/20), COMBO_TEXT_LOCATE_X, COMBO_TEXT_LOCATE_Y, 0);
				break;
			}
			default:
			{
				SUTIL_Paint_Frame(m_pFieldUiDamageNumAs ,FRAME_DAMAGE_NUM_GOOD-1+5, COMBO_TEXT_LOCATE_X, COMBO_TEXT_LOCATE_Y, 0);
				break;
			}
		}
	}
	else	//일반 콤보
	{
		int temp = m_nSaveComboTimer;

		//	콤보 바탕 이미지
		if(2 < temp)	{temp = 2;}
		
		SUTIL_Paint_Frame(m_pFieldUiDamageNumAs ,FRAME_DAMAGE_NUM_HIT_START+temp, COMBO_TEXT_LOCATE_X, COMBO_TEXT_LOCATE_Y, 0);

		//	콤보 숫자

		PaintNumber(m_pFieldUiDamageNumAs, MODULE_DAMAGE_NUM_COMBO_NUM, m_nSaveCombo,COMBO_TEXT_LOCATE_X+8, COMBO_TEXT_LOCATE_Y-16, -5,Graphics::RIGHT);
	}
	m_pFieldUiDamageNumAs->SetBlendCustom(false,false,0,0);//블랜딩 해제
}

//--------------------------------------------------------------------------
void FieldUi::AddCombo(int comboCnt)
//--------------------------------------------------------------------------
{
	m_nSaveComboTimer = 0;
//	m_nSaveCombo += comboCnt;
	m_nSaveComboMax += comboCnt;
}


//--------------------------------------------------------------------------
void FieldUi::ProcessCombo()
//--------------------------------------------------------------------------
{
	if(m_nSaveCombo < m_nSaveComboMax)	{m_nSaveCombo++;}//상호 - 콤보의 증가를 보여주기위한 부분으로 추측,,,,
	else if(m_nSaveCombo == m_nSaveComboMax)
	{
		m_nSaveComboTimer++;
	}
	
	if(30 < m_nSaveComboTimer)
	{
		m_nSaveComboTimer--;
		m_nSaveCombo = 0;
		m_nSaveComboMax = 0;
	}
}



