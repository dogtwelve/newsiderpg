//#include "..\common\memory.h"
//#include "..\common\resfile.h"
//#include "..\common\ResourceManager.h"
#include "..\wipi\brewtowipi.h"
#include "..\game\cGame.h"
#include "..\Game\cUI.h"
#include "..\wipi\Small_Font.h"
#include "WipiIgp.h"
#include "igp_string.h"
#include "igp_res.h"
#include "..\game\Defines.h"
//#include "GloftTheFarm.h"

#if SCREEN_WIDTH == 128
#include "igp_parameter_128x160.h"
#elif SCREEN_WIDTH == 176
#include "igp_parameter_176x220.h"
#elif SCREEN_WIDTH == 240
#include "igp_parameter_240x320.h"
#else
#include "igp_parameter_320x240.h"
#endif



CWipiIgp::CWipiIgp(cGame* game)
{
	_IGPNew = NULL;
	m_stateIGP = 0;
	_sprIGPCataLogo = NULL;
	m_pGame = game;	
	s_g = m_pGame->g;
	m_pFont = GL_NEW S_KR_Font();

	m_nTicker = 0;
	m_nCurItem = 0;
	m_nTotalItem = 0;
	
}

CWipiIgp::~CWipiIgp(void)
{
	Unload();
	SAFE_DEL(m_pFont);
}

void CWipiIgp::DrawNew(CGraphics* g, int x, int y, int align)
{
	if (!_IGPNew)
	{
		CFileStream file;
		bool hr = file.Open("igp_res.bar",CRawFile::MODE_READ);

		int count = file.ReadIntLE();
		int *tab = GL_NEW int[count];

		for( int i=0; i<count; i++ )
		{
			tab[i] = file.ReadIntLE();
		}

		file.SetPosition(tab[ID_new]);		
		_IGPNew = CImage::CreateImage(file);	
		delete [] tab;
		file.Close();

	}
	g->DrawImage(_IGPNew,x,y,align);
}

