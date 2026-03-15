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

//食材クラス
#include "Ingredients/Ingredients.h"
//食材プールクラス
#include "IngredientsPool.h"

//材料クラス
class IngredientsMng
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
	void GeneratePool(string ingredientsNamne, int poolSize);
	//全オブジェクトプールの破棄
	void DestroyPoolAll();
	//指定した食材のプール破棄
	void DestoryPool(string ingredientsName);

	//食材の生成
	void CreateIngredients(string ingredientsName,Vector2f position);

	//CSVからの生成
	void CreateIngredientsCSV(CSVData* pCsvData);

	//アクティブな食材の配列の先頭アドレスを返す
	Ingredients* GetActiveIngredients();

	//アクティブな食材の配列の大きさを返す
	int GetActiveIngredientsSize();

private:

	//アクティブなオブジェクトのポインタ配列
	vector<Ingredients*> mActiveIngredients;
	//食材ごとのオブジェクトプール
	map<string, IngredientsPool> mIngredientsPools;
	

};