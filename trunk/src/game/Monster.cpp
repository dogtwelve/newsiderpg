#include "Monster.h"


int Monster::m_nTotalMonCnt = 0;
int Monster::UniqueIdx = 0;
int BossMon5_1::m_nNowDownCool = 0;
int BossMon5_1::m_nBossStep = 0;		//	stand, down, sit, 

int BossMon5_1::m_nMaxLegHp = 0;
int BossMon5_1::m_nNowLegHp = 0;
//int Monster::m_nExtraDamage = 0;

int BossMon5_1::m_nCoreHp = 0;
int BossMon5_1::m_nMaxCoreHp = 0;

int BossMon5_1::m_nMaxFaceLeftArmHp = 0;
int BossMon5_1::m_nMaxFaceRightArmHp = 0;
int BossMon5_1::m_nFaceLeftArmHp = 0;
int BossMon5_1::m_nFaceRightArmHp = 0;

bool BossMon5_1::isJumpChar = false;
//int BossMon5_1::m_nPassbleJumpTimer = 0;

int BossMon5_1::m_nspikeTimer = 0;

int BossMon5_1::m_nFaintHp = 0;
int BossMon5_1::m_nMaxFaintHp = 0;

int	BossMon5_1::m_nMoveValue = 0;




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

	//	���� �ν� ����
	m_nRange_InBattle	= 100;			
	m_nRange_OutBattle	= 500;			//	���� ���� ����
	m_nRange_OutAction	= 400;			//	�׼� ���� ����(������ Ǯ��)
	m_nRange_Heal		= 250;			//	�Ʊ��� ���� �ʿ��ϴٴ°��� �ν��ϴ� ����
	m_nRange_HealAction	= 150;			//	�� �׼��� ������ ����

	//	����� �̹����� �����Ѵ�.
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

	s_ASpriteSet = (ASpriteSet*)s__ASpriteSet; // �׸���,ȿ�� ����Ʈ ��������Ʈ�� ������

	_ins_Debuff = GL_NEW ASpriteInstance(s_ASpriteSet->pDebuffAs, 100, 200, NULL);//����� �ν��Ͻ�

	//	���� ��������Ʈ �ε�
	ASprite* TmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_MON, m_nSpriteIdx);

	//	���� ����
	int blendnum[SPRITE_MON_MAX] = 
	{
		FRAME_MON01_BLEND, FRAME_MON02_BLEND, FRAME_MON03_BLEND, FRAME_MON04_BLEND,	FRAME_MON05_BLEND,
		FRAME_MON06_BLEND, FRAME_MON07_BLEND, FRAME_MON08_BLEND, FRAME_MON09_BLEND, FRAME_MON10_BLEND,
		FRAME_MON11_BLEND, FRAME_MON12_BLEND, FRAME_MON13_BLEND, FRAME_MON14_BLEND, FRAME_MON15_BLEND,
		FRAME_MON16_BLEND, FRAME_MON17_BLEND, FRAME_MON18_BLEND, FRAME_MON19_BLEND, FRAME_BOSS_1_BLEND,
		FRAME_BOSS_2_BLEND,	FRAME_BOSS_3_BLEND, FRAME_BOSS_4_BLEND, FRAME_BOSS_5_BLEND, FRAME_BOSS_6_BLEND,
		FRAME_BOSS_7_BLEND,	FRAME_MON_BARREL_BLEND
	};

	if(0 != blendnum[m_nSpriteIdx])	{TmpAsprite->SetBlendFrame(blendnum[m_nSpriteIdx]);}


	pMonAsIns = GL_NEW ASpriteInstance(TmpAsprite, 0, 0, NULL);// 0��° �迭, �ǻ��ô� define �ʿ�

	//	������ �� ����
}


//--------------------------------------------------------------------------------------
void Monster::SetRegenType(int type, int regenIdx, int baseX, int baseY)
//--------------------------------------------------------------------------------------
{
	m_nRegenIdx = regenIdx;

	switch(type)
	{
		case 1:		//	�� �ڸ����� ��������.
		{
//			m_AIState = MON_AI_STAND;
			m_StartPos.x = pMonAsIns->m_posX;
			m_StartPos.y = pMonAsIns->m_posY;
			break;
		}
		case 2:		//	�����ϸ鼭 �����Ѵ�.
		{
//			m_AIState = MON_AI_RETURN_BASE;
			m_StartPos.x = baseX;
			m_StartPos.y = baseY;
			break;
		}
		case 3:		//	������忡�� �����Ѵ�.
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

	//	�÷�����
	pMonAsIns->m_pal = color;

//	SUTIL_SetZPosAsprite(pMonAsIns, z);
//	SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);


	//	makeStet
	int RectData[4];
	SUTIL_GetASpriteAniRect(RectData, pMonAsIns->m_sprite, 0, 0);		// ������ ����
	m_Stet.m_Width = RectData[2]-RectData[0];
	m_Stet.m_Height = RectData[3]-RectData[1];

//	m_Stet.m_Name = MonBaseStet[m_Stet.m_BaseStetNum][STET_NAME];
//	m_Stet.m_Height = MonBaseStet[m_Stet.m_BaseStetNum][STET_HEIGHT]; 
//	m_Stet.m_Elemental = MonBaseStet[m_Stet.m_BaseStetNum][STET_ELEMENT];
	
	//((5+(���ͷ�-1)*4)*3+6+(���ͷ�-1)*1)*10
	//	�⺻ ü���� ���Ѵ�.
	m_Stet.m_MaxHp = ((5+(m_nLevel-1)*4)*3+6+(m_nLevel-1)*1)*10;
	
	//	������ ��� ����(�Ϲ�~����ũ)
	m_Stet.m_MaxHp = (m_Stet.m_MaxHp * MonBaseGradeStet[m_GradeData][GRADE_ADD_HP]) / 100;

	//	������ ���� ����(���� ��ȣ)
	m_Stet.m_MaxHp = (m_Stet.m_MaxHp * MonPtn[m_PtnIdx][STET_HP_RATE]) / 100;

	m_Stet.m_Hp = m_Stet.m_MaxHp;

	m_Stet.m_Atk = ((8+(m_nLevel-1)*3)*15)/8;

	if(MON_IDX_BIGDOG1 == m_nMonIdx)
	{
		BossMon5_1::m_nMaxLegHp = m_Stet.m_Hp/20;
		BossMon5_1::m_nNowLegHp = BossMon5_1::m_nMaxLegHp;
		BossMon5_1::m_nMaxCoreHp = m_Stet.m_Hp/20;
		BossMon5_1::m_nCoreHp = BossMon5_1::m_nMaxCoreHp;

		BossMon5_1::m_nMaxFaceLeftArmHp = m_Stet.m_Hp/20;
		BossMon5_1::m_nMaxFaceRightArmHp = m_Stet.m_Hp/20;

		BossMon5_1::m_nFaceLeftArmHp = BossMon5_1::m_nMaxFaceLeftArmHp;
		BossMon5_1::m_nFaceRightArmHp = BossMon5_1::m_nMaxFaceRightArmHp;

		BossMon5_1::m_nMaxFaintHp = m_Stet.m_Hp/20;
		BossMon5_1::m_nFaintHp = BossMon5_1::m_nMaxFaintHp;
	}

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

		//	�ΰ����ɿ��� �˷��ش�.
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

		//	�ΰ����ɿ��� �˷��ش�.
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


	//	��ݷ��� �������� ������ �������� ���� ��Ȳ
	//	���ܻ�Ȳ
	if(0 == _Power.Sqr_GetLength())
	{
		if(MON_AC_RCV_HOLDING == m_ActState || MON_AC_RCV_HOLDING_SKY == m_ActState)	{return true;}
	}

	if(MON_AC_RCV_HOLDING_DOWN == m_ActState && m_NextActState != MON_AC_ING_AIRDOWN)
	{
		return true;
	}

	//	������ ���� ī��Ʈ�� �÷��ش�.
	m_nAccumulatedHit++;
	m_nHitRate = 0;

	//	�ΰ����ɿ��� �˷��ش�.
	AI_RECEIVE_DEMEGE(this);

	//	���ο��
	if(MON_ATK_BURROW == m_ActState)	{return true;}
	if(MON_ATK_UNBURROW == m_ActState)	{return true;}
	//	���ο�ÿ��� 3�� �̻� ������ ���ο찡 Ǯ����.
	if(MON_ATK_BURROWED == m_ActState)
	{
		if(2 < m_nAccumulatedHit)	{ResvAction(MON_ATK_UNBURROW, 1);}
		return true;;
	}

	//	�� ���� ����
	m_nResvPower = _Power;
	if(m_CharInfo == NULL)return true;//��ȣ�� �̺�å >��<;; �ذ�ǽ� ���� ��Ź
	SetDirection(m_CharInfo->m_Direction * (-1));

//	MC_knlPrintk((signed char*)"force : %d, %d, %d \n", m_nResvPower.x, m_nResvPower.y, m_nResvPower.z);

	//	����ó��
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
		m_nMonIdx == MON_IDX_BIGDOG4)		//	����5�� �ٸ����
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nNowLegHp -= heroDamage;		//	�ٸ��� ���� �������� �����Ų��.
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG2 ||			//	�Ӹ� ������		���� ����
		m_nMonIdx == MON_IDX_BIGDOG3 ||
		m_nMonIdx == MON_IDX_BIGDOG6 ||
		m_nMonIdx == MON_IDX_BIGDOG7 ||
		m_nMonIdx == MON_IDX_BIGDOG8	)
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG5)			//	 �ھ����
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nCoreHp -= heroDamage;
		return;
	}

	else if(m_nMonIdx == MON_IDX_BIGDOG9)			//	 ���� ���ȵ�����
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nFaceLeftArmHp -= heroDamage;
		return;
	}
	else if(m_nMonIdx == MON_IDX_BIGDOG10)			//	 ���� �����ȵ�����
	{
		BossMon5_1::m_nFaintHp -= heroDamage;
		Monster::m_nExtraDamage += heroDamage;
		BossMon5_1::m_nFaceRightArmHp -= heroDamage;
		return;
	}
//	else if(m_nMonIdx == MON_IDX_BIG_DRAGON1 ||
//		m_nMonIdx == MON_IDX_BIG_DRAGON2 ||
//		m_nMonIdx == MON_IDX_BIG_DRAGON3)			//	 �巡�� ���� �ǻ���
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

	//	���ݷ� ���
	int tmpAtk = m_Stet.m_Atk;

	if(0 < nResvNextAtk)
	{
		tmpAtk = (tmpAtk * MonPtn[m_PtnIdx][STET_ATK_1+nResvNextAtk]/100);		//	0 �⺻����, 1 ù��°����, 2�ι�°����
	}
	tmpAtk = (tmpAtk * MonBaseGradeStet[m_GradeData][GRADE_ADD_ATK]/100);

	//������ ���
	tmpAtk = MAX(tmpAtk/8, (tmpAtk*heroDefense/100));

	//	������ ����
	//���� �� ����		 <  5��      : ���ݷ� -30%
    //		             >= 5��      : ���ݷ� +40%
	int tmpLevelDis = m_nLevel - heroLevel;
	if(tmpLevelDis < -5)		{tmpAtk = (tmpAtk * 30) / 100;}
	else if(tmpLevelDis > 5)	{tmpAtk = (tmpAtk * 140) / 100;}

	//	�Ӽ��� ���� ������ ������ �ʿ���

	switch(m_nElementIdx)
	{
		case MON_ELEMENTAL_STONE:
			switch(heroElemental)
			{
				case MON_ELEMENTAL_SNIPS:	tmpAtk = (tmpAtk * 130/100);	break;
				case MON_ELEMENTAL_PAPER:	tmpAtk = (tmpAtk * 40/100);		break;
			}
			break;
		case MON_ELEMENTAL_SNIPS:
			switch(heroElemental)
			{
				case MON_ELEMENTAL_STONE:	tmpAtk = (tmpAtk * 40/100);		break;
				case MON_ELEMENTAL_PAPER:	tmpAtk = (tmpAtk * 130/100);	break;
			}
			break;
		case MON_ELEMENTAL_PAPER:
			switch(heroElemental)
			{
				case MON_ELEMENTAL_STONE:	tmpAtk = (tmpAtk * 130/100);	break;
				case MON_ELEMENTAL_SNIPS:	tmpAtk = (tmpAtk * 40/100);		break;
			}
			break;
	}

	return tmpAtk;
}

