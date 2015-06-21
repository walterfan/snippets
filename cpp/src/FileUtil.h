#include <string>
#include <vector>

namespace wfan {

int file2msg(const char* filename,std::string& msg);

int file2msg(const char* filename,char *msg);

int RetrieveFiles(const char* szFolder, std::vector<string>& files);

}
