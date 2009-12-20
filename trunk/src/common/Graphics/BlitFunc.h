//Blit functions, included by Graphics.cpp  SangHo

#define BLIT_BLEND_COLOR_OPACITY(dst, src, opa)		ALPHA_BLEND_S16_D16(dst, dst, src, opa)

#define BLIT_BLEND_COLOR_ALPHA(dst, src) {\
	unsigned int c = src;\
	unsigned int a = c >> 24;\
	unsigned int fg = c & 0xFFFF;\
	if (0xFF == a)\
	dst = fg;\
	else if (0 != a) {\
	unsigned int bg = dst;\
	ALPHA_BLEND_S16_D16(dst, bg, fg, a);\
	}\
}

#define BLIT_BLEND_COLOR_OPACITY_COLOR(dst, src, opa) {\
	const unsigned int rMask = 0xF800;\
	const unsigned int gMask = 0x7E0;\
	const unsigned int bMask = 0x1f;\
	const unsigned int col = par->p_color;\
	const unsigned int ar = (rMask & ((col >> 8) & 0xF800) ) * opa / ALPHA_DEVISOR;\
	const unsigned int ag = (gMask & ((col >> 5) & 0xFE0)) * opa / ALPHA_DEVISOR;\
	const unsigned int ab = (bMask & ((col >> 3) & 0x1F)) * opa / ALPHA_DEVISOR;\
	const unsigned int alpha = ALPHA_DEVISOR - opa;\
	unsigned int c = src;\
	unsigned int fg = c & 0xFFFF;\
	int r = ar + (fg & rMask) * alpha / ALPHA_DEVISOR;\
	int g = ag + (fg & gMask) * alpha / ALPHA_DEVISOR;\
	int b = ab + (fg & bMask) * alpha / ALPHA_DEVISOR;\
	dst =  (unsigned short)((r & rMask) | (g & gMask) | (b & bMask));\
}

#define BLIT_BLEND_COLOR_GRAY(dst, src) {\
	int	nR = (src & 0xF000) >> 12;\
	int	nG = (src & 0x0780) >> 7;\
	int	nB = (src & 0x001E) >> 1;\
	int nGray = ((nR * 5) + (nG * 9) + (nB << 1)) >> 4;\
	if(nGray > 15)\
	nGray = 15;\
	dst = (nGray << 12) | (nGray << 7) | (nGray << 1);\
}



#define BLIT_BLEND_COLOR_OPACITY_ALPHA(dst, src, opa) {\
	unsigned int c = src;\
	unsigned int a = (c >> 24) * opa / ALPHA_DEVISOR;\
	unsigned int fg = c & 0xFFFF;\
	if (0xFF == a)\
	dst = fg;\
	else if (0 != a) {\
	unsigned int bg = dst;\
	ALPHA_BLEND_S16_D16(dst, bg, fg, a);\
	}\
}







//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void BlitD16S4P(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int c = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

void BlitD16S4PK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel
	const unsigned int key = par->colorKey;

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int c = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

void BlitD16S4PA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT && defined ENABLE_PALETTE_ALPHA_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;	//8 bit alpha, 8 bit 0, and 16 bit color
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j > 0)
		{
			unsigned int c = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			unsigned int a = c >> 24;
			unsigned int fg = c & 0xFFFF;
			if (0xFF == a)
				*d = fg;
			else if (0 != a)
			{
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, a);
			}
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

void BlitD16S4PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT && defined ENABLE_OPACITY_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel

	const int o = par->opacity;

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int fg = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			unsigned int bg = *d;
			ALPHA_BLEND_S16_D16(*d, bg, fg, o);
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

void BlitD16S4PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT && defined ENABLE_OPACITY_BLIT 
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel
	const unsigned int key = par->colorKey;

	const unsigned int o = par->opacity;

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int c = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			if(c != key)
			{
				unsigned int fg = c;
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, o);
			}
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

void BlitD16S4PAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_4_BLIT && defined ENABLE_OPACITY_BLIT && defined ENABLE_PALETTE_ALPHA_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;	//8 bit alpha, 8 bit 0, and 16 bit color
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;	//in pixel

	const unsigned int o = par->opacity;

	int skip = par->srcSkip;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j > 0)
		{
			unsigned int c = (skip & 1) ? pal[s[skip >> 1] & 0x0F] : pal[s[skip >> 1] >> 4];
			unsigned int a = (c >> 24) * o / ALPHA_DEVISOR;
			unsigned int fg = c & 0xFFFF;
			if (0xFF == a)
				*d = fg;
			else if (0 != a)
			{
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, a);
			}
			d = (unsigned short*)((char*)d + dx);
			++skip, --j;
		}
		skip += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	DISABLE_ASSERT
