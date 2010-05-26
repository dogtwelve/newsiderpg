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


//--------------------------------------------------------------------------------------
bool SNpc::PossibleToTalk(int dir, int x1, int y1, int x2, int y2)
//--------------------------------------------------------------------------------------
{
//	if(m_nEvtDelay)	{return 0;}
	//nDummy1 : direction
	//nDummy2 : x1
	//nDummy3 : y1
	//nDummy4 : x2
	//nDummy5 : y2
	if(x1 > GetAsIns()->m_posX )	{return false;}
	if(y1 > GetAsIns()->m_posY)		{return false;}
	if(x2 < GetAsIns()->m_posX)		{return false;}
	if(y2 < GetAsIns()->m_posY)		{return false;}

	//	╩С 1, го 2, аб 3, ©Л 4
	if(dir)
	{
		if(3 == dir)
		{
			SUTIL_SetDirAsprite(GetAsIns(), SDIR_RIGHT);
		}
		else if(4 == dir)
		{
			SUTIL_SetDirAsprite(GetAsIns(), SDIR_LEFT);
		}
	}

	//m_nEvtDelay = 0;
	return true;
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