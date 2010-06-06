#ifndef __EVENT_MANAGER_H_
#define __EVENT_MANAGER_H_

//	AI�� ��ȣ������ �Ѵ�.
#include	"WIPIHeader.h"
#include	"Device.h"
#include	"List.h"
#include	"SUTIL.h"
#include	"Message.h"

//	DEFINE EVENT MESSAGE
//#define EVT_SCREEN_FADE_OUT		1			//	ȭ���� ���̵� �ƿ���Ų��.


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
	int m_nParserIndex;						//�̺�Ʈ ���� ��Ȳ
	bool m_bIsLinkEventManager;				//�̺�Ʈ ���� ��Ȳ
	//List2< S_EVENTMGR_MSG* >		*pEvtList;

	void SetEvtData(int idx);
	int UpdateEvtParser();
};


#endif