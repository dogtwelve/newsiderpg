#include "Minimap.h"


//--------------------------------------------------------------------------
cMinimap::cMinimap()
//--------------------------------------------------------------------------
{
	m_pMiniMapList = GL_NEW List2<MiniMapData*>();

//	s_ASpriteSet = (ASpriteSet*)_sASpriteSet;
}


//--------------------------------------------------------------------------
cMinimap::~cMinimap()
//--------------------------------------------------------------------------
{
	ReleaseMiniMap();
	SAFE_DELETE(m_pMiniMapList);
}

//--------------------------------------------------------------------------
void cMinimap::LoadMiniMap()
//--------------------------------------------------------------------------
{
	//	TEST

	int MONINFO[MI_INFO_MAX] = 
    {
		200,1,1,		                    0, 0, 0,			     2, 3, 0, 20,  		NU, NU, NU, NU,	NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU
	};

	m_nCurZoneIdx = m_nNextZone;

	MoveHead(m_pMiniMapList);

	MiniMapData* tmpMapData = GL_NEW MiniMapData();

	tmpMapData->m_nXPos = 1;
	tmpMapData->m_nYPos = 1;
	tmpMapData->m_nBackType = 1;
	tmpMapData->m_nResType = 1;
	tmpMapData->m_nSectorIdx = 1;
	
	tmpMapData->m_nCellCount = 3;
	tmpMapData->m_sMapCellData = GL_NEW MiniMapCellData[tmpMapData->m_nCellCount];

	//	임시 몬스터 데이타 복사
	for(int loop = 0; loop < MI_INFO_MAX; loop++)
	{
		tmpMapData->m_MonsterInfo[loop] = MONINFO[loop];
	}

	tmpMapData->m_sMapCellData[0].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[0].m_PtnBackAndBackType = 1;
//	tmpMapData->m_sMapCellData[0].m_PtnGround = 1;
	tmpMapData->m_sMapCellData[0].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[0].m_nPtnType = MNC_NO_LINK;

	tmpMapData->m_sMapCellData[1].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[1].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[1].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[1].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[1].m_nPtnType = MNC_NO_LINK;

	tmpMapData->m_sMapCellData[2].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[2].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[2].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[2].m_PtnFrontGround = 1;
	tmpMapData->m_sMapCellData[2].m_nPtnType = MNC_RIGHT_LINK | MNC_DOWN_LINK;

	m_pMiniMapList->Insert_next(tmpMapData);

	//--------------------------------------------------------------------------------------
	tmpMapData = GL_NEW MiniMapData();

	tmpMapData->m_nXPos = 3;
	tmpMapData->m_nYPos = 2;
	tmpMapData->m_nBackType = 1;
	tmpMapData->m_nResType = 1;
	tmpMapData->m_nSectorIdx = 2;

	tmpMapData->m_nCellCount = 4;
	tmpMapData->m_sMapCellData = GL_NEW MiniMapCellData[tmpMapData->m_nCellCount];

	//	임시 몬스터 데이타 복사
	for(int loop = 0; loop < MI_INFO_MAX; loop++)
	{
		tmpMapData->m_MonsterInfo[loop] = MONINFO[loop];
	}

	tmpMapData->m_sMapCellData[0].m_PtnObject = 1;
//	tmpMapData->m_sMapCellData[0].m_PtnBackAndBackType = 1;
//	tmpMapData->m_sMapCellData[0].m_PtnGround = 1;
	tmpMapData->m_sMapCellData[0].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[0].m_nPtnType = MNC_UP_LINK;

	tmpMapData->m_sMapCellData[1].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[1].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[1].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[1].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[1].m_nPtnType = MNC_NO_LINK;

	tmpMapData->m_sMapCellData[2].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[2].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[2].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[2].m_PtnFrontGround = 1;
	tmpMapData->m_sMapCellData[2].m_nPtnType = MNC_NO_LINK;

	tmpMapData->m_sMapCellData[3].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[3].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[3].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[3].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[3].m_nPtnType = MNC_NO_LINK;

	m_pMiniMapList->Insert_next(tmpMapData);


	//--------------------------------------------------------------------------------------
	tmpMapData = GL_NEW MiniMapData();

	tmpMapData->m_nXPos = 4;
	tmpMapData->m_nYPos = 1;
	tmpMapData->m_nBackType = 1;
	tmpMapData->m_nResType = 1;
	tmpMapData->m_nSectorIdx = 3;

	tmpMapData->m_nCellCount = 2;
	tmpMapData->m_sMapCellData = GL_NEW MiniMapCellData[tmpMapData->m_nCellCount];

	//	임시 몬스터 데이타 복사
	for(int loop = 0; loop < MI_INFO_MAX; loop++)
	{
		tmpMapData->m_MonsterInfo[loop] = MONINFO[loop];
	}

	tmpMapData->m_sMapCellData[0].m_PtnObject = 1;
//	tmpMapData->m_sMapCellData[0].m_PtnBackAndBackType = 1;
//	tmpMapData->m_sMapCellData[0].m_PtnGround = 1;
	tmpMapData->m_sMapCellData[0].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[0].m_nPtnType = MNC_LEFT_LINK;

	tmpMapData->m_sMapCellData[1].m_PtnObject = 2;
//	tmpMapData->m_sMapCellData[1].m_PtnBackAndBackType = 0;
//	tmpMapData->m_sMapCellData[1].m_PtnGround = 0;
	tmpMapData->m_sMapCellData[1].m_PtnFrontGround = 2;
	tmpMapData->m_sMapCellData[1].m_nPtnType = MNC_NO_LINK;

	m_pMiniMapList->Insert_next(tmpMapData);
}