//--------------------------------------------------------------------------------------
void Monster::RCV_Debuff(int Debuff_Type)
//--------------------------------------------------------------------------------------
{
	if(Debuff_Type == 0)//������� ������ ����
		return;

	s_Debuff.All |=  Debuff_Type;//������� ��� �߰��� �ش�
	s_Debuff.color = 0;//����� �÷� �ʱ�ȭ
	bool novice = true;
	for(int xx = 0;xx<3;xx++){//������ ������߿� �ߺ��� �Ǵ��� �˻��Ѵ�.
		if(s_Debuff.stack[xx][0]==Debuff_Type){//�̹� �ִٸ� �װ��� 0���� ��ġ�� �ٲ��ش�(�űԷ� ���)
			novice = false;

			short yy = s_Debuff.stack[0][0];
			s_Debuff.stack[0][0] = s_Debuff.stack[xx][0];
			s_Debuff.stack[xx][0] = yy;

			s_Debuff.stack[xx][1] = s_Debuff.stack[0][1];
			s_Debuff.stack[0][1] = 0;//����� Ÿ�̸� �ʱ�ȭ
			break;
		}
	}
	if(novice){//�ߺ��� �ƴ϶�� 0��°�� ������ش�

		if(s_Debuff.stack[2][0])s_Debuff.All -= s_Debuff.stack[2][0];//������ ������ ���� ������ ������Ų��

		s_Debuff.stack[2][0] = s_Debuff.stack[1][0];
		s_Debuff.stack[2][1] = s_Debuff.stack[1][1];
		s_Debuff.stack[1][0] = s_Debuff.stack[0][0];
		s_Debuff.stack[1][1] = s_Debuff.stack[0][1];
		// �ϳ��� �ڷ� �о Ȯ���� 0���� �� ���
		s_Debuff.stack[0][0] = Debuff_Type;
		s_Debuff.stack[0][1] = 0;
	}
	switch(Debuff_Type){// �������� ó���� �ϴºκ� 
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

	if(m_nSpriteIdx == SPRITE_MON_BOSS_5 || m_nSpriteIdx == SPRITE_MON_BOSS_6)
	{

	}
	else
	{
		if(NULL != (DEBUF_WEAK & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_WEAK;}
		if(NULL != (DEBUF_ICE & m_Attack[m_nUseAtkNum].Debuff))			{return DEBUF_ICE;}
		if(NULL != (DEBUF_FREEZE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_FREEZE;}
		if(NULL != (DEBUF_STUN & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_STUN;}
		if(NULL != (DEBUF_STONE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_STONE;}
		if(NULL != (DEBUF_POISON & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_POISON;}
		if(NULL != (DEBUF_CONFUSE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_CONFUSE;}
		if(NULL != (DEBUF_VAMPIRE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_VAMPIRE;}
		if(NULL != (DEBUF_DE_VAMPIRE & m_Attack[m_nUseAtkNum].Debuff))	{return DEBUF_DE_VAMPIRE;}
		if(NULL != (DEBUF_MANABURN & m_Attack[m_nUseAtkNum].Debuff))	{return DEBUF_MANABURN;}
		if(NULL != (DEBUF_SILENCE & m_Attack[m_nUseAtkNum].Debuff))		{return DEBUF_SILENCE;}
	}

	return 0;
}

//--------------------------------------------------------------------------------------
int Monster::SND_Exp(int heroLevel)
//--------------------------------------------------------------------------------------
{
	if((m_nFeature & FE_DONT_GIVE_EXP))	{return 0;}

	// 8*((���ͷ�*2))+10/���ͷ� + ���� ���� ������ �߰�ġ(%) + ��� ������ �߰�ġ(%)
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

	if(0 == HoldType)	//	�Ϲ� ���
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
	else if(1 == HoldType)		//	�������
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;

		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}
	
	//	���� ���μ����� ������.
	if(!ExtProcess())
	{
		BaseProcess();

		if(false == m_bIsPanic)
		{
			AI_PROCESS(this);
		}
	}

	

//	// ��ǥ�� ������Ʈ �����ش�.
//	SUTIL_SetXPosAsprite(pMonAsIns, pMonAsIns->m_posX);
//	SUTIL_SetYPosAsprite(pMonAsIns, pMonAsIns->m_posY);
//	SUTIL_SetZPosAsprite(pMonAsIns, pMonAsIns->m_posZ);
}

//--------------------------------------------------------------------------------------
bool Monster::BaseProcess()
//--------------------------------------------------------------------------------------
{
	//	�������� ���� �ٿ��� �����ش�.
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
		case MON_AC_RCV_HOLDING_SKY:
		case MON_AC_STAND:
		case MON_AC_RCV_HOLDING_DOWN:
		case MON_AC_RCV_HOLDING:
		case MON_AC_RCV_DOWN_ATTACK:
		case MON_AC_ING_DOWN:
		case MON_AC_RCV_AIR_ATTACK:
		case MON_AC_AWAK:
		case MON_AC_RCV_GROUND_ATTACK:				{break;}
		case MON_AC_READY:
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
			//	���� ������ �������� �̵����� �����´�.
			int off = (pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule-1] + pMonAsIns->m_nCrtFrame) * 5;
			int nMove =  pMonAsIns->m_sprite->_aframes[off + 3];

			//	�̵����� ������츸 �̵����ش�.
			if(0 < nMove)
			{
				int nTotalMoveCount = SetMovingTime(nMove, m_nMoveVec.Sqr_GetLength());
				Position3D m_nDstVec;

				//	�ѹ��� �̵��Ҽ� �ִ� �Ÿ����
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

				//	��ǥ ����(y���� �Ѿ�� �ʵ��� �Ѵ�.)
				if(255 < pMonAsIns->m_posY)	{pMonAsIns->m_posY = 255;}
				if(180 > pMonAsIns->m_posY)	{pMonAsIns->m_posY = 180;}

				m_nMoveVec = m_nMoveVec - m_nDstVec;
			}

			//	�̵��Ÿ��� ���̶�� stand���·� ���ư���.
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

	//	���ϸ��̼��� ������Ʈ���ش�.
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
					// �дл��¸� Ǯ���ش�.
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
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
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

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
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
	//	���ϸ��̼��� ������ ��ǥ�� Ȯ�����´�.
	//SUTIL_UpdateTempXYAsprite(pMonAsIns, APPLY_X|APPLY_Z);

	//	���Ž� Ư�̻����� ����Ѵ�. (���� ��ǥ ����)
	switch(m_ActState)
	{
		case MON_AC_RCV_GROUND_ATTACK:
		//----------------------------------------------------------------------
		{
			//	���ִ� ���͵鶧���� z���� 0���� �����Ѵ�.
			SUTIL_SetZPosAsprite(pMonAsIns, 0);	
			break;
		}
	}

	//	�ֽ� ��ǥ�� ���Ź޴´�.
//	pMonAsIns->m_posX = SUTIL_GetXPosAsprite(pMonAsIns);
//	pMonAsIns->m_posY = SUTIL_GetYPosAsprite(pMonAsIns);
//	pMonAsIns->m_posZ = SUTIL_GetZPosAsprite(pMonAsIns);

	//	���� �ʱ�ȭ
	m_nTimer = 0;
	m_nAniIndex = 0;
	SUTIL_SetLoopAsprite(pMonAsIns, false);

	//	���� �ʱ�ȭ
	m_Physics->initForce();

	//	�߷� ����
	Position3D Force;
	Force.Init(0,0,UP_GRV);
	m_Physics->setGrForce(Force);

	//	����� �� ����
	m_Physics->setForce(m_nResvPower);
	m_nResvPower.Init();

	//  ����� ���� ����
	m_Physics->setReForce(m_nResvResist);
	m_nResvResist.Init();

	//	�׼��� �����Ѵ�.
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

			//	�������� ���� �������ش�.
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
			
			//	������ �����ش�.
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

			//	��ǥ�� ���������� �������ش�.
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
{// ����� ����Ʈ�� �׸���

	if(!s_Debuff.All)//������� �ϳ��� �ɷ������ʴٸ� 
		return;


	_ins_Debuff->m_posX = drawX;
	_ins_Debuff->m_posY = pMonAsIns->m_posY;
	char m_tempZ = drawZ;//pMonAsIns->m_sprite->_aframes[((pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule] + pMonAsIns->m_nCrtFrame) * 5)+3] & 0xFF;
	_ins_Debuff->m_posZ = m_tempZ;
	//_ins_Debuff->m_posZ = m_posZ - HERO_HEIGHT;

	_ins_Debuff->CameraX = pMonAsIns->CameraX;
	_ins_Debuff->CameraY = pMonAsIns->CameraY;




	for(int xx =0;xx<3;xx++){//������� ������ �׷������� ����
		if(xx < 2 && s_Debuff.stack[xx][0] == 0){
			s_Debuff.stack[xx][0] = s_Debuff.stack[xx+1][0];
			s_Debuff.stack[xx][1] = s_Debuff.stack[xx+1][1];
			s_Debuff.stack[xx+1][0] = 0;
			s_Debuff.stack[xx+1][1] = 0;
		}


		if(s_Debuff.stack[xx][0]){
			switch(s_Debuff.stack[xx][0]){
					case DEBUF_WEAK://��ȭ
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 16;//31 �� ������ �ȵ�
							s_Debuff.color = (s_Debuff.color+1)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12)+(s_Debuff.color<<7) : ((pxx-s_Debuff.color)<<12)+((pxx-s_Debuff.color)<<7)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
						}
						if(s_Debuff.stack[xx][1] > 100){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}

						break;
					case DEBUF_ICE://���̽�
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_COLD){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_COLD);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 31;//31 �� ������ �ȵ�
							s_Debuff.color = (s_Debuff.color+2)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<1)); 
							//int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<11)+(s_Debuff.color<<6)+(s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<11)+((pxx-s_Debuff.color)<<6)+((pxx-s_Debuff.color)<<1)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
						}
						if(s_Debuff.stack[xx][1] > 30){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_FREEZE://����
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_FREEZ_1 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_FREEZ_3){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_FREEZ_1);
								_ins_Debuff->m_bLoop = false;
							}else if(s_Debuff.stack[xx][1] == 50-2){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_FREEZ_3);
								_ins_Debuff->m_bLoop = false;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_STUN://����
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_STUN){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_STUN);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//�Ӹ����� �׷��ش�
						}
						if(s_Debuff.stack[xx][1] > 20){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_STONE://��ȭ
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(true,false,8,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_POISON://��
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_VENOM){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_VENOM);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 16;//31 �� ������ �ȵ�
							s_Debuff.color = (s_Debuff.color+1)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<7) : ((pxx-s_Debuff.color)<<7)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//�Ӹ����� �׷��ش�

						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_CONFUSE://ȥ��
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_CHAOS){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_CHAOS);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 16;//31 �� ������ �ȵ�
							s_Debuff.color = (s_Debuff.color+1)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12)+(s_Debuff.color<<1) : ((pxx-s_Debuff.color)<<12)+((pxx-s_Debuff.color)<<1));  
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//�Ӹ����� �׷��ش�
						}
						if(s_Debuff.stack[xx][1] > 100){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_VAMPIRE://���� A
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_DE_VAMPIRE://���� B
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_EMPTY){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_EMPTY);
								_ins_Debuff->m_bLoop = true;
							}
							int pxx = 28;//31 �� ������ �ȵ�
							s_Debuff.color = (s_Debuff.color+2)%pxx;
							int pyy = (s_Debuff.color <= (pxx/2) ? (s_Debuff.color<<12) : ((pxx-s_Debuff.color)<<12)); 
							pMonAsIns->SetBlendCustom(true,false,7,pyy);
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_MANABURN://��������
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_MANABURN){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_MANABURN);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
							s_Debuff.stack[xx][0] = 0;
							if(xx == 0 )pMonAsIns->SetBlendCustom(false,false,0,0);
						}
						break;
					case DEBUF_SILENCE://ħ��
						if(xx == 0 ){// 0��°(�ֽ�) ������̸�
							if(s_Debuff.stack[xx][1] == 0 || _ins_Debuff->m_nCrtModule != ANIM_WEFFECT_A_DEBUFF_SILENCE){// ����� Ÿ�̸Ӱ� ���� ���� �Ǿ��ٸ�
								_ins_Debuff->SetAnim(ANIM_WEFFECT_A_DEBUFF_SILENCE);
								_ins_Debuff->m_bLoop = true;
							}
							pMonAsIns->SetBlendCustom(false,false,0,0);
							_ins_Debuff->m_posZ -= HERO_HEIGHT;//�Ӹ����� �׷��ش�
						}
						if(s_Debuff.stack[xx][1] > 50){//������� ���� �Ǿ��ٸ�
							s_Debuff.All -= s_Debuff.stack[xx][0];//����� ����
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
Mon_GOLEM::Mon_GOLEM()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;	

	m_nSpriteIdx = SPRITE_MON_GOLEM;
	m_nMonIdx = MON_IDX_GOLEM;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_3;

	m_Physics = GL_NEW Physics(HEAVY_WEIGHT);

	m_nAtkMaxCount = 3;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);

	m_Attack[0].Name = MON_ATK_MELEE1;
