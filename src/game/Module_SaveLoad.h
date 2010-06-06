#ifndef _MODULE_SAVELOAD_
#define _MODULE_SAVELOAD_



//////////////////     SIZE     //////////////////
const int RECORD_YEAR_SIZE = 2;
const int RECORD_NAME_SIZE = 16;

typedef enum {
	STORE_OPTION = 0,
	STORE_SLOT1,
	STORE_SLOT2,
	STORE_SLOT3
}StoreType;


//////////////////    INDEX     //////////////////
enum {
	// ENVIRONMENT
	RECORD_SOUND = 0,
	RECORD_SPEED,
	RECORD_VIBRATION,
	RECORD_SAVE1_DATA,
	RECORD_SAVE2_DATA,
	RECORD_SAVE1,
	RECORD_SAVE2,	
	RECORD_OPTION_SIZE
};

enum {
	// USER INFO
	RECORD_USERINFO_NAME = RECORD_OPTION_SIZE,
	RECORD_USERINFO_LAST_YEAR = RECORD_USERINFO_NAME + RECORD_NAME_SIZE,
	RECORD_USERINFO_LAST_MONTH = RECORD_USERINFO_LAST_YEAR + RECORD_YEAR_SIZE ,			
	RECORD_USERINFO_LAST_DAY,				
	RECORD_USERINFO_LAST_WEEK,				
	RECORD_USERINFO_LAST_TIME,			
	RECORD_USERINFO_CURRENT_TIME, 
	RECORD_USERINFO_END
	

};

enum {

	RECORD_USERINFO_SIZE = RECORD_USERINFO_END - RECORD_OPTION_SIZE,

	RECORD_SIZE = RECORD_OPTION_SIZE + RECORD_USERINFO_SIZE*STORE_SLOT2,

	RECORD_BUFFDATA_SIZE = RECORD_OPTION_SIZE + RECORD_USERINFO_SIZE
};




////////////////////    DEFINES    //////////////////
//
//#define RESET_ALL								0x0007
//#define RESET_OPTION							0x0001
//#define RESET_DATA1								0x0002
//#define RESET_DATA2								0x0004
//

////////////////////   MAP DATA  //////////////////

#define MAP_MAX_COUNT	5
#define MAP_MAX_DATA	7
#define MAP_MAX_ENTITY	50

#define MAP_ONE_SIZE	(MAP_MAX_DATA*MAP_MAX_ENTITY*2)+2

#define MAP_MAX_SIZE	MAP_MAX_COUNT*MAP_ONE_SIZE

////////////////////   INIT DATA  //////////////////
//
//#define INIT_YEAR								1900
//#define INIT_MONTH								1
//#define INIT_DAY								1

#define RECORD_FILENAME "sidescroll.loft"

#define RECORD_MAP_FILENAME1 "zoo_map1.loft"
#define RECORD_MAP_FILENAME2 "zoo_map2.loft"
#define RECORD_MAP_FILENAME3 "zoo_map3.loft"
#define RECORD_MAP_FILENAME4 "zoo_map4.loft"
#define RECORD_MAP_FILENAME5 "zoo_map5.loft"


#define RECORD_DATA(i)						    record_buffData[i]

#endif //#ifndef _MODULE_SAVELOAD_
