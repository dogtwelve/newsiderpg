// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// \author  Qiu Guan Chen
// \author  Qiu Wei Min

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#define KEY_SUPPORT_DOUBLEPRESS
//#define KEY_SUPPORT_SIMULTANEOUS_PRESS
#define KEY_FIX_PULSE_PRESS

#include "Common.h"

#ifdef USE_OLD_KEY_CONTROL
/// @brief This class provides functions for handling keypad.
/// Ported from Beijing's Java Codelib.
class CKeypad
{
public:
	enum {
		DK_NUM1_INDEX = 0,
		DK_NUM2_INDEX,
		DK_NUM3_INDEX,
		DK_NUM4_INDEX,
		DK_NUM5_INDEX,
		DK_NUM6_INDEX,
		DK_NUM7_INDEX,
		DK_NUM8_INDEX,
		DK_NUM9_INDEX,
		DK_NUM0_INDEX,

		DK_POUND_INDEX,
		DK_STAR_INDEX,
		DK_PAD_LEFT_INDEX,
		DK_PAD_RIGHT_INDEX,
		DK_PAD_UP_INDEX,
		DK_PAD_DOWN_INDEX,
		DK_PAD_MIDDLE_INDEX,
		DK_SOFT_LEFT_INDEX,
		DK_SOFT_RIGHT_INDEX,
		DK_CLEAR_INDEX,
		
#if DEVICE == DEVICE_LGVX9800 || DEVICE == DEVICE_LGVX9400  || DEVICE == DEVICE_SAMSUNG_U740
		DK_FN_INDEX,
#endif
#if PLATFORM == PLATFORM_WIN32
		DK_UNDEAD_INDEX,
		DK_FREE_INDEX,
#endif
		DEVICE_KEY_COUNT
	};

	/// Don't use these constants directly in AI.
	/// Game application must redefine key code for portability and flexibility
	enum GameKey{

		/// gameKey for ITU-T key 1.
		DK_NUM1 = 1 << DK_NUM1_INDEX,
		/// gameKey for ITU-T key 2.
		DK_NUM2 = 1 << DK_NUM2_INDEX,
		/// gameKey for ITU-T key 3.
		DK_NUM3 = 1 << DK_NUM3_INDEX,
		/// gameKey for ITU-T key 4.
		DK_NUM4 = 1 << DK_NUM4_INDEX,
		/// gameKey for ITU-T key 5.
		DK_NUM5 = 1 << DK_NUM5_INDEX,
		/// gameKey for ITU-T key 6.
		DK_NUM6 = 1 << DK_NUM6_INDEX,
		/// gameKey for ITU-T key 7.
		DK_NUM7 = 1 << DK_NUM7_INDEX,
		/// gameKey for ITU-T key 8.
		DK_NUM8 = 1 << DK_NUM8_INDEX,
		/// gameKey for ITU-T key 9.
		DK_NUM9 = 1 << DK_NUM9_INDEX,
		/// gameKey for ITU-T key 0.
		DK_NUM0 = 1 << DK_NUM0_INDEX,
// #endif
		/// gameKey for ITU-T key "pound" (#).
		DK_POUND = 1 << DK_POUND_INDEX,
		/// gameKey for ITU-T key "star" (*).
		DK_STAR = 1 << DK_STAR_INDEX,
		/// gameKey for the LEFT key on navigation pad.
		DK_PAD_LEFT = 1 << DK_PAD_LEFT_INDEX,
		/// gameKey for the RIGHT key on navigation pad.
		DK_PAD_RIGHT = 1 << DK_PAD_RIGHT_INDEX,
		/// gameKey for the UP key on navigation pad.
		DK_PAD_UP = 1 << DK_PAD_UP_INDEX,
		/// gameKey for the DOWN key on navigation pad.
		DK_PAD_DOWN = 1 << DK_PAD_DOWN_INDEX,
		/// gameKey for the MIDDLE key on navigation pad.
		DK_PAD_MIDDLE = 1 << DK_PAD_MIDDLE_INDEX,
		/// gameKey for the left soft key.
		DK_SOFT_LEFT = 1 << DK_SOFT_LEFT_INDEX,
		/// gameKey for the right soft key.
		DK_SOFT_RIGHT = 1 << DK_SOFT_RIGHT_INDEX,
		///
		DK_CLEAR = 1 << DK_CLEAR_INDEX,

#if DEVICE == DEVICE_LGVX9800 || DEVICE == DEVICE_LGVX9400 || DEVICE == DEVICE_SAMSUNG_U740
		DK_FN = 1 << DK_FN_INDEX,
#endif
#if PLATFORM == PLATFORM_WIN32
		DK_FREE = 1 << DK_FREE_INDEX,
		DK_UNDEAD = 1 << DK_UNDEAD_INDEX,
#endif
	};


