// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "graphics.h"
//#include "engine.h"

#define ALPHA_DEVISOR	256 //should be 255, but use 256 for the sake of speed
//
//#define ALPHA_BLEND_S12_D12(dst, bg, fg, a) {\
//		const unsigned int rMask = 0xF00;\
//		const unsigned int gMask = 0xF0;\
//		const unsigned int bMask = 0xF;\
//		int r = bg & rMask;\
//		r += ((fg & rMask) - r) * a / ALPHA_DEVISOR;\
//		int g = bg & gMask;\
//		g += ((fg & gMask) - g) * a / ALPHA_DEVISOR;\
//		int b = bg & bMask;\
//		b += ((fg & bMask) - b) * a / ALPHA_DEVISOR;\
//		dst = (r & rMask) | (g & gMask) | (b & bMask);\
//	}
//
//#define ALPHA_BLEND_S32_D12(dst, bg, fg, a) {\
//		int t;\
//		t = (bg >> 8) & 0x0f;\
//		int r = t + (((fg >> 20) & 0xf) - t) * a / ALPHA_DEVISOR;\
//		t = (bg >> 4) & 0xf;\
//		int g = t + (((fg >> 12) & 0xf) - t) * a / ALPHA_DEVISOR;\
//		t = (bg) & 0xf;\
//		int b = t + (((fg >> 4) & 0xf) - t) * a / ALPHA_DEVISOR;\
//		dst = (r << 8) | (g << 4) | b;\
//	}
//
#ifdef ENABLE_ALPHA
#define ALPHA_BLEND_S16_D16(dst, bg, fg, a) {\
		const unsigned int rMask = 0xF800;\
		const unsigned int gMask = 0x7E0;\
		const unsigned int bMask = 0x1f;\
		int r = bg & rMask;\
		r += ((fg & rMask) - r) * a / ALPHA_DEVISOR;\
		int g = bg & gMask;\
		g += ((fg & gMask) - g) * a / ALPHA_DEVISOR;\
		int b = bg & bMask;\
		b += ((fg & bMask) - b) * a / ALPHA_DEVISOR;\
		dst = (r & rMask) | (g & gMask) | (b & bMask);\
	}
#endif

#define ALPHA_BLEND_S32_D16(dst, bg, fg, a) {\
		int t;\
		t = (bg >> 11) & 0x1f;\
		int r = t + (((fg >> 19) & 0x1f) - t) * a / ALPHA_DEVISOR;\
		t = (bg >> 5) & 0x3f;\
		int g = t + (((fg >> 10) & 0x3f) - t) * a / ALPHA_DEVISOR;\
		t = (bg) & 0x1f;\
		int b = t + (((fg >> 3) & 0x1f) - t) * a / ALPHA_DEVISOR;\
		dst = (r << 11) | (g << 5) | b;\
	}



//
//#define ALPHA_BLEND_S24_D24(dst, bg, fg, a) {\
//		const unsigned int rMask = 0xFF0000;\
//		const unsigned int gMask = 0xFF00;\
//		const unsigned int bMask = 0xFF;\
//		int r = bg & rMask;\
//		r += ((fg & rMask) - r) * a / ALPHA_DEVISOR;\
//		int g = bg & gMask;\
//		g += ((fg & gMask) - g) * a / ALPHA_DEVISOR;\
//		int b = bg & bMask;\
//		b += ((fg & bMask) - b) * a / ALPHA_DEVISOR;\
//		dst = (r & rMask) | (g & gMask) | (b & bMask);\
//	}

#define HALF_ALPHA_BLEND_S16_D16_565(dst, col){\
	dst = ((dst & 0xF7DE) >> 1) + ((col & 0xF7DE) >> 1);\
}

#define HALF_ALPHA_BLEND_S16_D16_444(dst, col){\
	dst = ((dst & 0x0EEE) >> 1) + ((col & 0x0EEE) >> 1);\
}

#include "Graphics\BlitFunc.h"

void  CGraphics::DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, int anchor, unsigned int palette)
{
#ifdef SUPPORT_FRAMEMODULES_ROTATE
    int width1 = width,height1 = height;
    width = (transform | CGraphics::ROTATE_90) == 0 ? width : height1;
    height = (transform | CGraphics::ROTATE_90) == 0 ? height : width1;
#endif
	if( anchor & CGraphics::RIGHT )
	{
		x_dest -= width; 
	}
	else if(anchor & CGraphics::HCENTER)
	{
		//x_dest = (GetImage()->GetWidth() - width)/2;
		x_dest -= (width+1)/2;
	}

	if(anchor & CGraphics::BOTTOM )
	{
		y_dest -= height;
	}
	else if( anchor & CGraphics::VCENTER )
	{
		//y_dest = (GetImage()->GetHeight() - height)/2;
		y_dest -= (height+1)/2;
	}
#ifdef SUPPORT_FRAMEMODULES_ROTATE
    width = width1;
    height = height1;
#endif 
	DrawRegion( pSrc,  x_src,  y_src,  width,  height,  transform,
	 x_dest,  y_dest,   palette);

}
CGraphics::~CGraphics()
{
}

void CGraphics::SetImage(CMutableImage *image)
{
	m_image = image;
	ResetClip();
	m_translate[0] = m_translate[1] = 0;
}

void CGraphics::SetChannel(unsigned char channel)	
{
	m_channel |= channel;
}

void CGraphics::UnSetChannel(unsigned char channel)	
{
	m_channel &= ~channel;
}

unsigned char CGraphics::GetChannel()
{
	return m_channel;
}

void CGraphics::SetClip(int x, int y, int width, int height)
{
	m_clipRect[0] = x + m_translate[0];
	m_clipRect[1] = y + m_translate[1];
	m_clipRect[2] = m_clipRect[0] + width;
	m_clipRect[3] = m_clipRect[1] + height;
	if(m_clipRect[0] < 0)
		m_clipRect[0] = 0;
	if(m_clipRect[1] < 0)
		m_clipRect[1] = 0;
	int n = m_image->GetWidth();
	if(m_clipRect[2] > n)
		m_clipRect[2] = n;
	n = m_image->GetHeight();
	if(m_clipRect[3] > n)
		m_clipRect[3] = n;
}
void CGraphics::GetPixels(unsigned char *src,
						  unsigned short *dest, 
						  int offset,
						  int scanlength,
						  int x,
						  int y,
						  int width,
						  int height, int flag)
{	
	for (int y0 = y; y0 < height+y; y0++)
		for (int x0 = x; x0 < width+x; x0++)
				*(dest + (x0-x) + width * (y0 - y)) = *(unsigned short *)(src + (y0 * scanlength + x0) * 2);
}

