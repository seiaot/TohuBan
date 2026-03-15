#pragma once

#include "Goal.h"

//ゴール地点クラス
class IngredientsGoal : public Goal
{
public:
	//初期化
	void Init();

private:

	//アニメーションの初期化
	void InitAnimaion();
};