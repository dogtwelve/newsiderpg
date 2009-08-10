#include "SUtil.h"
#include "List.h"
#include "BackLayer.h"
#include "VEvent.h"
#include "FieldObject.h"
#include "Character.h"
#include "FieldObject.h"
#include "SaveLoad.h"


#ifndef		__NEWFIELD_H_
#define		__NEWFIELD_H_

//#define MAX_MAP_SPRITE_SIZE		10

#define MAP_EVT_WAY_TYPE_AFTER_BATTLE		1
#define MAP_EVT_WAY_TYPE_ALL				2


#define MAP_EVT_WAY_DIR_UP					1
#define MAP_EVT_WAY_DIR_DOWN				2
#define MAP_EVT_WAY_DIR_LEFT				3
#define MAP_EVT_WAY_DIR_RIGHT				4

#define EVT_END_OF_LAYER					1
#define EVT_NEXT_MAP_POS					50
#define EVT_MAP_SIZE						51
#define EVT_NPC								52
#define EVT_DONT_GO_RECT					53
#define EVT_EVENT_RECT						54
#define EVT_MON_GEN_RECT					55

#define EVT_DESTROY_OBJECT					1000


#define GEN_FIELD_NUM						0
#define GEN_DISTANCE						1
#define GEN_LEVEL							2
#define GEN_ADD_RND_LEVEL					3
#define GEN_RARE_GRADE						4
#define GEN_UNIQUE_GRADE					5
#define GEN_SPECIAL_GRADE					6
#define GEN_MON1_IDX						7
#define GEN_MON1_NAME						8
#define GEN_MON1_PTN						9
#define GEN_MON1_COUNT						10
#define GEN_MON2_IDX						11
#define GEN_MON2_NAME						12
#define GEN_MON2_PTN						13
#define GEN_MON2_COUNT						14
#define GEN_MON3_IDX						15
#define GEN_MON3_NAME						16
#define GEN_MON3_PTN						17
#define GEN_MON3_COUNT						18
#define GEN_MON4_IDX						19
#define GEN_MON4_NAME						20
#define GEN_MON4_PTN						21
#define GEN_MON4_COUNT						22
#define GEN_MON5_IDX						23
#define GEN_MON5_NAME						24
#define GEN_MON5_PTN						25
#define GEN_MON5_COUNT						26
#define GEN_INFO_MAX						27
#define NU									999

#define GEN_MON_COUNT						5

