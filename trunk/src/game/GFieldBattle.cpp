#include "GFieldBattle.h"
#include "SObjectMgr.h"
#include "SScreenMgr.h"
#include "SEffectMgr.h"

//--------------------------------------------------------------------------
GFieldBattle::GFieldBattle()
//--------------------------------------------------------------------------
{
	isHoldingProcess = true;
	isHoldingPaint = true;
	isHoldingKey = true;

	// ½Ì±ÛÅÏ °´Ã¼ »ý¼º
	SObjectMgr* pObjectMgr = new SObjectMgr();
	SScreenMgr* pScreenMgr = new SScreenMgr();
	SEffectMgr* pSEffectMgr = new SEffectMgr();


}


//--------------------------------------------------------------------------
GFieldBattle::~GFieldBattle()
//--------------------------------------------------------------------------
{
	//	ÀÌº¥Æ® ¸Þ¼¼Áö¸¦ Á×ÀÎ´Ù.
	Message_FreeInstance();
	EventManager_FreeInstance();
	Quest_FreeInstance();


	SObjectMgr::GetInstPtr()->RemoveAll();

	//	½Ì±ÛÅÏ °´Ã¼ ÇØÁ¦
	SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
	SAFE_DELETE( pObjectMgr );

	SScreenMgr* pScreenMgr = SScreenMgr::GetInstPtr();
	SAFE_DELETE( pScreenMgr );

	SEffectMgr* pSEffectMgr = SEffectMgr::GetInstPtr();
	SAFE_DELETE( pSEffectMgr );
}


//--------------------------------------------------------------------------
void GFieldBattle::Initialize(int nDummy1, int nDummy2)		//	nDummy1:ÇÊµå ¹øÈ£,  nDummy2:¾È¾´´Ù.
//--------------------------------------------------------------------------
{
	ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT,0,10);
	ADD_EVENT_MSG(EVT_INIT_GAME, 10, 0, nDummy1, nDummy2);

}

//--------------------------------------------------------------------------
void GFieldBattle::LoadFirstData(int timer, int nDummy1, int nDummy2)
//--------------------------------------------------------------------------
{
	switch(timer)
	{
	case 0:
		//--------------------------------------------------------------------------
		{
			//	ÀÌº¥Æ®¸¦ ÃÊ±âÈ­½ÃÄÑÁØ´Ù.
			INIT_MESSAGE();
			INIT_QUEST();
			INIT_EVENT();
			break;
		}
	case 1:
		//--------------------------------------------------------------------------
		{
			//	±×¸²ÀÚ È¿°ú
			s_ASpriteSet.pShadowAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_SHADOW);
			s_ASpriteSet.pShadowAs->SetBlendFrame(FRAME_SHADOW_BLEND);

			s_ASpriteSet.pDebuffAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_FIELDEFT_UI);
			s_ASpriteSet.pDebuffAs->SetBlendFrame(FRAME_WEFFECT_BLEND);

			s_ASpriteSet.pFieldUiAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_FIELD_UI);
			s_ASpriteSet.pFieldUiAs->SetBlendFrame(FRAME_UI_BLEND);

			s_ASpriteSet.pItemAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_ITEM_UI);


			//	TODO	ÀÓ½Ã·Î ¼ÂÆÃ
			SEffectMgr* pSEffectMgr = SEffectMgr::GetInstPtr();
			pSEffectMgr->m_ShadowAs = s_ASpriteSet.pShadowAs;
			pSEffectMgr->m_DebuffAs = s_ASpriteSet.pDebuffAs;
			//s_ASpriteSet.pFieldUiAs->SetBlendFrame(FRAME_UI_BLEND);
			break;
		}
	case 2:
		//--------------------------------------------------------------------------
		{
			//	ÁÖÀÎ°ø
			hero = GL_NEW Character(SEX_WOMAN ,SDIR_RIGHT, (void*) &s_ASpriteSet);//ÀÎ¸¶¼öÀÇ°è¾à½º Æ÷ÀÎÅÍÀü´Þ, ¹æÇâÁöÁ¤ ¹× ÃÊ±âÈ­

			if(0 != nDummy2)
			{
				hero->InitCharPos(nDummy2, 240);
				if(300 < nDummy2)		{hero->_b_LookRight = SDIR_LEFT;	SUTIL_SetDirAsprite(hero->_ins_Hero, SDIR_LEFT);}
				else					{hero->_b_LookRight = SDIR_RIGHT;	SUTIL_SetDirAsprite(hero->_ins_Hero, SDIR_RIGHT);}
			}
			break;
		}
	case 3:
		//--------------------------------------------------------------------------
		{
			//	ÇÊµå UI
			pFieldUi = GL_NEW FieldUi((void*) &s_ASpriteSet);

			//	ÆË¾÷ UI
			pPopupUi = GL_NEW PopupUi((void*) &s_ASpriteSet/*,hero->_spr_Hero_W*/);

			//	Ãæµ¹Ã¼Å© µ¥ÀÌÅ¸
			m_CharInfo = (S_CHARINFO*)MALLOC(sizeof(S_CHARINFO));
			break;
		}
	case 4:
		//--------------------------------------------------------------------------
		{
			//	¹Ì´Ï¸Ê
			pMinimap = GL_NEW cMinimap();
			pMinimap->ResvNextSector(1, 1);

			//	Ä³¸¯ÅÍ ÃÊ±â À§Ä¡¸¦ ¼³Á¤ÇÑ´Ù.
			pMinimap->m_nNextCharPosX = MAP_START_X;
			pMinimap->m_nNextCharPosY = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;

			//	¹è°æ
			pField = GL_NEW Field((void*) &s_ASpriteSet);
			break;
		}

		//>> Ä³¸¯ÅÍ Á¤º¸°¡ ¾ø¾î¼­ ¸ó½ºÅÍ Å¬·Ð½Ã ¿¡·¯°¡ ³ª°í ÀÖÀ½


	case 5:
		//--------------------------------------------------------------------------
		{
			//	¾¾³×¸¶
			pCinema = GL_NEW cCinematic((void*) &s_ASpriteSet);

			//	¸ó½ºÅÍ
			//	Monster* tmpMonster;
			pMonList = GL_NEW List2<Monster*>();
//			pObjectList = GL_NEW List2<Monster*>();
			pMonSkillList = GL_NEW List2<S_MONSKILL*>();
			pMonMsgList = GL_NEW List2<S_MESSAGE*>();
			break;
		}
	case 6:
		//--------------------------------------------------------------------------
		{
			//-------------------Sound Load
			SUTIL_Sound_Load(EFFECT_SWORD_A	);
			SUTIL_Sound_Load(EFFECT_SWORD_B	);
			SUTIL_Sound_Load(EFFECT_SWORD_C	);
			SUTIL_Sound_Load(EFFECT_SWORD_D	);
			SUTIL_Sound_Load(EFFECT_GUN_A	);
			SUTIL_Sound_Load(EFFECT_GUN_B	);
			SUTIL_Sound_Load(EFFECT_ORB_A	);
			SUTIL_Sound_Load(EFFECT_ORB_B	);
			SUTIL_Sound_Load(EFFECT_ORB_C	);
			SUTIL_Sound_Load(BGM_TEST_A		);
			break;
		}
		//		case 7:
		//		//--------------------------------------------------------------------------
		//		{
		//			//Resv_ChangeStage(nDummy1);
		//	ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT,0,10);
		//	ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, nDummy1);
		//			ADD_EVENT_MSG(EVT_CHANGE_STAGE, 0, nDummy1);
		//
		//			break;
		//		}
	}
}
/////////////////////////////////////////////////////////////////////////////////

////--------------------------------------------------------------------------
//void GFieldBattle::Resv_ChangeStage(int nNextStage)
////--------------------------------------------------------------------------
//{
//	m_nNextStage = nNextStage;
//	m_nStageLoadStep = 0;
//	b_ChangeStage = true;
//}

//--------------------------------------------------------------------------
void GFieldBattle::LoadStage(int m_nNextStage, int step)
//--------------------------------------------------------------------------
{
	switch(step)
	{
	case 0:
		//----------------------------------------------------------
		{
			//	¸ó½ºÅÍ Á¤º¸
			//			nGenCnt = 0;
			ReleaseStage();
			for(int i =0;i<BULLET_MAX;i++)hero->s_Bullet_Eff[i].act = false;//½ºÅ³Á¾·á
		}
	case 1:
		//----------------------------------------------------------
		{
			//	ÇÊµå Á¤º¸
			//pField->LoadMap(m_nNextStage);

			pField->LoadMap( (void*)pMinimap->SetResvSector() );

			//	Ä³¸¯ÅÍ¿¡°Ô ÇÊµå ¾ÆÀÌµð¸¦ ³Ñ°ÜÁØ´Ù.(¸¶À»/ÇÊµå ±¸ºÐÀ§ÇØ¼­)
			hero->m_nFieldId = m_nNextStage;

			//	ÀÌº¥Æ®¿¡¼­ ³Ñ°ÜÁÙ¼ö ÀÖ´Ù. (Ä³¸¯ÅÍ À§Ä¡ ¼ÂÆÃ)
			hero->InitCharPos(pMinimap->m_nNextCharPosX, pMinimap->m_nNextCharPosY);

/*
			if(0 != pField->m_nWayMoveCharx)
			{
				//int temp = s_Camera.cX - hero->_ins_Hero->m_posX - hero->_ins_Hero->m_stopAniX;

				if(100 > pField->m_nWayMoveCharx)	//	¹æÇâÀº ¿À¸¥ÂÊÀ» º¸°í ÀÖ´Â´Ù.
				{
					hero->InitCharPos(pField->m_nWayMoveCharx, pField->m_nWayMoveChary, SDIR_RIGHT);
				}
				else if(100 > (pField->m_nFieldSize_X - pField->m_nWayMoveCharx))	//	¿ÞÂÊ
				{
					hero->InitCharPos(pField->m_nWayMoveCharx, pField->m_nWayMoveChary, SDIR_LEFT);
				}
				else	// Ã³¸®ÇÏÁö ¾Ê´Â´Ù.
				{
					hero->InitCharPos(pField->m_nWayMoveCharx, pField->m_nWayMoveChary);
				}

				//hero->InitCharPos(pField->m_nWayMoveCharx, pField->m_nWayMoveChary);
*/

				hero->_move_Order = HERO_STOP;

				pField->m_nWayMoveCharx = 0;

				//s_Camera.cX = temp;
				//	Ä«¸Þ¶ó ¾Þ±Û ÃÊ±âÈ­ Á¶Á¤
				s_Camera.cX = 0;
				SetCameraMove();
				//pField->SetCamera(pField->m_nSrcCamAngle_X);
//			}
			break;
		}
	case 2:
		//----------------------------------------------------------
		{
			//	Ä³¸¯ÅÍÀÇ Á¤º¸¸¦ ¾÷µ¥ÀÌÆ® ½ÃÄÑÁØ´Ù.
			m_CharInfo->m_nPos.x = hero->_ins_Hero->m_posX;
			m_CharInfo->m_nPos.y = hero->_ins_Hero->m_posY;
			m_CharInfo->m_nPos.z = hero->_ins_Hero->m_posZ;
			m_CharInfo->m_Direction = hero->_b_LookRight;

			//test
			MakeMonsterSeed();
			AddFirstMonSetting();

			if(26 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_THUNDERCLOUD);
				LoadMonsterSprite(MON_IDX_LASTBOSS);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				AddMonster(1, MON_IDX_LASTBOSS, 0, 0, GRADE_SPECIAL, 300, 180, 300, 180, NOT_REGEN, 0);

				//AddMonster(1, MON_IDX_THUNDERCLOUD, 0, 0, GRADE_SPECIAL, 300, 180, 300, 180, NOT_REGEN, 0);
			}


			if(22 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_TURTLE);
				LoadMonsterSprite(MON_IDX_BIGTURTLE);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				AddMonster(1, MON_IDX_BIGTURTLE, 0, 0, GRADE_SPECIAL, 300, 180, 300, 180, NOT_REGEN, 0);
			}

			if(21 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_BUG);
				LoadMonsterSprite(MON_IDX_WORM);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				AddMonster(1, MON_IDX_WORM, 0, 0, GRADE_SPECIAL, 300, 180, 300, 180, NOT_REGEN, 0);
			}
			else if(23 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_SKELBIRD);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				BossSkelBird* pTmpBossSkelBird = NULL;
				pTmpBossSkelBird = (BossSkelBird*)AddMonster(1, MON_IDX_SKELBIRD, 0, 0, GRADE_SPECIAL, 160, 180, 160, 180, NOT_REGEN, 0);
				pTmpBossSkelBird->pChildBody[0] = AddMonster(1, MON_IDX_SKELBIRD_L_ARM, 0, 0, GRADE_SPECIAL, 160, 180, 160, 180, NOT_REGEN, 0);
				pTmpBossSkelBird->pChildBody[1] = AddMonster(1, MON_IDX_SKELBIRD_R_ARM, 0, 0, GRADE_SPECIAL, 160, 180, 160, 180, NOT_REGEN, 0);

				(pTmpBossSkelBird->pChildBody[0])->m_pParents = (Monster*)pTmpBossSkelBird;
				(pTmpBossSkelBird->pChildBody[1])->m_pParents = (Monster*)pTmpBossSkelBird;
			}
			else if(24 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_SLIME);
				LoadMonsterSprite(MON_IDX_DRILL);
				LoadMonsterSprite(MON_IDX_FLOWER);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				BossFlower* pTmpBossFolwer = NULL;
				pTmpBossFolwer = (BossFlower*)AddMonster(1, MON_IDX_FLOWER, 0, 0, GRADE_SPECIAL, 160, 162, 160, 162, NOT_REGEN, 0);
				pTmpBossFolwer->pChildBody[0] = AddMonster(1, MON_IDX_FLOWER_BRAIN, 0, 0, GRADE_SPECIAL, 160, 162, 160, 162, NOT_REGEN, 0);

				(pTmpBossFolwer->pChildBody[0])->m_pParents = (Monster*)pTmpBossFolwer;
			}
			else if(25 == pMinimap->m_CurMapSector->m_nSectorIdx)
			{
				SUTIL_LoadAspritePack(PACK_SPRITE_MON);
				LoadMonsterSprite(MON_IDX_DARK_KNIGHT);
				SUTIL_ReleaseAspritePack();

				//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
				AddMonster(1, MON_IDX_DARK_KNIGHT, 0, 0, GRADE_SPECIAL, 160, 162, 160, 162, NOT_REGEN, 0);
			}

			break;
/*
			switch(m_nNextStage)
			{
				//				case 1000:
				//				case 1001:
				//				//---------------------------------------------------------------
				//				{
				//					AppMain::ResvNextState(MS_GAME_WORLDMAP, m_nNextStage, 0);
				//					return;
				//				}

			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
			case 105:
			case 106:
			case 107:
			case 108:
			case 109:
			case 110:
			case 111:
			case 112:
			case 113:
			case 114:
			case 115:
			case 116:
			case 117:
			case 200:
			case 201:
			case 202:
			case 203:
			case 204:
			case 205:
			case 206:
			case 207:
			case 208:
			case 209:
			case 210:
			case 211:
			case 212:
			case 213:
			case 214:
			case 215:
			case 216:
			case 217:
				//---------------------------------------------------------------
				{
					//	¸ó½ºÅÍ Á¤º¸
					MakeMonsterSeed(m_nNextStage);
					//					for(int loop = 0; loop < nMonTypeCnt; loop++)
					//					{
					//						LoadMonsterSprite( nMonDataIdx[loop] );
					//					}
					AddFirstMonSetting();

					if(MAIN_QUEST_openDoor >= GET_MAINQUEST_IDX())
					{
						if(201 == m_nNextStage)
						{
							Monster* pTmpMonster = NULL;
							pTmpMonster = AddMonster(1, MON_IDX_STONE_BIG, 0, 0, GRADE_NORMAL, 590, 270, 590, 270, NOT_REGEN, 0);
//							pTmpMonster->pMonAsIns->m_pal = 3;												  
//							pTmpMonster = AddMonster(1, MON_IDX_STONE_BIG, 0, 0, GRADE_NORMAL, 590, 270, 590, 270, NOT_REGEN, 0);
//							pTmpMonster->pMonAsIns->m_pal = 3;												  
//							pTmpMonster = AddMonster(1, MON_IDX_STONE_BIG, 0, 0, GRADE_NORMAL, 640, 280, 640, 280, NOT_REGEN, 0);
//							pTmpMonster->pMonAsIns->m_pal = 3;												  
//							pTmpMonster = AddMonster(1, MON_IDX_STONE_BIG, 0, 0, GRADE_NORMAL, 570, 290, 570, 290, NOT_REGEN, 0);
//							pTmpMonster->pMonAsIns->m_pal = 3;
						}
					}

					if(MAIN_QUEST_openDoor == GET_MAINQUEST_IDX())
					{
						//	ÀÌº¥Æ®½Ã ÅëÀ» ¸¸µé¾îÁØ´Ù.
						if(201 == m_nNextStage || 202 == m_nNextStage || 203 == m_nNextStage)
						{
							int xrnd = 0;
							int yrnd = 0;
							int rnd = 3+SUTIL_GetRandom()%5;
							for(int loop = 0; loop < rnd; loop++)
							{
								xrnd = (SUTIL_GetRandom()%pField->m_nFieldSize_X);
								yrnd = 170+(SUTIL_GetRandom()%100);

								AddMonster(1, MON_IDX_BARREL, 0, 0, GRADE_NORMAL, xrnd, yrnd, xrnd, yrnd, NOT_REGEN, 0);
							}
						}
					}

					if(MAIN_QUEST_findDiary == GET_MAINQUEST_IDX())
					{
						//	ÀÌº¥Æ®½Ã ´ÙÀÌ¾î¸® ¾ÆÀÌÅÛÀ» ¸¸µé¾îÁØ´Ù.
						if(203 == m_nNextStage)
						{
							if(pPopupUi->GET_Count(ITEM_CALL_diary) == 0)
							{
								//	¾ÆÀÌÅÛÀ» ¸¸µç´Ù.

								ItemBag tmpBag;
								tmpBag.Data0 = ITEM_CALL_diary;
								tmpBag.Data1 = 1;
								tmpBag.Data2 = 0;

								pField->InsertDropItem(tmpBag, 800, 230);
							}
						}
					}
					break;
				}

				case 400:
				//---------------------------------------------------------------
				{
					MakeMonsterSeed(m_nNextStage);

					SUTIL_LoadAspritePack(PACK_SPRITE_MON);
					LoadMonsterSprite(MON_IDX_HOROS);
					LoadMonsterSprite(MON_IDX_BUG);
					SUTIL_ReleaseAspritePack();

					//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
					AddMonster(1, MON_IDX_HOROS, 0, 0, GRADE_SPECIAL, 300, 180, 300, 180, NOT_REGEN, 0);
					break;
				}

				


				case 400:
				//---------------------------------------------------------------
				{
					MakeMonsterSeed(m_nNextStage);

					SUTIL_LoadAspritePack(PACK_SPRITE_MON);
					
					LoadMonsterSprite(MON_IDX_DRILL);
					LoadMonsterSprite(MON_IDX_BOSS5_DEVIL);

					LoadMonsterSprite(MON_IDX_BIGDOG1);
					LoadMonsterSprite(MON_IDX_BIGDOG2);
					LoadMonsterSprite(MON_IDX_BIGDOG3);
					LoadMonsterSprite(MON_IDX_BIGDOG4);
					LoadMonsterSprite(MON_IDX_BIGDOG5);

					LoadMonsterSprite(MON_IDX_BIGDOG6);
					LoadMonsterSprite(MON_IDX_BIGDOG7);
					LoadMonsterSprite(MON_IDX_BIGDOG8);
					LoadMonsterSprite(MON_IDX_BIGDOG9);
					LoadMonsterSprite(MON_IDX_BIGDOG10);


					

					SUTIL_ReleaseAspritePack();

					BossMon5_1* pTmpMon = (BossMon5_1*)AddMonster(1, MON_IDX_BIGDOG1, 0, 0, GRADE_SPECIAL, 230, 215-20, 230, 215-20, NOT_REGEN, 0);
					pTmpMon->pChildBody[0] = AddMonster(1, MON_IDX_BIGDOG2, 0, 0, GRADE_SPECIAL, 230, 215-10, 230, 215-10, NOT_REGEN, 0);
					pTmpMon->pChildBody[1] = AddMonster(1, MON_IDX_BIGDOG3, 0, 0, GRADE_SPECIAL, 230, 215+10, 230, 215+10, NOT_REGEN, 0);
					pTmpMon->pChildBody[2] = AddMonster(1, MON_IDX_BIGDOG4, 0, 0, GRADE_SPECIAL, 230, 215+20, 230, 215+20, NOT_REGEN, 0);
					pTmpMon->pChildBody[3] = AddMonster(1, MON_IDX_BIGDOG5, 0, 0, GRADE_SPECIAL, 230,	 110, 230,	  110, NOT_REGEN, 0);
					pTmpMon->pChildBody[4] = AddMonster(1, MON_IDX_BIGDOG6, 0, 0, GRADE_SPECIAL,   0,	-200,   0,	 -200, NOT_REGEN, 0);
					pTmpMon->pChildBody[5] = AddMonster(1, MON_IDX_BIGDOG7, 0, 0, GRADE_SPECIAL,   0,	-200,   0,	 -200, NOT_REGEN, 0);
					pTmpMon->pChildBody[6] = AddMonster(1, MON_IDX_BIGDOG8, 0, 0, GRADE_SPECIAL,   0,	-200,   0,	 -200, NOT_REGEN, 0);
					pTmpMon->pChildBody[7] = AddMonster(1, MON_IDX_BIGDOG9, 0, 0, GRADE_SPECIAL,   0,	-200,   0,	 -200, NOT_REGEN, 0);
					pTmpMon->pChildBody[8] = AddMonster(1, MON_IDX_BIGDOG10, 0, 0, GRADE_SPECIAL,  0,	-200,   0,	 -200, NOT_REGEN, 0);
					break;
				}


//´ëºñÁ¸½º
				case 400:
				//---------------------------------------------------------------
				{
					MakeMonsterSeed(m_nNextStage);

					SUTIL_LoadAspritePack(PACK_SPRITE_MON);
					LoadMonsterSprite(MON_IDX_DEVIJOHNS);
					SUTIL_ReleaseAspritePack();

					//	¼ÒÈ¯µÇ´Â ÂÌ(Áß°£Áß°£¿¡ ¼ÒÈ¯)
					AddMonster(1, MON_IDX_DEVIJOHNS, 0, 0, GRADE_SPECIAL, 180, 220, 180, 220, NOT_REGEN, 0);
					break;
				}




// 				case 400:
// 				//---------------------------------------------------------------
// 				{
// 					MakeMonsterSeed(m_nNextStage);
// 
// 					SUTIL_LoadAspritePack(PACK_SPRITE_MON);
// 					LoadMonsterSprite(MON_IDX_BIG_DRAGON1);
// 					LoadMonsterSprite(MON_IDX_BIG_DRAGON2);
// 					LoadMonsterSprite(MON_IDX_BIG_DRAGON3);
// 
// 					SUTIL_ReleaseAspritePack();
// 
// 					BossBigDragon1* pTmpMon = (BossBigDragon1*)AddMonster(1, MON_IDX_BIG_DRAGON1, 0, 0, GRADE_SPECIAL, 320, 210, 320, 210, NOT_REGEN, 0);
// 					pTmpMon->SetDirection(SDIR_LEFT);
// 					pTmpMon->pChildBody[0] = AddMonster(1, MON_IDX_BIG_DRAGON2, 0, 0, GRADE_SPECIAL, 0, 210, 0, 210, NOT_REGEN, 0);
// 					pTmpMon->SetDirection(SDIR_LEFT);
// 					pTmpMon->pChildBody[1] = AddMonster(1, MON_IDX_BIG_DRAGON3, 0, 0, GRADE_SPECIAL, 235-120, 173, 235-120, 173, NOT_REGEN, 0);
// 					break;
// 				}

			}

*/
			break;
		}
	}

}


//--------------------------------------------------------------------------
void GFieldBattle::ReleaseStage()
//--------------------------------------------------------------------------
{
	//	CLEAR_EVENT_MSG();

	//	static º¯¼ö ÃÊ±âÈ­
	Monster::UniqueIdx = 0;

	//	ÀÌ¹ÌÁö ÃÊ±âÈ­
	for(int loop = 0; loop < SPRITE_MON_MAX; loop++)
	{
		if(NULL != m_MonAs[loop])
		{
			SUTIL_FreeSprite(m_MonAs[loop]);
		}
	}

	InitList(pMonList);
	while(NotEndList(pMonList))
	{
		SAFE_DELETE(GetData(pMonList));
		pMonList->Delete();
	}
	//	SAFE_DELETE(pMonList)

//	InitList(pObjectList);
//	while(NotEndList(pObjectList))
//	{
//		SAFE_DELETE(GetData(pObjectList));
//		pObjectList->Delete();
//	}

	InitList(pMonSkillList);
	while(NotEndList(pMonSkillList))
	{
		SUTIL_FreeSpriteInstance(GetData(pMonSkillList)->pMonSkillAsIns);
		SAFE_DELETE(GetData(pMonSkillList));
		pMonSkillList->Delete();
	}
	//	SAFE_DELETE(pMonSkillList)

	//	message
	InitList(pMonMsgList);
	while(NotEndList(pMonMsgList))
	{
		SAFE_DELETE(GetData(pMonMsgList));
		pMonMsgList->Delete();
	}
	//	SAFE_DELETE(pMonMsgList)

	//	ÇÊµå UI
	//	SAFE_DELETE(pFieldUi);

	//	±âÅ¸
	SAFE_DELETE(pMonData);
	SAFE_DELETE(m_nSeedData);
	SAFE_DELETE(m_nSeedDataGrade);
}

///////////////////////////////////////////////////////////////////////////////






