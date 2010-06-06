#ifndef _CGAME_
#define _CGAME_

#include "..\wipi\brewtowipi.h" 
#include "../common/Engine.h"
#include "../common/Vector1.h"
#include "../wipi/Small_Font.h"
//#include "../wipi/Mid_Font.h"
#include "GAME.h"
//#include "header/package_common_sprite.h"


#include "AppMain.h"
#include "SUtil.h"


#include "Module_Utility.h"
#include "Defines.h"
#include "Module_SoftKey.h"
//#include "AEEText.h"  --sj
#include "Module_SaveLoad.h"

class SUtil;
class AppMain;

class Vector1;
//class Object;
class cEntity;
class ASprite;

//class GloftTheFarm;
class CGraphics;
//class Mid_Font;
class cUI;
//class cMiniGame;
class CEngine;
class cGame;
//class cObject_Character;
//GuanHao. IGP
class CWipiIgp;

extern cGame* g_pGame;

//#define ASSERT_str(x) {if(!(x)) {__asm int 3}}
#define ASSERT_str(x)

#ifndef WIPIC
typedef enum MH_KeyCode{
	MH_KEY_0		= 0,
	MH_KEY_1		,
	MH_KEY_2		,
	MH_KEY_3		,
	MH_KEY_4		,
	MH_KEY_5		,
	MH_KEY_6		,
	MH_KEY_7 		,
	MH_KEY_8		,
	MH_KEY_9		,
	MH_KEY_POUND	,
	MH_KEY_ASTERISK	,
	MH_KEY_SOFT1	,
	MH_KEY_SOFT2	,
	MH_KEY_UP		,
	MH_KEY_LEFT		,
	MH_KEY_RIGHT	,
	MH_KEY_DOWN		,
	
	
	MH_KEY_SELECT	,
	MH_KEY_CLEAR	,
	MH_KEY_SEND		= -10,
	MH_KEY_END		= -11,
	MH_KEY_POWER		= -12,
	MH_KEY_SIDE_UP		= -13,
	MH_KEY_SIDE_DOWN	= -14,
	MH_KEY_SIDE_SEL	= -15,
	
	MH_KEY_FLIPDOWN	= -17,
	MH_KEY_FLIPUP		= -18,
	MH_KEY_INVALID	= 0

} MH_KeyCode;
#endif

enum {
	CHANNEL_NIGHT = 0x01,
	CHANNEL_COLORALPHA = 0x02,
	CHANNEL_GRAY = 0x04
};

class cTempStr
{
public:
	cTempStr(int bufSize){_str = GL_NEW char[bufSize];_bufSize=bufSize;MEMSET(_str,0,bufSize);_bUsed = false;}
	~cTempStr(){delete[] _str; _str=NULL;}
	void reset(){MEMSET(_str,0,_bufSize); _bUsed = false;}
	int insert(int pos);
	int _bufSize;
	bool _bUsed;
	char* _str;
};


class cTempStrArray
{
public:

	static const int initSize = 2;
	static const int tempBufferSize = 1024;

	cTempStrArray():
	_nTotalStr(initSize),
	_nUsedStr(0)
	{
		_strArray = GL_NEW cTempStr*[_nTotalStr];
		MEMSET(_strArray, 0, _nTotalStr);
		for(int i=0; i < _nTotalStr; i++)
		{
			_strArray[i] = GL_NEW cTempStr(tempBufferSize);
		}
	}
	
	~cTempStrArray()
	{
		release();
	}
	
	char* getStr()
	{
		if(_nUsedStr == _nTotalStr)
			reloc(_nTotalStr*2);
		for(int i=0; i<_nTotalStr; i++)
		{
			if(_strArray[i]->_bUsed == false)
			{
				_strArray[i]->_bUsed = true;
				_nUsedStr++;
				return _strArray[i]->_str;
			}
		}
		return NULL;
	}
	void releaseStr(char*& str)
	{
		for(int i=0;i<_nTotalStr;i++)
		{
			if(str == _strArray[i]->_str)
			{
				_strArray[i]->reset();
				str = NULL;
				_nUsedStr--;
				return ;
			}
		}
//		ASSERT_str(false);
	}
	
private:
	void release()
	{
		if(_nUsedStr > 0)
		{
			ASSERT_str(false);
		}
		for(int i=0;i<_nTotalStr;i++)
		{
			if(_strArray[i]->_bUsed)
			{
				ASSERT_str(false);
			}
			delete _strArray[i];
			_strArray[i] = NULL;
		}
		delete[] _strArray;
	}
	
	void reloc(int size)
	{
		ASSERT_str(false);
		if(size <= _nUsedStr) 
		{
			ASSERT_str(false);
		}
		cTempStr** newArray = GL_NEW cTempStr*[size];
		for(int i=0; i<_nTotalStr; i++)
		{
			newArray[i] = _strArray[i];
		}
		for(int i=_nTotalStr; i<size; i++)
		{
			newArray[i] = GL_NEW cTempStr(tempBufferSize);
		}
		_nTotalStr = size;
		delete[] _strArray;
		_strArray = NULL;
		
		_strArray = newArray;
	}
private:
	int _nTotalStr;
	int _nUsedStr;
	cTempStr** _strArray;
};



class cGame : public CEngine /*extends javax.microedition.lcdui.Canvas implements Runnable 	*/
{

public:
	
	//int16 touch_x , touch_y , touch_status ;
	int16 obj_old_posX   ;

	//void Set_GameStart(int _state);
	//void OEMC_knlExecuteEx(    char*  url);  --sj;
	char _nickName[16];
	bool showIGPNew;

	//int16 touch_goto_x , touch_goto_y , touch_goto_status;
	
	char* load_stringArray[1000];

	cTempStrArray* m_pStrArray;

#ifdef USE_DRAWRGB_FOR_TILES
	ASprite** m_sprTileset;
	//static const int m_sprTileset_length = TILE_LAYER.k_id_cnt;
#else
	CImage*** 	m_tileSet;/* = GL_NEW Image[TILE_LAYER.k_id_cnt][];*/			//gh
#endif
	virtual ~cGame();
	

