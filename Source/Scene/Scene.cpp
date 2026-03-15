#include "Scene.h"

#include "Fwk/Framework.h"

//初期化
void Scene::Init() {
	//次のシーンの初期値をなしにしておく
	mNextScene = SceneType::None;

	//オブジェクト数分繰り返し
	for (int i = 0; i < mObjectNum; ++i)
	{
		mSprite[i].Init();
		mSprite[i].SetTexture(mTexture[i]);
	}
}

//終了
void Scene::Term() {

	//オブジェクト数分繰り返し
	for (int i = 0; i < mObjectNum; ++i)
	{
		mTexture[i].Unload();
		mSprite[i].Term();
	}
}

//更新
void Scene::Update() {

	//オブジェクト数分繰り返し
	for (int i = 0; i < mObjectNum; ++i)
	{
		mSprite[i].Update();
	}
}

//描画
void Scene::Render() {

	//オブジェクト数分繰り返し
	for (int i = 0; i < mObjectNum; ++i)
	{
		mSprite[i].Draw();
	}
}

//次のシーンを取得する
SceneType Scene::GetNextScene() {
	return mNextScene;
}