#include "SUtil.h"
#include "List.h"

#ifndef		__NEWBACKLAYER_H_
#define		__NEWBACKLAYER_H_

typedef struct _BackLayerObject
{
	class ASpriteInstance*	pAsIns;
	int type;
	int drawtype;
	int x,y,z;
	int width;
	int adjustx;

	int startx;
	int endx;

	int spridx;		//	rematch�� ���δ�.(��������Ʈ�� �����ٰ� �ٽ� �ε��Ұ�찡 ����)
}BackLayerObject;



class BackLayer
{
public:
	// ������Ʈ�� ����Ʈ
	int m_nBaseYLine;
	int m_nMoveRate;			//	�ѹ��� �����̴� ����	//	100%�� ������
	int	m_nMyAngleX;			//	���� �ޱ��� ��ġ
	int m_nLayerSizeX;
	List2<BackLayerObject*>	*pObjectList;

	BackLayer();
	~BackLayer();

	void InsertObject(BackLayerObject*);
	void SetAngle(int);
	void Process();
	void Paint();

	void LoadMapLayer(class ASprite** pAsprite, char* packName, int packIndex);
	//	�ʵ��� �̹����� ���ȴٰ� �ٽ� �ҷ��ð�� �ٽ� �����͸� ��Ī�����ش�.

	void RematchImage(class ASprite** pAsprite);

	inline void SetSortOption(int nSortOpt)	{m_nSortOption = nSortOpt;}

private:
	int m_nSortOption;
};


#endif