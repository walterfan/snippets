#include <stdio.h>

#include <string>
#include <iostream>

#include "ace/OS.h"
#include "ace/Reactor.h"
#include "ace/SOCK_Connector.h" 


using namespace std;

class MyClient:public ACE_Event_Handler 
{
public:
    bool open()
     {
         ACE_SOCK_Connector connector;
         ACE_INET_Addr addr(80,"127.0.0.1");
         ACE_Time_Value timeout(5,0);
        if(connector.connect(peer,addr,&timeout) != 0)
         {
            cout<<"connecetd fail"<<endl;
            return false;
         }
         ACE_Reactor::instance()->register_handler(this,ACE_Event_Handler::READ_MASK);
         cout<<"connecetd "<<endl;
        return true;
     }

     ACE_HANDLE get_handle(void) const
     {
        return peer.get_handle();
     }

    int handle_input (ACE_HANDLE fd)
     {
        int rev=0;
         ACE_Time_Value timeout(5,0);
        if((rev=peer.recv(buffer,1000,&timeout))>0)
         {
             buffer[rev]='\0';
             cout<<endl<<"rev:\t"<<buffer<<endl;
         }
        return 3;
     }

private:
     ACE_SOCK_Stream peer;
    char buffer[1024];
};

int reactor_test(int argc, char *argv[]) 
{
    MyClient client;
    bool ret = client.open();
	if(!ret) return -1;

	int count = 0;
    while(true)
     {
         ACE_Reactor::instance()->handle_events(); 
		 count ++;
		 if(count > argc) break;
		 else ACE_OS::sleep(1);
     }

    return 0; 
}