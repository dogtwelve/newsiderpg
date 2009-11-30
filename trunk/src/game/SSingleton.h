////////////////////////////////////////////////////////////////////////////////
///	@file		GsSingleton.h
///	@brief		���������� �� �Ѱ��� �ν��Ͻ����� ������ Singleton Pattern\n
///             <��ó> Game Programming Gem 1��.
///	@author		surap
///	@version	1.0.0
///	@date		09/18/2007
/// @section	Explain	����
///	- ���ø����̼ǿ��� ���� �Ѱ��� �ν��Ͻ��� �����Ǵ� Ŭ����(Singleton Class)�� ���
///	  SSingleton class�� ��ӹ����Ƿμ� �ս��� �̱��� Ŭ������ ������ �� �ִ�.
///	- ��) class CTest : public SSingleton<CTest>
///////////////////////////////////////////////////////////////////////////////

#ifndef __SSINGLETON_H__
#define __SSINGLETON_H__

//#include	"GcxComdDefs.h"

/// @brief	�̱��� ���Ͽ� ���̽� Ŭ����.
template<typename Derived> class SSingleton
{
private:
	static Derived* ms_pSingleton;

protected:
	SSingleton(void);
	virtual ~SSingleton(void);

public:
	inline static Derived& GetInst(void);
	inline static Derived* GetInstPtr(void);
};

template<typename Derived> SSingleton<Derived>::SSingleton( void )
{
	//ASSERT( !ms_pSingleton && "Singleton Ŭ������ �̹� �����Ǿ� �ֽ��ϴ�." );

	/*
	���߻�� ��� �ڵ���. -> ���߻�ӽ� ��ӹ��� ���� Ŭ������ this�� SSingleton��
	this�� �ٸ� ���� ����ų �� �����Ƿ�, �޸𸮻��� �ּ� 0x1�� �ִ� �������� �ʴ� ��ü��
	���ؼ� �װ��� �� �� ��η� ����ȯ�ϰ� ���̸� ���, �ش� �ɼ� ��ŭ ������ SSingleton��ü��
	�ּҸ� ��´�.
	*/
	size_t nOffset = (size_t)(Derived*)0x1 - (size_t)(SSingleton<Derived>*)(Derived*)0x1;
	ms_pSingleton = (Derived*)((size_t)this + nOffset);
}

template<typename Derived> SSingleton<Derived>::~SSingleton( void )
{
	//ASSERT( ms_pSingleton && "Singleton Ŭ������ �������� �ʾҽ��ϴ�" );
    ms_pSingleton = 0;
}

template<typename Derived> inline Derived& SSingleton<Derived>::GetInst( void )
{
	//ASSERT( ms_pSingleton && "Singleton Ŭ������ �������� �ʾҽ��ϴ�" );
    return ( *ms_pSingleton );
}

template<typename Derived> inline Derived* SSingleton<Derived>::GetInstPtr( void )
{
	//ASSERT( ms_pSingleton && "Singleton Ŭ������ �������� �ʾҽ��ϴ�" );
    return ( ms_pSingleton );
}

template<typename Derived> Derived* SSingleton<Derived>::ms_pSingleton = 0;



/*
////////////////////////////////////////////////////////////////////////////////
/// Singleton ��ũ�� ����
////////////////////////////////////////////////////////////////////////////////
/// @brief	<notice> �̱��� ��ü�� ����� ���� �ش� Ŭ���� ���� �ȿ� �� ��ũ�� �߰�.
#define DECLARE_SINGLETON_CLASS( cmName )	\
private:									\
	static cmName	s_Instance;				\
public:										\
	static cmName*	GetInst(void)		{ return &s_Instance; }	\
	static cmName*	GetInstPtr(void)	{ return &s_Instance; }

/// @brief	<notice> �̱��� ��ü�� ����� ���� �ش� Ŭ������ ������ �ҽ� ���Ͽ� �� ��ũ�� �߰�.
#define DEFINE_SINGLETON_CLASS( cmName )	cmName cmName::s_Instance;
*/
////////////////////////////////////////////////////////////////////////////////
#endif		//__SINGLETON_H__
////////////////////////////////////////////////////////////////////////////////
