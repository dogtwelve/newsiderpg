#ifndef __APPMAIN_
#define __APPMAIN_

#include "SUtil.h"
#include "VBaseState.h"

#include "GFieldBattle.h"
#include "GWorldMap.h"
#include "MainMenu.h"



//-------------------------------------------------------------------------------
//	MS_GAME_STATE
//-------------------------------------------------------------------------------
#define MS_NULL					0
#define MS_GAME_FIELD			(MS_NULL+1)
#define MS_GAME_WORLDMAP		(MS_NULL+2)
#define MS_GAME_MAINMENU		(MS_NULL+3)

//#define FIRST_MS_GAME_FIELD		(MS_GAME_WORLDMAP)
#define FIRST_MS_GAME_FIELD		(MS_GAME_MAINMENU)
#define FIRST_DUMMY1			(10003)
//#define FIRST_DUMMY1			(400)
#define FIRST_DUMMY2			(0)

extern int keyCodePress;//SangHo - Key �̺�Ʈ �ӽñ���
extern int keyCodeRelease;//SangHo - Key �̺�Ʈ �ӽñ���
extern bool keyLife;//SangHo - Key �̺�Ʈ �ӽñ���
extern bool keyRepeat;//SangHo - Key �̺�Ʈ �ӽñ���

class AppMain
{
public:
	AppMain();
	virtual ~AppMain();

	static void ResvNextState(int nState, int dummy1, int dummy2);
	void Update();

	int m_nSaveMainState;
	int m_nMainState;
	static int m_nAsprite_Ani;
	static int m_nNextMainState;
	static int m_nDummy1;
	static int m_nDummy2;

	int keyCodeMain;//SangHo - Key �̺�Ʈ �ӽñ���

	void getKeyrelease();//SangHo - Key �̺�Ʈ �ӽñ���
	void getKeypress();//SangHo - Key �̺�Ʈ �ӽñ���

private:
	VBaseState*	m_GameState;
	void ChangeState();
};


#endif//	__APPMAIN_