#endif
}

//void BlitD8S8(void *dst, void *src, BlitParam *par)
//{
//	unsigned char *d = (unsigned char*)dst;
//	unsigned char *s = (unsigned char*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		//Unroll the following loop in asm code
//		while(j != 0)
//		{
//			*d = *s++;
//			d += dx;
//			--j;
//		}
//		s += sy;
//		d += dy;
//	}
//}
//
//void BlitD8S8K(void *dst, void *src, BlitParam *par)
//{
//	unsigned char *d = (unsigned char*)dst;
//	unsigned char *s = (unsigned char*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		//Unroll the following loop in asm code
//		while(j != 0)
//		{
//			unsigned char v = *s++;
//			if(v != par->colorKey)
//				*d = v;
//			d += dx;
//			--j;
//		}
//		s += sy;
//		d += dy;
//	}
//}

void BlitD16S8P(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	//unsigned short *pal = (unsigned short*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;

	//const unsigned int palBit = par->palBits;
	//const unsigned int palMask = par->palMask;

	//int fg = 8 - par->palBits;	

	ASSERT(par->height > 0);
	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j >= 4)
		{
			*d = pal[*s++];
			d = (unsigned short*)((char*)d + dx);
			*d = pal[*s++];
			d = (unsigned short*)((char*)d + dx);
			*d = pal[*s++];
			d = (unsigned short*)((char*)d + dx);
			*d = pal[*s++];
			d = (unsigned short*)((char*)d + dx);
			j -= 4;
		}
		while(j != 0)
		{
			*d = pal[*s++];//((*s)>>fg)&palMask];
			d = (unsigned short*)((char*)d + dx);			
			--j;
		}
		s += sy;
		d = (unsigned short*)((char*)d + dy);
	}
}

//void BlitD24S8P(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned int *pal = (unsigned int*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//	
//	ASSERT(par->height > 0);
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j >= 4)
//		{
//			*d = pal[*s++];
//			d = (unsigned int*)((char*)d + dx);
//			*d = pal[*s++];
//			d = (unsigned int*)((char*)d + dx);
//			*d = pal[*s++];
//			d = (unsigned int*)((char*)d + dx);
//			*d = pal[*s++];
//			d = (unsigned int*)((char*)d + dx);
//			j -= 4;
//		}
//		while(j != 0)
//		{
//			*d = pal[*s++];
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s += sy;
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S8PO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned short *pal = (unsigned short*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = pal[*s++];
//			unsigned int bg = *d;
//			ALPHA_BLEND_S12_D12(*d, bg, fg, a);
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}
//
//void BlitD16S8PO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned short *pal = (unsigned short*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = pal[*s++];
//			unsigned int bg = *d;
//			ALPHA_BLEND_S16_D16(*d, bg, fg, a);
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}

//void BlitD24S8PO(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned int *pal = (unsigned int*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = pal[*s++];
//			unsigned int bg = *d;
//			ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

void BlitD16S8PK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	//unsigned short *pal = (unsigned short*)par->palette;
 	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;
	const unsigned int key = par->colorKey;
	
	//const unsigned int palBit = par->palBits;
	//const unsigned int palMask = par->palMask;

	//int fg = 8 - par->palBits;	




	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j >= 4)
		{
			int c = pal[*s++];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = pal[*s++];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = pal[*s++];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = pal[*s++];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			j -= 4;
			//--j;
		}

		while(j != 0)
		{				
			int c = pal[*s++];//((*s)>>fg)&palMask];
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			//if(fg == 0)
			//{
			//	++s;
			//	fg = 8;
			//}
			//fg = fg - par->palBits;
			
			--j;
		}
		s += sy;
		d = (unsigned short*)((char*)d + dy);
	}
}

void BlitD16S8PA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{

#if defined ENABLE_PALETTE_ALPHA_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;	//8 bit alpha, 8 bit 0, and 16 bit color
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;

	//const unsigned int palBit = par->palBits;
	//const unsigned int palMask = par->palMask;
	//int fg = 8 - par->palBits;	

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j > 0)
		{
			unsigned int c = pal[*s++];
			unsigned int a = c >> 24;
			unsigned int fg = c & 0xFFFF;
			if (0xFF == a)
				*d = fg;
			else if (0 != a)
			{
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, a);
			}
			d = (unsigned short*)((char*)d + dx);			
			--j;
		}
		s += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	ASSERT(false);
