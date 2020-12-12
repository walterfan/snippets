#include <thread>
//#include <boost/thread.hpp>
#include "run_example.h"

using namespace std;

#define JANUS_TRANSPORT_INIT(...) {		\
		.init = NULL,					\
		.destroy = NULL,				\
		.get_api_compatibility = NULL,	\
		.get_version = NULL,			\
		.get_version_string = NULL,		\
		.get_description = NULL,		\
		.get_name = NULL,				\
		.get_author = NULL,				\
		.get_package = NULL,			\
		.is_janus_api_enabled = NULL,	\
		.is_admin_api_enabled = NULL,	\
		.send_message = NULL,			\
		.session_created = NULL,		\
		.session_over = NULL,			\
		.session_claimed = NULL,		\
		.query_transport = NULL,		\
		## __VA_ARGS__ }

void compute() {
    
}

int thread_demo(int argc, char* argv[])
{
    thread t1;




    return 0;
}
