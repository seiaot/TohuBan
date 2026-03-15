#pragma once

//SpriteとTextureを使う為のヘッダファイル
#include<Fwk/Graphics.h>

//CSVデータを使うので
#include "Fwk/File/CSVFile.h"

class Tilemap
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

	//タイルサイズを取得
	float GetTileSize();

	//指定された座標にあるタイルが壁であるか否かを戻す
	bool IsWall(Vector2f position);

	//マップをCSVDataから生成する
	void CreateMap(CSVData* pMapdata);

private:
	//指定された列・行が壁であるか否かを戻す
	bool _isWall(int col, int row);

	//定数,C言語のenumは型名なしで列挙できる
	enum 
	{
		COL_NUM = 10,	//列数(X軸方向のタイル枚数)
		ROW_NUM = 6,	//行数(Y軸方向のタイル枚数)
	};

private:
	//タイルパターンの画像を読み込む為のテクスチャ
	Texture mTexture;
	//列数×行数分のスプライト
	Sprite mSprite[ROW_NUM][COL_NUM];

	//マップデータ(タイルID)を収める配列
	//クラスの宣言時にメンバ変数の初期値を書くこともできる
	int mMapData[ROW_NUM][COL_NUM] = {};

};