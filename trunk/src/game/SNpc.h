#ifndef _S_NPC_
#define _S_NPC_


#include "SCharacter.h"
#include "ASpriteInstance.h"


class SNpc : public SCharacter , public STalkInterface
{
private:
	int m_nEvtCode;
	int m_nActionType;


public:
	SNpc(ObjectType ObjType, uint8 nActionType, int nUniKey, ASpriteInstance* pAsins, uint8 Evtcode);
	virtual ~SNpc(void);

	inline void SetActionType(int ActionType)	{m_nActionType = ActionType;}
	inline int GetActionType()					{return m_nActionType;}

	inline void SetEventCode(int eventCode)		{m_nEvtCode = eventCode;}
	inline int GetEventCode()					{return m_nEvtCode;}

//	void Process(void);
//	void Paint(void)

	bool PossibleToTalk(int dir, int x1, int y1, int x2, int y2);
	inline int GetTalkCode()	{return nTalkCode;}
};



#endif