#include "FieldObject.h"



//--------------------------------------------------------------------------------------
FieldObject::FieldObject()
//--------------------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------------------
FieldObject::~FieldObject()
//--------------------------------------------------------------------------------------
{
	SUTIL_FreeSprite(m_Asins->m_sprite);
	SUTIL_FreeSpriteInstance(m_Asins);
}


//--------------------------------------------------------------------------------------
void FieldObject::ResvAction(int nNextAction)
//--------------------------------------------------------------------------------------
{
	m_nNextAction = nNextAction;
}

//--------------------------------------------------------------------------------------
void FieldObject::SetAngle(int x)
//--------------------------------------------------------------------------------------
{
	m_nXCamAngle = x;
}


//==============================================================================================================




//--------------------------------------------------------------------------------------
Npc::Npc(int idx, int x, int y)
//--------------------------------------------------------------------------------------
{
	m_nImgIdx = idx;
	m_nXPos = x;
	m_nYPos = y;

	m_nAction = ACT_NPC_NULL;

//	m_NpcAsins = ReadyAspriteInsNPC(idx, x, y);
}



//--------------------------------------------------------------------------------------
Npc::~Npc()
//--------------------------------------------------------------------------------------
{
	SUTIL_FreeSprite(m_Questionins->m_sprite);
	SUTIL_FreeSpriteInstance(m_Questionins);
}


//--------------------------------------------------------------------------------------
void Npc::Initialize(int nDummy1, int nDummy2)
//--------------------------------------------------------------------------------------
{

}


//--------------------------------------------------------------------------------------
void Npc::Release()
//--------------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------------
int  Npc::CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5)
//--------------------------------------------------------------------------------------
{
	if(m_nEvtDelay)	{return 0;}
	//nDummy1 : direction
	//nDummy2 : x1
	//nDummy3 : y1
	//nDummy4 : x2
	//nDummy5 : y2
	if(nDummy2 > m_nXPos)	{return 0;}
	if(nDummy3 > m_nYPos)	{return 0;}
	if(nDummy4 < m_nXPos)	{return 0;}
	if(nDummy5 < m_nYPos)	{return 0;}

	//	상 1, 하 2, 좌 3, 우 4
	if(nDummy1)
	{
		if(3 == nDummy1)
		{
			SUTIL_SetDirAsprite(m_Asins, SDIR_RIGHT);
		}
		else if(4 == nDummy1)
		{
			SUTIL_SetDirAsprite(m_Asins, SDIR_LEFT);
		}
	}

	m_nEvtDelay = 0;
	return m_nSaveEvtCode;
}


//--------------------------------------------------------------------------------------
void Npc::Process()
//--------------------------------------------------------------------------------------
{
	nTimer = (nTimer+1)%6;

	if(0 < m_nEvtDelay)
	{
		m_nEvtDelay--;
	}
	
	if(m_nNextAction != m_nAction)
	{
		SetAction();
		m_nAction = m_nNextAction;
		m_nNextAction = ACT_NPC_NULL;
	}

//	SUTIL_SetXPosAsprite(m_NpcAsins, m_nXPos - m_nXCamAngle);
//	SUTIL_SetYPosAsprite(m_NpcAsins, m_nYPos);
//	SUTIL_SetZPosAsprite(m_NpcAsins, 0);

	m_Asins->CameraX = - m_nXCamAngle;

	//	에니메이션 업데이트
	SUTIL_UpdateTimeAsprite(m_Asins);

	//	 퀘스트에 따른 물음표 표시
	nQuestionNum = 9999;

	if(NPC_CALL_kail == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_findKail == GET_MAINQUEST_IDX() ||
			MAIN_QUEST_callKail == GET_MAINQUEST_IDX() ||
			(MAIN_QUEST_oldMedal == GET_MAINQUEST_IDX() && PopupUi::GET_Count(ITEM_CALL_medal) >= MAX_medal) )
		{
			nQuestionNum = 0;
		}
	}
	else if(NPC_CALL_kaien == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_goKaien == GET_MAINQUEST_IDX() ||
			MAIN_QUEST_returnKaien == GET_MAINQUEST_IDX()	)
		{
			nQuestionNum = 0;
		}
	}
	else if(NPC_CALL_citizen1 == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_goCitizen1 == GET_MAINQUEST_IDX())
		{
			nQuestionNum = 0;
		}
	}
	else if(NPC_CALL_citizen2 == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_goCitizen2 == GET_MAINQUEST_IDX())
		{
			nQuestionNum = 0;
		}
	}
	else if(NPC_CALL_citizenK == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_goCitizenK == GET_MAINQUEST_IDX() || 
			(MAIN_QUEST_findCrystal == GET_MAINQUEST_IDX() && PopupUi::GET_Count(ITEM_CALL_crystal) >= MAX_crystal) )
		{
			nQuestionNum = 0;
		}
	}
	else if(NPC_CALL_scholar == m_nSaveEvtCode)
	{
		if(MAIN_QUEST_goScholar == GET_MAINQUEST_IDX())
		{
			nQuestionNum = 0;
		}
	}
}


