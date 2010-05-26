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
			class SNpc* pObject = new SNpc( ObjType,
										 NpcData[ObjSubType][NPC_TYPEDEF_TYPE],
										 MakeUniqueKey(),
										 TmpSprIns,
										 NpcData[ObjSubType][NPC_TYPEDEF_EVTCODE]);

			m_ObjectList->Insert_next((class SObject*)pObject);
			m_TalkObjectList->Insert_next((STalkInterface*)pObject);
			break;
		}
	}

	return true;
}


//--------------------------------------------------------------------------------------
bool SObjectMgr::Remove(class SObject* pObject)
//--------------------------------------------------------------------------------------
{
	for(InitList(m_ObjectList); NotEndList(m_ObjectList); MoveNext(m_ObjectList) )
	{
		if(pObject->GetObjID() == GetData(m_ObjectList)->GetObjID())
		{
			if(OBJ_M_NPC == pObject->GetObjType())
			{
				//	토크 이벤트를 지워준다.
				for(InitList(m_TalkObjectList); NotEndList(m_TalkObjectList); MoveNext(m_TalkObjectList) )
				{
					if(pObject == (class SObject*)(GetData(m_TalkObjectList)) )
					{
						m_TalkObjectList->Delete();
						break;
					}
				}
			}

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
//--------------------------------------------------------------------------------------
STalkInterface* SObjectMgr::GetTalkEvent(int dir, int x1, int y1, int x2, int y2)
//--------------------------------------------------------------------------------------
{
	for(InitList(m_TalkObjectList); NotEndList(m_TalkObjectList); MoveNext(m_TalkObjectList) )
	{
		if(GetData(m_TalkObjectList)->PossibleToTalk(dir, x1,y1,x2,y2))
		{
			return GetData(m_TalkObjectList);
		}
	}

	return NULL;
}
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