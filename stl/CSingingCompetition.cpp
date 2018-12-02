/*
 * CSingingCompetition.cpp
 *
 *  Created on: 2018年12月1日
 *      Author: Administrator
 */

#include "CSingingCompetition.h"

#include <time.h>

CSingingCompetition::CSingingCompetition() {
	// TODO Auto-generated constructor stub
	m_iRound = 0;
	srand((unsigned)time(0));
}

CSingingCompetition::~CSingingCompetition() {
	// TODO Auto-generated destructor stub
}

void PrintMap(const pair<int, Singer> &pa)
{
	cout << "参赛号："<< pa.first << " "<< ((Singer)(pa.second)).strName
			<<" 得分："<< ((Singer)pa.second).iLatestScore << endl;
}

void CSingingCompetition::PrintAllSingerAndScore()
{
	for_each(m_mapSinger.begin(), m_mapSinger.end(), PrintMap);
}

void PrintList(int id)
{
	cout << id << " ";
}

void CSingingCompetition::PrintRemainSinger()
{
	cout << "Remain Singer ID:"<<endl;
	for_each(m_listRemainingID.begin(), m_listRemainingID.end(), PrintList);
	cout << " ";
}

void CSingingCompetition::JoinCompetition()
{
	string strNameBaseSource = "ABCDEFGHIJKLMNOPQSRTUVWXYZ";

	random_shuffle(strNameBaseSource.begin(), strNameBaseSource.end());

	for(int i = 0; i < 24; i ++) {

		string strExt(1, strNameBaseSource[i]);

		// 构造对象
		Singer siners;
		siners.strName.empty();

		siners.iLatestScore = 0;
		//string str = strNameBaseSource[i];
//		cout << strNameBaseSource[i]<< endl;
		siners.strName = "选手" + strExt;

		// 录入选手信息
		m_mapSinger.insert(pair<int, Singer>(100 + i, siners));
		m_listRemainingID.push_back(100 + i);
	}
}

void CSingingCompetition::FirstKonckout()
{
	if(m_iRound == 0) {
		m_iRound = 1;

		// 淘汰赛
		Konckout();

		// 打印淘汰歌手名字
		cout << "第"<<m_iRound <<"轮淘汰赛中被淘汰的歌手名字"<< endl;
		for(vector<int>::iterator it = m_vecIDBeEliminatedInFirstRound.begin();
				it != m_vecIDBeEliminatedInFirstRound.end(); ++it) {
			cout << m_mapSinger[*it].strName << " ";
		}

		cout <<endl <<endl;
	}
}

void CSingingCompetition::SecondKonckout()
{
	if(m_iRound == 1) {
		m_iRound = 2;

		// 淘汰赛
		Konckout();

		// 打印淘汰歌手名字
		cout << "第"<<m_iRound <<"轮淘汰赛中被淘汰的歌手分数"<< endl;
		for(multiset<int>::iterator it = m_mltsetScoreBeEliminatedInSecondRound.begin();
				it != m_mltsetScoreBeEliminatedInSecondRound.end(); ++it) {
			cout << *it << " ";
		}

		cout <<endl <<endl;
	}
}

void CSingingCompetition::Konckout()
{
	cout << "************第"<<m_iRound<<"轮淘汰赛：*****************"<<endl;

	int iSingerIndex = 0;
	for(list<int>::iterator it=m_listRemainingID.begin();
			it!= m_listRemainingID.end();) {
		++iSingerIndex;

		// make socore
		MakeScore(m_mapSinger[*it]);

		// 记录当前组得分，降序排序
		m_mltmapCurGorup.insert(pair<int, int>(m_mapSinger[*it].iLatestScore, *it));

		if(iSingerIndex % 6 == 0) {
			// 小组完毕，打印得分和淘汰删除歌手

			// 小组演唱完毕，打印小组得分情况
			PrintGroupScore();

			// 在当前小组中淘汰歌手
			EraseInCurGroup();

			// 在剩余歌手中删除歌手
			EraseInRemainingID(it++);

		} else {
			++it;
		}
	}
}

