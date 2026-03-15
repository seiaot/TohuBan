#include "GoalPool.h"

//CollisionManagerを使うのでinclude
#include "Fwk/Framework.h"

//後片付け
void GoalPool::Term()
{
	//Goal*配列の各要素にnewされた敵のオブジェクトのアドレスが
	//記録されているので、１つ１つDELETEしていく
	for (int i = 0; i < mPool.size(); ++i)
	{
		SAFE_DELETE(mPool[i]);
	}
	//プールを破棄
	mPool.clear();
}

//オブジェクトを１つ活性化して戻す
Goal* GoalPool::Alloc()
{
	//戻り値を記録する変数
	Goal* pResult = nullptr;

	for (int i = 0; i < mPool.size(); ++i)
	{
		//非アクティブのオブジェクトを見つけたら活性化して戻り値にする
		if (mPool[i]->IsActive() == false)
		{
			//戻り値にする
			pResult = mPool[i];
			//活性化しておく
			pResult->SetActive(true);
			//ループを抜ける
			break;
		}
	}

	//保存した値を返す
	return pResult;
}