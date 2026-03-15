#pragma once

#include "Tilemap/Tilemap.h"
#include "Player/Player.h"
#include "Ingredients/IngredientsMng.h"
#include "Goal/GoalMng.h"

//全オブジェクト初期化
void GameObjectInit();

//全オブジェクト更新
void GameObjectUpdate();

//全オブジェクト描画
void GameObjectRender();

//全オブジェクト解放
void GameObjectTerm();

//Tilemapのアドレスを返す
Tilemap* GetMap();

//Playerのアドレスを返す
Player* GetPlayer();

//IngredientsMngクラスのアドレスを返す
IngredientsMng* GetIngredientsMng();

//GoalMngクラスのアドレスを返す
GoalMng* GetGoalMng();