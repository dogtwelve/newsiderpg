// Copyright (C) 2005 Gameloft. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "ResFile.h"
#include "SysUtil.h"
#include "Stream.h"
#include "LzmaDecode.h"
//#include "../Game/CGame.h"
#include "Memory.h"

CResFile::CResFile()
	:m_recordNumber(0),
	m_records(NULL),
	m_file(NULL)
{
}

CResFile::~CResFile()
{
	Close();
}

bool CResFile::Open(const char *pName)
{
	CFileStream *file = (GL_NEW/*(GetMemoryType(this))*/ CFileStream());
	if(!file->Open(pName, CRawFile::MODE_READ))
	{
		SAFE_DELETE(file);
		return false;
	}
	m_file = file;

	//verify magic number
	if (m_file->ReadIntLE() != 0x4b504c47)
	{
		SAFE_DELETE(m_file);
		return false;
	}
	m_recordNumber = m_file->ReadIntLE();
	if(m_file->GetLength() - m_file->GetPosition() < (m_recordNumber + 1) * (int)sizeof(Record))
	{
		SAFE_DELETE(m_file);
		m_recordNumber = 0;
		return false;
	}

	m_records = (GL_NEW/*(GetMemoryType(this))*/ Record[m_recordNumber + 1]);

	int i;


	for(i = 0; i < m_recordNumber + 1; i++)
	{
		m_records[i].m_hash = m_file->ReadIntLE();
		m_records[i].m_offset = m_file->ReadIntLE();
	}

	return true;
}

void CResFile::Close()
{
	SAFE_DELETE_ARRAY(m_records);
	SAFE_DELETE(m_file);
	m_recordNumber = 0;
}

void* CResFile::FindRecord(const char *pName)
{
	unsigned long h = ComputeHash(pName);
	int i, u, l;
	l = 0;
	u = m_recordNumber - 1;
	i = m_recordNumber / 2;
	while(m_records[i].m_hash != h)
	{
		if(u <= l)
		{
			//record not found
			return NULL;
		}
		if(m_records[i].m_hash > h)
			u = i - 1;
		else
			l = i + 1;
		i = (u + l) / 2;
	}
	return m_records + i;
}

unsigned long CResFile::ComputeHash(const char *s)
{
	unsigned long h=0;
	const char *p;
	for(p = s; *p ; p ++)
		h = ( h << 5 ) - h + (*p == '/' ? '\\' : *p);
	return h;
}

unsigned int CResFile::GetRecordPackedSize(void* hRecord)
{
	Record *p = (Record*)hRecord;

	ASSERT(p >= m_records && p < m_records + m_recordNumber);

	return p[1].m_offset - p[0].m_offset;
}

// Size before compression
unsigned int CResFile::GetRecordSize(void *hRecord)
{
	Record *p = (Record*)hRecord;
	m_file->SetPosition(p->m_offset);
	return m_file->ReadUIntLE();
}

#ifdef _LZMA_IN_CB
int LzmaRead(void *object, unsigned char **buffer, unsigned int *bufferSize)
{
	if(object == NULL)
		return -1;

	ILzmaInCallback* cb = (ILzmaInCallback*)object;
	CFileStream* fs = (CFileStream*)cb->mpFile;
	return fs->LzmaRead(buffer, bufferSize, cb->length);
}
#endif

unsigned int CResFile::ReadRecord(void *hRecord, void *pBuf, unsigned int len)
{
	unsigned int originalSize;
	unsigned int packedSize = GetRecordPackedSize(hRecord);
	m_file->SetPosition(((Record*)hRecord)->m_offset);
	
	packedSize -= 4;
	originalSize = m_file->ReadUIntLE();
	if(originalSize > len)
	{
		ASSERT(false);
		return 0;
	}
#ifndef _LZMA_IN_CB
	unsigned char *inBuf = NEW_BOTTOM unsigned char[packedSize];
	m_file->Read(inBuf, packedSize);
#endif

	int lc, lp, pb;
	unsigned int lzmaInternalSize;
	unsigned char *lzmaInternalData;

#ifdef _LZMA_IN_CB
	lc = m_file->ReadByte();
#else
	lc = inBuf[0];
#endif
    
    for (pb = 0; lc >= (9 * 5); pb++, lc -= (9 * 5));
    for (lp = 0; lc >= 9; lp++, lc -= 9);
	lzmaInternalSize = (LZMA_BASE_SIZE + (LZMA_LIT_SIZE << (lc + lp)))* sizeof(CProb);

	//lzmaInternalData = (NEW_BOTTOM unsigned char[lzmaInternalSize]);
	//MemoryType mt = POOL_BOTTOM;
	//if( GetEngine().GetMemoryPool(MEMORY_POOL_DEFAULT)->GetFreeMem() < lzmaInternalSize )
	//{
	//	mt = ACTOR_BOTTOM_PLAYER;
	//}
	lzmaInternalData = (GL_NEW/*(mt)*/ unsigned char[lzmaInternalSize]);

	unsigned int outSizeProcessed;


#ifdef _LZMA_IN_CB

	ILzmaInCallback cb;

	cb.mpFile = m_file;
	cb.length = packedSize;
	cb.Read = LzmaRead;

	((CFileStream*)m_file)->InitLzmaBuffer();
#endif

    if(LzmaDecode((unsigned char *)lzmaInternalData, lzmaInternalSize,
		lc, lp, pb, 
#ifdef _LZMA_IN_CB
		&cb,
#else
		inBuf + 1, packedSize,
#endif
		(unsigned char *)pBuf, originalSize, &outSizeProcessed))
	{
		ASSERT(false);
	}

#ifdef _LZMA_IN_CB	
	((CFileStream*)m_file)->ReleaseLzmaBuffer();
#endif
	  
	ASSERT(outSizeProcessed == originalSize);	
	SAFE_DELETE_ARRAY(lzmaInternalData);//MF

#ifndef _LZMA_IN_CB	
	SAFE_DELETE_ARRAY(inBuf);
#endif

	return outSizeProcessed;
}
