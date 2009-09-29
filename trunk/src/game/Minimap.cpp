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
	int loop = 0;

	m_nCurZoneIdx = m_nNextZone;

	SUTIL_Data_init(PACK_DATA_MAPINFO);
	SUTIL_Data_open(m_nCurZoneIdx-1);

	MoveHead(m_pMiniMapList);

//	int a = SUTIL_s_data_curOffset;
//	int b = SUTIL_s_s_data_sizes[m_nCurZoneIdx-1];

	int length = 0;
	while( length < SUTIL_s_s_data_sizes[m_nCurZoneIdx-1] )
	{
		MiniMapData* tmpMapData = GL_NEW MiniMapData();
		tmpMapData->m_nXPos = (int)SUTIL_Data_readU16();	length+=2;
		tmpMapData->m_nYPos = (int)SUTIL_Data_readU16();	length+=2;

		tmpMapData->m_nSectorIdx = (int)SUTIL_Data_readU16();	length+=2;
		tmpMapData->m_nResType = (int)SUTIL_Data_readU16();	length+=2;
		tmpMapData->m_nBackType = (int)SUTIL_Data_readU16();	length+=2;

		tmpMapData->m_nCellCount = (int)SUTIL_Data_readU16();	length+=2;

		for(loop = 0; loop < MI_INFO_MAX; loop++)
		{
			tmpMapData->m_MonsterInfo[loop] = (int)SUTIL_Data_readU16();	length+=2;
		}

		tmpMapData->m_sMapCellData = GL_NEW MiniMapCellData[tmpMapData->m_nCellCount];
		for(loop = 0; loop < tmpMapData->m_nCellCount; loop++)
		{
			tmpMapData->m_sMapCellData[loop].m_PtnObject = (int)SUTIL_Data_readU16();	length+=2;
			tmpMapData->m_sMapCellData[loop].m_PtnFrontGround = (int)SUTIL_Data_readU16();	length+=2;
			tmpMapData->m_sMapCellData[loop].m_nPtnType = (int)SUTIL_Data_readU16();	length+=2;
		}

		//	TEST
//		/////////////////////////////////////////////////////////
//		int MONINFO[MI_INFO_MAX] = 
//		{
//			//200,1,1,		                    0, 0, 0,			     18, 3, 0, 1,  		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU
//			200,1,1,		                    0, 0, 0,			     18, 3, 0, 0,  		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU
//		};
//		 
//		//	�ӽ� ���� ����Ÿ ����
//		for(int loop = 0; loop < MI_INFO_MAX; loop++)
//		{
//			tmpMapData->m_MonsterInfo[loop] = MONINFO[loop];
//		}
//		/////////////////////////////////////////////////////////

		m_pMiniMapList->Insert_next(tmpMapData);
	}

	SUTIL_Data_free();





/*
	//	TEST

	int MONINFO[MI_INFO_MAX] = 
    {
		//200,1,1,		                    0, 0, 0,			     4, 3, 0, 1,  		5, 3, 0, 1,		6, 3, 0, 1,		8, 3, 0, 1,		NU, NU, NU, NU
		//200,1,1,		                    0, 0, 0,			     4, 3, 0, 10,  		5, 3, 0, 10,		6, 3, 0, 10,		8, 3, 0, 10,		NU, NU, NU, NU
		200,1,1,		                    0, 0, 0,			     NU, NU, NU, NU,  		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU
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

	//	�ӽ� ���� ����Ÿ ����
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

	//	�ӽ� ���� ����Ÿ ����
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

	//	�ӽ� ���� ����Ÿ ����
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
*/
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
			//	���� ��
			if(MNC_LEFT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) - MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos
				);
			}

			//	������ ��
			if(MNC_RIGHT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop+1)) - MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop+1)) + MN_X_GAP-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + (MN_Y_DIS/2)-m_nMapDefYPos
				);
			}

			//	���� ��
			if(MNC_UP_LINK & GetData(m_pMiniMapList)->m_sMapCellData[loop].m_nPtnType)
			{
				SUTIL_DrawLine(
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) - MN_Y_GAP-m_nMapDefYPos,
					(MN_X_DIS*(GetData(m_pMiniMapList)->m_nXPos+loop)) + (MN_X_DIS/2)-m_nMapDefXPos,
					(MN_Y_DIS*(GetData(m_pMiniMapList)->m_nYPos)) + MN_Y_GAP-m_nMapDefYPos
				);
			}

			//	�Ʒ��� ��
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
			//	��ġ�ϴ� �� �߻�
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
	//	���� ���� �����Ѵ�.
	m_nNextZone = zone;
	m_nNextSector = sector;
}


