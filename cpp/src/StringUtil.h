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


#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <stdarg.h>
#include <string.h>
#include <sys/time.h>
#include <string>
using namespace std;

namespace wfan {


bool endswith(const std::string &str, const std::string &suffix);

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

int get_value_by_key(const std::string& strMsml, string &strValue, const char* key, const char* sep);

int replace_value_by_key(std::string& strMsml, string mask, const char* key="conn:", const char* sep="/\"");


}//namespace wfan

#endif