	int loadTileMap_rtn_length;
	int Data_readAll_rtn_length;


	
	MC_GrpFrameBuffer m_pIDisplay;
	IShell*			m_pIShell;
	IBitmap*			_ddb_buffer;


	AppMain*	pAppMain;

	//GuanHao. IGP
//	CWipiIgp* m_pIgp;
//	CKeypad *m_keypad;

	void DrawPage(CGraphics* g, char* str, int width, int height, int X, int Y, int tt, int anchor);


	//void RankingKeyCode();

	void DrawPage_Bold(CGraphics* g, char* str, int x, int y, int sizeX, int sizeY, int ddd, int anchor);

	//cGame();

	void tttt()
	{

		//this->application = application;

		unsigned char* pix =  GL_NEW unsigned char[2 * BB::CDB_W * BB::CDB_H];
		//m_imgBB = GL_NEW CMutableImage( BB::CDB_W, BB::CDB_H, (BB::CDB_W)<<1, 16,pix);
		//m_gBB	= &m_imgBB->GetGraphics();

		
		//backbuffpix =  GL_NEW unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT];

		//g->m_buffPixel = backbuffpix;
		//m_imgBBA = GL_NEW CMutableImage( SCREEN_WIDTH, SCREEN_HEIGHT, (SCREEN_WIDTH)<<1, 16,pix);
		//m_gBBA	= &m_imgBBA->GetGraphics();


		//jFont = GL_NEW M_KR_Font(SCREEN_WIDTH,SCREEN_HEIGHT);
		jFont = GL_NEW S_KR_Font(SCREEN_WIDTH,SCREEN_HEIGHT);

		//jFont.setOutline(true);
		//jFont.setOutlineColor(0x000000);

		gameInit();


	}




//	int resources_getPackageIndex(int resource) ;	

//	char* resources_getPackageFileName(int resource) ;	

//	int resources_getResourceIndex(int resource) ;	

//	int resources_getResourceSize(int resource) ;	

//	int resources_getResourceOffset(int resource) ;	

	static const bool 		k_data_dbgDataAccess = false;	

	static const int 		k_data_skipbufferSize = 256;	

	byte* 		s_data_skipBuffer;	

	CStream*	s_data_is;	

	char*		s_data_filename;	

	int			s_data_nbData;	

	int*		s_data_offset;	

	int			s_data_start;	

	int*		s_data_sizes;	

	int 		s_data_curOffset;	

	int			s_data_lastDataOpenType;	

	//static const  String [] 		s_data_mimeType = {	
	//	"unknown",	
	//	"audio/x-wav",	
	//	"audio/midi",	
	//	"audio/mpeg",	
	//	"ott",	
	//	"audio/amr",	
	//	"application/x-smaf",	
	//	"audio/basic",	
	//	"audio/x-vorbis",	
	//	"audio/3gpp",	
	//	"audio/amr-wb",	
	//	"audio/amr-wb+",	
	//	"audio/x-gsm",	
	//	"audio/x-gsmefr",	
	//	"audio/qcelp",	
	//	"audio/spmidi",	
	//	"audio/x-realaudio",	
	//	"audio/x-aiff",	
	//	"audio/x-ms-wma"	
	//};	

	bool Data_init (char* filename)	;

	void Data_open (int index);	

	void Data_skip (int nb)	;

	void Data_close ()	;	

	void Data_free ()	;

	int Data_read ();	

	int Data_read (byte* _array, int length);

	int Data_read (byte* _array, int off, int len);	

	int Data_readFully(byte* _array, int length)	;	

	int Data_readFully(byte* _array,int offset,int length)	;	

	byte* Data_readAll (int index);	

	int Data_readU8 ();

	int Data_readU16 ();	

	int Data_readU16LittleEndian ();	

	int Data_readU16BigEndian ();	

	int Data_readS32 ();	

	int Data_readS32LittleEndian ();	

	int Data_readS32BigEndian ()	;	

	static const int ARRAY_BYTE 	= 0;	
	static const int ARRAY_SHORT 	= 1;	
	static const int ARRAY_INT 		= 2;	

	int** Mem_ReadArray( );
	int	Mem_ReadArray_rtn_length;

	int* Mem_ReadArray2();

	byte* loadTileMap (int raw_index);	

	void loadColMap (int col_index)	;

	void loadTileSet (char* pack_index, int indexCnt_Num)	;	

	void loadTileSetA (char* pack_index, int indexCnt_Num);	

	void loadActorsData();	

	int* loadActorsDataSpriteList();	

	void BackBuffer_RefreshTiles (int minX, int minY, int maxX, int maxY);	

	void BackBuffer_Update (int x, int y);	

	void BackBuffer_Redraw (byte* layer, byte* flipmap, int sx, int sy,int layer_length);	

	void BackBuffer_Draw (int x, int y);	

	void BackBuffer_DebugRefresh (int sx, int sy);	

	byte*** text_array;/* = GL_NEW byte[5][][];*/	 //gh
	int text_array_length;
	int* text_array_sub_length;

	void Text_loadTextPack (char* filename, int index , int text_index);	

	char* Text_getString (int index,int text_index);	

	void Text_freeText (int text_index)	;	

	int s_drawPageOffset[200];	
	int s_drawPage_nLine;	
	bool s_isDrawPageInit/* = false*/;	
	int _index1/* = -1*/;	
	int _index2/* = -1*/;	
	int _line_spacing/* = 2*/;	
	int _char_spacing/* = 0*/;	

	void SetSubString(int i1, int i2);

	void InitPage(char* s, int width);	

	int DrawPage_Bold(CGraphics* g, char* s, int x, int y, int width, int height, int scroll, int anchor, bool auto_scroll);	

	int DrawPage(CGraphics* g, char* s, int x, int y, int width, int height, int scroll, int anchor, bool auto_scroll);	

