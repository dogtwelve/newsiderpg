#ifndef _ENTITY_
#define _ENTITY_

#include "..\common\Common.h"
//#include "ASpriteInstance.h"
#include "cGame.h"
#include "cui.h"
//#include "cObject_Character.h"
extern cGame* g_pGame;
//extern cUI* s_cUI;
class ASpriteInstance;
//class cObject_Character;
// ------------------------------------------------------------ nodes macros
#define PACK_POS(x, y)		((y*g_pGame->m_tileMapW)+x)
#define UNPACK_X(pos)		(pos%g_pGame->m_tileMapW)
#define UNPACK_Y(pos)		(pos/g_pGame->m_tileMapW)

// --------------------------------------------------------------- ai macros

#define SET_AI_ENTRY(a, str)		{ s_thinkEntry = a; }
#define SET_AI_CMD(a, str)			{ s_cmd = a; }
#define SET_AI_CMD_TIMER(a)			{ s_cmdTimer = a; }

enum
{
	PAR_PATROL_X1 = 0,
	PAR_PATROL_X2,
	PAR_PATROL_Y1,
	PAR_PATROL_Y2,
	PAR_PROBABILITY,
	PAR_VEL
};

class cEntity	
{	
public:
	cEntity()
	{

	}

	~cEntity();

	//short[] s_zones		= GL_NEW short[ZONES.k_cnt * ZONES.k_data_size]; 
	static short* s_zones;

	int					m_type;
	int					m_state;
	int					m_gameId;	
	int					m_flags;	

	int					m_posX;
	int					m_posY;
	int					m_posZ;

	int					m_OFFposX;
	int					m_OFFposY;

	int					m_posXBefore;
	int					m_posYBefore;
	int					m_posZBefore;

	int					m_velX;
	int					m_velY;
	int					m_velMax;

	int					m_accX;
	int					m_accY;

	int					m_dir;

	int					m_dirNext;
	int					m_dirBefore;	

	int					m_dirCount;
	int					m_dirNotCollCnt;

	///////////////////////////////
	short*				m_params;

	char*				arrow_str;	
	char				arrow_str_array[100];	

	int					m_supportTime; // 오브젝트의 유지시간

	ASpriteInstance**	m_renderer;
	int m_renderer_length;

	cEntity (int type, int sprite_amount);	

	void init (int flags, int pos_x, int pos_y, short* params,int actor_max);	

	void initSprite (int slot_idx, int sprite_idx);	

	void draw (int x, int y, int ox, int oy);
	//void draw (int ox, int oy);

	void set_direct( int _direct );

	int get_direct( );

	void free ();


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY UTILITIES ENTITY UTILITIES ENTITY UTILITIES ENTITY UTILITIES
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	void setFrame (int slot_idx, int afra_idx);

	bool setAnim (int slot_idx, int anim_idx);	

	void setAniLoop (int slot_idx , bool _loop);

	void setAnimNoReset (int slot_idx, int anim_idx);

	void setSpriteLayer (int slot_idx, int layer);	

	void resetSpriteLayer(int slot_idx);	

	void setSpriteFlag (int slot_idx, int flags);	

	void unsetSpriteFlag (int slot_idx, int flags);	

	int* GetRect(int slot_idx);

	int* GetAbsoluteRect(int slot_idx);	

	int* GetFModuleRect(int slot_idx , int module);	

	void setAnimStop (int slot_idx);	

	bool isAnimOver (int slot_idx);	

	int getCurrentAnim (int slot_idx);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY Updata,
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	void update ();	

	void process_move( int _velX, int _velY, boolean _plus );

	void Update_Fish();
	void set_fish();


#ifdef hasShine
	void PaintShine(int x, int y , int ox, int oy) ; 
#endif

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY Util
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	bool collisionObject_UserRect(int _entity_Num, int w, int h);
	bool chcekBolck();

	int directChange(int _slot,int _direct, int* _temp_direct, int* ani);
};	

#endif// _ENTITY_
