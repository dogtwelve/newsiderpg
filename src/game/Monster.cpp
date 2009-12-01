#include "Monster.h"


int Monster::m_nTotalMonCnt = 0;
int Monster::UniqueIdx = 0;


//--------------------------------------------------------------------------------------
Monster::Monster()
//--------------------------------------------------------------------------------------
{
//	m_nExtraDamage = 0;
	m_nBodySize = 20;

	m_bIsPanic = false;
	m_ActState = MON_AC_NULL;
	ResvAction(MON_AC_READY, 0);
	AI_INIT(this);
	//AIFuncPtr = GETMONAI->Process;

//	SetDirection(SDIR_RIGHT);

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;
	m_nMelee_or_Range = MON_MELEE_TYPE;
//	m_bIsCheckBody = true;

	//	전투 인식 범위
	m_nRange_InBattle	= 100;			
	m_nRange_OutBattle	= 500;			//	전투 해제 범위
	m_nRange_OutAction	= 400;			//	액션 해제 범위(전투도 풀림)
	m_nRange_Heal		= 250;			//	아군의 힐이 필요하다는것을 인식하는 범위
	m_nRange_HealAction	= 150;			//	힐 액션이 가능한 범위

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON01_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON01_WALK_VERTICAL_1;
	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON01_DOWN;
	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON01_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON01_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON01_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON01_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_MON01_WALK_VERTICAL_1;
	
	m_Stet.m_Cri = 10;
	m_Stet.m_nAvoid = 0;
}


//--------------------------------------------------------------------------------------
Monster::~Monster()
//--------------------------------------------------------------------------------------
{
	SUTIL_FreeSprite(pMonAsIns->m_sprite);
	SUTIL_FreeSpriteInstance(_ins_Debuff);
	SUTIL_FreeSpriteInstance(pMonAsIns);

	SAFE_DELETE(m_Physics);
}


//--------------------------------------------------------------------------------------
void Monster::RegistUsingBaseData(List2< struct S_MONSKILL* > *pMonSkillList,
						   List2< struct S_MESSAGE* > *pMonMsgList,
						   void* s__ASpriteSet)
//--------------------------------------------------------------------------------------
{
	m_MonSkillList = pMonSkillList;
	m_MonMsgList = pMonMsgList;

	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // 그림자,효과 이펙트 스프라이트의 포인터

	_ins_Debuff = GL_NEW ASpriteInstance(s_ASpriteSet->pDebuffAs, 100, 200, NULL);//디버프 인마수의계약스

	//	몬스터 스프라이트 로드
	ASprite* TmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_MON, m_nSpriteIdx);

	//	블랜딩 지정
	int blendnum[SPRITE_MON_MAX] = 
	{
		FRAME_MON01_BLEND, FRAME_MON02_BLEND, FRAME_MON03_BLEND, FRAME_MON04_BLEND,	FRAME_MON05_BLEND,
		FRAME_MON06_BLEND, FRAME_MON07_BLEND, FRAME_MON08_BLEND, FRAME_MON09_BLEND, FRAME_MON10_BLEND,
		FRAME_MON11_BLEND, FRAME_MON12_BLEND, FRAME_MON13_BLEND, FRAME_MON14_BLEND, FRAME_MON15_BLEND,
		FRAME_MON16_BLEND, FRAME_MON17_BLEND, FRAME_MON18_BLEND, FRAME_MON19_BLEND, FRAME_MON20_BLEND,
		FRAME_BOSS_1_BLEND,	FRAME_BOSS_2_BLEND,	FRAME_BOSS_3_BLEND, FRAME_BOSS_4_BLEND, FRAME_BOSS_5_BLEND,
		FRAME_BOSS_6_BLEND,	FRAME_BOSS_7_BLEND,	FRAME_MON_BARREL_BLEND
	};

	if(0 != blendnum[m_nSpriteIdx])	{TmpAsprite->SetBlendFrame(blendnum[m_nSpriteIdx]);}


	pMonAsIns = GL_NEW ASpriteInstance(TmpAsprite, 0, 0, NULL);// 0번째 배열, 실사용시는 define 필요

	//	몬스터의 색 변경
}


//--------------------------------------------------------------------------------------
void Monster::SetRegenType(int type, int regenIdx, int baseX, int baseY)
//--------------------------------------------------------------------------------------
{
	m_nRegenIdx = regenIdx;

	switch(type)
	{
		case 1:		//	제 자리에서 멈춰진다.
		{
//			m_AIState = MON_AI_STAND;
			m_StartPos.x = pMonAsIns->m_posX;
			m_StartPos.y = pMonAsIns->m_posY;
			break;
		}
		case 2:		//	접근하면서 시작한다.
		{
//			m_AIState = MON_AI_RETURN_BASE;
			m_StartPos.x = baseX;
			m_StartPos.y = baseY;
			break;
		}
		case 3:		//	전투모드에서 시작한다.
		{
			m_nResvNextAtk = SUTIL_GetRandom()%(m_nAtkMaxCount);
//			m_AIState = MON_AI_APPROACH;
			m_StartPos.x = pMonAsIns->m_posX;
			m_StartPos.y = pMonAsIns->m_posY;
			break;
		}
	}
}


//--------------------------------------------------------------------------------------
void Monster::SetMessage(int type, int temp1, int temp2, int temp3, int temp4, int delay)
//--------------------------------------------------------------------------------------
{
	S_MESSAGE* pMessage = GL_NEW S_MESSAGE();

	pMessage->m_MsgType		= type;
	pMessage->m_nDelay		= delay;
	pMessage->param[0]		= temp1;
	pMessage->param[1]		= temp2;
	pMessage->param[2]		= temp3;
	pMessage->param[3]		= temp4;

	MoveTail(m_MonMsgList);
	m_MonMsgList->Insert_prev(pMessage);
}

//--------------------------------------------------------------------------------------
void Monster::SetMonData(int color, int element, int nameidx, int ptnidx, int gradeidx, int level)
//--------------------------------------------------------------------------------------
{
	UniqueIdx++;

	m_nLevel = level;
	m_nUniqueIdx = UniqueIdx;
	m_PtnIdx = ptnidx;
	m_GradeData = gradeidx;
	m_nMonName = nameidx;

	//	컬러설정
	pMonAsIns->m_pal = color;

//	SUTIL_SetZPosAsprite(pMonAsIns, z);
//	SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);


	//	makeStet
	int RectData[4];
	SUTIL_GetASpriteAniRect(RectData, pMonAsIns->m_sprite, 0, 0);		// 몬스터의 정보
	m_Stet.m_Width = RectData[2]-RectData[0];
	m_Stet.m_Height = RectData[3]-RectData[1];

//	m_Stet.m_Name = MonBaseStet[m_Stet.m_BaseStetNum][STET_NAME];
//	m_Stet.m_Height = MonBaseStet[m_Stet.m_BaseStetNum][STET_HEIGHT]; 
//	m_Stet.m_Elemental = MonBaseStet[m_Stet.m_BaseStetNum][STET_ELEMENT];
	
	//((5+(몬스터랩-1)*4)*3+6+(몬스터랩-1)*1)*10
	//	기본 체력을 구한다.
	m_Stet.m_MaxHp = ((5+(m_nLevel-1)*4)*3+6+(m_nLevel-1)*1)*10;
	
	//	몬스터의 등급 적용(일반~유니크)
	m_Stet.m_MaxHp = (m_Stet.m_MaxHp * MonBaseGradeStet[m_GradeData][GRADE_ADD_HP]) / 100;

	//	몬스터의 종류 적용(몬스터 번호)
	m_Stet.m_MaxHp = (m_Stet.m_MaxHp * MonPtn[m_PtnIdx][STET_HP_RATE]) / 100;

	m_Stet.m_Hp = m_Stet.m_MaxHp;

	m_Stet.m_Atk = ((8+(m_nLevel-1)*3)*15)/8;

//	if(MON_IDX_BIGDOG1 == m_nMonIdx)
//	{
//		BossMon5_1::m_nMaxLegHp = m_Stet.m_Hp/20;
//		BossMon5_1::m_nNowLegHp = BossMon5_1::m_nMaxLegHp;
//		BossMon5_1::m_nMaxCoreHp = m_Stet.m_Hp/20;
//		BossMon5_1::m_nCoreHp = BossMon5_1::m_nMaxCoreHp;
//
//		BossMon5_1::m_nMaxFaceLeftArmHp = m_Stet.m_Hp/20;
//		BossMon5_1::m_nMaxFaceRightArmHp = m_Stet.m_Hp/20;
//
//		BossMon5_1::m_nFaceLeftArmHp = BossMon5_1::m_nMaxFaceLeftArmHp;
//		BossMon5_1::m_nFaceRightArmHp = BossMon5_1::m_nMaxFaceRightArmHp;
//
//		BossMon5_1::m_nMaxFaintHp = m_Stet.m_Hp/20;
//		BossMon5_1::m_nFaintHp = BossMon5_1::m_nMaxFaintHp;
//	}

	m_nElementIdx = element;
}

//--------------------------------------------------------------------------------------
void Monster::SetPosition(int x, int y, int z)
//--------------------------------------------------------------------------------------
{
	pMonAsIns->m_lastX = pMonAsIns->m_posX = x;
	pMonAsIns->m_lastY = pMonAsIns->m_posY = y;
	pMonAsIns->m_posZ = z;
}


//--------------------------------------------------------------------------------------
void Monster::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_nUseAtkNum = SUTIL_GetRandom()%(m_nAtkMaxCount); 

	while(1)
	{
		m_nUseAtkNum = SUTIL_GetRandom()%(m_nAtkMaxCount);

		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime
					= m_Attack[m_nUseAtkNum].MaxCoolTime;
			break;
		}
	}

	m_bIsSuccessAttack = false;
}



////--------------------------------------------------------------------------------------
//void Monster::SetSpriteInstance(ASprite* pAsprite, void* s__ASpriteSet, int color, int x, int y, int z)
////--------------------------------------------------------------------------------------
//{
//}


//--------------------------------------------------------------------------------------
void Monster::ResvAction(int _nActionState, int _isAccept)
//--------------------------------------------------------------------------------------
{
	//if(MON_AC_RCV_DAMAGE == m_ActState)	{if(MON_AC_MOVE == _nActionState){return;}}

//	m_IsAcceptChangeActState = _isAccept;
	m_NextActState = _nActionState;
}




//--------------------------------------------------------------------------------------
int Monster::SetMovingTime(int Moving, int sqrDstValue)
//--------------------------------------------------------------------------------------
{
	if(0 == Moving)	{return 0;}
	int rtnValue = 0;
	while(1)
	{
		rtnValue++;
		if(SQR(rtnValue*Moving) > sqrDstValue)
		{
			return rtnValue;
		}
	}
	return 0;
}


//--------------------------------------------------------------------------------------
bool Monster::ReceiveAttack(Position3D& _Power)
//--------------------------------------------------------------------------------------
{
	if((m_nFeature & FE_DONT_TOUCH))	{return false;}

	Position3D Force;


	if(m_nFeature & FE_HAVE_ONLY_DAMAGE)
	{
		if(MON_AC_DIE == m_ActState)			{return false;}
		if(MON_AC_DIE_AFTER == m_ActState)		{return false;}

		return true;
	}
/*
	if(MON_IDX_HOROS == m_nMonIdx)
	{
		
		if(MON_AC_DOWNED == m_ActState)			{return true;}
		if(MON_AC_ING_DOWN == m_ActState)		{return true;}
		if(MON_AC_DIE == m_ActState)			{return true;}
		if(MON_AC_DIE_AFTER == m_ActState)		{return true;}

		//	인공지능에다 알려준다.
		if(1 > m_Stet.m_Hp)
		{
			ResvAction(MON_AC_ING_DOWN, 1);
			AI_RECEIVE_DEMEGE(this);
			SetMessage(MSG_DE_SUMMONE_BUGS, 0, 0);
		}
		return true;
	}
	else if(SPRITE_MON_BOSS_5 == m_nSpriteIdx || SPRITE_MON_BOSS_6 == m_nSpriteIdx)
//		MON_IDX_BOSS5_1 == m_nMonIdx ||
//		MON_IDX_BOSS5_2 == m_nMonIdx ||
//		MON_IDX_BOSS5_3 == m_nMonIdx ||
//		MON_IDX_BOSS5_4 == m_nMonIdx ||
//		MON_IDX_BOSS5_5 == m_nMonIdx)
	{
		
//		if(MON_AC_DOWNED == m_ActState)			{return true;}
//		if(MON_AC_ING_DOWN == m_ActState)		{return true;}

		if(MON_AC_DIE == m_ActState)			{return true;}
		if(MON_AC_DIE_AFTER == m_ActState)		{return true;}

		//	인공지능에다 알려준다.
//		if(1 > m_Stet.m_Hp && 0 == Monster::m_nExtraDamage)
//		{
//			ResvAction(MON_AC_ING_DOWN, 1);
			AI_RECEIVE_DEMEGE(this);
//			//SetMessage(MSG_DE_SUMMONE_BUGS, 0, 0);
//		}
		return true;
	}
*/
	if(m_nFeature & FE_DONT_HAVE_DOWN)
	{
		if(MON_AC_DOWNED == m_ActState)			{return true;}
		if(MON_AC_ING_DOWN == m_ActState)		{return true;}
		if(MON_AC_DIE == m_ActState)			{return true;}
		if(MON_AC_DIE_AFTER == m_ActState)		{return true;}

//		_Power.Init();
		ResvAction(MON_AC_RCV_GROUND_ATTACK, 1);
		return true;
	}


	//	충격량이 들어오지는 않지만 데미지는 들어가는 상황
	//	예외상황
	if(0 == _Power.Sqr_GetLength())
	{
		if(MON_AC_RCV_HOLDING == m_ActState || MON_AC_RCV_HOLDING_SKY == m_ActState)	{return true;}
	}

	if(MON_AC_RCV_HOLDING_DOWN == m_ActState && m_NextActState != MON_AC_ING_AIRDOWN)
	{
		return true;
	}

	//	맞으면 맞은 카운트를 올려준다.
	m_nAccumulatedHit++;
	m_nHitRate = 0;

	//	인공지능에다 알려준다.
	AI_RECEIVE_DEMEGE(this);

	//	버로우시
	if(MON_ATK_BURROW == m_ActState)	{return true;}
	if(MON_ATK_UNBURROW == m_ActState)	{return true;}
	//	버로우시에는 3대 이상 맞으면 버로우가 풀린다.
	if(MON_ATK_BURROWED == m_ActState)
	{
		if(2 < m_nAccumulatedHit)	{ResvAction(MON_ATK_UNBURROW, 1);}
		return true;;
	}

	//	힘 방향 저장
	m_nResvPower = _Power;
	if(m_CharInfo == NULL)return true;//상호의 미봉책 >ㅂ<;; 해결되심 삭제 부탁
	SetDirection(m_CharInfo->m_Direction * (-1));

//	MC_knlPrintk((signed char*)"force : %d, %d, %d \n", m_nResvPower.x, m_nResvPower.y, m_nResvPower.z);

	//	공중처리
	if(0 > pMonAsIns->m_posZ)
	{
		ResvAction(MON_AC_ING_AIRDOWN, 1);
	}
	else
	{
		if(0 == m_nResvPower.z)
		{
			if(MON_AC_DOWNED == m_ActState || MON_AC_RCV_DOWN_ATTACK == m_ActState)
			{
				if(0 < m_nResvPower.x)			{m_nResvResist.Init(-REG_GROUND,0,0);}
				else if(0 > m_nResvPower.x)		{m_nResvResist.Init(REG_GROUND,0,0);}
				ResvAction(MON_AC_RCV_DOWN_ATTACK, 1);		
			}
			else
			{
				if(0 < m_nResvPower.x)			{m_nResvResist.Init(-REG_GROUND,0,0);}
				else if(0 > m_nResvPower.x)		{m_nResvResist.Init(REG_GROUND,0,0);}
				ResvAction(MON_AC_RCV_GROUND_ATTACK, 1);
			}
		}
		else
		{
			if(-40 >= _Power.z)		{m_nIsUpperAtk = 1;}
			else					{m_nIsUpperAtk = 0;}
			ResvAction(MON_AC_ING_AIRDOWN, 1);
		}
	}


	return true;
}


//--------------------------------------------------------------------------------------
void Monster::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
/*
	if(m_nMonIdx == MON_IDX_BIGDOG1 ||
		m_nMonIdx == MON_IDX_BIGDOG4)		//	보스5의 다리라면
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nNowLegHp -= heroDamage;		//	다리의 누적 데미지를 적용시킨다.
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG2 ||			//	머리 데미지		전면 몸통
		m_nMonIdx == MON_IDX_BIGDOG3 ||
		m_nMonIdx == MON_IDX_BIGDOG6 ||
		m_nMonIdx == MON_IDX_BIGDOG7 ||
		m_nMonIdx == MON_IDX_BIGDOG8	)
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG5)			//	 코어데미지
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nCoreHp -= heroDamage;
		return;
	}

	else if(m_nMonIdx == MON_IDX_BIGDOG9)			//	 전면 왼팔데미지
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nFaceLeftArmHp -= heroDamage;
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG10)			//	 전면 오른팔데미지
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nFaceRightArmHp -= heroDamage;
		return;
	}
//	else if(m_nMonIdx == MON_IDX_BIG_DRAGON1 ||
//		m_nMonIdx == MON_IDX_BIG_DRAGON2 ||
//		m_nMonIdx == MON_IDX_BIG_DRAGON3)			//	 드래곤 보스 피빼기
//	{
//		Monster::m_nExtraDamage += heroDamage;
//		return;
//	}
*/
	m_Stet.m_Hp -= heroDamage;
//	Monster::m_nExtraDamage = 0;
	if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
}


//--------------------------------------------------------------------------------------
int Monster::SND_Damage(int heroLevel, int heroElemental, int heroDefense, int D_index, int nResvNextAtk)
//--------------------------------------------------------------------------------------
{
	if(9999 == nResvNextAtk)	{return -1;}

	heroDefense = 100-heroDefense;

	//	공격력 계산
	int tmpAtk = m_Stet.m_Atk;

	if(0 < nResvNextAtk)
	{
		tmpAtk = (tmpAtk * MonPtn[m_PtnIdx][STET_ATK_1+nResvNextAtk]/100);		//	0 기본어택, 1 첫번째공격, 2두번째공격
	}
	tmpAtk = (tmpAtk * MonBaseGradeStet[m_GradeData][GRADE_ADD_ATK]/100);

	//데미지 계산
	tmpAtk = MAX(tmpAtk/8, (tmpAtk*heroDefense/100));

	//	데미지 보정
	//유저 랩 보다		 <  5랩      : 공격력 -30%
    //		             >= 5랩      : 공격력 +40%
	int tmpLevelDis = m_nLevel - heroLevel;
	if(tmpLevelDis < -5)		{tmpAtk = (tmpAtk * 30) / 100;}
	else if(tmpLevelDis > 5)	{tmpAtk = (tmpAtk * 140) / 100;}


//몬스터가 히어로를 때릴때는 데미지 보정이 없다

//	//	속성에 따른 데미지 보정이 필요함
// 	switch(m_nElementIdx)
// 	{
// 		case MON_ELEMENTAL_WOMAN:
// 			switch(heroElemental)
// 			{
// 				case MON_ELEMENTAL_MAN:	tmpAtk = (tmpAtk * 130/100);	break;
// 				case MON_ELEMENTAL_NEUTRAL :	tmpAtk = (tmpAtk * 40/100);		break;
// 			}
// 			break;
// 		case MON_ELEMENTAL_MAN:
// 			switch(heroElemental)
// 			{
// 				case MON_ELEMENTAL_WOMAN:	tmpAtk = (tmpAtk * 40/100);		break;
// 				case MON_ELEMENTAL_NEUTRAL :	tmpAtk = (tmpAtk * 130/100);	break;
// 			}
// 			break;
// 		case MON_ELEMENTAL_NEUTRAL :
// 			switch(heroElemental)
// 			{
// 				case MON_ELEMENTAL_WOMAN:	tmpAtk = (tmpAtk * 130/100);	break;
// 				case MON_ELEMENTAL_MAN:	tmpAtk = (tmpAtk * 40/100);		break;
// 			}
// 			break;
// 	}

	return tmpAtk;
}