void CWipiIgp::Load()
{
	if (_sprIGPCataLogo == NULL)
	{
		// load http
		CFileStream file ;
		//bool hr = 
		file.Open("igp.bar",CRawFile::MODE_READ );
		//if( !hr )
		//	return;

		m_iIGPLen = file.GetLength();
		m_iIGPUrlBuff = GL_NEW char[m_iIGPLen];
		file.Read(m_iIGPUrlBuff, m_iIGPLen);
		file.Close();

		// load igp resource(images and strings)
		//hr = 
		file.Open("igp_res.bar",CRawFile::MODE_READ);

		int count = file.ReadIntLE();
		int *tab = GL_NEW int[count];
		for( int i=0; i<count; i++ )
		{
			tab[i] = file.ReadIntLE();
		}

		file.SetPosition(tab[ID_ad0]);
		_sprIGPGame[0] = CImage::CreateImage(file);	

		file.SetPosition(tab[ID_ad1]);
		_sprIGPGame[1] = CImage::CreateImage(file);
		
		file.SetPosition(tab[ID_ad2]);
		_sprIGPGame[2] = CImage::CreateImage(file);

		// operator promption	
		file.SetPosition(tab[ID_left]);
		_leftArrow = CImage::CreateImage(file);
				
		file.SetPosition(tab[ID_right]);
		_rightArrow = CImage::CreateImage(file);
		
		file.SetPosition(tab[ID_tick]);
		_sprTickImages = CImage::CreateImage(file);		

		file.SetPosition(tab[ID_back]);
		_sprBackImages = CImage::CreateImage(file);		
		
		// logo
		file.SetPosition(tab[ID_logo]);
		_sprIGPCataLogo = CImage::CreateImage(file);		
		
		// promotion
		file.SetPosition(tab[ID_promotion_red]);
		_sprIGPRedPromotion= CImage::CreateImage(file);

		file.SetPosition(tab[ID_promotion_blue]);
		_sprIGPBluePromotion= CImage::CreateImage(file);

		file.SetPosition(tab[ID_promotion_yellow]);
		_sprIGPYellowPromotion= CImage::CreateImage(file);		

		// 2558
		file.SetPosition(tab[ID_2558]);
		_spr2558Nate= CImage::CreateImage(file);	
		
		// best sellers
		file.SetPosition(tab[ID_ibs0]);
		_sprBSImages[0] = CImage::CreateImage(file);

		file.SetPosition(tab[ID_ibs1]);
		_sprBSImages[1] = CImage::CreateImage(file);

		file.SetPosition(tab[ID_ibs2]);
		_sprBSImages[2] = CImage::CreateImage(file);		

		file.SetPosition(tab[ID_ibs3]);
		_sprBSImages[3] = CImage::CreateImage(file);		

		file.SetPosition(tab[ID_ibs4]);
		_sprBSImages[4] = CImage::CreateImage(file);		


		// what hot
		file.SetPosition(tab[ID_iwh0]);
		_sprWHImages[0] = CImage::CreateImage(file);
		
		file.SetPosition(tab[ID_iwh1]);
		_sprWHImages[1] = CImage::CreateImage(file);
		
		file.SetPosition(tab[ID_iwh2]);
		_sprWHImages[2] = CImage::CreateImage(file);		

		file.SetPosition(tab[ID_iwh3]);
		_sprWHImages[3] = CImage::CreateImage(file);		

		file.SetPosition(tab[ID_iwh4]);
		_sprWHImages[4] = CImage::CreateImage(file);
				
		// strings 
		file.SetPosition(tab[ID_igp_string_bin]);
		m_nIgpString = file.ReadIntLE();//CombineIntFromByteArray(data);data+=4;

		m_pIgpString = GL_NEW char*[m_nIgpString];
		for( int i=0; i<m_nIgpString; i++ )
		{
			int len = file.ReadIntLE();//CombineIntFromByteArray(data);data+=4;
			m_pIgpString[i] = GL_NEW char[len+1];
			file.Read(m_pIgpString[i],len);						
			m_pIgpString[i][len]=0;
		}

		delete [] tab;
		file.Close();
	}

	//m_stateIGP = 0;
	m_stateIGP = 1;
	_nIGPPage = 0;
}
void CWipiIgp::Unload()
{
	SAFE_DEL(m_iIGPUrlBuff);

	// ad
	SAFE_DEL(_sprIGPGame[0]);
	SAFE_DEL(_sprIGPGame[1]);
	SAFE_DEL(_sprIGPGame[2]);

	// operator prompt
	SAFE_DEL(_leftArrow);
	SAFE_DEL(_rightArrow);
	SAFE_DEL(_sprTickImages);
	SAFE_DEL(_sprBackImages);

	SAFE_DEL(_sprIGPCataLogo);
	SAFE_DEL(_IGPNew);
	
	// promotion
	SAFE_DEL(_sprIGPRedPromotion);
	SAFE_DEL(_sprIGPBluePromotion);
	SAFE_DEL(_sprIGPYellowPromotion);

	//WH icons
	SAFE_DEL(_sprWHImages[0]);
	SAFE_DEL(_sprWHImages[1]);
	SAFE_DEL(_sprWHImages[2]);
	SAFE_DEL(_sprWHImages[3]);
	SAFE_DEL(_sprWHImages[4]);

	//BS icons
	SAFE_DEL(_sprBSImages[0]);
	SAFE_DEL(_sprBSImages[1]);
	SAFE_DEL(_sprBSImages[2]);
	SAFE_DEL(_sprBSImages[3]);
	SAFE_DEL(_sprBSImages[4]);

	// 2558
	SAFE_DEL(_spr2558Nate);

	// strings
	if( m_pIgpString )
	{
		for( int i=0; i<m_nIgpString; i++ )
		{		
			SAFE_DEL(m_pIgpString[i]);		
		}
		SAFE_DEL(m_pIgpString);
	}
	
	m_stateIGP = 0;
	_nIGPPage = 0;
}

