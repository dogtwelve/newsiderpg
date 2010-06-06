// Copyright (C) 2007 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Lu Yan

//void BlitD16SI64RLE(void *dst, void *src, BlitParam *par)
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
	const unsigned int palBit = par->palBits;
	const unsigned int palMask = par->palMask;

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
		{
			count = *s >> palBit;
			index = *s & palMask;
			
#ifdef BLIT_HAS_COLOR_KEY
			if((pal[index] & 0xFFFF) == key)
			{
				while(count-- >= 0)
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
				while(count-- >= 0)
				{
					//*d = pal[index];
					
					BLIT_BLEND_COLOR(*d, pal[index], o);
					
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
			++s;
		}
	}
	else	//when clipping occurs
	{
		int count;
		unsigned int index;
		
		int t = par->srcSkip;//m_width * sy + sx;
		do
		{
			t -= (*s >> palBit) + 1;
			++s;
		}while (t >= 0);
		count = -t - 1;
		--s;
		index = *s & palMask;
		
		int i = h;
		e = (unsigned short*)((char*)d + ey);
		while(true)
		{
#ifdef BLIT_HAS_COLOR_KEY
			if((pal[index] & 0xFFFF) == key)
			{
				while(count-- >= 0)
				{	
					d = (unsigned short*)((char*)d + dx);					
					if(d == e )
						break;
				}
			}
			else
			{
				while(count-- >= 0)
				{	
					//*d = pal[index];
					
					BLIT_BLEND_COLOR(*d, pal[index], o);
					
					
					d = (unsigned short*)((char*)d + dx);					
					if(d == e )
						break;
				}
			}
			if(d == e )
			{
				if (--i <= 0)
					return;
				d = (unsigned short*)((char*)d + dy);				
				e = (unsigned short*)((char*)d + ey);
				t = sy - count - 1;
				while (t >= 0)
				{
					++s;
					t -= (*s >> palBit) + 1;
				}
				count = -t - 1;
			}
			else
			{
				++s;
				count = *s >> palBit;
			}
			index = *s & palMask;
#else
			while(count-- >= 0)
			{	
				//*d = pal[index];
					
				BLIT_BLEND_COLOR(*d, pal[index], o);
				
				d = (unsigned short*)((char*)d + dx);				
				if(d == e )
				{
					if (--i <= 0)
						return;
					d = (unsigned short*)((char*)d + dy);					
					e = (unsigned short*)((char*)d + ey);
					t = sy - count - 1;
					while (t >= 0)
					{
						++s;
						t -= (*s >> palBit) + 1;
					}
					count = -t - 1;
					index = *s & palMask;
				}
			}
			++s;
			count = *s >> palBit;
			index = *s & palMask;
#endif
		}
	}
//}
