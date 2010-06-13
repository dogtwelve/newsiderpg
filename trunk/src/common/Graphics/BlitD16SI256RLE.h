// Copyright (C) 2007 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Lu Yan

//void BlitD16SI256RLEK(void *dst, void *src, BlitParam *par)
//{
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
//#ifdef BLIT_HAS_ALPHA
//	unsigned int *pal = (unsigned int*)par->palette;
//#else
//	unsigned short *pal = (unsigned short*)par->palette;
//#endif
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	const int dx = par->dstXPitch;
	const int ey = par->width * dx;
	const int dy = par->dstYPitch - ey;//par->width * dx;
	const int sy = par->srcYPitch - par->width;	//sx == 1
	const int w  = par->width;
	const int h  = par->height;
#ifdef BLIT_HAS_COLOR_KEY
	const unsigned int key = par->colorKey;
#endif

#ifdef BLIT_HAS_OPACITY
	const int o = par->opacity;
#endif

	unsigned short *e = NULL;

	if(par->srcSkip < 0)	//the whole source image will be blit, no clipping
	{
		int count;
		unsigned int index;
		
		int i = h;
		e = (unsigned short*)((char*)d + ey);
		while(true)
		 {//이러한 복잡 다분화된 코드는 RLE 압축 을 해제하는과정에서 동일색상 연속 프린팅을 쓰기때문
			count = *s++;

			if (count >= 128)
			{
				count -= 128;
				while (--count >= 0)
				{
					index = *s++;
#ifdef BLIT_HAS_COLOR_KEY
					if ((pal[index] & 0xFFFF) != key)
#endif
					{
						//*d = pal[index];
						BLIT_BLEND_COLOR(*d, (unsigned short)pal[index], o);
					}
					d = (unsigned short*)((char*)d + dx);
					if(d == e )
					{
						if (--i <= 0)
							return;
						d = (unsigned short*)((char*)d + dy);
						e = (unsigned short*)((char*)d + ey);
					}
				}
			}
			else
			{
				index = *s++;
#ifdef BLIT_HAS_COLOR_KEY
				if((pal[index] & 0xFFFF) == key)
				{
					while(--count >= 0)
					{	
						d = (unsigned short*)((char*)d + dx);
						if(d == e )
						{
							if (--i <= 0)
								return;
							d = (unsigned short*)((char*)d + dy);
							e = (unsigned short*)((char*)d + ey);
						}
					}
				}
				else
#endif
				{
					while(--count >= 0)
					{	
						//*d = pal[index];
						BLIT_BLEND_COLOR(*d, (unsigned short)pal[index], o);
						d = (unsigned short*)((char*)d + dx);
						if(d == e )
						{
							if (--i <= 0)
								return;
							d = (unsigned short*)((char*)d + dy);
							e = (unsigned short*)((char*)d + ey);
						}
					}
				}
			}
		}
	}
	else	//when clipping occurs
	{
		int count;
		unsigned int index;
		
		int t = par->srcSkip;
		do
		{
			count = *s++;
			if (count < 128)
			{
				t -= count;
				++s;
			}
			else
			{
				t -= count - 128;
				s += count - 128;
			}
		}while (t >= 0);
		if (count < 128)
		{
			count = -t;
			--s;
		}
		else
		{
			count = 128 - t;
			s += t;
		}
		
		int i = h;
		e = (unsigned short*)((char*)d + ey);
		while(true)
		{
			if (count >= 128)
			{
				count -= 128;
				while (--count >= 0)
				{
					index = *s++;
#ifdef BLIT_HAS_COLOR_KEY
					if ((pal[index] & 0xFFFF) != key)
#endif
					{
						//*d = pal[index];
						BLIT_BLEND_COLOR(*d, (unsigned short)pal[index], o);
					}
					d = (unsigned short*)((char*)d + dx);
					if(d == e )
					{
						t = sy - count;
						s += count;
						count += 128;
						break;
					}
				}
			}
			else
			{
				index = *s++;
#ifdef BLIT_HAS_COLOR_KEY
				if((pal[index] & 0xFFFF) == key)
				{
					while(--count >= 0)
					{	
						d = (unsigned short*)((char*)d + dx);
						if(d == e )
						{
							t = sy - count;
							break;
						}
					}
				}
				else
#endif
				{
					while(--count >= 0)
					{	
						//*d = pal[index];

						BLIT_BLEND_COLOR(*d, (unsigned short)pal[index], o);
						d = (unsigned short*)((char*)d + dx);
						if(d == e )
						{
							t = sy - count;
							break;
						}
					}
				}
			}
			if(d == e )
			{
				if (--i <= 0)
					return;
				d = (unsigned short*)((char*)d + dy);
				e = (unsigned short*)((char*)d + ey);

				while (t >= 0)
				{
					count = *s++;
					if (count < 128)
					{
						t -= count;
						++s;
					}
					else
					{
						t -= count - 128;
						s += count - 128;
					}
				}
				if (count < 128)
				{
					count = -t;
					--s;
				}
				else
				{
					count = 128 - t;
					s += t;
				}
			}
			else
			{
				count = *s++;
			}
		}
	}
//}
