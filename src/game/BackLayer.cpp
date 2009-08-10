#include "BackLayer.h"

//--------------------------------------------------------------------------
BackLayer::BackLayer()
//--------------------------------------------------------------------------
{
	pObjectList = GL_NEW List2<BackLayerObject*>();
	m_nLayerSizeX = 0;
	m_nBaseYLine = 0;
}


//--------------------------------------------------------------------------
BackLayer::~BackLayer()
//--------------------------------------------------------------------------
{
	InitList(pObjectList);
	while(NotEndList(pObjectList))
	{
		SUTIL_FreeSpriteInstance(GetData(pObjectList)->pAsIns);
		SAFE_DELETE(GetData(pObjectList));
		pObjectList->Delete();
	}
	SAFE_DELETE(pObjectList);
}


//--------------------------------------------------------------------------
void BackLayer::InsertObject(BackLayerObject* pBackObject)		//	������Ʈ�� �߰���Ų��.
//--------------------------------------------------------------------------
{
/*
	InitList(pObjectList);

	if(0 == GetNodeCount(pObjectList))
	{
		pObjectList->Insert_prev(pBackObject);
		return;
	}

	while(NotEndList(pObjectList))
	{
		if(GetData(pObjectList)->x > pBackObject->x)
		{
			pObjectList->Insert_prev(pBackObject);
			return;
		}
		MoveNext(pObjectList);
	}
	
	pObjectList->Insert_prev(pBackObject);	
*/

	MoveTail(pObjectList);
	pObjectList->Insert_prev(pBackObject);	

}

//--------------------------------------------------------------------------
void BackLayer::Process()
//--------------------------------------------------------------------------
{
	
}


//--------------------------------------------------------------------------
void BackLayer::Paint()
//--------------------------------------------------------------------------
{
	int nTmpXAddAngle = m_nMyAngleX;
	nTmpXAddAngle %= m_nLayerSizeX;
	nTmpXAddAngle *= (-1);

	while(1)
	{
		InitList(pObjectList);
		while(NotEndList(pObjectList))
		{
			//	Ÿ���� ���� �ε����̴�.
//			if()

			// �̹����� ȭ���� ���ʺ��� ������ �׸��� �ʴ´�.
			if(0 < (GetData(pObjectList)->endx + nTmpXAddAngle))
			//if(0 < (GetData(pObjectList)->x + nTmpXAddAngle + GetData(pObjectList)->width))
			{
				// �̹����� ȭ���� �����ʺ��� ũ�� �׸��� �ʴ´�.
				if(SCREEN_WIDTH > (GetData(pObjectList)->startx + nTmpXAddAngle))
				{
					if(1 == GetData(pObjectList)->drawtype)	{SUTIL_UpdateTimeAsprite(GetData(pObjectList)->pAsIns);}
					SUTIL_SetXPosAsprite(GetData(pObjectList)->pAsIns, GetData(pObjectList)->x);
					SUTIL_SetYPosAsprite(GetData(pObjectList)->pAsIns, GetData(pObjectList)->y);
					SUTIL_SetZPosAsprite(GetData(pObjectList)->pAsIns, GetData(pObjectList)->z);

					GetData(pObjectList)->pAsIns->CameraX = nTmpXAddAngle;

					SUTIL_PaintAsprite(GetData(pObjectList)->pAsIns,S_NOT_INCLUDE_SORT);
				}
			}
			MoveNext(pObjectList);
		}
		nTmpXAddAngle += m_nLayerSizeX;
		
		if(SCREEN_WIDTH < nTmpXAddAngle){return;}
	}
}

//--------------------------------------------------------------------------
void BackLayer::SetAngle(int xAngle)
//--------------------------------------------------------------------------
{
	m_nMyAngleX = xAngle * m_nMoveRate / 100;
}


