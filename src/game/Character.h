#ifndef _CHARACTER_
#define _CHARACTER_


#include "ASpriteInstance.h"
#include "SUtil.h"
#include "Position3D.h"
#include "Physics.h"
#include "DEF.h"
#include "Defines.h"

#include "List.h"

#define	HERO_STOP 0

// #define	HERO_TURN_LEFT	1
// #define	HERO_TURN_RIGHT	2


#define	HERO_WALK_LEFT	10
#define	HERO_WALK_RIGHT	11
#define	HERO_WALK_UP	12
#define	HERO_WALK_DOWN	13

#define	HERO_ATTACK1	20
#define	HERO_ATTACK1END	21
#define	HERO_ATTACK2	22
#define	HERO_ATTACK2END	23
#define	HERO_ATTACK3	24
#define	HERO_ATTACK3END	25
#define	HERO_ATTACK4	26

#define	HERO_SWITCH			30// 히어로 변경

#define	HERO_LINE_MOVE_UP	31
#define	HERO_LINE_MOVE_DOWN	32
#define	HERO_DASH_RIGHT		33
#define	HERO_DASH_LEFT		34
#define	HERO_DASH_STOP		35
#define	HERO_DASH_ATT		36
#define	HERO_CHARGE			37
#define	HERO_CHARGE_SHOOT	38

#define	HERO_SKILL_0	40
#define	HERO_SKILL_1	41
#define	HERO_SKILL_2	42
#define	HERO_SKILL_3	43
#define	HERO_SKILL_4	44

#define	HERO_SKILL_E1	50
#define	HERO_SKILL_C2	51
#define	HERO_SKILL_E2	52
#define	HERO_SKILL_C3	53
#define	HERO_SKILL_E3	54
#define	HERO_SKILL_C4	55
#define	HERO_SKILL_E4	56
#define	HERO_SKILL_C5	57



#define	DAMAGE_NOT		100
#define	DAMAGE_FLY		101
#define	DAMAGE_GROUND	102
#define	DAMAGE_DOWN		103
#define	HERO_DOWNED		105
#define	HERO_DOWNED_2		106
#define	HERO_AWAKE		107
#define	HERO_THROW		108
#define	HERO_JumpUp		109
#define	HERO_JumpDown	110

#define	HERO_TAG_IN		500



//Skill
#define	SKILL_ACTIVE_S1		 0
#define	SKILL_ACTIVE_S2		 1
#define	SKILL_ACTIVE_S3		 2
#define	SKILL_ACTIVE_S4		 3
#define	SKILL_ACTIVE_S5		 4
#define	SKILL_ACTIVE_S6		 5
#define	SKILL_ACTIVE_S7		 6

#define	SKILL_ACTIVE_G1		 7
#define	SKILL_ACTIVE_G2		 8
#define	SKILL_ACTIVE_G3		 9
#define	SKILL_ACTIVE_G4		10
#define	SKILL_ACTIVE_G5		11
#define	SKILL_ACTIVE_G6		12
#define	SKILL_ACTIVE_G7		13

#define	SKILL_ACTIVE_O1		14
#define	SKILL_ACTIVE_O2		15
#define	SKILL_ACTIVE_O3		16
#define	SKILL_ACTIVE_O4		17
#define	SKILL_ACTIVE_O5		18
#define	SKILL_ACTIVE_O6		19
#define	SKILL_ACTIVE_O7		20
									
#define	SKILL_P_S_swordMaster		21
#define	SKILL_P_S_lifeUp			22
#define	SKILL_P_S_deadlyAttack		23
#define	SKILL_P_S_ironWall			24
#define	SKILL_P_S_poisonAttack		25
#define	SKILL_P_S_wingSword			26
#define	SKILL_P_S_spaceCut			27

#define	SKILL_P_G_gunMaster			28
#define	SKILL_P_G_criIncrease		29
#define	SKILL_P_G_highAgi			30
#define	SKILL_P_G_manaUp			31
#define	SKILL_P_G_identify			32
#define	SKILL_P_G_stunUp			33
#define	SKILL_P_G_healUp			34

#define	SKILL_P_O_orbMaster			35
#define	SKILL_P_O_immuneAttUp		36
#define	SKILL_P_O_recoveryUp		37
#define	SKILL_P_O_coolTimeDown		38
#define	SKILL_P_O_addAbility		39
#define	SKILL_P_O_ancientLang		40
#define	SKILL_P_O_iceUp				41

