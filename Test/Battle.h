#pragma once

#include "pch.h"

int DiceNumCalc(int dice, int bonus);
int KillValueBeforeBattle(Character& attacker, Character& defender);
double EstimateDamageDEF(int attackNum, Character& defender);
double EstimateDamageEVD(int attackNum, Character& defender);
int KillValueDEF(int attackNum, Character& defender);
int KillValueEVD(int attackNum, Character& defender);
double EstimateDamageBeforeBattle(Character& attacker, Character& defender);