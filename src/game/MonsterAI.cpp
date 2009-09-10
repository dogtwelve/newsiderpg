#include "MonsterAI.h"
#include "Monster.h"
#include "Position3D.h"

MonsterAI* MonsterAI::pMonsterAI = NULL;


//--------------------------------------------------------------------------
MonsterAI::MonsterAI()
//--------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------
MonsterAI::~MonsterAI()
//--------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------
MonsterAI* MonsterAI::GetInstance()
//--------------------------------------------------------------------------
{
	if(NULL == pMonsterAI)	{pMonsterAI = GL_NEW MonsterAI();}
	return pMonsterAI;
}

//--------------------------------------------------------------------------
void MonsterAI::FreeInstance()
//--------------------------------------------------------------------------
{
	if(NULL != pMonsterAI)
	{
		delete pMonsterAI;
		pMonsterAI = NULL;
	}
}


//--------------------------------------------------------------------------
void MonsterAI::AI_ResvState(Monster* pMonster, int _state)
//--------------------------------------------------------------------------
{
	pMonster->m_nAiNextState = _state;
}


//--------------------------------------------------------------------------
void MonsterAI::AI_Init(Monster* pM)
//--------------------------------------------------------------------------
{
	pM->m_bIsBattle = false;
	pM->m_bIsFirstAttack = true;
	pM->m_nSelectAtkTable = MON_USE_NORMAL_TABLE;
	AI_ResvState(pM, MON_AI_MOVE_FIRST_POSITION);
}



//--------------------------------------------------------------------------
bool MonsterAI::Move(Monster* pMonster, Position3D* pos, int action)
//--------------------------------------------------------------------------
{
	if(0 == pos->Sqr_GetLength())	{return true;}		//pMonster->ResvAction(MON_AC_STAND, 1);
	else
	{
		pMonster->m_nMoveVec = *pos;
		pMonster->ResvAction(action, 1);
	}

	return false;
}	

/*
//--------------------------------------------------------------------------
void MonsterAI::SetAttack(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	TEST
	//pMonster->m_nUseAtkNum = 1;

	//	이번턴에 할 공격을 선택한다.
	pMonster->m_nUseAtkNum = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount); 

	while(1)
	{
		pMonster->m_nUseAtkNum = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount);

		if(0 == pMonster->m_Attack[pMonster->m_nUseAtkNum].CoolTime)
		{
			pMonster->m_Attack[pMonster->m_nUseAtkNum].CoolTime
					= pMonster->m_Attack[pMonster->m_nUseAtkNum].MaxCoolTime;
			break;
		}
	}

	pMonster->m_bIsSuccessAttack = false;
}
*/

//--------------------------------------------------------------------------
void MonsterAI::ReceiveAttack(Monster* pM)
//--------------------------------------------------------------------------
{
	pM->m_bIsBattle = true;

	//	서서 있는 상태에서 맞은 데미지일 경우만 테이블을 날려준다.
	if(MON_AC_RCV_GROUND_ATTACK == pM->m_NextActState)
	{
		pM->m_nSelectAtkTable = MON_USE_RCV_HIT_TABLE;
		AI_ResvState(pM, MON_AI_WAIT_ORDER);
	}
	//	공중에 뜬 데미지
	else
	{
		AI_ResvState(pM, MON_AI_RCV_DEMEGE);
	}
}

//--------------------------------------------------------------------------
void MonsterAI::StartBattle(Monster* pM)
//--------------------------------------------------------------------------
{
	pM->m_bIsBattle = true;
	pM->m_bIsFirstAttack = true;
	AI_ResvState(pM, MON_AI_WAIT_ORDER);

}

//--------------------------------------------------------------------------
void MonsterAI::EndBattle(Monster* pM)
//--------------------------------------------------------------------------
{
	pM->m_nSelectAtkTable = MON_USE_NORMAL_TABLE;
	pM->m_bIsBattle = false;
	pM->m_bIsFirstAttack = true;
	AI_ResvState(pM, MON_AI_WAIT_ORDER);
}


//--------------------------------------------------------------------------
bool MonsterAI::CheckAttackRange(Monster* pM)
//--------------------------------------------------------------------------
{
	//	범위가 넓으면 공격하지 못한다.
	if( SQR(pM->m_Attack[pM->m_nUseAtkNum].AtkRect.x2) < SQR(pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX) )	{return false;}

	//	범위가 좁으면 공격하지 못한다.
	if( SQR(pM->m_Attack[pM->m_nUseAtkNum].AtkRect.x1) > SQR(pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX) )	{return false;}

	//	범위가 넓으면 공격하지 못한다.
	if( (pM->m_Attack[pM->m_nUseAtkNum].AtkRect.y2) < (pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY) )	{return false;}

	//	범위가 좁으면 공격하지 못한다.
	if( (pM->m_Attack[pM->m_nUseAtkNum].AtkRect.y1) > (pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY) )	{return false;}

	return true;
}


