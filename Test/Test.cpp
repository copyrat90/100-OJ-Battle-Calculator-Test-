#include "pch.h"
#include "Battle.h"

using namespace std;

int main()
{
	Character p1, p2;
	cout << "attacker's stat (HP, ATK, DEF, EVD) >> ";
	cin >> p1.HP >> p1.ATK >> p1.DEF >> p1.EVD;
	cout << "defender's stat (HP, ATK, DEF, EVD) >> ";
	cin >> p2.HP >> p2.ATK >> p2.DEF >> p2.EVD;
	cout << "기대 데미지: " << EstimateDamageBeforeBattle(p1, p2) << endl;
	cout << "킬 확률 : " << (double)KillValueBeforeBattle(p1, p2) / 36 << endl;
	while (cin)
	{
		cout << "Attacker's Battle Number is? >> ";
		int battleNum;
		cin >> battleNum;
		cout << "방어 시 평균 데미지 : " << EstimateDamageDEF(battleNum, p2) << endl;
		cout << "회피 시 평균 데미지 : " << EstimateDamageEVD(battleNum, p2) << endl;
		cout << "방어 시 KO 확률 : " << (double)KillValueDEF(battleNum, p2) / 6 << endl;
		cout << "회피 시 KO 확률 : " << (double)KillValueEVD(battleNum, p2) / 6 << endl;
	}

	return 0;
}
