#include <stdio.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"
#include <stdlib.h>


//���� �Լ�
int getAdd(int lData, int rData) {

	int sum, carry;

	//carry: �ڸ��ø� ������ &�����ڷ� �˾Ƴ���, �������� 1��ŭ ����Ʈ�Ͽ� ������ ���� ����
	//sum: xor�������� �ڸ��ø� ������� �ʰ� ���� ���� ����
	//carry+sum �ٽ� ����
	//�ڸ��ø��� �߻����� ���������� �ݺ�

	
	while (lData != 0) {
		carry = (lData & rData) << 1;
		sum = lData ^ rData;
		lData = carry;
		rData = sum;
	}
	return rData;
}

//���� �Լ�
int getSubstract(int lData, int rData) {
	int tmp = ~rData;	  //��Ʈ ����
	tmp = getAdd(1, tmp); //2�Ǻ��� ���ϱ�(����)
	return getAdd(lData, tmp);
}


//���� �Լ�
int getMultiply(int lData, int rData) {
	int result = 0;

	//rData�� ������ ��� ������ �ݺ�
	if (rData >= 0) {
		for (int i = 0; i < rData; ++i) {
			result = getAdd(result, lData);
		}
	}
	else {
		for (int i = 0; i > rData; --i) {
			result = getSubstract(result, lData);
		}
	}

	return result;
}

//���� ��ȯ �Լ�
int getAbsolute(int nData) {
	if (nData < 0) {
		nData = getSubstract(0, nData); //0-(����) : ����� ��
		return nData;
	}

	return nData;
}

//������ �Լ�
void getDivide(int dividend, int divisor, int* quot, int* remain) {
	*quot = 0;
	*remain = 0;

	int sign = (getMultiply(dividend, divisor) >= 0) ? 1 : 0;	//��ȣ�� ������ 1, �ٸ��� 0

	//������, ���� ���� ���� �� ������ ����
	int absdividend = getAbsolute(dividend);
	int absdivisor = getAbsolute(divisor);

	//�������� �������� �۰ų� ������ ���� ���� �ݺ�
	while (absdividend >= absdivisor) {
		absdividend = getSubstract(absdividend, absdivisor);
		*quot = getAdd(1, *quot); // ++*quot;
	}
	*remain = absdividend;

	//��ȣ ���� ������ ���� ���
	//��ȣ ���� �ٸ��� ���� ����
	//�������� �����϶� �������� ����
	if (sign == 1)
	{
		if (dividend < 0)
		{
			*remain = getSubstract(0, *remain);
			return;
		}
		return;
	}
	else
	{
		if (dividend < 0)
		{
			*quot = getSubstract(0, *quot);
			*remain = getSubstract(0, *remain);
			return;
		}

		*quot = getSubstract(0, *quot);
		return;
	}

}
