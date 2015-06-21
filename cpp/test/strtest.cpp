#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

TEST(StrTest, strok_r)
{
    cout<<"--- StringTest strok_r --"<<endl;
	
    int in=0;  
    char buffer[]="Fred male 25,John male 62,Anna female 16";  
    char *p[20];  
    char *buf=buffer;  
    char *outer_ptr=NULL;  
    char *inner_ptr=NULL;  
    while((p[in] = strtok_r(buf, ",", &outer_ptr))!=NULL)   
    {  
        buf=p[in];  
        while((p[in]=strtok_r(buf, " ", &inner_ptr))!=NULL)   
        {  
            in++;  
            buf=NULL;  
        }  
        buf=NULL;  
    }  
    printf("Here we have %d strings\n",in);  
    for (int j=0; j<in; j++)  
    {     
        printf("%s\n",p[j]);  
    }  


}