void CWipiIgp::Draw()
{
#ifdef EVALUATION
	if (m_stateIGP == 1)
	{
		DrawGradient( s_g, FONT_BLUE, PORTAL_BACKCLR );	
		m_pFont->DrawString(s_g, m_pIgpString[IGP_STR_BACK], SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1,ANCHOR_VCENTER|ANCHOR_HCENTER);
		drawSoftKeyCommand(m_pIgpString[IGP_STR_BACK], NULL);
	}
	return;
#endif
	if( m_stateIGP == 0 )
	{
	}
	else if( m_stateIGP == 1 )
	{
		int y = 10;

		int __IGPpos = 10;	

		switch( _nIGPPage )
		{
		case 0:
		case 1:
		case 2:
			DrawGradient( s_g, FONT_BLUE, PORTAL_BACKCLR );				
			s_g->DrawImage(_sprIGPGame[_nIGPPage] , 
				SCREEN_SHOOT_X,SCREEN_SHOOT_Y,  
				CGraphics::HCENTER | CGraphics::TOP );
			DrawIGPGameIntro( s_g,  m_pIgpString[IGP_STR_ADS_1+_nIGPPage],true);			
			break;		

		case 3:
			s_g->SetColor(0x000000);
			s_g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
			s_g->DrawImage(_sprIGPCataLogo , SCREEN_WIDTH >> 1 ,  IGP_LOGO_HEIGHT , Graphics::HCENTER | Graphics::TOP );
			s_g->DrawImage(_spr2558Nate , SCREEN_WIDTH >> 1 ,  (SCREEN_HEIGHT - _spr2558Nate->GetHeight()) >> 1 , Graphics::HCENTER | Graphics::TOP );			
			DrawVisit(true);	
			break;

		case 4:
			{
				drawAnotherGradient( s_g, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xFFB006, 0xF4F201);

				s_g->DrawImage(_sprIGPGame[0] , 
					SCREEN_SHOOT_X,SCREEN_SHOOT_Y,
					Graphics::HCENTER | Graphics::TOP );

				s_g->DrawImage(_sprIGPYellowPromotion , SCREEN_WIDTH >> 1 ,  (SCREEN_HEIGHT - _sprIGPYellowPromotion->GetHeight()) >> 1 , Graphics::HCENTER | Graphics::TOP );

				m_pFont->setOutlineColor(0);
				m_pFont->drawPage(s_g,m_pIgpString[IGP_STR_PLAY_FOR_FREE],				
					IGP_STR_PLAY_FOR_FREE_X, IGP_STR_PLAY_FOR_FREE_Y,
					IGP_STR_PLAY_FOR_FREE_WIDTH, IGP_STR_PLAY_FOR_FREE_HEIGHT,
					CGraphics::HCENTER|CGraphics::VCENTER,false,false);

				//DrawVisit(true);
				char *sPress5Get;
				int textWidth;

				if( ( m_nTicker & 15) < 8 ) 
				{
					sPress5Get = m_pIgpString[IGP_STR_PRESS_5_GET];
					s_g->SetColor( 0xff0000 );
					textWidth = ((m_pFont->getKStrWidth(sPress5Get)) + 28) >> 1;	
					s_g->FillRect( (OS_SCREEN_W - textWidth)>>1,
						SCREEN_HEIGHT - 34,
						textWidth + 2, 32 );	
					m_pFont->drawKStrMultiLines(s_g,sPress5Get,(OS_SCREEN_W - textWidth)>>1,
						SCREEN_HEIGHT - 30, 
						textWidth,32,FONT_WHITE,FONT_PURE_RED,CGraphics::LEFT|CGraphics::TOP,false);
				}
			}
			break;

		case 5:
			{				
				m_nTotalItem = 5;				
				DrawGradient( s_g, FONT_BLUE, PORTAL_BACKCLR);				
				s_g->DrawImage(_sprIGPCataLogo , SCREEN_WIDTH >> 1 ,  IGP_LOGO_HEIGHT , Graphics::HCENTER | Graphics::TOP );

				m_pFont->drawStrings(
					s_g ,m_pIgpString[IGP_STR_WH_TITLE], 
					IGP_WH_TITLE_X,IGP_WH_TITLE_Y,
					CGraphics::VCENTER|CGraphics::HCENTER,FONT_WHITE,FONT_PURE_RED);
				

				int item_y = IGP_WH_ICON_Y;
				for (int i = 0; i < m_nTotalItem; ++i)
				{
					s_g->DrawImage(_sprWHImages[i], IGP_WH_ICON_X,item_y ,
						Graphics::VCENTER | Graphics::LEFT );

					m_pFont->setOutlineColor((i != m_nTotalItem - 1)? FONT_BLACK:FONT_PURE_RED);
					s_g->SetClip(IGP_WH_TEXT_X-1,item_y-IGP_WH_ICON_GAP_Y/2,IGP_WH_TEXT_WIDTH+2,IGP_WH_ICON_GAP_Y);
					if( m_nCurItem == i )

						drawSwideString(m_pIgpString[IGP_STR_WH_1 + i],
						IGP_WH_TEXT_X,item_y,
						IGP_WH_TEXT_WIDTH,CGraphics::LEFT|CGraphics::VCENTER);	

					else
						m_pFont->DrawString(s_g,m_pIgpString[IGP_STR_WH_1 + i],
						IGP_WH_TEXT_X,item_y,
						CGraphics::LEFT|CGraphics::VCENTER);

					s_g->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
					item_y += IGP_WH_ICON_GAP_Y;
				}

				//draw item selection
				DrawSelectRec(IGP_SELECT_REC_X,IGP_WH_ICON_Y-IGP_WH_ICON_GAP_Y/2-1,IGP_SELECT_REC_WIDTH,IGP_WH_ICON_GAP_Y);

			}
			break;
			
		case 6:
			{				
				m_nTotalItem = 5;				
				DrawGradient( s_g, FONT_BLUE, PORTAL_BACKCLR);				
				s_g->DrawImage(_sprIGPCataLogo , SCREEN_WIDTH >> 1 ,  IGP_LOGO_HEIGHT , Graphics::HCENTER | Graphics::TOP );

				m_pFont->drawStrings(
					s_g ,m_pIgpString[IGP_STR_BS_TITLE], 
					IGP_WH_TITLE_X,IGP_WH_TITLE_Y,
					CGraphics::VCENTER|CGraphics::HCENTER,FONT_WHITE,FONT_PURE_RED);


				int item_y = IGP_WH_ICON_Y;
				for (int i = 0; i < m_nTotalItem; ++i)
				{
					s_g->DrawImage(_sprBSImages[i], IGP_WH_ICON_X,item_y ,
						Graphics::VCENTER | Graphics::LEFT );

					m_pFont->setOutlineColor((i != m_nTotalItem - 1)? FONT_BLACK:FONT_PURE_RED);
					s_g->SetClip(IGP_WH_TEXT_X-1,item_y-IGP_WH_ICON_GAP_Y/2,IGP_WH_TEXT_WIDTH+2,IGP_WH_ICON_GAP_Y);
					if( m_nCurItem == i )
						drawSwideString(m_pIgpString[IGP_STR_BS_1 + i],
						IGP_WH_TEXT_X,item_y,
						IGP_WH_TEXT_WIDTH,CGraphics::LEFT|CGraphics::VCENTER);	
					else
						m_pFont->DrawString(s_g,m_pIgpString[IGP_STR_BS_1 + i],
						IGP_WH_TEXT_X,item_y,
						CGraphics::LEFT|CGraphics::VCENTER);

					s_g->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
					item_y += IGP_WH_ICON_GAP_Y;
				}

				//draw item selection
				DrawSelectRec(IGP_SELECT_REC_X,IGP_WH_ICON_Y-IGP_WH_ICON_GAP_Y/2-1,IGP_SELECT_REC_WIDTH,IGP_WH_ICON_GAP_Y);

			}

			//m_nTotalItem = 5;
			//

			//DrawGradient( s_g, FONT_BLUE, PORTAL_BACKCLR);				

			//s_g->DrawImage(_sprIGPCataLogo , SCREEN_WIDTH >> 1 ,  IGP_LOGO_HEIGHT , CGraphics::HCENTER | CGraphics::TOP );

			//m_pFont->drawStrings(
			//	s_g ,m_pIgpString[IGP_STR_BS_TITLE], 
			//	IGP_WH_TITLE_X,IGP_WH_TITLE_Y
			//	, CGraphics::HCENTER|CGraphics::TOP,FONT_WHITE,FONT_PURE_RED);

			//for (int i = 0; i < m_nTotalItem; ++i){
			//	s_g->DrawImage(_sprBSImages[i],IGP_WH_ICON_X
			//		, ((SCREEN_HEIGHT -  _sprWHImages[0]->GetHeight() * m_nTotalItem +14 ) >> 1 ) + i*IGP_WH_ICON_GAP_Y 
			//		,CGraphics::HCENTER | CGraphics::LEFT );

			//	m_pFont->setOutlineColor((i != m_nTotalItem - 1)? FONT_BLACK:FONT_PURE_RED);
			//	drawSwideString(m_pIgpString[IGP_STR_BS_1 + i],
			//		IGP_WH_TEXT_X,
			//		((SCREEN_HEIGHT -  _sprWHImages[0]->GetHeight() * m_nTotalItem + 14) >> 1 ) + i*IGP_WH_ICON_GAP_Y  ,
			//		IGP_WH_TEXT_WIDTH,CGraphics::LEFT|CGraphics::TOP);	
			//}

			////draw item selection
			//DrawSelectRec(IGP_SELECT_REC_X
			//	, ((SCREEN_HEIGHT -  _sprWHImages[0]->GetHeight() * m_nTotalItem + 14 ) >> 1 ) - 3
			//	,IGP_SELECT_REC_WIDTH,IGP_WH_ICON_GAP_Y );

			//DrawVisit(true);
			break;

		case 7:
			s_g->SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
			drawAnotherGradient( s_g, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xFFB006, 0xF4F201);
			s_g->DrawImage(_sprIGPCataLogo , SCREEN_WIDTH >> 1 ,  IGP_LOGO_HEIGHT , CGraphics::HCENTER | CGraphics::TOP );
			s_g->DrawImage(_sprIGPBluePromotion , SCREEN_WIDTH >> 1 ,  (SCREEN_HEIGHT - _sprIGPBluePromotion->GetHeight()) >> 1 , Graphics::HCENTER | Graphics::TOP );
			
			m_pFont->setOutlineColor(FONT_PURE_RED);
			m_pFont->drawPage(s_g,m_pIgpString[IGP_STR_COMPLETE_CATALOGUE],				
				IGP_STR_PLAY_FOR_FREE_X, IGP_STR_PLAY_FOR_FREE_Y,
				IGP_STR_PLAY_FOR_FREE_WIDTH, IGP_STR_PLAY_FOR_FREE_HEIGHT,
				CGraphics::HCENTER|CGraphics::VCENTER,false,false);

			DrawVisit(true);
			break;

		}

		s_g->DrawImage(_rightArrow ,IGP_RIGHT_ARROW_X - ((m_nTicker%24) >>3),
			( SCREEN_HEIGHT-_rightArrow->GetHeight() ) >> 1, 
			CGraphics::RIGHT | CGraphics::TOP );
		s_g->DrawImage(_leftArrow ,IGP_LEFT_ARROW_X + ((m_nTicker%24) >>3),
			( SCREEN_HEIGHT-_leftArrow->GetHeight() ) >> 1,
			CGraphics::LEFT| CGraphics::TOP );

			drawSoftKeyCommand(m_pIgpString[IGP_STR_BACK],m_pIgpString[IGP_STR_SELECT]);
	}
	else if ( m_stateIGP == 2 )
	{
		DrawDownload();
	}	

}


