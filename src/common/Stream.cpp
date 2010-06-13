// Copyright (C) 2005 GameWG. All rights reserved.
// GAMELOFT PROPRIETARY/CONFIDENTIAL.
//
// Author: Qiu Wei Min

#include "Stream.h"
#include "SysUtil.h"
#include "ResFile.h"
#include "Engine.h"
#include "Memory.h"

CFileStream::CFileStream()
{
#ifdef _LZMA_IN_CB
	m_pFileBuffer = NULL;
#endif
}

CFileStream::~CFileStream()
{
#ifdef _LZMA_IN_CB
	SAFE_DELETE(m_pFileBuffer);
#endif
}


bool CFileStream::Open(const char* pName, int mode)
{
	m_mode = mode;
	if(!m_file.Open(pName, mode))
		return false;
	return true;
}

int CFileStream::GetLength()
{
	return m_file.GetLength();
}

int CFileStream::GetPosition()
{
	return m_file.GetPosition();
}

bool CFileStream::SetPosition(int pos)
{
	return m_file.Seek(pos, CRawFile::FSEEK_BEGIN);
}

bool CFileStream::Skip(int pos)
{
	return m_file.Seek(pos, CRawFile::FSEEK_CURRENT);
}

bool CFileStream::IsReadOnly()
{
	return m_mode == CRawFile::MODE_READ;
}

int CFileStream::Read(void* pBuffer, int length)
{
	return m_file.Read(pBuffer, length);
}

signed char CFileStream::ReadByte()
{
	signed char c;
	int ret = m_file.Read(&c, 1);
	ASSERT(ret == 1);
	return c;
}

unsigned char CFileStream::ReadUByte()
{
	unsigned char c;
	int ret = m_file.Read(&c, 1);
	ASSERT(ret == 1);
	return c;
}

short CFileStream::ReadShortLE()
{
	unsigned char c[2];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (short)((c[1] << 8) | c[0]);
}

unsigned short CFileStream::ReadUShortLE()
{
	unsigned char c[2];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (short)((c[1] << 8) | c[0]);
}

int CFileStream::ReadIntLE()
{
	unsigned char c[4];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (c[3] << 24) | (c[2] << 16) | (c[1] << 8) | c[0];
}

unsigned int CFileStream::ReadUIntLE()
{
	unsigned char c[4];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (c[3] << 24) | (c[2] << 16) | (c[1] << 8) | c[0];
}

short CFileStream::ReadShortBE()
{
	unsigned char c[2];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (short)((c[0] << 8) | c[1]);
}

unsigned short CFileStream::ReadUShortBE()
{
	unsigned char c[2];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (short)((c[0] << 8) | c[1]);
}

int CFileStream::ReadIntBE()
{
	unsigned char c[4];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3];
}

unsigned int CFileStream::ReadUIntBE()
{
	unsigned char c[4];
	int ret = m_file.Read(&c, sizeof(c));
	ASSERT(ret == sizeof(c));
	return (c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3];
}

int CFileStream::Write(const void* pBuffer, int length)
{
	return m_file.Write(pBuffer, length);
}

void CFileStream::WriteByte(int v)
{
	int ret = m_file.Write(&v, 1);
	ASSERT(ret == 1);
}

void CFileStream::WriteShortLE(int v)
{
	int ret = m_file.Write(&v, 2);
	ASSERT(ret == 2);
}

void CFileStream::WriteIntLE(int v)
{
	int ret = m_file.Write(&v, 4);
	ASSERT(ret == 4);
}

void CFileStream::WriteShortBE(short v)
{
	unsigned char c[2];
	c[0] = (v & 0xFF00) >> 8;
	c[1] = (v & 0x00FF) ;
	int ret = m_file.Write(&c, 2);
	ASSERT(ret == 2);
}