#define	SKILL_P_P_catch				42
#define	SKILL_P_P_lineMove			43
#define	SKILL_P_P_dashAtt			44
#define	SKILL_P_P_guard				45
#define	SKILL_P_P_chargeShot		46
#define	SKILL_P_P_manaCharge		47
//
//#define	SKILL_P_S_swordMaster				s_Skill.Level_P[ 0]
//#define	SKILL_P_S_lifeUp					s_Skill.Level_P[ 1]
//#define	SKILL_P_S_deadlyAttack				s_Skill.Level_P[ 2]
//#define	SKILL_P_S_ironWall					s_Skill.Level_P[ 3]
//#define	SKILL_P_S_poisonImmune				s_Skill.Level_P[ 4]
//#define	SKILL_P_S_wingSword					s_Skill.Level_P[ 5]
//#define	SKILL_P_S_spaceCut					s_Skill.Level_P[ 6]
//
//#define	SKILL_P_G_gunMaster					s_Skill.Level_P[ 7]
//#define	SKILL_P_G_criIncrease				s_Skill.Level_P[ 8]
//#define	SKILL_P_G_highAgi					s_Skill.Level_P[ 9]
//#define	SKILL_P_G_manaUp					s_Skill.Level_P[10]
//#define	SKILL_P_G_identify					s_Skill.Level_P[11]
//#define	SKILL_P_G_stunUp					s_Skill.Level_P[12]
//#define	SKILL_P_G_healUp					s_Skill.Level_P[13]
//
//#define	SKILL_P_O_orbMaster					s_Skill.Level_P[14]
//#define	SKILL_P_O_immuneAttUp				s_Skill.Level_P[15]
//#define	SKILL_P_O_recoveryUp				s_Skill.Level_P[16]
//#define	SKILL_P_O_coolTimeDown				s_Skill.Level_P[17]
//#define	SKILL_P_O_addAbility				s_Skill.Level_P[18]
//#define	SKILL_P_O_ancientLang				s_Skill.Level_P[19]
//#define	SKILL_P_O_iceUp						s_Skill.Level_P[20]
//
//#define	SKILL_P_P_catch						s_Skill.Level_P[21]
//#define	SKILL_P_P_lineMove					s_Skill.Level_P[22]
//#define	SKILL_P_P_guard						s_Skill.Level_P[23]
//#define	SKILL_P_P_manaCharge				s_Skill.Level_P[24]
//#define	SKILL_P_P_chargeShot				s_Skill.Level_P[25]
//#define	SKILL_P_P_dashAtt					s_Skill.Level_P[26]





#define	TAG_GAP				40


//COSTUME
#define	PAL_ORIGINAL		0 //이펙트
#define	PAL_HEAD			1 
#define	PAL_BODY			2 
#define	PAL_ARM				3 
#define	PAL_LEG				4 
#define	PAL_BOW				5 
#define	PAL_CLAW			6 
//#define	PAL_KNIFE2			7 
//#define	PAL_ORB				8 
//시작점
#define	START_W_HEAD				0//0 
#define	START_W_BODY				13//13
#define	START_W_ARM					23//24
#define	START_W_LEG					37//39
#define	START_W_BOW					56//69

#define	START_M_HEAD				0//0 
#define	START_M_BODY				12//13
#define	START_M_ARM					20//24
#define	START_M_LEG					26//39
#define	START_M_CLAW				48//69

//갯수
#define	LENGTH_W_HEAD				13//13 
#define	LENGTH_W_BODY				10//11
#define	LENGTH_W_ARM				14//15
#define	LENGTH_W_LEG				19//22
#define	LENGTH_W_BOW				4//3

#define	LENGTH_M_HEAD				12//13 
#define	LENGTH_M_BODY				8//11
#define	LENGTH_M_ARM				6//15
#define	LENGTH_M_LEG				22//22
#define	LENGTH_M_CLAW				8//4



//parameter
#define	JAB_KNIGHT	0
#define	JAB_GUNNER	1
#define	JAB_MAGE	2

//parameter

#define	SEX_WOMAN	0
#define	SEX_MAN		1

#define	TEMP_UP_LIMIT	157
#define	TEMP_DOWN_LIMIT	255

#define	D_RIGHT	1
#define	D_LEFT	2
#define	HERO_WRIGHT 25
#define	HERO_HEIGHT 50

