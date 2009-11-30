#include "SUtil.h"
#include "SCharacter.h"



////--------------------------------------------------------------------------------------
//SCharacter::SCharacter()
////--------------------------------------------------------------------------------------
//{
//	m_Physics = new Physics();
//}

//--------------------------------------------------------------------------------------
SCharacter::SCharacter(ObjectType ObjType, int nID, ASpriteInstance*	Asins, int Weight)
			: SObject(ObjType, nID)
//--------------------------------------------------------------------------------------
{
	SetAsIns(Asins);
	m_Physics = new Physics(Weight);

}



//--------------------------------------------------------------------------------------
SCharacter::~SCharacter()
//--------------------------------------------------------------------------------------
{
	SAFE_DELETE(m_Physics);

	ASpriteInstance* tmpAsIns = GetAsIns();

	SUTIL_FreeSprite(tmpAsIns->m_sprite);
	SUTIL_FreeSpriteInstance(tmpAsIns);
}


//--------------------------------------------------------------------------------------
void SCharacter::Process()
//--------------------------------------------------------------------------------------
{
	SUTIL_UpdateTimeAsprite(GetAsIns());
	//GetAsIns()->CameraX = 
}

//--------------------------------------------------------------------------------------
void SCharacter::Paint()
//--------------------------------------------------------------------------------------
{
	SUTIL_PaintAsprite(GetAsIns(), S_INCLUDE_SORT);
}