//--------------------------------------------------------------------------------------
void Monster::RCV_Debuff(int Debuff_Type)
//--------------------------------------------------------------------------------------
{
	if(Debuff_Type == 0)//디버프가 없으면 리턴
		return;

	//	이뮴상태라면 디버프를 받지 않는다.
	if((m_nFeature & FE_EMUM))	{return;}

	s_Debuff.All |=  Debuff_Type;//디버프를 계속 추가해 준다
	s_Debuff.color = 0;//디버프 컬러 초기화
	bool novice = true;
	for(int xx = 0;xx<3;xx++){//기존에 디버프중에 중복이 되는지 검사한다.
		if(s_Debuff.stack[xx][0]==Debuff_Type){//이미 있다면 그것을 0번과 위치를 바꿔준다(신규로 취급)
			novice = false;

			short yy = s_Debuff.stack[0][0];
			s_Debuff.stack[0][0] = s_Debuff.stack[xx][0];
			s_Debuff.stack[xx][0] = yy;

			s_Debuff.stack[xx][1] = s_Debuff.stack[0][1];
			s_Debuff.stack[0][1] = 0;//디버프 타이머 초기화
			break;
		}
	}
	if(novice){//중복이 아니라면 0번째에 기록해준다

		if(s_Debuff.stack[2][0])s_Debuff.All -= s_Debuff.stack[2][0];//마지막 버프에 값이 있으면 해제시킨다

		s_Debuff.stack[2][0] = s_Debuff.stack[1][0];
		s_Debuff.stack[2][1] = s_Debuff.stack[1][1];
		s_Debuff.stack[1][0] = s_Debuff.stack[0][0];
		s_Debuff.stack[1][1] = s_Debuff.stack[0][1];
		// 하나씩 뒤로 밀어서 확보된 0번에 값 기록
		s_Debuff.stack[0][0] = Debuff_Type;
		s_Debuff.stack[0][1] = 0;
	}
	switch(Debuff_Type){// 예외적인 처리를 하는부분 
			case DEBUF_WEAK:
				break;
	}
}
//--------------------------------------------------------------------------------------
int Monster::SND_Debuff(int Attack_Type)
//--------------------------------------------------------------------------------------
{
	//	if value have no attack, normaly return zero.
	if(!m_Attack)	{return 0;}

//	if(m_nSpriteIdx == SPRITE_MON_BOSS_5 || m_nSpriteIdx == SPRITE_MON_BOSS_6)
//	{
//
//	}
//	else
//	{
		if(NULL != (DEBUF_WEAK & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_WEAK;}
		if(NULL != (DEBUF_ICE & m_Attack[m_nUseAtkNum].Debuff))			{return DEBUF_ICE;}
		if(NULL != (DEBUF_FREEZE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_FREEZE;}
		if(NULL != (DEBUF_STUN & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_STUN;}
		if(NULL != (DEBUF_STONE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_STONE;}
		if(NULL != (DEBUF_POISON & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_POISON;}
//		if(NULL != (DEBUF_CONFUSE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_CONFUSE;}
		if(NULL != (DEBUF_VAMPIRE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_VAMPIRE;}
		if(NULL != (DEBUF_DE_VAMPIRE & m_Attack[m_nUseAtkNum].Debuff))	{return DEBUF_DE_VAMPIRE;}
//		if(NULL != (DEBUF_MANABURN & m_Attack[m_nUseAtkNum].Debuff))	{return DEBUF_MANABURN;}
		if(NULL != (DEBUF_SILENCE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_SILENCE;}
//	}

	return 0;
}

//--------------------------------------------------------------------------------------
int Monster::SND_Exp(int heroLevel)
//--------------------------------------------------------------------------------------
{
	if((m_nFeature & FE_DONT_GIVE_EXP))	{return 0;}

	// 8*((몬스터랩*2))+10/몬스터랩 + 몬스터 개성 데이터 추가치(%) + 등급 데이터 추가치(%)
	int exp = (8*(m_nLevel*2)) + 10/m_nLevel;
	exp = (exp * MonPtn[m_PtnIdx][STET_ADD_EXP]/100);
	exp = (exp * MonBaseGradeStet[m_GradeData][GRADE_ADD_EXP]/100);

	int tmpLevelDis = m_nLevel - heroLevel;
	if(tmpLevelDis < -4)		{exp = (exp * 30) / 100;}
	else if(tmpLevelDis > 5)	{exp = (exp * 140) / 100;}

	return exp;	
}

//--------------------------------------------------------------------------------------
void Monster::Set_StetData(int level, int specificDataIdx, int gradeDataidx)
//--------------------------------------------------------------------------------------
{

}


//--------------------------------------------------------------------------------------
void Monster::SetDirection(int _dir)
//--------------------------------------------------------------------------------------
{
	m_nDirection = _dir;
	SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
}

//--------------------------------------------------------------------------------------
bool Monster::SetHolding(int HoldType)
//--------------------------------------------------------------------------------------
{
	if(m_nFeature & FE_DONT_HAVE_DOWN)		{return false;}
//	if(MON_IDX_BOSS2_1 == MonBaseStet[m_PtnIdx][STET_BASE])	{return false;}
//	if(MON_IDX_BOSS5_1 == MonBaseStet[m_PtnIdx][STET_BASE])	{return false;}
//	if(MON_IDX_BOSS5_2 == MonBaseStet[m_PtnIdx][STET_BASE])	{return false;}
//	if(MON_IDX_BOSS5_3 == MonBaseStet[m_PtnIdx][STET_BASE])	{return false;}
//	if(MON_IDX_BOSS5_4 == MonBaseStet[m_PtnIdx][STET_BASE])	{return false;}

	if(!m_CharInfo)														{return false;}
	if(SQR(20) < (SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y)))				{return false;}

	if(SDIR_LEFT == m_CharInfo->m_Direction)
	{
		if(pMonAsIns->m_posX > m_CharInfo->m_nPos.x)								{return false;}
	}

	if(SDIR_RIGHT == m_CharInfo->m_Direction)
	{
		if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)								{return false;}
	}

	if(0 == HoldType)	//	일반 잡기
	{
		if(MON_AC_DIE == m_ActState ||
			MON_AC_ING_AIRDOWN == m_ActState ||
			MON_AC_DOWNED == m_ActState ||
			MON_AC_ING_DOWN == m_ActState ||
			MON_AC_RCV_DOWN_ATTACK == m_ActState ||
			MON_AC_RCV_AIR_ATTACK == m_ActState ||
			MON_AC_DIE_AFTER == m_ActState)		{return false;}

		if(SQR(22+m_Stet.m_Width/2) < SQR(pMonAsIns->m_posX - m_CharInfo->m_nPos.x))	{return false;}
		ResvAction(MON_AC_RCV_HOLDING, 0);
		m_bIsPanic = true;
		return true;
	}
	else if(1 == HoldType)		//	공중잡기
	{
		if(MON_AC_DIE == m_ActState ||
//			MON_AC_ING_AIRDOWN == m_ActState ||
			MON_AC_DOWNED == m_ActState ||
			MON_AC_ING_DOWN == m_ActState ||
			MON_AC_RCV_DOWN_ATTACK == m_ActState ||
			MON_AC_RCV_AIR_ATTACK == m_ActState ||
			MON_AC_DIE_AFTER == m_ActState)		{return false;}

		if(SQR(22+m_Stet.m_Width/2) < SQR(pMonAsIns->m_posX - m_CharInfo->m_nPos.x))	{return false;}
		if(-70 < pMonAsIns->m_posZ)												{return false;}
		if(-130 > pMonAsIns->m_posZ)												{return false;}

		ResvAction(MON_AC_RCV_HOLDING_SKY, 0);
		m_bIsPanic = true;
		return true;
	}
	else if(2 == HoldType)
	{
		if(MON_AC_DIE == m_ActState ||
	//		MON_AC_ING_AIRDOWN == m_ActState ||
			MON_AC_DOWNED == m_ActState ||
	//		MON_AC_ING_DOWN == m_ActState ||
	//		MON_AC_RCV_DOWN_ATTACK == m_ActState ||
	//		MON_AC_RCV_AIR_ATTACK == m_ActState ||
			MON_AC_DIE_AFTER == m_ActState)		{return false;}

		if(SQR(44+m_Stet.m_Width/2) < SQR(pMonAsIns->m_posX - m_CharInfo->m_nPos.x))	{return false;}
		ResvAction(MON_AC_RCV_HOLDING_DOWN, 0);
		m_bIsPanic = true;
		return true;
	}

	return false;
}


//--------------------------------------------------------------------------------------
void Monster::RemoveSkillList(int searchstate, int _skillnum, void* _who)
//--------------------------------------------------------------------------------------
{
	if(m_ActState == searchstate)	{return;}

	MoveHead(m_MonSkillList);
	MoveNext(m_MonSkillList);
	while(NotEndList(m_MonSkillList))
	{
		if(_skillnum == GetData(m_MonSkillList)->skillnum)
		{
			if(GetData(m_MonSkillList)->who == _who)
			{
				GetData(m_MonSkillList)->lifeTime = 0;
			}
		}
		MoveNext(m_MonSkillList);
	}
}


//--------------------------------------------------------------------------------------
void Monster::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;

		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}
	
	//	내부 프로세서를 돌린다.
	if(!ExtProcess())
	{
		BaseProcess();

		if(false == m_bIsPanic)
		{
			AI_PROCESS(this);
		}
	}

	

//	// 좌표를 업데이트 시켜준다.
//	SUTIL_SetXPosAsprite(pMonAsIns, pMonAsIns->m_posX);
//	SUTIL_SetYPosAsprite(pMonAsIns, pMonAsIns->m_posY);
//	SUTIL_SetZPosAsprite(pMonAsIns, pMonAsIns->m_posZ);
}

//--------------------------------------------------------------------------------------
bool Monster::BaseProcess()
//--------------------------------------------------------------------------------------
{
	//	보스들의 경우는 다운을 시켜준다.
	if((m_nFeature & FE_DONT_HAVE_DOWN))
	{
		if(0 == m_Stet.m_Hp)
		{
			m_Stet.m_Hp--;
			ResvAction(MON_AC_ING_DOWN, 0);
			return true;
		}
	}

	// animation step update
	switch(m_ActState)
	{
		default:									{return false;}
		case MON_AC_READY:
		//-----------------------------------------------------------------------
		{
			if(8 < m_nTimer)	{ResvAction(MON_AC_STAND, 0);}
			return true;
		}
		case MON_AC_RCV_HOLDING_SKY:
		case MON_AC_STAND:
		case MON_AC_RCV_HOLDING_DOWN:
		case MON_AC_RCV_HOLDING:
		case MON_AC_RCV_DOWN_ATTACK:
		case MON_AC_ING_DOWN:
		case MON_AC_RCV_AIR_ATTACK:
		case MON_AC_AWAK:
		case MON_AC_RCV_GROUND_ATTACK:				{break;}
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_RUN:
		case MON_AC_MOVE:
		case MON_AC_BEHOLD:
		case MON_AC_RUN_BEHOLD:
		//-----------------------------------------------------------------------
		{
			//	이전 에니의 프레임의 이동량을 가져온다.
			int off = (pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule-1] + pMonAsIns->m_nCrtFrame) * 5;
			int nMove =  pMonAsIns->m_sprite->_aframes[off + 3];

			//	이동량이 있을경우만 이동해준다.
			if(0 < nMove)
			{
				int nTotalMoveCount = SetMovingTime(nMove, m_nMoveVec.Sqr_GetLength());
				Position3D m_nDstVec;

				//	한번에 이동할수 있는 거리라면
				if(1 >= nTotalMoveCount)
				{
					m_nDstVec = m_nMoveVec;
				}
				else
				{
					m_nDstVec= ((((m_nMoveVec)*1000)/nTotalMoveCount)/1000);
				}
				pMonAsIns->m_posX += m_nDstVec.x;
				pMonAsIns->m_posY += m_nDstVec.y;
				pMonAsIns->m_posZ += m_nDstVec.z;
//				m_nPos = m_nPos + m_nDstVec;

				//	좌표 수정(y값이 넘어가지 않도록 한다.)
				if(255 < pMonAsIns->m_posY)	{pMonAsIns->m_posY = 255;}
				if(180 > pMonAsIns->m_posY)	{pMonAsIns->m_posY = 180;}

				m_nMoveVec = m_nMoveVec - m_nDstVec;
			}

			//	이동거리가 끝이라면 stand상태로 돌아간다.
//			if(0 == m_nMoveVec.Sqr_GetLength())
//			{
//				ResvAction(MON_AC_STAND, 0);
//			}

//			if(1 > m_Stet.m_Hp)
//			{
//				ResvAction(MON_AC_ING_DOWN, 0);
//			}

			break;
		}
		case MON_AC_ING_AIRDOWN:
		//-----------------------------------------------------------------------
		{
			int tmpAniState = 4;

			if(0 > m_nPhysicsPos.z)													//	up
			{
				if(1 == m_nIsUpperAtk)
				{
					tmpAniState = 0;
				}
				else
				{
					tmpAniState = 3;
				}
			}
			else if(0 < m_nPhysicsPos.z)	
			{
				m_nIsUpperAtk = 0;
				if(0 == (pMonAsIns->m_posZ))													//	bounce
				{
					m_Physics->SaveGrAccel.z = UP_GRV;
					m_Physics->setGrForce(m_Physics->SaveGrAccel);
					m_Physics->setRebound();
					if(-20 < m_Physics->SaveAccel.z)
					{
						tmpAniState = 4;
					}
					else
					{
						tmpAniState = 2;
					}		//	after bounce
				}
				else
				{
					m_Physics->SaveGrAccel.z = DOWN_GRV;
					m_Physics->setGrForce(m_Physics->SaveGrAccel);
					tmpAniState = 1;
				}
			}
			else
			{
				if(0 != (pMonAsIns->m_posZ))
				{
					if(1 == m_nIsUpperAtk)
					{
						tmpAniState = 0;
					}
					else
					{
						tmpAniState = 3;
					}
				}
			}

			if(tmpAniState != m_nAniIndex)
			{
				m_nAniIndex = tmpAniState;
				SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[MON_AC_ING_AIRDOWN] + m_nAniIndex);
			}
			break;
		}
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			m_nFeature |= FE_DONT_TOUCH;
			break;
		}
		case MON_AC_DIE_AFTER:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{

			break;
		}
	}

	//	에니메이션을 업데이트해준다.
	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			default:	{break;}
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				if(14 < m_nTimer)
				{
					ResvAction(MON_AC_DIE_AFTER, 0);
				}
				break;
			}
			case MON_AC_DOWNED:
			//-----------------------------------------------------------------------
			{
				if(1 > m_Stet.m_Hp)
				{
					ResvAction(MON_AC_DIE, 0);
				}
				else
				{
					// 패닉상태를 풀어준다.
					m_bIsPanic = false;
					ResvAction(MON_AC_AWAK, 0);
				}
				break;
			}
			case MON_AC_STAND:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DOWNED, 0);		break;}
			case MON_AC_AWAK:				{ResvAction(MON_AC_STAND, 0);		break;}
			case MON_AC_RCV_DOWN_ATTACK:	{ResvAction(MON_AC_DOWNED, 0);		break;}
			case MON_AC_RCV_AIR_ATTACK:		{ResvAction(MON_AC_ING_AIRDOWN, 0);	break;}
			case MON_AC_RCV_HOLDING:
			case MON_AC_RCV_HOLDING_SKY:	{ResvAction(MON_AC_DOWNED, 0);		break;}
			case MON_AC_RCV_HOLDING_DOWN:	{ResvAction(MON_AC_ING_AIRDOWN, 0);	break;}

			case MON_AC_READY:
			//-----------------------------------------------------------
			{
//				if(0 <= pMonAsIns->m_posZ)
//				{
//					pMonAsIns->m_posZ = 0;
					ResvAction(MON_AC_STAND, 0);
//				}
				break;
			}
			case MON_AC_ING_AIRDOWN:
			//-----------------------------------------------------------
			{
				if(4 == m_nAniIndex)
				{
					ResvAction(MON_AC_DOWNED, 0);
				}
				break;
			}
			case MON_AC_RCV_GROUND_ATTACK:
			//-----------------------------------------------------------
			{
				if(0 < m_Stet.m_Hp)		{ResvAction(MON_AC_STAND, 0);}
				else					{ResvAction(MON_AC_ING_DOWN, 0);}
				break;
			}

		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
void Monster::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	if(MON_AC_READY == m_ActState)
	{
		SUTIL_Paint_Frame(_ins_Debuff->m_sprite ,FRAME_WEFFECT_JOIN_SMALL+(m_nTimer%4) , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns),0);
	}

	if(MON_AC_READY != m_ActState || 5 < m_nTimer)
	{
		//	paint shadow
		//int tmpx = pMonAsIns->Get_AFrameXZ();
		//int tmpy = tmpx%100000;
		//tmpx = tmpx/100000; 


		/*pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);

		SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
		SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

		SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);*/
		SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

		//	paint Debuff
		Paint_Debuff(tmpx , tmpz);
	}
}



//--------------------------------------------------------------------------------------
void Monster::GetMessage()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
void Monster::SetAction(int _nActionState)
//--------------------------------------------------------------------------------------
{
	//	에니메이션의 마지막 좌표를 확정짓는다.
	//SUTIL_UpdateTempXYAsprite(pMonAsIns, APPLY_X|APPLY_Z);

	//	갱신시 특이사항을 기록한다. (에니 좌표 보정)
	switch(m_ActState)
	{
		case MON_AC_RCV_GROUND_ATTACK:
		//----------------------------------------------------------------------
		{
			//	떠있는 몬스터들때문에 z값을 0으로 셋팅한다.
			SUTIL_SetZPosAsprite(pMonAsIns, 0);	
			break;
		}
	}

	//	최신 좌표를 갱신받는다.
//	pMonAsIns->m_posX = SUTIL_GetXPosAsprite(pMonAsIns);
//	pMonAsIns->m_posY = SUTIL_GetYPosAsprite(pMonAsIns);
//	pMonAsIns->m_posZ = SUTIL_GetZPosAsprite(pMonAsIns);

	//	변수 초기화
	m_nTimer = 0;
	m_nAniIndex = 0;
	SUTIL_SetLoopAsprite(pMonAsIns, false);

	//	물리 초기화
	m_Physics->initForce();

	//	중력 셋팅
	Position3D Force;
	Force.Init(0,0,UP_GRV);
	m_Physics->setGrForce(Force);

	//	예약된 힘 셋팅
	m_Physics->setForce(m_nResvPower);
	m_nResvPower.Init();

	//  예약된 저항 셋팅
	m_Physics->setReForce(m_nResvResist);
	m_nResvResist.Init();

	//	액션을 셋팅한다.
	m_ActState = _nActionState;

	if(!ExtSetAction())	{BaseSetAction();}
	
	
}

