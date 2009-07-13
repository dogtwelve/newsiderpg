#include "VBaseState.h"
#include "SUtil.h"




#ifndef __GWORLDMAP_
#define __GWORLDMAP_



class GWorldMap : public VBaseState
{
public:

	GWorldMap();
	~GWorldMap();

	void Initialize(int nDummy1, int nDummy2);
	void Release();
	void Process();
	void Paint();
	void KeyEvent(int m_keyCode, int m_keyRepeat);

	int m_nEventIndex;

	class ASprite* m_pWorldMapAs;
	class ASpriteInstance* m_pWorldMapAsIns;


};

#endif	//__GWORLDMAP

