%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 0;

int total_chars = 0;
int total_words = 0;
int total_lines = 0;

%}

%%
[a-zA-Z]+    { words++; chars += strlen(yytext); }
\n           { chars++; lines++; }
.            { chars++; }
%%

int main(int argc, char** argv)
{
	int i;

	if(argc < 2) {

		yylex();//yyin is stdin by default if no arguments
		printf("chars:%8d, words:%8d, lines:%8d\n", chars, words, lines);
		return 0;
	}
	for(i = 1; i< argc; ++i) {
		FILE *f = fopen(argv[i], "r");

		if(!f) {
			perror(argv[i]);
			return 1;
		}

		yyrestart(f);
		yylex();
		fclose(f);
		printf("chars:%8d, words:%8d, lines:%8d in %s\n", chars, words, lines, argv[i]);

		total_chars += chars; chars = 0;
		total_words += words; words = 0;
		total_lines += lines; lines = 0;
	}

    if(argc>1) {
    	printf("chars:%8d, words:%8d, lines:%8d totally\n", total_chars, total_words, total_lines);
    } 
    
    
    return 0;
	
}

