#ifndef _MONSTER_
#define _MONSTER_

//	AI와 상호참조를 한다.
#include "ASpriteInstance.h"
#include "MonsterAI.h"
#include "SUtil.h"
#include "Position3D.h"
#include "Physics.h"
#include "SPRITE_DESC.h"
#include "List.h"
#include "Data.h"


//	monster action
#define MON_AC_NULL								9999	//	0이면 안된다.
#define MON_AC_BASE							0
#define MON_AC_STAND						1
#define MON_AC_MOVE							2
#define MON_AC_AWAK							3
#define MON_AC_ING_DOWN						4
#define MON_AC_ING_AIRDOWN					5
#define MON_AC_DOWNED						6
#define MON_AC_RCV_GROUND_ATTACK			7
#define MON_AC_RCV_DOWN_ATTACK				8
#define MON_AC_RCV_AIR_ATTACK				9
#define MON_AC_DIE							10
#define MON_AC_DIE_AFTER					11
#define MON_AC_RCV_HOLDING					12
#define MON_AC_RCV_HOLDING_SKY				13
#define MON_AC_RCV_HOLDING_DOWN				14
#define MON_AC_READY						15
#define MON_AC_RUN							16
#define MON_AC_BEHOLD						17
#define MON_AC_ING_SIT						18
#define MON_AC_SIT							19
#define MON_AC_SIT_STAND					20
#define MON_AC_HIDE							21
#define MON_AC_FALL							22
#define MON_AC_FAINTING						23
#define MON_AC_REST							24

#define MON_AC_FACE_FRONTSIDE				25
#define MON_AC_STAND_FRONTSIDE				26
#define MON_AC_MOVE_FRONTSIDE				27
#define MON_AC_REGEN_L_ARM_FRONTSIDE		28
#define MON_AC_REGEN_R_ARM_FRONTSIDE		29
#define MON_AC_HIDE_FRONTSIDE				30
#define MON_AC_FACE_LOST_LEFTHAND			31
#define MON_AC_FACE_LOST_RIGHTHAND			32
#define MON_AC_FACE_REST					33
#define MON_AC_DIE_AFTER_DONT_REMOVE		34
#define MON_AC_MAX							35

#define MON_EXT_BASE						100
#define MON_ATK_MELEE1						(MON_EXT_BASE+1)
#define MON_ATK_MELEE2						(MON_EXT_BASE+2)
#define MON_ATK_MELEE3						(MON_EXT_BASE+3)
#define MON_ATK_MELEE4						(MON_EXT_BASE+4)
#define MON_ATK_MELEE5						(MON_EXT_BASE+5)
#define MON_ATK_RANGE1						(MON_EXT_BASE+6)
#define MON_ATK_RANGE2						(MON_EXT_BASE+7)
#define MON_ATK_RANGE3						(MON_EXT_BASE+8)
#define MON_ATK_RANGE4						(MON_EXT_BASE+9)
#define MON_ATK_RANGE5						(MON_EXT_BASE+10)
#define MON_ATK_RANGE6						(MON_EXT_BASE+11)
#define MON_ATK_RANGE7						(MON_EXT_BASE+12)
#define MON_ATK_RANGE8						(MON_EXT_BASE+13)
#define MON_ATK_RANGE9						(MON_EXT_BASE+14)
#define MON_ATK_RANGE10						(MON_EXT_BASE+15)
#define MON_ATK_RANGE11						(MON_EXT_BASE+16)
#define MON_ATK_RANGE12						(MON_EXT_BASE+17)
#define MON_ATK_FIREBALL					(MON_EXT_BASE+18)
#define MON_ATK_THROWSTONE					(MON_EXT_BASE+19)
#define MON_ATK_LASERBEAM					(MON_EXT_BASE+20)
#define MON_ATK_WIND						(MON_EXT_BASE+21)
#define MON_ATK_FIRE_WAVE					(MON_EXT_BASE+22)
#define MON_ATK_ICE_WAVE					(MON_EXT_BASE+23)
#define MON_ATK_SUMMON_BUG					(MON_EXT_BASE+24)
#define MON_ATK_DEAD_ATTACK					(MON_EXT_BASE+25)
#define MON_ATK_BURROW						(MON_EXT_BASE+26)
#define MON_ATK_BURROWED					(MON_EXT_BASE+27)
#define MON_ATK_UNBURROW					(MON_EXT_BASE+28)
#define MON_ATK_GUARD						(MON_EXT_BASE+29)
#define MON_ATK_RANGE1_READY				(MON_EXT_BASE+30)
#define MON_ATK_RANGE2_READY				(MON_EXT_BASE+31)
#define MON_ATK_RANGE3_READY				(MON_EXT_BASE+32)
#define MON_ATK_RANGE4_READY				(MON_EXT_BASE+33)
#define MON_ATK_BOSS5_METEO					(MON_EXT_BASE+34)

#define MON_ATK_BOSS5_FACE_LEFT_HOOK		(MON_EXT_BASE+35)
#define MON_ATK_BOSS5_FACE_RIGHT_HOOK		(MON_EXT_BASE+36)
#define MON_ATK_BOSS5_FACE_SHOULDER			(MON_EXT_BASE+37)
#define MON_ATK_BOSS5_FACE_METEO			(MON_EXT_BASE+38)
#define MON_ATK_BOSS5_FACE_SHOULER_L_BEAM	(MON_EXT_BASE+39)
#define MON_ATK_BOSS5_FACE_SHOULER_R_BEAM	(MON_EXT_BASE+40)
#define MON_ATK_BOSS5_FACE_SHOULER_LR_BEAM	(MON_EXT_BASE+41)
#define MON_ATK_BOSS5_FACE_SHOULER_RL_BEAM	(MON_EXT_BASE+42)
#define MON_ATK_BOSS5_FACE_BEAM				(MON_EXT_BASE+43)
#define MON_ATK_BOSS5_FACE_WALL				(MON_EXT_BASE+44)
#define MON_ATK_BOSS5_FACE_SUMMON			(MON_EXT_BASE+45)

