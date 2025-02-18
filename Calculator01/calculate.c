#include <stdio.h>
#include <string.h>
#include "calculate.h"
#include "ui.h"
#include <stdlib.h>


//덧셈 함수
int getAdd(int lData, int rData) {

	int sum, carry;

	//carry: 자리올림 지점을 &연산자로 알아내고, 왼쪽으로 1만큼 쉬프트하여 더해줄 값을 구함
	//sum: xor연산으로 자리올림 고려하지 않고 더한 값을 구함
	//carry+sum 다시 더함
	//자리올림이 발생하지 않을때까지 반복

	
	while (lData != 0) {
		carry = (lData & rData) << 1;
		sum = lData ^ rData;
		lData = carry;
		rData = sum;
	}
	return rData;
}

//뺄셈 함수
int getSubstract(int lData, int rData) {
	int tmp = ~rData;	  //비트 반전
	tmp = getAdd(1, tmp); //2의보수 취하기(음수)
	return getAdd(lData, tmp);
}


//곱셈 함수
int getMultiply(int lData, int rData) {
	int result = 0;

	//rData가 음수인 경우 뺄셈을 반복
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

//절댓값 반환 함수
int getAbsolute(int nData) {
	if (nData < 0) {
		nData = getSubstract(0, nData); //0-(음수) : 양수가 됨
		return nData;
	}

	return nData;
}

//나눗셈 함수
void getDivide(int dividend, int divisor, int* quot, int* remain) {
	*quot = 0;
	*remain = 0;

	int sign = (getMultiply(dividend, divisor) >= 0) ? 1 : 0;	//부호가 같으면 1, 다르면 0

	//피제수, 제수 절댓값 취한 후 나눗셈 연산
	int absdividend = getAbsolute(dividend);
	int absdivisor = getAbsolute(divisor);

	//피제수가 제수보다 작거나 같을때 까지 뺄셈 반복
	while (absdividend >= absdivisor) {
		absdividend = getSubstract(absdividend, absdivisor);
		*quot = getAdd(1, *quot); // ++*quot;
	}
	*remain = absdividend;

	//부호 서로 같을때 몫이 양수
	//부호 서로 다를때 몫이 음수
	//피제수가 음수일때 나머지도 음수
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
