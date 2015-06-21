#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{      
	int n = 0, i = 0;      
	int s[10][2];     
	bool r[10];     
	char ch;
	int sum = 0;       
	cout<<"please input count: "<<endl;     
	cin>>n;           
	for (i=0;i<n;i++)     
	{          
		cout<<"please input the "<<i+1<<"  time: pig number and rest count, split by --"<<endl;         
		cin>>s[i][0]>>ch>>ch>>s[i][1];     
	}       

	for(i=0;i<10;i++)         
		r[i]=true;        
	
	for (sum=1;;sum++)     
	{          
		for (i=0;i<n;i++)              
		r[i]=(sum%s[i][0]==s[i][1]);         

		for (i=0;i<n;i++)         
		{              
			if (r[i]==0)                 
				break;         
		}          
		
		if (i==n)         
			break;     
	}      
	cout<<"Pig number is "<<sum<<" at least"<<endl;
}