//--------------------------------------------------------------------------
int MonsterAI::CheckNextAction(Monster* pM)
//--------------------------------------------------------------------------
{
	//	통같은 경우(공격이 없음)
	if(0 == pM->m_nAtkMaxCount)
	{
		return MON_AI_READY_TO_HIT;
	}

	//	전투 상태라면
	if(pM->m_bIsBattle)
	{
		//범위 밖이면 전투를 빼준다.
		if(SQR(pM->m_nRange_OutBattle) < pM->m_CharInfo->m_nPos.Sqr_Distance(pM->pMonAsIns->m_posX, pM->pMonAsIns->m_posY, pM->pMonAsIns->m_posZ) )
		{
			EndBattle(pM);
			return MON_AI_WAIT_ORDER;
		}

		//	최초 어택이면 최초 공격을 해준다.
		if(pM->m_bIsFirstAttack)
		{
			pM->m_bIsFirstAttack = false;
			return MON_AI_ATTACK;
		}

		//	미리 200주사위를 던져 놓는다.(1~200)
		int dice = SUTIL_GetRandom()%200+1;

		//	TEST
		//return MON_AI_ATTACK_FRONT;

		//	사용할 테이블을 설정한다.
		if(MON_USE_NORMAL_TABLE == pM->m_nSelectAtkTable)
		{
			if(MON_MELEE_TYPE == pM->m_nMelee_or_Range)
			{
				if(dice <= Mon_Melee_NormalTable[0][0])	{return MON_AI_ATTACK;}
				dice -= Mon_Melee_NormalTable[0][0];

				if(dice <= Mon_Melee_NormalTable[0][1])	{return MON_AI_ATTACK;}
				dice -= Mon_Melee_NormalTable[0][1];

				return MON_AI_READY_TO_HIT;
			}
			else	//MON_RANGE_TYPE
			{
				if(dice <= Mon_Range_NormalTable[0][0])	{return MON_AI_ATTACK;}
				dice -= Mon_Range_NormalTable[0][0];

				if(dice <= Mon_Range_NormalTable[0][1])	{return MON_AI_ATTACK;}
				dice -= Mon_Range_NormalTable[0][1];

				return MON_AI_READY_TO_HIT;
			}
		}
		else if(MON_USE_RCV_HIT_TABLE == pM->m_nSelectAtkTable)
		{
			//	테이블을 다시 일반으로 돌려준다. (데미가 들어오면 다시 이 테이블로 바뀐다.
			pM->m_nSelectAtkTable = MON_USE_NORMAL_TABLE;

			int level = pM->m_nAccumulatedHit;
			if(5 < level)	{level = 5;}

			if(MON_MELEE_TYPE == pM->m_nMelee_or_Range)
			{
				if(dice <= Mon_Melee_RcvAtckTable[level][0])	{return MON_AI_READY_TO_HIT;}
				dice -= Mon_Melee_RcvAtckTable[level][0];

				if(dice <= Mon_Melee_RcvAtckTable[level][1])	{return MON_AI_RESIST_ATTACK;}
				dice -= Mon_Melee_RcvAtckTable[level][1];

				return MON_AI_ESCAPE;
			}
			else	//MON_RANGE_TYPE
			{
				if(dice <= Mon_Range_RcvAtckTable[level][0])	{return MON_AI_READY_TO_HIT;}
				dice -= Mon_Range_RcvAtckTable[level][0];

				if(dice <= Mon_Range_RcvAtckTable[level][1])	{return MON_AI_RESIST_ATTACK;}
				dice -= Mon_Range_RcvAtckTable[level][1];

				return MON_AI_ESCAPE;
			}
		}
	}

	//	전투상태가 아니라면

	//범위를 체크해서 전투상태로 만들어준다.
	if(SQR(pM->m_nRange_InBattle) > pM->m_CharInfo->m_nPos.Sqr_Distance(pM->pMonAsIns->m_posX, pM->pMonAsIns->m_posY, pM->pMonAsIns->m_posZ))
	{
		StartBattle(pM);
		return MON_AI_WAIT_ORDER;
	}

	return MON_AI_LOOKAROUND;
}


//--------------------------------------------------------------------------
void MonsterAI::AI_ChangeState(Monster* pMonster)
//--------------------------------------------------------------------------
{
	pMonster->m_nAiState = pMonster->m_nAiNextState;
	pMonster->m_nAiNextState = MON_AI_NULL;

	//	타이머를 초기화시켜준다.
	pMonster->m_nAiPtnLimitTime = 100;
	pMonster->m_nAiTimer = 0;
}


