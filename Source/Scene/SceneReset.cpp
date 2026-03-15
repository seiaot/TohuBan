#include "SceneReset.h"

#include "Fwk/Framework.h"

#include "GameObjectMng/GameObjectMng.h"

//初期化
void SceneReset::Init()
{
	//基底クラスの初期化
	Scene::Init();
	//オブジェクトの片付け
	GameObjectTerm();
}

//更新
void SceneReset::Update() {
	//次のシーンを設定する	
	mNextScene = SceneType::InGame;
}