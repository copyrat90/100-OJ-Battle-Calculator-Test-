// 캐릭터 클래스 관련 함수들 (대부분 배틀 함수)
// 두 플레이어 정보가 필요한 경우 공격측 캐릭터 인스턴스가 함수를 호출하고 방어측 캐릭터를 인자로 받음


#include "pch.h"

// 주사위와 스탯을 합산해 실제 배틀 수치를 반환하는 멤버 함수
// 배틀 수치는 최소 1
int Character::DiceNumCalc(int dice, int bonus)
{
	if (dice + bonus <= 0)
		return 1;
	else
		return dice + bonus;
}

// 배틀 전 죽는 경우의 수를 반환하는 멤버 함수
// 인스턴스: 공격측 캐릭터
// 인자: 방어측 캐릭터
// 반환: (int) 36가지 주사위 조합 중 죽는 경우의 수(0~36)
int Character::KillValueBeforeBattle(Character& defender)
{
	int KOcount = 0;
	int attackNum;
	int killValueDEF, killValueEVD;

	int aDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(aDice, this->GetATK());

		killValueDEF = defender.KillValueDEF(attackNum);
		killValueEVD = defender.KillValueEVD(attackNum);

		KOcount += killValueDEF <= killValueEVD ? killValueDEF : killValueEVD;
	}

	return KOcount;
}

// 방어를 선택했을 때 평균 데미지를 계산하는 멤버 함수
// 인스턴스: 방어측 캐릭터
// 인자: 공격측 배틀 수치 값
// 반환: (double) 방어 시 평균 데미지
double Character::EstimateDamageDEF(int attackNum)
{
	int damageSum = 0;
	int defendNum, damage;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, this->GetDEF());
		damage = attackNum - defendNum;

		if (damage < 1)
			damageSum += 1;
		else
			damageSum += damage < this->GetHP() ? damage : this->GetHP();
	}

	return (double)damageSum / 6;
}

// 회피를 선택했을 때 평균 데미지를 계산하는 멤버 함수
// 인스턴스: 방어측 캐릭터
// 인자: 공격측 배틀 수치 값
// 반환: (double) 회피 시 평균 데미지
double Character::EstimateDamageEVD(int attackNum)
{
	int damageSum = 0;
	int evadeNum;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		evadeNum = DiceNumCalc(dDice, this->GetEVD());

		if (attackNum >= evadeNum)
			damageSum += attackNum < this->GetHP() ? attackNum : this->GetHP();
	}

	return (double)damageSum / 6;
}


// 방어를 선택했을 때 죽는 경우의 수를 반환하는 멤버 함수
// 인스턴스: 방어측 캐릭터
// 인자: 공격측 배틀 수치 값
// 반환: (int) 주사위 1~6 중 죽는 경우의 수(0~6)
int Character::KillValueDEF(int attackNum)
{
	int KOcount = 0;
	int defendNum, damage;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		defendNum = DiceNumCalc(dDice, this->GetDEF());
		damage = attackNum - defendNum;
		if (damage < 1) damage = 1;

		if (damage >= this->GetHP())
			++KOcount;
	}

	return KOcount;
}

// 회피를 선택했을 때 죽는 경우의 수를 반환하는 멤버 함수
// 인스턴스: 방어측 캐릭터
// 인자: 공격측 배틀 수치 값
// 반환: (int) 주사위 1~6 중 죽는 경우의 수(0~6)
int Character::KillValueEVD(int attackNum)
{
	int KOcount = 0;
	int evadeNum;

	if (attackNum < this->GetHP())
		return 0;

	for (int dDice = 1; dDice <= 6; ++dDice)
	{
		evadeNum = DiceNumCalc(dDice, this->GetEVD());
		if (evadeNum <= attackNum)
			++KOcount;
	}

	return KOcount;
}

// 배틀 전 데미지 기댓값 계산하는 멤버 함수
// 상대가 항상 최선의 선택(사망확률 낮은 것, 사망 확률 같으면 평균 데미지를 낮추는 선택)을 한다고 가정
// 인스턴스: 공격측 캐릭터
// 인자: 방어측 캐릭터
// 반환: (double) 데미지 기댓값
double Character::EstimateDamageBeforeBattle(Character& defender)
{
	double sum = 0;

	int attackNum;
	int killValueDEF, killValueEVD;
	int aDice;
	for (aDice = 1; aDice <= 6; ++aDice)
	{
		attackNum = DiceNumCalc(aDice, this->GetATK());

		killValueDEF = defender.KillValueDEF(attackNum);
		killValueEVD = defender.KillValueEVD(attackNum);

		if (killValueDEF < killValueEVD)
			sum += defender.EstimateDamageDEF(attackNum);
		else if (killValueDEF > killValueEVD)
			sum += defender.EstimateDamageEVD(attackNum);
		else if (defender.EstimateDamageDEF(attackNum) < defender.EstimateDamageEVD(attackNum))
			sum += defender.EstimateDamageDEF(attackNum);
		else
			sum += defender.EstimateDamageEVD(attackNum);
	}

	return sum / 6;
}