//--------------------------------------------------------------------------
int MonsterAI::Process(Monster* pMonster)
//--------------------------------------------------------------------------
{
/*
	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//	명령이 끝난 상태이므로 새로운 명령을 준다.
	if(pMonster->m_nAiState == MON_AI_WAIT_ORDER)
	{
		AI_ResvState(pMonster, CheckNextAction(pMonster));
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
*/

	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//범위를 체크해서 전투상태로 만들어준다.
	if(false == pMonster->m_bIsBattle)
	{
		if(SQR(pMonster->m_nRange_InBattle) > 
			pMonster->m_CharInfo->m_nPos.Sqr_Distance(pMonster->pMonAsIns->m_posX, pMonster->pMonAsIns->m_posY, pMonster->pMonAsIns->m_posZ))
		{
			StartBattle(pMonster);
			pMonster->m_nAiPtnProcess = 0;
			pMonster->ResvAction(MON_AC_STAND, 0);
			return 1;
		}
	}

	//	명령의 시간이 끝난 상태라면
	if(MON_AC_STAND == pMonster->m_ActState)
	{
		if(pMonster->m_nAiTimer >= pMonster->m_nAiPtnLimitTime)
		{
			//	통같은 경우(공격이 없음)
			if(0 == pMonster->m_nAtkMaxCount)		{return 1;}

			//	전투 상태라면
			if(pMonster->m_bIsBattle)
			{
				pMonster->m_nAiPtnProcess = (pMonster->m_nAiPtnProcess+1)%pMonster->m_nAiPtnTotCnt;
				AI_ResvState(pMonster, pMonster->m_nAiPtnData[pMonster->m_nAiPtnProcess]);
			}
			else
			{
				if(80 < SUTIL_GetRandom()%100)
				{
					AI_ResvState(pMonster, MON_AI_READY_TO_HIT);
				}
				else
				{
					AI_ResvState(pMonster, MON_AI_LOOKAROUND);
				}
			}
		}
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
}

//--------------------------------------------------------------------------
int MonsterAI::Process_BOSS1(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//	명령이 끝난 상태이므로 새로운 명령을 준다.
	if(pMonster->m_nAiState == MON_AI_WAIT_ORDER)
	{
		AI_ResvState(pMonster, CheckNextAction(pMonster));
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
}


//--------------------------------------------------------------------------
int MonsterAI::Process_BOSS2(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//	명령이 끝난 상태이므로 새로운 명령을 준다.
//	if(pMonster->m_nAiState == MON_AI_WAIT_ORDER)
//	{
//		AI_ResvState(pMonster, CheckNextAction(pMonster));
//	}

	//	명령의 시간이 끝난 상태라면
	if(MON_AC_STAND == pMonster->m_ActState)
	{
		if(pMonster->m_nAiTimer >= pMonster->m_nAiPtnLimitTime)
		{
			pMonster->m_nAiPtnProcess = (pMonster->m_nAiPtnProcess+1)%pMonster->m_nAiPtnTotCnt;

			AI_ResvState(pMonster, pMonster->m_nAiPtnData[pMonster->m_nAiPtnProcess]);
		}
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
}


/*

//--------------------------------------------------------------------------
int MonsterAI::Process_BOSS2(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//	명령이 끝난 상태이므로 새로운 명령을 준다.
	if(pMonster->m_nAiState == MON_AI_WAIT_ORDER)
	{
		AI_ResvState(pMonster, CheckNextAction(pMonster));
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
}

*/
//--------------------------------------------------------------------------
int MonsterAI::Process_BOSS5(Monster* _pM)
//--------------------------------------------------------------------------
{
	BossMon5_1* pMonster = (BossMon5_1*)_pM;

	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

	//	공격을 위한 주사위를 던진다.
	int rnd = SUTIL_GetRandom()%100;

	switch(pMonster->m_nBossStep)
	{
		case BOSS_STAND:
		//---------------------------------------------------------
		{
			pMonster->m_nNowDownCool--;

			//	서 있을 상태에서만 명령을 내린다.
			if(MON_AC_STAND == pMonster->m_ActState)
			{
				//	피가 없으면 없앤다.
				if(1 > pMonster->m_Stet.m_Hp)
				{
					pMonster->ResvBoss5_AllAction(MON_AC_ING_DOWN, 0);
					return 1;
				}

				//	숨고 정면 보스가 나오게 해준다.
				if(2 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4) || 0 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4))
				{
					pMonster->ResvBoss5_AllAction(MON_AC_HIDE, 0);
					return 1;
				}

				//	다리 데미지에 따라 앉게 해준다.
				if(1 > pMonster->m_nNowLegHp)
				{
					pMonster->ResvBoss5_AllAction(MON_AC_FAINTING, 0);
					return 1;
				}

				//	서있을때 타이머에 따라 앉게 해준다.
				if(1 > pMonster->m_nNowDownCool)
				{
					pMonster->ResvBoss5_AllAction(MON_AC_ING_SIT, 0);
					return 1;
				}

				//	공격 명령을 내린다.
				//	첫 공격이면 무조건 공격확률을 만든다.
				if(true == pMonster->isFirstTouch)	{rnd = 0;}
				
				if(ATTACK_PROTAGE > rnd)
				{
					//	공격의 상태를 정한다.
					pMonster->ResvBoss5_AllAction(pMonster->m_Attack[pMonster->CheckPassableAttack()].Name , 0);
				}
				else
				{
					pMonster->ResvBoss5_AllAction(MON_AC_REST, 0);				//	휴식을 취한다.
				}
			}
			//	대기 상태일 경우
			else if(MON_AC_REST == pMonster->m_ActState)
			{
				//	맞았을시 스탠드 상태로 한다.
				pMonster->ResvBoss5_AllAction(MON_AC_STAND, 0);
			}
			break;
		}
		case BOSS_SIT:
		//---------------------------------------------------------
		{
			//	점프해서 올라갔을경우
			if(pMonster->isJumpChar)
			{
				//	코어를 깬 경우 / 전체 피가 없는 경우
				if(0 > pMonster->m_nCoreHp || 1 > pMonster->m_Stet.m_Hp)
				{
					if(0 == pMonster->m_CharInfo->m_nPos.z)
					{
						if(true == 	Character::Set_MustAction(pMonster->m_CharInfo->m_nPos.x-18,
												pMonster->m_CharInfo->m_nPos.y+144,
												HERO_JumpDown,SDIR_RIGHT))
						{
							pMonster->ResvBoss5_AllAction(MON_AC_SIT_STAND, 0);
							return 1;
						}
					}
				}
			}
			else		//	주인공이 올라가기 전 상황
			{
				pMonster->m_nPassbleJumpTimer = (pMonster->m_nPassbleJumpTimer+1)%80;

				// 캐릭터를 점프시킨다.
				if(	40 > pMonster->m_nPassbleJumpTimer &&
					110 < pMonster->m_CharInfo->m_nPos.x &&
					160 > pMonster->m_CharInfo->m_nPos.x &&
					SDIR_RIGHT == pMonster->m_CharInfo->m_Direction &&
					190 < pMonster->m_CharInfo->m_nPos.y &&
					240 > pMonster->m_CharInfo->m_nPos.y &&
					false == pMonster->isJumpChar)
				{
					if(true == Character::Set_MustAction(243,110,HERO_JumpUp,SDIR_RIGHT))
					{
						pMonster->isJumpChar = true;
					}
				}

				if(MON_AC_SIT == pMonster->m_ActState)
				{
					//공격 명령을 내린다.
					//	타고 올라가야 하는 시간동안에는 대기상태로 있는다.
					if(40 > pMonster->m_nPassbleJumpTimer && false == pMonster->isJumpChar)		{rnd = 99;}

					if(ATTACK_PROTAGE > rnd)
					{
						//	공격의 상태를 정한다.
						pMonster->ResvBoss5_AllAction(pMonster->m_Attack[pMonster->CheckPassableAttack()].Name, 0);
					}
					else
					{
						pMonster->ResvBoss5_AllAction(MON_AC_SIT, 0);				//	휴식을 취한다.
					}
				}
			}
			break;
		}
		case BOSS_DOWN:
		//---------------------------------------------------------
		{
			//	피가 없으면 없앤다.
			if(1 > pMonster->m_Stet.m_Hp)
			{
				pMonster->ResvBoss5_AllAction(MON_AC_DOWNED, 0);
				return 1;
			}

			if(1 > pMonster->m_nFaintHp)
			{
				//	다리의 피를 돌려준다.
				pMonster->m_nNowLegHp = pMonster->m_nMaxLegHp;
				pMonster->ResvBoss5_AllAction(MON_AC_AWAK, 0);
				return 1;
			}

			break;
		}
		case BOSS_STAND_FACESIDE:
		//---------------------------------------------------------
		{
			if(1 > pMonster->m_nFaceLeftArmHp)
			{
				if(0 == pMonster->m_nFaceLeftArmGenTimer)
				{
					pMonster->m_nFaceLeftArmGenTimer = ARM_REGENTIME_MAX;
					pMonster->ResvBoss5_AllAction(MON_AC_FACE_LOST_LEFTHAND, 0);
					return 1;
				}
				else
				{
					pMonster->m_nFaceLeftArmGenTimer--;

					if(0 == pMonster->m_nFaceLeftArmGenTimer)
					{
						pMonster->m_nFaceLeftArmHp = pMonster->m_nMaxFaceLeftArmHp;
						pMonster->ResvBoss5_AllAction(MON_AC_REGEN_L_ARM_FRONTSIDE, 0);
						return 1;
					}
				}
			}

			if(1 > pMonster->m_nFaceRightArmHp)
			{
				if(0 == pMonster->m_nFaceRightArmGenTimer)
				{
					pMonster->m_nFaceRightArmGenTimer = ARM_REGENTIME_MAX;
					pMonster->ResvBoss5_AllAction(MON_AC_FACE_LOST_RIGHTHAND, 0);
					return 1;
				}
				else
				{
					pMonster->m_nFaceRightArmGenTimer--;

					if(0 == pMonster->m_nFaceRightArmGenTimer)
					{
						pMonster->m_nFaceRightArmHp = pMonster->m_nMaxFaceRightArmHp;
						pMonster->ResvBoss5_AllAction(MON_AC_REGEN_R_ARM_FRONTSIDE, 0);
						return 1;
					}
				}
			}

			//	서 있을 상태에서만 명령을 내린다.
			if(MON_AC_STAND_FRONTSIDE == pMonster->m_ActState)
			{
				if(1 > pMonster->m_Stet.m_Hp)
				{
					pMonster->ResvBoss5_AllAction(MON_AC_DIE, 0);
					return 1;
				}

				//	숨고 측면 보스가 나오게 해준다.
				if(1 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4) || 3 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4))
				{
					pMonster->ResvBoss5_AllAction(MON_AC_HIDE_FRONTSIDE, 0);
					return 1;
				}

				//	피가 없으면 없앤다.
//				if(1 > pMonster->m_Stet.m_Hp)
//				{
//					pMonster->ResvBoss5_AllAction(MON_AC_ING_DOWN, 0);
//					return 1;
//				}

				//	숨고 정면 보스가 나오게 해준다.
//				if(1 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4) || 3 == pMonster->m_Stet.m_Hp/(pMonster->m_Stet.m_MaxHp/4))
//				{
//					pMonster->ResvBoss5_AllAction(MON_AC_HIDE, 0);
//					return 1;
//				}

				//	다리 데미지에 따라 앉게 해준다.
//				if(1 > pMonster->m_nNowLegHp)
//				{
//					pMonster->ResvBoss5_AllAction(MON_AC_FAINTING, 0);
//					return 1;
//				}

				//	공격 명령을 내린다.
				//	첫 공격이면 무조건 공격확률을 만든다.
				//if(true == pMonster->isFirstTouch)	{rnd = 0;}
				
				if(ATTACK_PROTAGE > rnd)
				{
					//	공격의 상태를 정한다.
					pMonster->ResvBoss5_AllAction(pMonster->m_Attack[pMonster->CheckPassableAttack()].Name , 0);
				}
				else
				{
//					pMonster->ResvBoss5_AllAction(MON_AC_HIDE_FRONTSIDE , 0);
					//	
					//pMonster->ResvBoss5_AllAction(MON_AC_REST, 0);				//	휴식을 취한다.
				}

			}
			//	대기 상태일 경우
//			else if(MON_AC_REST == pMonster->m_ActState)
//			{
//				//	맞았을시 스탠드 상태로 한다.
//				pMonster->ResvBoss5_AllAction(MON_AC_STAND, 0);
//			}
			break;
		}
	}

	return 1;
}



