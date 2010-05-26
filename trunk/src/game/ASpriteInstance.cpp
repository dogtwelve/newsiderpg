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
	{//SangHo - �׸��� �Ӽ��� Module�� �ٲ��ش�
		//�ൿ�� �ٲ�� ������ ������ ��ǥ�� �ʱ�ȭ �����ش�
		m_lastAniX=0; 
		m_lastAniZ=0;

		m_nState = 2;
		m_nCrtAnimation		= -2;//SangHo - -2 �� ��� Animation �۵������ʴ´�
		m_nCrtModule		= id;
		//m_nCrtFrame	= -1;//SangHo - -1 �� ��� Frame �۵������ʴ´�

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ASpriteInstance::SetFrame(int id)
	{//SangHo - �׸��� �Ӽ��� Frame�� �ٲ��ش�
		//�ൿ�� �ٲ�� ������ ������ ��ǥ�� �ʱ�ȭ �����ش�
		m_lastAniX=0; 
		m_lastAniZ=0;

		m_nState = 1;
		m_nCrtAnimation		= -2;//SangHo - -2 �� ��� Animation �۵������ʴ´�
		m_nCrtModule		= -1;//SangHo - -1 �� ��� Module �۵������ʴ´�
		m_nCrtFrame	= id;

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ASpriteInstance::SetAnim(int id)
	{//SangHo - �׸��� �Ӽ��� Animation�� �ٲ��ش�
		//if(!m_bLoop)
		//{
			//m_bAnimIsOver = false;

		//�ൿ�� �ٲ�� ������ ������ ��ǥ�� �ʱ�ȭ �����ش�
		m_lastAniX=0; 
		m_lastAniZ=0;


			m_nState = 0;
			m_nCrtModule	= id;
			m_nCrtFrame	= 0;
			m_nCrtAnimation	= -1;//SangHo - 0��� -1�� ������ Paint ���� �׻� Ű���� ���� ������Ʈ�� �����ؾ� �ϹǷ� ù�������� ����� ������ �Ѱ趧��

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
	{//SangHo - id Anim ���� ��ü�� �ʱ�ȭ
		//m_bAnimIsOver = false;

		m_nCrtModule	= id;
		m_nCrtFrame	= 0;
		m_nCrtAnimation	= 0;
	}

		////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASpriteInstance::SetToLastFrame()
	{//SangHo - 	Anim�� ������ �ε��������� �̵�
		m_nCrtFrame	= m_sprite->GetAFrames(m_nCrtModule) - 1;
		m_nCrtAnimation		= m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame) - 1;
	}

	void ASpriteInstance::setAnimStop( )
	{//SangHo - 	Anim�� ����ߴ��� �ε��� �ʱ�ȭ		
		is_aniDone = true;
		m_nCrtFrame = 0;
	}

	void ASpriteInstance::setCamera(int _CameraX, int _CameraY)
	{//SangHo - 	Anim�� ����ߴ��� �ε��� �ʱ�ȭ		
		CameraX = _CameraX;
		CameraY = _CameraY;
	}


	bool	ASpriteInstance::IsAnimEnded()
	{//SangHo - 	Anim�� ���� ��������� �ƴ����� �˷��ش�
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
	void ASpriteInstance::Get_AFrameXZ(int* tmpXZ){//�׸��� ���� ��ǥ Ȯ���� �ʿ��Ҷ�
		m_sprite->Get_AFrameXY(tmpXZ , m_nCrtModule, m_nCrtFrame, m_posX + m_lastAniX, 0, m_flags, 0, 0);
	}

	void ASpriteInstance::PaintSprite(CGraphics* g,int flags)//SangHo - flags���� ����������� 0���� �����Ѵ�
	{
		m_flags = flags;
		PaintSprite(g);
	}
	void ASpriteInstance::PaintSprite(CGraphics* g,int posX,int posY,int flags)//SangHo - flags���� ����������� 0���� �����Ѵ�
	{
		m_posX = posX;
		m_posY = posY;
		m_flags = flags;
		PaintSprite(g);
	}

	void ASpriteInstance::PaintSprite(CGraphics* g)//SangHo - flags���� ���� �¿���Ϲ��� �Ǵ� 90�� ȸ���� �����Ѵ�
	{//CameraX,CameraY �� �� ��� ��ũ�ѿ� ���� ���� ��ġ
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

		
		

		if (m_nCrtAnimation >= -1)//-2 �� ��쿡 ���ϸ��̼��� �ƴ� �����ӶǴ� ����� �׸���
		{

				


			m_sprite->PaintAFrame(g, m_nCrtModule, m_nCrtFrame,CameraX+ m_posX + m_lastAniX, CameraY+ (m_posY + m_posZ) + m_lastAniZ, m_flags, 0, 0);


			if(!b_MoveLock){
				m_posX-=m_sprite->m_nowAniX - m_lastAniX;
				m_posZ-=m_sprite->m_nowAniZ - m_lastAniZ;
				//������ ���� ��ǥ�� �������� ��ǥ�� ������ŭ�� �����ش�

				m_lastAniX = m_sprite->m_nowAniX;
				m_lastAniZ = m_sprite->m_nowAniZ;
				m_stopFlag = m_sprite->m_nowFlag;
			}
			

		}
		else if (m_nCrtModule >= 0) // m_nCrtModule --> module
		{
			//	��Ŀ�� �ӽ÷� ����
			m_sprite->PaintModule(g, m_nCrtModule, CameraX+ m_posX, CameraY+ (m_posY + m_posZ), m_flags, g->BOTTOM | g->HCENTER );
		}
		else if (m_nCrtFrame >= 0) // m_nCrtFrame --> frame
		{
			m_sprite->PaintFrame(g, m_nCrtFrame,CameraX+ m_posX, CameraY+ (m_posY + m_posZ), m_flags, 0, 0);
		}

		//m_bAnimIsOver = IsAnimEnded();


		m_lastX =m_posX;	//SangHo - �θ����ǰ�ེ�� �� ��ǥ�� �ݿ��Ѵ�. - ����üũ�� ���ؼ�(����ǥ�� ���δ�)
		m_lastY =m_posY;				//SangHo - �θ����ǰ�ེ�� �� ��ǥ�� �ݿ��Ѵ�. - ����üũ�� ���ؼ�(����ǥ�� ���δ�)


	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	
	//SangHo - ������ ���� �ذ����� �ٽ����� (2008.12.19)
	bool ASpriteInstance::UpdateSpriteAnim()
	{//SangHo - Animation�� ���簪�� 1������Ų��.
		//return true	-  �ִϸ��̼� �����
		//return false	-  �ִϸ��̼� ����

		int _m_time = 0;//�� Time �� (�����̼�ġ �������� 0)
		int _m_frame = 0;//�� �����Ӱ� (������ �ƽ���)
		_m_time = m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame); // �ش� �������� Time��
		_m_frame = m_sprite->GetAFrames(m_nCrtModule);//m_nCrtModule �� �ִϸ��̼� �ѹ�

		{//���Ἲ üũ
			if (m_sprite == NULL) return true;
			if (m_nCrtAnimation < -1) return true;//������Ʈ ����� time ���� ������ ++ ��Ű�Ƿ� �ʱⰪ�� -1, �����Ĵ� 0���� ���ư���
			if ((m_flags & FLAG_PAUSED) != 0) return true;//�Ͻ������� ������ return
			
		}
		
		
		//{//���ܰ� ����ȭ ó��
		//	if (m_nCrtAnimation < 0) 
		//		m_nCrtAnimation=0;
		//}




		{//�������� Time ���� üũ�Ѵ� ----- Time ����ŭ ������ �Ŀ� ���� ���������� �Ѿ��
			m_nCrtAnimation++; //�θ����ǰ�ེ�� time �� 1����
			if (m_nCrtAnimation < _m_time) //�������� Ÿ�Ӱ����� �۴ٸ� 1���� �ϰ� �ѹ��� �׸�
				if (m_nCrtAnimation == (_m_time-1) && m_nCrtFrame == (_m_frame -1) ){//&&!m_bLoop) //������Time �϶� �������� ������ �������� ���ٸ� false �� �Ǿ��Ѵ�
					return false;
				}else
					return true;
		}

		{//�ִ��� ������ ���� üũ�Ѵ� ----- ������ �������� ��� (���������, ����) ���� �Ǵ�
			if (m_nCrtFrame < (_m_frame -1)){ //������ ����(-1) ���� ���� �������ε����� �۴ٸ� �������ε����� 1���� ��Ų��
				m_nCrtAnimation=0;//�������� Ÿ�Ӱ� �ʱ�ȭ
				m_nCrtFrame++;//��������������
				{//���� �Ѿ �������� ������ ������ & time 1 �̸� �̸� üũ�� ����� �Ѵ�-�ȱ׷��� ������ �������� �ѹ��� �׸���
					_m_time = m_sprite->GetAFrameTime(m_nCrtModule, m_nCrtFrame); // �ش� �������� Time��
					if((m_nCrtFrame == (_m_frame -1) && _m_time == 1 )&&!m_bLoop)
						return false;
					else
						return true;
				}
				
			}else{//������Ʈ ������ �� ����
				if(m_bLoop){//�����ִϸ��̼��� ���
					m_nCrtAnimation=0;//�������� Ÿ�Ӱ� �ʱ�ȭ
					m_nCrtFrame = 0;//ù����������

					m_lastAniX=0;
					m_lastAniZ=0;					
					//if(Move)UpdateTempXZ(APPLY_X|APPLY_Z);//������ ���� ������ǥ�� �ݿ��ؾ��Ѵ�
					return true;
				}else{//1ȸ�� �ִϸ��̼��� ���
					return false;//////////////////////////// ���ϸ��̼� ���� //////////////////////////// 
				}
			}
		}
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	int ASpriteInstance::GetCurrentAFrameOff(bool bY)
	{//SangHo - ���� Off�� ���ϴ� �κ��̱��ϳ� Ȱ�뿹��κ��� �𸣰���
		int off = (m_sprite->_anims_af_start[m_nCrtModule] + m_nCrtFrame) * 5;

		if (bY)
		{
			return m_sprite->_aframes[off + 3];
		}

		return m_sprite->_aframes[off + 2];
	}

	int ASpriteInstance::GetLastAFrameOff(bool bY)
	{//SangHo - ������ Off�� ���ϴ� �κ��̱��ϳ� Ȱ�뿹��κ��� �𸣰���
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
	{//SangHo - LCD������ ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.

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
	{//SangHo - ���������� ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.

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
	{//SangHo - ���� �θ����ǰ�ེ�� �׸����ִ� Animation Frame �� module��° ����� ��ǥ�� �����Ѵ�(��������, ������ �������� �ش��������)
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
	{//SangHo - ���� �θ����ǰ�ེ�� �׸����ִ� Animation Frame �� ����Index ���� �����Ѵ�(Ani off�� �ƴ�)
		if(m_sprite != NULL)
		{
			return m_sprite->GetAnimFrame(m_nCrtModule,m_nCrtFrame);
		}
		return 0;
	}




	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ASpriteInstance::IsRectCrossing(int rect1[], int rect2[])
	{//SangHo - �� ������ �浹�Ͽ������� �Ǵ��Ѵ�
		if (rect1[0] > rect2[2]) return false;
		if (rect1[2] < rect2[0]) return false;
		if (rect1[1] > rect2[3]) return false;
		if (rect1[3] < rect2[1]) return false;
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	
	bool ASpriteInstance::IsPointInRect(int x, int y, int rect[])
	{//SangHo - �������� ���� �ȿ� ���ִ��� �ƴ����� üũ�Ѵ�
		if (x < rect[0]) return false;
		if (x > rect[2]) return false;
		if (y < rect[1]) return false;
		if (y > rect[3]) return false;
		return true;
	}

	bool ASpriteInstance::SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent){
		//SangHo -  ���带 �������ڸ��� �׸��°��� �ƴ϶� List �� ������ �����Ŀ� �Ѳ����� �׸��⶧���� ���� ������ �ʿ伺�� ����
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



	///////////////////////////////////////////����ҽ� - SangHo/////////////////////////////////////////
	///////////////////////////////////////////����ҽ� - SangHo/////////////////////////////////////////
	/*
	int* ASpriteInstance::GetSpriteRect(int _m_posX, int _m_posY)
	{//SangHo - _m_posX,_m_posY �� ���������� ������ ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.
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
	{//SangHo - PaintSprite�� ��ü
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

	void ASpriteInstance::ApplyAnimOff()//��ǥ�� ����ġ ����� �ϴºκ� ��������
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
	{//SangHo - ������� ����
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
	{//SangHo - ������� ����
	return ((_vis & style) != 0);
	}



	int ASpriteInstance::getAniFrameOffY(){
	int off = (m_sprite->_anims_af_start[m_nCrtModule] + m_nCrtFrame) * 5;



	int m_posOffY = (m_sprite->_aframes[off+3] << FIXED_PRECISION) * ZOOM_Y_DIV / ZOOM_Y;
	if ((m_flags & FLAG_FLIP_Y) != 0) m_posOffY = -m_posOffY;
	return m_posOffY;
	}

	*/