//void CGraphics::FillTriangle(int bottomX, int bottomY, int left, int topL, int right, int topR)
//{
//	int x1, y1, x2, y2, h, i;
//
//	if (topL == topR)
//	{
//		if(topL < bottomY)
//		{
//			h = 1;//(bottomY - topL)/5;
//			for (i=0; i<4; i++)
//			{
//				x1 = left + ((right - left + 1)/5)*i;
//				y1 = topL + i*h;
//				x2 = right - ((right - left + 1)/5)*i;
//				y2 = topR + i*h;
//				//GFX_DrawLine(pDes, x1, y1, x2, y2, color);
//				DrawLine(x1,y1,x2,y2);
//			}	
//		} 
//		else if (topL > bottomY)
//		{
//			h = 1;//(topL - bottomY)/5;
//			for(i = 0; i < 4; i++)
//			{
//				x1 = left + ((right - left + 1)/5)*i;
//				y1 = topL - i*h;
//				x2 = right - ((right - left + 1)/5)*i;
//				y2 = topR - i*h;
//				//GFX_DrawLine(pDes,x1, y1, x2, y2, color);
//				DrawLine(x1,y1,x2,y2);
//			}
//		}
//	}
//	else if(left == right)
//	{
//		if(left < bottomX)
//		{
//			h = 1;//(bottomX - left)/5;
//			for (i=0; i<4; i++)
//			{
//				x1 = left + i*h;
//				y1 = topL + ((topR - topL + 1)/5)*i;
//				x2 = right + i*h;
//				y2 = topR - ((topR - topL + 1)/5)*i;
//				//GFX_DrawLine(pDes, x1, y1, x2, y2, color);
//				DrawLine(x1,y1,x2,y2);
//			}	
//		}
//		else if(left > bottomX)
//		{
//			h = 1;//(left - bottomX)/5;
//			for (i=0; i<4; i++)
//			{
//				x1 = left - i*h;
//				y1 = topL + ((topR - topL + 1)/5)*i;
//				x2 = right - i*h;
//				y2 = topR - ((topR - topL + 1)/5)*i;
//				//GFX_DrawLine(pDes, x1, y1, x2, y2, color);
//				DrawLine(x1,y1,x2,y2);
//			}	
//		}
//	}
//}



//void CGraphics::DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
//	int x_dest, int y_dest, unsigned int palette)
//SangHo - Blend - 블랜딩을 위해서 끝에 인자값 2개 추가 - 1번인자 블랜딩 종류 , 2번인자 블랜딩 퍼센트
void CGraphics::DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
	int x_dest, int y_dest, unsigned int palette, /*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)

{
	x_dest += m_translate[0];
	y_dest += m_translate[1];

	unsigned int f = TransformToFlag(transform);

	//I derived these clipping rules by studying at a bunch of diagrams with
	//all kinds of transforms ;)
	if(!(f & ROTATE_90))
	{
		int delta = m_clipRect[0] - x_dest;
		if(delta > 0)
		{
			if(!(f & FLIP_X))
				x_src += delta;
			width -= delta;
			x_dest = m_clipRect[0];
		}
		delta = x_dest + width - m_clipRect[2];
		if(delta > 0)
		{
			if(f & FLIP_X)
				x_src += delta;
			width -= delta;
		}
		delta = m_clipRect[1] - y_dest;
		if(delta > 0)
		{
			if(!(f & FLIP_Y))
				y_src += delta;
			height -= delta;
			y_dest = m_clipRect[1];
		}
		delta = y_dest + height - m_clipRect[3];
		if(delta > 0)
		{
			if(f & FLIP_Y)
				y_src += delta;
			height -= delta;
		}
	}
	else
	{
		int delta = m_clipRect[0] - x_dest;
		if(delta > 0)
		{
			if((f & FLIP_Y))
				y_src += delta;
			height -= delta;
			x_dest = m_clipRect[0];
		}
		delta = x_dest + height - m_clipRect[2];
		if(delta > 0)
		{
			if(!(f & FLIP_Y))
				y_src += delta;
			height -= delta;
		}
		delta = m_clipRect[1] - y_dest;
		if(delta > 0)
		{
			if(!(f & FLIP_X))
				x_src += delta;
			width -= delta;
			y_dest = m_clipRect[1];
		}
		delta = y_dest + width - m_clipRect[3];
		if(delta > 0)
		{
			if(f & FLIP_X)
				x_src += delta;
			width -= delta;
		}
	}

	if(width > 0 && height > 0)
		DrawRegion_NoClip_NoTranslat(pSrc, x_src, y_src, width, height, transform, x_dest, y_dest, palette,/*BLEND*/ Blend_Kind, Blend_Percent);// SangHo - Blend
}


void FillRect16(void *dst, int w, int h, int pitch, unsigned int nativeRgb)
{
	ASSERT(h > 0);	

	if(((int)dst & 3) == 0 && (w & 1) == 0)
	{
		unsigned int fclr = (nativeRgb << 16) | nativeRgb;
		unsigned int *dst32 = (unsigned int*)dst;
		unsigned int dy = pitch - w * 2;
		while(h != 0)
		{
			int i = w;
			while(i >= 8)
			{
				*dst32++ = fclr;
				*dst32++ = fclr;
				*dst32++ = fclr;
				*dst32++ = fclr;
				i -= 8;
			}
			while(i != 0)
			{
				*dst32++ = fclr;
				i -= 2;
			}
			dst32 = (unsigned int*)((char*)dst32 + dy);
			--h;
		}
	}
	else
	{
		unsigned short *d = (unsigned short*)dst;
		unsigned int fclr = nativeRgb;
		while(h != 0)
		{
			unsigned short *end = d + w;
			while(d < end)
			{
				*d++ = fclr;
			}
			d = (unsigned short*)((char*)(d - w) + pitch);
			--h;
		}
	}
}

