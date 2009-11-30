////////////////////////////////////////////////////////////////////////////////
///	@file		GsSingleton.h
///	@brief		디자인패턴 중 한개의 인스턴스만을 가지는 Singleton Pattern\n
///             <출처> Game Programming Gem 1권.
///	@author		surap
///	@version	1.0.0
///	@date		09/18/2007
/// @section	Explain	설명
///	- 어플리케이션에서 오직 한개의 인스턴스만 생성되는 클레스(Singleton Class)인 경우
///	  SSingleton class를 상속받으므로서 손쉽게 싱글턴 클레스를 생성할 수 있다.
///	- 예) class CTest : public SSingleton<CTest>
///////////////////////////////////////////////////////////////////////////////

#ifndef __SSINGLETON_H__
#define __SSINGLETON_H__

//#include	"GcxComdDefs.h"

/// @brief	싱글턴 패턴용 베이스 클레스.
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
	//ASSERT( !ms_pSingleton && "Singleton 클래스가 이미 생성되어 있습니다." );

	/*
	다중상속 대비 코드임. -> 다중상속시 상속받은 실제 클레스의 this와 SSingleton의
	this가 다른 것을 가리킬 수 있으므로, 메모리상의 주소 0x1에 있는 존재하지 않는 객체를
	취해서 그것을 두 형 모두로 형변환하고 차이를 얻고, 해당 옵셋 만큼 떨어진 SSingleton객체의
	주소를 얻는다.
	*/
	size_t nOffset = (size_t)(Derived*)0x1 - (size_t)(SSingleton<Derived>*)(Derived*)0x1;
	ms_pSingleton = (Derived*)((size_t)this + nOffset);
}

template<typename Derived> SSingleton<Derived>::~SSingleton( void )
{
	//ASSERT( ms_pSingleton && "Singleton 클래스가 생성되지 않았습니다" );
    ms_pSingleton = 0;
}

template<typename Derived> inline Derived& SSingleton<Derived>::GetInst( void )
{
	//ASSERT( ms_pSingleton && "Singleton 클래스가 생성되지 않았습니다" );
    return ( *ms_pSingleton );
}

template<typename Derived> inline Derived* SSingleton<Derived>::GetInstPtr( void )
{
	//ASSERT( ms_pSingleton && "Singleton 클래스가 생성되지 않았습니다" );
    return ( ms_pSingleton );
}

template<typename Derived> Derived* SSingleton<Derived>::ms_pSingleton = 0;



/*
////////////////////////////////////////////////////////////////////////////////
/// Singleton 메크로 버전
////////////////////////////////////////////////////////////////////////////////
/// @brief	<notice> 싱글턴 객체를 만들고 싶은 해당 클레스 정의 안에 본 매크로 추가.
#define DECLARE_SINGLETON_CLASS( cmName )	\
private:									\
	static cmName	s_Instance;				\
public:										\
	static cmName*	GetInst(void)		{ return &s_Instance; }	\
	static cmName*	GetInstPtr(void)	{ return &s_Instance; }

/// @brief	<notice> 싱글턴 객체를 만들고 싶은 해당 클레스가 구현된 소스 파일에 본 매크로 추가.
#define DEFINE_SINGLETON_CLASS( cmName )	cmName cmName::s_Instance;
*/
////////////////////////////////////////////////////////////////////////////////
#endif		//__SINGLETON_H__
////////////////////////////////////////////////////////////////////////////////
