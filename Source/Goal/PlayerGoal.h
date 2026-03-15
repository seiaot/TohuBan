#pragma once

#include "Goal.h"

//ゴール地点クラス
class PlayerGoal : public Goal
{
public:
	//初期化
	void Init();

	//更新
	void Update();

private:

	//コールバック関数
	void OnHit(const Collision& A, const Collision& B);

	//アニメーションの初期化
	void InitAnimaion();

	//開錠判定
	void IsOpen();

private:

	bool mIsOpen;
};