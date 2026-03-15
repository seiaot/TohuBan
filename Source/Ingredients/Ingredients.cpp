#include "Ingredients.h"

//コリジョングループの列挙型を使うために#include
#include "GameDef.h"
//CollisionManagerを使うのでinclude
#include "Fwk/Framework.h"
//GetMapを使う為GameObjectMng.hをinclude
#include "GameObjectMng/GameObjectMng.h"

//Vector2fクラスを使う為のヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

//プレイヤーの向きを扱う
#include "Player/Player.h"

//材料の初期化
void Ingredients::Init()
{
	//テクスチャの読み込み
	mTexture.Load("Images/tohu/Ingredients.png");

	mPosition = { 0.0f,0.0f };

	//スプライト
	mSprite.Init();
	mSprite.SetTexture(mTexture);
	mSprite.SetSize(64.0f, 64.0f);

	mSprite.SetPosition(mPosition);

	//コリジョンの設定
	{
		//自分は食材グループのコリジョン
		mCollision.SetGroup((int)CollisionGroup::Ingredients);
		//衝突対象にコリジョンを追加
		mCollision.AddHitGroup((int)CollisionGroup::Player);
		mCollision.AddHitGroup((int)CollisionGroup::Goal);
		//コリジョンにタグを設定
		mCollision.SetTag("Ingredients");
		//コリジョンのオーナーに自分を設定
		mCollision.SetOwner(this);
		//コリジョンを活性状態にしておく
		mCollision.SetActive(true);
		//コリジョンの形状を指定
		mCollision.SetRect(0.0f, 0.0f, 64.0f, 64.0f);
		//コリジョン衝突時のコールバック関数を設定
		mCollision.SetCallbackFunction(CreateCollisionEventCallback(Ingredients::OnHit));
		//コリジョンマネージャーにコリジョンを登録
		CollisionManager_I->Register(&mCollision);
	}

	//初期状態はアイドル
	mStatus = Status::Idle;

	//
	mIsGoal = false;
}

//材料の更新
void Ingredients::Update()
{
	//状態による分岐
	switch (mStatus)
	{
		//アイドル状態
	case Status::Idle:

		UpdateIdle();
		break;

		//移動中
	case Status::Moving:
	{
		//移動用関数に移動先座標を渡す
		UpdateMoving(TargetPos);
	}
		break;

		//落下中
	case Status::Falling:

		UpdateFalling();
		break;
	}

	mSprite.Update();
	mSprite.SetPosition(mPosition);
	mCollision.SetPosition(mPosition);
}

//材料の描画
void Ingredients::Render()
{
	mSprite.Draw();
}

//材料の後片付け
void Ingredients::Term()
{
	mTexture.Unload();
	mSprite.Term();
	CollisionManager_I->Register(&mCollision);
}

//アクティブか否かを取得
bool Ingredients::IsActive()
{
	return mActive;
}

//アクティブ状態の設定
void Ingredients::SetActive(bool bActive)
{
	//アクティブ状態の変更
	mActive = bActive;
	//コリジョンも同じ状態に
	mCollision.SetActive(bActive);
}

//位置を返す
Vector2f Ingredients::GetPosition()
{
	return mPosition;
}

//現在位置を設定
void Ingredients::SetPosition(Vector2f position)
{
	mPosition = position;
	mSprite.SetPosition(mPosition);
	//コリジョンの位置も更新
	mCollision.SetPosition(mPosition);
}

//ゴールの上か否か取得
bool Ingredients::IsGoal()
{
	return mIsGoal;
}

//コールバック関数
void Ingredients::OnHit(const Collision& A, const Collision& B)
{
	if (B.GetTag() == "Player")
	{
		//引数により使う値を変化させる為の配列
		Vector2f Movement[4] = { {0.0f,-64.0f},{64.0f,0.0f},{0.0f,64.0f},{-64.0f,0.0f} };

		//衝突したプレイヤーのアドレスを取得
		Player* pPlayer = (Player*)(B.GetOwner());
		//プレイヤーの現在の向きを取得
		Direction MoveDirection = pPlayer->GetDirection();

		//移動先座標に現在地と移動量を足した値を代入
		TargetPos = mPosition + Movement[(int)MoveDirection];

		//移動先が壁じゃないなら移動を開始
		if (!GetMap()->IsWall(TargetPos))
		{
			//状態を移動中に変更
			mStatus = Status::Moving;
			//衝突判定を非活性に
			mCollision.SetActive(false);
		}
	}

	if (B.GetTag() == "IngredientsGoal")
	{
		mIsGoal = true;
	}

}

//アイドル
void Ingredients::UpdateIdle()
{
	if (*(GetPlayer()->GetIsFalling()))
	{
		mStatus = Status::Falling;
	}
}

//移動
void Ingredients::UpdateMoving(Vector2f TargetPos)
{
	//フレームでの移動量
	float fSpeed = 120.0f * Time_I->GetDeltaTime();

	//現在位置から目的地までの距離がこのフレームでの移動量より大きい（遠い）
	if ((TargetPos - mPosition).GetLength() > fSpeed)
	{
		//現在位置に移動向きベクトルｘ移動量を足しこむ
		mPosition += ((TargetPos - mPosition).GetNormalized() * fSpeed);
	}
	else
	{
		//現在位置から目的地までの距離がこのフレームでの移動量より小さい（短い）場合
		//このフレームで目的地に到達することになるので現在位置を目的地に設定
		mPosition = TargetPos;
		//アイドル状態に戻す
		mStatus = Status::Idle;
		//衝突復活
		mCollision.SetActive(true);
		//ゴール剥奪
		mIsGoal = false;
	}
}

//落下
void Ingredients::UpdateFalling()
{
	//少しづつ小さく
	float W = mSprite.GetWidth();
	float H = mSprite.GetHeight();
	mSprite.SetSize(W - W / 100.0f, H - H / 100.0f);
}