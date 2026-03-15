#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"


//シーン種別の列挙型を使うので#include
#include "Scene.h"

//シーンクラス
class SceneInGame : public Scene
{
public:
	//初期化
	void Init();
	//終了
	void Term();
	//更新
	void Update();
	//描画
	void Render();

private:

	//手数
	int mMoveNum;
};









