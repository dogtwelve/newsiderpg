#include "SUtil.h"
#include "SNpc.h"



//--------------------------------------------------------------------------------------
SNpc::SNpc(ObjectType ObjType, uint8 nActionType, int nUniKey, ASpriteInstance* pAsins, uint8 Evtcode)
	: SCharacter(ObjType, nUniKey, pAsins)
//--------------------------------------------------------------------------------------
{
//	SetObjType(ObjType);
//	SetObjID(nUniKey);

	m_nActionType = nActionType;

	SetEventCode(Evtcode);

	SUTIL_SetTypeAniAsprite(pAsins, ANIM_NPC_01_1_STAND);
	SUTIL_SetLoopAsprite(pAsins, true);		
}


//--------------------------------------------------------------------------------------
SNpc::~SNpc()
//--------------------------------------------------------------------------------------
{

}


/*
//--------------------------------------------------------------------------------------
void SNpc::Process()
//--------------------------------------------------------------------------------------
{
	
}

//--------------------------------------------------------------------------------------
void SNpc::Paint()
//--------------------------------------------------------------------------------------
{

}

*/	