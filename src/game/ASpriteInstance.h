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
	ASprite*		m_sprite;		//SangHo - Instance �� �����ϴ� B��������Ʈ�� �����Ͱ�

	int				m_nState;		//Namyoung - ���º��� 0:���ϸ��̼�, 1:������, 2:���

	int				m_posX;			//SangHo - ���� X ��ǥ(����)
	int				m_posY;			//SangHo - ���� Y ��ǥ(����)
	int				m_posZ;			//SangHo - ���� Z ��ǥ(����)



	int				m_stopFlag;			//SangHo - ���������� �߻��� ������ �÷��װ��� ����Ѵ�

	int CameraX;					//SangHo - ī�޶� ��ǥ�� ��ϵȴ� , �̴� ������ǥ�� ���δ�
	int CameraY;					//SangHo - ī�޶� ��ǥ�� ��ϵȴ� , �̴� ������ǥ�� ���δ�

	int				m_flags;		//SangHo - �׷����� (Ani,Frame,Module) �� ��ȯ�� 0~7 ������ ���� ����
	
	int				m_pal;			//SangHo - �ȷ�Ʈ
	
	int				m_nCrtModule;		//SangHo - Index���� ������ ����, -1���� ������ Module�� ��Ȱ��ȭ �ȴ�
	int				m_nCrtFrame;		//SangHo - Index���� ������ ����, -1���� ������ Frame�� ��Ȱ��ȭ �ȴ�
	int				m_nCrtAnimation;	//SangHo - Index���� ������ ����, -1���� ������ Animation�� ��Ȱ��ȭ �ȴ�(Ȱ��ȭ�� m_nCrtModule�� Animation �ѹ��� �����ϰ�, m_nCrtFrame�� ���� �ε����� �ӽ� �����Ѵ�)

	int* 			m_rect;			//SangHo -  (Ani,Frame,Module)�� ��,��,�ʺ�,���� ���� �����ϴ� 4�迭
	
	bool			m_bLoop;		//SangHo - AniDraw ��� �������θ� ����
	bool			b_MoveLock;		//SangHo - �ִϸ��̼��� ������ ���� ��ǥ�� �ݿ� �ϴ� ���θ� ����
	//int				m_layer;					//SangHo - ��Ÿ���￡�� ���� ���� ������� ���̾� ����(�� �θ����ǰ��Ʈ ����)
	int				m_savedLayer/* = -1*/;		//SangHo - ��Ÿ���￡�� ���� ���� ������� ���̾� ����(�� �θ����ǰ��Ʈ ����)

	int				m_lastX;			//SangHo - X ���� �浹üũ�� ���ؼ� ���� X��ǥ�� ���
	int				m_lastY;			//SangHo - X ���� �浹üũ�� ���ؼ� ���� Y��ǥ�� ���

