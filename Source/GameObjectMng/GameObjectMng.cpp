#include "GameObjectMng.h"

#include "Player/Player.h"

#include "Ingredients/IngredientsMng.h"

#include "Goal/GoalMng.h"

//Input_Iを使うためのヘッダファイルをinclude
#include "Fwk/Framework.h"

Tilemap mMap;
Player mPlayer;
IngredientsMng mIngredientsMng;
GoalMng mGoalMng;

//全オブジェクト初期化
void GameObjectInit()
{
	//マップの初期化
	mMap.Init();
	//プレイヤーの初期化
	mPlayer.Init();

	//マップデータををファイルから取得する
	{
		CSVFile mapdataFile;
		mapdataFile.Load("Data/mapdata.csv");
		//CSVDataからマップを生成する
		mMap.CreateMap(mapdataFile.GetCSVData());
	}

	//醤油のプール確保
	mIngredientsMng.GeneratePool("Syoyu", 2);
	//長ねぎのプール確保
	mIngredientsMng.GeneratePool("NagaNegi", 2);
	//ひき肉のプール確保
	mIngredientsMng.GeneratePool("HikiNiku", 2);
	//麻婆の素のプール確保
	mIngredientsMng.GeneratePool("Maaboo", 2);
	{
		//食材の配置データをCSVから取得
		CSVFile csvFile;
		csvFile.Load("Data/Ingredients_Data.csv");
		//CSVをもとに食材を生成、配置
		mIngredientsMng.CreateIngredientsCSV(csvFile.GetCSVData());
	}

	//食材ゴールのプール
	mGoalMng.GeneratePool("IngredientsGoal", 5);
	//プレイヤーゴールのプール
	mGoalMng.GeneratePool("PlayerGoal", 1);
	{
		//CSVから生成
		CSVFile csvFile;
		csvFile.Load("Data/Goal_Data.csv");
		mGoalMng.CreateGoalCSV(csvFile.GetCSVData());
	}
}

//全オブジェクト更新
void GameObjectUpdate()
{
	//プレイヤー
	mPlayer.Update();
	//マップ
	mMap.Update();
	//食材
	mIngredientsMng.Update();
	//ゴール
	mGoalMng.Update();
}

//全オブジェクト描画
void GameObjectRender()
{
	//マップ
	mMap.Render();
	//ゴール
	mGoalMng.Render();
	//プレイヤー
	mPlayer.Render();
	//食材
	mIngredientsMng.Render();
}

//全オブジェクト解放
void GameObjectTerm()
{
	//プレイヤー
	mPlayer.Term();
	//マップ
	mMap.Term();
	//食材
	mIngredientsMng.Term();
	//ゴール
	mGoalMng.Term();
}

//Tilemapクラスのアドレスを返す
Tilemap* GetMap() {
	return &mMap;
}

//Plyerクラスのアドレスを返す
Player* GetPlayer()
{
	return &mPlayer;
}

//IngredientsMngクラスのアドレスを返す
IngredientsMng* GetIngredientsMng()
{
	return &mIngredientsMng;
}

//GoalMngクラスのアドレスを返す
GoalMng* GetGoalMng()
{
	return &mGoalMng;
}