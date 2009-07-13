//#include "build.h"
//#include "Brew\Brew.h"
#include "memory.h"
#include "engine.h"
//#include "..\Includes\defines.h"
#ifdef MY_DEBUG
//#ifdef AEE_SIMULATOR
//#include <crtdbg.h>  --sj
//-----------------sj;;;;;;
//#undef MALLOC
//#if (AEE_DBG_HEAP==1)
//#define MALLOC(size,file,line)	_malloc_dbg(size, _CRT_BLOCK, NULL, NULL)
//#else
//#define MALLOC(size)	_malloc_dbg(size, _CRT_BLOCK, NULL, NULL)
//#endif
//
//#undef FREE
//#define FREE(p)		_free_dbg(p, _CRT_BLOCK)
//
//#undef REALLOC		
//#define REALLOC(p,size)             _realloc_dbg(p, size, _CRT_BLOCK, NULL, NULL)
//#endif
#else
//#ifdef AEE_SIMULATOR
//#include "AEEHeap.h"
//
//#undef MALLOC
//#if (AEE_DBG_HEAP==1)
//#define MALLOC(size,file,line)	_malloc_dbg(size, _CRT_BLOCK, NULL, NULL)
//#else
//#define MALLOC(size)	_malloc_dbg(size, _CRT_BLOCK, NULL, NULL)
//#endif
//
//#undef FREE
//#define FREE(p)		_free_dbg(p, _CRT_BLOCK)
//
//#undef REALLOC		
//#define REALLOC(p,size)             _realloc_dbg(p, size, _CRT_BLOCK, NULL, NULL)
//#endif
#endif

#ifdef AEE_SIMULATOR
struct sMemNode{
    void * ptr;
    int size;
    sMemNode * pNext;

    char * file;
    int line;
	signed long memId;  //ADD sj 1103
};


extern int s_curr_mem = 0;
static sMemNode * root = NULL;

void SavePtr(void* ptr,int size,char * file,int line){
    if(!ptr)return;

    sMemNode* pNew = (sMemNode *)MALLOC(sizeof(sMemNode));
    MEMSET(pNew,0,sizeof(sMemNode));

    pNew->ptr = ptr;
    pNew->size = size;

    pNew->file = file;
    pNew->line = line;

    s_curr_mem += size+24;

	pNew->memId = *((signed long *)ptr - 2);

#ifdef MEMORY_OUTPUT
	DBGPRINTF(" ++curr mamID : %d   mem : %d   this malloc : %d \tFILE:%s  LINE:%d \n",pNew->memId , s_curr_mem,size,file,line);
#endif

    if(!root){
        root = pNew;
        return;
    }

    sMemNode* p = root;
    while(p->pNext){
        p = p->pNext;
    }
    p->pNext = pNew;

}

void DelPtr(void * ptr){
    if(!ptr || !root)return;

    sMemNode* p = root;
    sMemNode* pre = NULL;
    while(p){
        if( p->ptr == ptr)
            break;
        pre = p;
        p = p->pNext;
    }
    if(!p)
        return;
    if(pre==NULL){
        root = p->pNext;
    }else{
        pre->pNext = p->pNext;
    }
    s_curr_mem -= p->size;
#ifdef MEMORY_OUTPUT
    DBGPRINTF(" --current mamID : %d   mem : %d   this free : %d \tFILE:%s  LINE:%d \n",p->memId , s_curr_mem,p->size,p->file,p->line);
#endif
    FREE(p);
}

void dump_memory(){
    DBGPRINTF("*************************begine dump memory**************************************** \n");
    if(!root){
        DBGPRINTF(" no memory leak! :) \n");
    }
    else{
        sMemNode* p = root;
        while(p){
            DBGPRINTF("size:%d   \tFILE:%s    LINE:%d \n",p->size,p->file,p->line);
            p = p->pNext;
        }
    }
    DBGPRINTF("*************************end of dump memory**************************************** \n");
}

void* operator new(unsigned int size,char* f,int l)
{ 
    if(size == 0)
        return 0;

    void* ptr = MALLOC(size);

    ASSERT(ptr);

    if(!ptr)
        return 0;
    
    MEMSET(ptr, 0, size);
#if defined AEE_SIMULATOR && defined DEGUG_MEMORY
    SavePtr(ptr,size,f,l);
#endif
    return ptr;
}

void* operator new[](unsigned int size,char *f,int l)
{
    if(size == 0)
        return 0;

    void* ptr = MALLOC(size);
    
    ASSERT(ptr);

    if(!ptr)
        return 0;
    
    MEMSET(ptr, 0, size);
#if defined AEE_SIMULATOR && defined DEGUG_MEMORY
    SavePtr(ptr,size,f,l);
#endif
    return ptr;
}


void operator delete(void* ptr,char *f,int l)
{
#if defined AEE_SIMULATOR && defined DEGUG_MEMORY
    DelPtr(ptr);
#endif
    FREE(ptr);
}

void operator delete[](void* ptr,char *f,int l)
{
#if defined AEE_SIMULATOR && defined DEGUG_MEMORY
    DelPtr(ptr);
#endif
    FREE(ptr);
}


#endif //#ifdef AEE_SIMULATOR

void* operator new(unsigned int size)
{ 
	void *p = MALLOC(size);
	MEMSET(p, 0, size);
	return p;

//	if(size == 0)
//        return 0;
//
//    void* ptr = MALLOC(size);
//    if(!ptr)
//        return 0;
//    ASSERT(ptr);
//    MEMSET(ptr, 0, size);
////#ifdef AEE_SIMULATOR
//#if defined  AEE_SIMULATOR && defined DEGUG_MEMORY
//    //SavePtr(ptr,size);
//#endif
//    return ptr;
}

void* operator new[](unsigned int size)
{
	void *p = MALLOC(size);
	MEMSET(p, 0, size);
	return p;

//    if(size == 0)
//        return 0;
//
//    void* ptr = MALLOC(size);
//    if(!ptr)
//        return 0;
//    ASSERT(ptr);
//    MEMSET(ptr, 0, size);
////#ifdef AEE_SIMULATOR
//#if defined  AEE_SIMULATOR && defined DEGUG_MEMORY
//   // SavePtr(ptr,size);
//#endif
//    return ptr;
}




void operator delete(void* ptr)
{
#if defined  AEE_SIMULATOR && defined DEGUG_MEMORY
   DelPtr(ptr);
#endif 
	FREE(ptr);
}

void operator delete[](void* ptr)
{
#if defined  AEE_SIMULATOR && defined DEGUG_MEMORY
    DelPtr(ptr);
#endif 
	FREE(ptr);   
}

