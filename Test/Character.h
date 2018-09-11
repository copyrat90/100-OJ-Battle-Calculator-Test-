// ĳ���� Ŭ���� ����
// ĳ���ʹ� ���Ȱ� ��Ʋ�� ���õ� �Լ����� ���� Ŭ����

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
public:
	Character(int HP, int ATK, int DEF, int EVD)
		: m_HP(HP), m_ATK(ATK), m_DEF(DEF), m_EVD(EVD)
	{
		if (m_HP <= 0)
		{
			m_HP = 1;
			std::cout << "�ּ� HP 1�� ��������" << std::endl;
		}
	}

	int GetHP(void) { return m_HP; }
	int GetATK(void) { return m_ATK; }
	int GetDEF(void) { return m_DEF; }
	int GetEVD(void) { return m_EVD; }

	int KillValueBeforeBattle(Character& defender);
	double EstimateDamageDEF(int attackNum);
	double EstimateDamageEVD(int attackNum);
	int KillValueDEF(int attackNum);
	int KillValueEVD(int attackNum);
	double EstimateDamageBeforeBattle(Character& defender);

private:
	int DiceNumCalc(int dice, int bonus);

	int m_HP;
	int m_ATK;
	int m_DEF;
	int m_EVD;
};

#endif // CHARACTER_H