#include "..\game\cGame.h"
#include "Small_Font.h"

Small_Font::Small_Font()
{
	zoom = 1;
}

Small_Font::~Small_Font()
{
}
void Small_Font::decideChosung_NoJongsung(int argJungIndex)
{
	switch (argJungIndex)
	{
	case 0:
	case 2:
	case 4:
	case 6:
	case 20:
		choSetNum = 0;
		jungSetNum = 0;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		choSetNum = 1;
		jungSetNum = 0;
		break;
	case 8:
	case 12:
	case 18:
		choSetNum = 2;
		jungSetNum = 0;
		break;
	case 13:
	case 17:
		choSetNum = 3;
		jungSetNum = 0;
		break;
	case 9:
	case 11:
	case 19:
		choSetNum = 4;
		jungSetNum = 0;
		break;
	case 14:
	case 16:
		choSetNum = 5;
		jungSetNum = 0;
		break;
	case 10:
		choSetNum = 6;
		jungSetNum = 0;
		break;
	case 15:
		choSetNum = 7;
		jungSetNum = 0;
		break;

	}

}


void Small_Font::decideChosung_Jongsung(int argJungIndex)
{
	switch (argJungIndex)
	{
	case 0:
	case 2:
	case 4:
	case 6:
	case 20:
		choSetNum = 8;
		jungSetNum = 1;
		jongSetNum = 1;
		break;
	case 14:
	case 16:
		choSetNum = 13;
		jungSetNum = 1;
		jongSetNum = 3;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		choSetNum = 9;
		jungSetNum = 1;
		jongSetNum = 5;
		break;
	case 8:
	case 12:
		choSetNum = 10;
		jungSetNum = 1;
		jongSetNum = 2;
		break;
	case 18:
		choSetNum = 11;
		jungSetNum = 1;
		jongSetNum = 6;
		break;
	case 13:
	case 17:
		choSetNum = 12;
		jungSetNum = 1;
		jongSetNum = 3;
		break;
	case 9:
	case 19:
		choSetNum = 13;
		jungSetNum = 1;
		jongSetNum = 1;
		break;
	case 11:
		choSetNum = 14;
		jungSetNum = 2;
		jongSetNum = 3;
		break;
	case 10:
		choSetNum = 15;
		jungSetNum = 1;
		jongSetNum = 4;
		break;
	case 15:
		choSetNum = 17;
		jungSetNum = 1;
		jongSetNum = 3;
		break;

	}
}


int Small_Font::getSymbolIndex(int argSymbol)
{
	int returnIndex = 29;

	switch (argSymbol)
	{
	case 126:	// ~
		returnIndex = 0;
		break;
	case 33:	// !
		returnIndex = 1;
		break;
	case 64:	// @
		returnIndex = 2;
		break;
	case 35:	// #
		returnIndex = 3;
		break;
	case 36:	// $
		returnIndex = 4;
		break;
	case 37:	// %
		returnIndex = 5;
		break;
	case 94:	// ^
		returnIndex = 6;
		break;
	case 38:	// &
		returnIndex = 7;
		break;
	case 42:	// *
		returnIndex = 8;
		break;
	case 40:	// (
		returnIndex = 9;
		break;
	case 41:	// )
		returnIndex = 10;
		break;
	case 95:	// _
		returnIndex = 11;
		break;
	case 45:	// -
		returnIndex = 12;
		break;
	case 43:	// +
		returnIndex = 13;
		break;
	case 61:	// =
		returnIndex = 14;
		break;
	case 124:	// |
		returnIndex = 15;
		break;
	case 91:	// [
		returnIndex = 16;
		break;
	case 93:	// ]
		returnIndex = 17;
		break;
	case 59:	// ;
		returnIndex = 18;
		break;
	case 39:	// '
		returnIndex = 19;
		break;
	case 44:	// ,
		returnIndex = 20;
		break;
	case 46:	// .
		returnIndex = 21;
		break;
	case 47:	// /
		returnIndex = 22;
		break;
	case 123:	// {
		returnIndex = 23;
		break;
	case 125:	// }
		returnIndex = 24;
		break;
	case 58:	// :
		returnIndex = 25;
		break;
	case 34:	// "
		returnIndex = 26;
		break;
	case 60:	// <
		returnIndex = 27;
		break;
	case 62:	// >
		returnIndex = 28;
		break;
	case 63:	// ?
		returnIndex = 29;
		break;
	case 92:	// 
		returnIndex = 30;
		break;
	case 96:	// `
		returnIndex = 31;
		break;
	case 12593:	// ㄱ
		returnIndex = 32;
		break;
	case 12596:	// ㄴ
		returnIndex = 33;
		break;
	case 12599:	// ㄷ
		returnIndex = 34;
		break;
	case 12601:	// ㄹ
		returnIndex = 35;
		break;
	case 12609:	// ㅁ
		returnIndex = 36;
		break;
	case 12610:	// ㅂ
		returnIndex = 37;
		break;
	case 12613:	// ㅅ
		returnIndex = 38;
		break;
	case 12615:	// ㅇ
		returnIndex = 39;
		break;
	case 12616:	// ㅈ
		returnIndex = 40;
		break;
	case 12618:	// ㅊ
		returnIndex = 41;
		break;
	case 12619:	// ㅋ
		returnIndex = 42;
		break;
	case 12620:	// ㅌ
		returnIndex = 43;
		break;
	case 12621:	// ㅍ
		returnIndex = 44;
		break;
	case 12622:	// ㅎ
		returnIndex = 45;
		break;
	case 12636:	// ㅜ
		returnIndex = 46;
		break;
	case 12640:	// ㅠ
		returnIndex = 47;
		break;

	}

	return returnIndex;
}