	CKeypad();
	virtual ~CKeypad();
	void KeyReleased(unsigned int keyIndex);
	void KeyPressed(unsigned int keyIndex);

	/// @brief Clear all stored keys. It is used when resuming from interrupt.
	void ClearKey();
	
	void ClearKey(int clearKey);

	/// @brief Update device key information.
	///
	/// It should be called at the beginning of every frame.
	void Update();

	/// @brief Check if a game key is hold currently.
	/// @param gameKey The game key to be checked
	/// @return The checked result
	bool IsKeyHold(unsigned int gameKey) {return (m_keyCurrent & gameKey) != 0;}

    /// @brief Check if a game key is pressed currently.
    /// @param gameKey The game key to be checked
    /// @return The checked result
    bool IsKeyPressed(unsigned int gameKey) {return (m_keyPressed & gameKey) != 0;}

    /// @brief Check if a game key is activated currently.
	///
    /// "activated" means it is hold or pressed. The result is equal to "IsKeyHold(gameKey) | IsKeyPressed(gameKey)".
    /// @param gameKey The game key to be checked
    /// @return The checked result
    bool IsKeyActivated(unsigned int gameKey) {return ((m_keyCurrent | m_keyPressed) & gameKey) != 0;}

    /// @brief Check if a game key is released currently.
    /// @param gameKey The game key to be checked
    /// @return The checked result
    bool IsKeyReleased(unsigned int gameKey) { return (m_keyReleased & gameKey) != 0; }

#ifdef KEY_SUPPORT_DOUBLEPRESS
	/// @brief Check if a game key is currently double pressed.
	/// @param gameKey the game key to be checked
	/// @return The checked result
	bool IsKeyDoublePressed(unsigned int gameKey);
#endif

	/// @brief Check if any key is hold currently.
	/// @return The checked result
    bool IsAnyKeyHold() { return m_keyCurrent != 0; }

	/// @brief Check if any key is pressed currently.
	/// @return The checked result
    bool IsAnyKeyPressed() { return m_keyPressed != 0; }
	
	/// @brief Get CurrentKey Value
	/// @return the CurrentKey 
	int GetCurrentKey() { return m_keyCurrent;}
	int GetCurrentPressedKey() { return m_keyPressed; }

protected:
    /// The device keys being hold currently.
    unsigned int m_keyCurrent;
    /// The device keys being hold at the last frame.
    unsigned int m_keyPrevious;
    /// The device keys being pressed since the last frame.
    unsigned int m_keyPressed;
    /// The device keys being released since the last frame.
    unsigned int m_keyReleased;

#ifdef KEY_FIX_PULSE_PRESS
	/// Keys that are pressed and reseased in one frame
	unsigned int m_keyCurrentPulse, m_keyPreviousPulse;
#endif

#ifdef KEY_SUPPORT_DOUBLEPRESS
    /// When is each key being pressed last time? The measure is millisecond.
    unsigned int m_pressLastTime[DEVICE_KEY_COUNT];
	/// How long is it since each key has been pressed last time? The measure is millisecond.
    unsigned int m_pressInterval[DEVICE_KEY_COUNT];
	/// The allowed maximum interval of twice press of a single key, if it is millisecond.
    unsigned int m_doublePressInterval;
#endif
};
#else//USE_OLD_KEY_CONTROL

