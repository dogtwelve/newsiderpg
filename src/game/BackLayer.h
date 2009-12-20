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

	int spridx;		//	rematch시 쓰인다.(스프라이트를 지웠다가 다시 로드할경우가 있음)
}BackLayerObject;



class BackLayer
{
public:
	// 오브젝트의 리스트
	int m_nBaseYLine;
	int m_nMoveRate;			//	한번에 움직이는 비율	//	100%가 정비율
	int	m_nMyAngleX;			//	현재 앵글의 위치
	int m_nLayerSizeX;
	List2<BackLayerObject*>	*pObjectList;

	BackLayer();
	~BackLayer();

	void InsertObject(BackLayerObject*);
	void SetAngle(int);
	void Process();
	void Paint();

	void LoadMapLayer(class ASprite** pAsprite, char* packName, int packIndex);
	//	필드의 이미지만 날렸다가 다시 불러올경우 다시 포인터를 매칭시켜준다.

	void RematchImage(class ASprite** pAsprite);

	inline void SetSortOption(int nSortOpt)	{m_nSortOption = nSortOpt;}

private:
	int m_nSortOption;
};


#endif