//--------------------------------------------------------------------------
void cMinimap::ReleaseMiniMap()
//--------------------------------------------------------------------------
{
	InitList(m_pMiniMapList);
	while(NotEndList(m_pMiniMapList))
	{
		SAFE_DELETE( GetData(m_pMiniMapList)->m_sMapCellData );
		SAFE_DELETE(GetData(m_pMiniMapList));
		m_pMiniMapList->Delete();
	}
}


#define MN_X_DIS	(20)
#define MN_Y_DIS	(20)

#define MN_X_GAP	(4)
#define MN_Y_GAP	(4)

//--------------------------------------------------------------------------
void cMinimap::PaintMiniMap()
//--------------------------------------------------------------------------
{
//	SUTIL_SetColor(0x000000);
//	SUTIL_FillRect(0,0,240,320);


	int x = 0;
	int y = 0;
	int loop = 0;

	SUTIL_SetColor(0xffffff);

	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		SUTIL_DrawRect(
			MN_X_GAP + (MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos))-m_nMapDefXPos,
			MN_Y_GAP + (MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos))-m_nMapDefYPos,
			(MN_X_DIS * GetData(m_pMiniMapList)->m_nCellCount) - (MN_X_GAP*2),
			(MN_Y_DIS) - (MN_Y_GAP*2)
		);

		
		for(loop = 0; loop < GetData(m_pMiniMapList)->m_nCellCount; loop++)
		{
			//	왼쪽 길
			if(MNC_LEFT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) - MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos
				);
			}

			//	오른쪽 길
			if(MNC_RIGHT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop+1)) - MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop+1)) + MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos
				);
			}

			//	위쪽 길
			if(MNC_UP_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) - MN_Y_GAP-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + MN_Y_GAP-m_nMapDefYPos
				);
			}

			//	아랫쪽 길
			if(MNC_DOWN_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos+1)) - MN_Y_GAP-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos+1)) + MN_Y_GAP-m_nMapDefYPos
				);
			}
		}
	}
}



