#include "SUtil.h"
#include "ASprite.h"
#include "ASpriteInstance.h"
#include "Character.h"

#ifndef		__FIELD_UI_H_
#define		__FIELD_UI_H_


#define MON_NUM		0
#define MON_CRI_NUM	1
#define HERO_NUM	2
#define HERO_CRI_NUM	3
#define HEAL_NUM	4


#define NO_FACE			0
#define FACE_00			1
#define FACE_01			2


typedef struct _SKILL_EFT
{
	int lifeTime;
	class ASpriteInstance*	pSkillEftAsIns;
}SKILL_EFT;

typedef struct _MON_VIEW_UI
{
	int lifeTime;
	int maxHp;
	int nowHp;
	int name;
	int level;
	int idx;
	int elemental;
}MON_VIEW_UI;

typedef struct _DAMAGE_NUM_EFT
{
	int x;
	int y;
	int z;
	int lifeTime;
	int damageValue;
	int start_ImgIndex;
}DAMAGE_NUM_EFT;



class FieldUi
{
public:
	FieldUi(void* s__ASpriteSet);
	//FieldUi(ASpriteInstance* _pFieldAsIns);
	~FieldUi();

	struct ASpriteSet{//���� ��������Ʈ ����
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	int nState;

	void Process();
	void Paint();
	void GetMessage();

	


	struct TalkBox{// ��ȭâ�� ������������ ������ �˷���
		bool View;//������â�� �������� ����	
		int index;//���� �ؽ�Ʈ�� Y����
		int count;//���� ���� �ִϸ��̼�
		
		int Emotion;//X
		int Line;//X
		int LineMAX;//X
		int EventNum;
		int Face_Now;
		int Face_Next;

		class ASprite* _spr_TalkBox;
		class ASprite* FaceNowAs;
		class ASprite* FaceNextAs;
		struct _TEXT_PACK*	pText;
	};TalkBox s_TalkBox;

	struct MAIN_Q{// ��ȭâ�� ������������ ������ �˷���
		bool CENTER;//�Ϸ���Ʈ���� ��� ���������� �ؽ�Ʈ	
		int Scene;//X
	};MAIN_Q s_Main;

	struct SUB_Q{// ��ȭâ�� ������������ ������ �˷���
		bool Popup_Ready;//����Ʈ �������� �˾��� �������϶�
		bool Popup_Yes_No;//������â�� �������� ����
		bool Yes_No;//������â�� �������� ����	

		int village;//Y ��ũ��
		int NPC_ID;//Y ��ũ��
		int NPC_Name;//Y ��ũ��
		int QuestNum;
		int QuestSelect;

		int SameFAM;//������ ��ġ�� ��ȭ - �� �����̼� �ؽ�Ʈ
		int SameFam_MAX;//������ ��ġ�� ��ȭ - �� �����̼� �ؽ�Ʈ ����

		int Talk_ID;//Y ��ũ��
		int Talk_Num;//�Ϲ� ��ȭ�� ���������� �ߴ� ��ȭ��ȣ
	};SUB_Q s_Sub;




	class ASprite* m_pFieldUiDamageNumAs;
	

	ASpriteInstance* m_pFieldUiDamageNumAsIns;
	//class ASprite* m_pFieldUiAs;
	ASpriteInstance* m_pFieldUiAsIns;

	//class ASprite* m_pFieldEftAs;
	ASpriteInstance* m_pFieldEftAsIns;

	List2< SKILL_EFT* >			*pEftList;
	List2< MON_VIEW_UI* >		*pMonEftList;
	List2< DAMAGE_NUM_EFT* >	*pDamageNumList;
	int						m_nMonEftCurIdx;

	struct _TEXT_PACK*				pMonNameText;
	struct _TEXT_PACK*				pTalkNameText;
	struct _TEXT_PACK*				pTalkNpcNameText;


/////////////////////////////////////////  TALK  /////////////////////////////////////////////////
	void SetTalkCinema(int Scene, int Paragraph ){
		SetTalkBox(-1, Paragraph, Scene);//�ó׸� ��ȭ�� ���ѹ��� ������ ��ȣ�� �Ѿ�´�
	}
	void SetTalkNPC(int Village , int NPC){
		if(s_Sub.Talk_ID != NPC){
			s_Sub.Talk_ID = NPC;
			s_Sub.Talk_Num = 0;
		}else{
			s_Sub.Talk_Num++;
		}
		SetTalkBox(Village, NPC, -1);//NPC ��ȭ�� ���� ���� index �� �ο��ȴ�
	}
	void SetTalkBox(int Village, int index, int Scene);
	int Load_Face(int index);
	int Find_NpcStart(int NPC_ID);
	int Find_NpcRewind(int Up , int Line);
	void Set_Next_Face(int NextFace);
	void PaintTalkBox();
	int KeyTalkBox(int m_keyCode, int m_keyRepeat);
	void SetQuest(int index);
	int GetFlags(int index);//END ���� ó�������ؼ�
/////////////////////////////////////////  TALK  /////////////////////////////////////////////////



	void PaintCharInfo(int level, int NowHp, int MaxHp, int NowMp, int MaxMp, int elemental);
	void PaintComboGage(int Combo);
	void PaintMonsterInfo(int MonName, int level, int NowHp, int MaxHp, int elemental);
	void PaintSkillInfo(int* skill_id,int* coolMax,int* cooltime,int mana,int* needmana);//��ų ���� ID , ��Ÿ�� Max , ��Ÿ�� 
	void PaintPotionTagInfo(int* coolMax,int* cooltime);
	void PaintExpInfo(int NowExp, int MaxExp);

	void InsertdamageNum(int x, int y, int z, int damage, int type);	
	void InsertEffect(int x, int y, int z, int eftnum);
	void Insert_CrashEffect(int x, int y, int z, int eftnum);
	void InsertMonsterInfo(int _idx, int _name, int _level, int _nowHp, int _maxHp, int _elemental);

	void AddCombo(int comboCnt=1);

private:

	void PaintGage(int gageType, int gagewidth,int gageheight, int x, int y, int nowvalue, int maxvalue);

	void ProcessCombo();
	void PaintCombo();
	void InitCombo();
	int m_nSaveCombo;
	int m_nSaveComboMax;
	int m_nSaveComboTimer;
	int m_nBuffComboLevel;
	int m_nBuffComboTimer;
	
	//void PaintLevel(int x, int y, int level);
	void PaintNumber(ASprite* pAsIns, int numImgIdx, int value, int x, int y, int gap , int position);
};

#endif