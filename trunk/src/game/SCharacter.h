#ifndef _S_CHARACTER_
#define _S_CHARACTER_


#include "SObject.h"
#include "Physics.h"

class SCharacter : public SObject
{
private:
	Physics* m_Physics;

public:
	SCharacter(ObjectType nType, int nID, ASpriteInstance*	Asins, int Weight = DEFAULT_WEIGHT);
	virtual ~SCharacter(void);

	virtual bool Make( )     {return true;}
	virtual void Release()  {}

	virtual void Process(void);
	virtual void Paint(void);
};



#endif