#include "ASpriteInstance.h"
#include "ASprite.h"

/*int ASpriteInstance::x;
int ASpriteInstance::y;
int ASpriteInstance::_posX;
int ASpriteInstance::_posY;*/

#include "Macro.h"
	ASpriteInstance::ASpriteInstance(ASprite* spr, int posX, int posY, ASpriteInstance* parent)
	{
		CameraX=0;
		CameraY=0;

		m_lastX = m_posX = posX;
		m_lastY = m_posY = posY;
		

		//	m_flags = 0;
		m_pal		= 0;
		m_sprite		= spr;

		m_nState = 0;
		m_nCrtModule	= 0;
		m_nCrtFrame	= 0;
		m_nCrtAnimation	= 0;
		m_rect		= GL_NEW int[4];
		m_bLoop		= true;

//		m_parent = parent;
	}

	ASpriteInstance::~ASpriteInstance()
	{
		SAFE_DEL_ARRAY(m_rect);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ASpriteInstance::SetModule(int id)
	{//SangHo - 그리기 속성을 Module로 바꿔준다
		//행동이 바뀌면 기존의 마지막 좌표는 초기화 시켜준다
		m_lastAniX=0; 
		m_lastAniZ=0;

		m_nState = 2;
		m_nCrtAnimation		= -2;//SangHo - -2 일 경우 Animation 작동하지않는다
		m_nCrtModule		= id;
		//m_nCrtFrame	= -1;//SangHo - -1 일 경우 Frame 작동하지않는다

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ASpriteInstance::SetFrame(int id)
	{//SangHo - 그리기 속성을 Frame로 바꿔준다
		//행동이 바뀌면 기존의 마지막 좌표는 초기화 시켜준다
		m_lastAniX=0; 
		m_lastAniZ=0;

		m_nState = 1;
		m_nCrtAnimation		= -2;//SangHo - -2 일 경우 Animation 작동하지않는다
		m_nCrtModule		= -1;//SangHo - -1 일 경우 Module 작동하지않는다
		m_nCrtFrame	= id;

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ASpriteInstance::SetAnim(int id)
	{//SangHo - 그리기 속성을 Animation로 바꿔준다
		//if(!m_bLoop)
		//{
			//m_bAnimIsOver = false;

		//행동이 바뀌면 기존의 마지막 좌표는 초기화 시켜준다
		m_lastAniX=0; 
		m_lastAniZ=0;


			m_nState = 0;
			m_nCrtModule	= id;
			m_nCrtFrame	= 0;
			m_nCrtAnimation	= -1;//SangHo - 0대신 -1인 이유는 Paint 전에 항상 키값에 대한 업데이트를 수행해야 하므로 첫프레임을 못찍는 구조적 한계때문

			is_aniDone = false;
			return true;
		//}
		//else
		//{
		//	if (id != m_nCrtModule)
		//	{
		//		//m_bAnimIsOver = false;

		//		m_nCrtModule	= id;
		//		m_nCrtFrame	= 0;
		//		m_nCrtAnimation	= 0;

		//		is_aniDone = false;
		//		return true;
		//	}
		//}
		//return false;
	}

	//void ASpriteInstance::SetAniLoop(bool _loop)	
	
	void ASpriteInstance::RewindAnim(int id)
	{//SangHo - id Anim 으로 교체후 초기화
		//m_bAnimIsOver = false;

		m_nCrtModule	= id;
		m_nCrtFrame	= 0;
		m_nCrtAnimation	= 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASpriteInstance::SetToLastFrame()
	{//SangHo - 	Anim의 마지막 인덱스값으로 이동
		m_nCrtFrame	= m_sprite->GetAFrames(m_nCrtModule) - 1;
		m_nCrtAnimation		= m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame) - 1;
	}

	void ASpriteInstance::setAnimStop( )
	{//SangHo - 	Anim을 재생중단후 인덱스 초기화		
		is_aniDone = true;
		m_nCrtFrame = 0;
	}

	void ASpriteInstance::setCamera(int _CameraX, int _CameraY)
	{//SangHo - 	Anim을 재생중단후 인덱스 초기화		
		CameraX = _CameraX;
		CameraY = _CameraY;
	}


	bool	ASpriteInstance::IsAnimEnded()
	{//SangHo - 	Anim가 현재 재생중인지 아닌지를 알려준다
		if(is_aniDone)
		{
			return true;
		}
		//if (m_bReverse)
		//{
		//	if (m_nCrtFrame != 0)
		//	{
		//		return false;
		//	}
		//}
		else if (m_nCrtFrame != m_sprite->GetAFrames(m_nCrtModule) - 1)
		{
			return false;
		}

		int time = m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame);

		return ((time == 0) || (m_nCrtAnimation == time - 1));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ASpriteInstance::Get_AFrameXZ(int* tmpXZ){//그리기 전에 좌표 확인이 필요할때
		m_sprite->Get_AFrameXY(tmpXZ , m_nCrtModule, m_nCrtFrame, m_posX + m_lastAniX, 0, m_flags, 0, 0);
	}

	void ASpriteInstance::PaintSprite(CGraphics* g,int flags)//SangHo - flags값을 넣지않을경우 0으로 간주한다
	{
		m_flags = flags;
		PaintSprite(g);
	}
	void ASpriteInstance::PaintSprite(CGraphics* g,int posX,int posY,int flags)//SangHo - flags값을 넣지않을경우 0으로 간주한다
	{
		m_posX = posX;
		m_posY = posY;
		m_flags = flags;
		PaintSprite(g);
	}

	void ASpriteInstance::PaintSprite(CGraphics* g)//SangHo - flags값에 따라 좌우상하반전 또는 90도 회전을 지원한다
	{//CameraX,CameraY 는 맵 배경 스크롤에 따른 보정 수치
		//const static byte FLAG_FLIP_X	= 0x01;
		//const static byte FLAG_FLIP_Y	= 0x02;
		//const static byte FLAG_ROT_90	= 0x04;
//		m_flags = flags;
		//m_bAnimIsOver = false;

		if (m_sprite == NULL)
			return;

		//if ((m_flags & FLAG_DONTDRAW) != 0)
		//{
		//	return;
		//}

		//if ((m_layer & 4) != 0)
		//{
		//	return;
		//}
		
		
		
		m_sprite->changePal(m_pal);
		m_sprite->SetBlendCustom(s_Blend.blendCustom,s_Blend.overWrite,s_Blend.Blend_Kind,s_Blend.Blend_Percent);

		
		

		if (m_nCrtAnimation >= -1)//-2 일 경우에 에니메이션이 아닌 프레임또는 모듈을 그린다
		{

				


			m_sprite->PaintAFrame(g, m_nCrtModule, m_nCrtFrame,CameraX+ m_posX + m_lastAniX, CameraY+ (m_posY + m_posZ) + m_lastAniZ, m_flags, 0, 0);


			if(!b_MoveLock){
				m_posX-=m_sprite->m_nowAniX - m_lastAniX;
				m_posZ-=m_sprite->m_nowAniZ - m_lastAniZ;
				//갱신이 끝난 좌표에 전프레임 좌표를 뺀값만큼을 더해준다

				m_lastAniX = m_sprite->m_nowAniX;
				m_lastAniZ = m_sprite->m_nowAniZ;
				m_stopFlag = m_sprite->m_nowFlag;
			}
			

		}
		else if (m_nCrtModule >= 0) // m_nCrtModule --> module
		{
			//	앵커는 임시로 쓰임
			m_sprite->PaintModule(g, m_nCrtModule, CameraX+ m_posX, CameraY+ (m_posY + m_posZ), m_flags, g->BOTTOM | g->HCENTER );
		}
		else if (m_nCrtFrame >= 0) // m_nCrtFrame --> frame
		{
			m_sprite->PaintFrame(g, m_nCrtFrame,CameraX+ m_posX, CameraY+ (m_posY + m_posZ), m_flags, 0, 0);
		}

		//m_bAnimIsOver = IsAnimEnded();


		m_lastX =m_posX;	//SangHo - 인마수의계약스의 현 좌표를 반영한다. - 몸통체크를 위해서(전좌표로 쓰인다)
		m_lastY =m_posY;				//SangHo - 인마수의계약스의 현 좌표를 반영한다. - 몸통체크를 위해서(전좌표로 쓰인다)


	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	
	//SangHo - 구조적 문제 해결위해 다시제작 (2008.12.19)
	bool ASpriteInstance::UpdateSpriteAnim()
	{//SangHo - Animation의 현재값을 1증가시킨다.
		//return true	-  애니메이션 재생중
		//return false	-  애니메이션 종료

		int _m_time = 0;//총 Time 값 (딜레이수치 디폴값은 0)
		int _m_frame = 0;//총 프레임값 (프레임 맥스값)
		_m_time = m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame); // 해당 프레임의 Time값
		_m_frame = m_sprite->GetAFrames(m_nCrtModule);//m_nCrtModule 는 애니메이션 넘버

		{//무결성 체크
			if (m_sprite == NULL) return true;
			if (m_nCrtAnimation < -1) return true;//업데이트 수행시 time 값을 무조건 ++ 시키므로 초기값은 -1, 루프후는 0으로 돌아간다
			if ((m_flags & FLAG_PAUSED) != 0) return true;//일시정지시 무조건 return
			
		}
		
		
		//{//예외값 통일화 처리
		//	if (m_nCrtAnimation < 0) 
		//		m_nCrtAnimation=0;
		//}




		{//프레임의 Time 값을 체크한다 ----- Time 값만큼 딜레이 후에 다음 프레임으로 넘어간다
			m_nCrtAnimation++; //인마수의계약스의 time 값 1증가
			if (m_nCrtAnimation < _m_time) //프레임의 타임값보다 작다면 1증가 하고 한번더 그림
				if (m_nCrtAnimation == (_m_time-1) && m_nCrtFrame == (_m_frame -1) ){//&&!m_bLoop) //마지막Time 일때 다음으로 증가할 프레임이 없다면 false 가 되야한다
					return false;
				}else
					return true;
		}

		{//애니의 프레임 값을 체크한다 ----- 마지막 프레임일 경우 (드로잉종료, 루프) 여부 판단
			if (m_nCrtFrame < (_m_frame -1)){ //프레임 갯수(-1) 보다 현재 프레임인덱스가 작다면 프레임인덱스를 1증가 시킨다
				m_nCrtAnimation=0;//프레임의 타임값 초기화
				m_nCrtFrame++;//다음프레임으로
				{//만약 넘어간 프레임이 마지막 프레임 & time 1 이면 미리 체크를 해줘야 한다-안그러면 마지막 프레임을 한번더 그린다
					_m_time = m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame); // 해당 프레임의 Time값
					if((m_nCrtFrame == (_m_frame -1) && _m_time == 1 )&&!m_bLoop)
						return false;
					else
						return true;
				}
				
			}else{//업데이트 마지막 값 도달
				if(m_bLoop){//루프애니메이션일 경우
					m_nCrtAnimation=0;//프레임의 타임값 초기화
					m_nCrtFrame = 0;//첫프레임으로

					m_lastAniX=0;
					m_lastAniZ=0;					
					//if(Move)UpdateTempXZ(APPLY_X|APPLY_Z);//루프가 돌면 최종좌표를 반영해야한다
					return true;
				}else{//1회성 애니메이션일 경우
					return false;//////////////////////////// 에니메이션 종료 //////////////////////////// 
				}
			}
		}
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int ASpriteInstance::GetCurrentAFrameOff(bool bY)
	{//SangHo - 현재 Off값 구하는 부분이긴하나 활용예상부분을 모르겠음
		int off = (m_sprite->_anims_af_start[m_nCrtModule] + m_nCrtFrame) * 5;

		if (bY)
		{
			return m_sprite->_aframes[off + 3];
		}

		return m_sprite->_aframes[off + 2];
	}

	int ASpriteInstance::GetLastAFrameOff(bool bY)
	{//SangHo - 마지막 Off값 구하는 부분이긴하나 활용예상부분을 모르겠음
		int lastAFrame = m_sprite->GetAFrames(m_nCrtModule) - 1;
		int off = (m_sprite->_anims_af_start[m_nCrtModule] + lastAFrame) * 5;

		if (bY)
		{
			return m_sprite->_aframes[off + 3];
		}

		return m_sprite->_aframes[off + 2];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	int* ASpriteInstance::GetRect(bool bColRect)
	{//SangHo - LCD기준의 좌,상,너비,높이 4개인자값을 리턴한다.

		if (m_rect == NULL)
		{
			m_rect = GL_NEW int[4];
		}

		int posX = m_posX;
		int posY = m_posY;

		if (m_sprite != NULL)
		{
			if (m_nCrtModule >= 0)
			{
				if (m_nCrtAnimation >= 0)
				{
					m_sprite->GetAFrameRect(m_rect, m_nCrtModule, m_nCrtFrame, posX, posY, m_flags, 0, 0);//bColRect
				}
				else
				{
					m_sprite->GetModuleRect(m_rect, m_nCrtModule, posX, posY);
				}
			}
			else if (m_nCrtFrame >= 0)
			{
				m_sprite->GetFrameRect(m_rect, m_nCrtFrame, posX, posY, m_flags, 0, 0);//bColRect
			}
		}

		return m_rect;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	int* ASpriteInstance::GetAbsoluteRect(bool bColRect)
	{//SangHo - 원점기준의 좌,상,너비,높이 4개인자값을 리턴한다.

		if (m_rect == NULL)
		{
			m_rect = GL_NEW int[4];
		}

		if (m_sprite != NULL)
		{
			/*if (bColRect && m_sprite->_frames_coll == NULL)
			{
				return NULL;
			}*/

			if (m_nCrtAnimation >= 0)
			{
				m_sprite->GetAFrameRect(m_rect, m_nCrtModule, m_nCrtFrame, 0, 0, m_flags, 0, 0);//bColRect
			}
			else if (m_nCrtModule >= 0)
			{
				m_sprite->GetModuleRect(m_rect, m_nCrtModule, 0, 0);
			}
			else if (m_nCrtFrame >= 0)
			{
				m_sprite->GetFrameRect(m_rect, m_nCrtFrame, 0, 0, m_flags, 0, 0);//bColRect
			}
		}

		return m_rect;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////	

	int*  ASpriteInstance::GetFModuleRect(int module,int posX, int posY, int flags, int hx, int hy)
	{//SangHo - 현재 인마수의계약스가 그리고있는 Animation Frame 의 module번째 모듈의 좌표를 리턴한다(원점기준, 하이퍼 프레임은 해당되지않음)
		if (m_rect == NULL)
		{
			m_rect = GL_NEW int[4];
		}
		//System.out.println("m_nCrtFrame::::::::::"+m_nCrtFrame);
		//System.out.println("GetAnimFrame(m_nCrtModule,m_nCrtFrame):"+m_sprite->GetAnimFrame(m_nCrtModule,m_nCrtFrame));
		if(m_sprite != NULL)
		{
			m_sprite->GetFModuleRect(m_rect,GetAnimFrame(),module,posX,posY,flags,hx,hy);
			return m_rect;
		}
		return NULL;

	}


	int ASpriteInstance::GetAnimFrame()
	{//SangHo - 현재 인마수의계약스가 그리고있는 Animation Frame 의 고유Index 값을 리턴한다(Ani off값 아님)
		if(m_sprite != NULL)
		{
			return m_sprite->GetAnimFrame(m_nCrtModule,m_nCrtFrame);
		}
		return 0;
	}




	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ASpriteInstance::IsRectCrossing(int rect1[], int rect2[])
	{//SangHo - 두 면적이 충돌하였는지를 판단한다
		if (rect1[0] > rect2[2]) return false;
		if (rect1[2] < rect2[0]) return false;
		if (rect1[1] > rect2[3]) return false;
		if (rect1[3] < rect2[1]) return false;
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	
	bool ASpriteInstance::IsPointInRect(int x, int y, int rect[])
	{//SangHo - 한지점이 면적 안에 들어가있는지 아닌지를 체크한다
		if (x < rect[0]) return false;
		if (x > rect[2]) return false;
		if (y < rect[1]) return false;
		if (y > rect[3]) return false;
		return true;
	}

	bool ASpriteInstance::SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent){
		//SangHo -  블랜드를 지정하자마자 그리는것이 아니라 List 에 넣은뒤 정렬후에 한꺼번에 그리기때문에 값을 저장할 필요성이 있음
		s_Blend.blendCustom = blendCustom;
		s_Blend.overWrite = overWrite;		
		s_Blend.Blend_Kind = Blend_Kind;	
		s_Blend.Blend_Percent = Blend_Percent;
		return true;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////

	//	static int ZOOM_IN_X(int x) { return (((x)*ZOOM_X)/ZOOM_X_DIV); }
	//	static int ZOOM_IN_Y(int y) { return (((y)*ZOOM_Y)/ZOOM_Y_DIV); }

	//	static int ZOOM_OUT_X(int x) { return (((x)*ZOOM_X_DIV)/ZOOM_X); }
	//	static int ZOOM_OUT_Y(int y) { return (((y)*ZOOM_Y_DIV)/ZOOM_Y); }

	//static int ZOOM_IN_FIXED_X(int x) { return ((((x)>>FIXED_PRECISION)*ZOOM_X)/ZOOM_X_DIV); }
	//static int ZOOM_IN_FIXED_Y(int y) { return ((((y)>>FIXED_PRECISION)*ZOOM_Y)/ZOOM_Y_DIV); }

	// [Sinh.2007/02/22] optimize for Triplets

	//	static int ZOOM_OUT_FIXED_X(int x) { return ((((x)<<FIXED_PRECISION)*ZOOM_X_DIV)/ZOOM_X); }
	//	static int ZOOM_OUT_FIXED_Y(int y) { return ((((y)<<FIXED_PRECISION)*ZOOM_Y_DIV)/ZOOM_Y); }

	////////////////////////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////▽폐소스 - SangHo/////////////////////////////////////////
	///////////////////////////////////////////▽폐소스 - SangHo/////////////////////////////////////////
	/*
	int* ASpriteInstance::GetSpriteRect(int _m_posX, int _m_posY)
	{//SangHo - _m_posX,_m_posY 을 기준점으로 가정된 좌,상,너비,높이 4개인자값을 리턴한다.
		if (m_rect == NULL)
		{
			m_rect = GL_NEW int[4];
		}

		if (m_sprite != NULL)
		{
			if (m_nCrtAnimation >= 0)
				m_sprite->GetAFrameRect(m_rect, m_nCrtModule, m_nCrtFrame, _m_posX, _m_posY, m_flags, 0, 0);
			else if (m_nCrtModule >= 0)
				m_sprite->GetModuleRect(m_rect, m_nCrtModule, _m_posX, _m_posY);
			else if (m_nCrtFrame >= 0)
				m_sprite->GetFrameRect(m_rect, m_nCrtFrame, _m_posX, _m_posY, m_flags, 0, 0);

			//m_rect[1] -= m_posZ;
			//m_rect[3] -= m_posZ;

			return m_rect; 
		}
		return NULL;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASpriteInstance::PaintSprite_NO_ZOOM(CGraphics* g)
	{//SangHo - PaintSprite로 대체
	if (m_sprite == NULL)
	return;

	int posX = m_posX,
	posY = m_posY;
	for (ASpriteInstance* o = m_parent; o != NULL; o = o->m_parent)
	{
	posX += o->m_posX;
	posY += o->m_posY;
	}
	posX = ( posX >>FIXED_PRECISION ) + SV_X;
	posY = ( posY >>FIXED_PRECISION ) + SV_Y;

	//		System.out.println("PaintSprite("+posX+", "+posY+")...");

	m_sprite->SetCurrentPalette(m_pal);

	if (m_nCrtAnimation >= 0)
	m_sprite->PaintAFrame(g, m_nCrtModule, m_nCrtFrame, posX, posY, m_flags, 0, 0);
	else if (m_nCrtModule >= 0) // m_nCrtModule --> module
	m_sprite->PaintModule(g, m_nCrtModule, posX, posY, m_flags);
	else if (m_nCrtFrame >= 0) // m_nCrtFrame --> frame
	m_sprite->PaintFrame(g, m_nCrtFrame, posX, posY, m_flags, 0, 0);


	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASpriteInstance::ApplyAnimOff()//좌표에 가중치 계산을 하는부분 쓸모없어보임
	{
		//	if (bASSERT) DBG.ASSERT(m_sprite != NULL);

		m_posX -= m_posOffX;
		m_posY -= m_posOffY;

		//////////

		//	m_sprite->GetAFrameOffset(&m_posOffX, &m_posOffY);

		int off = (m_sprite->_anims_af_start[m_nCrtModule] + m_nCrtFrame) * 5;

		//	m_posOffX = ZOOM_OUT_FIXED_X(m_sprite->_aframes[off+2] << FIXED_PRECISION);
		m_posOffX = (m_sprite->_aframes[off+2] << FIXED_PRECISION) * ZOOM_X_DIV / ZOOM_X;
		if ((m_flags & FLAG_FLIP_X) != 0) m_posOffX = -m_posOffX;

		//	m_posOffY = ZOOM_OUT_FIXED_Y(m_sprite->_aframes[off+3] << FIXED_PRECISION);
		m_posOffY = (m_sprite->_aframes[off+3] << FIXED_PRECISION) * ZOOM_Y_DIV / ZOOM_Y;
		if ((m_flags & FLAG_FLIP_Y) != 0) m_posOffY = -m_posOffY;

		//////////

		m_posX += m_posOffX;
		m_posY += m_posOffY;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////


	void ASpriteInstance::OnScreenTest()
	{//SangHo - 사용하지 않음
	//	_vis = 1 + 2 + 4 + 8;

	int ox = 0, oy = 0;
	for (ASpriteInstance* o = m_parent; o != NULL; o = o->m_parent)
	{
	ox += o->m_posX;
	oy += o->m_posY;
	}

	int* rect = GetRect(false);

	rect[0] += ox - (GV_W << FIXED_PRECISION);
	rect[1] += oy - (GV_H << FIXED_PRECISION);
	rect[2] += ox;
	rect[3] += oy;

	_vis = 0;

	if (rect[0] < 0 && rect[2] >= 0 && rect[1] < 0 && rect[3] >= 0)
	{
	_vis = 1 + 2 + 4 + 8;
	}
	else
	{
	//...
	}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool	ASpriteInstance::IsOnScreen(int style)
	{//SangHo - 사용하지 않음
	return ((_vis & style) != 0);
	}



	int ASpriteInstance::getAniFrameOffY(){
	int off = (m_sprite->_anims_af_start[m_nCrtModule] + m_nCrtFrame) * 5;



	int m_posOffY = (m_sprite->_aframes[off+3] << FIXED_PRECISION) * ZOOM_Y_DIV / ZOOM_Y;
	if ((m_flags & FLAG_FLIP_Y) != 0) m_posOffY = -m_posOffY;
	return m_posOffY;
	}

	*/