void CWipiIgp::DrawGradient(CGraphics* pGraphics, int iInteriorColor, int iExteriorColor )
{
	pGraphics->SetClip( 0, 0, OS_SCREEN_W, OS_SCREEN_H );
	//Any start color
	int r1=((iInteriorColor &0xff0000)>>16 ),
		g1=((iInteriorColor &0x00ff00)>>8  ),
		b1= (iInteriorColor &0x0000ff); 
	//Any stop color
	int r2 =((iExteriorColor &0xff0000)>>16),
		g2 =((iExteriorColor &0x00ff00)>>8 ),
		b2 = (iExteriorColor &0x0000ff); 

	//Integrate over half the screen height
	int height = SCREEN_HEIGHT ;
	for(int posY = 0; posY <= height>>1; posY++)
	{
		//calculate the new rgb values
		byte r, g, b;
		r = (byte)( r1 + ((posY) * (r2-r1) / (height>>1)) );
		g = (byte)( g1 + ((posY) * (g2-g1) / (height>>1)) );
		b = (byte)( b1 + ((posY) * (b2-b1) / (height>>1)) );

		//convert them into a 32bit word 
		pGraphics->SetColor( ((r&0xff)<<16|(g&0xff)<<8|(b&0xff))  );

		//here we batch draw to save us some time, this will save us IGP_SCREEN_H/2 iterations in this for loop.
		pGraphics->DrawLine(0, (height>>1)-posY, OS_SCREEN_W, (height>>1)-posY);
		pGraphics->DrawLine(0, (height>>1)+posY, OS_SCREEN_W, (height>>1)+posY);
	}
}