//--------------------------------------------------------------------------------------
void Npc::Paint()
//--------------------------------------------------------------------------------------
{
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,0 , m_nXPos - m_nXCamAngle, m_nYPos, 0);

	SUTIL_PaintAsprite(m_Asins, S_INCLUDE_SORT);
//	SUTIL_PaintAsprite(m_NpcAsins, S_NOT_INCLUDE_SORT);


	if(9999 != nQuestionNum)
	{
		if(3 > nTimer)
		{
			SUTIL_Paint_Frame(m_Questionins->m_sprite, nTimer, m_nXPos - m_nXCamAngle, m_nYPos-nNpcHeight, 0);
		}
		else
		{
			SUTIL_Paint_Frame(m_Questionins->m_sprite, 5-nTimer, m_nXPos - m_nXCamAngle, m_nYPos-nNpcHeight, 0);
		}
	}
}



//--------------------------------------------------------------------------------------
void Npc::SetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_nNextAction)
	{
		case ACT_NPC_STAND:
		//--------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(m_Asins, m_nUsingImgIdx[m_nNextAction]);
			SUTIL_SetLoopAsprite(m_Asins, true);
			break;
		}
		case ACT_NPC_RUN:
		//--------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(m_Asins, m_nUsingImgIdx[m_nNextAction]);
			SUTIL_SetLoopAsprite(m_Asins, true);
			break;
		}
	}
}