void CSingingCompetition::EraseInRemainingID(list<int>::iterator it)
{
	// 逆向遍历索引
	int iSingerReverseIndexInGroup = 0;

	while(iSingerReverseIndexInGroup < 6) {
		multimap<int, int, greater<int>>::iterator itMltmapScoreToID =
				find(m_mltmapCurGorup.begin(), m_mltmapCurGorup.end(),
					multimap<int, int, greater<int>>::value_type(m_mapSinger[*it].iLatestScore, *it));
		if(itMltmapScoreToID == m_mltmapCurGorup.end()) {
			// 没找到，从剩余歌手删除歌手参赛号
			it = m_listRemainingID.erase(it);
		}

		++iSingerReverseIndexInGroup;

		// 防止容器的begin迭代器进行--操作
		if(it != m_listRemainingID.begin()) {
			--it;
		}
	}

	m_mltmapCurGorup.clear();
}


void CSingingCompetition::EraseInCurGroup()
{
	int iSingerLastIndexInGroup = 0;

	while(iSingerLastIndexInGroup < 3) {
		multimap<int, int, greater<int>>::iterator it =
				m_mltmapCurGorup.end();
		--it;

		++iSingerLastIndexInGroup;

		if(m_iRound == 1) {
			m_vecIDBeEliminatedInFirstRound.push_back(it->second);
		} else if(m_iRound == 2) {
			m_mltsetScoreBeEliminatedInSecondRound.insert(m_mapSinger[it->second].iLatestScore);
		}
		m_mltmapCurGorup.erase(it);
	}
}

void CSingingCompetition::PrintGroupScore()
{
	cout << "小组得分情况："<<endl;

	for(multimap<int, int, greater<int>>::iterator it =
			m_mltmapCurGorup.begin(); m_mltmapCurGorup.end() != it; ++it) {
		cout << m_mapSinger[it->second].strName<< " 得分："<< it->first << endl;
	}
	cout << endl;
}

void CSingingCompetition::MakeScore(Singer &siner)
{
	deque<int> deqSocre;

	// make socre
	for(int i = 0; i < 10; ++ i) {
		int iScore = 60 + rand()%40;
		deqSocre.push_back(iScore);
	}

	// 从高到低排序
	sort(deqSocre.begin(), deqSocre.end());

	// 去掉最高分
	deqSocre.pop_front();
	// 去掉最低分
	deqSocre.pop_back();

	// 八个评委总和
	int iSocreSum = accumulate(deqSocre.begin(), deqSocre.end(), 0);

	// 平均分
	int iSocreAverage = iSocreSum / deqSocre.size();

	// 设置得分
	siner.iLatestScore = iSocreAverage;
}

void CSingingCompetition::Finals()
{
	if(m_iRound == 2) {
		m_iRound = 3;

		for(list<int>::iterator it = m_listRemainingID.begin();
				it != m_listRemainingID.end(); ++it) {

			// make socore
			MakeScore(m_mapSinger[*it]);

			// 记录当前组得分，降序排序
			m_mltmapCurGorup.insert(pair<int, int>(m_mapSinger[*it].iLatestScore, *it));
		}
		 // 打印决赛歌手名字
		cout <<"********决赛情况********"<< endl;
		for(multimap<int, int, greater<int>>::iterator it =
				m_mltmapCurGorup.begin(); m_mltmapCurGorup.end() != it; ++it) {
			cout << m_mapSinger[it->second].strName
					<< m_mapSinger[it->second].strName<< " 得分："<< it->first << endl;
		}
		cout << endl;

		// 清楚所有的数据
		m_mapSinger.clear();
		m_listRemainingID.clear();
		m_vecIDBeEliminatedInFirstRound.clear();
		m_mltsetScoreBeEliminatedInSecondRound.clear();
		m_mltmapCurGorup.clear();
		m_iRound = 0;
	}
}
