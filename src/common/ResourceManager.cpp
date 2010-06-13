// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "resourcemanager.h"
#include "Memory.h"

CResourceManager::CResourceManager()
{
	MEMSET(m_files, 0, sizeof(m_files));
}

CResourceManager::~CResourceManager()
{
#if DEBUG_LEVEL > 0
	//make sure all files are removed
	for(int i = 0; i < MAX_RESOURCE_FILE; i++)
		ASSERT(m_files[i] == NULL);
#endif
}

void CResourceManager::AddResFile(CResFile *file)
{
	int i;
	for(i = 0; i < MAX_RESOURCE_FILE; i++)
	{
		if(m_files[i] == file)
		{
			ASSERT(false);
			return;
		}
		if(m_files[i] == NULL)
		{
			m_files[i] = file;
			return;
		}
	}

	//too much resource files have been added
	ASSERT(false);
}

void CResourceManager::RemoveResFile(CResFile *file)
{
	int i;
	for(i = 0; i < MAX_RESOURCE_FILE; i++)
	{
		if(m_files[i] == file)
		{
			m_files[i] = NULL;
			return;
		}
	}
}

CStream* CResourceManager::GetResourceAsStream(const char *name, MemoryType memType)
{
	void* hRecord;
	CResFile *file;
	for(int i = 0; i < MAX_RESOURCE_FILE; i++)
	{
		file = m_files[i];
		hRecord = file->FindRecord(name);
		if(hRecord)
			break;
	}
	if(!hRecord)
	{
		//record does not exist
		ASSERT(false);
		return NULL;
	}

	unsigned int len = file->GetRecordSize(hRecord);
	CMemoryStream *stream = (GL_NEW/*(memType)*/ CMemoryStream(len, memType));
	file->ReadRecord(hRecord, stream->GetBuffer(), len);

	return stream;
}