//--------------------------------------------------------------------------------------
bool Monster::BaseSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:									{return false;}
//		case MON_AC_READY:
//		//-----------------------------------------------------------
//		{
//			SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[m_ActState]);
//			SUTIL_SetLoopAsprite(pMonAsIns, true);

			//	떨어지는 값을 셋팅해준다.
//			Position3D Force;
//			Force.Init(0,0,UP_GRV+15);
//			m_Physics->setGrForce(Force);
//			break;
//		}
		case MON_AC_STAND:
		case MON_AC_READY:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[m_ActState]);
//			SUTIL_SetLoopAsprite(pMonAsIns, true);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)	{SetDirection(SDIR_RIGHT);}
			else											{SetDirection(SDIR_LEFT);}

			break;
		}
		case MON_AC_RUN:
		case MON_AC_MOVE:
		case MON_AC_BEHOLD:	
		case MON_AC_RUN_BEHOLD:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[m_ActState]);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			
			//	방향을 정해준다.
			if(MON_AC_BEHOLD == m_ActState)
			{
				if(m_CharInfo->m_nPos.x < pMonAsIns->m_posX)			{SetDirection(SDIR_LEFT);}
				else if(m_CharInfo->m_nPos.x > pMonAsIns->m_posX)	{SetDirection(SDIR_RIGHT);}
			}
			else
			{
				if(0 < m_nMoveVec.x)		{SetDirection(SDIR_RIGHT);}
				else if(0 > m_nMoveVec.x)	{SetDirection(SDIR_LEFT);}
			}
			break;
		}
		case MON_AC_AWAK:
		case MON_AC_ING_DOWN:
		case MON_AC_ING_AIRDOWN:
		case MON_AC_DOWNED:
		case MON_AC_RCV_GROUND_ATTACK:
		case MON_AC_RCV_DOWN_ATTACK:
		case MON_AC_DIE_AFTER:
		case MON_AC_RCV_AIR_ATTACK:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[m_ActState]);
			break;
		}
		case MON_AC_RCV_HOLDING_DOWN:
		case MON_AC_RCV_HOLDING_SKY:
		case MON_AC_RCV_HOLDING:
		//-----------------------------------------------------------
		{
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pMonAsIns, m_nUsingImgIdx[m_ActState]);
			SetDirection(m_CharInfo->m_Direction);

			//	좌표를 강제적으로 셋팅해준다.
//			pMonAsIns->m_posX = SUTIL_SetXPosAsprite(pMonAsIns, m_CharInfo->m_nPos.x);
//			pMonAsIns->m_posY = SUTIL_SetYPosAsprite(pMonAsIns, m_CharInfo->m_nPos.y-1);
//			pMonAsIns->m_posZ = SUTIL_SetZPosAsprite(pMonAsIns, m_CharInfo->m_nPos.z);

			SUTIL_SetXPosAsprite(pMonAsIns, m_CharInfo->m_nPos.x);
			SUTIL_SetYPosAsprite(pMonAsIns, m_CharInfo->m_nPos.y-1);
			SUTIL_SetZPosAsprite(pMonAsIns, m_CharInfo->m_nPos.z);
			break;
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
void Monster::Paint_Debuff(int drawX,int drawZ)
//--------------------------------------------------------------------------------------
{// 디버프 이펙트를 그릴때

	if(!s_Debuff.All)//디버프가 하나도 걸려있지않다면 
		return;


	_ins_Debuff->m_posX = drawX;
	_ins_Debuff->m_posY = pMonAsIns->m_posY;
	char m_tempZ = drawZ;//pMonAsIns->m_sprite->_aframes[((pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule] + pMonAsIns->m_nCrtFrame) * 5)+3] & 0xFF;
	_ins_Debuff->m_posZ = m_tempZ;
	//_ins_Debuff->m_posZ = m_posZ - HERO_HEIGHT;

	_ins_Debuff->CameraX = pMonAsIns->CameraX;
	_ins_Debuff->CameraY = pMonAsIns->CameraY;




	for(int xx =0;xx<3;xx++){//디버프의 해제와 그래픽적인 구현
		if(xx < 2 && s_Debuff.stack[xx][0] == 0){
			s_Debuff.stack[xx][0] = s_Debuff.stack[xx+1][0];
			s_Debuff.stack[xx][1] = s_Debuff.stack[xx+1][1];
			s_Debuff.stack[xx+1][0] = 0;
			s_Debuff.stack[xx+1][1] = 0;
		}


		if(s_Debuff.stack[xx][0]){
			switch(s_Debuff.stack[xx][0]){
					case DEBUF_WEAK://약화
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 16;//31 이 넘으면 안됨
							s_Debuff.color = (s_Debuff.color+1)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12)+(s_Debuff.color<<7) : ((pxx-s_Debuff.color)<<12)+((pxx-s_Debuff.color)<<7)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
						}
						if(s_Debuff.stack[xx][1] > 100){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}

						break;
// 					case DEBUF_ICE://아이스
// 						if(xx == 0 ){// 0번째(최신) 디버프이며
// 							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_COLD){// 디버프 타이머가 지금 시작 되었다면
// 								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_COLD);
// 								_ins_Debuff->m_bLoop = true;
// 							}
// 							int pxx = 31;//31 이 넘으면 안됨
// 							s_Debuff.color = (s_Debuff.color+2)%pxx;
// 							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<1)); 
// 							//int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<11)+(s_Debuff.color<<6)+(s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<11)+((pxx-s_Debuff.color)<<6)+((pxx-s_Debuff.color)<<1)); 
// 							pMonAsIns->SetBlendCustom(true,false,7,pyy);
// 						}
// 						if(s_Debuff.stack[xx][1] > 30){//디버프가 종료 되었다면
// 							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
// 							s_Debuff.stack[xx][0] = 0;
// 							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
// 						}
// 						break;
					case DEBUF_FREEZE://동결
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_FREEZ_1 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_FREEZ_3){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_FREEZ_1);
								_ins_Debuff->m_bLoop = false;
							}else if(s_Debuff.stack[xx][1] == 50-2){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_FREEZ_3);
								_ins_Debuff->m_bLoop = false;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_STUN://마수의계약
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_STUN){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_STUN);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//머리에서 그려준다
						}
						if(s_Debuff.stack[xx][1] > 20){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_STONE://석화
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(true,false,8,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_POISON://독
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_VENOM){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_VENOM);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 16;//31 이 넘으면 안됨
							s_Debuff.color = (s_Debuff.color+1)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<7) : ((pxx-s_Debuff.color)<<7)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//머리에서 그려준다

						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
// 					case DEBUF_CONFUSE://혼란
// 						if(xx == 0 ){// 0번째(최신) 디버프이며
// 							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_CHAOS){// 디버프 타이머가 지금 시작 되었다면
// 								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_CHAOS);
// 								_ins_Debuff->m_bLoop = true;
// 							}
// 							int pxx = 16;//31 이 넘으면 안됨
// 							s_Debuff.color = (s_Debuff.color+1)%pxx;
// 							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12)+(s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<12)+((pxx-s_Debuff.color)<<1));  
// 							pMonAsIns->SetBlendCustom(true,false,7,pyy);
// 							_ins_Debuff->m_posZ -= HERO_HEIGHT;//머리에서 그려준다
// 						}
// 						if(s_Debuff.stack[xx][1] > 100){//디버프가 종료 되었다면
// 							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
// 							s_Debuff.stack[xx][0] = 0;
// 							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
// 						}
// 						break;
					case DEBUF_VAMPIRE://흡혈 A
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_DE_VAMPIRE://흡혈 B
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 28;//31 이 넘으면 안됨
							s_Debuff.color = (s_Debuff.color+2)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12) : ((pxx-s_Debuff.color)<<12)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
// 					case DEBUF_MANABURN://마나연소
// 						if(xx == 0 ){// 0번째(최신) 디버프이며
// 							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_MANABURN){// 디버프 타이머가 지금 시작 되었다면
// 								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_MANABURN);
// 								_ins_Debuff->m_bLoop = true;
// 							}
// 							pMonAsIns->SetBlendCustom(false,false,0,0);
// 						}
// 						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
// 							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
// 							s_Debuff.stack[xx][0] = 0;
// 							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
// 						}
// 						break;
					case DEBUF_SILENCE://침묵
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_SILENCE){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_SILENCE);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//머리에서 그려준다
						}
						if(s_Debuff.stack[xx][1] > 50){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;

					case DEBUF_KEY_SEAL://키입력불가 디버프
						if(xx == 0 ){// 0번째(최신) 디버프이며
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// 디버프 타이머가 지금 시작 되었다면
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//머리에서 그려준다
						}
						if(s_Debuff.stack[xx][1] > 2){//디버프가 종료 되었다면
							s_Debuff.All -= s_Debuff.stack[xx][0];//디버프 해제
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
			}
			s_Debuff.stack[xx][1]++;
		}

	}

	_ins_Debuff->UpdateSpriteAnim();
	SUTIL_PaintAsprite(_ins_Debuff,S_INCLUDE_SORT);

}








//--------------------------------------------------------------------------------------
//void Monster::AiProcess()
//--------------------------------------------------------------------------------------
//{
///	AI_PROCESS(this);
//}









//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_GHOST::Mon_GHOST()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_GHOST;
	m_nMonIdx = MON_IDX_GHOST;
	m_nFeature = FE_NORMAL_MONSTER;

	//BaseAction(MON_AC_READY);

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;

	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 40;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);

//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 40;

	m_Attack[1].Name = MON_ATK_MELEE2;

	m_Attack[1].AtkRect.x1 = 30;
	m_Attack[1].AtkRect.x2 = 60;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);


//	m_Attack[1].MinScope = 30;
//	m_Attack[1].MaxScope = 60;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_GHOST::~Mon_GHOST()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_GHOST::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_GHOST::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON01_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{SetDirection(SDIR_RIGHT);}
			else										{SetDirection(SDIR_LEFT);}
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON01_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{SetDirection(SDIR_RIGHT);}
			else										{SetDirection(SDIR_LEFT);}
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_SUNFLOWER::Mon_SUNFLOWER()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;	

	m_nSpriteIdx = SPRITE_MON_SUNFLOWER;
	m_nMonIdx = MON_IDX_SUNFLOWER;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 70;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);


	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 70;
//	m_Attack[1].MaxScope = 110;

	m_Attack[1].AtkRect.x1 = 40;
	m_Attack[1].AtkRect.x2 = 120;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);


//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_SUNFLOWER::~Mon_SUNFLOWER()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_SUNFLOWER::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_SUNFLOWER::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON02_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON02_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_SLIME::Mon_SLIME()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_SLIME;
	m_nMonIdx = MON_IDX_SLIME;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 30;

	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 30;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);

	m_Attack[1].Name = MON_ATK_FIREBALL;
//	m_Attack[1].MinScope = 70;
//	m_Attack[1].MaxScope = 110;

	m_Attack[1].AtkRect.x1 = 70;
	m_Attack[1].AtkRect.x2 = 110;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_SLIME::~Mon_SLIME()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_SLIME::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_FIREBALL:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_FIREBALL:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_SLIME::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON03_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_FIREBALL:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON03_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON03_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(30*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 5;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_CROWN_BOMB::Mon_CROWN_BOMB()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	//	분열이 가능한 상태로 만든다.
	isPassbleClone = true;
	m_Clonetimer = 0;

	m_nSpriteIdx = SPRITE_MON_CROWNBOMB;
	m_nMonIdx = MON_IDX_CROWN_BOMB;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(COMMON_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 30;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 30;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);

	m_Attack[1].Name = MON_ATK_RANGE1;
//	m_Attack[1].MinScope = 50;
//	m_Attack[1].MaxScope = 180;
	m_Attack[1].AtkRect.x1 = 50;
	m_Attack[1].AtkRect.x2 = 180;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);

//	ResvAction(MON_ATK_SPECIAL1, 0);

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_CROWN_BOMB::~Mon_CROWN_BOMB()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_CROWN_BOMB::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	레이져 빔일 경우 스킬리스트에서 제외시켜준다.
	RemoveSkillList(MON_ATK_RANGE1, 0, (void*)this);

	switch(m_ActState)
	{
		default:
		{
			m_Clonetimer = 0;
			return false;
		}
		case MON_ATK_SPECIAL1:		//	분열
		//-----------------------------------------------------------
		{
			m_Clonetimer++;
			if(11 == m_Clonetimer)
			{
				SetMessage(MSG_MON4_CLONE, pMonAsIns->m_posX+15, pMonAsIns->m_posY, m_nDirection, 0, 5);
				//pMonAsIns->m_posX += 20;
			}
			break;
		}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			m_Clonetimer = 0;
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			case MON_ATK_SPECIAL1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}


	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_CROWN_BOMB::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_SPECIAL1:		//	분열
		//-----------------------------------------------------------
		{
			isPassbleClone = false;
			m_Clonetimer = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON04_CLONE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON04_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON04_RANGE_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);

			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;

			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON04_BULLET_1);
			SUTIL_SetLoopAsprite(tmpAsIns, true);

			SUTIL_SetXPosAsprite(tmpAsIns, m_CharInfo->m_nPos.x);
			//SUTIL_SetXPosAsprite(tmpAsIns, m_CharInfo->m_nPos.x+(-5*m_nDirection) );
			SUTIL_SetYPosAsprite(tmpAsIns, m_CharInfo->m_nPos.y );
			SUTIL_SetZPosAsprite(tmpAsIns, 0 );
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 8;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 5;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 0;
			tmpMonSkill->damagetime = 2;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
//			pWaterHand = tmpMonSkill;
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_BEAR::Mon_BEAR()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_BEAR;
	m_nMonIdx = MON_IDX_BEAR;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 30;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 30;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);

	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 100;
	m_Attack[1].AtkRect.x1 = 60;
	m_Attack[1].AtkRect.x2 = 100;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].Debuff = DEBUF_STUN;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_BEAR::~Mon_BEAR()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_BEAR::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_BEAR::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON05_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON05_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_TREE::Mon_TREE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_TREE;
	m_nMonIdx = MON_IDX_TREE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 90;
	m_Attack[1].AtkRect.x2 = 200;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 90;
//	m_Attack[1].MaxScope = 200;



//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_TREE::~Mon_TREE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_TREE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_TREE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON06_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON06_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON06_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(13*m_nDirection));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)+(3));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 3;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON06_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(16*m_nDirection));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-(7));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 6;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_SHREK::Mon_SHREK()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_SHREK;
	m_nMonIdx = Mon_IDX_SHREK;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 60;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 60;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 90;
	m_Attack[1].AtkRect.x2 = 300;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 90;
//	m_Attack[1].MaxScope = 300;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_SHREK::~Mon_SHREK()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_SHREK::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_SHREK::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON07_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON07_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON07_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(60*m_nDirection));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)+(3));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 7;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
	}
	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_GOLLUM::Mon_GOLLUM()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_GOLLUM;
	m_nMonIdx = MON_IDX_GOLLUM;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_1;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 80;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 80;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 80;
	m_Attack[1].AtkRect.x2 = 200;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 80;
//	m_Attack[1].MaxScope = 200;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_GOLLUM::~Mon_GOLLUM()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_GOLLUM::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	//AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_GOLLUM::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON08_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON08_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON08_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(5*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 3;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_SHRIMP::Mon_SHRIMP()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_SHRIMP;
	m_nMonIdx = MON_IDX_SHRIMP;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 120;
	m_Attack[1].AtkRect.x2 = 180;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 120;
//	m_Attack[1].MaxScope = 180;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_SHRIMP::~Mon_SHRIMP()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_SHRIMP::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	레이져 빔일 경우 스킬리스트에서 제외시켜준다.
//	RemoveSkillList(MON_ATK_LASERBEAM, 1, (void*)this);

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}


	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_SHRIMP::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON09_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON09_RANGE_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);

			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;
			for(int loop = 0; loop < MON9_LASERBEAM_COUNT; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON09_BEAM_1);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+((67)*m_nDirection)+(MON9_LASERBEAM_SIZE*loop*m_nDirection));
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 6;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 5;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 1;
				tmpMonSkill->damagetime = 6;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

			}

			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_BEE::Mon_BEE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_BEE;
	m_nMonIdx = MON_IDX_BEE;
	m_nFeature = FE_NORMAL_MONSTER;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 20;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 20;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 35;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 35;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_BEE::~Mon_BEE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_BEE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_BEE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON10_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON10_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_ELF_FIRE::Mon_ELF_FIRE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_ELF;
	m_nMonIdx = MON_IDX_ELF_FIRE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_1;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 1;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_RANGE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 200;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 200;

//	m_Attack[1].Name = MON_ATK_ICE_WAVE;
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 110;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	//	test 힐
	//ResvAction(MON_ATK_RANGE2, 0);

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_ELF_FIRE::~Mon_ELF_FIRE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_ELF_FIRE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_RANGE2:	//	heal
		//-----------------------------------------------------------
		{
			m_nHealTimer++;

			if(3 == m_nHealTimer)
			{
				SetMessage(MSG_ELF_HEAL, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nUniqueIdx, 200, 0);
				// > 메세지로 힐을 시킨다.
			}
			break;
		}
	}


	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_RANGE2:	//	heal
			//-----------------------------------------------------------
			{
				m_nHealTimer = 0;
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_ELF_FIRE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON11_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON11_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(20*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 5;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 0;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_RANGE2:	//	heal
		//-----------------------------------------------------------
		{
			m_nHealTimer = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON11_HEAL_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

//			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
//			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON11_BULLET_1);
//			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
//			SUTIL_SetLoopAsprite(tmpAsIns, true);
//			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(5*m_nDirection));
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
//			SUTIL_UpdateTimeAsprite(tmpAsIns);
//
//			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
//			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
//			tmpMonSkill->type = SKILL_REMOVE;
//			tmpMonSkill->lifeTime = 10;
//			tmpMonSkill->Damage = 10;
//			tmpMonSkill->Delay = 5;
//			tmpMonSkill->who = (void*)this;
//			//tmpMonSkill->skillnum = m_ActState;
//			tmpMonSkill->skillnum = 0;
//			tmpMonSkill->damagetime = 1;
//			MoveTail(m_MonSkillList);
//			m_MonSkillList->Insert_prev(tmpMonSkill);
//			m_nSkillCount++;
			return true;
		}

	}

	return false;
}


//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_ELF_ICE::Mon_ELF_ICE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_ELF;
	m_nMonIdx = MON_IDX_ELF_ICE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_1;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 1;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_RANGE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 200;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 200;


