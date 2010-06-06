#ifndef __QUEST_H_
#define __QUEST_H_

//	AI�� ��ȣ������ �Ѵ�.
#include	"WIPIHeader.h"
#include	"Device.h"
#include	"List.h"
#include	"SUTIL.h"
#include	"Message.h"


#define INIT_QUEST()					(EventQuest::GetInstance())
#define Quest_FreeInstance()			(INIT_QUEST()->FreeInstance())		

#define GET_MAINQUEST_IDX()				(INIT_QUEST()->m_nMainQuestidx)
#define INCREASE_MAINQUEST_IDX()		(INIT_QUEST()->m_nMainQuestidx+=1)

#define QUEST_NEW						(0)
#define QUEST_ING						(1)
#define QUEST_FIN						(2)
#define QUEST_END						(3)

#define SUBQUEST_MAX					(200)
#define SUBQUEST_IDX(a)					(INIT_QUEST()->m_nSubQuestidx[(a)])



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �̺�Ʈ ȣ���� ���� define ��(������, �ʵ�, NPC)
#define NPC_CALL_kail				1007//Ʈ���� ���� ī��
#define NPC_CALL_kaien				1022//ī�̿�
#define NPC_CALL_citizen1			1017//�ù�1
#define NPC_CALL_citizen2			1018//�ù�2
#define NPC_CALL_citizenK			1013//�ù�k
#define NPC_CALL_scholar  			1011//�������
//---------------------------------------------
#define FIELD_CALL_caveOpen			2000//���� �Ա�
#define FIELD_CALL_smallTown		2001//���� Ÿ��
#define FIELD_CALL_forest1			2002//�ʿ� ù��° ����� �ʵ�
#define FIELD_CALL_forest2			2003//�ʿ� �ι�° ����� �ʵ�
//---------------------------------------------
#define ITEM_CALL_tntBoom				9000//����
#define ITEM_CALL_medal					9001//�޴�
#define ITEM_CALL_crystal				9002//�ڼ���
#define ITEM_CALL_diary					9003//����
//---------------------------------------------
#define TIMER_CALL_end					9999//Ÿ�̸� �̺�Ʈ

//-------------------���� ���� ����--------------------------
#define MAX_tntBoom				5//����
#define MAX_medal				10//�޴�
#define MAX_crystal				5//�ڼ���
#define MAX_diary				1//����




// ���� ����Ʈ ���� define ��
#define MAIN_QUEST_findOpen				0	//���� �Ա��� ã�ƶ�!!
#define MAIN_QUEST_openDoor				1	//���� �Ա��� �����!
#define MAIN_QUEST_findKail				2	//Ʈ���� ���� ī���� ã�ƶ�
#define MAIN_QUEST_oldMedal				3	//���� Ÿ�� �ʿ� ���� ���� �޴� 10���� ���ѵ� ī�Ͽ��Է� ���ư���
#define MAIN_QUEST_callKail				4	//ī���� ȣ��
#define MAIN_QUEST_goKaien				5	//ī�̿� ���� �Ұ����� ���� �϶�
#define MAIN_QUEST_goCitizen1			6	//���þ� ������ ������ �����϶� �ù� 1
#define MAIN_QUEST_goCitizen2			7	//���þ� ������ ������ �����϶� �ù� 2
#define MAIN_QUEST_goCitizenK			8	//���þ� ������ ������ �����϶� �ù� K
#define MAIN_QUEST_findCrystal			9	//�ڼ����� ���ؿͼ� K���� ��ȭ�϶� 
#define MAIN_QUEST_returnKaien			10	//ī�̿� ���� ���ư���
#define MAIN_QUEST_goScholar			11	//������ڸ� ã�ƶ�
#define MAIN_QUEST_findDiary			12	//�Ҿ���� ������ ã�ƶ�
#define MAIN_QUEST_goSmallTown			13	//������ ��������, ���� - �̵� Ÿ������ ����
#define MAIN_QUEST_findSiz1				14	//������ ��������, ���� - ������ �μŶ�
#define MAIN_QUEST_findSiz2				15	//������ ��������, ���� - ����� ����
//#define MAIN_QUEST_012					12	//ī�̿����� ���ư���
//#define MAIN_QUEST_013					13	//������ ã�ƶ�
//#define MAIN_QUEST_013					13	//1�а� ���߶�
//#define MAIN_QUEST_013					13	//���� �����߷���

// ���� ����Ʈ ���� define ��
#define SUB_QUEST_000		0//���� �Ա��� ã�ƶ�!!
#define SUB_QUEST_001		1//���� �Ա��� �����!
#define SUB_QUEST_002		2//Ʈ���� ���� ī���� ã�ƶ�
#define SUB_QUEST_003		3//���� Ÿ�� �ʿ� ���� ���� �޴� 10���� ���϶�!
#define SUB_QUEST_004		4//ī�� ���� ���ư���!
#define SUB_QUEST_005		5//ī�̿� ���� �Ұ����� ���� �϶�
#define SUB_QUEST_006		6//���þ� ������ ������ �����϶�
#define SUB_QUEST_007		7//������ڸ� ã�ƶ�
#define SUB_QUEST_008		8//������ ã�ƶ�!
#define SUB_QUEST_009		9//������ �Ǹ����� ã�ƶ�
#define SUB_QUEST_010		10//ī�̿����� ���ư���
#define SUB_QUEST_011		11//������ ã�ƶ�
#define SUB_QUEST_012		12//1�а� ���߶�
#define SUB_QUEST_013		13//���� �����߷���

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//typedef struct _S_EVENTMGR
//{
//	int	m_MsgType;
//	int param[3];
//}S_EVENTMGR;


class EventQuest
{
private:
	static EventQuest* pQuest;
	EventQuest();

public:
//	S_EVENTMGR pMsg;

	~EventQuest();
	static EventQuest* GetInstance();
	void FreeInstance();

	int		m_nMainQuestidx;//��������Ʈ �ε���
	byte	m_nSubQuestidx[SUBQUEST_MAX];//����

//	int		ProcessEventCode(int code, int dummy = 0);
//	void	CheckQuest();



//	struct _TEXT_PACK*		pEvtText;
//	int m_nParserIndex;						//�̺�Ʈ ���� ��Ȳ
//	bool m_bIsLinkEventManager;				//�̺�Ʈ ���� ��Ȳ
	//List2< S_EVENTMGR_MSG* >		*pEvtList;

//	void SetEvtData(int idx);
//	int UpdateEvtParser();
//	void Init();
};


#endif