//--------------------------------------------------------------------------
void GFieldBattle::MakeMonsterSeed()
//--------------------------------------------------------------------------
{
	int loop = 0;
	int nRealFieldNum = 0;

//	while(NU != FIELD_MONSTER_INFO[nRealFieldNum][0])
//	{
//		if(nStageNum == FIELD_MONSTER_INFO[nRealFieldNum][GEN_FIELD_NUM])	{break;}
//		nRealFieldNum++;
//	}
//
//	if(NU == FIELD_MONSTER_INFO[nRealFieldNum][0])	{return;}

	m_nMonLevel = pMinimap->m_CurMapSector->m_MonsterInfo[MI_LEVEL];
	
	// TODO ¸ó½ºÅÍ ·¹º§À» ÁÖÀÎ°ø ·¹º§¿¡ ¸ÂÃß´Â ÀÓ½ÃÄÚµå¸¦ ³Ö´Â´Ù.
	m_nMonLevel = hero->s_Status[hero->s_HeroTag.SEX].LEVEL;

	m_nMonLevelRnd = pMinimap->m_CurMapSector->m_MonsterInfo[MI_ADD_RND_LEVEL]+1;

	pField->m_nRegenDistance = pMinimap->m_CurMapSector->m_MonsterInfo[MI_DISTANCE];

	if(0 == pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_COUNT])	{return;}

	//	¸ó½ºÅÍ µî±Þ ¼³Á¤
	nMonGradeCnt[GRADE_RARE]	= pMinimap->m_CurMapSector->m_MonsterInfo[MI_RARE_GRADE];
	nMonGradeCnt[GRADE_UNIQUE]	= pMinimap->m_CurMapSector->m_MonsterInfo[MI_UNIQUE_GRADE];
	nMonGradeCnt[GRADE_SPECIAL]	= pMinimap->m_CurMapSector->m_MonsterInfo[MI_SPECIAL_GRADE];

	//	¸ó½ºÅÍ ¼³Á¤
	nMonTypeCnt = 0;
	for(loop = 0; loop < MI_MON_COUNT; loop++)
	{
		if(NU != pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_IDX+loop*4])	{nMonTypeCnt++;}
	}

	//	nMonTypeCnt = 3;
	pMonData = GL_NEW STAGE_MON_DATA [nMonTypeCnt];

	for(loop = 0; loop < nMonTypeCnt; loop++)
	{
		pMonData[loop].nMonIdx = pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_IDX+loop*4];
		pMonData[loop].nNameIdx = pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_NAME+loop*4];
		pMonData[loop].nPtn = pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_PTN+loop*4];
		pMonData[loop].nCount = pMinimap->m_CurMapSector->m_MonsterInfo[MI_MON1_COUNT+loop*4];
	}

	//	¸ó½ºÅÍ ÃÑ °¹¼ö
	m_nMonSeedCnt = 0;
	for(int loop = 0; loop < nMonTypeCnt; loop++)
	{
		m_nMonSeedCnt += pMonData[loop].nCount;
	}

	//	¸ó½ºÅÍ°¡ ¾ø´Ù.
	if(!m_nMonSeedCnt)	{return;}
	/////////////////////////////////////////////////////////////////////////////////////////////

	//	¸ó½ºÅÍ µ¥ÀÌÅ¸ ±¸¼º
	m_nSeedData	= GL_NEW int[m_nMonSeedCnt];

	loop = 0;
	int loop2 = 0;
	int addcnt = 0;

	for(loop = 0; loop < nMonTypeCnt; loop++)
	{
		for(loop2 = 0; loop2 < pMonData[loop].nCount; loop2++)
		{
			m_nSeedData[loop2+addcnt] = loop;
		}
		addcnt += loop2;
	}

	//	½Ãµå ½º¿Ò(10¹ø)
	int src, dst, tmp;
	for(loop = 0; loop < 10; loop++)
	{
		src = SUTIL_GetRandom()%(m_nMonSeedCnt);
		dst = SUTIL_GetRandom()%(m_nMonSeedCnt);

		tmp = m_nSeedData[src];
		m_nSeedData[src] = m_nSeedData[dst];
		m_nSeedData[dst] = tmp;
	}

	//	µî±Þ °áÁ¤ Å×ÀÌºí
	int GradeDiceTable[5][4] = {{0, 38, 15, 5},	{0, 36, 16, 6},	{0, 34, 17, 7},	{0, 34, 17, 8},	{0, 33, 17, 9}};

	//	µî±Þ°áÁ¤À» ÇØ¾ßµÊ
	m_nSeedDataGrade = GL_NEW int [m_nMonSeedCnt];

	int TableIdx = 4;
	if(70 < hero->s_Status[hero->s_HeroTag.SEX].LEVEL)		{TableIdx = 0;}
	else if(60 < hero->s_Status[hero->s_HeroTag.SEX].LEVEL)	{TableIdx = 1;}
	else if(40 < hero->s_Status[hero->s_HeroTag.SEX].LEVEL)	{TableIdx = 2;}
	else if(20 < hero->s_Status[hero->s_HeroTag.SEX].LEVEL)	{TableIdx = 3;}

	//	µî±Þ È®ÀÎ
	int Dice = 0;
	for(loop = GRADE_RARE; loop <= GRADE_SPECIAL; loop++)
	{
		while(0 < nMonGradeCnt[loop])
		{
			Dice = SUTIL_GetRandom()%100;
			if(GradeDiceTable[TableIdx][loop] > Dice)
			{
				m_nSeedDataGrade[Dice%m_nMonSeedCnt] = loop;
			}
			nMonGradeCnt[loop]--;
		}
	}

	//	¸ó½ºÅÍÀÇ ÀÌ¹ÌÁö¸¦ ·Îµå½ÃÅ²´Ù.
	SUTIL_LoadAspritePack(PACK_SPRITE_MON);
	for(loop = 0; loop < nMonTypeCnt; loop++)
	{
		LoadMonsterSprite(pMonData[loop].nMonIdx);
	}
	SUTIL_ReleaseAspritePack();
}


//--------------------------------------------------------------------------
void GFieldBattle::LoadMonsterSprite(int monidx)
//--------------------------------------------------------------------------
{
	//		pMonData[loop].nMonIdx = FIELD_MONSTER_INFO[nRealFieldNum][GEN_MON1_IDX+loop*4];

	//	ÀÏ¹Ý ¸ó½ºÅÍ //////////////////////////////////////////////////

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
}

//--------------------------------------------------------------------------
Monster* GFieldBattle::AddMonster(int addType, int monidx, int nameidx, int ptnIdx, int gradeDataidx, int x, int y, int startx, int starty, int regenidx, int z)
//--------------------------------------------------------------------------
{
	Monster* tmpMonster = NULL;

	//	ÀÏ¹Ý ¸ó½ºÅÍ //////////////////////////////////////////////////
	int namestartidx = 0;
	int ptnstartidx = 0;

	switch(monidx)
	{
		case MON_IDX_GHOST:			{tmpMonster = GL_NEW Mon_GHOST();		break;}
		case MON_IDX_SUNFLOWER:		{tmpMonster = GL_NEW Mon_SUNFLOWER();		break;}
		case MON_IDX_SLIME:			{tmpMonster = GL_NEW Mon_SLIME();		break;}
		case MON_IDX_CROWN_BOMB:	{tmpMonster = GL_NEW Mon_CROWN_BOMB();	break;}
		case MON_IDX_BEAR:			{tmpMonster = GL_NEW Mon_BEAR();		break;}
		case MON_IDX_TREE:			{tmpMonster = GL_NEW Mon_TREE();		break;}
		case Mon_IDX_SHREK:			{tmpMonster = GL_NEW Mon_SHREK();		break;}
		case MON_IDX_GOLLUM:		{tmpMonster = GL_NEW Mon_GOLLUM();		break;}
		case MON_IDX_SHRIMP:		{tmpMonster = GL_NEW Mon_SHRIMP();		break;}
		case MON_IDX_BEE:			{tmpMonster = GL_NEW Mon_BEE();			break;}
		case MON_IDX_ELF_FIRE:		{tmpMonster = GL_NEW Mon_ELF_FIRE();	break;}
		case MON_IDX_ELF_ICE:		{tmpMonster = GL_NEW Mon_ELF_ICE();		break;}
//		case MON_IDX_ELF_SILENCE:	{tmpMonster = GL_NEW Mon_ELF_SILENCE();	break;}
		case MON_IDX_FIRE:			{tmpMonster = GL_NEW Mon_FIRE();		break;}
		case MON_IDX_EYE:			{tmpMonster = GL_NEW Mon_EYE();			break;}
		case MON_IDX_SPEAR:			{tmpMonster = GL_NEW Mon_SPEAR();		break;}
		case MON_IDX_HUMAN_MELEE:	{tmpMonster = GL_NEW Mon_HUMAN_MELEE();	break;}
		case MON_IDX_HUMAN_RANGE:	{tmpMonster = GL_NEW Mon_HUMAN_RANGE();	break;}
		case MON_IDX_LIZARD:		{tmpMonster = GL_NEW Mon_LIZARD();		break;}
		case MON_IDX_TURTLE:		{tmpMonster = GL_NEW Mon_TURTLE();		break;}
		case MON_IDX_THUNDERCLOUD:	{tmpMonster = GL_NEW Mon_THUNDERCLOUD();		break;}
		default:					{										break;}
	}

	if(tmpMonster)
	{
		//	Ä³¸¯ÅÍÀÇ À§Ä¡¸¦ ³Ö¾îÁØ´Ù.
		tmpMonster->m_CharInfo = m_CharInfo;

		tmpMonster->RegistUsingBaseData(pMonSkillList, pMonMsgList, &s_ASpriteSet);

		//	ÄÃ·¯ °áÁ¤
		//int coloridx = nameidx * tmpMonster->m_nSpriteIdx;
		int coloridx = nameidx%3;


		//	¼Ó¼º °áÁ¤
		int elementidx = nameidx%3;

		//	¼Ó¼º °áÁ¤
		//int levelidx = hero->s_Status[hero->s_HeroTag.SEX].LEVEL;
		int levelidx = m_nMonLevel;
		
		if(m_nMonLevelRnd)
		{
			levelidx += SUTIL_GetRandom()%(m_nMonLevelRnd);
		}

		tmpMonster->SetMonData(coloridx, elementidx, (namestartidx+(monidx*9)+nameidx), (ptnstartidx+(monidx*2)+ptnIdx), gradeDataidx, levelidx);
		tmpMonster->SetPosition(x, y, z);
		tmpMonster->SetRegenType(addType, regenidx, startx, starty);
		MoveTail(pMonList);
		pMonList->Insert_prev(tmpMonster);
		return tmpMonster;
	}

	//	Ãß°¡ ¿ÀºêÁ§Æ® //////////////////////////////////////////////////
	namestartidx += MON_IDX_COUNT_NORMAL_MON*9;	//	ÀÎµ¦½º º¸Á¤
	ptnstartidx += MON_IDX_COUNT_NORMAL_MON*2;

	switch(monidx)
	{
		case MON_IDX_BARREL:				{tmpMonster = GL_NEW Barrel();					break;}
		case MON_IDX_STONE_BIG:				{tmpMonster = GL_NEW Stone_big();				break;}
		case MON_IDX_BOX:					{tmpMonster = GL_NEW Box();						break;}
		case MON_IDX_KNIGHT:				{tmpMonster = GL_NEW Knight();					break;}
		case MON_IDX_TEMPLE_CROCK_SMALL:	{tmpMonster = GL_NEW Temple_crock_small();		break;}
		case MON_IDX_TEMPLE_CROCK_BIG:		{tmpMonster = GL_NEW Temple_crock_big();		break;}
		case MON_IDX_TEMPLE_STONEBOX_SMALL:	{tmpMonster = GL_NEW Temple_stonebox_small();	break;}
		case MON_IDX_TEMPLE_STONEBOX_BIG:	{tmpMonster = GL_NEW Temple_stonebox_big();		break;}
		case MON_IDX_BUG:					{tmpMonster = GL_NEW Mon_BUG();					break;}
		case MON_IDX_DRILL:					{tmpMonster = GL_NEW Mon_DRILL();				break;}
		case MON_IDX_BOSS5_DEVIL:			{tmpMonster = GL_NEW Mon_BOSS5_DEVIL();			break;}
										
	}

	if(tmpMonster)
	{
		//	Ä³¸¯ÅÍÀÇ À§Ä¡¸¦ ³Ö¾îÁØ´Ù.
		tmpMonster->m_CharInfo = m_CharInfo;

		tmpMonster->RegistUsingBaseData(pMonSkillList, pMonMsgList, &s_ASpriteSet);

//		//	ÄÃ·¯ °áÁ¤
//		int coloridx = 0;

//		//	¼Ó¼º °áÁ¤
//		int elementidx = 0;

//		//	·¹º§ °áÁ¤
//		int levelidx = m_nMonLevel;

//		tmpMonster->SetMonData(coloridx, elementidx, nameidx, ptnIdx, gradeDataidx, levelidx);

		tmpMonster->SetMonData(0, MON_ELEMENTAL_NON, (namestartidx + (monidx-MON_IDX_BARREL)),
														(ptnstartidx + (monidx-MON_IDX_BARREL)), GRADE_NORMAL, m_nMonLevel);
		tmpMonster->SetPosition(x, y, z);
		tmpMonster->SetRegenType(addType, regenidx, startx, starty);
		MoveTail(pMonList);
		pMonList->Insert_prev(tmpMonster);

		return tmpMonster;
	}


	//	º¸½º ¸ó½ºÅÍ //////////////////////////////////////////////////
	namestartidx += (MON_IDX_COUNT_OBJECT);	//	ÀÎµ¦½º º¸Á¤
	ptnstartidx += (MON_IDX_COUNT_OBJECT);

	switch(monidx)
	{
		case MON_IDX_HOROS:					{tmpMonster = GL_NEW BossMon2_1();					break;}

		case MON_IDX_DEVIJOHNS:				{tmpMonster = GL_NEW Mon_DEVIJOHNS();				break;}

//		case MON_IDX_BIG_DRAGON1:			{tmpMonster = GL_NEW BossBigDragon1();				break;}
//		case MON_IDX_BIG_DRAGON2:			{tmpMonster = GL_NEW BossBigDragon2();				break;}
//		case MON_IDX_BIG_DRAGON3:			{tmpMonster = GL_NEW BossBigDragon3();				break;}

		case MON_IDX_WORM:					{tmpMonster = GL_NEW BossWorm();					break;}
		case MON_IDX_SKELBIRD:				{tmpMonster = GL_NEW BossSkelBird();				break;}
		case MON_IDX_SKELBIRD_L_ARM:		{tmpMonster = GL_NEW BossSkelBird_L_ARM();			break;}
		case MON_IDX_SKELBIRD_R_ARM:		{tmpMonster = GL_NEW BossSkelBird_R_ARM();			break;}

		case MON_IDX_FLOWER:				{tmpMonster = GL_NEW BossFlower();					break;}
		case MON_IDX_FLOWER_BRAIN:			{tmpMonster = GL_NEW BossFlower_Brain();			break;}

		case MON_IDX_DARK_KNIGHT:			{tmpMonster = GL_NEW DarkKnight();					break;}
		case MON_IDX_DARK_KNIGHT_MIRROR:	{tmpMonster = GL_NEW DarkKnight_Mirror();			break;}

		case MON_IDX_BIGTURTLE:				{tmpMonster = GL_NEW BigTurtle();					break;}

		case MON_IDX_LASTBOSS:				{tmpMonster = GL_NEW LastBoss();					break;}
											
	}

	if(tmpMonster)
	{
		//	Ä³¸¯ÅÍÀÇ À§Ä¡¸¦ ³Ö¾îÁØ´Ù.
		tmpMonster->m_CharInfo = m_CharInfo;

		tmpMonster->RegistUsingBaseData(pMonSkillList, pMonMsgList, &s_ASpriteSet);

		//	ÄÃ·¯ °áÁ¤
		//int coloridx = nameidx * tmpMonster->m_nSpriteIdx;
		int coloridx = 0;

		//	¼Ó¼º °áÁ¤
		int elementidx = 0;

		//	¼Ó¼º °áÁ¤ (º¸½º ·¹º§À» ·£´ýÀ¸·Î ÇÏ¸é ÇÑ ¸öÅëÀÇ ¸ó½ºÅÍµéÀÇ ÇÇ°¡ ´Þ¶óÁø´Ù.)
		int levelidx = m_nMonLevel;

//		if(m_nMonLevelRnd)	{levelidx += SUTIL_GetRandom()%(m_nMonLevelRnd);}

		tmpMonster->SetMonData(coloridx, elementidx, nameidx, ptnIdx, gradeDataidx, levelidx);
		tmpMonster->SetPosition(x, y, z);
		tmpMonster->SetRegenType(addType, regenidx, startx, starty);
		MoveTail(pMonList);
		pMonList->Insert_prev(tmpMonster);
		return tmpMonster;
	}

	return NULL;

	/*
	case MON_IDX_BOSS2_1:		{tmpMonster = GL_NEW BossMon2_1();		break;}
	//		case MON_IDX_BOSS3_1:		{tmpMonster = GL_NEW BossMon3_1();		break;}
	//		case MON_IDX_BOSS3_2:		{tmpMonster = GL_NEW BossMon3_2();		break;}
	case MON_IDX_BOSS5_1:		{tmpMonster = GL_NEW BossMon5_1();		break;}
	case MON_IDX_BOSS5_2:		{tmpMonster = GL_NEW BossMon5_2();		break;}
	case MON_IDX_BOSS5_3:		{tmpMonster = GL_NEW BossMon5_3();		break;}
	case MON_IDX_BOSS5_4:		{tmpMonster = GL_NEW BossMon5_4();		break;}
	case MON_IDX_BOSS5_5:		{tmpMonster = GL_NEW BossMon5_5();		break;}
	//	case MON_IDX_BOSS6_1:		{tmpMonster = GL_NEW BossMon6_1();		break;}
	default:	{return NULL;}
	}

	*/
}



//--------------------------------------------------------------------------
void GFieldBattle::AddRegenMonSetting(int defPosx)
//--------------------------------------------------------------------------
{
	if(0 >= m_nMonSeedCnt)	{return;}
	m_nMonSeedCnt--;

	int x = SUTIL_GetRandom()%(pField->m_nRegenDistance);
	x += defPosx;

	int y = 185 + SUTIL_GetRandom()%70;

	//add
	AddMonster(1,
		pMonData[m_nSeedData[m_nMonSeedCnt]].nMonIdx,
		pMonData[m_nSeedData[m_nMonSeedCnt]].nNameIdx,
		pMonData[m_nSeedData[m_nMonSeedCnt]].nPtn,
		m_nSeedDataGrade[m_nMonSeedCnt],
		x, y, x, y, defPosx, 0);
}


//--------------------------------------------------------------------------
void GFieldBattle::AddFirstMonSetting()
//--------------------------------------------------------------------------
{
	//	ÀÌ°ªÀ» Ãß°¡ÇØÁÖ¸é ¿©±â¼­ºÎÅÍ ÇÑ¸¶¸® ¸¸µé¾îÁö°Ô ÇÑ´Ù.
	int x, y;
	int nRegenTmp = 0;

	while(pField->m_nFieldSize_X > nRegenTmp)
	{
		if(0 >= m_nMonSeedCnt)	{break;}

		AddRegenMonSetting(nRegenTmp);
		nRegenTmp += pField->m_nRegenDistance;
	}
}

/*
//--------------------------------------------------------------------------
void GFieldBattle::AddRegenMonSetting()
//--------------------------------------------------------------------------
{
if(1 > m_nMonSeedCnt)	{return;}

int MonIdx = 0;
int RegenDice = 0;

//	¸®Á¨ ¿µ¿ª °áÁ¤
while(1)
{
RegenDice = SUTIL_GetRandom()%nRegenCnt;
//		if(1 > m_nRegenType[RegenDice])		{continue;}		//	¸®Á¨ ¿µ¿ªÀÌ ¾Æ´Ï¶ó¸é
if(1 == m_nIsRegen[RegenDice])	{continue;}
break;
}

//	¸®Á¨ ¿µ¿ª ¹× ¸®Á¨ Å¸ÀÔ ¼³Á¤
int mapsize = pField->m_nFieldSize_X;
int mapstart = pField->m_nSrcCamAngle_X;
int xTmp = m_nRegenX[RegenDice];
int yTmp = m_nRegenY[RegenDice];
int regenXTmp = xTmp;
int regenYTmp = yTmp;
int addType = 0;

if(xTmp > mapstart && xTmp < (mapstart+SCREEN_WIDTH))		//	È­¸é ¾ÈÀÌ¶ó¸é
{
addType = 3;
}
else
{
addType = (SUTIL_GetRandom()%2)+2;
}

if(addType == 2)		//	Á¢±ÙÇÏ¸é¼­ ½ÃÀÛÇÑ´Ù. Á¢±Ù°Å¸®¸¦ °è»êÇÑ´Ù.
{
regenXTmp = (xTmp+m_CharInfo->m_nPos.x)/2;
}
else if(addType == 3)		//	±ÙÃ³¿¡¼­ Àç»ýµÇ¾î ÀüÅõ¸ðµå·Î µé¾î¿Â´Ù.
{
if(xTmp < m_CharInfo->m_nPos.x)
{
xTmp = m_CharInfo->m_nPos.x-SCREEN_WIDTH;
}
else
{
xTmp = m_CharInfo->m_nPos.x+SCREEN_WIDTH;
}

if(0 > xTmp)		{xTmp = m_CharInfo->m_nPos.x+SCREEN_WIDTH;}
if(mapsize < xTmp)	{xTmp = m_CharInfo->m_nPos.x-SCREEN_WIDTH;}

regenXTmp = xTmp;
}

//	¸ó½ºÅÍÀÇ °¹¼ö¸¦ ÁÙ¿©ÁØ´Ù.
m_nMonSeedCnt--;

//	¸ó½ºÅÍ °áÁ¤
//	ÇöÀç ¸®Á¨ÁßÀÎ »óÅÂÀÎ°É ¾Ë·ÁÁØ´Ù.
m_nIsRegen[RegenDice] = 1;

AddMonster(addType, m_nSeedData[m_nMonSeedCnt], m_nSeedDataGrade[m_nMonSeedCnt],
xTmp, yTmp,	regenXTmp, regenYTmp, RegenDice);

GetData(pMonList)->Process(m_CharInfo);
}
*/



//--------------------------------------------------------------------------
void GFieldBattle::Release()
//--------------------------------------------------------------------------
{	
	//	±×¸²ÀÚ È¿°ú
	SUTIL_FreeSprite(s_ASpriteSet.pShadowAs);
	SUTIL_FreeSprite(s_ASpriteSet.pDebuffAs);
	SUTIL_FreeSprite(s_ASpriteSet.pFieldUiAs);
	SUTIL_FreeSprite(s_ASpriteSet.pItemAs);

	//	ÁÖÀÎ°ø
	SAFE_DEL(hero);

	// ¹è°æ
	//	/*SUTIL_FreeSprite*/SAFE_DELETE(pFieldAs);
	//	/*SUTIL_FreeSpriteInstance*/SAFE_DELETE(pFieldAsins);
	SAFE_DELETE(pField)

		//	¸ó½ºÅÍ

		SAFE_DELETE(m_CharInfo);

	for(int loop = 0; loop < SPRITE_MON_MAX; loop++)
	{
		if(NULL != m_MonAs[loop])
		{
			SUTIL_FreeSprite(m_MonAs[loop]);
		}
	}

	if(pMonList)
	{
		MoveHead(pMonList);
		MoveNext(pMonList);
		while(NotEndList(pMonList))
		{
			SAFE_DELETE(GetData(pMonList));
			pMonList->Delete();
			//		MoveNext(pMonList);
		}
	}
	SAFE_DELETE(pMonList)

		if(pMonSkillList)
		{
			MoveHead(pMonSkillList);
			MoveNext(pMonSkillList);
			while(NotEndList(pMonSkillList))
			{
				SUTIL_FreeSpriteInstance(GetData(pMonSkillList)->pMonSkillAsIns);
				SAFE_DELETE(GetData(pMonSkillList));
				pMonSkillList->Delete();
				//	MoveNext(pMonSkillList);
			}
		}
		SAFE_DELETE(pMonSkillList)

			//	message
			if(pMonMsgList)
			{
				MoveHead(pMonMsgList);
				MoveNext(pMonMsgList);
				while(NotEndList(pMonMsgList))
				{
					SAFE_DELETE(GetData(pMonMsgList));
					pMonMsgList->Delete();
				}
			}
			SAFE_DELETE(pMonMsgList)



				//	ÇÊµå UI
				SAFE_DELETE(pFieldUi);

			//	±âÅ¸
			SAFE_DELETE(pMonData);
			SAFE_DELETE(m_nSeedData);
			SAFE_DELETE(m_nSeedDataGrade);

			for(int i=0; i<MAX_SOUND; i++)
			{
				SUTIL_Sound_Free(i);
			}

			//	¾¾³×¸¶
			if(pCinema)
			{
				pCinema->Release_Cinematics();
			}
			SAFE_DELETE(pCinema);

	SAFE_DELETE(pMinimap);
	
}