class CKeypad
{
public:
	enum {
		DK_NUM1_INDEX = 0,
		DK_NUM2_INDEX,
		DK_NUM3_INDEX,
		DK_NUM4_INDEX,
		DK_NUM5_INDEX,
		DK_NUM6_INDEX,
		DK_NUM7_INDEX,
		DK_NUM8_INDEX,
		DK_NUM9_INDEX,
		DK_NUM0_INDEX,

		DK_POUND_INDEX,
		DK_STAR_INDEX,
		DK_PAD_LEFT_INDEX,
		DK_PAD_RIGHT_INDEX,
		DK_PAD_UP_INDEX,
		DK_PAD_DOWN_INDEX,
		DK_PAD_MIDDLE_INDEX,
		DK_SOFT_LEFT_INDEX,
		DK_SOFT_RIGHT_INDEX,
		DK_CLEAR_INDEX,
		
#if DEVICE == DEVICE_LGVX9800 || DEVICE == DEVICE_LGVX9400 || DEVICE == DEVICE_LGVX10000 || DEVICE == DEVICE_SAMSUNG_U740
		DK_FN_INDEX,
#endif
#if PLATFORM == PLATFORM_WIN32
		DK_UNDEAD_INDEX,
		DK_FREE_INDEX,
#endif
		DEVICE_KEY_COUNT
	};

	/// Don't use these constants directly in AI.
	/// Game application must redefine key code for portability and flexibility
	enum GameKey{
		/// gameKey for ITU-T key 1.
		DK_NUM1 = 1 << DK_NUM1_INDEX,
		/// gameKey for ITU-T key 2.
		DK_NUM2 = 1 << DK_NUM2_INDEX,
		/// gameKey for ITU-T key 3.
		DK_NUM3 = 1 << DK_NUM3_INDEX,
		/// gameKey for ITU-T key 4.
		DK_NUM4 = 1 << DK_NUM4_INDEX,
		/// gameKey for ITU-T key 5.
		DK_NUM5 = 1 << DK_NUM5_INDEX,
		/// gameKey for ITU-T key 6.
		DK_NUM6 = 1 << DK_NUM6_INDEX,
		/// gameKey for ITU-T key 7.
		DK_NUM7 = 1 << DK_NUM7_INDEX,
		/// gameKey for ITU-T key 8.
		DK_NUM8 = 1 << DK_NUM8_INDEX,
		/// gameKey for ITU-T key 9.
		DK_NUM9 = 1 << DK_NUM9_INDEX,
		/// gameKey for ITU-T key 0.
		DK_NUM0 = 1 << DK_NUM0_INDEX,
// #endif
		/// gameKey for ITU-T key "pound" (#).
		DK_POUND = 1 << DK_POUND_INDEX,
		/// gameKey for ITU-T key "star" (*).
		DK_STAR = 1 << DK_STAR_INDEX,
		/// gameKey for the LEFT key on navigation pad.
		DK_PAD_LEFT = 1 << DK_PAD_LEFT_INDEX,
		/// gameKey for the RIGHT key on navigation pad.
		DK_PAD_RIGHT = 1 << DK_PAD_RIGHT_INDEX,
		/// gameKey for the UP key on navigation pad.
		DK_PAD_UP = 1 << DK_PAD_UP_INDEX,
		/// gameKey for the DOWN key on navigation pad.
		DK_PAD_DOWN = 1 << DK_PAD_DOWN_INDEX,
		/// gameKey for the MIDDLE key on navigation pad.
		DK_PAD_MIDDLE = 1 << DK_PAD_MIDDLE_INDEX,
#ifdef USE_KDDI
		///change by liuzhen
		DK_SOFT_LEFT = 1 << DK_SOFT_RIGHT_INDEX,
		/// gameKey for the right soft key.
		DK_SOFT_RIGHT = 1 << DK_SOFT_LEFT_INDEX,
#else
		///change by liuzhen
		DK_SOFT_LEFT = 1 << DK_SOFT_LEFT_INDEX,
		/// gameKey for the right soft key.
		DK_SOFT_RIGHT = 1 << DK_SOFT_RIGHT_INDEX,
#endif
		///
		DK_CLEAR = 1 << DK_CLEAR_INDEX,

#if DEVICE == DEVICE_LGVX9800 || DEVICE == DEVICE_LGVX9400 || DEVICE == DEVICE_LGVX10000 || DEVICE == DEVICE_SAMSUNG_U740
		DK_FN = 1 << DK_FN_INDEX,
#endif
#if PLATFORM == PLATFORM_WIN32
		DK_FREE = 1 << DK_FREE_INDEX,
		DK_UNDEAD = 1 << DK_UNDEAD_INDEX,
#endif
	};

