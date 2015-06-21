/*
* Copyright  2005 JinWei Bird Studio All rights reserved
*
* Filename: wf_base.h
* Description: base header file
*
* Version:1.0
* Create date: 08/19/2005
* Author: Walter Fan, walter.fan@gmail.com
*/


#ifndef __WF_UTIL_H__
#define __WF_UTIL_H__

#include <stdarg.h>
#include "wf_base.h"

char* get_cur_info(char* szBuf, int len);

namespace wfan {

enum RET_STATUS{RET_ERR=-1,RET_OK=0};

const int MSGLEN=1024;
const int BUFLEN=256;
const int TIMELEN=12;
const int FULLTIMELEN=30;
const int DAYTIMES=24*60*60;

string GetTimeStr();

inline void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

inline void error(int status,int err, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if(err)
    	fprintf(stderr, "%d: %s\n", err, strerror(err));
    if(status)
    	exit(status);
}

int file2msg(const char* filename,string& msg);

int file2msg(const char* filename,char *msg);

string Trim(const string& s);

string LowerCase(const string& s);

string UpperCase(const string& s);

/*************************************     
     *Function:        Basename
     *Description:   Trim path and extend name of filename
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string Basename(const string& filename);
/*************************************     
     *Function:        GetDateStr
     *Description:   get datestring, such as 20041118
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string GetDateStr();
/*************************************     
     *Function:        TrimSuffix
     *Description:   Trim file extend name
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string TrimSuffix(const string& filename);

//--------------template class --------------------//

template<class Seq> void purge(Seq& c)
{
    typename Seq::iterator it;
    for(it=c.begin();it!=c.end();++it)
    {
        if((*it)!=NULL)
        {
            delete *it;
            *it=NULL;
        }
    }
};
    
template<class T> struct FnPrint : public unary_function<T, void>
{
    FnPrint(ostream& out) : os(out), count(0)
    {}
    void operator() (T x)
    {
        os << x << ' ';
        ++count;
    }
    ostream& os;
    int count;
};

template<class T>
int msg2log(string filename,T message,char* file=NULL, int line=0)
{
        ofstream logfile(filename.c_str(), ios::app);

        if(!logfile)
        {
            cout<<"Unable to write "<<filename<<endl;
            return -1;
        }
        if(file==NULL||line==0)
            logfile<<file<<", line"<<line<<":\t"<<message<<endl;
        else
            logfile<<GetTimeStr()<<":\t"<<message<<endl;
        logfile.close();

        return 0;
}



template<class T>
int msg2file(const char* filename,const T message)
{
    ofstream tmpfile(filename,ios::out);
    if(!tmpfile)
    {
        cout<<"Unable to write "<<filename<<endl;
        return -1;
    }
    tmpfile<<message<<endl;
    tmpfile.close();
    return 0;
}

inline int String2File(string str, string filename)
{
	return msg2file(filename.c_str(), str);
}

inline int File2String(string strFilename, string& str)
{
    return file2msg(strFilename.c_str(), str);
}

}//namespace wfan

#endif
