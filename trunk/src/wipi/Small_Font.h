#ifndef __SMALL_FONT_H_
#define __SMALL_FONT_H_      
#include "..\wipi\brewtowipi.h"

/////////////////////////////////////////////////////////////////////////
//2009-05-11 : 복잡한 구조를 하나의 DrawString 으로 통합 처리하기 위해서 전체적인 리빌드 실행
/////////////////////////////////////////////////////////////////////////
//특수문자 및 특수기능에 대한 정의 및 구현사항 메뉴얼(Lee SangHo)
//
// 1. 중간 삽입문자는 대문자 N 0,1,2  3개가 있고 한문장 내에서 몇번이고 중복사용이 가능하다
//    EX>  "N1마을 N2에게 N0 10개를 가져다줘라"
// 2. 중간 색변환 문자는 ^ 0~9 까지 사용한다 ^0은 원래 컬러로 되돌리는역할을 한다
//    EX>  "^1하데스가도^0에는 무시무시한 괴물 ^3킹뽀그^0가 살고있다"
// 3. 강제 줄바꿈 문자는 |를 사용한다
//    EX>  "당신은...| 뉘기?"
/////////////////////////////////////////////////////////////////////////
#ifndef MAX_KTEXT_LENGTH
#define  MAX_KTEXT_LENGTH	600//텍스트를 저장할 버퍼 - 이것보다 큰 텍스트는 잘린다
#define  MAX_KTEXT_MAXLINE	20//줄의 가로 픽셀을 저장할 공간최대 줄수
#endif

#ifndef MAX_KTEXT_LINES
#define  MAX_KTEXT_LINES	50//최고 출력 줄수
#endif

//#ifndef TEMP_KTEXT_LENGTH
//#define  TEMP_KTEXT_LENGTH	100//한줄의 예상길이 지역에서 사용된다
//#endif

#ifndef TEMP_KTIME_STR_LENGTH
#define  TEMP_KTIME_STR_LENGTH	100
#endif

#define ANCHOR_VCENTER                                                              CGraphics::VCENTER
#define ANCHOR_HCENTER                                                              CGraphics::HCENTER
#define ANCHOR_TOP									CGraphics::TOP
#define ANCHOR_LEFT									CGraphics::LEFT
#define ANCHOR_BOTTOM								CGraphics::BOTTOM
#define ANCHOR_RIGHT								CGraphics::RIGHT


const int S_FONT_WIDTH = 8;
const int S_FONT_HEIGHT = 9;
const int S_FONT_DEFAULT_WIDTH = 9;

const int S_FONT_CHOSUNG_AMOUNT = 19;
const int S_FONT_JUNGSUNG_AMOUNT = 21;
const int S_FONT_JONGSUNG_AMOUNT = 28;
const int S_FONT_ALPHABET_AMOUNT = 26;

const int S_FONT_SYMBOL_AMOUNT = 48;//31;
const int S_FONT_NUMBER_AMOUNT = 10;

const int S_FONT_CHOSUNG_SET = 18;
const int S_FONT_JUNGSUNG_SET = 3;
const int S_FONT_JONGSUNG_SET = 7;
const int S_FONT_ALPHABET_SET = 2;
const int S_FONT_SYMBOL_SET = 1;
const int S_FONT_NUMBER_SET = 1;


const int S_FONT_HANGEUL_DEFAULT_WIDTH = 9;
const int S_FONT_COPYRIGHT_DEFAULT_WIDTH = 10;

const int S_FONT_ALPHABET_UPPER_DEFAULT_WIDTH = 6;
const int S_FONT_ALPHABET_LOWER_DEFAULT_WIDTH = 6;

const int S_FONT_NUMBER_DEFAULT_WIDTH = 5;
const int S_FONT_SYMBOL_DEFAULT_WIDTH = 7;
const int S_FONT_BLANK_WIDTH = 5;

// delay frame when use the auto scroll. 
const int S_FONT_SCROLL_DELAY = 20;

//the moving unit of scroll
const int S_FONT_SCROLL_UNIT = 1;

