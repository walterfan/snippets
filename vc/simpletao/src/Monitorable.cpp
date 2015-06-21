#include "Monitorable.h"


Monitorable::Monitorable(void)
{
}


Monitorable::~Monitorable(void)
{
}

MonitorResult Monitorable::Check(MonitorCategory category)
{
	return OK;
}