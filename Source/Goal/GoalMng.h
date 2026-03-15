#pragma once

#include <string>
#include <vector> //可変長配列のため
#include <map>	//連想配列
using namespace std;

//Vector2fクラスを使う為のヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

//CSVデータを使う
#include "Fwk/File/CSVFile.h"

//ゴールクラス
#include "Goal/Goal.h"
//ゴールプールクラス
#include "GoalPool.h"

//材料クラス
class GoalMng
{
public :

	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Render();
	//後片付け
	void Term();

	//オブジェクトプールの生成
	void GeneratePool(string GoalNamne, int poolSize);
	//全オブジェクトプールの破棄
	void DestroyPoolAll();
	//指定したゴールのプール破棄
	void DestoryPool(string GoalName);

	//ゴールの生成
	void CreateGoal(string GoalName,Vector2f position);

	//CSVからの生成
	void CreateGoalCSV(CSVData* pCsvData);

private:

	//アクティブなオブジェクトのポインタ配列
	vector<Goal*> mActiveGoal;
	//ゴールごとのオブジェクトプール
	map<string, GoalPool> mGoalPools;
};