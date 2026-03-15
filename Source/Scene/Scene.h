#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"


//シーン種別の列挙型を使うので#include
#include "GameDef.h"

//シーンクラス
class Scene
{
public:
	//初期化
	virtual void Init();
	//終了
	virtual void Term();
	//更新
	virtual void Update();
	//描画
	virtual void Render();
	//次のシーンを取得する
	SceneType GetNextScene();

protected:
	//次のシーン
	SceneType mNextScene;
	//オブジェクトの数
	int mObjectNum;
	//表示用スプライト
	Sprite mSprite[4];
	//テクスチャ
	Texture mTexture[4];
	//オブジェクトの位置
	Vector2f mPosition;


};









