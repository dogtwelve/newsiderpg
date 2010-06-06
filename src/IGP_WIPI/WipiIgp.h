//#pragma once
#ifndef _WIPI_IGP_
#define _WIPI_IGP_


class CGraphics;
class cGame;
class CImage;
class M_KR_Font;

#define IGP_PAGE_NUM 8

//Korean Font color
#define FONT_PURE_RED			0xFF0000
#define FONT_PURE_GREEN			0x00FF00
#define FONT_PURE_BLUE			0x0000FF
#define FONT_BLACK				0x000000
#define FONT_WHITE				0xFFFFFF
#define FONT_BLUE				0x8CC3F0	
#define FONT_YELLOW				0xffff00
#define MAKE_FONT_RGB(r,g,b)    (((uint32)(r)<< 16) + ((uint32)(g) << 8) + ((uint32)(b)) ) 

#define PORTAL_BACKCLR  0x000000


class CWipiIgp
{
public:
	CWipiIgp(cGame* game);
	~CWipiIgp(void);
	void Load();	
	void Unload();
	int  Update();
	void Draw();
	void DrawNew(CGraphics* gg,int x,int y,int align);
private:
	void DrawGradient(CGraphics* gg, int iInteriorColor, int iExteriorColor);
	void DrawVisit(bool bButtom);
	void DrawIGPGameIntro( CGraphics *gg, char *sGameIntro , bool bUp );
	void DrawDownload();
	void GetIGPURL();	
	void DrawConfirm(int str_id, bool drawNo, bool drawYes, bool bFill);
	void UpdateSKT();
	void drawSoftKeyCommand(char* left,char* right);
	void DrawSelectRec(int x, int y, int w,int h);
	void drawAnotherGradient( CGraphics* gg, int x, int y, int wx, int wy, int C1, int C2 );
	void drawSwideString(char* s,int x, int y, int width, int v_align);
	bool KeyPressed(int key);
	void ClearKey();


private:
	int m_nTicker;
	bool resetSwingStr;

	// core variable
	int m_stateIGP;
	int _nIGPPage;
	int m_nCurItem;
	int m_nTotalItem;	
	
	//confirm
	char m_confirm;

	// support	
	cGame* m_pGame;	
	CGraphics* s_g;
	S_KR_Font* m_pFont;

	// strings
	int    m_nIgpString;
	char** m_pIgpString;

	// url 
	int m_iIGPLen;
	char m_iUrlIGP[128];
	char* m_iIGPUrlBuff;

	// images lists
	CImage *_sprIGPGame[3];
	CImage *_sprIGPCataLogo;
	CImage *_sprIGPBestsell;
	CImage *_sprIGPActionLogo;
	CImage *_sprIGPAllGames;
	CImage *_sprIGPWhatNew;
	CImage *_green_rating;
	CImage *_SKTTable;
	CImage *_IGPNew;
	CImage *_leftArrow;
	CImage *_rightArrow;
	CImage * _strIGPComplete;

	//Promotion page
	CImage * _sprIGPRedPromotion;
	CImage * _sprIGPBluePromotion;
	CImage * _sprIGPYellowPromotion;
	
	//WH icons
	CImage *	_sprWHImages[5];
	//BS icons
	CImage *	_sprBSImages[5];

	//tick, back
	CImage * _sprTickImages;
	CImage * _sprBackImages;
	CImage * _spr2558Nate;
};


#endif //_WIPI_IGP_