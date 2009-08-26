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

#define	HERO_SWITCH			30// ����� ����

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
#define	PAL_ORIGINAL		0 //����Ʈ
#define	PAL_HEAD			1 
#define	PAL_BODY			2 
#define	PAL_ARM				3 
#define	PAL_LEG				4 
#define	PAL_BOW				5 
#define	PAL_CLAW			6 
//#define	PAL_KNIFE2			7 
//#define	PAL_ORB				8 
//������
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

//����
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
#define	LOW_BOUND	-20	//���� �ٿ���� ��� ����
#define	LAST_BOUND	-8	//�ٿ�尡 �Ͼ�� �ʴ� �Ѱ�
#define	HIGH_PITCH	5	//ü������ ó������ Z +-���밪

//�Ӽ�
#define	ELEMENTAL_STONE 0 
#define	ELEMENTAL_SNIPS 1
#define	ELEMENTAL_PAPER 2
#define	ELEMENTAL_NON	3

//struct Skill_Set{
//	int Num;//��ų��ȣ (0,1,2,3,4) - ���Թ�ȣ
//	int Input_Key;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
//	int Skill_ID[5];//��ų�� ���� ID �� ���� ��ų�� ����ó���� ���ȴ�
//	bool OVER_SkillEffect;		//SangHo - ���ΰ��� ��ų�� �ߵ��ϸ� True �̴�
//	bool DOWN_SkillEffect;		//SangHo - ���ΰ��� ��ų�� �ߵ��ϸ� True �̴�
//};
//Skill_Set s_Skill_Set;

#define	TOWN (m_nFieldId/100 == 8)
#define	FULL_NEED_FRAME_HP 750
#define	FULL_NEED_FRAME_MP 750


#include "CharacterTable.h"

struct CommandSkill{
	short name;			//��ų Ŀ�ǵ� �̸�
	short count;		//��ų�� Ŀ�ǵ� ��
	short c_ins_Skill[5];		//��ų Ŀ�ǵ� ����
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
	int STR;	//��  -�˻� ���ݷ�(�ǳ���80%) , ����(70%)
	int DEX;	//��ø-�ǳ� ���ݷ�(100%) , ȸ��,ũ��
	int CON;	//ü��-�����, ����(30%),����� ȸ����
	int INT;	//����-������ ���ݷ�(�ǳ��� 130%) , ����
	int FAM;	//��-���� ���� , ����Ʈ ���� �� ���� ������� ��ȭ �ʿ�
	int POINT;	//��-���� ���� , ����Ʈ ���� �� ���� ������� ��ȭ �ʿ�
// 	int JAB_KNIFE;	//�˻� - ���� ���� �����ϴٸ� true
// 	int JAB_GUN;	//�ѻ� - ���� ���� �����ϴٸ� true
// 	int JAB_MAGIC;	//���� - ���� ���� �����ϴٸ� true
};
struct HeroStatus{
	int LIFE;			//���� 0 �� �Ǹ� �״´�.
	int LIFE_MAX;			//���� 0 �� �Ǹ� �״´�.
	int MANA;			//���� 0 �� �Ǹ� ��ų�� ������.
	int MANA_MAX;			//���� 0 �� �Ǹ� ��ų�� ������.

	int EXP;			//���� 0 �� �Ǹ� ��ų�� ������.
	int EXP_MAX;			//���� 0 �� �Ǹ� ��ų�� ������.
	int LEVEL;			//���� 0 �� �Ǹ� ��ų�� ������.

	int ATTACK_MAX[3];		//Į,��,�� ���ݷ�
	int ATTACK_MIN[3];		//Į,��,�� ���ݷ�
	int DAMAGE;			//���Ŀ� ���� ��뿡�� �������� Ÿ���� �ִ� ��ġ
	int DEBUFF;			//����1ȸ���� ������� ���Ǿ� ����ȴ�
	int DEFENSE;		//���� ���� ����� ��꿡 ���� ��� ��ġ(���ΰ��� ����/�̰��� �� �÷�����)
	int DEFENSE_PER;	//�������� �ڵ� ��� ��� ������ ��� % (�������� �������� ����)
	int CRITICAL;		//ũ��Ƽ�� ������ �� Ȯ��
	int AVOID;			//���� ������ ���� Ȯ��
	int LIFE_RECOVERY;	//ü���� ȸ�� ��� ��ġ
	int MANA_RECOVERY;	//������ ȸ�� ��� ��ġ
	//int	ELEMENTAL;		//���Ŀ� ���� ��뿡�� �������� Ÿ���� �ִ� ��ġ
	//int	SEX;		//0: ����, 1:����
	int	Qslot[2];		//0:Bag  1:Slot