//--------------------------------------------------------------------------
bool cMinimap::KeyEvent(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{

	switch(m_keyCode)
	{
		case MH_KEY_LEFT:
		{
			m_nMapDefXPos -= 2;
			return true;
		}
		case MH_KEY_RIGHT://	{AppMain::ResvNextState(MS_GAME_FIELD, 101, 1950);		break;}
		{
			m_nMapDefXPos += 2;
			return true;
		}
		case MH_KEY_UP://	{AppMain::ResvNextState(MS_GAME_FIELD, 200, 0);	break;}
		{
			m_nMapDefYPos -= 2;
			return true;
		}

		case MH_KEY_DOWN://	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 0);		break;}
		{
			m_nMapDefYPos += 2;
			return true;
		}

	}

	return false;
}

/*
//--------------------------------------------------------------------------
MiniMapData* cMinimap::GetNextStageInfo(int zone, int sector)
//--------------------------------------------------------------------------
{
	//->zone check

	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		if(sector == GetData(m_pMiniMapList)->m_nSectorIdx)
		{
			//	일치하는 맵 발생
			return (GetData(m_pMiniMapList));
		}
	}

	return NULL;
}
*/

//--------------------------------------------------------------------------
void cMinimap::ResvNextSector(int zone, int sector)
//--------------------------------------------------------------------------
{
	//	다음 맵을 예약한다.
	m_nNextZone = zone;
	m_nNextSector = sector;
}


//--------------------------------------------------------------------------
bool cMinimap::ResvNextSector(int charx, int chary, int aaa)
//--------------------------------------------------------------------------
{
	//	이동할 영역을 결정한다.

//	m_nNextCharPosX = MAP_START_X;
//	m_nNextCharPosY = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;

	int mapposX = m_CurMapSector->m_nXPos + charx/SECTOR_SIZE;
	int mapposY = m_CurMapSector->m_nYPos;

	bool isChangeScetor = false; 

	unsigned char loadinfo = m_CurMapSector->m_sMapCellData[(charx/SECTOR_SIZE)].m_nPtnType;

	if( (MNC_LEFT_LINK	&loadinfo) && (MAP_MOVE_X > charx))
	{
		m_nNextCharPosX = SECTOR_SIZE - MAP_START_X;
		m_nNextCharPosY = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;
		mapposX--;
		isChangeScetor = true;
	}
	else if( (MNC_RIGHT_LINK	&loadinfo) && (m_CurMapSector->m_nCellCount*SECTOR_SIZE) - MAP_MOVE_X < charx)
	{
		m_nNextCharPosX = MAP_START_X;
		m_nNextCharPosY = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;
		mapposX++;
		isChangeScetor = true;
	}
	else if( (MNC_UP_LINK		&loadinfo) && MAP_MOVE_UP_Y > chary)
	{
		m_nNextCharPosX = (SECTOR_SIZE/2);
		m_nNextCharPosY = MAP_MOVE_DOWN_Y - MAP_START_Y;
		mapposY--;
		isChangeScetor = true;
	}
	else if( (MNC_DOWN_LINK	&loadinfo) && MAP_MOVE_DOWN_Y < chary)
	{
		m_nNextCharPosX = (SECTOR_SIZE/2);
		m_nNextCharPosY = MAP_MOVE_UP_Y + MAP_START_Y;
		mapposY++;
		isChangeScetor = true;
	}

	//	이동할수 있는지 확인한다.
	if(false == isChangeScetor)	{return false;}

	int loop = 0;
	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		for(loop = 0; loop < GetData(m_pMiniMapList)->m_nCellCount; loop++)
		{
			if(mapposX == (GetData(m_pMiniMapList)->m_nXPos+loop) &&
				mapposY == GetData(m_pMiniMapList)->m_nYPos)
			{
				//	X값을 보정해준다.
//				if( (MNC_LEFT_LINK&loadinfo) || (MNC_RIGHT_LINK&loadinfo))
//				{
					m_nNextCharPosX += loop*SECTOR_SIZE;
//					m_nNextCharPosY = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;
//				}
//				else
//				{
//					m_nNextCharPosX = loop*SECTOR_SIZE + (SECTOR_SIZE/2);
//					
//				}

				// 이동을 예약한다.
				ResvNextSector(m_nCurZoneIdx, GetData(m_pMiniMapList)->m_nSectorIdx);
				return true;
			}
		}
	}

	return false;
	//	다음 맵을 예약한다.
//	m_nNextZone = zone;
//	m_nNextSector = sector;
}


//--------------------------------------------------------------------------
MiniMapData* cMinimap::SetResvSector()
//--------------------------------------------------------------------------
{
//	m_nNextZone = zone;
//	m_nNextSector = sector

	//	초기화시킨다.
	m_CurMapSector = NULL;

	//->zone check
	//	이미 로드가 되었다면 로드하지 않는다.
	if(m_nCurZoneIdx != m_nNextZone)
	{
		LoadMiniMap();
	}

	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		if(m_nNextSector == GetData(m_pMiniMapList)->m_nSectorIdx)
		{
			//	일치하는 맵 발생
			m_CurMapSector = GetData(m_pMiniMapList);
			return (m_CurMapSector);
		}
	}

	return NULL;
}




/*
//--------------------------------------------------------------------------
MiniMapData* cMinimap::GetNextStageInfo(int mapXPos, int mapYPos)
//--------------------------------------------------------------------------
{
	int loop = 0;

	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		if(mapYPos != GetData(m_pMiniMapList)->m_nYPos)	{continue;}

		for(loop = 0; loop < GetData(m_pMiniMapList)->m_nCellCount; loop++)
		{
			if(mapXPos == (GetData(m_pMiniMapList)->m_nXPos+loop) )
			{
				//	일치하는 맵 발생
				return (GetData(m_pMiniMapList));
			}
		}
	}

	return NULL;
}
*/