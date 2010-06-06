#include "GWorldMap.h"


//--------------------------------------------------------------------------
GWorldMap::GWorldMap()
//--------------------------------------------------------------------------
{
	m_nEventIndex = 0;
}


//--------------------------------------------------------------------------
GWorldMap::~GWorldMap()
//--------------------------------------------------------------------------
{
}


//--------------------------------------------------------------------------
void GWorldMap::Initialize(int nDummy1, int nDummy2)
//--------------------------------------------------------------------------
{
	m_nEventIndex = nDummy1;

	//Cinema* pCinema = GL_NEW Cinema();
//	pCinema->LoadCinema(PACK_DATA_CINEMA, DATA_CINEMA_SCENE1);

//	m_pWorldMapAs = SUTIL_LoadSprite(PACK_SPRITE_WORLDMAP, SPRITE_WORLDMAP_WORLDMAP);
//	m_pWorldMapAs->SetBlendFrame(FRAME_SHADOW_BLEND);

//	m_pWorldMapAsIns = GL_NEW ASpriteInstance(m_pWorldMapAs, 50, 100, NULL);
//	SUTIL_SetTypeFrameAsprite(m_pWorldMapAsIns, FRAME_WORLDMAP_TEST);
//	pCinema->LoadCinema(PACK_DATA_CINEMA, DATA_CINEMA_SCENE1);

}


//--------------------------------------------------------------------------
void GWorldMap::Release()
//--------------------------------------------------------------------------
{
//	SUTIL_FreeSpriteInstance(m_pWorldMapAsIns);
//	SUTIL_FreeSprite(m_pWorldMapAs);

//	pCinema->Release_Cinematics();
//	SAFE_DELETE(pCinema);
}

//--------------------------------------------------------------------------
void GWorldMap::Process()
//--------------------------------------------------------------------------
{
//	pCinema->Update_Cinematics();
}


//--------------------------------------------------------------------------
void GWorldMap::Paint()
//--------------------------------------------------------------------------
{

	SUTIL_SetColor(0x000000);
	SUTIL_FillRect(0,0,240,320);

//	pCinema->Paint_Cinematics();

	switch(m_nEventIndex)
	{
		case 1000:
		//------------------------------------------------------------
		{
			_SUTIL->pFont->setColor(0xFFFFFF);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"1 : GO TO SMALL TOWN", 50, 100, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"2 : GO TO FOREST1", 50, 120, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"3 : GO TO CRYSTAL CAVE", 50, 141, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"4 : GO TO MIDDLE TOWN ROAD", 50, 160, 0);//Text
			break;
		}

		case 1001:
		//------------------------------------------------------------
		{
			_SUTIL->pFont->setColor(0xFFFFFF);
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"1 : GO TO MIDDLE TOWN", 50, 100, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"2 : GO TO WEST FOREST", 50, 120, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"3 : GO TO EAST FOREST", 50, 140, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"4 : GO TO MIST CAVE", 50, 160, 0);//Text
			_SUTIL->pFont->DrawText(_SUTIL->g, (char*)"5 : GO TO SMALL TOWN ROAD", 50, 180, 0);//Text
			break;
		}

	}
//	SUTIL_PaintAsprite(m_pWorldMapAsIns, S_NOT_INCLUDE_SORT);

}

//--------------------------------------------------------------------------
void GWorldMap::KeyEvent(int m_keyCode, int m_keyRepeat)
//--------------------------------------------------------------------------
{
	switch(m_nEventIndex)
	{
		case 1000:
		//------------------------------------------------------------
		{
			switch(m_keyCode)
			{
				case MH_KEY_1:	{AppMain::ResvNextState(MS_GAME_FIELD, 801, 0);	break;}
				case MH_KEY_2:	{AppMain::ResvNextState(MS_GAME_FIELD, 101, 1950);		break;}
				case MH_KEY_3:	{AppMain::ResvNextState(MS_GAME_FIELD, 200, 0);	break;}
				case MH_KEY_4:	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 0);		break;}
			}

			break;
		}
		case 1001:
		//------------------------------------------------------------
		{
			switch(m_keyCode)
			{
				case MH_KEY_1:	{AppMain::ResvNextState(MS_GAME_FIELD, 803, 0);		break;}
				case MH_KEY_2:	{AppMain::ResvNextState(MS_GAME_FIELD, 105, 450);		break;}
				case MH_KEY_3:	{AppMain::ResvNextState(MS_GAME_FIELD, 113, 50);		break;}
				case MH_KEY_4:	{AppMain::ResvNextState(MS_GAME_FIELD, 205, 50);		break;}
				case MH_KEY_5:	{AppMain::ResvNextState(MS_GAME_FIELD, 104, 1450);		break;}
			}

			break;
		}

	}
}