//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_ELF_ICE::~Mon_ELF_ICE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_ELF_ICE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_RANGE2:	//	heal
		//-----------------------------------------------------------
		{
			m_nHealTimer++;

			if(3 == m_nHealTimer)
			{
				SetMessage(MSG_ELF_TOTAL_HEAL, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nUniqueIdx, 200, 0);
				// > 메세지로 힐을 시킨다.
			}
			break;
		}
	}


	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_RANGE1:
			case MON_ATK_RANGE2:
			//-----------------------------------------------------------
			{
				m_nHealTimer = 0;
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_ELF_ICE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON11_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON11_BULLET_2);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(5*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 5;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_RANGE2:	//	heal
		//-----------------------------------------------------------
		{
			m_nHealTimer = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON11_HEAL_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

//			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
//			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON11_BULLET_1);
//			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
//			SUTIL_SetLoopAsprite(tmpAsIns, true);
//			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(5*m_nDirection));
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
//			SUTIL_UpdateTimeAsprite(tmpAsIns);
//
//			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
//			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
//			tmpMonSkill->type = SKILL_REMOVE;
//			tmpMonSkill->lifeTime = 10;
//			tmpMonSkill->Damage = 10;
//			tmpMonSkill->Delay = 5;
//			tmpMonSkill->who = (void*)this;
//			//tmpMonSkill->skillnum = m_ActState;
//			tmpMonSkill->skillnum = 0;
//			tmpMonSkill->damagetime = 1;
//			MoveTail(m_MonSkillList);
//			m_MonSkillList->Insert_prev(tmpMonSkill);
//			m_nSkillCount++;
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_FIRE::Mon_FIRE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_FIRE;
	m_nMonIdx = MON_IDX_FIRE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 3;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 60;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 60;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 60;
	m_Attack[1].AtkRect.x2 = 120;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 120;

	m_Attack[2].Name = MON_ATK_BURROW;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 40;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 40;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_FIRE::~Mon_FIRE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_FIRE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	자기장일 경우 스킬리스트에서 제외시켜준다.
	RemoveSkillList(MON_ATK_BURROWED, 2, (void*)this);

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_BURROW:
		case MON_ATK_UNBURROW:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_BURROWED:
		//-----------------------------------------------------------------------
		{
			if(60 < m_nTimer)		{ResvAction(MON_ATK_UNBURROW, 0);}
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			case MON_ATK_UNBURROW:
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_BURROW:
			//-----------------------------------------------------------
			{
				ResvAction(MON_ATK_BURROWED, 0);
				break;
			}
			default:	{break;}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_FIRE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON12_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON12_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BURROW:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON12_BURROW);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BURROWED:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON12_BURROWED);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON12_MELEE_3);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 60;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 0;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 2;
			tmpMonSkill->damagetime = 9;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_UNBURROW:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON12_UNBURROW);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_EYE::Mon_EYE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_EYE;
	m_nMonIdx = MON_IDX_EYE;
	m_nFeature = FE_NORMAL_MONSTER;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 50;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 50;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 80;
	m_Attack[1].AtkRect.x2 = 200;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 80;
//	m_Attack[1].MaxScope = 200;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_EYE::~Mon_EYE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_EYE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_EYE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON13_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON13_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON13_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(20*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 4;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_SPEAR::Mon_SPEAR()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_SPEAR;
	m_nMonIdx = MON_IDX_SPEAR;
	m_nFeature = FE_NORMAL_MONSTER;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 110;
	m_Attack[1].AtkRect.x2 = 150;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 110;
//	m_Attack[1].MaxScope = 150;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_SPEAR::~Mon_SPEAR()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_SPEAR::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_SPEAR::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON14_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON14_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_HUMAN_MELEE::Mon_HUMAN_MELEE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_HUMAN;
	m_nMonIdx = MON_IDX_HUMAN_MELEE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON15_STAND_D;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON15_WALK_VERTICAL_1_D;
	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON15_AWAKE_D;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON15_DOWN_D;
	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON15_FLY_1_D;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON15_DOWNED_D;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON15_DAMAGE_1_D;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON15_DOWN_DAMAGE_D;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON15_AIR_DAMAGE_D;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON15_DOWNED_D;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON15_DOWNED_D;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON15_CATCH_1_D;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON15_CATCH_3_D;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON15_CATCH_2_D;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON15_STAND_D;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON15_WALK_VERTICAL_2_D;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_MON15_WALK_VERTICAL_1_D;

	m_nAtkMaxCount = 1;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 55;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 55;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_HUMAN_MELEE::~Mon_HUMAN_MELEE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_HUMAN_MELEE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_HUMAN_MELEE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON15_MELEE_1_D);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}




//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_HUMAN_RANGE::Mon_HUMAN_RANGE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_HUMAN;
	m_nMonIdx = MON_IDX_HUMAN_RANGE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	//	woman mage setting
	//m_nBaseAniIdx = ANIM_MON15_STAND_W;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON15_STAND_W;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON15_WALK_VERTICAL_1_W;
	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON15_AWAKE_W;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON15_DOWN_W;
	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON15_FLY_1_W;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON15_DOWNED_W;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON15_DAMAGE_1_W;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON15_DOWN_DAMAGE_W;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON15_AIR_DAMAGE_W;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON15_DOWNED_W;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON15_DOWNED_W;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON15_CATCH_1_W;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON15_CATCH_3_W;
	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON15_CATCH_2_W;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON15_STAND_W;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON15_WALK_VERTICAL_2_W;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_MON15_WALK_VERTICAL_1_W;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 1;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_RANGE1;
	m_Attack[0].AtkRect.x1 = 50;
	m_Attack[0].AtkRect.x2 = 200;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 50;
//	m_Attack[0].MaxScope = 200;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_HUMAN_RANGE::~Mon_HUMAN_RANGE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_HUMAN_RANGE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}

//--------------------------------------------------------------------------------------
bool Mon_HUMAN_RANGE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON15_RANGE_1_W);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON15_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(10*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 4;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 0;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_LIZARD::Mon_LIZARD()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_LIZARD;
	m_nMonIdx = MON_IDX_LIZARD;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 50;
	m_Attack[1].AtkRect.x2 = 180;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;


	//	m_Attack[1].Name = MON_ATK_RANGE1;
//	m_Attack[1].MinScope = 70;
//	m_Attack[1].MaxScope = 110;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_LIZARD::~Mon_LIZARD()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_LIZARD::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_LIZARD::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON16_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON16_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON16_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(5*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 4;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}

	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_TURTLE::Mon_TURTLE()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_TURTLE;
	m_nMonIdx = MON_IDX_TURTLE;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_1;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 90;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 50;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 70;
//	m_Attack[1].MaxScope = 110;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON17_START;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_TURTLE::~Mon_TURTLE()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_TURTLE::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_TURTLE::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON17_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON17_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_BUG::Mon_BUG()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 8;

	m_nSpriteIdx = SPRITE_MON_BUG;
	m_nMonIdx = MON_IDX_BUG;
	m_nFeature = FE_NORMAL_MONSTER | FE_DONT_HAVE_DOWN | FE_DONT_HAVE_ITEM;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 1;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_4;
//	m_bIsCheckBody = false;

//	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON18_START;
	
//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 7;
	m_nAiPtnData[0] = MON_AI_MOVE_BACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_MOVE_BACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_ATTACK;
}



//--------------------------------------------------------------------------------------
Mon_BUG::~Mon_BUG()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_BUG::ExtProcess()
//--------------------------------------------------------------------------------------
{
	// TEST
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_READY:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_READY:
			case MON_ATK_MELEE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	if(MON_AC_READY != m_ActState)
	{
		AI_PROCESS(this);
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_BUG::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON18_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_READY:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON18_START);
//			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
//			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

	}

	return false;
}


//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_DRILL::Mon_DRILL()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_DIRLL;
	m_nMonIdx = MON_IDX_DRILL;
	m_nFeature = FE_NORMAL_MONSTER | FE_DONT_HAVE_DOWN | FE_DONT_GIVE_EXP | FE_DONT_HAVE_ITEM;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	ResvAction(MON_ATK_MELEE1, 0);

//	m_nAtkMaxCount = 1;
//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);
//
//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_4;
//	m_bIsCheckBody = false;

//	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON19_STAND;
//	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON19_START;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON19_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON19_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON19_END;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON19_END;

	m_nLifeTimer = 100;
//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Mon_DRILL::~Mon_DRILL()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_DRILL::ExtProcess()
//--------------------------------------------------------------------------------------
{
	// TEST
//	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_STAND:
		//-----------------------------------------------------------------------
		{
			m_nLifeTimer--;
			break;
		}
		case MON_ATK_MELEE1:
		case MON_AC_RCV_GROUND_ATTACK:
		case MON_AC_DIE_AFTER:
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_RCV_GROUND_ATTACK:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_STAND:
			//-----------------------------------------------------------------------
			{
				if(1 > m_Stet.m_Hp || 1 > m_nLifeTimer)
				{
					ResvAction(MON_AC_HIDE, 0);
				}
				break;
			}
			case MON_AC_HIDE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER, 0);
				break;
			}
			default:	{break;}
		}
	}

//	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_DRILL::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON19_START);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON19_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		case MON_AC_DIE_AFTER:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON19_END);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}
//==============================================================================================================



//--------------------------------------------------------------------------------------
Mon_BOSS5_DEVIL::Mon_BOSS5_DEVIL()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_KNIGHT;
	m_nMonIdx = MON_IDX_BOSS5_DEVIL;
	m_nFeature = FE_NORMAL_MONSTER | FE_DONT_GIVE_EXP | FE_DONT_HAVE_ITEM;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 120;
	m_Attack[1].AtkRect.x2 = 150;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 120;
//	m_Attack[1].MaxScope = 150;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Mon_BOSS5_DEVIL::~Mon_BOSS5_DEVIL()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_BOSS5_DEVIL::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			//-----------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_BOSS5_DEVIL::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON14_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON14_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}
//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_THUNDERCLOUD::Mon_THUNDERCLOUD()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_THUNDER;
	m_nMonIdx = MON_IDX_THUNDERCLOUD;
	m_nFeature = FE_NORMAL_MONSTER | FE_DONT_HAVE_DOWN | FE_DONT_GIVE_EXP | FE_DONT_HAVE_ITEM;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

//	ResvAction(MON_ATK_MELEE1, 0);

//	m_nAtkMaxCount = 1;
//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);
//
//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].AtkRect.x1 = 0;
//	m_Attack[0].AtkRect.x2 = 10;
//	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
//	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);

	m_nShadowIdx = FRAME_SHADOW_SHADOW_4;
//	m_bIsCheckBody = false;

	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON20_STAND;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON20_START;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON20_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON20_END;
	m_nUsingImgIdx[MON_AC_HIDE]				= ANIM_MON20_END;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON19_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON20_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON19_END;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON19_END;

	m_nLifeTimer = CLOUD_LIFETIME;
//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 1;
	m_nAiPtnData[0] = MON_AI_READY_TO_HIT;
}



//--------------------------------------------------------------------------------------
Mon_THUNDERCLOUD::~Mon_THUNDERCLOUD()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_THUNDERCLOUD::ExtProcess()
//--------------------------------------------------------------------------------------
{
	// TEST
//	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:	{return false;}
//		case MON_AC_READY:
		case MON_AC_STAND:
		//-----------------------------------------------------------------------
		{
			m_nLifeTimer--;
			pMonAsIns->m_posX -= (5);
			pMonAsIns->m_posY -= (5);

			pMonAsIns->m_posX += (SUTIL_GetRandom()%11);
			pMonAsIns->m_posY += (SUTIL_GetRandom()%11);

			if( 0 > pMonAsIns->m_posX)	{pMonAsIns->m_posX = 0;}
			if( MAP_MOVE_UP_Y > pMonAsIns->m_posY)	{pMonAsIns->m_posY = MAP_MOVE_UP_Y;}
			if( Field::m_nFieldSize_X < pMonAsIns->m_posX)	{pMonAsIns->m_posX = Field::m_nFieldSize_X;}
			if( MAP_MOVE_DOWN_Y < pMonAsIns->m_posY)	{pMonAsIns->m_posY = MAP_MOVE_DOWN_Y;}

			break;
		}
//		case MON_ATK_MELEE1:
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
//			case MON_AC_READY:
			case MON_AC_STAND:
			//-----------------------------------------------------------------------
			{
				if(1 > m_Stet.m_Hp || 1 > m_nLifeTimer)
				{
					ResvAction(MON_AC_HIDE, 0);
				}
				else
				{
					ResvAction(MON_AC_STAND, 0);
				}
				break;
			}
//			case MON_ATK_MELEE1:
//			//-----------------------------------------------------------------------
//			{
//				if(1 > m_Stet.m_Hp || 1 > m_nLifeTimer)
//				{
//					ResvAction(MON_AC_HIDE, 0);
//				}
//				else
//				{
//					ResvAction(MON_AC_STAND, 0);
//				}
//				break;
//			}
			case MON_AC_HIDE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER, 0);
				break;
			}
			default:	{break;}
		}
	}

	//AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Mon_THUNDERCLOUD::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
//		case MON_ATK_MELEE1:
//		//-----------------------------------------------------------
//		{
//			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON20_WALK_VERTICAL);
//			m_nDirection = SDIR_RIGHT;
//			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
//			m_Physics->initForce();
//			return true;
//		}
		case MON_AC_HIDE:
		case MON_AC_DIE_AFTER:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON20_END);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}


//========================================================================================



//--------------------------------------------------------------------------------------
Barrel::Barrel()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_BARREL;
	m_nMonIdx = MON_IDX_BARREL;
	m_nFeature = FE_ONLY_OBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_BARREL_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_BARREL_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_BARREL_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_BARREL_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_BARREL_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_BARREL_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_BARREL_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_BARREL_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_BARREL_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Barrel::~Barrel()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Barrel::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Barrel::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}



//==============================================================================================================



//--------------------------------------------------------------------------------------
Stone_big::Stone_big()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_STONE_BIG;
	m_nMonIdx = MON_IDX_STONE_BIG;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_STONE_BIG_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_STONE_BIG_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_STONE_BIG_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_STONE_BIG_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_STONE_BIG_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_STONE_BIG_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Stone_big::~Stone_big()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Stone_big::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Stone_big::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}




//==============================================================================================================



//--------------------------------------------------------------------------------------
Box::Box()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_BOX;
	m_nMonIdx = MON_IDX_BOX;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_BOX_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_BOX_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_BOX_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_BOX_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_BOX_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_BOX_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_BOX_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_BOX_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_BOX_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Box::~Box()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Box::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Box::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}



//==============================================================================================================



//--------------------------------------------------------------------------------------
Knight::Knight()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_KNIGHT;
	m_nMonIdx = MON_IDX_KNIGHT;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_KNIGHT_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_KNIGHT_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_KNIGHT_DOWNED;
	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_KNIGHT_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_KNIGHT_DAMAGE;
	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_KNIGHT_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_KNIGHT_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_KNIGHT_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_KNIGHT_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Knight::~Knight()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Knight::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Knight::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}



//==============================================================================================================



//--------------------------------------------------------------------------------------
Temple_crock_small::Temple_crock_small()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_TMP_CROCK;
	m_nMonIdx = MON_IDX_TEMPLE_CROCK_SMALL;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_TEMPLE_CROCK_STAND_S;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
//	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_STONE_BIG_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_TEMPLE_CROCK_STAND_S;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Temple_crock_small::~Temple_crock_small()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Temple_crock_small::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Temple_crock_small::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}


//==============================================================================================================



//--------------------------------------------------------------------------------------
Temple_crock_big::Temple_crock_big()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_TMP_CROCK;
	m_nMonIdx = MON_IDX_TEMPLE_CROCK_BIG;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_TEMPLE_CROCK_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
//	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_STONE_BIG_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_TEMPLE_CROCK_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Temple_crock_big::~Temple_crock_big()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Temple_crock_big::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Temple_crock_big::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}


//==============================================================================================================



//--------------------------------------------------------------------------------------
Temple_stonebox_small::Temple_stonebox_small()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_TMP_STONEBOX;
	m_nMonIdx = MON_IDX_TEMPLE_STONEBOX_SMALL;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_MON_TEMPLE_STONEBOX_STAND1;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
//	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_STONE_BIG_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_MON_TEMPLE_STONEBOX_STAND1;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Temple_stonebox_small::~Temple_stonebox_small()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Temple_stonebox_small::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Temple_stonebox_small::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}



//==============================================================================================================



//--------------------------------------------------------------------------------------
Temple_stonebox_big::Temple_stonebox_big()
//--------------------------------------------------------------------------------------
{
	m_nSpriteIdx = SPRITE_MON_TMP_STONEBOX;
	m_nMonIdx = MON_IDX_TEMPLE_STONEBOX_BIG;
	m_nFeature = FE_ONLY_BACKOBJECT;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 0;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= MON_IDX_TEMPLE_STONEBOX_BIG;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_MON_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON_MON01_AWAKE;
//	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_MON_STONE_BIG_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON_STONE_BIG_DAMAGE;
//	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_MON_STONE_BIG_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= MON_IDX_TEMPLE_STONEBOX_BIG;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON_MON01_WALK_VERTICAL_2;

//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 80;
//	m_Attack[1].Debuff = DEBUF_POISON;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Temple_stonebox_big::~Temple_stonebox_big()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Temple_stonebox_big::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_ING_DOWN:			{ResvAction(MON_AC_DIE_AFTER, 0);		break;}
			default:	{break;}
		}
	}

	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool Temple_stonebox_big::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return false;
}

//==============================================================================================================





//--------------------------------------------------------------------------------------
BossMon2_1::BossMon2_1()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_BOSS_2;
	m_nMonIdx = MON_IDX_HOROS;
	m_nFeature = FE_NORMAL_MONSTER | FE_DONT_HAVE_DOWN;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 4;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 45;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 45;
	m_Attack[0].MaxCoolTime = 0;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 45;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 45;
	m_Attack[1].MaxCoolTime = 300;
	m_Attack[1].CoolTime = 50;

	m_Attack[2].Name = MON_ATK_RANGE1;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 120;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 120;
	m_Attack[2].MaxCoolTime = 300;
	m_Attack[2].CoolTime = 150;

	m_Attack[3].Name = MON_ATK_SUMMON_BUG;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 120;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 120;
	m_Attack[3].MaxCoolTime = 300;
	m_Attack[3].CoolTime = 200;

/*
	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].MinScope = 0;
	m_Attack[1].MaxScope = 45;

	m_Attack[2].Name = MON_ATK_RANGE1;
	m_Attack[2].MinScope = 0;
	m_Attack[2].MaxScope = 120;

	m_Attack[3].Name = MON_ATK_SUMMON_BUG;
	m_Attack[3].MinScope = 0;
	m_Attack[3].MaxScope = 120;
*/
	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_2_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_2_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_2_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon2_1::~BossMon2_1()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon2_1::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);

	// 좌표를 업데이트 시켜준다.
//	SUTIL_SetXPosAsprite(pMonAsIns, pMonAsIns->m_posX);
//	SUTIL_SetYPosAsprite(pMonAsIns, pMonAsIns->m_posY);
//	SUTIL_SetZPosAsprite(pMonAsIns, pMonAsIns->m_posZ);
}

//--------------------------------------------------------------------------------------
bool BossMon2_1::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			case MON_ATK_RANGE1:
			case MON_ATK_SUMMON_BUG:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			default:	{break;}
		}
	}

//	AI_PROCESS(this);

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon2_1::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
/*
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_2_BULLET_1);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(165*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns)+0);
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 36;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 0;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 36;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
*/
			return true;
		}
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------
		{
/*
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_SUMMON);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	벌레 소환
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, 0, 0, 5);
*/
			return true;
		}
	}

	return false;
}


//==============================================================================================================





//--------------------------------------------------------------------------------------
Mon_DEVIJOHNS::Mon_DEVIJOHNS()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_7;
	m_nMonIdx = MON_IDX_DEVIJOHNS;
	m_nFeature =  FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 3;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);
/*
	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 70;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].MinScope = 40;
	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;

	m_Attack[2].Name = MON_ATK_MELEE3;
	m_Attack[2].MinScope = 0;
	m_Attack[2].MaxScope = 80;
	m_Attack[2].Debuff = DEBUF_STUN;
*/

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_7_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_7_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_7_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_7_WALK_VERTICAL;

	ResvAction(MON_AC_STAND, 0);
}



