#ifndef __QUEST_H_
#define __QUEST_H_

//	AI와 상호참조를 한다.
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
// 이벤트 호출자 고유 define 값(아이템, 필드, NPC)
#define NPC_CALL_kail				1007//트레져 헌터 카일
#define NPC_CALL_kaien				1022//카이엔
#define NPC_CALL_citizen1			1017//시민1
#define NPC_CALL_citizen2			1018//시민2
#define NPC_CALL_citizenK			1013//시민k
#define NPC_CALL_scholar  			1011//고고학자
//---------------------------------------------
#define FIELD_CALL_caveOpen			2000//동굴 입구
#define FIELD_CALL_smallTown		2001//스몰 타운
#define FIELD_CALL_forest1			2002//초원 첫번째 비오는 필드
#define FIELD_CALL_forest2			2003//초원 두번째 비오는 필드
//---------------------------------------------
#define ITEM_CALL_tntBoom				9000//폭약
#define ITEM_CALL_medal					9001//메달
#define ITEM_CALL_crystal				9002//자수정
#define ITEM_CALL_diary					9003//일지
//---------------------------------------------
#define TIMER_CALL_end					9999//타이머 이벤트

//-------------------퀘템 수집 갯수--------------------------
#define MAX_tntBoom				5//폭약
#define MAX_medal				10//메달
#define MAX_crystal				5//자수정
#define MAX_diary				1//일지




// 메인 퀘스트 고유 define 값
#define MAIN_QUEST_findOpen				0	//동굴 입구를 찾아라!!
#define MAIN_QUEST_openDoor				1	//동굴 입구를 열어라!
#define MAIN_QUEST_findKail				2	//트레져 헌터 카일을 찾아라
#define MAIN_QUEST_oldMedal				3	//스몰 타운 초원 에서 낡은 메달 10개를 구한뒤 카일에게로 돌아가라
#define MAIN_QUEST_callKail				4	//카일의 호출
#define MAIN_QUEST_goKaien				5	//카이엔 에게 소개장을 전달 하라
#define MAIN_QUEST_goCitizen1			6	//엘시안 문명의 정보를 수집하라 시민 1
#define MAIN_QUEST_goCitizen2			7	//엘시안 문명의 정보를 수집하라 시민 2
#define MAIN_QUEST_goCitizenK			8	//엘시안 문명의 정보를 수집하라 시민 K
#define MAIN_QUEST_findCrystal			9	//자수정을 구해와서 K씨와 대화하라 
#define MAIN_QUEST_returnKaien			10	//카이엔 에게 돌아가라
#define MAIN_QUEST_goScholar			11	//고고학자를 찾아라
#define MAIN_QUEST_findDiary			12	//잃어버린 일지를 찾아라
#define MAIN_QUEST_goSmallTown			13	//일지를 돌려주자, 서브 - 미들 타운으로 가라
#define MAIN_QUEST_findSiz1				14	//일지를 돌려주자, 서브 - 바위를 부셔라
#define MAIN_QUEST_findSiz2				15	//일지를 돌려주자, 서브 - 시즈에게 가라
//#define MAIN_QUEST_012					12	//카이엔에게 돌아가라
//#define MAIN_QUEST_013					13	//신전을 찾아라
//#define MAIN_QUEST_013					13	//1분간 버텨라
//#define MAIN_QUEST_013					13	//골렘을 쓰러뜨려라

// 서브 퀘스트 고유 define 값
#define SUB_QUEST_000		0//동굴 입구를 찾아라!!
#define SUB_QUEST_001		1//동굴 입구를 열어라!
#define SUB_QUEST_002		2//트레져 헌터 카일을 찾아라
#define SUB_QUEST_003		3//스몰 타운 초원 에서 낡은 메달 10개를 구하라!
#define SUB_QUEST_004		4//카일 에게 돌아가라!
#define SUB_QUEST_005		5//카이엔 에게 소개장을 전달 하라
#define SUB_QUEST_006		6//엘시안 문명의 정보를 수집하라
#define SUB_QUEST_007		7//고고학자를 찾아라
#define SUB_QUEST_008		8//일지를 찾아라!
#define SUB_QUEST_009		9//신전의 실마리를 찾아라
#define SUB_QUEST_010		10//카이엔에게 돌아가라
#define SUB_QUEST_011		11//신전을 찾아라
#define SUB_QUEST_012		12//1분간 버텨라
#define SUB_QUEST_013		13//골렘을 쓰러뜨려라

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

	int		m_nMainQuestidx;//메인퀘스트 인덱스
	byte	m_nSubQuestidx[SUBQUEST_MAX];//서브

//	int		ProcessEventCode(int code, int dummy = 0);
//	void	CheckQuest();



//	struct _TEXT_PACK*		pEvtText;
//	int m_nParserIndex;						//이벤트 진행 상황
//	bool m_bIsLinkEventManager;				//이벤트 진행 상황
	//List2< S_EVENTMGR_MSG* >		*pEvtList;

//	void SetEvtData(int idx);
//	int UpdateEvtParser();
//	void Init();
};


#endif