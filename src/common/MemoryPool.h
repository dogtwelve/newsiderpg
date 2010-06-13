// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

#include "Common.h"
#include "..\wipi\brewtowipi.h" //++sj

#ifdef AEE_SIMULATOR
// debug stuff
typedef enum
{
	CHECK_NONE,
		CHECK_PER_FRAME,
		CHECK_PER_CALL,
} MemCheckType ;
#endif

class CMemoryPool{
public:
	CMemoryPool();
	virtual ~CMemoryPool();

	bool Open(int size);
	void Close();

	void* AllocateBottom(unsigned int length);
	void* AllocateTop(unsigned int length);

	void FreeBottom(void* p) {
		ASSERT((char*)p == *((char**)m_currentBottom - 1));
		m_currentBottom = (char*)p;
	}

	void FreeTop(void* p) {
		ASSERT(p == m_currentTop + 4);
		m_currentTop = *(char**)m_currentTop;
	}

	bool Free(void* p);

	int GetMinimunFree() {
		return m_minFree;
	}
	
	int GetFreeMem() {
		return m_currentTop - m_currentBottom;
	};

	void* GetTop() {
		return m_currentTop;
	}

	void SetTop(void* top) {
		char *p = (char*)top;
		ASSERT(p >= m_buffer && p < m_buffer + m_length);
		m_currentTop = p;
	}

	void* GetBottom() {
		return m_currentBottom;
	}

	void SetBottom(void* bottom) {
		char *p = (char*)bottom;
		ASSERT(p >= m_buffer && p < m_buffer + m_length);
		m_currentBottom = p;
	}
	
	void ResetTop(){
		m_currentTop = m_buffer + m_length;
		m_minFree = m_currentTop - m_currentBottom;
		MEMSET(m_currentBottom, 0, m_minFree);
	}

	void ResetButtom(){
		m_currentBottom = m_buffer;
		m_minFree = m_currentTop - m_currentBottom;
		MEMSET(m_currentBottom, 0, m_minFree);	
	}

	bool IsEmpty() {
		return m_currentTop == m_buffer + m_length && m_currentBottom == m_buffer;
	}

	bool IsInTop(void *p) {
		char *c = (char*)p;
		return c >= m_currentTop && c < m_buffer + m_length;
	}

	bool IsInBottom(void *p) {
		char *c = (char*)p;
		return c >= m_buffer && c < m_currentBottom;
	}

	unsigned int GetPoolSize() {
		return m_length;
	}

#ifdef AEE_SIMULATOR
	// debug stuff
	static MemCheckType	checkType;
	static void* _top_pointers[MEMORY_POOL_TOTAL];
	static void* _bottom_pointers[MEMORY_POOL_TOTAL];
	static char _last_alloc_file[512];
	static int _last_alloc_line;
	static void Check( char* file, int line );
	static void SetCheck( MemCheckType type );
#endif

private:
	CMemoryPool& operator=(const CMemoryPool& rhs);
	unsigned int m_length;
	char *m_buffer;
	char *m_currentTop;
	char *m_currentBottom;
	int m_minFree;
};
#endif