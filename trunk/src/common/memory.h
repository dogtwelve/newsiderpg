#ifndef __MEMORY_H__
#define __MEMORY_H__


//#define SAFE_DEL(p)					{ if (p) { delete (p); p = NULL; } }
//#define SAFE_DEL_ARRAY(p)			{ if (p) { delete[] (p); p = NULL; } }
#define SAFE_DEL_ARRAY_OBJ(p, n)	{ if (p) { for (int __i = 0; __i < n; __i++) SAFE_DEL((p)[__i]); delete[] (p); p = NULL; } }
#define SAFE_DEL_ARRAY_ARRAY(p, n)	{ if (p) { for (int __i = 0; __i < n; __i++) SAFE_DEL_ARRAY((p)[__i]); delete[] (p); p = NULL; } }

#define SAFE_DEL_TYPE(p,t)			{ if ((t)p) { delete ((t)p); p = NULL; } }
#define SAFE_DEL_ARRAY_TYPE(p,t)	{ if ((t)p) { delete[] ((t)p); p = NULL; } }

#define SAFE_NEW_RET(p,t,s)			{ p = new t[s]; if ((p) == NULL) { return FALSE; } }
#define SAFE_NEW_CLEAN(p,t,s)		{ p = new t[s]; if ((p) != NULL) MEMSET((u8*)(p), 0, (s)*(sizeof(t))); }
#define SAFE_NEW_CLEAN_RET(p,t,s)	{ p = new t[s]; if ((p) == NULL) { return FALSE; } MEMSET((u8*)(p), 0, (s)*(sizeof(t))); }

#define CHECK_ALLOC(p)				{ if ((p) == NULL) return -1; }
#define CHECK_RESULT(f)				{ if ((f) < 0) return -1; }

#ifdef AEE_SIMULATOR

    #define debug_new new(__FILE__,__LINE__)

    void* operator new(unsigned int size,char * file,int line);
    void* operator new[](unsigned int size,char * file ,int line); 

    void operator delete(void* ptr,char * file,int line);
    void operator delete[](void* ptr,char * file,int line);

    void dump_memory();
#endif

void* operator new(unsigned int size);
void* operator new[](unsigned int size);


void operator delete(void* ptr);
void operator delete[](void* ptr);



#define SAFE_DEL(a)				{if(a){delete (a);a=NULL;}}
#define SAFE_DEL_ARRAY(a)		{if(a){delete [] (a);a=NULL;}}


#endif //__MEMORY_H__