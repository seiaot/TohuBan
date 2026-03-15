#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"

//Vector2fクラスを使うためのヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

//コリジョンクラスを使うのでinclude
#include "Fwk/Collision/Collision.h"
using namespace Fwk::Collision;

//ゴール地点クラス
class Goal
{
public:
	//初期化
	virtual void Init();
	//終了
	void Term();
	//更新
	virtual void Update();
	//描画
	void Render();

	//アクティブか否かを取得
	bool IsActive();

	bool Goalflg();


	//アクティブ状態を設定
	void SetActive(bool bActive);

	//位置設定
	void SetPosition(Vector2f position);

protected:

	//コールバック関数
	virtual void OnHit(const Collision& A, const Collision& B);

	//アニメーションのコールバック関数
	void OnAnimationEvent(const AnimationEvent& animEvent);

protected:
	//表示用スプライト
	Sprite mSprite;
	//テクスチャ
	Texture mTexture;

	//オブジェクトの位置
	Vector2f mPosition;
	//コリジョン
	Collision mCollision;

	//アクティブ状態
	bool mActive;
	//アニメ再生済みか
	bool mPlayAnim;

};