//--------------------------------------------------------------------------
void GFieldBattle::Process()
//--------------------------------------------------------------------------
{
	if(b_WorldMap){return;}//¿ùµå¸Ê ±×¸®±â
		
	

	if(UpdatePrologue())	{return;}

	//	ÀÌº¥Æ®´Â ºÐ¼®ÇÑ´Ù.
	Analysis_Event();
	if(isHoldingProcess)	{return;}



	if(true == pCinema->m_IsPlayCinema)
	{
		pCinema->Update_Cinematics();
		return;
	}

	int loop = 0;

	if(b_PopupUi)
	{
		return;
	}
	else if(hero->_m_actNum == HERO_DOWNED_2 && hero->s_Status[hero->s_HeroTag.SEX].LIFE<=0){//ÁÖÀÎ°ø »ç¸Á
		b_PopupUi = true;
		pPopupUi->GameOver = true;
		pField->workPal(false,0,0);
	}


	ProcessTimerEvent();

	//	¸Þ¼¼Áö¸¦ ºÐ¼®ÇÑ´Ù.
	Analysis_Mon_Message();

	//	//	ÁÖÀÎ°øÀÇ Á¤º¸¸¦ ¸ó½ºÅÍ¿¡°Ô ³Ñ°ÜÁÖ±âÀ§ÇÑ µ¥ÀÌÅÍ¸¦ ¸¸µç´Ù.
	//	m_CharInfo->m_nPos.x = hero->_ins_Hero->m_posX - hero->_ins_Hero->m_stopAniX;
	//	m_CharInfo->m_nPos.y = hero->_ins_Hero->m_posY;
	//	m_CharInfo->m_nPos.z = hero->_ins_Hero->m_posZ - hero->_ins_Hero->m_stopAniZ;
	//	m_CharInfo->m_Direction = hero->_b_LookRight;

	//	//	¸ó½ºÅÍ°¡ 3¸¶¸® ÀÌÇÏ¸é Ãß°¡½ÃÄÑÁØ´Ù.
	//	if(nGenCnt > GetNodeCount(pMonList))
	//	{
	//		AddMonster(SUTIL_GetRandom()%6);
	//		AddMonster(0);
	//		AddRegenMonSetting();
	//	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////// Ãæµ¹Ã¼Å©	//////////////////////////////////////////////////////
	////////////////////////////////////////////////////// Ãæµ¹Ã¼Å©	//////////////////////////////////////////////////////
	LIST__START(pMonList)//È÷¾î·Î°¡ ¸ó½ºÅÍ¸¦¶§¸®´Â°æ¿ì
//		if(MON_AC_DIE != GetData(pMonList)->m_ActState &&
//			MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState &&
//			MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState)
		if(!(GetData(pMonList)->m_nFeature & FE_DONT_TOUCH))
		{
			if(Contact_Check(hero->_ins_Hero, GetData(pMonList)->pMonAsIns,NULL,GetData(pMonList)->m_nBodySize))
			{
				DamageSand_Hero(hero, GetData(pMonList));//ÁÖÀÎ°ø ÆòÅ¸
			}

			if(hero->s_Skill_Set[hero->s_HeroTag.SEX].OVER_SkillEffect)
			{
				if(Contact_Check(hero->_ins_Skill[hero->s_HeroTag.SEX][hero->s_Skill_Set[hero->s_HeroTag.SEX].Num][0], GetData(pMonList)->pMonAsIns,NULL, GetData(pMonList)->m_nBodySize))
				{
					DamageSand_Hero(hero, GetData(pMonList));//ÁÖÀÎ°ø ½ºÅ³
				}
			}

			for(int i =0;i<3;i++){
				if(hero->s_Knife_Eff[i].act && hero->s_Knife_Eff[i].LVup_Eff_Ins)
					if(Contact_Check(hero->s_Knife_Eff[i].LVup_Eff_Ins, GetData(pMonList)->pMonAsIns,NULL,GetData(pMonList)->m_nBodySize))//Ãæ®G!!
					{
						DamageSand_Hero(hero, GetData(pMonList));//Ä® ¹öÇÁ Ã¼Å©
					}
			}

			for(int i =0 ;i<BULLET_MAX ; i++){
				if(hero->s_Bullet_Eff[i].act && hero->s_Bullet_Eff[i].LVup_Eff_Ins)
				{
					if(Contact_Check(hero->s_Bullet_Eff[i].LVup_Eff_Ins, GetData(pMonList)->pMonAsIns,NULL,GetData(pMonList)->m_nBodySize))//Ãæ®G!!
					{
						DamageSand_Hero(hero, GetData(pMonList));//ÀåÇ³ Ã¼Å©
						switch (i){
							case 0:case 1:case 2:case 3:case 4:
								hero->s_Bullet_Eff[i].LVupEff_Num = 100;//ÀåÇ³»ç¶óÁü
								break;
							case 7:case 8:case 9:
								if(hero->s_Bullet_Eff[i].LVup_Eff_Ins->m_nCrtModule == ANIM_WOMAN_S7_A_S_SKILL7_2)
									hero->s_Bullet_Eff[i].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S7_A_S_SKILL7_3);
								break;
						}
					}
				}
			}
		}
		LIST____END(pMonList)

			if(!(Exception_Num & PROCESS_MON_NOT)){//¸ó½ºÅÍ°¡ È÷¾î·Î¸¦ ¶§¸®´Â°æ¿ì
				LIST__START(pMonList)

					if(Contact_Check(GetData(pMonList)->pMonAsIns,hero->_ins_Hero,NULL,14))//Ãæ®G!!
					{
						DamageSand_Mon(GetData(pMonList),hero);//¸ó½ºÅÍ ÆòÅ¸
						hero->RCV_Debuff( GetData(pMonList)->SND_Debuff(0) );
					}
					LIST____END(pMonList)

						LIST__START(pMonSkillList)
						if(1 > GetData(pMonSkillList)->Delay)
						{
							if(0 < GetData(pMonSkillList)->damagetime)
							{
								GetData(pMonSkillList)->pMonSkillAsIns->m_posX += (GetData(pMonSkillList)->Movex);
								GetData(pMonSkillList)->pMonSkillAsIns->m_posY += (GetData(pMonSkillList)->Movey);
								GetData(pMonSkillList)->pMonSkillAsIns->m_posZ += (GetData(pMonSkillList)->Movez);

								if(Contact_Check(GetData(pMonSkillList)->pMonSkillAsIns,hero->_ins_Hero,NULL,14))//Ãæ®G!!
								{
									GetData(pMonSkillList)->damagetime--;
									DamageSand_Mon((Monster*)(GetData(pMonSkillList)->who),hero);//¸ó½ºÅÍ ½ºÅ³ 
									if(SKILL_REMOVE == GetData(pMonSkillList)->type)GetData(pMonSkillList)->lifeTime = 0;
								}
							}
						}
						LIST____END(pMonSkillList)

			}
			////////////////////////////////////////////////////// Ãæµ¹Ã¼Å©	//////////////////////////////////////////////////////
			////////////////////////////////////////////////////// Ãæµ¹Ã¼Å©	//////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//	ÁÖÀÎ°ø
			hero->Process();

			//	ÁÖÀÎ°øÀÇ Á¤º¸¸¦ ¸ó½ºÅÍ¿¡°Ô ³Ñ°ÜÁÖ±âÀ§ÇÑ µ¥ÀÌÅÍ¸¦ ¸¸µç´Ù.
			m_CharInfo->m_nPos.x = hero->_ins_Hero->m_posX;
			m_CharInfo->m_nPos.y = hero->_ins_Hero->m_posY;
			m_CharInfo->m_nPos.z = hero->_ins_Hero->m_posZ;
			m_CharInfo->m_Direction = hero->_b_LookRight;

			//	¸ó½ºÅÍ
			if(!(Exception_Num & PROCESS_MON_NOT)){
				MoveHead(pMonList);
				MoveNext(pMonList);
				while(NotEndList(pMonList))
				{
					GetData(pMonList)->Process(m_CharInfo);

					//	¸ó½ºÅÍ°¡ Á×¾úÀ» °æ¿ì
					if(MON_AC_DIE_AFTER == GetData(pMonList)->m_ActState && 0 == GetData(pMonList)->m_nSkillCount)
					{
						if(NOT_REGEN != GetData(pMonList)->m_nRegenIdx)
						{
							if(0 < m_nMonSeedCnt)
							{
								ADD_EVENT_MSG(EVT_ADD_MONSTER, 20, GetData(pMonList)->m_nRegenIdx);
							}
							//					m_nIsRegen[GetData(pMonList)->m_nRegenIdx] = 0;	//	Àç»ý ¿µ¿ªÀ» ÃÊ±âÈ­½ÃÄÑÁØ´Ù.
						}
						hero->Set_Exp(GetData(pMonList)->SND_Exp(hero->s_Status[hero->s_HeroTag.SEX].LEVEL) );

						if(!(GetData(pMonList)->m_nFeature & FE_DONT_HAVE_ITEM))
						{
							ItemBag tmp = pPopupUi->MakeItem(GetData(pMonList)->m_nMonIdx , GetData(pMonList)->m_nLevel, hero->s_HeroTag.SEX, pField->m_nSaveStageNum);
							if(0 != tmp.ITEM_KIND)
							{
								pField->InsertDropItem(tmp, GetData(pMonList)->pMonAsIns->m_posX, GetData(pMonList)->pMonAsIns->m_posY+15);
								//pField->InsertDropItem(tmp, 100, 200);
							}
						}

						//	ÆË¾÷ UI
						SAFE_DELETE(GetData(pMonList));
						pMonList->Delete();
						continue;
					}

					MoveNext(pMonList);
				}

				//	¸ó½ºÅÍ ½ºÅ³
				MoveHead(pMonSkillList);
				MoveNext(pMonSkillList);
				while(NotEndList(pMonSkillList))
				{
					if(1 > GetData(pMonSkillList)->lifeTime)
					{
						SUTIL_FreeSpriteInstance(GetData(pMonSkillList)->pMonSkillAsIns);
						((Monster*)(GetData(pMonSkillList)->who))->m_nSkillCount--;
						SAFE_DELETE(GetData(pMonSkillList));
						pMonSkillList->Delete();
						continue;
					}

					if(1 > GetData(pMonSkillList)->Delay)
					{
						SUTIL_UpdateTimeAsprite(GetData(pMonSkillList)->pMonSkillAsIns);
						GetData(pMonSkillList)->lifeTime--;
					}
					else	{GetData(pMonSkillList)->Delay--;}

					MoveNext(pMonSkillList);
				}
			}

			SetCameraMove();
			pField->Process();
			EventProcess();

			//	¿ÀºêÁ§Æ®¸¦ ¾÷µ¥ÀÌÆ® ½ÃÄÑÁØ´Ù.
			SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
			pObjectMgr->Process();

			//	ÇÊµå UI
			pFieldUi->Process();

			//	È­¸é ½ºÅ©·Ñ ¼ÂÆÃ

			int camera_x = -(pField->m_nSrcCamAngle_X);
			hero->_ins_Hero->setCamera(camera_x,0);
			for(int xx = 0;xx<3;xx++){//ÀÌÆåÆ®¿¡ Ä«¸Þ¶óÁÂÇ¥ Àû¿ë
				for(int sex = 0;sex<2;sex++){
					if(hero->s_Skill.Equip_A[sex*3 + xx]>=0){
						hero->_ins_Skill[sex][xx][0]->setCamera(camera_x,0);
						hero->_ins_Skill[sex][xx][1]->setCamera(camera_x,0);
					}
				}
			}
			if(hero->s_HeroTag.act){
				hero->_ins_Hero_clone->setCamera(camera_x,0);
				if(hero->s_HeroTag.OVER_SkillEffect)hero->_ins_Skill_clone[0]->setCamera(camera_x,0);
				if(hero->s_HeroTag.DOWN_SkillEffect)hero->_ins_Skill_clone[1]->setCamera(camera_x,0);
					
			}

			//	¸ó½ºÅÍ
			MoveHead(pMonList);
			MoveNext(pMonList);
			while(NotEndList(pMonList))
			{
				GetData(pMonList)->pMonAsIns->setCamera(camera_x,0);
				MoveNext(pMonList);
			}

			//	¸ó½ºÅÍ ½ºÅ³
			MoveHead(pMonSkillList);
			MoveNext(pMonSkillList);
			while(NotEndList(pMonSkillList))
			{
				GetData(pMonSkillList)->pMonSkillAsIns->setCamera(camera_x,0);
				MoveNext(pMonSkillList);
			}

			//hero->_m_mapX = ( pField->getRelativityX());  // ÀÌÇÔ¼ö¸¦ ÀÌ¿ëÇÏ¿© ±¸ÇÑ ÁÂÇ¥¸¦ Ä³¸¯ÅÍ³ª ¸ó½ºÅÍ¸¦ ±×¸±¶§ ´õÇØÁØ´Ù 
			//pField->getMapSizeX();  //¸ÊÀÇ ±æÀÌ¸¦ ¸®ÅÏÇÑ´Ù 
			//	ÇÊµå ÀÌÆåÆ®
			MoveHead(pFieldUi->pEftList);
			MoveNext(pFieldUi->pEftList);
			while(NotEndList(pFieldUi->pEftList))
			{
				GetData(pFieldUi->pEftList)->pSkillEftAsIns->setCamera(camera_x,0);
				MoveNext(pFieldUi->pEftList);
			}

			pFieldUi->m_pFieldUiDamageNumAsIns->setCamera(camera_x,0);

			//¸ðµç ÇÁ·Î¼¼½º°¡ Á¾·áµÈ ÈÄ¿¡ ÁÖÀÎ°øÄÉ¸¯ÅÍÀÇ ÁÂÇ¥¸¦ º¸Á¤ÇÑ´Ù.
			MoveHead(pMonList);
			MoveNext(pMonList);
			while(NotEndList(pMonList))
			{
//				if((MON_AC_DIE != GetData(pMonList)->m_ActState) &&
//					(MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState) &&
//					(MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState) &&
//					(true == GetData(pMonList)->m_bIsCheckBody) )

				if(!(GetData(pMonList)->m_nFeature & FE_DONT_TOUCH))
				{
					if(!hero->s_Skill_Set[hero->s_HeroTag.SEX].OVER_SkillEffect)
					{
						Contact_Body_Check(hero->_ins_Hero, GetData(pMonList)->pMonAsIns,10,10,true);//Ãæµ¹½Ã ÁÂÇ¥º¸Á¤
					}
				}
				MoveNext(pMonList);
			}


			MoveHead(pMonList);
			MoveNext(pMonList);
			int x_max = pField->m_nFieldSize_X;
			while(NotEndList(pMonList))
			{
//				if((MON_AC_DIE != GetData(pMonList)->m_ActState) &&
//					MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState &&
//					(MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState))
				if(!(GetData(pMonList)->m_nFeature & FE_DONT_AREA_CHECK))
				{
//					if(!hero->s_Skill_Set[hero->s_HeroTag.SEX].OVER_SkillEffect)
//					{
						Area_Check(GetData(pMonList)->pMonAsIns,x_max);//Ãæµ¹½Ã ÁÂÇ¥º¸Á¤

//						if(1)
//						{
//							int a = GetData(pMonList)->pMonAsIns->m_posX - GetData(pMonList)->pMonAsIns->m_stopAniX;
//							int b = GetData(pMonList)->m_nPos.x
//						}

						//	¸ó½ºÅÍ´Â ÁÂÇ¥°¡ µû·Î °ü¸®µÈ´Ù.
//						GetData(pMonList)->m_nPos.x = GetData(pMonList)->pMonAsIns->m_posX;
//					}
				}
				MoveNext(pMonList);
			}

			///////////////////////////////////////////////////////////////////////////
			//	ÇÊµå Ãæµ¹Ã¼Å©

			///////////////////////////////////////////////////////////////////////////

//			for(InitList(pField->pLayerList);NotEndList(pField->pLayerList);MoveNext(pField->pLayerList))
//			{
//				for(InitList(GetData(pField->pLayerList)->pObjectList);
//					NotEndList(GetData(pField->pLayerList)->pObjectList);
//					MoveNext(GetData(pField->pLayerList)->pObjectList))
//				{
//					Contact_Body_Check(hero->_ins_Hero, GetData(GetData(pField->pLayerList)->pObjectList)->pAsIns,10,10, true);//Ãæµ¹½Ã ÁÂÇ¥º¸Á¤
//				}
//			}

///////////////////////////////////////////////////////////////////////////////////////////////////////
			//	¸ó½ºÅÍ ³¢¸®ÀÇ Ãæµ¹Ã¼Å©
			if(1)
			{
				Monster* pTmpMonster = NULL;
				for(InitList(pMonList);NotEndList(pMonList);MoveNext(pMonList))
				{
					pMonList->SaveCurrentState();
					pTmpMonster = GetData(pMonList);

					if(!(pTmpMonster->m_nFeature & (FE_DONT_TOUCH|FE_DONT_HAVE_DOWN)))
					{
						for(InitList(pMonList);NotEndList(pMonList);MoveNext(pMonList))
						{
							if(GetData(pMonList) != pTmpMonster)
							{
								Contact_Body_Check(pTmpMonster->pMonAsIns, GetData(pMonList)->pMonAsIns,10,10,false);//Ãæµ¹½Ã ÁÂÇ¥º¸Á¤
							}
						}
					}

					pMonList->RestoreCurrentState();
				}
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////




			//	¸Ê¿¡ ´ëÇÑ Ãæµ¹Ã¼Å©
			for(InitList(pField->pDontgoRect);NotEndList(pField->pDontgoRect);MoveNext(pField->pDontgoRect))
			{
				Contact_Map_Check(hero->_ins_Hero, 10,
					GetData(pField->pDontgoRect)->sx,  GetData(pField->pDontgoRect)->sy,
					GetData(pField->pDontgoRect)->dx,  GetData(pField->pDontgoRect)->dy, true);
			}

			//	NPC
			for(InitList(pField->pKeyInputEvt);NotEndList(pField->pKeyInputEvt);MoveNext(pField->pKeyInputEvt))
			{
				switch( GetData(pField->pKeyInputEvt)->m_nType )
				{
					case EVT_NPC:
					//-------------------------------------------------------
					{
						Npc* tmp = (Npc*)GetData(pField->pKeyInputEvt);
						Contact_Body_Check(hero->_ins_Hero, tmp->m_Asins, 10, 10, true);//Ãæµ¹½Ã ÁÂÇ¥º¸Á¤
						break;
					}
				}
			}

			int Hero_XY = Area_Check(hero->_ins_Hero,x_max);


			if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act){
				if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[Character::s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 11){//¿¹¿Ü½ºÅ³
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][1]->m_posX = hero->_ins_Skill[hero->s_HeroTag.SEX][hero->s_Skill_Set[hero->s_HeroTag.SEX].Num][0]->m_posX = hero->_ins_Hero->m_posX;
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][1]->m_posY = hero->_ins_Skill[hero->s_HeroTag.SEX][hero->s_Skill_Set[hero->s_HeroTag.SEX].Num][0]->m_posY = hero->_ins_Hero->m_posY; 
				}else{
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][1]->m_posX += (Hero_XY%100000);
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][0]->m_posX += (Hero_XY%100000);
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][1]->m_posY += (Hero_XY/100000);
					hero->_ins_Skill[Character::s_HeroTag.SEX][hero->s_Skill_Set[Character::s_HeroTag.SEX].Num][0]->m_posY += (Hero_XY/100000);
				}
			}


			if(SUTIL_SOUND_GetState() == -1){//ÄðÅ¸ÀÓÀÌ Áö³­µÚ¿¡ BGMÃâ·Â
				if(m_BGM_Cooltime >SOUND_COOLTIME){
					//m_BGM_Cooltime=0; SUTIL_Sound_Play(BGM_TEST_A,true);
				}else{
					m_BGM_Cooltime ++;
				}
			}else{
				m_BGM_Cooltime=0;
			}

			//	ÇöÀç ¸ó½ºÅÍÀÇ °¹¼ö¸¦ ÆÄ¾ÇÇØµÐ´Ù. (¸ó½ºÅÍ ¼ÒÈ¯ °¹¼ö Á¶Àý¿¡ ¾²ÀÓ)
			Monster::m_nTotalMonCnt = GetNodeCount(pMonList);
}


//--------------------------------------------------------------------------
void GFieldBattle::Paint_ChangeScrollEvent(int type)
//--------------------------------------------------------------------------
{
	switch(type)
	{
	case 0:
		{
			_SUTIL->g->blandBlur(); 
			break;
		}
	case 1:
		{
			_SUTIL->g->blandBlur(); 
			break;
		}
	}
}


//--------------------------------------------------------------------------
void GFieldBattle::Paint()
//--------------------------------------------------------------------------
{
	if(b_WorldMap){//¿ùµå¸Ê ±×¸®±â
		
		pWorldMapUi->Paint();
		if(pWorldMapUi->b_ViewWorldMap == false){//¿ùµå¸Ê Ã¢ÀÌ ´ÝÈ÷¸é
			b_WorldMap = false;
			SAFE_DELETE(pWorldMapUi);
		}
		return;
	}

	if(PaintPrologue())	{return;}

	m_nLodingtime = (m_nLodingtime+1)%3;

	if(0 < m_nFadeOutTime)
	{
		m_nFadeOutTime--;
		Paint_ChangeScrollEvent(0);


		PAINT_LODING();
		//		SUTIL_SetColor(0xff0000);
		//		SUTIL_FillRect(30*m_nLodingtime,20,10,10);

		return;
	}

	//	SUTIL_SetColor(0xff0000);
	//	SUTIL_FillRect(30*m_nLodingtime,20,10,10);

	PAINT_LODING();

	if(isHoldingPaint)	{return;}

	//	SUTIL_SetColor(0x000000);
	//	SUTIL_FillRect(0,0,240,320);
	//SUTIL_PaintAsprite(__ins_Hero);

	//	ÁÖÀÎ°ø

/*
	if(1)
	{
		pMinimap->PaintMiniMap();
		//return;
	}
*/

	if(true == pCinema->m_IsPlayCinema)
	{
		pCinema->Paint_Cinematics();

		//	È­¸éÀ» °»½Å½ÃÄÑÁØ´Ù.
		SUTIL_UpdateSprite();

		if(pFieldUi->s_TalkBox.View){//´ëÈ­Ã¢ÀÌ¶ã¶§
			pFieldUi->PaintTalkBox();
		}

		pPopupUi->PaintMessage();//ÀÌº¥Æ®°¡ ºÎ¿©µÇ¾úÀ»¶§

		//¾ÆÀÌÅÛ ½Àµæ ¸®½ºÆ®
		pPopupUi->PaintItemList();

		//	È­¸é ÀüÈ¯½Ã ÀÚ¿¬½º·´°Ô ¿òÁ÷¿©ÁØ´Ù.
		if(0 < m_nFadeInTime)
		{
			m_nFadeInTime--;

			for(int loop = 0; loop < (m_nFadeInTime); loop++)
			{
				Paint_ChangeScrollEvent(1);
			}
		}

#ifdef LOOK_Debug
		PaintDebug();
#endif

		return;
	}
	//hero->Paint();SUTIL_UpdateSprite();return;

	Paint_Exception_Check();//±×¸®±â¿¡ ´ëÇØ¼­ ¸î°¡Áö Æ¯¼öÇÑ »óÈ²À» Ã³¸®ÇÑ´Ù
	//	¹è°æ
	pField->Paint();

//	if(BOSS_STAND_FACESIDE != BossMon5_1::m_nBossStep)
//	{
		pField->MiddlePaint();
//	}


	//	ÇÊµåÀÇ ÀÛÀº ¸ÊÈ­¸éÀÌ¶ó¸é ¸®ÅÏ½ÃÅ²´Ù.
	if(1000 <= pField->m_nSaveStageNum)
	{
		//	È­¸é ÀüÈ¯½Ã ÀÚ¿¬½º·´°Ô ¿òÁ÷¿©ÁØ´Ù.
		if(0 < m_nFadeInTime)
		{
			m_nFadeInTime--;

			for(int loop = 0; loop < (m_nFadeInTime); loop++)
			{
				Paint_ChangeScrollEvent(1);
			}
		}
		return;
	}

	if(!(Exception_Num & PAINT_HERO_NOT)){
		hero->Paint();
	}

	//	¸ó½ºÅÍ
	if(!(Exception_Num & PAINT_MON_NOT)){
		MoveHead(pMonList);
		MoveNext(pMonList);
		while(NotEndList(pMonList))
		{
			GetData(pMonList)->Paint();
			MoveNext(pMonList);
		}


		//	¸ó½ºÅÍ ½ºÅ³
		MoveHead(pMonSkillList);
		MoveNext(pMonSkillList);
		while(NotEndList(pMonSkillList))
		{
			if(1 > GetData(pMonSkillList)->Delay)
			{
				SUTIL_PaintAsprite(GetData(pMonSkillList)->pMonSkillAsIns,S_INCLUDE_SORT);
			}
			MoveNext(pMonSkillList);
		}
	}

	//	ÇÊµå¸¦ ³ª´©¾î¼­ ºÎ¸¥´Ù.(boss5 ¿¹¿ÜÃ³¸®)
//	if(BOSS_STAND_FACESIDE == BossMon5_1::m_nBossStep)
//	{
//		pField->MiddlePaint();
//	}
	

	SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
	pObjectMgr->Paint();

	//±×¸®±â °»½Å
	SUTIL_UpdateSprite();

	if(!(Exception_Num & PAINT_FIELD_FRONT_NOT)){
		//	¹è°æ2 ÁÖÀÎ°ø ¾ÕºÎºÐ À§Ä¡

		pField->FrontPaint();
	}


	//	ÇÊµå UI ( ±×¸®±â°¡ ³¡³­ÈÄ À§¿¡ µ¤¾îÁØ´Ù.)
	pFieldUi->Paint();

	pFieldUi->PaintCharInfo(hero->s_Status[hero->s_HeroTag.SEX].LEVEL,
		hero->s_Status[hero->s_HeroTag.SEX].LIFE,
		hero->s_Status[hero->s_HeroTag.SEX].LIFE_MAX,
		hero->s_Status[hero->s_HeroTag.SEX].MANA,
		hero->s_Status[hero->s_HeroTag.SEX].MANA_MAX,
		hero->s_HeroTag.SEX /*hero->s_Status[hero->s_HeroTag.SEX].ELEMENTAL*/ );

	pFieldUi->PaintComboGage(5);//ÄÞº¸°ÔÀÌÁö
	

	//	¹Ì´Ï¸Ê ÀÓ½Ã
	//PaintMiniMap();

	//¾ÆÀÌÅÛ ½Àµæ ¸®½ºÆ®
	pPopupUi->PaintItemList();

	//pFieldUi->SetTalkCinema(0);
	if(pFieldUi->s_TalkBox.View){//´ëÈ­Ã¢ÀÌ¶ã¶§
		pFieldUi->PaintTalkBox();
	}else{
		pFieldUi->PaintSkillInfo(&(hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[0]),
			&(hero->s_Skill_Set[hero->s_HeroTag.SEX].Cool_TimeMax[0]),
			&(hero->s_Skill_Set[hero->s_HeroTag.SEX].Cool_TimeNow[0]),
			hero->s_Status[hero->s_HeroTag.SEX].MANA,
			&(hero->s_Skill_Set[hero->s_HeroTag.SEX].Need_Mana[0]));

		
		for(int sex = 0;sex<2;sex++){
			for(int xx = 0;xx<3;xx++){//ÄðÅ¸ÀÓ °¨¼Ò
				if(hero->s_Skill_Set[sex].Cool_TimeNow[xx]>0)hero->s_Skill_Set[sex].Cool_TimeNow[xx]--;
			}
		}
		

		pFieldUi->PaintExpInfo(hero->s_Status[hero->s_HeroTag.SEX].EXP,
			hero->s_Status[hero->s_HeroTag.SEX].EXP_MAX);

		pFieldUi->PaintPotionTagInfo(&(hero->s_Potion_Tag.Cool_TimeMax[0]),
			&(hero->s_Potion_Tag.Cool_TimeNow[0]));

	}


	if(b_PopupUi){//CLR ÆË¾÷ÀÌ ¶ã¶§ 
		_SUTIL->g->blandBlur(); 
		pPopupUi->Paint();//
	}

	pPopupUi->PaintAreaMessage();//Áö¿ª¸íÀ» Ç¥½ÃÇÒ¶§
	pPopupUi->PaintMessage();//°¡¹æ °ø°£ºÎÁ·ÇÒ¶§


	//	È­¸é ÀüÈ¯½Ã ÀÚ¿¬½º·´°Ô ¿òÁ÷¿©ÁØ´Ù.
	if(0 < m_nFadeInTime)
	{
		m_nFadeInTime--;

		for(int loop = 0; loop < (m_nFadeInTime); loop++)
		{
			Paint_ChangeScrollEvent(1);
		}
	}


#ifdef LOOK_Debug
	PaintDebug();
#endif
}