//	m_Attack[0].MinScope = 0;
//	m_Attack[0].MaxScope = 70;

	m_Attack[0].AtkRect.x1 = 0;
	m_Attack[0].AtkRect.x2 = 70;
	m_Attack[0].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[0].AtkRect.y2 = (m_nBodySize/2);


	m_Attack[1].Name = MON_ATK_THROWSTONE;
//	m_Attack[1].MinScope = 70;
//	m_Attack[1].MaxScope = 110;

	m_Attack[1].AtkRect.x1 = 70;
	m_Attack[1].AtkRect.x2 = 110;
	m_Attack[1].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[1].AtkRect.y2 = (m_nBodySize/2);


	m_Attack[2].Name = MON_ATK_LASERBEAM;
//	m_Attack[2].MinScope = 70;
//	m_Attack[2].MaxScope = 180;

	m_Attack[2].AtkRect.x1 = 70;
	m_Attack[2].AtkRect.x2 = 180;
	m_Attack[2].AtkRect.y1 = -(m_nBodySize/2);
	m_Attack[2].AtkRect.y2 = (m_nBodySize/2);


//	m_nStrollScope = 60;
//	m_nSearchScope = 90;
//	m_nEscapeCurTick = 0;
//	m_nEscapeMaxTick = 100;
//	m_nResvNextAtk = MON_NOT_ATTACK;
//	m_nIsBattle = 0;
}



//--------------------------------------------------------------------------------------
Mon_GOLEM::~Mon_GOLEM()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_GOLEM::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	������ ���� ��� ��ų����Ʈ���� ���ܽ����ش�.
	RemoveSkillList(MON_ATK_LASERBEAM, 2, (void*)this);

	switch(m_ActState)
	{
		default:	{return false;}
		case MON_ATK_MELEE1:
		case MON_ATK_THROWSTONE:
		case MON_ATK_LASERBEAM:
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
			case MON_ATK_THROWSTONE:
			case MON_ATK_LASERBEAM:
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
bool Mon_GOLEM::ExtSetAction()
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
		case MON_ATK_THROWSTONE:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON02_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON02_BULLET_1);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(65*m_nDirection));
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns)+0);
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 12;
			tmpMonSkill->who = (void*)this;
			//tmpMonSkill->skillnum = m_ActState;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 1;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_LASERBEAM:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_MON02_RANGE_2);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);

			SUTIL_SetLoopAsprite(pMonAsIns, false);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL * tmpMonSkill;
			for(int loop = 0; loop < MON2_LASERBEAM_COUNT; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON02_BEAM_1);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+(19*m_nDirection)
													+(MON2_LASERBEAM_SIZE*loop*m_nDirection));
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 6;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 14;
				tmpMonSkill->who = (void*)this;
				//tmpMonSkill->skillnum = m_ActState;
				tmpMonSkill->skillnum = 2;
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

	//	ĳ������ ��ǥ�� ���Ž����ش�.
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

	//	�п��� ������ ���·� �����.
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
	//	������ ���� ��� ��ų����Ʈ���� ���ܽ����ش�.
	RemoveSkillList(MON_ATK_RANGE1, 0, (void*)this);

	switch(m_ActState)
	{
		default:
		{
			m_Clonetimer = 0;
			return false;
		}
		case MON_ATK_SPECIAL1:		//	�п�
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
		case MON_ATK_SPECIAL1:		//	�п�
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
	//	������ ���� ��� ��ų����Ʈ���� ���ܽ����ش�.
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

	//	test ��
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
				// > �޼����� ���� ��Ų��.
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
				// > �޼����� ���� ��Ų��.
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
	//	�ڱ����� ��� ��ų����Ʈ���� ���ܽ����ش�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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
Mon_FLYTRAP::Mon_FLYTRAP()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_FLYTRAP;
	m_nMonIdx = MON_IDX_FLYTRAP;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_2;

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
Mon_FLYTRAP::~Mon_FLYTRAP()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_FLYTRAP::ExtProcess()
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
bool Mon_FLYTRAP::ExtSetAction()
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
/*
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
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_MON07_BULLET);
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
*/
	}

	return false;
}



//==============================================================================================================




//--------------------------------------------------------------------------------------
Mon_CRAB::Mon_CRAB()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 14;

	m_nSpriteIdx = SPRITE_MON_CRAB;
	m_nMonIdx = MON_IDX_CRAB;
	m_nFeature = FE_NORMAL_MONSTER;

	m_nShadowIdx = FRAME_SHADOW_SHADOW_1;

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
	m_Attack[1].AtkRect.x1 = 70;
	m_Attack[1].AtkRect.x2 = 110;
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
Mon_CRAB::~Mon_CRAB()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
bool Mon_CRAB::ExtProcess()
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
bool Mon_CRAB::ExtSetAction()
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
	//	TEST �׽�����
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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
	//	����� �̹����� �����Ѵ�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);

	// ��ǥ�� ������Ʈ �����ش�.
//	SUTIL_SetXPosAsprite(pMonAsIns, pMonAsIns->m_posX);
//	SUTIL_SetYPosAsprite(pMonAsIns, pMonAsIns->m_posY);
//	SUTIL_SetZPosAsprite(pMonAsIns, pMonAsIns->m_posZ);
}

//--------------------------------------------------------------------------------------
bool BossMon2_1::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
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

			//	���� ��ȯ
			SetMessage(MSG_SUMMONE_BUGS, pMonAsIns->m_posX, pMonAsIns->m_posY, 0, 0, 5);
*/
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
BossMon5_1::BossMon5_1()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nMoveTimer = 0;
	m_nMoveLocatex = 0;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGDOG1;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	isFirstTouch = true;
	isJumpChar = false;
	m_nPassbleJumpTimer = 0;
	m_nNowDownCool = DOWNTIME_MAX;

	m_nBossStep = BOSS_STAND;

	m_ActState = MON_AC_NULL;
	ResvAction(MON_AC_STAND, 0);

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);
	m_nAtkMaxCount = 33;
	m_Attack = (S_MONATK*)MALLOC(sizeof(S_MONATK)*m_nAtkMaxCount);
/*
	m_Attack[0].Name = MON_ATK_MELEE1;			m_Attack[0].MinScope = 0;	m_Attack[0].MaxScope = 1000;	m_Attack[0].MaxCoolTime = 0;		m_Attack[0].CoolTime = 0;
	m_Attack[1].Name = MON_ATK_MELEE2;			m_Attack[1].MinScope = 0;	m_Attack[1].MaxScope = 300;		m_Attack[1].MaxCoolTime = 1000;		m_Attack[1].CoolTime = 0;
	m_Attack[2].Name = MON_ATK_MELEE3;			m_Attack[2].MinScope = 0;	m_Attack[2].MaxScope = 1000;	m_Attack[2].MaxCoolTime = 0;		m_Attack[2].CoolTime = 0;
	m_Attack[3].Name = MON_ATK_MELEE4;			m_Attack[3].MinScope = 0;	m_Attack[3].MaxScope = 1000;	m_Attack[3].MaxCoolTime = 0;		m_Attack[3].CoolTime = 0;
	m_Attack[4].Name = MON_ATK_RANGE1_READY;	m_Attack[4].MinScope = 0;	m_Attack[4].MaxScope = 1000;	m_Attack[4].MaxCoolTime = 1000;		m_Attack[4].CoolTime = 0;
	m_Attack[5].Name = MON_ATK_RANGE2_READY;	m_Attack[5].MinScope = 0;	m_Attack[5].MaxScope = 1000;	m_Attack[5].MaxCoolTime = 0;		m_Attack[5].CoolTime = 0;
	m_Attack[6].Name = MON_ATK_RANGE3_READY;	m_Attack[6].MinScope = 0;	m_Attack[6].MaxScope = 1000;	m_Attack[6].MaxCoolTime = 0;		m_Attack[6].CoolTime = 0;
	m_Attack[7].Name = MON_ATK_RANGE4_READY;	m_Attack[7].MinScope = 0;	m_Attack[7].MaxScope = 1000;	m_Attack[7].MaxCoolTime = 0;		m_Attack[7].CoolTime = 0;
	m_Attack[8].Name = MON_ATK_RANGE5;			m_Attack[8].MinScope = 0;	m_Attack[8].MaxScope = 1000;	m_Attack[8].MaxCoolTime = 0;		m_Attack[8].CoolTime = 0;
	m_Attack[9].Name = MON_ATK_RANGE6;			m_Attack[9].MinScope = 0;	m_Attack[9].MaxScope = 1000;	m_Attack[9].MaxCoolTime = 0;		m_Attack[9].CoolTime = 0;
	m_Attack[10].Name = MON_ATK_RANGE7;			m_Attack[10].MinScope = 0;	m_Attack[10].MaxScope = 1000;	m_Attack[10].MaxCoolTime = 0;		m_Attack[10].CoolTime = 0;
	m_Attack[11].Name = MON_ATK_RANGE8;			m_Attack[11].MinScope = 0;	m_Attack[11].MaxScope = 1000;	m_Attack[11].MaxCoolTime = 0;		m_Attack[11].CoolTime = 0;
	m_Attack[12].Name = MON_ATK_RANGE9;			m_Attack[12].MinScope = 0;	m_Attack[12].MaxScope = 1000;	m_Attack[12].MaxCoolTime = 0;		m_Attack[12].CoolTime = 0;
	m_Attack[13].Name = MON_ATK_RANGE10;		m_Attack[13].MinScope = 0;	m_Attack[13].MaxScope = 1000;	m_Attack[13].MaxCoolTime = 0;		m_Attack[13].CoolTime = 0;
	m_Attack[14].Name = MON_ATK_RANGE11;		m_Attack[14].MinScope = 0;	m_Attack[14].MaxScope = 1000;	m_Attack[14].MaxCoolTime = 0;		m_Attack[14].CoolTime = 0;
	m_Attack[15].Name = MON_ATK_MELEE5;			m_Attack[15].MinScope = 0;	m_Attack[15].MaxScope = 1000;	m_Attack[15].MaxCoolTime = 0;		m_Attack[15].CoolTime = 0;
	m_Attack[16].Name = MON_ATK_RANGE1;			m_Attack[16].MinScope = 0;	m_Attack[16].MaxScope = 1000;	m_Attack[16].MaxCoolTime = 0;		m_Attack[16].CoolTime = 0;
	m_Attack[17].Name = MON_ATK_RANGE2;			m_Attack[17].MinScope = 0;	m_Attack[17].MaxScope = 1000;	m_Attack[17].MaxCoolTime = 0;		m_Attack[17].CoolTime = 0;
	m_Attack[18].Name = MON_ATK_RANGE3;			m_Attack[18].MinScope = 0;	m_Attack[18].MaxScope = 1000;	m_Attack[18].MaxCoolTime = 0;		m_Attack[18].CoolTime = 0;
	m_Attack[19].Name = MON_ATK_RANGE4;			m_Attack[19].MinScope = 0;	m_Attack[19].MaxScope = 1000;	m_Attack[19].MaxCoolTime = 0;		m_Attack[19].CoolTime = 0;
	m_Attack[20].Name = MON_ATK_BOSS5_METEO;	m_Attack[20].MinScope = 0;	m_Attack[20].MaxScope = 1000;	m_Attack[20].MaxCoolTime = 0;		m_Attack[20].CoolTime = 0;
	m_Attack[21].Name = MON_ATK_BOSS5_FACE_LEFT_HOOK;		m_Attack[21].MinScope = 0;	m_Attack[21].MaxScope = 1000;	m_Attack[21].MaxCoolTime = 0;		m_Attack[21].CoolTime = 0;
	m_Attack[22].Name = MON_ATK_BOSS5_FACE_RIGHT_HOOK;		m_Attack[22].MinScope = 0;	m_Attack[22].MaxScope = 1000;	m_Attack[22].MaxCoolTime = 0;		m_Attack[22].CoolTime = 0;
	m_Attack[23].Name = MON_ATK_BOSS5_FACE_SHOULDER;		m_Attack[23].MinScope = 0;	m_Attack[23].MaxScope = 1000;	m_Attack[23].MaxCoolTime = 0;		m_Attack[23].CoolTime = 0;
	m_Attack[24].Name = MON_ATK_BOSS5_FACE_METEO;			m_Attack[24].MinScope = 0;	m_Attack[24].MaxScope = 1000;	m_Attack[24].MaxCoolTime = 0;		m_Attack[24].CoolTime = 0;
	m_Attack[25].Name = MON_ATK_BOSS5_FACE_SHOULER_L_BEAM;	m_Attack[25].MinScope = 0;	m_Attack[25].MaxScope = 1000;	m_Attack[25].MaxCoolTime = 0;		m_Attack[25].CoolTime = 0;
	m_Attack[26].Name = MON_ATK_BOSS5_FACE_SHOULER_R_BEAM;	m_Attack[26].MinScope = 0;	m_Attack[26].MaxScope = 1000;	m_Attack[26].MaxCoolTime = 0;		m_Attack[26].CoolTime = 0;
	m_Attack[27].Name = MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM;	m_Attack[27].MinScope = 0;	m_Attack[27].MaxScope = 1000;	m_Attack[27].MaxCoolTime = 0;		m_Attack[27].CoolTime = 0;
	m_Attack[28].Name = MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM;	m_Attack[28].MinScope = 0;	m_Attack[28].MaxScope = 1000;	m_Attack[28].MaxCoolTime = 0;		m_Attack[28].CoolTime = 0;
	m_Attack[29].Name = MON_ATK_BOSS5_FACE_BEAM;			m_Attack[29].MinScope = 0;	m_Attack[29].MaxScope = 1000;	m_Attack[29].MaxCoolTime = 0;		m_Attack[29].CoolTime = 0;
	m_Attack[30].Name = MON_ATK_BOSS5_FACE_WALL;			m_Attack[30].MinScope = 0;	m_Attack[30].MaxScope = 1000;	m_Attack[30].MaxCoolTime = 0;		m_Attack[30].CoolTime = 0;
	m_Attack[31].Name = MON_ATK_BOSS5_FACE_SUMMON;			m_Attack[31].MinScope = 0;	m_Attack[31].MaxScope = 1000;	m_Attack[31].MaxCoolTime = 0;		m_Attack[31].CoolTime = 0;
*/
	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_LEG_1_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_LEG_1_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_LEG_1_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;

	



}



