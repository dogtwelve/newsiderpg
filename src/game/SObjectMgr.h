#ifndef _S_OBJECT_MANAGER_
#define _S_OBJECT_MANAGER_

//	AI�� ��ȣ������ �Ѵ�.
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
/// ������Ʈ ���� ����ü  ////////////////////////////////////////////////////////
typedef struct tagNpcInfo
{
	uint8		nType;					/// ��������Ʈ ����
	uint8		nAspritNum;				/// ��������Ʈ ����
	uint8		nColor;					/// �÷���
	uint8		nDummy;					///	����
} stNpcInfo;

typedef struct tagMonsterInfo
{
	uint8		nType;					/// ��������Ʈ ����
	uint8		nAspritNum;				/// ��������Ʈ ����
	uint8		nColor;					/// �÷���
	uint8		nDummy;					///	����
} stMonsterInfo;

typedef struct tagBossInfo
{
	uint8		nType;					/// ��������Ʈ ����
	uint8		nAspritNum;				/// ��������Ʈ ����
	uint8		nColor;					/// �÷���
	uint8		nDummy;					///	����
} stMonsterInfo;
*/




//	MONSTER DATA	///////////////////////////////////////////////////////////////////////////////


class SObjectMgr : public SSingleton<SObjectMgr>
{
private:
	int m_nUniqueIdx;		//	������Ʈ�� ���� ���̵�
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

	// �׼ǿ� ���Ѱ��� �������ش�.
	void Process(void);
	void Paint(void);

	STalkInterface* SObjectMgr::GetTalkEvent(int dir, int x1, int y1, int x2, int y2);

//	SObject* GetAttachObject(ObjectType eObjType = OBJ_M_NPC);

	

};



#endif