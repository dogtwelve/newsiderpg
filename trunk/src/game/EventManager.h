#ifndef __EVENT_MANAGER_H_
#define __EVENT_MANAGER_H_

//	AI와 상호참조를 한다.
#include	"WIPIHeader.h"
#include	"Device.h"
#include	"List.h"
#include	"SUTIL.h"
#include	"Message.h"

//	DEFINE EVENT MESSAGE
//#define EVT_SCREEN_FADE_OUT		1			//	화면을 페이드 아웃시킨다.


#define INIT_EVENT()						(EventManager::GetInstance())
#define EventManager_FreeInstance			INIT_EVENT()->FreeInstance

#define PARSER_EVENT						INIT_EVENT()->UpdateEvtParser
#define SET_EVENT							INIT_EVENT()->SetEvtData
#define GET_EVENT_STATE()					INIT_EVENT()->m_bIsLinkEventManager



//#define GET_EVENT_MSG_STRUCT()				SMSG->pMsgList
//#define RELEASE_EVENT_MSG()					SMSG->FreeInstance()

typedef struct _S_EVENTMGR
{
	int	m_MsgType;
	int param[3];
}S_EVENTMGR;


class EventManager
{
private:
	static EventManager* pEventManager;
	EventManager();

public:
	S_EVENTMGR pMsg;

	~EventManager();
	static EventManager* GetInstance();
	void FreeInstance();

	struct _TEXT_PACK*		pEvtText;
	int m_nParserIndex;						//이벤트 진행 상황
	bool m_bIsLinkEventManager;				//이벤트 진행 상황
	//List2< S_EVENTMGR_MSG* >		*pEvtList;

	void SetEvtData(int idx);
	int UpdateEvtParser();
};


#endif