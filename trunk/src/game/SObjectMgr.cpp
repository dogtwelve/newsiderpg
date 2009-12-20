#include "SUtil.h"
#include "SObjectMgr.h"

#include "SCharacter.h"
#include "SNpc.h"



//--------------------------------------------------------------------------------------
SObjectMgr::SObjectMgr()
//--------------------------------------------------------------------------------------
{
	//	리스트 생성
	m_ObjectList = GL_NEW List2<class SObject*>();

	m_TalkObjectList = GL_NEW List2<class STalkInterface*>();

	InitMgr();
}


//--------------------------------------------------------------------------------------
SObjectMgr::~SObjectMgr()
//--------------------------------------------------------------------------------------
{
	RemoveAll();
	SAFE_DELETE(m_ObjectList);
}


//--------------------------------------------------------------------------------------
void SObjectMgr::InitMgr(void)
//--------------------------------------------------------------------------------------
{
	InitUniqueCnt();
	RemoveAll();
}


//--------------------------------------------------------------------------------------
void SObjectMgr::RemoveAll(void)
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList);  )
	{
		DeleteNowList(m_ObjectList);
	}

	for(InitList(m_TalkObjectList); NotEndList(m_TalkObjectList);  )
	{
		m_TalkObjectList->Delete();	
	}
}

//--------------------------------------------------------------------------------------
bool SObjectMgr::Add(ObjectType ObjType, int ObjSubType, int color, int xPos, int yPos)
//--------------------------------------------------------------------------------------
{
	MoveHead(m_ObjectList);
	MoveHead(m_TalkObjectList);

	switch(ObjType)
	{
		case OBJ_M_NPC:
		//---------------------------------------------------------------------------------------
		{
			ASprite* TmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_NPC, NpcData[ObjSubType][NPC_TYPEDEF_SPRITEIDX]);
			ASpriteInstance* TmpSprIns =  new ASpriteInstance(TmpAsprite, xPos, yPos, NULL);//디버프 인스턴스

			//	TODO : 컬러값 셋팅해야됨
			class SObject* pObject = new SNpc( ObjType,
										 NpcData[ObjSubType][NPC_TYPEDEF_TYPE],
										 MakeUniqueKey(),
										 TmpSprIns,
										 NpcData[ObjSubType][NPC_TYPEDEF_EVTCODE]);

			m_ObjectList->Insert_next(pObject);
			m_TalkObjectList->Insert_next((STalkInterface*)pObject);
			break;
		}
	}

	

	return true;
}


//--------------------------------------------------------------------------------------
bool SObjectMgr::Remove(int nUniqueIdx)
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		if(nUniqueIdx == GetData(m_ObjectList)->GetObjID())
		{
			DeleteNowList(m_ObjectList);
			break;
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
void SObjectMgr::Process()
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		GetData(m_ObjectList)->Process();
	}
}


//--------------------------------------------------------------------------------------
void SObjectMgr::Paint()
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		GetData(m_ObjectList)->Paint();
	}
}
/*
//--------------------------------------------------------------------------------------
int SObjectMgr::GetTalkEvent()
//--------------------------------------------------------------------------------------
{
	SNpc* pSNpc = NULL;

	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		if(OBJ_M_NPC == GetData(m_ObjectList)->GetObjType())
		{
			pSNpc = (SNpc*)GetData(m_ObjectList);

			if(NPC_TYPE_TALK == pSNpc->GetActionType())
			{
				return pSNpc->GetEventCode();
			}
		}
	}

	return 0;
}
*/
/*
//--------------------------------------------------------------------------------------
SObject* SObjectMgr::GetAttachObject(ObjectType eObjType)
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		// 타입체크	
		if(eObjType != GetData(m_ObjectList)->GetObjType() )	{continue;}

		// 거리체크
		SQR
		
	}

	return NULL;
}
*/