	void Update();

	void KeyPressed(unsigned int  keyCode);
//    {	
//		s_keyPressedRT |= GID_TO_MASK(keyCode);
//
//        s_keyHold |= s_keyPressedRT;
//        s_keyCurrent |= s_keyPressedRT;
//    }
//
	void KeyReleased(unsigned int  keyCode);
//    {
//
//        s_keyReleasedRT |= GID_TO_MASK(keyCode);
//        s_keyCurrent &= ~s_keyReleasedRT;
//        s_keyHold &= ~s_keyReleasedRT;
////        s_keyHoldFrame = -1;
//    }

	void StoreAnyKeyPressed()
    {
        if (s_keyPressed != 0)
        {
            s_keyPressedInStore = s_keyPressed;
        }
    }

    bool IsKeyPressedInStore(int gameKey)
    {
        return (s_keyPressedInStore & gameKey) != 0;
    }

    void ClearKeyPressedInStore()
    {
        s_keyPressedInStore = 0;
    }

    bool IsKeyHold(int gameKey)
    {
        return (s_keyHold & gameKey) != 0;
    }
    bool IsKeyOnlyHold(int gameKey)
    {
        return (s_keyHold & gameKey) != 0 && (s_keyHold & ~gameKey) == 0;
    }
    
    bool IsKeyPressed(int gameKey)
    {
        return (s_keyPressed & gameKey) != 0;
    }

    bool IsKeyReleased(int gameKey)
    {
        return (s_keyReleased & gameKey) != 0;
    }

    bool IsKeyDoublePressed(int gameKey)
    {
        return ((s_keyPressed & gameKey) != 0 && s_keyPressed == s_keyPrev && s_keyPrevFrame < 5);
    }

    bool IsAnyKeyHold()
    {
        return (s_keyHold & 0x1FFFF) != 0;
    }

    bool IsAnyKeyPressed()
    {
        return s_keyPressed != 0;
    }

    void ClearKey()
    {
        s_keyCurrent = 0;
        s_keyHold = 0;
        s_keyPressed = 0;
        s_keyReleased = 0;
        s_keyPressedRT = 0;
        s_keyReleasedRT = 0;
        s_keyPressedInStore = 0;
    }
	int GetCurrentKey() { return s_keyCurrent;}


protected:

    unsigned int s_keyPressed;

    unsigned int s_keyPressedRT;

    unsigned int s_keyPressedInStore;

	unsigned int s_keyCurrent;

    unsigned int s_keyHold;

    unsigned int s_keyHoldFrame;
    
    unsigned int s_keyReleased;

    unsigned int s_keyReleasedRT;

    unsigned int s_keyPrev;

    unsigned int s_keyPrevFrame;



};

#endif //USE_OLD_KEY_CONTROL
#endif