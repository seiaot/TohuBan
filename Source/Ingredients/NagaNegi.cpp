#include "NagaNegi.h"

//初期化
void NagaNegi::Init()
{
	Ingredients::Init();
	//テクスチャの描画範囲を変更
	mSprite.SetTexCoord(0.2f, 0.0f, 0.2f, 0.5f);
}