#include "SUtil.h"
#include "ASprite.h"
#include "ASpriteInstance.h"
#include "Character.h"
#include "Text.h"

#ifndef		__WORLDMAP_UI_H_
#define		__WORLDMAP_UI_H_


#define		LAND1_X		(-124)
#define		LAND2_X		(-108)
#define		LAND3_X		(-4)	
#define		LAND4_X		(-94)	
#define		LAND5_X		(+118)
#define		LAND6_X		(+118)
#define		LAND7_X		(+87)

#define		LAND1_Y		(+12)	
#define		LAND2_Y		(-54)	
#define		LAND3_Y		(+109)
#define		LAND4_Y		(-99)	
#define		LAND5_Y		(+10)	
#define		LAND6_Y		(+10)	
#define		LAND7_Y		(-85)	

#include "WorldmapSpot.h"


class WorldmapUI
{
public:

	class ASprite*		_spr_Worldmap_WEST;
	class ASprite*		_spr_Worldmap_EAST;
	class ASprite*		_spr_Worldmap_SEA;


	struct _TEXT_PACK*	_txt_AreaName;

	WorldmapUI(int TOWN_id);
	~WorldmapUI();
	void KeyEvent(int m_keyCode, int m_keyRepeat);
	void Process();
	void Paint();

	short Town_Buffer[10][6];

	

	int b_ViewWorldMap;

	int TOWN_Num;
	int spot_Num;//ÀÌµ¿°¡´ÉÇÑ ½ºÆýÀÇ °¹¼ö

	int initSpot;

	int Focus_X;
	int Focus_Y;
	int AccelerationX;
	int AccelerationY;

	int Target_Name;
	int Target_Num;
	int Target_X;
	int Target_Y;
	int MC_posX;
	int MC_derection;


	int Ani_Num;


};

#endif