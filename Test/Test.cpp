#include "pch.h"

using namespace std;

// 주사위와 스탯을 합산해 실제 배틀 수치를 반환하는 함수
// 배틀 수치는 최소 1
int DiceNumCalc(int dice, int bonus)
{
	if (dice + bonus <= 0)
		return 1;
	else
		return dice + bonus;
}

// WIP: 배틀 전 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 캐릭터, 방어측 캐릭터
// 반환: (int) 36가지 주사위 조합 중 죽는 경우의 수(0~36)
double KillValueBeforeBattle(Character& attacker, Character& defender)
{
	int KOcount = 0;
	int attackNum, defendNum;
	int killValueDEF, killValueEVD;
	
	int aDice, dDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(aDice, attacker.ATK);

		killValueDEF = KillValueDEF(attackNum, defender);
		killValueEVD = KillValueEVD(attackNum, defender);

		if (killValueDEF == killValueEVD)
		{
			
		}
	}
}

// 방어를 선택했을 때 평균 데미지를 계산하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (double) 방어 시 평균 데미지
double EstimateDamageDEF(int attackNum, Character& defender)
{
	int damageSum = 0;
	int defendNum;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, defender.DEF);

		if (attackNum - defendNum <= 0)
			damageSum += 1;
		else
			damageSum += attackNum - defendNum;
	}

	return (double)damageSum / 6;
}

// 회피를 선택했을 때 평균 데미지를 계산하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (double) 회피 시 평균 데미지
double EstimateDamageEVD(int attackNum, Character& defender)
{
	int damageSum = 0;
	int evadeNum;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		evadeNum = DiceNumCalc(dDice, defender.EVD);

		if (attackNum >= evadeNum)
			damageSum += attackNum;
	}

	return (double)damageSum / 6;
}


// 방어를 선택했을 때 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (int) 주사위 1~6 중 죽는 경우의 수
int KillValueDEF(int attackNum, Character& defender)
{
	int KOcount = 0;
	int defendNum;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, defender.DEF);
		if (attackNum - defendNum >= defender.HP)
			++KOcount;
	}

	return KOcount;
}

// 회피를 선택했을 때 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (int) 주사위 1~6 중 죽는 경우의 수
int KillValueEVD(int attackNum, Character& defender)
{
	int KOcount = 0;
	int evadeNum;

	if (attackNum < defender.HP)
		return 0;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		evadeNum = DiceNumCalc(dDice, defender.EVD);
		if (evadeNum <= attackNum)
			++KOcount;
	}

	return KOcount;
}

// WIP: 배틀 전 데미지 기댓값 계산
// 상대가 항상 최선의 선택(사망확률 낮은 것, 사망 확률 같으면 평균 데미지를 낮추는 선택)을 한다고 가정
double EstimateDamageBeforeBattle(Character& attacker, Character& defender)
{
	int count = 0, sum = 0;
	double average = 0;
	
	int attackNum, defendNum;
	int aDice, dDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(dDice, attacker.ATK);

		// WIP
	}
}


int main()
{
	Character p1, p2;
	cout << "attacker's attack >> ";
	std::cin >> p1.ATK;
	cout << "defender's defence >> ";
	std::cin >> p2.DEF;
	std::cout << EstimateDamageBeforeBattle(p1, p2);

	return 0;
}
