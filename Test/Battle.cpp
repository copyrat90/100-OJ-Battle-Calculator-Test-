#include "pch.h"
#include "Battle.h"

// 주사위와 스탯을 합산해 실제 배틀 수치를 반환하는 함수
// 배틀 수치는 최소 1
int DiceNumCalc(int dice, int bonus)
{
	if (dice + bonus <= 0)
		return 1;
	else
		return dice + bonus;
}

// 배틀 전 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 캐릭터, 방어측 캐릭터
// 반환: (int) 36가지 주사위 조합 중 죽는 경우의 수(0~36)
int KillValueBeforeBattle(Character& attacker, Character& defender)
{
	int KOcount = 0;
	int attackNum;
	int killValueDEF, killValueEVD;

	int aDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(aDice, attacker.ATK);

		killValueDEF = KillValueDEF(attackNum, defender);
		killValueEVD = KillValueEVD(attackNum, defender);

		KOcount += killValueDEF <= killValueEVD ? killValueDEF : killValueEVD;
	}

	return KOcount;
}

// 방어를 선택했을 때 평균 데미지를 계산하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (double) 방어 시 평균 데미지
double EstimateDamageDEF(int attackNum, Character& defender)
{
	int damageSum = 0;
	int defendNum, damage;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, defender.DEF);
		damage = attackNum - defendNum;

		if (damage < 1)
			damageSum += 1;
		else
			damageSum += damage < defender.HP ? damage : defender.HP;
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
			damageSum += attackNum < defender.HP ? attackNum : defender.HP;
	}

	return (double)damageSum / 6;
}


// 방어를 선택했을 때 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (int) 주사위 1~6 중 죽는 경우의 수(0~6)
int KillValueDEF(int attackNum, Character& defender)
{
	int KOcount = 0;
	int defendNum, damage;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, defender.DEF);
		damage = attackNum - defendNum;
		if (damage < 1) damage = 1;

		if (damage >= defender.HP)
			++KOcount;
	}

	return KOcount;
}

// 회피를 선택했을 때 죽는 경우의 수를 반환하는 함수
// 인자: 공격측 배틀 수치 값, 방어 캐릭터 클래스
// 반환: (int) 주사위 1~6 중 죽는 경우의 수(0~6)
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

// 배틀 전 데미지 기댓값 계산
// 상대가 항상 최선의 선택(사망확률 낮은 것, 사망 확률 같으면 평균 데미지를 낮추는 선택)을 한다고 가정
double EstimateDamageBeforeBattle(Character& attacker, Character& defender)
{
	double sum = 0;

	int attackNum;
	int killValueDEF, killValueEVD;
	int aDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(aDice, attacker.ATK);

		killValueDEF = KillValueDEF(attackNum, defender);
		killValueEVD = KillValueEVD(attackNum, defender);

		if (killValueDEF < killValueEVD)
			sum += EstimateDamageDEF(attackNum, defender);
		else if (killValueDEF > killValueEVD)
			sum += EstimateDamageEVD(attackNum, defender);
		else if (EstimateDamageDEF(attackNum, defender) < EstimateDamageEVD(attackNum, defender))
			sum += EstimateDamageDEF(attackNum, defender);
		else
			sum += EstimateDamageEVD(attackNum, defender);
	}

	return sum / 6;
}