void FillRect24(void *dst, int w, int h, int pitch, unsigned int nativeRgb)
{
	unsigned int *dst32 = (unsigned int*)dst;
	unsigned int dy = pitch - w * 4;
	ASSERT(h > 0);
	while(h != 0)
	{
		int i = w;
		while(i >= 4)
		{
			*dst32++ = nativeRgb;
			*dst32++ = nativeRgb;
			*dst32++ = nativeRgb;
			*dst32++ = nativeRgb;
			i -= 4;
		}
		while(i != 0)
		{
			*dst32++ = nativeRgb;
			i--;
		}
		dst32 = (unsigned int*)((char*)dst32 + dy);
		--h;
	}
}

//void FillRectARGB12(void *dst, int w, int h, int pitch, unsigned int argb)
//{
//	unsigned int fa = argb >> 24;
//	unsigned int fr = ((argb >> 16) & 0xff) * fa / ALPHA_DEVISOR >> 4;
//	unsigned int fg = ((argb >> 8) & 0xff) * fa / ALPHA_DEVISOR >> 4;
//	unsigned int fb = ((argb) & 0xff) * fa / ALPHA_DEVISOR >> 4;
//	unsigned int fclr = (fr << 8) | (fg << 4) | (fb);
//
//	fa = ALPHA_DEVISOR - fa;
//	unsigned short *d = (unsigned short*)dst;
//	while(h != 0)
//	{
//		unsigned short *end = d + w;
//		while(d < end)
//		{
//			unsigned int v = *d;
//			unsigned int r = ((v >> 8) & 0xf) * fa / ALPHA_DEVISOR;
//			unsigned int g = ((v >> 4) & 0xf) * fa / ALPHA_DEVISOR;
//			unsigned int b = ((v) & 0xf) * fa / ALPHA_DEVISOR;
//			*d++ = ((r << 8) | (g << 4) | (b)) + fclr;
//		}
//		d = (unsigned short*)((char*)(d - w) + pitch);
//		--h;
//	}
//}
//
#ifdef ENABLE_ALPHA

void FillRectARGB16(void *dst, int w, int h, int pitch, unsigned int nativeRgb, unsigned int alpha)
{
	ASSERT(h > 0);
	ASSERT(alpha < 0xFF);
	
	unsigned short *d = (unsigned short*)dst;
	const unsigned int fclr = nativeRgb;
	
/*	if (0x80 == alpha)
	{
		while(h != 0)
		{
			unsigned short *end = d + w;
			while(d < end)
			{
				HALF_ALPHA_BLEND_S16_D16_565(*d, fclr);
				d++; 
			}
			d = (unsigned short*)((char*)(d - w) + pitch);	
			--h;
		}
	}
	else*/ if (alpha > 0)
	{
		const unsigned int rMask = 0xF800;
		const unsigned int gMask = 0x7E0;
		const unsigned int bMask = 0x1f;
		const unsigned int fr = (rMask & fclr) * alpha / ALPHA_DEVISOR;
		const unsigned int fg = (gMask & fclr) * alpha / ALPHA_DEVISOR;
		const unsigned int fb = (bMask & fclr) * alpha / ALPHA_DEVISOR;
		const unsigned int a = ALPHA_DEVISOR - alpha;
		while(h != 0)
		{
			unsigned short *end = d + w;
			while(d < end)
			{
				unsigned int c = (unsigned int)*d;
				int r = fr + (c & rMask) * a / ALPHA_DEVISOR;
				int g = fg + (c & gMask) * a / ALPHA_DEVISOR;
				int b = fb + (c & bMask) * a / ALPHA_DEVISOR;
				*d = (unsigned short)((r & rMask) | (g & gMask) | (b & bMask));
//				ALPHA_BLEND_S16_D16(*d, c, fclr, alpha);
				d++; 
			}
			d = (unsigned short*)((char*)(d - w) + pitch);	
			--h;
		}
	}
}

//void FillRectARGB16(void *dst, int w, int h, int pitch, unsigned int argb)
//{
//	unsigned int fa = argb >> 24;
//	unsigned int fr = ((argb >> 16) & 0xff) * fa / ALPHA_DEVISOR >> 3;
//	unsigned int fg = ((argb >> 8) & 0xff) * fa / ALPHA_DEVISOR >> 2;
//	unsigned int fb = ((argb) & 0xff) * fa / ALPHA_DEVISOR >> 3;
//	unsigned int fclr = (fr << 11) | (fg << 5) | (fb);
//
//	fa = ALPHA_DEVISOR - fa;
//	unsigned short *d = (unsigned short*)dst;
//	while(h != 0)
//	{
//		unsigned short *end = d + w;
//		while(d < end)
//		{
//			unsigned int v = *d;
//			unsigned int r = ((v >> 11) & 0x1f) * fa / ALPHA_DEVISOR;
//			unsigned int g = ((v >> 5) & 0x3f) * fa / ALPHA_DEVISOR;
//			unsigned int b = ((v) & 0x1f) * fa / ALPHA_DEVISOR;
//			*d++ = ((r << 11) | (g << 5) | (b)) + fclr;
//		}
//		d = (unsigned short*)((char*)(d - w) + pitch);
//		--h;
//	}
//}
#endif
//void FillRectARGB24(void *dst, int w, int h, int pitch, unsigned int argb)
//{
//	unsigned int fa = argb >> 24;
//	unsigned int fr = ((argb >> 16) & 0xff) * fa / ALPHA_DEVISOR;
//	unsigned int fg = ((argb >> 8) & 0xff) * fa / ALPHA_DEVISOR;
//	unsigned int fb = ((argb) & 0xff) * fa / ALPHA_DEVISOR;
//	unsigned int fclr = (fr << 16) | (fg << 8) | (fb);
//
//	fa = ALPHA_DEVISOR - fa;
//	unsigned int *d = (unsigned int*)dst;
//	while(h != 0)
//	{
//		unsigned int *end = d + w;
//		while(d < end)
//		{
//			unsigned int v = *d;
//			unsigned int r = ((v >> 16) & 0xff) * fa / ALPHA_DEVISOR;
//			unsigned int g = ((v >> 8) & 0xff) * fa / ALPHA_DEVISOR;
//			unsigned int b = ((v) & 0xff) * fa / ALPHA_DEVISOR;
//			*d++ = ((r << 16) | (g << 8) | (b)) + fclr;
//		}
//		d = (unsigned int*)((char*)(d - w) + pitch);
//		--h;
//	}
//}