#ifdef LOOK_Debug
void GFieldBattle::PaintDebug()
//--------------------------------------------------------------------------
{
	///////////////////°¢Á¾ °ÔÀÓ »óÅÂ Ãâ·ÂºÎ//////////////////////
	///////////////////°¢Á¾ °ÔÀÓ »óÅÂ Ãâ·ÂºÎ//////////////////////
	///////////////////°¢Á¾ °ÔÀÓ »óÅÂ Ãâ·ÂºÎ//////////////////////
#define X_POSITION 150
#define Y_POSITION 60

#ifdef LOOK_USE_MEMORY
	char str[30] ; 
	int h = Y_POSITION+10;
	int a = 0;
	_SUTIL->g->SetColor( 0xffffff );
	a = MC_knlGetTotalMemory();
	_SUTIL->g->DrawRect(X_POSITION+0, h+0, a/(100*1024), 5);

	_SUTIL->g->SetColor( 0xff0000 );
	a = MC_knlGetTotalMemory() - MC_knlGetFreeMemory();
	_SUTIL->g->FillRect(X_POSITION+1, h+1, a/(100*1024), 4);

	_SUTIL->g->SetColor( 0x00ff00 );
	//a = MC_knlGetFreeMemory();
	//g->FillRect(1, 1, a/(100*1024), 2);
	_SUTIL->g->FillRect(X_POSITION+33, h+2, 1, 2);

	_SUTIL->g->SetColor( 0xFFffFF );
	_SUTIL->g->FillRect(X_POSITION+10, h+6, 1, 1);
	_SUTIL->g->FillRect(X_POSITION+20, h+6, 1, 1);
	_SUTIL->g->FillRect(X_POSITION+30, h+6, 1, 1);
	_SUTIL->g->FillRect(X_POSITION+40, h+6, 1, 1);
	_SUTIL->g->FillRect(X_POSITION+50, h+6, 1, 2);


	_SUTIL->pFont->setColor(0xff0000);
	_SUTIL->pFont->setOutline(true);
	_SUTIL->pFont->setOutlineColor(0x000000);

	SPRINTF(str, "USE_M : %d", a);
	_SUTIL->pFont->DrawText(_SUTIL->g, str,X_POSITION+ 0 , Y_POSITION, 0);
	_SUTIL->pFont->setColor(0x00FF00); 
	_SUTIL->pFont->DrawText(_SUTIL->g, ".",X_POSITION+ 66 , Y_POSITION-8 , 0); 
	_SUTIL->pFont->DrawText(_SUTIL->g, ".",X_POSITION+ 51 , Y_POSITION-8 , 0); 
#endif

#ifdef LOOK_FRM_PER_SEC
	long TimeNow = MC_knlCurrentTime();
	int tempTime = 10000 / ((TimeNow+1) - TimeLast);
	TimeLast = MC_knlCurrentTime();

	_SUTIL->pFont->setColor(0xff7777); 

	SPRINTF(str, "frm^2/^0sec : %d.%d", tempTime/10,tempTime%10); 
	_SUTIL->pFont->DrawText(_SUTIL->g, str,X_POSITION+ 0, Y_POSITION+20, 0);

	MEMSET(str, 0x00, 30);
	SPRINTF(str, "stage : %d", pMinimap->m_CurMapSector->m_nSectorIdx); 
	_SUTIL->pFont->DrawText(_SUTIL->g, str,X_POSITION+ 0, Y_POSITION+30, 0);

	MEMSET(str, 0x00, 30);
	SPRINTF(str, "MCpos : %d.%d", m_CharInfo->m_nPos.x ,m_CharInfo->m_nPos.y); 
	_SUTIL->pFont->DrawText(_SUTIL->g, str,X_POSITION+ 0, Y_POSITION+40, 0);
#endif


	//////////////////////////////////////////////////////////////////
	//	MoveHead(_SUTIL->pDrawList);
	//	MoveNext(_SUTIL->pDrawList);
	//	while(NotEndList(_SUTIL->pDrawList))
	//	{
	//		if(NULL  ==  GetData(_SUTIL->pDrawList)->m_rect)
	//		{
	//			int a = 0;
	//		}
	//		MoveNext(_SUTIL->pDrawList);
	//	}
	//
	//////////////////////////////////////////////////////////////////


#ifdef LOOK_EVENT_RECT
	_SUTIL->g->DrawRect(hero->s_Event_Rect.X1-pField->m_nSrcCamAngle_X,hero->s_Event_Rect.Y1,
		hero->s_Event_Rect.W,hero->s_Event_Rect.H);

	/////////////////////////////////////////////////////////////////
	for(InitList(pField->pEvtWayList);NotEndList(pField->pEvtWayList);MoveNext(pField->pEvtWayList))
	{
		_SUTIL->g->DrawRect(GetData(pField->pEvtWayList)->sx-pField->m_nSrcCamAngle_X, GetData(pField->pEvtWayList)->sy,
			GetData(pField->pEvtWayList)->dx-GetData(pField->pEvtWayList)->sx,
			GetData(pField->pEvtWayList)->dy-GetData(pField->pEvtWayList)->sy);
	}
	/////////////////////////////////////////////////////////////////

#endif

#ifdef	LOOK_DONT_GO_RECT
	_SUTIL->g->SetColor( 0x00ff00 );
	for(InitList(pField->pDontgoRect);NotEndList(pField->pDontgoRect);MoveNext(pField->pDontgoRect))
	{

		_SUTIL->g->DrawRect(GetData(pField->pDontgoRect)->sx - pField->m_nSrcCamAngle_X,
			GetData(pField->pDontgoRect)->sy,
			GetData(pField->pDontgoRect)->dx,
			GetData(pField->pDontgoRect)->dy);
	}

#endif
	//	TEST
	//	_SUTIL->pFont->setOutline(TRUE);
	//	if(10001 == pField->m_nSaveStageNum || 10000 == pField->m_nSaveStageNum || 10002 == pField->m_nSaveStageNum)
	//	{
	//		_SUTIL->pFont->setColor(0xFFFFFF);
	//		_SUTIL->pFont->setOutlineColor(0x000000);
	//		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"SMALL TOWN", 10, 45, 0);//Text
	//	}
	//	
	//	if(10003 == pField->m_nSaveStageNum || 10004 == pField->m_nSaveStageNum || 10005 == pField->m_nSaveStageNum)
	//	{
	//		_SUTIL->pFont->setColor(0xFFFFFF);
	//		_SUTIL->pFont->setOutlineColor(0x000000);
	//		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"MIDDLE TOWN", 10, 45, 0);//Text
	//	}
	//	_SUTIL->pFont->setOutline(FALSE);
}
#endif

void GFieldBattle::GetHomingXY(Homing* p_Homing){

	int Xx = 0 , Yy = 0 , Cc = 0;//Áß°£ÁÂÇ¥
	int CitaTemp = 0;

	p_Homing->Cita2 = GetAngle(p_Homing->X2 - p_Homing->X1, p_Homing->Y2 - p_Homing->Y1);//ÇöÀç°¢µµ ±¸ÇÏ±â
	if(ABS(p_Homing->Cita1 - p_Homing->Cita2) >180){//µÐ°¢ÀÏ °æ¿ì ÀÛÀº°¢¿¡ 360µµ¸¦ ´õÇØ¼­ Æò±Õ°ªÀ» ±¸ÇÒ¼öÀÖ°ÔÇÑ´Ù
		if(p_Homing->Cita1 < p_Homing->Cita2)
			p_Homing->Cita1+=360;
		else
			p_Homing->Cita2+=360;

		//	CitaTemp = (p_Homing->Cita1 + p_Homing->Cita2)/2;
		//}else{//µÐ°¢Àº 180µµ ¹Ý´ëÂÊ °¢À» Ã¼Å©ÇØ¾ßÇÑ´Ù
		//	CitaTemp = ((p_Homing->Cita1 + p_Homing->Cita2)/2 +180 )%360;
	}
	CitaTemp = (p_Homing->Cita1+p_Homing->Cita2)/2;

	if(p_Homing->TurnCita < ABS(p_Homing->Cita1 - CitaTemp)){//ÃÖ´ë ÅÏ °¢µµ º¸´Ù ¸¹ÀÌ ÈÖ¾îÁö¸é º¸Á¤ÇÑ´Ù
		if(p_Homing->Cita1 > CitaTemp)
			p_Homing->Cita1-=p_Homing->TurnCita;
		else
			p_Homing->Cita1+=p_Homing->TurnCita;

	}else{
		p_Homing->Cita1 = CitaTemp;
	}

	p_Homing->Cita1 = p_Homing->Cita1%360;

	p_Homing->X1 = p_Homing->X1 + p_Homing->R*SIN(p_Homing->Cita1)/1000;
	p_Homing->Y1 = p_Homing->Y1 + p_Homing->R*(-COS(p_Homing->Cita1))/1000; 

}

int GFieldBattle::GetAngle(int rx,int ry){
	if(rx==0) return(ry<0?0:180);
	if(ry==0) return(rx<0?270:90);

	int X = 0, Y = 0, AddAngle =0;
	if (rx > 0){
		if (ry > 0){
			//2»çºÐ¸é
			X = rx;
			Y = ry;
			AddAngle = 90;
		}else{
			//1»çºÐ¸é
			X = -ry;
			Y = rx;
			AddAngle = 0;
		}
	}else{
		if (ry > 0){
			//3»çºÐ¸é
			X = ry;
			Y = -rx;
			AddAngle = 180;
		}else{
			//4»çºÐ¸é
			X = -rx;
			Y = -ry;
			AddAngle = 270;
		}
	}


	//2»çºÐ¸é ±âÁØ
	if (X > Y){//ºÐ¸ð°¡ Å©´Ù¸é
		int dig = (Y*1000)/X;
		for(int i = 0 , h = 0,h2 =2000 ; i<=45 ;i++){
			h = dig - TAN(i);
			//h = ABS(h);
			if(h<=0)
				return AddAngle+i;
		}
	}else{//ºÐÀÚ°¡ Å©´Ù¸é 90µµ¿¡¼­ ¿ªÁÂÇ¥
		int dig = (X*1000)/Y;
		for(int i = 0 , h = 0,h2 =2000 ; i<=45 ;i++){
			h = dig - TAN(i);
			//h = ABS(h);
			if(h<=0)
				return AddAngle + 90 - i;
		}


	}

	return 0;
}




void GFieldBattle::drawOverlab()
{
	if( overlabCnt == OVERLAB_STOP)
		return; 
	int screenArea = SCREEN_WIDTH*SCREEN_HEIGHT; 
	short* backBuf = (short*)_SUTIL->g->m_image->GetPixelData(); 

	if( copyBackBuf == NULL)
	{
		copyBackBuf = (short*)MALLOC(sizeof(short)*screenArea); 
		memcpy(copyBackBuf, backBuf, sizeof(short)*screenArea);
		overlabCnt = 0; 
	}

	overlabCnt+=1; 
	int overlabCntRevers = OVERLAB_BLAND_MAX - overlabCnt;
	if( overlabCnt > OVERLAB_BLAND_MAX)
	{	overlabCnt = OVERLAB_STOP; 
	SAFE_DEL(copyBackBuf);
	return; 
	}

	for( int i =0; i< screenArea; i++)
	{	 *(backBuf+i) = ((((*(backBuf+i)&0xF81f)*overlabCnt + (*(copyBackBuf+i)&0xF81f)*overlabCntRevers)>> OVERLAB_BLAND_MOVE_BIT) & 0xF81f) 
	| ((((*(backBuf+i)&0x7E0)*overlabCnt + (*(copyBackBuf+i)&0x7E0)*overlabCntRevers) >> OVERLAB_BLAND_MOVE_BIT) & 0x7E0);
	}
}

void GFieldBattle::setGamma(int gammaCase)
{	
	int screenArea = SCREEN_WIDTH*SCREEN_HEIGHT; 
	short* backBuf = (short*)_SUTIL->g->m_image->GetPixelData(); 

	short xorBit[] = 
	{
		0xffff,	//all revers
		0xF800,	//R		red
		0x7E0,  //G		green
		0x1F,   //B		blue
		0xF81f,	//RB	pink
		0xFFE0,	//RG	yellow
		0x7FF,  //GB	aqua
	}; 

	for( int i =0; i< screenArea; i++)
		*(backBuf+i) = xorBit[gammaCase]^(*(backBuf+i));

}
//--------------------------------------------------------------------------
void GFieldBattle::KeyEvent(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{
	if(b_WorldMap){
		pWorldMapUi->KeyEvent(m_keyCode, m_keyRepeat);
		return;
	}

	if(isHoldingKey)	{return;}

//	if(true == pMinimap->KeyEvent(m_keyCode, m_keyRepeat))	{return;}
	

	if(true == pField->KeyEvent(m_keyCode, m_keyRepeat))	{return;}

	///////////////////////////////////°ÔÀÓÁß ÅØ½ºÆ®Ã¢ È£Ãâ///////////////////////////////////////
	if(pFieldUi->s_TalkBox.View){//s_TalkBox°¡ ¶ã¶§ 
		pFieldUi->KeyTalkBox(m_keyCode, m_keyRepeat);
		hero->KeyEvent(0,0);//ÄÉ¸¯ÅÍÀÇ Çàµ¿À» Á¤Áö½ÃÄÑÁÖ±âÀ§ÇÑ ¿ëµµ
		return;
	}
	///////////////////////////////////°ÔÀÓÁß ÅØ½ºÆ®Ã¢ È£Ãâ///////////////////////////////////////

	//	¾¾³×¸¶ÁßÀÌ¸é ¸®ÅÏ
	if(true == pCinema->m_IsPlayCinema)	{return;}

	///////////////////////////////////°ÔÀÓÁß ÆË¾÷ È£Ãâ///////////////////////////////////////
	if(m_keyCode == MH_KEY_CLEAR && !m_keyRepeat && !b_PopupUi){
		if(hero->_move_Order == HERO_STOP){

			b_PopupUi = true;
			pPopupUi->s_Page.Woman_Man = hero->s_HeroTag.SEX;//ÇöÀç ¼±ÅÃµÈ ¼ºº°À» ¹Ý¿µÇÑ´Ù
			if(hero->s_Knife_Eff[3].act)hero->s_Knife_Eff[3].LVup_ActionEnd = true;//°Ë¹öÇÁ´Â²À ÇØÁöÇØ¾ßÇÑ´Ù
		}
	}else if(b_PopupUi){
		b_PopupUi = pPopupUi->KeyEvent(m_keyCode, m_keyRepeat);

		if(!b_PopupUi){//ÆË¾÷Ã¢ÀÌ ´ÝÈú¶§
			if(pPopupUi->SkillChange_A){
				hero->Init_Skill();
				pPopupUi->SkillChange_A=false;
			}
		}
	}else
		///////////////////////////////////°ÔÀÓÁß ÆË¾÷ È£Ãâ///////////////////////////////////////


	{

		switch(m_keyCode)
		{
		case MH_KEY_5:
		case MH_KEY_SELECT:
			{
				//	ÀÌº¥Æ®¿¡¼­ Å°¿¡ °ü·ÃµÈ ÀÏÀº ÀÌ°÷¿¡¼­ Ã³¸®

				//	ÀÌº¥Æ®°¡ ÀÏ¾î³ª¸é ±×³É Å°¸¦ ³¡³½´Ù.
				if(!m_keyRepeat)
				{
					if(KeyEventProcess())	{return;}
				}

				//ItemBag tmpBag = pField->CheckDropItem(m_CharInfo->m_nPos.x, m_CharInfo->m_nPos.y);
				ItemBag* tmpBag = pField->CheckDropItem(hero->_ins_Hero->m_posX,
					hero->_ins_Hero->m_posY);

				if(tmpBag){
					if(0 != tmpBag->ITEM_KIND)
					{
						if(true == pPopupUi->GET_item(tmpBag))
						{
							m_keyCode = 0;
							if(tmpBag->ITEM_ID>=8000){//¾ÆÀÌÅÛ ÀÌº¥Æ® È£Ãâ
								ADD_EVENT_MSG(EVT_GAME_KEYEVENT, 40, tmpBag->ITEM_ID);//Analysis_Event , CheckEvent
							}
							pField->DeleteNowItem();
						}else{
							pPopupUi->AddMessage(CLRMENU_Q5);
						}
					}
				}

				break;
			}
		case MH_KEY_SEND:
			{
				//Resv_ChangeStage(101);

				//SetEvent(4,0);
				//pField->m_nSrcCamAngle_X -= 3;
				//pMonList->CurNode()->ResvAction(MON_ATK_FIREBALL);

				//if(false == pCinema->s_cinematicsPause)
				//{
				//	pCinema->s_cinematicsPause = true;
				//}
				//else
				//{
				//	pCinema->s_cinematicsPause = false;
				//}
				//ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
				//ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 100);
//				GET_MAINQUEST_IDX() = MAIN_QUEST_openDoor;

//				if(ischeck)
//				{
//					ischeck = false;
//				}
//				else
//				{
//					ischeck = true;
//				}

				//					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 100);



				//					LoadPrologue(DATA_TALK_OPENING, 0);


				break;
			}
		case MH_KEY_SOFT1:
			//Resv_ChangeStage(100);
			//ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
			//ADD_EVENT_MSG(EVT_START_CINEMA, 10, 5);

			//				SET_EVENT(1);
			//				PARSER_EVENT();
			break;
		case MH_KEY_SOFT2:
			{
				//pFieldUi->SetTalkCinema(0,1);//´ë»çÃ¢ ¶ç¿ì±â
				/*INIT_EVENT();
				SET_EVENT(2);
				PARSER_EVENT();*/
				//					pFieldUi->SetTalkCinema(0);//´ë»çÃ¢ ¶ç¿ì±â
				//
				//					
				//
				//					MoveHead(pMonList);
				//					MoveNext(pMonList);
				//					while(NotEndList(pMonList))
				//					{
				//						GetData(pMonList)->RCV_Debuff(DEBUF_POISON );
				//						MoveNext(pMonList);
				//					}
				break;
			}

		case MH_KEY_SIDE_UP:
			SUTIL_SOUND_SetVol(SUTIL_SOUND_GetVol()+10);
			break;
		case MH_KEY_SIDE_DOWN:
			SUTIL_SOUND_SetVol(SUTIL_SOUND_GetVol()-10);
			break;

			//case MH_KEY_SIDE_UP:
			//	break;
			//case MH_KEY_SIDE_DOWN:
			//	break;
		}




		hero->KeyEvent(m_keyCode, m_keyRepeat);
		Throw_Check();// ÁÖÀÎ°øÀÇ Àâ±â


	}


}

bool GFieldBattle::Contact_Check(ASpriteInstance* p_Attacker,ASpriteInstance* p_Defender,int attGap,int defGap)
{//Ãæµ¹ Ã¼Å© ¸Þ¼Òµå - InstanceÁÂÇ¥¿¡ Asprite¤±ÁÂÇ¥ÀÇ "Flag °ª¿¡ µû¶ó" ÇÕ»êÇÑ´Ù, µû¶ó¼­ º°µµÀÇ °è»êÀÌ³ª Flag º¸Á¤ ÀüÃ³¸®´Â ÇÊ¿ä¾ø´Ù




	int att_Frame_Index = p_Attacker->GetAnimFrame();// Attacker ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù
	int def_Frame_Index = p_Defender->GetAnimFrame();// Defender ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù


	int aa = p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index+1] - p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index];
	int bb = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index+1] - p_Defender->m_sprite->_frames_rects_start[def_Frame_Index];

	if( aa < 2 || bb < 1) //¹«°á¼ºÃ¼Å© - ¾îÅÃÆÇÁ¤ÀÌ ¾ø°Å³ª || ¸Â´ÂÆÇÁ¤ÀÌ¾ø°Å³ª
		return false;//ÆÇÁ¤ÇÏÁö ¾Ê´Â´Ù - def_RectÀº 1¹øÂ°¿¡ ±â·ÏµÇ°í, att_Rect Àº 2¹øÂ°ºÎÅÍ ±â·ÏµÇ¾î ÀÖ´Ù, µÑÁßÇÏ³ª¶óµµ ¾ø´Ù¸é F¸®ÅÏ


	//if( RECT_NUM(p_Attacker, att_Frame_Index) < 2 || RECT_NUM(p_Defender, def_Frame_Index) < 1) //¹«°á¼ºÃ¼Å© - ¾îÅÃÆÇÁ¤ÀÌ ¾ø°Å³ª || ¸Â´ÂÆÇÁ¤ÀÌ¾ø°Å³ª
	//	return false;//ÆÇÁ¤ÇÏÁö ¾Ê´Â´Ù - def_RectÀº 1¹øÂ°¿¡ ±â·ÏµÇ°í, att_Rect Àº 2¹øÂ°ºÎÅÍ ±â·ÏµÇ¾î ÀÖ´Ù, µÑÁßÇÏ³ª¶óµµ ¾ø´Ù¸é F¸®ÅÏ
	//
	short X_a, Y_a, X_d, Y_d;//Ãæµ¹¿µ¿ª XYWH
	byte W_a, H_a, W_d, H_d;//Ãæµ¹¿µ¿ª XYWH



	int att_Rect_Index = (p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index]+1)*4;// Attacker ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	int def_Rect_Index = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index]*4;// Defender ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º


	if(attGap==0){//attGap·Î °ªÀÌ ³Ñ¾î¿Â°Ô ¾ø´Ù¸é »õ·Î °ªÀ» °¡Á®¿Í¼­ ÆÇ´ÜÇÑ´Ù
		switch(WH(p_Attacker, att_Rect_Index+2)){
			case 0:attGap = 14;break;
			case 1:attGap = 24;break;
			case 2:attGap = 8;break;
			case 3:attGap = 36;break;
			case 4:attGap = 46;break;
			case 5:attGap = 68;break;
			case 6:attGap = 250;break;
		}
	}
	if(	(p_Attacker->m_posY +attGap/2	<	p_Defender->m_posY -defGap/2	) || 
		(p_Attacker->m_posY -attGap/2	>	p_Defender->m_posY +defGap/2	) )
		return false;//ÆÇÁ¤ÇÏÁö ¾Ê´Â´Ù - Y°ªÀÌ °ãÄ¡Áö ¾ÊÀ¸¹Ç·Î


	short ac_X_Att = p_Attacker->m_posX;						//Absolute coordinates 
	short ac_Y_Att = p_Attacker->m_posZ;					//Absolute coordinates 
	short ac_X_Def = p_Defender->m_posX;						//Absolute coordinates 
	short ac_Y_Def = p_Defender->m_posZ;					//Absolute coordinates 



	X_d =XY(p_Defender, def_Rect_Index  );
	Y_d =XY(p_Defender, def_Rect_Index+1);
	W_d =WH(p_Defender, def_Rect_Index+2);
	H_d =WH(p_Defender, def_Rect_Index+3);
	if(p_Defender->m_stopFlag & FLAG_FLIP_X) X_d = -(X_d+W_d);// ¼öºñ ¾Ö´Ï ¹ÝÀüÀÌ¸é

	for(int xx = 0 ; xx <= (RECT_NUM(p_Attacker, att_Frame_Index)-2) ; xx++ , att_Rect_Index+=4){//°ø°ÝÃøÀº Rect°¡ 1°³ ÀÌ»óÀÏ ¼ö µµ ÀÖ´Ù - (RECT_NUM(p_Attacker, att_Frame_Index)-2):°ø°ÝÃø Ãæµ¹¿µ¿ª °¹¼ö

		if(xx==0){//xÃæ°Ý·®,zÃæ°Ý·® ÀúÀåÇÏ±â - Ãæµ¹¿µ¿ªÀÇ 2¹øÂ° Rect´Â Á¤º¸°ªÀ» ÀúÀåÇÑ´Ù
			//xÃæ°Ý·® - ¸Â´Â´ë»óÀÌ +ÀÏ¶§´Â ¹Ð·Á³ª°¡°í -ÀÏ¶§´Â ´ç°Ü¿Â´Ù ´Ü, ÁÖÀÎ°øÀÇ µÚ¿¡ ¸ó½ºÅÍ°¡ ÀÖ´Ù¸é ºÎÈ£´Â ¹Ý´ë·Î Àâ¾ÆÁØ´Ù
			s_Contact.x =		XY(p_Attacker, att_Rect_Index  );
			s_Contact.z =		XY(p_Attacker, att_Rect_Index+1);
			s_Contact.D_index = WH(p_Attacker, att_Rect_Index+3);

			//¡Ù¡Ù¡Ù°ø°ÝÀÚ  Àý´ëÁÂÇ¥¿Í ¼öºñÀÚ  Àý´ëÁÂÇ¥¸¦ ºñ±³ÇÏ¿© X¹æÇâÀ» µÚÁý´Â´Ù 
			//¡Ù¡Ù¡Ù°ø°ÝÀÚ°¡ º¸´Â ¹æÇâÀº µûÁöÁö ¾Ê´Â´Ù

			


			switch(s_Contact.D_index){
				case 52:
				case 53:
				case 60:
				case 61:
				case 62:
				case 63:
				case 64:
				case 65:
				case 72:
				case 73:
					if(ac_X_Att > ac_X_Def)s_Contact.x = -s_Contact.x;// °ø°ÝÀÚ º¸´Ù ´õ µÚ¿¡ÀÖ´Â ÇÇ°ÝÀÚ´Â ¹°¸®X¹æÇâÀÌ ¹Ý´ë°¡ µÈ´Ù
					break;
				default:
					if(p_Attacker->m_flags)s_Contact.x = -s_Contact.x;// °ø°ÝÀÚ°¡ º¸´Â¹æÇâÀ¸·Î ¹«Á¶°Ç ¹Ð¸²
					break;
			}
			

		}else{

			/*X_a=XYWH(p_Attacker, att_Rect_Index  );
			Y_a=XYWH(p_Attacker, att_Rect_Index+1);
			W_a=XYWH(p_Attacker, att_Rect_Index+2);
			H_a=XYWH(p_Attacker, att_Rect_Index+3);*/

			X_a=p_Attacker->m_sprite->_frames_rects[att_Rect_Index];
			Y_a=p_Attacker->m_sprite->_frames_rects[att_Rect_Index+1];
			W_a=(byte)p_Attacker->m_sprite->_frames_rects[att_Rect_Index+2];
			H_a=(byte)p_Attacker->m_sprite->_frames_rects[att_Rect_Index+3];

			if(p_Attacker->m_stopFlag & FLAG_FLIP_X) X_a = -(X_a+W_a);// °ø°Ý ¾Ö´Ï ¹ÝÀüÀÌ¸é
			if(Y_a ==0){
				int zz = true;
			}	


			if(
				(ac_X_Att+ X_a+W_a	> ac_X_Def+ X_d		) && 
				(ac_X_Att+ X_a		< ac_X_Def+ X_d+W_d	) && 
				(ac_Y_Att+ Y_a+H_a	> ac_Y_Def+ Y_d		) && 
				(ac_Y_Att+ Y_a		< ac_Y_Def+ Y_d+H_d	) ){//Ãæµ¹ÆÇ´Ü °ø½Ä

					s_Contact.crash_x=(MAX(ac_X_Att+ X_a, ac_X_Def+ X_d) + MIN(ac_X_Att+ X_a+W_a, ac_X_Def+ X_d+W_d))>>1;//XÃæ°Ý ÀÌÆåÆ® ÁöÁ¡ 
					s_Contact.crash_z=(MAX(ac_Y_Att+ Y_a, ac_Y_Def+ Y_d) + MIN(ac_Y_Att+ Y_a+H_a, ac_Y_Def+ Y_d+H_d))>>1;//ZÃæ°Ý ÀÌÆåÆ® ÁöÁ¡
					return true;//Ãæµ¹ ÆÇ´Ü
			}
		}
	}

	return false;
}



