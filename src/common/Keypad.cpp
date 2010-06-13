// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// \author  Qiu Guan Chen
// \author  Qiu Wei Min

#include "Keypad.h"
#include "Engine.h"

#define ID_TO_MASK(x) (1 << (x))

#ifdef USE_OLD_KEY_CONTROL
CKeypad::CKeypad()
#ifdef KEY_SUPPORT_DOUBLEPRESS
	:m_doublePressInterval(5)
#endif
{
	ClearKey();
#ifdef KEY_SUPPORT_DOUBLEPRESS
	MEMSET(m_pressLastTime, 0, sizeof(m_pressLastTime));
	MEMSET(m_pressInterval, 0, sizeof(m_pressInterval));
#endif
}

CKeypad::~CKeypad()
{
}



void CKeypad::ClearKey()
{
    m_keyCurrent = 0;
    m_keyPrevious = 0;
    m_keyPressed = 0;
    m_keyReleased = 0;
#ifdef KEY_FIX_PULSE_PRESS
	m_keyCurrentPulse = 0;
	m_keyPreviousPulse = 0;
#endif
}

void CKeypad::ClearKey(int clearKey)
{
	int mask = ~clearKey;
	m_keyCurrent &= mask;
	m_keyPrevious &= mask;
	m_keyPressed &= mask;
	m_keyReleased &= mask;
#ifdef KEY_FIX_PULSE_PRESS
	m_keyPreviousPulse &= mask;
	m_keyCurrentPulse &= mask;
#endif	

}


void CKeypad::Update()
{
#ifdef KEY_FIX_PULSE_PRESS
	m_keyCurrent &= ~m_keyPreviousPulse;
	m_keyPreviousPulse = m_keyCurrentPulse;
	m_keyCurrentPulse = 0;
#endif
    m_keyPressed = ~m_keyPrevious & m_keyCurrent;
    m_keyReleased = m_keyPrevious & ~m_keyCurrent;
    m_keyPrevious = m_keyCurrent;
}

void CKeypad::KeyPressed(unsigned int keyIndex)
{
	ASSERT(keyIndex >= DK_NUM1_INDEX && keyIndex < DEVICE_KEY_COUNT);
	int mask = ID_TO_MASK(keyIndex);
#ifdef KEY_FIX_PULSE_PRESS
	m_keyPreviousPulse &= ~mask;
#endif

#ifdef KEY_SUPPORT_SIMULTANEOUS_PRESS
    m_keyCurrent |= mask;
#else
//    if (m_keyCurrent == 0)
        m_keyCurrent = mask;
//    else
//        return;
#endif

#ifdef KEY_SUPPORT_DOUBLEPRESS
	unsigned int fc = GetEngine().GetFrameCounter();
    m_pressInterval[keyIndex] = fc - m_pressLastTime[keyIndex];
    m_pressLastTime[keyIndex] = fc;
#endif
}

void CKeypad::KeyReleased(unsigned int keyIndex)
{
	ASSERT(keyIndex >= DK_NUM1_INDEX && keyIndex < DEVICE_KEY_COUNT);
	unsigned int mask = ID_TO_MASK(keyIndex);

#ifdef KEY_FIX_PULSE_PRESS
	if(!(mask & m_keyPrevious))
	{
		m_keyCurrentPulse |= mask;
		return;
	}
#endif
	
#ifdef KEY_SUPPORT_SIMULTANEOUS_PRESS
    m_keyCurrent &= ~mask;
#else
    if (m_keyCurrent == mask)
        m_keyCurrent = 0;
#endif
}

#ifdef KEY_SUPPORT_DOUBLEPRESS

bool CKeypad::IsKeyDoublePressed(unsigned int gameKey)
{
    unsigned int deviceKey;
    for (int i = 0; i < DEVICE_KEY_COUNT; i++)
    {
        deviceKey = ID_TO_MASK(i);
        if ((deviceKey & gameKey) && IsKeyPressed(deviceKey))
        {
            return m_pressInterval[i] < m_doublePressInterval;
        }
    }
    return false;
}
#endif
#else//USE_OLD_KEY_CONTROL

