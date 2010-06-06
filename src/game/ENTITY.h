

class ENTITY
{
public:
	// ------------------------------------------------------------ entity types
	const static int k_main_character					= 1;  
	const static int k_chick_chr						= 2;
	const static int k_intro_ani						= 3;
	const static int k_imoticon							= 4;
	const static int k_cloud							= 5;
	const static int k_bug								= 6;


	
#ifdef USE_MAP_EMOTION
	const static int k_emotion							= 9;
	const static int k_max							= 30;  // 갯수 지정해서 적어준다.
#else
	const static int k_max							= 60;  // 갯수 지정해서 적어준다.
#endif

	// ------------------------------------------------------------ entity flags
	//const static int k_flag_hidden					= (1 << 0);
	//const static int k_flag_no_ai_refresh			= (1 << 1);
	//const static int k_flag_linked					= (1 << 2);
	//const static int k_flag_display_list			= 0;//(1 << 3);
	//const static int k_flag_small_object			= (1 << 4);
	//const static int k_flag_HIDELayer				= (1 << 5);
	//const static int k_flag_recal					= (1 << 6);
	//const static int k_flag_tile_cant_move_object	= (1 << 7);

	//const static int k_flag_tile_cant_sit			= (1 << 8);
	//const static int k_flag_tile_shift				= 3;
	//const static int k_flag_tile_mask				= 0x7;
	

	enum { K_SHINE = 220 };

	//SHINE_TYPE
	enum { 
		VALUE_SHINE_TYPE_SMALL_BOTH_FOR_TILE_1= 0,
		VALUE_SHINE_TYPE_SMALL_LEFT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_SMALL_RIGHT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_MIDDLE_BOTH_FOR_TILE_1,
		VALUE_SHINE_TYPE_MIDDLE_LEFT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_MIDDLE_RIGHT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_BIG_BOTH_FOR_TILE_1,
		VALUE_SHINE_TYPE_BIG_LEFT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_BIG_RIGHT_ONLY_FOR_TILE_1,
		VALUE_SHINE_TYPE_SMALL_BOTH_FOR_TILE_4,
		VALUE_SHINE_TYPE_SMALL_LEFT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_SMALL_RIGHT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_MIDDLE_BOTH_FOR_TILE_4,
		VALUE_SHINE_TYPE_MIDDLE_LEFT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_MIDDLE_RIGHT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_BIG_BOTH_FOR_TILE_4,
		VALUE_SHINE_TYPE_BIG_LEFT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_BIG_RIGHT_ONLY_FOR_TILE_4,
		VALUE_SHINE_TYPE_SMAL_CYCLE
	};

};

//class ZONES
//typedef enum
class ZONES
{

	public:
	const static int k_door_0				= 200;
	const static int k_door_1				= 201;
	const static int k_door_2				= 202;
	const static int k_door_3				= 203;
	const static int k_door_4				= 204;

	const static int k_max					= 208;

	//k_poop_cnt				= k_poop3 - k_poop + 1;

	const static int k_start				= k_door_0;
	const static int k_cnt					= k_max - k_start;

	const static int k_data_x				= 0;
	const static int k_data_y				= 1;
	const static int k_data_w				= 2;
	const static int k_data_h				= 3;
	const static int k_data_size			= 4;
};

class LAYER
//typedef enum
{
	public:
	// ------------------------------------------- object sprite layers (normal)
	const static int k_dig					= -1;
	const static int k_inactive				= 0;
	const static int k_shadow				= 1;
	const static int k_ground				= 2;
	const static int k_air  				= 3;
	const static int k_hide  				= 4;
};


class CHARSLOT
{
	public:
	const static int k_slot_shadow		= 0;
	const static int k_slot_effect		= 1;
	const static int k_slot_boby		= 2;	
	const static int k_slot_etc			= 3;
	
};

class ETCSLOT
{
	public:
	const static int k_slot_boby		= 0;
	const static int k_slot_effect		= 1;
	const static int k_slot_effect2		= 2;
};

class FISHSLOT
{
public:
	const static int k_slot_1		= 0;
	const static int k_slot_2		= 1;
	const static int k_slot_3		= 2;
};



class DFLAGS
//typedef enum
{
	public:
	const static int MAP_LAYER		= 1<<1;
	const static int TOP_LAYER		= 1<<3;
	const static int BOTTOM_LAYER	= 1<<2;
	const static int HIDE_LAYER		= 1<<4;

};

#ifdef hasShine

class SHINE	
{
	public:

	enum
	{
		PARAM_INDEX_SHINE_COUNT = 6,
		PARAM_INDEX_SHINE_LENGTH
	};	