bool GFieldBattle::Contact_Body_Check(ASpriteInstance* p_Attacker,ASpriteInstance* p_Defender,int attGap,int defGap,boolean HERO)
{//Ãæµ¹ Ã¼Å© ¸Þ¼Òµå - InstanceÁÂÇ¥¿¡ AspriteÁÂÇ¥ÀÇ "Flag °ª¿¡ µû¶ó" ÇÕ»êÇÑ´Ù, µû¶ó¼­ º°µµÀÇ °è»êÀÌ³ª Flag º¸Á¤ ÀüÃ³¸®´Â ÇÊ¿ä¾ø´Ù

	//	Ãæµ¹Ã¼Å©°¡ ¾ø´Ù¸é ¸®ÅÏ
	if(!p_Attacker->m_sprite->_frames_rects_start)	{return false;}
	if(!p_Defender->m_sprite->_frames_rects_start)	{return false;}

	//¸öÅë°£ ¾ÈÀü°Å¸® -5ÇÈ¼¿ ÃßÈÄ±¸Çö ÀÌºÎºÐÀÌ ÀÛÀ¸¸é ÀÛÀ»¼ö·Ï Á¢±Ù´ë»ó¿¡ ´ëÇØ ¶ÕÀ» °¡´É¼ºÀÌ Ä¿Áø´Ù
	int Safe_range = 10;
	int tmpXZ[2];
	short X_a,W_a,	X_d,W_d;//Ãæ°ÝÃ¼¿Í ÇÇ°ÝÃ¼ÀÇ  XYWH

	//Ãæ°ÝÃ¼ ÀüÁÂÇ¥
	short Att_acX_before = p_Attacker->m_lastX;								//before Absolute coordinates 
	short Att_acY_before = p_Attacker->m_lastY;								//before Absolute coordinates 


	//Ãæ°ÝÃ¼ ÇöÁÂÇ¥
	short Att_acX = 0;
	short Att_acY = 0;
	int att_Frame_Index = 0;
	int att_Rect_Index = 0;
	if(0 == p_Attacker->m_nState)	//	¿¡´Ï¸ÞÀÌ¼Ç
	{
		p_Attacker->Get_AFrameXZ(&tmpXZ[0]);//ÀÌ¹ø¿¡ ±×·ÁÁú Ani ÀÇ x,z ÁÂÇ¥¸¦ ¾ò¾î¿Â´Ù
		Att_acX = tmpXZ[0] ;								//Absolute coordinates 
		Att_acY = p_Attacker->m_posY;				//Absolute coordinates 
		att_Frame_Index = p_Attacker->GetAnimFrame();// Attacker ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù
		att_Rect_Index = p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}
	else if(1 == p_Attacker->m_nState)	//	ÇÁ·¹ÀÓ
	{
		Att_acX = p_Attacker->m_posX;								//Absolute coordinates 
		Att_acY = p_Attacker->m_posY;				//Absolute coordinates 
		att_Frame_Index = p_Attacker->m_nCrtFrame;
		att_Rect_Index = p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}

	//ÇÇ°ÝÃ¼
	short Def_acX = 0;
	short Def_acY = 0;
	int def_Frame_Index = 0;
	int def_Rect_Index = 0;
	if(0 == p_Defender->m_nState)	//	¿¡´Ï¸ÞÀÌ¼Ç
	{
		p_Defender->Get_AFrameXZ(&tmpXZ[0]);//ÀÌ¹ø¿¡ ±×·ÁÁú Ani ÀÇ x,z ÁÂÇ¥¸¦ ¾ò¾î¿Â´Ù
		Def_acX = tmpXZ[0] ;								//Absolute coordinates 
		Def_acY = p_Defender->m_posY;				//Absolute coordinates 
		def_Frame_Index = p_Defender->GetAnimFrame();// Defender ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù	
		def_Rect_Index = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index]*4;// DefenderBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}
	else if(1 == p_Defender->m_nState)	//	ÇÁ·¹ÀÓ
	{
		Def_acX = p_Defender->m_posX;								//Absolute coordinates 
		Def_acY = p_Defender->m_posY;				//Absolute coordinates 
		def_Frame_Index = p_Defender->m_nCrtFrame;
		def_Rect_Index = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}

	//¡Ú.1////////////	ÇöÁÂÇ¥¿Í ÇÇ°ÝÃ¼ Áß¿¡ ÇÑÂÊÀÌ¶óµµ ¸öÅëÀÌ ¾ø´Ù¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	if( RECT_NUM(p_Attacker, att_Frame_Index) < 1 || RECT_NUM(p_Defender, def_Frame_Index) < 1) //¹«°á¼ºÃ¼Å© - ¾çÂÊÁß¿¡ ÇÑÂÊÀÌ¶óµµ ¸öÅëÀÌ ¾ø´Ù¸é
		return false;//ÆÇÁ¤ÇÏÁö ¾Ê´Â´Ù

	X_a =XY(p_Attacker, att_Rect_Index  );
	W_a =WH(p_Attacker, att_Rect_Index+2);
	if(p_Attacker->m_stopFlag & FLAG_FLIP_X) X_a = -(X_a+W_a);// °ø°Ý ¾Ö´Ï ¹ÝÀüÀÌ¸é

	X_d =XY(p_Defender, def_Rect_Index  );
	W_d =WH(p_Defender, def_Rect_Index+2);
	if(p_Defender->m_stopFlag & FLAG_FLIP_X) X_d = -(X_d+W_d);// ¼öºñ ¾Ö´Ï ¹ÝÀüÀÌ¸é


	//¡Ú.2////////////	ÀüÁÂÇ¥°¡ ¿µ¿ª ¾È¿¡ ÀÖ´Ù¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	if	((Att_acY_before +attGap/2	>	Def_acY -defGap/2	) && 
		(Att_acY_before -attGap/2		<	Def_acY +defGap/2	)){//Ãæ°ÝÃ¼ ÀüÁÂÇ¥¿Í ÇÇ°ÝÃ¼ÀÇ Y °ãÄ§

			if((Att_acX_before + (X_a+W_a)	>	Def_acX + (X_d) + Safe_range	) && 
				(Att_acX_before + (X_a) + Safe_range	<	Def_acX + (X_d+W_d)	)){
					return false;////ÀüÁÂÇ¥°¡ ÀÌ¹Ì °ãÃÄ ÀÖÀ»¶§´Â Ãæµ¹Ã¼Å©°¡ °¡µ¿ÇÏÁö ¾Ê´Â´Ù
			}

	}

	//¡Ú.3////////////	XÇÕ°è¿µ¿ª, YÇÕ°è¿µ¿ª ¾È¿¡ ÇÇ°ÝÃ¼°¡ Á¸ÀçÇÏÁö¾ÊÀ¸¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	if ((MIN(Att_acX_before+(X_a), Att_acX+(X_a))			>= Def_acX + (X_d+W_d)	)||
		(MAX(Att_acX_before+(X_a+W_a), Att_acX+(X_a+W_a))	<= Def_acX + (X_d)		)||
		(MIN(Att_acY_before-attGap/2, Att_acY-attGap/2)		>= Def_acY + attGap/2	)||
		(MAX(Att_acY_before+attGap/2, Att_acY+attGap/2)		<= Def_acY - attGap/2	))
		return false;//¾î´ÀÇÑÂÊÀÌ¶óµµ ¹þ¾î³ª¸é  Ãæµ¹Ã¼Å©°¡ °¡µ¿ÇÏÁö ¾Ê´Â´Ù




	int overX_Length = 0;
	if(HERO && Att_acX_before == Att_acX){
	}else
		if(Att_acX_before < Def_acX){//¡Ú¿ÞÂÊÀ¸·Î µÇµ¹¾Æ¿Ã °æ¿ì
			//if	(Att_acX	+ (X_a+W_a)	>	Def_acX +(X_d)		)//ÀÌµ¿ ÁÂÇ¥ »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ÀÖ´Ù.
			if(Att_acX_before < Att_acX)//¿À¸¥ÂÊÀ¸·Î ÀÌµ¿ÇÑ°ÍÀÌ ¸Â´Â°¡? - °ãÃÄÁö´Ù°¡ ¹þ¾î³­°æ¿ì °É¸±¼öµµ ÀÖÀ½
				overX_Length = - ((Att_acX	+ (X_a+W_a)) - (Def_acX + (X_d)));
		}else{//¡Ú¿À¸¥ÂÊÀ¸·Î µÇµ¹¾Æ¿Ã °æ¿ì
			//if	(Att_acX	+ (X_a)		<	Def_acX +(X_d+W_d)	)//ÀÌµ¿ ÁÂÇ¥ »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ÀÖ´Ù.
			if(Att_acX_before > Att_acX)//¿ÞÂÊÀ¸·Î ÀÌµ¿ÇÑ°ÍÀÌ ¸Â´Â°¡? - °ãÃÄÁö´Ù°¡ ¹þ¾î³­°æ¿ì °É¸±¼öµµ ÀÖÀ½
				overX_Length = + ((Def_acX +(X_d+W_d)) - (Att_acX + (X_a)));
		}

		int overY_Length = 0;
		if(HERO && Att_acY_before == Att_acY){
		}else
			if(Att_acY_before < Def_acY){//¡ÚÀ§·Î µÇµ¹¾Æ¿Ã °æ¿ì
				//if	(Att_acY	+ attGap/2	>	Def_acY - defGap/2	)//ÀÌµ¿ ÁÂÇ¥ »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ÀÖ´Ù.
				overY_Length = - ((Att_acY	+ attGap/2) - (Def_acY - defGap/2));

			}else{//¡Ú¾Æ·¡·Î µÇµ¹¾Æ¿Ã °æ¿ì
				//if	(Att_acY	- attGap/2	<	Def_acY + defGap/2	)//ÀÌµ¿ ÁÂÇ¥ »çÀÌ¿¡ Àå¾Ö¹°ÀÌ ÀÖ´Ù.
				overY_Length = + ((Def_acY + defGap/2) - (Att_acY - attGap/2));
			}


			if(HERO){
				if( abs(overX_Length) > 0 ){// yÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é x ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posX += overX_Length;
					return true;
				}
				if( abs(overY_Length) > 0 ){// yÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é x ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posY += overY_Length;
					return true;
				}
			}else{//¸ó½ºÅÍÀÇ °æ¿ì ¹è°æ°ú ºñ±³ÇÒ¶§ ¾²ÀÓ
				if( ABS(overX_Length) < ABS(overY_Length) ){// YÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é X ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posX += overX_Length;
					return true;
				}else{// YÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é X ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posY += overY_Length;
					return true;
				}
			}

			return true;
}



