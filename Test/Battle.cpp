#include "pch.h"
#include "Battle.h"

// �ֻ����� ������ �ջ��� ���� ��Ʋ ��ġ�� ��ȯ�ϴ� �Լ�
// ��Ʋ ��ġ�� �ּ� 1
int DiceNumCalc(int dice, int bonus)
{
	if (dice + bonus <= 0)
		return 1;
	else
		return dice + bonus;
}

// ��Ʋ �� �״� ����� ���� ��ȯ�ϴ� �Լ�
// ����: ������ ĳ����, ����� ĳ����
// ��ȯ: (int) 36���� �ֻ��� ���� �� �״� ����� ��(0~36)
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

// �� �������� �� ��� �������� ����ϴ� �Լ�
// ����: ������ ��Ʋ ��ġ ��, ��� ĳ���� Ŭ����
// ��ȯ: (double) ��� �� ��� ������
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

// ȸ�Ǹ� �������� �� ��� �������� ����ϴ� �Լ�
// ����: ������ ��Ʋ ��ġ ��, ��� ĳ���� Ŭ����
// ��ȯ: (double) ȸ�� �� ��� ������
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


// �� �������� �� �״� ����� ���� ��ȯ�ϴ� �Լ�
// ����: ������ ��Ʋ ��ġ ��, ��� ĳ���� Ŭ����
// ��ȯ: (int) �ֻ��� 1~6 �� �״� ����� ��(0~6)
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

// ȸ�Ǹ� �������� �� �״� ����� ���� ��ȯ�ϴ� �Լ�
// ����: ������ ��Ʋ ��ġ ��, ��� ĳ���� Ŭ����
// ��ȯ: (int) �ֻ��� 1~6 �� �״� ����� ��(0~6)
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

// ��Ʋ �� ������ ��� ���
// ��밡 �׻� �ּ��� ����(���Ȯ�� ���� ��, ��� Ȯ�� ������ ��� �������� ���ߴ� ����)�� �Ѵٰ� ����
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