//--------------------------------------------------------------------------------------
void Npc::ReadyObject(void* _s_ASpriteSet) 
//--------------------------------------------------------------------------------------
{
	s_ASpriteSet = (ASpriteSet*)_s_ASpriteSet;

	//	이미지 테이블을 매칭 시켜준다.
	int idx = 0;
/*
	switch(m_nImgIdx)
	{
		case 0:		{idx = SPRITE_NPC_NPC9;		break;}				
		case 1:		{idx = SPRITE_NPC_NPC10;	break;}				
		case 2:		{idx = SPRITE_NPC_NPC1;		break;}				
		case 3:		{idx = SPRITE_NPC_NPC2;		break;}				
		case 4:		{idx = SPRITE_NPC_NPC4;		break;}				
		case 5:		{idx = SPRITE_NPC_NPC5;		break;}				
		case 6:		{idx = SPRITE_NPC_NPC6;		break;}				
		case 7:		{idx = SPRITE_NPC_NPC19;	break;}				
		case 8:		{idx = SPRITE_NPC_NPC3;		break;}				
		case 9:		{idx = SPRITE_NPC_NPC18;	break;}				
		case 10:	{idx = SPRITE_NPC_NPC13;	break;}				
		case 11:	{idx = SPRITE_NPC_NPC7;		break;}				
		case 12:	{idx = SPRITE_NPC_NPC8;		break;}				
		default:	{							break;}
	}
*/


	//	20의 배수로 정했음
	idx = m_nImgIdx/20;

	ASprite* pTmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_NPC, idx);
	m_Asins = GL_NEW ASpriteInstance(pTmpAsprite, m_nXPos, m_nYPos, NULL);	// 0번째 배열, 실사용시는 define 필요

	pTmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_CINEMA, SPRITE_CINEMA_EMOTION_QUEST);
	m_Questionins = GL_NEW ASpriteInstance(pTmpAsprite, 0, 0, NULL);

	//	makeStet
	int RectData[4];
	SUTIL_GetASpriteAniRect(RectData, m_Asins->m_sprite, 0, 0);		// 몬스터의 정보
	nNpcHeight = RectData[3]-RectData[1];

	//	방향은 랜덤으로 설정한다.
	if(SUTIL_GetRandom()%2)	{SUTIL_SetDirAsprite(m_Asins, SDIR_LEFT);}
	else					{SUTIL_SetDirAsprite(m_Asins, SDIR_RIGHT);}

	//	imsi
	m_nUsingImgIdx[ACT_NPC_STAND] = 0;
	m_nUsingImgIdx[ACT_NPC_RUN] = 0;


	//	서 있는 곳의 에니메이션은 0번이다.
	int colorset = 0;
	int typeset = m_nImgIdx%20;
	int offset = 0;
	switch(idx)
	{
		case 10:	//	sub npc
		case 11:
		case 14:
		case 15:
		case 16:
		//------------------------------------------------------------
		{
			m_nUsingImgIdx[ACT_NPC_STAND] = 0;
			m_Asins->m_pal = 0;
			break;
		}
		case 0:
		case 1:
		//------------------------------------------------------------
		{
			offset = 2;
			m_nUsingImgIdx[ACT_NPC_STAND] = (typeset%offset);
			m_nUsingImgIdx[ACT_NPC_RUN] = (typeset%offset) + offset;
			m_Asins->m_pal = typeset/offset;
			break;
		}
		case 13:
		//------------------------------------------------------------
		{
			offset = 4;
			m_nUsingImgIdx[ACT_NPC_STAND] = (typeset%offset);
			m_nUsingImgIdx[ACT_NPC_RUN] = (typeset%offset) + offset;
			m_Asins->m_pal = typeset/offset;
			break;
		}
		case 5:
		//------------------------------------------------------------
		{
			offset = 4;
			switch(typeset%2)
			{
				case 0:	{m_nUsingImgIdx[ACT_NPC_RUN] = offset;		break;}
				case 1:	{m_nUsingImgIdx[ACT_NPC_RUN] = offset+1;	break;}
			}
			m_nUsingImgIdx[ACT_NPC_STAND] = typeset%offset;
			m_Asins->m_pal = typeset%offset;
			break;
		}
		default:
		{
			switch(idx)
			{
				case 2:		{offset = 6;	break;}
				case 3:		{offset = 4;	break;}
				case 4:		{offset = 4;	break;}
				case 6:		{offset = 2;	break;}
				case 7:		{offset = 2;	break;}
				case 8:		{offset = 4;	break;}
				case 9:		{offset = 4;	break;}
				case 12:	{offset = 4;	break;}
				case 17:	{offset = 5;	break;}
				case 18:	{offset = 8;	break;}
				case 19:	{offset = 2;	break;}
			}

			m_nUsingImgIdx[ACT_NPC_STAND] = typeset%offset;
			m_Asins->m_pal = typeset%offset;
			break;
		}
		case 2:
		//------------------------------------------------------------
		{
			
			break;
		}
	}

	m_nAction = m_nNextAction = ACT_NPC_STAND;
	SetAction();
}


//==============================================================================================================



