#include "Field.h"
#include "Minimap.h"

#include "SObjectMgr.h"


int Field::m_nFieldSize_X = 0;

int Field::m_nWayMoveCharx = 0;
int Field::m_nWayMoveChary = 0;


//--------------------------------------------------------------------------
Field::Field(void* _sASpriteSet)
//--------------------------------------------------------------------------
{
	m_nWayMoveCharx = 0;

	s_ASpriteSet = (ASpriteSet*)_sASpriteSet;

	pLayerList = GL_NEW List2<BackLayer*>();
	pMiddleLayerList = GL_NEW List2<BackLayer*>();

	pEnvirSprList = GL_NEW List2<ASprite*>();

	pEvtWayList = GL_NEW List2<MAP_EVT_WAY*>();

	pKeyInputEvt = GL_NEW List2<VEvent*>();

	pDropItem = GL_NEW List2<ITEM_STRUCT*>();

	pDontgoRect = GL_NEW List2<DONT_GO_RECT*>();

	pEventRect = GL_NEW List2<EVENT_RECT*>();
	m_nLastZoneEvent = 0;

//	pMonsterGenRect = GL_NEW List2<MONSTER_REGEN_DATA*>();


	pWayAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_BGOBJECT_UI);
//	m_pFieldUiDamageNumAsIns = GL_NEW ASpriteInstance(m_pFieldUiDamageNumAs, 0, 0, NULL);// 0번째 배열, 실사용시는 define 필요
//	m_pFieldUiDamageNumAs->SetBlendFrame(FRAME_DAMAGE_NUM_BLEND);


//	InitState(stageIdx);
}


//--------------------------------------------------------------------------
Field::~Field()
//--------------------------------------------------------------------------
{
	DeleteFieldImage();

//	for(int loop = 0; loop < SPRITE_MAP_MAX; loop++)
//	{
//		if(pFieldAs[loop])	{SUTIL_FreeSprite(pFieldAs[loop]);}
//	}

	InitList(pLayerList);
	while(NotEndList(pLayerList))
	{
		SAFE_DELETE(GetData(pLayerList));
		pLayerList->Delete();
	}
	SAFE_DELETE(pLayerList);

	InitList(pMiddleLayerList);
	while(NotEndList(pMiddleLayerList))
	{
		SAFE_DELETE(GetData(pMiddleLayerList));
		pMiddleLayerList->Delete();
	}
	SAFE_DELETE(pMiddleLayerList);

	SAFE_DELETE(pFrontLayer);

	//	리스트만 지워준다.
	InitList(pEnvirSprList);
	while(NotEndList(pEnvirSprList))
	{
		pEnvirSprList->Delete();
	}
	SAFE_DELETE(pEnvirSprList);

	Release_EVT_WAY();
	SAFE_DELETE(pEvtWayList);

	Release_EVT_INPUTKEY();
	SAFE_DELETE(pKeyInputEvt);

	InitList(pDropItem);
	while(NotEndList(pDropItem))
	{
		SUTIL_FreeSpriteInstance(GetData(pDropItem)->pInstance);
		SAFE_DELETE(GetData(pDropItem)->item);
		SAFE_DELETE(GetData(pDropItem));
		pDropItem->Delete();
	}
	SAFE_DELETE(pDropItem);

	SUTIL_FreeSprite(pWayAs);

	InitList(pDontgoRect);
	while(NotEndList(pDontgoRect))
	{
		SAFE_DELETE(GetData(pDontgoRect));
		pDontgoRect->Delete();
	}
	SAFE_DELETE(pDontgoRect);

	InitList(pEventRect);
	while(NotEndList(pEventRect))
	{
		SAFE_DELETE(GetData(pEventRect));
		pEventRect->Delete();
	}
	SAFE_DELETE(pEventRect);

//	InitList(pMonsterGenRect);
//	while(NotEndList(pMonsterGenRect))
//	{
//		SAFE_DELETE(GetData(pMonsterGenRect));
//		pMonsterGenRect->Delete();
//	}
//	SAFE_DELETE(pMonsterGenRect);
}


//--------------------------------------------------------------------------
void Field::Paint(bool isCinema)
//--------------------------------------------------------------------------
{
//	SUTIL_SetColor(0x000000);
//	SUTIL_FillRect(0,0,240,320);

	if(900 == m_nSaveStageNum)
	{
		SUTIL_SetColor(0x000000);
		SUTIL_FillRect(0,0,240,320);
	}
	else if(1000 <= m_nSaveStageNum)
	{
		PaintWorldMap();
	}
	else
	{
		InitList(pLayerList);
		while(NotEndList(pLayerList))
		{
			GetData(pLayerList)->Paint();
			MoveNext(pLayerList);
		}

		if(false == isCinema)
		{
			Paint_EVT_INPUTKEY();
			PaintDropItem();
			Paint_EVT_WAY();
			Paint_EVT_Rect();
		}
	}
}

//--------------------------------------------------------------------------
void Field::FrontPaint()
//--------------------------------------------------------------------------
{
	if(pFrontLayer)
	{
		pFrontLayer->Paint();
	}
}


//--------------------------------------------------------------------------
void Field::MiddlePaint()
//--------------------------------------------------------------------------
{
	if(900 > m_nSaveStageNum)
	{
		InitList(pMiddleLayerList);
		while(NotEndList(pMiddleLayerList))
		{
			GetData(pMiddleLayerList)->Paint();
			MoveNext(pMiddleLayerList);
		}
	}
}


//--------------------------------------------------------------------------
void Field::Process()
//--------------------------------------------------------------------------
{
	if(pFrontLayer)
	{
		pFrontLayer->SetAngle(m_nSrcCamAngle_X);
		//GetData(pLayerList)->Process();
		pFrontLayer->Process();
	}




	InitList(pLayerList);
	while(NotEndList(pLayerList))
	{
		GetData(pLayerList)->SetAngle(m_nSrcCamAngle_X);
		GetData(pLayerList)->Process();
		MoveNext(pLayerList);
	}

	InitList(pMiddleLayerList);
	while(NotEndList(pMiddleLayerList))
	{
		GetData(pMiddleLayerList)->SetAngle(m_nSrcCamAngle_X);
		GetData(pMiddleLayerList)->Process();
		MoveNext(pMiddleLayerList);
	}

	Process_EVT_INPUTKEY();

	ProcessDropItem();

	ProcessWorldMap();

//	 dbg(">>y Yellow >>a Aqua >>r Red >>g Green >>b Blue >>p  puple >>w  White \n" ); 
//	 dbg(">>>Y Yellow >>>a Aqua >>>r Red >>>g Green >>>b Blue >>>p  puple >>>w White \n"); 
//	 dbg(" >>a pause >>>b Test >>pause \n");

//	 dbg( "int %d char* %s char %c\n", 100, "가나다afadfas", 'A');
}


//--------------------------------------------------------------------------
void Field::GetMessage()
//--------------------------------------------------------------------------
{

}




