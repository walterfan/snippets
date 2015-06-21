#ifndef __MONITORABLE_H__
#define __MONITORABLE_H__

typedef enum{
OK
} MonitorResult;

typedef enum{
SYSTEM
} MonitorCategory;

class Monitorable
{
public:
	Monitorable();
	virtual ~Monitorable();
	virtual MonitorResult Check(MonitorCategory category);

};

#endif