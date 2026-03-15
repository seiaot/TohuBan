#include "Player.h"

//Input_Iを使うためのヘッダファイルをinclude
#include "Fwk/Framework.h"

//GetMapを使う為GameObjectMng.hをinclude
#include "GameObjectMng/GameObjectMng.h"

//プレイヤーの初期化
void Player::Init()
{
	//位置の初期化
	mPosition = { 1.0f * 64.0f + 32.0f,-(1.0f * 64.0f + 32.0f) };
	//初期状態はアイドル
	mStatus = Status::Idle;
	//最初は何も押していない
	mIsPushing = false;
	//初期状態落下出来ない
	mIsFalling = false;
	//タイマーの初期化
	mTimer = 0.0f;
	//手数の初期化
	mMoveNum = 0;

	//テクスチャの読み込み
	mTexture.Load("Images/tohu/tofukunn.png");

	//スプライトの初期化
	mSprite.Init();
	mSprite.SetTexture(mTexture);
	mSprite.SetSize(64.0f, 64.0f);
	mSprite.SetPosition(mPosition);

	//アニメーションの初期化
	_initAnimation();

	//コリジョンの設定
	{
		//自分はプレイヤーグループのコリジョン
		mCollision.SetGroup((int)CollisionGroup::Player);
		//衝突対象にプレイヤーグループのコリジョンを追加
		mCollision.AddHitGroup((int)CollisionGroup::Ingredients);
		//コリジョンにタグを設定
		mCollision.SetTag("Player");
		//コリジョンのオーナーに自分を設定
		mCollision.SetOwner(this);
		//コリジョンを活性状態にしておく
		mCollision.SetActive(true);
		//コリジョンの形状を指定(少し小さめにしないと隣に立てない)
		mCollision.SetRect(0.0f, 0.0f, 63.99f, 63.99f);
		//コリジョンマネージャーにコリジョンを登録
		CollisionManager_I->Register(&mCollision);
	}
}

//プレイヤーの更新
void Player::Update()
{
	switch (mStatus)
	{
	case Status::Idle:

		UpdateIdle();
		break;

	case Status::Moving:

		UpdateMoving();
		break;

	case Status::Falling:

		UpdateFalling();
		break;
	}

	// 向きを更新
	if (mMove.GetLength() != 0.0f) {
		if (fabsf(mMove.x) > fabsf(mMove.y)) {
			//移動ベクトルのx成分がy成分より大きい場合
			//移動ベクトルのx成分が負数であれば左向き、でなければ右向き
			mDirection = (mMove.x < 0.0f) ? Direction::Left : Direction::Right;
		}
		else {
			//移動ベクトルのy成分がx成分より大きい場合
			//移動ベクトルのy成分が負数であれば前向き、でなければ後ろ向き
			mDirection = (mMove.y < 0.0f) ? Direction::Front : Direction::Back;
		}
	}

	//アニメーションの更新
	{
		//アイドル時のアニメーション名
		const string animName_idle[] = { "idle_front","idle_right","idle_back","idle_left" };
		//歩行時のアニメーション名
		const string animName_walk[] = { "walk_front","walk_right","walk_back","walk_left" };
		//押し時のアニメーション名
		const string animName_push[] = { "push_front","push_right","push_back","push_left" };

		//再生するアニメーション名
		string playAnimName;

		//アイドル時のアニメ
		if (mStatus == Status::Idle || mStatus == Status::Falling) 
		{
			//向きに応じたアイドル時のアニメを選択
			playAnimName = animName_idle[(int)mDirection];
		}
		//移動時のアニメ
		else 
		{
			//食材を押していたら押すアニメ
			if (mIsPushing)
			{
				playAnimName = animName_push[(int)mDirection];
			}
			else
			{
				//通常の移動時アニメ
				playAnimName = animName_walk[(int)mDirection];
			}
		}

		//再生するアニメを選択
		//第二引数は"既に同じアニメを再生していた場合そのまま継続する"という指定
		mSprite.PlayAnimation(playAnimName, AnimationPlayStyle::Continue);
	}

	//スプライトの位置を更新
	mSprite.SetPosition(mPosition);
	mCollision.SetPosition(mPosition);

	//スプライトの更新
	mSprite.Update();

}

//アイドル時の処理
void Player::UpdateIdle()
{
	//入力を取得
	Input();

	//移動可能か判定
	if (CanMove())
	{
		//移動カウント加算
		mMoveNum += 1;
		//可能なら状態を変更
		mStatus = Status::Moving;
	}
}