int Small_Font::getCharWidth(unsigned char argChar, int argX)
{
	int result = 0;

	//if (argChar >= '\uAC00' && argChar <= '\uD7A3')
	//{
	//	//			argX = argX + NEXT_FONT_WIDTH * zoom;
	//	result =  S_FONT_HANGEUL_DEFAULT_WIDTH;
	//}
	if (argChar > 128)
	{
		if (argChar == 0xC2)
			result = S_FONT_COPYRIGHT_DEFAULT_WIDTH;
		else
			result =  S_FONT_HANGEUL_DEFAULT_WIDTH;
	}
	else
	{
		if (argChar >= 'A' && argChar <= 'Z')
		{
			switch(argChar)
			{
			case 'A':
				result = 7;
				break;
			case 'B':
				result = 7;
				break;
			case 'C':
				result = 7;
				break;
			case 'D':
				result = 7;
				break;
			case 'G':
				result = 7;
				break;
			case 'H':
				result = 7;
				break;
			case 'J':
				result = 5;
				break;
			case 'M':
				result = 8;
				break;
			case 'N':
				result = 7;
				break;
			case 'O':
				result = 7;
				break;
			case 'Q':
				result = 7;
				break;
			case 'U':
				result = 7;
				break;
			case 'W':
				result = 8;
				break;
			case 'I':
				result = 4;
				break;


			default:
				result = S_FONT_ALPHABET_UPPER_DEFAULT_WIDTH;
				break;
			}
		}
		else if (argChar >= 'a' && argChar <= 'z')
		{
			switch(argChar)
			{
			case 'f':
				result = 4;
				break;
			case 'i':
				result = 3;
				break;
			case 'j':
				result = 5;
				break;
			case 'l':
				result = 2;
				break;
			case 'r':
				result = 4;
				break;
			case 't':
				result = 4;
				break;
			case 'm':
				result = 8;
				break;
			case 'w':
				result = 8;
				break;
			case 's':
				result = 5;
				break;
			case 'y':
				result = 5;
				break;
			case 'k':
				result = 5;
				break;

			default:
				result = S_FONT_ALPHABET_LOWER_DEFAULT_WIDTH;
				break;
			}
		}
		else if (argChar == ' ')
		{
			if (argX == defaultX)
				result = defaultX;
			else
				result =  S_FONT_BLANK_WIDTH;
		}
		else if (argChar >= '0' && argChar <= '9')
		{
			switch(argChar)
			{
			case '1':
				result = 5;
				break;

			default:
				result = S_FONT_NUMBER_DEFAULT_WIDTH;
				break;
			}
		}
		else
		{
			switch(argChar)
			{
			case 33:	// !
				result = 3;
				break;
			case 94:	// ^
				result = 6;
				break;
			case 42:	// *
				result = 5;
				break;
			case 40:	// (
				result = 4;
				break;
			case 41:	// )
				result = 4;
				break;
			case 91:	// [
				result = 4;
				break;
			case 93:	// ]
				result = 4;
				break;
			case 92:	// 
				result = 11;
				break;
			case 59:	// ;
				result = 3;
				break;
			case 39:	// '
				result = 4;
				break;
			case 44:	// ,
				result = 4;
				break;
			case 46:	// .
				result = 3;
				break;
			case 58:	// :
				result = 3;
				break;
			case 37:	// %
				result = 9;
				break;
			case 12636:	// ㅜ
				result = 9;
				break;
			case 12640:	// ㅠ
				result = 9;
				break;
			case 123:	// {
				result = 4;
				break;
			case 125:	// }
				result = 4;
				break;
			case 60:	// <
				result = 4;
				break;
			case 62:	// >
				result = 6;
				break;
			case 64:	// @
				result = 9;
				break;
			case 95:	// _
				result = 7;
				break;
			case 45:	// -
				result = 6;
				break;
			case 47:	// /
				result = 5;
				break;
			case 38:	// &
				result = 8;
				break;
			case 126:	// ~
				result = 10;
				break;

			default:
				result = S_FONT_SYMBOL_DEFAULT_WIDTH;
				break;
			}

			if(result == 0 && argChar != '|' && argChar == '\r' && argChar == '\n')
				result = S_FONT_SYMBOL_DEFAULT_WIDTH;
		}
	}


	return result*zoom;
}

