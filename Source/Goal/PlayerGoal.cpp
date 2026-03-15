#include "PlayerGoal.h"

//CollisonManagerを使うために必要なのでinclude
#include "Fwk/Framework.h"

//CollisionGroupを使うために必要
#include "GameDef.h"

//上に物の有るゴール数を得る為
#include "GameObjectMng/GameObjectMng.h"

#include "Player/Player.h"



//初期化
void PlayerGoal::Init()
{
	//衝突対象を追加
	mCollision.AddHitGroup((int)CollisionGroup::Player);
	//衝突用のタグを追加
	mCollision.SetTag("PlayerGoal");

	//基底クラスの初期化を呼ぶ
	Goal::Init();

	//テクスチャ変更
	mTexture.Load("Images/tohu/DeadGoal.png");

	//テクスチャの描画範囲を変更
	mSprite.SetTexCoord(0.0f, 0.0f, 1.0f, 1.0f);

	//アニメーションの初期化
	InitAnimaion();

	//開かない
	mIsOpen = false;
}

//更新
void PlayerGoal::Update()
{
	//開錠判定
	IsOpen();

	//基底クラスの更新を呼ぶ
	Goal::Update();
}

//コールバック関数
void PlayerGoal::OnHit(const Collision& A, const Collision& B)
{
	if (mIsOpen)
	{
		//プレイヤーのアドレスを取得
		Player* pPlayer = (Player*)(B.GetOwner());
		//プレイヤーの移動が終わった時に状態を変更させるフラグをオンに
		*(pPlayer->GetIsFalling()) = true;
	}
}

//アニメーションの初期化
void PlayerGoal::InitAnimaion()
{
	//画像一つの大きさ
	float W = 1.0f / 4.0f;
	float H = 1.0f / 2.0f;

	//UV座標リストを作成
	UVRect uv[] =
	{
		{W * 0.0f,H * 1.0f,W,H},
		{W * 1.0f,H * 1.0f,W,H},
		{W * 2.0f,H * 1.0f,W,H},
		{W * 3.0f,H * 1.0f,W,H},
		{},
	};

	//アニメーション変数
	Animation anim;

	//アニメーションデータ作成（2秒間、ループなし）
	CreateAnimationUV(anim, "Open", 5, 2.0f, false, uv);

	//アニメーションにコールバック関数を登録
	anim.SetEventCallback(CreateAnimationEventCallback(PlayerGoal::OnAnimationEvent));
	//スプライトにアニメーションを追加
	mSprite.AddAnimation(anim);
}

//開錠判定
void PlayerGoal::IsOpen()
{
	if (!mIsOpen)
	{
		//アクティブな食材の配列の大きさを取得
		int iActiveSize = GetIngredientsMng()->GetActiveIngredientsSize();
		//上記配列の先頭アドレスを取得
		Ingredients* pGoal = GetIngredientsMng()->GetActiveIngredients();
		//配列の大きさ分繰り返し
		for (int i = 0; i < iActiveSize; ++i)
		{
			//メンバ変数IsGoalで分岐
			if (!(pGoal + i)->IsGoal())
			{
				//一つでもゴール上に無かったら関数を抜ける
				return;
			}
		}

		//開錠
		mIsOpen = true;
		//テクスチャ変更
		mTexture.Load("Images/tohu/Goal.png");
		mSprite.SetTexCoord(0.0f, 0.5f, 0.25f, 0.5f);
	}
}