//--------------------------------------------------------------------------------------
BossMon5_1::~BossMon5_1()
//--------------------------------------------------------------------------------------
{
	m_nBossStep = BOSS_NOT_USE;
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_1::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	Ư�����̽�
	if(BOSS_SIT == m_nBossStep )
	{
		if(true == isJumpChar)
		{
			m_nspikeTimer++;

			if(100 < m_nspikeTimer)
			{
				m_nspikeTimer = 0;

				ASpriteInstance* tmpAsIns = NULL;
				S_MONSKILL * tmpMonSkill = NULL;
				int seed = SUTIL_GetRandom()%5;
				for(int loop = 0; loop < 2; loop++)
				{
					tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
					SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_SPIKE_ATTACK);
					SUTIL_SetLoopAsprite(tmpAsIns, true);
					SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+14+(18*((seed+loop)%5)) );
					SUTIL_SetYPosAsprite(tmpAsIns, 109);
					SUTIL_SetZPosAsprite(tmpAsIns, 0);
					SUTIL_UpdateTimeAsprite(tmpAsIns);

					tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
					tmpMonSkill->pMonSkillAsIns = tmpAsIns;
					tmpMonSkill->type = SKILL_REMAIN;
					tmpMonSkill->lifeTime = 5;
					tmpMonSkill->Damage = 10;
					tmpMonSkill->Delay = 1+loop;
					tmpMonSkill->who = (void*)this;
					tmpMonSkill->skillnum = 4;
					tmpMonSkill->damagetime = 5;
					MoveTail(m_MonSkillList);
					m_MonSkillList->Insert_prev(tmpMonSkill);
					m_nSkillCount++;
				}

				seed = SUTIL_GetRandom()%5;
				for(int loop = 0; loop < 2; loop++)
				{
					tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
					SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_SPIKE_ATTACK);
					SUTIL_SetLoopAsprite(tmpAsIns, true);
					SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+14+(18*((seed+loop)%5)) );
					SUTIL_SetYPosAsprite(tmpAsIns, 109);
					SUTIL_SetZPosAsprite(tmpAsIns, 0);
					SUTIL_UpdateTimeAsprite(tmpAsIns);

					tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
					tmpMonSkill->pMonSkillAsIns = tmpAsIns;
					tmpMonSkill->type = SKILL_REMAIN;
					tmpMonSkill->lifeTime = 5;
					tmpMonSkill->Damage = 10;
					tmpMonSkill->Delay = 25+loop;
					tmpMonSkill->who = (void*)this;
					tmpMonSkill->skillnum = 4;
					tmpMonSkill->damagetime = 5;
					MoveTail(m_MonSkillList);
					m_MonSkillList->Insert_prev(tmpMonSkill);
					m_nSkillCount++;
				}

			}
		}
		else
		{
			if(false == isJumpChar)
			{
				m_nGroundspikeTimer++;

				if(10 < m_nGroundspikeTimer)
				{
					m_nGroundspikeTimer = 0;

					ASpriteInstance* tmpAsIns = NULL;
					S_MONSKILL * tmpMonSkill = NULL;
					int seed = SUTIL_GetRandom()%5;
					for(int loop = 0; loop < 1; loop++)
					{
						tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
						SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_GROUND_ATTACK);
						SUTIL_SetLoopAsprite(tmpAsIns, true);
						SUTIL_SetXPosAsprite(tmpAsIns, m_CharInfo->m_nPos.x );
						SUTIL_SetYPosAsprite(tmpAsIns, m_CharInfo->m_nPos.y);
						SUTIL_SetZPosAsprite(tmpAsIns, 0);
						SUTIL_UpdateTimeAsprite(tmpAsIns);

						tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
						tmpMonSkill->pMonSkillAsIns = tmpAsIns;
						tmpMonSkill->type = SKILL_REMAIN;
						tmpMonSkill->lifeTime = 11;
						tmpMonSkill->Damage = 10;
						tmpMonSkill->Delay = 6+loop;
						tmpMonSkill->who = (void*)this;
						tmpMonSkill->skillnum = 4;
						tmpMonSkill->damagetime = 5;
						MoveTail(m_MonSkillList);
						m_MonSkillList->Insert_prev(tmpMonSkill);
						m_nSkillCount++;
					}
				}
			}
		}
	}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS5(this);

}

//--------------------------------------------------------------------------------------
void BossMon5_1::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	if(true == isJumpChar)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}
	else
	{
		if(40 > m_nPassbleJumpTimer && BOSS_SIT == m_nBossStep)
		{
			SUTIL_Paint_Frame(pMonAsIns->m_sprite , FRAME_BOSS_5_GATE+(m_nPassbleJumpTimer%8) , 111 + pMonAsIns->CameraX, 210 ,0);
			//SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
		}
		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}


//--------------------------------------------------------------------------------------
bool BossMon5_1::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_FACE_FRONTSIDE:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_FAINTING:
		//-----------------------------------------------------------------------
		{
			m_nStandTime--;
			break;
		}
		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			m_nRestTime--;
			break;
		}
		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			if(MON_AC_FACE_REST == m_ActState)		{m_nRestTime--;	}

			m_nMoveTimer = (m_nMoveTimer+1)%100;

			if(50 > m_nMoveTimer)
			{
				if( 7 > ABS(pChildBody[4]->pMonAsIns->m_posX - m_nMoveLocatex) )
				{
					m_nMoveLocatex = 50 + SUTIL_GetRandom()%(Field::m_nFieldSize_X-100);
				}

				m_nMoveValue = (m_nMoveLocatex - pChildBody[4]->pMonAsIns->m_posX)/7;
			}
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_DIE:
			//-----------------------------------------------------------------------
			{
				ResvBoss5_AllAction(MON_AC_DIE_AFTER, 0);
				break;
			}
			case MON_AC_REST:
			//-----------------------------------------------------------------------
			{
				if(1 > m_nRestTime)
				{
					ResvBoss5_AllAction(MON_AC_STAND, 0);
				}
				break;
			}
			case MON_AC_FACE_REST:
			//-----------------------------------------------------------------------
			{
				if(1 > m_nRestTime)
				{
					ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);
				}
				break;
			}
			case MON_AC_FAINTING:
			//-----------------------------------------------------------------------
			{
				if(1 > m_nStandTime)
				{
					//	�ٸ��� �Ǹ� �����ش�.
					m_nNowLegHp = m_nMaxLegHp;
					ResvBoss5_AllAction(MON_AC_AWAK, 0);
				}
				break;
			}
			case MON_AC_DOWNED:
			//-----------------------------------------------------------------------
			{
				//if(1 > m_Stet.m_Hp && 1 > m_nExtraDamage)
				if(1 > m_Stet.m_Hp)
				{
					ResvBoss5_AllAction(MON_AC_DIE, 0);
				}
				break;
			}
			case MON_AC_ING_DOWN:
			//-----------------------------------------------------------------------
			{
				ResvBoss5_AllAction(MON_AC_DOWNED, 0);
				break;
			}
			case MON_AC_AWAK:
			case MON_AC_SIT_STAND:
			case MON_AC_FALL:
			//-----------------------------------------------------------------------
			{
				ResvBoss5_AllAction(MON_AC_STAND, 0);
				break;
			}
			case MON_ATK_MELEE1:
			case MON_ATK_MELEE2:
			case MON_ATK_RANGE5:
			case MON_ATK_RANGE6:
			case MON_ATK_BOSS5_METEO:
			//-----------------------------------------------------------------------
			{
				ResvBoss5_AllAction(MON_AC_REST, 0);
				break;
			}
			case MON_ATK_RANGE1:
			case MON_ATK_RANGE4:
			//-----------------------------------------------------------------------
			{
				if(BOSS_STAND == m_nBossStep)		{ResvBoss5_AllAction(MON_AC_AWAK, 0);}
				else if(BOSS_SIT == m_nBossStep)	{ResvBoss5_AllAction(MON_AC_SIT, 0);}
				
				break;
			}
			case MON_ATK_RANGE9:
			case MON_ATK_RANGE7:
			case MON_ATK_MELEE5:
			case MON_ATK_RANGE11:
			//-----------------------------------------------------------------------
			{
				if(BOSS_STAND == m_nBossStep)		{ResvBoss5_AllAction(MON_AC_STAND, 0);}
				else if(BOSS_SIT == m_nBossStep)	{ResvBoss5_AllAction(MON_AC_SIT, 0);}
				
				break;
			}
			case MON_AC_SIT:
			//-----------------------------------------------------------------------
			{
//				ResvAction(MON_AC_SIT, 0);
				break;
			}
			case MON_ATK_MELEE3:		{ResvBoss5_AllAction(MON_ATK_MELEE2, 0);		break;}
			case MON_ATK_MELEE4:		{ResvBoss5_AllAction(MON_ATK_MELEE1, 0);		break;}
			case MON_ATK_RANGE1_READY:	{ResvBoss5_AllAction(MON_ATK_RANGE1, 0);		break;}
			case MON_ATK_RANGE2_READY:	{ResvBoss5_AllAction(MON_ATK_RANGE2, 0);		break;}
			case MON_ATK_RANGE3_READY:	{ResvBoss5_AllAction(MON_ATK_RANGE3, 0);		break;}
			case MON_ATK_RANGE4_READY:	{ResvBoss5_AllAction(MON_ATK_RANGE4, 0);		break;}
			case MON_ATK_RANGE2:		{ResvBoss5_AllAction(MON_ATK_RANGE4, 0);		break;}
			case MON_ATK_RANGE3:		{ResvBoss5_AllAction(MON_ATK_RANGE1, 0);		break;}
			case MON_ATK_RANGE8:		{ResvBoss5_AllAction(MON_ATK_RANGE9, 0);		break;}
			case MON_ATK_RANGE10:		{ResvBoss5_AllAction(MON_ATK_RANGE7, 0);		break;}
			case MON_AC_ING_SIT:		{ResvBoss5_AllAction(MON_AC_SIT, 0);			break;}
			case MON_AC_HIDE:			{ResvBoss5_AllAction(MON_AC_FACE_FRONTSIDE, 0);	break;}
			case MON_AC_FACE_FRONTSIDE:
			{
				if(m_nTimer > 5)		{ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);}
				break;
			}
			case MON_AC_HIDE_FRONTSIDE:
			{
				if(m_nTimer > 5)		{ResvBoss5_AllAction(MON_AC_FALL, 0);}
				break;
			}
			case MON_ATK_BOSS5_FACE_LEFT_HOOK:			{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_RIGHT_HOOK:			{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_SHOULDER:			{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:		{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:		{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:	{ResvBoss5_AllAction(MON_ATK_BOSS5_FACE_SHOULER_R_BEAM, 0);	break;}
			case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:	{ResvBoss5_AllAction(MON_ATK_BOSS5_FACE_SHOULER_L_BEAM, 0);	break;}
			case MON_ATK_BOSS5_FACE_BEAM:				{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_SUMMON:				{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_METEO:				{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_ATK_BOSS5_FACE_WALL:				{ResvBoss5_AllAction(MON_AC_FACE_REST, 0);	break;}
			case MON_AC_REGEN_L_ARM_FRONTSIDE:			{ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);	break;}
			case MON_AC_REGEN_R_ARM_FRONTSIDE:			{ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);	break;}
			case MON_AC_FACE_LOST_LEFTHAND:				{ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);	break;}
			case MON_AC_FACE_LOST_RIGHTHAND:			{ResvBoss5_AllAction(MON_AC_STAND_FRONTSIDE, 0);	break;}
			default:	{break;}
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_1::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE5);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			m_nMoveLocatex = pMonAsIns->m_posX;
//			break;		//�귯�������ߵǹǷ� break�� ����.
		}
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			m_nRestTime = RESTTIME_MAX;
//			break;		//�귯�������ߵǹǷ� break�� ����.
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_AC_STAND_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			m_nBossStep = BOSS_STAND_FACESIDE;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_STAND_WALK_MELEE12_RANGE6);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_MELEE3);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE123);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE4_SUMMON);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_REGEN);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			m_nRestTime = RESTTIME_MAX;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_HIDE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX = 230;
			m_nBossStep = BOSS_STAND;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_FALL);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_RANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;
			int seed = 2 + SUTIL_GetRandom()%2;

			for(int loop = 0; loop < seed; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%100 );
				SUTIL_SetYPosAsprite(tmpAsIns, 170 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 11;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 6+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%100 );
				SUTIL_SetYPosAsprite(tmpAsIns, 200 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 11;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 8+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;

				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%100 );
				SUTIL_SetYPosAsprite(tmpAsIns, 230 + SUTIL_GetRandom()%30);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 11;
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
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_DOWNED);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FAINTING:
		//-----------------------------------------------------------------------
		{
			m_nStandTime = STANDTIME_MAX;
			m_nFaintHp = m_nMaxFaintHp;
			m_nBossStep = BOSS_DOWN;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_AWAK:
		//-----------------------------------------------------------------------
		{
			m_nBossStep = BOSS_STAND;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_AWAKE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT_STAND:
		//-----------------------------------------------------------------------
		{
			m_nPassbleJumpTimer = 80;
			isJumpChar = false;
			m_nNowDownCool = DOWNTIME_MAX;

			m_nBossStep = BOSS_STAND;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_DAMAGE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_SIT:
		//-----------------------------------------------------------------------
		{
			m_nBossStep = BOSS_SIT;
			m_nPassbleJumpTimer = 0;

			m_nCoreHp = m_nMaxCoreHp;
			m_nspikeTimer = 50+SUTIL_GetRandom()%40;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITFORATTACK);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_MELEE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_MELEE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SIT);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITRANGE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITRANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE5:	//	��� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_RANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_IN_RANGE_2);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-20);
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 4;
			tmpMonSkill->damagetime = 10;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_RANGE6:	//	�� �ҽ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_MELEE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_IN_MELEE_3);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-20);
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 24;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 1;
			tmpMonSkill->damagetime = 24;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITRANGE_4);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITRANGE_5);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITRANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;

			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BULLET_1);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+90);
