#include "brewtowipi.h"
#include "Calendar.h"

Calendar::Calendar()
{

	GetCurJulianTime();

}
Calendar::~Calendar()
{}
void Calendar::GetCurJulianTime()
{
  	GETJULIANDATE(0, &m_JulianDate);
  	m_CurYear = m_JulianDate.wYear;
	//m_CurMonth = m_JulianDate.wMonth;
	m_CurMonth = (m_JulianDate.wMonth + 11) % 12;// ( 0,1,2,3,4,5,6,7,8,9,10,11)
	m_CurDay = m_JulianDate.wDay;
	m_CurHour = m_JulianDate.wHour;
	m_CurMinute = m_JulianDate.wMinute;
	m_CurSecond = m_JulianDate.wSecond;

	GetDateString();
	GetTimeString();
}


void Calendar::GetDateString()
{
	MEMSET(m_CurDate, NULL, Date_Length);
	SPRINTF(m_CurDate,"%d%s%d%s%d" ,m_CurYear,"/",m_CurMonth,"/",m_CurDay);
	return ;
}


void Calendar::GetTimeString()
{
	MEMSET(m_CurTime, NULL, Time_Length);
	SPRINTF(m_CurTime,"%d%s%d%s%d %d%s%d" ,m_CurYear,"/",m_CurMonth,"/",m_CurDay,m_CurHour, ":", m_CurMinute);
	return ;
}

int Calendar::GetCurWeekDay()
{

	int   c,y,day;  

	if(m_CurMonth<3){
		m_CurYear-=1;
		m_CurMonth+=10;
	}  
	if(m_CurMonth>2)
		m_CurMonth-=2;  
	
	y=m_CurYear%10;
	c=(m_CurYear-y)/100;

	day=(m_CurDay+(13*m_CurMonth-1)/5+y+y/4+c/4-2*c)%7; 
	
	while(day<0)   
		day+=7;  
	
	return day;  

}
