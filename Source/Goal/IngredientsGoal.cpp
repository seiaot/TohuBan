#include "IngredientsGoal.h"

//CollisonManagerを使うために必要なのでinclude
#include "Fwk/Framework.h"

//CollisionGroupを使うために必要
#include "GameDef.h"

//上に物の有るゴール数を得る為
#include "GameObjectMng/GameObjectMng.h"

//初期化
void IngredientsGoal::Init()
{
	//衝突用のタグを設定
	mCollision.SetTag("IngredientsGoal");
	//基底クラスの初期化を呼び出し
	Goal::Init();

	//描画範囲の変更
	mSprite.SetTexCoord(0.0f, 0.0f, 0.25f, 0.5f);

	//アニメーションの初期化
	InitAnimaion();
}

//アニメーションの初期化
void IngredientsGoal::InitAnimaion()
{
	//画像一つの大きさ
	float W = 1.0f / 4.0f;
	float H = 1.0f / 2.0f;

	//UV座標リスト
	UVRect uv[] =
	{
		{W * 0.0f,H * 0.0f,W,H},
		{W * 1.0f,H * 0.0f,W,H},
		{W * 2.0f,H * 0.0f,W,H},
		{W * 3.0f,H * 0.0f,W,H},
		{},
	};

	//アニメーションの変数
	Animation anim;

	//アニメーションデータの作成
	CreateAnimationUV(anim, "Open", 5, 2.0f, false, uv);

	//アニメーションデータにコールバック関数を登録
	anim.SetEventCallback(CreateAnimationEventCallback(IngredientsGoal::OnAnimationEvent));
	//スプライトにアニメーションを追加
	mSprite.AddAnimation(anim);
}