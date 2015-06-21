#include "IDGenerator.h"

short IDGenerator::prefix_(1);

IDGenerator::IDGenerator(void):counter_(0)
{
}

IDGenerator::~IDGenerator(void)
{
}

long IDGenerator::operator()(void)
{
	if(counter_ == max_counter_)
		counter_ = 0;
	else
		++ counter_;
	return prefix_ *(max_counter_ + 1) + counter_;
}