#define MON_ATK_BOSS1_HEAD_MELEE2			(MON_EXT_BASE+46)



#define MON_ATK_MAX							(MON_EXT_BASE+47)


#define MON_NOT_ATTACK						9999

#define BASE_ACTION_SIZE					ANIM_MON01_CATCH_3	//(18)


//	physics option
#define UP_GRV			4
#define DOWN_GRV		3
#define REG_GROUND		2

#define LIGHT_WEIGHT	20
#define COMMON_WEIGHT	21
#define HEAVY_WEIGHT	22


//	skill type
#define SKILL_REMOVE	0
#define SKILL_REMAIN	1



struct S_MONSKILL
{
	void* who;
	int damagetime;								//	데미지가 지속되는 시간
	int skillnum;								//	스킬의 번호
	int type;									//	맞았을시 사라지는지
	int lifeTime;								//	에니메이션의 유지시간
	int Damage;									//	데미지량
	int Delay;									//	에니메이션이 들어가기전의 딜레이시간
	int Movex;
	int Movey;
	int Movez;
	class ASpriteInstance*	pMonSkillAsIns;		//	인스턴스
};	


struct S_MONATK
{
	int Name;
	int MinScope;
	int MaxScope;
	int Debuff;
	int CoolTime;
	int MaxCoolTime;
};


struct S_CHARINFO
{
	Position3D	m_nPos;
	int			m_Direction;
};


//	ABOUT MONSTER GRADE ///////////////////////////////////////////////////
//	monster grade
#define GRADE_NORMAL		0
#define GRADE_RARE			1
#define GRADE_UNIQUE		2
#define GRADE_SPECIAL		3

#define GRADE_ADD_ATK		0
#define GRADE_ADD_DEF		1
#define GRADE_ADD_HP		2
#define GRADE_ADD_EXP		3
#define GRADE_MAX			4

#define	MON_MELEE_TYPE		(1)
#define	MON_RANGE_TYPE		(2)

static const int MonBaseGradeStet[][GRADE_MAX] = 
{
	//공격률증가치, 수비율증가치,	체력증가율, 추가경험치
	{ 100,			0,				100,		100},													//	GRADE_NORMAL
	{ 125,			3,				300,		300},													//	GRADE_RARE
	{ 150,			6,				400,		400},													//	GRADE_UNIQUE
	{ 175,			9,				500,		500},													//	GRADE_SPECIAL
};



//	ABOUT MONSTER STET_DATA //////////////////////////////////////////////////
#define	MON_IDX_RAPTER					0 
#define	MON_IDX_GOLEM					1 
#define	MON_IDX_SLIME					2 
#define	MON_IDX_WATER_ELE				3 
#define	MON_IDX_COBOLT					4 
#define	MON_IDX_THUNDERBIRD				5 
#define	MON_IDX_TANK					6
#define	MON_IDX_PUMPKIN					7
#define	MON_IDX_SKELETON				8
#define	MON_IDX_GUNNER					9
#define	MON_IDX_ELF_FIRE				10
#define	MON_IDX_ELF_ICE					11
#define	MON_IDX_ELF_SILENCE				12
#define	MON_IDX_TRICERATOPS				13
#define	MON_IDX_REDDRAGON				14
#define	MON_IDX_DEVIL					15
#define	MON_IDX_HUMAN_SWORD				16
#define	MON_IDX_HUMAN_MAGE				17
#define	MON_IDX_FLYTRAP					18
#define	MON_IDX_CRAB					19


#define	MON_IDX_COUNT_NORMAL_MON		20
//------------------------------------------------------

#define	MON_IDX_BARREL					40
#define	MON_IDX_STONE_BIG				41
#define	MON_IDX_BOX						42
#define	MON_IDX_KNIGHT					43
#define	MON_IDX_TEMPLE_CROCK_SMALL		44
#define	MON_IDX_TEMPLE_CROCK_BIG		45
#define	MON_IDX_TEMPLE_STONEBOX_SMALL	46
#define	MON_IDX_TEMPLE_STONEBOX_BIG		47
#define	MON_IDX_BUG						48
#define	MON_IDX_DRILL					49
#define	MON_IDX_BOSS5_DEVIL				50


#define	MON_IDX_COUNT_OBJECT			11
//------------------------------------------------------

#define	MON_IDX_HOROS					60

#define	MON_IDX_BIGDOG1					61
#define	MON_IDX_BIGDOG2					62
#define	MON_IDX_BIGDOG3					63
#define	MON_IDX_BIGDOG4					64
#define	MON_IDX_BIGDOG5					65

#define	MON_IDX_BIGDOG6					66
#define	MON_IDX_BIGDOG7					67
#define	MON_IDX_BIGDOG8					68
#define	MON_IDX_BIGDOG9					69
#define	MON_IDX_BIGDOG10				70

#define	MON_IDX_DEVIJOHNS				71

#define	MON_IDX_BIG_DRAGON1				72
#define	MON_IDX_BIG_DRAGON2				73
#define	MON_IDX_BIG_DRAGON3				74


#define	MON_IDX_COUNT_BOSS				15
//------------------------------------------------------


