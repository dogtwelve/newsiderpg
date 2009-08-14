#include "VBaseState.h"
#include "Monster.h"
#include "Character.h"
#include "Field.h"
#include "WorldmapUI.h"
#include "FieldUi.h"
#include "PopupUI.h"
#include "FieldObject.h"
#include "SUtil.h"
#include "Cinematic.h"	
#include "Message.h"
#include "SaveLoad.h"
#include "EventManager.h"
#include "Loading.h"
#include "Quest.h"
#include "Minimap.h"


#ifndef __GFIELDBATTLE_
#define __GFIELDBATTLE_


//�ý��� ��� ��Ʈ�� Ask For SangHo
#define	LOOK_Debug //SangHo

#ifdef LOOK_Debug
	#define	LOOK_FRM_PER_SEC //SangHo
	#define	LOOK_USE_MEMORY	//SangHo
	//#define LOOK_EVENT_RECT
	#define LOOK_DONT_GO_RECT
#endif


#define WORLD_MAP_STAGE_NUM		(999)			//���ΰ��� �ȱ׸���

#define PAINT_HERO_NOT		(1 << 1)			//���ΰ��� �ȱ׸���
#define PAINT_MON_NOT		(1 << 2)			//������ �ȱ׸���
#define PAINT_FIELD_FRONT_NOT		(1 << 3)	//�ֻ��� ����� �ȱ׸���
#define PROCESS_HERO_NOT		(1 << 4)		//���ΰ� ���μ����� �ȵ�����
#define PROCESS_MON_NOT		(1 << 5)			//���� ���μ����� �ȵ�����
#define PROCESS_FIELD_FRONT_NOT		(1 << 6)	//�ֻ��� ��� ���μ����� �ȵ�����


#define DEBUF_WEAK			(1 << 1)			//��ȭ
#define DEBUF_ICE			(1 << 2)			//���̽�
#define DEBUF_FREEZE		(1 << 3)			//����
#define DEBUF_STUN			(1 << 4)			//����
#define DEBUF_STONE			(1 << 5)			//��ȭ
#define DEBUF_POISON		(1 << 6)			//��
#define DEBUF_CONFUSE		(1 << 7)			//ȥ��
#define DEBUF_VAMPIRE		(1 << 8)			//����A
#define DEBUF_DE_VAMPIRE	(1 << 9)			//����B
#define DEBUF_MANABURN		(1 << 10)			//��������
#define DEBUF_SILENCE		(1 << 11)			//ħ��

#define LIST__START(ListName)			MoveHead(ListName);MoveNext(ListName);while(NotEndList(ListName)){
#define LIST____END(ListName)			MoveNext(ListName);}



//SangHo - �������� Rect ����(1��°�� �ǰ�����,2��°�̻��� Ÿ������,0���� ��������)
#define	RECT_NUM(AS_Inst, Frame_Index)			AS_Inst->m_sprite->_frames_rects_start[Frame_Index+1] - AS_Inst->m_sprite->_frames_rects_start[Frame_Index]
#define	XY(AS_Inst, Frame_Index)				AS_Inst->m_sprite->_frames_rects[Frame_Index]//������ ����
#define	WH(AS_Inst, Frame_Index)				(byte)AS_Inst->m_sprite->_frames_rects[Frame_Index]//����� ����
#define	FLAG_X_SUM(AS_Inst)						0x1 & (AS_Inst->m_flags ^ (AS_Inst->m_sprite->_aframes[((AS_Inst->m_sprite->_anims_af_start[AS_Inst->m_nCrtModule] + AS_Inst->m_nCrtFrame) * 5)  + 4] & 0x0F) )


//#define	MON_MAX_COUNT		(19)

//#define	CRITICAL_HERO		bool cri = false;if(RND(0,100)<(hero->s_Status[s_HeroTag.SEX].CRITICAL)) {tmp*=2;cri=true;}
//#define	CRITICAL_MON		bool cri = false;if(RND(0,100)<(mon->m_Stet.m_Cri)) {tmp*=2;cri=true;}
#define	AVOID_HERO			(RND(0,100)<(hero->s_Status[hero->s_HeroTag.SEX].AVOID))