#ifdef ENABLE_ALPHA
void DrawLineARGB16(unsigned short *dst, int dx, int dy, int pitch, unsigned int nativeColor, unsigned int alpha)
{
	ASSERT(alpha < 0xFF);
	int	dx2, dy2, x_inc, y_inc;
	
	// test which direction the line is going in i.e. slope angle
	if(dx >= 0)
	{
		x_inc = sizeof(*dst);
	} // end if line is moving right
	else
	{
		x_inc = -(int)sizeof(*dst);
		dx    = -dx;  // need absolute value
	} // end else moving left
	
	// test y component of slope
	if(dy >= 0)
	{
		y_inc = pitch;
	} // end if line is moving down
	else
	{
		y_inc = -pitch;
		dy    = -dy;  // need absolute value
	} // end else moving up
	
	if(dx < dy)
	{
		int tmp = x_inc;
		x_inc = y_inc;
		y_inc = tmp;
		
		tmp = dx;
		dx = dy;
		dy = tmp;
	}
	
	// compute (dx,dy) * 2
	dx2 = dx << 1;
	dy2 = dy << 1;
	
	int error = dy2 - dx;
	while(dx >= 0)
	{
		if (0x80 == alpha)
		{
			HALF_ALPHA_BLEND_S16_D16_565(*dst, nativeColor);
		}
		else if (alpha > 0)
		{
			const unsigned int rMask = 0xF800;
			const unsigned int gMask = 0x7E0;
			const unsigned int bMask = 0x1f;
			const unsigned int fr = (rMask & nativeColor) * alpha / ALPHA_DEVISOR;
			const unsigned int fg = (gMask & nativeColor) * alpha / ALPHA_DEVISOR;
			const unsigned int fb = (bMask & nativeColor) * alpha / ALPHA_DEVISOR;
			const unsigned int a = ALPHA_DEVISOR - alpha;

			unsigned int c = (unsigned int)*dst;
			int r = fr + (c & rMask) * a / ALPHA_DEVISOR;
			int g = fg + (c & gMask) * a / ALPHA_DEVISOR;
			int b = fb + (c & bMask) * a / ALPHA_DEVISOR;

			*dst =  (unsigned short)((r & rMask) | (g & gMask) | (b & bMask)); // set the pixel
		}
		//*dst = nativeColor; // set the pixel
		
		if (error >= 0)
		{
			error -= dx2;
			dst = (unsigned short*)((char*)dst + y_inc); // move to next line
		} // end if error overflowed
		dst = (unsigned short*)((char*)dst + x_inc); // move to the next pixel
		error += dy2; // adjust the error term
		--dx;
	}
}


#endif

void DrawLine16(unsigned short *dst, int dx, int dy, int pitch, unsigned int nativeColor)
{
	int	dx2, dy2, x_inc, y_inc;
	
	// test which direction the line is going in i.e. slope angle
	if(dx >= 0)
	{
		x_inc = sizeof(*dst);
	} // end if line is moving right
	else
	{
		x_inc = -(int)sizeof(*dst);
		dx    = -dx;  // need absolute value
	} // end else moving left
	
	// test y component of slope
	if(dy >= 0)
	{
		y_inc = pitch;
	} // end if line is moving down
	else
	{
		y_inc = -pitch;
		dy    = -dy;  // need absolute value
	} // end else moving up
	
	if(dx < dy)
	{
		int tmp = x_inc;
		x_inc = y_inc;
		y_inc = tmp;

		tmp = dx;
		dx = dy;
		dy = tmp;
	}

	// compute (dx,dy) * 2
	dx2 = dx << 1;
	dy2 = dy << 1;

	int error = dy2 - dx;
	while(dx >= 0)
	{
		*dst = nativeColor; // set the pixel
		if (error >= 0)
		{
			error -= dx2;
			dst = (unsigned short*)((char*)dst + y_inc); // move to next line
		} // end if error overflowed
		dst = (unsigned short*)((char*)dst + x_inc); // move to the next pixel
		error += dy2; // adjust the error term
		--dx;
	}
}

void DrawLine24(unsigned int *dst, int dx, int dy, int pitch, unsigned int nativeColor)
{
	int	dx2, dy2, x_inc, y_inc;

	// test which direction the line is going in i.e. slope angle
	if(dx >= 0)
	{
		x_inc = sizeof(*dst);
	} // end if line is moving right
	else
	{
		x_inc = -(int)sizeof(*dst);
		dx    = -dx;  // need absolute value
	} // end else moving left
	
	// test y component of slope
	if(dy >= 0)
	{
		y_inc = pitch;
	} // end if line is moving down
	else
	{
		y_inc = -pitch;
		dy    = -dy;  // need absolute value
	} // end else moving up
	
	if(dx < dy)
	{
		int tmp = x_inc;
		x_inc = y_inc;
		y_inc = tmp;

		tmp = dx;
		dx = dy;
		dy = tmp;
	}

	// compute (dx,dy) * 2
	dx2 = dx << 1;
	dy2 = dy << 1;

	int error = dy2 - dx;
	while(dx >= 0)
	{
		*dst = nativeColor; // set the pixel
		if (error >= 0)
		{
			error -= dx2;
			dst = (unsigned int*)((char*)dst + y_inc); // move to next line
		} // end if error overflowed
		error += dy2; // adjust the error term
		dst = (unsigned int*)((char*)dst + x_inc); // move to the next pixel
		--dx;
	}
}

static int findRegion(int x, int y, int w, int h)
{
    int code=0;
    if(y < 0)
    code |= 1; //top
    else if(y >= h)
    code |= 2; //bottom
    if(x >= w)
    code |= 4; //right
    else if (x < 0)
    code |= 8; //left
    return code;
}

