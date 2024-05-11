#include "GameScene.h"

#include"../Object/Player/Player.h"
#include"../Object/Enemy/Enemy.h"

void GameScene::PreUpdate()
{
	//Updateの前の更新処理
	//オブジェクトリストの整理をしておく

	//イテレータとは　・・・　コンテナクラス用のポインタ
	//コンテナを先頭から末尾まで遡る際に使用

	//イテレータ作成　ベタ書き
	//std::vector<std::shared_ptr<BaseObject>>::iterator it;
	//it = m_objList.begin();

	//イテレータ　auto版
	auto it = m_objList.begin();

	while (it!=m_objList.end())  //end()は最後の要素の１個後ろを返す
	{
		//オブジェクトの有効チェック
		if ((*it)->GeAliveFlg()==false)
		{
			//無効なオブジェクトをリストから削除
			it = m_objList.erase(it);
		}
		else
		{
			it++;  //次の要素へイテレータを進める
		}
	}

	//↑の後には有効なオブジェクトだけのリストになっている
}

void GameScene::Update()
{
	//m_player->Update();
	//m_enemy->Update();

	//全オブジェクトの更新関数を呼ぶ

	//３％の確率で敵を出現させてみる
	if (rand() % 100 + 1 <= 3)
	{
		std::shared_ptr<Enemy> enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(640.0f, 0.0f);
		enemy->SetMovePow({ -2.0f,-2.0f,0.0f });
		m_objList.push_back(enemy);
	}

	for (int b = 0; b < m_objList.size(); ++b)
	{
		m_objList[b]->Update();
	}
}

void GameScene::Draw()
{
	//m_player->Draw();
	//m_enemy->Draw();

		//全オブジェクトの描画関数を呼ぶ
	for (int b = 0; b < m_objList.size(); ++b)
	{
		m_objList[b]->Draw();
	}
}

void GameScene::Init()
{
	//プレイヤー
	//m_player = new Player;                //生ポインタ　インスタンス生成
	//m_player = std::make_shared<Player>();  //スマートポインタ　インスタンス生成
	//m_player->Init();
	//m_player->SetOwner(this);

	//エネミー
	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();

	//プレイヤー
	std::shared_ptr<Player> player;
	player=std::make_shared<Player>();  //１，派生クラスを生成
	//player->Init();                   //２，初期化関連
	player->SetOwner(this);
	m_objList.push_back(player);        //３，リストへ追加
	
	//エネミー
	std::shared_ptr<Enemy> enemy[10];
	for (int e = 0; e < 10; ++e)
	{
		enemy[e] = std::make_shared<Enemy>();
		enemy[e]->Init();
		enemy[e]->SetPos(-640+(e*128), 360.0f);
		m_objList.push_back(enemy[e]);
	}
}

void GameScene::Release()
{
	//delete m_player;  //生ポインタ　インスタンス破棄
}
