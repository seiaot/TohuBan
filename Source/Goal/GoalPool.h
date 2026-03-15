#pragma once

//ゴールのプールクラス

//可変長配列std::vectorを使う
#include <vector>

#include "Goal.h"

class GoalPool
{

public:
	//初期化
	template <class T>
	//引数でプールサイズを渡す
	void Init(int poolSize)
	{
		//プールの全要素分のゴールオブジェクトを生成
		for (int i = 0; i < poolSize; ++i)
		{
			//指定されたクラスの変数を1つ生成
			Goal* pNewGoal = new T();
			//初期化
			pNewGoal->Init();
			//最初は非アクティブ
			pNewGoal->SetActive(false);
			//プールにアドレスを記録しておく
			mPool.push_back(pNewGoal);
		}
	}

	//後片付け
	void Term();

	//オブジェクト１つ活性化して戻す
	Goal* Alloc();

protected:
	//Goal*型の可変長配列
	std::vector<Goal*> mPool;
};