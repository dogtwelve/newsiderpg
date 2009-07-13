#include "Message.h"

Message* Message::pMessage = NULL;

//--------------------------------------------------------------------------------------
Message::Message()
//--------------------------------------------------------------------------------------
{
	pMsgList = GL_NEW List2<S_EVENT_MSG*>();
}


//--------------------------------------------------------------------------------------
Message::~Message()
//--------------------------------------------------------------------------------------
{
	InitList(pMsgList);
	while(NotEndList(pMsgList))
	{
		SAFE_DELETE(GetData(pMsgList));
		pMsgList->Delete();
	}

	SAFE_DELETE(pMsgList);
}


//--------------------------------------------------------------------------
Message* Message::GetInstance()
//--------------------------------------------------------------------------
{
	if(NULL == pMessage)
	{
		pMessage = new Message();
	}

	return pMessage;
}

//--------------------------------------------------------------------------
void Message::FreeInstance()
//--------------------------------------------------------------------------
{
	if(NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}
}


//--------------------------------------------------------------------------
void Message::AddMessage(int _MagType, int _delay, int _param1, int _param2, int _param3)
//--------------------------------------------------------------------------
{
	S_EVENT_MSG* tmpMsg = GL_NEW S_EVENT_MSG();


	tmpMsg->m_MsgType = _MagType;
	tmpMsg->m_nDelay = _delay;
	tmpMsg->param[0] = _param1;
	tmpMsg->param[1] = _param2;
	tmpMsg->param[2] = _param3;

	if((pMsgList)->now == (pMsgList)->head)
	{
		pMsgList->Insert_next(tmpMsg);
		MovePre(pMsgList);
	}
	else
	{
		//	메세지 중간에 끼는 경우가 생긴다.
		pMsgList->Insert_prev(tmpMsg);
		MoveNext(pMsgList);
	}
}


//--------------------------------------------------------------------------
void Message::ClearMessage()
//--------------------------------------------------------------------------
{
	InitList(pMsgList);
	while(NotEndList(pMsgList))
	{
		if(EVT_DELETE_WHEN_CHANG_STAGE <= GetData(pMsgList)->m_MsgType)
		{
			SAFE_DELETE(GetData(pMsgList));
			pMsgList->Delete();
		}
		else
		{
			MoveNext(pMsgList);
		}
	}
}