//--------------------------------------------------------------------------
bool cMinimap::ResvNextSector(int charx, int chary, int aaa)
//--------------------------------------------------------------------------
{
	//	�̵��� ������ �����Ѵ�.

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

	//	�̵��Ҽ� �ִ��� Ȯ���Ѵ�.
	if(false == isChangeScetor)	{return false;}

	int loop = 0;
	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		for(loop = 0; loop < GetData(m_pMiniMapList)->m_nCellCount; loop++)
		{
			if(mapposX == (GetData(m_pMiniMapList)->m_nXPos+loop) &&
				mapposY == GetData(m_pMiniMapList)->m_nYPos)
			{
				//	X���� �������ش�.
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

				//	������ �ٲ��.
				if(100 <= GetData(m_pMiniMapList)->m_nSectorIdx)
				{
					// �̵��� �����Ѵ�.
					ResvNextSector(GetData(m_pMiniMapList)->m_nResType, GetData(m_pMiniMapList)->m_nBackType);
				}
				else
				{
					// �̵��� �����Ѵ�.
					ResvNextSector(m_nCurZoneIdx, GetData(m_pMiniMapList)->m_nSectorIdx);
				}
				return true;
			}
		}
	}

	return false;
	//	���� ���� �����Ѵ�.
//	m_nNextZone = zone;
//	m_nNextSector = sector;
}


//--------------------------------------------------------------------------
MiniMapData* cMinimap::SetResvSector()
//--------------------------------------------------------------------------
{
//	m_nNextZone = zone;
//	m_nNextSector = sector

	//	�ʱ�ȭ��Ų��.
	m_CurMapSector = NULL;

	//->zone check
	//	�̹� �ε尡 �Ǿ��ٸ� �ε����� �ʴ´�.
	if(m_nCurZoneIdx != m_nNextZone)
	{
		ReleaseMiniMap();
		LoadMiniMap();
	}

/////////////////////////////////////////////
	//	�Ա�
	if(100 <= m_nNextSector)
	{
		for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
		{
			//int a = GetData(m_pMiniMapList)->m_nSectorIdx;
			if(m_nNextSector == GetData(m_pMiniMapList)->m_nSectorIdx)
			{
				m_CurMapSector = GetData(m_pMiniMapList);
				break;
			}
		}

		int charx = SECTOR_SIZE/2;
		int chary = (MAP_MOVE_UP_Y+MAP_MOVE_DOWN_Y)/2;

		if(MNC_RIGHT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[0].m_nPtnType)
		{
			charx = SECTOR_SIZE-1;
		}

		if(MNC_LEFT_LINK & GetData(m_pMiniMapList)->m_sMapCellData[0].m_nPtnType)
		{
			charx = 1;
		}

		if(MNC_UP_LINK & GetData(m_pMiniMapList)->m_sMapCellData[0].m_nPtnType)
		{
			chary = MAP_MOVE_UP_Y-1;
		}

		if(MNC_DOWN_LINK & GetData(m_pMiniMapList)->m_sMapCellData[0].m_nPtnType)
		{
			chary = MAP_MOVE_DOWN_Y+1;
		}

		
		ResvNextSector(charx, chary, 0);
	}
/////////////////////////////////////////////


	for(InitList(m_pMiniMapList);NotEndList(m_pMiniMapList);MoveNext(m_pMiniMapList))
	{
		if(m_nNextSector == GetData(m_pMiniMapList)->m_nSectorIdx)
		{
			//	��ġ�ϴ� �� �߻�
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
				//	��ġ�ϴ� �� �߻�
				return (GetData(m_pMiniMapList));
			}
		}
	}

	return NULL;
}
*/