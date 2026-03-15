#include "Numbers.h"

//プレイヤーのアドレスを得る為
#include "GameObjectMng/GameObjectMng.h"

//初期化
void Numbers::Init()
{
	for (int i = 0; i < 2; ++i)
	{
		//テクスチャの読み込み
		mTexture[i].Load("Images/tohu/NumberAtlus.png");

		//Spriteの初期化と各種設定
		mSprite[i].Init();
		mSprite[i].SetTexture(mTexture[i]);
		mSprite[i].SetSize(48.0f, 48.0f);
	}
}

//終了
void Numbers::Term()
{
	for (int i = 0; i < 2; ++i)
	{
		mSprite[i].Term();
		mTexture[i].Unload();
	}
}

//更新
void Numbers::Update()
{
	for (int i = 0; i < 2; ++i)
	{
		//スプライトの更新
		mSprite[i].Update();
	}
}

//描画
void Numbers::Render()
{
	for (int i = 0; i < 2; ++i)
	{
		mSprite[i].Draw();
	}
}

//位置設定
void Numbers::SetPosition(Vector2f position)
{
	//スプライトの位置を更新
	mSprite[0].SetPosition(position);
	//スプライトの位置を更新(1の左側)
	mSprite[1].SetPosition({position.x - 36.0f,position.y});
}

//渡された値に変更
void Numbers::SetNum(int iNum)
{
	Number2 number2 = PurgeNum(iNum);
	Sprite* pSprite = mSprite;
	ChangeNum(pSprite, number2.iNum1);
	ChangeNum(pSprite + 1, number2.iNum2);
}

//数字の色変更
void Numbers::SetNumColor(int iNum)
{
	//色を選択
	RGB rgb = SelectNumColor(iNum);

	//色を変更
	SetNumColors(rgb.R, rgb.G, rgb.B);
}

//与えられた数字を桁ごとに分離
Number2 Numbers::PurgeNum(int iNum)
{
	//戻り値用
	Number2 number2 = {};

	//一の位
	number2.iNum1 = iNum % 10;

	//十の位
	number2.iNum2 = (int)((double)iNum * 0.1);

	//0以下は無効
	if (number2.iNum2 < 0)
	{
		number2.iNum2 = 0;
	}

	//返す
	return number2;
}

//数字の変更
void Numbers::ChangeNum(Sprite* sprite, int iNum)
{
	//描画範囲の変更
	sprite->SetTexCoord(0.1f * (float)iNum, 0.0f, 0.1f, 1.0f);
}

//数字の色選択
RGB Numbers::SelectNumColor(int iNum)
{
	//色リスト
	RGB rgb[21] =
	{
		{1.0f,0.0f,0.0f},
		{1.0f,0.1f,0.0f},
		{1.0f,0.2f,0.0f},
		{1.0f,0.3f,0.0f},
		{1.0f,0.4f,0.0f},
		{1.0f,0.5f,0.0f},
		{1.0f,0.6f,0.0f},
		{1.0f,0.7f,0.0f},
		{1.0f,0.8f,0.0f},
		{1.0f,0.9f,0.0f},
		{1.0f,1.0f,0.0f},
		{0.9f,1.0f,0.0f},
		{0.8f,1.0f,0.0f},
		{0.7f,1.0f,0.0f},
		{0.6f,1.0f,0.0f},
		{0.5f,1.0f,0.0f},
		{0.4f,1.0f,0.0f},
		{0.3f,1.0f,0.0f},
		{0.2f,1.0f,0.0f},
		{0.1f,1.0f,0.0f},
		{0.0f,1.0f,0.0f},
	};

	//カウントに合った色を返す
	return rgb[iNum];
}

//数字二つの色変更
void Numbers::SetNumColors(float R, float G, float B)
{
	//両方の桁の色変更
	for (int i = 0; i < 2; ++i)
	{
		mSprite[i].SetAdditionalColor(R, G, B);
	}
}