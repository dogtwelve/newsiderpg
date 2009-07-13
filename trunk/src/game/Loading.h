#ifndef __LOADING_H_
#define __LOADING_H_

//	AI와 상호참조를 한다.
#include	"SUTIL.h"
#include "WIPIHeader.h"
#include "Device.h"


#define LDSG							(Loading::GetInstance())

#define LOAD_LOADING					LDSG->Load_Loading
#define RELEASE_LOADING					LDSG->Release_Loading
#define PAINT_LODING					LDSG->Paint_Loading

class Loading
{

public:
	~Loading();
	static Loading* GetInstance();
	void FreeInstance();

	class ASprite*			m_LoadingSprite;

	struct _TEXT_PACK*		pLoadingText;
	int	m_nLoadTimer;
	int	m_nSelectNoticeIdx;

private:
	static Loading* pLoading;
	Loading();


public:
	void Load_Loading();
	void Release_Loading();
	void Paint_Loading();
};


#endif