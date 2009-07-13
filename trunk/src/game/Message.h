#ifndef __MESSAGE_H_
#define __MESSAGE_H_

//	AI�� ��ȣ������ �Ѵ�.
#include "WIPIHeader.h"
#include	"Device.h"
#include "List.h"

//	DEFINE EVENT MESSAGE
#define EVT_NULL				0			//	����
#define EVT_SCREEN_FADE_OUT		1			//	ȭ���� ���̵� �ƿ���Ų��.
#define EVT_SCREEN_FADE_IN		2			//	ȭ���� ���̵� �ν�Ų��.
#define EVT_CHANGE_STAGE		3			//	���������� �ٲ۴�.
#define EVT_START_CINEMA		4			//	���׸��� ������.
#define EVT_END_CINEMA			5			//	���׸��� ������.
#define EVT_INIT_GAME			6			//	���� ���۽� ȣ���Ѵ�.
#define EVT_PROLOGUE			7			//	���ѷα׸� ȣ���Ѵ�.
#define EVT_WATCH				8			//	�ð��̺�Ʈ
#define EVT_SET_CAHRPOS			9			//	ĳ������ ��ġ ���� �̺�Ʈ

//------100�� ���ʹ� ��������.(�ʵ� ü������)
#define EVT_DELETE_WHEN_CHANG_STAGE		100	//	����� �����ϴ� ��ȣ
#define EVT_ADD_MONSTER			101			//	���͸� �����Ѵ�.
#define EVT_GAME_KEYEVENT		102			//	���ΰ��� ���� �繰�� Ŭ�������� ������ �̺�Ʈ
#define EVT_CINEMA_ADDEVT		103			//	���׸������� �̺�Ʈ�� �ٽ� ȣ�����ش�.
#define EVT_TALK_STARTEVT		104			//	��縦 �����ҽ� �ö�´�.
#define EVT_TALK_ENDEVT			105			//	��簡 �������� �ö�´�.


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