//--------------------------------------------------------------------------
//	멍청히 서 있는다.
void MonsterAI::AI_F_WAIT_ORDER(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	액션의 제한시간을 정한다.
	if(0 == pMonster->m_nAiTimer)
	{
		pMonster->m_nAiPtnLimitTime = 10+SUTIL_GetRandom()%20;
	}

	//	아무행동도 하지 않는다.
}


//--------------------------------------------------------------------------
//	멍청히 서 있는다.
void MonsterAI::AI_F_READY_TO_HIT(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	액션의 제한시간을 정한다.
	if(0 == pMonster->m_nAiTimer)
	{
		pMonster->m_nAiPtnLimitTime = 10+SUTIL_GetRandom()%20;
	}

	//	아무행동도 하지 않는다.
}


//--------------------------------------------------------------------------
//	주위를 살펴본다.
void MonsterAI::AI_F_LOOKAROUND(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	액션의 제한시간을 정한다.
	if(0 == pMonster->m_nAiTimer)
	{
		pMonster->m_nAiPtnLimitTime = 20+SUTIL_GetRandom()%20;
		pMonster->m_nDstLookSeed = (pMonster->m_nDstLookSeed+1)%4;

		//	액션을 실행한다. (추후 이동방향 추가)
		Position3D pos;
		pos.Init( (SUTIL_GetRandom()%100)-50,   (SUTIL_GetRandom()%50)-25, 0);

		Move(pMonster, &pos, MON_AC_MOVE);
	}

	// 액션의 종료를 체크해서 완료시킨다.
	if(MON_AC_STAND == pMonster->m_NextActState)
	{
		pMonster->m_nAiTimer = pMonster->m_nAiPtnLimitTime;
	}
}






//--------------------------------------------------------------------------
//	주인공을 공격한다.
void MonsterAI::AI_F_ATTACK(Monster* pM)
//--------------------------------------------------------------------------
{
	if(0 == pM->m_nAiTimer)
	{
		//	액션의 제한시간을 정한다.
		pM->m_nAiPtnLimitTime = 100+SUTIL_GetRandom()%100;

		//	초기 공격 좌표를 찍어놓는다. 이거리로 부터 몇픽셀 이상이면 탈출로 잡는다.
		pM->m_SaveAtkPos = pM->m_CharInfo->m_nPos;

		//	공격을 셋팅한다.
		pM->SetAttack();
	}

//	//	전투액션 범위보다 크면 전투를 풀어준다.
//	if(SQR(pM->m_nRange_OutAction) < (pM->m_CharInfo->m_nPos.Sqr_Distance(pM->m_SaveAtkPos)) )
//	{
//		//	전투를 풀어준다.
//		EndBattle(pM);
//		return;
//	}

	//	성공한 상태이면 오더를 기다리는 상태로 바꾼다.
	if(true == pM->m_bIsSuccessAttack)
	{
		if(MON_AC_STAND == pM->m_ActState)
		{
			pM->m_nAiTimer = pM->m_nAiPtnLimitTime;
//			AI_ResvState(pM, MON_AI_WAIT_ORDER);
			return;
		}
	}
	else
	{
		if(pM->m_nAiTimer == pM->m_nAiPtnLimitTime)
		{
			pM->ResvAction(MON_AC_STAND , 0);
			return;
		}

		if(CheckAttackRange(pM))
		{
			pM->m_bIsSuccessAttack = true;
			pM->ResvAction(pM->m_Attack[pM->m_nUseAtkNum].Name , 0);
			return;
		}

		//	추적 위치 설정
		if(0 == pM->m_nAiTimer%(pM->pMonAsIns->m_sprite->GetAFrames(pM->m_nUsingImgIdx[MON_AC_MOVE]) ))
		{
			//	공격 거리 체크
			Position3D AtkPoint;

			if(pM->m_CharInfo->m_nPos.x > pM->pMonAsIns->m_posX)
			{
				AtkPoint.x = pM->m_CharInfo->m_nPos.x - pM->m_Attack[pM->m_nUseAtkNum].AtkRect.x2;
			}
			else
			{
				AtkPoint.x = pM->m_CharInfo->m_nPos.x + pM->m_Attack[pM->m_nUseAtkNum].AtkRect.x2;
			}
			

			AtkPoint.y = pM->m_CharInfo->m_nPos.y - pM->m_Attack[pM->m_nUseAtkNum].AtkRect.y2;

//			if(pM->m_CharInfo->m_nPos.y > pM->pMonAsIns->m_posY)
//			{
//				AtkPoint.y = pM->m_CharInfo->m_nPos.y - pM->m_Attack[pM->m_nUseAtkNum].AtkRect.y2;
//			}
//			else
//			{
//				AtkPoint.y = pM->m_CharInfo->m_nPos.y + pM->m_Attack[pM->m_nUseAtkNum].AtkRect.y2;
//			}


//			//	임시변수로 잠깐쓰고 밑에서 값을 다시 준다.
//			AtkPoint.z = pM->m_Attack[pM->m_nUseAtkNum].MinScope
//								+ (SUTIL_GetRandom()%(pM->m_Attack[pM->m_nUseAtkNum].MaxScope
//									- pM->m_Attack[pM->m_nUseAtkNum].MinScope));
//
//			if(0 < pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX)	{AtkPoint.x += AtkPoint.z;}
//			else														{AtkPoint.x -= AtkPoint.z;}
//			AtkPoint.y = (pM->m_CharInfo->m_nPos.y);

			AtkPoint.x -= pM->pMonAsIns->m_posX;
			AtkPoint.y -= pM->pMonAsIns->m_posY;
			AtkPoint.z = 0;

//			Position3D pos;
//
//			pos.x = pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX;
//			pos.y = pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY;
//			pos.z = pM->m_CharInfo->m_nPos.z - pM->pMonAsIns->m_posZ;

			Move(pM, &AtkPoint, MON_AC_BEHOLD);
		}

//		if(1 == pM->m_nAiTimer)
//		{
//			Position3D pos;
//
//			pos.x = pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX;
//			pos.y = pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY;
//			pos.z = pM->m_CharInfo->m_nPos.z - pM->pMonAsIns->m_posZ;
////			pos = pM->m_CharInfo->m_nPos - pM->m_nPos;
//
//			Move(pM, &pos, 0);
//		}
//
//		// 몬스터의 움직임이 한 움직임이 끝나면 타이머를 1로 만들어서 추적을 재설정하게 해준다.
//		int movetime = pM->pMonAsIns->m_sprite->GetAFrames(pM->m_nUsingImgIdx[MON_AC_MOVE]);
//		if(movetime <= pM->m_nAiTimer+1)	{pM->m_nAiTimer = 0;}
	}
}