//			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns));
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns)-121);
			SUTIL_SetYPosAsprite(tmpAsIns, 109);
			SUTIL_SetZPosAsprite(tmpAsIns, -34);

			SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 20;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 4;
			tmpMonSkill->damagetime = 2;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;


			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BULLET_1);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+110);
//			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns));
//			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns)-117);
			SUTIL_SetYPosAsprite(tmpAsIns, 109);
			SUTIL_SetZPosAsprite(tmpAsIns, -30);
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMOVE;
			tmpMonSkill->lifeTime = 20;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 4;
			tmpMonSkill->damagetime = 2;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_1_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------------
int BossMon5_1::CheckPassableAttack()
//--------------------------------------------------------------------------------------
{
	//���� : ���ΰ��� ��� ��ġ�� �ִ��� Ȯ��
	// �ٿ���¶�� ������ ���Ѵ�.
	
	int loop = 0;
	int truecount = 0;
	bool index[MON_ATK_MAX-MON_EXT_BASE];
	for(loop = 0; loop < MON_ATK_MAX-MON_EXT_BASE; loop++)	{index[loop] = false;}

	if(true == isJumpChar)
	{
		index[MON_ATK_RANGE7-MON_EXT_BASE] = true;	truecount++;
		index[MON_ATK_RANGE8-MON_EXT_BASE] = true;	truecount++;
		index[MON_ATK_RANGE9-MON_EXT_BASE] = true;	truecount++;
		index[MON_ATK_RANGE10-MON_EXT_BASE] = true;	truecount++;
		//	�ö������� �� ����	MON_ATK_RANGE7	MON_ATK_RANGE8 MON_ATK_RANGE9	MON_ATK_RANGE10
		//	���˺� ����	MON_ATK_RANGE11
	}
	else
	{
		if(BOSS_STAND_FACESIDE == m_nBossStep)
		{

			 //	�� �ֵθ���
			if(200 > m_CharInfo->m_nPos.y)
			{
				if(0 < m_nFaceLeftArmHp)
				{
					if(-120 < (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x) && -50 > (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x))
					{
						index[MON_ATK_BOSS5_FACE_LEFT_HOOK-MON_EXT_BASE] = true;		truecount++;
					}
				}

				if(0 < m_nFaceRightArmHp)
				{
					if(120 > (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x) && 50 < (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x))
					{
						index[MON_ATK_BOSS5_FACE_RIGHT_HOOK-MON_EXT_BASE] = true;		truecount++;
					}
				}
			}

			if( 30 > ABS(pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x) )
			{
				index[MON_ATK_BOSS5_FACE_BEAM-MON_EXT_BASE] = true;					truecount++;
			}

			if( -80 < (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x) && -30 > (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x))
			{
				index[MON_ATK_BOSS5_FACE_SHOULDER-MON_EXT_BASE] = true;					truecount++;
			}

			if( 30 < (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x) && 80 > (pChildBody[4]->pMonAsIns->m_posX - m_CharInfo->m_nPos.x))
			{
				index[MON_ATK_BOSS5_FACE_SHOULDER-MON_EXT_BASE] = true;					truecount++;
			}

//			index[MON_ATK_BOSS5_FACE_LEFT_HOOK-MON_EXT_BASE] = true;		truecount++;
//			index[MON_ATK_BOSS5_FACE_RIGHT_HOOK-MON_EXT_BASE] = true;		truecount++;
//			index[MON_ATK_BOSS5_FACE_SHOULDER-MON_EXT_BASE] = true;			truecount++;
//			index[MON_ATK_BOSS5_FACE_SHOULER_L_BEAM-MON_EXT_BASE] = true;	truecount++;
//			index[MON_ATK_BOSS5_FACE_SHOULER_R_BEAM-MON_EXT_BASE] = true;	truecount++;
//			index[MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM-MON_EXT_BASE] = true;	truecount++;
//			index[MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM-MON_EXT_BASE] = true;	truecount++;
//			index[MON_ATK_BOSS5_FACE_BEAM-MON_EXT_BASE] = true;				truecount++;
//			index[MON_ATK_BOSS5_FACE_METEO-MON_EXT_BASE] = true;			truecount++;
//			index[MON_ATK_BOSS5_FACE_WALL-MON_EXT_BASE] = true;				truecount++;
//			index[MON_ATK_BOSS5_FACE_SUMMON-MON_EXT_BASE] = true;			truecount++;
		}
		else
		{
			 //	�� ����
			 if(100 > m_CharInfo->m_nPos.x)
			 {
				if(200 < m_CharInfo->m_nPos.y && 220 > m_CharInfo->m_nPos.y)
				{
					if(BOSS_SIT == m_nBossStep)		//	���� ���� ����	MON_ATK_RANGE1_READY	MON_ATK_RANGE2_READY
					{
						index[MON_ATK_RANGE1_READY-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_RANGE2_READY-MON_EXT_BASE] = true;	truecount++;
					}
					else
					{
						index[MON_ATK_RANGE1-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_RANGE2-MON_EXT_BASE] = true;	truecount++;
					}
				}
				if(220 < m_CharInfo->m_nPos.y && 240 > m_CharInfo->m_nPos.y)
				{
					if(BOSS_SIT == m_nBossStep)
					{
						index[MON_ATK_RANGE3_READY-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_RANGE4_READY-MON_EXT_BASE] = true;	truecount++;
					}//	�Ʒ��� ���� ����	MON_ATK_RANGE3_READY	MON_ATK_RANGE4_READY
					else
					{
						index[MON_ATK_RANGE3-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_RANGE4-MON_EXT_BASE] = true;	truecount++;
					}//						MON_ATK_RANGE3			MON_ATK_RANGE4
				}
			 }

			 if(BOSS_STAND == m_nBossStep)
			 {
	 			 //	���
				 if(100 < m_CharInfo->m_nPos.x && 200 > m_CharInfo->m_nPos.x)
				 {
					if(195 < m_CharInfo->m_nPos.y && 235 > m_CharInfo->m_nPos.y)	//	���� �� ����		MON_ATK_MELEE1 MON_ATK_MELEE3
					{
						index[MON_ATK_MELEE1-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_MELEE3-MON_EXT_BASE] = true;	truecount++;
					}
				 }		

				 if(120 < m_CharInfo->m_nPos.x && 220 > m_CharInfo->m_nPos.x)
				 {
					if(215 < m_CharInfo->m_nPos.y && 255 > m_CharInfo->m_nPos.y)	//	�Ʒ��� �� ����		MON_ATK_MELEE2	MON_ATK_MELEE4
					{
						index[MON_ATK_MELEE2-MON_EXT_BASE] = true;	truecount++;
						index[MON_ATK_MELEE4-MON_EXT_BASE] = true;	truecount++;
					}
				 }		

				 //	���ϱ�(100 ~200)
				 if(120 < m_CharInfo->m_nPos.x && 250 > m_CharInfo->m_nPos.x)	//	���ϱ� ���� MON_ATK_RANGE6
				 {
					 index[MON_ATK_RANGE6-MON_EXT_BASE] = true;	truecount++;
				 }

				 //	���̵� ������ ��
				 if(120 < m_CharInfo->m_nPos.x)
				 {
					if(190 > m_CharInfo->m_nPos.y || 240 < m_CharInfo->m_nPos.y)
					{
						index[MON_ATK_RANGE5-MON_EXT_BASE] = true;	truecount++;
					}//	���� �������� ����	MON_ATK_RANGE5
				 }

				 //	���׿�
 				 if(100 > m_CharInfo->m_nPos.x)
				 {
					index[MON_ATK_BOSS5_METEO-MON_EXT_BASE] = true;	truecount++;
				 }
			 }
		}


	}

	int rnd = SUTIL_GetRandom()%(MON_ATK_MAX-MON_EXT_BASE);
	int rnd2 = 0;

	if(truecount)
	{
		rnd2 = SUTIL_GetRandom()%(truecount);
	}

	for(loop = 0; loop < (MON_ATK_MAX-MON_EXT_BASE); loop++)
	{
		if(true == index[(rnd+loop)%(MON_ATK_MAX-MON_EXT_BASE)])
		{
			// ����ī��Ʈ���� ã�´�.
			for(int loop2 = 0; loop2 < m_nAtkMaxCount; loop2++)
			{
				if(m_Attack[loop2].Name-MON_EXT_BASE == ((rnd+loop)%(MON_ATK_MAX-MON_EXT_BASE)) )
				{
					if(0 < rnd2)	{rnd2--;}
					else
					{
						//	������ �ִ� ������ ��Ÿ���� üũ�ؼ� false�� ������ش�.
						if(0 < m_Attack[loop2].CoolTime)
						{
							index[(rnd+loop)%(MON_ATK_MAX-MON_EXT_BASE)] = false;
						}
						else
						{
							m_Attack[loop2].CoolTime = m_Attack[loop2].MaxCoolTime;
							return loop2;
						}
					}
				}
			}
		}
	}
	
	//	�ƹ��͵� �����ô� �������ش�.
	 if(BOSS_STAND == m_nBossStep)
	 {
		 switch( SUTIL_GetRandom()%(6) )
		 {
			case 0:	return 9;
			case 1:	return 4;
			case 2:	return 5;
			case 3:	return 6;
			case 4:	return 7;
			case 5:	return 20;//���׿�
		 }
	 }
	 else if(BOSS_STAND_FACESIDE == m_nBossStep)
	 {
		 switch( SUTIL_GetRandom()%(7) )
		 {
			case 0:	return 24;
			case 1:	return 25;
			case 2:	return 26;
			case 3:	return 27;
			case 4:	return 28;
			case 5:	return 30;
			case 6:	return 31;
		 }
	 }
	 else
	 {
		 switch( SUTIL_GetRandom()%(4) )
		 {
			case 0:	return 16;
			case 1:	return 17;
			case 2:	return 18;
			case 3:	return 19;
		 }
	 }
	

	return 1;	 
}

