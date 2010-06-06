#include "cKRConvert.h"

int ConvertKSC5601toUTF16( unsigned char *chKSC5601_, int iKSC5601Size_, unsigned char *chUTF16_ )
{
	int x_=0, y_=0, tab_idx = 0, i = 0, code_ucs2 = 0;

	int count = 0;

	while( iKSC5601Size_ )
	{
		if( *chKSC5601_ >= 0xB0 && *chKSC5601_ <= 0xC8 )//한글이라면
		{
			x_ = ((int)*chKSC5601_++ - 0x00a1) * 94;
			y_ = (int)*chKSC5601_++ - 0x00a1;

			tab_idx = x_ + y_;

			if (tab_idx >= 0 && tab_idx < ksc5601max) 
			{
				code_ucs2 = tabksc5601[tab_idx];

				*chUTF16_++ = (unsigned char)(code_ucs2>>8);
				*chUTF16_++ = (unsigned char)(code_ucs2);

				iKSC5601Size_ -= 2;
			}
		}
		else if( *chKSC5601_ >= 0xA4 && ( *(chKSC5601_+1) >= 0xA1 && *(chKSC5601_+1) <= 0xD3 ) )//자음 모음만
		{
			*chUTF16_++ = (unsigned char)0x00;
			*chUTF16_++ = (unsigned char)0x3F;
			
			chKSC5601_ += 2;

			iKSC5601Size_ -= 2;
		}
		else
		{
			*chUTF16_++ = (unsigned char)0x00;
			*chUTF16_++ = *chKSC5601_++;

			--iKSC5601Size_;
		}

		count += 2;
	}

	return count;
}

unsigned char * init_utf(unsigned char *q, int i)
{
	//memset(q, 0x00, i*2);

	/**q = 0xEF;
	*(q + 1) = 0xBB;
	*(q + 2) = 0xBF;

	q += 3;*/

	return q;
}

int confirm_unicode(unsigned char *p)
{
	if( (*p == 0xFF) && (*(p+1) == 0xFE) )
		return LITTLE_ENDIAN;
	else 
		return BIG_ENDIAN;
}

unsigned short make_syllable(unsigned char *p, int flag)
{
	int k;
	if( flag == LITTLE_ENDIAN ) {
		k = ((unsigned short)*(p+1) << 8);
		k = k | (unsigned short)*p;
	}
	else 
	{
		k = ((unsigned short)*p << 8);
		k = k | (unsigned short)*(p+1);
	}

	return k;
}

int make_utf(unsigned char *q, unsigned short k, int flag)
{
	// unicode가
	// 0x0000이면서 변환 방식이 UTF-7인 경우
	if( (flag == CONVUTF_7) && (k == 0x0000) ) 
	{
		*q = *q | 0xC0;
		*q = *q | (unsigned char)((k & 0x07C0) >> 6);
		
		*(q+1) = *(q+1) | 0x80;
		*(q+1) = *(q+1) | (unsigned char)(k & 0x003F);
		
		return CONVERT_TWO;
	}
	// 0x0000이면서 변환 방식이 UTF-8인 경우
	else if( (flag == CONVUTF_8) && (k == 0x0000) ) 
	{
		*q = (unsigned char)k;
		return CONVERT_ONE;
	}
	// 0x0001부터 0x007F까지
	else if( (k > 0x0000) && (k <= 0x007F) )
	{
		*q = (unsigned char)k;
		return CONVERT_ONE;
	}
	// 0x0081부터 0x07FF까지
	else if( (k >= 0x0080) && (k <= 0x07FF) ) 
	{
		*q = *q | 0xC0;
		*q = *q | (unsigned char)((k & 0x07C0) >> 6);
		
		*(q+1) = *(q+1) | 0x80;
		*(q+1) = *(q+1) | (unsigned char)(k & 0x003F);
		
		return CONVERT_TWO;
	}
	// 0x0800부터 0xFFFF까지
	else if( (k >= 0x0800) && (k <= 0xFFFF) ) 
	{
		*q = *q | 0xE0;
		*q = *q | (unsigned char)((k & 0xF000) >> 12);
				
		*(q+1) = *(q+1) | 0x80;
		*(q+1) = *(q+1) | (unsigned char)((k & 0x0FC0) >> 6);
				
		*(q+2) = *(q+2) | 0x80;
		*(q+2) = *(q+2) | (unsigned char)(k & 0x003F);
		
		return CONVERT_THREE;
	}
	// 0x00010000 이상은 제외
	else 
	{
	}

	return CONVERT_FAIL;
}

int ConvertUTF16toUTF8( unsigned char *unicode, unsigned char *utf, int i, int flag )
{
	int t, j;

	unsigned char *p, *q;
	unsigned short k;
	
	p = unicode;
	q = utf;

	int count=0;

	//q = init_utf(q, i);

	// a -> 61 00
	if( confirm_unicode(p) == LITTLE_ENDIAN) 
	{
		for(t = 2; t < i; t += 2) 
		{
			k = make_syllable((p+t), LITTLE_ENDIAN);
			j = make_utf(q, k, flag);
			q += j;
		}
	}
	// a -> 00 61
	else 
	{
		for(t = 0; t < i; t += 2) 
		{
			k = make_syllable((p+t), BIG_ENDIAN);
			j = make_utf(q, k, flag);
			q += j;
			count += j;
		}
	}

	return count;
}