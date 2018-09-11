// ĳ���� Ŭ���� ���� �Լ��� (��κ� ��Ʋ �Լ�)
// �� �÷��̾� ������ �ʿ��� ��� ������ ĳ���� �ν��Ͻ��� �Լ��� ȣ���ϰ� ����� ĳ���͸� ���ڷ� ����


#include "pch.h"

// �ֻ����� ������ �ջ��� ���� ��Ʋ ��ġ�� ��ȯ�ϴ� ��� �Լ�
// ��Ʋ ��ġ�� �ּ� 1
int Character::DiceNumCalc(int dice, int bonus)
{
	if (dice + bonus <= 0)
		return 1;
	else
		return dice + bonus;
}

// ��Ʋ �� �״� ����� ���� ��ȯ�ϴ� ��� �Լ�
// �ν��Ͻ�: ������ ĳ����
// ����: ����� ĳ����
// ��ȯ: (int) 36���� �ֻ��� ���� �� �״� ����� ��(0~36)
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

// �� �������� �� ��� �������� ����ϴ� ��� �Լ�
// �ν��Ͻ�: ����� ĳ����
// ����: ������ ��Ʋ ��ġ ��
// ��ȯ: (double) ��� �� ��� ������
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

// ȸ�Ǹ� �������� �� ��� �������� ����ϴ� ��� �Լ�
// �ν��Ͻ�: ����� ĳ����
// ����: ������ ��Ʋ ��ġ ��
// ��ȯ: (double) ȸ�� �� ��� ������
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


// �� �������� �� �״� ����� ���� ��ȯ�ϴ� ��� �Լ�
// �ν��Ͻ�: ����� ĳ����
// ����: ������ ��Ʋ ��ġ ��
// ��ȯ: (int) �ֻ��� 1~6 �� �״� ����� ��(0~6)
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

// ȸ�Ǹ� �������� �� �״� ����� ���� ��ȯ�ϴ� ��� �Լ�
// �ν��Ͻ�: ����� ĳ����
// ����: ������ ��Ʋ ��ġ ��
// ��ȯ: (int) �ֻ��� 1~6 �� �״� ����� ��(0~6)
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

// ��Ʋ �� ������ ��� ����ϴ� ��� �Լ�
// ��밡 �׻� �ּ��� ����(���Ȯ�� ���� ��, ��� Ȯ�� ������ ��� �������� ���ߴ� ����)�� �Ѵٰ� ����
// �ν��Ͻ�: ������ ĳ����
// ����: ����� ĳ����
// ��ȯ: (double) ������ ���
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