//--------------------------------------------------------------------------------------
Mon_DEVIJOHNS::~Mon_DEVIJOHNS()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_DEVIJOHNS::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:
		{
			if(1 > m_Stet.m_Hp )
			{
				m_Stet.m_Hp = 0;
				ResvAction(MON_AC_DIE, 0);
				return true;
			}

			return false;
		}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			case MON_ATK_MELEE3:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER_DONT_REMOVE, 0);
				break;
			}
			default:	{break;}
		}
	}

//	AI_PROCESS(this);
	return true;
}


//--------------------------------------------------------------------------------------
void Mon_DEVIJOHNS::Paint()
//--------------------------------------------------------------------------------------
{
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	등장 / 퇴장신에는 정렬이 안되게 한다.
//	if(isPossibleAction)
//	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
//	}
//	else
//	{
//		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
//	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


/*

//--------------------------------------------------------------------------------------
void Mon_DEVIJOHNS::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	m_nDelayTimer--;
	if(MON_AC_STAND == m_ActState && 1 > m_nDelayTimer)
	{
		int seed = SUTIL_GetRandom()%m_nAtkMaxCount;

		while(1)
		{
			seed = (seed+1)%m_nAtkMaxCount;
			if(1 > m_Attack[seed].CoolTime)
			{
				m_nDelayTimer = 100;
				ResvAction(m_Attack[seed].Name, 0);
				break;
			}
		}

		if(0 > m_Stet.m_Hp)
		{
			m_Stet.m_Hp = 0;
			ResvAction(MON_AC_DIE, 0);
		}
	}

	//	보스5는 데미지를 따로 통합해서 관리해서 1번이 가지고 있는다.
	//	초기화는 5번에서 관리한다.

}
*/
//--------------------------------------------------------------------------------------
bool Mon_DEVIJOHNS::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_7_DOWN);
			return true;
		}
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_7_DOWNED);
			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_7_MELEE1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_7_MELEE2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_7_MELEE3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//==============================================================================================================



/*

//--------------------------------------------------------------------------------------
BossBigDragon1::BossBigDragon1()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_1;
	m_nMonIdx = MON_IDX_BIG_DRAGON1;
	m_nFeature =  FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 3;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 70;

	m_Attack[1].Name = MON_ATK_BOSS1_HEAD_MELEE2;
	m_Attack[1].MinScope = 40;
	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;

	m_Attack[2].Name = MON_ATK_RANGE1;
	m_Attack[2].MinScope = 0;
	m_Attack[2].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;


	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_7_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_7_WALK_VERTICAL;
}



//--------------------------------------------------------------------------------------
BossBigDragon1::~BossBigDragon1()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}

//--------------------------------------------------------------------------------------
void BossBigDragon1::ResvBossDragon_AllAction(int changeState, int dummy)
//--------------------------------------------------------------------------------------
{
	//	보스1번이 모든 보스의 몸통을 제어한다.
	ResvAction(changeState, 0);

	for(int loop = 0; loop < BOSS_DRAGON_MAX_BODY_COUNT; loop++)
	{
		SetMessage(MSG_BOSS_CHANGESTATE, pChildBody[loop]->m_nUniqueIdx, changeState);
	}
}


//--------------------------------------------------------------------------------------
bool BossBigDragon1::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_BOSS1_HEAD_MELEE2:
		case MON_ATK_RANGE1:
		case MON_AC_READY:
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_STAND:
		//-----------------------------------------------------------------------
		{
			int addFieldX = m_CharInfo->m_nPos.x - 170;
			if(0 > addFieldX)	{addFieldX = 0;}
			addFieldX = (30*addFieldX)/ 100;

			if(1 > ABS(m_nMoveY - pMonAsIns->m_posY))
			{
				m_nMoveTimer--;

				if(1 > m_nMoveTimer)
				{
					if(50 < (SUTIL_GetRandom()%100) )
					{
						m_nMoveY = 190 + (SUTIL_GetRandom()%50);
						m_nMoveX = m_nFirstX - (SUTIL_GetRandom()%20) + addFieldX;
						m_nMoveTimer = 10+(SUTIL_GetRandom()%10);
						m_nCurMoveTimer = 0;
						m_nSaveX = pMonAsIns->m_posX;
						m_nSaveY = pMonAsIns->m_posY;
						SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_WALK_VERTICAL);
					}
					else
					{
						m_nMoveTimer = (SUTIL_GetRandom()%30);
						pMonAsIns->m_posX = m_nMoveX;
						pMonAsIns->m_posY = m_nMoveY;
						SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_STAND);
					}
				}
			}
			else
			{
				m_nCurMoveTimer++;
				pMonAsIns->m_posX = m_nSaveX + (m_nMoveX - m_nSaveX)*m_nCurMoveTimer/m_nMoveTimer;
				pMonAsIns->m_posY = m_nSaveY + (m_nMoveY - m_nSaveY)*m_nCurMoveTimer/m_nMoveTimer;

				if(1 > ABS(m_nMoveX - pMonAsIns->m_posX) && 1 > ABS(m_nMoveY - pMonAsIns->m_posY))	{m_nMoveTimer = 0;}
			}
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				pMonAsIns->m_posX = m_nMoveX;
				m_nMoveY = pMonAsIns->m_posY;
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_READY:
			//-----------------------------------------------------------------------
			{

				m_nMoveX = m_nFirstX = pMonAsIns->m_posX;
				m_nMoveY = pMonAsIns->m_posY;
				m_nMoveTimer = 0;
				//m_nMoveTimerY = 0;

				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_BOSS1_HEAD_MELEE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_ATK_MELEE2, 0);
				break;
			}
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER_DONT_REMOVE, 0);
				break;
			}
			default:	{break;}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
void BossBigDragon1::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	m_nDelayTimer--;
	if(MON_AC_STAND == m_ActState && 1 > m_nDelayTimer)
	{
		int seed = SUTIL_GetRandom()%m_nAtkMaxCount;

		while(1)
		{
			seed = (seed+1)%m_nAtkMaxCount;
			if(1 > m_Attack[seed].CoolTime)
			{
				m_nDelayTimer = 100;
				ResvAction(m_Attack[seed].Name, 0);
				break;
			}
		}
	}

	//	보스5는 데미지를 따로 통합해서 관리해서 1번이 가지고 있는다.
	//	초기화는 5번에서 관리한다.
	if(0 < Monster::m_nExtraDamage)
	{
		m_Stet.m_Hp -= Monster::m_nExtraDamage;
		if(0 > m_Stet.m_Hp)
		{
			m_Stet.m_Hp = 0;
			ResvAction(MON_AC_DIE, 0);
		}
	}
}

//--------------------------------------------------------------------------------------
void BossBigDragon1::Paint()
//--------------------------------------------------------------------------------------
{
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	등장 / 퇴장신에는 정렬이 안되게 한다.
//	if(isPossibleAction)
//	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
//	}
//	else
//	{
//		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
//	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossBigDragon1::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_DOWN);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_DOWNED);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_READY:
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_STAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
//			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
//			else													{m_nDirection = SDIR_LEFT;}
//			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_LEFT);
			//m_Physics->initForce();
			return true;
			break;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS1_HEAD_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_HIDE);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			pMonAsIns->m_posX = 320+120;
			pMonAsIns->m_posY = 190 + (SUTIL_GetRandom()%50);

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_HEAD_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			int addx = 0;
			if(SDIR_LEFT == m_nDirection)			{addx -= 20;}
			else									{addx += 20;}

			for(int loop = 0; loop < 15; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_1_BEAM_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+(loop*(addx)));
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				//SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 32;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 0;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 3;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			return true;
		}
	}

	return false;
}



//==============================================================================================================





//--------------------------------------------------------------------------------------
BossBigDragon2::BossBigDragon2()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_1;
	m_nMonIdx = MON_IDX_BIG_DRAGON2;
	m_nFeature =  FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 70;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].MinScope = 40;
	m_Attack[1].MaxScope = 100;



	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_7_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_7_WALK_VERTICAL;
}



//--------------------------------------------------------------------------------------
BossBigDragon2::~BossBigDragon2()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}

//--------------------------------------------------------------------------------------
bool BossBigDragon2::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_AC_READY:
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			m_nMelee2AtkTime--;

			if(1 > m_nMelee2AtkTime)
			{
				ResvAction(MON_AC_STAND, 0);
			}
			break;
		}

		case MON_AC_STAND:
		//-----------------------------------------------------------------------
		{

			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_ATK_MELEE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_READY:
			//-----------------------------------------------------------------------
			{

//				m_nMoveX = m_nFirstX = pMonAsIns->m_posX;
//				m_nMoveY = pMonAsIns->m_posY;
//				m_nMoveTimer = 0;
				//m_nMoveTimerY = 0;

				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER_DONT_REMOVE, 0);
				break;
			}
			default:	{break;}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
void BossBigDragon2::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	m_nDelayTimer--;
	if(MON_AC_STAND == m_ActState && 1 > m_nDelayTimer)
	{
		int seed = SUTIL_GetRandom()%m_nAtkMaxCount;

		while(1)
		{
			seed = (seed+1)%m_nAtkMaxCount;
			if(1 > m_Attack[seed].CoolTime)
			{
				m_nDelayTimer = 100;
				ResvAction(m_Attack[seed].Name, 0);
				break;
			}
		}
	}

	//	보스5는 데미지를 따로 통합해서 관리해서 1번이 가지고 있는다.
	//	초기화는 5번에서 관리한다.
	if(0 < Monster::m_nExtraDamage)
	{
		m_Stet.m_Hp -= Monster::m_nExtraDamage;
		if(0 > m_Stet.m_Hp)
		{
			m_Stet.m_Hp = 0;
			ResvAction(MON_AC_DIE, 0);
		}
	}
}

//--------------------------------------------------------------------------------------
void BossBigDragon2::Paint()
//--------------------------------------------------------------------------------------
{
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	등장 / 퇴장신에는 정렬이 안되게 한다.
//	if(isPossibleAction)
//	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
//	}
//	else
//	{
//		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
//	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossBigDragon2::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_DOWNED);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_DOWNED);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_READY:
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_EMPTY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
//			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
//			else													{m_nDirection = SDIR_LEFT;}
//			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_LEFT);
			//m_Physics->initForce();
			return true;
			break;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			pMonAsIns->m_posX = 0;
			pMonAsIns->m_posY = 190 + (SUTIL_GetRandom()%50);
//				m_nMoveY = pMonAsIns->m_posY;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_LEFT;}
			else										{m_nDirection = SDIR_RIGHT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			m_nMelee2AtkTime = 60;

			pMonAsIns->m_posX = -50;
			pMonAsIns->m_posY = 190 + (SUTIL_GetRandom()%50);

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_MELEE_2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}

//==============================================================================================================





//--------------------------------------------------------------------------------------
BossBigDragon3::BossBigDragon3()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_1;
	m_nMonIdx = MON_IDX_BIG_DRAGON3;
	m_nFeature =  FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

//	m_nAtkMaxCount = 2;
//	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);
//
//	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;
//
//	m_Attack[1].Name = MON_ATK_MELEE2;
//	m_Attack[1].MinScope = 40;
//	m_Attack[1].MaxScope = 100;



	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_7_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_7_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_1_HEAD_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_7_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_7_WALK_VERTICAL;
}



//--------------------------------------------------------------------------------------
BossBigDragon3::~BossBigDragon3()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}

//--------------------------------------------------------------------------------------
bool BossBigDragon3::ExtProcess()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		default:	{return false;}
		case MON_AC_READY:
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_STAND:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_READY:
			//-----------------------------------------------------------------------
			{

//				m_nMoveX = m_nFirstX = pMonAsIns->m_posX;
//				m_nMoveY = pMonAsIns->m_posY;
//				m_nMoveTimer = 0;
				//m_nMoveTimerY = 0;

				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_DIE_AFTER_DONT_REMOVE, 0);
				break;
			}
			default:	{break;}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------------
void BossBigDragon3::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스5는 데미지를 따로 통합해서 관리해서 1번이 가지고 있는다.
	//	초기화는 5번에서 관리한다.
	if(0 < Monster::m_nExtraDamage)
	{
		m_Stet.m_Hp -= Monster::m_nExtraDamage;
		if(0 > m_Stet.m_Hp)
		{
			m_Stet.m_Hp = 0;
			ResvAction(MON_AC_DIE, 0);
			Monster::m_nExtraDamage = 0;
		}
	}
}

//--------------------------------------------------------------------------------------
void BossBigDragon3::Paint()
//--------------------------------------------------------------------------------------
{
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	등장 / 퇴장신에는 정렬이 안되게 한다.
//	if(isPossibleAction)
//	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
//	}
//	else
//	{
//		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
//	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossBigDragon3::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_TOP_DOWN);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_DIE_AFTER_DONT_REMOVE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_TOP_DOWNED);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			return true;
		}
		case MON_AC_READY:
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BODY_TOP_STAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
//			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
//			else													{m_nDirection = SDIR_LEFT;}
//			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetDirAsprite(pMonAsIns, SDIR_RIGHT);
			//m_Physics->initForce();
			return true;
			break;
		}
	}

	return false;
}

*/
//==============================================================================================================



//--------------------------------------------------------------------------------------
BossWorm::BossWorm()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_1;
	m_nMonIdx = MON_IDX_WORM;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 5;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 60;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 60;

	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 60;
	m_Attack[1].AtkRect.x2 = 100;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;

	m_Attack[2].Name = MON_ATK_MELEE3;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 60;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 60;
//	m_Attack[2].Debuff = DEBUF_STUN;

	m_Attack[3].Name = MON_ATK_RANGE1;
	m_Attack[3].AtkRect.x1 = 100;
	m_Attack[3].AtkRect.x2 = 200;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 100;
//	m_Attack[3].MaxScope = 200;
//	m_Attack[2].Debuff = DEBUF_STUN;

	m_Attack[4].Name = MON_ATK_SUMMON_BUG;
	m_Attack[4].AtkRect.x1 = 0;
	m_Attack[4].AtkRect.x2 = 120;
	m_Attack[4].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[4].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[4].MinScope = 0;
//	m_Attack[4].MaxScope = 120;
	m_Attack[4].MaxCoolTime = 300;
	m_Attack[4].CoolTime = 200;


	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_1_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_1_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_1_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_1_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_1_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_1_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_1_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_1_B_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_1_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_1_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_WORM_BURROWMOVE;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_MOVE_BACK;


}



//--------------------------------------------------------------------------------------
BossWorm::~BossWorm()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossWorm::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	//MON_ATK_SUMMON_BUG


	m_nUseAtkNum = 4;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(10 > m_nTotalMonCnt)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}

	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void BossWorm::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);
}

//--------------------------------------------------------------------------------------
bool BossWorm::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_AC_WORM_BURROW:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_RUN, 0);
			}
			return true;
		}
		case MON_AC_WORM_UNBURROW:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_RANGE1:
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool BossWorm::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_WORM_BURROW:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_BURROW);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_WORM_UNBURROW:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_UNBURROW);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
//			pMonAsIns->m_posX = 320+120;
//			pMonAsIns->m_posY = 190 + (SUTIL_GetRandom()%50);

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_MELEE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			int addx = 0;
			if(SDIR_LEFT == m_nDirection)			{addx -= 20;}
			else									{addx += 20;}

//			for(int loop = 0; loop < 15; loop++)
//			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_1_BULLET_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
//				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+(loop*(addx)));
//				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);

				SUTIL_SetXPosAsprite(tmpAsIns, m_CharInfo->m_nPos.x);
				SUTIL_SetYPosAsprite(tmpAsIns, m_CharInfo->m_nPos.y);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				//SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 17;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 0;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 3;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
//			}

			return true;
		}
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_1_SUMMON);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	벌레 소환
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 5);
			return true;
		}
	}

	return false;
}


//==============================================================================================================



//--------------------------------------------------------------------------------------
BossSkelBird::BossSkelBird()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_2;
	m_nMonIdx = MON_IDX_SKELBIRD;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 4;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE3;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 20;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize);
	m_Attack[0].AtkRect.y2 = 0;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 80;
//	m_Attack[0].Debuff = DEBUF_STUN;
	m_Attack[0].CoolTime = 0;
	m_Attack[0].MaxCoolTime = 0;

	m_Attack[1].Name = MON_ATK_MELEE1;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 70;
	m_Attack[1].AtkRect.y1 = -5;
	m_Attack[1].AtkRect.y2 = (m_nBodySize-5);
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 70;
	m_Attack[1].CoolTime = 0;
	m_Attack[1].MaxCoolTime = 80;

	m_Attack[2].Name = MON_ATK_MELEE2;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 60;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = 60;
//	m_Attack[2].MinScope = 40;
//	m_Attack[2].MaxScope = 100;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].CoolTime = 0;
	m_Attack[2].MaxCoolTime = 200;



	m_Attack[3].Name = MON_ATK_RANGE1;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 300;
	m_Attack[3].AtkRect.y1 = -(300);
	m_Attack[3].AtkRect.y2 = (300);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[3].CoolTime = 0;
	m_Attack[3].MaxCoolTime = 400;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_2_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_2_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_2_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_2_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_1_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[4] = MON_AI_ATTACK;
	m_nAiPtnData[5] = MON_AI_MOVE_BACK;


}



//--------------------------------------------------------------------------------------
BossSkelBird::~BossSkelBird()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}



//--------------------------------------------------------------------------------------
void BossSkelBird::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void BossSkelBird::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
//		pChildBody[0]->SetAction(m_NextActState);
//		pChildBody[1]->SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);
	SUTIL_UpdateTimeAsprite(pChildBody[1]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);


	//	child의 좌표를 갱신시킨다.
	pChildBody[1]->pMonAsIns->m_posX = pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
	pChildBody[1]->pMonAsIns->m_posY = pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
	pChildBody[1]->pMonAsIns->m_posZ = pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void BossSkelBird::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	//	paint shadow
	//int tmpx = pMonAsIns->Get_AFrameXZ();
	//int tmpy = tmpx%100000;
	//tmpx = tmpx/100000; 

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	/*pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);

	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);*/
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

	SUTIL_PaintAsprite(pChildBody[0]->pMonAsIns, S_INCLUDE_SORT);
	SUTIL_PaintAsprite(pChildBody[1]->pMonAsIns, S_INCLUDE_SORT);

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossSkelBird::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_FALL, 0);
			}
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------------------
		{
			//	앞으로 전진하는 기술이다.
			pMonAsIns->m_posY += 3;

			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE3:
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool BossSkelBird::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	//	미리 비어놓는다.
	SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_FLING);
	SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_FLING);

	switch(m_ActState)
	{
/*
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_DOWN);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_DOWN);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return false;
		}
		case MON_AC_DOWNED:
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_DOWNED);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_DOWNED);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return false;
		}
*/
		case MON_AC_STAND:
		case MON_AC_READY:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_STAND);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_STAND);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return false;
		}

		case MON_AC_MOVE:
		case MON_AC_RUN:
		case MON_AC_BEHOLD:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_WALK);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_WALK);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return false;
		}

		case MON_AC_FALL:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_FALL);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_FALL);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_FALL);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();

			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_MELEE_1);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_MELEE_1);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();

			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
//			pMonAsIns->m_posX = 320+120;
//			pMonAsIns->m_posY = 190 + (SUTIL_GetRandom()%50);

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_MELEE_2);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_MELEE_2);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_MELEE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_MELEE_3);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_MELEE_3);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_2_FLY);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_2_ARM_L_FLY);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SUTIL_SetTypeAniAsprite(pChildBody[1]->pMonAsIns,ANIM_BOSS_2_ARM_R_FLY);
			SUTIL_SetDirAsprite(pChildBody[1]->pMonAsIns, m_nDirection);
			pChildBody[1]->m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			int addx = 0;
			if(SDIR_LEFT == m_nDirection)			{addx -= 20;}
			else									{addx += 20;}


			int seed = 8 + SUTIL_GetRandom()%4;
			for(int loop = 0; loop < seed; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_2_BULLET_1);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 170 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 27;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 30+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_2_BULLET_1);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 200 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 27;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 30+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_2_BULLET_1);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 230 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 30+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
