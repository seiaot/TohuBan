#include "SceneTitle.h"

#include "Fwk/Framework.h"

//初期化
void SceneTitle::Init() {

	//扱うオブジェクト数
	mObjectNum = 3;

	mTexture[0].Load("Images/tohu/ScreenStart.jpg");
	mTexture[1].Load("Images/tohu/tohuban.png");
	mTexture[2].Load("Images/tohu/GameStart.png");

	//基底クラスの初期化
	Scene::Init();

	//スプライトの初期化
	mSprite[0].SetSize(1920.0f, 1080.0f);
	mSprite[0].SetPosition(320.0f, -216.0f);

	mSprite[1].SetSize(1920.0f, 1080.0f);
	mSprite[1].SetPosition(320.0f, -216.0f);

	mSprite[2].SetSize(1344.0f, 756.0f);
	mSprite[2].SetPosition(672.0f, -672.0f);

}

//更新
void SceneTitle::Update() {
	//Aボタンを押したら次のシーンにInGameを設定する
	if (Input_I->IsKeyDown('Z')) {
		mNextScene = SceneType::InGame;
	}
}