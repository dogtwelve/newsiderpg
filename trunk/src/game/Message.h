#ifndef __MESSAGE_H_
#define __MESSAGE_H_

//	AI와 상호참조를 한다.
#include "WIPIHeader.h"
#include	"Device.h"
#include "List.h"

//	DEFINE EVENT MESSAGE
#define EVT_NULL				0			//	없음
#define EVT_SCREEN_FADE_OUT		1			//	화면을 페이드 아웃시킨다.
#define EVT_SCREEN_FADE_IN		2			//	화면을 페이드 인스킨다.
#define EVT_CHANGE_STAGE		3			//	스테이지를 바꾼다.
#define EVT_START_CINEMA		4			//	씨네마를 돌린다.
#define EVT_END_CINEMA			5			//	씨네마를 끝낸다.
#define EVT_INIT_GAME			6			//	최초 시작시 호출한다.
#define EVT_PROLOGUE			7			//	프롤로그를 호출한다.
#define EVT_WATCH				8			//	시간이벤트
#define EVT_SET_CAHRPOS			9			//	캐릭터의 위치 지정 이벤트

//------100번 부터는 지워진다.(필드 체인지시)
#define EVT_DELETE_WHEN_CHANG_STAGE		100	//	지우기 시작하는 번호
#define EVT_ADD_MONSTER			101			//	몬스터를 갱신한다.
#define EVT_GAME_KEYEVENT		102			//	주인공이 주위 사물을 클릭했을때 나오는 이벤트
#define EVT_CINEMA_ADDEVT		103			//	씨네마돌릴시 이벤트를 다시 호출해준다.
#define EVT_TALK_STARTEVT		104			//	대사를 시작할시 올라온다.
#define EVT_TALK_ENDEVT			105			//	대사가 끝났을시 올라온다.


#define INIT_MESSAGE()						(Message::GetInstance())

#define CLEAR_EVENT_MSG						INIT_MESSAGE()->ClearMessage
#define ADD_EVENT_MSG						INIT_MESSAGE()->AddMessage
#define GET_EVENT_MSG_STRUCT()				INIT_MESSAGE()->pMsgList
#define Message_FreeInstance				INIT_MESSAGE()->FreeInstance



typedef struct _S_EVENT_MSG
{
	int m_nDelay;
	int	m_MsgType;
	int param[3];
}S_EVENT_MSG;


class Message	
{

public:
	~Message();
	static Message* GetInstance();
	void FreeInstance();

	List2< S_EVENT_MSG* >		*pMsgList;

private:
	static Message* pMessage;
	Message();


public:
	void AddMessage(int m_MagType, int delay=0, int param1=0, int param2=0, int param3=0);
	void ClearMessage();
};


#endif