void CWipiIgp::DrawVisit( bool bButtom)
{
	char *sPress5Get;	
	int textWidth;

	int y = 0;
	if (bButtom)
	{
		y = SCREEN_HEIGHT - (_sprTickImages->GetHeight() << 1);
	}
	else{
		y = SCREEN_HEIGHT - (_leftArrow->GetHeight() >> 1);
	}
	if( ( m_nTicker & 15) < 8 ) 
	{
		sPress5Get = m_pIgpString[IGP_STR_PRESS_5_VISIT];
		s_g ->SetColor( 0xff0000 );

		textWidth = m_pFont->getKStrWidth(sPress5Get)+4;	
		if( textWidth > SCREEN_WIDTH )
		{
			textWidth = 88;

			s_g->FillRect( (OS_SCREEN_W - textWidth)>>1,
				y -13,
				textWidth+ 2, 30 );

			m_pFont->drawKStrMultiLines(s_g,sPress5Get,(OS_SCREEN_W - textWidth)>>1,
				y -12,
				textWidth,32,FONT_WHITE,FONT_PURE_RED,CGraphics::HCENTER|CGraphics::VCENTER,false);
		}
		else
		{
			s_g->FillRect( (OS_SCREEN_W - textWidth)>>1, 
				y -13,
				textWidth+ 2, 15 );

			m_pFont->drawStrings(s_g,sPress5Get,
				SCREEN_WIDTH>>1,
				y -12,
				CGraphics::TOP|CGraphics::HCENTER,FONT_WHITE,
				FONT_PURE_RED);
		}		
	}
}