//--------------------------------------------------------------------------
//	움직일 수 없는 보스들의 공격
void MonsterAI::AI_F_ATTACK_DONTMOVE(Monster* pM)
//--------------------------------------------------------------------------
{
	if(0 == pM->m_nAiTimer)
	{
		//	액션의 제한시간을 정한다.
		pM->m_nAiPtnLimitTime = 100+SUTIL_GetRandom()%100;

		//	공격을 셋팅한다.
		pM->SetAttack();
	}

	//	성공한 상태이면 오더를 기다리는 상태로 바꾼다.
	if(true == pM->m_bIsSuccessAttack)
	{
		if(MON_AC_STAND == pM->m_ActState)
		{
			pM->m_nAiTimer = pM->m_nAiPtnLimitTime;
			return;
		}
	}
	else
	{
		if(pM->m_nAiTimer == pM->m_nAiPtnLimitTime)
		{
			pM->ResvAction(MON_AC_STAND , 0);
			return;
		}

		if(CheckAttackRange(pM))
		{
			pM->m_bIsSuccessAttack = true;
			pM->ResvAction(pM->m_Attack[pM->m_nUseAtkNum].Name , 0);
			return;
		}
	}
}

//--------------------------------------------------------------------------
//	웜 보스 특별 행동 버로우상태로 움직인다.
void MonsterAI::AI_F_WORM_BURROWMOVE(Monster* pM)
//--------------------------------------------------------------------------
{
	if(0 == pM->m_nAiTimer)
	{
		//	액션의 제한시간을 정한다.
		pM->m_nAiPtnLimitTime = 50+SUTIL_GetRandom()%20;
		pM->ResvAction(MON_AC_WORM_BURROW, 0);
		return;
	}

	//	미리 올려놓고 대기한다.
	if(pM->m_nAiTimer +8 == pM->m_nAiPtnLimitTime)
	{
		pM->ResvAction(MON_AC_WORM_UNBURROW, 0);
		return;
	}

	//	버로우 움직임 상태라면
	if(MON_AC_RUN == pM->m_ActState)
	{
		if(0 == pM->m_nAiTimer%(pM->pMonAsIns->m_sprite->GetAFrames(pM->m_nUsingImgIdx[MON_AC_RUN]) ))
		{
			Position3D pos;

			pos.x = pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX;
			pos.y = pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY;
			pos.z = pM->m_CharInfo->m_nPos.z - pM->pMonAsIns->m_posZ;
			Move(pM, &pos, MON_AC_RUN);
		}
	}
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_MOVE_BACK(Monster* pM)
//--------------------------------------------------------------------------
{

	//	처음 들어왔다면 셋팅해준다.
	if(0 == pM->m_nAiTimer)
	{
		//	액션의 제한시간을 정한다.
		pM->m_nAiPtnLimitTime = 30+SUTIL_GetRandom()%20;
	}

	//	시간이 지나면 서있는 상태로 바꿔줘야 액션이 끝난다.
	if(pM->m_nAiPtnLimitTime == pM->m_nAiTimer)
	{
		pM->ResvAction(MON_AC_STAND, 0);
		return;
	}

	//	추적 위치 설정
	if(0 == pM->m_nAiTimer%(pM->pMonAsIns->m_sprite->GetAFrames(pM->m_nUsingImgIdx[MON_AC_BEHOLD]) ))
	{
		Position3D pos;
		pos.x = pM->m_CharInfo->m_nPos.x - pM->pMonAsIns->m_posX;
		pos.y = pM->m_CharInfo->m_nPos.y - pM->pMonAsIns->m_posY;

		if(0 < pos.x)
		{
			pos.x -= (70+SUTIL_GetRandom()%40);
		}
		else
		{
			pos.x += (70+SUTIL_GetRandom()%40);
		}
		
		Move(pM, &pos, MON_AC_BEHOLD);
	}
}


/*
//--------------------------------------------------------------------------
void MonsterAI::AI_F_BEHOLD(Monster* pM)
//--------------------------------------------------------------------------
{
	//	처음 들어왔다면 셋팅해준다.
	if(0 == pM->m_nAiTimer)
	{
		//	원하는 시간 만큼 대기시간을 준다.
		pM->m_nDstTime = 40+SUTIL_GetRandom()%70;
	}

	if(pM->m_nDstTime < pM->m_nAiTimer)
	{
		AI_ResvState(pM, MON_AI_WAIT_ORDER);
		return;
	}

	//	대기하는 위치를 설정한다.
	//	추적 위치 설정
	if(1 == pM->m_nAiTimer)
	{
		Position3D pos;
		pos = pM->m_CharInfo->m_nPos - pM->m_nPos;

		if(0 < pos.x)
		{
			pos.x -= (70+SUTIL_GetRandom()%40);
		}
		else
		{
			pos.x += (70+SUTIL_GetRandom()%40);
		}
		
		Behold(pM, &pos, 0);
	}

	// 몬스터의 움직임이 한 움직임이 끝나면 타이머를 1로 만들어서 추적을 재설정하게 해준다.
	int movetime = pM->pMonAsIns[0]->m_sprite->GetAFrames(pM->m_nUsingImgIdx[MON_AC_BEHOLD]);
	if(movetime <= pM->m_nAiTimer+1)
	{
		pM->m_nDstTime -= movetime;
		pM->m_nAiTimer = 0;
	}
}


*/

//--------------------------------------------------------------------------
void MonsterAI::AI_F_RESIST_ATTACK(Monster* pM)
//--------------------------------------------------------------------------
{
	//미구현
	AI_ResvState(pM, MON_AI_WAIT_ORDER);
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_ESCAPE(Monster* pM)
//--------------------------------------------------------------------------
{
	//미구현
	AI_ResvState(pM, MON_AI_WAIT_ORDER);
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_MOVE_FIRST_POSITION(Monster* pM)
//--------------------------------------------------------------------------
{
	//	처음 들어왔다면 셋팅해준다.
	if(0 == pM->m_nAiTimer)
	{
//		pM->m_StartPos = pM->m_StartPos - pM->m_nPos;

		pM->m_StartPos.x -= pM->pMonAsIns->m_posX;
		pM->m_StartPos.y -= pM->pMonAsIns->m_posY;
		pM->m_StartPos.z -= pM->pMonAsIns->m_posZ;

		if(0 != pM->m_StartPos.Sqr_GetLength())
		{
			Move(pM, &pM->m_StartPos, MON_AC_MOVE);
		}
		else
		{
			AI_ResvState(pM, MON_AI_WAIT_ORDER);
			return;
		}
	}

	//범위를 체크해서 전투상태로 만들어준다.
	if(SQR(pM->m_nRange_InBattle) > pM->m_CharInfo->m_nPos.Sqr_Distance(pM->pMonAsIns->m_posX, pM->pMonAsIns->m_posY, pM->pMonAsIns->m_posZ))
	{
		StartBattle(pM);
		return;
	}

	//	스탠드상태면 원하는 이동량만큼 이동이 끝이란 얘기다.
	if(MON_AC_STAND == pM->m_NextActState)
	{
		AI_ResvState(pM, MON_AI_WAIT_ORDER);
	}
}

//--------------------------------------------------------------------------
void MonsterAI::AI_F_RCV_DEMEGE(Monster* pM)
//--------------------------------------------------------------------------
{
	//	스탠드상태면 원하는 이동량만큼 이동이 끝이란 얘기다.
	if(MON_AC_STAND == pM->m_ActState)
	{
		//	다음패턴으로 넘어간다.
		pM->m_nAiTimer = pM->m_nAiPtnLimitTime;
		//AI_ResvState(pM, MON_AI_WAIT_ORDER);
	}	
}























































































/*
//--------------------------------------------------------------------------
void MonsterAI::ChangeTick(Monster* pMonster, int _tick)
//--------------------------------------------------------------------------
{
	pMonster->m_AITick = _tick;
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_STAND(Monster* pMonster)
//--------------------------------------------------------------------------
{
	if(0 == pMonster->m_nPos.z)
	{
		pMonster->m_nAdjustPos.Init((SUTIL_GetRandom()%60)-30, (SUTIL_GetRandom()%30)-15, 0);
		ChangeState(pMonster, MON_AI_STROLL);
	}
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_STROLL(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	캐릭터가 범위 안에 들어오면 상태를 APPROACH로 바꿔준다.
	if(SQR(pMonster->m_nSearchScope) > pMonster->m_nPos.Sqr_Distance(pMonster->m_CharInfo->m_nPos) || (IS_BATTLE_ON))
	{
		BATTLE_ON();
		RECHARGE_ESCAPETICK();

		//	대기상태로 진입할 확률
		if(50 < (SUTIL_GetRandom()%100))
		{
			ChangeState(pMonster, MON_AI_WATCH_HERO);
			return;
		}

		pMonster->m_nResvNextAtk = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount);
		ChangeState(pMonster, MON_AI_APPROACH);
		return;
	}
	
	if(0 < pMonster->m_AITick)	{return;}

	//	탈출틱을 초기화시켜준다.
	INIT_ESCAPETICK();
	BATTLE_OFF();

	//	범위 밖으로 너무 벗어나면 돌아온다.
	if(SQR(pMonster->m_nStrollScope) < pMonster->m_nPos.Sqr_Distance(pMonster->m_StartPos))
	{
		ChangeState(pMonster, MON_AI_RETURN_BASE);
		return;
	}

	//	캐릭터가 오기전까진 범위안에서 움직인다.
	if(0 == pMonster->m_AiDetailSeed)
	{
		pMonster->m_AiDetailSeed = 1;
		pMonster->m_AiDetailSeedStep = 0;
	}

	Position3D MovingPos;
	MovingPos.Init();
	//pMonster->m_AiDetailSeedStep++;
	//pMonster->m_AiDetailSeedStep = ((SUTIL_GetRandom())%7) + 1;
	switch(pMonster->m_AiDetailSeed)
	{
		case 1:
		//------------------------------------------------------------------------------
		{
			switch(pMonster->m_AiDetailSeedStep)
			{
				case 0:		{MovingPos.x = 20;	MovingPos.y = 5;	break;}
				case 1:		{MovingPos.x = 0;	MovingPos.y = 0;	break;}
				case 2:		{MovingPos.x = -20;	MovingPos.y = 0;	break;}
				case 3:		{MovingPos.x = 0;	MovingPos.y = 0;	break;}
				case 4:		{MovingPos.x = 0;	MovingPos.y = 10;	break;}
				case 5:		{MovingPos.x = 0;	MovingPos.y = 0;	break;}
				case 6:		{MovingPos.x = 20;	MovingPos.y = -5;	break;}
				case 7:		{MovingPos.x = 0;	MovingPos.y = 0;	break;}
				case 8:		{MovingPos.x = -5;	MovingPos.y = -20;	break;}
				case 9:		{MovingPos.x = 0;	MovingPos.y = 0;	break;}
				default:	{pMonster->m_AiDetailSeed = 0;			break;}
			}
			break;
		}
	}

	pMonster->m_AiDetailSeedStep++;

	if(0 == (MovingPos.x+MovingPos.y))
	{
		ChangeTick(pMonster, (SUTIL_GetRandom()%4+12) );
	}
	else
	{
		ChangeTick(pMonster, (SUTIL_GetRandom()%4+8) );
	}
//	}
//	else
//	{
//		ChangeTick(pMonster, pMonster->SetMovingTime(pMonster->m_nMaxMove, MovingPos.Sqr_GetLength()));
//	}
	
	Move(pMonster, &MovingPos, 1);
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_WATCH_HERO(Monster* pMonster)
//--------------------------------------------------------------------------
{
	Position3D pos;

	pos = pMonster->m_CharInfo->m_nPos+pMonster->m_nAdjustPos;

	int dis = pMonster->m_nPos.Sqr_Distance(pos);
	pos.Init();

	//	기본거리확보
	if(SQR(60) < dis)
	{
		pos = (pMonster->m_CharInfo->m_nPos) - pMonster->m_nPos + pMonster->m_nAdjustPos;
		Move(pMonster, &pos, 1);

//		if(0 < pos.x)	{pMonster->m_nDirection = SDIR_RIGHT;}
//		else			{pMonster->m_nDirection = SDIR_LEFT;}
//		SUTIL_SetDirAsprite(pMonster->pMonAsIns, pMonster->m_nDirection);
		return;
	}

	//배회한다.
	pos = (pMonster->m_CharInfo->m_nPos) - pMonster->m_nPos + pMonster->m_nAdjustPos;
	if(0 < pos.x)	{pos.x -= 60;}
	else			{pos.x += 60;}

	Move(pMonster, &pos, 1);

//	if(0 < pos.x)	{pMonster->m_nDirection = SDIR_RIGHT;}
//	else			{pMonster->m_nDirection = SDIR_LEFT;}
//	SUTIL_SetDirAsprite(pMonster->pMonAsIns, pMonster->m_nDirection);

	RECHARGE_ESCAPETICK();

	if(1 > pMonster->m_AITick)
	{
		//	대기상태를 벗어날 확률
		if(40 < (SUTIL_GetRandom()%100))
		{
			ChangeState(pMonster, MON_AI_STROLL);
			return;
		}

		pMonster->m_nAdjustPos.Init((SUTIL_GetRandom()%60)-30, (SUTIL_GetRandom()%30)-15, 0);
		ChangeTick(pMonster, (30+SUTIL_GetRandom()%10));
	}
}

//--------------------------------------------------------------------------
void MonsterAI::AI_F_APPROACH(Monster* pMonster)
//--------------------------------------------------------------------------
{
	Position3D pos;
	int dis = pMonster->m_nPos.Sqr_Distance(pMonster->m_CharInfo->m_nPos);

	//	최대거리확보
	if(SQR(pMonster->m_Attack[pMonster->m_nResvNextAtk].MaxScope) < dis)
	{
		pos = (pMonster->m_CharInfo->m_nPos) - pMonster->m_nPos;
		Move(pMonster, &pos, 1);
		return;
	}

	//	최소거리확보
	//int disx = pMonster->m_CharInfo->m_nPos.x - pMonster->m_nPos.x;
	pos = (pMonster->m_CharInfo->m_nPos) - (pMonster->m_nPos);
	if(SQR(pMonster->m_Attack[pMonster->m_nResvNextAtk].MinScope) > SQR(pos.x))
	{
		if(0 < pos.x)	{pos.x -= (pMonster->m_Attack[pMonster->m_nResvNextAtk].MinScope);}
		else			{pos.x += (pMonster->m_Attack[pMonster->m_nResvNextAtk].MinScope);}
//		Move(pMonster, &pos, pMonster->m_AiDetailSeed);
		Move(pMonster, &pos, 2);
		return;
	}

	//	y 거리 확보
	if(SQR(6) < SQR(pMonster->m_nPos.y - pMonster->m_CharInfo->m_nPos.y))
	{
		pos = (pMonster->m_CharInfo->m_nPos) - pMonster->m_nPos;
		Move(pMonster, &pos, 1);
		return;
	}

	//	공 격
	RECHARGE_ESCAPETICK();
	ChangeState(pMonster, MON_AI_ATTACK);
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_ATTACK(Monster* pMonster)
//--------------------------------------------------------------------------
{
	if(0 < pMonster->m_AITick)	{return;}

	if(MON_NOT_ATTACK == pMonster->m_nResvNextAtk)		//	공격후 다시 접근 상태부터 한다.
	{
		RECHARGE_ESCAPETICK();
		ChangeState(pMonster, MON_AI_STROLL);
//		pMonster->m_nResvNextAtk = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount);
//		ChangeState(pMonster, MON_AI_APPROACH);
		return;
	}

	int dis = pMonster->m_nPos.Sqr_Distance(pMonster->m_CharInfo->m_nPos);


	if(SQR(6) < SQR(pMonster->m_nPos.y - pMonster->m_CharInfo->m_nPos.y))
	{
		//ChangeState(pMonster, MON_AI_APPROACH);
		ChangeState(pMonster, MON_AI_STROLL);
		return;
	}

	if(SQR(pMonster->m_Attack[pMonster->m_nResvNextAtk].MinScope) > dis)
	{
		//ChangeState(pMonster, MON_AI_APPROACH);
		ChangeState(pMonster, MON_AI_STROLL);
		return;
	}

	if(SQR(pMonster->m_Attack[pMonster->m_nResvNextAtk].MaxScope) < dis)
	{
		//ChangeState(pMonster, MON_AI_APPROACH);
		ChangeState(pMonster, MON_AI_STROLL);
		return;
	}

	pMonster->ResvAction(pMonster->m_Attack[pMonster->m_nResvNextAtk].Name, 0);
	pMonster->m_nResvNextAtk = MON_NOT_ATTACK;

	RECHARGE_ESCAPETICK();
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_RCV_ATTACK(Monster* pMonster)
//--------------------------------------------------------------------------
{
	RECHARGE_ESCAPETICK();

	if(0 < pMonster->m_nPos.z)	{return;}

	if(MON_AC_STAND == pMonster->m_ActState)
	{
		//BATTLE_ON();
		//RECHARGE_ESCAPETICK();
		//pMonster->m_nResvNextAtk = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount);
		//ChangeState(pMonster, MON_AI_APPROACH);
		ChangeState(pMonster, MON_AI_STROLL);
	}
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_RETURN_BASE(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	캐릭터가 범위 안에 들어오면 상태를 APPROACH로 바꿔준다.
	if(SQR(pMonster->m_nSearchScope) > pMonster->m_nPos.Sqr_Distance(pMonster->m_CharInfo->m_nPos) || (IS_BATTLE_ON))
	{
		BATTLE_ON();
		RECHARGE_ESCAPETICK();

		//	대기상태로 진입할 확률
		if(50 < (SUTIL_GetRandom()%100))
		{
			ChangeState(pMonster, MON_AI_WATCH_HERO);
			return;
		}

		pMonster->m_nResvNextAtk = SUTIL_GetRandom()%(pMonster->m_nAtkMaxCount);
		ChangeState(pMonster, MON_AI_APPROACH);
		return;
	}

	BATTLE_OFF();

	int dis = pMonster->m_nPos.Sqr_Distance(pMonster->m_StartPos);

	if(SQR(20) > dis)
	{
		ChangeState(pMonster, MON_AI_STAND);
		return;
	}

	Position3D pos;
	pos = (pMonster->m_StartPos) - pMonster->m_nPos;

	if(0 == pMonster->m_AiDetailSeed)
	{
		pMonster->m_AiDetailSeed = 1;
	}

	Move(pMonster, &pos, pMonster->m_AiDetailSeed);
}


//--------------------------------------------------------------------------
void MonsterAI::AI_F_DIE(Monster* pMonster)
//--------------------------------------------------------------------------
{
	BATTLE_OFF();
	pMonster->ResvAction(MON_AC_DIE, 1);
}



*/







/*
	switch(seed)
	{

		case 1:
		//------------------------------------------------------------------------------
		{
			if(6 < pos->y)		{pMonster->ResvAction(MON_AC_MOVE_DOWN);		return;}
			if(-6 > pos->y)		{pMonster->ResvAction(MON_AC_MOVE_UP);			return;}
			if(6 < pos->x)		{pMonster->ResvAction(MON_AC_MOVE_RIGHT);		return;}
			if(-6 > pos->x)		{pMonster->ResvAction(MON_AC_MOVE_LEFT);		return;}
			break;
		}
		case 2:
		//------------------------------------------------------------------------------
		{
			if(6 < pos->x)		{pMonster->ResvAction(MON_AC_MOVE_RIGHT);		return;}
			if(-6 > pos->x)		{pMonster->ResvAction(MON_AC_MOVE_LEFT);		return;}
			if(6 < pos->y)		{pMonster->ResvAction(MON_AC_MOVE_DOWN);		return;}
			if(-6 > pos->y)		{pMonster->ResvAction(MON_AC_MOVE_UP);			return;}
			break;
		}

		case 1:
		//------------------------------------------------------------------------------
		{
			if(0 < pos->y)		{pMonster->ResvAction(MON_AC_MOVE_DOWN);		return;}
			if(0 > pos->y)		{pMonster->ResvAction(MON_AC_MOVE_UP);			return;}
			if(0 < pos->x)		{pMonster->ResvAction(MON_AC_MOVE_RIGHT);		return;}
			if(0 > pos->x)		{pMonster->ResvAction(MON_AC_MOVE_LEFT);		return;}
			break;
		}
		case 2:
		//------------------------------------------------------------------------------
		{
			if(0 < pos->x)		{pMonster->ResvAction(MON_AC_MOVE_RIGHT);		return;}
			if(0 > pos->x)		{pMonster->ResvAction(MON_AC_MOVE_LEFT);		return;}
			if(0 < pos->y)		{pMonster->ResvAction(MON_AC_MOVE_DOWN);		return;}
			if(0 > pos->y)		{pMonster->ResvAction(MON_AC_MOVE_UP);			return;}
			break;
		}

	}
*/




/*
//--------------------------------------------------------------------------
int MonsterAI::Process(Monster* pMonster)
//--------------------------------------------------------------------------
{
	if(0 < pMonster->m_AITick)			{pMonster->m_AITick--;}
	if(0 < pMonster->m_nEscapeCurTick)	{pMonster->m_nEscapeCurTick--;}
	
	if(MON_AC_RCV_HOLDING == pMonster->m_ActState)	{return 1;}
	//	메세지를 받는다.

	//	물리적인 공격을 받았을 경우
	if(MON_AC_RCV_GROUND_ATTACK == pMonster->m_ActState ||
		MON_AC_RCV_DOWN_ATTACK == pMonster->m_ActState ||
		MON_AC_RCV_AIR_ATTACK == pMonster->m_ActState ||
		MON_AC_ING_AIRDOWN == pMonster->m_ActState)
	{
		RECHARGE_ESCAPETICK();
		ChangeState(pMonster, MON_AI_RCV_ATTACK);
	}
	else if(IS_BATTLE_ON)
	{
		if(IS_ESCAPETICK_NULL)
		{
			BATTLE_OFF();
			pMonster->m_nResvNextAtk = MON_NOT_ATTACK;
			ChangeState(pMonster, MON_AI_STROLL);
		}
	}

	//	피가 없을경우
//	if(1 > pMonster->m_Stet.m_Hp)
//	{
//		ChangeState(pMonster, MON_AI_RCV_ATTACK);
//	}

	int nTmpState = pMonster->m_AIState;


	AIFuncPtr[nTmpState](pMonster);

	return 1;
}
*/

/*
//--------------------------------------------------------------------------
int MonsterAI::Process_BOSS5_Dummy(Monster* pMonster)
//--------------------------------------------------------------------------
{
	//	타이머 셋팅
	pMonster->m_nAiTimer = (pMonster->m_nAiTimer+1)%100000;

//	if(1 > pMonster->m_Stet.m_Hp)	{return 1;}

	//	명령이 끝난 상태이므로 새로운 명령을 준다.
	if(pMonster->m_nAiState == MON_AI_WAIT_ORDER)
	{
//		//	AI_ResvState(pMonster, CheckNextAction_Boss5(pMonster));
//		//	상태를 변경시켜준다.
//		pMonster->m_nAiState = MON_AI_READY_ORDER;
//		SetAttack(pMonster);
//		pMonster->SetMessage(MSG_BOSS_CHANGESTATE,	MON_AI_ATTACK_DONTMOVE,	pMonster->m_nUseAtkNum);
	}

	//	상태 변경
	if(MON_AI_NULL != pMonster->m_nAiNextState)	{AI_ChangeState(pMonster);}

	//	ai 실행
	AIFuncPtr[pMonster->m_nAiState](pMonster);

	return 1;
}
*/