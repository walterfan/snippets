#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

typedef enum {
	BAD_TOKEN,
	NUM_TOKEN,
	ADD_OPT_TOKEN,
	SUB_OPT_TOKEN,
	MUL_OPT_TOKEN,
	DIV_OPT_TOKEN,
	LINE_END_TOKEN
} TokenKind

const size_t MAX_TOKEN_SIZE = 100;

typedef struct {
	TokenKind token;
	double value;
	char str[MAX_TOKEN_SIZE];
}

class Calcultor
{
public:	
	int calculate(char* expression);
	int parse(char* expression);
private:
    string m_strExp;
    int m_nPos
};



char* get_cur_time(char* buffer, int len=30)
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime );
	timeinfo = localtime(&rawtime );

	strftime (buffer,30,"%x %X\0",timeinfo);
	return buffer;

}

int main(int argc, char* argv[])
{
    char str[30] = {'\0'};
    printf("# [%s] --- calculator ---\n", get_cur_time(str));

	return 0;
}