	//StringBuffer* strbuff /*= GL_NEW	StringBuffer();*/	 //gh
	char* stringChange(char* strIndex , int strAdd, char** strRtn);	
	char* stringChange(char* strIndex , char* strAdd, char** strRtn);

	char** String_phase(char* str);	//gh

	char** String_phase_Quest(char* str);	 //gh

	void Set_Emotion(int _slot , int _chr , int _index);

#ifdef USE_MAP_EMOTION
	void Set_Emotion_Pos(int _slot , int _posX , int _posY , int _index);//612
#endif

	void Set_FreeEmotion(int _slot, int _chr);//612	

	void Set_ALLFreeEmotion();//612

	char Get_Emotion(int _slot, int _chr);//612	

	int Get_Emotion_Ani(int _slot, int _chr);//612	

	void Set_talk(int _param, int _slot);	

	bool collisionDetection (int* rect1, int* rect2);	

	bool collisionDetection (int* rect, int x, int y);	

	int canDropObject(int* rect, int posX, int posY);	

	void getCollisionRect(int * rect , cEntity * _obj);

	bool collideWithZone(int zoneID);

	bool collideWithZone(int* rect);	

	bool collideWithZoneAnimal(int zoneID, int _m_posX, int _m_posY);	

	void loadSprite (int index);	

	class TrampolineExtraParam	
	{	
	public:
		static const int TrampolineType = 0;	
	};	

	class WaitType	
	{
	public:
		static const int DialogEnd = 0;	
		static const int BarMovementEnd = DialogEnd + 1;	
		static const int FocusCameraOnPlayer = BarMovementEnd + 1;	
		static const int PlayerBlocked = FocusCameraOnPlayer + 1;	
		static const int Count = PlayerBlocked + 1;	
		static const int None = Count + 1;	
	};

/*




	static const int CCMD_CAMERA = 10;	
	static const int CCMD_CAMERA_SET_POS = (CCMD_CAMERA + 1); 
	static const int CCMD_CAMERA_CENTER_TO = (CCMD_CAMERA + 2); 
	static const int CCMD_CAMERA_FOCUS_ON = (CCMD_CAMERA + 3); 

	static const int CCMD_OBJ_LAYER = 20;	
	static const int CCMD_OBJ_LAYER_SET_POS = (CCMD_OBJ_LAYER + 1); 
	static const int CCMD_OBJ_LAYER_SET_ANIM = (CCMD_OBJ_LAYER + 2); 
	static const int CCMD_OBJ_LAYER_ADD_FLAGS = (CCMD_OBJ_LAYER + 3); 
	static const int CCMD_OBJ_LAYER_REMOVE_FLAGS = (CCMD_OBJ_LAYER + 4); 

	static const int CCMD_BASIC = 30;	
	static const int CCMD_BASIC_SET_POS = (CCMD_BASIC + 1); 
	static const int CCMD_BASIC_SET_ACTION = (CCMD_BASIC + 2); 
	static const int CCMD_BASIC_SET_ACTION_FLAGS = (CCMD_BASIC + 3); 
	static const int CCMD_BASIC_OBJEVENT1 = (CCMD_BASIC + 4); 
	static const int CCMD_BASIC_OBJEVENT2 = (CCMD_BASIC + 5); 
	static const int CCMD_BASIC_OBJEVENT3 = (CCMD_BASIC + 6); 
	static const int CCMD_BASIC_EVENT1 = (CCMD_BASIC + 7); 
	static const int CCMD_BASIC_EVENT2 = (CCMD_BASIC + 8); 
	static const int CCMD_BASIC_EVENT3 = (CCMD_BASIC + 9); 

	static const int CCMD_SI = 40;	
	static const int CCMD_SI_SET_POS = (CCMD_SI + 1); 
	static const int CCMD_SI_SET_ANIM = (CCMD_SI + 2); 
	static const int CCMD_SI_ADD_FLAGS = (CCMD_SI + 3); 
	static const int CCMD_SI_REMOVE_FLAGS = (CCMD_SI + 4); 

	static const int CCMD_FIRST_CUSTOM = 100;	

	enum AuroraFlags	
	{	
		Invisible = 0x800000,	
		FlipX	  = 0x10000,	
	};	


	static const int CTRACK_BASIC = 0;	
	static const int CTRACK_CAMERA = 1;	
	static const int CTRACK_OBJ_LAYER = 2;	


	static const int CINEMATIC_PLAYING = 0x01;	
	static const int CINEMATIC_CIRCLE = 0x02;		
	static const int CINEMATIC_PLAYED = 0x04;		

*/
	//byte [][][] 	s_cinematics;			//gh
	byte*** 	s_cinematics;			//gh
	int			s_cinematics_length;
	int*		s_cinematics_sub_length;
	int**		s_cinematics_sub_sub_length;

	short*     	s_cinematicsId;
	int     	s_cinematicsId_length; 		

	short*     	s_cinematicsFrameTime; 	
	int         s_cinematicsFrameTime_length;
	
	int**   	s_currentFramePos;
	int			s_currentFramePos_length;
	int*		s_currentFramePos_sub_length;
	bool 		s_cinematicsPause;	
	bool 		s_cinematicsSkip;	
	bool		s_enableUserSkipCinematic;	
	bool		s_smoothCinematicRestoreCamera;	
	int			s_cinematicWaitType;


	int**		s_runningCinematicTrackActors;
	int			s_runningCinematicTrackActors_length;
	int*		s_runningCinematicTrackActors_sub_length;
	int			s_nextCinematic/* = -1*/;	

	enum SpecialCinematicCommands	
	{	
		BlockedPlayer			= 0x0001,
		ReFocusingCamera		= 0x0002,
	};	

	int s_specialCineCommand;	

	bool s_savePlayerPositionAfterCinematic;	

	void LoadCinematics (byte* data);	

	void ResetCinematic(int id);	

	void ResetCinematics();

	void FreeCinematics();	

	void EndCinematic (int index);	

	void PauseCinematics ();

