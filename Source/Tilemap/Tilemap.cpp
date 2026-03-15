#include "Tilemap.h"

//定数タイル１枚分のSpriteのサイズ
const float TileSize = 64.0f;

//初期化
void Tilemap::Init()
{
	//テクスチャファイルの読み込み
	mTexture.Load("Images/tohu/Map.png");

	//スプライトの初期化と各種設定
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int n = 0; n < COL_NUM; ++n) {
			//初期化
			mSprite[i][n].Init();
			//テクスチャ設定
			mSprite[i][n].SetTexture(mTexture);
			//サイズを設定
			mSprite[i][n].SetSize(TileSize, TileSize);
			//位置を設定
			mSprite[i][n].SetPosition((float)n * TileSize, (float)-i * TileSize);

			//マップデータからタイルIDを取得
			int id = mMapData[i][n];

			//スプライトのUV座標設定
			//テクスチャサイズは256*256でテクスチャ上のパターンのサイズは16*16
			//テクスチャ上には16列＊16行のパターンが並んでいる
			float w = 64.0f / 320.0f;	//パターン1つ分の幅
			float h = 64.0f / 64.0f;	//パターン1つ分の高さ
			float u = (float)(id % 64) * w;		//タイルIDが示すパターンの左端の座標
			float v = (float)(id / 64) * h;		//タイルIDが示すパターンの上橋の座標
			mSprite[i][n].SetTexCoord(u, v, w, h);

			//左上をスプライトの中心点とする
			mSprite[i][n].SetPivot(Pivot::TopLeft);
		}
	}
}

//終了
void Tilemap::Term()
{
	//スプライトの解放
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int n = 0; n < COL_NUM; ++n) {
			mSprite[i][n].Term();
		}
	}
	//テクスチャの破棄
	mTexture.Unload();
}

//更新
void Tilemap::Update()
{
	//なし
}

//描画
void Tilemap::Render()
{
	//スプライトの描画
	for (int i = 0; i < ROW_NUM; ++i) {
		for (int n = 0; n < COL_NUM; ++n) {
			mSprite[i][n].Draw();
		}
	}
}

//タイルサイズを取得
float Tilemap::GetTileSize() {
	return TileSize;
}

//指定された座標にあるタイルが壁であるか否かを戻す
bool Tilemap::IsWall(Vector2f position) {
	//与えられた座標をタイルサイズで割って端数を切り捨てれば
	//マップデータの列・行となる,ｙ座標は符号に注意
	int col = (int)(position.x / TileSize);
	int row = (int)(position.y / -TileSize);
	//列・行を指定して壁か否かを判定する
	return _isWall(col, row);
}

//指定された列・行が壁であるか否かを戻す
bool Tilemap::_isWall(int col, int row)
{
	//不正値チェック
	if (col < 0 || col >= COL_NUM || row < 0 || row >= ROW_NUM) {
		return false;
	}
	//指定の列・行のタイルIDを取得する
	int id = mMapData[row][col];
	//タイルID1番を壁と判定する
	if (id == 1 || id == 0) {
		return true;
	}
	return false;
}

//マップをCSVDataから生成する
void Tilemap::CreateMap(CSVData* pMapdata) {

	if (pMapdata == nullptr) {
		return;
	}

	//行数分繰り返し
	for (int i = 0; i < ROW_NUM; ++i) {
		//列数分繰り返し
		for (int n = 0; n < COL_NUM; ++n) {
			//n列i行目のタイルIDをCSVDataから取得
			int id = pMapdata->GetInt(n + (i * COL_NUM));
			//マップデータのn列目i行目のタイルIDを上書き
			mMapData[i][n] = id;

			//n列i行目に位置するスプライトのUV座標を
			//タイルIDに合わせて設定
			float w = 64.0f / 320.0f;
			float h = 64.0f / 64.0f;
			float u = (float)(id % 64) * w;
			float v = (float)(id / 64) * h;
			mSprite[i][n].SetTexCoord(u, v, w, h);
		}
	}
}