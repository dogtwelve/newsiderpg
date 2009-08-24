#ifndef __MONSTER_AI_
#define __MONSTER_AI_

#include "Position3D.h"



#define GETMONAI						(MonsterAI::GetInstance())


#define AI_INIT(a)						(GETMONAI)->AI_Init(a)
#define AI_PROCESS(a)					(GETMONAI)->Process(a)
#define AI_PROCESS_BOSS1(a)				(GETMONAI)->Process_BOSS1(a)
#define AI_PROCESS_BOSS2(a)				(GETMONAI)->Process_BOSS2(a)
#define AI_PROCESS_BOSS5(a)				(GETMONAI)->Process_BOSS5(a)
//#define AI_PROCESS_BOSS5_DUMMY(a)		(GETMONAI)->Process_BOSS5_Dummy(a)


#define AI_RECEIVE_DEMEGE(a)			(GETMONAI)->ReceiveAttack(a)




//	보기편하게 인공지능 부분을 정의해둔다.
#define RECHARGE_ESCAPETICK()			(pMonster->m_nEscapeCurTick = pMonster->m_nEscapeMaxTick)
#define IS_ESCAPETICK_NULL				(0 >= pMonster->m_nEscapeCurTick)
#define INIT_ESCAPETICK()				(pMonster->m_nEscapeCurTick = 0)
#define BATTLE_OFF()					(pMonster->m_nIsBattle = 0)
#define BATTLE_ON()						(pMonster->m_nIsBattle = 1)
#define IS_BATTLE_ON					(1 == pMonster->m_nIsBattle)


//	속성
#define	ATRI_INC_CRITICAL_10			0x00000000001
#define	ATRI_INC_ATTACK_10				0x00000000010
#define	ATRI_INC_ATTACKSPD_10			0x00000000100
#define	ATRI_INC_CRITICAL_100			0x00000000100
#define	ATRI_GIV_STUN					0x00000000100
#define	ATRI_GIV_POISION				0x00000000100
#define	ATRI_GIV_SLEEP					0x00000000100
#define	ATRI_GIV_STOP					0x00000000100
#define	ATRI_PSB_GUARD					0x00000000100
#define	ATRI_ONLY_DAMEGE				0x00000000100


//	MonsterState
/*
#define MON_AI_NULL						(0)
#define MON_AI_STAND					(1)
#define MON_AI_STROLL					(MON_AI_STAND+1)
#define MON_AI_APPROACH					(MON_AI_STAND+2)
#define MON_AI_WATCH_HERO				(MON_AI_STAND+3)
#define MON_AI_ATTACK					(MON_AI_STAND+4)
#define MON_AI_RCV_ATTACK				(MON_AI_STAND+5)
#define MON_AI_RETURN_BASE				(MON_AI_STAND+6)
#define MON_AI_DIE						(MON_AI_STAND+7)
*/

//	Attack select table
#define MON_USE_NORMAL_TABLE			(1)
#define MON_USE_RCV_HIT_TABLE			(2)

//	MON AI ACTION


#define RESV_STATE(a,b)					((a)->m_nAiNextState=(b))	

//#define MON_AI_MAX						(MON_AI_STAND+4)

typedef struct _Range
{
	int x;
	int y;
	int width;
	int height;
}Range;

static const int Mon_Melee_NormalTable[][3] = 
{
	//	전방공격	후방공격	대기
	//	TEST
//	{	140,		0,			60},
//	{	50,			50,			100},
	{	40,			40,			120},
};

static const int Mon_Range_NormalTable[][3] = 
{
	//	전방공격	후방공격	대기
//	{	50,			50,			100},
	{	40,			40,			120},
};


static const int Mon_Melee_RcvAtckTable[][3] = 
{
	//	대기		반격		탈출
	{	200,		0,			0},		//	0번째는 쓰지 않치만 리스트 순서상 만들어준다.
	{	200,		0,			0},
	{	200,		0,			0},
	{	200,		0,			0},
	{	199,		0,			1},
	{	198,		0,			2},	
};

static const int Mon_Range_RcvAtckTable[][3] = 
{
	//	대기		반격		탈출
	{	200,		0,			0},		//	0번째는 쓰지 않치만 리스트 순서상 만들어준다.
	{	196,		2,			2},
	{	191,		4,			5},
	{	184,		6,			10},
	{	172,		8,			20},
	{	150,		10,			40},		
};


class Monster;


