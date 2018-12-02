/*
 * CSingingCompetition.h
 *
 *  Created on: 2018年12月1日
 *      Author: Administrator
 */

#ifndef CSINGINGCOMPETITION_H_
#define CSINGINGCOMPETITION_H_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

/**
 * 1.打印出所有选手的名字与参赛号，并以升序排序
 *
 * 2.打印第一轮和第二轮淘汰赛中，各小组名字和得分，并以名次顺序排序
 *
 *
 */

struct Singer {
	string strName;
	int iLatestScore;
};

class CSingingCompetition {
public:
	CSingingCompetition();
	virtual ~CSingingCompetition();

	// 报名参加比赛
	void JoinCompetition();

	// 第一轮淘汰赛
	void FirstKonckout();

	// 第二轮淘汰赛
	void SecondKonckout();

	// 决赛
	void Finals();

// private:
	void PrintAllSingerAndScore();
	void PrintRemainSinger();
	void EraseInRemainingID(list<int>::iterator it);

private:
	void Konckout();
	void MakeScore(Singer &siner);
	void PrintGroupScore();
	void EraseInCurGroup();

private:
	map<int, Singer> m_mapSinger; // 参赛选手
	list<int> m_listRemainingID; // 剩余选手

	multimap<int, int, greater<int>> m_mltmapCurGorup;// 当前组得分集合

	vector<int> m_vecIDBeEliminatedInFirstRound;// 第一轮淘汰歌手
	//vector<int> m_vecIDBeEliminatedInSecondRound;// 第二轮淘汰歌手
	multiset<int> m_mltsetScoreBeEliminatedInFirstRound;// 第一轮淘汰歌手分数
	multiset<int> m_mltsetScoreBeEliminatedInSecondRound;// 第二轮淘汰歌手分数

	int m_iRound; // 轮数标识

};

#endif /* CSINGINGCOMPETITION_H_ */
