#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"

//Vector2fクラスを使う為のヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

//向きの定数を使うのでinclude
#include "GameDef.h"

#include "Fwk/Collision/Collision.h"
using namespace Fwk::Collision;

//現在の状態を表す列挙型
enum class Status {
	Idle,
	Moving,
	Falling,
};

//プレイヤークラス
class Player {

public:

	//プレイヤーの初期化
	void Init();

	//プレイヤーの更新
	void Update();

	//プレイヤーの描画
	void Render();

	//プレイヤーの後片付け
	void Term();

	//プレイヤーの向きの取得
	Direction GetDirection();

	//プレイヤーの状態のアドレスの取得
	bool* GetIsFalling();

	//タイマーのアドレスの取得
	float* GetTimer();

	//手数の取得
	int GetMoveNum();

private:
	//アニメーションの初期化
	void _initAnimation();
	
	//アイドル時の処理
	void UpdateIdle();
	//移動時の処理
	void UpdateMoving();
	//落下中に処理
	void UpdateFalling();

	//入力を取得
	void Input();
	//移動可能か判定
	bool CanMove();
	//移動先に食材が有るかの判定
	bool IsIngredientsThere(Vector2f position);

private:
	//表示用スプライト
	Sprite mSprite;
	//テクスチャ
	Texture mTexture;

	//オブジェクトの位置
	Vector2f mPosition;
	//移動先の座標
	Vector2f mTargetPos;
	//現在の移動量
	Vector2f mMove;

	//現在の向き
	Direction mDirection;
	//現在の状態
	Status mStatus;
	//食材を押しているか
	bool mIsPushing;
	//落下状態に移れるか
	bool mIsFalling;

	//コリジョン
	Collision mCollision;

	//タイマー
	float mTimer;
	//動いた回数
	int mMoveNum;
};