bool GFieldBattle::Contact_Map_Check(ASpriteInstance* p_Attacker,int attGap,int X,int Y,int W,int H, boolean HERO)
{//Ãæµ¹ Ã¼Å© ¸Þ¼Òµå - InstanceÁÂÇ¥¿¡ AspriteÁÂÇ¥ÀÇ "Flag °ª¿¡ µû¶ó" ÇÕ»êÇÑ´Ù, µû¶ó¼­ º°µµÀÇ °è»êÀÌ³ª Flag º¸Á¤ ÀüÃ³¸®´Â ÇÊ¿ä¾ø´Ù

	//	Ãæµ¹Ã¼Å©°¡ ¾ø´Ù¸é ¸®ÅÏ
	if(!p_Attacker->m_sprite->_frames_rects_start)	{return false;}

	//¸öÅë°£ ¾ÈÀü°Å¸® -5ÇÈ¼¿ ÃßÈÄ±¸Çö ÀÌºÎºÐÀÌ ÀÛÀ¸¸é ÀÛÀ»¼ö·Ï Á¢±Ù´ë»ó¿¡ ´ëÇØ ¶ÕÀ» °¡´É¼ºÀÌ Ä¿Áø´Ù
	int Safe_range = 10;
	int tmpXZ[2];
	short X_a,W_a,	X_d,W_d;//Ãæ°ÝÃ¼¿Í ÇÇ°ÝÃ¼ÀÇ  XYWH

	//Ãæ°ÝÃ¼ ÀüÁÂÇ¥
	short Att_acX_before = p_Attacker->m_lastX;								//before Absolute coordinates 
	short Att_acY_before = p_Attacker->m_lastY;								//before Absolute coordinates 

	//Ãæ°ÝÃ¼ ÇöÁÂÇ¥
	short Att_acX = 0;
	short Att_acY = 0;
	int att_Frame_Index = 0;
	int att_Rect_Index = 0;
	if(0 == p_Attacker->m_nState)	//	¿¡´Ï¸ÞÀÌ¼Ç
	{
		p_Attacker->Get_AFrameXZ(&tmpXZ[0]);//ÀÌ¹ø¿¡ ±×·ÁÁú Ani ÀÇ x,z ÁÂÇ¥¸¦ ¾ò¾î¿Â´Ù
		Att_acX = tmpXZ[0] ;								//Absolute coordinates 
		Att_acY = p_Attacker->m_posY;				//Absolute coordinates 
		att_Frame_Index = p_Attacker->GetAnimFrame();// Attacker ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù
		att_Rect_Index = p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}
	else if(1 == p_Attacker->m_nState)	//	ÇÁ·¹ÀÓ
	{
		Att_acX = p_Attacker->m_posX;								//Absolute coordinates 
		Att_acY = p_Attacker->m_posY;				//Absolute coordinates 
		att_Frame_Index = p_Attacker->m_nCrtFrame;
		att_Rect_Index = p_Attacker->m_sprite->_frames_rects_start[att_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	}

	//ÇÇ°ÝÃ¼
	//short Def_acX = 0;
	//short Def_acY = 0;
	//int def_Frame_Index = 0;
	//int def_Rect_Index = 0;
	//if(0 == p_Defender->m_nState)	//	¿¡´Ï¸ÞÀÌ¼Ç
	//{
	//	p_Defender->Get_AFrameXZ(&tmpXZ[0]);//ÀÌ¹ø¿¡ ±×·ÁÁú Ani ÀÇ x,z ÁÂÇ¥¸¦ ¾ò¾î¿Â´Ù
	//	Def_acX = tmpXZ[0] ;								//Absolute coordinates 
	//	Def_acY = p_Defender->m_posY;				//Absolute coordinates 
	//	def_Frame_Index = p_Defender->GetAnimFrame();// Defender ¾Ö´Ï¸ÞÀÌ¼ÇÀÇ ÇÁ·¹ÀÓ¿¡ °íÀ¯ Index °ªÀ» ¾ò¾î¿Â´Ù	
	//	def_Rect_Index = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index]*4;// DefenderBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	//}
	//else if(1 == p_Defender->m_nState)	//	ÇÁ·¹ÀÓ
	//{
	//	Def_acX = p_Defender->m_posX;								//Absolute coordinates 
	//	Def_acY = p_Defender->m_posY;				//Absolute coordinates 
	//	def_Frame_Index = p_Defender->m_nCrtFrame;
	//	def_Rect_Index = p_Defender->m_sprite->_frames_rects_start[def_Frame_Index]*4;// AttackerBODY ÇÁ·¹ÀÓÀÇ ½ÃÀÛÁöÁ¡ ¹è¿­ÀÎµ¦½º
	//}

	//¡Ú.1////////////	ÇöÁÂÇ¥¿Í ÇÇ°ÝÃ¼ Áß¿¡ ÇÑÂÊÀÌ¶óµµ ¸öÅëÀÌ ¾ø´Ù¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	if( RECT_NUM(p_Attacker, att_Frame_Index) < 1) //¹«°á¼ºÃ¼Å© - °ø°ÝÀÚ°¡ ¸öÅëÀÌ ¾ø´Ù¸é
		return false;//ÆÇÁ¤ÇÏÁö ¾Ê´Â´Ù

	X_a =XY(p_Attacker, att_Rect_Index  );
	W_a =WH(p_Attacker, att_Rect_Index+2);
	if(p_Attacker->m_stopFlag & FLAG_FLIP_X) X_a = -(X_a+W_a);// °ø°Ý ¾Ö´Ï ¹ÝÀüÀÌ¸é

	//X_d =XY(p_Defender, def_Rect_Index  );
	//W_d =WH(p_Defender, def_Rect_Index+2);
	//if(p_Defender->m_stopFlag & FLAG_FLIP_X) X_d = -(X_d+W_d);// ¼öºñ ¾Ö´Ï ¹ÝÀüÀÌ¸é


	//¡Ú.2////////////	ÀüÁÂÇ¥°¡ ¿µ¿ª ¾È¿¡ ÀÖ´Ù¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	//if	((Att_acY_before +attGap/2	>	Def_acY -defGap/2	) && 
	//	(Att_acY_before -attGap/2		<	Def_acY +defGap/2	)){//Ãæ°ÝÃ¼ ÀüÁÂÇ¥¿Í ÇÇ°ÝÃ¼ÀÇ Y °ãÄ§

	//		if((Att_acX_before + (X_a+W_a)	>	Def_acX + (X_d) + Safe_range	) && 
	//			(Att_acX_before + (X_a) + Safe_range	<	Def_acX + (X_d+W_d)	)){
	//				return false;////ÀüÁÂÇ¥°¡ ÀÌ¹Ì °ãÃÄ ÀÖÀ»¶§´Â Ãæµ¹Ã¼Å©°¡ °¡µ¿ÇÏÁö ¾Ê´Â´Ù
	//		}

	//}

	//¡Ú.3////////////	XÇÕ°è¿µ¿ª, YÇÕ°è¿µ¿ª ¾È¿¡ ÇÇ°ÝÃ¼°¡ Á¸ÀçÇÏÁö¾ÊÀ¸¸é Ãæµ¹Ã¼Å©´Â ÇÏÁö¾Ê´Â´Ù.
	//bool a1= (MIN(Att_acX_before+(X_a), Att_acX+(X_a))			>= X+W	);
	//bool a2= (MAX(Att_acX_before+(X_a+W_a), Att_acX+(X_a+W_a))	<= X		);
	//bool a3= (MIN(Att_acY_before-attGap/2, Att_acY-attGap/2)		>= Y+H	);
	//bool a4= (MAX(Att_acY_before+attGap/2, Att_acY+attGap/2)		<= Y	);

	if ((MIN(Att_acX_before+(X_a), Att_acX+(X_a))			>= X+W	)||
		(MAX(Att_acX_before+(X_a+W_a), Att_acX+(X_a+W_a))	<= X	)||
		(MIN(Att_acY_before-attGap/2, Att_acY-attGap/2)		>= Y+H	)||
		(MAX(Att_acY_before+attGap/2, Att_acY+attGap/2)		<= Y	))
		return false;//¾î´ÀÇÑÂÊÀÌ¶óµµ ¹þ¾î³ª¸é  Ãæµ¹Ã¼Å©°¡ °¡µ¿ÇÏÁö ¾Ê´Â´Ù




	int overX_Length = 0;
	if(HERO && Att_acX_before == Att_acX){
	}else
		if(Att_acX_before < X){//¡Ú¿ÞÂÊÀ¸·Î µÇµ¹¾Æ¿Ã °æ¿ì
			if(Att_acX_before < Att_acX)//¿À¸¥ÂÊÀ¸·Î ÀÌµ¿ÇÑ°ÍÀÌ ¸Â´Â°¡? - °ãÃÄÁö´Ù°¡ ¹þ¾î³­°æ¿ì °É¸±¼öµµ ÀÖÀ½
				overX_Length = - ((Att_acX	+ (X_a+W_a)) - (X));
		}else{//¡Ú¿À¸¥ÂÊÀ¸·Î µÇµ¹¾Æ¿Ã °æ¿ì
			if(Att_acX_before > Att_acX)//¿ÞÂÊÀ¸·Î ÀÌµ¿ÇÑ°ÍÀÌ ¸Â´Â°¡? - °ãÃÄÁö´Ù°¡ ¹þ¾î³­°æ¿ì °É¸±¼öµµ ÀÖÀ½
				overX_Length = + ((X+W) - (Att_acX + (X_a)));

		}

		int overY_Length = 0;
		if(HERO && Att_acY_before == Att_acY){
		}else
			if(Att_acY_before < Y){//¡ÚÀ§·Î µÇµ¹¾Æ¿Ã °æ¿ì
				overY_Length = - ((Att_acY	+ attGap/2) - (Y));

			}else{//¡Ú¾Æ·¡·Î µÇµ¹¾Æ¿Ã °æ¿ì
				overY_Length = + ((Y+H) - (Att_acY - attGap/2));
			}


			if(HERO){
				if( abs(overX_Length) > 0 ){// yÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é x ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posX += overX_Length;
					return true;
				}
				if( abs(overY_Length) > 0 ){// yÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é x ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posY += overY_Length;
					return true;
				}
			}else{//¸ó½ºÅÍÀÇ °æ¿ì ¹è°æ°ú ºñ±³ÇÒ¶§ ¾²ÀÓ
				if( ABS(overX_Length) < ABS(overY_Length) ){// YÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é X ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posX += overX_Length;
					return true;
				}else{// YÃàÀÇ ÀÌµ¿·®ÀÌ Å©´Ù¸é X ¸¦ ¹Ý¿µÇÑ´Ù.
					p_Attacker->m_posY += overY_Length;
					return true;
				}
			}

			return true;
}

int GFieldBattle::Area_Check(ASpriteInstance* Instance,int x_MAX)
{//¸ÊÀÇ x¹üÀ§ ¾È¿¡ Á¸ÀçÇÏ´ÂÁö Ã¼Å©ÇØ¼­ ¹ÛÀ¸·Î ³ª°¬À»¶§ ¾ÈÀ¸·Î ²ø¾îµé¿©¿À´Â ºÎºÐ
	//¸öÅë°£ ¾ÈÀü°Å¸® -5ÇÈ¼¿ ÃßÈÄ±¸Çö ÀÌºÎºÐÀÌ ÀÛÀ¸¸é ÀÛÀ»¼ö·Ï Á¢±Ù´ë»ó¿¡ ´ëÇØ ¶ÕÀ» °¡´É¼ºÀÌ Ä¿Áø´Ù
	int Safe_range = 35;

	int x_NOW = Instance->m_posX;


	int modify_X = 0;//º¸Á¤ °ªÀ» X ¿¡ ¹Ý¿µÇÑ´Ù
	int modify_Y = 0;
	if(x_NOW > x_MAX-Safe_range){
//		Instance->m_posX -= (x_NOW -  (x_MAX-Safe_range));
		modify_X = (x_MAX-Safe_range) - Instance->m_posX;
		Instance->m_posX = (x_MAX-Safe_range);
	}

	if(x_NOW < 0+Safe_range){
//		Instance->m_posX -= (x_NOW - (0+Safe_range));
		modify_X = (Safe_range) - Instance->m_posX;
		Instance->m_posX = (Safe_range);
	}

	return modify_Y*100000 + modify_X;
}
void GFieldBattle::Paint_Exception_Check()
{
	Exception_Num = 0; //ÃÊ±âÈ­

	
	if(   (hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 7)//ÇöÀç ÄÉ¸¯ÀÌ›§°Å³ª
		||(hero->s_Skill_Set[!hero->s_HeroTag.SEX].act&& hero->s_Skill_Set[!hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[!hero->s_HeroTag.SEX].Num] == 7 ))//½ºÀ§Äª ÄÉ¸¯ÀÌ ›§°Å³ª
	{///*ÇÏ¿ï¸µ*/ ½ÃÀüÇßÀ»¶§
		class ASpriteInstance*	_ins_Temp;
		_ins_Temp = (hero->s_HeroTag.SEX ? hero->_ins_Hero: hero->_ins_Hero_clone);

		if(_ins_Temp->m_nCrtFrame == 1 && _ins_Temp->m_nCrtAnimation==0){
			pFieldUi->InsertEffect(pField->m_nSrcCamAngle_X+(SCREEN_WIDTH>>1), (SCREEN_HEIGHT>>1)-4, 0, ANIM_WEFFECT_A_LINE);	
		}


		switch(_ins_Temp->m_nCrtFrame){
			case 1:
				pField->workPal(true,0,-24);
				break;
			case 3:
				pField->workPal(false,0,0);
				break;
		}

	}

	if(   (hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 0)//ÇöÀç ÄÉ¸¯ÀÌ›§°Å³ª
		||(hero->s_Skill_Set[!hero->s_HeroTag.SEX].act&& hero->s_Skill_Set[!hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[!hero->s_HeroTag.SEX].Num] == 0 ))//½ºÀ§Äª ÄÉ¸¯ÀÌ ›§°Å³ª
	{///*5¿¬¹ß¼¦*/ ½ÃÀüÇßÀ»¶§
		class ASpriteInstance*	_ins_Temp;
		_ins_Temp = (hero->s_HeroTag.SEX ? hero->_ins_Hero_clone: hero->_ins_Hero);


		if(_ins_Temp->m_nCrtFrame == 1 && _ins_Temp->m_nCrtAnimation==0){
			pFieldUi->InsertEffect(pField->m_nSrcCamAngle_X+(SCREEN_WIDTH>>1), (SCREEN_HEIGHT>>1)-4, 0, ANIM_WEFFECT_A_LINE);	
		}

		switch(_ins_Temp->m_nCrtFrame){
			case 1:
				pField->workPal(true,0,-24);
				break;
			case 4:
				pField->workPal(false,0,0);
// 				int ani_time = hero->_ins_Hero->m_nCrtAnimation;
// 				switch(ani_time){
// 					case 0:
// 						pField->workPal(true,0,20);
// 						break;
// 					case 1:
// 						pField->workPal(true,0,10);
// 						break;
// 					case 2:
// 						pField->workPal(false,0,0);
// 						break;
// 				}
				break;
		}

	}

	if(   (hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 1)//ÇöÀç ÄÉ¸¯ÀÌ›§°Å³ª
		||(hero->s_Skill_Set[!hero->s_HeroTag.SEX].act&& hero->s_Skill_Set[!hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[!hero->s_HeroTag.SEX].Num] == 1 ))//½ºÀ§Äª ÄÉ¸¯ÀÌ ›§°Å³ª
	{///*ÇÁ·ÎÁð »þ¿ö*/

		class ASpriteInstance*	_ins_Temp;
		_ins_Temp = (hero->s_HeroTag.SEX ? hero->_ins_Hero_clone: hero->_ins_Hero);

		if(_ins_Temp->m_nCrtFrame == 0 && _ins_Temp->m_nCrtAnimation==0){
			pFieldUi->InsertEffect(_ins_Temp->m_posX+(_ins_Temp->m_flags? +32:-32), _ins_Temp->m_posY, 0, ANIM_WEFFECT_A_WOMAN_S2);	
		}
		
		switch(_ins_Temp->m_nCrtFrame){
			case 5:
				pField->workPal(true,0,-24);
				break;
			case 8:
				pField->workPal(false,0,0);
				break;
		}

		if(_ins_Temp->m_nCrtFrame==5){
			Exception_Num+=PROCESS_MON_NOT;//¸ó½ºÅÍ Á¤Áö
		}

	}

	if(   (hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 8)//ÇöÀç ÄÉ¸¯ÀÌ›§°Å³ª
		||(hero->s_Skill_Set[!hero->s_HeroTag.SEX].act&& hero->s_Skill_Set[!hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[!hero->s_HeroTag.SEX].Num] == 8 ))//½ºÀ§Äª ÄÉ¸¯ÀÌ ›§°Å³ª
	{///*¸¶¼öÀÇ °è¾à*/

		class ASpriteInstance*	_ins_Temp;
		_ins_Temp = (hero->s_HeroTag.SEX ? hero->_ins_Hero: hero->_ins_Hero_clone);


		if(_ins_Temp->m_nCrtFrame == 0 && _ins_Temp->m_nCrtAnimation==0){
			pFieldUi->InsertEffect(_ins_Temp->m_posX, _ins_Temp->m_posY, 0, ANIM_WEFFECT_A_MAN_S2);	
		}

		switch(_ins_Temp->m_nCrtFrame){
			case 6:
				pField->workPal(true,0,-24);
				break;
			case 15:
				pField->workPal(false,0,0);
				break;
		}

		if(_ins_Temp->m_nCrtFrame==6){
			Exception_Num+=PROCESS_MON_NOT;//¸ó½ºÅÍ Á¤Áö
		}

	}


// 	if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 18)
// 	{//ºí·¢È¦
// 		int ani_time = hero->_ins_Hero->m_nCrtAnimation;
// 
// 		switch(hero->_ins_Hero->m_nCrtFrame){
// 			case 6:
// 				switch(ani_time%4){
// 			case 0:
// 				pField->workPal(true,0,-3);
// 				break;
// 			case 1:
// 				pField->workPal(true,0,-7);
// 				break;
// 			case 2:
// 				pField->workPal(true,0,-3);
// 				break;
// 			case 3:
// 				pField->workPal(false,0,0);
// 				break;
// 
// 
// 				}
// 				break;
// 			case 7:
// 				pField->workPal(false,0,0);
// 				break;
// 
// 
// 		}
// 		//if(hero->_ins_Hero->m_nCrtFrame < 7){//»¡¾Æ´ç±â±â
// 		//	MoveHead(pMonList);
// 		//	MoveNext(pMonList);
// 		//	while(NotEndList(pMonList))
// 		//	{
// 		//		if(MON_AC_DIE != GetData(pMonList)->m_ActState && MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState)
// 		//		{
// 
// 		//			//MON_AC_BLACKHOLE
// 
// 		//		}
// 		//		MoveNext(pMonList);
// 		//	}	
// 		//}
// 
// 	}
// 


	if(		(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 4)//ÇöÀç ÄÉ¸¯ÀÌ›§°Å³ª
		  ||(hero->s_Skill_Set[!hero->s_HeroTag.SEX].act&& hero->s_Skill_Set[!hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[!hero->s_HeroTag.SEX].Num] ==4 ))//½ºÀ§Äª ÄÉ¸¯ÀÌ ›§°Å³ª
	{//È÷¾î·Î ¸ÅÁ÷¹Ì»çÀÏ ½ÃÀüÇßÀ»¶§

		class ASpriteInstance*	_ins_Temp;
		_ins_Temp = (hero->s_HeroTag.SEX ? hero->_ins_Hero_clone: hero->_ins_Hero);

		switch(_ins_Temp->m_nCrtFrame){
			case 7://±â¼ú ¹ß»çÁ÷Àü ¶§ Å¸°Ù ¸ó½ºÅÍ ÁöÁ¤
 				{
 					int RangeLengthMAX = 200;
 					int RangeLengthMIN = 0;
 
 					int pMonsIns_Num = 0;
 					class Monster* pMonsIns[5]; 
 
 					MoveHead(pMonList);
 					MoveNext(pMonList);
 					while(NotEndList(pMonList))
 					{
 						if((MON_AC_DIE != GetData(pMonList)->m_ActState) &&
 							MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState &&
 							(MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState))
 						{
 
 							int tempX = GetData(pMonList)->pMonAsIns->m_posX - (_ins_Temp->m_posX);
 							int tempY = 0;//GetData(pMonList)->pMonAsIns->m_posY - (_ins_Temp->m_posY);
 
 
 							if((RangeLengthMAX> ABS(tempX)+ABS(tempY)) && (RangeLengthMIN< ABS(tempX)+ABS(tempY))){//¹ß»ç°Å¸®¿¡ Á¸ÀçÇÏ¸é ¸®½ºÆ®¿¡ Ãß°¡
 								pMonsIns[pMonsIns_Num] = GetData(pMonList);//Æ÷ÀÎÅÍ ÀúÀå 
 								pMonsIns_Num++;
 								if(pMonsIns_Num > 4)
 									break;//¸ó½ºÅÍ Ç®ÀÌ °¡µæ Ã¡´Ù
 
 							}
 
 						}
 						MoveNext(pMonList);
 					}		
 
 
 
 					if(pMonsIns_Num>0){//Å¸Å¶ ¸ó½ºÅÍ°¡ 1¸¶¸® ÀÌ»ó ÀÖÀ¸¸é
 						s_Homing[0].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
 						s_Homing[1].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
 						s_Homing[2].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
 
						

// 			 						hero->s_Knife_Eff[3].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_ATT_E_BACK);
// 			 						hero->s_Knife_Eff[3].LVup_Eff_Ins->m_bLoop = false;
// 			 
// 			 						hero->s_Knife_Eff[4].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_ATT_E);
// 			 						hero->s_Knife_Eff[4].LVup_Eff_Ins->m_bLoop = false;
					}else{
						for(int i = 0;i<3;i++){
							s_Homing[i].pMons = NULL;
							s_Homing[i].X2 = (_ins_Temp->m_flags? -10000:+10000);
							s_Homing[i].Y2 = (_ins_Temp->m_posY);
						}
						
					}
 				}
 
 				break;
			case 8:
				hero->s_Knife_Eff[0].act = true;
				hero->s_Knife_Eff[0].LVup_Eff_Ins = GL_NEW ASpriteInstance(hero->_spr_Skill[SEX_WOMAN][hero->s_Skill_Set[SEX_WOMAN].Num], 100, 200, NULL);// 0¹øÂ° ¹è¿­, ½Ç»ç¿ë½Ã´Â define ÇÊ¿ä
				hero->s_Knife_Eff[0].LVup_Eff_Ins->m_bLoop = true;
				s_Homing[0].X1 =(_ins_Temp->m_flags? -30:+30) + (_ins_Temp->m_posX);
				s_Homing[0].Y1 = (_ins_Temp->m_posY);
// 							if(s_Homing[0].pMons){
// 								s_Homing[0].X2 = s_Homing[0].pMons->pMonAsIns->m_posX;
// 								s_Homing[0].Y2 = s_Homing[0].pMons->pMonAsIns->m_posY;
// 							}
				s_Homing[0].Cita1=(_ins_Temp->m_flags? 270:90);
 
				s_Homing[0].TurnCita = 5;//½ÃÀÛ È¸Àü ÇÑ°è°¢(Á¡Á¡´Ã¾î³²)
				s_Homing[0].R = 15;//ÀÌµ¿·®
				break;
			case 11:
				hero->s_Knife_Eff[1].act = true;
				hero->s_Knife_Eff[1].LVup_Eff_Ins = GL_NEW ASpriteInstance(hero->_spr_Skill[SEX_WOMAN][hero->s_Skill_Set[SEX_WOMAN].Num], 100, 200, NULL);// 0¹øÂ° ¹è¿­, ½Ç»ç¿ë½Ã´Â define ÇÊ¿ä
				hero->s_Knife_Eff[1].LVup_Eff_Ins->m_bLoop = true;
				s_Homing[1].X1 =(_ins_Temp->m_flags? -30:+30) + (_ins_Temp->m_posX);
				s_Homing[1].Y1 = (_ins_Temp->m_posY);
// 							if(s_Homing[1].pMons){
// 	 							s_Homing[1].X2 = s_Homing[1].pMons->pMonAsIns->m_posX;
// 	 							s_Homing[1].Y2 = s_Homing[1].pMons->pMonAsIns->m_posY;
// 							}
				s_Homing[1].Cita1=(_ins_Temp->m_flags? 270:90);
 
				s_Homing[1].TurnCita = 5;//½ÃÀÛ È¸Àü ÇÑ°è°¢(Á¡Á¡´Ã¾î³²)
				s_Homing[1].R = 15;//ÀÌµ¿·®
				break;
			case 14:
				hero->s_Knife_Eff[2].act = true;
				hero->s_Knife_Eff[2].LVup_Eff_Ins = GL_NEW ASpriteInstance(hero->_spr_Skill[SEX_WOMAN][hero->s_Skill_Set[SEX_WOMAN].Num], 100, 200, NULL);// 0¹øÂ° ¹è¿­, ½Ç»ç¿ë½Ã´Â define ÇÊ¿ä
				hero->s_Knife_Eff[2].LVup_Eff_Ins->m_bLoop = true;
				s_Homing[2].X1 =(_ins_Temp->m_flags? -30:+30) + (_ins_Temp->m_posX);
				s_Homing[2].Y1 = (_ins_Temp->m_posY);
// 							if(s_Homing[2].pMons){
// 	 							s_Homing[2].X2 = s_Homing[2].pMons->pMonAsIns->m_posX;
// 	 							s_Homing[2].Y2 = s_Homing[2].pMons->pMonAsIns->m_posY;
// 							}
				s_Homing[2].Cita1=(_ins_Temp->m_flags? 270:90);
 
				s_Homing[2].TurnCita = 5;//½ÃÀÛ È¸Àü ÇÑ°è°¢(Á¡Á¡´Ã¾î³²)
				s_Homing[2].R = 15;//ÀÌµ¿·®
				break;

		}
			 
// 
// 
// 
// 			 				for(int i =0;i<3;i++){
// 			 					if(hero->s_Knife_Eff[i].act && hero->s_Knife_Eff[i].LVup_Eff_Ins!=NULL){//È£¹Ö ½ÃÀÛ
// 			 
// 			 
// 			 
// 			 
// 			 						if(ABS(s_Homing[i].X1 - s_Homing[i].X2) + ABS(s_Homing[i].Y1 - s_Homing[i].Y2) < s_Homing[i].R){
// 			 							hero->s_Knife_Eff[i].LVup_ActionEnd = !hero->s_Knife_Eff[i].LVup_Eff_Ins->UpdateSpriteAnim();//Effect ¿¡´Ï¸ÞÀÌ¼Ç ¾÷µ¥ÀÌÆ® ½ÇÇà
// 			 							if(hero->s_Knife_Eff[i].LVup_ActionEnd ){
// 			 								int zz = 0;
// 			 							}
// 			 							if(hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop){
// 			 								//hero->s_Knife_Eff[i].LVup_ActionEnd=true;
// 			 								hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_HIT1+i);
// 			 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X2;
// 			 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y2+1;
// 			 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop = false;
// 			 
// 			 								//s_Homing[i].R=0;
// 			 							}
// 			 
// 			 
// 			 						}else{
// 			 
// 			 							if(s_Homing[i].pMons){
// 			 								s_Homing[i].X2 = s_Homing[i].pMons->pMonAsIns->m_posX;
// 			 								s_Homing[i].Y2 = s_Homing[i].pMons->pMonAsIns->m_posY;
// 			 							}
// 			 
// 			 							GetHomingXY(&s_Homing[i]);
// 			 							hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X1;
// 			 							hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y1;
// 			 
// 			 							int xxx = ANIM_WOMAN_S1_DAGGER+((s_Homing[i].Cita1+15)%360) /30;
// 			 							if(xxx != hero->s_Knife_Eff[i].LVup_Eff_Ins->m_nCrtModule)
// 			 								hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(xxx);
// 			 
// 			 							if(s_Homing[i].TurnCita <90)s_Homing[i].TurnCita *= 2;
// 			 							if(s_Homing[i].R<30)s_Homing[i].R += 1;
// 			 
// 			 						}
// 			 					}
// 			 				}
// 			 
// 			 				break;
//			 		}

	}
	//¸ÅÁ÷ ¹Ì»çÀÏ ÃßÀûºÎºÐ
	for(int i =0,Homing = 6;i<3;i++){
		if(hero->s_Knife_Eff[i].act){
			if(hero->s_Knife_Eff[i].act && hero->s_Knife_Eff[i].LVup_Eff_Ins!=NULL){//È£¹Ö ½ÃÀÛ




				if(ABS(s_Homing[i].X1 - s_Homing[i].X2) + ABS(s_Homing[i].Y1 - s_Homing[i].Y2) < s_Homing[i].R){
					hero->s_Knife_Eff[i].LVup_ActionEnd = !hero->s_Knife_Eff[i].LVup_Eff_Ins->UpdateSpriteAnim();//Effect ¿¡´Ï¸ÞÀÌ¼Ç ¾÷µ¥ÀÌÆ® ½ÇÇà
					if(hero->s_Knife_Eff[i].LVup_ActionEnd ){
						int zz = 0;
					}
					if(hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop){
						//hero->s_Knife_Eff[i].LVup_ActionEnd=true;
						hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S5_HIT_1+(i%2));
						hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X2;
						hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y2+1;
						hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop = false;

						//s_Homing[i].R=0;
					}


				}else{

					if(s_Homing[i].pMons){
						if(	MON_AC_DIE == s_Homing[i].pMons->m_ActState ||
							MON_ATK_DEAD_ATTACK == s_Homing[i].pMons->m_ActState ||
							MON_AC_DIE_AFTER == s_Homing[i].pMons->m_ActState ||
							s_Homing[i].pMons->pMonAsIns==NULL)
						{//¸ó½ºÅÍ°¡ »ç¸ÁÇß°Å³ª ½ºÇÁ¶óÀÌÆ® ÀÎ¸¶¼öÀÇ°è¾à½º°¡ ¾ø´Ù¸é
							s_Homing[i].pMons = NULL;//ÃßÀûÁÂÇ¥ °»½ÅÀ» ÁßÁöÇÑ´Ù
						}else{
							s_Homing[i].X2 = s_Homing[i].pMons->pMonAsIns->m_posX;
							s_Homing[i].Y2 = s_Homing[i].pMons->pMonAsIns->m_posY;
						}
					}
					


					GetHomingXY(&s_Homing[i]);
					hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X1;
					hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y1;

					int xxx = ANIM_WOMAN_S5_DAGGER+((s_Homing[i].Cita1+15)%360) /30;
					if(xxx != hero->s_Knife_Eff[i].LVup_Eff_Ins->m_nCrtModule)
						hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(xxx);

					if(s_Homing[i].TurnCita <90)s_Homing[i].TurnCita *= 2;
					if(s_Homing[i].R<30)s_Homing[i].R += 1;

				}
			}
		}
	}



// 	if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 0)
// 	{//È÷¾î·Î °Ë¹öÇÁ ½ÃÀüÇßÀ»¶§
// 		int ani_time = hero->_ins_Hero->m_nCrtAnimation;
// 
// 		switch(hero->_ins_Hero->m_nCrtFrame){
// 			case 16:
// 				switch(ani_time){
// 			case 0:
// 				pField->workPal(true,0,31);
// 				Exception_Num+=PAINT_MON_NOT+PAINT_HERO_NOT;
// 
// 				break;
// 			case 1:
// 				pField->workPal(true,0,15);
// 				break;
// 				}
// 				break;
// 			case 17:
// 				pField->workPal(false,0,0);
// 				break;
// 
// 
// 
// 		}
// 	}
// 	if(hero->s_Knife_Eff[3].act && hero->s_Knife_Eff[3].LVup_Eff_Ins)
// 	{//È÷¾î·Î °Ë¹öÇÁ ÁßÀÏ¶§
// 
// 		if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 11)
// 			hero->s_Knife_Eff[3].LVup_ActionEnd = true;//¿ìÁÖºö ¹ßµ¿½Ã¿¡´Â ÇØÁ¦ÇÑ´Ù
// 
// 		switch(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_nCrtModule){
// 			case ANIM_WOMAN_S1_A_S_SKILL1_BUFF_E_BACK://Ã­Áö
// 				{
// 					int RangeLengthMAX = 200;
// 					int RangeLengthMIN = 100;
// 
// 					int pMonsIns_Num = 0;
// 					class Monster* pMonsIns[5]; 
// 
// 					MoveHead(pMonList);
// 					MoveNext(pMonList);
// 					while(NotEndList(pMonList))
// 					{
// 						if((MON_AC_DIE != GetData(pMonList)->m_ActState) &&
// 							MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState &&
// 							(MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState))
// 						{
// 
// 							int tempX = GetData(pMonList)->pMonAsIns->m_posX - (hero->_ins_Hero->m_posX);
// 							int tempY = GetData(pMonList)->pMonAsIns->m_posY - (hero->_ins_Hero->m_posY);
// 
// 
// 							if((RangeLengthMAX> ABS(tempX)+ABS(tempY)) && (RangeLengthMIN< ABS(tempX)+ABS(tempY))){//¹ß»ç°Å¸®¿¡ Á¸ÀçÇÏ¸é ¸®½ºÆ®¿¡ Ãß°¡
// 								pMonsIns[pMonsIns_Num] = GetData(pMonList);//Æ÷ÀÎÅÍ ÀúÀå 
// 								pMonsIns_Num++;
// 								if(pMonsIns_Num > 4)
// 									break;//¸ó½ºÅÍ Ç®ÀÌ °¡µæ Ã¡´Ù
// 
// 							}
// 
// 						}
// 						MoveNext(pMonList);
// 					}		
// 
// 
// 
// 					if(pMonsIns_Num>0){//Å¸Å¶ ¸ó½ºÅÍ°¡ 1¸¶¸® ÀÌ»ó ÀÖÀ¸¸é
// 						s_Homing[0].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
// 						s_Homing[1].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
// 						s_Homing[2].pMons = pMonsIns[RND(0,pMonsIns_Num-1)];//¸ó½ºÅÍ Æ÷ÀÎÅÍ ³Ñ±â±â
// 
// 						hero->s_Knife_Eff[3].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_ATT_E_BACK);
// 						hero->s_Knife_Eff[3].LVup_Eff_Ins->m_bLoop = false;
// 
// 						hero->s_Knife_Eff[4].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_ATT_E);
// 						hero->s_Knife_Eff[4].LVup_Eff_Ins->m_bLoop = false;
// 					}
// 				}
// 
// 				break;
// 			case ANIM_WOMAN_S1_A_S_SKILL1_ATT_E_BACK://¹ß»ç
// 				switch(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_nCrtFrame){
// 			case 4:
// 				hero->s_Knife_Eff[0].act = true;
// 
// 				s_Homing[0].X1 =(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? -51:+51) + (hero->_ins_Hero->m_posX);
// 				s_Homing[0].Y1 =-6 + (hero->_ins_Hero->m_posY);
// 				s_Homing[0].X2 = s_Homing[0].pMons->pMonAsIns->m_posX;
// 				s_Homing[0].Y2 = s_Homing[0].pMons->pMonAsIns->m_posY;
// 				s_Homing[0].Cita1=(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? 240:120);
// 
// 				s_Homing[0].TurnCita = 5;
// 				s_Homing[0].R = 15;
// 				break;
// 			case 5:
// 				hero->s_Knife_Eff[1].act = true;
// 
// 				s_Homing[1].X1 =(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? -61:+61) + (hero->_ins_Hero->m_posX);
// 				s_Homing[1].Y1 =-19 + (hero->_ins_Hero->m_posY);
// 				s_Homing[1].X2 = s_Homing[1].pMons->pMonAsIns->m_posX;
// 				s_Homing[1].Y2 = s_Homing[1].pMons->pMonAsIns->m_posY;
// 				s_Homing[1].Cita1=(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? 300:60);
// 
// 				s_Homing[1].TurnCita = 5;
// 				s_Homing[1].R = 15;
// 				break;
// 			case 6:
// 				hero->s_Knife_Eff[2].act = true;
// 
// 				s_Homing[2].X1 =(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? -71:+71) + (hero->_ins_Hero->m_posX);
// 				s_Homing[2].Y1 =+28 + (hero->_ins_Hero->m_posY);
// 				s_Homing[2].X2 = s_Homing[2].pMons->pMonAsIns->m_posX;
// 				s_Homing[2].Y2 = s_Homing[2].pMons->pMonAsIns->m_posY;
// 				s_Homing[2].Cita1=(hero->s_Knife_Eff[3].LVup_Eff_Ins->m_flags? 210:150);
// 
// 				s_Homing[2].TurnCita = 5;
// 				s_Homing[2].R = 15;
// 				break;
// 
// 				}
// 
// 				for(int i =0;i<3;i++){
// 					if(hero->s_Knife_Eff[i].act && hero->s_Knife_Eff[i].LVup_Eff_Ins!=NULL){//È£¹Ö ½ÃÀÛ
// 
// 
// 
// 
// 						if(ABS(s_Homing[i].X1 - s_Homing[i].X2) + ABS(s_Homing[i].Y1 - s_Homing[i].Y2) < s_Homing[i].R){
// 							hero->s_Knife_Eff[i].LVup_ActionEnd = !hero->s_Knife_Eff[i].LVup_Eff_Ins->UpdateSpriteAnim();//Effect ¿¡´Ï¸ÞÀÌ¼Ç ¾÷µ¥ÀÌÆ® ½ÇÇà
// 							if(hero->s_Knife_Eff[i].LVup_ActionEnd ){
// 								int zz = 0;
// 							}
// 							if(hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop){
// 								//hero->s_Knife_Eff[i].LVup_ActionEnd=true;
// 								hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(ANIM_WOMAN_S1_A_S_SKILL1_HIT1+i);
// 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X2;
// 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y2+1;
// 								hero->s_Knife_Eff[i].LVup_Eff_Ins->m_bLoop = false;
// 
// 								//s_Homing[i].R=0;
// 							}
// 
// 
// 						}else{
// 
// 							if(s_Homing[i].pMons){
// 								s_Homing[i].X2 = s_Homing[i].pMons->pMonAsIns->m_posX;
// 								s_Homing[i].Y2 = s_Homing[i].pMons->pMonAsIns->m_posY;
// 							}
// 
// 							GetHomingXY(&s_Homing[i]);
// 							hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posX = s_Homing[i].X1;
// 							hero->s_Knife_Eff[i].LVup_Eff_Ins->m_posY = s_Homing[i].Y1;
// 
// 							int xxx = ANIM_WOMAN_S1_DAGGER+((s_Homing[i].Cita1+15)%360) /30;
// 							if(xxx != hero->s_Knife_Eff[i].LVup_Eff_Ins->m_nCrtModule)
// 								hero->s_Knife_Eff[i].LVup_Eff_Ins->SetAnim(xxx);
// 
// 							if(s_Homing[i].TurnCita <90)s_Homing[i].TurnCita *= 2;
// 							if(s_Homing[i].R<30)s_Homing[i].R += 1;
// 
// 						}
// 					}
// 				}
// 
// 				break;
// 		}
// 	}
// 
// 
// 
// 
// 
// 	if(hero->s_Skill_Set[hero->s_HeroTag.SEX].act && hero->s_Skill_Set[hero->s_HeroTag.SEX].Skill_ID[hero->s_Skill_Set[hero->s_HeroTag.SEX].Num] == 11)
// 	{//¿ìÁÖºö
// 
// 
// 		int ani_time = hero->_ins_Hero->m_nCrtAnimation;
// 
// 		switch(hero->_ins_Hero->m_nCrtFrame){
// 			case 2:if(ani_time==0)pField->workPal(true,0,-5);
// 				break;
// 			case 3:if(ani_time==0)pField->workPal(true,0,-17);
// 				break;
// 			case 4:
// 				if(ani_time==0){
// 					pField->workPal(true,0,-31);
// 					BAKUP_HERO_Y = hero->_ins_Hero->m_posY;
// 					hero->_ins_Hero->m_posY = SCREEN_HEIGHT/2;
// 				}
// 				break;
// 			case 37:
// 				s_Camera.CameraAdd = (ani_time%2 ?-1 : +1)*RND(1,3);//Ä«¸Þ¶ó Èçµé±â
// 				switch(ani_time){
// 			case 0:
// 				hero->_ins_Hero->m_posY  = BAKUP_HERO_Y;
// 				pField->workPal(true,0,0);
// 				break;
// 			case 11:
// 				pField->workPal(true,0,15);
// 				for(int xx = 0;xx<SPRITE_MON_MAX;xx++) if(m_MonAs[xx])m_MonAs[xx]->workPal(true,0,15);
// 				break;
// 			case 12:
// 				pField->workPal(true,0,21);
// 				for(int xx = 0;xx<SPRITE_MON_MAX;xx++) if(m_MonAs[xx])m_MonAs[xx]->workPal(true,0,31);
// 				break;
// 			case 14:
// 				pField->workPal(true,0,20);
// 				for(int xx = 0;xx<SPRITE_MON_MAX;xx++) if(m_MonAs[xx])m_MonAs[xx]->workPal(true,0,17);
// 				break;
// 			case 15:
// 				pField->workPal(true,0,10);
// 				for(int xx = 0;xx<SPRITE_MON_MAX;xx++) if(m_MonAs[xx])m_MonAs[xx]->workPal(true,0,5);
// 				{
// 					MoveHead(pMonList);
// 					MoveNext(pMonList);
// 					Position3D power;
// 					int tmp = 0;
// 					while(NotEndList(pMonList))
// 					{
// 						if((MON_AC_DIE != GetData(pMonList)->m_ActState) &&
// 							MON_ATK_DEAD_ATTACK != GetData(pMonList)->m_ActState &&
// 							(MON_AC_DIE_AFTER != GetData(pMonList)->m_ActState))
// 						{
// 
// 							s_Contact.x = 0;
// 							s_Contact.y = 0;
// 							s_Contact.z = -50;
// 							s_Contact.D_index = 72;//½Â·æ±Ç ÀÎµ¦½º
// 							DamageSand_Hero(hero, GetData(pMonList));//ÁÖÀÎ°øÀÇ °ø°Ý
// 
// 						}
// 
// 						MoveNext(pMonList);
// 					}
// 				}
// 
// 				break;
// 			case 16:
// 				pField->workPal(false,0,0);
// 				for(int xx = 0;xx<SPRITE_MON_MAX;xx++) if(m_MonAs[xx])m_MonAs[xx]->workPal(false,0,0);
// 				break;
// 
// 				}
// 
// 				break;
// 		}
// 		if(hero->_ins_Hero->m_nCrtFrame >= 4 && hero->_ins_Hero->m_nCrtFrame <= 36){
// 			Exception_Num+=PAINT_MON_NOT+PAINT_FIELD_FRONT_NOT;
// 		}
// 
// 	}
// 
// 	if(CRI_SHINING){//Å©¸®Æ¼ÄÃ È­¸é ¹øÂ½ÀÓ
// 		CRI_SHINING--;
// 		pField->workPal(CRI_SHINING,0,7*CRI_SHINING);
// 	}

}

//--------------------------------------------------------------------------
void GFieldBattle::Throw_Check()
//--------------------------------------------------------------------------
{
	if(hero->s_Throw.ThrowPossible==true)
	{//ÁÖÀÎ°øÀÌ Àâ±â°¡ °¡´ÉÇÒ Å¸ÀÌ¹ÖÀÏ¶§ È®ÀÎÀÛ¾÷À» ÇÑ´Ù
		hero->s_Throw.ThrowPossible=false;//´øÁö±â Ã¼Å©°¡ ³¡³ª¸é ´øÁö±â°¡´É »óÅÂ´Â ¹Ù·ÎÇØÁ¦ ÇÑ´Ù
		MoveHead(pMonList);
		MoveNext(pMonList);
		while(NotEndList(pMonList))
		{
			if(GetData(pMonList)->SetHolding(hero->s_Throw.ThrowNum))
			{
				hero->s_Throw.act = true;

				return;
			}

			MoveNext(pMonList);
		}
	}
}