const short Sin_arr[91] = {0,	17,	35,	52,	70,	87,	105,	122,	139,	156,	174,	191,	208,	225,	242,	259,	276,	292,	309,	326,	342,	358,	375,	391,	407,	423,	438,	454,	469,	485,	500,	515,	530,	545,	559,	574,	588,	602,	616,	629,	643,	656,	669,	682,	695,	707,	719,	731,	743,	755,	766,	777,	788,	799,	809,	819,	829,	839,	848,	857,	866,	875,	883,	891,	899,	906,	914,	921,	927,	934,	940,	946,	951,	956,	961,	966,	970,	974,	978,	982,	985,	988,	990,	993,	995,	996,	998,	999,	999,	1000,	1000};
const short Tan_arr[46] = {0,	17,	35,	52,	70,	87,	105,	123,	141,	158,	176,	194,	213,	231,	249,	268,	287,	306,	325,	344,	364,	384,	404,	424,	445,	466,	488,	510,	532,	554,	577,	601,	625,	649,	675,	700,	727,	754,	781,	810,	839,	869,	900,	933,	966,	1000};//,	1036,	1072,	1111,	1150,	1192,	1235,	1280,	1327,	1376,	1428,	1483,	1540,	1600,	1664,	1732,	1804,	1881,	1963,	2050,	2145,	2246,	2356,	2475,	2605,	2747,	2904,	3078,	3271,	3487,	3732,	4011,	4331,	4705,	5145,	5671,	6314,	7115,	8144,	9514,	11430,	14301,	19081,	-1,	-1,	-1};
#define SIN(a)						(((a)<180 ? Sin_arr[((a)<90 ? (a) : 180-(a))] : -Sin_arr[((a)<270? (a)-180 : 360-(a))] ))
#define COS(a)						(SIN((a+90)%360))
#define TAN(a)						(Tan_arr[(a)])

//	�������� �ε忡 �ʿ��� ����Ÿ�� �־��ش�.
typedef struct _STAGE_MON_DATA
{
	byte nMonIdx;
	byte nNameIdx;
	byte nCount;
	byte nPtn;
}STAGE_MON_DATA;



#define SOUND_COOLTIME 30//���� BGM ������

//overlab
#define OVERLAB_BLAND_MAX 32
#define OVERLAB_BLAND_MOVE_BIT 5
#define OVERLAB_STOP 10000
class CSound;

class GFieldBattle : public VBaseState
{
public:

	GFieldBattle();
	~GFieldBattle();

	void LoadFirstData(int timer, int nDummy1, int nDummy2);

	void Initialize(int nDummy1, int nDummy2);
	void Release();
	void Process();
	void Paint();
	void KeyEvent(int m_keyCode, int m_keyRepeat);
	void drawOverlab(); 
	void setGamma(int gammaCase); 

	///////////////////////////////////////////////////////////


	void LoadStage(int nNextStage, int step); 
	void ReleaseStage(); 

	bool	b_ChangeStage;
//	int		m_nNextStage;
	int		m_nStageLoadStep;

	void	Paint_ChangeScrollEvent(int type);
//	void	Resv_ChangeStage(int nNextStage);
//	void	ChangeStage();

	//	���̵��� �ƿ� ���� ��
	int		m_nFadeInTime;
	int		m_nFadeOutTime;
	bool	m_nIsDarkScreen;

	bool	CheckEvent(int param);
	void	SetFadeOut(int time=0);
	void	SetFadeIn(int time=0);

	void	UpdatePARSER_EVENT();

	///////////////////////////////////////////////////////////



	//	����
	struct S_CHARINFO*	m_CharInfo;			//	ĳ���� ������ ������ �ִ� ����ü

	STAGE_MON_DATA* pMonData;
	int nMonTypeCnt;		//	���� ������ ����
	int nMonGradeCnt[4];	//	����/����ũ/����� ������ ����		�Ϲ�(0)�� ����д�.

	int	m_nMonSeedCnt;		//	�� ������ ����
	int* m_nSeedData;
	int* m_nSeedDataGrade;
	int	m_nMonLevel;
	int m_nMonLevelRnd;

	class ASprite* m_MonAs[SPRITE_MON_MAX];


//	int*	m_nSeedData;
//	int*	m_nSeedDataGrade;
//	int*	m_nRegenType;
//	int*	m_nRegenX;
//	int*	m_nRegenY;
//	int*	m_nIsRegen;

	bool	b_PopupUi;//���� �˾� UI�� Ȱ��ȭ �Ǹ� True �� �ȴ�
	bool	b_WorldMap;

	int		m_BGM_Cooltime;

//	int	m_nMakeLastMonsterIdx[2];
//	int	m_nMakeLastElementIdx[2];

		//	temp
//	bool ischeck;

	List2< class Monster* >			*pMonList;
//	List2< class Monster* >			*pObjectList;
	List2< struct S_MONSKILL* >		*pMonSkillList;
	List2< struct S_MESSAGE* >		*pMonMsgList;

	// ĳ����
	class Character* hero;//���ΰ�

	//	�ʵ� UI
	class FieldUi* pFieldUi;

	//	�˾� UI
	class PopupUi* pPopupUi;

	//	����� UI
	class WorldmapUI* pWorldMapUi;

	//	���
	Field*		pField;
	class ASprite* pFieldAs;	
	class ASpriteInstance* pFieldAsins;
	int overlabCnt; 
	short* copyBackBuf; 
	
	//	���׸�
	class cCinematic* pCinema;
	

