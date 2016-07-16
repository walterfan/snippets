#include "wf_util.h"
#include "StringUtil.h"
#include "FileUtil.h"

using namespace std;
using namespace wfan;

namespace wfan {

int file2msg(const char* filename,string& msg)
{
    ifstream ifile(filename);
    if(!ifile)
    {
        cout<<"Unable to read "<<filename<<endl;
        return RET_ERR;
    }
    ostringstream buf;
    char ch;
    while ( buf && ifile.get( ch ))
        buf.put( ch );
    ifile.close();
    msg=buf.str();
    return RET_OK;
}

int file2msg(const char* filename,char *msg)
{
    ifstream ifile(filename);
    if(!ifile)
    {
        cout<<"Unable to read "<<filename<<endl;
        return -1;
    }
    ostringstream buf;
    char ch;
    while ( buf && ifile.get( ch ))
    buf.put( ch );
    strcpy(msg, buf.str().c_str());
    return 0;
}

int RetrieveFiles(const char* szFolder, vector<string>& vecFiles, const char* szExt)
{
  struct dirent* direntp;
  DIR* dirp = opendir(szFolder);

  if(NULL == dirp) {
    return -1;
  }

  while( NULL != (direntp = readdir(dirp))) {
    string file = direntp->d_name;
    if(".." == file || "." == file)
        continue;
    
    string strPath = szFolder;
    strPath.append("/");
    strPath.append(file);

    struct stat stFileInfo;
    int nStatus = stat(strPath.c_str(), &stFileInfo);
    if (nStatus == 0 && S_ISDIR(stFileInfo.st_mode )) {
        RetrieveFiles(strPath.c_str(), vecFiles, szExt);
    }



    if(NULL == szExt) {
      vecFiles.push_back(strPath);
    }
    else {
      bool hasSuffix = endswith(strPath, szExt);
      if(hasSuffix) {
        vecFiles.push_back(strPath);
      }
    }
  }

  while((-1 == closedir(dirp)) && (errno == EINTR));

  return vecFiles.size();
}

}