/**
 * Clip a line by a rectangle.
 * @clipRect	pointer to the rectangle(x, y, w, h)
 * @line		pointer to the line to be clipped(x0, y0, x1, y1)
 * @return		ture if have a trivial accept or false if a trivial reject
*/
bool ClipLine(int *clipRect, int* line)
{
    int code1, code2, codeout;
    bool accept = false, done = false;
	int x1 = line[0] - clipRect[0];
	int x2 = line[2] - clipRect[0];
	int y1 = line[1] - clipRect[1];
	int y2 = line[3] - clipRect[1];

    code1 = findRegion(x1, y1, clipRect[2], clipRect[3]); //the region outcodes for the endpoints
    code2 = findRegion(x2, y2, clipRect[2], clipRect[3]);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
        if(!(code1 | code2))
			accept = done = true;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2)
			done = true; //the line isn't visible on screen, trivial reject
		else  //if no trivial reject or accept, continue the loop
        {
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) //top
            {
                x = x1 - (x2 - x1) * y1 / (y2 - y1);
                y = 0;
            }
            else if(codeout & 2) //bottom
            {
                x = x1 + (x2 - x1) * (clipRect[3] - y1) / (y2 - y1);
                y = clipRect[3] - 1;
            }
            else if(codeout & 4) //right
            {
                y = y1 + (y2 - y1) * (clipRect[2] - x1) / (x2 - x1);
                x = clipRect[2] - 1;
            }
            else //left
            {
                y = y1 - (y2 - y1) * x1 / (x2 - x1);
                x = 0;
            }
			if(codeout == code1) //first endpoint was clipped
            {
                x1 = x; y1 = y;
                code1 = findRegion(x1, y1, clipRect[2], clipRect[3]);
            }
            else //second endpoint was clipped
            {
                x2 = x; y2 = y;
                code2 = findRegion(x2, y2, clipRect[2], clipRect[3]);
            }
        }
    }
    while(done == false);
	if(accept)
    {
		line[0] = x1 + clipRect[0];
		line[2] = x2 + clipRect[0];
		line[1] = y1 + clipRect[1];
		line[3] = y2 + clipRect[1];
        return true;
    }
    else
    {
		return false;
    }
}

void CGraphics::DrawRect(int x, int y, int width, int height)
{
	DrawLine(x, y, x + width, y);
	DrawLine(x, y + height, x + width, y + height);
	DrawLine(x, y, x, y + height);
	DrawLine(x + width, y, x + width, y + height);
}

void CGraphics::DrawLine(int x0, int y0, int x1, int y1)
{
	int r[4];
	r[0] = m_clipRect[0];
	r[1] = m_clipRect[1];
	r[2] = m_clipRect[2] - m_clipRect[0];
	r[3] = m_clipRect[3] - m_clipRect[1];
	int l[4] = {
		ToRawX(x0), ToRawY(y0), ToRawX(x1), ToRawY(y1)
	};

	if(ClipLine(r, l))
		DrawLine_NoClip_NoTranslat(l[0], l[1], l[2], l[3]);
}
void CGraphics::blandBlur()
{	
#define BIT_G 0x7C0
#define BIT_RB 0xf81f

#define pixel1  *(backBuf+i)
#define pixel2  *(backBuf+i+1)
#define pixel3  *(backBuf+i+SCREEN_WIDTH)
#define pixel4  *(backBuf+i+SCREEN_WIDTH+1)


	SetColor(0x000000); 
	FillRect(0,0,SCREEN_WIDTH,2);


	short* backBuf = (short*)m_image->GetPixelData(); 

	int len = SCREEN_WIDTH * SCREEN_HEIGHT -SCREEN_WIDTH-1;


	for( int i =1; i<len; i++) 
	{


		*(backBuf+i+1+SCREEN_WIDTH) = 
			((((pixel1 & BIT_RB) +(pixel2 & BIT_RB) +(pixel3 & BIT_RB) +(pixel4 & BIT_RB))>>2)& BIT_RB)+
			((((pixel1 & BIT_G) +(pixel2 & BIT_G) +(pixel3 & BIT_G) +(pixel4 & BIT_G))>>2)& BIT_G);

	}
}
/*
void CGraphics::DrawRegion(CImage *pSrc, int x_src, int y_src, int w_src, int h_src, int transform,
	int x_dest, int y_dest, int w_dest, int h_dest, int x_pivot, int y_pivot, int angle, unsigned int palette)
{
	Vertex2D v[4];

    int i;
    unsigned int f = TransformToFlag(transform);

    if (f & FLIP_X)
    {
        v[0].screen.x = ToRawX(x_dest + w_dest);
       	v[1].screen.x = ToRawX(x_dest);
        v[2].screen.x = ToRawX(x_dest);
        v[3].screen.x = ToRawX(x_dest + w_dest);
    }
    else
    {
        v[0].screen.x = ToRawX(x_dest);
        v[1].screen.x = ToRawX(x_dest + w_dest);
        v[2].screen.x = ToRawX(x_dest + w_dest);
        v[3].screen.x = ToRawX(x_dest);
    }

    if (f & FLIP_Y)
    {
        v[0].screen.y = ToRawY(y_dest + h_dest);
        v[1].screen.y = ToRawY(y_dest + h_dest);
        v[2].screen.y = ToRawY(y_dest);
        v[3].screen.y = ToRawY(y_dest);
    }
	else
    {
        v[0].screen.y = ToRawY(y_dest);
        v[1].screen.y = ToRawY(y_dest);
        v[2].screen.y = ToRawY(y_dest + h_dest);
        v[3].screen.y = ToRawY(y_dest + h_dest);
    }

    if (f & ROTATE_90)
    {
        // rotate the specified image region clockwise by 90 degrees
        int xcenter = (v[0].screen.x + v[1].screen.x) / 2;
        int ycenter = (v[0].screen.y + v[3].screen.y) / 2;
        int x_coord;
        for(i = 0; i < 4; i++)
        {
            x_coord = v[i].screen.x;
            v[i].screen.x = xcenter - (v[i].screen.y - ycenter);
            v[i].screen.y = ycenter + (x_coord - xcenter);
        }
    }

	v[0].texture.x = (x_src);
	v[0].texture.y = (y_src);
	v[1].texture.x = (x_src + w_src);
	v[1].texture.y = (y_src);
	v[2].texture.x = (x_src + w_src);
	v[2].texture.y = (y_src + h_src);
	v[3].texture.x = (x_src);
	v[3].texture.y = (y_src + h_src);

    CFMath::Point2D pivot;
	pivot.x = ToRawX(x_pivot);
	pivot.y = ToRawY(y_pivot);
    
	for(i = 0; i < 4; i++)
	{
		CFMath::Rotate(v[i].screen, v[i].screen, pivot, angle);
	}
	DrawPoly4T(v, pSrc, palette);
//	Vertex2D test[4];
//	test[0] = v[2];
//	test[1] = v[3];
//	test[2] = v[0];
//	DrawPoly3T(v, pSrc, palette);
//	DrawPoly3T(test, pSrc, palette);
}*/


