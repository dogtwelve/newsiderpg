// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min
// Author: Du Hai Tao	Add transform support to the DrawRegion function that support rotate

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "image.h"
//#include "FMath.h"
#include "..\wipi\brewtowipi.h" //++sj

typedef struct {
	unsigned short width;
	unsigned short height;
	unsigned short opacity;
	short srcYPitch;
	short dstXPitch;
	short dstYPitch;
	void *palette;
	unsigned int colorKey;
	int srcSkip;	//for RLE source, indicating how many pixels in source should be skipped. minus means that the whole source will be blit.
					//for 4 bit source, indicating how many pixels in source should be skipped, only 0 and 1 is valid.
	unsigned char palMask;
	unsigned char palBits;
	unsigned char bChannel;
//	int x_dest;
//	int y_dest;
//	unsigned char *bgbuff;	
	int p_color;
}BlitParam;

/// @brief Provides simple 2D geometric rendering capability.
///
/// Most functions are identical to the APIs in J2ME MIDP Graphics class.\n\n
/// This class can't be instantiated, use CGraphicsT instead. Please refer to the code of
/// \code CMutableImage::CMutableImage(unsigned int w, unsigned int h, int bpp, MemoryType memType) \endcode
/// for how to instantiate a CGraphicsT class and how to attach to a mutable image. In most
/// cases there's no need to create a stand-along CGraphicsT object, using CMutableImage
/// returned from CMutableImage::GetGraphics is enough.\n\n
/// Each CMutableImage object contains a CGraphics object, you can use CMutableImage::GetGraphics
/// to get the CGraphics of the mutable image.\n\n
/// Function Name,Clip,Translate,8Bit Dest,12Bit Dest,16Bit Dest,Opacity
/// ToNativeColor,,,,Y,Y,
/// ToRGB24Color,,,,Y,Y,
/// SetPixel,Y,Y,Y,Y,Y,
/// DrawRegion_NoClip_NoTranslat,,,Y,Y,Y,
/// DrawRegion,Y,Y,Y,Y,Y,
/// FillRect,Y,Y,,,Y,
/// @todo Support RLE image

class CGraphics
{


public:
	
	void DrawString(char* str, int x, int y, int anchor)
	{
		//Robust, must be implements
	}

	

//	typedef struct {
//		CFMath::Point2D screen;
//		CFMath::Point2D texture;
//	}Vertex2D;

//	typedef struct {
//		short xMin, xMax;
//		F12 uMin, uMax;
//		F12 vMin, vMax;
//	}SpanT;

	/// @brief constant for transform, same as MIDP2.0
	enum Transform{
		///causes the specified image region to be copied unchanged
		TRANS_NONE = 0,
		///causes the specified image region to be rotated clockwise by 90 degrees
		TRANS_MIRROR_ROT180 = 1,
		///causes the specified image region to be rotated clockwise by 180 degrees
		TRANS_MIRROR = 2,
		///causes the specified image region to be rotated clockwise by 270 degrees
		TRANS_ROT180 = 3,
		///causes the specified image region to be reflected about its vertical center
		TRANS_MIRROR_ROT270 = 4,
		///causes the specified image region to be reflected about its vertical center
		///and then rotated clockwise by 90 degrees
		TRANS_ROT90 = 5,
		///causes the specified image region to be reflected about its vertical center
		///and then rotated clockwise by 180 degrees
		TRANS_ROT270 = 6,
		///causes the specified image region to be reflected about its vertical center
		///and then rotated clockwise by 270 degrees
		TRANS_MIRROR_ROT90 = 7
	};



	/// @brief flags of transform translated by TransformToFlag
	enum {
		///The transform contains x flip
		FLIP_X = 1,
		///The transform contains y flip
		FLIP_Y = 2,
		///The transform contains rotation by 90 degrees
		ROTATE_90 = 4
	};

	
	enum{
		HCENTER = 1 << 0,
		VCENTER = 1 << 1,
		LEFT = 1 << 2,
		RIGHT = 1 << 3,
		TOP = 1 << 4,
		BASELINE = 1 << 5,
		BOTTOM = 1 << 6,
	};




	/// @brief default constructor.
	///
	/// No image is attached. Set color to white and default opacity to 255.\n
	/// Must call SetImage before any graphics operation.
	CGraphics(){
		m_channel = false;
		m_image =	NULL;
		SetColor(0);
		SetOpacity(255);
	}

	/// @brief destructor.
	virtual ~CGraphics();

	/// @brief Set the destination image to which CGraphics functions will render. 
	///	@param[in]	image	pointer to CMutableImage that will be used for rendering.
	void SetImage(CMutableImage *image);

	/// @brief Get the destination image to which CGraphics functions will render. 
	///	@return	Pointer to the current destination image.
	CMutableImage* GetImage();

	/// @brief Set the current clip to the rectangle specified by the given coordinates.
	///
	/// Rendering operations have no effect outside of the clipping area.
	/// @attention Some functions like DrawLine_NoClip_NoTranslat ignore the clip.
	///	@param[in]	x	the x coordinate of the new clip rectangle.
	///	@param[in]	y	the y coordinate of the new clip rectangle.
	///	@param[in]	width	the width of the new clip rectangle.
	///	@param[in]	height	the height of the new clip rectangle.
	void SetClip(int x, int y, int width, int height);

	void SetChannel(unsigned char channel);	
	void UnSetChannel(unsigned char channel);	
	unsigned char GetChannel();	

	bool GetIntersection( short* rect1, short* rect2, short* intersect )
	{
		if( rect1[2] < rect2[0] )
		{
			return false;
		}
		if ( rect1[0] > rect2[2] )
		{
			return false;
		}
		if ( rect1[1] > rect2[3] )
		{
			return false;
		}
		if ( rect1[3] < rect2[1] )
		{
			return false;
		}
		intersect[0] = max( rect1[0], rect2[0] );
		intersect[1] = max( rect1[1], rect2[1] );
		intersect[2] = min( rect1[2], rect2[2] );
		intersect[3] = min( rect1[3], rect2[3] );
		return true;
	}

	void ClipRect( int x, int y, int width, int height )
	{
		short rect[4];
		rect[0] = x + m_translate[0];
		rect[1] = y + m_translate[1];
		rect[2] = rect[0] + width;
		rect[3] = rect[1] + height;
		short newClip[4] = {0};

		if( GetIntersection( m_clipRect, rect, newClip ) )
		{
			SetClip( newClip[0] - m_translate[0], newClip[1] - m_translate[1],
				newClip[2] - newClip[0], newClip[3] - newClip[1] );
		}
		else
		{
			SetClip( 0, 0, 0, 0 );
		}		
	}

	/// @brief Reset the current clip to the entire destination image.
	void ResetClip();

	/// @brief Get the Y offset of the current clipping area, relative to the coordinate system origin of this graphics context. 
	///	@return	Y offset of the current clipping area.
	int GetClipX();

	/// @brief Get the X offset of the current clipping area, relative to the coordinate system origin of this graphics context. 
	///	@return	X offset of the current clipping area.
	int GetClipY();

	/// @brief Get the width of the current clipping area. 
	///	@return	width of the current clipping area.
	int GetClipWidth();

	/// @brief Get the height of the current clipping area. 
	///	@return	height of the current clipping area.
	int GetClipHeight();

	/// @brief Translate the origin of the graphics context to the point (x, y) in the current coordinate system.
	///
	/// All coordinates used in subsequent rendering operations on this graphics context will be relative to this new origin.\n
	/// The effect of calls to Translate() are cumulative. For example, calling Translate(1, 2) and then Translate(3, 4) results in a translation of (4, 6).\n 
	/// The application can set an absolute origin (ax, ay) using the following technique:
	/// \code g.Translate(ax - g.getTranslateX(), ay - g.getTranslateY()) \endcode
	///	@param[in]	x	the x coordinate of the new translation origin
	///	@param[in]	y	the y coordinate of the new translation origin
	void Translate(int x, int y);
	
	/// @brief Get the X coordinate of the translated origin of this graphics context.
	///	@return	X of current origin.
	short GetTranslateX();

