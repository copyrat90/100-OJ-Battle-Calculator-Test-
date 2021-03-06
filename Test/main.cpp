// 100% OJ 배틀 계산기
// 2018.9.11 최종수정


#include "pch.h"

using namespace std;

int main()
{
	int HPbuff, ATKbuff, DEFbuff, EVDbuff;

	cout << "공격측 스탯 (HP, ATK, DEF, EVD) >> ";
	cin >> HPbuff >> ATKbuff >> DEFbuff >> EVDbuff;
	Character Player1(HPbuff, ATKbuff, DEFbuff, EVDbuff);

	cout << "방어측 스탯 (HP, ATK, DEF, EVD) >> ";
	cin >> HPbuff >> ATKbuff >> DEFbuff >> EVDbuff;
	Character Player2(HPbuff, ATKbuff, DEFbuff, EVDbuff);

	double Player1WinRate = (double)Player1.KillValueBeforeBattle(Player2) / 36;
	double Player2EstimateDamage = Player1.EstimateDamageBeforeBattle(Player2);

	double Player2WinRateOriginal = (double)Player2.KillValueBeforeBattle(Player1) / 36;
	double Player1EstimateDamageOriginal = Player2.EstimateDamageBeforeBattle(Player1);
	// Player2 가 KO당해 공격하지 못하는 걸 고려한 Player1의 실제 KO 확률과 기대 데미지
	double Player2WinRateActual = Player2WinRateOriginal * (1 - Player1WinRate);
	double Player1EstimateDamageActual = Player1EstimateDamageOriginal * (1 - Player1WinRate);

	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "방어측이 KO당할 확률 : " << Player1WinRate*100 << "%" << endl;
	cout << "방어측이 받는 평균 데미지: " << Player2EstimateDamage << endl;
	cout << "공격측이 KO당할 확률 : " << Player2WinRateActual*100 << "% (" << Player2WinRateOriginal*100 << "%)" << endl;
	cout << "공격측이 받는 평균 데미지: " << Player1EstimateDamageActual << " (" << Player1EstimateDamageOriginal << ")" << endl;
	cout << endl;

	while (true)
	{
		cout << "공격측의 최종 공격 수치는? >> ";
		int battleNum;
		cin >> battleNum;
		if (!cin) break;

		cout << "방어 시 KO 확률 : " << (double)Player2.KillValueDEF(battleNum) / 6 << endl;
		cout << "회피 시 KO 확률 : " << (double)Player2.KillValueEVD(battleNum) / 6 << endl;
		cout << "방어 시 평균 데미지 : " << Player2.EstimateDamageDEF(battleNum) << endl;
		cout << "회피 시 평균 데미지 : " << Player2.EstimateDamageEVD(battleNum) << endl;
		cout << endl;
	}

	return 0;
}
