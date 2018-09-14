// 캐릭터 클래스 선언
// 캐릭터는 스탯과 배틀과 관련된 함수들을 갖는 클래스

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
			std::cout << "최소 HP 1로 재조정됨" << std::endl;
		}
	}

	int GetHP(void) const { return m_HP; }
	int GetATK(void) const { return m_ATK; }
	int GetDEF(void) const { return m_DEF; }
	int GetEVD(void) const { return m_EVD; }

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
