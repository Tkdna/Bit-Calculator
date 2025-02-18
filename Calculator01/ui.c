#include <stdio.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"
#include <stdlib.h>

//����� �Է�
CALC UserInput(EXPRESSION* pEx) {

	system("cls");
	printf("�����Է�> ");
	scanf_s("%d%c%d%*c", &pEx->lData, &pEx->op, sizeof(char), &pEx->rData);

	switch (pEx->op) {
	case '+':
		return ADD;
	case '-':
		return SUBSTRACT;
	case '*':
		return MULTIPLY;
	case '/':
		return DIVIDE;
	}
	return;
}

//�̺�Ʈ ����
void EventloopRun() {
	char out;
	CALC calc = 0;
	EXPRESSION* pEx = malloc(sizeof(EXPRESSION));

	while (1) {
		calc = UserInput(pEx);
		switch (calc)
		{
		case ADD:
			printf("> %d\n", getAdd(pEx->lData, pEx->rData));
			break;
		case SUBSTRACT:
			printf("> %d\n", getSubstract(pEx->lData, pEx->rData));
			break;
		case MULTIPLY:
			printf("> %d\n", getMultiply(pEx->lData, pEx->rData));
			break;
		case DIVIDE: {
			int quot, remain = 0;
			if (pEx->rData == 0) {
				printf("[ERROR: Divide by Zero]\n");
				break;
			}
			getDivide(pEx->lData, pEx->rData, &quot, &remain);
			printf("> ��:%d, ������:%d\n", quot, remain);
			break;
		}
		default:
			break;
		}

		printf("���α׷��� �����Ͻðڽ��ϱ�? (Y/N) ");
		scanf_s("%c", &out, 1);
		if (out == 'N' || out == 'n') {
			continue;
		}
		else if (out == 'Y' || out == 'y') {
			free(pEx);
			break;
		}
	}
	puts("Bye~!");
	return;
}