#define	MON_ELEMENTAL_STONE				0	//	바위
#define	MON_ELEMENTAL_SNIPS				1	//	가위
#define	MON_ELEMENTAL_PAPER				2	//	보
#define	MON_ELEMENTAL_NON				3



/*
#define		UNQ_BOSS_2_IDX				57
#define		UNQ_BOSS_2_SUMMON_BUG		58

#define		UNQ_BOSS_3_1_IDX	59
#define		UNQ_BOSS_3_2_IDX	60
#define		UNQ_BOSS_3_BABY		51

#define		UNQ_BOSS_5_1_IDX		61
#define		UNQ_BOSS_5_2_IDX		62
#define		UNQ_BOSS_5_3_IDX		63
#define		UNQ_BOSS_5_4_IDX		64
#define		UNQ_BOSS_5_5_IDX		65

#define		UNQ_BOSS_6_1_IDX		66

#define		MON_BARREL_IDX			67
#define		MON_STONE_BIG_IDX		68
*/



struct S_MON_STET
{
	int			m_Hp;
	int			m_MaxHp;
	int			m_Defance;		// 방어율
	int			m_Atk;			// 공격력
	int			m_Cri;
	int			m_Height;
	int			m_Width;
};


struct S_MESSAGE
{
	int m_nDelay;
	int	m_MsgType;
	int param[4];
};

//	monster message
#define		MSG_NULL				0
#define		MSG_CHANGE_STATE		1
#define		MSG_SUMMONE_BABY		2
#define		MSG_SUMMONE_BUGS		3
#define		MSG_DE_SUMMONE_BUGS		4
#define		MSG_BOSS_CHANGESTATE	5

#define		MSG_BOSS5_SUMMON_WALL	6
#define		MSG_BOSS5_SUMMON_DEVIL	7

#define		NOT_REGEN				9999


#define STET_DEF_RATE			0
#define STET_HP_RATE			1
#define STET_CRI_RATE			2
#define STET_AGI_RATE			3
#define STET_ADD_EXP			4
#define STET_ATK_1				5
#define STET_ATK_2				6
#define STET_ATK_3				7
#define STET_ATK_4				8
#define STET_MAX				9


//	추가 몬스터에 대한 패턴은 이곳에 정의해둔다.
#define PTN_COUNT				(2)
#define START_ADD_MON_PTN		(MON_IDX_BUG*PTN_COUNT)


