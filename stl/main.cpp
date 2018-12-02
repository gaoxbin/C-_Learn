/*
 * main.cpp
 *
 *  Created on: 2018年12月1日
 *      Author: Administrator
 */

#include "CSingingCompetition.h"



int main(int argc, char **argv)
{
	CSingingCompetition cSinging;

	cSinging.JoinCompetition();

	cSinging.PrintAllSingerAndScore();

	cSinging.PrintRemainSinger();

	cSinging.FirstKonckout();

	cSinging.SecondKonckout();

	cSinging.Finals();

	return 0;
}



