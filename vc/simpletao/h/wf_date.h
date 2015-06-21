#ifndef _WF_DATE_H
#define _WF_DATE_H

class CDate
{
public:
	CDate(int y, int m, int d):year(y),month(m), day(d){ }

	CDate(CDate& rhs): year(rhs.year), month(rhs.month), day(rhs.day) { }

	~CDate() {};

	CDate& operator=(const CDate& oDate);

	bool operator!=(const CDate& oDate) const;

	bool operator == (const CDate& rhs) const;

	bool operator > (const CDate& rhs) const;

	bool operator < (const CDate& rhs) const;

	
public:
	int compare(const CDate& rhs) const ;

	int year;
	int month;
	int day;
};

#endif