	/// @brief Get the Y coordinate of the translated origin of this graphics context.
	///	@return	Y of current origin.
	short GetTranslateY();
	
	/// @brief Set the current color and opacity to the specified ARGB values.
	///
	/// All subsequent rendering operations will use this specified color and opacity level.\n
	/// The RGB value passed in is interpreted with the least significant eight bits giving the blue component,
	/// the next eight more significant bits giving the green component, the next eight more significant bits giving the red component,
	/// and the last eight most significant bits giving the opacity level.
	/// That is to say, the color component is specified in the form of 0xAARRGGBB.
	///	@param[in]	argb	the color being set
	void SetARGBColor(unsigned int argb);

	/// @brief Set the current color to the specified RGB values.
	///
	/// All subsequent rendering operations will use this specified color.\n
	/// The RGB value passed in is interpreted with the least significant eight bits giving the blue component,
	/// the next eight more significant bits giving the green component, and the next eight more significant bits giving the red component.
	/// That is to say, the color component is specified in the form of 0x00RRGGBB. The high order byte of this value is ignored.
	///	@param[in]	rgb	the color being set
	void SetColor(unsigned int rgb);

	void SetColor(unsigned int r, unsigned int g, unsigned int b);

	/// @brief Get the current color.
	///	@return	an integer in form 0x00RRGGBB
	unsigned int GetColor();

	/// @brief Set the current opacity level.
	///
	/// All subsequent rendering operations will use this specified opacity level.\n
	/// 0 means totally transparent, while 255 means totally opaque.
	///	@param[in]	a	opacity level from 0 to 255.
	void SetOpacity(unsigned int a);

	/// @brief Get the current opacity level.
	///	@return	an integer from 0 to 255
	unsigned int GetOpacity();

	/// @brief Convert a RGB color to native color.
	///	@param[in]	rgb	RGB value in 0x00RRGGBB.
	///	@return	an integer of converted color in native format
	virtual unsigned int ToNativeColor(unsigned int rgb) = 0;

	/// @brief Convert a native color to RGB color in 0x00RRGGBB.
	///	@param[in]	color	color in native pixel format
	///	@return	an integer of native color to be converted.
	virtual unsigned int ToRGB24Color(unsigned int color) = 0;

	/// @brief Draw a pixel in specified position.
	///	@param[in]	x	the x coordinate of the pixel to be drawn
	///	@param[in]	y	the y coordinate of the pixel to be drawn
	///	@param[in]	nativeColor	the color of the pixel to be drawn in native color format
	virtual void SetPixel(int x, int y, unsigned int nativeColor) = 0;


	void GetPixels(unsigned char *src,unsigned short *dest,  int offset, int scanlength,int x, int y,int width,int height, int flag);

	/// @brief Copies a region of the specified source image to a location within the destination,
	/// possibly transforming (rotating and reflecting) the image data using the chosen transform function.
	/// @warning This function is almost the same as the DrawRegion function in J2ME MIDP API, except the last
	/// parameter. In MIDP API, it's anchor point. But here it's the number of palette shift.
	///	@param[in]	pSrc	the source image to copy from
	///	@param[in]	x_src	the x coordinate of the upper left corner of the region within the source image to copy
	///	@param[in]	y_src	the y coordinate of the upper left corner of the region within the source image to copy
	///	@param[in]	width	the width of the region to copy
	///	@param[in]	height	the height of the region to copy
	///	@param[in]	transform	the desired transformation for the selected region being copied
	///	@param[in]	x_dest	the x coordinate of the upper left corner in the destination drawing area
	///	@param[in]	y_dest	the y coordinate of the upper left corner in the destination drawing area
	///	@param[in]	palette	the number of palette entry to shift in source image


//	void DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
//		int x_dest, int y_dest, unsigned int palette = 0);
//SangHo - Blend - 블랜딩을 위해서 끝에 인자값 2개 추가 - 1번인자 블랜딩 종류 , 2번인자 블랜딩 퍼센트
	void DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, unsigned int palette = 0,/*Blend*/ unsigned char Blend_Kind = 0, unsigned  int Blend_Percent = 0);


	void  DrawRegion(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, int anchor, unsigned int palette);

	void DrawImage(CImage *pSrc, int x, int y, int anchor)
	{
			DrawRegion(pSrc, 0, 0, pSrc->GetWidth(), pSrc->GetHeight(), CGraphics::TRANS_NONE,
		x, y, anchor, 0);
	};
	/// @brief Same as DrawRegion but no clip and translate.
	///
	/// This function is slightly faster than DrawRegion. If there're many small image clips to be drawn in screen,
	/// using this one can be faster.
	virtual void DrawRegion_NoClip_NoTranslat(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, unsigned int palette, /*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent) = 0;// SangHo - Blend - 


	//bool DrawGLI(CGLI *pGli, int transform, int x_dest, int y_dest, unsigned int palette = 0);


	/// @brief Fills the specified rectangle with the current color.
	///
	/// If either width or height is zero or less, nothing is drawn.
	///	@param[in]	x	the x coordinate of the rectangle to be filled
	///	@param[in]	y	the y coordinate of the rectangle to be filled
	///	@param[in]	width	the width of the rectangle to be filled
	///	@param[in]	height	the height of the rectangle to be filled
	virtual void FillRect(int x, int y, int width, int height) = 0;
	//virtual void FillRectSemitransparent(int x, int y, int width, int height) = 0;
	
	/// @brief Draws the specified rectangle with the current color.
	///
	///	@param[in]	x	the x coordinate of the rectangle to be drawn
	///	@param[in]	y	the y coordinate of the rectangle to be drawn
	///	@param[in]	width	the width of the rectangle to be drawn
	///	@param[in]	height	the height of the rectangle to be drawn
	void DrawRect(int x, int y, int width, int height);

	/// @brief Draws a line between the coordinates (x1,y1) and (x2,y2) using the current color.
	///	@param[in]	x0	the x coordinate of the start of the line
	///	@param[in]	y0	the y coordinate of the start of the line
	///	@param[in]	x1	the x coordinate of the end of the line
	///	@param[in]	y1	the y coordinate of the end of the line
	void DrawLine(int x0, int y0, int x1, int y1);

	void blandBlur(); 

	/// @brief Same as DrawLine but no clip and translate.
	///
	/// This function is slightly faster than DrawLine.
	virtual void DrawLine_NoClip_NoTranslat(int x0, int y0, int x1, int y1) = 0;


	/// @brief Draws the outline of a circular.
	///	@param[in]	x	the x coordinate of the center of the circular.
	///	@param[in]	y	the y coordinate of the center of the circular.
	///	@param[in]	r	the radius of the circular to be drawn
	//virtual void DrawCircle(int x, int y, int r) = 0;

	virtual void DrawArc(int x0, int y0, int w, int h, int start, int end) = 0;
	virtual void FillArc(int x0, int y0, int w, int h, int start, int end) = 0;

	/// @brief Copies a region of the specified source image to a location within the destination,
	/// possibly transforming (rotating, reflecting and scaling) the image data using the chosen transform function.
	///	@param[in]	pSrc	the source image to copy from
	///	@param[in]	x_src	the x coordinate of the upper left corner of the region within the source image to copy
	///	@param[in]	y_src	the y coordinate of the upper left corner of the region within the source image to copy
	///	@param[in]	w_src	the width of the source region to copy
	///	@param[in]	h_src	the height of the source region to copy
	///	@param[in]	transform	the desired transformation for the selected region being copied
	///	@param[in]	x_dest	the x coordinate of the upper left corner in the destination drawing area
	///	@param[in]	y_dest	the y coordinate of the upper left corner in the destination drawing area
	///	@param[in]	w_dest	the width of the destination region
	///	@param[in]	h_dest	the height of the destination region
	///	@param[in]	x_pivot	the x coordinate of the rotation pivot pointe within the destination drawing area
	///	@param[in]	y_pivot	the y coordinate of the rotation pivot pointe within the destination drawing area
	///	@param[in]	angle	the angle to rotate in 4096ths of a circle (2PI radian = 4096). Can be set to any signed integer.
	///	@param[in]	palette	the number of palette entry to shift in source image
//	void DrawRegion(CImage *pSrc, int x_src, int y_src, int w_src, int h_src, int transform,
//		int x_dest, int y_dest, int w_dest, int h_dest, int x_pivot, int y_pivot, F12 angle,
//		unsigned int palette = 0);


	/// @brief Fills the specified triangle will the current color.
	///
	/// The lines connecting each pair of points are included in the filled triangle.
	///	@param[in]	x1	the x coordinate of the first vertex of the triangle
	///	@param[in]	y1	the y coordinate of the first vertex of the triangle
	///	@param[in]	x2	the x coordinate of the second vertex of the triangle
	///	@param[in]	y2	the y coordinate of the second vertex of the triangle
	///	@param[in]	x3	the x coordinate of the third vertex of the triangle
	///	@param[in]	y3	the y coordinate of the third vertex of the triangle
	//void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

	/// @brief Draw a textured quad with affine texture mapping.
	///	@param[in]	point	pointer to the four vertex of the quad
	///	@param[in]	texture	the texture of the quad
	///	@param[in]	palette	the number of palette entry to shift in texture image
//	void DrawPoly4T(Vertex2D *point, CImage *texture, unsigned int palette);

	/// @brief Draw a textured triangle with affine texture mapping.
	///	@param[in]	point	pointer to the three vertex of the triangle
	///	@param[in]	texture	the texture of the triangle
	///	@param[in]	palette	the number of palette entry to shift in texture image
//	void DrawPoly3T(Vertex2D *point, CImage *texture, unsigned int palette);

	static unsigned int TransformToFlag(int transform);

	virtual void EnableGrayEffect() = 0;	
	virtual void EnableBlackAlphaEffect(int alpha , int nativeRgb  ) = 0;

	unsigned char *m_buffPixel;

protected:

//	class CSpanGenerator {
//	public:
//		enum {
//			MAX_SPAN = 320
//		};
//		bool Prepare(int yMin, int yMax, int clipY0, int clipY1);
//		void EmitEdgeT(Vertex2D *p1, Vertex2D *p2);
//		void EmitEdge(Vertex2D *p1, Vertex2D *p2);
//
//		int m_yMin, m_yMax;
//		int m_clipY0, m_clipY1;
//		SpanT m_span[MAX_SPAN];
//		CFMath *m_math;
//	};

	int ToRawX(int logicX);
	int ToRawY(int logicY);
//	void DrawSpanT(int y, CGraphics::SpanT *span, CImage *texture, unsigned int palette, CFMath *math);
//	virtual void FillHLineT(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette) = 0;

	///Clip rectangle {l, t, r, b}. r, b is exclusive
	unsigned char m_channel;

	short m_clipRect[4];
	short m_translate[2];

	unsigned int m_color;
	




public:
	CMutableImage *m_image;
	void fillRoundRect(int posX, int posY, int width, int height, int start, int end)
	{
		FillRect(posX,posY,width,height);
	}

	void setAlpha(int color)
	{
		SetOpacity(color);
	}
};

inline CMutableImage* CGraphics::GetImage()
{
	return m_image;
}

inline void CGraphics::ResetClip()
{
	m_clipRect[0] = m_clipRect[1] = 0;
	m_clipRect[2] = m_image->GetWidth();
	m_clipRect[3] = m_image->GetHeight();
}

inline int CGraphics::GetClipX() {
	return m_clipRect[0] - m_translate[0];
}
inline int CGraphics::GetClipY() {
	return m_clipRect[1] - m_translate[1];
}
inline int CGraphics::GetClipWidth() {
	return m_clipRect[2] - m_clipRect[0] /*- m_translate[0]*/;
}
inline int CGraphics::GetClipHeight() {
	return m_clipRect[3] - m_clipRect[1] /*- m_translate[1]*/;
}