//bool CGraphics::CSpanGenerator::Prepare(int yMin, int yMax, int clipY0, int clipY1)
//{
//	m_clipY0 = clipY0;
//	m_clipY1 = clipY1;
//	m_yMin = yMin >= m_clipY0 ? yMin : m_clipY0;
//	m_yMax = yMax <= m_clipY1 ? yMax : m_clipY1;
//	int n = m_yMax - m_yMin;
//	ASSERT(n < MAX_SPAN);
//	if(n <= 0 || n >= MAX_SPAN)
//		return false;
//	int i;
//	for(i = 0; i < n; i++)
//	{
//		m_span[i].xMax = -32768;
//		m_span[i].xMin = 32767;
//	}
//	m_math = &GetMath();
//	return true;
//}
//
//void CGraphics::CSpanGenerator::EmitEdgeT(Vertex2D *p1, Vertex2D *p2)
//{
//	Vertex2D *vTop, *vBottom;
//	//sort by Y
//	if(p1->screen.y <= p2->screen.y)
//	{
//		vTop = p1;
//		vBottom = p2;
//	}
//	else
//	{
//		vTop = p2;
//		vBottom = p1;
//	}
//
//	int yStart = vTop->screen.y;
//	int ySkip = 0;
//	if(yStart < m_yMin)
//	{
//		ySkip = m_yMin - yStart;
//		yStart = m_yMin;
//	}
//
//	int h = vBottom->screen.y > m_yMax ? m_yMax - yStart : vBottom->screen.y - yStart;
//	if(h <= 0)
//		return;
//
//	int deltaY = vBottom->screen.y - vTop->screen.y;
//	int deltaX = vBottom->screen.x - vTop->screen.x;
//	int xStart, xStep, numerator;
//	int errorTerm;
//	CFMath::FloorDivMod(deltaX * (yStart - vTop->screen.y) - 1, deltaY, xStart, errorTerm);
//	xStart += vTop->screen.x + 1;
//	CFMath::FloorDivMod(deltaX, deltaY, xStep, numerator);
//
//	F12 u = IntToF12(vTop->texture.x);
//	F12 du = m_math->FastDiv(IntToF12(vBottom->texture.x - vTop->texture.x), deltaY);
//	//see the comment in DrawSpanT for the reason to decrease u du < 0
//	if(du < 0)
//		--u;
//
//	F12 v = IntToF12(vTop->texture.y);
//	F12 dv = m_math->FastDiv(IntToF12(vBottom->texture.y - vTop->texture.y), deltaY);
//	if(dv < 0)
//		--v;
//
//	if(ySkip)
//	{
//		u += du * ySkip;
//		v += dv * ySkip;
//	}
//
//	SpanT *span = m_span + yStart - m_yMin;
//	do {
//		ASSERT(m_span <= span && m_span + MAX_SPAN > span);
//		if(xStart > span->xMax)
//		{
//			span->xMax = xStart;
//			span->uMax = u;
//			span->vMax = v;
//		}
//		if(xStart < span->xMin)
//		{
//			span->xMin = xStart;
//			span->uMin = u;
//			span->vMin = v;
//		}
//		xStart += xStep;
//		errorTerm += numerator;
//		if(errorTerm >= deltaY)
//		{
//			xStart++;
//			errorTerm -= deltaY;
//		}
//		u += du;
//		v += dv;
//		span++;
//	}while(--h != 0);
//}
//
//void CGraphics::CSpanGenerator::EmitEdge(Vertex2D *p1, Vertex2D *p2)
//{
//	Vertex2D *vTop, *vBottom;
//	//sort by Y
//	if(p1->screen.y <= p2->screen.y)
//	{
//		vTop = p1;
//		vBottom = p2;
//	}
//	else
//	{
//		vTop = p2;
//		vBottom = p1;
//	}
//
//	int yStart = vTop->screen.y;
//	int ySkip = 0;
//	if(yStart < m_yMin)
//	{
//		ySkip = m_yMin - yStart;
//		yStart = m_yMin;
//	}
//
//	int h = vBottom->screen.y > m_yMax ? m_yMax - yStart : vBottom->screen.y - yStart;
//	if(h <= 0)
//		return;
//
//	int deltaY = vBottom->screen.y - vTop->screen.y;
//	int deltaX = vBottom->screen.x - vTop->screen.x;
//	int xStart, xStep, numerator;
//	int errorTerm;
//	CFMath::FloorDivMod(deltaX * (yStart - vTop->screen.y) - 1, deltaY, xStart, errorTerm);
//	xStart += vTop->screen.x + 1;
//	CFMath::FloorDivMod(deltaX, deltaY, xStep, numerator);
//
//	SpanT *span = m_span + yStart - m_yMin;
//	do {
//		ASSERT(m_span <= span && m_span + MAX_SPAN > span);
//		if(xStart > span->xMax)
//		{
//			span->xMax = xStart;
//		}
//		if(xStart < span->xMin)
//		{
//			span->xMin = xStart;
//		}
//		xStart += xStep;
//		errorTerm += numerator;
//		if(errorTerm >= deltaY)
//		{
//			xStart++;
//			errorTerm -= deltaY;
//		}
//		span++;
//	}while(--h != 0);
//}

