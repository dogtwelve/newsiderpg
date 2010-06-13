// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "Engine.h"
#include "ResourceManager.h"
#include "Memory.h"
#include "Device.h"
#include "Stream.h"
#include "Graphics.h"
#include "Keypad.h"
#include "Sound.h"

//void* operator new(unsigned int size)
//{
//	void *p = MALLOC(size);
//	MEMSET(p, 0, size);
//	return p;
//}

//void* operator new[](unsigned int size)
//{
//	return operator new(size);
//}

/// @ingroup Global
/// @brief This operator attempts to dynamically allocate one or more objects from pool or heap.
/// @attention Don't use this operator directly, please use #GL_NEW, #NEW_TOP, #NEW_BOTTOM,
/// #SAFE_DELETE, #SAFE_DELETE_ARRAY instead.
/// @param[in] size	Size of the object to allocate.
/// @param[in] memType	Type of the memory to allocate.
/// @return pointer to allocated memory, or NULL if failed.
//void* operator new(unsigned int size, MemoryType memType)
//{
//	if(size == 0)
//		return NULL;
//
//	if(memType == DYNAMIC)
//		return MALLOC(size);
//
//	ASSERT(memType / 2 < MEMORY_POOL_TOTAL);
//	if(memType % 2 == POOL_BOTTOM)
//		return 	GetEngine().GetMemoryPool(memType / 2)->AllocateBottom(size);
//	else
//		return 	GetEngine().GetMemoryPool(memType / 2)->AllocateTop(size);
//}

//void* operator new[](unsigned int size, MemoryType memType)
//{
//	return operator new(size, memType);
//}
/// @ingroup Global
/// @brief This operator attempts to free one or more objects in pool or heap.
///
/// This delete operator can find out the memory type of the object, and free it properly.
/// @attention Don't use this operator directly, please use #GL_NEW, #NEW_TOP, #NEW_BOTTOM,
/// #SAFE_DELETE, #SAFE_DELETE_ARRAY instead.
/// @param[in] p	Pointer to the object to be freed.
//void operator delete(void *p)
//{
//	if(!p)
//		return;
//
//	for(int i = 0; i < MEMORY_POOL_TOTAL; i++)
//	{
//		CMemoryPool *pMemory = GetEngine().GetMemoryPool(i);
//		if(pMemory && pMemory->Free(p))
//			return;
//	}
//	FREE(p);
//}

//no use, just overload to remove compiler warning
//void operator delete(void *p, MemoryType memType)
//{
//	operator delete(p);
//}
//
//void operator delete[](void *p)
//{
//	operator delete(p);
//}
//
////no use, just overload to remove compiler warning
//void operator delete[](void *p, MemoryType memType)
//{
//	operator delete[](p);
//}

MemoryType GetMemoryType(void *p)
{
	//for(int i = 0; i < MEMORY_POOL_TOTAL; i++)
	//{
	//	CMemoryPool *pMemory = GetEngine().GetMemoryPool(i);
	//	if(pMemory)
	//	{
	//		if(pMemory->IsInBottom(p))
	//			return (MemoryType)(i * 2);
	//		else if(pMemory->IsInTop(p))
	//			return (MemoryType)(i * 2 + 1);
	//	}
	//}
	return DYNAMIC;
}

CEngine::CEngine():
	m_device(NULL),
	m_math(NULL),
	m_keypad(NULL),
	m_resourceManager(NULL),
	m_defaultResFile(NULL),
	m_sound(NULL),
	m_frameCounter(0)
{
	for(int i = 0; i < MEMORY_POOL_TOTAL; i++)
		m_memoryPool[i] = NULL;
	/*pos_touch_x = NONE_VALUE_CLICK;
	pos_touch_y = NONE_VALUE_CLICK;
	pos_touch_status = MY_EVT_PEN_UP;*/
}

CEngine::~CEngine()
{
	//make sure Finalize is called
	//minh_dang move it
	if(m_sound)
	{
		for(int i=0; i<50; i++)
		{
			SAFE_DEL_ARRAY(m_sound->m_pData[i]);
		}
	}
	SAFE_DEL(m_sound);
//	SAFE_DEL(m_touchkit);
	SAFE_DEL(m_device);
	SAFE_DEL(m_math);
	SAFE_DEL(m_keypad);
	SAFE_DEL(m_resourceManager);
	SAFE_DEL(m_defaultResFile);
	ASSERT(m_resourceManager == NULL);
	ASSERT(m_defaultResFile == NULL);
	ASSERT(m_device == NULL);
}