//移動時の処理
void Player::UpdateMoving()
{
	//スピードを初期化
	float speed = 120.0f * Time_I->GetDeltaTime();
	//現在位置から目的地までの距離がこのフレームでの移動量より大きい(速い)
	if ((mTargetPos - mPosition).GetLength() > speed) {
		//目的地までの向きベクトルを作って
		Vector2f vDirection = (mTargetPos - mPosition).GetNormalized();
		//現在位置に移動向きベクトル×移動量を足しこむ
		mPosition += (vDirection * speed);
	}
	else {
		//現在位置から目的地までの距離がこのフレームでの移動量より小さい(短い)場合
		//このフレームでの目的地に到達するこのになるので現在位置を目的地に設定
		mPosition = mTargetPos;

		//落下状態に移れる状態なら
		if (mIsFalling)
		{
			//状態変更
			mStatus = Status::Falling;
			return;
		}

		//入力を取得
		Input();
		//引き続き移動可能なら
		if (CanMove())
		{
			//移動カウント加算
			mMoveNum += 1;
			//食材の無い方向に移動
			if (!IsIngredientsThere(mTargetPos))
			{
				//押していない状態に戻す
				mIsPushing = false;
			}
		}
		else
		{
			//アイドル状態に戻す
			mStatus = Status::Idle;
			//押していない状態に戻す
			mIsPushing = false;
		}
	}
}

//落下中の処理
void Player::UpdateFalling()
{
	//少しづつ小さく
	float W = mSprite.GetWidth();
	float H = mSprite.GetHeight();
	mSprite.SetSize(W - W / 100.0f, H - H / 100.0f);
	//タイマー加算
	mTimer += Time_I->GetDeltaTime();
}

//入力を取得
void Player::Input()
{
	//タイルのサイズ
	float TileSize = GetMap()->GetTileSize();

	Input_I->GetStickInput(0, GAMEPAD_STICK::LEFT, &mMove);

	// キーボードの入力を取得
	if (Input_I->IsKeyPressed(VK_UP) || Input_I->IsKeyPressed('W')) {
		mMove.y = TileSize;  // 上
	}
	if (Input_I->IsKeyPressed(VK_DOWN) || Input_I->IsKeyPressed('S')) {
		mMove.y = -TileSize;   // 下
	}
	if (Input_I->IsKeyPressed(VK_LEFT) || Input_I->IsKeyPressed('A')) {
		mMove.x = -TileSize;  // 左
	}
	if (Input_I->IsKeyPressed(VK_RIGHT) || Input_I->IsKeyPressed('D')) {
		mMove.x = TileSize;   // 右
	}
}

//移動可能か判定
bool Player::CanMove()
{
	//戻り値用変数
	bool bRetu = false;

	//斜め移動を弾く
	if ((mMove.x != 0.0f && mMove.y == 0.0f)
		|| (mMove.x == 0.0f && mMove.y != 0.0f))
	{
		//移動先座標を作成
		mTargetPos = mPosition + mMove;

		//移動先に食材があるかの判定
		if (IsIngredientsThere(mTargetPos))
		{
			//有ったらもう一つ先の座標を調べる
			//もう一つ先の座標
			Vector2f vTargetPos = mTargetPos + mMove;

			//そこが食材でも壁でもないなら動ける
			if (!IsIngredientsThere(vTargetPos) && !GetMap()->IsWall(vTargetPos))
			{
				//移動可能
				bRetu = true;
				//食材を押している状態に変更
				mIsPushing = true;
			}
		}
		//食材が無ければ壁か調べる
		else if (!GetMap()->IsWall(mTargetPos))
		{
			//移動可能
			bRetu = true;
		}
	}

	//返す
	return bRetu;
}

//移動先に食材が有るかの判定
bool Player::IsIngredientsThere(Vector2f position)
{
	//戻り値用の変数
	bool bRetu = false;
	//アクティブな食材の配列の先頭アドレスを取得
	Ingredients* pIngredients = GetIngredientsMng()->GetActiveIngredients();

	//アクティブな食材の配列の大きさ分繰り返し
	for (int i = 0; i < GetIngredientsMng()->GetActiveIngredientsSize(); ++i)
	{
		//対象の座標に多少の幅を持たせる
		float W = 32.0f;
		float H = 32.0f;
		//食材の座標を代入
		Vector2f vIngredientsPos = (pIngredients + i)->GetPosition();
		//移動先の上下左右の一定範囲内に食材の座標が有ったら
		if (
			position.x - W < vIngredientsPos.x && position.x + W > vIngredientsPos.x
			&& position.y + H > vIngredientsPos.y && position.y - H < vIngredientsPos.y
			)
		{
			bRetu = true;
		}
	}

	//結果を返す
	return bRetu;
}

//プレイヤーの描画
void Player::Render()
{
	mSprite.Draw();
}