inline void CGraphics::Translate(int x, int y) {
	m_translate[0] += x;
	m_translate[1] += y;
}

inline short CGraphics::GetTranslateX() {
	return m_translate[0];
}
inline short CGraphics::GetTranslateY() {
	return m_translate[1];
}

inline int CGraphics::ToRawX(int logicX) {
	return logicX + m_translate[0];
}

inline int CGraphics::ToRawY(int logicY) {
	return logicY + m_translate[1];
}

inline void CGraphics::SetARGBColor(unsigned int argb) {
	m_color = argb;
}

inline void CGraphics::SetColor(unsigned int rgb) {
	//ASSERT((rgb >> 24) == 0);
	m_color = (m_color & 0xff000000) | rgb;
}
inline void CGraphics::SetColor( unsigned int r, unsigned int g, unsigned int b ){
	SetColor( GET_RGB(r,g,b) );
}
inline unsigned int CGraphics::GetColor() {
	return m_color & 0xffffff;
}
inline void CGraphics::SetOpacity(unsigned int a) {
	ASSERT(a < 256);
	m_color = (m_color & 0xffffff) | (a << 24);
}
inline unsigned int CGraphics::GetOpacity() {
	return m_color >> 24;
}

inline unsigned int CGraphics::TransformToFlag(int transform) {
	static const unsigned char flag[] = {
		0, FLIP_Y, FLIP_X, FLIP_X | FLIP_Y,
		FLIP_Y | ROTATE_90, ROTATE_90, FLIP_X | FLIP_Y | ROTATE_90, FLIP_X | ROTATE_90
	};
	return flag[transform];
}

typedef void (*BlitFunc)(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);

//void BlitD8S8(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S8PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD16S8PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S8PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD8S8K(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S8PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD16S8PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S8PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8P(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8PK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8PA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S8PAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);


void BlitD16S4P(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S4PK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S4PA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S4PO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S4PKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S4PAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);


