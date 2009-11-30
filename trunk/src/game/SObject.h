#ifndef __SOBJECT_
#define __SOBJECT_

#include "Position3D.h"
#include "Physics.h"
#include "SUtil.h"


//	메인 타입 ///////////////////////////////////////////////////////
enum ObjectType {
	OBJ_M_ERR = -1,
	OBJ_M_NPC,
};

//	오브젝트 컬러 타입
enum ObjectColorType {
	OBJ_COLOR1 = 0,
	OBJ_COLOR2 = 1,
	OBJ_COLOR3 = 2
};

//	몬스터 타입 /////////////////////////////////////////////////////
enum ObjectMonsterType {
	OBJ_S_MON_ERR = -1,
};

//	엔피씨 타입
enum ObjectNpcType {
	OBJ_S_NPC_ERR = -1,
};

//	맵 오브젝트 타입
enum ObjectMapType {
	OBJ_S_MAP_ERR = -1,
};



//	NPC DATA	/////////////////////////////////////////////////////////////////////////////////////////
enum EnumNpcType
{
	NPC_TYPE_NONE = -1,
	NPC_TYPE_TALK,
	NPC_TYPE_MAX
};

enum EnumNpcTypeDefine
{
	NPC_TYPEDEF_TYPE = 0,
	NPC_TYPEDEF_SPRITEIDX,
	NPC_TYPEDEF_COLOR,
	NPC_TYPEDEF_EVTCODE,
	NPC_TYPEDEF_MAX,
};

static const uint8 NpcData[][NPC_TYPEDEF_MAX] = 
{
	//	타입, 스프라이트,바리에이션,이벤트 번호
	{NPC_TYPE_TALK, SPRITE_NPC_NPC1, 0, 0},
	{NPC_TYPE_TALK, SPRITE_NPC_NPC1, 0, 0},
};

class SObject
{
private:
	int					m_nID;		//	오브젝트의 고유 아이디
	ObjectType			m_nType;			//	타입
	int					m_nFeature;

//	Physics				m_Physics;
	ASpriteInstance*	m_pAsIns;

public:
	SObject()								{}
	SObject(ObjectType nType, int nID)		{SetObjType(nType);	 SetObjID(nID);} 
	virtual ~SObject()						{}

	inline void			SetObjType(ObjectType ObjType)	{m_nType = ObjType;}
	inline void			SetObjID(int nID)				{m_nID = nID;}

	inline ObjectType	GetObjType(void)				{return m_nType;}
	inline int			GetObjID(void)					{return m_nID;}
	
	inline void			SetAsIns(ASpriteInstance*	pAsIns)	{m_pAsIns = pAsIns;}
	inline ASpriteInstance*	GetAsIns()		{return (m_pAsIns);}

	virtual bool		Make()				{return true;}
	virtual	void		Release(void)		{}

	virtual void		Process()=0;
	virtual void		Paint()=0;


};


#endif//	__SOBJECT_