//アニメーションの初期化
void Player::_initAnimation()
{
	//UVの幅と高さ
	float uvW = 1.0f / 8.0f;
	float uvH = 1.0f / 3.0f;

	//スプライトセル構造体リスト
	UVRect uvs[] = 
	{
		{uvW * 0.0f,uvH * 0.0f,uvW,uvH}, //アイドル　前向き
		{uvW * 2.0f,uvH * 0.0f,uvW,uvH}, //アイドル　右向き
		{uvW * 4.0f,uvH * 0.0f,uvW,uvH}, //アイドル　後ろ向き
		{uvW * 6.0f,uvH * 0.0f,uvW,uvH}, //アイドル　左向き

		{uvW * 0.0f,uvH * 1.0f,uvW,uvH}, //移動 前向き　パターン１
		{uvW * 1.0f,uvH * 1.0f,uvW,uvH}, //移動 前向き　パターン２
		{uvW * 2.0f,uvH * 1.0f,uvW,uvH}, //移動 右向き　パターン１
		{uvW * 3.0f,uvH * 1.0f,uvW,uvH}, //移動 右向き　パターン２
		{uvW * 4.0f,uvH * 1.0f,uvW,uvH}, //移動 後向き　パターン１
		{uvW * 5.0f,uvH * 1.0f,uvW,uvH}, //移動 後向き　パターン２
		{uvW * 6.0f,uvH * 1.0f,uvW,uvH}, //移動 左向き　パターン１
		{uvW * 7.0f,uvH * 1.0f,uvW,uvH}, //移動 左向き　パターン２

		{uvW * 0.0f,uvH * 2.0f,uvW,uvH}, //押し 前向き　パターン１
		{uvW * 1.0f,uvH * 2.0f,uvW,uvH}, //押し 前向き　パターン２
		{uvW * 2.0f,uvH * 2.0f,uvW,uvH}, //押し 右向き　パターン１
		{uvW * 3.0f,uvH * 2.0f,uvW,uvH}, //押し 右向き　パターン２
		{uvW * 4.0f,uvH * 2.0f,uvW,uvH}, //押し 後向き　パターン１
		{uvW * 5.0f,uvH * 2.0f,uvW,uvH}, //押し 後向き　パターン２
		{uvW * 6.0f,uvH * 2.0f,uvW,uvH}, //押し 左向き　パターン１
		{uvW * 7.0f,uvH * 2.0f,uvW,uvH}, //押し 左向き　パターン２
	};

	//プレイヤーのアイドル時のアニメ
	UVRect idle_front[] = { uvs[0] };	//前
	UVRect idle_right[] = { uvs[1] };	//右
	UVRect idle_back[] = { uvs[2] };	//後
	UVRect idle_left[] = { uvs[3] };	//左

	//プレイヤー移動時のアニメ
	//前
	UVRect walk_front[] = 
	{
		uvs[4],
		uvs[5],
		{}
	};
	//右
	UVRect walk_right[] = 
	{
		uvs[6],
		uvs[7],
		{}
	};
	//後
	UVRect walk_back[] = 
	{
		uvs[8],
		uvs[9],
		{}
	};
	//左
	UVRect walk_left[] = 
	{
		uvs[10],
		uvs[11],
		{}
	};

	//プレイヤー押し時のアニメ
	//前
	UVRect push_front[] =
	{
		uvs[12],
		uvs[13],
		{}
	};
	//右
	UVRect push_right[] =
	{
		uvs[14],
		uvs[15],
		{}
	};
	//後
	UVRect push_back[] =
	{
		uvs[16],
		uvs[17],
		{}
	};
	//左
	UVRect push_left[] =
	{
		uvs[18],
		uvs[19],
		{}
	};

	//アニメーションデータ
	Animation anim[12];

	//アニメーションデータ作成：アイドル時アニメ
	//前向き
	CreateAnimationUV(anim[0], "idle_front", 1, 0.0f, false, idle_front);
	//右向き
	CreateAnimationUV(anim[1], "idle_right", 1, 0.0f, false, idle_right);
	//後向き
	CreateAnimationUV(anim[2], "idle_back", 1, 0.0f, false, idle_back);
	//左向き
	CreateAnimationUV(anim[3], "idle_left", 1, 0.0f, false, idle_left);

	//アニメーションデータ作成：移動時アニメ
	//前向き
	CreateAnimationUV(anim[4], "walk_front", 3, 0.35f, true, walk_front);
	//右向き
	CreateAnimationUV(anim[5], "walk_right", 3, 0.35f, true, walk_right);
	//後向き
	CreateAnimationUV(anim[6], "walk_back", 3, 0.35f, true, walk_back);
	//左向き
	CreateAnimationUV(anim[7], "walk_left", 3, 0.35f, true, walk_left);

	//アニメーションデータ作成：押し時アニメ
	//前向き
	CreateAnimationUV(anim[8], "push_front", 3, 0.35f, true, push_front);
	//右向き
	CreateAnimationUV(anim[9], "push_right", 3, 0.35f, true, push_right);
	//後向き
	CreateAnimationUV(anim[10], "push_back", 3, 0.35f, true, push_back);
	//左向き
	CreateAnimationUV(anim[11], "push_left", 3, 0.35f, true, push_left);


	//アニメーションをスプライトに登録
	for (int i = 0; i < 12; ++i) {
		mSprite.AddAnimation(anim[i]);
	}

	//初期のアニメ設定
	mSprite.PlayAnimation("idle_front");
}

//プレイヤーの後片付け
void Player::Term()
{
	mSprite.Term();
	mTexture.Unload();
}

//向きの取得
Direction Player::GetDirection()
{
	return mDirection;
}

//プレイヤーの落下状態のアドレスの取得
bool* Player::GetIsFalling()
{
	return &mIsFalling;
}

//タイマーの取得
float* Player::GetTimer()
{
	return &mTimer;
}

//手数の取得
int Player::GetMoveNum()
{
	return mMoveNum;
}