	void ResumeCinematics ();	

	int GetCinematicIndex (int id) ;	

	int GetActiveCinematicCurrentTime();	

	bool IsCinematicActive();	

	bool IsCinematicRunning();	

	void EndCinematicWait();	

	void EndAllCinematic();	

	void UpdateCinematic();	

	cEntity* GetActorByUID(int uid);	

	void StartCinematic (int index);	

	void CinematicEvent(int param);	

	void updateFxDrawingArea ();	

	//void updateFxDrawingArea_competitor ();


	int    mascot_currentState/* = 0 */;	

//	int    mascot_currentAction/* = 0 */;	

	int    mascot_mascotDirect/* = DIRECT_LEFT; */;	

	int    mascot_currentDispX/* = 131 */;	

	int    mascot_currentDispY/* = 131 */;	

//	int    mascot_barDispY/* = 52 */;	

	char   mascot_currentText[4096];

	int		mascot_currentImage;

	char     mascot_currentImageName[100];

	int      mascot_currentTextScroll;

	int		 mascot_s_sceneState;

	int		 talk_cnt;	

	ASprite* mascot_currentImage_Sprite;	

	int      popup_currentState/* = 0 */;	
	int      popup_currentAction/* = 0 */;	

	int      popup_mascotDispX/* = 131 */;	
	int      popup_barDispY/* = 65 */;	

//	char*    popup_currentText;	
	char     popup_currentText[1024];	

	int      popup_currentImage;	

	int      popup_currentTextScroll;	

	int		date_currentWeekDay;	
	int		date_currentDay;	
	int		date_currentYear;	
	int		date_currentMonth;	
	//int	date_currentHour;

	int		m_clockCounter;     
	int		m_worldClockM;	

	int		m_clockH; 			
	int		m_clockM; 			

	int		m_clockHPosX;	
	int		m_clockHPosY;	
	int		m_clockMPosX;	
	int		m_clockMPosY;	


	//int move_zip/* = 0*/;	
	//bool bmove_zip/* = false*/;	

	//int selectMenuY[5]; 	
	//int maxMenuX/* = 4*/; 	
	//int maxMenuY/* = 1*/;	
	//int dipIndex/* = 0*/;	
	//int menuIndex/* = 0*/;	
	int currentTextScroll;	

	//bool bInvenCLR;	

	int		 softkey_leftText;	
	int      softkey_rightText;	
	int      softkey_centerText;	
	bool     softkey_drawBar;	
	int      softkey_currentSelection;	



	//char*               RECORD_FILENAME; /* = "/farm_tycoon9.sav";*/	 //gh

	//gh
	byte*  record_buffData;
	byte*  record_mapUserData;

//	short  mapUser_count;
//	short**  mapUser_Data;
	short  mapUser_Data[50][7];

	//= GL_NEW byte  [((((((1 +1) +1) +1) +1) +1)  + ((((((((((((((((((((((((((1 +1) +1) +1) +1) +1)  + 6 )  + 2 )  + 1)  + 1)  + 1)  + 4 )  + 4 )  + 4 )  + 1)  + 1)  + 1)  + 4)  + 4)  + 1)  + 4)  + 1)  + 1)  + 50 ) + 124*4 )  - (((((1 +1) +1) +1) +1) +1)   ) *2)+1 ) ];	
	//int data_Index;	


	//int q_type;	
	//int q_desc;	

	//int		q_request[4][4][8];	 //gh
	//const static int q_request_length = 4;
	//const static int q_request_sub_length = 4;
	//const static int q_request_sub_sub_length = 8;

	//int q_request_string;

	//int q_satisfaction[5];	
	//char*		q_string[5][2];	
	////char* temp_Quest_String;
	//bool 	b_q_result; 


	bool DrawSort(cEntity*  a, cEntity*  b);	

	void updateAndDrawViewTop ();	

	Vector1 * _actorDrawVector;/* = GL_NEW Vector();	*/ //gh

	void drawViewTop ();	

	bool IsInCamera (int* rect);	

	bool IsInCamera (int posX , int posY) ;	

	bool have_save_file;
	//ASprite*						load_sprite;	

	int				            load_currentStep;	
	int				            load_totalSteps1;	
	int				            load_totalSteps2;	
	int				            load_totalSteps;	

	int			                load_Tip_str;	

	int load_nextState;	

	int                         load_spriteListSize;	
	int*						load_spriteList;
	int                         load_spriteList_length;
	ASprite**					load_spriteArray;
	int							load_spriteArray_length;

	int                         load_commonSpriteListSize;	
	int*                        load_commonSpriteList;	
	int                         load_commonSpriteList_length;	
	ASprite**					load_commonSpriteArray;
	int							load_commonSpriteArray_length;

	int                         load_bgSpriteListSize;	
	int*						load_bgSpriteList;	
	ASprite**					load_bgSpriteArray;	
	int							load_bgSpriteArray_length;

	//int                         load_dataListSize;	
	//int*						  load_dataList;	
	//int						  load_commonDataListSize;	
	//int*						  load_commonDataList;	
	//char**					  load_StringArray;	

	//int*						load_gameData;	

	bool						load_gamefile;	
	int*						load_gmaeList;	
	int                         load_gmaeList_length;
	int*						load_gmaeSpriteList;	
	int							load_gmaeSpriteList_length;	
	char*						load_gameTileList;	

	bool			            load_bShowProgressBar;	



	bool load_update();	

	bool load_update1();	

	bool load_update2();	


	void load_paint(CGraphics* g);

	void drawProcessBarNoImage(CGraphics* g, int _current, int _total);

	void drawProcessBar(CGraphics* g, int _current, int _total);	


	void load_reset();	

	void process_State_Load( int message );	

	void Free_GameRes( );	
	
	/////////////////////////////////////////////////////
	// TEXT_FIELD
	/////////////////////////////////////////////////////
	
	//ITextCtl		*		_cText;
	////ITextCtl * getUiCom(){ return _cText;}


