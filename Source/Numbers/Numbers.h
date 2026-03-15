#pragma once

//SpriteやTexture,Animationを使うためのヘッダファイル
#include "Fwk/Graphics.h"

//Vector2fクラスを使うためのヘッダファイル
#include "Lib/Math/Vector.h"
using namespace Lib::Math;

//桁ごとの数字
struct Number2
{
	int iNum1;
	int iNum2;
};

//RGB
struct RGB
{
	float R;
	float G;
	float B;
};

//数字
class Numbers
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

	//位置設定
	void SetPosition(Vector2f position);

	//渡された値に変更
	void SetNum(int iNum);

	//数字の色の変更
	void SetNumColor(int iNum);

private:

	//数字により表示を変更する
	void ChangeNum(Sprite* sprite,int iNum);

	//与えられた数字を桁ごとに分離
	Number2 PurgeNum(int iNum);

	//色の変更（色選択段階）
	RGB SelectNumColor(int iNum);

	//数字二つの色を変更
	void SetNumColors(float R, float G, float B);

private:
	//表示用スプライト
	Sprite mSprite[2];
	//テクスチャ
	Texture mTexture[2];
	//オブジェクトの位置
	Vector2f mPosition[2];
};