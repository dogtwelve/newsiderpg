#include "EventManager.h"

EventManager* EventManager::pEventManager = NULL;

//--------------------------------------------------------------------------------------
EventManager::EventManager()
//--------------------------------------------------------------------------------------
{
	//	�ؽ�Ʈ ���� �ε����ش�.
	pEvtText = _SUTIL->LoadTextPack(PACK_DATA_TALK, DATA_TALK_EVENT);
	m_bIsLinkEventManager = false;
}


//--------------------------------------------------------------------------------------
EventManager::~EventManager()
//--------------------------------------------------------------------------------------
{
	SUTIL_FreeTextPack(pEvtText);
}


//--------------------------------------------------------------------------
EventManager* EventManager::GetInstance()
//--------------------------------------------------------------------------
{
	if(NULL == pEventManager)
	{
		pEventManager = new EventManager();
	}

	return pEventManager;
}

//--------------------------------------------------------------------------
void EventManager::FreeInstance()
//--------------------------------------------------------------------------
{
	if(NULL != pEventManager)
	{
		delete pEventManager;
		pEventManager = NULL;
	}
}


//--------------------------------------------------------------------------
void EventManager::SetEvtData(int idx)
//--------------------------------------------------------------------------
{
	//	�ļ��� ���� �˻��� ��������.
	for(int loop = 0; loop < pEvtText->nTextNum; loop++)
	{
		if('S' != pEvtText->nText[loop][0])	{continue;}
//		if('c' != pEvtText->nText[loop][1])	{continue;}		//	�ӵ������ ���� ���ش�.
//		if('e' != pEvtText->nText[loop][2])	{continue;}
//		if('n' != pEvtText->nText[loop][3])	{continue;}
//		if('e' != pEvtText->nText[loop][4])	{continue;}

		if(idx != ( (pEvtText->nText[loop][6]-'0')*100 +
					(pEvtText->nText[loop][7]-'0')*10 +
					(pEvtText->nText[loop][8]-'0')*1 ))	{continue;}

		//	�� ���� �ε����� �Ѱ��ش�.
		m_nParserIndex = loop;	
		break;
	}

	//	Ȱ��ȭ�����ش�.
	m_bIsLinkEventManager = true;
}


//--------------------------------------------------------------------------
int EventManager::UpdateEvtParser()
//--------------------------------------------------------------------------
{
	if(false == m_bIsLinkEventManager)	{return 0;}

	m_nParserIndex++;

	//	ó���� �ε����� �ѱ��.
	if(m_nParserIndex >= pEvtText->nTextNum)	{return 0;}

	int idx1 = 0;
	int idx2 = 0;

	switch(pEvtText->nText[m_nParserIndex][0])
	{
		case 'S':	//	scene(???) ���� ���̹Ƿ� �����Ų��.
		case 'E':	//	end(???) ���ϰ��
		//-----------------------------------------------------------
		{
			//	Ȱ��ȭ�����ش�.
			m_bIsLinkEventManager = false;
			return 0;
		}
		case 'C':	//	cinema(???) ���׸��� �����Ų��.
		//-----------------------------------------------------------
		{
//			return UpdateEvtParser();

			idx1 = 	(pEvtText->nText[m_nParserIndex][7]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][8]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][9]-'0')*1  ;

			idx2 = 	(pEvtText->nText[m_nParserIndex][11]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][12]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][13]-'0')*1  ;

			//	 nams test
			idx1 = 0;

			ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
			ADD_EVENT_MSG(EVT_START_CINEMA, 10, idx1, idx2);
			return EVT_START_CINEMA;

		}
		case 'T':	//	talk(???) ��縦 �����Ѵ�.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][5]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][6]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][7]-'0')*1  ;

			idx2 = 	(pEvtText->nText[m_nParserIndex][9]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][10]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][11]-'0')*1  ;

			ADD_EVENT_MSG(EVT_TALK_STARTEVT, 0, idx1, idx2);
			return EVT_TALK_STARTEVT;
		}
		case 'M':	//	map(???) ���� �����ų ���� �̸��̴�.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][4]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][5]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][6]-'0')*1  ;

			ADD_EVENT_MSG(EVT_CHANGE_STAGE, 0, idx1);
			return EVT_CHANGE_STAGE;
		}
		case 'P':	//	prologue(???) ���� �����ų ���� �̸��̴�.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][9]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][10]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][11]-'0')*1  ;

			ADD_EVENT_MSG(EVT_PROLOGUE, 0, idx1);
			return EVT_PROLOGUE;
		}
		case 'W':	//	watch(????) Ÿ�̸��� �ð��̴�.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][6]-'0')*1000 +
					(pEvtText->nText[m_nParserIndex][7]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][8]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][9]-'0')*1		;

			idx1 *= 10;
			ADD_EVENT_MSG(EVT_WATCH, 0, idx1);
			return EVT_WATCH;
		}
		case 'L':	//	locate(????) ĳ������ ��ġ�� �����Ѵ�.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][7]-'0')*1000 +
					(pEvtText->nText[m_nParserIndex][8]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][9]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][10]-'0')*1		;

			idx2 = 	(pEvtText->nText[m_nParserIndex][12]-'0')*1000 +
					(pEvtText->nText[m_nParserIndex][13]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][14]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][15]-'0')*1		;

			
			ADD_EVENT_MSG(EVT_SET_CAHRPOS, 0, idx1, idx2, SDIR_RIGHT);
			return EVT_SET_CAHRPOS;
		}
//		case 'Q':	//	quest(???) ����Ʈ�� �˸���.
//		//-----------------------------------------------------------
//		{
//			idx = 	(pEvtText->nText[m_nParserIndex][6]-'0')*100 +
//					(pEvtText->nText[m_nParserIndex][7]-'0')*10 +
//					(pEvtText->nText[m_nParserIndex][8]-'0')*1  ;
//
//			break;
//		}
		default:
		//-----------------------------------------------------------
		{
			//error
			break;
		}
	}

	return 0;
}


////--------------------------------------------------------------------------
//void EventManager::AddMessage(int _MagType, int _delay, int _param1, int _param2, int _param3)
////--------------------------------------------------------------------------
//{
//	S_EVENT_MSG* tmpMsg = GL_NEW S_EVENT_MSG();
//
//	tmpMsg->m_MsgType = _MagType;
//	tmpMsg->m_nDelay = _delay;
//	tmpMsg->param[0] = _param1;
//	tmpMsg->param[1] = _param2;
//	tmpMsg->param[2] = _param3;
//
//	if((pMsgList)->now == (pMsgList)->head)
//	{
//		pMsgList->Insert_next(tmpMsg);
//		MovePre(pMsgList);
//	}
//	else
//	{
//		//	�޼��� �߰��� ���� ��찡 �����.
//		pMsgList->Insert_prev(tmpMsg);
//		MoveNext(pMsgList);
//	}
//}