void CWipiIgp::DrawIGPGameIntro( CGraphics *g, char *sGameIntro , bool bUp )
{
	char *sPress5Get;
	int textWidth;

	if(( m_stateIGP == 1) && ( m_nTicker & 15) < 8 ) 
	{
		sPress5Get = m_pIgpString[IGP_STR_PRESS_5_GET];
		g->SetColor( 0xff0000 );

		textWidth = ((m_pFont->getKStrWidth(sPress5Get)) + 28) >> 1;	

		g->FillRect( (OS_SCREEN_W - textWidth)>>1,
			( SCREEN_HEIGHT-_leftArrow->GetHeight() )/2 - 13,
			textWidth -5, 32 );	

		m_pFont->drawKStrMultiLines(g,sPress5Get,(OS_SCREEN_W - textWidth)>>1,
			(( SCREEN_HEIGHT-_leftArrow->GetHeight() ) >> 1 ) - 12, 
			textWidth,32,FONT_WHITE,FONT_PURE_RED,CGraphics::HCENTER|CGraphics::VCENTER,false);
	}

	//draw game intro
	m_pFont->setOutlineColor(0);
	drawSwideString(sGameIntro,0,IGP_GAME_INTRO_Y,SCREEN_WIDTH,
		CGraphics::TOP|CGraphics::HCENTER);
}

bool CWipiIgp::KeyPressed(int key)
{
	return ( m_pGame->IsKeyPressed(key));//(m_pGame->game_keyPressedSingle&key);
}

void CWipiIgp::ClearKey()
{
	m_pGame->ClearKey();//m_pGame->game_keyPressedSingle=0;
}

int CWipiIgp::Update()
{
	m_nTicker++;
	//int ret_value = 0;

	if( m_stateIGP == 0 )
	{
		Load();
		//ret_value = 0;
	}
	else if( m_stateIGP == 1 )
	{
#ifdef EVALUATION
		if(KeyPressed(GAME_KEY_MENU_PRE_ACTION))	
		{
			resetSwingStr = true;
			m_stateIGP = 3;
			//ret_value = 1;
		}
#else

		if(KeyPressed(GAME_KEY_ALL_RIGHT))
		{
			resetSwingStr = true;
			m_nTicker=0;
			_nIGPPage++;
			if (_nIGPPage == 4)
			{
				_nIGPPage++;//fixed a bug
			}
			if (_nIGPPage>=IGP_PAGE_NUM)
				_nIGPPage = 0;

			m_nCurItem = 0;
		}
		else if(KeyPressed(GAME_KEY_ALL_LEFT))
		{
			resetSwingStr = true;
			m_nTicker=0;
			_nIGPPage--;
			if (_nIGPPage == 4)
			{
				_nIGPPage--;//fixed a bug
			}
			if (_nIGPPage<0)
				_nIGPPage = IGP_PAGE_NUM - 1;

			m_nCurItem = 0;
		}
		else if(KeyPressed(GAME_KEY_MENU_ALL_ACTION))
		{
			resetSwingStr = true;
			m_nTicker=0;
			m_stateIGP = 2;
			m_confirm = 0;
		}
		else if(KeyPressed(GAME_KEY_MENU_PRE_ACTION))	
		{
			resetSwingStr = true;
			m_stateIGP = 3;
			//ret_value = 1;
		}
		else if(KeyPressed(GAME_KEY_ALL_DOWN))
		{
			//GuanHao. IGP. scroll
			if ((_nIGPPage==5)||(_nIGPPage==6))
			{
				resetSwingStr = true;
			}

			++m_nCurItem;
			if(m_nCurItem >= m_nTotalItem)
				m_nCurItem = 0;
		}
		else if(KeyPressed(GAME_KEY_ALL_UP))
		{
			//GuanHao. IGP. scroll
			if ((_nIGPPage==5)||(_nIGPPage==6))
			{
				resetSwingStr = true;
			}

			--m_nCurItem;
			if(m_nCurItem < 0)
				m_nCurItem = m_nTotalItem - 1;
		}
#endif
	}
	else if( m_stateIGP == 2 )
	{

		if (KeyPressed(GAME_KEY_CLICK | GAME_KEY_5)	) {
			if (m_confirm) {
				m_stateIGP = 1;
			} else {
				GetIGPURL();
				/*  OEMC_knlExecuteEx((signed char*)"NGB", 2, "URL", m_iUrlIGP);//add assert*/
				/*  MC_knlExit(0);		*/
				g_pGame->OEMC_knlExecuteEx( m_iUrlIGP);
			//	g_pGame->application->destroyApp(true);
				g_pGame->Terminate();
			}
		}
		else if (KeyPressed(GAME_KEY_CLEAR)) {
			m_nTicker=0;
			m_stateIGP = 1;
		}
		else if (KeyPressed(GAME_KEY_ALL_LEFT) || KeyPressed(GAME_KEY_ALL_RIGHT)) {
			m_confirm = ++m_confirm & 1;
		}
	}
	else if (m_stateIGP == 3) {
		Unload();
		return true;
	}

	ClearKey();
	//if( ret_value )
	//{
	//	m_stateIGP = 1;
	//	_nIGPPage = 0;
	//}
	//return ret_value;
	return false;
}