const int S_FONT_pixelData_Length = 4;
const int S_FONT_offset_Length = 100;
	

class cGame;

class Small_Font
{
public:
	Small_Font();
	virtual ~Small_Font();
	void decideChosung_NoJongsung(int argJungIndex);
	void decideChosung_Jongsung(int argJungIndex);
	int getSymbolIndex(int argSymbol);
	int getCharWidth(unsigned char argChar, int argX);
	
	
public:
	int choSetNum;
	int jungSetNum;
	int jongSetNum;
	int defaultX;
	int zoom;
	
};

struct DrawType
{
	int wrap_Width;//1줄의 최대 가로 길이(넘어가면 자동 줄바꿈이 실행된다)
	int startLine;//줄바꿈이 된상황이서의 첫줄
	int LineCount;
};

class S_KR_Font: public Small_Font
{
public:
	short wPixel[MAX_KTEXT_MAXLINE];//줄바꿈 되기전의 

	DrawType s_DrawType;
	bool isInitalizedPage;
	int stringHeight()
	{
		return 12;
	}
	S_KR_Font();
	S_KR_Font(int argWidth, int argHeight);
	virtual ~S_KR_Font();
	void Initialize();
	void Finalize();
	void initializeOffset(short* offset, char* argSize, int length);
	void loadData();
	void setColor(int argColor);
	void setOutlineColor(int argColor);
	void setOutline(bool argOutline);
	void drawString_bold(CGraphics* g,char* argStr, int argX, int argY, int argAnchor, bool argIsNewLine);
	void setZoom(int argZoom);
	void setLineSpace(int argSpace);
	int charWidth(char argChar);
	int stringWidth(char* str);

	void drawChar(char* argData, short* argOffset, char* argSize, 
				  int argIndex, int argX, int argY, bool isOutline);

	void drawChars(CGraphics* g, char* argCharArray, 
					int argX, int argY,
					bool argOutline, bool argIsNewLine);

	int KStringWrap(const char* str, int width);
	void delKStrWrap(const char* str);
	int getKStrWidth(char* str);

	

//****************************************************START**********************************************************	
	/* - SangHo - 2009-05-11
	*char* argStr	- 캐릭터 포인터
	*int posX		- 좌상 X좌표
	*int posY		- 좌상 Y좌표
	*int argAnchor	- 좌,우 정렬 
	*return : 몇픽셀이 올라갔는지를 리턴, 0 이면 스크롤이 끝난 상태임
	*/

	//Master DrawString 메소드 - 각종 설정은 모두 Dry 메소드에서 처리한다 
	int DrawText(CGraphics* g, char* argStr, int posX, int posY, int argAnchor, char* N0 = NULL, char* N1 = NULL, char* N2 = NULL);
	//입력 형태가 숫자일때 처리하기위한 부분
	int DrawText(CGraphics* g, int numberTemp, int posX, int posY, int argAnchor, char* N0 = NULL, char* N1 = NULL, char* N2 = NULL){
		char str[11];//int 최대크기
		SPRINTF(str, "%d", numberTemp); 
		return DrawText(g, str, posX, posY, argAnchor, N0, N1, N2);
	}
	// 이전에 출력한 문자열의 바로 뒤에 이어서 문자열을 출력한다.
	int DrawText(CGraphics* g, char* argStr, int Space, char* N0 = NULL, char* N1 = NULL, char* N2 = NULL)
	{
		return DrawText(g, argStr, nextX+Space, nextY, 0, N0, N1, N2);
	}

	//아래의 옵션들은 DrawText 확장옵션들이다 DrawText가 한번 실행이 되고나면 모든 옵션은 초기화 된다
	void Dry_Wrap_Width(int wrap_Width){	s_DrawType.wrap_Width = wrap_Width;	}
	void Dry_StartLine_Max(int startLine,int LineCount){	s_DrawType.startLine = startLine;	s_DrawType.LineCount = LineCount;}
//******************************************************END********************************************************



private:
	void drawStrings(CGraphics* g, char* argStr, int argX, int argY, int argAnchor, bool isNewLine = false);
	void drawStr(CGraphics* g, char* argStr, int argX, int argY, bool argIsNewLine);

