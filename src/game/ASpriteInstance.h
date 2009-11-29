#ifndef _ASPRITE_INSTANCE_
#define _ASPRITE_INSTANCE_

#include "ASprite.h"
#include "DEF.h"

#define APPLY_X	1
//#define	APPLY_Y	2
#define	APPLY_Z	4

class ASprite;
class CGraphics;

const static bool DRAW_DEBUG_FRAMES = false;

class ASpriteInstance	
{
public:
	~ASpriteInstance();
//	ASpriteInstance*	m_parent;	
	ASprite*		m_sprite;		//SangHo - Instance 가 참조하는 B스프라이트의 포인터값

	int				m_nState;		//Namyoung - 상태변수 0:에니메이션, 1:프레임, 2:모듈

	int				m_posX;			//SangHo - 원점 X 좌표(가로)
	int				m_posY;			//SangHo - 원점 Y 좌표(세로)
	int				m_posZ;			//SangHo - 원점 Z 좌표(높이)



	int				m_stopFlag;			//SangHo - 최종적으로 발생한 프레임 플래그값을 기록한다

	int CameraX;					//SangHo - 카메라 좌표가 기록된다 , 이는 보정좌표로 쓰인다
	int CameraY;					//SangHo - 카메라 좌표가 기록된다 , 이는 보정좌표로 쓰인다

	int				m_flags;		//SangHo - 그려지는 (Ani,Frame,Module) 의 변환값 0~7 사이의 값을 가짐
	
	int				m_pal;			//SangHo - 팔레트
	
	int				m_nCrtModule;		//SangHo - Index값을 가지는 변수, -1값을 가지면 Module은 비활성화 된다
	int				m_nCrtFrame;		//SangHo - Index값을 가지는 변수, -1값을 가지면 Frame은 비활성화 된다
	int				m_nCrtAnimation;	//SangHo - Index값을 가지는 변수, -1값을 가지면 Animation은 비활성화 된다(활성화시 m_nCrtModule는 Animation 넘버를 저장하고, m_nCrtFrame은 현재 인덱스를 임시 저장한다)

	int* 			m_rect;			//SangHo -  (Ani,Frame,Module)의 좌,상,너비,높이 값을 리턴하는 4배열
	
	bool			m_bLoop;		//SangHo - AniDraw 경우 루프여부를 지정
	bool			b_MoveLock;		//SangHo - 애니메이션이 종료후 원점 좌표에 반영 하는 여부를 지정
	//int				m_layer;					//SangHo - 주타이쿤에서 쓰기 위해 만들어진 레이어 개념(비 인마수의계약트 변수)
	int				m_savedLayer/* = -1*/;		//SangHo - 주타이쿤에서 쓰기 위해 만들어진 레이어 개념(비 인마수의계약트 변수)

	int				m_lastX;			//SangHo - X 몸통 충돌체크를 위해서 지난 X좌표를 기록
	int				m_lastY;			//SangHo - X 몸통 충돌체크를 위해서 지난 Y좌표를 기록

private:
	int				m_lastAniX;			//SangHo - Animation의 이전 좌표 - 현재 프레임의 포지션에 빼주기 위해서 존재
	int				m_lastAniZ;			//SangHo - Animation의 이전 좌표 - 현재 프레임의 포지션에 빼주기 위해서 존재
public:


	bool is_aniDone/* = false*/;	

	struct Blend{
		bool blendCustom;	
		bool overWrite;		
		short Blend_Kind;	
		short Blend_Percent;
	};Blend s_Blend;

	ASpriteInstance()	
	{	
		m_savedLayer = -1;
		//m_bUpdateRect = true;
		is_aniDone = false;

		s_Blend.blendCustom = false;
		s_Blend.overWrite = false;		
		s_Blend.Blend_Kind = 0;	
		s_Blend.Blend_Percent = 0;
	}	

	ASpriteInstance(const ASpriteInstance* rhs)	
	{	
		m_rect = GL_NEW int[4];

		m_sprite = rhs->m_sprite;
		m_posX = rhs->m_posX;
		m_posY = rhs->m_posY;
		m_posZ = rhs->m_posZ;
		m_lastAniX = rhs->m_lastAniX;
		m_lastAniZ = rhs->m_lastAniZ;
		m_stopFlag = rhs->m_stopFlag;
		m_flags = rhs->m_flags;
		m_pal = rhs->m_pal;
		m_nCrtModule = rhs->m_nCrtModule;
		m_nCrtFrame = rhs->m_nCrtFrame;
		m_nCrtAnimation = rhs->m_nCrtAnimation;
		MEMCPY(m_rect, rhs->m_rect, 4*4);
		m_bLoop = rhs->m_bLoop;
		//m_layer = rhs->m_layer;
		m_savedLayer = rhs->m_savedLayer;
		is_aniDone = rhs->is_aniDone;
	}
	
