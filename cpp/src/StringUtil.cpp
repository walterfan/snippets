#include "StringUtil.h"

#include "wf_util.h"

char* get_cur_info(char* szBuf, int len)
{
    struct timeval  tv;
    struct timezone tz;
    struct tm      *tm;

    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);

#ifdef TRACE_THREAD
    snprintf(szBuf, len, "[%04d-%02d-%02d %02d:%02d:%02d.%03ld tid=%ld]",
                    tm->tm_year + 1900,tm->tm_mon + 1, tm->tm_mday,
                    tm->tm_hour, tm->tm_min, tm->tm_sec,
                    tv.tv_usec / 1000,
                    gettid());
#else
    snprintf(szBuf, len, "[%04d-%02d-%02d %02d:%02d:%02d.%03ld]",
                    tm->tm_year + 1900,tm->tm_mon + 1, tm->tm_mday,
                    tm->tm_hour, tm->tm_min, tm->tm_sec,
                    tv.tv_usec / 1000);

#endif
    return szBuf;

}

namespace wfan {

string GetTimeStr()
{
    time_t the_time;
    struct timeval current_time;
    struct tm loc_time;
    char buffer[FULLTIMELEN];
    char buf1[TIMELEN];
    char buf2[TIMELEN];

    gettimeofday(&current_time,NULL);
    the_time=(time_t)current_time.tv_sec;
    localtime_r(&the_time,&loc_time);//localtime is local time, gmtime is GMT time

    strftime(buf1, TIMELEN, "%H:%M:%S:", &loc_time);
    snprintf(buf2, TIMELEN, "%5ld",(long)current_time.tv_usec);//micro second
    snprintf(buffer,FULLTIMELEN,"%s %s ms",buf1,buf2);
    return string(buffer);

}


string Trim(const string& s)
{
      if(s.length() == 0)
        return s;
      int b = s.find_first_not_of(" \t");
      int e = s.find_last_not_of(" \t");
      if(b == -1) // No non-spaces
        return "";
      return std::string(s, b, e - b + 1);
}

string LowerCase(const string& s)
{
     string lower(s);
      for(size_t i = 0; i < s.length(); ++i)
            lower[i] = tolower(lower[i]);
      return lower;
}

string UpperCase(const string& s)
{
     string upper(s);
      for(size_t i = 0; i < s.length(); ++i)
        upper[i] = toupper(upper[i]);
      return upper;
}



/*************************************
     *Function:        Basename
     *Description:   Trim path and extend name of filename
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string Basename(const string& filename)
{
    string strfile(filename);
    string::size_type nlastdot = 0,nlastslash = 0;
    nlastslash=strfile.find_last_of("/");
    nlastdot=strfile.find_last_of(".");
    //cout<<strfile.size()<<" from "<<nlastslash<<" to "<<nlastdot<<endl;
    if(nlastslash!=string::npos&&nlastdot!=string::npos&&nlastslash<nlastdot)
        return strfile.substr(nlastslash+1,nlastdot-nlastslash-1);
    else if(nlastslash!=string::npos)
        return strfile.substr(nlastslash+1,strfile.size()-nlastslash-1);
    else if(nlastdot>0)
        return strfile.substr(0,nlastdot);
    else
        return strfile;
}
/*************************************
     *Function:        GetDateStr
     *Description:   get datestring, such as 20041118
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string GetDateStr()
{
    string strdate="";
    char buf[10];
    time_t the_time;
    struct tm *loc_time;
    time(&the_time);
    loc_time=localtime(&the_time);
    strftime(buf,10,"%Y%m%d",loc_time);
    strdate=buf;
    return strdate;
}
/*************************************
     *Function:        TrimSuffix
     *Description:   Trim file extend name
*Parameters:  string filename
*Return:       string filename without suffix
     *************************************/
string TrimSuffix(const string& filename)
{
    string strfile(filename);
    string::size_type nlastdot=strfile.find_last_of(".");
    //cout<<strfile.size()<<" from 0 to "<<nlastdot<<endl;
    if(nlastdot!=string::npos)
        return strfile.substr(0,nlastdot);
    else
        return strfile;
}

bool endswith(const std::string &str, const std::string &suffix)
{
  string::size_type totalSize = str.size();
  string::size_type suffixSize = suffix.size();

  if(totalSize < suffixSize) {
    return false;
  }

  return str.compare(totalSize - suffixSize, suffixSize, suffix) == 0;
}


int get_value_by_key(const std::string& strMsml, string &strValue, const char* key, const char* sep) {
  std::string::size_type nBegin = strMsml.find(key);
  int nKeyLen = strlen(key);
  if(string::npos == nBegin) return -1;

  std::string::size_type nEnd = strMsml.find_first_of(sep, nBegin + nKeyLen);

  if(std::string::npos == nEnd) {
    return -1;
  }
  
  fprintf(stdout, "nEnd=%d , nBegin=%d , nKeyLen=%d",nEnd , nBegin , nKeyLen);
  strValue = strMsml.substr(nBegin + nKeyLen, nEnd - nBegin - nKeyLen);

  return 0;
}

int replace_value_by_key(std::string& strMsml, string mask, const char* key, const char* sep) {

  std::string::size_type nBegin = strMsml.find(key);
  if(string::npos == nBegin) return -1;

  std::string::size_type nEnd = strMsml.find_first_of(sep, nBegin);
  printf("%d to %d", nBegin, nEnd);
  if(std::string::npos == nEnd) {
        strMsml  = strMsml.substr(0, nBegin) + key + mask;
  } else {
        strMsml = strMsml.substr(0, nBegin) + key + mask + strMsml.substr(nEnd);
  }
  
  return 0;
}



} /* namespace wfan */