	cGame *m_pGame;
	CGraphics* m_pGfx;

	M_Int32 tempmem[8];
	char* m_FontData;

	int nextX;
	int nextY;
	
	// width and height of screen.
	int screenWidth, screenHeight;
	
	//size of a cho-sung<br>
	//column: the set number of a cho-sung, row: index of a cho-sung<br>
	char chosung_size[S_FONT_CHOSUNG_SET][S_FONT_CHOSUNG_AMOUNT];
	
	//size of a jung-sung<br>
	//column: the set number of a jung-sung, row: index of a jung-sung.
	char jungsung_size[S_FONT_JUNGSUNG_SET][S_FONT_JUNGSUNG_AMOUNT];
	
	// size of a jong-sung<br>
	// column: the set number of a jong-sung, row: index of a jong-sung.
	char jongsung_size[S_FONT_JONGSUNG_SET][S_FONT_JONGSUNG_AMOUNT];
	char alphabet_size[S_FONT_ALPHABET_SET][S_FONT_ALPHABET_AMOUNT];
	
	// the symbol is limited to a set.
	char symbol_size[S_FONT_SYMBOL_AMOUNT];
	char number_size[S_FONT_NUMBER_SET][S_FONT_NUMBER_AMOUNT];
	
	//the pixel data of cho-sung
	/* this is made in acount of stroke each the cho-sung.
	* infomation of each stroke is 2 byte.
	* 1byte(basis x , basis y ), 1byte(width, height)
	*/
	char* chosung_data[S_FONT_CHOSUNG_SET];
	
	//the pixel data of jung-sung.
	char* jungsung_data[S_FONT_JUNGSUNG_SET];
	
	//the pixel data of jong-sung.
	char* jongsung_data[S_FONT_JONGSUNG_SET];
	
	char* alphabet_data[S_FONT_ALPHABET_SET];
	char* symbol_data;
	char* number_data[S_FONT_NUMBER_SET];
	
	
	//offset of cho-sung
	//this is calculate by the size array
	short chosung_offset[S_FONT_CHOSUNG_SET][S_FONT_CHOSUNG_AMOUNT];
	
	short jungsung_offset[S_FONT_JUNGSUNG_SET][S_FONT_JUNGSUNG_AMOUNT];
	
	short jongsung_offset[S_FONT_JONGSUNG_SET][S_FONT_JONGSUNG_AMOUNT];
	
	short alphabet_offset[S_FONT_ALPHABET_SET][S_FONT_ALPHABET_AMOUNT];
	short symbol_offset[S_FONT_SYMBOL_AMOUNT];
	short number_offset[S_FONT_NUMBER_SET][S_FONT_NUMBER_AMOUNT];
	
	
	//x, y, widht, height
	byte pixelData[S_FONT_pixelData_Length];
	

	//color of letters.
	int foreColor;

	//GuanHao. 6 basic seeds
	int tempColor;
	
	//color of outline.
	int outlineColor;
	
	//draw outline if true <br>
	bool isOutlineDraw;
	
	
	//line space without height of character.
	
	int lineSpace;
	
	
	//caution : you must set false before use the drawPage method.
	//bool isInitalizedPage;
	
	//index of the line feed in sentence.
	int offset[S_FONT_offset_Length];
	
	//account of line to draw.
	int lines;
		
	
	
	//SangHo - 폰트 컬러변수 ^
	int currentColorIndex;//SangHo - 텍스트 출력중에 원하는 단어를 색변경 하기위해서 존재하는 컬러 슬롯 인덱서
	int colorSet[10];//SangHo - 미리 지정된 9개의 컬러[1~9] + 사용자정의 컬러 1개[0]
	
	//account of lines * (height of character + line space) - line space

	int sentenceHeight;
	
	int m_ScrollOffset;

	//added by Wang Xiaomei
	char m_stringWrapped[MAX_KTEXT_LENGTH];
	char m_stringDelWrap[MAX_KTEXT_LENGTH];
	int m_off[MAX_KTEXT_LINES];

};
#endif