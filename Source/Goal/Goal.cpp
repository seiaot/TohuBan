#include "Goal.h"

//CollisonManagerを使うために必要なのでinclude
#include "Fwk/Framework.h"

//CollisionGroupを使うために必要
#include "GameDef.h"

//プレイヤーの
#include "GameObjectMng/GameObjectMng.h"

//初期化
void Goal::Init()
{
	//テクスチャの読み込み
	mTexture.Load("Images/tohu/Goal.png");

	//Spriteの初期化と各種設定
	mSprite.Init();
	mSprite.SetTexture(mTexture);
	mSprite.SetSize(64.0f, 64.0f);

	//コリジョンの設定
	{
		//自分はゴールグループのコリジョン
		mCollision.SetGroup((int)CollisionGroup::Goal);
		//コリジョンのオーナーを自分に設定
		mCollision.SetOwner(this);
		//コリジョンの形状を指定（矩形）
		mCollision.SetRect(0.0f,0.0f,1.0f,1.0f);
		//コリジョンを活性状態にしておく
		mCollision.SetActive(true);
		//コリジョン衝突時のコールバック関数を設定
		mCollision.SetCallbackFunction(CreateCollisionEventCallback(Goal::OnHit));
		//コリジョンマネージャーにコリジョンを登録
		CollisionManager_I->Register(&mCollision);
	}

	mPlayAnim = false;
}

//終了
void Goal::Term()
{
	//コリジョンマネージャーから登録解除
	CollisionManager_I->Unregister(&mCollision);
	mSprite.Term();
	mTexture.Unload();
}

//更新
void Goal::Update()
{
	if (*GetPlayer()->GetIsFalling() && !mPlayAnim)
	{
		mSprite.PlayAnimation("Open");
		mPlayAnim = true;
	}

	//スプライトの更新
	mSprite.Update();
}

//描画
void Goal::Render()
{
	mSprite.Draw();
}

//アクティブか否かを取得
bool Goal::IsActive()
{
	return mActive;
}

bool Goal::Goalflg() 
{
	return true;
}

//アクティブ状態の設定
void Goal::SetActive(bool bActive)
{
	//アクティブ状態の変更
	mActive = bActive;
	//コリジョンも同じ状態に
	mCollision.SetActive(bActive);
}

//位置設定
void Goal::SetPosition(Vector2f position)
{
	//スプライトの位置を更新
	mSprite.SetPosition(position);
	//コリジョンの位置も更新
	mCollision.SetPosition(position);
}

//コールバック関数
void Goal::OnHit(const Collision& A, const Collision& B)
{

}

//アニメーションのコールバック関数
void Goal::OnAnimationEvent(const AnimationEvent& animEvent)
{
	switch (animEvent.EventType)
	{
	case AnimationEventType::Completed:

		mSprite.SetVisible(false);
		break;
	}
}