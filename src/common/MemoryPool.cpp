// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "MemoryPool.h"
#include "SysUtil.h"
#include "Engine.h"

CMemoryPool::CMemoryPool()
	:m_length(0),
	m_buffer(NULL),
	m_currentTop(NULL),
	m_currentBottom(NULL),
	m_minFree(0)
{

}

CMemoryPool::~CMemoryPool()
{
	Close();
}

/* =========================================================================

Function:  open()

Description:
   This function creates a memeory pool with size of <size>.

Parameters:
   size: Size of the pool to be created

Return Value:
   ture if the pool is created successfully

Comments:  None

   ========================================================================= */
bool CMemoryPool::Open(int size)
{
	ASSERT(size > 0);
	m_buffer = (char*)MALLOC(size);
	if(!m_buffer)
		return false;
#if DEBUG_LEVEL > 1
	// Zero initialization in BREW can hide problems in portability, so avoid this problem by filling
	// dummy value.
	MEMSET(m_buffer, 0xCC, size);
#endif
	m_length = size;
	m_currentBottom = m_buffer;
	m_currentTop = m_buffer + m_length;
	
	m_minFree = m_currentTop - m_currentBottom;
	return true;
}


void CMemoryPool::Close()
{
	if(m_buffer)
	{
		FREE(m_buffer);
		m_buffer = NULL;
	}
}


void* CMemoryPool::AllocateBottom(unsigned int length)
{
	char *p;

	//align the length to multiple of 4
	length = (length + 3 ) & ~3;
	p = m_currentBottom + length;
	
	ASSERT(p + 4 <= m_currentTop);

	//store
	*(char**)p = m_currentBottom;
	char *p2 = m_currentBottom;
	m_currentBottom = p + 4;
	
	//save usage info
	if(m_minFree > m_currentTop - m_currentBottom)
		m_minFree = m_currentTop - m_currentBottom;

	MEMSET(p2, 0, length);

	return p2;
}

void* CMemoryPool::AllocateTop(unsigned int length)
{
	char *p;

	//align the length to multiple of 4
	length = (length + 3 ) & ~3;
	p = m_currentTop - length - 4;
	
	ASSERT(p >= m_currentBottom);                    

	//store 
	*(char**)p = m_currentTop;
	m_currentTop = p;
	
	//save usage info
	if(m_minFree > m_currentTop - m_currentBottom)
		m_minFree = m_currentTop - m_currentBottom;
	
	MEMSET(p + 4, 0, length);

	return p + 4;
}

bool CMemoryPool::Free(void* p)
{
	if(p == (void*)this)
		return false;
	char *p0 = (char*)p;
	if(p0 < m_buffer || p0 >= m_buffer + m_length)
		return false;
	if(p0 < m_currentBottom)
	{
		FreeBottom(p0);
	}
	else if(p0 > m_currentTop)
	{
		FreeTop(p0);
	}
	else
	{
		ASSERT(false);
	}
	return true;
}

#ifdef AEE_SIMULATOR

MemCheckType	CMemoryPool::checkType = CHECK_NONE;
void* CMemoryPool::_bottom_pointers[MEMORY_POOL_TOTAL] = {0};
void* CMemoryPool::_top_pointers[MEMORY_POOL_TOTAL] = {0};
char CMemoryPool::_last_alloc_file[512] = {0};
int CMemoryPool::_last_alloc_line = 0;

void CMemoryPool::Check( char* file, int line )
{
	ASSERT( !file || STRLEN(file) < ARRAY_SIZE(_last_alloc_file) );
	if ( checkType == CHECK_NONE ) return;

	if ( checkType == CHECK_PER_CALL )
	{
		DBGPRINTF("unexpected memory alloc at file :\n %s, line %d\ncheck the call stack for details\n", file, line);
		__asm int 3;
	}
	else if ( checkType == CHECK_PER_FRAME && file == NULL )
	{
		bool check_succeed = true;
		for ( int i = 0; i < MEMORY_POOL_TOTAL * 2; i ++)
		{
			if( i % 2 == POOL_BOTTOM )
			{
				if( _bottom_pointers[ i/2 ] != GetEngine().GetMemoryPool( i / 2)->GetBottom() )
				{
					check_succeed = false;
				}
			}
			else
			{
				if( _top_pointers[ i/2 ] != GetEngine().GetMemoryPool( i / 2)->GetTop() )
				{
					check_succeed = false;
				}
			}
			if( !check_succeed )
			{
				DBGPRINTF("unexpected memory alloc at file :\n %s, line %d", 
					_last_alloc_file, _last_alloc_line);
				__asm int 3;
				
				break;
			}
		}
	}

	if ( file )
	{
		STRCPY( _last_alloc_file, file );
		_last_alloc_line = line;
	}
}



void CMemoryPool::SetCheck( MemCheckType type )
{
	checkType = type;

	for ( int i = 0; i < MEMORY_POOL_TOTAL * 2; i++)
	{
		if( i % 2 == POOL_BOTTOM )
		{
			_bottom_pointers[ i/2 ] = GetEngine().GetMemoryPool( i / 2)->GetBottom();
		}
		else
		{
			_top_pointers[ i/2 ] = GetEngine().GetMemoryPool( i / 2)->GetTop();
		}
	}
}


#endif