//--------------------------------------------------------------------------
void BackLayer::LoadMapLayer(ASprite** pASprite, char* packName, int packIndex)
//--------------------------------------------------------------------------
{
	BackLayerObject* pBackObject = NULL;
	int tmpsprid = 0;

	SUTIL_Data_init(packName);
	SUTIL_Data_open(packIndex);

	int AsframeNum = 0;
	int tmpId = 0;

	ASprite*	tmpASprite;
	while(1)
	{
		SUTIL_Data_readU8();											//	0x08		�а� ������.
		tmpId				= (short)SUTIL_Data_readU16();

		if(1 == tmpId)		//	������ ����Ÿ
		{
			m_nLayerSizeX += (short)SUTIL_Data_readU16();
			break;
		}
		else if(2 == tmpId || 3 == tmpId)			//	�ӽð� �׳� �귯����.
		{
		}
		else if(11 == tmpId)							//	��Ʈ�� �׷��� �Ѵ�.
		{
			(short)SUTIL_Data_readU16();				//	x
			(short)SUTIL_Data_readU16();				//	y
			(short)SUTIL_Data_readU16();				//	���� Ÿ��
			(short)SUTIL_Data_readU16();				//	draw type	//	0�̸� frame, 1�̸� animation
			(short)SUTIL_Data_readU16();				//	draw num
			(short)SUTIL_Data_readU16();											//	�ӽ�3		�а� ������.
			(short)SUTIL_Data_readU16();											//	�ӽ�3		�а� ������.
			continue;
		}
		else
		{
			//DONT_GO_RECT* pTmpRect;

			if(100 <= tmpId)		//���� ������Ʈ�� ��������Ʈ �ѹ����� �˷��ش�.
			{
				tmpsprid = (tmpId-100)/100;
				tmpASprite = pASprite[tmpsprid];
			}
		}

		pBackObject	= GL_NEW BackLayerObject();
		pBackObject->x			= (short)SUTIL_Data_readU16();				//	x
		pBackObject->y			= (short)SUTIL_Data_readU16();				//	y

								  (short)SUTIL_Data_readU16();				//	�а� ������.
		pBackObject->type		= (short)SUTIL_Data_readU16();				//	���� Ÿ��
		pBackObject->drawtype	= (short)SUTIL_Data_readU16();				//	draw type	//	0�̸� frame, 1�̸� animation
		AsframeNum				= (short)SUTIL_Data_readU16();				//	draw num
								  (short)SUTIL_Data_readU16();				//	�ӽ�3		�а� ������.

		pBackObject->spridx = tmpsprid;
		pBackObject->pAsIns = GL_NEW ASpriteInstance(tmpASprite, 0, 0, NULL);
		pBackObject->pAsIns->SetAniMoveLock(true);

		if(0 == pBackObject->drawtype)		{SUTIL_SetTypeFrameAsprite(pBackObject->pAsIns, AsframeNum);}
		else if(1 == pBackObject->drawtype)
		{
			SUTIL_SetTypeAniAsprite(pBackObject->pAsIns, AsframeNum);
			SUTIL_SetLoopAsprite(pBackObject->pAsIns, true);
		}
		
	//	pBackObject->adjustx = tmpASprite->GetFrameX(AsframeNum);
	//	pBackObject->width = tmpASprite->GetFrameWidth(AsframeNum);
		pBackObject->x += m_nLayerSizeX;
		pBackObject->y += m_nBaseYLine;
	//	pBackObject->x += pBackObject->adjustx;
		pBackObject->z = 0;

		pBackObject->startx = pBackObject->x + tmpASprite->GetFrameX(AsframeNum);
		pBackObject->endx = pBackObject->startx + tmpASprite->GetFrameWidth(AsframeNum);

		InsertObject(pBackObject);
	}

	SUTIL_Data_free();
}


//--------------------------------------------------------------------------
void BackLayer::RematchImage(class ASprite** pAsprite)
//--------------------------------------------------------------------------
{
	for(InitList(pObjectList);NotEndList(pObjectList);MoveNext(pObjectList))
	{
		GetData(pObjectList)->pAsIns->m_sprite = pAsprite[GetData(pObjectList)->spridx];
	}
}
