#ifndef _S_NPC_
#define _S_NPC_


#include "SCharacter.h"
#include "ASpriteInstance.h"


class SNpc : public SCharacter
{
private:
	uint8 m_nActionType;
	uint8 m_nEvtCode;

public:
	SNpc(ObjectType ObjType, uint8 nActionType, int nUniKey, ASpriteInstance* pAsins, uint8 Evtcode);
	virtual ~SNpc(void);

//	void Process(void);
//	void Paint(void)
};



#endif