private:
	int				m_lastAniX;			//SangHo - Animation�� ���� ��ǥ - ���� �������� �����ǿ� ���ֱ� ���ؼ� ����
	int				m_lastAniZ;			//SangHo - Animation�� ���� ��ǥ - ���� �������� �����ǿ� ���ֱ� ���ؼ� ����
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

	void SetModule(int id);	//SangHo - �׸��� �Ӽ��� Module�� �ٲ��ش�	

	void SetFrame(int id);	//SangHo - �׸��� �Ӽ��� Frame�� �ٲ��ش�
	
	bool SetAnim(int id);	//SangHo - �׸��� �Ӽ��� Animation�� �ٲ��ش�
	
	void SetAniLoop(bool _loop){m_bLoop = _loop;}			//SangHo - int id, bool _loop); //SangHo - Animation �� ���Ͽ� �������θ� �����Ѵ�
	void SetAniMoveLock(bool _Lock){b_MoveLock = _Lock;}	//SangHo - �ִϸ��̼��� ������ ���� ��ǥ�� �ݿ� �ϴ� ���θ� ����

	void RewindAnim(int id);	//SangHo - id Anim ���� ��ü�� �ʱ�ȭ
	
	void SetToLastFrame();	//SangHo - 	Anim�� ������ �ε��������� �̵�

	void setAnimStop( );	//SangHo - 	Anim�� ����ߴ��� �ε��� �ʱ�ȭ

	void setCamera(int _CameraX, int _CameraY);	//SangHo - 	Anim�� ����ߴ��� �ε��� �ʱ�ȭ
	
	bool IsAnimEnded();	//SangHo - 	Anim�� ���� ��������� �ƴ����� �˷��ش�
	

	void Get_AFrameXZ(int* tmpXZ);//�׸��� ���� ��ǥȮ���� �ʿ��Ҷ�
	void PaintSprite(CGraphics* g);	//SangHo - PaintSprite ���� �ε�
	void PaintSprite(CGraphics* g,int posX,int posY,int flags);	//SangHo - PaintSprite ���� �ε�
	void PaintSprite(CGraphics* g,int flags);	//SangHo - flags���� ���� �¿���Ϲ��� �Ǵ� 90�� ȸ���� �����Ѵ�(m_flags ����)
		
	bool UpdateSpriteAnim();	//SangHo - Animation�� ���簪�� 1������Ų��.

	int GetCurrentAFrameOff(bool bY);	//SangHo - ���� Off�� ���ϴ� �κ��̱��ϳ� Ȱ�뿹��κ��� �𸣰���
	
	int GetLastAFrameOff(bool bY);	//SangHo - ������ Off�� ���ϴ� �κ��̱��ϳ� Ȱ�뿹��κ��� �𸣰���	
	
	int* GetRect(bool bColRect);//SangHo - LCD������ ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.	
	
	int* GetAbsoluteRect(bool bColRect);//SangHo - ���������� ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.	
	
	int* GetFModuleRect(int module,int posX, int posY, int flags, int hx, int hy);	//SangHo - ���� �θ����ǰ�ེ�� �׸����ִ� Animation Frame �� module��° ����� ��ǥ�� �����Ѵ�(��������, ������ �������� �ش��������)
		
	int GetAnimFrame();	//SangHo - ���� �θ����ǰ�ེ�� �׸����ִ� Animation Frame �� ����ID���� �����Ѵ�
	
	bool IsRectCrossing(int* rect1, int* rect2);	//SangHo - �� ������ �浹�Ͽ������� �Ǵ��Ѵ�
	
	bool IsPointInRect(int x, int y, int* rect);	//SangHo - �������� ���� �ȿ� ���ִ��� �ƴ����� üũ�Ѵ�

	bool SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent);	//SangHo - �������� ���� �ȿ� ���ִ��� �ƴ����� üũ�Ѵ�
	
	

};

///////////////////////////////////////////����ҽ� - SangHo/////////////////////////////////////////
///////////////////////////////////////////����ҽ� - SangHo/////////////////////////////////////////
/*
	bool			m_bReverse;		//������ ����
	bool			m_bAnimIsOver;	//SangHo - ���ʿ��� �Լ�	
	int*			m_boundingRect;	//SangHo - ������ ����
	bool			m_bUpdateRect;	//SangHo - ������ ����
	int _vis;	//SangHo - ������� ����	 
	void PaintSprite_NO_ZOOM(CGraphics* g);	//SangHo - PaintSprite�� ��ü
	int* GetSpriteRect(int _m_posX, int _m_posY);//SangHo - _m_posX,_m_posY �� ���������� ������ ��,��,�ʺ�,���� 4�����ڰ��� �����Ѵ�.
	void ApplyAnimOff();
	static int ZOOM_IN_FIXED_X(int x)
	{
	return (x >> FIXED_PRECISION);
	}

	static int ZOOM_IN_FIXED_Y(int y)
	{
	return (y >> FIXED_PRECISION);
	}

	void OnScreenTest();	//SangHo - ������� ����	

	bool	IsOnScreen(int style);	//SangHo - ������� ����	

	int getAniFrameOffY();	//������ ����
*/
	

#endif //_ASPRITE_INSTANCE_


	
