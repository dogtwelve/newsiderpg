#ifndef _S_FIELD_MANAGER_
#define _S_FIELD_MANAGER_

#include "SSingleton.h"
#include "List.h"
#include "BackLayer.h"
#include "MemMgr.h"

class SFieldZone
{
private:
	int m_nZoneID;
};


class SFieldSector
{
private:
	int m_nSectorID;

	BackLayer*			pFrontLayer;						//	캐릭터보다 앞에 위치한다.
	List2<BackLayer*>	*pMiddleLayerList;
	List2<BackLayer*>	*pLayerList;
};


class SFieldMgr : public SSingleton<SFieldMgr>
{
private:
	SFieldZone		m_Zone;
	SFieldSector	m_Sector;
	

public:
	SFieldMgr(void);
	virtual ~SFieldMgr(void);

	void LoadZone(int nZoneID);
	void LoadSector(int nSectorID);
	void LoadMap(int nZondID, int nSectorID);
};



#endif