//DAMAGE_FLY
#define	LOW_BOUND	-20	//낮은 바운딩이 대는 지점
#define	LAST_BOUND	-8	//바운드가 일어나지 않는 한계
#define	HIGH_PITCH	5	//체공으로 처리해줄 Z +-절대값

//속성
#define	ELEMENTAL_STONE 0 
#define	ELEMENTAL_SNIPS 1
#define	ELEMENTAL_PAPER 2
#define	ELEMENTAL_NON	3

//struct Skill_Set{
//	int Num;//스킬번호 (0,1,2,3,4) - 슬롯번호
//	int Input_Key;	//SangHo - 주인공의 잡기가 가능하다면
//	int Skill_ID[5];//스킬의 고유 ID 를 저장 스킬의 예외처리에 사용된다
//	bool OVER_SkillEffect;		//SangHo - 주인공의 스킬이 발동하면 True 이다
//	bool DOWN_SkillEffect;		//SangHo - 주인공의 스킬이 발동하면 True 이다
//};
//Skill_Set s_Skill_Set;

#define	TOWN (m_nFieldId/100 == 8)
#define	FULL_NEED_FRAME_HP 750
#define	FULL_NEED_FRAME_MP 750


#include "CharacterTable.h"

struct CommandSkill{
	short name;			//스킬 커맨드 이름
	short count;		//스킬의 커맨드 수
	short c_ins_Skill[5];		//스킬 커맨드 정보
};

const CommandSkill s_C_Skill[5] = {
	{HERO_LINE_MOVE_UP	,2,{MH_KEY_UP	,MH_KEY_UP		,0,0,0}},
	{HERO_LINE_MOVE_DOWN,2,{MH_KEY_DOWN	,MH_KEY_DOWN	,0,0,0}},
	{HERO_DASH_RIGHT	,2,{MH_KEY_RIGHT,MH_KEY_RIGHT	,0,0,0}},
	{HERO_DASH_LEFT		,2,{MH_KEY_LEFT	,MH_KEY_LEFT	,0,0,0}},
	{HERO_CHARGE	,5,{MH_KEY_SELECT,MH_KEY_SELECT,MH_KEY_SELECT,MH_KEY_SELECT,MH_KEY_SELECT}}
};const int cSkill_length = 7;







////////////////////STATE///////////////////////////////
struct HeroAbility{
	int STR;	//힘  -검사 공격력(건너의80%) , 방어력(70%)
	int DEX;	//민첩-건너 공격력(100%) , 회피,크리
	int CON;	//체력-생명력, 방어력(30%),생명력 회복률
	int INT;	//지능-마법사 공격력(건너의 130%) , 마나
	int FAM;	//명성-별도 스탯 , 퀘스트 습득 및 마을 사람과의 대화 필요
	int POINT;	//명성-별도 스탯 , 퀘스트 습득 및 마을 사람과의 대화 필요
// 	int JAB_KNIFE;	//검사 - 직업 선택 가능하다면 true
// 	int JAB_GUN;	//총사 - 직업 선택 가능하다면 true
// 	int JAB_MAGIC;	//술사 - 직업 선택 가능하다면 true
};
struct HeroStatus{
	int LIFE;			//생명 0 이 되면 죽는다.
	int LIFE_MAX;			//생명 0 이 되면 죽는다.
	int MANA;			//마나 0 이 되면 스킬을 못쓴다.
	int MANA_MAX;			//마나 0 이 되면 스킬을 못쓴다.

	int EXP;			//마나 0 이 되면 스킬을 못쓴다.
	int EXP_MAX;			//마나 0 이 되면 스킬을 못쓴다.
	int LEVEL;			//마나 0 이 되면 스킬을 못쓴다.

	int ATTACK_MAX[3];		//칼,검,마 공격력
	int ATTACK_MIN[3];		//칼,검,마 공격력
	int DAMAGE;			//공식에 의해 상대에게 직접적인 타격을 주는 수치
	int DEBUFF;			//공격1회마다 디버프가 계산되어 적용된다
	int DEFENSE;		//방어구에 의해 방어율 계산에 적용 대는 수치(주인공만 있음/이것을 디스 플레이함)
	int DEFENSE_PER;	//방어력으로 자동 계산 대는 데미지 상쇄 % (유저에겐 보여주지 않음)
	int CRITICAL;		//크리티컬 데미지 들어갈 확률
	int AVOID;			//적의 공격을 피할 확률
	int LIFE_RECOVERY;	//체력이 회복 대는 수치
	int MANA_RECOVERY;	//마나가 회복 대는 수치
	//int	ELEMENTAL;		//공식에 의해 상대에게 직접적인 타격을 주는 수치
	//int	SEX;		//0: 남자, 1:여자
	int	Qslot[2];		//0:Bag  1:Slot

