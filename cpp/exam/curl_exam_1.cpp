#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

const int URL_MAX_LEN = 2048;
static int nHeaderCount = 0;

static size_t curlHeaderCallbackFunc(char *ptr, size_t size, size_t nitems, void *userdata)
{
  /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
  /* 'userdata' is set with CURLOPT_HEADERDATA */
    string* pHeader = (string*)userdata;
    size_t nHeaderSize = nitems * size;
    if(nHeaderSize <= 2) {
      return nHeaderSize;
    }
    string aHeader = string(ptr, nHeaderSize);

    cout << (++nHeaderCount) << "Got head: " << aHeader << ", nitems="<< nitems << ", size=" << size <<endl;

    if(aHeader.find("Content-Type") != string::npos) {
      *pHeader = aHeader;
    }
    

    return nHeaderSize;
}

int main(int argc, char* argv[])
{
  
  char url[URL_MAX_LEN] = "https://api.douban.com/v2/book/isbn/9787115376756";
  if(argc > 1) {
    int len = strlen(argv[1]);

    if(len >= URL_MAX_LEN)
	    len = URL_MAX_LEN - 1;
    strncpy(url, argv[1], len);	
  }
  CURL *curl;
  CURLcode res;
 
  string strContentType = "";

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curlHeaderCallbackFunc);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)(&strContentType));

    for(int i=0; i<1; i++) {
      long beginTime = time(NULL);
      printf("\n%d. --- begin --- %ld \n", i, beginTime);
      res = curl_easy_perform(curl);
      /* Check for errors */ 
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

      printf("\n%d. --- end --- duraion: %ld - userdata: %s\n", i, time(NULL) -  beginTime, strContentType.c_str());
      usleep(1000*1000*1);
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}

