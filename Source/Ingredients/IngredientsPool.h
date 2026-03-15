#pragma once

//食材のプールクラス

//可変長配列std::vectorを使う
#include <vector>

#include "Ingredients.h"

class IngredientsPool
{

public:
	//初期化
	template <class T>
	//引数でプールサイズを渡す
	void Init(int poolSize)
	{
		//プールの全要素分の食材オブジェクトを生成
		for (int i = 0; i < poolSize; ++i)
		{
			//指定されたクラスの変数を1つ生成
			Ingredients* pNewIngredients = new T();
			//初期化
			pNewIngredients->Init();
			//最初は非アクティブ
			pNewIngredients->SetActive(false);
			//プールにアドレスを記録しておく
			mPool.push_back(pNewIngredients);
		}
	}

	//後片付け
	void Term();

	//オブジェクト１つ活性化して戻す
	Ingredients* Alloc();

protected:
	//Ingredients*型の可変長配列
	std::vector<Ingredients*> mPool;
};