#include "..\Game\Game.h"
#include "..\Game\CSprite.h"
#include "..\Game\CActor.h"
extern CGame* g_pGame;


void CKeypad::Update()
{
	if (s_keyPressed != 0)
	{
		s_keyPrev = s_keyPressed;
		s_keyPrevFrame = 0;
	}
	if(s_keyReleased != 0)
	{
		s_keyHoldFrame = -1;
	}
	s_keyPrevFrame++;
	//        System.out.println("s_keyPrevFrame" + s_keyPrevFrame);

	if (s_keyHold != s_keyCurrent || s_keyHold == 0)
	{
		if(g_pGame->s_assassin != NULL)
			if((g_pGame->s_assassin->_nCrtAnim == ANIM::HERO_A_JUMP_FORWARD
				|| g_pGame->s_assassin->_nCrtAnim == ANIM::HERO_A_JUMP_VERTICALLY)
				&& s_keyHoldFrame >= 0)
			{
				if(s_keyHoldFrame <= 2)

					g_pGame->s_assShortJump = true;
				else
					g_pGame->s_assShortJump = false;
			}
			//          System.out.println("s_keyHoldFrame" + s_keyHoldFrame);
			s_keyHoldFrame = -1;
	}

	if (s_keyHold != 0)
	{
		s_keyHoldFrame++;
		//          System.out.println("s_keyHoldFrame" + s_keyHoldFrame);
		//          System.out.println("s_keyHold: "+s_keyHold+"s_keyPrev :"+s_keyPrev);
	}

	s_keyHold = s_keyCurrent;
	s_keyPressed = s_keyPressedRT;
	s_keyReleased = s_keyReleasedRT;
	s_keyPressedRT = 0;
	s_keyReleasedRT = 0;
}

void CKeypad::KeyPressed(unsigned int  keyCode)
{	
	s_keyPressedRT |= ID_TO_MASK(keyCode);
	int keyCode1 = GetDeviceKey(keyCode);
	s_keyPressedRT |= keyCode1;
	if ((keyCode1&STATE::GK_LEFT)!=0)
	{
		s_keyPressedRT&=~ STATE::GK_RIGHT;
		s_keyPressedRT&=~ STATE::GK_UP;
		s_keyPressedRT&=~ STATE::GK_DOWN;
	} 
	if ((keyCode1&STATE::GK_RIGHT)!=0)
	{
		s_keyPressedRT&=~ STATE::GK_LEFT;
		s_keyPressedRT&=~ STATE::GK_UP;
		s_keyPressedRT&=~ STATE::GK_DOWN;
	} 
	if ((keyCode1&STATE::GK_UP)!=0)
	{
		s_keyPressedRT&=~ STATE::GK_LEFT;
		s_keyPressedRT&=~ STATE::GK_RIGHT;
		s_keyPressedRT&=~ STATE::GK_DOWN;
	}	
	if ((keyCode1&STATE::GK_DOWN)!=0)
	{
		s_keyPressedRT&=~ STATE::GK_LEFT;
		s_keyPressedRT&=~ STATE::GK_RIGHT;
		s_keyPressedRT&=~ STATE::GK_UP;
	}
	if ((keyCode1&STATE::GK_CENTER)!=0)
	{
		s_keyPressedRT&=~ STATE::GK_LEFT;
		s_keyPressedRT&=~ STATE::GK_RIGHT;
		s_keyPressedRT&=~ STATE::GK_DOWN;
		s_keyPressedRT&=~ STATE::GK_UP;
	}

    s_keyHold |= s_keyPressedRT;
    s_keyCurrent |= s_keyPressedRT;
}

void CKeypad::KeyReleased(unsigned int  keyCode)
{

    s_keyReleasedRT |= ID_TO_MASK(keyCode);
#ifdef Zero_Hold_Key_When_Release
    s_keyCurrent = s_keyHold = 0;
#else
    s_keyCurrent &= ~s_keyReleasedRT;
    s_keyHold &= ~s_keyReleasedRT;
#endif //#ifdef Zero_Hold_Key_When_Release

}
#endif//USE_OLD_KEY_CONTROL