	int	MONEY;		//보유금액
};
struct Damage{
	short Type;				//주인공이 입은 데미지의 타입을 결정한다
	short Sum;			//주인공이 입은 데미지를 합산한다
	short Direction;	//주인공이 X축에서 어느쪽으로 밀리는지를 기록한다.
	short Bound;			//주인공이 땅에 튄 횟수
	short Bound_Num;		//주인공이 땅에 튄 후 프레임 수 (튈때마다 초기화)

	short Down_Time;		//주인공이 땅에 튄 후 프레임 수 (튈때마다 초기화)

	bool _b_Must_Decide;//행동 Decide를 무조건적으로 들어가는지의 여부를 체크

};
struct HeroTag{
	bool act;			//SangHo - 태그중이라면
	int	SEX;		//0: 남자, 1:여자
	int FocusHero;		//현재 컨트롤 대상 히어로를 지정한다
	bool OVER_SkillEffect;
	bool DOWN_SkillEffect;
	bool _b_ActionEnd;
	bool TAG_OUT;
	Damage s_Damage;
};
struct Skill{ 
	int Equip_A[3*2];	//장착 액티브 스킬//-1은 미습득
	int Equip_P[9];	//장착 패시브 스킬//-1은 미습득

	int Level_A[7*3];	//액티브 스킬레벨
	int Level_P[7*4];	//칼 패시브 스킬레벨
};
struct Skill_Set{
	bool act;	//SangHo - 스킬이 시전되면
	int Num;//스킬번호 (0,1,2,3,4) - 슬롯번호
	int Input_Key;	//SangHo - 주인공의 잡기가 가능하다면
	int Skill_ID[2][3];//스킬의 고유 ID 를 저장 스킬의 예외처리에 사용된다
	int Skill_LEVEL[2][3];//스킬의 고유 ID 를 저장 스킬의 예외처리에 사용된다
	int Need_Mana[2][3];//스킬의 소비마나 수치
	int Cool_TimeMax[2][5];//스킬의 쿨타임을 기록
	int Cool_TimeNow[2][5];//스킬의 현재 쿨타임
	bool OVER_SkillEffect;		//SangHo - 주인공의 스킬이 발동하면 True 이다
	bool DOWN_SkillEffect;		//SangHo - 주인공의 스킬이 발동하면 True 이다
};
struct ItemBag{
	int Data0;		//아이템의 인덱스및 컬러,착용 정보
	//장착인덱스(2),스프라이트인덱스(2), 팔레트(1), 아이템ID(4)

	int Data1;	//아이템의 정보 - 아이템에따라 해석하는 방식이 달라진다
	//소켓3(2),소켓2(2),소켓1(2),접두사(2),등급(1)

	int Data2;	//아이템의 추가 정보 - 아이템에따라 해석하는 방식이 달라진다
	//강화(2),스탯스크롤(2)
};

struct ItemAbility{
		int ATT_MIN;
		int ATT_MAX;
		int DEF;

		int CRI;
		int AGI;
		int HP;
		int MP;

		int STR;
		int DEX; 
		int CON; 
		int INT; 
};
struct MustAction{
	int must_X;	//이동해야할 X
	int must_Y;	//이동해야할 Y
	int must_Action;//취해야하는 행동
	int must_Look;//취해야하는 행동
};
////////////////////STATE///////////////////////////////


class Character	
{
public:

	

	Character(bool Woman, int b_direction_R, void* s_ASpriteSet);
	~Character();


	//팝업 UI를 위한 참조변수
	static HeroAbility s_Ability[2];
	static HeroStatus s_Status[2];
	static HeroTag s_HeroTag;//히어로의 태그시 사용되는 각종 변수

	
	static Skill s_Skill;
	static Skill_Set s_Skill_Set;

	static ItemBag s_ItemEquip[2][7];//착용 아이템
	static ItemAbility s_ItemAbil[2][7];//착용 아이템의 능력

	static ItemBag s_ItemSlot[4];//가방 슬롯
	static ItemBag s_ItemBag[4][32];//슬롯당 인벤
	static ItemBag s_ItemPick;//픽업 슬롯