	ASpriteInstance(ASprite* spr, int posX, int posY, ASpriteInstance* parent);	

	void SetModule(int id);	//SangHo - 그리기 속성을 Module로 바꿔준다	

	void SetFrame(int id);	//SangHo - 그리기 속성을 Frame로 바꿔준다
	
	bool SetAnim(int id);	//SangHo - 그리기 속성을 Animation로 바꿔준다
	
	void SetAniLoop(bool _loop){m_bLoop = _loop;}			//SangHo - int id, bool _loop); //SangHo - Animation 에 한하여 루프여부를 지정한다
	void SetAniMoveLock(bool _Lock){b_MoveLock = _Lock;}	//SangHo - 애니메이션이 종료후 원점 좌표에 반영 하는 여부를 지정

	void RewindAnim(int id);	//SangHo - id Anim 으로 교체후 초기화
	
	void SetToLastFrame();	//SangHo - 	Anim의 마지막 인덱스값으로 이동

	void setAnimStop( );	//SangHo - 	Anim을 재생중단후 인덱스 초기화

	void setCamera(int _CameraX, int _CameraY);	//SangHo - 	Anim을 재생중단후 인덱스 초기화
	
	bool IsAnimEnded();	//SangHo - 	Anim가 현재 재생중인지 아닌지를 알려준다
	

	void Get_AFrameXZ(int* tmpXZ);//그리기 전에 좌표확인이 필요할때
	void PaintSprite(CGraphics* g);	//SangHo - PaintSprite 오버 로드
	void PaintSprite(CGraphics* g,int posX,int posY,int flags);	//SangHo - PaintSprite 오버 로드
	void PaintSprite(CGraphics* g,int flags);	//SangHo - flags값에 따라 좌우상하반전 또는 90도 회전을 지원한다(m_flags 참고)
		
	bool UpdateSpriteAnim();	//SangHo - Animation의 현재값을 1증가시킨다.

	int GetCurrentAFrameOff(bool bY);	//SangHo - 현재 Off값 구하는 부분이긴하나 활용예상부분을 모르겠음
	
	int GetLastAFrameOff(bool bY);	//SangHo - 마지막 Off값 구하는 부분이긴하나 활용예상부분을 모르겠음	
	
	int* GetRect(bool bColRect);//SangHo - LCD기준의 좌,상,너비,높이 4개인자값을 리턴한다.	
	
	int* GetAbsoluteRect(bool bColRect);//SangHo - 원점기준의 좌,상,너비,높이 4개인자값을 리턴한다.	
	
	int* GetFModuleRect(int module,int posX, int posY, int flags, int hx, int hy);	//SangHo - 현재 인마수의계약스가 그리고있는 Animation Frame 의 module번째 모듈의 좌표를 리턴한다(원점기준, 하이퍼 프레임은 해당되지않음)
		
	int GetAnimFrame();	//SangHo - 현재 인마수의계약스가 그리고있는 Animation Frame 의 고유ID값을 리턴한다
	
	bool IsRectCrossing(int* rect1, int* rect2);	//SangHo - 두 면적이 충돌하였는지를 판단한다
	
	bool IsPointInRect(int x, int y, int* rect);	//SangHo - 한지점이 면적 안에 들어가있는지 아닌지를 체크한다

	bool SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent);	//SangHo - 한지점이 면적 안에 들어가있는지 아닌지를 체크한다
	
	

};

///////////////////////////////////////////▽폐소스 - SangHo/////////////////////////////////////////
///////////////////////////////////////////▽폐소스 - SangHo/////////////////////////////////////////
/*
	bool			m_bReverse;		//쓰이지 않음
	bool			m_bAnimIsOver;	//SangHo - 불필요한 함수	
	int*			m_boundingRect;	//SangHo - 쓰이지 않음
	bool			m_bUpdateRect;	//SangHo - 쓰이지 않음
	int _vis;	//SangHo - 사용하지 않음	 
	void PaintSprite_NO_ZOOM(CGraphics* g);	//SangHo - PaintSprite로 대체
	int* GetSpriteRect(int _m_posX, int _m_posY);//SangHo - _m_posX,_m_posY 을 기준점으로 가정된 좌,상,너비,높이 4개인자값을 리턴한다.
	void ApplyAnimOff();
	static int ZOOM_IN_FIXED_X(int x)
	{
	return (x >> FIXED_PRECISION);
	}

	static int ZOOM_IN_FIXED_Y(int y)
	{
	return (y >> FIXED_PRECISION);
	}

	void OnScreenTest();	//SangHo - 사용하지 않음	

	bool	IsOnScreen(int style);	//SangHo - 사용하지 않음	

	int getAniFrameOffY();	//쓰이지 않음
*/
	

#endif //_ASPRITE_INSTANCE_


	