////////////////////////////////////////////////////////////////////////////////////

S_KR_Font::S_KR_Font()	
{
	Initialize();
}

S_KR_Font::~S_KR_Font()
{
	Finalize();
}

S_KR_Font::S_KR_Font(int argWidth, int argHeight)
{
	screenWidth = argWidth;
	screenHeight = argHeight;
	
	Initialize();
}
//void S_KR_Font::setOutline(CGraphics* g,
//									char* str,
//									int x,
//									int y,
//									int anchor,
//									int color,
//									int color2)
//{
//	drawStrings(g, str, x, y, anchor,color, color2, false);
//}

void S_KR_Font::drawString_bold(CGraphics* g,char* argStr, int argX, int argY, int argAnchor, bool argIsNewLine)
{
	//argStr = utf8ToUnicode(argStr);

	int strWidth = stringWidth(argStr);

	if ((argAnchor & Graphics::HCENTER) == Graphics::HCENTER)
	{
		argX -= (strWidth >> 1);
	}
	else if ((argAnchor & Graphics::RIGHT) == Graphics::RIGHT)
	{
		argX -= strWidth;
	}

	if ((argAnchor & Graphics::VCENTER) == Graphics::VCENTER)
	{
		argY -= (S_FONT_HEIGHT >> 1);
	}
	else if ((argAnchor & Graphics::BOTTOM) == Graphics::BOTTOM)
	{
		argY -= S_FONT_HEIGHT;
	}

	
	//drawString(g, argStr, argX, argY, argIsNewLine);
	//drawString(g, argStr, argX+1, argY, argIsNewLine);
	drawStr(g, argStr, argX, argY, argIsNewLine);
	drawStr(g, argStr, argX+1, argY, argIsNewLine);
}
void S_KR_Font::Initialize()
{
	m_pGame = g_pGame ;
	m_pGfx = NULL;
	
	isOutlineDraw = false;
	lineSpace = 2;
	int i = 0;
	//colorSet[0] 은 백업컬러
	colorSet[1] = 0xFF0000;//빨강
	colorSet[2] = 0x00FF00;//초록
	colorSet[3] = 0x7777FF;//파랑
	colorSet[4] = 0x000000;
	colorSet[5] = 0x000000;
	colorSet[6] = 0x000000;
	colorSet[7] = 0x000000;
	colorSet[8] = 0x000000;
	colorSet[9] = 0x000000;

	//GuanHao. 6 basic seeds.
	tempColor = 0;
	
	for(i=0; i < S_FONT_CHOSUNG_SET; i++)
	{
		MEMSET(chosung_size[i], NULL, S_FONT_CHOSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_JUNGSUNG_SET; i++)
	{
		MEMSET(jungsung_size[i], NULL, S_FONT_JUNGSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_JONGSUNG_SET; i++)
	{
		MEMSET(jongsung_size[i], NULL, S_FONT_JONGSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_ALPHABET_SET; i++)
	{
		MEMSET(alphabet_size[i], NULL, S_FONT_ALPHABET_AMOUNT);
	}
	
	MEMSET(symbol_size, NULL, S_FONT_SYMBOL_AMOUNT);
	
	for(i=0; i < S_FONT_NUMBER_SET; i++)
	{
		MEMSET(number_size[i], NULL, S_FONT_NUMBER_AMOUNT);
	}
	
	loadData();
	
	for(i=0; i < S_FONT_CHOSUNG_SET; i++)
	{
		initializeOffset(chosung_offset[i], chosung_size[i], S_FONT_CHOSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_JUNGSUNG_SET; i++)
	{
		initializeOffset(jungsung_offset[i], jungsung_size[i], S_FONT_JUNGSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_JONGSUNG_SET; i++)
	{
		initializeOffset(jongsung_offset[i], jongsung_size[i], S_FONT_JONGSUNG_AMOUNT);
	}
	
	for(i=0; i < S_FONT_ALPHABET_SET; i++)
	{
		initializeOffset(alphabet_offset[i], alphabet_size[i], S_FONT_ALPHABET_AMOUNT);
	}
	
	initializeOffset(symbol_offset, symbol_size, S_FONT_SYMBOL_AMOUNT);
	
	for(i=0; i < S_FONT_NUMBER_SET; i++)
	{
		initializeOffset(number_offset[i], number_size[i], S_FONT_NUMBER_AMOUNT);
	}
}

void S_KR_Font::Finalize()
{
	int i = 0;
	for (i=0; i < S_FONT_CHOSUNG_SET; i++)
	{
		SAFE_DELETE(chosung_data[i]);
	}
	for (i=0; i < S_FONT_JUNGSUNG_SET; i++)
	{
		SAFE_DELETE(jungsung_data[i]);
	}
	for (i=0; i < S_FONT_JONGSUNG_SET; i++)
	{
		SAFE_DELETE(jongsung_data[i]);
	}
	for (i=0; i < S_FONT_ALPHABET_SET; i++)
	{
		SAFE_DELETE(alphabet_data[i]);
	}

	SAFE_DELETE(symbol_data);

	for (i=0; i < S_FONT_NUMBER_SET; i++)
	{
		SAFE_DELETE(number_data[i]);
	}

	FREE(m_FontData);
}

void S_KR_Font::loadData()
{
	//M_Int32	resID;			// resource ID
	//M_Int32 resAddr;
	M_Int32	resSize;			// img buffer size
	
	
	/*minh_dang resID	= MC_knlGetResourceID((signed char*)"small_font.dat", &resSize);
	tempmem[0] = MC_knlCalloc(resSize);
	m_FontData = (char*)MC_GETDPTR(tempmem[0]);
	char* Res_FontAddr = m_FontData; 
	resAddr = (long)m_FontData;
	MC_knlGetResource(resID, (void*)&resAddr, resSize);*/
	
	CRawFile * lFileID_ = new CRawFile();

	//if( !lFileID_ && !lFileID_->Open((const char*)"small_font.dat" , CRawFile::MODE_READ))
	if(!lFileID_->Open((const char*)"small_font.dat" , CRawFile::MODE_READ))
	{
		lFileID_->Close();//MC_fsClose(lFileID_);
		delete lFileID_ ;
		//return iSuccess_;
	}
	resSize = lFileID_->GetLength();
	m_FontData = (char *)MALLOC(resSize) ;
	lFileID_->Read(m_FontData , resSize );
	char* Res_FontAddr = m_FontData; 
	//resAddr = m_FontData;
	delete lFileID_ ;
	int i = 0;
	for(i=0; i < S_FONT_CHOSUNG_SET; i++)
	{
		MEMCPY(chosung_size[i], Res_FontAddr, S_FONT_CHOSUNG_AMOUNT);
		Res_FontAddr += S_FONT_CHOSUNG_AMOUNT;
		//is.read(chosung_size[i]);
	}
	
	for(i=0; i < S_FONT_JUNGSUNG_SET; i++)
	{
		//is.read(jungsung_size[i]);
		STRNCPY(jungsung_size[i], Res_FontAddr, S_FONT_JUNGSUNG_AMOUNT);
		Res_FontAddr += S_FONT_JUNGSUNG_AMOUNT;
	}
	
	for(i=0; i < S_FONT_JONGSUNG_SET; i++)
	{
		//is.read(jongsung_size[i]);
		MEMCPY(jongsung_size[i], Res_FontAddr, S_FONT_JONGSUNG_AMOUNT);
		Res_FontAddr += S_FONT_JONGSUNG_AMOUNT;
	}
	
	for(i=0; i < S_FONT_ALPHABET_SET; i++)
	{
		//is.read(alphabet_size[i]);
		MEMCPY(alphabet_size[i], Res_FontAddr,S_FONT_ALPHABET_AMOUNT);
		Res_FontAddr += S_FONT_ALPHABET_AMOUNT;
	}
	
	//is.read(symbol_size);
	MEMCPY(symbol_size, Res_FontAddr,S_FONT_SYMBOL_AMOUNT);
	Res_FontAddr += S_FONT_SYMBOL_AMOUNT;
	
	
	for(i=0; i < S_FONT_NUMBER_SET; i++)
	{
		//is.read(number_size[i]);
		MEMCPY(number_size[i], Res_FontAddr,S_FONT_NUMBER_AMOUNT);
		Res_FontAddr += S_FONT_NUMBER_AMOUNT;
		
	}
	
	int index = 0;
	int size = 0;
	
	for(i=0; i < S_FONT_CHOSUNG_SET; i++, index++)
	{
		
		for(int k=0; k < S_FONT_CHOSUNG_AMOUNT; k++)
		{
			size += chosung_size[i][k];	
		}	
		
		chosung_data[i] = GL_NEW char[size];
		//is.read(chosung_data[i]);	
		MEMCPY(chosung_data[i], Res_FontAddr, size);
		Res_FontAddr += size;
		size = 0;
	}
	
	
	for(i=0; i < S_FONT_JUNGSUNG_SET; i++, index++)
	{
		for(int k=0; k < S_FONT_JUNGSUNG_AMOUNT; k++)
		{
			size += jungsung_size[i][k];
		}
		
		jungsung_data[i] = GL_NEW char[size];
		//is.read(jungsung_data[i]);
		MEMCPY(jungsung_data[i], Res_FontAddr, size);
		Res_FontAddr += size;
		size = 0;
	}
	
	
	for(i=0; i < S_FONT_JONGSUNG_SET; i++, index++)
	{
		for(int k=0; k < S_FONT_JONGSUNG_AMOUNT; k++)
		{
			size += jongsung_size[i][k];
		}
		
		jongsung_data[i] = GL_NEW char[size];
		//is.read(jongsung_data[i]);
		MEMCPY(jongsung_data[i], Res_FontAddr, size);
		Res_FontAddr += size;
		size = 0;
	}
	
	for(i=0; i < S_FONT_ALPHABET_SET; i++, index++)
	{
		for(int k=0; k < S_FONT_ALPHABET_AMOUNT; k++)
		{
			size += alphabet_size[i][k];
		}
		
		alphabet_data[i] = GL_NEW char[size];
		//is.read(alphabet_data[i]);
		MEMCPY(alphabet_data[i], Res_FontAddr, size);
		Res_FontAddr += size;
		size = 0;
	}
	
	for(int k=0; k < S_FONT_SYMBOL_AMOUNT; k++)
	{
		size += symbol_size[k];
	}
	
	symbol_data = GL_NEW char[size];
	//is.read(symbol_data);
	MEMCPY(symbol_data, Res_FontAddr, size);
	Res_FontAddr += size;
	size = 0;
	
	for(i=0; i < S_FONT_NUMBER_SET; i++, index++)
	{
		for(int k=0; k < S_FONT_NUMBER_AMOUNT; k++)
		{
			size += number_size[i][k];
		}
		
		number_data[i] = GL_NEW char[size];
		//is.read(number_data[i]);
		MEMCPY(number_data[i], Res_FontAddr, size);
		Res_FontAddr += size;
		size = 0;
	}
}

void S_KR_Font::initializeOffset(short* offset, char* argSize, int length)
{
	if (argSize == NULL)
	{
		offset = NULL;
	}
	
	short total = 0;
	MEMSET(offset, NULL, length * sizeof(short));
	for (int i = 0; i < length; i++)
	{
		offset[i] = total;
		total += argSize[i];
	}
}

void S_KR_Font::setColor(int argColor)
{
	foreColor = argColor;
	currentColorIndex = 0;//컬러인덱스를 0으로 초기화
	if(colorSet != NULL)
	{
		colorSet[0] = foreColor; 
	}
}

void S_KR_Font::setOutlineColor(int argColor)
{
	outlineColor = argColor;
	if (argColor == -1)
	{
		setOutline(false);
	}
	else
	{
		setOutline(true);
	}
}

void S_KR_Font::setOutline(bool argOutline)
{
	isOutlineDraw = argOutline;
}

void S_KR_Font::setZoom(int argZoom)
{
	zoom = argZoom;
}

void S_KR_Font::setLineSpace(int argSpace)
{
	lineSpace = argSpace;
}

int S_KR_Font::charWidth(char argChar) 
{
	if(argChar == ' ')
	{
		return S_FONT_BLANK_WIDTH * zoom;
	}
	else
	{
		char temp[2];
		MEMSET(temp, NULL, 2);
		temp[0] = argChar;
		return stringWidth(temp);
	}
}

int S_KR_Font::stringWidth(char* str)
{
	int strWidth = 0;
	unsigned char char_Index = NULL;
	int str_len = STRLEN(str);

	for (int i = 0; i < str_len; i++)
	{
		//if(argCharArray[i] == '^' && (i+1) < argLength)
		//{//컬러문자
		//	if(argCharArray[i+1] >= '0' && argCharArray[i+1] <= '9')
		//		currentColorIndex = argCharArray[i+1] - '0';
		//	i+=2;
		//}

		char_Index = str[i];

		if (char_Index == ' ')
		{
			if (strWidth == 0)
			{
				strWidth = 0;
			}
			else
			{
				strWidth += S_FONT_BLANK_WIDTH * zoom;
			}
		}
		//Note: by Wang Xiaomei, not sure about '\u00B1'
// 		else if(char_Index == 177)//'\u00B1')
// 		{
// 			if (strWidth == 0)
// 			{
// 				strWidth = 0;
// 			}		
// 			i++;
// 		}
		else if (char_Index > 128)
		{
			//version 1.0.1.0
			strWidth += getCharWidth(char_Index, 0);
			i += 2;
		}
		else
		{
			strWidth += getCharWidth(char_Index, 0);
		}
	}
	return strWidth;
}

void S_KR_Font::drawChar(char* argData, short* argOffset, char* argSize, 
					   int argIndex, int argX, int argY, bool isOutline)
{
	if (isOutline)
	{
		m_pGfx->SetColor(outlineColor);
		for (int i = argOffset[argIndex]; i < argOffset[argIndex] + argSize[argIndex]; i += 2)
		{
			
			pixelData[0] = (byte) ((argData[i] >> 4) & 0x0F);
			pixelData[1] = (byte) (argData[i] & 0x0F);
			pixelData[2] = (byte) ((argData[i + 1] >> 4) & 0x0F);
			pixelData[3] = (byte) (argData[i + 1] & 0x0F);
			
			m_pGfx->FillRect(argX + ((pixelData[0] - 1) * zoom), 
							 argY + ((pixelData[1] - 1) * zoom),
							 (pixelData[2] + 2) * zoom,
							 (pixelData[3] + 2) * zoom);
		}
	}
	else
	{
		m_pGfx->SetColor(foreColor);
		for (int i = argOffset[argIndex]; i < argOffset[argIndex] + argSize[argIndex]; i += 2)
		{
			
			pixelData[0] = (byte) ((argData[i] >> 4) & 0x0F);
			pixelData[1] = (byte) (argData[i] & 0x0F);
			pixelData[2] = (byte) ((argData[i + 1] >> 4) & 0x0F);
			pixelData[3] = (byte) (argData[i + 1] & 0x0F);
			
			m_pGfx->FillRect(argX + (pixelData[0]) * zoom,
							 argY + (pixelData[1]) * zoom, 
							 pixelData[2] * zoom,
							 pixelData[3] * zoom);
		}
	}
}


void S_KR_Font::drawChars(CGraphics* g, char* argCharArray, 
						int argX, int argY, 
						bool argOutline, bool argIsNewLine)
{
	m_pGfx = g;
	
	int choidx = 0, jungidx = 0, jongidx = 0;
	int code = 0;
	int fontXGap = 0;
	
	int argLength = STRLEN(argCharArray);
	
	unsigned char argChar_Index = NULL;
	
	for (int i = 0; i < argLength; i++)
	{
		if(argCharArray[i] == '^' && (i+1) < argLength)
		{//컬러문자
			if(argCharArray[i+1] >= '0' && argCharArray[i+1] <= '9')
				currentColorIndex = argCharArray[i+1] - '0';
			i+=2;
			if(i >= argLength)
				break;
		}

		argChar_Index = argCharArray[i];
		
		fontXGap = 0;
		
		if (argIsNewLine && (argX > (screenWidth - (S_FONT_DEFAULT_WIDTH * zoom) )))
		{
			argY = argY + (S_FONT_HEIGHT+lineSpace) * zoom;
			argX = defaultX;
			
			if (argY + S_FONT_HEIGHT * zoom > screenHeight)
			{
				break;
			}
		}
		
		//version 1.0.1.0
		if(colorSet != NULL)
		{
			foreColor = colorSet[currentColorIndex];
		}
		
		if ('0' <= argChar_Index && '9' >= argChar_Index)
		{
			drawChar(number_data[0], number_offset[0], number_size[0], (argChar_Index - 48), argX, argY, argOutline);
		}
		else if ('A' <= argChar_Index && 'Z' >= argChar_Index)
		{
			drawChar(alphabet_data[0], alphabet_offset[0], alphabet_size[0], (argChar_Index - 65), argX, argY, argOutline);
		}
		else if ('a' <= argChar_Index && 'z' >= argChar_Index)
		{
			drawChar(alphabet_data[1], alphabet_offset[1], alphabet_size[1], (argChar_Index - 97), argX, argY, argOutline);
		}
		else if (argChar_Index < 128)//('\uAC00' > argCharArray[i] || '\uD7A3' < argCharArray[i]) 
		{
			if (argChar_Index == '\r' || argChar_Index == '|' || argChar_Index == '\n') 
			{
				if(argIsNewLine)
				{
					argY = argY + (S_FONT_HEIGHT + lineSpace) * zoom;
					argX = defaultX;
				}
			}
			//version 1.0.1.0
			//Note: by Wang Xiaomei, not sure about '\u00B1'
// 			else if(argChar_Index == 177)//argCharArray[i] == '\u00B1')
// 			{
// 				currentColorIndex = argCharArray[++i] - '0';
// 				continue;
// 			}
			else if (argChar_Index != ' ')
			{
				drawChar(symbol_data, symbol_offset, symbol_size, getSymbolIndex(argChar_Index), argX, argY, argOutline);
			}
		}
		else if (argChar_Index > 128) //(argCharArray[i] >= '\uAC00' && argCharArray[i] <= '\uD7A3') // 
		{
			//code = (int) argChar_Index;//argCharArray[i];
			//added by Wang Xiaomei
			if ((i + 3) > argLength)
			{
				return ;
			}
			fontXGap = 1;
			code = (((short int)((unsigned char)(argCharArray[i] << 4) | (unsigned char)((argCharArray[i+1] & 0x3C) ) >> 2) << 8) | (short int)((unsigned char)(argCharArray[i+1] << 6) | (unsigned char)(argCharArray[i+2] & 0x3F)));
			
			code -= 0xac00;
			choidx = (code / (21 * 28)); // cho-sung index (0~18)
			jungidx = (code / 28) % 21; // jung-sung index (0~20)
			jongidx = code % 28; // jong-sung index (0~27)
			
		
			if (jongidx == 0) 
			{
				decideChosung_NoJongsung(jungidx);
				
				drawChar(chosung_data[choSetNum], chosung_offset[choSetNum], chosung_size[choSetNum], 
					choidx, argX, argY, argOutline);
				
				drawChar(jungsung_data[jungSetNum], jungsung_offset[jungSetNum], jungsung_size[jungSetNum], 
					jungidx, argX, argY, argOutline);
			}
			else
			{
				decideChosung_Jongsung(jungidx);
				
				drawChar(chosung_data[choSetNum], chosung_offset[choSetNum], chosung_size[choSetNum], 
					choidx, argX, argY, argOutline);
				
				drawChar(jungsung_data[jungSetNum], jungsung_offset[jungSetNum], jungsung_size[jungSetNum], 
					jungidx, argX, argY, argOutline);
				
				drawChar(jongsung_data[jongSetNum], jongsung_offset[jongSetNum], jongsung_size[jongSetNum], 
					jongidx, argX, argY, argOutline);
			}
		}
		
		if(argChar_Index == ' ' && argX == defaultX)
		{
			argX = getCharWidth(argChar_Index, argX);
		}
		else
		{
			argX += getCharWidth(argChar_Index, argX);
		}
		if (fontXGap == 1)
		{
			i += 2;
		}
	}
	
	if (!argOutline)
	{
		nextX = argX;
		nextY = argY;
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////
// this function can draw the strings without alignment
// if strings exceeds one line and has some separator, argIsNewLine must be true;
// the separators could be found in function drawChars
// now separators are '\r' ||   '|' ||   '\n'
//////////////////////////////////////////////////////////////////////////////////////////

void S_KR_Font::drawStr(CGraphics* g, char* argStr, int argX, int argY, bool argIsNewLine)
{
	m_pGfx = g;
	defaultX = argX;
	
	if(isOutlineDraw)
	{
		drawChars(g, argStr, argX, argY, true, argIsNewLine);
	}
	
	drawChars(g, argStr, argX, argY, false, argIsNewLine);
}

//////////////////////////////////////////////////////////////////////////////////////////
// this function can draw the strings with alignment
// so it can not draw multiline-strings
//////////////////////////////////////////////////////////////////////////////////////////
void S_KR_Font::drawStrings(CGraphics* g, char* argStr, int argX, int argY, int argAnchor, bool isNewLine)
{
	if(!argStr)
	{
		return;
	}
	m_pGfx = g;
	
	int strWidth = getKStrWidth(argStr);

	
	if ((argAnchor & ANCHOR_HCENTER) != 0) //== ANCHOR_HCENTER)
	{
		argX -= (strWidth >> 1);
	}
	else if ((argAnchor & ANCHOR_RIGHT) != 0)// == ANCHOR_RIGHT)
	{
		argX -= strWidth;
	}
	
	if ((argAnchor & ANCHOR_VCENTER) != 0)// == ANCHOR_VCENTER)
	{
		argY -= (S_FONT_HEIGHT >> 1);
	}
	else if ((argAnchor & ANCHOR_BOTTOM) != 0)// == Graphics.BOTTOM)
	{
		argY -= S_FONT_HEIGHT;
	}
	
	drawStr(g, argStr, argX, argY, isNewLine);
}

////////////////////////////////////////////////////////////////////////////
// just to calculate the position to break
int S_KR_Font::KStringWrap(const char* str, int width)//이부분 값이 이상하게 넘어옴
{
	MEMSET(m_stringWrapped, NULL, MAX_KTEXT_LENGTH);
	int lines = 0;
	int start = 0;
	int end = 0;
	const char *dest = str;
	int length = STRLEN(str);

	int lastToken = 0;
	int curToken = 0;
	int stringIndex = 0;
	char tempChar[MAX_KTEXT_LENGTH];
	int lineSize = 0;
	for(int xx = 0;xx<MAX_KTEXT_MAXLINE;xx++){wPixel[xx]=0;}

	for(int i = 0; i < length  && lines < MAX_KTEXT_LINES-2; i++)
	{
		//if(str[i] != '|' /*&& str[i] != '^'*/ && str[i] !='#' && str[i] !=' ')
		//{
		//	m_stringWrapped[stringIndex] = str[i];
		//	++stringIndex;
		//}
		//else 
		{
			lastToken = curToken;
		//	if (str[i] == ' ')
			{
				m_stringWrapped[stringIndex] = str[i];
				++stringIndex;
			}
			if (str[i] == '^' && i+1 < length){//컬러문자
				if(str[i+1] >= '0' && str[i+1] <= '9'){
					i++;
					m_stringWrapped[stringIndex] = str[i];
					++stringIndex;
					i++;
					m_stringWrapped[stringIndex] = str[i];
					++stringIndex;
				}
			}
			

			
			curToken = stringIndex;
			//to judge whether the words before the \n is too long for a line
			MEMSET(tempChar, NULL, MAX_KTEXT_LENGTH);
			MEMCPY(tempChar, (m_stringWrapped + start), stringIndex - start);
			lineSize = getKStrWidth(tempChar);
			if (lineSize >= width)
			{
				m_off[++lines] = lastToken;
				start = lastToken;
			}
			//when meet with '\n', wrap here without condition...
			if ( str[i] == '|')
			{
				m_off[++lines] = curToken;
				start = curToken;
				lastToken = curToken;
			}

			if(lines<MAX_KTEXT_MAXLINE){//각 줄의 픽셀 길이
				wPixel[lines] = lineSize;
			}

		}
	}


	m_stringWrapped[stringIndex] = '\0';
	//To handle the remaining text...
	MEMSET(tempChar, NULL, MAX_KTEXT_LENGTH);
	MEMCPY(tempChar, (m_stringWrapped + start), stringIndex - start);
	lineSize = getKStrWidth(tempChar);
	if (lineSize >= width)
	{
		m_off[++lines] = curToken;
	}
	m_off[++lines] = stringIndex;

	return lines;
}

void S_KR_Font::delKStrWrap(const char* str)
{
	MEMSET(m_stringDelWrap, NULL, MAX_KTEXT_LENGTH);
	char* dest = m_stringDelWrap;
	int length = STRLEN(str);
	for (int i = 0; i < length; ++i)
	{
		if (str[i] == '^')
		{
			i++;
		}else if (str[i] != '|' && str[i] !='#' )
		{
			*dest = str[i];
			++dest;
		}

	}
	*dest = '\0'; 
}

int S_KR_Font::getKStrWidth(char* str)
{
	delKStrWrap(str);
	return	stringWidth(m_stringDelWrap);

}

int S_KR_Font::DrawText(CGraphics* g, char* str, int posX, int posY, int argAnchor, char* N0, char* N1, char* N2){
	
	int width = 0, startLine = 0, LineCount = 0;
	char tempStr[MAX_KTEXT_LENGTH];

	{// Dry Setting & init
		width = (s_DrawType.wrap_Width?s_DrawType.wrap_Width:1024);		// 0 이라면 충분한 픽셀을 잡아준다
		startLine = s_DrawType.startLine;
		LineCount = (s_DrawType.LineCount?s_DrawType.LineCount:1024);	// 0 이라면 충분한 픽셀을 잡아준다

		s_DrawType.wrap_Width = s_DrawType.startLine = s_DrawType.LineCount = 0;
	}

	{// Insert Text Change & init

		if(N0 || N1 || N2){//N0, N1, N2 3개의 삽입문자중 한개라도 사용한다면

			MEMSET(tempStr, NULL, MAX_KTEXT_LENGTH);
			//MEMSET(tempChar, NULL, MAX_KTEXT_LENGTH);

			for (int xx = 0,yy = 0, argLength = STRLEN(str); xx < argLength; xx++,yy++){
				if(str[xx] == 'N' && (xx+1) < argLength){
					switch(str[xx+1]){
						case '0':
							if(N0){//N0 캐스팅이 있다면
								for(int zz = 0, N0_Length = STRLEN(N0) ; zz<N0_Length  ; yy++,zz++,argLength++){
									tempStr[yy]=N0[zz];
								}
							}
							xx+=2;
							break;
						case '1':
							if(N1){//N1 캐스팅이 있다면
								for(int zz = 0, N1_Length = STRLEN(N1) ; zz<N1_Length  ; yy++,zz++,argLength++){
									tempStr[yy]=N1[zz];
								}
							}
							xx+=2;
							break;
						case '2':
							if(N2){//N2 캐스팅이 있다면
								for(int zz = 0, N2_Length = STRLEN(N2) ; zz<N2_Length  ; yy++,zz++,argLength++){
									tempStr[yy]=N2[zz];
								}
							}
							xx+=2;
							break;
					}
				}
				tempStr[yy] = str[xx];
			}
			str = tempStr;
		}

	}

	lines = KStringWrap(str, width);//width 단위로 잘랐을때 최대 몇줄이 되는지 계산 & m_stringWrapped 버퍼에 변환
	

	for (int j = startLine,x_left = posX ; j < lines && j< (startLine+LineCount) ; j++)
	{
		MEMSET(tempStr, NULL, MAX_KTEXT_LENGTH);
		MEMCPY(tempStr, m_stringWrapped + m_off[j] , m_off[j+1] - m_off[j]);

		drawStrings(g, tempStr, posX,
			posY + (j-startLine) * (S_FONT_HEIGHT + lineSpace),
			argAnchor);
	}

	return lines;
}