	static ItemBag s_ItemShop[24];//상점 인벤
////////////////////////////////////////////////////////////////////////////////////////

	static MustAction s_MustAction;
	static class ASprite*	_spr_Hero_W;				//스프라이트 - 히어로 여
	static class ASprite*	_spr_Hero_M;				//스프라이트 - 히어로 남

	class ASprite*	_spr_Skill[2][3];		//스프라이트 - 히어로 스킬 2x3개

	class ASpriteInstance*	_ins_Hero;			//인스턴스 - 히어로
	class ASpriteInstance*	_ins_Hero_clone;	//인스턴스 - 태그직후 히어로의 행동 보존개체
	class ASpriteInstance*	_ins_Skill_clone[2];		//인스턴스 - 히어로 스킬 5개

	class ASpriteInstance*	_ins_Debuff;	//인스턴스 - 디버프
	class ASpriteInstance*	_ins_Skill[2][3][2];		//인스턴스 -{남,여] [히어로 스킬 3개] [앞,뒤]
////////////////////////////////////////////////////////////////////////////////////////


	struct ASpriteSet{//공용 스프라이트 묶음
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	struct Queue{
		int full[5];		//큐풀
		int tick;			//Tick타임
		short delTick;		//큐가 초기화 대는데 까지 걸리는 Tick타임
		short count;		//큐풀 인덱스 카운터
	};
	Queue s_KeyQueue;

	

	struct Debuff{
		short All;	//SangHo - 주인공의 잡기가 가능하다면
		short stack[3][2];	//SangHo - 주인공의 잡기가 가능하다면
		short color;//상태이상 컬러증가치
	};
	Debuff s_Debuff;

	struct weapon_Switch{
		bool act;				//활성여부
		short next_Event;		//장비 스위치가 끝나고 이어지는 스킬
		short nextWeapon;		//장비 스위치가 끝나고 바뀌어야할 무기

	};
	weapon_Switch s_WeaponSwitch;


	Damage s_Damage;

	struct Level_Eff{
		bool act;
		bool LVup_ActionEnd;
		short LVupEff_Num;
		class ASpriteInstance*	LVup_Eff_Ins;
	};
	Level_Eff s_LV_Eff;

	struct Bullet_Eff{//발사형 스킬 이펙트
		bool act;	//SangHo - 스킬이 시전되면
		bool LVup_ActionEnd;
		short LVupEff_Num;
		class ASpriteInstance*	Bullet_Eff_Ins;
	};
	/*
	#스킬5(유도탄)
	6 - 첫탄=8프레임 x55
	7 - 둘째탄=11프레임x55
	8 - 셋째탄=14프레임x55

	@여
	#스킬1
		0 - 불렛1=8프레임 x26
		1 - 불렛2=12프레임 x26
		2 - 불렛3=15프레임 x26
		3 - 불렛4=18프레임 x26
		4 - 불렛5=21프레임 x26
	#스킬2= 
		5 - 0프레임 x0  장풍지속시간 22프레임간

	#스킬6
		6 - 5프레임 x26  지속시간 32프레임간
	#스킬7
		7 - 0프레임 x0 31프레임간
		8 - 0프레임 x0 31프레임간
		9 - 0프레임 x0 31프레임간
	*/
#define	BULLET_MAX 10
	Level_Eff s_Bullet_Eff[BULLET_MAX];
	Level_Eff s_Knife_Eff[3];//K1,K2,K3 ,Back_E , Front_E
	bool	_b_Knife_ActionEnd;		//SangHo - 주인공의 액션이 종료했다면 True 이다
	int	_b_Knife_SetNum;		//SangHo - 주인공의 액션이 종료했다면 True 이다

	struct Throw{
		bool ThrowPossible;	//SangHo - 주인공의 잡기가 가능하다면
		bool act;	//SangHo - 주인공의 잡기가 가능하다면
		int ThrowNum;	//SangHo - 주인공의 잡기가 가능하다면
		// 0 - 일반잡기   1 - 1단잡기    2 - 2단잡기
	};
	Throw s_Throw;

	struct Event_Rect{//SangHo - 주인공의 이벤트 영역
		int X1;
		int Y1;
		int X2;
		int Y2;
		int W;
		int H;
		int Direction;
	};Event_Rect s_Event_Rect;






