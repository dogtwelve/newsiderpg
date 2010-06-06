/**
 * FontDataGenerator 에서 생성되는 소스 입니다.
 * 본 파일의 version은 FontDataGenerator의 버전과 일치하니, 버전을 확인후 사용하세요.
 * version 1.0.1.2 이하 버전에서는 줄바꿈 관련 일부 버그가 존재합니다.
 * 
 * @version 1.0.1.5
 * 
 */
public abstract class FontData 
{
	final static int FONT_WIDTH = 8;
	final static int FONT_HEIGHT = 10;
	
	final static int CHOSUNG_AMOUNT = 19;
	final static int JUNGSUNG_AMOUNT = 21;
	final static int JONGSUNG_AMOUNT = 28;
	final static int ALPHABET_AMOUNT = 26;
	
	final static int SYMBOL_AMOUNT = 48;
	final static int NUMBER_AMOUNT = 10;
	
	final static int CHOSUNG_SET = 18;
	final static int JUNGSUNG_SET = 3;
	final static int JONGSUNG_SET = 7;
	final static int ALPHABET_SET = 2;
	final static int SYMBOL_SET = 1;
	final static int NUMBER_SET = 1;
	
	//각 문자 종류별 width 입니다.
	//각각의 문자가 너무 붙어서 출력되면 수치를 조금 늘려서 사용하세요.
	final static int DEFAULT_FONT_WIDTH = 9;

	final static int HANGEUL_DEFAULT_WIDTH = 9;
	
	final static int ALPHABET_UPPER_DEFAULT_WIDTH = 6;
	final static int ALPHABET_LOWER_DEFAULT_WIDTH = 6;
	
	final static int NUMBER_DEFAULT_WIDTH = 5;
	final static int SYMBOL_DEFAULT_WIDTH = 7;
	//end - 각 문자 종류별 width

	final static int BLANK_WIDTH = 5;
	
	protected int choSetNum;
	protected int jungSetNum;
	protected int jongSetNum;
	
	protected int defaultX;
	
	protected int zoom = 1;
	
	
	protected void decideChosung_NoJongsung(int argJungIndex)
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
	
	
	protected void decideChosung_Jongsung(int argJungIndex)
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
	
	
	protected int getSymbolIndex(int argSymbol)
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
			case 92:	// \
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
	
	protected int getCharWidth(char argChar, int argX)
	{
		int result = 0;

		if (argChar >= '\uAC00' && argChar <= '\uD7A3')
		{
			//			argX = argX + NEXT_FONT_WIDTH * zoom;
			result =  HANGEUL_DEFAULT_WIDTH;
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
						result = ALPHABET_UPPER_DEFAULT_WIDTH;
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
						result = ALPHABET_LOWER_DEFAULT_WIDTH;
						break;
				}
			}
			else if (argChar == ' ')
			{
				if (argX == defaultX)
					result = defaultX;
				else
					result =  BLANK_WIDTH;
			}
			else if (argChar >= '0' && argChar <= '9')
			{
				switch(argChar)
				{

					default:
						result = NUMBER_DEFAULT_WIDTH;
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
				case 92:	// \
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

					//default:
					//	result = SYMBOL_DEFAULT_WIDTH;
					//	break;
				}
				
				//fixed bug in ver 1.0.1.3
				if(result == 0 && argChar != '|' && argChar != '\r' && argChar != '\n')
                    result = SYMBOL_DEFAULT_WIDTH;
			}
		}


		return result*zoom;
	}
}