	//���� ��������Ʈ ��Ʈ
	struct ASpriteSet{//���� ��������Ʈ ����
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet s_ASpriteSet;


	void Throw_Check();//��� ������ �����ɶ� ���� ��� ���� üũ 
	//	S �浹üũ - Ask by SangHo
	Position3D power;
	struct Contact{
		short x;		//x��ݷ� - �´´���� +�϶��� �з������� -�϶��� ��ܿ´�
		short y;		//y��ݷ�
		short z;		//z��ݷ� - �⺻������ -��ġ�� ������ �ϴ÷� �������
		short D_index;	//������ �ε���
		short crash_x;		//X��� ����Ʈ ���� 
		short crash_z;		//Z��� ����Ʈ ����
	};Contact s_Contact;
	bool Contact_Check(ASpriteInstance* p_Attacker,ASpriteInstance* p_Defender,int attGap,int defGap);	//attGap �� �����(0�ʰ�)�� ������ �װ������� 0�̸� ��������Ʈ�� ��ϵ� ��������
	bool Contact_Body_Check(ASpriteInstance* p_Attacker,ASpriteInstance* p_Defender,int attGap,int defGap, boolean HERO);//(HERO = FALSE)  For namyoung
	bool Contact_Map_Check(ASpriteInstance* p_Attacker,int attGap,int X,int Y,int W,int H, boolean HERO);//For namyoung
	int Area_Check(ASpriteInstance* Instance,int x_MAX);

	void PaintMiniMap();

#define BAKUP_HERO_Y	Exception[1]
#define CRI_SHINING		Exception[0]

	int Exception_Num; 
	int Exception[5];//�ʿ��� ��ŭ �ø���


	//	E �浹üũ
	
	Monster* AddMonster(int addType, int monidx, int nameidx, int ptnIdx, int gradeDataidx, int x, int y, int startx, int starty, int regenIdx, int z = 0);		//	���, �Ӽ�, ����
	void LoadMonsterSprite(int monidx);
	void AddFirstMonSetting();
	void AddRegenMonSetting(int defPosx);
//	void AddRegenMonSetting();
//	void LoadMonsterSprite(int nIdx);
	void MakeMonsterSeed(int nStageNum);
	void MakeMonsterSeed();


	void Analysis_Mon_Message();




//////////////SangHo

#ifdef LOOK_FRM_PER_SEC
	long TimeLast;
#endif

	void Paint_Exception_Check();

#define CAMERA_DELAY 1	//�������·� ��ü�ϴ½ð�
#define CAMERA_MAX_SPACE 50	//look Ȯ���Ÿ�
#define CAMERA_MAX_MOVE 70	//move Ȯ���Ÿ�
//#define CAMERA_DASH_SCROLL 60	//��ũ�� �ִ� �Ÿ�
	struct Camera{
		short cX, cY;//������ǥ
		short stop_Frame;//������ ���·� ��ü�ϴ� �ð�
		short CameraAdd;
	};Camera s_Camera;
	void SetCameraMove();//ī�޶� ��ǥ��ǥ ����

	struct Homing{
		short X1 , Y1;//������ǥ
		short Cita1;//�������� 
		short X2 , Y2;//��ǥ��ǥ
		short Cita2;//���������� ����
		short R;//������
		short TurnCita;//�ִ�� ������ �ִ� ����
		class Monster* pMons;//Ÿ��
	};Homing s_Homing[3];
	int GetAngle(int X,int Y);
	void GetHomingXY(Homing* p_Homing);
//private:
//	CImage*					img_splash;

	void DamageSand_Hero(Character* hero, Monster* mon);
	void DamageSand_Mon(Monster* mon , Character* hero);

	//void SetEvent(int nEvtCode, int dummy1);
	void EventProcess();
	bool KeyEventProcess();


	void Sound_Load();
	void playSound(int soundID, bool loopflag)	;	
	void stopSound() ;	

	// ���� �̺�Ʈ �޼���
	void Analysis_Event();

	//	�̺�Ʈ ���� �÷���
	bool	isHoldingProcess;
	bool	isHoldingPaint;
	bool	isHoldingKey;

	int		m_nLodingtime;

	//	���ѷα� �̺�Ʈ
	bool	m_bIsPlayPrologue;
	int		m_nPrologueTimer;
	void	LoadPrologue(int idx, int textIdx);
	bool	PaintPrologue();
	bool	UpdatePrologue();

	//	Ÿ�̸� �̺�Ʈ
	int		m_nSaveEvtTimer;
	void	ProcessTimerEvent();
	void	SetTimerEvent(int nTime);

#ifdef LOOK_Debug
	void PaintDebug();
#endif

	void ProcessWorldMap();
	void PaintWorldMap();
	void KeyEvtWorldMap(int m_keyCode, int m_keyRepeat);

	//	minimap
	class cMinimap* pMinimap;


};

#endif	//__GFIELDBATTLE_

