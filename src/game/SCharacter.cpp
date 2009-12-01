#include "SUtil.h"
#include "SCharacter.h"

#include "SScreenMgr.h"
#include "SEffectMgr.h"


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
	GetAsIns()->setCamera(SScreenMgr::GetInstPtr()->GetWorldXPos(), 0);
	SUTIL_UpdateTimeAsprite(GetAsIns());
}

//--------------------------------------------------------------------------------------
void SCharacter::Paint()
//--------------------------------------------------------------------------------------
{
	SEffectMgr* pSEffectMgr = SEffectMgr::GetInstPtr();

	//	그림자를 그려준다.
	int tmpXZ[2];
	GetAsIns()->Get_AFrameXZ(&tmpXZ[0]);
	int tmpx = tmpXZ[0];
	int tmpz = tmpXZ[1];

	SUTIL_Paint_Frame(pSEffectMgr->GetShadowAs() ,FRAME_SHADOW_SHADOW_1 ,
						  tmpx  + GetAsIns()->CameraX,  GetAsIns()->m_posY+1,0);

	//	스프라이트를 그려준다.
	SUTIL_PaintAsprite(GetAsIns(), S_INCLUDE_SORT);
}