	byte			_b_JabNum;			//SangHo - 직업번호 0,1,2
	int				_m_stackZ;			//SangHo - Y 스택 좌표
	int				_m_actNum;			//SangHo - 주인공 케릭터의 액션 상태값
	int				_b_LookRight;		//SangHo - 주인공이 오른쪽을 보고있으면 True 이다
	bool			_b_ActionEnd;		//SangHo - 주인공의 액션이 종료했다면 True 이다
	
	int _m_Hero_AttackNum;
	int _move_Order;
	

	bool _b_Key_Nullity;	//사용자의 키 입력을 강제적으로 무시한다.
	bool _b_Key_Protect;	//지정된 액션이 끝나기 전까지 보호할 _move_Order값이 있을때
	bool _b_Hero_Protect;	//지정된 액션이 끝나기 전까지 주인공이 보호대어야 할때

	int _m_dashRepeat;//대쉬 반복횟수

	int NUMBER;//지속적으로 증가하는 수치

	bool Critical;//지속적으로 증가하는 수치

	Position3D	m_Hero_Pos;		//주인공의 현 포지션
	Physics*	m_Hero_Physics; //주인공의 

	
	int m_HEADTOP;//주인공 머리꼭대기

	
	int _m_test;//지울것





	






	void KeyEvent(int m_keyCode, int m_keyRepeat);
	void Process();
	void Paint();






private:
	//KeyEvent
	int		Event_command();
	int		Event_move(int m_keyCode,int m_keyRepeat);							//이벤트의 최초할당 및 키 지속적인 반영을 위한 부분
	int		Event_skill(int m_keyCode,int m_keyRepeat,int m_actNum);	//한번의 키 입력으로 애니 종료까지 애니메이션이 방해받지않는 이벤트들

	//Process
	void	Recovery();														//매 프레임마다 자동적으로 취해지는 연산
	int		SetDamageDecide(ASpriteInstance*	_ins_Hero,Damage& s_Damage);													//SangHo - 물리값에 의한 이벤트 처리 
	void	SetActionDecide(int m_actNum);

	//Paint
	void	Paint_Debuff(int drawX,int drawZ);						// debuf 상태일때
	void	Paint_Knife();											// 호밍 나이프 버프 상태일때
	void	Paint_Bollet();											// 발사형 스킬 이펙트 그릴때
	void	Paint_LevelUp();											// 레벨업 이펙트를 그릴때

	//ETC
	bool	Check_command(int m_keyCode, int m_keyRepeat);					//액션 커맨드를 저장하는 큐공간
	bool	Check_skill_impossible(int m_skillnum);									//스킬 사용 가능여부를 판단
	//int		Check_jab(int m_Jab_Knight,int  m_Jab_Gunner,int  m_Jab_Magi);
	
	int		Check_weapon(int m_Must_Weapon , int m_if_true_set_action );
	int		Set_skill_chain(int chain_Num, int m_keyCode, int chain_Key, int skill_Now, int skill_Next, int skill_Stop);
	void	Set_left_right(int b_direction_R);
	void	Set_fly_motion(ASpriteInstance*	_ins_Hero,Damage& p_Damage,Position3D& p_Position3D);
	void	Check_Sound();
	

	

public://G Field
	
	static int	Check_sex(int m_Woman,int  m_Man);
	static void	Set_state_calculate();//각종 수치 변환으로 인한 데이터의 재계산이 필요할시 적용
	static void InitCostume();
	static void ChangeCostume(ASprite* spr, int part,int index,int pal);

	static bool	Set_MustAction(int x, int y,int Action,int Look);//주인공이 강제적으로 취해야 할 행동에 대한부분
	
	
	void	Init_Skill();//스킬들의 초기화를 처리
	void ReceiveAttack(Position3D& _Power);//공격자에게서 공격을 받았을때 처리해주는 구문

	void RCV_Damage(int monDamage); //데미지를 받았을때
	int SND_Damage(int monLevel, int monElemental , int monDefense, int D_index);//공격을 할때

	void RCV_Debuff(int Debuff_Type); //디버프를 받았을때
	int SND_Debuff(int Attack_Type);//디버프를 가할때

	int Set_Exp(int _Exp);//경험치 가감수치
	int CloneCopy();//현재 취하고 있는 행동을 모두 클론에게 카피한다

	void InitCharPos(int x, int y, int Look = 0);


	static int Get_Skill(int passive_Num);//액티브 스킬 값받아오기


	int	m_nFieldId;//지역ID




private:

};

#endif