	int	MONEY;		//�����ݾ�
};
struct Damage{
	short Type;				//���ΰ��� ���� �������� Ÿ���� �����Ѵ�
	short Sum;			//���ΰ��� ���� �������� �ջ��Ѵ�
	short Direction;	//���ΰ��� X�࿡�� ��������� �и������� ����Ѵ�.
	short Bound;			//���ΰ��� ���� Ƥ Ƚ��
	short Bound_Num;		//���ΰ��� ���� Ƥ �� ������ �� (ƥ������ �ʱ�ȭ)

	short Down_Time;		//���ΰ��� ���� Ƥ �� ������ �� (ƥ������ �ʱ�ȭ)

	bool _b_Must_Decide;//�ൿ Decide�� ������������ �������� ���θ� üũ

};
struct HeroTag{
	bool act;			//SangHo - �±����̶��
	int	SEX;		//0: ����, 1:����
	int FocusHero;		//���� ��Ʈ�� ��� ����θ� �����Ѵ�
	bool OVER_SkillEffect;
	bool DOWN_SkillEffect;
	bool _b_ActionEnd;
	bool TAG_OUT;
	Damage s_Damage;
};
struct Skill{ 
	int Equip_A[3*2];	//���� ��Ƽ�� ��ų//-1�� �̽���
	int Equip_P[9];	//���� �нú� ��ų//-1�� �̽���

	int Level_A[7*3];	//��Ƽ�� ��ų����
	int Level_P[7*4];	//Į �нú� ��ų����
};
struct Skill_Set{
	bool act;	//SangHo - ��ų�� �����Ǹ�
	int Num;//��ų��ȣ (0,1,2,3,4) - ���Թ�ȣ
	int Input_Key;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
	int Skill_ID[2][3];//��ų�� ���� ID �� ���� ��ų�� ����ó���� ���ȴ�
	int Skill_LEVEL[2][3];//��ų�� ���� ID �� ���� ��ų�� ����ó���� ���ȴ�
	int Need_Mana[2][3];//��ų�� �Һ񸶳� ��ġ
	int Cool_TimeMax[2][5];//��ų�� ��Ÿ���� ���
	int Cool_TimeNow[2][5];//��ų�� ���� ��Ÿ��
	bool OVER_SkillEffect;		//SangHo - ���ΰ��� ��ų�� �ߵ��ϸ� True �̴�
	bool DOWN_SkillEffect;		//SangHo - ���ΰ��� ��ų�� �ߵ��ϸ� True �̴�
};
struct ItemBag{
	int Data0;		//�������� �ε����� �÷�,���� ����
	//�����ε���(2),��������Ʈ�ε���(2), �ȷ�Ʈ(1), ������ID(4)

	int Data1;	//�������� ���� - �����ۿ����� �ؼ��ϴ� ����� �޶�����
	//����3(2),����2(2),����1(2),���λ�(2),���(1)

	int Data2;	//�������� �߰� ���� - �����ۿ����� �ؼ��ϴ� ����� �޶�����
	//��ȭ(2),���Ƚ�ũ��(2)
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
	int must_X;	//�̵��ؾ��� X
	int must_Y;	//�̵��ؾ��� Y
	int must_Action;//���ؾ��ϴ� �ൿ
	int must_Look;//���ؾ��ϴ� �ൿ
};
////////////////////STATE///////////////////////////////


class Character	
{
public:

	

	Character(bool Woman, int b_direction_R, void* s_ASpriteSet);
	~Character();


	//�˾� UI�� ���� ��������
	static HeroAbility s_Ability[2];
	static HeroStatus s_Status[2];
	static HeroTag s_HeroTag;//������� �±׽� ���Ǵ� ���� ����

	
	static Skill s_Skill;
	static Skill_Set s_Skill_Set;

	static ItemBag s_ItemEquip[2][7];//���� ������
	static ItemAbility s_ItemAbil[2][7];//���� �������� �ɷ�

	static ItemBag s_ItemSlot[4];//���� ����
	static ItemBag s_ItemBag[4][32];//���Դ� �κ�
	static ItemBag s_ItemPick;//�Ⱦ� ����

	static ItemBag s_ItemShop[24];//���� �κ�
////////////////////////////////////////////////////////////////////////////////////////

	static MustAction s_MustAction;
	static class ASprite*	_spr_Hero_W;				//��������Ʈ - ����� ��
	static class ASprite*	_spr_Hero_M;				//��������Ʈ - ����� ��

	class ASprite*	_spr_Skill[2][3];		//��������Ʈ - ����� ��ų 2x3��

	class ASpriteInstance*	_ins_Hero;			//�ν��Ͻ� - �����
	class ASpriteInstance*	_ins_Hero_clone;	//�ν��Ͻ� - �±����� ������� �ൿ ������ü
	class ASpriteInstance*	_ins_Skill_clone[2];		//�ν��Ͻ� - ����� ��ų 5��

	class ASpriteInstance*	_ins_Debuff;	//�ν��Ͻ� - �����
	class ASpriteInstance*	_ins_Skill[2][3][2];		//�ν��Ͻ� -{��,��] [����� ��ų 3��] [��,��]
////////////////////////////////////////////////////////////////////////////////////////


	struct ASpriteSet{//���� ��������Ʈ ����
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	struct Queue{
		int full[5];		//ťǮ
		int tick;			//TickŸ��
		short delTick;		//ť�� �ʱ�ȭ ��µ� ���� �ɸ��� TickŸ��
		short count;		//ťǮ �ε��� ī����
	};
	Queue s_KeyQueue;

	

	struct Debuff{
		short All;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
		short stack[3][2];	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
		short color;//�����̻� �÷�����ġ
	};
	Debuff s_Debuff;

	struct weapon_Switch{
		bool act;				//Ȱ������
		short next_Event;		//��� ����ġ�� ������ �̾����� ��ų
		short nextWeapon;		//��� ����ġ�� ������ �ٲ����� ����

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

	struct Bullet_Eff{//�߻��� ��ų ����Ʈ
		bool act;	//SangHo - ��ų�� �����Ǹ�
		bool LVup_ActionEnd;
		short LVupEff_Num;
		class ASpriteInstance*	Bullet_Eff_Ins;
	};
	/*
	#��ų5(����ź)
	6 - ùź=8������ x55
	7 - ��°ź=11������x55
	8 - ��°ź=14������x55

	@��
	#��ų1
		0 - �ҷ�1=8������ x26
		1 - �ҷ�2=12������ x26
		2 - �ҷ�3=15������ x26
		3 - �ҷ�4=18������ x26
		4 - �ҷ�5=21������ x26
	#��ų2= 
		5 - 0������ x0  ��ǳ���ӽð� 22�����Ӱ�

	#��ų6
		6 - 5������ x26  ���ӽð� 32�����Ӱ�
	#��ų7
		7 - 0������ x0 31�����Ӱ�
		8 - 0������ x0 31�����Ӱ�
		9 - 0������ x0 31�����Ӱ�
	*/
#define	BULLET_MAX 10
	Level_Eff s_Bullet_Eff[BULLET_MAX];
	Level_Eff s_Knife_Eff[3];//K1,K2,K3 ,Back_E , Front_E
	bool	_b_Knife_ActionEnd;		//SangHo - ���ΰ��� �׼��� �����ߴٸ� True �̴�
	int	_b_Knife_SetNum;		//SangHo - ���ΰ��� �׼��� �����ߴٸ� True �̴�

	struct Throw{
		bool ThrowPossible;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
		bool act;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
		int ThrowNum;	//SangHo - ���ΰ��� ��Ⱑ �����ϴٸ�
		// 0 - �Ϲ����   1 - 1�����    2 - 2�����
	};
	Throw s_Throw;

	struct Event_Rect{//SangHo - ���ΰ��� �̺�Ʈ ����
		int X1;
		int Y1;
		int X2;
		int Y2;
		int W;
		int H;
		int Direction;
	};Event_Rect s_Event_Rect;






	byte			_b_JabNum;			//SangHo - ������ȣ 0,1,2
	int				_m_stackZ;			//SangHo - Y ���� ��ǥ
	int				_m_actNum;			//SangHo - ���ΰ� �ɸ����� �׼� ���°�
	int				_b_LookRight;		//SangHo - ���ΰ��� �������� ���������� True �̴�
	bool			_b_ActionEnd;		//SangHo - ���ΰ��� �׼��� �����ߴٸ� True �̴�
	
