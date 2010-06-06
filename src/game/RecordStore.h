//	RecordStore.java
#ifndef RECORDSTORE_H
#define RECORDSTORE_H

#include "..\Common\Stream.h"

class RecordStore
{
public:
	static CFileStream* fs_sav;
	//static int recordId;	//hw-

	RecordStore()
	{
		//recordId = 1;	//hw-
		fs_sav = GL_NEW CFileStream();
	}

	~RecordStore()
	{
		if (fs_sav) {
			delete fs_sav;
			fs_sav = NULL;
		}
	}

	int getNumRecords();

	void addRecord(byte* data, int offset, int numBytes);
	void setRecord(/*int id,*/byte* buffer, int offset, int numBytes);	//hw#
	byte* getRecord(/*int recordId,*/int offset);	//hw#
	byte* getRecord(/*int recordId,*/int offset, int bufSize);	//hw#

	static bool openRecordStore(const char* dataBaseName, bool create/*, int id*/);	//hw#
	static void closeRecordStore();

	//static int getRecordId() { return recordId; }	//hw-
};

#endif
