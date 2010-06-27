#include "EventManager.h"

EventManager* EventManager::pEventManager = NULL;

//--------------------------------------------------------------------------------------
EventManager::EventManager()
//--------------------------------------------------------------------------------------
{
	//	텍스트 팩을 로드해준다.
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
	//	파서로 씬을 검색해 내려간다.
	for(int loop = 0; loop < pEvtText->nTextNum; loop++)
	{
		if('S' != pEvtText->nText[loop][0])	{continue;}
//		if('c' != pEvtText->nText[loop][1])	{continue;}		//	속도향상을 위해 없앤다.
//		if('e' != pEvtText->nText[loop][2])	{continue;}
//		if('n' != pEvtText->nText[loop][3])	{continue;}
//		if('e' != pEvtText->nText[loop][4])	{continue;}

		if(idx != ( (pEvtText->nText[loop][6]-'0')*100 +
					(pEvtText->nText[loop][7]-'0')*10 +
					(pEvtText->nText[loop][8]-'0')*1 ))	{continue;}

		//	씬 다음 인덱스로 넘겨준다.
		m_nParserIndex = loop;	
		break;
	}

	//	활성화시켜준다.
	m_bIsLinkEventManager = true;
}


//--------------------------------------------------------------------------
int EventManager::UpdateEvtParser()
//--------------------------------------------------------------------------
{
	if(false == m_bIsLinkEventManager)	{return 0;}

	m_nParserIndex++;

	//	처리후 인덱스를 넘긴다.
	if(m_nParserIndex >= pEvtText->nTextNum)	{return 0;}

	int idx1 = 0;
	int idx2 = 0;

	switch(pEvtText->nText[m_nParserIndex][0])
	{
		case 'S':	//	scene(???) 다음 씬이므로 종료시킨다.
		case 'E':	//	end(???) 끝일경우
		//-----------------------------------------------------------
		{
			//	활성화시켜준다.
			m_bIsLinkEventManager = false;
			return 0;
		}
		case 'C':	//	cinema(???) 씨네마를 실행시킨다.
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
		case 'T':	//	talk(???) 대사를 실행한다.
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
		case 'M':	//	map(???) 현재 실행시킬 맵의 이름이다.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][4]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][5]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][6]-'0')*1  ;

			ADD_EVENT_MSG(EVT_CHANGE_STAGE, 0, idx1);
			return EVT_CHANGE_STAGE;
		}
		case 'P':	//	prologue(???) 현재 실행시킬 맵의 이름이다.
		//-----------------------------------------------------------
		{
			idx1 = 	(pEvtText->nText[m_nParserIndex][9]-'0')*100 +
					(pEvtText->nText[m_nParserIndex][10]-'0')*10 +
					(pEvtText->nText[m_nParserIndex][11]-'0')*1  ;

			ADD_EVENT_MSG(EVT_PROLOGUE, 0, idx1);
			return EVT_PROLOGUE;
		}
		case 'W':	//	watch(????) 타이머의 시간이다.
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
		case 'L':	//	locate(????) 캐릭터의 위치를 수정한다.
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
//		case 'Q':	//	quest(???) 퀘스트를 알린다.
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
//		//	메세지 중간에 끼는 경우가 생긴다.
//		pMsgList->Insert_prev(tmpMsg);
//		MoveNext(pMsgList);
//	}
//}