void BlitD16S16(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S24(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S12O(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S16O(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S24O(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S16K(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S24K(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S12KO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
#ifdef ENABLE_ALPHA
void BlitD16S16KO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
#endif
//void BlitD24S24KO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S32A(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16S32A(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S32A(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD12S32AO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD16S32AO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
//void BlitD24S32AO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);

void BlitD16SRLE(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEK(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEA(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEKO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEAO(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);

void BlitD16SRLEKG(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);
void BlitD16SRLEKOC(void *dst, void *src, BlitParam *par,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);


void BlitD16SI64RLEAOL(void *dst, void *src, BlitParam *par , void *bst);

void FillRect16(void *dst, int w, int h, int pitch, unsigned int nativeRgb);
void FillRect24(void *dst, int w, int h, int pitch, unsigned int nativeRgb);
//void FillRectARGB12(void *dst, int w, int h, int pitch, unsigned int argb);
#ifdef ENABLE_ALPHA
void FillRectARGB16(void *dst, int w, int h, int pitch, unsigned int nativeRgb, unsigned int alpha);
void DrawLineARGB16(unsigned short *dst, int dx, int dy, int pitch, unsigned int nativeColor, unsigned int alpha);
#endif
//void FillRectARGB24(void *dst, int w, int h, int pitch, unsigned int argb);
void DrawLine16(unsigned short *dst, int dx, int dy, int pitch, unsigned int nativeColor);
void DrawLine24(unsigned int *dst, int dx, int dy, int pitch, unsigned int nativeColor);
//void FillHLineTD16S8PK(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette);
//void FillHLineTD24S8PK(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette);
//void FillHLineTD12S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity);
//void FillHLineTD16S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity);
//void FillHLineTD24S8PKO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette, int opacity);
//void FillHLineTD16S32A(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length);
//void FillHLineTD16S32AO(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, int opacity);


#ifdef ENABLE_ZDS
void BlitD16SZDS(void *dst, void *src, void *alpha, BlitParam *par, int state);
#endif

template <typename PT, int bpp>
class CGraphicsT: public CGraphics
{
public:
	//This dummy line remove ADS compiler warning
	typedef CGraphicsT<PT, bpp> FOOTYPE;
	CGraphicsT() {
		// a: opacity, 0 - no, 1 - yes
		// b: src color key, 0 - no, 1 - yes
		// c: src bpp, 0 - 8bit, 1 - 24 bit, 2 - Native
		MEMSET(m_blitFuncs, 0, sizeof(m_blitFuncs));
		if(bpp == 8)
		{
			m_blitFuncs[0][0][0] = NULL;//BlitD8S8;
			m_blitFuncs[0][1][0] = NULL;//BlitD8S8K;
		}
		else if(bpp == 12)
		{
			m_blitFuncs[0][0][0] = BlitD16S8P;
			m_blitFuncs[0][1][0] = BlitD16S8PK;
			m_blitFuncs[1][0][0] = NULL;//BlitD12S8PO;
			m_blitFuncs[1][1][0] = NULL;//BlitD12S8PKO;
			m_blitFuncs[0][0][1] = NULL;//BlitD12S32A;
			m_blitFuncs[0][1][1] = NULL;//BlitD12S32A;
			m_blitFuncs[1][0][1] = NULL;//BlitD12S32AO;
			m_blitFuncs[1][1][1] = NULL;//BlitD12S32AO;
			m_blitFuncs[0][0][2] = BlitD16S16;
			m_blitFuncs[0][1][2] = BlitD16S16K;
			m_blitFuncs[1][0][2] = NULL;//BlitD12S12O;
			m_blitFuncs[1][1][2] = NULL;//BlitD12S12KO;
		}
		else if(bpp == 16)
		{
			m_blitFuncs[0][0][0] = BlitD16S8P;
			m_blitFuncs[0][1][0] = BlitD16S8PK;
			m_blitFuncs[0][2][0] = BlitD16S8PA;
			m_blitFuncs[1][0][0] = BlitD16S8PO;
			m_blitFuncs[1][1][0] = BlitD16S8PKO;
			m_blitFuncs[1][2][0] = BlitD16S8PAO;
			
			m_blitFuncs[0][0][1] = NULL;//BlitD16S32;
			m_blitFuncs[0][1][1] = NULL;//BlitD16S32K;
			m_blitFuncs[0][2][1] = BlitD16S32A;
			m_blitFuncs[1][0][1] = NULL;//BlitD16S32O;
			m_blitFuncs[1][1][1] = NULL;//BlitD16S32KO;
			m_blitFuncs[1][2][1] = BlitD16S32A;//BlitD16S32AO;

			m_blitFuncs[0][0][2] = BlitD16S16;
			m_blitFuncs[0][1][2] = BlitD16S16K;	
			m_blitFuncs[0][2][2] = NULL;//BlitD16S16A;
#ifdef ENABLE_ALPHA
			m_blitFuncs[1][0][2] = BlitD16S16O;
			m_blitFuncs[1][1][2] = BlitD16S16KO;
			m_blitFuncs[1][2][2] = NULL;//BlitD16S16AO;
#else
			m_blitFuncs[1][0][2] = NULL;//BlitD16S16O;
			m_blitFuncs[1][1][2] = NULL;//BlitD16S16KO;
			m_blitFuncs[1][2][2] = NULL;//BlitD16S16AO;
#endif
			m_blitFuncs[0][0][3] = BlitD16SRLE;
			m_blitFuncs[0][1][3] = BlitD16SRLEK;
			m_blitFuncs[0][2][3] = BlitD16SRLEA;
			m_blitFuncs[1][0][3] = BlitD16SRLEO;
			m_blitFuncs[1][1][3] = BlitD16SRLEKO;
			m_blitFuncs[1][2][3] = BlitD16SRLEAO;	

			m_blitFuncs[0][0][4] = BlitD16S4P;
			m_blitFuncs[0][1][4] = BlitD16S4PK;
			m_blitFuncs[0][2][4] = BlitD16S4PA;
			m_blitFuncs[1][0][4] = BlitD16S4PO;
			m_blitFuncs[1][1][4] = BlitD16S4PKO;
			m_blitFuncs[1][2][4] = BlitD16S4PAO;
			
		}
		else if(bpp == 24)
		{
			m_blitFuncs[0][0][0] = NULL;//BlitD24S8P;
			m_blitFuncs[0][1][0] = NULL;//BlitD24S8PK;
			m_blitFuncs[1][0][0] = NULL;//BlitD24S8PO;
			m_blitFuncs[1][1][0] = NULL;//BlitD24S8PKO;
			m_blitFuncs[0][0][1] = NULL;//BlitD24S32A;
			m_blitFuncs[0][1][1] = NULL;//BlitD24S32A;
			m_blitFuncs[1][0][1] = NULL;//BlitD24S32AO;
			m_blitFuncs[1][1][1] = NULL;//BlitD24S32AO;
			m_blitFuncs[0][0][2] = NULL;//BlitD24S24;
			m_blitFuncs[0][1][2] = NULL;//BlitD24S24K;
			m_blitFuncs[1][0][2] = NULL;//BlitD24S24O;
			m_blitFuncs[1][1][2] = NULL;//BlitD24S24KO;
		}
	}
	
	inline static unsigned int ToNativeColorS(int r, int g, int b) {
		if(bpp == 24)
		{
			return (r << 16) | (g << 8) | b;
		}
		else if(bpp == 16)
		{
			return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
		}
		else if(bpp == 12)
		{
			return ((r >> 4) << 8) | ((g >> 4) << 4) | (b >> 4);
		}
		else
		{
			//not implemented
			ASSERT(false);
			return 0;
		}
	}

	inline static unsigned int ToNativeColorS(unsigned int argb) {
		if(bpp == 24)
			return argb;
		else if(bpp == 16)
		{
			unsigned int fr = (argb >> 8) & 0xF800;
			unsigned int fg = (argb >> 5) & 0x7E0;
			unsigned int fb = (argb >> 3) & 0x1F;
			return fr | fg | fb;
		}
		else if(bpp == 12)
		{
			unsigned int fr = (argb >> 12) & 0xF00;
			unsigned int fg = (argb >> 8) & 0xF0;
			unsigned int fb = (argb >> 4) & 0xF;
			return fr | fg | fb;
		}
		else
		{
			ASSERT(false);
			return 0;
		}
	}

	virtual unsigned int ToNativeColor(unsigned int rgb) {
		return ToNativeColorS(rgb);
	}

	inline static unsigned int ToRGB24ColorS(unsigned int color) {
		unsigned int r, g, b;
		if(bpp == 24)
		{
			return color;
		}
		else if(bpp == 16)
		{
			r = (color & 0xF800) << 8;
			g = (color & 0x7E0) << 5;
			b = (color & 0x1F) << 3;
		}
		else if(bpp == 12)
		{
			r = (color & 0xF00) << 12;
			g = (color & 0xF0) << 8;
			b = (color & 0xF) << 4;
		}
		else
		{
			//not implemented
			ASSERT(false);
			r = g = b = 0;
		}
		return r | g | b;
	}
	

	virtual unsigned int ToRGB24Color(unsigned int color) {
		return ToRGB24ColorS(color);
	}

	virtual void SetPixel(int x, int y, unsigned int nativeColor) {
		SetPixel_NoTranslat(ToRawX(x), ToRawY(y), nativeColor);
	}
	
	virtual void DrawRegion_NoClip_NoTranslat(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, unsigned int palette,/*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent);

	virtual void FillRect(int x, int y, int width, int height) {
		x = ToRawX(x);
		y = ToRawY(y);

		if(x < m_clipRect[0])
		{
			width -= m_clipRect[0] - x;
			x = m_clipRect[0];
		}
		if (width <= 0)
			return;
		//if(x < m_clipRect[0])
		//	x = m_clipRect[0];
		if(x + width > m_clipRect[2])
			width = m_clipRect[2] - x;
		if(width <= 0)
			return;
		if(y < m_clipRect[1])
		{
			height -= m_clipRect[1] - y;
			y = m_clipRect[1];
		}
		if (height <= 0)
			return;
//		if(y < m_clipRect[1])
//			y = m_clipRect[1];
		if(y + height > m_clipRect[3])
			height = m_clipRect[3] - y;
		if(height <= 0)
			return;
		if(bpp == 12)
		{
			if((m_color >> 24) == 0xff)
			{
				FillRect16(GetPixelPointer(x, y), width, height, m_image->GetPitch(), ToNativeColorS(m_color));
			}
			else
			{
				ASSERT(0);// FillRectARGB12(GetPixelPointer(x, y), width, height, m_image->GetPitch(), m_color);
			}
		}
		else if(bpp == 16)
		{
			if((m_color >> 24) == 0xff)
			{
				FillRect16(GetPixelPointer(x, y), width, height, m_image->GetPitch(), ToNativeColorS(m_color));
			}
			else
			{
#ifdef ENABLE_ALPHA				
				FillRectARGB16(GetPixelPointer(x, y), width, height, m_image->GetPitch(), ToNativeColorS(m_color), (m_color >> 24));
#else
				ASSERT(0);// FillRectARGB16(GetPixelPointer(x, y), width, height, m_image->GetPitch(), m_color);
#endif
			}
		}
		else if(bpp == 24)
		{
			if((m_color >> 24) == 0xff)
			{
				FillRect24(GetPixelPointer(x, y), width, height, m_image->GetPitch(), ToNativeColorS(m_color));
			}
			else
			{
				ASSERT(0);//FillRectARGB24(GetPixelPointer(x, y), width, height, m_image->GetPitch(), m_color);
			}
		}
		else
			ASSERT(false);
	}
//	void FillRectSemitransparent(int x, int y, int width, int height){
//		int i,j;
//		for (i = 0;i<height;i++)
//		{
//			for (j = 0; j<width;j++)
//			{
//				if((((i % 2)== 0)&&((j % 2)== 0))||(((i % 2)!= 0)&&((j % 2)!= 0)))
//					DrawLine(x+j,y+i,(x+j),y+i);
//			}
//		}
//	}

	virtual void DrawLine_NoClip_NoTranslat(int x0, int y0, int x1, int y1) {
		ASSERT(x0 >= m_clipRect[0] && x0 < m_clipRect[2]);
		ASSERT(x1 >= m_clipRect[0] && x1 < m_clipRect[2]);
		ASSERT(y0 >= m_clipRect[1] && y0 < m_clipRect[3]);
		ASSERT(y1 >= m_clipRect[1] && y1 < m_clipRect[3]);
		if(bpp > 8 && bpp <= 16)
		{
			if((m_color >> 24) == 0xff)
				DrawLine16((unsigned short*)GetPixelPointer(x0, y0), x1 - x0, y1 - y0, m_image->GetPitch(), ToNativeColorS(m_color));
			else
#ifdef ENABLE_ALPHA
				DrawLineARGB16((unsigned short*)GetPixelPointer(x0, y0), x1 - x0, y1 - y0, m_image->GetPitch(), ToNativeColorS(m_color), (m_color >> 24));
#else
				ASSERT(false);
#endif
		}
		else if(bpp == 24)
		{
			if((m_color >> 24) == 0xff)
				DrawLine24((unsigned int*)GetPixelPointer(x0, y0), x1 - x0, y1 - y0, m_image->GetPitch(), ToNativeColorS(m_color));
			else
				ASSERT(false); //not implemented yet
		}
		else
			ASSERT(false); ////not implemented yet
	}

//	virtual void DrawCircle(int x, int y, int r)
//	{
//		ASSERT(r >= 0);
//		ASSERT((m_color >> 24) == 0xff);
//		x = ToRawX(x);
//		y = ToRawY(y);
//		unsigned int nativeColor = ToNativeColorS(m_color);
//		int xx,yy,x1,x2,x3,x4,x5,x6,x7,x8,y1,y2,y3,y4,y5,y6,y7,y8,pk;
//		xx = 0;	yy = r;
//		x1 = x; y1 = y + r;
//		x2 = x; y2 = y + r;
//		x3 = x; y3 = y - r;
//		x4 = x; y4 = y - r;
//		x5 = x + r; y5 = y;
//		x6 = x - r; y6 = y;
//		x7 = x + r; y7 = y;
//		x8 = x - r; y8 = y;
//		pk = 1 - r;
//		while(xx <= yy)
//		{
//			SetPixel_NoTranslat(x1, y1, nativeColor);
//			SetPixel_NoTranslat(x2, y2, nativeColor);
//			SetPixel_NoTranslat(x3, y3, nativeColor);
//			SetPixel_NoTranslat(x4, y4, nativeColor);
//			SetPixel_NoTranslat(x5, y5, nativeColor);
//			SetPixel_NoTranslat(x6, y6, nativeColor);
//			SetPixel_NoTranslat(x7, y7, nativeColor);
//			SetPixel_NoTranslat(x8, y8, nativeColor);
//			xx++;
//			x1++; x2--; x3++; x4--;
//			y5++; y6++; y7--; y8--;
//			if(pk < 0)
//				pk+= 2*xx + 1;
//			else
//			{
//				yy--;
//				y1--; y2--; y3++; y4++;
//				x5--; x6++; x7--; x8++;
//				pk += 2 * (xx - yy) + 1;
//			}
//		}
//	}

	//specially added by Lu Yan for GangStar, not precise, and must be 0 - 360 degrees
	virtual void DrawArc(int x0, int y0, int w, int h, int start, int end)
	{
		int a = (w - 0) / 2;
		int b = (h - 0) / 2;
		int x = x0 + a;
		int y = y0 + b;
#ifndef remove_ARGB
		start = 0;
		end = 360;
#else
		ASSERT(start == 0 && end == 360);
		ASSERT((m_color >> 24) == 0xff);
#endif
		ASSERT(a >= 0 && b >= 0);
		x = ToRawX(x);
		y = ToRawY(y);
//#ifndef remove_ARGB
		unsigned int nativeColor;
//		if ((m_color >> 24) == 0xff)
//		nativeColor = ToNativeColorS(m_color);
//		else
		nativeColor = m_color;
//#else
//		unsigned int nativeColor = ToNativeColorS(m_color);
//#endif
		int xx,yy,x1,x2,x3,x4,x5,x6,x7,x8,y1,y2,y3,y4,y5,y6,y7,y8,pk;
		int t1 = 0, t2 = 0, t3 = 0;

		int r = a >= b ? a : b;
		xx = 0;	yy = r;
		x1 = x; y1 = y + b;
		x2 = x; y2 = y + b;
		x3 = x; y3 = y - b;
		x4 = x; y4 = y - b;
		x5 = x + a; y5 = y;
		x6 = x - a; y6 = y;
		x7 = x + a; y7 = y;
		x8 = x - a; y8 = y;
		pk = 1 - r;
		if (a >= b)
		{
			t1 = b / 3;
			t2 = b / 3;
			t3 = 2 * (xx - yy) + 1;
			while(xx <= yy)
			{
				SetPixel_NoTranslat(x1, y1, nativeColor);
				SetPixel_NoTranslat(x2, y2, nativeColor);
				SetPixel_NoTranslat(x3, y3, nativeColor);
				SetPixel_NoTranslat(x4, y4, nativeColor);
				SetPixel_NoTranslat(x5, y5, nativeColor);
				SetPixel_NoTranslat(x6, y6, nativeColor);
				SetPixel_NoTranslat(x7, y7, nativeColor);
				SetPixel_NoTranslat(x8, y8, nativeColor);
				xx++;
				x1++; x2--; x3++; x4--;
				if ((t1 += b) >= a)
				{
					y5++; y6++; y7--; y8--;
					t1 -= a;
				}
				if(pk < 0)
					pk+= 2*xx + 1;
				else
				{
					yy--;
					if ((t2 += b) >= a)
					{
						y1--; y2--; y3++; y4++;
						t2 -= a;
					}
					x5--; x6++; x7--; x8++;
					pk += 2 * (xx - yy) + 1;
				}
			}
		}
		else
		{
			t1 = a / 3;
			t2 = a / 3;
			while(xx <= yy)
			{
				SetPixel_NoTranslat(x1, y1, nativeColor);
				SetPixel_NoTranslat(x2, y2, nativeColor);
				SetPixel_NoTranslat(x3, y3, nativeColor);
				SetPixel_NoTranslat(x4, y4, nativeColor);
				SetPixel_NoTranslat(x5, y5, nativeColor);
				SetPixel_NoTranslat(x6, y6, nativeColor);
				SetPixel_NoTranslat(x7, y7, nativeColor);
				SetPixel_NoTranslat(x8, y8, nativeColor);
				xx++;
				if ((t1 += a) >= b)
				{
					x1++; x2--; x3++; x4--;
					t1 -= b;
				}
				y5++; y6++; y7--; y8--;
				if(pk < 0)
					pk+= 2*xx + 1;
				else
				{
					yy--;
					y1--; y2--; y3++; y4++;
					if ((t2 += a) >= b)
					{
						x5--; x6++; x7--; x8++;
						t2 -= b;
					}
					pk += 2 * (xx - yy) + 1;
				}
			}
		}
	}

	//specially added by Lu Yan for GangStar, not precise, and must be 0 - 360 degrees
	virtual void FillArc(int x0, int y0, int w, int h, int start, int end)
	{
		int a = (w - 0) / 2;
		int b = (h - 0) / 2;
		int x = x0 + a;
		int y = y0 + b;
#ifndef remove_ARGB
		start = 0;
		end = 360;
#else
		ASSERT(start == 0 && end == 360);
		ASSERT((m_color >> 24) == 0xff);
#endif
		ASSERT(a >= 0 && b >= 0);
		x = ToRawX(x);
		y = ToRawY(y);
//#ifndef remove_ARGB
		unsigned int nativeColor;
		//if ((m_color >> 24) == 0xff)
		//nativeColor = ToNativeColorS(m_color);
		//else
		nativeColor = m_color;
//#else
//		unsigned int nativeColor = ToNativeColorS(m_color);
//#endif
		int xx,yy,x1,x2,x3,x4,x5,x6,x7,x8,y1,y2,y3,y4,y5,y6,y7,y8,pk;
		int t1 = 0, t2 = 0, t3 = 0;

		int r = a >= b ? a : b;
		xx = 0;	yy = r;
		x1 = x; y1 = y + b;
		x2 = x; y2 = y + b;
		x3 = x; y3 = y - b;
		x4 = x; y4 = y - b;
		x5 = x + a; y5 = y;
		x6 = x - a; y6 = y;
		x7 = x + a; y7 = y;
		x8 = x - a; y8 = y;
		pk = 1 - r;
		if (a >= b)
		{
			t1 = b / 3;
			t2 = b / 3;
			t3 = 2 * (xx - yy) + 1;
			while(xx <= yy)
			{
				DrawHLine_NoTranslat(x2, y1, x1, nativeColor);
				if ( y3 != y1 )//ADD BY ZF
				DrawHLine_NoTranslat(x4, y3, x3, nativeColor);
				if ( y5 != y3 && y5 != y1 )//ADD BY ZF
				DrawHLine_NoTranslat(x6, y5, x5, nativeColor);
				if ( y7 != y5 && y7 != y3 && y7 != y1 )
				DrawHLine_NoTranslat(x8, y7, x7, nativeColor);
				if (xx == yy)
					break;
				xx++;
				x1++; x2--; x3++; x4--;
				if ((t1 += b) >= a)
				{
					y5++; y6++; y7--; y8--;
					t1 -= a;
				}
				if(pk < 0)
					pk+= 2*xx + 1;
				else
				{
					yy--;
					if ((t2 += b) >= a)
					{
						y1--; y2--; y3++; y4++;
						t2 -= a;
					}
					x5--; x6++; x7--; x8++;
					pk += 2 * (xx - yy) + 1;
				}
			}
//			DrawHLine_NoTranslat(x6, y5, x5, nativeColor);//removed by zf
//			DrawHLine_NoTranslat(x8, y7, x7, nativeColor);//removed by zf
		}
		else
		{
			t1 = a / 3;
			t2 = a / 3;
			while(xx <= yy)
			{
				DrawHLine_NoTranslat(x2, y1, x1, nativeColor);
				DrawHLine_NoTranslat(x4, y3, x3, nativeColor);
				DrawHLine_NoTranslat(x6, y5, x5, nativeColor);
				DrawHLine_NoTranslat(x8, y7, x7, nativeColor);
				xx++;
				if ((t1 += a) >= b)
				{
					x1++; x2--; x3++; x4--;
					t1 -= b;
				}
				y5++; y6++; y7--; y8--;
				if(pk < 0)
					pk+= 2*xx + 1;
				else
				{
					yy--;
					y1--; y2--; y3++; y4++;
					if ((t2 += a) >= b)
					{
						x5--; x6++; x7--; x8++;
						t2 -= b;
					}
					pk += 2 * (xx - yy) + 1;
				}
			}
		}
	}

//	virtual void FillHLineT(F12 uStart, F12 dux, F12 vStart, F12 dvx, CImage *texture, void *pStart, int x, int length, unsigned int palette)
//	{
//		if(texture->GetType() == CImage::TYPE_INDEXED)
//		{
//			ASSERT(texture->GetBitsPerPixel() == 8);
//			if(GetOpacity() == 255)
//			{
//				if(bpp > 8 && bpp <= 16)
//					FillHLineTD16S8PK(uStart, dux, vStart, dvx, texture, pStart, x, length, palette);
//				else if(bpp == 24)
//					FillHLineTD24S8PK(uStart, dux, vStart, dvx, texture, pStart, x, length, palette);
//				else	
//					ASSERT(false);
//			}
//			else
//			{
//				if(bpp == 12)
//					FillHLineTD12S8PKO(uStart, dux, vStart, dvx, texture, pStart, x, length, palette, GetOpacity());
//				else if(bpp == 16)
//					FillHLineTD16S8PKO(uStart, dux, vStart, dvx, texture, pStart, x, length, palette, GetOpacity());
//				else if(bpp == 24)
//					FillHLineTD24S8PKO(uStart, dux, vStart, dvx, texture, pStart, x, length, palette, GetOpacity());
//				else
//					ASSERT(false);
//			}
//		}
//		else if(texture->GetType() == CImage::TYPE_RGB)
//		{
//			if(GetOpacity() == 255)
//			{
//				if(bpp > 8 && bpp <= 16)
//					FillHLineTD16S32A(uStart, dux, vStart, dvx, texture, pStart, x, length);
//				else	
//					ASSERT(false);
//			}
//			else
//			{
//				if(bpp == 16)
//					FillHLineTD16S32AO(uStart, dux, vStart, dvx, texture, pStart, x, length, GetOpacity());
//				else
//					ASSERT(false);
//			}
//		}
//		else
//			ASSERT(false);
//	}


	virtual void EnableGrayEffect();
	virtual void EnableBlackAlphaEffect(int alpha , int nativeRgb  );

protected:
	BlitFunc m_blitFuncs[2][3][5];

	inline PT* GetPixelPointer(int x, int y) {
		return (PT*)(m_image->GetPixelData() + y * m_image->GetPitch()) + x;
	}

	void SetPixel_NoTranslat(int x, int y, int nativeColor) {
		if(x < m_clipRect[0] || x >= m_clipRect[2] || y < m_clipRect[1] || y >= m_clipRect[3])
			return;
#ifndef remove_ARGB
		if ((nativeColor>>24)!=0xFF)
		{
			const unsigned int alpha = ((nativeColor&0xFF000000)>>24);
			unsigned int color = ToNativeColorS(nativeColor);
			const unsigned int rMask = 0xF800;
			const unsigned int gMask = 0x7E0;
			const unsigned int bMask = 0x1f;
			const unsigned int fr = (rMask & color) * alpha / 256;
			const unsigned int fg = (gMask & color) * alpha / 256;
			const unsigned int fb = (bMask & color) * alpha / 256;
			const unsigned int a = 256 - alpha;
			
			unsigned int c = GetPixelPointer(x, y)[0];
			int r = fr + (c & rMask) * a / 256;
			int g = fg + (c & gMask) * a / 256;
			int b = fb + (c & bMask) * a / 256;
			
			GetPixelPointer(x, y)[0] =  (unsigned short)((r & rMask) | (g & gMask) | (b & bMask)); // set the pixel
		}
			else
#endif
		GetPixelPointer(x, y)[0] = nativeColor;
	}

	void DrawHLine_NoTranslat(int x1, int y1, int x2, int nativeColor){
		//ASSERT(x1 <= x2);
		if (x1 > x2)
			x1 ^= x2 ^= x1 ^= x2;	//switch x1 and x2
		if(x2 < m_clipRect[0] || x1 >= m_clipRect[2] || y1 < m_clipRect[1] || y1 >= m_clipRect[3])
			return;
		if (x1 < m_clipRect[0])
			x1 = m_clipRect[0];
		if (x2 >= m_clipRect[2])
			x2 = m_clipRect[2] - 1;
		PT *p = GetPixelPointer(x1, y1);
		for (; x1 <= x2; ++x1)
		{
#ifndef remove_ARGB
			if ((nativeColor>>24)!=0xFF)
			{
				const unsigned int alpha = ((nativeColor&0xFF000000)>>24);
				unsigned int color = ToNativeColorS(nativeColor);
				const unsigned int rMask = 0xF800;
				const unsigned int gMask = 0x7E0;
				const unsigned int bMask = 0x1f;
				const unsigned int fr = (rMask & color) * alpha / 256;
				const unsigned int fg = (gMask & color) * alpha / 256;
				const unsigned int fb = (bMask & color) * alpha / 256;
				const unsigned int a = 256 - alpha;
				
				unsigned int c = GetPixelPointer(x1, y1)[0];
				int r = fr + (c & rMask) * a / 256;
				int g = fg + (c & gMask) * a / 256;
				int b = fb + (c & bMask) * a / 256;
				
				*p++ = (unsigned short)((r & rMask) | (g & gMask) | (b & bMask)); // set the pixel
			}
				else
#endif
			*p++ = nativeColor;
		}
	}

	void DrawVLine_NoTranslat(int x1, int y1, int y2, int nativeColor){
		//ASSERT(y1 <= y2);
		if (y1 > y2)
			y1 ^= y2 ^= y1 ^= y2;	//switch y1 and y2
		if(x1 < m_clipRect[0] || x1 >= m_clipRect[2] || y2 < m_clipRect[1] || y1 >= m_clipRect[3])
			return;
		if (y1 < m_clipRect[1])
			y1 = m_clipRect[1];
		if (y2 >= m_clipRect[3])
			y2 = m_clipRect[3] - 1;
		int dy = m_image->GetPitch() - sizeof(PT);
		PT *p = GetPixelPointer(x1, y1);
		for (; y1 <= y2; ++y1)
		{
			*p = nativeColor;
			p = (PT*)((char*)p + dy);
		}
	}

};

template <typename PT, int bpp>
void CGraphicsT<PT, bpp>::DrawRegion_NoClip_NoTranslat(CImage *pSrc, int x_src, int y_src, int width, int height, int transform,
		int x_dest, int y_dest, unsigned int palette, /*Blend*/ unsigned char Blend_Kind, unsigned  int Blend_Percent)// SangHo - Blend - 
{
	//pSrc - 원본 모듈 이미지 포인터
	//x_src - x 는 영역의 왼쪽 상단 구석의 원본 이미지 내에서의 좌표. 일반적으로 0
	//y_src - y 는 영역의 왼쪽 상단 구석의 원본 이미지 내에서의 좌표. 일반적으로 0
	//width - 영역의 너비 
	//height - 영역의 높이 
	//transform - 변환을 원하는 선택한 지역에 대한 복사 
	//x_dest - 그릴 위치 
	//y_dest - 그릴 위치
	//palette - 팔레트 항목의 원본에있는 이미지를 교대로 번호
	ASSERT(pSrc != NULL);
	ASSERT(x_src >= 0);
	ASSERT(x_src + width <= pSrc->GetWidth());//SangHo - 이미지 좌표를 벗어난 곳을 시작점으로 잡지않았는가
	ASSERT(y_src >= 0);
	ASSERT(y_src + height <= pSrc->GetHeight());
	BlitParam par;
	
	int dstXPitch = m_image->GetPitch();
	switch(transform)
	{
	case TRANS_NONE:
		par.dstXPitch = sizeof(PT);
		par.dstYPitch = dstXPitch;
		break;
	case TRANS_MIRROR_ROT180:
		y_dest += height - 1;
		par.dstXPitch = sizeof(PT);
		par.dstYPitch = -dstXPitch;
		break;
	case TRANS_MIRROR:
		x_dest += width - 1;
		par.dstXPitch = -(int)sizeof(PT);
		par.dstYPitch = dstXPitch;
		break;
	case TRANS_ROT180:
		x_dest += width - 1;
		y_dest += height - 1;
		par.dstXPitch = -(int)sizeof(PT);
		par.dstYPitch = -dstXPitch;
		break;
	case TRANS_MIRROR_ROT270:
		par.dstXPitch = dstXPitch;
		par.dstYPitch = sizeof(PT);
		break;
	case TRANS_ROT90:
		x_dest += height - 1;
		par.dstXPitch = dstXPitch;
		par.dstYPitch = -(int)sizeof(PT);
		break;
	case TRANS_ROT270:
		y_dest += width - 1;
		par.dstXPitch = -dstXPitch;
		par.dstYPitch = sizeof(PT);
		break;
	case TRANS_MIRROR_ROT90:
		x_dest += height - 1;
		y_dest += width - 1;
		par.dstXPitch = -dstXPitch;
		par.dstYPitch = -(int)sizeof(PT);
		break;
	default:
		ASSERT(false);
	}
	
	par.srcYPitch = pSrc->GetPitch();
	par.width = width;
	par.height = height;
	par.bChannel = GetChannel();
//	par.x_dest = x_dest;
//	par.y_dest = y_dest;
//	par.bgbuff = m_buffPixel ; //g_pGame->backbuffpix;
	par.p_color = m_color;
	int id3;
	int opacity = m_color >> 24;
	
	if(opacity == 255)
		id3 = 0;
	else
	{
		par.opacity = opacity;
		id3 = 1;
	}

	BlitFunc *curBlitFunc;
	if (pSrc->GetFlag() & BBM_ALPHA)
	{
		curBlitFunc = m_blitFuncs[id3][2];
	}
	else if(pSrc->GetFlag() & BBM_COLOR_KEY)
	{
		curBlitFunc = m_blitFuncs[id3][1];
		par.colorKey = pSrc->GetColorKey();
	}
	else
	{
		curBlitFunc = m_blitFuncs[id3][0];
	}
	
	if(pSrc->GetType() == CImage::TYPE_INDEXED)
	{
		CIndexedImage *image = DYNAMIC_CAST(CIndexedImage*, pSrc);
		
		ASSERT(palette < image->GetPaletteEntryNumber());
		par.palette = image->GetPaletteData() + palette;
		
		//par.palBits = image->GetPalBits();
		//par.palMask = image->GetPalMasks();
		
		//par.srcSkip = image->GetPitch() * y_src + x_src;

		//BlitFunc blitFunc = curBlitFunc[0];
		//ASSERT(blitFunc != NULL);
		//(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData() + image->GetPitch() * y_src + x_src, &par);
	
	
		BlitFunc blitFunc = NULL;
		unsigned char *src = image->GetPixelData();
		switch (image->GetBitsPerPixel())
		{
		case 8:
			blitFunc = curBlitFunc[0];
			src += image->GetPitch() * y_src + x_src;
			break;
		case 4:
			blitFunc = curBlitFunc[4];
			src += (image->GetPitch() * y_src + x_src) >> 1;
			par.srcSkip = (image->GetPitch() * y_src + x_src) & 1;
			break;
		default:
			ASSERT(false);
			return;
		}
		ASSERT(blitFunc != NULL);
		(*blitFunc)(GetPixelPointer(x_dest, y_dest), src, &par,/*Blend*/Blend_Kind, Blend_Percent);
	
	}
	else if(pSrc->GetType() == CImage::TYPE_RGB || pSrc->GetType() == CImage::TYPE_MUTABLE)
	{
		CRgbImage *image = DYNAMIC_CAST(CRgbImage*, pSrc);
		if(image->GetBitsPerPixel() == 32)
		{
			BlitFunc blitFunc = curBlitFunc[1];
			ASSERT(blitFunc != NULL);
			(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData() + image->GetPitch() * y_src + x_src * 4, &par,/*Blend*/Blend_Kind, Blend_Percent);
		}
		else if(image->GetBitsPerPixel() == bpp)
		{
			BlitFunc blitFunc = curBlitFunc[2];
			ASSERT(blitFunc != NULL);
			if(bpp > 8 && bpp <= 16)//SangHo - 픽셀당 2바이트 인가
				(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData() + image->GetPitch() * y_src + x_src * 2, &par,/*Blend*/Blend_Kind, Blend_Percent);
			//GetPixelPointer(x_dest, y_dest)그릴대상의 좌표에 이미지 정보를 얻어옴
			else if(bpp == 24)//SangHo - 픽셀당 3바이트 인가
				(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData() + image->GetPitch() * y_src + x_src * 2, &par,/*Blend*/Blend_Kind, Blend_Percent);
			else
				ASSERT(false);
		}
		else
			ASSERT(false);
	}
	else if(pSrc->GetType() == CImage::TYPE_RLE)
	{//SangHo - RLE압축포맷을 사용할때 진입
		CRleImage *image = DYNAMIC_CAST(CRleImage*, pSrc);

		ASSERT(palette < image->GetPaletteEntryNumber());
		par.palette = image->GetPaletteData() + palette;
		par.palMask = image->GetPalMask();
		par.palBits = image->GetPalBits();
		if (x_src == 0 && y_src == 0 && width == image->GetWidth() && height == image->GetHeight())
			par.srcSkip = -1;
		else
			par.srcSkip = image->GetPitch() * y_src + x_src;
		BlitFunc blitFunc = curBlitFunc[3];
		ASSERT(blitFunc != NULL);
		if(pSrc->GetFlag() & BBM_NIGHTALPHA)
		{	
			if(GetChannel() & CHANNEL_NIGHT)
			{			
				BlitD16SI64RLEAOL(GetPixelPointer(x_dest, y_dest), image->GetPixelData(), &par , (m_buffPixel + y_dest*(m_image->GetPitch()>>1) ) + x_dest);
			}
		}
		else 
		{
			if(GetChannel() & CHANNEL_COLORALPHA)
			{
				BlitD16SRLEKOC(GetPixelPointer(x_dest, y_dest), image->GetPixelData(), &par,/*Blend*/Blend_Kind, Blend_Percent);
			}
			else if( GetChannel() & CHANNEL_GRAY)
			{
				BlitD16SRLEKG(GetPixelPointer(x_dest, y_dest), image->GetPixelData(), &par,/*Blend*/Blend_Kind, Blend_Percent);
			}
			else
			{		
				
				//(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData(), &par);
				// SangHo - Blend - 블랜딩 구현을 위해서 인자 2개 추가
				(*blitFunc)(GetPixelPointer(x_dest, y_dest), image->GetPixelData(), &par,/*Blend*/Blend_Kind, Blend_Percent);
			}
		}
	}
#ifdef ENABLE_ZDS
	else if(pSrc->GetType() == CImage::TYPE_ZDS)
	{
		CZDS *image = DYNAMIC_CAST(CZDS*, pSrc);

		BlitD16SZDS(GetPixelPointer(x_dest, y_dest), 
					image->GetPixelData() + image->GetPitch() * y_src + x_src * 2, 
					image->GetAlphaData() + image->GetWidth() * y_src + x_src,
					&par,
					image->GetRenderState());
	}
#endif
	else
		ASSERT(false);
}


template <typename PT, int bpp>
void CGraphicsT<PT, bpp>::EnableGrayEffect()
{
	const int x = m_clipRect[0];
	const int y = m_clipRect[1];
	const int w = m_clipRect[2];
	const int h = m_clipRect[3];

	const int s_space = m_image->GetPitch() / 2 - w;

	unsigned short *d = (unsigned short*)GetPixelPointer(x, y);

#if NATIVE_COLOR_DEPTH == 12	
	for(int i = y ; i < y + h; i++)
	{	
		unsigned short *e = d + w;
		
		while(d < e)
		{
			int	nR = (*d & 0xF00) >> 8;
			int	nG = (*d & 0xF0) >> 4;
			int	nB = (*d & 0xF);
			
			int nGray = ((nR * 5) + (nG * 9) + (nB << 1)) >> 4;//0.299*R+0.587*G+0.114*B
			
			if(nGray > 15)
				nGray = 15;
			
			*d++ = (nGray << 8) | (nGray << 4) | nGray;
		}
		
		d += s_space;
	}
#elif NATIVE_COLOR_DEPTH == 16	
	for(int i = y ; i < y + h; i++)
	{	
		unsigned short *e = d + w;
	
		while(d < e)
		{
			int	nR = (*d & 0xF000) >> 12;
			int	nG = (*d & 0x0780) >> 7;
			int	nB = (*d & 0x001E) >> 1;
			
			int nGray = ((nR * 5) + (nG * 9) + (nB << 1)) >> 4;//0.299*R+0.587*G+0.114*B

			if(nGray > 15)
				nGray = 15;

			*d++ = (nGray << 12) | (nGray << 7) | (nGray << 1);
		}
		
		d += s_space;
	}
#endif
}


template <typename PT, int bpp>
void CGraphicsT<PT, bpp>::EnableBlackAlphaEffect(int alpha , int nativeRgb  )
{
	
	ASSERT(alpha < 0xFF);

	const int x = m_clipRect[0];
	const int y = m_clipRect[1];
	const int w = m_clipRect[2];
	const int h = m_clipRect[3];

	const int s_space = m_image->GetPitch() / 2 - w;

	unsigned short *d = (unsigned short*)GetPixelPointer(x, y);

	unsigned char *b = (unsigned char*) (m_buffPixel + y * (m_image->GetPitch()>>1) ) + x;

	const unsigned int fclr = nativeRgb;
	
	const int bx = 1;

#if NATIVE_COLOR_DEPTH == 16	

	const unsigned int rMask = 0xF800;
	const unsigned int gMask = 0x7E0;
	const unsigned int bMask = 0x1f;

	const unsigned int a = 256 - alpha;
	
	for(int i = y ; i < y + h; i++)
	//while(h != 0)
	{	
		unsigned short *e = d + w;

		while(d < e)
		{	
			unsigned int ba = *b; 
			const unsigned int aa = (256 - ba);

			int ar =  ((*d & rMask) * (aa)) >>8; //256;
			int ag =  ((*d & gMask) * (aa)) >>8; ///256;
			int ab =  ((*d & bMask) * (aa)) >>8; ///256;			
			
			*d++ = (unsigned short) ((ar & rMask) | (ag & gMask) | (ab & bMask));
			*b++;
			
			//b = (unsigned char*)((unsigned char*)b + bx);
		}

		d += s_space;	
		b += s_space;
	}


	//const unsigned int rMask = 0xF800;
	//const unsigned int gMask = 0x7E0;
	//const unsigned int bMask = 0x1f;
	//const unsigned int fr = (rMask & fclr) * alpha / 256;
	//const unsigned int fg = (gMask & fclr) * alpha / 256;
	//const unsigned int fb = (bMask & fclr) * alpha / 256;
	//const unsigned int a = 256 - alpha;

	//for(int i = y ; i < y + h; i++)
	//	//while(h != 0)
	//{	
	//	unsigned short *e = d + w;

	//	while(d < e)
	//	{		
	//		int r = fr + (*d & rMask) * a / 256;
	//		int g = fg + (*d & gMask) * a / 256;
	//		int b = fb + (*d & bMask) * a / 256;			

	//		*d++ = (unsigned short) ((r & rMask) | (g & gMask) | (b & bMask));
	//	}

	//	d += s_space;		
	//}
#else
	ASSERT(false);
#endif
}


#if NATIVE_COLOR_DEPTH == 16
typedef CGraphicsT<NativePixel, 16> CNativeGraphics;
#elif NATIVE_COLOR_DEPTH == 12
typedef CGraphicsT<NativePixel, 12> CNativeGraphics;
#elif NATIVE_COLOR_DEPTH == 24
typedef CGraphicsT<NativePixel, 24> CNativeGraphics;
#else
#error NATIVE_COLOR_DEPTH is not supported
#endif



#endif