#ifndef __VBASESTATE_
#define __VBASESTATE_



class VBaseState
{
public:
   virtual void Initialize(int nDummy1, int nDummy2)=0;
   virtual void Release()=0;
   virtual void Process()=0;
   virtual void Paint()=0;
   virtual void KeyEvent(int m_keyCode, int m_keyRepeat)=0;
};


#endif//	__VBASESTATE_


