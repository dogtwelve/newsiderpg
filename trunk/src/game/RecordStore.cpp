#include "RecordStore.h"
#include "cGame.h"



int RecordStore::getNumRecords()
{
	return fs_sav->GetLength();
}

void RecordStore::addRecord(byte* data, int offset, int numBytes)
{
	//recordId++;	//hw-

	if (fs_sav) {
		fs_sav->Skip(offset);
		fs_sav->Write(data, numBytes);
	}
}

void RecordStore::setRecord(/*int id, */byte* buffer, int offset, int numBytes)	//hw#
{
	//recordId++;	//hw-
	if (fs_sav) {
		fs_sav->Skip(offset);
		fs_sav->Write(buffer, numBytes);
	}
}

byte* RecordStore::getRecord(/*int recordId, */int offset)	//hw#
{
	int bufSize = fs_sav->GetLength();
	byte* buffer = GL_NEW byte[bufSize];
	if(fs_sav) {
		fs_sav->Skip(offset);
		fs_sav->Read(buffer, bufSize);
		return buffer;
	} else {
		return NULL;
	}
}

byte* RecordStore::getRecord(/*int recordId, */int offset, int bufSize)
{
	byte* buffer = GL_NEW byte[bufSize];
	if(fs_sav) {
		fs_sav->Skip(offset);
		fs_sav->Read(buffer, bufSize);
		return buffer;
	} else {
		return NULL;
	}
}

bool RecordStore::openRecordStore( const char* dataBaseName, bool create )	
{	
	if (create) {
		if (fs_sav->Open(dataBaseName, CRawFile::MODE_WRITE)) {			
			return true;
		} else {			
			if (fs_sav->Open(dataBaseName, CRawFile::MODE_CREATE)) 
			{
				return true;
			}
			return false;
		}
	} else {
		if (fs_sav->Open(dataBaseName, CRawFile::MODE_READ)) {	
			
			g_pGame->have_save_file = true;
			return true;
		} else {
			
			g_pGame->have_save_file = false;

			if (fs_sav->Open(dataBaseName, CRawFile::MODE_CREATE)) 
			{
				return true;
			}
			return false;
		}
	}
}

void RecordStore::closeRecordStore()
{
	if (fs_sav)
		fs_sav->Close();
}


CFileStream* RecordStore::fs_sav;
//int RecordStore::recordId;	//hw-