//--------------------------------------------------------------------------
void GFieldBattle::Analysis_Mon_Message()
//--------------------------------------------------------------------------
{
	int msg = 0;
	//	message
	MoveHead(pMonMsgList);
	MoveNext(pMonMsgList);
	while(NotEndList(pMonMsgList))
	{
		if(0 < GetData(pMonMsgList)->m_nDelay)
		{
			GetData(pMonMsgList)->m_nDelay--;
			MoveNext(pMonMsgList);
			continue;
		}

		switch(GetData(pMonMsgList)->m_MsgType)
		{
		case MSG_CHANGE_STATE:
			//------------------------------------------------------------
			{
				int dst = GetData(pMonMsgList)->param[0];
				int changeState = GetData(pMonMsgList)->param[1];

				//	´ë»óÀ» °Ë»öÇÑ´Ù.
				MoveHead(pMonList);
				MoveNext(pMonList);
				while(NotEndList(pMonList))
				{
					if(dst == GetData(pMonList)->m_nMonIdx)	//	°°Àº Å¸ÀÔÀÌ¶ó¸é
					{
						GetData(pMonList)->ResvAction(changeState, 0);
						break;
					}
					MoveNext(pMonList);
				}
				break;
			}
		case MSG_MON4_CLONE:
		//------------------------------------------------------------
		{
			AddMonster(1, MON_IDX_CROWN_BOMB, 0, 0, GRADE_NORMAL,
				GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
				GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
				NOT_REGEN);

			//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
			GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

			//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
			GetData(pMonList)->Process(m_CharInfo);

			break;
		}
		case MSG_ELF_HEAL:
		//------------------------------------------------------------
		{
			//	´ë»óÀ» °Ë»öÇÑ´Ù.
			Monster* pMonster = NULL;
			bool isMove = false;

			//	¸Ê¿¡ ´ëÇÑ Ãæµ¹Ã¼Å©
			for(InitList(pMonList);NotEndList(pMonList);MoveNext(pMonList))
			{
				//	»óÅÂ°¡ ¿òÁ÷ÀÌ°Å³ª ¼­ÀÖÀ»¶§¸¸ ÈúÀÌ µé¾î°¡°Ô ÇÑ´Ù.
				if(MON_AC_MOVE < GetData(pMonList)->m_ActState)	{continue;}

				//	°Å¸®°¡ ¸Ö¸é ³Ñ¾î°£´Ù.
				if(SQR(200) < (SQR(GetData(pMonMsgList)->param[0]-GetData(pMonList)->pMonAsIns->m_posX )
									+SQR(GetData(pMonMsgList)->param[1]-GetData(pMonList)->pMonAsIns->m_posY)))	{continue;}

				//	Ã¼·ÂÀÌ ¸¹À¸¸é ³Ñ¾î°£´Ù.
				if(GetData(pMonList)->m_Stet.m_MaxHp/2 < GetData(pMonList)->m_Stet.m_Hp )		{continue;}

				if(NULL == pMonster)
				{
					pMonster = GetData(pMonList);
				}
				else
				{
					if(pMonster->m_Stet.m_Hp > GetData(pMonList)->m_Stet.m_Hp )
					{
						pMonster = GetData(pMonList);
					}
				}
			}

			if(pMonster)
			{
				//	ÈúÀ» °É¾îÁØ´Ù.
				pFieldUi->InsertdamageNum(pMonster->pMonAsIns->m_posX , pMonster->pMonAsIns->m_posY , pMonster->pMonAsIns->m_posZ, 545, MON_CRI_NUM);
				pMonster->RCV_Debuff( DEBUF_ICE );
				pMonster->m_Stet.m_Hp += 100;
				if(pMonster->m_Stet.m_MaxHp < pMonster->m_Stet.m_Hp)
				{
					pMonster->m_Stet.m_Hp = pMonster->m_Stet.m_MaxHp;
				}
			}

			break;
		}

		case MSG_ELF_TOTAL_HEAL:
		//------------------------------------------------------------
		{
			//	´ë»óÀ» °Ë»öÇÑ´Ù.
			Monster* pMonster;
			bool isMove = false;

			//	¸Ê¿¡ ´ëÇÑ Ãæµ¹Ã¼Å©
			for(InitList(pMonList);NotEndList(pMonList);MoveNext(pMonList))
			{
				//	»óÅÂ°¡ ¿òÁ÷ÀÌ°Å³ª ¼­ÀÖÀ»¶§¸¸ ÈúÀÌ µé¾î°¡°Ô ÇÑ´Ù.
				if(MON_AC_MOVE < GetData(pMonList)->m_ActState)	{continue;}

				//	°Å¸®°¡ ¸Ö¸é ³Ñ¾î°£´Ù.
				if(SQR(200) < (SQR(GetData(pMonMsgList)->param[0]-GetData(pMonList)->pMonAsIns->m_posX )
									+SQR(GetData(pMonMsgList)->param[1]-GetData(pMonList)->pMonAsIns->m_posY)))	{continue;}

				//	Ã¼·ÂÀÌ ¸¹À¸¸é ³Ñ¾î°£´Ù.
				if(GetData(pMonList)->m_Stet.m_MaxHp/2 < GetData(pMonList)->m_Stet.m_Hp )		{continue;}

				//	ÈúÀ» °É¾îÁØ´Ù.
				pFieldUi->InsertdamageNum(GetData(pMonList)->pMonAsIns->m_posX , GetData(pMonList)->pMonAsIns->m_posY , GetData(pMonList)->pMonAsIns->m_posZ, 545, MON_CRI_NUM);
				GetData(pMonList)->RCV_Debuff( DEBUF_ICE );
				GetData(pMonList)->m_Stet.m_Hp += 100;
				if(GetData(pMonList)->m_Stet.m_MaxHp < GetData(pMonList)->m_Stet.m_Hp)
				{
					GetData(pMonList)->m_Stet.m_Hp = GetData(pMonList)->m_Stet.m_MaxHp;
				}
			}
			break;
		}
		case MSG_SUMMONE_BABY:
			//------------------------------------------------------------
			{
				//				AddMonster(1, GetData(pMonMsgList)->param[0], GRADE_SPECIAL,
				//								GetData(pMonMsgList)->param[1], GetData(pMonMsgList)->param[2],
				//								GetData(pMonMsgList)->param[1], GetData(pMonMsgList)->param[2], 0,
				//								GetData(pMonMsgList)->param[3]);

				//	¼ÒÈ¯ÇÏ´Ù¸»¾ÒÀ½
				//	µô·¹ÀÌ ½Ã°£ Ã¼Å©
				break;
			}
		case MSG_SUMMONE_BUGS:
			//------------------------------------------------------------
			{
				switch(GetData(pMonMsgList)->param[3])
				{
					case MON_IDX_WORM:
					//-----------------------------------------------------------------
					{
						AddMonster(1, MON_IDX_BUG, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);
						break;
					}
					case MON_IDX_FLOWER:
					//-----------------------------------------------------------------
					{
						AddMonster(1, MON_IDX_SLIME, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1]+20,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1]+20,
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);
						break;
					}
					case MON_IDX_DARK_KNIGHT:
					//-----------------------------------------------------------------
					{
						AddMonster(1, MON_IDX_DARK_KNIGHT_MIRROR, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0]-30, GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0]-30, GetData(pMonMsgList)->param[1],
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);

						AddMonster(1, MON_IDX_DARK_KNIGHT_MIRROR, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0]+30, GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0]+30, GetData(pMonMsgList)->param[1],
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);

						break;
					}
					case MON_IDX_BIGTURTLE:
					//-----------------------------------------------------------------
					{
						AddMonster(1, MON_IDX_TURTLE, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);
						break;
					}
					case MON_IDX_LASTBOSS:
					//-----------------------------------------------------------------
					{
						AddMonster(1, MON_IDX_THUNDERCLOUD, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							NOT_REGEN);

						//	¹æÇâÀ» Á¤ÇØÁØ´Ù.
						GetData(pMonList)->m_nDirection = GetData(pMonMsgList)->param[2];

						//	ÇÁ·Î¼¼¼­¸¦ ÇÑ¹ø µ¹·ÁÁØ´Ù.
						GetData(pMonList)->Process(m_CharInfo);
						break;
					}
				}

				//	¼ÒÈ¯ÇÏ´Ù¸»¾ÒÀ½
				//	µô·¹ÀÌ ½Ã°£ Ã¼Å©
				break;
			}
		case MSG_DE_SUMMONE_BUGS:
			//------------------------------------------------------------
			{
				//	´ë»óÀ» °Ë»öÇÑ´Ù.
				MoveHead(pMonList);
				MoveNext(pMonList);
				while(NotEndList(pMonList))
				{
					//	¸ðµç ¸ó½ºÅÍÀÇ ÇÇ¸¦ ¾ø¾ÖÁØ´Ù. 
					GetData(pMonList)->m_Stet.m_Hp = 0;

					if(MON_IDX_WORM != GetData(pMonList)->m_PtnIdx)
					{
						//						if(MON_AC_STAND == GetData(pMonList)->m_ActState ||
						//							MON_AC_MOVE == GetData(pMonList)->m_ActState ||
						//							MON_AC_RUN == GetData(pMonList)->m_ActState)
						//						{
						GetData(pMonList)->ResvAction(MON_AC_DIE, 1);
						//						}

					}

					MoveNext(pMonList);
				}

				break;
			}
		case MSG_BOSS_CHANGESTATE:
			//------------------------------------------------------------
			{
				for(InitList(pMonList);NotEndList(pMonList);MoveNext(pMonList))
				{
					if(GetData(pMonList)->m_nUniqueIdx == GetData(pMonMsgList)->param[0])
					{
						GetData(pMonList)->ResvAction(GetData(pMonMsgList)->param[1], 0);
					}
					
/*

					if(GetData(pMonList)->m_nMonIdx == MON_IDX_BIGDOG1)
					{
						GetData(pMonList)->m_nAiNextState = GetData(pMonMsgList)->param[0];

						if(MON_AI_ATTACK_DONTMOVE == GetData(pMonMsgList)->param[0])
						{
							GetData(pMonList)->m_nUseAtkNum = GetData(pMonMsgList)->param[1];
							GetData(pMonList)->m_bIsSuccessAttack = false;

							GetData(pMonList)->m_Attack[GetData(pMonList)->m_nUseAtkNum].CoolTime =
								GetData(pMonList)->m_Attack[GetData(pMonList)->m_nUseAtkNum].MaxCoolTime;
						}
						else if(MON_AI_READY_TO_HIT == GetData(pMonMsgList)->param[0])
						{
							GetData(pMonList)->m_nDstTime = 20;
						}
					}
*/
				}
				break;
			}
			case MSG_BOSS3_SUMMON_WALL:
			//------------------------------------------------------------
			{
				AddMonster(1, MON_IDX_DRILL, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],	NOT_REGEN);
						GetData(pMonList)->Process(m_CharInfo);
/*
				//	width
				if(0 == GetData(pMonMsgList)->param[0])
				{
					for(int loop = 0; loop < 20; loop++)
					{
						AddMonster(1, MON_IDX_DRILL, 0, 0, GRADE_NORMAL,

							15 + loop*20, GetData(pMonMsgList)->param[1]-10+SUTIL_GetRandom()%20,
							15 + loop*20, GetData(pMonMsgList)->param[1]-10+SUTIL_GetRandom()%20,
							NOT_REGEN);
						GetData(pMonList)->Process(m_CharInfo);
					}
				}
				//	height
				else
				{
					for(int loop = 0; loop < 6; loop++)
					{
						AddMonster(1, MON_IDX_DRILL, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[1]-10+SUTIL_GetRandom()%20, 180 + loop*20,
							GetData(pMonMsgList)->param[1]-10+SUTIL_GetRandom()%20, 180 + loop*20,
							NOT_REGEN);
						GetData(pMonList)->Process(m_CharInfo);
					}
				}
*/
				break;
			}
			case MSG_BOSS5_SUMMON_DEVIL:
			//------------------------------------------------------------
			{
				AddMonster(1, MON_IDX_BOSS5_DEVIL, 0, 0, GRADE_NORMAL,
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],
							GetData(pMonMsgList)->param[0], GetData(pMonMsgList)->param[1],	NOT_REGEN);
						GetData(pMonList)->Process(m_CharInfo);


				break;
			}

			default:
			//------------------------------------------------------------
			{
				MoveNext(pMonMsgList);
				continue;
			}
		}

		//	¸Þ¼¼Áö¸¦ Áö¿öÁØ´Ù.
		SAFE_DELETE(GetData(pMonMsgList));
		pMonMsgList->Delete();
	}
}





#define RADER_POS_X	(90)
#define RADER_POS_Y	(5)
#define RADER_POS_W	(62 - 4)
#define RADER_POS_H	(16 - 4)
#define Y_START	(157)
#define Y_END	(255)
void GFieldBattle::PaintMiniMap(){
	////	¹Ì´Ï¸Ê
	SUTIL_Paint_Frame(pFieldUi->s_ASpriteSet->pFieldUiAs ,FRAME_UI_RADER, RADER_POS_X, RADER_POS_Y,0);

	int mapsize = pField->m_nFieldSize_X;

	MoveHead(pMonList);
	MoveNext(pMonList);
	while(NotEndList(pMonList))
	{
		////¸ó½ºÅÍ (ÅëÀÌ³ª µ¹Àº ¸ÂÀ¸¸é ¾ÈµÊ)
		if(0 == (GetData(pMonList)->m_nFeature & FE_DONT_DRAW_MAP))
		{
			SUTIL_Paint_Frame(pFieldUi->s_ASpriteSet->pFieldUiAs ,
				FRAME_UI_RADER_ENEMY,
				RADER_POS_X + GetData(pMonList)->pMonAsIns->m_posX*RADER_POS_W/mapsize +2,
				RADER_POS_Y + (GetData(pMonList)->pMonAsIns->m_posY - Y_START)*RADER_POS_H/(Y_END - Y_START) +1,
				0);
		}
		MoveNext(pMonList);
	}

	////	ÁÖÀÎ°ø	
	SUTIL_Paint_Frame(pFieldUi->s_ASpriteSet->pFieldUiAs ,
		FRAME_UI_RADER_MC,
		RADER_POS_X + m_CharInfo->m_nPos.x * RADER_POS_W/mapsize +2,
		RADER_POS_Y + (m_CharInfo->m_nPos.y - Y_START) *RADER_POS_H/(Y_END - Y_START) +1,
		0);

}

//--------------------------------------------------------------------------
void GFieldBattle::SetCameraMove()
//--------------------------------------------------------------------------
{
	if(s_Camera.cX == 0)
	{
		s_Camera.cX = hero->_ins_Hero->m_posX;
	}

	int tempX = hero->_ins_Hero->m_posX;
	int heroX = tempX;

	int scroll_x=0;

	int scroll_speed=0;
	switch(hero->_move_Order){
		case HERO_DASH_RIGHT:
		case HERO_DASH_LEFT:
		case HERO_DASH_STOP:
			/*s_Camera.stop_Frame=0;
			s_Camera.CameraAdd=0;
			tempX = s_Camera.cX;
			scroll_x = CAMERA_DASH_SCROLL;*/
			scroll_speed = 65;
			break;
		default:

			scroll_speed = 80;
			break;


			//case	HERO_STOP:
			//case 	HERO_ATTACK1	:
			//case 	HERO_ATTACK1END	:
			//case 	HERO_ATTACK2	:
			//case 	HERO_ATTACK2END	:
			//case 	HERO_ATTACK3	:
			//case 	HERO_ATTACK3END	:
			//case 	HERO_ATTACK4	:
			//	scroll_x = CAMERA_MAX_MOVE;

			//	s_Camera.stop_Frame++;
			//	if(CAMERA_DELAY < s_Camera.stop_Frame){//ÀÏÁ¤½Ã°£ÀÌ»ó ´ë±âÇÏ¸é ½Ã¾ßÈ®º¸
			//		tempX += (hero->_ins_Hero->m_flags ? -CAMERA_MAX_SPACE : +CAMERA_MAX_SPACE);
			//	}else{
			//		tempX = s_Camera.cX;
			//	}
			//	break;
			//default:
			//	s_Camera.stop_Frame=0;
			//	tempX = s_Camera.cX;
			//	scroll_x = CAMERA_MAX_MOVE;
			//	break;

	}

	scroll_x = CAMERA_MAX_MOVE;

	//s_Camera.stop_Frame++;
	//if(CAMERA_DELAY < s_Camera.stop_Frame){//ÀÏÁ¤½Ã°£ÀÌ»ó ´ë±âÇÏ¸é ½Ã¾ßÈ®º¸
	tempX += (hero->_ins_Hero->m_flags ? -CAMERA_MAX_SPACE : +CAMERA_MAX_SPACE);
	/*}else{
	tempX = s_Camera.cX;
	}*/




	if(tempX > heroX){
		if(tempX - heroX > scroll_x) 
			tempX -= (tempX - heroX) - scroll_x;
		else
			tempX += ((((s_Camera.cX)-tempX) * scroll_speed) / 100);
	}else{
		if(heroX - tempX > scroll_x) 
			tempX += (heroX - tempX) - scroll_x;
		else
			tempX += ((((s_Camera.cX)-tempX) * scroll_speed) / 100);
	}


	//ºÎµå·¯¿î ½ºÅ©·Ñ
	//tempX += ((((s_Camera.cX)-tempX) * 80) / 100);

	pField->SetCamera(tempX+s_Camera.CameraAdd);
	s_Camera.cX = tempX;

	//	½ºÅ©¸° ¸Å´ÏÁ® Ãß°¡
	SScreenMgr::GetInstPtr()->SetWorldPos(-(pField->m_nSrcCamAngle_X));

}


//--------------------------------------------------------------------------
void GFieldBattle::DamageSand_Hero(Character* hero, Monster* mon)
//--------------------------------------------------------------------------
{
	//	·¹µð»óÅÂ´Â µ¥¹ÌÁö°¡ ¾È µé¾î°£´Ù.
	if(MON_AC_READY == mon->m_ActState )	{return;}

	int tmp = 0;
	
	power.Init(s_Contact.x,s_Contact.y,s_Contact.z);

	//	È¸ÇÇ Ã³¸®
	if(SUTIL_GetRandom()%(100) < mon->m_Stet.m_nAvoid)
	{
		pFieldUi->InsertdamageNum(s_Contact.crash_x , mon->pMonAsIns->m_posY-mon->m_Stet.m_Height , mon->pMonAsIns->m_posZ, 0, MON_NUM);
	}
	else
	{
		if(mon->ReceiveAttack(power))
		{
			tmp = hero->SND_Damage(mon->m_nLevel,
				mon->m_nElementIdx,   
				mon->m_Stet.m_Defance,
				s_Contact.D_index);
			//CRITICAL_HERO
			if(hero->Critical && !CRI_SHINING)
			{
				CRI_SHINING=3;
			}

			mon->RCV_Damage(tmp);

			if(tmp)
			{
				pFieldUi->InsertdamageNum(s_Contact.crash_x , mon->pMonAsIns->m_posY-mon->m_Stet.m_Height , mon->pMonAsIns->m_posZ, tmp, (hero->Critical?MON_CRI_NUM:MON_NUM));
				pFieldUi->Insert_CrashEffect(s_Contact.crash_x, mon->pMonAsIns->m_posY, s_Contact.crash_z, (hero->Critical?ANIM_WEFFECT_A_CRITICAL_1:ANIM_WEFFECT_A_EFF_HIT1));
				mon->RCV_Debuff( hero->SND_Debuff(0) );
			}

			pFieldUi->InsertMonsterInfo(mon->m_nUniqueIdx,
				mon->m_nMonName,
				mon->m_nLevel,
				mon->m_Stet.m_Hp,
				mon->m_Stet.m_MaxHp,
				mon->m_nElementIdx);
		}

		pFieldUi->AddCombo();	//	nams
	}


}

//--------------------------------------------------------------------------
void GFieldBattle::DamageSand_Mon(Monster* mon , Character* hero)
//--------------------------------------------------------------------------
{

	if(AVOID_HERO){//ÁÖÀÎ°øÀÌ È¸ÇÇ¿¡ ¼º°øÇßÀ»°æ¿ì
		pFieldUi->InsertdamageNum(s_Contact.crash_x, hero->_ins_Hero->m_posY, hero->m_HEADTOP, 0, HERO_NUM);
	}else{
		int tmp = 0;

		tmp = mon->SND_Damage(hero->s_Status[hero->s_HeroTag.SEX].LEVEL,
			hero->s_HeroTag.SEX /*hero->s_Status[hero->s_HeroTag.SEX].ELEMENTAL*/,
			hero->s_Status[hero->s_HeroTag.SEX].DEFENSE_PER + 
			(hero->s_Status[hero->s_HeroTag.SEX].LIFE*10 < hero->s_Status[hero->s_HeroTag.SEX].LIFE_MAX*3 ?  hero->Check_sex(0, hero->Get_Skill(SKILL_P_M_IronSkin)) : 0),
			s_Contact.D_index);
		

			bool cri = false;
			if((RND(1,100)<= (mon->m_Stet.m_Cri)) && (RND(1,100) > hero->Check_sex( hero->Get_Skill(SKILL_P_W_CriDown) , 0))) {tmp*=2;cri=true;}


			if(hero->_move_Order == HERO_CHARGE && hero->_b_JabNum == JAB_KNIGHT){//ÁÖÀÎ°øÀÌ °¡µå¿¡ ¼º°øÇßÀ»°æ¿ì
				tmp = (tmp*3)/10;
				pFieldUi->InsertEffect(s_Contact.crash_x, hero->_ins_Hero->m_posY, s_Contact.crash_z, ANIM_WEFFECT_A_HIT_DEFENSE);	
			}else{
				pFieldUi->Insert_CrashEffect(s_Contact.crash_x, hero->_ins_Hero->m_posY, s_Contact.crash_z, ANIM_WEFFECT_A_EFF_HITMC);	
			}
			//if(RND(1,100) <= hero->Get_Skill(SKILL_P_S_ironWall)) {tmp/=2;}//ÆÐ½Ãºê

			hero->RCV_Damage(tmp);
			pFieldUi->InsertdamageNum(s_Contact.crash_x, hero->_ins_Hero->m_posY, hero->m_HEADTOP, tmp, (cri?HERO_CRI_NUM:HERO_NUM));

			/////////////////////////////////////////////////////

			power.Init(s_Contact.x,s_Contact.y,s_Contact.z);
			hero->ReceiveAttack(power);

	}
	////////////////////////////////////////////////////
}


////--------------------------------------------------------------------------
//void GFieldBattle::SetEvent(int nEvtCode, int dummy1)
////--------------------------------------------------------------------------
//{	
//	if(!nEvtCode)	{return;}
//
//	switch(nEvtCode)
//	{
//		case 1:		//	¸ÊÀÌµ¿ ÀÌº¥Æ®
//		//---------------------------------------------------------------
//		{
//			Resv_ChangeStage(dummy1);
//			break;
//		}
//		case 3:		//	Áö¿ª ÀÌµ¿ ÀÌº¥Æ®
//		//---------------------------------------------------------------
//		{
//			Resv_ChangeStage(dummy1);
//			break;
//		}
//		case 2:		//	»óÁ¡ npc
//		//---------------------------------------------------------------
//		{
//			//Resv_ChangeStage(dummy1);
//			int a = 90;
//			b_PopupUi = true;
//			break;
//		}
//		case 4:		//	¾¾³×¸¶ ÀÌº¥Æ®
//		//---------------------------------------------------------------
//		{
//			switch(dummy1)
//			{
//				case 0:
//				//------------------------------------------------------------
//				{
//					pCinema->Load_Cinematics(PACK_DATA_CINEMA, DATA_CINEMA_SCENE1, 1, pField);
//					break;
//				}
//				case 1:
//				//------------------------------------------------------------
//				{
//					hero->Set_MustAction(pCinema->m_ASpriteIns[0][1]->m_posX,
//											pCinema->m_ASpriteIns[0][1]->m_posY,
//											0, 0);
//
//					pCinema->Release_Cinematics();
////					m_nRestoreStageCount = 7;
//					
//					break;
//				}
//			}
//		}
//	}
//}


//--------------------------------------------------------------------------
void GFieldBattle::EventProcess()
//--------------------------------------------------------------------------
{
	pField->Process_EVT_WAY(0,0,0,0);

	//	ÀÌµ¿»óÅÂÀÏ ¶§¸¸ ÀÌµ¿ ÀÌº¥Æ®¸¦ °¡´ÉÇÏ°Ô ÇÑ´Ù.
	if(HERO_WALK_LEFT > hero->_move_Order || HERO_WALK_DOWN < hero->_move_Order)	{return;}
	
	//	ÆäÀÌµå ÀÎ »óÅÂÀÌ°Å³ª ÆäÀÌµå ¾Æ¿ô»óÅÂ¶ó¸é ÇÏÁö ¾Ê´Â´Ù.
	if(m_nFadeInTime || m_nFadeOutTime)	{return;}

	if(true == pMinimap->ResvNextSector(m_CharInfo->m_nPos.x, m_CharInfo->m_nPos.y, 0) )
	{
		ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
		ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 0);

//		pField->LoadMap( (void*)pMinimap->SetResvSector() );
	}
	
/*
	if(MAP_MOVE_UP_Y > m_CharInfo->m_nPos.y)
	{
		pMinimap->ResvNextSector();

//		pField->LoadMap( (void*)pMinimap->SetResvSector() );
	}

	if(MAP_MOVE_DOWN_Y < m_CharInfo->m_nPos.y)
	{

	}

	if(MAP_MOVE_X > m_CharInfo->m_nPos.x)
	{

	}

	if(pField->m_nFieldSize_X - MAP_MOVE_X > m_CharInfo->m_nPos.x)
	{

	}


	// ±æ ÀÌº¥Æ® È®ÀÎ
*/
/*
	//	imsi
	if(1000 <= pField->m_nSaveStageNum)												{return;}

	//	ÇÊµå ÀÌµ¿°ü·Ã ÀÌº¥Æ®
	int result = pField->Process_EVT_WAY(MAP_EVT_WAY_TYPE_ALL, hero->s_Event_Rect.Direction, m_CharInfo->m_nPos.x, m_CharInfo->m_nPos.y);
	//	int result = pField->Process_EVT_WAY(MAP_EVT_WAY_TYPE_ALL, hero->s_Event_Rect.X1, hero->s_Event_Rect.Y1,
	//											hero->s_Event_Rect.X2, hero->s_Event_Rect.Y2);


	//	ÀÌµ¿»óÅÂÀÏ ¶§¸¸ ÀÌµ¿ ÀÌº¥Æ®¸¦ °¡´ÉÇÏ°Ô ÇÑ´Ù.
	if(HERO_WALK_LEFT > hero->_move_Order || HERO_WALK_DOWN < hero->_move_Order)	{return;}

	if(WORLD_MAP_STAGE_NUM <= result){//¿ùµå¸Ê È£Ãâ

		if(b_WorldMap){return;}

		b_WorldMap = true;
		pWorldMapUi = GL_NEW WorldmapUI(pField->m_nVillageUniqueIdx);
		return;
	}	
		
	//	µ¹ÀÌ ÀÖÀ¸¸é ³Ñ¾î°¥¼ö ¾ø´Ù.
	if(MAIN_QUEST_openDoor >= GET_MAINQUEST_IDX())
	{
		if(200 == result && 201 == pField->m_nSaveStageNum)							{return;}
	}

	if(0 != result)
	{
		ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
		ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, result);
	}

	//	ÀÌº¥Æ®¿¡ ´ëÇÑ Ãæµ¹Ã¼Å©
	result = pField->Process_EVT_Rect(m_CharInfo->m_nPos.x, m_CharInfo->m_nPos.y);

	if(0 != result)
	{
		ADD_EVENT_MSG(EVT_GAME_KEYEVENT, 0, result);
	}
*/
}