class MonsterAI	
{
private:
	MonsterAI();
	static MonsterAI*	pMonsterAI;

public:
	~MonsterAI();

	static MonsterAI* GetInstance();
	void FreeInstance();
	int Process(Monster*);
	int Process_BOSS1(Monster*);
	int Process_BOSS2(Monster*);
	int Process_BOSS5(Monster*);
//	int Process_BOSS5_Dummy(Monster*);
	static bool Move(Monster* pMonster, Position3D* pos, int action);
	static void SetAttack(Monster* pMonster);
	static void EndBattle(Monster* pMonster);
	static void StartBattle(Monster* pMonster);
	static void ReceiveAttack(Monster* pMonster);
	static bool CheckAttackRange(Monster* pMonster);
	static int CheckNextAction(Monster* pMonster);
//	static int CheckNextAction_Boss5(Monster* pMonster);
	

	static void AI_Init(Monster* pMonster);
	static void AI_ChangeState(Monster* pMonster);
	static void AI_ResvState(Monster* pMonster, int _state);

	static void AI_F_WAIT_ORDER(Monster* pMonster);			//	아무액션도 취하지 않는다.
	static void AI_F_LOOKAROUND(Monster* pMonster);
	static void AI_F_READY_TO_HIT(Monster* pMonster);
	static void AI_F_ATTACK(Monster* pMonster);
	static void AI_F_MOVE_BACK(Monster* pMonster);
	static void AI_F_RESIST_ATTACK(Monster* pMonster);
	static void AI_F_ESCAPE(Monster* pMonster);
	static void AI_F_MOVE_FIRST_POSITION(Monster* pMonster);
	static void AI_F_RCV_DEMEGE(Monster* pMonster);
	static void AI_F_ATTACK_DONTMOVE(Monster* pMonster);
	static void AI_F_WORM_BURROWMOVE(Monster* pMonster);


//////////////////////////////////////////////////////////////////
//	static void ChangeTick(Monster* pMonster, int _tick);
//	static void ChangeState(Monster* pMonster, int state);
//	static void AI_F_STAND(Monster* pMonster);
//	static void AI_F_STROLL(Monster* pMonster);
//	static void AI_F_APPROACH(Monster* pMonster);
//	static void AI_F_WATCH_HERO(Monster* pMonster);
//	static void AI_F_ATTACK(Monster* pMonster);
//	static void AI_F_RCV_ATTACK(Monster* pMonster);
//	static void AI_F_RETURN_BASE(Monster* pMonster);
//	static void AI_F_DIE(Monster* pMonster);





//	add state

	//	AI MESSAGE PROCESS
private:

};


///////////////////////////////////////////////////////
#define MON_AI_NULL						(0)
#define MON_AI_WAIT_ORDER				(1)
#define MON_AI_LOOKAROUND				(2)
#define MON_AI_READY_TO_HIT				(3)
#define MON_AI_ATTACK					(4)
#define MON_AI_RESIST_ATTACK			(5)
#define MON_AI_ESCAPE					(6)
#define MON_AI_MOVE_FIRST_POSITION		(7)
#define MON_AI_RCV_DEMEGE				(8)
#define MON_AI_READY_ORDER				(9)
#define MON_AI_ATTACK_DONTMOVE			(10)
#define MON_AI_MOVE_BACK				(11)

#define MON_AI_WORM_BURROWMOVE			(12)

static void (*AIFuncPtr[])(Monster*) = 
{
	0,
	MonsterAI::AI_F_WAIT_ORDER,
	MonsterAI::AI_F_LOOKAROUND,
	MonsterAI::AI_F_READY_TO_HIT,
	MonsterAI::AI_F_ATTACK,
	MonsterAI::AI_F_RESIST_ATTACK,
	MonsterAI::AI_F_ESCAPE,
	MonsterAI::AI_F_MOVE_FIRST_POSITION,
	MonsterAI::AI_F_RCV_DEMEGE,
	MonsterAI::AI_F_WAIT_ORDER,
	MonsterAI::AI_F_ATTACK_DONTMOVE,
	MonsterAI::AI_F_MOVE_BACK,

	MonsterAI::AI_F_WORM_BURROWMOVE,
	

//	MonsterAI::AI_F_WATCH_HERO,
//	MonsterAI::AI_F_ATTACK,
//	MonsterAI::AI_F_RCV_ATTACK,
//	MonsterAI::AI_F_RETURN_BASE,
//	MonsterAI::AI_F_DIE,
};

#endif	// __MONSTER_AI_