static const int FIELD_MONSTER_INFO[][GEN_INFO_MAX] = 
{
  	//�ʵ��ε���,�ʱ����,����,��������, /  RARE, UNIQ, SPEC, / ���͹�ȣ,���̺� �̸�,���Ͱ���, ������ / <- �ִ� 5���� ����
    // �������� 1	
    // ��������
    {103, 200,1,1,		                    0, 0, 0,			     2, 3, 0, 4,  		NU, NU, NU, NU,	NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {200, 300,1,1,		                    0, 0, 0,			     2, 6, 0, 4,		4, 7, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {201, 200,1,2,		                    0, 0, 0,			     2, 1, 0, 3,		4, 4, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {202, 300,1,2,		                    0, 0, 0,			     2, 1, 0, 5,		4, 4, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {203, 200,1,2,		                    0, 0, 0,			     2, 6, 0, 4,		4, 7, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},

    //����Ÿ�� �ʿ�
    {100, 250,3,2,		                    0, 0, 0,			     13, 2, 0,5,		4,6, 0, 10,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {101, 200,3,2,		                    0, 0, 0,			     2, 3, 0, 5,		4,6, 0, 10,		13, 1, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU},

    // �̵�Ÿ�� �����
    {104, 200,5,2,		                    0, 0, 0,			     2, 3, 0, 6,		4, 2, 0, 6,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
 
     // ���� ���ʽ�
    {105, 200,7,2,		                    0, 0, 0,			     2, 0, 0, 5,		4, 4, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {106, 150,7,2,		                    0, 0, 0,			     2, 3, 0, 8,		4, 7, 0, 8,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {107, 150,7,2,		                    0, 0, 0,			     2, 6, 0, 4,		4, 1, 0, 5,		3, 1, 0, 4,			NU, NU, NU, NU,		NU, NU, NU, NU},
    {108, 150,7,2,		                    0, 0, 0,			     2, 3, 0, 5,		4, 4, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {109, 200,8,2,		                    0, 0, 0,			     2, 0, 0, 7,		4, 7, 0, 7,		3, 1, 0, 6,			NU, NU, NU, NU,		NU, NU, NU, NU},
    {110, 200,8,2,		                    0, 0, 0,			     2, 6, 0, 5,		3, 1, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {111, 150,8,2,		                    0, 0, 0,			     2, 0, 0, 3,		3, 7, 0, 3,		4, 1, 0, 3,			NU, NU, NU, NU,		NU, NU, NU, NU},
    {112, 200,8,2,		                    0, 0, 0,			     3, 3, 0, 7,		4, 4, 0, 7,		13, 1, 0, 7,		NU, NU, NU, NU,		NU, NU, NU, NU},
//    {300, 200,8,2,		                    0, 0, 0,			     3, 6, 0, 3,		4, 1, 0, 3,		13, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU},
	//	ȣ�ν� ���� �׽�Ʈ ��������
    {300, 200,10,2,		                    0, 0, 0,			     NU, NU, NU, NU,	NU, NU, NU, NU,	NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {400, 200,10,2,		                    0, 0, 0,			     NU, NU, NU, NU,	NU, NU, NU, NU,	NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},


    //���� ���ʽ�
    {113, 200,6,2,		                    0, 0, 0,			     3, 1, 0, 5,		4, 3, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {114, 200,6,2,		                    0, 0, 0,			     3, 7, 0, 8,		4, 6, 0, 8,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {115, 200,6,2,		                    0, 0, 0,			     3, 4, 0, 4,		4, 0, 0, 5,		13, 1, 0, 4,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {116, 150,6,2,		                    0, 0, 0,			     3, 7, 0, 5,		4, 3, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {117, 200,7,2,		                    0, 0, 0,			     3, 1, 0, 7,		4, 6, 0, 7,		13, 1, 0, 6,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {204, 150,7,2,		                    0, 0, 0,			     3, 4, 0, 5,		4, 0, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    
   // �̷ε���
    {205, 250,9,2,		                    0, 0, 0,			     2, 0, 0, 5,		3, 4, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {206, 200,9,2,		                    0, 0, 0,			     3, 3, 0, 8,		4, 7, 0, 8,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {207, 150,9,2,		                    0, 0, 0,			     2, 6, 0, 4,		3, 1, 0, 5,		4, 1, 0, 4,			NU, NU, NU, NU,		NU, NU, NU, NU},
    {208, 200,9,2,		                    0, 0, 0,			     2, 3, 0, 5,		4, 4, 0, 5,		13, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {209, 150,9,2,		                    0, 0, 0,			     2, 0, 0, 7,		4, 7, 0, 7,		13, 1, 0, 6,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {210, 200,9,2,		                    0, 0, 0,			     4, 6, 0, 5,		13, 1, 0, 5,	NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {211, 100,9,2,		                    0, 0, 0,			     3, 0, 0, 3,		4, 7, 0, 3,		13, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {212, 200,9,2,		                    0, 0, 0,			     3, 3, 0, 7,		4, 4, 0, 7,		13, 1, 0, 7,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {213, 200,10,2,		                    0, 0, 0,			     3, 6, 0, 3,		4, 1, 0, 3,		13, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {214, 200,10,2,		                    0, 0, 0,			     2, 6, 0, 5,		3, 1, 0, 5,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {215, 150,10,2,		                    0, 0, 0,			     2, 0, 0, 3,		3, 7, 0, 3,		13, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {216, 150,10,2,		                    0, 0, 0,			     3, 3, 0, 7,		4, 4, 0, 7,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},
    {217, 200,10,2,		                    0, 0, 0,			     3, 6, 0, 3,		4, 1, 0, 3,		NU, NU, NU, NU,		NU, NU, NU, NU,		NU, NU, NU, NU},

	{NU},
};




typedef struct _MAP_EVT_WAY
{
//	int sx,sy,dx,dy;
//	int direction;
//	int switchtime;
//	int nextStage;
//	int type;
//	int charx;
//	int chary;
//	int arrowpointx;
//	int arrowpointy;
//	int arrowtype;
	ASpriteInstance* pArrawAsIns;
}MAP_EVT_WAY;


typedef struct _DONT_GO_RECT
{
	int sx,sy,dx,dy;
}DONT_GO_RECT;


typedef struct _EVENT_RECT
{
	int sx,sy,dx,dy;
	int eCode;
	int dummy[3];
}EVENT_RECT;

typedef struct _ITEM_STRUCT
{
	bool bPossibleEat;
	Physics* m_Physics;
	struct ItemBag* item;
	ASpriteInstance* pInstance;
}ITEM_STRUCT;

//typedef struct _MONSTER_REGEN_DATA
//{
//	int x,y;
//	int nType;
//}MONSTER_REGEN_DATA;

 
class Field
{
public:
	Field(void* sASpriteSet);
	~Field();

	struct ASpriteSet{//���� ��������Ʈ ����
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};
	ASpriteSet* s_ASpriteSet;

	void Process();
	void Paint(bool isCinema = false);
	void GetMessage();

	void FrontPaint();
	void MiddlePaint();

	boolean workPal(boolean Work, int Pal_Kind, int percent);
	void SetCamera(int camx, int camy = 0);

	void LoadSprite(int nSpriteNum);
	void LoadMap(int nNextStageNum);
	void LoadMap(void* pMinimapData);
	void LoadMapLayer(BackLayer* pBackLayer, char* packName, int packIndex, bool isRepeat = false);

	void ReleaseMap(int nResIdx);
	int m_nSaveStageNum;		//	�ε��� ���ؼ� �������������� ����Ѵ�.(�ε� ��ȣ�� ������� �̹����� ������ �ʴ´�.)

	int m_nSaveResType;			//	�ε��� ���ؼ� �������������� ����Ѵ�.(�ε� ��ȣ�� ������� �̹����� ������ �ʴ´�.)
	int m_nSaveZone;			//	�ε��� ���ؼ� �������������� ����Ѵ�.(�ε� ��ȣ�� ������� �̹����� ������ �ʴ´�.)
	int m_nSaveSector;			//	�ε��� ���ؼ� �������������� ����Ѵ�.(�ε� ��ȣ�� ������� �̹����� ������ �ʴ´�.)

	BackLayer*			pFrontLayer;						//	ĳ���ͺ��� �տ� ��ġ�Ѵ�.

	List2<BackLayer*>	*pMiddleLayerList;
	List2<BackLayer*>	*pLayerList;
	List2<class ASprite*>		*pEnvirSprList;		//	�ȷ�Ʈ ������ �ϴ� �κ��� ��������Ʈ�� ��Ͻ�Ų��.
	class ASprite*		pFieldAs[SPRITE_MAP_MAX];

	int m_nDstCamAngle_X;
	int	m_nSrcCamAngle_X;
	static int m_nFieldSize_X;

	static int m_nWayMoveCharx;			//	�̺�Ʈ���� �����ִ� ĳ������ �ʱ� ��ġ
	static int m_nWayMoveChary;
//	int m_nWayMoveDirection;

	//	ABOUT EVT_WAY	�̺�Ʈ�� �ش��ϴ� ���� ��ġ�� ǥ�� //////////
	List2<MAP_EVT_WAY*>	*pEvtWayList;
	int Process_EVT_WAY(int battleState, int herodir, int herox1, int heroy1);
	void Load_EVT(char* packName, int packIndex);
	void Release_EVT_WAY();

	//	ABOUT EVT_WAY	Ű������ �ʿ��� �̺�Ʈ //////////
	List2<VEvent*>	*pKeyInputEvt;
	int Process_EVT_INPUTKEY();
	void Paint_EVT_INPUTKEY();
	void Release_EVT_INPUTKEY();
	void Paint_EVT_WAY();

	int KeyPressEvent(int dir, int x1, int y1, int x2, int y2);				//	Ű�� ������ �ش�Ǵ� �̺�Ʈ�� �ִ��� üũ�Ѵ�.
	
	//	ABOUT ITEM	
	List2<ITEM_STRUCT*>	*pDropItem;
	void InsertDropItem(struct ItemBag _item, int x, int y);
	struct ItemBag* CheckDropItem(int x1, int y1);
	void	DeleteNowItem();
	void PaintDropItem();
	void ProcessDropItem();

	int m_nCharx;		//	ĳ������ ��ġ
	int m_nChary;

	ASprite* pWayAs;

	List2<DONT_GO_RECT*>	*pDontgoRect;
	List2<EVENT_RECT*>		*pEventRect;
	int	m_nRegenDistance;		//	������ �� ����
//	List2<MONSTER_REGEN_DATA*>		*pMonsterGenRect;


	
	

	//	�ٸ� �ʵ� �ε�� �̹����� �����ش�.
	void DeleteFieldImage();	
	void LoadFieldImage(int idx);

	void ReMatchFieldImage();

	byte m_nEventArrowTimer;
	byte m_nEventAddYPos;
	int Process_EVT_Rect(int herox1, int heroy1);
	void Paint_EVT_Rect();
	int	 m_nLastZoneEvent;

	int  m_nVillageUniqueIdx;//���� ���� �ε���

	//	�����
	void ProcessWorldMap();
	void PaintWorldMap();
	bool KeyEvent(int m_keyCode, int m_keyRepeat);

	void* m_pMiniMapData;
};

#endif