#ifndef ID_GENERATOR_
#define ID_GENERATOR_

class IDGenerator
{
public:
	IDGenerator(void);
	long operator()(void);
	virtual ~IDGenerator(void);

private:
	short counter_;
	static short prefix_;
	static long int const max_counter_ = 32767;
};

#endif