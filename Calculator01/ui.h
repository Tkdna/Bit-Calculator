#pragma once

typedef enum { EXIT, ADD, SUBSTRACT, MULTIPLY, DIVIDE } CALC;

//���� ����ü
typedef struct EXPRESSION {
	int lData;
	char op;
	int rData;
}EXPRESSION;

CALC UserInput(EXPRESSION* pEx);
void EventloopRun();