//--------------------------------------------------------------------------
bool GFieldBattle::KeyEventProcess()
//--------------------------------------------------------------------------
{
	//	ÇÊµå¿¡¼­ Å°¹öÆ° Ã¼Å©½Ã ÀÌº¥Æ® Ã¼Å©ÀÌº¥Æ® Ã¼Å©
	int evtcode = pField->KeyPressEvent(hero->s_Event_Rect.Direction,
		hero->s_Event_Rect.X1,hero->s_Event_Rect.Y1,
		hero->s_Event_Rect.X2,hero->s_Event_Rect.Y2);
	if(evtcode)
	{
		ADD_EVENT_MSG(EVT_GAME_KEYEVENT, 0, evtcode);
		return true;
	}

	return false;
}




//--------------------------------------------------------------------------
void GFieldBattle::Analysis_Event()
//--------------------------------------------------------------------------
{	
	bool bIsCrearMsg = false;;

	List2< S_EVENT_MSG* > *pMsgList = GET_EVENT_MSG_STRUCT();

	InitList( pMsgList );

	while(NotEndList( pMsgList ))
	{
		if(0 < GetData( pMsgList )->m_nDelay )
		{
			int delay = (GetData( pMsgList )->m_nDelay--);
			MoveNext( pMsgList );
			continue;
		}

		//	¸Þ¼¼Áö¸¦ ºÐ¼®ÇÑ´Ù.
		switch( GetData(pMsgList)->m_MsgType )
		{
		case EVT_SCREEN_FADE_OUT:
			//--------------------------------------------------------
			{
				SetFadeOut(GetData( pMsgList )->param[0]);
				break;
			}
		case EVT_SCREEN_FADE_IN:
			//--------------------------------------------------------
			{
				SetFadeIn(GetData( pMsgList )->param[0]);
				break;
			}
		case EVT_INIT_GAME:
			//--------------------------------------------------------
			{
				if(0 == GetData(pMsgList)->param[0])
				{
					LOAD_LOADING();
				}

				LoadFirstData(GetData( pMsgList )->param[0], GetData( pMsgList )->param[1], GetData( pMsgList )->param[2]);
				GetData( pMsgList )->param[0]++;

				if(7 > GetData( pMsgList )->param[0])
				{
					ADD_EVENT_MSG(EVT_INIT_GAME, 10, GetData( pMsgList )->param[0], GetData( pMsgList )->param[1], GetData( pMsgList )->param[2]);
				}
				else
				{
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 0, GetData( pMsgList )->param[1], 0, 1);
				}
				break;
			}
		case EVT_CHANGE_STAGE:
			//--------------------------------------------------------
			{
				//				if(1000 <= GetData( pMsgList )->param[0])
				//				{
				//					//Å« ¸¶À» ÀÌµ¿
				//					AppMain::ResvNextState(MS_GAME_WORLDMAP, GetData( pMsgList )->param[0], 0);
				//					isHoldingProcess = true;
				//					isHoldingPaint = true;
				//					isHoldingKey = true;
				//				}
				//				else
				//				{
				//	Äù½ºÆ®¿¡ µû¶ó¼­ ¸ÊÀÇ ¹øÈ£¸¦ ´Þ¸®ÇØÁØ´Ù.

				//	param2 ´Â Ã³À½ µé¾î¿Ã¶© 1·Î µé¾î¿Â´Ù.
				if(0 == GetData(pMsgList)->param[1] && 0 == GetData(pMsgList)->param[2])
				{
					//	¸Þ¼¼Áö¸¦ ³¯·ÁÁØ´Ù.
					bIsCrearMsg = true;
					if(!GET_EVENT_STATE())	{LOAD_LOADING();}
				}

				//	ÀÏ¹Ý ¸Ê ÀÌµ¿
				LoadStage(GetData(pMsgList)->param[0], GetData(pMsgList)->param[1]);
				GetData(pMsgList)->param[1]++;

				isHoldingProcess = true;
				isHoldingPaint = true;
				isHoldingKey = true;

				//	¼øÂ÷ÀûÀ¸·Î ·ÎµùÀ» ½ÃÄÑÁØ´Ù.
				if(3 > GetData(pMsgList)->param[1])
				{
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 0, GetData(pMsgList)->param[0], GetData(pMsgList)->param[1]);
				}
				else
				{
					UpdatePARSER_EVENT();


					/*
					//	ÀÌº¥Æ®¸¦ Ã¼Å©ÇÑ´Ù.
					switch(PARSER_EVENT())
					{
					case EVT_START_CINEMA:
					{
					RELEASE_LOADING();
					break;
					}
					case EVT_CHANGE_STAGE:
					{
					break;
					}
					case EVT_NULL:
					case EVT_TALK_STARTEVT:
					{
					RELEASE_LOADING();
					SetFadeIn(5);

					isHoldingProcess = false;
					isHoldingPaint = false;
					isHoldingKey = false;
					break;
					}
					case EVT_WATCH:
					{
					isHoldingPaint = false;
					isHoldingProcess = false;
					isHoldingKey = false;
					break;
					}
					}
					*/
				}
				//				}

				break;
			}
		case EVT_START_CINEMA:
			//--------------------------------------------------------
			{
				isHoldingPaint = false;
				isHoldingProcess = false;
				isHoldingKey = false;
				RELEASE_LOADING();

				if(0 != GetData( pMsgList )->param[1])
				{
					pField->DeleteFieldImage();
					Field* ppField = GL_NEW Field((void*) &s_ASpriteSet);
					//ppField->LoadMap(GetData( pMsgList )->param[1]);
					pCinema->Load_Cinematics(PACK_DATA_CINEMA, GetData( pMsgList )->param[0], 0, ppField);
				}
				else
				{
					//	ÇöÀç ÇÊµå¸¦ ³Ñ°ÜÁØ´Ù.
					pCinema->Load_Cinematics(PACK_DATA_CINEMA, GetData( pMsgList )->param[0], 0, pField);
				}

				SetFadeIn(5);
				break;
			}
		case EVT_END_CINEMA:
			//--------------------------------------------------------
			{
				isHoldingPaint = true;
				isHoldingProcess = true;
				isHoldingKey = true;

				pCinema->Release_Cinematics();

				if(pField != pCinema->pField)
				{
					SAFE_DELETE(pCinema->pField);
					pField->LoadFieldImage(pField->m_nSaveStageNum);
					pField->ReMatchFieldImage();
				}

				UpdatePARSER_EVENT();
				/*
				//	ÀÌº¥Æ®¸¦ Ã¼Å©ÇÑ´Ù.
				switch(PARSER_EVENT())
				{
				case EVT_NULL:
				case EVT_TALK_STARTEVT:
				{
				isHoldingPaint = false;
				isHoldingProcess = false;
				isHoldingKey = false;
				SetFadeIn(5);
				break;
				}
				case EVT_WATCH:
				{
				isHoldingPaint = false;
				isHoldingProcess = false;
				isHoldingKey = false;
				break;
				}
				default:
				{
				isHoldingPaint = true;
				isHoldingProcess = true;
				isHoldingKey = true;
				break;
				}

				}
				*/
				break;
			}
		case EVT_CINEMA_ADDEVT:		//	¾¾³×¸¶½Ã ÀÌº¥Æ®·Î ³Ñ¾î¿À´Â °ªµé
			//--------------------------------------------------------
			{
				switch(GetData( pMsgList )->param[0])
				{
				case 0:
					//------------------------------------------------------------
					{
						//	//GetData( pMsgList )->param[1] = 0;
						//	//GetData( pMsgList )->param[2] = 1;

						pCinema->Pause_Cinematics();
						pFieldUi->SetTalkCinema(GetData( pMsgList )->param[1],
							GetData( pMsgList )->param[2]);//´ë»çÃ¢ ¶ç¿ì±â
						//pCinema->Load_Cinematics(PACK_DATA_CINEMA, DATA_CINEMA_SCENE1, 1, pField);
						break;
					}
				}
				break;
			}
		case EVT_GAME_KEYEVENT:	//	0¹øÀº ¾²¸é ¾ÈµÈ´Ù.	//°¢Á¾ Äù½ºÆ® °ü·Ã È£ÃâÀÚµéÀÇ ¿Ï·á¿©ºÎ Ã¼Å©¸¦ ´ã´ç
			//--------------------------------------------------------
			{
				//false °ªÀÌ ³Ñ¾î¿Â´Ù¸é NPC¿ÍÀÇ ´ëÈ­ÀÏ °æ¿ì¿¡ Á¤»óÀûÀÎ ´ëÈ­¸¦ È£ÃâÇÑ´Ù
				if(CheckEvent(GetData( pMsgList )->param[0]) == false)
				{//¸¶À»´ëÈ­
					pFieldUi->SetTalkNPC(pField->m_nVillageUniqueIdx, GetData( pMsgList )->param[0]);
				}
				break;
			}
		case EVT_TALK_STARTEVT:		//´ë»çÃ¢ ¶ç¿ì±â
			//--------------------------------------------------------
			{
				pFieldUi->SetTalkCinema(GetData( pMsgList )->param[0],
					GetData( pMsgList )->param[1]);
				break;
			}
		case EVT_TALK_ENDEVT:
			//--------------------------------------------------------
			{
				switch(GetData( pMsgList )->param[0])
				{
				case (-1):
					//------------------------------------------------------------
					{
						//	³²Àº ¾¾³×¸¶°¡ ÀÖÀ¸¸é ÁøÇàÇØÁØ´Ù.
						if(true == pCinema->s_cinematicsPause) 
						{
							pCinema->Resume_Cinematics();
						}
						else
						{
							UpdatePARSER_EVENT();

							//	ÀÌº¥Æ®¸¦ Ã¼Å©ÇÑ´Ù.
							//PARSER_EVENT();
						}

						break;
					}				
				}
				break;
			}
		case EVT_PROLOGUE:
			//--------------------------------------------------------
			{
				LoadPrologue(DATA_TALK_OPENING, GetData( pMsgList )->param[0]);
				break;
			}
		case EVT_WATCH:
			//--------------------------------------------------------
			{
				SetTimerEvent(GetData( pMsgList )->param[0]);
				break;
			}
		case EVT_ADD_MONSTER:
			//--------------------------------------------------------
			{
				AddRegenMonSetting(GetData( pMsgList )->param[0]);
				break;
			}
		case EVT_SET_CAHRPOS:
			//--------------------------------------------------------
			{
				//AddRegenMonSetting(GetData( pMsgList )->param[0]);
				if(hero)
				{
					hero->InitCharPos(GetData( pMsgList )->param[0], GetData( pMsgList )->param[1], GetData( pMsgList )->param[2]);
					s_Camera.cX = 0;
					SetCameraMove();
				}

				UpdatePARSER_EVENT();
				/*
				//	ÀÌº¥Æ®¸¦ Ã¼Å©ÇÑ´Ù.
				switch(PARSER_EVENT())
				{
				case EVT_NULL:
				case EVT_TALK_STARTEVT:
				case EVT_SET_CAHRPOS:
				{
				isHoldingPaint = false;
				isHoldingProcess = false;
				isHoldingKey = false;
				SetFadeIn(5);
				break;
				}
				case EVT_WATCH:
				{
				isHoldingPaint = false;
				isHoldingProcess = false;
				isHoldingKey = false;
				break;
				}
				default:
				{
				isHoldingPaint = true;
				isHoldingProcess = true;
				isHoldingKey = true;
				break;
				}

				}
				*/
				break;
			}
		}

		SAFE_DELETE( GetData(pMsgList) );
		pMsgList->Delete();
	}

	//	ÇÊµå ÀÌº¥Æ®µéÀ» ³¯·ÁÁØ´Ù.
	if(bIsCrearMsg)
	{
		CLEAR_EVENT_MSG();
	}
}

//---------------------------ÀÌ°ÅÀÌ°ÅÀÌ°ÅÀÌ°ÅÀÌ°ÅÀÌ°ÅÀÌ°ÅÀÌ°Å----------------------------------
bool GFieldBattle::CheckEvent(int param)
//--------------------------------------------------------------------------
{

	//GET_MAINQUEST_IDX() - ¸ÞÀÎÄù½ºÆ® ³Ñ¹ö
	switch(param)
	{
	case NPC_CALL_kail://Æ®·¹Á® ÇåÅÍ Ä«ÀÏ
		{
			if(MAIN_QUEST_findKail == GET_MAINQUEST_IDX()){//Æ®·¹Á® ÇåÅÍ Ä«ÀÏÀ» Ã£¾Æ¶ó
				//pFieldUi->SetTalkCinema(0, 0);
				SET_EVENT(4);
				PARSER_EVENT();
				return true;
			}
			if(MAIN_QUEST_oldMedal == GET_MAINQUEST_IDX()){//½º¸ô Å¸¿î ÃÊ¿ø ¿¡¼­ ³°Àº ¸Þ´Þ 10°³¸¦ ±¸ÇÏ¶ó!
				//10°³ ÀÌ»óÀÌ³Ä?
				if(pPopupUi->GET_Count(ITEM_CALL_medal) >= MAX_medal){
					pPopupUi->REMOVE_Item(ITEM_CALL_medal,ALL_DEL);	
					SET_EVENT(5);
					PARSER_EVENT();
					return true;
				}
			}
			if(MAIN_QUEST_callKail == GET_MAINQUEST_IDX()){//Ä«ÀÏÀÇ È£Ãâ
				SET_EVENT(6);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case NPC_CALL_kaien://Ä«ÀÌ¿£
		{
			if(MAIN_QUEST_goKaien == GET_MAINQUEST_IDX()){//Ä«ÀÌ¿£ ¿¡°Ô ¼Ò°³ÀåÀ» Àü´Þ ÇÏ¶ó
				SET_EVENT(7);
				PARSER_EVENT();
				return true;
			}
			if(MAIN_QUEST_returnKaien == GET_MAINQUEST_IDX()){//Ä«ÀÌ¿£ ¿¡°Ô µ¹¾Æ°¡¶ó
				SET_EVENT(12);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case NPC_CALL_citizen1://½Ã¹Î1
		{
			if(MAIN_QUEST_goCitizen1 == GET_MAINQUEST_IDX()){//¿¤½Ã¾È ¹®¸íÀÇ Á¤º¸¸¦ ¼öÁýÇÏ¶ó ½Ã¹Î 1
				SET_EVENT(8);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case NPC_CALL_citizen2://½Ã¹Î2
		{
			//int aaa = GET_MAINQUEST_IDX();
			if(MAIN_QUEST_goCitizen2 == GET_MAINQUEST_IDX()){//¿¤½Ã¾È ¹®¸íÀÇ Á¤º¸¸¦ ¼öÁýÇÏ¶ó ½Ã¹Î 2
				SET_EVENT(9);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case NPC_CALL_citizenK://½Ã¹Îk
		{
			if(MAIN_QUEST_goCitizenK == GET_MAINQUEST_IDX()){//¿¤½Ã¾È ¹®¸íÀÇ Á¤º¸¸¦ ¼öÁýÇÏ¶ó ½Ã¹Î K
				SET_EVENT(10);
				PARSER_EVENT();
				return true;
			}

			if(MAIN_QUEST_findCrystal == GET_MAINQUEST_IDX()){//ÀÚ¼öÁ¤À» ±¸ÇØ¿Í¼­ K¾¾¿Í ´ëÈ­ÇÏ¶ó 

				//10°³ ÀÌ»óÀÌ³Ä?
				if(pPopupUi->GET_Count(ITEM_CALL_crystal) >= MAX_crystal){
					pPopupUi->REMOVE_Item(ITEM_CALL_crystal,ALL_DEL);	
					SET_EVENT(11);
					PARSER_EVENT();
					return true;
				}

			}
			break;
		}
	case NPC_CALL_scholar://°í°íÇÐÀÚ
		{
			if(MAIN_QUEST_goScholar == GET_MAINQUEST_IDX()){//°í°íÇÐÀÚ¸¦ Ã£¾Æ¶ó
				SET_EVENT(13);
				PARSER_EVENT();
				return true;
			}
			break;
		} 
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case FIELD_CALL_caveOpen://µ¿±¼ ÀÔ±¸
		{
			if(MAIN_QUEST_findOpen == GET_MAINQUEST_IDX()){//µ¿±¼ ÀÔ±¸¸¦ Ã£¾Æ¶ó!!
				SET_EVENT(2);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case FIELD_CALL_smallTown://½º¸ô Å¸¿î
		{
			if(MAIN_QUEST_goSmallTown == GET_MAINQUEST_IDX()){//ÀÏÁö¸¦ µ¹·ÁÁÖÀÚ, ¼­ºê - ¹Ìµé Å¸¿îÀ¸·Î °¡¶ó
				SET_EVENT(14);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case FIELD_CALL_forest1://ÃÊ¿ø Ã¹¹øÂ° ºñ¿À´Â ÇÊµå
		{
			if(FIELD_CALL_forest1 == GET_MAINQUEST_IDX()){//ÀÏÁö¸¦ µ¹·ÁÁÖÀÚ, ¼­ºê - ½ÃÁî¸¦ Ã£¾Æ¶ó
				SET_EVENT(15);
				PARSER_EVENT();
				return true;
			}
			break;
		}
	case FIELD_CALL_forest2://ÃÊ¿ø µÎ¹øÂ° ºñ¿À´Â ÇÊµå
		{
			if(FIELD_CALL_forest2 == GET_MAINQUEST_IDX()){//ÀÏÁö¸¦ µ¹·ÁÁÖÀÚ, ¼­ºê - ¹ÙÀ§¸¦ ºÎ¼Å¶ó
				SET_EVENT(16);
				PARSER_EVENT();
				return true;
			}
			break;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case ITEM_CALL_tntBoom://Æø¾à
		{
			if(MAIN_QUEST_openDoor == GET_MAINQUEST_IDX()){//µ¿±¼ ÀÔ±¸¸¦ ¿­¾î¶ó!
				if(pPopupUi->GET_Count(ITEM_CALL_tntBoom) >= MAX_tntBoom){
					pPopupUi->REMOVE_Item(ITEM_CALL_tntBoom,ALL_DEL);
					SET_EVENT(3);
					PARSER_EVENT();
					return true;
				}
			}
			break;
		}
	case ITEM_CALL_diary://ÀÏÁö
		{
			if(MAIN_QUEST_findDiary == GET_MAINQUEST_IDX()){//ÀÒ¾î¹ö¸° ÀÏÁö¸¦ Ã£¾Æ¶ó
				if(pPopupUi->GET_Count(ITEM_CALL_diary) >= MAX_diary){
					SET_EVENT(14);
					PARSER_EVENT();
					return true;
				}
			}
			break;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	case TIMER_CALL_end://Å¸ÀÌ¸Ó
		{
			//switch(GET_MAINQUEST_IDX()){//µ¿±¼ ÀÔ±¸¸¦ ¿­¾î¶ó!
			//	case kfhasldfkj:
			//			if(¹ÙÀ§ ´Ù ÆÄ±«){
			//			}else{
			//				SET_EVENT(3);
			//				PARSER_EVENT();
			//				pPopupUi->REMOVE_Item(ITEM_CALL_tntBoom,1);
			//			}
			int a = 0;
			break;

		}


	}
	return false;
}
//--------------------------------------------------------------------------
void GFieldBattle::SetFadeOut(int time)
//--------------------------------------------------------------------------
{
	m_nIsDarkScreen = true;
	if(0 == time)	{time = 5;}
	m_nFadeOutTime = time;
}


//--------------------------------------------------------------------------
void GFieldBattle::SetFadeIn(int time)
//--------------------------------------------------------------------------
{
	m_nIsDarkScreen = false;
	if(0 == time)	{time = 5;}
	m_nFadeInTime = time;
}

//--------------------------------------------------------------------------
void GFieldBattle::LoadPrologue(int idx, int textIdx)
//--------------------------------------------------------------------------
{

	m_nPrologueTimer = 0;
	m_bIsPlayPrologue = true;
	pFieldUi->SetTalkCinema(idx-DATA_TALK_SCENE_00, textIdx);
}


//--------------------------------------------------------------------------
bool GFieldBattle::UpdatePrologue()
//--------------------------------------------------------------------------
{
	if(false == m_bIsPlayPrologue)	{return false;}
	//	if(false == pFieldUi->s_TalkBox.View)	{return false;}

	m_nPrologueTimer++;

	if( 40 < m_nPrologueTimer)
	{
		m_nPrologueTimer = 0;							//	´ÙÀ½ ½ÅÀ¸·Î ¾÷µ¥ÀÌÆ® ÇØÁØ´Ù.
		pFieldUi->KeyTalkBox(MH_KEY_5, false);			//	Å° ÀÌº¥Æ®

		if(false == pFieldUi->s_TalkBox.View)
		{
			m_bIsPlayPrologue = false;
		}
	}

	return true;
}

//--------------------------------------------------------------------------
bool GFieldBattle::PaintPrologue()
//--------------------------------------------------------------------------
{
	if(false == m_bIsPlayPrologue)	{return false;}
	//	if(false == pFieldUi->s_TalkBox.View)	{return false;}

	//	ÆäÀÌµå ¾Æ¿ô

	if(30 < m_nPrologueTimer)
	{
		SUTIL_SetColor(0x000000);
		SUTIL_FillRect(0,0,240,320);
		return true;
	}

	if(20 < m_nPrologueTimer)
	{
		Paint_ChangeScrollEvent(1);
		return true;
	}

	SUTIL_SetColor(0x000000);
	SUTIL_FillRect(0,0,240,320);

	pFieldUi->PaintTalkBox();

	//	ÆäÀÌµå ÀÎ
	if(5 > m_nPrologueTimer)
	{
		for(int loop = 0; loop < 5-m_nPrologueTimer; loop++)
		{
			Paint_ChangeScrollEvent(1);
		}
	}

	return true;
}


//--------------------------------------------------------------------------
void GFieldBattle::ProcessTimerEvent()
//--------------------------------------------------------------------------
{
	if(0 < m_nSaveEvtTimer)
	{
		m_nSaveEvtTimer--;

		if(0 == m_nSaveEvtTimer)
		{
			ADD_EVENT_MSG(EVT_GAME_KEYEVENT, 0, TIMER_CALL_end);
			//	ÀÌº¥Æ®¸¦ º¸³½´Ù.
		}
	}
}


//--------------------------------------------------------------------------
void GFieldBattle::SetTimerEvent(int nTime)
//--------------------------------------------------------------------------
{
	m_nSaveEvtTimer = nTime;
}


//--------------------------------------------------------------------------
void GFieldBattle::UpdatePARSER_EVENT()
//--------------------------------------------------------------------------
{
	//	·ÎµùÀÌ ³¡³µÀ» °æ¿ì
	RELEASE_LOADING();

	switch(PARSER_EVENT())
	{
	case EVT_NULL:
	case EVT_TALK_STARTEVT:
		{
			if(m_nIsDarkScreen)
			{
				SetFadeIn(5);
			}
			isHoldingProcess = false;
			isHoldingPaint = false;
			isHoldingKey = false;
			break;
		}

		//EVT_CHANGE_STAGE
		//EVT_WATCH
		//EVT_SET_CAHRPOS
		//		case EVT_START_CINEMA:
		//
		//		{
		//		}
	}
}

/*
//--------------------------------------------------------------------------
void GFieldBattle::ProcessWorldMap()
//--------------------------------------------------------------------------
{
//	pCinema->Update_Cinematics();
}


//--------------------------------------------------------------------------
void GFieldBattle::PaintWorldMap()
//--------------------------------------------------------------------------
{

SUTIL_SetColor(0x000000);
SUTIL_FillRect(0,0,240,320);

//	pCinema->Paint_Cinematics();

switch(m_nEventIndex)
{
case 1000:
//------------------------------------------------------------
{
_SUTIL->pFont->setColor(0xFFFFFF);
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"1 : GO TO SMALL TOWN", 50, 100, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"2 : GO TO FOREST1", 50, 120, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"3 : GO TO CRYSTAL CAVE", 50, 141, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"4 : GO TO MIDDLE TOWN ROAD", 50, 160, 0);//Text
break;
}

case 1001:
//------------------------------------------------------------
{
_SUTIL->pFont->setColor(0xFFFFFF);
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"1 : GO TO MIDDLE TOWN", 50, 100, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"2 : GO TO WEST FOREST", 50, 120, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"3 : GO TO EAST FOREST", 50, 140, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"4 : GO TO MIST CAVE", 50, 160, 0);//Text
_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"5 : GO TO SMALL TOWN ROAD", 50, 180, 0);//Text
break;
}

}
//	SUTIL_PaintAsprite(m_pWorldMapAsIns, S_NOT_INCLUDE_SORT);

}

//--------------------------------------------------------------------------
void GFieldBattle::KeyEvtWorldMap(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{
switch(m_nEventIndex)
{
case 1000:
//------------------------------------------------------------
{
switch(m_keyCode)
{
case MH_KEY_1:	{AppMain::ResvNextState(MS_GAME_FIELD, 801, 0);	break;}
case MH_KEY_2:	{AppMain::ResvNextState(MS_GAME_FIELD, 101, 1950);		break;}
case MH_KEY_3:	{AppMain::ResvNextState(MS_GAME_FIELD, 200, 0);	break;}
case MH_KEY_4:	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 0);		break;}
}

break;
}
case 1001:
//------------------------------------------------------------
{
switch(m_keyCode)
{
case MH_KEY_1:	{AppMain::ResvNextState(MS_GAME_FIELD, 803, 0);		break;}
case MH_KEY_2:	{AppMain::ResvNextState(MS_GAME_FIELD, 105, 450);		break;}
case MH_KEY_3:	{AppMain::ResvNextState(MS_GAME_FIELD, 113, 50);		break;}
case MH_KEY_4:	{AppMain::ResvNextState(MS_GAME_FIELD, 205, 50);		break;}
case MH_KEY_5:	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 1450);		break;}
}

break;
}

}
}
*/