	//void set_textField( int _bAutomata_ );
	//int update_Key_textField( );
	//char* getText(char** strRtn);

	//char textField_Name[16];
	//
	//int m_automateType;

	//byte _bAutomata[AUTOMATA_NUM1];//={AEE_TM_ENGLISH_US,AEE_TM_NUMBERS,AEE_TM_HANGUL};
	
	

	////////////////////////////////////////////////////



	void process_State_Load_Common( int message );

	//void Set_Quest_str0( );//612

	bool mascot_isHidden();	

//	int mascot_getCurrentState();	

//	void mascot_setText(char* _str);

	void mascot_show(int action, char* String);	

	void mascot_hide(/*bool_TYPE isGradual*/)	;	

	void mascot_Keyupdate();	

	void mascot_paint();	

	void popup_paint();	

	void popup_update();

	//bool popup_isHidden();	

	int popup_getCurrentState();	

	void popup_show(int action, char* String);	

	void popup_hide(/*bool_TYPE isGradual*/);

	void popup_end(/*bool_TYPE isGradual*/);	

	bool bMapMove_PopupShow;	
	//void set_MapMove_Popup(char*  _str);

	//bool updatge_MapMove_Popup();	

	void date_Initialize();	

	int date_getCurrentDay();	

	int date_getCurrentYear();

	int date_getCurrentMonth();	

	int date_getCurrentWeekDay();	

	void update_setDay( );

	int Check_setDay( );


	const static byte s_clockPrecalc[];// 
	/*= 	{	
	0, -1,	
	1,  0,	
	0,  1,	
	-1,  0, 
	};	
	*/


	void updateClock ();	

	int clock_color;

	void drawClock ();	

	void setClock(int _hour, int _min);

	int getClock();

	void Draw_Time();

	void Draw_MainUI()	;	

	void Draw_Maingauge(int pos_y);	
	void Draw_MainCount(int pos_y);

	void Draw_Date(int pos_y );	
	
	void set_fadeOut(int _index);

	void set_fadeIn();

	//void setSleep(int index );	

	//void drawInventory();	

	//void resetKey( bool _system );	


	//void drawInventoryBox();	

	//void Keypressed_inventory();	

	int drawScrollY(int h, int p , int pa);	

	void draw_result_popup(int kind , int select_index, int item_max_index);	


	void selectBox(int x, int y, int w, int h);	


	void fillRoundRect( int iX_, int iY_, int iWidth_, int iHeight_ );	


	//bool update_chrPopup(int _depth ,int maxMenu);	

	//bool update_MarketPopup(int _depth ,int maxMenuX , int maxMenuY);	

	//void draw_MemoPopup(char* _str , char* _strA);	

	//void set_market_item(int _group);	

	//void SetGroupBuy_Item(int _group);	

	//void SetGroupSell_Item(int _group);	

	//void SetGroupRepair_Item(int _group);	

	//int SetGroupGift();	

	//void sort_Inven_Item();	

	//int set_Inven_Item(int _index, int _ea, int _quality);	

	//int set_Inven_ItemAA(int _index, int _ea, int _quality);//612

	//int get_Inven_item_Durability(int _index, int _ea)	;	

	//void set_Inven_Item_Repair(int _item);	

	//int set_Inven_fish(int _item ,  int _ea);	

	//int set_Inven_fishAA(int _item ,  int _ea);//612

	//int set_Inven_fish_Del(int _ea);

	//int get_Inven_fish_ea()	;	

	//int get_Inven_Item_ea(int _item)	;	

	//int get_Inven_fruit_ea( );	

	//int get_Inven_empty_ea( );//485

	//int get_Item_price(int _index , int _but_state);	

	//int get_Item_ea(int _index);	

	//int get_Item_kind(int _index);	

	//int get_Inven_Item_Level(int _item);	

	//void reset_Inven_Item();	

	//void item_use(int _item);	

	//void set_savemoney(int _money);

	//void set_money(int _money);	

	//int add_money(int _money);	

	//int get_money()	;	

	void goto_map( int _state );	

	//void init_popup( );	

	//void draw1_popup( int x, int y, int w, int h, int _title_fameindex , bool _viewmoney, bool _viewok , int _viewnum)	;



	//int set_Mail(int index);


	//bool check_Mail();

	//void Set_Quset();

	//void Process_FireWork();

	//void Draw_FireWork();

	//void Free_FireWork();

	//void Stop_FireWork();

	//void set_MainPopup(char* str);

	//void draw_MainPopup();	

	//void draw_item_info(int x,int y,int index);	

	//char* Set_Quest_strA(int _index, char** buf);

	void draw_round_rect(int x, int y, int w, int h , int color, int color1);	


	//void sort_mail();//485

	//bool get_GOTOMAP();//485


	//bool isNetFromGame;

	//int			bank_point;				
	//int			bank_savepoint;			
	//int			bank_uppoint;	

	//int			charge_Point;
	//int			bank_ChrgePoint;//Bank Charge

	//int			bank_state;				
	//int			bank_inputmoney;		

	/*	int			bank_monthLoan;	*/	//485
	//int			bank_LoanYield;			// 485
	//int			bank_DelayYield;		// 485
	//int			bank_LoanTotal;	//612


	//int			bank_monthYield1;		


	//int			bank_LoanYield1;		
	//int			bank_LoanYield2;		

	//int			bank_Loandate;		



	//void Init_Bank( );

	//void Init_Month_Money( int _state );

	//void Init_Bank_Money();//485

	//void Free_Bank( );	

	int maxVol/* = 5*/;		


	//Player*  m_sound/* = NULL*/;  //Robust	


	//byte** MultysndBuff; /*= null;*/	 //gh

	int cursound;	
	bool curFlag/* = false*/;	


	char* getSoundName(int soundID);	

	void  initMultySound(int _Maxsound);	

	void  loadMultySound( int _buffnum ,int soundID  );	

	void  freeMultySound();	

	void  playMultySound(int _buffnum, bool loopflag);	