//--------------------------------------------------------------------------------------
void BossMon5_1::ResvBoss5_AllAction(int changeState, int dummy)
//--------------------------------------------------------------------------------------
{
	//	����1���� ��� ������ ������ �����Ѵ�.
	ResvAction(changeState, 0);

	for(int loop = 0; loop < BOSS5_MAX_BODY_COUNT; loop++)
	{
		SetMessage(MSG_BOSS_CHANGESTATE, pChildBody[loop]->m_nUniqueIdx, changeState);
	}
}




//--------------------------------------------------------------------------------------
BossMon5_2::BossMon5_2()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGDOG2;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_HEAD_1_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_HEAD_1_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_HEAD_1_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_2::~BossMon5_2()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_2::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_2::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	if(true == BossMon5_1::isJumpChar)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}
	else
	{
		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}

//--------------------------------------------------------------------------------------
bool BossMon5_2::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_AC_REST:
		case MON_AC_FACE_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	//	����1���� �����Ѵ�.
	SUTIL_UpdateTimeAsprite(pMonAsIns);

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_2::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE5);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_STAND_WALK_MELEE12_RANGE6);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_MELEE3);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE123);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE4_SUMMON);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_REGEN);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_HIDE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX = 230;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_FALL);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_RANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_DOWNED);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_AWAK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_AWAKE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT_STAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_DAMAGE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITFORATTACK);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_MELEE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_MELEE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SIT);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITRANGE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;
			for(int loop = 0; loop < 2; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BEAM_1);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)-238-(140*loop));
				SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)+20);
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 10;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 1;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 10;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			return true;
		}
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITRANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_RANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE6:	//	�� �ҽ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_MELEE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITRANGE_4);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITRANGE_5);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITRANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_1_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;
			int seed = SUTIL_GetRandom()%5;
			for(int loop = 0; loop < 3; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_SPIKE_ATTACK);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)+14+(18*((seed+loop)%5)) );
				SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns));
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns)-96);
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 5;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 1+loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 5;
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
BossMon5_3::BossMon5_3()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGDOG3;
	m_nFeature = FE_BOSS;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_HEAD_2_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_HEAD_1_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_HEAD_1_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_3::~BossMon5_3()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_3::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_3::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	if(true == BossMon5_1::isJumpChar)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}
	else
	{
		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}

//--------------------------------------------------------------------------------------
bool BossMon5_3::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_HIDE_FRONTSIDE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_AC_REST:
		case MON_AC_FACE_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	SUTIL_UpdateTimeAsprite(pMonAsIns);


	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_3::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE5);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_STAND_WALK_MELEE12_RANGE6);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_MELEE3);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE123);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE4_SUMMON);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_REGEN);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_HIDE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX = 230;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_FALL);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_RANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_DOWNED);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_AWAK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_AWAKE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT_STAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_DAMAGE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITFORATTACK);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_MELEE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_MELEE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SIT);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITRANGE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITRANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = NULL;
			S_MONSKILL * tmpMonSkill = NULL;
			for(int loop = 0; loop < 2; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_BEAM_1);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns)-258-(loop*140));
				SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)-20);
				SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
				SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 10;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 1;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 4;
				tmpMonSkill->damagetime = 10;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}
			return true;
		}

		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_RANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE6:	//	�� �ҽ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_MELEE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITRANGE_4);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITRANGE_5);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITRANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_HEAD_2_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------------
BossMon5_4::BossMon5_4()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGDOG4;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_LEG_2_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_LEG_2_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_LEG_2_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_4::~BossMon5_4()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_4::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_4::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	if(true == BossMon5_1::isJumpChar)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}
	else
	{
		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}

//--------------------------------------------------------------------------------------
bool BossMon5_4::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_HIDE_FRONTSIDE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_AC_REST:
		case MON_AC_FACE_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	SUTIL_UpdateTimeAsprite(pMonAsIns);

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_4::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE5);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_STAND_WALK_MELEE12_RANGE6);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_MELEE3);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE123);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE4_SUMMON);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_REGEN);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_HIDE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX = 230;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_FALL);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_RANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_DOWNED);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FAINTING:
		case MON_AC_ING_DOWN:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_AWAK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_AWAKE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT_STAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_DAMAGE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_SIT:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITFORATTACK);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_MELEE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_MELEE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SIT);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITRANGE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITRANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_RANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_OUT_RANGE_2);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)+10);
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 10;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 4;
			tmpMonSkill->damagetime = 10;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;
			return true;
		}
		case MON_ATK_RANGE6:	//	�� �ҽ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_MELEE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_5_OUT_MELEE_3);
			SUTIL_SetLoopAsprite(tmpAsIns, true);
			SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetXPosAsprite(tmpAsIns));
			SUTIL_SetYPosAsprite(tmpAsIns, SUTIL_GetYPosAsprite(tmpAsIns)+20);
			SUTIL_SetZPosAsprite(tmpAsIns, SUTIL_GetZPosAsprite(tmpAsIns));
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			S_MONSKILL * tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 24;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 1;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 6;
			tmpMonSkill->damagetime = 24;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;


			return true;
		}
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITRANGE_4);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITRANGE_5);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITRANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_LEG_2_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//--------------------------------------------------------------------------------------
BossMon5_5::BossMon5_5()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_5;
	m_nMonIdx = MON_IDX_BIGDOG5;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_5_JEWEL_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_5_JEWEL_DOWN;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_5_EMPTY_RANGE4_SUMMON;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_5_JEWEL_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_5::~BossMon5_5()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_5::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_5::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	if(true == BossMon5_1::isJumpChar)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}
	else
	{
		//	paint monster
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}

//--------------------------------------------------------------------------------------
bool BossMon5_5::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_DIE:
		case MON_AC_HIDE_FRONTSIDE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_AC_REST:
		case MON_AC_FACE_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
	}

	SUTIL_UpdateTimeAsprite(pMonAsIns);

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_5::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE5);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_STAND_WALK_MELEE12_RANGE6);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_MELEE3);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE123);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_RANGE4_SUMMON);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_EMPTY_REGEN);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REST:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_STAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_HIDE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FALL:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX = 230;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_FALL);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_RANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_DOWNED:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_DOWNED);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_DOWN);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_AWAK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_AWAKE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT_STAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_DAMAGE);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_ING_SIT:
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITFORATTACK);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_SIT:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_MELEE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_MELEE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SIT);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITRANGE_1);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITRANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_RANGE_2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE6:	//	�� �ҽ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_MELEE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITRANGE_4);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITRANGE_5);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITRANGE_3);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_5_JEWEL_SITTING);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//--------------------------------------------------------------------------------------
BossMon5_6::BossMon5_6()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_BIGDOG6;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWN_ARM;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWN_ARM;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_6::~BossMon5_6()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_6::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_6::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

//	if(true == BossMon5_1::isJumpChar)
//	{
	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
	if(isPossibleAction)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}
	else
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}

		
//	}
//	else
//	{
		//	paint monster
//		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
//	}

	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}



//--------------------------------------------------------------------------------------
bool BossMon5_6::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY += FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY -= FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_DIE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX += BossMon5_1::m_nMoveValue;
			break;
		}

	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_FACE_LOST_LEFTHAND:
			//-----------------------------------------------------------------------
			{
				pMonAsIns->m_posZ += BOSS6_FACE_NOT_VIEW_ARM;
				break;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_6::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_DOWN_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_5_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	METEO
			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

//			int max = Field::m_nFieldSize_X/26;

			int maxloop = 8+SUTIL_GetRandom()%6;
			for(int loop = 0; loop < maxloop; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_5);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%Field::m_nFieldSize_X );
				SUTIL_SetYPosAsprite(tmpAsIns, 180 + SUTIL_GetRandom()%100);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				//SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMOVE;
				tmpMonSkill->lifeTime = 11;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;


				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_5);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, SUTIL_GetRandom()%Field::m_nFieldSize_X );
				SUTIL_SetYPosAsprite(tmpAsIns, 180 + SUTIL_GetRandom()%100);
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				//SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMOVE;
				tmpMonSkill->lifeTime = 11;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = loop;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			return true;
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
//
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_6_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

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
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	add bones
			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_MELEE_3_BONE);
			SUTIL_SetLoopAsprite(tmpAsIns, false);
			SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
			SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);
			SUTIL_SetZPosAsprite(tmpAsIns, 0);
			SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 2;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 3;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 9;
			tmpMonSkill->damagetime = 2;
			tmpMonSkill->Movey = 47;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_MELEE_3_BONE2);
			SUTIL_SetLoopAsprite(tmpAsIns, false);
			SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
			SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);
			SUTIL_SetZPosAsprite(tmpAsIns, 0);
//			SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 14;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 0;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 9;
			tmpMonSkill->damagetime = 5;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;

			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_2_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();


			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;
			for(int loop = 0; loop < 2; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetDirAsprite(tmpAsIns, SDIR_LEFT);

				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, Field::m_nFieldSize_X+100);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+30+(loop*60));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
	//			SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 40;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+(loop);
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}


			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_3_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;
			for(int loop = 0; loop < 2; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetDirAsprite(tmpAsIns, SDIR_RIGHT);

				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_BULLET_2);
				SUTIL_SetLoopAsprite(tmpAsIns, true);
				SUTIL_SetXPosAsprite(tmpAsIns, -100);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+60+(loop*60));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
	//			SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 40;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 10+(loop);
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 2;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_4_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			//	beam
			for(int loop = 0; loop < 10; loop++)
			{
				tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
				SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_RANGE_4_ICE);
				SUTIL_SetLoopAsprite(tmpAsIns, false);
				SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
				SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+(loop*20));
				SUTIL_SetZPosAsprite(tmpAsIns, 0);
				//SUTIL_UpdateTimeAsprite(tmpAsIns);

				tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
				tmpMonSkill->pMonSkillAsIns = tmpAsIns;
				tmpMonSkill->type = SKILL_REMAIN;
				tmpMonSkill->lifeTime = 16;
				tmpMonSkill->Damage = 10;
				tmpMonSkill->Delay = 0;
				tmpMonSkill->who = (void*)this;
				tmpMonSkill->skillnum = 9;
				tmpMonSkill->damagetime = 3;
				MoveTail(m_MonSkillList);
				m_MonSkillList->Insert_prev(tmpMonSkill);
				m_nSkillCount++;
			}

			//after icetree
			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_RANGE_4_ICE_BACK);
			SUTIL_SetLoopAsprite(tmpAsIns, false);
			SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
			SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY+(10));
			SUTIL_SetZPosAsprite(tmpAsIns, 0);
			//SUTIL_UpdateTimeAsprite(tmpAsIns);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 56;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 8;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 9;
			tmpMonSkill->damagetime = 3;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;



			return true;
		}
		case MON_ATK_BOSS5_FACE_SUMMON:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_SUMMON_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	��ȯ ���ϸ��̼�
			//after icetree
			ASpriteInstance* tmpAsIns;
			S_MONSKILL *tmpMonSkill;

			tmpAsIns = GL_NEW ASpriteInstance(pMonAsIns);
			SUTIL_SetTypeAniAsprite(tmpAsIns,ANIM_BOSS_6_SUMMON_MONSTER);
			SUTIL_SetLoopAsprite(tmpAsIns, false);
			SUTIL_SetXPosAsprite(tmpAsIns, pMonAsIns->m_posX);
			SUTIL_SetYPosAsprite(tmpAsIns, pMonAsIns->m_posY);
			SUTIL_SetZPosAsprite(tmpAsIns, 0);

			tmpMonSkill = (S_MONSKILL*)MALLOC(sizeof(S_MONSKILL));
			tmpMonSkill->pMonSkillAsIns = tmpAsIns;
			tmpMonSkill->type = SKILL_REMAIN;
			tmpMonSkill->lifeTime = 16;
			tmpMonSkill->Damage = 10;
			tmpMonSkill->Delay = 0;
			tmpMonSkill->who = (void*)this;
			tmpMonSkill->skillnum = 9;
			tmpMonSkill->damagetime = 0;
			MoveTail(m_MonSkillList);
			m_MonSkillList->Insert_prev(tmpMonSkill);
			m_nSkillCount++;


			//	�Ǹ� ��ȯ
			SetMessage(MSG_BOSS5_SUMMON_DEVIL, (pMonAsIns->m_posX-50), 200, 0, 0, 14);			
			SetMessage(MSG_BOSS5_SUMMON_DEVIL, (pMonAsIns->m_posX+50), 200, 0, 0, 14);

			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posZ -= BOSS6_FACE_NOT_VIEW_ARM;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENL_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			BossMon5_1::m_nFaceRightArmHp = BossMon5_1::m_nMaxFaceRightArmHp;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENR_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_LEFTHAND:
		//-----------------------------------------------------------------------
		{
			BossMon5_1::m_nFaceLeftArmHp = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARML_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			BossMon5_1::m_nFaceRightArmHp = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARMR_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			pMonAsIns->m_posX = 175;
			pMonAsIns->m_posY = BOSS6_FACE_YPOS;
			pMonAsIns->m_posZ = 0;

			//	���� �������� �ʱ�ȭ�����ش�.
			BossMon5_1::m_nFaceLeftArmHp = BossMon5_1::m_nMaxFaceLeftArmHp;
			BossMon5_1::m_nFaceRightArmHp = BossMon5_1::m_nMaxFaceRightArmHp;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REST:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		case MON_ATK_RANGE6:	//	�� �ҽ��
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY = 1000;
			pMonAsIns->m_posZ = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}



