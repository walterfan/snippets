#include "wf_util.h"
#include "FileUtil.h"
using namespace std;

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

int RetrieveFiles(const char* szFolder, vector<string>& files)
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
    files.push_back(file);
  }

  while((-1 == closedir(dirp)) && (errno == EINTR));

  return files.size();
}

}