	int _m_Hero_AttackNum;
	int _move_Order;
	

	bool _b_Key_Nullity;	//������� Ű �Է��� ���������� �����Ѵ�.
	bool _b_Key_Protect;	//������ �׼��� ������ ������ ��ȣ�� _move_Order���� ������
	bool _b_Hero_Protect;	//������ �׼��� ������ ������ ���ΰ��� ��ȣ���� �Ҷ�

	int _m_dashRepeat;//�뽬 �ݺ�Ƚ��

	int NUMBER;//���������� �����ϴ� ��ġ

	bool Critical;//���������� �����ϴ� ��ġ

	Position3D	m_Hero_Pos;		//���ΰ��� �� ������
	Physics*	m_Hero_Physics; //���ΰ��� 

	
	int m_HEADTOP;//���ΰ� �Ӹ������

	
	int _m_test;//�����





	






	void KeyEvent(int m_keyCode, int m_keyRepeat);
	void Process();
	void Paint();






private:
	//KeyEvent
	int		Event_command();
	int		Event_move(int m_keyCode,int m_keyRepeat);							//�̺�Ʈ�� �����Ҵ� �� Ű �������� �ݿ��� ���� �κ�
	int		Event_skill(int m_keyCode,int m_keyRepeat,int m_actNum);	//�ѹ��� Ű �Է����� �ִ� ������� �ִϸ��̼��� ���ع����ʴ� �̺�Ʈ��

	//Process
	void	Recovery();														//�� �����Ӹ��� �ڵ������� �������� ����
	int		SetDamageDecide(ASpriteInstance*	_ins_Hero,Damage& s_Damage);													//SangHo - �������� ���� �̺�Ʈ ó�� 
	void	SetActionDecide(int m_actNum);

	//Paint
	void	Paint_Debuff(int drawX,int drawZ);						// debuf �����϶�
	void	Paint_Knife();											// ȣ�� ������ ���� �����϶�
	void	Paint_Bollet();											// �߻��� ��ų ����Ʈ �׸���
	void	Paint_LevelUp();											// ������ ����Ʈ�� �׸���

	//ETC
	bool	Check_command(int m_keyCode, int m_keyRepeat);					//�׼� Ŀ�ǵ带 �����ϴ� ť����
	bool	Check_skill_impossible(int m_skillnum);									//��ų ��� ���ɿ��θ� �Ǵ�
	//int		Check_jab(int m_Jab_Knight,int  m_Jab_Gunner,int  m_Jab_Magi);
	
	int		Check_weapon(int m_Must_Weapon , int m_if_true_set_action );
	int		Set_skill_chain(int chain_Num, int m_keyCode, int chain_Key, int skill_Now, int skill_Next, int skill_Stop);
	void	Set_left_right(int b_direction_R);
	void	Set_fly_motion(ASpriteInstance*	_ins_Hero,Damage& p_Damage,Position3D& p_Position3D);
	void	Check_Sound();
	

	

public://G Field
	
	static int	Check_sex(int m_Woman,int  m_Man);
	static void	Set_state_calculate();//���� ��ġ ��ȯ���� ���� �������� ������ �ʿ��ҽ� ����
	static void InitCostume();
	static void ChangeCostume(ASprite* spr, int part,int index,int pal);

	static bool	Set_MustAction(int x, int y,int Action,int Look);//���ΰ��� ���������� ���ؾ� �� �ൿ�� ���Ѻκ�
	
	
	void	Init_Skill();//��ų���� �ʱ�ȭ�� ó��
	void ReceiveAttack(Position3D& _Power);//�����ڿ��Լ� ������ �޾����� ó�����ִ� ����

	void RCV_Damage(int monDamage); //�������� �޾�����
	int SND_Damage(int monLevel, int monElemental , int monDefense, int D_index);//������ �Ҷ�

	void RCV_Debuff(int Debuff_Type); //������� �޾�����
	int SND_Debuff(int Attack_Type);//������� ���Ҷ�

	int Set_Exp(int _Exp);//����ġ ������ġ
	int CloneCopy();//���� ���ϰ� �ִ� �ൿ�� ��� Ŭ�п��� ī���Ѵ�

	void InitCharPos(int x, int y, int Look = 0);


	static int Get_Skill(int passive_Num);//��Ƽ�� ��ų ���޾ƿ���


	int	m_nFieldId;//����ID




private:

};

#endif