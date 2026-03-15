#include "SceneInGame.h"

#include "Fwk/Framework.h"

#include "GameObjectMng/GameObjectMng.h"

#include "Numbers/Numbers.h"

Numbers mNumbers;

//初期化
void SceneInGame::Init() {

	//扱うオブジェクト数
	mObjectNum = 4;

	//テクスチャの読み込み
	mTexture[0].Load("Images/tohu/ScreenGameGrass.jpg");
	mTexture[1].Load("Images/tohu/UIReSet.png");
	mTexture[2].Load("Images/tohu/UIrest.png");
	mTexture[3].Load("Images/tohu/Dish.png");

	//基底クラスの初期化
	Scene::Init();

	mSprite[0].SetSize(1920.0f, 1080.0f);
	mSprite[0].SetPosition(320.0f, -216.0f);

	mSprite[1].SetSize(288.0f, 96.0f);
	mSprite[1].SetPosition(-490.0f, 270.0f);

	mSprite[2].SetSize(288.0f, 96.0f);
	mSprite[2].SetPosition(1130.0f, 270.0f);

	mSprite[3].SetSize(1728.0f, 972.0f);
	mSprite[3].SetPosition(320.0f, -216.0f);

	//ゲームオブジェクトの初期化
	GameObjectInit();

	//移動可能手数
	mMoveNum = 20;

	//Numbersクラスの初期化
	mNumbers.Init();
	mNumbers.SetPosition({1180.0f, 270.0f});

}

//終了
void SceneInGame::Term() {
	//ゲームオブジェクトの片づけ
	GameObjectTerm();
	//基底クラスの片づけ
	Scene::Term();
}

//更新
void SceneInGame::Update() {

	//if (Input_I->IsKeyDown('Z')) {		
		//mNextScene = SceneType::GameClear;
	//}
	if (Input_I->IsKeyDown('R') && *GetPlayer()->GetTimer() == 0.0f) {
		SceneInGame::Init();
	}
	//プレイヤーのタイマーを取得して一定以上で遷移
	if (*GetPlayer()->GetTimer() > 4.0f)
	{
		mNextScene = SceneType::GameClear;
	}

	//最大移動量-プレイヤーの移動した回数を保存
	int iCount = mMoveNum - GetPlayer()->GetMoveNum();

	//0未満だったら
	if (iCount < 0)
	{
		//ゲームオーバー
		mNextScene = SceneType::GameOver;
	}
	//そうじゃないなら
	else
	{
		//数を変更
		mNumbers.SetNum(iCount);
		//色を変更
		mNumbers.SetNumColor(iCount);
	}

	GameObjectUpdate();

	//基底クラスの更新
	Scene::Update();

	mNumbers.Update();
}

//描画
void SceneInGame::Render() {

	//基底クラスの描画
	Scene::Render();
	//数字の描画
	mNumbers.Render();
	//ゲームオブジェクトの描画
	GameObjectRender();
}