//--------------------------------------------------------------------------------------
BossMon5_7::BossMon5_7()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_BIGDOG7;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWN_ARM2;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWN_ARM2;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_7::~BossMon5_7()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_7::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_7::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
	if(isPossibleAction)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}
	else
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}



//--------------------------------------------------------------------------------------
bool BossMon5_7::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY += FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY -= FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_DIE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}

		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX += BossMon5_1::m_nMoveValue;
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_FACE_LOST_RIGHTHAND:
			//-----------------------------------------------------------------------
			{
				pMonAsIns->m_posZ += BOSS6_FACE_NOT_VIEW_ARM;
				break;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_7::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_DOWN_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_5_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

//
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_6_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_2_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_3_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_4_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SUMMON:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_SUMMON_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENL_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posZ -= BOSS6_FACE_NOT_VIEW_ARM;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENR_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_LEFTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARML_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARMR_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			pMonAsIns->m_posX = 175;
			pMonAsIns->m_posY = BOSS6_FACE_YPOS;
			pMonAsIns->m_posZ = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REST:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		case MON_ATK_RANGE6:	//	�� �ҽ��
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY = 1000;
			pMonAsIns->m_posZ = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_ARM2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
BossMon5_8::BossMon5_8()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_BIGDOG8;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWN_BODY;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWN_BODY;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_8::~BossMon5_8()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_8::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_8::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
	if(isPossibleAction)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}
	else
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}



//--------------------------------------------------------------------------------------
bool BossMon5_8::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY += FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY -= FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_DIE:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX += BossMon5_1::m_nMoveValue;
			break;
		}
	}

	SUTIL_UpdateTimeAsprite(pMonAsIns);

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_8::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_DOWN_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_5_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
//
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_6_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_2_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_3_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_4_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SUMMON:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_SUMMON_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENL_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENR_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_LEFTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARML_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARMR_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			// ������ ������ ���� �ʴ´�.
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			pMonAsIns->m_posX = 175;
			pMonAsIns->m_posY = BOSS6_FACE_YPOS;
			pMonAsIns->m_posZ = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_BODY);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REST:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		case MON_ATK_RANGE6:	//	�� �ҽ��
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY = 1000;
			pMonAsIns->m_posZ = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_BODY);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------------
BossMon5_9::BossMon5_9()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_BIGDOG9;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWN_HAND;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWN_HAND;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_9::~BossMon5_9()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_9::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_9::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
	if(isPossibleAction)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}
	else
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}



//--------------------------------------------------------------------------------------
bool BossMon5_9::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY += FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY -= FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_DIE:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX += BossMon5_1::m_nMoveValue;
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_FACE_LOST_LEFTHAND:
			//-----------------------------------------------------------------------
			{
				pMonAsIns->m_posZ += BOSS6_FACE_NOT_VIEW_ARM;
				break;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_9::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_DOWN_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_5_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
//
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_6_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_2_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_3_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_4_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SUMMON:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_SUMMON_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posZ -= BOSS6_FACE_NOT_VIEW_ARM;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENL_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENR_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_LEFTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARML_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARMR_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = true;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			pMonAsIns->m_posX = 175;
			pMonAsIns->m_posY = BOSS6_FACE_YPOS;
			pMonAsIns->m_posZ = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REST:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		case MON_ATK_RANGE6:	//	�� �ҽ��
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY = 1000;
			pMonAsIns->m_posZ = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------------------------------
BossMon5_10::BossMon5_10()
//--------------------------------------------------------------------------------------
{
	m_nBodySize = 24;

	m_nSpriteIdx = SPRITE_MON_BOSS_6;
	m_nMonIdx = MON_IDX_BIGDOG10;
	m_nFeature = FE_BOSS | FE_DONT_DRAW_MAP|FE_DONT_AREA_CHECK;

	m_Physics = GL_NEW Physics(LIGHT_WEIGHT);

	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_2_WALK_VERTICAL;
//	m_nUsingImgIdx[MON_AC_AWAK]				= ANIM_MON01_AWAKE;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_ING_AIRDOWN]		= ANIM_MON01_FLY_1;
//	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_2_DOWNED;
//	m_nUsingImgIdx[MON_AC_RCV_GROUND_ATTACK]= ANIM_MON01_DAMAGE_1;
//	m_nUsingImgIdx[MON_AC_RCV_DOWN_ATTACK]	= ANIM_MON01_DOWN_DAMAGE;
//	m_nUsingImgIdx[MON_AC_RCV_AIR_ATTACK]	= ANIM_MON01_AIR_DAMAGE;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_6_DOWN_HAND2;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_6_DOWN_HAND2;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING]		= ANIM_MON01_CATCH_1;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_SKY]	= ANIM_MON01_CATCH_3;
//	m_nUsingImgIdx[MON_AC_RCV_HOLDING_DOWN]	= ANIM_MON01_CATCH_2;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_6_STAND;
//	m_nUsingImgIdx[MON_AC_RUN]				= ANIM_MON01_WALK_VERTICAL_2;
}



//--------------------------------------------------------------------------------------
BossMon5_10::~BossMon5_10()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void BossMon5_10::Process(S_CHARINFO* _CharInfo)
//--------------------------------------------------------------------------------------
{
	if(m_NextActState)
	{
		SetAction(m_NextActState);
		m_NextActState = 0;
	}

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	//AI_PROCESS_BOSS5_DUMMY(this);

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
//	if(0 < Monster::m_nExtraDamage)
//	{
//		m_Stet.m_Hp -= Monster::m_nExtraDamage;
//		if(0 > m_Stet.m_Hp)	{m_Stet.m_Hp = 0;}
//		Monster::m_nExtraDamage = 0;
//	}
}

//--------------------------------------------------------------------------------------
void BossMon5_10::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
	if(isPossibleAction)
	{
		SUTIL_PaintAsprite(pMonAsIns, S_INCLUDE_SORT);
	}
	else
	{
		SUTIL_PaintAsprite(pMonAsIns, S_NOT_INCLUDE_SORT);
	}


	//	paint Debuff
	Paint_Debuff(tmpx , tmpz);
}



//--------------------------------------------------------------------------------------
bool BossMon5_10::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		default:
		//-----------------------------------------------------------------------
		{
			return false;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY += FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY -= FACE_BOSS5_POS[m_nTimer];
			break;
		}
		case MON_AC_DIE:
		case MON_AC_FACE_LOST_RIGHTHAND:
		case MON_AC_FACE_LOST_LEFTHAND:
		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		case MON_ATK_BOSS5_FACE_SHOULDER:
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		case MON_ATK_BOSS5_FACE_BEAM:
		case MON_ATK_BOSS5_FACE_SUMMON:
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		case MON_ATK_BOSS5_FACE_METEO:
		case MON_ATK_BOSS5_FACE_WALL:
		case MON_AC_REST:
		case MON_AC_FAINTING:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:
		case MON_ATK_MELEE2:
		case MON_ATK_MELEE3:
		case MON_ATK_MELEE4:
		case MON_ATK_MELEE5:
		case MON_ATK_RANGE1:
		case MON_ATK_RANGE2:
		case MON_ATK_RANGE3:
		case MON_ATK_RANGE4:
		case MON_ATK_RANGE5:
		case MON_ATK_RANGE6:
		case MON_ATK_RANGE7:
		case MON_ATK_RANGE8:
		case MON_ATK_RANGE9:
		case MON_ATK_RANGE10:
		case MON_ATK_RANGE11:
		case MON_ATK_RANGE1_READY:
		case MON_ATK_RANGE2_READY:
		case MON_ATK_RANGE3_READY:
		case MON_ATK_RANGE4_READY:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		//-----------------------------------------------------------------------
		{
			break;
		}
		case MON_AC_FACE_REST:
		case MON_AC_STAND_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posX += BossMon5_1::m_nMoveValue;

			//	�������̶� �����ش�.
			BossMon5_1::m_nMoveValue = 0;
			break;
		}
	}

	if(!SUTIL_UpdateTimeAsprite(pMonAsIns))
	{
		switch(m_ActState)
		{
			case MON_AC_FACE_LOST_RIGHTHAND:
			//-----------------------------------------------------------------------
			{
				pMonAsIns->m_posZ += BOSS6_FACE_NOT_VIEW_ARM;
				break;
			}
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool BossMon5_10::ExtSetAction()
//--------------------------------------------------------------------------------------
{
	// Ÿ�̸Ӹ� �ʱ�ȭ�����ش�.
	m_nTimer = 0;	

	switch(m_ActState)
	{
		case MON_AC_DIE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_DOWN_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			break;
		}
		case MON_ATK_BOSS5_FACE_METEO:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_5_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_LEFT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_1_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_RIGHT_HOOK:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_2_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
//
		case MON_ATK_BOSS5_FACE_WALL:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_6_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULDER:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_MELEE_3_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_L_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_2_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SHOULER_R_BEAM:
		case MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_3_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_BEAM:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_RANGE_4_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_BOSS5_FACE_SUMMON:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_SUMMON_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}

		case MON_AC_REGEN_L_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENL_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REGEN_R_ARM_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posZ -= BOSS6_FACE_NOT_VIEW_ARM;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_ARMREGENR_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_LEFTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARML_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_LOST_RIGHTHAND:
		//-----------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_LOSTARMR_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_STAND_FRONTSIDE:
		case MON_AC_FACE_REST:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = true;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_FACE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			pMonAsIns->m_posX = 175;
			pMonAsIns->m_posY = BOSS6_FACE_YPOS;
			pMonAsIns->m_posZ = 0;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_HIDE_FRONTSIDE:
		//-----------------------------------------------------------------------
		{
			isPossibleAction = false;
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND2);
			SUTIL_SetLoopAsprite(pMonAsIns, true);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_AC_REST:
		case MON_AC_HIDE:
		case MON_AC_FALL:
		case MON_ATK_BOSS5_METEO:
		case MON_AC_DOWNED:
		case MON_AC_ING_DOWN:
		case MON_AC_FAINTING:
		case MON_AC_AWAK:
		case MON_AC_SIT_STAND:
		case MON_AC_ING_SIT:
		case MON_AC_SIT:
		case MON_ATK_MELEE1:	//	�޹� ��
		case MON_ATK_MELEE3:	//	�޹�-������ ��
		case MON_ATK_MELEE2:	//	������ ��
		case MON_ATK_MELEE4:	//	������-�޹� ��
		case MON_ATK_RANGE1_READY:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2_READY:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3_READY:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4_READY:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE1:	//	�ɾƼ� ���� �Ӹ���
		case MON_ATK_RANGE2:	//	�ɾƼ� ����-������ �Ӹ���
		case MON_ATK_RANGE3:	//	�ɾƼ� ������ �Ӹ���
		case MON_ATK_RANGE4:	//	�ɾƼ� ������-���� �Ӹ���
		case MON_ATK_RANGE5:	//	�ɾƼ� ��� ����
		case MON_ATK_RANGE6:	//	�� �ҽ��
		case MON_ATK_RANGE7:	//	���� ��� ��
		case MON_ATK_RANGE8:	//	����-������ ��� ��
		case MON_ATK_RANGE9:	//	������ ��� ��
		case MON_ATK_RANGE10:	//	������-���� ��� ��
		case MON_ATK_RANGE11:	//	���׶� ��� ������
		case MON_ATK_MELEE5:	//	�� ���
		//-----------------------------------------------------------------------
		{
			pMonAsIns->m_posY = 1000;
			pMonAsIns->m_posZ = 0;

			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_6_STAND_HAND2);
			m_nDirection = SDIR_RIGHT;
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
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

	//	����� �̹����� �����Ѵ�.
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
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
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

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
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

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.

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


	//	����� �̹����� �����Ѵ�.
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
	//	����1���� ��� ������ ������ �����Ѵ�.
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

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
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

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
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
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
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



	//	����� �̹����� �����Ѵ�.
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

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
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

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
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
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
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



	//	����� �̹����� �����Ѵ�.
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

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
//	m_nHitRate++;
//	if(5 < m_nHitRate)
//	{
//		m_nHitRate = 5;
//		m_nAccumulatedHit = 0;
//	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	����5�� �������� ���� �����ؼ� �����ؼ� 1���� ������ �ִ´�.
	//	�ʱ�ȭ�� 5������ �����Ѵ�.
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
//	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
//	if((MON_AC_DIE == m_ActState) && (1 < m_nTimer%4))	{return;}

	int tmpXZ[2];
	pMonAsIns->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

//	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,m_nShadowIdx , tmpx  + pMonAsIns->CameraX, SUTIL_GetYPosAsprite(pMonAsIns)-2,0);

	//	���� / ����ſ��� ������ �ȵǰ� �Ѵ�.
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


	//	����� �̹����� �����Ѵ�.
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
		//	�� ��ȯ�� 10�� ���� �ʰ� �Ѵ�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;


		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);
}