//void CGraphics::DrawPoly4T(Vertex2D *point, CImage *texture, unsigned int palette)
//{
//	int yMin, yMax;
//	yMin = yMax = point[0].screen.y;
//	if(point[1].screen.y < yMin)
//		yMin = point[1].screen.y;
//	else if(point[1].screen.y > yMax)
//		yMax = point[1].screen.y;
//	if(point[2].screen.y < yMin)
//		yMin = point[2].screen.y;
//	else if(point[2].screen.y > yMax)
//		yMax = point[2].screen.y;
//	if(point[3].screen.y < yMin)
//		yMin = point[3].screen.y;
//	else if(point[3].screen.y > yMax)
//		yMax = point[3].screen.y;
//	CSpanGenerator sg;
//	if(!sg.Prepare(yMin, yMax, m_clipRect[1], m_clipRect[3]))
//		return;
//	sg.EmitEdgeT(point, point + 1);
//	sg.EmitEdgeT(point + 1, point + 2);
//	sg.EmitEdgeT(point + 2, point + 3);
//	sg.EmitEdgeT(point + 3, point);
//	int i, n = sg.m_yMax - sg.m_yMin;
//	for(i = 0; i < n; i++)
//	{
//		DrawSpanT(i + sg.m_yMin, sg.m_span + i, texture, palette, sg.m_math);
//	}
//}

/*
void CGraphics::DrawPoly3T(Vertex2D *point, CImage *texture, unsigned int palette)
{
	int yMin, yMax;
	yMin = yMax = point[0].screen.y;
	if(point[1].screen.y < yMin)
		yMin = point[1].screen.y;
	else if(point[1].screen.y > yMax)
		yMax = point[1].screen.y;
	if(point[2].screen.y < yMin)
		yMin = point[2].screen.y;
	else if(point[2].screen.y > yMax)
		yMax = point[2].screen.y;
	CSpanGenerator sg;
	if(!sg.Prepare(yMin, yMax, m_clipRect[1], m_clipRect[3]))
		return;
	sg.EmitEdgeT(point, point + 1);
	sg.EmitEdgeT(point + 1, point + 2);
	sg.EmitEdgeT(point + 2, point);
	int i, n = sg.m_yMax - sg.m_yMin;
	for(i = 0; i < n; i++)
	{
		DrawSpanT(i + sg.m_yMin, sg.m_span + i, texture, palette, sg.m_math);
	}

}
*/
//void FillHLineTD16S8PK(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette)
//{
//	unsigned short *pos = (unsigned short*)pStart + x;
//	unsigned short *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned char *pixel = timage->GetPixelData();
//	unsigned short *pal = (unsigned short*)timage->GetPaletteData() + palette;
//	int key = timage->GetColorKey();
//	const int tpitch = timage->GetPitch();
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//  		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		int v = pixel[tv * tpitch + tu];
//		if(v != key)
//			*pos = pal[v];
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void FillHLineTD24S8PK(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette)
//{
//	unsigned int *pos = (unsigned int*)pStart + x;
//	unsigned int *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned char *pixel = timage->GetPixelData();
//	unsigned int *pal = (unsigned int*)timage->GetPaletteData() + palette;
//	int key = timage->GetColorKey();
//	const int tpitch = timage->GetPitch();
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//  		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		int v = pixel[tv * tpitch + tu];
//		if(v != key)
//			*pos = pal[v];
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void FillHLineTD12S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity)
//{
//	unsigned short *pos = (unsigned short*)pStart + x;
//	unsigned short *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned char *pixel = timage->GetPixelData();
//	unsigned short *pal = (unsigned short*)timage->GetPaletteData() + palette;
//	int key = timage->GetColorKey();
//	const int tpitch = timage->GetPitch();
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		int v = pixel[tv * tpitch + tu];
//		if(v != key)
//		{
//			int bg = *pos;
//			int fg = pal[v];
//			ALPHA_BLEND_S12_D12(*pos, bg, fg, opacity);
//		}
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void FillHLineTD16S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity)
//{
//	unsigned short *pos = (unsigned short*)pStart + x;
//	unsigned short *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned char *pixel = timage->GetPixelData();
//	unsigned short *pal = (unsigned short*)timage->GetPaletteData() + palette;
//	int key = timage->GetColorKey();
//	const int tpitch = timage->GetPitch();
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		int v = pixel[tv * tpitch + tu];
//		if(v != key)
//		{
//			int bg = *pos;
//			int fg = pal[v];
//			ALPHA_BLEND_S16_D16(*pos, bg, fg, opacity);
//		}
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void FillHLineTD24S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity)
//{
//	unsigned int *pos = (unsigned int*)pStart + x;
//	unsigned int *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned char *pixel = timage->GetPixelData();
//	unsigned int *pal = (unsigned int*)timage->GetPaletteData() + palette;
//	int key = timage->GetColorKey();
//	const int tpitch = timage->GetPitch();
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		int v = pixel[tv * tpitch + tu];
//		if(v != key)
//		{
//			int bg = *pos;
//			int fg = pal[v];
//			ALPHA_BLEND_S24_D24(*pos, bg, fg, opacity);
//		}
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void FillHLineTD16S32A(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length)
//{
//	unsigned short *pos = (unsigned short*)pStart + x;
//	unsigned short *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned int *pixel = (unsigned int*)timage->GetPixelData();
//	const int tpitch = timage->GetPitch() / 4;
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		unsigned int fg = pixel[tv * tpitch + tu];
//		unsigned int bg = *pos;
//		unsigned int a = fg >> 24;
//		ALPHA_BLEND_S32_D16(*pos, bg, fg, a);
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}
//
//void FillHLineTD16S32AO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, int opacity)
//{
//	unsigned short *pos = (unsigned short*)pStart + x;
//	unsigned short *end = pos + length;
//	CIndexedImage *timage = DYNAMIC_CAST(CIndexedImage*, texture);
//	unsigned int *pixel = (unsigned int*)timage->GetPixelData();
//	const int tpitch = timage->GetPitch() / 4;
//
//	while (pos < end)
//	{
//		int tu = F12ToInt(uStart);
//		int tv = F12ToInt(vStart);
//#if DEBUG_LEVEL > 1
//		ASSERT(tu >= 0 && tu < timage->GetWidth());
//		ASSERT(tv >= 0 && tv < timage->GetHeight());
//#endif
//		unsigned int fg = pixel[tv * tpitch + tu];
//		unsigned int bg = *pos;
//		unsigned int a = (fg >> 24) * opacity / ALPHA_DEVISOR;
//		ALPHA_BLEND_S32_D16(*pos, bg, fg, a);
//		++pos;
//		uStart += dux;
//		vStart += dvx;
//	}
//}

