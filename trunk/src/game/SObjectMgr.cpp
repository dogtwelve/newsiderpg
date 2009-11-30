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
}

/*
//--------------------------------------------------------------------------------------
ASpriteInstance* SObjectMgr::MakeResource(int Idx, int IsMakeInstance)
//--------------------------------------------------------------------------------------
{
	//		pMonData[loop].nMonIdx = FIELD_MONSTER_INFO[nRealFieldNum][GEN_MON1_IDX+loop*4];

	//	일반 몬스터 //////////////////////////////////////////////////

	int loop2 = 0;
	int addcnt = 0;

	switch(monidx)
	{
		case MON_IDX_GHOST:			{loop2 = SPRITE_MON_GHOST;	addcnt = FRAME_MON01_BLEND;		break;}
		case MON_IDX_SUNFLOWER:		{loop2 = SPRITE_MON_SUNFLOWER;	addcnt = FRAME_MON02_BLEND;		break;}
		case MON_IDX_SLIME:			{loop2 = SPRITE_MON_SLIME;	addcnt = FRAME_MON03_BLEND;		break;}
		case MON_IDX_CROWN_BOMB:	{loop2 = SPRITE_MON_CROWNBOMB;	addcnt = FRAME_MON04_BLEND;	break;}
		case MON_IDX_BEAR:			{loop2 = SPRITE_MON_BEAR;	addcnt = FRAME_MON05_BLEND;		break;}
		case MON_IDX_TREE:			{loop2 = SPRITE_MON_TREE;	addcnt = FRAME_MON06_BLEND;		break;}
		case Mon_IDX_SHREK:			{loop2 = SPRITE_MON_SHREK;	addcnt = FRAME_MON07_BLEND;		break;}
		case MON_IDX_GOLLUM:		{loop2 = SPRITE_MON_GOLLUM;	addcnt = FRAME_MON08_BLEND;		break;}
		case MON_IDX_SHRIMP:		{loop2 = SPRITE_MON_SHRIMP;	addcnt = FRAME_MON09_BLEND;		break;}
		case MON_IDX_BEE:			{loop2 = SPRITE_MON_BEE;	addcnt = FRAME_MON10_BLEND;		break;}
		case MON_IDX_ELF_FIRE:		{loop2 = SPRITE_MON_ELF;	addcnt = FRAME_MON11_BLEND;		break;}
		case MON_IDX_ELF_ICE:		{loop2 = SPRITE_MON_ELF;	addcnt = FRAME_MON11_BLEND;		break;}
//		case MON_IDX_ELF_SILENCE:	{loop2 = SPRITE_MON_ELF;	addcnt = FRAME_MON11_BLEND;		break;}
		case MON_IDX_FIRE:			{loop2 = SPRITE_MON_FIRE;	addcnt = FRAME_MON12_BLEND;		break;}
		case MON_IDX_EYE:			{loop2 = SPRITE_MON_EYE;	addcnt = FRAME_MON13_BLEND;		break;}
//		case MON_IDX_BOSS5_DEVIL:
		case MON_IDX_SPEAR:			{loop2 = SPRITE_MON_SPEAR;	addcnt = FRAME_MON14_BLEND;		break;}
		case MON_IDX_HUMAN_MELEE:	{loop2 = SPRITE_MON_HUMAN;	addcnt = FRAME_MON15_BLEND;		break;}
		case MON_IDX_HUMAN_RANGE:	{loop2 = SPRITE_MON_HUMAN;	addcnt = FRAME_MON15_BLEND;		break;}
		case MON_IDX_LIZARD:		{loop2 = SPRITE_MON_LIZARD;	addcnt = FRAME_MON16_BLEND;	break;}
		case MON_IDX_TURTLE:		{loop2 = SPRITE_MON_TURTLE;	addcnt = FRAME_MON17_BLEND;		break;}
		case MON_IDX_BUG:			{loop2 = SPRITE_MON_BUG;	addcnt = FRAME_MON18_BLEND;		break;}
		case MON_IDX_DRILL:			{loop2 = SPRITE_MON_DIRLL;	addcnt = FRAME_MON19_BLEND;		break;}
		case MON_IDX_THUNDERCLOUD:	{loop2 = SPRITE_MON_THUNDER;	addcnt = FRAME_MON20_BLEND;		break;}
									

		case MON_IDX_HOROS:			{loop2 = SPRITE_MON_BOSS_2;	addcnt = FRAME_BOSS_2_BLEND;	break;}

		case MON_IDX_DEVIJOHNS:		{loop2 = SPRITE_MON_BOSS_7;	addcnt = FRAME_BOSS_7_BLEND;	break;}

//		case MON_IDX_BIG_DRAGON1:
//		case MON_IDX_BIG_DRAGON2:
//		case MON_IDX_BIG_DRAGON3:	{loop2 = SPRITE_MON_BOSS_1;	addcnt = FRAME_BOSS_1_BLEND;	break;}

		case MON_IDX_WORM:			{loop2 = SPRITE_MON_BOSS_1;	addcnt = FRAME_BOSS_1_BLEND;	break;}
		case MON_IDX_SKELBIRD:		{loop2 = SPRITE_MON_BOSS_2;	addcnt = FRAME_BOSS_2_BLEND;	break;}
		case MON_IDX_FLOWER:		{loop2 = SPRITE_MON_BOSS_3;	addcnt = FRAME_BOSS_3_BLEND;	break;}
									
		case MON_IDX_DARK_KNIGHT:		{loop2 = SPRITE_MON_BOSS_4;	addcnt = FRAME_BOSS_4_BLEND;	break;}
		case MON_IDX_DARK_KNIGHT_MIRROR:{loop2 = SPRITE_MON_BOSS_4;	addcnt = FRAME_BOSS_4_BLEND;	break;}
	
		case MON_IDX_BIGTURTLE:		{loop2 = SPRITE_MON_BOSS_5;	addcnt = FRAME_BOSS_5_BLEND;	break;}
		case MON_IDX_LASTBOSS:		{loop2 = SPRITE_MON_BOSS_6;	addcnt = FRAME_BOSS_6_BLEND;	break;}


//		case MON_IDX_BARREL:		{loop2 = SPRITE_MON_BARREL;	addcnt = 0;						break;}
//		case MON_IDX_STONE_BIG:		{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;					break;}
//		case MON_IDX_BOX:			{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;					break;}
//		case MON_IDX_KNIGHT:		{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;					break;}
//		case MON_IDX_TEMPLE_CROCK_SMALL:	{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;			break;}
//		case MON_IDX_TEMPLE_CROCK_BIG:		{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;			break;}
//		case MON_IDX_TEMPLE_STONEBOX_SMALL:	{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;			break;}
//		case MON_IDX_TEMPLE_STONEBOX_BIG:	{loop2 = SPRITE_MON_STONE_BIG;	addcnt = 0;			break;}
		default:					{															break;}
	}

	SUTIL_FreeSprite(m_MonAs[loop2]);
	m_MonAs[loop2] = SUTIL_LoadAspriteFromPack(PACK_SPRITE_MON, loop2);

	m_MonAs[loop2]->SetBlendFrame(addcnt);	

	return true;
}
*/

//--------------------------------------------------------------------------------------
bool SObjectMgr::Add(ObjectType ObjType, int ObjSubType, int color, int xPos, int yPos)
//--------------------------------------------------------------------------------------
{
	MoveHead(m_ObjectList);	

	switch(ObjType)
	{
		case OBJ_M_NPC:
		//---------------------------------------------------------------------------------------
		{
			ASprite* TmpAsprite = SUTIL_LoadSprite(PACK_SPRITE_NPC, NpcData[ObjSubType][NPC_TYPEDEF_SPRITEIDX]);
			ASpriteInstance* TmpSprIns =  new ASpriteInstance(TmpAsprite, xPos, yPos, NULL);//디버프 인스턴스

			//	TODO : 컬러값 셋팅해야됨

			m_ObjectList->Insert_next(new SNpc( ObjType, NpcData[ObjSubType][NPC_TYPEDEF_TYPE], MakeUniqueKey(), TmpSprIns,
												NpcData[ObjSubType][NPC_TYPEDEF_EVTCODE]) );
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