void BossSkelBird::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
	m_Stet.m_Hp -= heroDamage;
	if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}

	pChildBody[0]->m_Stet.m_Hp = m_Stet.m_Hp;
	pChildBody[1]->m_Stet.m_Hp = m_Stet.m_Hp;
}



//==============================================================================================================



//--------------------------------------------------------------------------------------
BossSkelBird_L_ARM::BossSkelBird_L_ARM()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_2;
	m_nMonIdx = MON_IDX_SKELBIRD_L_ARM;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_2_WALK_VERTICAL;
}




//--------------------------------------------------------------------------------------
BossSkelBird_L_ARM::~BossSkelBird_L_ARM()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
bool BossSkelBird_L_ARM::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return true;
}


//--------------------------------------------------------------------------------------
bool BossSkelBird_L_ARM::ExtProcess()
//--------------------------------------------------------------------------------------
{
	return true;
}


//--------------------------------------------------------------------------------------
void BossSkelBird_L_ARM::Paint()
//--------------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------------
void BossSkelBird_L_ARM::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
	m_pParents->RCV_Damage(heroDamage);
}

//==============================================================================================================

//--------------------------------------------------------------------------------------
BossSkelBird_R_ARM::BossSkelBird_R_ARM()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_2;
	m_nMonIdx = MON_IDX_SKELBIRD_L_ARM;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_2_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_2_WALK_VERTICAL;
}



//--------------------------------------------------------------------------------------
BossSkelBird_R_ARM::~BossSkelBird_R_ARM()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
bool BossSkelBird_R_ARM::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return true;
}


//--------------------------------------------------------------------------------------
bool BossSkelBird_R_ARM::ExtProcess()
//--------------------------------------------------------------------------------------
{
	return true;
}

//--------------------------------------------------------------------------------------
void BossSkelBird_R_ARM::Paint()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
void BossSkelBird_R_ARM::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
	m_pParents->RCV_Damage(heroDamage);
}






//==============================================================================================================



//--------------------------------------------------------------------------------------
BossFlower::BossFlower()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_3;
	m_nMonIdx = MON_IDX_FLOWER;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 5;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 50;
	m_Attack[0].AtkRect.y1 = 0;
	m_Attack[0].AtkRect.y2 = m_nBodySize;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;
	m_Attack[0].CoolTime = 0;
	m_Attack[0].MaxCoolTime = 0;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 200;
	m_Attack[1].AtkRect.y1 = 0;
	m_Attack[1].AtkRect.y2 = 200;
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;
	m_Attack[1].CoolTime = 0;
	m_Attack[1].MaxCoolTime = 60;

	m_Attack[2].Name = MON_ATK_RANGE2;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 200;
	m_Attack[2].AtkRect.y1 = -100;
	m_Attack[2].AtkRect.y2 = 300;
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].CoolTime = 0;
	m_Attack[2].MaxCoolTime = 200;


	m_Attack[3].Name = MON_ATK_RANGE3;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 300;
	m_Attack[3].AtkRect.y1 = -100;
	m_Attack[3].AtkRect.y2 = 300;
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[3].CoolTime = 0;
	m_Attack[3].MaxCoolTime = 400;


	m_Attack[4].Name = MON_ATK_SUMMON_BUG;
	m_Attack[4].AtkRect.x1 = 0;
	m_Attack[4].AtkRect.x2 = 300;
	m_Attack[4].AtkRect.y1 = -(300);
	m_Attack[4].AtkRect.y2 = (300);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[4].CoolTime = 0;
	m_Attack[4].MaxCoolTime = 400;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_3_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_3_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_3_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_3_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_3_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_3_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_3_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_1_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 19;
	m_nAiPtnData[0] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[3] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[4] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[5] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[6] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[7] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[8] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[9] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[10] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[11] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[12] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[13] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[14] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[15] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[16] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[17] = MON_AI_ATTACK_DONTMOVE;
	m_nAiPtnData[18] = MON_AI_READY_TO_HIT;
}



//--------------------------------------------------------------------------------------
BossFlower::~BossFlower()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossFlower::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	m_nUseAtkNum = 4;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(10 > m_nTotalMonCnt)
		{
			//	체력이 아직 많이 남아있으면 소환을 하지 않는다.
			if(m_Stet.m_MaxHp > (m_Stet.m_Hp*2))
			{
				m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
				return;
			}
		}
	}

	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void BossFlower::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
//		pChildBody[0]->SetAction(m_NextActState);
//		pChildBody[1]->SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);


	//	child의 좌표를 갱신시킨다.
	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void BossFlower::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	//	paint shadow
	//int tmpx = pMonAsIns->Get_AFrameXZ();
	//int tmpy = tmpx%100000;
	//tmpx = tmpx/100000; 

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	/*pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);

	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);*/
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

	SUTIL_PaintAsprite(pChildBody[0]->pMonAsIns, S_INCLUDE_SORT);

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossFlower::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool BossFlower::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_DOWN);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_DIE_AFTER:
		case MON_AC_DOWNED:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_DOWNED);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();
			return false;
		}

		case MON_AC_STAND:
		case MON_AC_READY:
		//-----------------------------------------------------------
		{
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}

			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_STAND);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();
			return false;
		}
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_SUMMON);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	얼굴 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_SUMMON);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 4);

			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	얼굴 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_MELEE_1);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			return true;
		}
		case MON_ATK_RANGE1:	//	방사형 포
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	얼굴 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_RANGE_1);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;

			int BulletSet[5][2] = {{-53,-40},{-32,-28},{0,-15},{44,-40},{23,-28}};
			int BulletMove[5][2] = {{-8,+3},{-5,+4},{0,+4},{8,+3},{5,+4}};

//			int BulletSet[8][2] = {{-32,-66},{-53,-54},{-53,-40},{-32,-28},{23,-66},{44,-54},{44,-40},{23,-28}};
//			int BulletMove[8][2] = {{-6,-4},{-8,-3},{-8,+3},{-6,+4},{6,-4},{8,-3},{8,+3},{6,+4}};


			for(int loop = 0; loop < 5; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+BulletSet[loop][0]+5);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+BulletSet[loop][1]+40);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMOVE;
				tmpMonSkill->lifeTime = 17;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 0;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 2;
				tmpMonSkill->damagetime = 6;
				tmpMonSkill->Movex = BulletMove[loop][0];
				tmpMonSkill->Movey = BulletMove[loop][1];
				tmpMonSkill->Movez = 0;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}


			return true;
		}
		case MON_ATK_RANGE3:		//	돌뭉치 떨어뜨림
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	얼굴 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_RANGE_2);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			int addx = 0;
			if(SDIR_LEFT == m_nDirection)			{addx -= 20;}
			else									{addx += 20;}

			int seed = 8 + SUTIL_GetRandom()%4;
			for(int loop = 0; loop < seed; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 170 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 6+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 200 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 8+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 230 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}


			return true;
		}
		case MON_ATK_RANGE2:		//	벽 소환
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	얼굴 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_RANGE_3);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			//	
			//0 width, 1 height
			if(SUTIL_GetRandom()%2)
			{
				for(int loop = 0; loop < 6; loop++)
				{
					SetMessage(MSG_BOSS3_SUMMON_WALL, (m_CharInfo->m_nPos.x)-10+SUTIL_GetRandom()%20, 180 + loop*20, 0, 0, loop);			
				}
			}
			else
			{
				int max = Field::m_nFieldSize_X/26;
				for(int loop = 0; loop < max; loop++)
				{
					SetMessage(MSG_BOSS3_SUMMON_WALL, 15 + loop*26, (m_CharInfo->m_nPos.y)-10+SUTIL_GetRandom()%20, 0, 0, loop);
				}
			}

			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
void BossFlower::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
	m_Stet.m_Hp -= heroDamage;
	if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}

	pChildBody[0]->m_Stet.m_Hp = m_Stet.m_Hp;
}






//==============================================================================================================



//--------------------------------------------------------------------------------------
BossFlower_Brain::BossFlower_Brain()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_3;
	m_nMonIdx = MON_IDX_FLOWER_BRAIN;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

//	//	사용할 이미지를 설정한다.
//	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_2_STAND;
//	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_2_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_2_WALK_VERTICAL;
}




//--------------------------------------------------------------------------------------
BossFlower_Brain::~BossFlower_Brain()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
bool BossFlower_Brain::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	return true;
}


//--------------------------------------------------------------------------------------
bool BossFlower_Brain::ExtProcess()
//--------------------------------------------------------------------------------------
{
	return true;
}


//--------------------------------------------------------------------------------------
void BossFlower_Brain::Paint()
//--------------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------------
void BossFlower_Brain::RCV_Damage(int heroDamage)
//--------------------------------------------------------------------------------------
{
	m_pParents->RCV_Damage(heroDamage);
}


//==============================================================================================================




//--------------------------------------------------------------------------------------
DarkKnight::DarkKnight()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_4;
	m_nMonIdx = MON_IDX_DARK_KNIGHT;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 5;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 50;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;
	m_Attack[0].CoolTime = 0;
	m_Attack[0].MaxCoolTime = 0;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 110;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;
	m_Attack[1].CoolTime = 0;
	m_Attack[1].MaxCoolTime = 60;

	m_Attack[2].Name = MON_ATK_RANGE2;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 300;
	m_Attack[2].AtkRect.y1 = -300;
	m_Attack[2].AtkRect.y2 = 300;
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].CoolTime = 0;
	m_Attack[2].MaxCoolTime = 200;


	m_Attack[3].Name = MON_ATK_RANGE6;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 110;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[3].CoolTime = 0;
	m_Attack[3].MaxCoolTime = 300;


	m_Attack[4].Name = MON_ATK_SPECIAL1;
	m_Attack[4].AtkRect.x1 = 100;
	m_Attack[4].AtkRect.x2 = 300;
	m_Attack[4].AtkRect.y1 = -(300);
	m_Attack[4].AtkRect.y2 = (300);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[4].CoolTime = 100;
	m_Attack[4].MaxCoolTime = 500;

	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_4_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_4_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_4_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_4_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 19;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[4] = MON_AI_ATTACK;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[7] = MON_AI_ATTACK;
	m_nAiPtnData[8] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[9] = MON_AI_ATTACK;
	m_nAiPtnData[10] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[11] = MON_AI_ATTACK;
	m_nAiPtnData[12] = MON_AI_ATTACK;
	m_nAiPtnData[13] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[14] = MON_AI_ATTACK;
	m_nAiPtnData[15] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[16] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[17] = MON_AI_ATTACK;
	m_nAiPtnData[18] = MON_AI_READY_TO_HIT;
}



//--------------------------------------------------------------------------------------
DarkKnight::~DarkKnight()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void DarkKnight::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	m_nUseAtkNum = 4;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(1 == m_nTotalMonCnt)
		{
			//	체력이 아직 많이 남아있으면 소환을 하지 않는다.
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}

	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
//		if(1 == m_nTotalMonCnt)
//		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
//		}
		return;
	}

	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void DarkKnight::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
//	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);


	//	child의 좌표를 갱신시킨다.
//	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
//	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
//	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void DarkKnight::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	//	paint shadow
	//int tmpx = pMonAsIns->Get_AFrameXZ();
	//int tmpy = tmpx%100000;
	//tmpx = tmpx/100000; 

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);
//
//	//	그림자
//	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
//	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);
//	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);
//
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

	//SUTIL_PaintAsprite(pChildBody[0]->pMonAsIns, S_INCLUDE_SORT);

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool DarkKnight::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_ATK_RANGE4, 0);
			}
			return true;
		}
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------------------
		{
			//	좌표를 보정해준다.(점프가 2프레임부터 시작한다.)
			if(1 < m_nTimer)
			{
				//	2일때 최종 캐릭터의 위치를 갱신해준다.
				if(2 == m_nTimer)	{m_nStartPosX = pMonAsIns->m_posX;}

				pMonAsIns->m_posX = m_nStartPosX + ((m_nEndPosX - m_nStartPosX)*(m_nTimer-2))/8;
			}

			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_ATK_RANGE3, 0);
			}
			return true;
		}
		case MON_ATK_RANGE3:
		//-----------------------------------------------------------------------
		{
			//	1일때 최종 캐릭터의 위치를 갱신해준다.
			if(1 == m_nTimer)
			{
				m_nStartPosX = pMonAsIns->m_posX;
				m_nStartPosY = pMonAsIns->m_posY;
			}

			if(5 > m_nTimer)
			{
				pMonAsIns->m_posX = m_nStartPosX + ((m_nEndPosX - m_nStartPosX)*(m_nTimer))/5;
				pMonAsIns->m_posY = m_nStartPosY + ((m_nEndPosY - m_nStartPosY)*(m_nTimer))/5;
			}

			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
		case MON_ATK_RANGE4:
		//-----------------------------------------------------------------------
		{
			bool isEndAni = SUTIL_UpdateTimeAsprite(pMonAsIns);
			//	임시변수로 쓰였음
			m_nStartPosX = m_nDirection*(m_CharInfo->m_nPos.x - pMonAsIns->m_posX);

			if(0 < m_nStartPosX && 30 >= m_nStartPosX)
			{
				if(SQR(m_nBodySize/2) > SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y))
				{
					pMonAsIns->m_posX = m_CharInfo->m_nPos.x - (m_nDirection*55); //	에니 갱신량이 30이가 때문에 거리+에니갱신량을 해준다.
					pMonAsIns->m_posY = m_CharInfo->m_nPos.y;
					ResvAction(MON_ATK_RANGE5, 0);
					return true;
				}
			}

			if(!isEndAni)	{ResvAction(MON_AC_STAND, 0);}

			return true;
		}
		case MON_ATK_RANGE6:
		//-----------------------------------------------------------------------
		{
			bool isEndAni = SUTIL_UpdateTimeAsprite(pMonAsIns);

			if(8 < m_nTimer)
			{
				//	임시변수로 쓰였음
				m_nStartPosX = m_nDirection*(m_CharInfo->m_nPos.x - pMonAsIns->m_posX);

				if(0 < m_nStartPosX && 40 >= m_nStartPosX)
				{
					if(SQR(m_nBodySize/2) > SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y))
					{
						pMonAsIns->m_posX = m_CharInfo->m_nPos.x - (m_nDirection*70); //	에니 갱신량이 30이가 때문에 거리+에니갱신량을 해준다.
						pMonAsIns->m_posY = m_CharInfo->m_nPos.y;
						ResvAction(MON_ATK_RANGE7, 0);
						return true;
					}
				}
			}

			if(!isEndAni)	{ResvAction(MON_AC_STAND, 0);}

			return true;
		}
		case MON_ATK_MELEE1:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE7:
		case MON_ATK_SPECIAL1:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool DarkKnight::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_SPECIAL1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MIRROR_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 11);

			return true;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			return true;
		}
		case MON_ATK_RANGE1:	//	포 발사 -> MON_ATK_RANGE4
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_4_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(20*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 8;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 4;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_RANGE4:	//	포 발사 후 돌진 공격	
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_2_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE5:	//	포 발사 후 돌진 후 깨물기 공격	
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_2_2);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE6:	//	난무 공격
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_4_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE7:	//	난무 공격 성공
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_4_2);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE2:		//	스트리트 파이터 베가 공격1 -> MON_ATK_RANGE3
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_1);

			m_nStartPosX = pMonAsIns->m_posX;

			//	오른쪽 벽을 틩긴다.
			if(pMonAsIns->m_posX > Field::m_nFieldSize_X/2)
			{
				m_nEndPosX = Field::m_nFieldSize_X;
				m_nDirection = SDIR_RIGHT;
			}
			//	왼쪽벽을 틩긴다.
			else								
			{
				m_nEndPosX = 0;
				m_nDirection = SDIR_LEFT;
			}				
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:		//	스트리트 파이터 베가 공격2
		//-----------------------------------------------------------
		{
			//	z값을 강제로 없애준다. 에니에서 처리되어있음
			pMonAsIns->m_posZ = 0;
			m_nStartPosX = m_nEndPosX;
			m_nEndPosX = m_CharInfo->m_nPos.x;

			m_nStartPosY = pMonAsIns->m_posY;
			m_nEndPosY = m_CharInfo->m_nPos.y;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_2);

			if(0 == m_nStartPosX)	{m_nDirection = SDIR_LEFT;}
			else					{m_nDirection = SDIR_RIGHT;}

			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
/*
		case MON_ATK_RANGE3:		//	돌뭉치 떨어뜨림
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			int addx = 0;
			if(SDIR_LEFT == m_nDirection)			{addx -= 20;}
			else									{addx += 20;}

			int seed = 8 + SUTIL_GetRandom()%4;
			for(int loop = 0; loop < seed; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 170 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 6+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 200 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 8+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 230 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}


			return true;
		}
		case MON_ATK_RANGE2:		//	벽 소환
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	
			//0 width, 1 height
			if(SUTIL_GetRandom()%2)
			{
				for(int loop = 0; loop < 6; loop++)
				{
					SetMessage(MSG_BOSS3_SUMMON_WALL, (m_CharInfo->m_nPos.x)-10+SUTIL_GetRandom()%20, 180 + loop*20, 0, 0, loop);			
				}
			}
			else
			{
				int max = Field::m_nFieldSize_X/26;
				for(int loop = 0; loop < max; loop++)
				{
					SetMessage(MSG_BOSS3_SUMMON_WALL, 15 + loop*26, (m_CharInfo->m_nPos.y)-10+SUTIL_GetRandom()%20, 0, 0, loop);
				}
			}

			return true;
		}
*/
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
DarkKnight_Mirror::DarkKnight_Mirror()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_4;
	m_nMonIdx = MON_IDX_DARK_KNIGHT_MIRROR;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 2;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 50;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;
	m_Attack[0].CoolTime = 0;
	m_Attack[0].MaxCoolTime = 0;

	m_Attack[1].Name = MON_ATK_RANGE2;
	m_Attack[1].AtkRect.x1 = 0;
	m_Attack[1].AtkRect.x2 = 200;
	m_Attack[1].AtkRect.y1 = 0;
	m_Attack[1].AtkRect.y2 = 200;
//	m_Attack[1].MinScope = 0;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;
	m_Attack[1].CoolTime = 0;
	m_Attack[1].MaxCoolTime = 60;
/*
	m_Attack[2].Name = MON_ATK_RANGE2;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 200;
	m_Attack[2].AtkRect.y1 = -100;
	m_Attack[2].AtkRect.y2 = 300;
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].CoolTime = 0;
	m_Attack[2].MaxCoolTime = 200;


	m_Attack[3].Name = MON_ATK_SPECIAL1;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 300;
	m_Attack[3].AtkRect.y1 = -100;
	m_Attack[3].AtkRect.y2 = 300;
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[3].CoolTime = 0;
	m_Attack[3].MaxCoolTime = 400;


	m_Attack[4].Name = MON_ATK_MELEE1;
	m_Attack[4].AtkRect.x1 = 0;
	m_Attack[4].AtkRect.x2 = 300;
	m_Attack[4].AtkRect.y1 = -(300);
	m_Attack[4].AtkRect.y2 = (300);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 80;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[4].CoolTime = 0;
	m_Attack[4].MaxCoolTime = 400;
*/
	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_4_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_4_MIRRORDOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_4_MIRRORDOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_4_MIRRORDOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_4_MIRRORDOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_4_MIRROR_2;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_4_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 19;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[4] = MON_AI_ATTACK;
	m_nAiPtnData[5] = MON_AI_ATTACK;
	m_nAiPtnData[6] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[7] = MON_AI_ATTACK;
	m_nAiPtnData[8] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[9] = MON_AI_ATTACK;
	m_nAiPtnData[10] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[11] = MON_AI_ATTACK;
	m_nAiPtnData[12] = MON_AI_ATTACK;
	m_nAiPtnData[13] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[14] = MON_AI_ATTACK;
	m_nAiPtnData[15] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[16] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[17] = MON_AI_ATTACK;
	m_nAiPtnData[18] = MON_AI_READY_TO_HIT;
}



