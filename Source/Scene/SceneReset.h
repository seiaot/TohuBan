#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"

//シーン種別の列挙型を使うので#include
#include "Scene.h"

//シーンクラス
class SceneReset : public Scene
{
public:
	//初期化
	void Init();

	//更新
	void Update();
};