	void  freeSound();	

	void Sound_Load();

	void playSound(int soundID, bool loopflag)	;	

	void stopSound() ;	

	void setVib(int time);	

	void setVolSideKey( int off );

	void setVol( int cursound ,  int _vol);	

	void changeVolume(int diff);	

	void softkey_init(int leftText, int rightText, int centerText);	

	void softkey_init(int leftText, int rightText);	

	void softkey_initLeft(int text)
	{
		softkey_leftText = text;
		//softkey_rightText = rightText;
		softkey_centerText = 0;
		softkey_currentSelection = SOFTKEY_NONE;
	}

	void softkey_initRight(int text)
	{
		//softkey_leftText = leftText;
		softkey_rightText = text;
		softkey_centerText = 0;
		softkey_currentSelection = SOFTKEY_NONE;
	}
	int softkey_getCurrentSelection()	;	

	byte softkey_update();	

	//GuanHao. net. softkey
	//void softkey_paint();	
	void softkey_paint(bool isFromNet=false);	



	////////////////////////////////////////////////////////////////
	//** save DATA
	////////////////////////////////////////////////////////////////
	StoreType	m_dataslot;

	void  ResetRecord( StoreType _type );

	void Save_AllGame( StoreType _type );

	void SetStoreType(StoreType _type);
	StoreType GetStoreType();

#ifdef USE_CHECKSPACE
	bool s_bCanLoad;
	bool s_bCanSave;
	bool s_bSaveMode;

	void CheckSpace(const char* dataBaseName, bool &canLoad, bool &canSave, int size, bool remove);
	void UpdateNoSpace();
#endif

	//////////////////////////////////////////////////////////////
	//** SAVE DATA
	//////////////////////////////////////////////////////////////

	bool  SaveLoadRecord(bool  save );	

	void  SetRecordDataByte(byte* buffData,int  index, int  value  );	
	char GetRecordDataByte(byte* buffData,int  index);	

	void  SetRecordDataShort(byte* buffData,int  index, int  value);	
	short  GetRecordDataShort(byte* buffData,int  index);	

	void  SetRecordDataInt(byte* buffData,int  index, int  value);	
	int  GetRecordDataInt(byte* buffData,int  index);	
	
	void SetRecordDataLong(byte* buffData,int index, M_Int64 value);
	M_Int64 GetRecordDataLong(byte* buffData,int index);
	
	int SetRecordDataArray(int dst_off, char* src ,int src_length);
	int GetRecordDataArray(int src_off, char* dst, int dst_length);


	short GetRecord_BigEndianShort(byte* buffData,int index);
	void SetRecord_BigEndianShort(byte* buffData,int index, int value);


	//////////////////////////////////////////////////////////////
	//** USER MAP DATA
	//////////////////////////////////////////////////////////////

	bool SaveLoad_MapRecord(int _mapindex, bool save ) ;

	void Get_UserMapRecord(int _mapindex ); 

	void Set_UserMapRecord( int _count, int _index, short* _data, boolean _save );

	void Add_UserEntity(short* params, boolean _save );


	int get_Quest_EntityToNpc(int _index);

//	GloftTheFarm*		application;	

	CGraphics*          g;                              

	int				game_appStatus;

	M_Int64 		s_game_frameDT;

	M_Int64			s_game_frameDTTimer;

	//long 			s_game_timeWhenFrameStart;	//no used
	M_Int64			s_game_timeSystem;

	S_KR_Font*		jFont;	
	//M_KR_Font*			jFont;
	//int				s_iCounter;

	int				game_currentState;				
	int				game_nextState;	

	bool	        game_bEnterNextState;           
	bool			game_bExitCurrentState;	

	int				game_sub_state;	
	int				game_save_state;

	//int				game_keyNet;//612
	//int				game_keyPressed;	
	//int				game_keyReleased;	
	//int				game_lastKeyPressed;
	//int				game_netKeyPressed;//612
	//int				game_keyRepeatCount;	

	//int				game_keyPressedSingle;	
	//int				game_keyPressedHeld;	

	//int				game_keyPressedCount;	
	//int				game_keyReleasedCount;	

	int				game_currentSubState;	
	int				game_nextSubState;	

	int				game_counter;

	int				m_sndVol/*		= 3*/;	
	int				m_vibrateOn/*	= 1*/; 
	int				m_speed/*		= 0*/; 
	int				m_runtime/*		= 0*/;

	int				popup_MoveposX;
	int				popup_MoveposY;
	int				popup_MoveDirectX;
	int				popup_MoveDirectY;
	int				popup_DrawposX;
	int				popup_DrawposY;
	int				popup_sizeX;
	int				popup_sizeY;
	int				popup_imgsizeX;
	int				popup_imgsizeY;
	bool			bpopup_move;
	bool			bpopup_line;


public:
//	bool				load_delay_from_game;

	CEngine*			s_cEngine;
//	cUI*				s_cUI;	
//	cMiniGame*			s_cMiniGame;	


	int**				game_resourceOffset;	  //gh
	CStream*			game_resourceStream;	
	int					game_currentResourceCategory;	
	int					game_curResOff;	

	//public static String			menu_str[];
	char**				menu_str;

	//Random*            s_math_random;/* = GL_NEW Random();*/	//gh

	int					m_tileMapH;	
	int					m_tileMapW;	

	byte**				m_tileMapLayer; /*= GL_NEW byte[TILE_LAYER.k_id_cnt][];*/
	int					m_tileMapLayer_length;
	int*				m_tileMapLayer_sub_length;

	byte**				m_tileFlipLayer;/* = GL_NEW byte[TILE_LAYER.k_id_cnt][];	*/
	int					m_tileFlipLayer_length;
	int*				m_tileFlipLayer_sub_length;

	byte*				m_actorsData;	
	int                 m_actorsData_length;
	int                 m_actorsMax_count;

	int                 m_actorsNew_count;	// USER NEW COUNT

