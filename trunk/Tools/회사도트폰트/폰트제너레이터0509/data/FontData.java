/**
 * FontDataGenerator 에서 생성되는 소스 입니다.
 * 본 파일의 version은 FontDataGenerator의 버전과 일치하니, 버전을 확인후 사용하세요.
 * version 1.0.1.2 이하 버전에서는 줄바꿈 관련 일부 버그가 존재합니다.
 * 
 * @version #VERSION
 * 
 */
public abstract class FontData 
{
	final static int FONT_WIDTH = #FONT_WIDTH;
	final static int FONT_HEIGHT = #FONT_HEIGHT;
	
	final static int CHOSUNG_AMOUNT = 19;
	final static int JUNGSUNG_AMOUNT = 21;
	final static int JONGSUNG_AMOUNT = 28;
	final static int ALPHABET_AMOUNT = 26;
	
	final static int SYMBOL_AMOUNT = #SYMBOL_AMOUNT;
	final static int NUMBER_AMOUNT = 10;
	
	final static int CHOSUNG_SET = #CHOSUNG_SET;
	final static int JUNGSUNG_SET = #JUNGSUNG_SET;
	final static int JONGSUNG_SET = #JONGSUNG_SET;
	final static int ALPHABET_SET = #ALPHABET_SET;
	final static int SYMBOL_SET = #SYMBOL_SET;
	final static int NUMBER_SET = #NUMBER_SET;
	
	//각 문자 종류별 width 입니다.
	//각각의 문자가 너무 붙어서 출력되면 수치를 조금 늘려서 사용하세요.
	final static int DEFAULT_FONT_WIDTH = #DEFAULT_FONT_WIDTH;

	final static int HANGEUL_DEFAULT_WIDTH = #HANGEUL_DEFAULT_WIDTH;
	
	final static int ALPHABET_UPPER_DEFAULT_WIDTH = #ALPHABET_UPPER_DEFAULT_WIDTH;
	final static int ALPHABET_LOWER_DEFAULT_WIDTH = #ALPHABET_LOWER_DEFAULT_WIDTH;
	
	final static int NUMBER_DEFAULT_WIDTH = #NUMBER_DEFAULT_WIDTH;
	final static int SYMBOL_DEFAULT_WIDTH = #SYMBOL_DEFAULT_WIDTH;
	//end - 각 문자 종류별 width

	final static int BLANK_WIDTH = #BLANK_WIDTH;
	
	protected int choSetNum;
	protected int jungSetNum;
	protected int jongSetNum;
	
	protected int defaultX;
	
	protected int zoom = 1;
	
	
	protected void decideChosung_NoJongsung(int argJungIndex)
	{
		switch (argJungIndex)
		{
#decideChosung_NoJongsung
		}
		
	}
	
	
	protected void decideChosung_Jongsung(int argJungIndex)
	{
		switch (argJungIndex)
		{
#decideChosung_Jongsung
		}
	}
	
	
	protected int getSymbolIndex(int argSymbol)
	{
		int returnIndex = #defaultSymbol;
		
		switch (argSymbol)
		{
#getSymbolIndex
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
#AlphabetUpperWidth
					default:
						result = ALPHABET_UPPER_DEFAULT_WIDTH;
						break;
				}
			}
			else if (argChar >= 'a' && argChar <= 'z')
			{
				switch(argChar)
				{
#AlphabetLowerWidth
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
#NumberWidth
					default:
						result = NUMBER_DEFAULT_WIDTH;
						break;
				}
			}
			else
			{
				switch(argChar)
				{
#SymbolWidth
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