//--------------------------------------------------------------------------------------
DarkKnight_Mirror::~DarkKnight_Mirror()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void DarkKnight_Mirror::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;
/*
	m_nUseAtkNum = 4;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(10 > m_nTotalMonCnt)
		{
			//	체력이 아직 많이 남아있으면 소환을 하지 않는다.
			if(m_Stet.m_MaxHp > (m_Stet.m_Hp*2))
			{
				m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
				return;
			}
		}
	}

	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		if(1 == m_nTotalMonCnt)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		}
		return;
	}

	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
*/
	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void DarkKnight_Mirror::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
//	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);


	//	child의 좌표를 갱신시킨다.
//	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
//	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
//	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void DarkKnight_Mirror::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	//	paint shadow
	//int tmpx = pMonAsIns->Get_AFrameXZ();
	//int tmpy = tmpx%100000;
	//tmpx = tmpx/100000; 

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);
//
//	//	그림자
//	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
//	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);
//	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);
//
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

	//SUTIL_PaintAsprite(pChildBody[0]->pMonAsIns, S_INCLUDE_SORT);

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool DarkKnight_Mirror::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------------------
		{
			//	좌표를 보정해준다.(점프가 2프레임부터 시작한다.)
			if(1 < m_nTimer)
			{
				//	2일때 최종 캐릭터의 위치를 갱신해준다.
				if(2 == m_nTimer)	{m_nStartPosX = pMonAsIns->m_posX;}

				pMonAsIns->m_posX = m_nStartPosX + ((m_nEndPosX - m_nStartPosX)*(m_nTimer-2))/8;
			}

			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_ATK_RANGE3, 0);
			}
			return true;
		}
		case MON_ATK_RANGE3:
		//-----------------------------------------------------------------------
		{
			//	1일때 최종 캐릭터의 위치를 갱신해준다.
			if(1 == m_nTimer)
			{
				m_nStartPosX = pMonAsIns->m_posX;
				m_nStartPosY = pMonAsIns->m_posY;
			}

			if(5 > m_nTimer)
			{
				pMonAsIns->m_posX = m_nStartPosX + ((m_nEndPosX - m_nStartPosX)*(m_nTimer))/5;
				pMonAsIns->m_posY = m_nStartPosY + ((m_nEndPosY - m_nStartPosY)*(m_nTimer))/5;
			}

			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}

		case MON_ATK_MELEE1:
		case MON_ATK_RANGE1:
		case MON_ATK_SPECIAL1:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool DarkKnight_Mirror::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			return true;
		}
		case MON_ATK_RANGE1:	//	포 발사
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_4_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(20*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 8;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 4;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_RANGE2:		//	스트리트 파이터 베가 공격1
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_1);

			m_nStartPosX = pMonAsIns->m_posX;

			//	오른쪽 벽을 틩긴다.
			if(pMonAsIns->m_posX > Field::m_nFieldSize_X/2)
			{
				m_nEndPosX = Field::m_nFieldSize_X;
				m_nDirection = SDIR_RIGHT;
			}
			//	왼쪽벽을 틩긴다.
			else								
			{
				m_nEndPosX = 0;
				m_nDirection = SDIR_LEFT;
			}				
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:		//	스트리트 파이터 베가 공격2
		//-----------------------------------------------------------
		{
			//	z값을 강제로 없애준다. 에니에서 처리되어있음
			pMonAsIns->m_posZ = 0;
			m_nStartPosX = m_nEndPosX;
			m_nEndPosX = m_CharInfo->m_nPos.x;

			m_nStartPosY = pMonAsIns->m_posY;
			m_nEndPosY = m_CharInfo->m_nPos.y;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_2);

			if(0 == m_nStartPosX)	{m_nDirection = SDIR_LEFT;}
			else					{m_nDirection = SDIR_RIGHT;}

			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}


//==============================================================================================================

//--------------------------------------------------------------------------------------
BigTurtle::BigTurtle()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGTURTLE;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 4;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 60;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 60;
	m_Attack[0].MaxCoolTime = 0;
	m_Attack[0].CoolTime = 0;


	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 60;
	m_Attack[1].AtkRect.x2 = 100;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;
	m_Attack[1].MaxCoolTime = 0;
	m_Attack[1].CoolTime = 0;


	m_Attack[2].Name = MON_ATK_MELEE3;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 60;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 60;
//	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].MaxCoolTime = 100;
	m_Attack[2].CoolTime = 50;


	m_Attack[3].Name = MON_ATK_SUMMON_BUG;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 60;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 60;
//	m_Attack[3].Debuff = DEBUF_STUN;
	m_Attack[3].MaxCoolTime = 300;
	m_Attack[3].CoolTime = 200;


	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_5_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_5_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_5_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_5_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_1_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_ATTACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_MOVE_BACK;


}



//--------------------------------------------------------------------------------------
BigTurtle::~BigTurtle()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BigTurtle::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	//MON_ATK_SUMMON_BUG


	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(10 > m_nTotalMonCnt)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}
/*
	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
*/
	m_nUseAtkNum = 2;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 1;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}

	m_nUseAtkNum = 0;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
		return;
	}
}

//--------------------------------------------------------------------------------------
void BigTurtle::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);
}

//--------------------------------------------------------------------------------------
bool BigTurtle::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool BigTurtle::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_MELEE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_MELEE_3_E);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
//			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-2);		//	충격파가 캐릭터 밑으로 가게 해준다.
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 9;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 3;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_SUMMON);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	벌레 소환
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 3);
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 6);
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, m_nDirection, m_nMonIdx, 9);

			return true;
		}
	}

	return false;
}

//==============================================================================================================

//--------------------------------------------------------------------------------------
LastBoss::LastBoss()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_LASTBOSS;
	m_nFeature =  FE_BOSS;	//FE_BOSS | FE_DONT_AREA_CHECK;


	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 9;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 60;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 60;
	m_Attack[0].MaxCoolTime = 0;
	m_Attack[0].CoolTime = 0;


	m_Attack[1].Name = MON_ATK_MELEE2;
	m_Attack[1].AtkRect.x1 = 110;
	m_Attack[1].AtkRect.x2 = 180;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[1].MinScope = 60;
//	m_Attack[1].MaxScope = 100;
//	m_Attack[1].Debuff = DEBUF_STUN;
	m_Attack[1].MaxCoolTime = 100;
	m_Attack[1].CoolTime = 50;


	m_Attack[2].Name = MON_ATK_MELEE3;
	m_Attack[2].AtkRect.x1 = 0;
	m_Attack[2].AtkRect.x2 = 90;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[2].MinScope = 0;
//	m_Attack[2].MaxScope = 60;
	m_Attack[2].Debuff = DEBUF_STUN;
	m_Attack[2].MaxCoolTime = 200;
	m_Attack[2].CoolTime = 100;


	m_Attack[3].Name = MON_ATK_RANGE1;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 0;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 60;
//	m_Attack[3].Debuff = DEBUF_STUN;
	m_Attack[3].MaxCoolTime = 300;
	m_Attack[3].CoolTime = 150;

	m_Attack[4].Name = MON_ATK_RANGE2;
	m_Attack[4].AtkRect.x1 = 0;
	m_Attack[4].AtkRect.x2 = 200;
	m_Attack[4].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[4].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[4].MinScope = 0;
//	m_Attack[4].MaxScope = 60;
//	m_Attack[4].Debuff = DEBUF_STUN;
	m_Attack[4].MaxCoolTime = 0;
	m_Attack[4].CoolTime = 0;

	m_Attack[5].Name = MON_ATK_MELEE4;
	m_Attack[5].AtkRect.x1 = 80;
	m_Attack[5].AtkRect.x2 = 300;
	m_Attack[5].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[5].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[5].MinScope = 0;
//	m_Attack[5].MaxScope = 60;
//	m_Attack[5].Debuff = DEBUF_STUN;
	m_Attack[5].MaxCoolTime = 0;
	m_Attack[5].CoolTime = 0;

	m_Attack[6].Name = MON_ATK_RANGE3;
	m_Attack[6].AtkRect.x1 = 0;
	m_Attack[6].AtkRect.x2 = 150;
	m_Attack[6].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[6].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[6].MinScope = 0;
//	m_Attack[6].MaxScope = 60;
//	m_Attack[6].Debuff = DEBUF_STUN;
	m_Attack[6].MaxCoolTime = 0;
	m_Attack[6].CoolTime = 0;

	m_Attack[7].Name = MON_ATK_RANGE4;
	m_Attack[7].AtkRect.x1 = 0;
	m_Attack[7].AtkRect.x2 = 150;
	m_Attack[7].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[7].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[7].MinScope = 0;
//	m_Attack[7].MaxScope = 60;
//	m_Attack[7].Debuff = DEBUF_STUN;
	m_Attack[7].MaxCoolTime = 0;
	m_Attack[7].CoolTime = 0;

	m_Attack[8].Name = MON_ATK_SPECIAL1;
	m_Attack[8].AtkRect.x1 = 0;
	m_Attack[8].AtkRect.x2 = 1000;
	m_Attack[8].AtkRect.y1 = -1000;
	m_Attack[8].AtkRect.y2 = 1000;
//	m_Attack[8].MinScope = 0;
//	m_Attack[8].MaxScope = 60;
//	m_Attack[8].Debuff = DEBUF_STUN;
	m_Attack[8].MaxCoolTime = 0;
	m_Attack[8].CoolTime = 0;

/*
	m_Attack[3].Name = MON_ATK_SUMMON_BUG;
	m_Attack[3].AtkRect.x1 = 0;
	m_Attack[3].AtkRect.x2 = 60;
	m_Attack[3].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[3].AtkRect.y2 = (m_nBodySize/2);
//	m_Attack[3].MinScope = 0;
//	m_Attack[3].MaxScope = 60;
//	m_Attack[3].Debuff = DEBUF_STUN;
	m_Attack[3].MaxCoolTime = 300;
	m_Attack[3].CoolTime = 200;

*/
	//	사용할 이미지를 설정한다.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_6_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_6_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_6_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_6_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_6_WALK_VERTICAL;

	m_nAiPtnProcess = 0;
	m_nAiPtnTotCnt = 6;
	m_nAiPtnData[0] = MON_AI_ATTACK;
	m_nAiPtnData[1] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[2] = MON_AI_ATTACK;
	m_nAiPtnData[3] = MON_AI_ATTACK;
	m_nAiPtnData[4] = MON_AI_READY_TO_HIT;
	m_nAiPtnData[5] = MON_AI_MOVE_BACK;

	m_nFlyTimer = FLY_MAXTIME;
	m_nIsFly = 0;

	m_nInit = false;
}



//--------------------------------------------------------------------------------------
LastBoss::~LastBoss()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void LastBoss::SetAttack()
//--------------------------------------------------------------------------------------
{
	m_bIsSuccessAttack = false;

	//MON_ATK_SUMMON_BUG

/*
	m_nUseAtkNum = 3;
	if(0 == m_Attack[m_nUseAtkNum].CoolTime)
	{
		//	총 소환이 10을 넘지 않게 한다.
		if(10 > m_nTotalMonCnt)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}
*/
	

	if(m_nHealState != m_Stet.m_Hp/m_nHealDevide)
	{
		m_nHealState = m_Stet.m_Hp/m_nHealDevide;

		if(0 < m_nHealCount && 9 > m_nHealState)
		{
			m_nHealCount--;
			m_nUseAtkNum = 8;
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}

	if(1 == m_nIsFly)
	{
		m_nUseAtkNum = 7;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 6;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 5;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 4;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}
	else
	{
		m_nUseAtkNum = 3;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 2;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 1;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}

		m_nUseAtkNum = 0;
		if(0 == m_Attack[m_nUseAtkNum].CoolTime)
		{
			m_Attack[m_nUseAtkNum].CoolTime = m_Attack[m_nUseAtkNum].MaxCoolTime;
			return;
		}
	}

}
/*
//--------------------------------------------------------------------------------------
void LastBoss::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	죽은이후는 그리지 않는다.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	//	paint shadow
	//int tmpx = pMonAsIns->Get_AFrameXZ();
	//int tmpy = tmpx%100000;
	//tmpx = tmpx/100000; 

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	//	그림자
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}
*/
//--------------------------------------------------------------------------------------
void LastBoss::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	물리좌표를 갱신받는다.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	이동량이 없으므로 모든 값을 초기화시켜준다.
		m_Physics->initForce();
	}
	else
	{
		//	이동량에 따라 좌표를 보정시켜준다.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	저항상황이라면 (그라운드라면)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	//	자체 타이머를 갖는다.
	m_nTimer= (m_nTimer+1)%1000;

	//	맞았을시 올라가던 히트 레이트를 올려준다.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	공격에 대한 쿨타임을 줄여준다.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	내부 프로세서를 돌린다.
	if(!ExtProcess())	{BaseProcess();}

	//	보스전용 인공지능
	AI_PROCESS_BOSS2(this);
}

//--------------------------------------------------------------------------------------
bool LastBoss::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST 항시전투
	m_bIsBattle = true;

	//	초기화
	if(false == m_nInit)
	{
		m_nOriPower = m_Stet.m_Atk;
		m_nInit = true;
		m_nHealCount = 7;
		m_nHealState = 10;
		m_nHealDevide = m_Stet.m_MaxHp/10;
		m_bPowerMode = false;
	}

	//	추가 상태변화
	//	밀리4는 번개 쓸고 지나가는 액션이다.
	if(MON_ATK_MELEE4 != m_ActState)
	{
		m_nFlyTimer--;
	}
	
	//	플라이 모드
	if(0 > m_nFlyTimer)
	{
		m_nFlyTimer = FLY_MAXTIME;
		m_nIsFly = (m_nIsFly+1)%2;

		if(0 == m_nIsFly)
		{
			m_Stet.m_Atk = m_nOriPower;

			m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
			m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_6_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
			m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_6_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_6_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_6_WALK_VERTICAL;			
		}
		else
		{
			m_Stet.m_Atk = (m_nOriPower*13)/10;			

			m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_FLY_STAND;
			m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_6_FLY_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_FLY_STAND;
			m_nUsingImgIdx[MON_AC_RUN]				= ANIM_BOSS_6_FLY_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_BEHOLD]			= ANIM_BOSS_6_FLY_WALK_VERTICAL;
			m_nUsingImgIdx[MON_AC_RUN_BEHOLD]		= ANIM_BOSS_6_FLY_WALK_VERTICAL;
		}
	}

	//	파워모드
	if(m_bPowerMode)
	{
		int pxx = 16;//31 이 넘으면 안됨
		s_Debuff.color = (s_Debuff.color+1)%pxx;
		int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12)+(s_Debuff.color<<7) : ((pxx-s_Debuff.color)<<12)+((pxx-s_Debuff.color)<<7)); 
		pMonAsIns->SetBlendCustom(true,false,7,pyy);
	}
	else
	{
		if(m_Stet.m_Hp < m_nHealDevide*2)
		{
			
			m_bPowerMode = true;

			//	방어력을 올려준다.
			m_Stet.m_Defance = (m_Stet.m_Defance * 13)/10;

			//	이뮴상태로 만든다.
			m_nFeature |= FE_EMUM;
		}
	}

	//	속성 변환
	switch(m_Stet.m_Hp/(m_nHealDevide*2))
	{
		case 0:	case 1:			{m_nElementIdx = MON_ELEMENTAL_NEUTRAL;	break;}
		case 3:					{m_nElementIdx = MON_ELEMENTAL_WOMAN;	break;}
		case 2:	case 4:	case 5:	{m_nElementIdx = MON_ELEMENTAL_MAN;		break;}
	}

	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_RANGE1:

		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		//case MON_ATK_SUMMON_BUG:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_AC_STAND, 0);
			}
			return true;
		}
		case MON_ATK_MELEE4:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				ResvAction(MON_ATK_MELEE5, 0);
			}
		}
		case MON_ATK_MELEE5:
		//-----------------------------------------------------------
		{
			//	캐릭터의 위치를 이동시켜준다.
			pMonAsIns->m_posX += m_nBeamAdd;

			if(SQR(2) < SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y))
			{
				if(pMonAsIns->m_posY < m_CharInfo->m_nPos.y)				{pMonAsIns->m_posY += 2;}
				else if(pMonAsIns->m_posY > m_CharInfo->m_nPos.y)			{pMonAsIns->m_posY -= 2;}
			}
			
			SUTIL_UpdateTimeAsprite(pMonAsIns);

			m_nBeamTimer--;

			if(0 > m_nBeamTimer)
			{
				ResvAction(MON_AC_STAND, 0);
			}
			break;
		}
		case MON_ATK_SPECIAL1:
		//-----------------------------------------------------------------------
		{
			if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
			{
				//	에너지를 채워준다.
				m_Stet.m_Hp = m_Stet.m_Hp + (m_nHealDevide/2);

				//	다시 힐 상태를 초기화시켜준다.
				m_nHealState = m_Stet.m_Hp/m_nHealDevide;
				ResvAction(MON_AC_STAND, 0);
			}
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
bool LastBoss::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_ActState)
	{
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			return true;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_0);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;
			for(int loop = 0; loop < 4; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_0);
				//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, (SUTIL_GetRandom()%(Field::m_nFieldSize_X) ));
				SUTIL_SetYPosAsprite(tmpAsIns, MAP_MOVE_UP_Y + (SUTIL_GetRandom()%(MAP_MOVE_DOWN_Y-MAP_MOVE_UP_Y) ));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMOVE;
				tmpMonSkill->lifeTime = 63;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = loop*2;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 1;
				tmpMonSkill->damagetime = 1;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			return true;
		}
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_FLY_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_1);
			//SUTIL_UpdateTempXYAsprite(tmpAsIns, APPLY_X);	
			SUTIL_SetLoopAsprite(tmpAsIns, true);
//			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-2);		//	충격파가 캐릭터 밑으로 가게 해준다.
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 9;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 6;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_MELEE4:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_FLY_MELEE_2);
			//SUTIL_SetLoopAsprite(pMonAsIns, true);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			m_nBeamTimer = ABS((m_CharInfo->m_nPos.x - pMonAsIns->m_posX)/BEAM_MOVE_X) + 6;
//			m_nBeamTimer = BEAM_MAXTIME;
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)				{m_nBeamAdd = BEAM_MOVE_X;}
			else if(pMonAsIns->m_posX > m_CharInfo->m_nPos.x)			{m_nBeamAdd = -BEAM_MOVE_X;}

			return true;
		}
		case MON_ATK_MELEE5:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_FLY_MELEE_WALK_VERTICAL);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