//--------------------------------------------------------------------------
void Field::LoadMapLayer(BackLayer* pBackLayer, char* packName, int packIndex, bool isRepeat)
//--------------------------------------------------------------------------
{
	BackLayerObject* pBackObject = NULL;
	int tmpsprid = 0;

//	SUTIL_Data_init(packName);
//	SUTIL_Data_open(packIndex);

	SUTIL_Data_init(packName);
	byte* pBuf = SUTIL_Data_readAll(packIndex);
	SUTIL_Data_free();

	int AsframeNum = 0;
	int tmpId = 0;
	int nBufCnt = 0;

	ASprite*	tmpASprite;
	while(1)
	{
		
		nBufCnt++;											//	0x08		읽고 버린다.
		tmpId				= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;

		switch(tmpId)
		{
			case EVT_NPC:				//	NPC
			//---------------------------------------------------------------
			{
				int x				 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	x
				int y				 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	y
				int imgidx			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	인자1
				int evtCode			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;		//	인자2
				nBufCnt+=2;				//	더미
				nBufCnt+=2;				//	
				nBufCnt+=2;				//	

//				pKeyInputEvt->Insert_next(pTmpStoreNpc);

				x += pBackLayer->m_nLayerSizeX;
				SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
				pObjectMgr->Add(OBJ_M_NPC, 0, 0, x, y );



/*
				int x				 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	x
				int y				 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	y
				int imgidx			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	인자1
				Npc* pTmpStoreNpc = GL_NEW Npc(imgidx, x, y);
				pTmpStoreNpc->m_nType = tmpId;
				pTmpStoreNpc->m_nSaveEvtCode = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;		//	인자2
				nBufCnt+=2;				//	더미
				nBufCnt+=2;				//	
				nBufCnt+=2;				//	

				pKeyInputEvt->Insert_next(pTmpStoreNpc);


				SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
				pObjectMgr->Add(new SNpc(OBJ_M_NPC, 0, 0, x, y) );

*/
				continue;
			}
			case EVT_DONT_GO_RECT:				//	EVT_DONT_GO_RECT
			//---------------------------------------------------------------
			{
				DONT_GO_RECT* pTmpRect = GL_NEW DONT_GO_RECT();

				pTmpRect->sx			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	x
				pTmpRect->sy			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	y
				pTmpRect->dx			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	w
				pTmpRect->dy			 = (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	h
				nBufCnt+=2;
				nBufCnt+=2;
				nBufCnt+=2;
				nBufCnt+=2;

				//	패턴이기 때문에 더해줘야 된다.
				pTmpRect->sx += pBackLayer->m_nLayerSizeX;

				pDontgoRect->Insert_next(pTmpRect);
				continue;
			}
			case EVT_END_OF_LAYER:			
			//---------------------------------------------------------------
			{
				pBackLayer->m_nLayerSizeX += (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;
				break;
			}
			default:
			//---------------------------------------------------------------
			{
				//	리피트 일경우는 이벤트만 복사해야되므로 이미지패턴은 재로드하지 않는다.
				if(true == isRepeat)
				{
					nBufCnt+=2;
					nBufCnt+=2;
					nBufCnt+=2;
					nBufCnt+=2;
					nBufCnt+=2;
					nBufCnt+=2;
					nBufCnt+=2;
					continue;
				}


				if(100 <= tmpId)		//현재 오브젝트의 스프라이트 넘버값을 알려준다.
				{
					tmpsprid = (tmpId-100)/100;
					tmpASprite = pFieldAs[tmpsprid];
				}
				else
				{
					break;
				}

				pBackObject	= GL_NEW BackLayerObject();
				pBackObject->x			= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	x
				pBackObject->y			= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	y

										  (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	읽고 버린다.
				pBackObject->type		= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	고유 타입
				pBackObject->drawtype	= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	draw type	//	0이면 frame, 1이면 animation
				AsframeNum				= (short)( (pBuf[nBufCnt]) | (pBuf[nBufCnt+1] << 8) );	nBufCnt+=2;				//	draw num
										  nBufCnt+=2;;											//	임시3		읽고 버린다.

				pBackObject->spridx = tmpsprid;
				pBackObject->pAsIns = GL_NEW ASpriteInstance(tmpASprite, 0, 0, NULL);
				pBackObject->pAsIns->SetAniMoveLock(true);

				if(0 == pBackObject->drawtype)		{SUTIL_SetTypeFrameAsprite(pBackObject->pAsIns, AsframeNum);}
				else if(1 == pBackObject->drawtype)
				{
					SUTIL_SetTypeAniAsprite(pBackObject->pAsIns, AsframeNum);
					SUTIL_SetLoopAsprite(pBackObject->pAsIns, true);
				}
				
			//	pBackObject->adjustx = tmpASprite->GetFrameX(AsframeNum);
			//	pBackObject->width = tmpASprite->GetFrameWidth(AsframeNum);
				pBackObject->x += pBackLayer->m_nLayerSizeX;
			//	pBackObject->y += pBackLayer->m_nBaseYLine;
			//	pBackObject->x += pBackObject->adjustx;
				pBackObject->z = 0;

				pBackObject->startx = pBackObject->x + tmpASprite->GetFrameX(AsframeNum);
				pBackObject->endx = pBackObject->startx + tmpASprite->GetFrameWidth(AsframeNum);

//				int aaaa = tmpASprite->GetFrameWidth(AsframeNum);
//				if(200 < aaaa)
//				{
//					int b = 0;
//				}

				pBackLayer->InsertObject(pBackObject);

				continue;;
			}
		}

		break;
	}

	SAFE_DELETE(pBuf);
	//SUTIL_Data_free();

	//	로드를 한후 이미지를 로드한다. (파일 인풋때문에)
/*
	for(InitList(pKeyInputEvt);NotEndList(pKeyInputEvt);MoveNext(pKeyInputEvt))
	{
		switch(GetData(pKeyInputEvt)->m_nType )
		{
			case EVT_NPC:
			//--------------------------------------------------------------
			{
				((Npc*)GetData(pKeyInputEvt))->ReadyObject(s_ASpriteSet);
				break;
			}
//			case EVT_BARREL:
//			//--------------------------------------------------------------
//			{
//				((CrushObj*)GetData(pKeyInputEvt))->ReadyObject(s_ASpriteSet);
//				break;
//			}

			
		}
	}
*/
/*

//		if(1 == tmpId)		//	마지막 데이타
//		{
//			pBackLayer->m_nLayerSizeX += (short)SUTIL_Data_readU16();
//			break;
//		}
		else if(2 == tmpId || 3 == tmpId)			//	임시값 그냥 흘러간다.
		{
		}
		else if(11 == tmpId)							//	랙트를 그려야 한다.
		{
			(short)SUTIL_Data_readU16();				//	x
			(short)SUTIL_Data_readU16();				//	y
			(short)SUTIL_Data_readU16();				//	고유 타입
			(short)SUTIL_Data_readU16();				//	draw type	//	0이면 frame, 1이면 animation
			(short)SUTIL_Data_readU16();				//	draw num
			(short)SUTIL_Data_readU16();											//	임시3		읽고 버린다.
			(short)SUTIL_Data_readU16();											//	임시3		읽고 버린다.
			continue;
		}
		else
		{
			//DONT_GO_RECT* pTmpRect;

			if(100 <= tmpId)		//현재 오브젝트의 스프라이트 넘버값을 알려준다.
			{
				tmpsprid = (tmpId-100)/100;
				tmpASprite = pFieldAs[tmpsprid];
			}
		}

		pBackObject	= GL_NEW BackLayerObject();
		pBackObject->x			= (short)SUTIL_Data_readU16();				//	x
		pBackObject->y			= (short)SUTIL_Data_readU16();				//	y

								  (short)SUTIL_Data_readU16();				//	읽고 버린다.
		pBackObject->type		= (short)SUTIL_Data_readU16();				//	고유 타입
		pBackObject->drawtype	= (short)SUTIL_Data_readU16();				//	draw type	//	0이면 frame, 1이면 animation
		AsframeNum				= (short)SUTIL_Data_readU16();				//	draw num
								  (short)SUTIL_Data_readU16();				//	임시3		읽고 버린다.

		pBackObject->spridx = tmpsprid;
		pBackObject->pAsIns = GL_NEW ASpriteInstance(tmpASprite, 0, 0, NULL);
		pBackObject->pAsIns->SetAniMoveLock(true);

		if(0 == pBackObject->drawtype)		{SUTIL_SetTypeFrameAsprite(pBackObject->pAsIns, AsframeNum);}
		else if(1 == pBackObject->drawtype)
		{
			SUTIL_SetTypeAniAsprite(pBackObject->pAsIns, AsframeNum);
			SUTIL_SetLoopAsprite(pBackObject->pAsIns, true);
		}
		
	//	pBackObject->adjustx = tmpASprite->GetFrameX(AsframeNum);
	//	pBackObject->width = tmpASprite->GetFrameWidth(AsframeNum);
		pBackObject->x += pBackLayer->m_nLayerSizeX;
		pBackObject->y += pBackLayer->m_nBaseYLine;
	//	pBackObject->x += pBackObject->adjustx;
		pBackObject->z = 0;

		pBackObject->startx = pBackObject->x + tmpASprite->GetFrameX(AsframeNum);
		pBackObject->endx = pBackObject->startx + tmpASprite->GetFrameWidth(AsframeNum);

		pBackLayer->InsertObject(pBackObject);
	}

	SUTIL_Data_free();
*/
}




//--------------------------------------------------------------------------
void Field::LoadMap(void* pMinimapData)
//--------------------------------------------------------------------------
{
	int loop = 0;

	BackLayer* pBackLayer = NULL;
	m_nSrcCamAngle_X = 0;

	m_pMiniMapData = pMinimapData;
//	m_pMiniMapData = (MiniMapData*)pMinimapData;
	MiniMapData* pMiniMapData = (MiniMapData*)m_pMiniMapData;

	//	리소스 해제
	ReleaseMap(pMiniMapData->m_nResType);

	//	스프라이트 로드
	if(m_nSaveResType != pMiniMapData->m_nResType)
	{
		m_nSaveResType = pMiniMapData->m_nResType;
		LoadFieldImage(m_nSaveResType);
	}

	//	이동영역 제한 리스트
	MoveHead(pDontgoRect);

	char packName[3];
	int baseIdx[4];

	switch(m_nSaveResType)
	{
		case 1:		// forest
		//-------------------------------------------------------------------
		{
			strcpy(packName, PACK_DATA_MAP_FOREST);	

			baseIdx[0] = 0;			//	landscape 시작
			baseIdx[1] = 1;			//	ground 시작
			baseIdx[2] = 2;			//	up_obj 시작
			baseIdx[3] = 7;			//	down_obj 시작
			break;
		}
		case 8:		// village
		//-------------------------------------------------------------------
		{
			strcpy(packName, PACK_DATA_MAP_VILLAGE);	

			baseIdx[0] = 0;			//	landscape 시작
			baseIdx[1] = 1;			//	ground 시작
			baseIdx[2] = 2;			//	up_obj 시작
			baseIdx[3] = 5;			//	down_obj 시작
			break;
		}
	}

	//	인덱스가 1부터 시작한다.
	baseIdx[0] -= 1;
	baseIdx[1] -= 1;
	baseIdx[2] -= 1;
	baseIdx[3] -= 1;
	
	// 맵데이타 로드
	MoveHead(pLayerList);

	//	배경 레이어 로드 //////////////////////////////////////////////////////////
	pBackLayer = GL_NEW BackLayer();
	pBackLayer->m_nMoveRate = 30;
	LoadMapLayer(pBackLayer, packName, baseIdx[0] + pMiniMapData->m_nBackType);
	pLayerList->Insert_next(pBackLayer);
//	DBGPRINTF(" baseIdx[0], >  %d \n",  baseIdx[0] + pMiniMapData->m_nBackType);

	//	바닥 레이어 로드 /////////////////////////////////////////////////////////
	pBackLayer = GL_NEW BackLayer();
	pBackLayer->m_nMoveRate = 100;
	LoadMapLayer(pBackLayer, packName, baseIdx[1]+1 );
	pLayerList->Insert_next(pBackLayer);
//	DBGPRINTF("baseIdx[1], >  %d \n", baseIdx[1]+1);

	//	위 오브젝트 레이어 로드 //////////////////////////////////////////////////////////
	pBackLayer = GL_NEW BackLayer();
	pBackLayer->SetSortOption(S_INCLUDE_SORT);
	pBackLayer->m_nMoveRate = 100;
	for(loop = 0; loop < pMiniMapData->m_nCellCount; loop++)
	{
		if(0 == pMiniMapData->m_sMapCellData[loop].m_PtnObject)	{break;}
		LoadMapLayer(pBackLayer, packName, baseIdx[2] + pMiniMapData->m_sMapCellData[loop].m_PtnObject );
//		DBGPRINTF("baseIdx[2], >  %d \n", baseIdx[2] + pMiniMapData->m_sMapCellData[loop].m_PtnObject);
	}
	pLayerList->Insert_next(pBackLayer);


	//	앞 오브젝트 레이어 로드 //////////////////////////////////////////////
	pFrontLayer = GL_NEW BackLayer();

	if(8 == m_nSaveResType)
	{
		pFrontLayer->m_nMoveRate = 100;
	}
	else
	{
		pFrontLayer->m_nMoveRate = 140;
	}

	for(loop = 0; loop < pMiniMapData->m_nCellCount; loop++)
	{
		if(0 == pMiniMapData->m_sMapCellData[loop].m_PtnFrontGround)	{break;}
		LoadMapLayer(pFrontLayer, packName, baseIdx[3] + pMiniMapData->m_sMapCellData[loop].m_PtnFrontGround );
//		DBGPRINTF("baseIdx[3], >  %d \n", baseIdx[3] + pMiniMapData->m_sMapCellData[loop].m_PtnFrontGround);
	}

	//	맵 정보
	m_nFieldSize_X = pMiniMapData->m_nCellCount*SECTOR_SIZE;


	//	맵 화살표 정보
	Release_EVT_WAY();

	MAP_EVT_WAY* pEvtWay = NULL;

	for(loop = 0; loop < pMiniMapData->m_nCellCount; loop++)
	{
		if(MNC_RIGHT_LINK & pMiniMapData->m_sMapCellData[loop].m_nPtnType)
		{
			pEvtWay = GL_NEW MAP_EVT_WAY();
			pEvtWay->pArrawAsIns = GL_NEW ASpriteInstance(pWayAs, (SECTOR_SIZE*(loop+1))-20, (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2, NULL);// 0번째 배열, 실사용시는 define 필요
			SUTIL_SetTypeAniAsprite(pEvtWay->pArrawAsIns, ANIM_BG_OBJECT_ARROW_RIGHT);
			SUTIL_SetLoopAsprite(pEvtWay->pArrawAsIns, true);
			pEvtWayList->Insert_next(pEvtWay);
		}

		if(MNC_LEFT_LINK & pMiniMapData->m_sMapCellData[loop].m_nPtnType)
		{
			pEvtWay = GL_NEW MAP_EVT_WAY();
			pEvtWay->pArrawAsIns = GL_NEW ASpriteInstance(pWayAs, (SECTOR_SIZE*(loop+0))+20, (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2, NULL);// 0번째 배열, 실사용시는 define 필요
			SUTIL_SetTypeAniAsprite(pEvtWay->pArrawAsIns, ANIM_BG_OBJECT_ARROW_LEFT);
			SUTIL_SetLoopAsprite(pEvtWay->pArrawAsIns, true);
			pEvtWayList->Insert_next(pEvtWay);
		}

		if(MNC_UP_LINK & pMiniMapData->m_sMapCellData[loop].m_nPtnType)
		{
			pEvtWay = GL_NEW MAP_EVT_WAY();
			pEvtWay->pArrawAsIns = GL_NEW ASpriteInstance(pWayAs, (SECTOR_SIZE*(loop))+(SECTOR_SIZE/2), (MAP_DEF_CHAR_UP_Y), NULL);// 0번째 배열, 실사용시는 define 필요
			SUTIL_SetTypeAniAsprite(pEvtWay->pArrawAsIns, ANIM_BG_OBJECT_ARROW_UP);
			SUTIL_SetLoopAsprite(pEvtWay->pArrawAsIns, true);
			pEvtWayList->Insert_next(pEvtWay);
		}

		if(MNC_DOWN_LINK & pMiniMapData->m_sMapCellData[loop].m_nPtnType)
		{
			pEvtWay = GL_NEW MAP_EVT_WAY();
			pEvtWay->pArrawAsIns = GL_NEW ASpriteInstance(pWayAs, (SECTOR_SIZE*(loop))+(SECTOR_SIZE/2), (MAP_DEF_CHAR_DOWN_Y), NULL);// 0번째 배열, 실사용시는 define 필요
			SUTIL_SetTypeAniAsprite(pEvtWay->pArrawAsIns, ANIM_BG_OBJECT_ARROW_DOWN);
			SUTIL_SetLoopAsprite(pEvtWay->pArrawAsIns, true);
			pEvtWayList->Insert_next(pEvtWay);
		}
	}

	//	캐릭터 위치 설정


/*

	MiniMapData* pMiniMapData = (MiniMapData*)m_pMiniMapData;

	for(loop = 0; loop < pMiniMapData->m_nCellCount; loop++)
	{

m_nPtnType = MNC_RIGHT_LINK | MNC_DOWN_LINK;


		if(MNC_RIGHT_LINK & pMiniMapData->m_sMapCellData[loop].m_nPtnType)
		{

		}

		MNC_DOWN_LINK
	}


	for(InitList(pEvtWayList);NotEndList(pEvtWayList);MoveNext(pEvtWayList))
	{
		GetData(pEvtWayList)->pArrawAsIns->CameraX = -m_nSrcCamAngle_X;
		SUTIL_PaintAsprite(GetData(pEvtWayList)->pArrawAsIns, S_NOT_INCLUDE_SORT);
	}


*/


//				pEvtWay = GL_NEW MAP_EVT_WAY();
//				pEvtWay->switchtime	 = 0;
/*
				pEvtWay->sx			 = (short)SUTIL_Data_readU16();				//	x
				pEvtWay->sy			 = (short)SUTIL_Data_readU16();				//	y
				pEvtWay->dx			 = (short)SUTIL_Data_readU16();				//	인자1
				pEvtWay->dy			 = (short)SUTIL_Data_readU16();				//	인자2
				pEvtWay->type		 = (short)SUTIL_Data_readU16();				//	언제나:1 전투후:2
				pEvtWay->nextStage	 = (short)SUTIL_Data_readU16();				//	다음 움직일 스테이지
				pEvtWay->charx		 = (short)SUTIL_Data_readU16();				//	캐릭터 위치x
				pEvtWay->chary		 = (short)SUTIL_Data_readU16();				//	캐릭터 위치y

				pEvtWay->dx += pEvtWay->sx;										//	넓이를 좌표로 바꿔서 저장한다.
				pEvtWay->dy += pEvtWay->sy;

				//	화살표 셋팅
				arrowpointx = (pEvtWay->sx+pEvtWay->dx)/2;
				arrowpointy = (pEvtWay->sy+pEvtWay->dy)/2;

				//	에니메이션 셋팅
				arrowtype = ANIM_BG_OBJECT_ARROW_RIGHT;
				if(150 > arrowpointy)	{arrowtype = ANIM_BG_OBJECT_ARROW_UP;}
				if(250 < arrowpointy)	{arrowtype = ANIM_BG_OBJECT_ARROW_DOWN;}
				if(0 > arrowpointx)	{arrowtype = ANIM_BG_OBJECT_ARROW_LEFT;}

				switch(arrowtype)
				{
					case ANIM_BG_OBJECT_ARROW_DOWN:	{arrowpointy = pEvtWay->sy;		break;}
					case ANIM_BG_OBJECT_ARROW_UP:	{arrowpointy = pEvtWay->dy;		break;}
					case ANIM_BG_OBJECT_ARROW_LEFT:	{arrowpointx = pEvtWay->dx+20;	break;}
					case ANIM_BG_OBJECT_ARROW_RIGHT:{arrowpointx = pEvtWay->sx-20;	break;}
					default:	{break;}
				}

				pEvtWay->pArrawAsIns = GL_NEW ASpriteInstance(pWayAs, arrowpointx, arrowpointy, NULL);// 0번째 배열, 실사용시는 define 필요
				SUTIL_SetTypeAniAsprite(pEvtWay->pArrawAsIns, arrowtype);
				SUTIL_SetLoopAsprite(pEvtWay->pArrawAsIns, true);

				pEvtWayList->Insert_next(pEvtWay);
*/

}



//--------------------------------------------------------------------------
void Field::ReleaseMap(int nResIdx)
//--------------------------------------------------------------------------
{
	//	같으면 이미지 재로딩을 하지 않는다.
	if(m_nSaveResType != nResIdx)
	{
		DeleteFieldImage();

//		for(int loop = 0; loop < SPRITE_MAP_MAX; loop++)
//		{
//			if(pFieldAs[loop])	{SUTIL_FreeSprite(pFieldAs[loop]);}
//		}
	}

	m_pMiniMapData = NULL;

	InitList(pLayerList);
	while(NotEndList(pLayerList))
	{
		SAFE_DELETE(GetData(pLayerList));
		pLayerList->Delete();
	}
//	SAFE_DELETE(pLayerList);
	SAFE_DELETE(pFrontLayer);

	InitList(pMiddleLayerList);
	while(NotEndList(pMiddleLayerList))
	{
		SAFE_DELETE(GetData(pMiddleLayerList));
		pMiddleLayerList->Delete();
	}


	//	리스트만 지워준다.
	if(m_nSaveResType != nResIdx)
	{
		InitList(pEnvirSprList);
		while(NotEndList(pEnvirSprList))
		{
			pEnvirSprList->Delete();
		}
	//	SAFE_DELETE(pEnvirSprList);
		//Release_EVT_WAY();
	}

	InitList(pDropItem);
	while(NotEndList(pDropItem))
	{
		SUTIL_FreeSpriteInstance(GetData(pDropItem)->pInstance);
		SAFE_DELETE(GetData(pDropItem)->item)
		SAFE_DELETE(GetData(pDropItem));
		pDropItem->Delete();
	}

	InitList(pDontgoRect);
	while(NotEndList(pDontgoRect))
	{
		SAFE_DELETE(GetData(pDontgoRect));
		pDontgoRect->Delete();
	}

	InitList(pEventRect);
	while(NotEndList(pEventRect))
	{
		SAFE_DELETE(GetData(pEventRect));
		pEventRect->Delete();
	}

//	InitList(pMonsterGenRect);
//	while(NotEndList(pMonsterGenRect))
//	{
//		SAFE_DELETE(GetData(pMonsterGenRect));
//		pMonsterGenRect->Delete();
//	}

	//	오브젝트를 날려준다.
	SObjectMgr* pObjectMgr = SObjectMgr::GetInstPtr();
	pObjectMgr->RemoveAll();


}


//--------------------------------------------------------------------------
void Field::LoadSprite(int nSpriteNum)
//--------------------------------------------------------------------------
{
//	if(pFieldAs[nSpriteNum])	{return;}

	//	스프라이트 파일 로드
	//pFieldAs[nSpriteNum] = SUTIL_LoadSprite(PACK_SPRITE_MAP, nSpriteNum);
	pFieldAs[nSpriteNum] = SUTIL_LoadAspriteFromPack(PACK_SPRITE_MAP, nSpriteNum);
	

	//	블랜딩 등록
	int blendnum[SPRITE_MAP_MAX] = 
	{
		FRAME_MAP_0_BLEND, FRAME_MAP_1_BLEND, FRAME_MAP_2_BLEND, 0,	FRAME_MAP_4_BLEND,
		FRAME_MAP_5_BLEND, 0, 0, FRAME_MAP_8_BLEND, FRAME_MAP_9_BLEND,
		0, 0, FRAME_MAP_12_BLEND, FRAME_MAP_13_BLEND, 0, 
		FRAME_MAP_15_BLEND, FRAME_MAP_16_BLEND, FRAME_MAP_17_BLEND, 0, FRAME_MAP_19_BLEND, 
		FRAME_MAP_20_BLEND, FRAME_MAP_21_BLEND, 0, 0, 0, 
		FRAME_MAP_25_BLEND, 0, 0, 0, 0, 
		0, 0, 0, 0, FRAME_MAP_34_BLEND, 
		FRAME_MAP_35_BLEND, 0,
	};

	if(0 != blendnum[nSpriteNum])
	{
		pFieldAs[nSpriteNum]->SetBlendFrame(blendnum[nSpriteNum]);
	}
		
	//	환경효과 등록
	MoveHead(pEnvirSprList);
	pEnvirSprList->Insert_next(pFieldAs[nSpriteNum]);	//	환경효과를 내는 스프라이트면 등록시켜준다.
}

/////////////////////////////////////////////////////


/*
//--------------------------------------------------------------------------
void Field::InitState(int nStateNum)
//--------------------------------------------------------------------------
{
	BackLayer* pBackLayer = NULL;
	MoveHead(pLayerList);

	MoveHead(pEnvirSprList);

	//	화면 출력 순서대로 등록시켜준다.
	switch(nStateNum)
	{
		case 1:
		{
			//	필드정보
			m_nFieldSize_X = 3000;
			m_nSrcCamAngle_X = 0;

			//	스프라이트 파일 로드
			pFieldAs[0] = SUTIL_LoadSprite(PACK_SPRITE_MAP, SPRITE_MAP_MAP_0);
			pFieldAs[1] = SUTIL_LoadSprite(PACK_SPRITE_MAP, SPRITE_MAP_MAP_1);
			pFieldAs[2] = SUTIL_LoadSprite(PACK_SPRITE_MAP, SPRITE_MAP_MAP_2);
			pFieldAs[3] = SUTIL_LoadSprite(PACK_SPRITE_MAP, SPRITE_MAP_MAP_3);

			pFieldAs[2]->SetBlendFrame(FRAME_MAP_2_BLEND);

			pEnvirSprList->Insert_next(pFieldAs[0]);			//	환경효과를 내는 스프라이트면 등록시켜준다.
			pEnvirSprList->Insert_next(pFieldAs[1]);			//	환경효과를 내는 스프라이트면 등록시켜준다.
			pEnvirSprList->Insert_next(pFieldAs[2]);			//	환경효과를 내는 스프라이트면 등록시켜준다.
			pEnvirSprList->Insert_next(pFieldAs[3]);			//	환경효과를 내는 스프라이트면 등록시켜준다.

			// 3번 레이어 로드 //////////////////////////////////////////////////////////
			pBackLayer = GL_NEW BackLayer();
			
			pBackLayer->m_nMoveRate = 30;
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_BACKINT);
			pLayerList->Insert_next(pBackLayer);

			//	5번 레이어 로드 /////////////////////////////////////////////////////////
			pBackLayer = GL_NEW BackLayer();
			
			pBackLayer->m_nMoveRate = 100;
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FIELD);
			pLayerList->Insert_next(pBackLayer);

			//	4번 레이어 로드 /////////////////////////////////////////////////////////
			pBackLayer = GL_NEW BackLayer();
			
			pBacmkLayer->m_nMoveRate = 100;
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_TREEIN2);
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_TREEIN1);
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_TREEIN3);
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_TREEINEXIT);
			pBackLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_TREEIN3);
			pLayerList->Insert_next(pBackLayer);

			//	6번 레이어 로드 /////////////////////////////////////////////////////////
			//	캐릭터 앞에 위치하는 레이어
			pFrontLayer = GL_NEW BackLayer();
			pFrontLayer->m_nBaseYLine = 0;
			pFrontLayer->m_nMoveRate = 200;
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT1);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT1);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT2);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT2);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT1);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT2);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONTEXIT);
			pFrontLayer->LoadMapLayer(pFieldAs, PACK_DATA_MAP_FOREST, DATA_MAP_FOREST_FRONT2);
//			pLayerList->Insert_next(pBackLayer);
			break;



		}
	}
}
*/

//--------------------------------------------------------------------------
boolean Field::workPal(boolean Work, int Pal_Kind, int percent)
//--------------------------------------------------------------------------
{//SangHo - 필드는 다수의 팔렛트가 있을 가능성이 항상존재하므로 세부제어를 필드에 맏긴다

	//	환경효과
	boolean _Field_Work = Work;
	int _Field_Pal_Kind = Pal_Kind;
	int _Field_percent = percent;

	boolean _b_result = false;

	InitList(pEnvirSprList);
	while(NotEndList(pEnvirSprList))
	{
		if(Pal_Kind == 0)
		{
			if(!GetData(pEnvirSprList)->workPal(Work, Pal_Kind, percent) )
				_b_result = false;
		}
		MoveNext(pEnvirSprList);
	}
	return _b_result;
}



//--------------------------------------------------------------------------
void Field::SetCamera(int camx, int camy)
//--------------------------------------------------------------------------
{
//	m_nSrcCamAngle_X += ((((camx-120)-m_nSrcCamAngle_X) * 20) / 100);

	m_nSrcCamAngle_X = camx-120;

	if(0 > m_nSrcCamAngle_X)	{m_nSrcCamAngle_X = 0;}
	if(m_nFieldSize_X-SCREEN_WIDTH < m_nSrcCamAngle_X)	{m_nSrcCamAngle_X = m_nFieldSize_X-SCREEN_WIDTH;}
}




//--------------------------------------------------------------------------
void Field::Release_EVT_WAY()
//--------------------------------------------------------------------------
{
	InitList(pEvtWayList);
	while(NotEndList(pEvtWayList))
	{
		SUTIL_FreeSpriteInstance(GetData(pEvtWayList)->pArrawAsIns);
		SAFE_DELETE(GetData(pEvtWayList));
		pEvtWayList->Delete();
	}
	MoveHead(pEvtWayList);
}

//--------------------------------------------------------------------------
int Field::Process_EVT_WAY(int battleState, int herodir, int herox1, int heroy1)
//--------------------------------------------------------------------------
{
	//	캐릭터의 위치
//	m_nCharx = herox1;
//	m_nChary = heroy1;
//
//	switch(herodir)
//	{
//		case MAP_EVT_WAY_DIR_UP:	{heroy1-=40;	break;}
//		case MAP_EVT_WAY_DIR_DOWN:	{heroy1+=40;	break;}
//		case MAP_EVT_WAY_DIR_LEFT:	{herox1-=40;	break;}
//		case MAP_EVT_WAY_DIR_RIGHT:	{herox1+=40;	break;}
//	}

	//	화살표 에니메이션 업데이트
	for(InitList(pEvtWayList);NotEndList(pEvtWayList);MoveNext(pEvtWayList))
	{
		SUTIL_UpdateTimeAsprite(GetData(pEvtWayList)->pArrawAsIns);
	}
/*
	for(InitList(pEvtWayList);NotEndList(pEvtWayList);MoveNext(pEvtWayList))
	{
		if(herox1 > GetData(pEvtWayList)->sx &&
			herox1 < GetData(pEvtWayList)->dx &&
			heroy1 > GetData(pEvtWayList)->sy &&
			heroy1 < GetData(pEvtWayList)->dy &&
			battleState >= GetData(pEvtWayList)->type )
		{
//			GetData(pEvtWayList)->switchtime++;

//			if(5 < GetData(pEvtWayList)->switchtime)
			{
//				if(100 > GetData(pEvtWayList)->charx)	//	방향은 오른쪽을 보고 있는다.
//				{
//					ADD_EVENT_MSG(EVT_SET_CAHRPOS, 0, GetData(pEvtWayList)->charx, GetData(pEvtWayList)->chary, SDIR_RIGHT);
//				}
//				else if(100 > (m_nFieldSize_X - GetData(pEvtWayList)->charx))	//	왼쪽
//				{
//					ADD_EVENT_MSG(EVT_SET_CAHRPOS, 0, GetData(pEvtWayList)->charx, GetData(pEvtWayList)->chary, SDIR_LEFT);
//				}

				m_nWayMoveCharx = GetData(pEvtWayList)->charx;
				m_nWayMoveChary = GetData(pEvtWayList)->chary;

				//	이벤트를 던지고 최소 시간을 딜레이준다. 안그럼 계속 이벤트를 던짐
//				GetData(pEvtWayList)->switchtime = -20;

				return GetData(pEvtWayList)->nextStage;
			}
		}
		else
		{
//			GetData(pEvtWayList)->switchtime = 0;
		}
	}
*/
	return 0;
}

//--------------------------------------------------------------------------
void Field::Paint_EVT_WAY()
//--------------------------------------------------------------------------
{
	for(InitList(pEvtWayList);NotEndList(pEvtWayList);MoveNext(pEvtWayList))
	{
		GetData(pEvtWayList)->pArrawAsIns->CameraX = -m_nSrcCamAngle_X;
		SUTIL_PaintAsprite(GetData(pEvtWayList)->pArrawAsIns, S_NOT_INCLUDE_SORT);
	}
}

//--------------------------------------------------------------------------
void Field::Release_EVT_INPUTKEY()
//--------------------------------------------------------------------------
{
	InitList(pKeyInputEvt);
	while(NotEndList(pKeyInputEvt))
	{
		SAFE_DELETE(GetData(pKeyInputEvt));
		pKeyInputEvt->Delete();
	}
	MoveHead(pKeyInputEvt);
}


//--------------------------------------------------------------------------
int Field::Process_EVT_INPUTKEY()
//--------------------------------------------------------------------------
{
	for(InitList(pKeyInputEvt);NotEndList(pKeyInputEvt);MoveNext(pKeyInputEvt))
	{
		switch( GetData(pKeyInputEvt)->m_nType )
		{
			case EVT_NPC:
//			case EVT_BARREL:
			//-------------------------------------------------------
			{
				GetData(pKeyInputEvt)->SetAngle(m_nSrcCamAngle_X);
				GetData(pKeyInputEvt)->Process();
				break;
			}

		}
	}

	return 0;
}

//--------------------------------------------------------------------------
void Field::Paint_EVT_INPUTKEY()
//--------------------------------------------------------------------------
{
	for(InitList(pKeyInputEvt);NotEndList(pKeyInputEvt);MoveNext(pKeyInputEvt))
	{
		switch( GetData(pKeyInputEvt)->m_nType )
		{
			case EVT_NPC:
//			case EVT_BARREL:
			//-------------------------------------------------------
			{
				GetData(pKeyInputEvt)->Paint();
				break;
			}
		}
	}
}


//--------------------------------------------------------------------------
int Field::KeyPressEvent(int dir, int x1, int y1, int x2, int y2)
//--------------------------------------------------------------------------
{
	int evtcode = 0;

	for(InitList(pKeyInputEvt);NotEndList(pKeyInputEvt);MoveNext(pKeyInputEvt))
	{
		switch( GetData(pKeyInputEvt)->m_nType )
		{
			case EVT_NPC:
			//-------------------------------------------------------
			{
				evtcode = GetData(pKeyInputEvt)->CheckEvent(dir, x1,y1,x2,y2);
				if(evtcode)	{return evtcode;}
				break;
			}
		}
	}

	return 0;
}

//--------------------------------------------------------------------------
void Field::ProcessDropItem()
//--------------------------------------------------------------------------
{
	Position3D m_nPhysicsPos;

	for(InitList(pDropItem);NotEndList(pDropItem);MoveNext(pDropItem))
	{
		if(true == GetData(pDropItem)->bPossibleEat)	{continue;}

		//	물리좌표를 갱신받는다.
		m_nPhysicsPos = GetData(pDropItem)->m_Physics->process();

//		if(0 == m_nPhysicsPos.Sqr_GetLength() && 0 == GetData(pDropItem)->pInstance->m_posZ)
//		{
//			//	이동량이 없으므로 모든 값을 초기화시켜준다.
//			GetData(pDropItem)->m_Physics->initForce();
//			continue;
//		}

		GetData(pDropItem)->pInstance->m_posX += m_nPhysicsPos.x;
		GetData(pDropItem)->pInstance->m_posY += m_nPhysicsPos.y;
		GetData(pDropItem)->pInstance->m_posZ += m_nPhysicsPos.z;

		if(0 <= GetData(pDropItem)->pInstance->m_posZ)
		{
			GetData(pDropItem)->pInstance->m_posZ = 0;
			GetData(pDropItem)->m_Physics->SaveGrAccel.z = UP_GRV;
			GetData(pDropItem)->m_Physics->setRebound();

//			if(-1 < GetData(pDropItem)->m_Physics->SaveAccel.z)
//			{
//				GetData(pDropItem)->m_Physics->initForce();
//				GetData(pDropItem)->bPossibleEat = true;
//			}
		}

		if(0 == GetData(pDropItem)->m_Physics->SaveAccel.Sqr_GetLength())
		{
			GetData(pDropItem)->pInstance->m_posZ = 0;
			GetData(pDropItem)->m_Physics->initForce();
			GetData(pDropItem)->bPossibleEat = true;
		}
	}
}

//--------------------------------------------------------------------------
void Field::InsertDropItem(ItemBag _item, int x, int y)
//--------------------------------------------------------------------------
{
	MoveHead(pDropItem);
	ITEM_STRUCT* pItemStruct = GL_NEW ITEM_STRUCT();

	pItemStruct->m_Physics = GL_NEW Physics(LIGHT_WEIGHT);
	pItemStruct->m_Physics->initForce();

	Position3D Force;
	Force.Init(0,0,UP_GRV);
	pItemStruct->m_Physics->setGrForce(Force);
	Force.Init(SUTIL_GetRandom()%30-15, SUTIL_GetRandom()%10-5,-25-(SUTIL_GetRandom()%15));

	//	아이템이 필드를 나가는 부분 삭제
	if(220 > y && 0 > Force.y)						{Force.y *= (-1);}
	else if(240 < y && 0 < Force.y)					{Force.y *= (-1);}

	if(100 > x && 0 > Force.x)						{Force.x *= (-1);}
	else if(m_nFieldSize_X-100 < x && 0 < Force.x)	{Force.x *= (-1);}

	pItemStruct->m_Physics->setForce(Force);

	pItemStruct->bPossibleEat = false;
	pItemStruct->item = GL_NEW ItemBag();
	pItemStruct->item->Data0 = _item.Data0;
	pItemStruct->item->Data1 = _item.Data1;
	pItemStruct->item->Data2 = _item.Data2;
	pItemStruct->pInstance = GL_NEW ASpriteInstance(s_ASpriteSet->pItemAs, x, y, NULL);
	SUTIL_SetTypeModuleAsprite(pItemStruct->pInstance, PopupUi::itemICON(_item));
	pDropItem->Insert_next(pItemStruct);
}

//--------------------------------------------------------------------------
void Field::PaintDropItem()
//--------------------------------------------------------------------------
{
	for(InitList(pDropItem);NotEndList(pDropItem);MoveNext(pDropItem))
	{
		SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs ,3 ,
			GetData(pDropItem)->pInstance->m_posX -m_nSrcCamAngle_X+1,
			GetData(pDropItem)->pInstance->m_posY-3, 0);

		GetData(pDropItem)->pInstance->CameraX = -m_nSrcCamAngle_X;
		SUTIL_PaintAsprite(GetData(pDropItem)->pInstance,S_NOT_INCLUDE_SORT);
	}
}


//--------------------------------------------------------------------------
ItemBag* Field::CheckDropItem(int x1, int y1)
//--------------------------------------------------------------------------
{
	ItemBag tmpItembag;
	tmpItembag.Data0 = 0;

	int x,y = 0;
	for(InitList(pDropItem);NotEndList(pDropItem);MoveNext(pDropItem))
	{
		x = GetData(pDropItem)->pInstance->m_posX - x1;
		y = GetData(pDropItem)->pInstance->m_posY - y1;
		if(SQR(20) < SQR(x) +SQR(y))	{continue;}

//		if(x1 > GetData(pDropItem)->pInstance->m_posX- GetData(pDropItem)->pInstance->m_stopAniX)	{continue;}
//		if(x2 < GetData(pDropItem)->pInstance->m_posX- GetData(pDropItem)->pInstance->m_stopAniX)	{continue;}
//		if(y1 > GetData(pDropItem)->pInstance->m_posX- GetData(pDropItem)->pInstance->m_stopAniX)	{continue;}
//		if(y2 < GetData(pDropItem)->pInstance->m_posX- GetData(pDropItem)->pInstance->m_stopAniX)	{continue;}

		//tmpItembag.Data0 = GetData(pDropItem)->item->Data0;
		//tmpItembag.Data1 = GetData(pDropItem)->item->Data1;
		//tmpItembag.Data2 = GetData(pDropItem)->item->Data2;

//		SUTIL_FreeSpriteInstance(GetData(pDropItem)->pInstance);
//		SAFE_DELETE(GetData(pDropItem)->item)
//		SAFE_DELETE(GetData(pDropItem));
//		pDropItem->Delete();

		return (GetData(pDropItem)->item);
	}

	return NULL;
}

//--------------------------------------------------------------------------
void Field::DeleteNowItem()
//--------------------------------------------------------------------------
{
	//	현재 리스트의 아이템을 지운다 조금 위험한 코드
	SAFE_DELETE(GetData(pDropItem)->m_Physics)
	SUTIL_FreeSpriteInstance(GetData(pDropItem)->pInstance);
	SAFE_DELETE(GetData(pDropItem)->item)
	SAFE_DELETE(GetData(pDropItem));
	pDropItem->Delete();
}


//--------------------------------------------------------------------------
void Field::DeleteFieldImage()
//--------------------------------------------------------------------------
{
	for(int loop = 0; loop < SPRITE_MAP_MAX; loop++)
	{
		if(pFieldAs[loop])
		{
			SUTIL_FreeSprite(pFieldAs[loop]);
		}
	}		
}


//--------------------------------------------------------------------------
void Field::ReMatchFieldImage()
//--------------------------------------------------------------------------
{
	for(InitList(pLayerList);NotEndList(pLayerList);MoveNext(pLayerList))
	{
		GetData(pLayerList)->RematchImage(pFieldAs);
	}

	for(InitList(pMiddleLayerList);NotEndList(pMiddleLayerList);MoveNext(pMiddleLayerList))
	{
		GetData(pMiddleLayerList)->RematchImage(pFieldAs);
	}

	if(pFrontLayer)
	{
		pFrontLayer->RematchImage(pFieldAs);
	}
	

	//	환경효과를 다시 등록시킨다.
	InitList(pEnvirSprList);
	while(NotEndList(pEnvirSprList))
	{
		pEnvirSprList->Delete();
	}

	for(int loop = 0; loop < SPRITE_MAP_MAX; loop++)
	{
		if(pFieldAs[loop])
		{
			MoveHead(pEnvirSprList);
			pEnvirSprList->Insert_next(pFieldAs[loop]);	//	환경효과를 내는 스프라이트면 등록시켜준다.
		}
	}
}

//--------------------------------------------------------------------------
void Field::LoadFieldImage(int idx)
//--------------------------------------------------------------------------
{
//	if(nNextStageNum/100 != m_nSaveStageNum/100)
//	{
		SUTIL_LoadAspritePack(PACK_SPRITE_MAP);
		switch(idx)
		{
			case 1://	FOREST
			//-----------------------------------------------------------
			{
				LoadSprite(SPRITE_MAP_MAP_0);
				LoadSprite(SPRITE_MAP_MAP_1);
				LoadSprite(SPRITE_MAP_MAP_2);
				LoadSprite(SPRITE_MAP_MAP_3);
				LoadSprite(SPRITE_MAP_MAP_33);
				break;
			}
			case 2://	CAVE
			//-----------------------------------------------------------
			{
				LoadSprite(SPRITE_MAP_MAP_4);
				LoadSprite(SPRITE_MAP_MAP_5);
				LoadSprite(SPRITE_MAP_MAP_6);
				break;
			}
			case 3://	TEMPLE
			//-----------------------------------------------------------
			{
				LoadSprite(SPRITE_MAP_MAP_16);
				LoadSprite(SPRITE_MAP_MAP_17);
				break;
			}
			case 4://	DEVILZONE
			//-----------------------------------------------------------
			{
				LoadSprite(SPRITE_MAP_MAP_22);
				LoadSprite(SPRITE_MAP_MAP_23);
				LoadSprite(SPRITE_MAP_MAP_24);
				LoadSprite(SPRITE_MAP_MAP_25);
				break;
			}
			case 8://	VILLAGE
			//-----------------------------------------------------------
			{
				LoadSprite(SPRITE_MAP_MAP_7);
				LoadSprite(SPRITE_MAP_MAP_8);
				LoadSprite(SPRITE_MAP_MAP_9);
				LoadSprite(SPRITE_MAP_MAP_10);
				LoadSprite(SPRITE_MAP_MAP_11);
				LoadSprite(SPRITE_MAP_MAP_12);
				LoadSprite(SPRITE_MAP_MAP_13);
/*
				LoadSprite(SPRITE_MAP_MAP_14);
				LoadSprite(SPRITE_MAP_MAP_15);
				LoadSprite(SPRITE_MAP_MAP_16);
				LoadSprite(SPRITE_MAP_MAP_26);
				LoadSprite(SPRITE_MAP_MAP_27);
				LoadSprite(SPRITE_MAP_MAP_28);
				LoadSprite(SPRITE_MAP_MAP_36);
*/
				break;
			}
			case 9://	검은 배경
			//-----------------------------------------------------------
			{
				break;
			}
			
		}
		SUTIL_ReleaseAspritePack();
//	}
}

//--------------------------------------------------------------------------
void Field::Paint_EVT_Rect()
//--------------------------------------------------------------------------
{
	for(InitList(pEventRect);NotEndList(pEventRect);MoveNext(pEventRect))
	{
		if(MAIN_QUEST_findOpen == GET_MAINQUEST_IDX() && FIELD_CALL_caveOpen == GetData(pEventRect)->eCode)
		{
			SUTIL_Paint_Frame(pWayAs, FRAME_BG_OBJECT_EVENT_ARROW ,
				((GetData(pEventRect)->dx+GetData(pEventRect)->sx)>>1) - m_nSrcCamAngle_X,
				((GetData(pEventRect)->dy+GetData(pEventRect)->sy)>>1) + m_nEventAddYPos, 0);
		}
	}
}


//--------------------------------------------------------------------------
int Field::Process_EVT_Rect(int herox1, int heroy1)
//--------------------------------------------------------------------------
{
	m_nEventArrowTimer = (m_nEventArrowTimer+1)%4;
	m_nEventAddYPos = 0;
	if(1 == m_nEventArrowTimer)			{m_nEventAddYPos = 2;}
	else if(2 == m_nEventArrowTimer)	{m_nEventAddYPos = 1;}

	for(InitList(pEventRect);NotEndList(pEventRect);MoveNext(pEventRect))
	{
		if(herox1 > GetData(pEventRect)->sx &&
			herox1 < GetData(pEventRect)->dx &&
			heroy1 > GetData(pEventRect)->sy &&
			heroy1 < GetData(pEventRect)->dy	 )
		{
			if(m_nLastZoneEvent == GetData(pEventRect)->eCode)
			{
				return 0;
			}
			else
			{
				m_nLastZoneEvent = GetData(pEventRect)->eCode;
				return m_nLastZoneEvent;
			}
		}
	}

	m_nLastZoneEvent = 0;
	return m_nLastZoneEvent;
}



//--------------------------------------------------------------------------
void Field::ProcessWorldMap()
//--------------------------------------------------------------------------
{
//	pCinema->Update_Cinematics();
}


//--------------------------------------------------------------------------
void Field::PaintWorldMap()
//--------------------------------------------------------------------------
{
	return;

	SUTIL_SetColor(0x000000);
	SUTIL_FillRect(0,0,240,320);

//	pCinema->Paint_Cinematics();

	switch(m_nSaveStageNum)
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
bool Field::KeyEvent(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{
/*
	switch(m_nSaveStageNum)
	{
		case 1000:
		//------------------------------------------------------------
		{
			switch(m_keyCode)
			{
				case MH_KEY_1:
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 801, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;
					return true;
				}
				case MH_KEY_2://	{AppMain::ResvNextState(MS_GAME_FIELD, 101, 1950);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 101, 0);
					m_nWayMoveCharx = 1950;
					m_nWayMoveChary = 240;
					return true;
				}
				case MH_KEY_3://	{AppMain::ResvNextState(MS_GAME_FIELD, 200, 0);	break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 200, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;
					return true;
				}

				case MH_KEY_4://	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 0);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 104, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;
					return true;
				}

			}

			break;
		}
		case 1001:
		//------------------------------------------------------------
		{
			switch(m_keyCode)
			{
				case MH_KEY_1://	{AppMain::ResvNextState(MS_GAME_FIELD, 803, 0);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 803, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;
					return true;
				}

				case MH_KEY_2://	{AppMain::ResvNextState(MS_GAME_FIELD, 105, 450);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 105, 0);
					m_nWayMoveCharx = 450;
					m_nWayMoveChary = 240;
					return true;
				}

				case MH_KEY_3://	{AppMain::ResvNextState(MS_GAME_FIELD, 113, 50);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 113, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;
					return true;
				}

				case MH_KEY_4://	{AppMain::ResvNextState(MS_GAME_FIELD, 205, 50);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 205, 0);
					m_nWayMoveCharx = 50;
					m_nWayMoveChary = 240;

					return true;
				}

				case MH_KEY_5://	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 1450);		break;}
				{
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, 104, 0);
					m_nWayMoveCharx = 1450;
					m_nWayMoveChary = 240;
					return true;
				}

			}

			break;
		}
	}
*/
	return false;
}