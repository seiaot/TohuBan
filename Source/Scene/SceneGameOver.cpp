#include "SceneGameOver.h"

#include "Fwk/Framework.h"

#include "GameObjectMng/GameObjectMng.h"

//初期化
void SceneGameOver::Init() {

	//扱うオブジェクト数
	mObjectNum = 2;

	//ゲームオーバー画像
	mTexture[0].Load("Images/tohu/ScreenGameOver.jpg");
	//文字
	mTexture[1].Load("Images/tohu/GameEnd.png");

	//基底クラスの呼び出し
	Scene::Init();
	
	mSprite[0].SetSize(1920, 1080);
	mSprite[0].SetPosition(320, -216);

	mSprite[1].SetSize(1344.0f, 756.0f);
	mSprite[1].SetPosition(767.0f, -735.0f);
	mSprite[1].SetAdditionalColor(1.0f, 0.0f, 0.0f);
}

//更新
void SceneGameOver::Update() {
	//Aボタンを押したら次のシーンにTitleを設定する
	if (Input_I->IsKeyDown('Z')) {
		mNextScene = SceneType::Title;
		GameObjectTerm();
	}

	//基底クラスの更新
	Scene::Update();
}