#endif
}

void BlitD16S8PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_OPACITY_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;

	const int o = par->opacity;

	//const unsigned int palBit = par->palBits;
	//const unsigned int palMask = par->palMask;
	//int fg = 8 - par->palBits;	

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int fg = pal[*s++];
			unsigned int bg = *d;
			ALPHA_BLEND_S16_D16(*d, bg, fg, o);
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (s + sy);
		d = (unsigned short*)((char*)d + dy);
	}
#else
	ASSERT(false);
#endif
}

void BlitD16S8PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_OPACITY_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;
	const unsigned int key = par->colorKey;

	const unsigned int o = par->opacity;

	//const unsigned int palBit = par->palBits;
	//const unsigned int palMask = par->palMask;
	//int fg = 8 - par->palBits;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int c = pal[*s++];
			if(c != key)
			{
				unsigned int fg = c;
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, o);
			}
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (s + sy);
		d = (unsigned short*)((char*)d + dy);
	}
#else
	ASSERT(false);
#endif
}

void BlitD16S8PAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_OPACITY_BLIT && defined ENABLE_PALETTE_ALPHA_BLIT
	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;	//8 bit alpha, 8 bit 0, and 16 bit color
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width;

	const unsigned int o = par->opacity;


	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j > 0)
		{
			unsigned int c = pal[*s++];
			unsigned int a = (c >> 24) * o / ALPHA_DEVISOR;
			unsigned int fg = c & 0xFFFF;
			if (0xFF == a)
				*d = fg;
			else if (0 != a)
			{
				unsigned int bg = *d;
				ALPHA_BLEND_S16_D16(*d, bg, fg, a);
			}
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s += sy;
		d = (unsigned short*)((char*)d + dy);
	}
#else
	ASSERT(false);
#endif
}

//void BlitD24S8PK(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned int *pal = (unsigned int*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//	int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j >= 4)
//		{
//			int c = *s++;
//			if(c != key)
//				*d = pal[c];
//			d = (unsigned int*)((char*)d + dx);
//			c = *s++;
//			if(c != key)
//				*d = pal[c];
//			d = (unsigned int*)((char*)d + dx);
//			c = *s++;
//			if(c != key)
//				*d = pal[c];
//			d = (unsigned int*)((char*)d + dx);
//			c = *s++;
//			if(c != key)
//				*d = pal[c];
//			d = (unsigned int*)((char*)d + dx);
//			j -= 4;
//		}
//		while(j != 0)
//		{
//			int c = *s++;
//			if(c != key)
//				*d = pal[c];
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s += sy;
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S8PKO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned short *pal = (unsigned short*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int c = *s++;
//			if(c != key)
//			{
//				unsigned int fg = pal[c];
//				unsigned int bg = *d;
//				ALPHA_BLEND_S12_D12(*d, bg, fg, a);
//			}
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}
//
//void BlitD16S8PKO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned short *pal = (unsigned short*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int c = *s++;
//			if(c != key)
//			{
//				unsigned int fg = pal[c];
//				unsigned int bg = *d;
//				ALPHA_BLEND_S16_D16(*d, bg, fg, a);
//			}
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}

//void BlitD24S8PKO(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned char *s = (unsigned char*)src;
//	unsigned int *pal = (unsigned int*)par->palette;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width;
//
//	const int a = par->opacity;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int c = *s++;
//			if(c != key)
//			{
//				unsigned int fg = pal[c];
//				unsigned int bg = *d;
//				ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			}
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD16S32A(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = fg >> 24;
//			ALPHA_BLEND_S32_D16(*d, bg, fg, a);
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}

//void BlitD24S32A(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = fg >> 24;
//			ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S32AO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	const unsigned int opacity = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = (fg >> 24) * opacity / ALPHA_DEVISOR;
//			ALPHA_BLEND_S32_D12(*d, bg, fg, a);
//
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}
//
//void BlitD16S32AO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	const unsigned int opacity = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = (fg >> 24) * opacity / ALPHA_DEVISOR;
//			ALPHA_BLEND_S32_D16(*d, bg, fg, a);
//
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}

//void BlitD24S32AO(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	const unsigned int opacity = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = (fg >> 24) * opacity / ALPHA_DEVISOR;
//			ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S32A(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * 4;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = par->width;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			int bg = *d;
//			int a = fg >> 24;
//			ALPHA_BLEND_S32_D12(*d, bg, fg, a);
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}

