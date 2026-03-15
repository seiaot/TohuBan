#include "IngredientsMng.h"

//GetMapを使う為
#include "GameObjectMng/GameObjectMng.h"

//SaFE_DELETEを使う為に
#include "Lib/LibDef.h"

//扱うクラスの読み込み
#include "Syoyu.h"
#include "NagaNegi.h"
#include "HikiNiku.h"
#include "Maaboo.h"

//初期化
void IngredientsMng::Init()
{
	//アクティブなポインタの配列を空に
	mActiveIngredients.clear();
}

//更新
void IngredientsMng::Update()
{
	//アクティブな食材全て更新
	for (int i = 0; i < mActiveIngredients.size(); ++i)
	{
		mActiveIngredients[i]->Update();
	}

	//更新後非アクティブとなったものがあるならば取り除く
	for (int i = 0; i < mActiveIngredients.size(); ++i)
	{
		if (mActiveIngredients[i]->IsActive())
		{
			//mActiveIngredients[i]がアクティブのままであれば
			//次の要素を処理するのでiをインクリメント
			++i;
		}
		else
		{
			//mActiveIngredients[i]が非アクティブとなっていたらその要素を取り除く
			mActiveIngredients.erase(mActiveIngredients.begin() + i);

			//※ここでは i をインクリメントしない
			//要素が取り除かれたら後の要素が前に詰められるらしい
		}
	}

}

//描画
void IngredientsMng::Render()
{
	//アクティブな食材全て表示
	for (int i = 0; i < mActiveIngredients.size(); ++i)
	{
		mActiveIngredients[i]->Render();
	}
}

//後片付け
void IngredientsMng::Term()
{
	//アクティブなポインタの配列を空に
	mActiveIngredients.clear();
	//全部の食材プールを破棄
	DestroyPoolAll();
}

//オブジェクトプールの生成
void IngredientsMng::GeneratePool(string ingredientsNamne, int poolSize)
{
	//醤油
	if (ingredientsNamne == "Syoyu")
	{
		mIngredientsPools[ingredientsNamne].Init<Syoyu>(poolSize);
	}

	//長ねぎ
	if (ingredientsNamne == "NagaNegi")
	{
		mIngredientsPools[ingredientsNamne].Init<NagaNegi>(poolSize);
	}

	//ひき肉
	if (ingredientsNamne == "HikiNiku")
	{
		mIngredientsPools[ingredientsNamne].Init<HikiNiku>(poolSize);
	}

	//麻婆の素
	if (ingredientsNamne == "Maaboo")
	{
		mIngredientsPools[ingredientsNamne].Init<Maaboo>(poolSize);
	}
}

//全オブジェクトプールの破棄
void IngredientsMng::DestroyPoolAll()
{
	//バッファの破棄
	//醤油
	DestoryPool("Syoyu");
	//長ねぎ
	DestoryPool("NagaNegi");
	//ひき肉
	DestoryPool("HikiNiku");
	//麻婆の素
	DestoryPool("Maaboo");
}

//指定した食材のプール破棄
void IngredientsMng::DestoryPool(string ingredientsName)
{
	//食材プールの破棄
	if (mIngredientsPools.count(ingredientsName) > 0)
	{
		//食材クラスの片づけを呼んでいる
		mIngredientsPools[ingredientsName].Term();
		//指定された名前の要素を削除している？
		mIngredientsPools.erase(ingredientsName);
	}
}

//食材の生成
void IngredientsMng::CreateIngredients(string ingredientsName, Vector2f position)
{
	//取得した非アクティブのオブジェクトのアドレスを保存するポインター型変数
	Ingredients* pIngredients = nullptr;

	//特定の名前の要素数が0より大きかったら非アクティブのオブジェクトがある
	//そしたら変数にその名前に対応した値のうち一つを代入（？）
	if (mIngredientsPools.count(ingredientsName) > 0)
	{
		pIngredients = mIngredientsPools[ingredientsName].Alloc();
	}

	//非アクティブの敵がいない（上のifが処理されずにnullのまま）
	if (pIngredients == nullptr)
	{
		return;
	}

	//位置を設定
	pIngredients->SetPosition(position);

	//アクティブな食材の配列に追加
	mActiveIngredients.push_back(pIngredients);
}

//CSVからの生成
void IngredientsMng::CreateIngredientsCSV(CSVData* pCsvData)
{
	//引数がnullなら何もしない
	if (pCsvData == nullptr)
	{
		return;
	}

	//名前、X、Yの3つで1組
	//食材の数を判定
	int ingredientsNum = pCsvData->GetElementCount() / 3;
	//食材の数分繰り返し
	for (int i = 0; i < ingredientsNum; ++i)
	{
		//配置データの先頭（名前）の要素番号（列数）
		int index = i * 3;
		//名前の取得
		string  ingredientsName;
		pCsvData->GetString(index, &ingredientsName);
		//配置先の座標
		Vector2f position;
		float TileSize = GetMap()->GetTileSize();
		position.x = (float)pCsvData->GetInt(index + 1) * TileSize + TileSize / 2;
		position.y = (float)-(pCsvData->GetInt(index + 2) * TileSize + TileSize / 2);

		//取り出した値をもとに生成
		CreateIngredients(ingredientsName, position);
	}

}

//アクティブな食材の配列の先頭アドレスを返す
Ingredients* IngredientsMng::GetActiveIngredients()
{
	return mActiveIngredients[0];
}

//アクティブな食材の配列の大きさを返す
int IngredientsMng::GetActiveIngredientsSize()
{
	return mActiveIngredients.size();
}