void CFileStream::WriteIntBE(int v)
{
	unsigned char c[4];
	c[0] = (v & 0xFF000000) >> 24;
	c[1] = (v & 0x00FF0000) >> 16;
	c[2] = (v & 0x0000FF00) >> 8;
	c[3] = (v & 0x000000FF) ;
	int ret = m_file.Write(&c, 4);
	ASSERT(ret == 4);
}

#ifdef _LZMA_IN_CB
void CFileStream::InitLzmaBuffer(int size)
{
	ASSERT(m_pFileBuffer == NULL);
	ASSERT(size > 0);

	m_nBufferSize = size;

	// << by wubin, use POOL_BOTTOM
	//m_pFileBuffer = (GL_NEW/*(GetMemoryType(this))*/ unsigned char[m_nBufferSize]);
	m_pFileBuffer = (GL_NEW/*(POOL_BOTTOM)*/ unsigned char[m_nBufferSize]);
	// >>
}

void CFileStream::ReleaseLzmaBuffer()
{
	SAFE_DELETE_ARRAY(m_pFileBuffer);//MF
}

int CFileStream::LzmaRead(unsigned char **buffer, unsigned int *bufferSize, int& size)
{
	ASSERT(m_pFileBuffer != NULL);

	*buffer = m_pFileBuffer;

	if(size - m_nBufferSize > 0)
	{
		*bufferSize = m_file.Read(m_pFileBuffer, m_nBufferSize);
	}
	else
	{
		*bufferSize = m_file.Read(m_pFileBuffer, size);
	}		
	
	size -= *bufferSize;

	return 0;
}
#endif

void CFileStream::Close()
{
	m_file.Close();
}



CMemoryStream::CMemoryStream(void *buf, int length)
{
	m_data = (unsigned char*)buf;
	m_current = m_data;
	m_length = length;
	m_needFreeBuffer = false;
}

CMemoryStream::CMemoryStream(int length, MemoryType memType)
{
	m_data = (GL_NEW/*(memType)*/ unsigned char[length]);
	m_current = m_data;
	m_length = length;
	m_needFreeBuffer = true;
}

CMemoryStream::~CMemoryStream()
{
	Close();
}

int CMemoryStream::GetLength()
{
	return m_length;
}

int CMemoryStream::GetPosition()
{
	return m_current - m_data;
}

bool CMemoryStream::IsReadOnly()
{
	//always read-write
	return false;
}

int CMemoryStream::Write(const void* pBuffer, int length)
{
	ASSERT(m_current + length <= m_data + m_length);
	MEMCPY(m_current, pBuffer, length);
	m_current += length;
	return length;
}

void CMemoryStream::WriteByte(int v)
{
	ASSERT(m_current < m_data + m_length);
	*m_current++ = v;
}

void CMemoryStream::WriteShortLE(int v)
{	
	ASSERT(m_current + 2 <= m_data + m_length);
	*m_current++ = v;
	*m_current++ = v >> 8;
}


void CMemoryStream::WriteIntLE(int v)
{
	ASSERT(m_current + 4 <= m_data + m_length);
	*m_current++ = v;
	*m_current++ = v >> 8;
	*m_current++ = v >> 16;
	*m_current++ = v >> 24;
}

void CMemoryStream::Close()
{
	if(m_needFreeBuffer)
	{
		SAFE_DELETE_ARRAY(m_data);
	}
	m_data = NULL;
}

bool CMemoryStream::Skip(int len)
{
	m_current += len;
	ASSERT(m_current >= m_data && m_current <= m_data + m_length);
	return true;
}

bool CMemoryStream::SetPosition(int pos)
{
	ASSERT(pos < m_length);
	m_current = m_data + pos;
	return true;
}

int CMemoryStream::Read(void* pBuffer, int length)
{
	ASSERT(m_current + length <= m_data + m_length);
	MEMCPY(pBuffer, m_current, length);
	m_current += length;
	return length;
}

signed char CMemoryStream::ReadByte()
{
	ASSERT(m_current < m_data + m_length);
	return (signed char)*m_current++;
}

