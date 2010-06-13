// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

/// @defgroup Global Global types and functions

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Stream.h"
#include "Common.h"
#include "../brew/Device.h"
//#include "TouchKit.h"

class CResourceManager;
class BrewDevice;
class CMemoryPool;
class CStream;
class CResFile;
class CKeypad;
class CSound;
class CFMath;

/// @brief The CEngine class is the base class from which you derive a game application object.
class CEngine
{
public:
	/// @brief constant of error code
	typedef enum {
		///no error
		E_SUCCESS,
		///insufficient heap memory
		E_INSUFFICIENT_MEMORY,
		///insufficient storage memory or disk space
		E_INSUFFICIENT_STORAGE,
		///other unspecified error
		E_OTHERS
	}ERROR_TYPE;
	/*uint16 pos_touch_x ;
	uint16 pos_touch_y ;
	uint16 pos_touch_status ;*/
	CEngine();
	virtual ~CEngine();

	/// @brief Called before the first Update call to initialize game engine.
	///
	/// Override this function in derived class to prepare game variables before game loop.
	/// @attention The derived class should check storage space and return E_INSUFFICIENT_STORAGE if there's not enough
	/// disk/storage space for the game to run. If the game has memory allocation except on the default pool,
	/// the derived class should also check memory space in Initialize function and return E_INSUFFICIENT_MEMORY
	/// if not enough heap memory.
	/// @attention The overriding function must call CEngine::Initialize in the start.
	virtual ERROR_TYPE Initialize();

	/// @brief Called before exit to free resource occupied by game engine.
	///
	/// Override this function in derived class to free resource before game exit.
	/// @attention The overriding function must call CEngine::Finalize in the end.
	virtual void Finalize();

	void OnTimer();

	/// @brief Handle the suspend event sent by system.
	///
	/// Should be Overrided in derived class
	virtual void OnSuspend();

	/// @brief Handle the resume event sent by system.
	///
	/// Should be overrided in derived class
	virtual void OnResume();
//	virtual bool OnTouchEvent(bool isDown, short x, short y);	//hw+	touch

	#ifdef DEBUG_MESSAGE_EVENT
	void OnDebugEvent(AEEEvent eCode, uint16 wParam, uint32 dwParam);
	#endif

	virtual bool OnKeyEvent(unsigned int deviceKeyCode, bool isPreseed);

	virtual void KeyPressed (int KeyIndex);

	virtual void KeyReleased (int KeyIndex);


	/// @brief The entrance of game loop.
	///
	/// This function is called periodically by engine framework. The interval of calls is
	/// given by TICK_PER_FRAME in config_version.h.
	/// 
	/// Override this function in derived class to perform game loop and graphics update.
	/// @attention The overriding function must call CEngine::Update in the start.
	virtual void Update();

	/// @brief Terminate current game application.
	///
	/// When this function is called, the game application will exit after the current game loop.
	virtual void Terminate();

	/// @brief Get current frame counter.
	///
	/// The frame counter is +1 in each Update call.
	unsigned int GetFrameCounter() {
		return m_frameCounter;
	}

	/// @brief Get the CKeypad instance.
	/// @return the reference to CKeypad instance
	CKeypad& GetKeypad() {
		return *m_keypad;
	}

	/// @brief Get memory pool specified by index.
	/// @param[in] poolIndex	index of the memory pool, the index of default memory pool is MEMORY_POOL_DEFAULT
	/// @return the pointer to CMemoryPool instance
	CMemoryPool* GetMemoryPool(int poolIndex){
		ASSERT(poolIndex >= 0 && poolIndex < MEMORY_POOL_TOTAL);
		return m_memoryPool[poolIndex];
	}


	CMemoryPool *m_memoryPool[MEMORY_POOL_TOTAL];

	CDevice *m_device;
	CFMath *m_math;

	CKeypad *m_keypad;

//	CTouchKit *m_touchkit;
	CResourceManager *m_resourceManager;
	CResFile *m_defaultResFile;
	CSound *m_sound;
	unsigned int m_frameCounter;

	#ifdef DEBUG_MESSAGE_EVENT
	uint32 event_db_code[500][3] ;
	int event_db_code_index;
	#endif

	unsigned int m_timer;
	int	 m_nFPS;

private:
	CEngine& operator=(const CEngine& rhs);
};

/// @ingroup Global
/// @brief Get the global CDevice instance.
/// @warning Be careful to use these global GetXXX functions because they may need many CPU circles to get the result.
/// Cache the result if it will be used extensively in a class/function.
inline CDevice& GetDevice() {
	return *GetEngine().m_device;
}

/// @ingroup Global
/// @brief Get the global CFMath instance.
/// @warning Be careful to use these global GetXXX functions because they may need many CPU circles to get the result.
/// Cache the result if it will be used extensively in a class/function.
inline CFMath& GetMath() {
	return *GetEngine().m_math;
}

/// @ingroup Global
/// @brief Get the global CResourceManager instance.
/// @warning Be careful to use these global GetXXX functions because they may need many CPU circles to get the result.
/// Cache the result if it will be used extensively in a class/function.
inline CResourceManager& GetResourceManager() {
	return *GetEngine().m_resourceManager;
}

/// @ingroup Global
/// @brief Get the global CSound instance.
/// @warning Be careful to use these global GetXXX functions because they may need many CPU circles to get the result.
/// Cache the result if it will be used extensively in a class/function.
inline CSound& GetSound() {
	return *GetEngine().m_sound;
}




//inline CKeypad& GetKeypad() {
//	return *GetEngine().m_keypad;
//}


#endif //__ENGINE_H__