	byte*				m_cinematicData;	
	ASprite*			ts;

#ifndef USE_DRAWRGB_FOR_TILES
	ASprite*			mapSprites[100];
	int					mapSprites_len;

	void				addMapSprite(ASprite* sp);
	void				resetMapSprite();
#endif
	short*				m_tileBB;	

	CMutableImage*			m_imgBB;			
	CGraphics*				m_gBB;	
	
	unsigned char*			backbuffpix;
		
	int 					m_lastTileX;	
	int 					m_lastTileY;	
	int 					m_oldLevelX;	
	int 					m_oldLevelY;	

	int					m_map_kind;

	//int					map_kind;

	char* 				m_mapCol;	
	char* 				m_mapUserCol;	

	//int					m_mapOldX;	
	//int					m_mapOldY;	
	int					m_mapX;	
	int					m_mapY;	
	//int					m_mapXMin;	
	//int					m_mapYMin;	
	//int					m_mapXMax;	
	//int					m_mapYMax;	

	//int					m_offsetXMax;	
	//int					m_offsetYMax;	


	//bool				m_displayListYSort;	

	bool				m_colMap_hold;	
	int					m_colMap_water;	
	int					m_colMap_count;	

	//int					m_CameraX;
	//int					m_CameraY;
	// Auto move variable
	//int					auto_move;

	cEntity*			m_viewTopFocus;	
	int					m_viewTopFocusOffX;	
	int					m_viewTopFocusOffY;	

	cEntity*			m_objectSmall;	

	

	int					m_CharAbility;

	int					m_StateStory;
	//int					temp_m_StateStory;	
	//int					m_AnimationNum;

	//int					m_Npc_tc;	
	//byte		m_Quest[10][3];	 //gh
	//const static int			m_Quest_length = 10;//612add
	//const static int			m_Quest_sub_length = 3;//612aded

	//static int[]			m_mail = new int[5];
	//int					m_mail[5];  //sec. 
	//static const int		m_mail_length = 5;

	//int					m_Npc_Number;

	//int					 dogChangeBoy;	

	//int					 dogAction;	
	//int					 dogAction_Attack;	
	//byte					 bDogRed;	
	//int					 m_DogChangeBoy;

	//int					 m_DogAction;
	//int					 m_DogAction_Attack;
	//byte					 m_bDogRed;

//	int					m_snake_Arr[15];	 //gh
//	int					m_snake_Move[5][600];	
//	int					m_snake_index;

	bool				m_game_pause;
	bool				m_time_pause;
	bool				m_chrMove_pause;	

	bool				m_bNote;

	//int					m_characterHp;	
	//int					m_characterMp;

	//const static int	m_charLove_length = 13;
	//int				m_charLove[m_charLove_length];	 //gh


	//byte					fadeOut;	
	//bool					fadeIndex;	
	byte					m_fadeOut;
	bool					m_fadeIndex;
	byte					m_setsleep_index;

	//int					m_dayWorking;	

	//bool					m_newDay;

	//int					m_UseFood;//612

	//int					m_oneObject;	

	//byte					pasture_level;	
	//byte					fish_level;	
	//char					m_pasture_level;
	//char					m_fish_level;

	//GuanHao. sec.
	// -------------------------------------------------------- NETWORK
	byte state;
	enum GameState
	{
		MENU = 0,
		CAUTION_POPUP,
		RANKING ,
		CHARGE,
		DOWNLOAD,
		INITDOWNLOAD,//612
		REDOWNLOAD,
		DOWNLOADSUCCESS,
		DOWNLOAD_NOTENOUGH_SIZE,
		REPLAY,
		ALREADY_REPLAY,
		NEEDLESS_REPLAY,
		CANCLE_REPLAY
	};


	int**				gauge_color;	//gh
	int					gauge_color_length;

//	int**				m_Item_Info  ;
//	int					m_Item_Info_length;
//	int*				m_Item_Info_sub_length;
//	int					m_shop_slot[5][15];	
//	static const int	m_shop_slot_length = 5;
//	static const int	m_shop_slot_sub_length = 15;


	//int				m_max_CowSheep[34];
//	static const int	m_max_CowSheep_length = 34;

	int					m_popCnt ; 	
	char*				m_Popup_str ;	


	//int m_item_insecticide;	
	//int m_item_scarecrow;	

//	int m_money;	
//	int m_loanmoney;	
//	int m_monthloanmoney;
//	int m_monthYield;//612
//	int m_bankmoney;


//	int bank_Realmoney;
//	int bank_Gamemoney;//Bank Charge

//	int m_loancount;
//	int m_bufloancount;//612
//	int m_replay;//612

//	int m_temp_monthloanmoney;//612
//	int m_temp_monthYield;//612

//	int m_gameresultRUN;//612

	//int m_gameresult;			
	//int m_gamedifficult;			

	int m_Year;	
	int m_Month;	
	int m_Day;	
	int m_WeekDay;	
	int m_FirstDay;
	int m_PlusDay;
	int m_NameIndex;//612

//	bool m_cheatOn;	
//	bool m_DebugOn;	
//	int m_SetDebuglevel;	


	char				emotion_m_type[15];	 //gh
	static const int	emotion_m_type_length = 15;//612add

	ASprite*			m_bSprite[60];
	static const int	m_bSprite_length = 60;
	cEntity**			m_entEntities;/* = GL_NEW cEntity[ENTITY.k_max];*/
	int					m_entEntities_length;

//	int hero_mosX;	
//	int hero_mosY;	
//	void *				Xplayer_share_buff  ;
	bool				bObjectCollision;	

	int					cntRain/* = 0*/;		
	int					cntAniRain/* = 0*/;


//	bool b_hp_warning; 
//	bool b_date_warning;


//	ASprite*				weather_sprite;	

	//int Weather_kind;		
	//int Weather_areaposx;				
	//int Weather_areaposy;				
	//int Weather_areasize;		
	//int Weather_speed;	
	//int Weather_total;		

	//bool Weather_Active;		
	//bool Weather_Active2;	