unsigned char CMemoryStream::ReadUByte()
{
	ASSERT(m_current < m_data + m_length);
	return (unsigned char)*m_current++;
}

short CMemoryStream::ReadShortLE()
{
	ASSERT(m_current + 2 <= m_data + m_length);
	short r = (short)((m_current[1] << 8) | m_current[0]);
	m_current += 2;
	return r;
}

unsigned short CMemoryStream::ReadUShortLE()
{
	ASSERT(m_current + 2 <= m_data + m_length);
	unsigned short r = (unsigned short)((m_current[1] << 8) | m_current[0]);
	m_current += 2;
	return r;
}

int CMemoryStream::ReadIntLE()
{
	ASSERT(m_current + 4 <= m_data + m_length);
	int r = (m_current[3] << 24) | (m_current[2] << 16) | (m_current[1] << 8) | m_current[0];
	m_current += 4;
	return r;
}

unsigned int CMemoryStream::ReadUIntLE()
{
	ASSERT(m_current + 4 <= m_data + m_length);
	unsigned int r = (m_current[3] << 24) | (m_current[2] << 16) | (m_current[1] << 8) | m_current[0];
	m_current += 4;
	return r;
}

short CMemoryStream::ReadShortBE()
{		
	ASSERT(m_current + 2 <= m_data + m_length);
	short r = (short)((m_current[0] << 8) | m_current[1]);
	m_current += 2;
	return r;
}

unsigned short CMemoryStream::ReadUShortBE()
{
	ASSERT(m_current + 2 <= m_data + m_length);
	unsigned short r = (unsigned short)((m_current[0] << 8) | m_current[1]);
	m_current += 2;
	return r;
}

int CMemoryStream::ReadIntBE()
{
	ASSERT(m_current + 4 <= m_data + m_length);
	int r = (m_current[0] << 24) | (m_current[1] << 16) | (m_current[2] << 8) | m_current[3];
	m_current += 4;
	return r;
}

unsigned int CMemoryStream::ReadUIntBE()
{
	ASSERT(m_current + 4 <= m_data + m_length);
	unsigned int r = (m_current[0] << 24) | (m_current[1] << 16) | (m_current[2] << 8) | m_current[3];
	m_current += 4;
	return r;
}

//s64 CMemoryStream::ReadInt64BE()
//{
//	ASSERT(m_current + 4 <= m_data + m_length);
//	int high = (m_current[0] << 24) | (m_current[1] << 16) | (m_current[2] << 8) | m_current[3];
//	m_current += 4;
//	unsigned int low = (m_current[0] << 24) | (m_current[1] << 16) | (m_current[2] << 8) | m_current[3];
//	m_current += 4;
//
//	//s64 r = (((s64)high)<<32) + (s64)low;
//	//DBGPRINTF("****** returning s64 h=%d,l=%d",high,low);
//	return s64(high, low);
//}

char* CMemoryStream::readUTF(MemoryType memType)
{
	unsigned short len = ReadUShortBE();
	char* str = (GL_NEW/*(memType)*/ char[len + 1]);
	str[Read(str, len)] = 0;
	return str;
}

bool CMemoryStream::FreeBottom()
{
	//MemoryType pMemType = GetMemoryType(m_data);

	//if(pMemType != POOL_TOP)
	//{
	//	return false;
	//}

	//CMemoryPool *pool =	GetEngine().GetMemoryPool(MEMORY_POOL_DEFAULT);

	//int *pTop = (int*)pool->GetTop();

	//if((int*)m_data != pTop + 1)
	//{
	//	return false;
	//}

	//int len = (m_current - m_data) & ~3;

	//unsigned char *p = m_data;

	//m_data += len;
	//m_length -= len;

	//int *pTopNew = (int*)m_data - 1;
	//*pTopNew = *pTop;

	//pool->SetTop(pTopNew);

	//return true;
	return false;
}