CEngine::ERROR_TYPE CEngine::Initialize()
{	
	//init memory 
	//for(int i = 0; i < MEMORY_POOL_TOTAL; i++)
	//{
	//	m_memoryPool[i] = (GL_NEW CMemoryPool());
	//	if(!m_memoryPool[i] ||
	//		!m_memoryPool[i]->Open(kDefaultPoolSize[i]))
	//	{
	//		CEngine::Finalize();
	//		return E_INSUFFICIENT_MEMORY;
	//	}
	//}

	//init device
	m_device = (GL_NEW /*(GLOBAL_BOTTOM) */CDevice());
	if(!m_device->Open())
	{
		CEngine::Finalize();
		return E_OTHERS;
	}

//	m_math = GL_NEW/*(GLOBAL_BOTTOM)*/ CFMath();
	m_keypad = (GL_NEW/*(GLOBAL_BOTTOM)*/ CKeypad());

	//m_keypad = (GL_NEW(GLOBAL_BOTTOM) CKeypad());
	//m_keypad = GL_NEW(GLOBAL_BOTTOM) CKeypad();

//	m_touchkit = GL_NEW/*(GLOBAL_BOTTOM)*/ CTouchKit();	//hw+ touch

	m_resourceManager = (GL_NEW/*(GLOBAL_BOTTOM)*/ CResourceManager());
	
	m_defaultResFile = (GL_NEW/*(GLOBAL_BOTTOM)*/ CResFile());

	if(!m_defaultResFile->Open(DEFAULT_RESOURCE_FILE))
	{
		ASSERT(false);
		CEngine::Finalize();
		return E_OTHERS;
	}

	m_resourceManager->AddResFile(m_defaultResFile);

//	m_sound = GL_NEW/*(GLOBAL_BOTTOM)*/ CSound();
#if SOUND_LEVEL == 0	
	//m_sound = (GL_NEW/*(GLOBAL_BOTTOM)*/ CSoundPlayer());  --sj
	m_sound = (GL_NEW/*(GLOBAL_BOTTOM)*/ CMediaPlayer()); //++sj
#elif SOUND_LEVEL == 1	
	m_sound = (GL_NEW/*(GLOBAL_BOTTOM)*/ CMediaPlayer());
#elif SOUND_LEVEL == 2	
	m_sound = (GL_NEW/*(GLOBAL_BOTTOM)*/ CMultiMediaPlayer());
#endif

	if( !m_sound->Init()/* && !m_sound->Init2()*/ )
	{
		ASSERT(false);
		CEngine::Finalize();
		return E_OTHERS;
	}

	return E_SUCCESS;
}

void CEngine::Finalize()
{
	int i;
	//minh_dang move it
	if(m_sound)
	{
		for(int i=0; i<50; i++)
		{
			SAFE_DEL_ARRAY(m_sound->m_pData[i]);
		}
	}
	SAFE_DELETE(m_sound);
	if(m_resourceManager)
		m_resourceManager->RemoveResFile(m_defaultResFile);
	
	SAFE_DELETE(m_defaultResFile);
	SAFE_DELETE(m_resourceManager);
	SAFE_DELETE(m_keypad);
	SAFE_DELETE(m_device);

	for(i = 0; i < MEMORY_POOL_TOTAL; i++)
	{
		if(m_memoryPool[i])
		{
			SAFE_DELETE(m_memoryPool[i]);
		}
	}
}

void CEngine::OnTimer()
{
	++m_frameCounter;
	
	if(GETTIMEMS() - m_timer > 1000)
	{
		m_nFPS = m_frameCounter;
		m_frameCounter = 0;
		m_timer = GETTIMEMS();
	}	
	
	Update();
}

void CEngine::OnSuspend()
{
}

void CEngine::OnResume()
{
}

bool CEngine::OnKeyEvent(unsigned int deviceKeyCode, bool isPreseed)
{
	if(!m_keypad)
		return false;

	int idx = CDevice::KeyIndexFromDeviceKey(deviceKeyCode);

	if(idx < 0)
		return false;
	if(isPreseed)
		m_keypad->KeyPressed(idx);
	else
		m_keypad->KeyReleased(idx);
	return true;
}



void CEngine::KeyPressed (int KeyIndex)
{
	m_keypad->KeyPressed(KeyIndex);
}

void CEngine::KeyReleased (int KeyIndex)
{
	m_keypad->KeyReleased(KeyIndex);
}


//bool CEngine::OnTouchEvent(bool isDown, short x, short y)
//{
//	if (!m_touchkit) return false;
//
//	m_touchkit->set(isDown, x, y);
//
//	return true;
//}


#ifdef DEBUG_MESSAGE_EVENT
bool CEngine::OnDebugEvent(AEEEvent eCode, uint16 wParam, uint32 dwParam)
{
	if(event_db_code_index >= 500 )
		event_db_code_index = 0;
	event_db_code[event_db_code_index][0] =  eCode ;
	event_db_code[event_db_code_index][1] =  wParam ;
	event_db_code[event_db_code_index][2] =  dwParam ;
	event_db_code_index++;
		
}
#endif


void CEngine::Update()
{

	m_keypad->Update();


#ifdef AEE_SIMULATOR
//	CMemoryPool::Check( NULL, 0 );
#endif


}

void CEngine::Terminate()
{
	GetDevice().SendShutDownMessage();
}