void BlitD16SI64RLE(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT
#define BLIT_BLEND_COLOR(d, s, o)		{d = s;}	
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLE(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT
#define BLIT_BLEND_COLOR(d, s, o)		{d = s;}
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLE(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I256RLE_BLIT
#define BLIT_BLEND_COLOR(d, s, o)		{d = s;}
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#else
	ASSERT(false);
#endif
}

void BlitD16SRLE(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLE(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLE(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLE(dst, src, par);
		break;
	}
}



/////////////K
void BlitD16SI64RLEK(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_BLEND_COLOR(d, s, o)		{d = s;}
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEK(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_BLEND_COLOR(d, s, o)		{d = s;}
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{//SangHo -(SideScroll) 565 각 포인터간의 데이터 전송으로 실제 이미지를 그리는부분(I256RLE)
#if defined ENABLE_I256RLE_BLIT
#define BLIT_HAS_COLOR_KEY
	
//SangHo - BLEND - 0: normal, 1: alpha, 2: DodgeChannel, 3: linearDodge, 4: shadow, 5: Lighten, 6: alphaChannel 6: LV1

			if(Blend_Kind == 0){
#define BLIT_BLEND_COLOR(d, s, o) d = s;
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 1){
#define BLIT_BLEND_COLOR(d, s, o) d= ((((d&0xF81f)*(32-Blend_Percent) + (s&0xF81f)*Blend_Percent)>> 5) & 0xF81f) | ((((d&0x7E0)*(32-Blend_Percent) + (s&0x7E0)*Blend_Percent) >> 5) & 0x7E0);
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 2){
				unsigned short blend_Percent;
				unsigned int bR,bG,bB;
#define BLIT_BLEND_COLOR(d, s, o) {blend_Percent =32 - (((s&0xF800)>>11)+((s&0x7E0)>>6)+(s&0x1F))/6;\
	bR=(((d&0xF800)*(blend_Percent)>> 5)+(s&0xF800));\
	bG=(((d&0x7e0)*(blend_Percent)>> 5)+(s&0x7e0));\
	bB=(((d&0x1f)*(blend_Percent)>> 5)+(s&0x1f));\
	d=(bR > 0xF800 ? 0xF800 : (bR & 0xF800)) | (bG > 0x7E0 ? 0x7E0 : (bG & 0x7E0)) | (bB > 0x1f ? 0x1f : (bB & 0x1f));}
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 3){
#define BLIT_BLEND_COLOR(d, s, o) d=(((d&0xF800)+(s&0xF800) > 0xF800) ? 0xF800 : (d&0xF800)+(s&0xF800)) | (((d&0x7E0)+(s&0x7E0) > 0x7E0) ? 0x7E0 : (d&0x7E0)+(s&0x7E0)) | (((d&0x1f)+(s&0x1f) > 0x1f) ? 0x1f : (d&0x1f)+(s&0x1f));
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 4){
#define BLIT_BLEND_COLOR(d, s, o) d=(((d&0xF800)>(s&0xF800)) ? (d&0xF800)-(s&0xF800) : 0) | (((d&0x7E0)>(s&0x7E0)) ? ((d&0x7E0)-(s&0x7E0)) : 0) |(((d&0x1f)>(s&0x1f)) ? ((d&0x1f)-(s&0x1f)) : 0);
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 5){
#define BLIT_BLEND_COLOR(d, s, o) d=(((d&0xF800)>(s&0xF800)) ? (d&0xF800) : (s&0xF800)) | (((d&0x7E0)>(s&0x7E0)) ? (d&0x7E0) : (s&0x7E0)) |(((d&0x1f)>(s&0x1f)) ? (d&0x1f) : (s&0x1f));
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 6){//알파채널=>멀티플라이 로변경
//#define BLIT_BLEND_COLOR(d, s, o) {const unsigned int blend_Percent =(((s&0xF800)>>11)+((s&0x7E0)>>6)+(s&0x1F))/3;\
//	d= ((((d&0xF81f)*(32-blend_Percent) + (s&0xF81f)*blend_Percent)>> 5) & 0xF81f) | ((((d&0x7E0)*(32-blend_Percent) + (s&0x7E0)*blend_Percent) >> 5) & 0x7E0);}
#define BLIT_BLEND_COLOR(d, s, o) d=((((d&0xF800)*(s&0xF800))/0xF800)&0xF800) | ((((d&0x7E0)*(s&0x7E0))/0x7E0)&0x7E0) |((((d&0x1F)*(s&0x1F))/0x1F)&0x1F)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 7){
#define BLIT_BLEND_COLOR(d, s, o) d=(((Blend_Percent&0xF800)+(s&0xF800) > 0xF800) ? 0xF800 : (Blend_Percent&0xF800)+(s&0xF800)) | (((Blend_Percent&0x7E0)+(s&0x7E0) > 0x7E0) ? 0x7E0 : (Blend_Percent&0x7E0)+(s&0x7E0)) | (((Blend_Percent&0x1f)+(s&0x1f) > 0x1f) ? 0x1f : (Blend_Percent&0x1f)+(s&0x1f));
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}
			if(Blend_Kind == 8){
				unsigned short grayScale;
#define BLIT_BLEND_COLOR(d, s, o) {grayScale = ((s>>11&0x1f)+(s>>6&0x1f)+(s&0x1f))/3;\
	d= grayScale<<11 | grayScale<<6 | grayScale;}
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}else
			if(Blend_Kind == 9){
				unsigned short blend_Percent;
				unsigned int bR,bG,bB;
#define BLIT_BLEND_COLOR(d, s, o) {blend_Percent =32 - (((s&0xF800)>>11)+((s&0x7E0)>>6)+(s&0x1F))/2;\
	bR=(((d&0xF800)*(blend_Percent)>> 5)+(s&0xF800));\
	bG=(((d&0x7e0)*(blend_Percent)>> 5)+(s&0x7e0));\
	bB=(((d&0x1f)*(blend_Percent)>> 5)+(s&0x1f));\
	d=(bR > 0xF800 ? 0xF800 : (bR & 0xF800)) | (bG > 0x7E0 ? 0x7E0 : (bG & 0x7E0)) | (bB > 0x1f ? 0x1f : (bB & 0x1f));}
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
			}

#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEK(dst, src, par,/*Blend*/  Blend_Kind, Blend_Percent);
		break;
	case 7:
		BlitD16SI127RLEK(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEK(dst, src, par);
		break;
	}
}

/////////////A
void BlitD16SI64RLEA(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT&& defined ENABLE_RLE_ALPHA_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_ALPHA(d, s)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEA(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT && defined ENABLE_RLE_ALPHA_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_ALPHA(d, s)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEA(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I256RLE_BLIT && defined ENABLE_RLE_ALPHA_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_ALPHA(d, s)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_RLE_ALPHA_BLIT
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEA(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEA(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEA(dst, src, par);
		break;
	}
#else
	ASSERT(false);
#endif
}

/////////////O
void BlitD16SI64RLEO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I256RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_RLE_OPACITY_BLIT
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEO(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEO(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEO(dst, src, par);
		break;
	}
#else
	ASSERT(false);
#endif
}

/////////////KO
void BlitD16SI64RLEKO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEKO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEKO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I256RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY(d, s, o)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_RLE_OPACITY_BLIT
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEKO(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEKO(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEKO(dst, src, par);
		break;
	}
#else
	ASSERT(false);
#endif
}

/////////////AO
void BlitD16SI64RLEAO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT && defined ENABLE_RLE_ALPHA_OPACITY_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_ALPHA(d, s, o)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEAO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT && defined ENABLE_RLE_ALPHA_OPACITY_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_ALPHA(d, s, o)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEAO(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I256RLE_BLIT && defined ENABLE_RLE_ALPHA_OPACITY_BLIT
#define BLIT_HAS_ALPHA
#define BLIT_HAS_OPACITY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_ALPHA(d, s, o)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_ALPHA
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_RLE_ALPHA_OPACITY_BLIT
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEAO(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEAO(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEAO(dst, src, par);
		break;
	}
#else
	ASSERT(false);
#endif
}

/////////////KG
void BlitD16SI64RLEKG(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_GRAY(d,s)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEKG(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_GRAY(d,s)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEKG(void *dst, void *src, BlitParam *par)
{
	int a = 0; 
#if defined ENABLE_I256RLE_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_GRAY(d,s)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}
void BlitD16SRLEKG(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEKG(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEKG(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEKG(dst, src, par);
		break;
	}
}

/////////////KOC
void BlitD16SI64RLEKOC(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I64RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_HAS_CHANNEL_COLOR
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_COLOR(d, s, o)
#include "BlitD16SI64RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_CHANNEL_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI127RLEKOC(void *dst, void *src, BlitParam *par)
{
#if defined ENABLE_I127RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_HAS_CHANNEL_COLOR
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_COLOR(d, s, o)
#include "BlitD16SI127RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_CHANNEL_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SI256RLEKOC(void *dst, void *src, BlitParam *par)
{
	
#if defined ENABLE_I256RLE_BLIT && defined ENABLE_RLE_OPACITY_BLIT
#define BLIT_HAS_COLOR_KEY
#define BLIT_HAS_OPACITY
#define BLIT_HAS_CHANNEL_COLOR
#define BLIT_BLEND_COLOR(d, s, o)		BLIT_BLEND_COLOR_OPACITY_COLOR(d, s, o)
#include "BlitD16SI256RLE.h"
#undef BLIT_BLEND_COLOR
#undef BLIT_HAS_CHANNEL_COLOR
#undef BLIT_HAS_OPACITY
#undef BLIT_HAS_COLOR_KEY
#else
	ASSERT(false);
#endif
}

void BlitD16SRLEKOC(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
#if defined ENABLE_RLE_OPACITY_BLIT
	switch (par->palBits)
	{
	case 8:
		BlitD16SI256RLEKOC(dst, src, par);
		break;
	case 7:
		BlitD16SI127RLEKOC(dst, src, par);
		break;
	default:
		if (par->palBits > 8)	//for old engine (GLI)
			par->palBits = 7;
		BlitD16SI64RLEKOC(dst, src, par);
		break;
	}
#else
	ASSERT(false);
#endif
}


void BlitD16S16(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	unsigned short *d = (unsigned short*)dst;
	unsigned short *s = (unsigned short*)src;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width * sizeof(*s);

	const int w = par->width;

	for(int i = par->height; i != 0; i--)
	{
		int j = w;
#if defined ENABLE_ACCELERATE_BLIT
		while(j >= 4)
		{
			unsigned int c = *s++;
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			j -= 4;
		}
#endif
		while(j != 0)
		{
			unsigned int c = *s++;
			*d = c;
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (unsigned short*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
	}	
}

//void BlitD24S24(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			*d = *s++;
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S12O(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned short *s = (unsigned short*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	const int a = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			unsigned int bg = *d;
//			ALPHA_BLEND_S12_D12(*d, bg, fg, a);
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned short*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}
//

#ifdef ENABLE_ALPHA
void BlitD16S16O(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	unsigned short *d = (unsigned short*)dst;
	unsigned short *s = (unsigned short*)src;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width * sizeof(*s);

	const int w = par->width;
	const int a = par->opacity;

	for(int i = par->height; i != 0; i--)
	{
		int j = w;
		while(j != 0)
		{
			unsigned int fg = *s++;
			unsigned int bg = *d;
			ALPHA_BLEND_S16_D16(*d, bg, fg, a);
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (unsigned short*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
	}
}
#endif

//void BlitD24S24O(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	const int a = par->opacity;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			unsigned int bg = *d;
//			ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

void BlitD16S16K(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{//SangHo - 565 각 포인터간의 데이터 전송으로 실제 이미지를 그리는부분
	unsigned short *d = (unsigned short*)dst;//SangHo - 그릴 대상버퍼의 좌상픽셀 포인터
	unsigned short *s = (unsigned short*)src;//SangHo -
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;//SangHo - 다음 Y라인의 첫X픽셀까지의 거리(byte)
	int sy = par->srcYPitch - par->width * sizeof(*s);

	const int w = par->width;
	const unsigned int key = par->colorKey;

	for(int i = par->height; i != 0; i--)
	{
		int j = w;

#if defined ENABLE_ACCELERATE_BLIT
		while(j >= 4)
		{
			unsigned int c = *s++;
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			c = *s++;
			if(c != key)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			j -= 4;
		}
#endif
		while(j != 0)
		{
			unsigned int c = *s++;
			if(c != key)//SangHo - key:투명 컬러값 1111100000011111  (63519)
				*d = c;
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (unsigned short*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
	}
}

//void BlitD24S24K(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			unsigned int c = *s++;
//			if(c != key)
//				*d = c;
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}

//void BlitD12S12KO(void *dst, void *src, BlitParam *par)
//{
//	unsigned short *d = (unsigned short*)dst;
//	unsigned short *s = (unsigned short*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	const int a = par->opacity;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			if(fg != key)
//			{
//				unsigned int bg = *d;
//				ALPHA_BLEND_S12_D12(*d, bg, fg, a);
//			}
//			d = (unsigned short*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned short*)((char*)s + sy);
//		d = (unsigned short*)((char*)d + dy);
//	}
//}
//
#ifdef ENABLE_ALPHA
void BlitD16S16KO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{
	const unsigned int rMask = 0xF800;
	const unsigned int gMask = 0x7E0;
	const unsigned int bMask = 0x1f;

	unsigned short *d = (unsigned short*)dst;
	unsigned short *s = (unsigned short*)src;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width * sizeof(*s);

	const int w = par->width;	
	const int a = par->opacity;
	const unsigned int key = par->colorKey;


	//unsigned short *q = (unsigned short*) (par->bgbuff + par->y_dest*480 ) + par->x_dest;


	for(int i = par->height; i != 0; i--)
	{
		int j = w;

		while(j != 0)
		{
			unsigned int fg = *s++;
			if(fg != key)
			{
				unsigned int bg = *d;


				//if( par->bChannel  == 1)
				//{	
				//	unsigned int qbg = *q;

				//	int ur =  (qbg & rMask);
				//	int ug =  (qbg & gMask);
				//	int ub =  (qbg & bMask);

				//	int afff = 0;
				//	int aur = 0;
				//	if(ur != 0)
				//	{
				//		aur = ( (bg & rMask) * ALPHA_DEVISOR / ur );
				//		afff++;
				//	}
				//	if(ug != 0)
				//	{
				//		aur += ( (bg & gMask) * ALPHA_DEVISOR / ug );
				//		afff++;
				//	}
				//	if(ub != 0)
				//	{
				//		aur += ( (bg & bMask) * ALPHA_DEVISOR / ub );
				//		afff++;
				//	}

				//	if(afff != 0)
				//		aur = aur/afff;

				//	aur = 256- aur;




				//	if(aur > 180)
				//		aur = 180;
				//	else if(aur < 1)
				//		aur = 0;
				//	//TEST SEongjin 1017
				//	//const int ca = (((255 - ((0x1f & fg) << 3))*(aur))/255 );
				//	const int ca = (((255 - ((0x1f & fg) << 3))*(a))/255 );

				//	ur = (ur) * (256-ca) / ALPHA_DEVISOR;
				//	ug = (ug) * (256-ca) / ALPHA_DEVISOR;
				//	ub = (ub) * (256-ca) / ALPHA_DEVISOR;

				//	*d = (ur & rMask) | (ug & gMask) | (ub & bMask);

				//}
				//else if(par->bChannel == 2)
				//{							
				//	unsigned int ufr = (par->p_color >> 8) & 0xF800;
				//	unsigned int ufg = (par->p_color >> 5) & 0x7E0;
				//	unsigned int ufb = (par->p_color >> 3) & 0x1F;					

				//	unsigned int color = ufr | ufg | ufb ;					
				//	const unsigned int ar = (rMask & color) * a / ALPHA_DEVISOR;
				//	const unsigned int ag = (gMask & color) * a / ALPHA_DEVISOR;
				//	const unsigned int ab = (bMask & color) * a / ALPHA_DEVISOR;
				//	const unsigned int alpha = ALPHA_DEVISOR - a;


				//	int r = ar + (fg & rMask) * alpha / ALPHA_DEVISOR;
				//	int g = ag + (fg & gMask) * alpha / ALPHA_DEVISOR;
				//	int b = ab + (fg & bMask) * alpha / ALPHA_DEVISOR;

				//	*d =  (unsigned short)((r & rMask) | (g & gMask) | (b & bMask)); // set the pixel					

				//}
				//else if(par->bChannel == 3)
				//{
				//	int r = ((fg & rMask) << 3) >> 11;
				//	int g = ((fg & gMask) << 2 ) >> 5;
				//	int b = (fg & bMask) << 3;

				//	int gray = (r*76 + g*151 + b*29)/256;

				//	*d =  (unsigned short) ((gray >> 3) << 11) | ((gray >> 2) << 5) | (gray >> 3);	
				//}
				//else
				{
					int r = bg & rMask;
					r += ((fg & rMask) - r) * a / ALPHA_DEVISOR;
					int g = bg & gMask;
					g += ((fg & gMask) - g) * a / ALPHA_DEVISOR;
					int b = bg & bMask;
					b += ((fg & bMask) - b) * a / ALPHA_DEVISOR;
					*d = (r & rMask) | (g & gMask) | (b & bMask);
					//ALPHA_BLEND_S16_D16(*d, bg, fg, a);
				}
			}

			d = (unsigned short*)((char*)d + dx);
			--j;

			//q = (unsigned short*)((char*)q + dx);
		}
		s = (unsigned short*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
		//q = (unsigned short*)((char*)q + dy);
	}
}
#endif

//void BlitD24S24KO(void *dst, void *src, BlitParam *par)
//{
//	unsigned int *d = (unsigned int*)dst;
//	unsigned int *s = (unsigned int*)src;
//	int dx = par->dstXPitch;
//	int dy = par->dstYPitch - par->width * dx;
//	int sy = par->srcYPitch - par->width * sizeof(*s);
//
//	const int w = par->width;
//	const int a = par->opacity;
//	const unsigned int key = par->colorKey;
//	
//	for(int i = par->height; i != 0; i--)
//	{
//		int j = w;
//		while(j != 0)
//		{
//			unsigned int fg = *s++;
//			if(fg != key)
//			{
//				unsigned int bg = *d;
//				ALPHA_BLEND_S24_D24(*d, bg, fg, a);
//			}
//			d = (unsigned int*)((char*)d + dx);
//			--j;
//		}
//		s = (unsigned int*)((char*)s + sy);
//		d = (unsigned int*)((char*)d + dy);
//	}
//}


void BlitD16S32A(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)
{

	unsigned short *d = (unsigned short*)dst;
	unsigned int *s = (unsigned int*)src;
	int dx = par->dstXPitch;
	int dy = par->dstYPitch - par->width * dx;
	int sy = par->srcYPitch - par->width * 4;

	for(int i = par->height; i != 0; i--)
	{
		int j = par->width;
		while(j != 0)
		{
			unsigned int fg = *s++;
			int bg = *d;
			int a = fg >> 24;
			ALPHA_BLEND_S16_D16(*d, bg, fg, a);//modify for bowling @08/01/17 for alpha blend
			//ALPHA_BLEND_S32_D16(*d, bg, fg, a);
			d = (unsigned short*)((char*)d + dx);
			--j;
		}
		s = (unsigned int*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
	}

}


void BlitD16SI64RLEAOL(void *dst, void *src, BlitParam *par, void *bst )
{
#if defined ENABLE_I64RLE_BLIT && defined ENABLE_RLE_ALPHA_OPACITY_BLIT

	unsigned short *d = (unsigned short*)dst;
	unsigned char *s = (unsigned char*)src;
	unsigned char *b = (unsigned char*)bst;
	PalettePixel_16 *pal = (PalettePixel_16*)par->palette;
	const int dx = par->dstXPitch;
	const int ey = par->width * dx;
	const int dy = par->dstYPitch - ey;//par->width * dx;
	const int sy = par->srcYPitch - par->width;	//sx == 1
	const int w  = par->width;
	const int h  = par->height;

	const unsigned int palBit = par->palBits;
	const unsigned int palMask = par->palMask;


	const int bdx = (par->dstXPitch>>1) ;
	const int bdy = (par->dstYPitch>>1) - par->width*bdx ;


	// TEST SEONGJIN
	//unsigned short *q = (unsigned short*) (par->bgbuff + par->y_dest*480 ) + par->x_dest;


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


			{
				while(count-- >= 0)
				{					
					///////////////////					
					unsigned int ab = *b;
					unsigned int c = pal[index];					 
					unsigned int a = (255-(c >> 24)) * ab / ALPHA_DEVISOR;						
					*b = a;
					///////////////////


					d = (unsigned short*)((char*)d + dx);
					b = (unsigned char*)((unsigned char*)b + bdx);
					if(d == e )
					{
						if (--i <= 0)
							return;
						d = (unsigned short*)((char*)d + dy);
						b = (unsigned char*)((unsigned char*)b + bdy);
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

			while(count-- >= 0)
			{	

				///////////////////					
				unsigned int ab = *b;
				unsigned int c = pal[index];					 
				unsigned int a = (255-(c >> 24)) * ab / ALPHA_DEVISOR;						
				*b = a;
				///////////////////

				d = (unsigned short*)((char*)d + dx);
				b = (unsigned char*)((char*)b + bdx);
				if(d == e )
				{
					if (--i <= 0)
						return;
					d = (unsigned short*)((char*)d + dy);
					b = (unsigned char*)((char*)b + bdy);
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

		}
	}

#else
	ASSERT(false);
#endif
}