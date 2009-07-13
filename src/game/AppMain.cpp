#include "AppMain.h"

int AppMain::m_nAsprite_Ani = 0;
int AppMain::m_nNextMainState = MS_NULL;
int AppMain::m_nDummy1 = MS_NULL;
int AppMain::m_nDummy2 = MS_NULL;

//--------------------------------------------------------------------------
AppMain::AppMain()
//--------------------------------------------------------------------------
{
	m_nSaveMainState = MS_NULL;
	m_nMainState = MS_NULL;
	m_nNextMainState = MS_NULL;

	//	임시 : 필드번호를 1로 넘겨준다.
//	ResvNextState(FIRST_MS_GAME_FIELD, 1, 0);
	ResvNextState(FIRST_MS_GAME_FIELD, FIRST_DUMMY1, FIRST_DUMMY2);
}


//--------------------------------------------------------------------------
AppMain::~AppMain()
//--------------------------------------------------------------------------
{
	if(NULL != m_GameState)
	{
		m_GameState->Release();
		delete m_GameState;
	}
}


//--------------------------------------------------------------------------
void AppMain::ResvNextState(int nState, int nDummy1, int nDummy2)
//--------------------------------------------------------------------------
{
	m_nNextMainState = nState;
	m_nDummy1 = nDummy1;
	m_nDummy2 = nDummy2;
}


//--------------------------------------------------------------------------
void AppMain::ChangeState()
//--------------------------------------------------------------------------
{
	if(NULL != m_GameState)
	{
		m_GameState->Release();
		delete m_GameState;
	}

	m_nSaveMainState = m_nMainState;
	m_nMainState = m_nNextMainState;
	m_nNextMainState = MS_NULL;

	switch(m_nMainState)
	{
		default:				{																							break;}
		case MS_GAME_FIELD:		{m_GameState = GL_NEW GFieldBattle();	m_GameState->Initialize(m_nDummy1, m_nDummy2);		break;}
		case MS_GAME_WORLDMAP:	{m_GameState = GL_NEW GWorldMap();		m_GameState->Initialize(m_nDummy1, m_nDummy2);		break;}
		case MS_GAME_MAINMENU:	{m_GameState = GL_NEW MainMenu();		m_GameState->Initialize(m_nDummy1, m_nDummy2);		break;}
	}

	m_nDummy1 = MS_NULL;
	m_nDummy2 = MS_NULL;
}


//--------------------------------------------------------------------------
void AppMain::Update()
//--------------------------------------------------------------------------
{
	

	if(MS_NULL != m_nNextMainState)		{ChangeState();}

	getKeyrelease();//SangHo - Key 이벤트 임시구현
	getKeypress();//SangHo - Key 이벤트 임시구현

	m_GameState->KeyEvent(keyCodeMain, keyRepeat);
	m_GameState->Process();
	m_GameState->Paint();

	if(m_nAsprite_Ani<1000000000)m_nAsprite_Ani++;
}


//--------------------------------------------------------------------------
void AppMain::getKeyrelease()//SangHo - Key 이벤트 임시구현
//--------------------------------------------------------------------------
{
	if (keyLife) return;
	if (keyCodeRelease) keyCodePress=keyCodeRelease=0;
	else if(keyCodePress) keyRepeat=true;
}


//--------------------------------------------------------------------------
void AppMain::getKeypress()//SangHo - Key 이벤트 임시구현
//--------------------------------------------------------------------------
{
	keyCodeMain = keyCodePress;
	keyLife = false;
}
