#pragma once
#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <string>

#define DEBUG_TRACE printf
#define MAX_TOKEN_SIZE 128

typedef enum {
	BAD_TOKEN,
	NUM_TOKEN,
	ADD_OPT_TOKEN,
	SUB_OPT_TOKEN,
	MUL_OPT_TOKEN,
	DIV_OPT_TOKEN,
	EOL_TOKEN
} TokenKind;


typedef struct {
	TokenKind kind;
	double value;
	char str[MAX_TOKEN_SIZE];
} Token;

typedef enum {
	INITIAL_STATUS,
	IN_INT_PART_STATUS,
	DOT__STATUS,
	IN_FRAC_PART_STATUS
} LexerStatus;

class Calculator
{
public:

	Calculator(void);

	virtual ~Calculator(void);

	int Eval(const char* pszExp);

private:
	std::string m_strExpresson;
	int m_nPos;
};

int calculator_test(int argc, char* argv[]);

#endif
