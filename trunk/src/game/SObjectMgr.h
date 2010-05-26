#ifndef _S_OBJECT_MANAGER_
#define _S_OBJECT_MANAGER_

//	AI와 상호참조를 한다.
//#include "ASpriteInstance.h"
//#include "MonsterAI.h"
//#include "SUtil.h"
//#include "Position3D.h"
//#include "Physics.h"
//#include "SPRITE_DESC.h"
//#include "List.h"
//#include "Data.h"

#include "SSingleton.h"
#include "SObject.h"
#include "List.h"
#include "Data.h"

//#include "SCharacter.h"
//#include "SNpc.h"




/*
/// 오브젝트 정보 구조체  ////////////////////////////////////////////////////////
typedef struct tagNpcInfo
{
	uint8		nType;					/// 스프라이트 정보
	uint8		nAspritNum;				/// 스프라이트 정보
	uint8		nColor;					/// 컬러값
	uint8		nDummy;					///	더미
} stNpcInfo;

typedef struct tagMonsterInfo
{
	uint8		nType;					/// 스프라이트 정보
	uint8		nAspritNum;				/// 스프라이트 정보
	uint8		nColor;					/// 컬러값
	uint8		nDummy;					///	더미
} stMonsterInfo;

typedef struct tagBossInfo
{
	uint8		nType;					/// 스프라이트 정보
	uint8		nAspritNum;				/// 스프라이트 정보
	uint8		nColor;					/// 컬러값
	uint8		nDummy;					///	더미
} stMonsterInfo;
*/




//	MONSTER DATA	///////////////////////////////////////////////////////////////////////////////


class SObjectMgr : public SSingleton<SObjectMgr>
{
private:
	int m_nUniqueIdx;		//	오브젝트의 고유 아이디
	List2< class SObject* >					*m_ObjectList;	

	List2< class STalkInterface* >			*m_TalkObjectList;

	inline int MakeUniqueKey(void)		{return (m_nUniqueIdx++);}

public:
	SObjectMgr(void);
	virtual ~SObjectMgr(void);

	void InitMgr(void);
	bool Add(ObjectType ObjType, int ObjSubType, int color, int xPos, int yPos); 
	bool Remove(class SObject* pObject);
	void RemoveAll(void);


	inline int GetCount(ObjectType nType)	{return GetNodeCount(m_ObjectList);}
	inline void InitUniqueCnt()				{m_nUniqueIdx = 0;}

	// 액션에 관한것을 정의해준다.
	void Process(void);
	void Paint(void);

	STalkInterface* SObjectMgr::GetTalkEvent(int dir, int x1, int y1, int x2, int y2);

//	SObject* GetAttachObject(ObjectType eObjType = OBJ_M_NPC);

	

};



#endif