#include "wf_date.h"

CDate& CDate::operator=(const CDate& oDate)
{
	this->year = oDate.year;
	this->month = oDate.month;
	this->day = oDate.day;

	return *this;
}

bool CDate::operator == (const CDate& rhs) const
{
	return this->year == rhs.year 
		&& this->month == rhs.month 
		&& this->day == rhs.day;

}

bool CDate::operator != (const CDate& rhs) const
{
	return !(*this == rhs);

}

bool CDate::operator > (const CDate& rhs) const
{
	return this->compare(rhs) > 0;
}
	
bool CDate::operator < (const CDate& rhs) const
{
	return this->compare(rhs) < 0;
}


int CDate::compare(const CDate& rhs) const {
		if(this->year > rhs.year) return 1;
		else if(this->year > rhs.year) return -1;

		if(this->month > rhs.month) return 2;		
		else if(this->month > rhs.month) return -2;

		if(this->day > rhs.day) return 3;
		else if(this->day > rhs.day) return -3;

		return 0;
}