	enum
	{
		m_type = 0,
		m_paramY,
		m_paramY2,
		m_paramX1,
		m_paramX2,
		m_paramX3,
		m_minHeight,
		m_maxHeight,
		m_z_order,
		_rectIce_length,
		_rectIce_array

	};

	enum
	{

		SHINE_COUNT = 11,
	};

	//@#if hasShine
	//////////////////////////shine/////////////////////////////////
	enum { SHINE_BIG_IMAGE_WIDTH = 34 };
	enum { SHINE_BIG_IMAGE_HEIGHT = 121 };
	enum { SHINE_BIG_LINE_DY = 74 };
	enum { SHINE_BIG_LINE_ALPHA0 = 128 };
	enum { SHINE_BIG_LINE_ALPHA1 = 6 };
	enum { SHINE_BIG_LINE_WIDTH = 38 };
	enum { SHINE_BIG_LINE_WIDTH2 = 53 };
	enum { SHINE_BIG_LINE_SCAN_LINE = 34 };
	enum { SHINE_SMALL_IMAGE_WIDTH = 21 };
	enum { SHINE_SMALL_IMAGE_HEIGHT = 73 };
	enum { SHINE_SMALL_LINE_DY = 49 };
	enum { SHINE_SMALL_LINE_ALPHA0 = 81 };
	enum { SHINE_SMALL_LINE_ALPHA1 = 3 };
	enum { SHINE_SMALL_LINE_WIDTH = 26 };
	enum { SHINE_SMALL_LINE_WIDTH2 = 30 };
	enum { SHINE_SMALL_LINE_SCAN_LINE = 21 };
	//@#endif //hasShine
};
#endif

//class NPC
//typedef enum
//class NPC
//{
//
//	public:
//	const static int NPC_TC_1       = 0; //도구 점_캐릭터_1 (농장 상점=== farm)
//	const static int NPC_TC_2		= 1; //촌장_캐릭터_2		
//	const static int NPC_TC_3		= 2; //도박장_캐릭터_3		
//	const static int NPC_TC_4		= 3; //레스토랑_캐릭터_3		
//	const static int NPC_TC_5		= 4; //낚시가게_캐릭터_4		
//	const static int NPC_TC_6		= 5; //꽃집_캐릭터_5		
//	const static int NPC_TC_7		= 6; //자동차상점_캐릭터_6
//	const static int NPC_TC_8		= 7; //목공소 wood_man
//
//	const static int EMOTION_TC_1       = 0x00001; //촌장_캐릭터_1 
//	const static int EMOTION_TC_2		= 0x00002; //농사가게_2		
//	const static int EMOTION_TC_3		= 0x00004; //낚시가게_3		
//	const static int EMOTION_TC_4		= 0x00008; //꽃집가게 캐릭터_3		
//	const static int EMOTION_TC_5		= 0x00010; //식당가게_캐릭터_4		
//	const static int EMOTION_TC_6		= 0x00020; //자동차 캐릭터_5		
//	const static int EMOTION_TC_7		= 0x00040; //목공소_캐릭터_6
//	const static int EMOTION_TC_8		= 0x00080; //
//	const static int EMOTION_TC_9		= 0x00100; //
//	const static int EMOTION_TC_10		= 0x00200; //
//	const static int EMOTION_TC_11		= 0x00400; //
//
//};


#define STATE_ENTITY_NULL			0
#define STATE_ENTITY_DEATH			1


#define PATHFINDING_MAX_NODE			PATHFIDING::k_max_node
#define PATHFINDING_MOVE_COST			PATHFIDING::k_move_cost
#define PATHFINDING_DIR_CHANGE_COST		PATHFIDING::k_dir_change_cost

#define DIR_NONE						(DIR::k_none) 
#define DIR_UP							(DIR::k_up) 
#define DIR_DOWN						(DIR::k_down) 
#define DIR_LEFT						(DIR::k_left) 
#define DIR_RIGHT						(DIR::k_right) 
#define DIR_AMOUNT						(DIR::k_amount) 
#define DIR_UP_RIGHT					(DIR::k_up_right) 
#define DIR_DOWN_RIGHT					(DIR::k_down_right) 
#define DIR_DOWN_LEFT					(DIR::k_down_left) 
#define DIR_UP_LEFT						(DIR::k_up_left)  

//class PATHFIDING
typedef enum
{
	k_max_node			= 1500,
	k_move_cost		= 10,
	k_dir_change_cost 	= 30

}PATHFIDING;

typedef enum
{

	// -------------------------------------------------------------- directions
	k_none		= -1,
	k_up		= 0,
	k_down		= 1,
	k_left		= 2,
	k_right	= 3,
	k_amount	= 4,

	k_up_right		= 4,
	k_down_right	= 5,
	k_down_left	= 6,
	k_up_left		= 7,
}DIR;
