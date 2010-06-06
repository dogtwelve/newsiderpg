#include "Loading.h"

Loading* Loading::pLoading = NULL;

//--------------------------------------------------------------------------------------
Loading::Loading()
//--------------------------------------------------------------------------------------
{
	m_nLoadTimer = -1;
}


//--------------------------------------------------------------------------------------
Loading::~Loading()
//--------------------------------------------------------------------------------------
{
	Release_Loading();
}


//--------------------------------------------------------------------------
Loading* Loading::GetInstance()
//--------------------------------------------------------------------------
{
	if(NULL == pLoading)
	{
		pLoading = new Loading();
	}

	return pLoading;
}

//--------------------------------------------------------------------------
void Loading::FreeInstance()
//--------------------------------------------------------------------------
{
	if(NULL != pLoading)
	{
		delete pLoading;
		pLoading = NULL;
	}
}


//--------------------------------------------------------------------------
void Loading::Load_Loading()
//--------------------------------------------------------------------------
{
	if(-1 != m_nLoadTimer)	{return;}

	m_nLoadTimer = 0;
	pLoadingText = _SUTIL->LoadTextPack(PACK_DATA_LOADING, DATA_LOADING_TEXT_LOADING);
	m_LoadingSprite = SUTIL_LoadSprite(PACK_SPRITE_LOADING, SPRITE_LOADING_LODING );

	m_nSelectNoticeIdx = 2+(SUTIL_GetRandom()%(pLoadingText->nTextNum - 2));
}


//--------------------------------------------------------------------------
void Loading::Release_Loading()
//--------------------------------------------------------------------------
{
	m_nLoadTimer = -1;
	SUTIL_FreeSprite(m_LoadingSprite);
	SUTIL_FreeTextPack(pLoadingText);
}

/*
//--------------------------------------------------------------------------
void Loading::Paint_Loading()
//--------------------------------------------------------------------------
{
	if(0 > m_nLoadTimer)	{return;}

	m_nLoadTimer = (m_nLoadTimer+1)%10;	

	//	loading
	_SUTIL->pFont->setColor(0xfffda1);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pLoadingText->nText[LOADING_LOADING], 137, 280, 0);

	//	...
	SUTIL_SetColor(0xfffda1);
	for(int loop = 0; loop < 4 ; loop++)
	{
		if(loop < (m_nLoadTimer%4))	{SUTIL_SetColor(0xfffda1);}
		else						{SUTIL_SetColor(0x000000);}
		SUTIL_FillRect(212+(loop*3),286,1,2);
	}

	//	jewel
	SUTIL_Paint_Frame(m_LoadingSprite, (m_nLoadTimer%6), 238, 294, 0);	
}
*/




//--------------------------------------------------------------------------
void Loading::Paint_Loading()
//--------------------------------------------------------------------------
{
	if(0 > m_nLoadTimer)	{return;}

	m_nLoadTimer = (m_nLoadTimer+1)%10;	

	SUTIL_SetColor(0x735530);
	SUTIL_DrawRect(5,130,230,45);

	SUTIL_SetColor(0x000000);
	SUTIL_FillRect(4,129,32,10);

	//	hint
	_SUTIL->pFont->setColor(0xfffda1);
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pLoadingText->nText[LOADING_HINT], 8, 126, 0);

	//	loading
	_SUTIL->pFont->DrawText(_SUTIL->g, (char*)pLoadingText->nText[LOADING_LOADING], 137, 280, 0);

	//	...
	SUTIL_SetColor(0xfffda1);
	for(int loop = 0; loop < 4 ; loop++)
	{
		if(loop < (m_nLoadTimer%4))	{SUTIL_SetColor(0xfffda1);}
		else						{SUTIL_SetColor(0x000000);}
		SUTIL_FillRect(212+(loop*3),286,1,2);
	}

	//	hint notice
	_SUTIL->pFont->setColor(0xffffff);
	_SUTIL->pFont->Dry_Wrap_Width(215);
	_SUTIL->pFont->DrawText(_SUTIL->g,
							(char*)pLoadingText->nText[m_nSelectNoticeIdx], 15, 143, 0);

	//	jewel
	SUTIL_Paint_Frame(m_LoadingSprite, (m_nLoadTimer%6), 238, 294, 0);	
}

