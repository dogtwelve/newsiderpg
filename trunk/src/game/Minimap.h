#ifndef CMINIMAP
#define CMINIMAP

#include "SUtil.h"

#define MAP_MOVE_UP_Y	170
#define MAP_MOVE_DOWN_Y	255
#define MAP_MOVE_X		30
#define MAP_DEF_CHAR_UP_Y	(MAP_MOVE_UP_Y+10)
#define MAP_DEF_CHAR_DOWN_Y	(MAP_MOVE_DOWN_Y-10)
#define SECTOR_SIZE		320
#define MAP_START_X		50
#define MAP_START_Y		20


#define MNC_NO_LINK		(0)
#define MNC_RIGHT_LINK	(1)
#define MNC_LEFT_LINK	(2)
#define MNC_UP_LINK		(4)
#define MNC_DOWN_LINK	(8)


#define MI_DISTANCE						0
#define MI_LEVEL						1
#define MI_ADD_RND_LEVEL				2
#define MI_RARE_GRADE					3
#define MI_UNIQUE_GRADE					4
#define MI_SPECIAL_GRADE				5
#define MI_MON1_IDX						6
#define MI_MON1_NAME					7
#define MI_MON1_PTN						8
#define MI_MON1_COUNT					9
#define MI_MON2_IDX						10
#define MI_MON2_NAME					11
#define MI_MON2_PTN						12
#define MI_MON2_COUNT					13
#define MI_MON3_IDX						14
#define MI_MON3_NAME					15
#define MI_MON3_PTN						16
#define MI_MON3_COUNT					17
#define MI_MON4_IDX						18
#define MI_MON4_NAME					19
#define MI_MON4_PTN						20
#define MI_MON4_COUNT					21
#define MI_MON5_IDX						22
#define MI_MON5_NAME					23
#define MI_MON5_PTN						24
#define MI_MON5_COUNT					25
#define MI_INFO_MAX						26
#define NU								999

#define MI_MON_COUNT					5





typedef struct _MiniMapCellData
{
	unsigned char m_PtnObject;					//	오브젝트들 (위쪽 길을 표시함)
	unsigned char m_PtnFrontGround;				//	앞의 패턴(전경 / 바닥)
	unsigned char m_nPtnType;					//	미니맵에서 표현하기위해 ptn의 타입
}MiniMapCellData;


typedef struct _MiniMapData
{
	unsigned char m_nSectorIdx;				//	섹터 인덱스
	unsigned char m_nCellCount;				//	맵 패턴의 갯수
	unsigned char m_nResType;				//	이미지 종류
	unsigned char m_nBackType;				//	전경의 패턴 인덱스

	unsigned char m_nXPos;					//	zone 에서 sector 좌표
	unsigned char m_nYPos;

	MiniMapCellData*	m_sMapCellData;

	short		  m_MonsterInfo[MI_INFO_MAX];
}MiniMapData;


class cMinimap
{
public:

	// Members
	List2<MiniMapData*>	*m_pMiniMapList;

//	unsigned char m_nZoneIdx;		//	현재 zone의 인덱스

	int m_nMapDefXPos;				//	미니맵의 좌표
	int m_nMapDefYPos;

	int m_nCurZoneIdx;				//	현재 로드된 미니맵존의 인덱스

	MiniMapData*	m_CurMapSector;
	

	cMinimap();
	~cMinimap();

	void			LoadMiniMap();
	void			ReleaseMiniMap();
	void			PaintMiniMap();
	bool			KeyEvent(int m_keyCode, int m_keyRepeat);

	bool			ResvNextSector(int charx, int chary, int aa);
	void			ResvNextSector(int zone, int sector);
	MiniMapData*	SetResvSector();
	int				SearchNextMap(int type);

//private:
	int				m_nNextZone;
	int				m_nNextSector;
	int				m_nNextCharPosX;
	int				m_nNextCharPosY;

//	MiniMapData*	GetNextStageInfo(int zone, int sector);
};

#endif