void CWipiIgp::DrawDownload()
{


	s_g->SetColor(0x000000);
	s_g->FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

	//DrawGradient( s_g , 0x0000FF, PORTAL_BACKCLR);

	m_pFont->drawKStrMultiLines(s_g ,m_pIgpString[IGP_STR_OPENBROWSER],
		0,	0,
		SCREEN_WIDTH ,SCREEN_HEIGHT ,
		FONT_WHITE,-1,CGraphics::HCENTER|CGraphics::VCENTER,true);

	if ( m_confirm == 0 )
	{
		DRAW_KORSTR_LINE( s_g, GET_STRING(COMMON_YES ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH-30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff, 0x000000  );
		DRAW_KORSTR( s_g, GET_STRING(COMMON_NO ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH+30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff);
	}
	else 
	{
		DRAW_KORSTR( s_g, GET_STRING(COMMON_YES ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH-30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff );
		DRAW_KORSTR_LINE( s_g, GET_STRING(COMMON_NO ,TEXT_INDEX_COMMON) , SCREEN_HALF_WIDTH+30, SCREEN_HALF_HEIGHT+45, Graphics::TOP|Graphics::HCENTER , 0xffffff, 0x000000 );
	}

}


void CWipiIgp::drawSoftKeyCommand(char* left,char* right)
{
	if(left)
		s_g->DrawImage(_sprBackImages,0, SCREEN_HEIGHT - 3, CGraphics::BOTTOM| CGraphics::LEFT );
	if(right)
		s_g->DrawImage(_sprTickImages, SCREEN_WIDTH, SCREEN_HEIGHT - 3,CGraphics::BOTTOM| CGraphics::RIGHT );
}

void CWipiIgp::GetIGPURL()
{
	char strIn[10] = "URL";//STRCAT("URL",  pGameFrame->m_whichPage);
	int URL_index = 0;
	if(_nIGPPage < 5)
		URL_index = _nIGPPage + 1;
	else if(_nIGPPage == 5)
		URL_index = 5 + m_nCurItem + 1;
	else if(_nIGPPage == 6)
		URL_index = 10 + m_nCurItem + 1;
	else if(_nIGPPage == 7)
		URL_index = 15 + 1;
//	MC_knlSprintk((M_Char *)strIn+3, (M_Char *)"%d", URL_index);
	char *strOut = STRSTR(m_iIGPUrlBuff, strIn);

	int strBeginPos = 0;
	if (strOut != NULL){
		if(URL_index < 10){
			strBeginPos = strOut - m_iIGPUrlBuff;
		}
		else
		{
			strBeginPos = strOut - m_iIGPUrlBuff + 1;
		}
	}	

	for (int index = 0; index < m_iIGPLen; ++index)
	{
		if (m_iIGPUrlBuff[strBeginPos + index + 5] == '\n')
		{
			m_iUrlIGP[index-1] = '\0';
			break;
		}
		m_iUrlIGP[index] = m_iIGPUrlBuff[strBeginPos + index + 5];
	}
}



void CWipiIgp::DrawConfirm(int str_id, bool drawNo, bool drawYes, bool bFill)
{
	if( bFill )
	{
		DrawGradient( s_g, 0x18a618, PORTAL_BACKCLR );
	}
}

void  CWipiIgp::UpdateSKT()
{
	//GuanHao. IGP
	if(KeyPressed(GAME_KEY_LEFT))
	{			

	}
	//else if(m_pGame->game_keyPressedSingle&GAME_KEY_CLICK || m_pGame->game_keyPressedSingle&GAME_KEY_RIGHT)
	else if(m_pGame->IsKeyPressed(GAME_KEY_CLICK)|| m_pGame->IsKeyPressed(GAME_KEY_RIGHT))
	{
		/* OEMC_knlExecuteEx((signed char*)"NGB", 2, "URL", "http://mw.nate.com/p.jsp?page_ID=0036553823&PID=0026033177");
		MC_knlExit(0);*/
		g_pGame->OEMC_knlExecuteEx( "http://mw.nate.com/p.jsp?page_ID=0036553823&PID=0026033177");
	//	g_pGame->application->destroyApp(true);
		g_pGame->Terminate();
	}
}

void CWipiIgp::DrawSelectRec(int x, int y, int w,int h)
{
	//draw item selection
	int selIndex = m_nCurItem - 0;
	int sel_x = x;
	int sel_y = y + IGP_WH_ICON_GAP_Y  * selIndex;
	int sel_h = h;
	int sel_w = w;

	s_g->SetColor( 0xffffff );

	s_g->DrawRect( sel_x, sel_y,  sel_w, sel_h );
	s_g->DrawRect( sel_x - 1, sel_y - 1,  sel_w + 2, sel_h + 2);
}


void CWipiIgp::drawAnotherGradient( CGraphics* g, int x, int y, int wx, int wy, int C1, int C2 )
{
	int IGP_SCRH = SCREEN_HEIGHT;
	int IGP_SCRW = SCREEN_WIDTH;
	int gradR1 = C1 >> 16;
	int gradG1 = (C1 >> 8) & 0x0000FF;
	int gradB1 = C1 & 0x0000FF;

	int gradR2 = C2 >> 16;
	int gradG2 = (C2 >> 8) & 0x0000FF;
	int gradB2 = C2 & 0x0000FF;
	if ( y+wy > IGP_SCRH ) wy = IGP_SCRH-y;
	if ( x+wx > IGP_SCRW ) wx = IGP_SCRW-x;

	int dr = gradR2 - gradR1;
	int dg = gradG2 - gradG1;
	int db = gradB2 - gradB1;
	int intr = gradR1;
	int intg = gradG1;
	int intb = gradB1;

	int stp = 0;

	for ( int i = y; i < y+wy; i++ )
	{
		if ( i < IGP_SCRH/2 )
		{
			stp = i;
		} else
			if ( i == IGP_SCRH/2 )
			{
				intr = gradR2; intg = gradG2; intb = gradB2;
				stp = 0;
			} else
			{
				stp = IGP_SCRH/2 - i;
			}
			g->SetColor( intr + dr * stp / (IGP_SCRH/2), intg + dg * stp / (IGP_SCRH/2), intb + db * stp / (IGP_SCRH/2) );
			g->DrawLine( x, i, x+wx, i );
	}

}




void CWipiIgp::drawSwideString(char* s,int x, int y, int width, int align)
{	
 #define STR_START	30		//Robust, the first shown x Pos
#define STR_GAP		50		//Robust, the gap of the two strings.
	int str_width = m_pFont->stringWidth(s);

	if( str_width >= width )
	{
		static int curPos = STR_START;

		if(resetSwingStr)
		{
			curPos = STR_START;
			resetSwingStr = false;
		}
		curPos --;

		m_pFont->DrawString(s_g,
			s,
			curPos,
			y,
			CGraphics::LEFT|(align&(CGraphics::TOP|CGraphics::BOTTOM|CGraphics::VCENTER)));

		m_pFont->DrawString(s_g,
			s,
			curPos + str_width + STR_GAP,
			y,
			CGraphics::LEFT|(align&(CGraphics::TOP|CGraphics::BOTTOM|CGraphics::VCENTER)));

		if( curPos <= (STR_START - str_width - STR_GAP) )
			curPos = STR_START;

		


		//int marge = 50;
		//int swing = str_width+marge-width;

		//if( swing > 0 )
		//{
		//	int dx = (m_nTicker % (swing << 2)) >> 1;
		//	if(dx > swing)
		//		dx = 2*swing - dx;
		//	x += marge/2+dx-swing;

		//	m_pFont->DrawString(s_g,s,x,y,
		//		CGraphics::LEFT|(align&(CGraphics::TOP|CGraphics::BOTTOM|CGraphics::VCENTER)));
		//}

	}
	else
	{
		if( align&CGraphics::HCENTER )
			x += width/2;
		else if( align&CGraphics::RIGHT )
			x += width;
		m_pFont->DrawString(s_g,s,x,y,align);
	}
}