	///*int Weather_Posx[];	
	//int Weather_Posy[];	
	//int Weather_Direct[];	
	//int Weather_Speed[];	
	//int Weather_type[];*/	
	//int* Weather_Posx;	
	//int* Weather_Posy;	
	//int* Weather_Direct;	
	//int* Weather_Speed;	
	//int* Weather_type;	
	//int weather_position;


//	bool FireWork_start; 
//	int* FireWork_Posx;
//	int* FireWork_Posy;
//	int FireWork_Posx[FIRE_WORK_MAX];
//	int FireWork_Posy[FIRE_WORK_MAX];
//	int FireWork_Viewcount;
//	int FireWork_couter;


//	void Init_FireWork();

	int random(int a, int b);	

	int random();	

	int except_random( int _a, int _b, int _expt );

	int abs( int _number );	

	int smallValue(int _index);	
	int bigValue(int _index);	


	CImage* create_Image ( char* _str );	


	static const int s_math_F_1		= 1 << 8;

	static  const int s_math_F_05	= (s_math_F_1>>1);	


	//static int s_math_cosTable[];	
	//static int s_math_tanTable[];	
	//static int s_math_sqrtTable[];	
	int* s_math_cosTable;	
	int* s_math_tanTable;	
	int* s_math_sqrtTable;	

	void Math_init (char* packName, int _cos, int _tan, int _sqrt);	

	void Math_quit ();	

	int Math_fixedPointAdjust (int a);	

	int Math_fixedPointToInt (int a)	;	

	int Math_det (int x1, int y1, int x2, int y2);	

	int Math_dotProduct (int x1, int y1, int x2, int y2);	

	int Math_norm (int x, int y, int iter);	



	int Math_tan (int a);	

	int Math_atan (int st, int end, int tang);	

	int Math_atan (int dx, int dy);	

	int Math_log (int index, int iter);	


	int FastDistance(int x, int y);

	int DirTo(int x, int y);

	void Draw_Number( ASprite* _asprite, int _positionx , int _positony  , int _number , int _startmodule , int _direct , int _maxcount  ,bool _bOneNum = false , bool _bComma = false);	

	void Draw_GaugeW( int _x , int _y , int _height , int _currentgauge , int _max  ,int _gaugeMax , int _color);	

	int ConstraintToRange(int value, int min, int max);	


	int getEntityNumber(int index);	

	int getEntityGameID(int _gameId);	

	void pursuit_object(int aimX , int aimY);

	int pursuit_index_pos(int index, int _camera, int _screen );

	void init_wheather( int _type , int _speed ,int _quantity );	

	void SET_wheather( bool _active );	

	void SET_wheather( bool _active , int _speed , int _quantity );	

	void SET_wheather(int m_map_kind);	

	void free_wheather( );	

	void Process_wheather( );	

	void draw_wheather( );	

	void init_Popup( int _x, int _y, int _sizex, int _sizey, bool _bmove, bool _bline );	

	void Process_Popup( );	

	//void fillRoundRect( int iX_, int iY_, int iWidth_, int iHeight_ );

	//void Draw_Number( ASprite* _asprite, int _positionx , int _positony  , int _number , int _startmodule , int _direct , int _maxcount );

	//void Draw_GaugeW( int _x , int _y , int _height , int _currentgauge , int _max  ,int _gaugeMax , int _color);


	void Draw_Popup( int _plussize );	

	void Draw_RectinPopup( int _x , int _y , int _dx , int _dy );	

	//void add_Character_Hp( int _index);	

	//int check_Character_Hp_Date()	;	

//	bool get_DayWorking(int index);	


	cGame ( );	
//	cGame (GloftTheFarm* application);	

	void gameInit();	


	//M_Int64 game_lastTime/* = 0*/;	
	M_Int64 game_currentTime/* = 0*/;
	//M_Int64 game_FirstTime;//612

	long game_timeDiff/* = 0*/;//612	
	M_Int64 s_game_timeWhenFrameStart;

//	void run();	


	void OnSuspend();	

	void OnResume();	

//	void Destroy();	

	void paint(CGraphics* g);	


	//void keyPressed(int keyCode);
	//void keyReleased(int keyCode);
	//void keyReSet( );	
	//void keyRepeated(int keyCode);
	//int getKeyMask( int keyCode );
	//void processKeyPress( int key );


	bool IsKeyHold(int gameKey);
	bool IsKeyOnlyHold(int gameKey);
	bool IsKeyPressed(int gameKey);
	bool IsKeyReleased(int gameKey);
	bool IsKeyDoublePressed(int gameKey);
	bool IsAnyKeyHold();
	bool IsAnyKeyPressed();
	void ClearKey();

	int s_keyHold;
	int s_keyHoldFrame;

	//long aaaaaaaaaaa;	

	void gamePaint(CGraphics* _g);	

	void pushState(int stateID, bool pushLoad );	

	void sendMessage( int message );	

	//byte* loadResource(int res, bool close_file);

	//byte* loadResourceStream(int res, bool close_file);//612

	void closeFileStream();	


#ifdef DBG_FPS

	void _drawDebugStrings(	
		CGraphics* g, char* msg, int separator,	
		int x, int y, bool bScreenCoords,	
		int textColor, int bgcolor )	;

	void drawFpsSpeed(Graphics g);//612
#endif

	void drawFadeOut(CGraphics* g);//612
	
	void Update();

	CEngine::ERROR_TYPE  Initialize();

	
#ifdef hasShine
	CImage** _shineImgs;

	void InitShine();
	void Bresenham_Line_4444(int x0, int y0, int x1, int y1, int alpha0, int alpha1, int width, unsigned short* dest, int scan_line);
	void Bresenham_Line_8888(int x0, int y0, int x1, int y1, int alpha0, int alpha1, int width, int width2, unsigned int* dest, int scan_line, int color);
#endif
#ifdef USE_DIRECT_DRAW
	void ModifyPalette(ASprite* sprite, int palNb, int color);
#endif

};


#endif// _CGAME_
