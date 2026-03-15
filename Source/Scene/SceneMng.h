#pragma once

#include "GameDef.h"

//シーンクラスを使うので#incdlue
#include "Scene.h"

//シーンクラス
class SceneMng
{
public:
	//初期化
	void Init(SceneType startScene);
	//終了
	void Term();
	//更新
	void Update();
	//描画
	void Render();
private:
	//あたらしいシーンを開始する
	void _beginScene(SceneType newScene);
	//現在のシーンを終了する
	void _endCurrentScene();
private:
	//現在のシーン
	SceneType mCurrentScene;
	//次のシーン
	SceneType mNextScene;
	//現在動いているシーンクラスの変数ポインタ
	Scene* mpScene;

};









