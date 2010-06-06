#ifndef _CALENDAR_
#define _CALENDAR_
//Calander
#define  Date_Length	100
#define  Time_Length	100
#include "../common/Common.h"
class Calendar
{
public:
	JulianType m_JulianDate;
	int   m_CurYear;
	int	  m_CurMonth;
	int   m_CurDay;
	int   m_CurHour;
	int   m_CurMinute;
	int   m_CurSecond;
	char  m_CurDate[Date_Length];
	char  m_CurTime[Time_Length];

public:
	Calendar();

	~Calendar();
	void GetCurJulianTime();
	void GetDateString();
	void GetTimeString();
	int GetCurWeekDay();
};	

#endif//_UI_