//void CGraphics::DrawSpanT(int y, CGraphics::SpanT *span, CImage *texture, unsigned int palette, CFMath *math)
//{
//	const int dx = span->xMax - span->xMin;
//	if(dx <= 0)
//		return;
//	F12 uStart = span->uMin;
//	F12 dux = math->FastDiv((span->uMax - span->uMin), dx);
//	//if dux < 0, using span->uMin as the start of u may result in sampling out of texture
//	//bound since u is exclusive on right edge. For example, if span->uMin = u_right, the
//	//texture coordinate of first pixel will be u_right, which is not acceptable.
//	//To correct this problem, decrease uStart by one when dux < 0.
//	if(dux < 0)
//		--uStart;
//
//	F12 vStart = span->vMin;
//	F12 dvx = math->FastDiv((span->vMax - span->vMin), dx);
//	//same as uStart
//	if(dvx < 0)
//		--vStart;
//
//	int xStart = span->xMin;
//	int xSkip = 0;
//	if(xStart < m_clipRect[0])
//	{
//		xSkip = m_clipRect[0] - xStart;
//		xStart = m_clipRect[0];
//	}
//	if(xSkip)
//	{
//		uStart += dux * xSkip;
//		vStart += dvx * xSkip;
//	}
//	int xEnd = span->xMax;
//	if(xEnd > m_clipRect[2])
//		xEnd = m_clipRect[2];
//	unsigned char* p = m_image->GetPixelData() + m_image->GetPitch() * y;
//	FillHLineT(uStart, dux, vStart, dvx, texture, p, xStart, xEnd - xStart, palette);
//}

//void CGraphics::FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
//{
//	int yMin, yMax;
//	yMin = yMax = y1;
//	if(y2 < yMin)
//		yMin = y2;
//	else if(y2 > yMax)
//		yMax = y2;
//	if(y3 < yMin)
//		yMin = y3;
//	else if(y3 > yMax)
//		yMax = y3;
//
//	yMin = ToRawY(yMin);
//	yMax = ToRawY(yMax);
//
//	Vertex2D point[3];
//	point[0].screen.x = ToRawX(x1);
//	point[0].screen.y = ToRawY(y1);
//	point[1].screen.x = ToRawX(x2);
//	point[1].screen.y = ToRawY(y2);
//	point[2].screen.x = ToRawX(x3);
//	point[2].screen.y = ToRawY(y3);
//	
//	CSpanGenerator sg;
//	if(!sg.Prepare(yMin, yMax, m_clipRect[1], m_clipRect[3]))
//		return;
//	sg.EmitEdge(point, point + 1);
//	sg.EmitEdge(point + 1, point + 2);
//	sg.EmitEdge(point + 2, point);
//
//	int i, n = sg.m_yMax - sg.m_yMin;
//	for(i = 0; i < n; i++)
//	{
//		FillRect(sg.m_span[i].xMin, i + sg.m_yMin, sg.m_span[i].xMax - sg.m_span[i].xMin, 1);
//	}
//
//	//the right and bottom edge is not filled by above code, so fills these edges
//	//to be consistent with MIDP's FillTriangle
//	DrawLine(x1, y1, x2, y2);
//	DrawLine(x2, y2, x3, y3);
//	DrawLine(x1, y1, x3, y3);
//}

#ifdef ENABLE_ZDS


const unsigned int rShift = 5;
const unsigned int gShift = 6;
const unsigned int bShift = 5;

const unsigned int rMask = 0xF800;
const unsigned int gMask = 0x7E0;
const unsigned int bMask = 0x1f;

void DrawPixel_Additive_565(unsigned short* dstPixel, unsigned short* srcPixel, unsigned char v)
{
	int r = *dstPixel & rMask;
	int g = *dstPixel & gMask;
	int b = *dstPixel & bMask;

	r += (v << 8) & rMask;
	if((r & ~rMask) != 0) r = rMask;

	g += (v << 3) & gMask;
	if((g & ~gMask) != 0) g = gMask;

	b += (v >> 3) & bMask;
	if((b & ~bMask) != 0) b = bMask;

	*dstPixel = (r & rMask) |(g & gMask) | (b & bMask);	
}

const unsigned int ALPHA_SHIFT = 8;

void DrawPixel_AlphaBlend_565(unsigned short* dstPixel, unsigned short* srcPixel, unsigned char a)
{
	const unsigned int c = *srcPixel;

	int r = *dstPixel & rMask;
	r += (((c & rMask) - r) * a) >> ALPHA_SHIFT;
	
	int g = *dstPixel & gMask;
	g += (((c & gMask) - g) * a) >> ALPHA_SHIFT;
	
	int b = *dstPixel & bMask;
	b += (((c & bMask) - b) * a) >> ALPHA_SHIFT;
	
	*dstPixel = (r & rMask) | (g & gMask) | (b & bMask);		
}


void BlitD16SZDS(void *dst, void *src, void *alpha, BlitParam *par, int state)
{
	unsigned short *d = (unsigned short*)dst;
	unsigned short *s = (unsigned short*)src;
	unsigned char  *a = (unsigned char*)alpha;

	const int dx = par->dstXPitch;
	const int dy = par->dstYPitch - par->width * dx;
	const int sy = par->srcYPitch - par->width * sizeof(*s);
	const int ay = sy >> 1;

	const int w = par->width;	

	CZDS::RenderState renderState = (CZDS::RenderState)state;

	void (*DrawPixel)(unsigned short* , unsigned short*, unsigned char) = NULL;

	switch(renderState)
	{
	case CZDS::ALPHA_BLEND:
		DrawPixel = DrawPixel_AlphaBlend_565;
		break;

	case CZDS::ADDITIVE:
		DrawPixel = DrawPixel_Additive_565;
		break;

	default:
		ASSERT(0);
		return;
	}

	for(int i = par->height; i != 0; i--)
	{
		int j = w;

		while(j != 0)
		{		
			DrawPixel(d, s, *a);
			d = (unsigned short*)((char*)d + dx);	
			s++;a++;--j;
		}
		
		a = a + ay;
		s = (unsigned short*)((char*)s + sy);
		d = (unsigned short*)((char*)d + dy);
	}
}	

#endif
