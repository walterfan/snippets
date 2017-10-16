#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include <string>
#include <vector>

using namespace std;

namespace wfan {

int file2msg(const char* filename,std::string& msg);

int file2msg(const char* filename,char *msg);

int RetrieveFiles(const char* szFolder, vector<string>& vecFiles, const char* szExt = NULL);

inline int String2File(string str, string filename)
{
	return msg2file(filename.c_str(), str);
}

inline int File2String(string strFilename, string& str)
{
    return file2msg(strFilename.c_str(), str);
}

}

#endif