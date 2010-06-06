#ifndef _FIELD_OBJECT_
#define _FIELD_OBJECT_

#include "SUtil.h"
#include "VEvent.h"



class FieldObject : public VEvent
{
public:
	FieldObject();
	virtual ~FieldObject();
	
	struct ASpriteSet{//공용 스프라이트 묶음
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};ASpriteSet* s_ASpriteSet;

	int m_nEvtDelay;
	int m_nSaveEvtCode;			//	이벤트시 실행해야될 이벤트 번호

	int m_nNextAction;
	int m_nAction;

	int m_nImgIdx;
	int m_nXPos;
	int m_nYPos;
	int m_nXCamAngle;

	ASpriteInstance* m_Asins;

	void ResvAction(int nNextAction);
	void SetAngle(int x);

	virtual void SetAction()=0;
	virtual void Initialize(int nDummy1, int nDummy2)=0;
	virtual void Release()=0;
	virtual void Process()=0;
	virtual void Paint()=0;
	virtual int  CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5)=0;
	virtual	void ReadyObject(void* _s_ASpriteSet)=0;

};


//--------------------------------------------------------------------------------
#define ACT_NPC_NULL		0
#define ACT_NPC_STAND		1
#define ACT_NPC_RUN			2
#define ACT_NPC_TALK		3	//	안쓰일지도 모름
#define ACT_NPC_MAX			4


#define NPC_KAIL			10
#define NPC_KAIEN			9

class Npc : public FieldObject
{
public:
	Npc(int idx, int x, int y);
	~Npc();

	ASpriteInstance* m_Questionins;
	int nTimer;
	int nNpcHeight;
	int nQuestionNum;

	int m_nUsingImgIdx[ACT_NPC_MAX];

	void SetAction();
	void Initialize(int nDummy1, int nDummy2);
	void Release();
	void Process();
	void Paint();
	int  CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5);
	void ReadyObject(void* _s_ASpriteSet);

private:
};


//--------------------------------------------------------------------------------
#define ACT_CRUSH_OBJ_NULL		0
#define ACT_CRUSH_OBJ_STAND		1
#define ACT_CRUSH_OBJ_DESTROY	2
#define ACT_CRUSH_OBJ_MAX		3

class CrushObj : public FieldObject
{
public:
	CrushObj(int idx, int x, int y);
	~CrushObj();

	int m_nUsingImgIdx[ACT_CRUSH_OBJ_MAX];
	int m_nHp;

	void SetAction();
	void Initialize(int nDummy1, int nDummy2);
	void Release();
	void Process();
	void Paint();
	int  CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5);
	void ReadyObject(void* _s_ASpriteSet);

private:
};


#endif