//	몬스터 당 2개씩 18(SPRITE_MON_BUG까지) = 36개+ 1개(사람은 2명)+ 2개(페어리 3명)
static const int MonPtn[][STET_MAX] = 
{
//DDF, HP, CRI, AGI, EXP, AT1, AT2, AT3, AT4
  //랩터-중형
  {15, 80, 5,	0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//골램-대형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//젤리페어리-소형
  {0, 80, 3, 0, 100,  100, 110, 100, 100},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//워터엘리-중형
  {0, 100, 0, 0, 100, 200, 160, 100, 100},
	{0, 120, 8, 0, 100, 220, 180, 140, 140},
	//코볼트-중형
  {5, 120, 6, 0, 100, 100, 170, 100, 100},
	{10, 200, 12, 0, 100, 100, 230, 100, 100},
	//거대새-대형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//탱크-대형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//호박로봇-소형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//해골법사-대형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//총딱다구리-소형
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//페어리불
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//페어리물
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//페어리침묵
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//트리케라
  {0, 100, 0, 0, 100, 100, 200, 250, 100},
	{10, 80, 8, 0, 100, 200, 250, 100, 100},
	//새끼용
   {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//데몬쌍검
   {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//인간칼
   {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//인간법사
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//괴물식물
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
	{15, 80, 5, 0, 100, 140, 140, 140, 140},
	//메카크랩
  {15, 80, 5, 0, 100, 140, 140, 140, 140},
  {15, 80, 5, 0, 100, 140, 140, 140, 140},


//-------------------------------------------------------------------
  //오브젝트
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},
  {0, 30, 0, 0, 0, 0, 0, 0, 0},

  //딱정벌레
  {15, 30, 5, 0, 100, 140, 140, 140, 140},

  //BOSS5 DRILL
  {15, 30, 5, 0, 100, 140, 140, 140, 140},

  //BOSS5_DEVIL
  {15, 30, 5, 0, 100, 140, 140, 140, 140},


//-------------------------------------------------------------------
	//보스
	{15, 400, 5, 0, 100, 140, 140, 140, 140},

	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},

	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},
	{15, 400, 5, 0, 100, 140, 140, 140, 140},

	{15, 400, 5, 0, 100, 140, 140, 140, 140},		//	MON_IDX_DEVIJOHNS

	{15, 400, 5, 0, 100, 140, 140, 140, 140},		//	MON_IDX_BIG_DRAGON1
	{15, 400, 5, 0, 100, 140, 140, 140, 140},		//	MON_IDX_BIG_DRAGON2
	{15, 400, 5, 0, 100, 140, 140, 140, 140},		//	MON_IDX_BIG_DRAGON3
};


///////////////////////////////////////////////////


//몬스터 특징 : m_nFeature
#define FE_DONT_TOUCH		(0x00000001)
#define FE_DONT_DRAW_MAP	(0x00000010)
#define FE_ONLY_HAVE_AI		(0x00000100)
#define FE_DONT_GIVE_EXP	(0x00001000)
#define FE_DONT_HAVE_DOWN	(0x00010000)
#define FE_HAVE_ONLY_DAMAGE	(0x00100000)
#define FE_DONT_HAVE_ITEM	(0x01000000)
#define FE_DONT_AREA_CHECK	(0x10000000)

#define FE_NORMAL_MONSTER	(0)
#define FE_BOSS				(FE_HAVE_ONLY_DAMAGE | FE_DONT_HAVE_DOWN )
#define FE_ONLY_OBJECT		(FE_DONT_DRAW_MAP|FE_ONLY_HAVE_AI|FE_DONT_GIVE_EXP|FE_DONT_HAVE_DOWN)
#define FE_ONLY_BACKOBJECT	(FE_DONT_DRAW_MAP|FE_ONLY_HAVE_AI|FE_DONT_GIVE_EXP|FE_DONT_TOUCH|FE_DONT_HAVE_DOWN|FE_DONT_AREA_CHECK)


static const int FACE_BOSS5_POS[6] = {0, -100, -60, -22,	3, -1};

class Monster	
{
public:
	//Monster(ASpriteInstance* m_AS, bool b_direction_R);
	Monster();
	virtual ~Monster();

public:
	struct ASpriteSet{//공용 스프라이트 묶음
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	struct Debuff{
		short All;	//SangHo - 주인공의 잡기가 가능하다면
		short stack[3][2];	//SangHo - 디버프저장소
		short color;//상태이상 컬러증가치
	};Debuff s_Debuff;

	//	고유 ID
	static int	UniqueIdx;

	S_CHARINFO*	m_CharInfo;				//	캐릭터 정보
	int			m_nTimer;
	int			m_ActState;				//	액션 상태
	int			m_NextActState;			
	int			m_nDirection;
//	Position3D	m_nPos;
	Physics*	m_Physics;				
	Position3D	m_nPhysicsPos;			// 물리적으로 갱신되는 백터
	Position3D	m_nMoveVec;				// 이동시 목표점
	int			m_nAniIndex;			// 현재 사용중인 에니메이션
	Position3D	m_nResvPower;			// 상태 변경시 적용되어질 힘
	Position3D	m_nResvResist;			// 상태 변경시 적용되어질 저항
	int			m_nResistZ;				// Z저항상태를 체크하기 위한 변수
	int			m_nRegenIdx;			//	몬스터가 나온 곳
	int			m_nIsUpperAtk;			//	어퍼 어택이냐 아니냐.
	int			m_nShadowIdx;			//	몬스터에 따라 쓰는 그림자 크기가 다른다.
	int			m_nBodySize;			//	monster body size

	//	about STET -----------------------------------
	int			m_nUniqueIdx;			//	몬스터 고유번호
	int			m_nMonIdx;				//	몬스터 번호
	int			m_nSpriteIdx;			//	스프라이트의 번호

	int			m_nLevel;				//	몬스터 레벨
	int			m_PtnIdx;				//	고유 데이타
	int			m_nElementIdx;			//	속성 데이타
	int			m_nMonName;				//	몬스터 이름
	int			m_GradeData;			//	일반 / 레어 / 유니크 / 스페셜
//	bool		m_bIsCheckBody;			//	충돌체크시 몸통체크를 안하는 몬스터
	S_MON_STET	m_Stet;

	//	고유 스텟
	//	int			m_AIState;						//	AI STATE
	int			m_nAttribute;					//	속성들의 모임
	int			m_nHealCnt;						//	힐을 할 수 있는 카운트
	int			m_nDevideCnt;					//	분열할수 있는 카운트
	int			m_nDevideCoolTime;				//	분열할수 있는 쿨타임
	int			m_nCurDamageCnt;				//	순간 누적된 순간 대미지
	int			m_nTotalDamageCnt;				//	총 맞은 대미지
	int			m_nFeature;						//	몬스터 고유의 특징


	//	인공지능 부분
	int			m_nAiTimer;
	int			m_nAiNextState;
	int			m_nAiState;

	//	인공지능 판단 데이타
	int			m_nSelectAtkTable;				//	 현재 상태가 1:일반상태인지 / 2:맞는상태인지.
	int			m_nMelee_or_Range;				//	 현재 상태가 1:melee / 2:range
	bool		m_bIsBattle;
	bool		m_bIsFirstAttack;
	int			m_nDstLookSeed;					//	방황시 가야할 목적점의 이동경로 시드
	int			m_nDstTime;						//	어떤 목적이든 대기시간의 필요할때 쓰임
	Position3D	m_SaveAtkPos;					//	몹의 첫 공격 지점 (탈출 시간을 재기 위해 쓰임)
	int			m_nUseAtkNum;					//	이번턴에 선택된 공격의 번호
	bool		m_bIsSuccessAttack;				//	이번턴의 몬스터의 공격이 성공했는지 판단.
	bool		m_bIsPanic;						//	잡힌상태든 몬스터의 AI를 실행할수 없는순간

	static int	m_nExtraDamage;					//	몸땡이 보스들을 같이 피를 감소할때 쓰임

	//	인공지능 각종 판단 기본 범위
	int			m_nRange_InBattle;				//	전투 인식 범위
	int			m_nRange_OutBattle;				//	전투 해제 범위
	int			m_nRange_OutAction;				//	액션 해제 범위(전투도 풀림)
	int			m_nRange_Heal;					//	아군의 힐이 필요하다는것을 인식하는 범위
	int			m_nRange_HealAction;			//	힐 액션이 가능한 범위
	Position3D	m_StartPos;						//	몬스터가 처음 이동해야할 범위
	int			m_nHitRate;						//	마지막으로 맞은후 몇프레임이 지났는지
	int			m_nAccumulatedHit;				//	순간 데미지가 얼마나 들어갔는지

	//	인공지능 스킬 관련 체크
	int			m_nSkillCount;					//	가지고 있는 스킬의 갯수
	int			m_nResvNextAtk;					//	다음 공격 셋팅
	int			m_nAtkMaxCount;					//	총 공격의 갯수
	S_MONATK*	m_Attack;						//	공격데이타

	//int (*AIFuncPtr)(Monster*);				//	돌릴 인공지능 설정

	//	image
	class ASpriteInstance* pMonAsIns;
//	class ASpriteInstance* pShaodwAsIns;
	class ASpriteInstance*	_ins_Debuff;	//인스턴스 - 디버프

	List2< S_MONSKILL* >	*m_MonSkillList;
	List2< S_MESSAGE* >		*m_MonMsgList;

	virtual void Process(S_CHARINFO* _CharInfo);
	void SetAction(int _nActionState);
	void ResvAction(int _nActionState, int _isAccept);
	bool BaseSetAction();
	virtual bool ExtSetAction()=0;
	bool BaseProcess();
	virtual bool ExtProcess()=0;

	//	상황에 따라 오버라이딩한다.
	virtual void Paint();
	void GetMessage();
	bool SetHolding(int HoldType);
	bool ReceiveAttack(Position3D& _Power);

	void SetMonData(int coloridx, int element, int nameidx, int ptnidx, int gradeidx, int level);
	void SetPosition(int x, int y, int z);

	void SetSpriteInstance(class ASprite* pAsprite, void* s_ASpriteSet, int color, int x, int y, int z=0);
	void RCV_Damage(int heroDamage);
	int SND_Damage(int heroLevel, int heroElemental, int heroDefense, int D_index, int nResvNextAtk = 0);
	void RCV_Debuff(int Debuff_Type); //디버프를 받았을때
	int SND_Debuff(int Attack_Type);//디버프를 가할때
	int	SND_Exp(int heroLevel);
	void Set_StetData(int level, int specificDataIdx, int gradeDataidx);
	void RegistUsingBaseData(List2< struct S_MONSKILL* > *pMonSkillList, List2< S_MESSAGE* > *pMonMsgList, void* s__ASpriteSet);
	void SetRegenType(int type, int regenIdx, int baseX=0, int baseY=0);
	void SetMessage(int type, int temp1=0, int temp2=0, int temp3=0, int temp4=0, int delay=0);
	void SetDirection(int _dir);
	int	m_nUsingImgIdx[MON_AC_MAX];
	void RemoveSkillList(int searchstate, int skillnum, void* who);
	int	SetMovingTime(int Moving, int sqrDstValue);
	void Paint_Debuff(int drawX,int drawZ);


};


//--------------------------------------------------------------------------------
class Mon_RAPTER : public Monster
{
public:
	Mon_RAPTER();
	~Mon_RAPTER();
	bool ExtSetAction();
	bool ExtProcess();
private:
};

//--------------------------------------------------------------------------------
#define MON2_LASERBEAM_COUNT					(4)
#define MON2_LASERBEAM_SIZE						(120)
class Mon_GOLEM : public Monster
{
public:
	Mon_GOLEM();
	~Mon_GOLEM();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Mon_SLIME : public Monster
{
public:
	Mon_SLIME();
	~Mon_SLIME();
	bool ExtSetAction();
	bool ExtProcess();
private:
};

//--------------------------------------------------------------------------------
class Mon_WATER_EFE : public Monster
{
public:
	Mon_WATER_EFE();
	~Mon_WATER_EFE();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Mon_COBOLT : public Monster
{
public:
	Mon_COBOLT();
	~Mon_COBOLT();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Mon_THUNDERBIRD : public Monster
{
public:
	Mon_THUNDERBIRD();
	~Mon_THUNDERBIRD();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_TANK : public Monster
{
public:
	Mon_TANK();
	~Mon_TANK();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_PUMPKIN : public Monster
{
public:
	Mon_PUMPKIN();
	~Mon_PUMPKIN();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
#define MON9_LASERBEAM_COUNT					(4)
#define MON9_LASERBEAM_SIZE						(120)
class Mon_SKELETON : public Monster
{
public:
	Mon_SKELETON();
	~Mon_SKELETON();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_GUNNER : public Monster
{
public:
	Mon_GUNNER();
	~Mon_GUNNER();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_ELF_FIRE : public Monster
{
public:
	Mon_ELF_FIRE();
	~Mon_ELF_FIRE();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_ELF_ICE : public Monster
{
public:
	Mon_ELF_ICE();
	~Mon_ELF_ICE();
	bool ExtSetAction();
	bool ExtProcess();
	
private:
};

//--------------------------------------------------------------------------------
class Mon_ELF_SILENCE : public Monster
{
public:
	Mon_ELF_SILENCE();
	~Mon_ELF_SILENCE();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Mon_TRICERATOPS : public Monster
{
public:
	Mon_TRICERATOPS();
	~Mon_TRICERATOPS();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_REDDRAGON : public Monster
{
public:
	Mon_REDDRAGON();
	~Mon_REDDRAGON();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_DEVIL : public Monster
{
public:
	Mon_DEVIL();
	~Mon_DEVIL();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_HUMAN_SWORD : public Monster
{
public:
	Mon_HUMAN_SWORD();
	~Mon_HUMAN_SWORD();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_HUMAN_MAGE : public Monster
{
public:
	Mon_HUMAN_MAGE();
	~Mon_HUMAN_MAGE();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_FLYTRAP : public Monster
{
public:
	Mon_FLYTRAP();
	~Mon_FLYTRAP();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Mon_CRAB : public Monster
{
public:
	Mon_CRAB();
	~Mon_CRAB();
	bool ExtSetAction();
	bool ExtProcess();

private:
};




//--------------------------------------------------------------------------------
class Mon_BUG : public Monster
{
public:
	Mon_BUG();
	~Mon_BUG();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Mon_DRILL : public Monster
{
public:
	Mon_DRILL();
	~Mon_DRILL();
	bool ExtSetAction();
	bool ExtProcess();

private:
	int  m_nLifeTimer;
};

//--------------------------------------------------------------------------------
class Mon_BOSS5_DEVIL : public Monster
{
public:
	Mon_BOSS5_DEVIL();
	~Mon_BOSS5_DEVIL();
	bool ExtSetAction();
	bool ExtProcess();

private:
	int  m_nLifeTimer;
};

//--------------------------------------------------------------------------------
class BossMon2_1 : public Monster
{
public:
	BossMon2_1();
	~BossMon2_1();
	bool ExtSetAction();
	bool ExtProcess();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();

private:
};


//--------------------------------------------------------------------------------
#define BOSS5_MAX_BODY_COUNT		9

#define BOSS_NOT_USE			0
#define BOSS_STAND				1
#define BOSS_SIT				2
#define	BOSS_DOWN				3
#define	BOSS_STAND_FACESIDE		4

#define	STANDTIME_MAX		100
#define	DOWNTIME_MAX		100
#define	RESTTIME_MAX		30
#define	ATTACK_PROTAGE		70

#define	ARM_REGENTIME_MAX		80

#define	BOSS6_FACE_VIEW_ARM			(160)
#define	BOSS6_FACE_NOT_VIEW_ARM		(1000)		//	180 move value

#define	BOSS6_FACE_YPOS		((BOSS6_FACE_VIEW_ARM)+180)		//	180 move value


class BossMon5_1 : public Monster
{
public:
	BossMon5_1();
	~BossMon5_1();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();

	int	CheckPassableAttack();
	void ResvBoss5_AllAction(int changeState, int dummy);
	Monster* pChildBody[BOSS5_MAX_BODY_COUNT];

	bool isFirstTouch;
	//	int  m_nMonStandState;
	static int  m_nNowDownCool;
	static int  m_nBossStep;		//	stand, down, sit, 

	static bool	isJumpChar;
	int m_nPassbleJumpTimer;
	static int m_nMaxLegHp;
	static int m_nNowLegHp;

	static int m_nMaxCoreHp;
	static int m_nCoreHp;

	static int m_nMaxFaceLeftArmHp;
	static int m_nMaxFaceRightArmHp;
	static int m_nFaceLeftArmHp;
	static int m_nFaceRightArmHp;

	static int m_nspikeTimer;
	int	m_nGroundspikeTimer;
	int m_nStandTime;
	int m_nRestTime;

	int m_nFaceLeftArmGenTimer;
	int m_nFaceRightArmGenTimer;

	static int m_nFaintHp;
	static int m_nMaxFaintHp;

	static int m_nMoveValue;
	int m_nMoveLocatex;
	int m_nMoveTimer;

private:

	//	ASpriteInstance* pAddMonAsIns[3];
};

//--------------------------------------------------------------------------------
class BossMon5_2 : public Monster
{
public:
	BossMon5_2();
	~BossMon5_2();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();
private:

	//	ASpriteInstance* pAddMonAsIns[3];
};


//--------------------------------------------------------------------------------
class BossMon5_3 : public Monster
{
public:
	BossMon5_3();
	~BossMon5_3();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();

private:

	//	ASpriteInstance* pAddMonAsIns[3];
};


//--------------------------------------------------------------------------------
class BossMon5_4 : public Monster
{
public:
	BossMon5_4();
	~BossMon5_4();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();

private:

	//	ASpriteInstance* pAddMonAsIns[3];
};


//--------------------------------------------------------------------------------
class BossMon5_5 : public Monster
{
public:
	BossMon5_5();
	~BossMon5_5();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);

	//	bool ExtSetAction();
	//	bool ExtProcess();
	//	void Paint();
	//	void GetMessage();

private:

	//	ASpriteInstance* pAddMonAsIns[3];
};


//--------------------------------------------------------------------------------
class BossMon5_6 : public Monster
{
public:
	BossMon5_6();
	~BossMon5_6();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	bool isPossibleAction;		//	정렬 상태로 바뀌는지 체크
};


//--------------------------------------------------------------------------------
class BossMon5_7 : public Monster
{
public:
	BossMon5_7();
	~BossMon5_7();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	bool isPossibleAction;
};

//--------------------------------------------------------------------------------
class BossMon5_8 : public Monster
{
public:
	BossMon5_8();
	~BossMon5_8();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	bool isPossibleAction;
};

//--------------------------------------------------------------------------------
class BossMon5_9 : public Monster
{
public:
	BossMon5_9();
	~BossMon5_9();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	bool isPossibleAction;
};

//--------------------------------------------------------------------------------
class BossMon5_10 : public Monster
{
public:
	BossMon5_10();
	~BossMon5_10();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	bool isPossibleAction;
};


//--------------------------------------------------------------------------------
class Mon_DEVIJOHNS : public Monster
{
public:
	Mon_DEVIJOHNS();
	~Mon_DEVIJOHNS();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();

private:
	int m_nDelayTimer;
};


//--------------------------------------------------------------------------------
#define BOSS_DRAGON_MAX_BODY_COUNT		2

class BossBigDragon1 : public Monster
{
public:

	void ResvBossDragon_AllAction(int changeState, int dummy);
	Monster* pChildBody[BOSS_DRAGON_MAX_BODY_COUNT];

	BossBigDragon1();
	~BossBigDragon1();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
	int m_nMoveX;
	int m_nMoveY;

	int m_nFirstX;

	int m_nMoveTimer;

	int m_nSaveX;
	int m_nSaveY;
	int m_nCurMoveTimer;

	int m_nDelayTimer;
};

//--------------------------------------------------------------------------------
class BossBigDragon2 : public Monster
{
public:
	BossBigDragon2();
	~BossBigDragon2();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:

	int m_nDelayTimer;
	int m_nMelee2AtkTime;
};

//--------------------------------------------------------------------------------
class BossBigDragon3 : public Monster
{
public:
	BossBigDragon3();
	~BossBigDragon3();
	bool ExtSetAction();
	bool ExtProcess();
	void Paint();
	void Process(S_CHARINFO* _CharInfo);
private:
};


//--------------------------------------------------------------------------------
class Barrel : public Monster
{
public:
	Barrel();
	~Barrel();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Stone_big : public Monster
{
public:
	Stone_big();
	~Stone_big();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Box : public Monster
{
public:
	Box();
	~Box();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

//--------------------------------------------------------------------------------
class Knight : public Monster
{
public:
	Knight();
	~Knight();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Temple_crock_small : public Monster
{
public:
	Temple_crock_small();
	~Temple_crock_small();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Temple_crock_big : public Monster
{
public:
	Temple_crock_big();
	~Temple_crock_big();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Temple_stonebox_small : public Monster
{
public:
	Temple_stonebox_small();
	~Temple_stonebox_small();
	bool ExtSetAction();
	bool ExtProcess();

private:
};


//--------------------------------------------------------------------------------
class Temple_stonebox_big : public Monster
{
public:
	Temple_stonebox_big();
	~Temple_stonebox_big();
	bool ExtSetAction();
	bool ExtProcess();

private:
};

#endif







/* 0*/	
/* 1*/	
/* 2*/	
/* 3*/	
/* 4*/	
/* 5*/	
/* 6*/	
/* 7*/	
/* 8*/	
/* 9*/	
/*10*/	
/*11*/	
/*12*/	
/*13*/	
/*14*/	
/*15*/	
/*16*/	
/*17*/	
/*18*/	
/*19*/	
/*20*/	
/*21*/	
/*22*/	
/*23*/	
/*24*/	
/*25*/	
/*26*/	
/*27*/	
/*28*/	
/*29*/	
/*30*/	
/*31*/	
/*32*/	
/*33*/	
/*34*/	
/*35*/	
/*36*/	
/*37*/	
/*38*/	
/*39*/	
/*40*/	
/*41*/	
/*42*/	
/*43*/	
/*44*/	
/*45*/	
/*46*/	
/*47*/	
/*48*/	
/*49*/	
/*50*/	
/*51*/	
/*52*/	
/*53*/	
/*54*/	
/*55*/	
/*56*/	
/*57*/	
/*58*/	
/*59*/	
/*60*/	
/*61*/	
/*62*/	
/*63*/	
/*64*/	
/*65*/	
/*66*/	
/*67*/	
/*68*/	

/*
#define STET_SPRITE				0
#define STET_BASE				1
#define STET_NAME				2
#define STET_ELEMENT			3
#define STET_COLOR				4
#define STET_ATK_1				5
#define STET_ATK_2				6
#define STET_ATK_3				7
#define STET_DEF_RATE			8
#define STET_HP_RATE			9
#define STET_CRI_RATE			10
#define STET_AGI_RATE			11
#define STET_ADD_EXP			12
#define STET_MAX				13

static const int MonBaseStet[][STET_MAX] = 
{
		//스프라이트 인덱스,		베이스,					이름,	속성,					컬러,	공격1,	공격2,	공격3,	방어율,	체력,	크리율, 회피율, 추가경험치
{ SPRITE_MON_SLIME,			MON_IDX_SLIME,			0,		MON_ELEMENTAL_SNIPS,	0,		100,	110,	  0,	  0,	 80,	  3,	  0,	100},		//	젤리푸
{ SPRITE_MON_SLIME,			MON_IDX_SLIME,			1,		MON_ELEMENTAL_STONE,	1,		120,	110,	  0,	  0,	100,	  4,	  0,	100},		//	젤리포우
{ SPRITE_MON_SLIME,			MON_IDX_SLIME,			2,		MON_ELEMENTAL_PAPER,	2,		140,	140,	  0,	 15,	 80,	  5,	  0,	100},		//	젤리킹
{ SPRITE_MON_GOLEM,			MON_IDX_GOLEM,			3,		MON_ELEMENTAL_SNIPS,	0,		150,	100,	200,	 50,	 80,	  0,	  0,	100},		//	골렘
{ SPRITE_MON_GOLEM,			MON_IDX_GOLEM,			4,		MON_ELEMENTAL_STONE,	1,		150,	150,	300,	 25,	250,	  5,	  0,	100},		//	락골렘
{ SPRITE_MON_GOLEM,			MON_IDX_GOLEM,			5,		MON_ELEMENTAL_PAPER,	2,		200,	300,	250,	 30,	300,	 20,	  0,	100},		//	헬골렘
{ SPRITE_MON_BIRD,			MON_IDX_THUNDERBIRD,	6,		MON_ELEMENTAL_SNIPS,	0,		120,	200,	  0,	 10,	200,	 30,	  0,	100},		//	뇌조
{ SPRITE_MON_BIRD,			MON_IDX_THUNDERBIRD,	7,		MON_ELEMENTAL_STONE,	1,		150,	250,	  0,	 15,	300,	 40,	  0,	100},		//	풍조
{ SPRITE_MON_BIRD,			MON_IDX_THUNDERBIRD,	8,		MON_ELEMENTAL_PAPER,	2,		170,	300,	  0,	  0,	400,	 50,	  0,	100},		//	불사조
{ SPRITE_MON_COBOLT,		MON_IDX_COBOLT,			9,		MON_ELEMENTAL_SNIPS,	0,		100,	170,	  0,	  5,	120,	  6,	  0,	100},		//	코볼트
{ SPRITE_MON_COBOLT,		MON_IDX_COBOLT,			10,		MON_ELEMENTAL_STONE,	1,		100,	200,	  0,	  7,	150,	  7,	  0,	100},		//	홉고블린
{ SPRITE_MON_COBOLT,		MON_IDX_COBOLT,			11,		MON_ELEMENTAL_PAPER,	2,		100,	230,	  0,	 10,	200,	 12,	  0,	100},		//	코볼트킹
{ SPRITE_MON_T_REX,			MON_IDX_RAPTER,			12,		MON_ELEMENTAL_SNIPS,	0,		120,	200,	  0,	  0,	150,	 20,	  0,	100},		//	랩터
{ SPRITE_MON_T_REX,			MON_IDX_RAPTER,			13,		MON_ELEMENTAL_STONE,	1,		130,	220,	  0,	  7,	170,	 25,	  0,	100},		//	톱니랩터
{ SPRITE_MON_T_REX,			MON_IDX_RAPTER,			14,		MON_ELEMENTAL_PAPER,	2,		140,	240,	  0,	 10,	220,	 30,	  0,	100},		//	칼발랩터
{ SPRITE_MON_ELEMENT,		MON_IDX_WATER_ELE,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_ELEMENT,		MON_IDX_WATER_ELE,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_ELEMENT,		MON_IDX_WATER_ELE,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_TANK,			MON_IDX_TANK,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_TANK,			MON_IDX_TANK,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_TANK,			MON_IDX_TANK,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_PUMPKIN,		MON_IDX_PUMPKIN,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_PUMPKIN,		MON_IDX_PUMPKIN,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_PUMPKIN,		MON_IDX_PUMPKIN,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_SKELETON,		MON_IDX_SKELETON,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_SKELETON,		MON_IDX_SKELETON,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_SKELETON,		MON_IDX_SKELETON,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_GUNNER,		MON_IDX_GUNNER,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_GUNNER,		MON_IDX_GUNNER,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_GUNNER,		MON_IDX_GUNNER,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_ELF,			MON_IDX_ELF,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_ELF,			MON_IDX_ELF,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_ELF,			MON_IDX_ELF,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_TRICERATOPS,	MON_IDX_TRICERATOPS,	15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_TRICERATOPS,	MON_IDX_TRICERATOPS,	16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_TRICERATOPS,	MON_IDX_TRICERATOPS,	17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_REDDRAGON,		MON_IDX_REDDRAGON,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_REDDRAGON,		MON_IDX_REDDRAGON,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_REDDRAGON,		MON_IDX_REDDRAGON,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_DEVIL,			MON_IDX_DEVIL,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_DEVIL,			MON_IDX_DEVIL,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_DEVIL,			MON_IDX_DEVIL,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_SWORD,	15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_SWORD,	16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_SWORD,	17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_MAGE,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_MAGE,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_HUMAN,			MON_IDX_HUMAN_MAGE,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_FLYTRAP,		MON_IDX_FLYTRAP,		15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_FLYTRAP,		MON_IDX_FLYTRAP,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_FLYTRAP,		MON_IDX_FLYTRAP,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_CRAB,			MON_IDX_CRAB,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_CRAB,			MON_IDX_CRAB,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_CRAB,			MON_IDX_CRAB,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BUG,			MON_IDX_BUG,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	100,	  0,	  0,	100},		//	물정령
{ SPRITE_MON_BUG,			MON_IDX_BUG,			16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_BUG,			MON_IDX_BUG,			17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_2,		MON_IDX_BOSS2_1,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	 20,	600,	 15,	  0,   1000},		//	운디네
{ SPRITE_MON_BUG,			MON_IDX_BUG,			15,		MON_ELEMENTAL_SNIPS,	0,		200,	160,	  0,	  0,	 30,		  0,	  0,	  0},		//	물정령
{ SPRITE_MON_BOSS_3,		MON_IDX_BOSS3_1,		16,		MON_ELEMENTAL_STONE,	1,		220,	180,	  0,	  0,	120,	  4,	  0,	100},		//	운디네
{ SPRITE_MON_BOSS_3,		MON_IDX_BOSS3_2,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_5,		MON_IDX_BOSS5_1,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_5,		MON_IDX_BOSS5_2,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_5,		MON_IDX_BOSS5_3,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_5,		MON_IDX_BOSS5_4,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_5,		MON_IDX_BOSS5_5,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BOSS_6,		MON_IDX_BOSS6_1,		17,		MON_ELEMENTAL_PAPER,	2,		240,	200,	  0,	 15,	140,	  8,	  0,	100},		//	워터팬텀
{ SPRITE_MON_BARREL,		MON_IDX_BARREL,			17,		MON_ELEMENTAL_PAPER,	0,		240,	200,	  0,	 15,	10,		  8,	  0,	0},			//	워터팬텀
{ SPRITE_MON_STONE_BIG,		MON_IDX_STONE_BIG,		17,		MON_ELEMENTAL_PAPER,	0,		240,	200,	  0,	 15,	999,	  8,	  0,	0},			//	워터팬텀



};
*/