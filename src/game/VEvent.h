#ifndef __VEVENT_
#define __VEVENT_



class VEvent
{
public:
	int m_nType;
   virtual void Initialize(int nDummy1, int nDummy2)=0;
   virtual void Release()=0;
   virtual void Process()=0;
   virtual void Paint()=0;
   virtual int CheckEvent(int nDummy1, int nDummy2, int nDummy3, int nDummy4, int nDummy5)=0;
   virtual void SetAngle(int x)=0;
};


#endif//	__VEVENT_