//--------------------------------------------------------------------------------------
CrushObj::CrushObj(int idx, int x, int y)
//--------------------------------------------------------------------------------------
{
	m_nImgIdx = idx;
	m_nXPos = x;
	m_nYPos = y;

	m_nAction = ACT_NPC_NULL;

	//	서 있는 곳의 에니메이션은 0번이다.
	m_nUsingImgIdx[ACT_NPC_STAND] = 0;

	m_nHp = 10;

//	m_NpcAsins = ReadyAspriteInsNPC(idx, x, y);
}



//--------------------------------------------------------------------------------------
CrushObj::~CrushObj()
//--------------------------------------------------------------------------------------
{
//	SAFE_DELETE(m_Attack);
}


//--------------------------------------------------------------------------------------
void CrushObj::Initialize(int nDummy1, int nDummy2)
//--------------------------------------------------------------------------------------
{

}


//--------------------------------------------------------------------------------------
void CrushObj::Release()
//--------------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------------
int  CrushObj::CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5)
//--------------------------------------------------------------------------------------
{
	//nDummy1 : direction
	//nDummy2 : x1
	//nDummy3 : y1
	//nDummy4 : x2
	//nDummy5 : y2
	if(nDummy2 > m_nXPos)	{return 0;}
	if(nDummy3 > m_nYPos)	{return 0;}
	if(nDummy4 < m_nXPos)	{return 0;}
	if(nDummy5 < m_nYPos)	{return 0;}
	
	return 2;
		
}


//--------------------------------------------------------------------------------------
void CrushObj::Process()
//--------------------------------------------------------------------------------------
{
	if(m_nNextAction != m_nAction)
	{
		SetAction();
		m_nAction = m_nNextAction;
		m_nNextAction = ACT_NPC_NULL;
	}

//	SUTIL_SetXPosAsprite(m_NpcAsins, m_nXPos - m_nXCamAngle);
//	SUTIL_SetYPosAsprite(m_NpcAsins, m_nYPos);
//	SUTIL_SetZPosAsprite(m_NpcAsins, 0);

	m_Asins->CameraX = - m_nXCamAngle;

	//	에니메이션 업데이트
	SUTIL_UpdateTimeAsprite(m_Asins);
}


//--------------------------------------------------------------------------------------
void CrushObj::Paint()
//--------------------------------------------------------------------------------------
{
	SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,0 , m_nXPos - m_nXCamAngle, m_nYPos, 0);

	SUTIL_PaintAsprite(m_Asins, S_INCLUDE_SORT);
//	SUTIL_PaintAsprite(m_NpcAsins, S_NOT_INCLUDE_SORT);
}



//--------------------------------------------------------------------------------------
void CrushObj::SetAction()
//--------------------------------------------------------------------------------------
{
	switch(m_nNextAction)
	{
		case ACT_CRUSH_OBJ_STAND:
		//--------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(m_Asins, m_nUsingImgIdx[m_nNextAction]);
			SUTIL_SetLoopAsprite(m_Asins, true);
			break;
		}
		case ACT_CRUSH_OBJ_DESTROY:
		//--------------------------------------------------------------------
		{
			SUTIL_SetTypeAniAsprite(m_Asins, m_nUsingImgIdx[m_nNextAction]);
			SUTIL_SetLoopAsprite(m_Asins, true);
			break;
		}
	}
}

//--------------------------------------------------------------------------------------
void CrushObj::ReadyObject(void* _s_ASpriteSet) 
//--------------------------------------------------------------------------------------
{
	s_ASpriteSet = (ASpriteSet*)_s_ASpriteSet;
	ASprite* pTmpAsprite = NULL;

//	switch(m_nType)
//	{
//		case EVT_BARREL:
//		{
//			//pTmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_OBJECT, SPRITE_OBJECT_BARREL);
//			break;
//		}
//	}

	m_Asins = GL_NEW ASpriteInstance(pTmpAsprite, m_nXPos, m_nYPos, NULL);	// 0번째 배열, 실사용시는 define 필요
	m_nAction = m_nNextAction = ACT_CRUSH_OBJ_STAND;
	SetAction();
}


//==============================================================================================================

