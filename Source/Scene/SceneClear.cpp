#include "SceneClear.h"

#include "Fwk/Framework.h"

#include "GameObjectMng/GameObjectMng.h"

//初期化
void SceneClear::Init() {

	//扱うオブジェクト数
	mObjectNum = 3;

	mTexture[0].Load("Images/tohu/ScreenGool.jpg");
	mTexture[1].Load("Images/tohu/hiyayakko.png");
	mTexture[2].Load("Images/tohu/GameEnd.png");

	//基底クラスの初期化
	Scene::Init();

	//スプライトの初期化
	mSprite[0].SetSize(1920.0f, 1080.0f);
	mSprite[0].SetPosition(320.0f, -216.0f);
	mSprite[1].SetSize(1290.0f, 921.0f);
	mSprite[1].SetPosition(320.0f, -216.0f);
	mSprite[2].SetSize(960.0f, 540.0f);
	mSprite[2].SetPosition(384.0f, -712.0f);
}

//更新
void SceneClear::Update() {
	//Aボタンを押したら次のシーンにTitleを設定する
	if (Input_I->IsKeyDown('Z')) {
		mNextScene = SceneType::Title;
		GameObjectTerm();
	}

	//基底クラスの更新
	Scene::Update();
}