//--------------------------------------------------------------------------------------
bool BossWorm::ExtProcess()
//--------------------------------------------------------------------------------------
{
	//	TEST �׽�����
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

			//	���� ��ȯ
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

	//	����� �̹����� �����Ѵ�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);
	SUTIL_UpdateTimeAsprite(pChildBody[1]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);


	//	child�� ��ǥ�� ���Ž�Ų��.
	pChildBody[1]->pMonAsIns->m_posX = pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
	pChildBody[1]->pMonAsIns->m_posY = pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
	pChildBody[1]->pMonAsIns->m_posZ = pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void BossSkelBird::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
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
	//	TEST �׽�����
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
			//	������ �����ϴ� ����̴�.
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
	//	�̸� �����´�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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
		//	�� ��ȯ�� 10�� ���� �ʰ� �Ѵ�.
		if(10 > m_nTotalMonCnt)
		{
			//	ü���� ���� ���� ���������� ��ȯ�� ���� �ʴ´�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);


	//	child�� ��ǥ�� ���Ž�Ų��.
	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void BossFlower::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
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
	//	TEST �׽�����
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

			//	�� 
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

			//	�� 
			SUTIL_SetTypeAniAsprite(pChildBody[0]->pMonAsIns,ANIM_BOSS_3_TOP_MELEE_1);
			SUTIL_SetDirAsprite(pChildBody[0]->pMonAsIns, m_nDirection);
			pChildBody[0]->m_Physics->initForce();

			return true;
		}
		case MON_ATK_RANGE1:	//	����� ��
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_1);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	�� 
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
		case MON_ATK_RANGE3:		//	����ġ ����߸�
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_2);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	�� 
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
		case MON_ATK_RANGE2:		//	�� ��ȯ
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_3_RANGE_3);
			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else										{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();

			//	�� 
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

//	//	����� �̹����� �����Ѵ�.
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

	//	����� �̹����� �����Ѵ�.
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
		//	�� ��ȯ�� 10�� ���� �ʰ� �Ѵ�.
		if(1 == m_nTotalMonCnt)
		{
			//	ü���� ���� ���� ���������� ��ȯ�� ���� �ʴ´�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
//	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);


	//	child�� ��ǥ�� ���Ž�Ų��.
//	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
//	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
//	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void DarkKnight::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
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
//	//	�׸���
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
	//	TEST �׽�����
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
			//	��ǥ�� �������ش�.(������ 2�����Ӻ��� �����Ѵ�.)
			if(1 < m_nTimer)
			{
				//	2�϶� ���� ĳ������ ��ġ�� �������ش�.
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
			//	1�϶� ���� ĳ������ ��ġ�� �������ش�.
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
			//	�ӽú����� ������
			m_nStartPosX = m_nDirection*(m_CharInfo->m_nPos.x - pMonAsIns->m_posX);

			if(0 < m_nStartPosX && 30 >= m_nStartPosX)
			{
				if(SQR(m_nBodySize/2) > SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y))
				{
					pMonAsIns->m_posX = m_CharInfo->m_nPos.x - (m_nDirection*55); //	���� ���ŷ��� 30�̰� ������ �Ÿ�+���ϰ��ŷ��� ���ش�.
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
				//	�ӽú����� ������
				m_nStartPosX = m_nDirection*(m_CharInfo->m_nPos.x - pMonAsIns->m_posX);

				if(0 < m_nStartPosX && 40 >= m_nStartPosX)
				{
					if(SQR(m_nBodySize/2) > SQR(pMonAsIns->m_posY - m_CharInfo->m_nPos.y))
					{
						pMonAsIns->m_posX = m_CharInfo->m_nPos.x - (m_nDirection*70); //	���� ���ŷ��� 30�̰� ������ �Ÿ�+���ϰ��ŷ��� ���ش�.
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
		case MON_ATK_RANGE1:	//	�� �߻� -> MON_ATK_RANGE4
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
		case MON_ATK_RANGE4:	//	�� �߻� �� ���� ����	
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_2_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE5:	//	�� �߻� �� ���� �� ������ ����	
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_2_2);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE6:	//	���� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_4_1);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE7:	//	���� ���� ����
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_4_2);

			if(pMonAsIns->m_posX < m_CharInfo->m_nPos.x)			{m_nDirection = SDIR_RIGHT;}
			else													{m_nDirection = SDIR_LEFT;}
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE2:		//	��Ʈ��Ʈ ������ ���� ����1 -> MON_ATK_RANGE3
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_1);

			m_nStartPosX = pMonAsIns->m_posX;

			//	������ ���� �����.
			if(pMonAsIns->m_posX > Field::m_nFieldSize_X/2)
			{
				m_nEndPosX = Field::m_nFieldSize_X;
				m_nDirection = SDIR_RIGHT;
			}
			//	���ʺ��� �����.
			else								
			{
				m_nEndPosX = 0;
				m_nDirection = SDIR_LEFT;
			}				
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:		//	��Ʈ��Ʈ ������ ���� ����2
		//-----------------------------------------------------------
		{
			//	z���� ������ �����ش�. ���Ͽ��� ó���Ǿ�����
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
		case MON_ATK_RANGE3:		//	����ġ ����߸�
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
		case MON_ATK_RANGE2:		//	�� ��ȯ
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
	//	����� �̹����� �����Ѵ�.
	m_nUsingImgIdx[MON_AC_STAND]			= ANIM_BOSS_4_STAND;
	m_nUsingImgIdx[MON_AC_MOVE]				= ANIM_BOSS_4_WALK_VERTICAL;
	m_nUsingImgIdx[MON_AC_ING_DOWN]			= ANIM_BOSS_4_DOWN;
	m_nUsingImgIdx[MON_AC_DOWNED]			= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE]				= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_DIE_AFTER]		= ANIM_BOSS_4_DOWNED;
	m_nUsingImgIdx[MON_AC_READY]			= ANIM_BOSS_4_MAN_MIRROR_2;
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
		//	�� ��ȯ�� 10�� ���� �ʰ� �Ѵ�.
		if(10 > m_nTotalMonCnt)
		{
			//	ü���� ���� ���� ���������� ��ȯ�� ���� �ʴ´�.
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

	//	������ǥ�� ���Ź޴´�.
	m_nPhysicsPos = m_Physics->process();
	if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == pMonAsIns->m_posZ)
	{
		//	�̵����� �����Ƿ� ��� ���� �ʱ�ȭ�����ش�.
		m_Physics->initForce();
	}
	else
	{
		//	�̵����� ���� ��ǥ�� ���������ش�.
//		m_nPos = m_nPos + m_nPhysicsPos;
		pMonAsIns->m_posX += m_nPhysicsPos.x;
		pMonAsIns->m_posY += m_nPhysicsPos.y;
		pMonAsIns->m_posZ += m_nPhysicsPos.z;
		if(0 < pMonAsIns->m_posZ)	{pMonAsIns->m_posZ = 0;}

		//	���׻�Ȳ�̶�� (�׶�����)
		if(m_nResistZ == pMonAsIns->m_posZ && 0 == pMonAsIns->m_posZ)
		{
			m_Physics->resistGr();
		}
		m_nResistZ = pMonAsIns->m_posZ;		
	}

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	//	��ü Ÿ�̸Ӹ� ���´�.
	m_nTimer= (m_nTimer+1)%1000;

	//	�¾����� �ö󰡴� ��Ʈ ����Ʈ�� �÷��ش�.
	m_nHitRate++;
	if(5 < m_nHitRate)
	{
		m_nHitRate = 5;
		m_nAccumulatedHit = 0;
	}

	//	���ݿ� ���� ��Ÿ���� �ٿ��ش�.
	for(int loop = 0; loop < m_nAtkMaxCount; loop++)
	{
		m_Attack[loop].CoolTime--;
		if(0 > m_Attack[loop].CoolTime)	{m_Attack[loop].CoolTime = 0;}
	}

	//	���� ���μ����� ������.
//	SUTIL_UpdateTimeAsprite(pChildBody[0]->pMonAsIns);

	if(!ExtProcess())	{BaseProcess();}

	//	�������� �ΰ�����
	AI_PROCESS_BOSS2(this);


	//	child�� ��ǥ�� ���Ž�Ų��.
//	pChildBody[0]->pMonAsIns->m_posX = pMonAsIns->m_posX;
//	pChildBody[0]->pMonAsIns->m_posY = pMonAsIns->m_posY;
//	pChildBody[0]->pMonAsIns->m_posZ = pMonAsIns->m_posZ;

}

//--------------------------------------------------------------------------------------
void DarkKnight_Mirror::Paint()
//--------------------------------------------------------------------------------------
{
	if(MON_AC_DIE_AFTER == m_ActState)	{return;}						//	�������Ĵ� �׸��� �ʴ´�.
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
//	//	�׸���
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
	//	TEST �׽�����
	m_bIsBattle = true;

	switch(m_ActState)
	{
		case MON_ATK_RANGE2:
		//-----------------------------------------------------------------------
		{
			//	��ǥ�� �������ش�.(������ 2�����Ӻ��� �����Ѵ�.)
			if(1 < m_nTimer)
			{
				//	2�϶� ���� ĳ������ ��ġ�� �������ش�.
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
			//	1�϶� ���� ĳ������ ��ġ�� �������ش�.
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
		case MON_ATK_RANGE1:	//	�� �߻�
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
		case MON_ATK_RANGE2:		//	��Ʈ��Ʈ ������ ���� ����1
		//-----------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(pMonAsIns,ANIM_BOSS_4_MELEE_3_1);

			m_nStartPosX = pMonAsIns->m_posX;

			//	������ ���� �����.
			if(pMonAsIns->m_posX > Field::m_nFieldSize_X/2)
			{
				m_nEndPosX = Field::m_nFieldSize_X;
				m_nDirection = SDIR_RIGHT;
			}
			//	���ʺ��� �����.
			else								
			{
				m_nEndPosX = 0;
				m_nDirection = SDIR_LEFT;
			}				
			SUTIL_SetDirAsprite(pMonAsIns, m_nDirection);
			m_Physics->initForce();
			return true;
		}
		case MON_ATK_RANGE3:		//	��Ʈ��Ʈ ������ ���� ����2
		//-----------------------------------------------------------
		{
			//	z���� ������ �����ش�. ���Ͽ��� ó���Ǿ�����
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

	//	ĳ������ ��ǥ�� ���Ž����ش�.
	m_CharInfo = _CharInfo;

	if(m_NextActState != m_ActState || 1 == m_IsAcceptChangeActState)
	{
		m_IsAcceptChangeActState = 0;
		SUTIL_UpdateTempXYAsprite(pMonAsIns, APPLY_X|APPLY_Z);	
		//SUTIL_SetZPosAsprite(pMonAsIns, 0);

		SetAction(m_NextActState);
	}


	//	���¸� ��������ش�.
	//	SetMessage(MSG_CHANGE_STATE, 0, UNQ_BOSS_3_2_IDX, MON_ATK_MELEE1);

	//	���ϸ��̼� ������Ʈ
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

	//	ĳ������ ��ǥ�� ���Ž����ش�.
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

			//	���¸� ��������ش�.
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
	// ���
	if(m_nResvAction)
	{
		m_ActionProcFuncPtr[m_nCurAction];
	}

	m_ActionProcFuncPtr[m_nCurAction];
	SetSpritePosition();		//	��ǥ�� ���Ž����ش�.
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
	//	���� ������ �������� �̵����� �����´�.
	int off = (pMonAsIns->m_sprite->_anims_af_start[pMonAsIns->m_nCrtModule-1] + pMonAsIns->m_nCrtFrame) * 5;
	int nMove =  pMonAsIns->m_sprite->_aframes[off + 3];

	int nTotalMoveCount = SetMovingTime(nMove, m_nMoveVec.Sqr_GetLength());

	//	�ѹ��� �̵��Ҽ� �ִ� �Ÿ����
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

			//	���� ������ �������� �̵����� �����´�.
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
			else	//	�������� ������ �׻� z���� 0�̴�.
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