//			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
//			else										{m_nDirection = SDIR_LEFT;}
//			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:		//	돌뭉치 떨어뜨림
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_FLY_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			int seed = 8 + SUTIL_GetRandom()%4;
			for(int loop = 0; loop < seed; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 170 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 6+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 200 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 8+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%320 );
				SUTIL_SetYPosAsprite(tmpAsIns, 230 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 7;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			return true;
		}

		case MON_ATK_RANGE4:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_FLY_RANGE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			for(int loop = 0; loop < 2; loop++)
			{
				SetMessage(MSG_SUMMONE_BUGS, SUTIL_GetRandom()%(Field::m_nFieldSize_X),
					MAP_MOVE_UP_Y + (SUTIL_GetRandom()%(MAP_MOVE_DOWN_Y-MAP_MOVE_UP_Y) ),
					m_nDirection, m_nMonIdx, 0);
			}

			return true;
		}
		case MON_ATK_SPECIAL1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_HEAL);
//			SUTIL_SetLoopAsprite(pMonAsIns, true);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}

/*
//--------------------------------------------------------------------------------------
BossMon3_1::BossMon3_1()
//--------------------------------------------------------------------------------------
{
	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 4;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 200;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].MinScope = 0;
	m_Attack[1].MaxScope = 200;

	m_Attack[2].Name = MON_ATK_RANGE2;
	m_Attack[2].MinScope = 0;
	m_Attack[2].MaxScope = 200;

	m_Attack[3].Name = MON_ATK_RANGE3;
	m_Attack[3].MinScope = 0;
	m_Attack[3].MaxScope = 200;



//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

//	m_AIState = MON_AI_STAND;
//	m_nAniIndex = 0;
//	m_nBaseAniIdx = 0;
//	m_nDirection = SDIR_RIGHT;
//	m_nAdjustPos.Init();
//	ResvAction(MON_AC_STAND, 1);
}



//--------------------------------------------------------------------------------------
BossMon3_1::~BossMon3_1()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool BossMon3_1::ExtProcess()
//--------------------------------------------------------------------------------------
{

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	if(m_NextActState != m_ActState || 1 == m_IsAcceptChangeActState)
	{
		m_IsAcceptChangeActState = 0;
		SUTIL_UpdateTempXYAsprite(pMonAsIns, APPLY_X|APPLY_Z);	
		//SUTIL_SetZPosAsprite(pMonAsIns, 0);

		SetAction(m_NextActState);
	}


	//	상태를 변경시켜준다.
	//	SetMessage(MSG_CHANGE_STATE, 0, UNQ_BOSS_3_2_IDX, MON_ATK_MELEE1);

	//	에니메이션 업데이트
	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			default:
			//-----------------------------------------------------------------------
			{
				break;
			}
			case MON_ATK_MELEE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_RANGE1:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_RANGE2:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_RANGE3:
			//-----------------------------------------------------------------------
			{
				ResvAction(MON_AC_STAND, 0);
				break;
			}
		}
	}


	return true;
}


//--------------------------------------------------------------------------------------
void BossMon3_1::Paint()
//--------------------------------------------------------------------------------------
{

	if((MON_AC_DIE == m_ActState) && (m_nTimer < (m_nMaxTimer/2)))	{return;}

	//	paint shadow
	int tmpx = pMonAsIns->Get_AFrameXY();
	int tmpy = tmpx%100000;
	tmpx = tmpx/100000; 

	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_1);

	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

}

//--------------------------------------------------------------------------------------
bool BossMon3_1::ExtSetAction()
//--------------------------------------------------------------------------------------
{

//	if(BaseAction(_nActionState))	{return;}

	m_ActState = _nActionState;
	SUTIL_SetLoopAsprite(pMonAsIns, false);

	switch(m_ActState)
	{
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_BOTTOM_STAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			break;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;
			for(int loop = 0; loop < BOSS3_1_LASERBEAM_COUNT; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BEAM_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+(BOSS3_1_LASERBEAM_SIZE*loop*m_nDirection));
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 33;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 1;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 1;
				tmpMonSkill->damagetime = 6;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			m_nDirection *= (-1);
			for(int loop = 0; loop < BOSS3_1_LASERBEAM_COUNT; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BEAM_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+(BOSS3_1_LASERBEAM_SIZE*loop*m_nDirection));
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 33;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 1;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 2;
				tmpMonSkill->damagetime = 6;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}
			m_nDirection *= (-1);

			break;
		}
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;
			for(int loop = 0; loop < 8; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_BULLET_2);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+(15*(SUTIL_GetRandom()%20-10)));
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+100+(10*(SUTIL_GetRandom()%10-5)));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 11;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+(SUTIL_GetRandom()%20);
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 3;
				tmpMonSkill->damagetime = 6;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			break;
		}
		case MON_ATK_RANGE3:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
	}


	return false;
}


//--------------------------------------------------------------------------------------
void BossMon3_1::GetMessage()
//--------------------------------------------------------------------------------------
{
}


//==============================================================================================================




//--------------------------------------------------------------------------------------
BossMon3_2::BossMon3_2()
//--------------------------------------------------------------------------------------
{
	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	m_nAtkMaxCount = 4;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
	m_Attack[0].MinScope = 0;
	m_Attack[0].MaxScope = 45;

	m_Attack[1].Name = MON_ATK_RANGE1;
	m_Attack[1].MinScope = 0;
	m_Attack[1].MaxScope = 45;

	m_Attack[2].Name = MON_ATK_RANGE2;
	m_Attack[2].MinScope = 0;
	m_Attack[2].MaxScope = 45;

	m_Attack[3].Name = MON_ATK_SUMMON;
	m_Attack[3].MinScope = 0;
	m_Attack[3].MaxScope = 45;

//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;

//	m_AIState = MON_AI_STAND;
//	m_nAniIndex = 0;
//	m_nBaseAniIdx = 0;
//	m_nDirection = SDIR_RIGHT;
//	m_nAdjustPos.Init();

//	ResvAction(MON_ATK_SUMMON, 1);
}



//--------------------------------------------------------------------------------------
BossMon3_2::~BossMon3_2()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool BossMon3_2::ExtProcess()
//--------------------------------------------------------------------------------------
{

	//	캐릭터의 좌표를 갱신시켜준다.
	m_CharInfo = _CharInfo;

	if(m_NextActState != m_ActState || 1 == m_IsAcceptChangeActState)
	{
		m_IsAcceptChangeActState = 0;
		SUTIL_UpdateTempXYAsprite(pMonAsIns, APPLY_X|APPLY_Z);	
		//SUTIL_SetZPosAsprite(pMonAsIns, 0);

		SetAction(m_NextActState);
	}



//	if(!BaseProcess())
//	{
		if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
		{
			switch(m_ActState)
			{
				default:
				//-----------------------------------------------------------------------
				{
					break;
				}
				case MON_ATK_MELEE1:
				case MON_ATK_RANGE1:
				case MON_ATK_RANGE2:
				case MON_ATK_SUMMON:
				//-----------------------------------------------------------------------
				{
					//ResvAction(MON_AC_STAND, 0);
					ResvAction(MON_ATK_SUMMON, 1);
					break;
				}
			}
		}
//	}

//	AI_PROCESS(this);


	return true;
}


//--------------------------------------------------------------------------------------
void BossMon3_2::Paint()
//--------------------------------------------------------------------------------------
{

	if((MON_AC_DIE == m_ActState) && (m_nTimer < (m_nMaxTimer/2)))	{return;}

	//	paint shadow
	int tmpx = pMonAsIns->Get_AFrameXY();
	int tmpy = tmpx%100000;
	tmpx = tmpx/100000; 

	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_1);

	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);

}

//--------------------------------------------------------------------------------------
bool BossMon3_2::ExtSetAction()
//--------------------------------------------------------------------------------------
{

	m_ActState = _nActionState;
	SUTIL_SetLoopAsprite(pMonAsIns, false);

	switch(m_ActState)
	{
		case MON_AC_READY:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_TOP_STAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			break;
		}
		case MON_AC_STAND:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_T_ROBOT_STAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			break;
		}
		case MON_ATK_MELEE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_T_MELEE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_RANGE1:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_T_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;
			for(int loop = 0; loop < BOSS3_2_LASERBEAM_COUNT; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_T_BEAM_1);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+(loop*BOSS3_2_LASERBEAM_SIZE));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 4;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 14;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 1;
				tmpMonSkill->damagetime = 6;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			break;
		}
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_T_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();


			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;

			int BulletSet[8][2] = {{-32,-66},{-53,-54},{-53,-40},{-32,-28},{23,-66},{44,-54},{44,-40},{23,-28}};
			int BulletMove[8][2] = {{-6,-4},{-8,-3},{-8,+3},{-6,+4},{6,-4},{8,-3},{8,+3},{6,+4}};

			for(int loop = 0; loop < 8; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_3_T_BULLET_2);
				SUTIL_SetDirAsprite(tmpAsIns, m_nDirection);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX+BulletSet[loop][0]+5);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+BulletSet[loop][1]+40);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMOVE;
				tmpMonSkill->lifeTime = 20;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 6;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 2;
				tmpMonSkill->damagetime = 6;
				tmpMonSkill->Movex = BulletMove[loop][0];
				tmpMonSkill->Movey = BulletMove[loop][1];
				tmpMonSkill->Movez = 0;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			break;
		}
		case MON_ATK_SUMMON:
		//-----------------------------------------------------------
		{	
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_T_ROBOT_SUMMON);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	상태를 변경시켜준다.
			SetMessage(MSG_SUMMONE_BABY, UNQ_BOSS_3_BABY, pMonAsIns->m_posX, pMonAsIns->m_posY, pMonAsIns->m_posZ-60, 11);
			SetMessage(MSG_SUMMONE_BABY, UNQ_BOSS_3_BABY, pMonAsIns->m_posX, pMonAsIns->m_posY, pMonAsIns->m_posZ-60, 17);
			SetMessage(MSG_SUMMONE_BABY, UNQ_BOSS_3_BABY, pMonAsIns->m_posX, pMonAsIns->m_posY, pMonAsIns->m_posZ-60, 23);
			
			break;
		}
	}


	return false;
}


//--------------------------------------------------------------------------------------
void BossMon3_2::GetMessage()
//--------------------------------------------------------------------------------------
{
}

*/
///////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////
//assist function
/*
//--------------------------------------------------------------------------------------
Monster2::Monster2()
//--------------------------------------------------------------------------------------
{
	m_nActionCount = 0;
}


//--------------------------------------------------------------------------------------
Monster2::~Monster2()
//--------------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------------
void Monster2::SetDirection(int _dir)
//--------------------------------------------------------------------------------------
{
	m_nDirection = _dir;
	SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
}


//--------------------------------------------------------------------------------------
void Monster2::InitPhysics()
//--------------------------------------------------------------------------------------
{
	m_Physics->initForce();
	pMonAsIns->m_posZ = 0;
}

//--------------------------------------------------------------------------------------
void Monster2::GetSpritePosition()
//--------------------------------------------------------------------------------------
{
	pMonAsIns->m_posX = SUTIL_GetXPosAsprite(pMonAsIns);
	pMonAsIns->m_posY = SUTIL_GetYPosAsprite(pMonAsIns);
	pMonAsIns->m_posZ = SUTIL_GetZPosAsprite(pMonAsIns);
}

//--------------------------------------------------------------------------------------
void Monster2::SetSpritePosition()
//--------------------------------------------------------------------------------------
{
	 SUTIL_SetXPosAsprite(pMonAsIns, pMonAsIns->m_posX);
	 SUTIL_SetYPosAsprite(pMonAsIns, pMonAsIns->m_posY);
	 SUTIL_SetZPosAsprite(pMonAsIns, pMonAsIns->m_posZ);
}


//--------------------------------------------------------------------------------------
int Monster2::SetMovingTime(int Moving, int sqrDstValue)
//--------------------------------------------------------------------------------------
{
	if(0 == Moving)	{return 0;}
	int rtnValue = 0;
	while(1)
	{
		rtnValue++;
		if(SQR(rtnValue*Moving) > sqrDstValue)
		{
			return rtnValue;
		}
	}
	return 0;
}


//--------------------------------------------------------------------------------------
//int Monster2::RegiesterState( void (*_ActionProcFuncPtr)() )
int Monster2::RegiesterState( int action )
//--------------------------------------------------------------------------------------
{
	switch(action)
	{
		case ACT_MOVE:
		//-----------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,0);
			SUTIL_SetLoopAsprite(pMonAsIns, true);

			if(0 < m_nMoveVec.x)		{SetDirection(SDIR_RIGHT);}
			else if(0 > m_nMoveVec.x)	{SetDirection(SDIR_LEFT);}

			InitPhysics();
			
			break;
		}
	}

	m_nActionCount++;
	if(MAX_ACTION_SIZE <= m_nActionCount )	{return 0;}

	//m_ActionProcFuncPtr[m_nActionCount] = _ActionProcFuncPtr;
	return m_nActionCount;
}



//--------------------------------------------------------------------------------------
void Monster2::ACTION_PROCESS()
//--------------------------------------------------------------------------------------
{
	// 계산
	if(m_nResvAction)
	{
		m_ActionProcFuncPtr[m_nCurAction];
	}

	m_ActionProcFuncPtr[m_nCurAction];
	SetSpritePosition();		//	좌표를 갱신시켜준다.
}


//--------------------------------------------------------------------------------------
void Monster2::ACTION_PAINT()
//--------------------------------------------------------------------------------------
{
	//	paint shadow
	int tmpx = pMonAsIns->Get_AFrameXY();
	int tmpy = tmpx%100000;
	tmpx = tmpx/100000; 

	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);
	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);
	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
}

//	action define


//--------------------------------------------------------------------------------------
void Monster2::ACTION_MOVE_SET()
//--------------------------------------------------------------------------------------
{
	SUTIL_SetTypeAniAsprite(pMonAsIns,0);
	SUTIL_SetLoopAsprite(pMonAsIns, true);

	if(0 < m_nMoveVec.x)		{SetDirection(SDIR_RIGHT);}
	else if(0 > m_nMoveVec.x)	{SetDirection(SDIR_LEFT);}

	InitPhysics();
}


//--------------------------------------------------------------------------------------
void Monster2::ACTION_MOVE_PROCESS()
//--------------------------------------------------------------------------------------
{
	//	이전 에니의 프레임의 이동량을 가져온다.
	int off = (pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule-1] + pMonAsIns->m_nCrtFrame) * 5;
	int nMove =  pMonAsIns->m_sprite->_aframes[off + 3];

	int nTotalMoveCount = SetMovingTime(nMove, m_nMoveVec.Sqr_GetLength());

	//	한번에 이동할수 있는 거리라면
	if(1 == nTotalMoveCount)
	{
		m_nPos = m_nPos + m_nMoveVec;
	}
	else
	{
		m_nPos = m_nPos + ((((m_nMoveVec)*100)/nTotalMoveCount)/100);
	}

	m_nMoveVec = m_nMoveVec - m_nPos;
}


//--------------------------------------------------------------------------------------
void Monster2::ACTION_MOVE_PAINT()
//--------------------------------------------------------------------------------------
{
}


*/


/*

			m_nCurMovingTick++;
			m_AddPos.Init();

			pMonAsIns->m_posX = SUTIL_GetXPosAsprite(pMonAsIns);
			pMonAsIns->m_posY = SUTIL_GetYPosAsprite(pMonAsIns);
			pMonAsIns->m_posZ = SUTIL_GetZPosAsprite(pMonAsIns);

			//	이전 에니의 프레임의 이동량을 가져온다.
			int off = (pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule-1] + pMonAsIns->m_nCrtFrame) * 5;
			m_nMaxMove =  pMonAsIns->m_sprite->_aframes[off + 3];

			m_nCurMovingTick = 1;
			m_nMaxMovingTick = SetMovingTime(m_nMaxMove, m_MoveValue.Sqr_GetLength());

			if(0 < m_nMaxMovingTick)
			{
				if(m_nCurMovingTick == m_nMaxMovingTick)
				{
					m_AddPos = m_MoveValue;
				}
				else
				{
					m_AddPos = m_AddPos + ((((m_MoveValue*m_nCurMovingTick)*100)/m_nMaxMovingTick)/100);
				}
			}
			else	//	움직임이 없을땐 항상 z값은 0이다.
			{
				pMonAsIns->m_posZ = 0;
			}
			
			//m_nPos = m_SrcPos + m_AddPos;
			m_nPos = m_nPos + m_AddPos;

			if(m_nIsBattle)
			{
				if(m_CharInfo->m_nPos.x < pMonAsIns->m_posX)		{m_nDirection = SDIR_LEFT;}
				else if(m_CharInfo->m_nPos.x > pMonAsIns->m_posX)	{m_nDirection = SDIR_RIGHT;}
				SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			}
*/


/*
			PhysicsPos = m_Physics->process();

			m_nPos = PhysicsPos;
			pMonAsIns->m_posX += SUTIL_GetXPosAsprite(pMonAsIns);
			pMonAsIns->m_posY += SUTIL_GetYPosAsprite(pMonAsIns);
			pMonAsIns->m_posZ += SUTIL_GetZPosAsprite(pMonAsIns);

			int tmpAniState = 3;

			if(0 > PhysicsPos.z)													//	up
			{
				if(1 == m_nIsUpperAtk)
				{
					tmpAniState = 0;
				}
				else
				{
					tmpAniState = 3;
				}
			}
			else if(0 < PhysicsPos.z)	
			{
				m_nIsUpperAtk = 0;
				//if(0 < (m_Physics->Movetotal.z))									//	bounce
				if(0 < (pMonAsIns->m_posZ))									//	bounce
				{
//					m_Physics->Movetotal.z = 0;
//					pMonAsIns->m_posZ -= (m_Physics->Movetotal.z);
					pMonAsIns->m_posZ = 0;
					m_Physics->SaveGrAccel.z = UP_GRV;
					m_Physics->setGrForce(m_Physics->SaveGrAccel);
					m_Physics->setRebound();
					if(-20 < m_Physics->SaveAccel.z)		{tmpAniState = 4;}
					else									{tmpAniState = 2;}		//	after bounce
				}
				else
				{
					m_Physics->SaveGrAccel.z = DOWN_GRV;
					m_Physics->setGrForce(m_Physics->SaveGrAccel);
					tmpAniState = 1;
				}
			}

			if(tmpAniState != m_nAniIndex)
			{
				m_nAniIndex = tmpAniState;
				SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON03_FLY_1+m_nAniIndex+m_nBaseAniIdx);
			}
*/

/*
//--------------------------------------------------------------------------------------
void Mon_GHOST::Paint()
//--------------------------------------------------------------------------------------
{
	if((MON_AC_DIE == m_ActState) && (m_nTimer < (m_nMaxTimer/2)))	{return;}

	//	paint shadow
	int tmpx = pMonAsIns->Get_AFrameXY();
	int tmpy = tmpx%100000;
	tmpx = tmpx/100000; 

	pShaodwAsIns->SetFrame(FRAME_SHADOW_SHADOW_3);

	SUTIL_SetXPosAsprite(pShaodwAsIns,	tmpx);
	SUTIL_SetYPosAsprite(pShaodwAsIns,	SUTIL_GetYPosAsprite(pMonAsIns)-2);

	SUTIL_PaintAsprite(pShaodwAsIns, S_NOT_INCLUDE_SORT);

	//	paint monster
	SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
}
*/

/*
	if(MON_ATK_LASERBEAM != m_ActState)
	{
		MoveHead(m_MonSkillList);
		MoveNext(m_MonSkillList);
		while(NotEndList(m_MonSkillList))
		{
			if(2 == GetData(m_MonSkillList)->skillnum)
			{
				if(GetData(m_MonSkillList)->who == (void*)this)
				{
					GetData(m_MonSkillList)->lifeTime = 0;
				}
			}
			MoveNext(m_MonSkillList);
		}
	}
*/