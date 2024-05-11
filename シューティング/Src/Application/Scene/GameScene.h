#pragma once

//class Player;
class BaseObject;

class GameScene
{
public:
	GameScene(){}					//生成時
	~GameScene() { Release(); }     //破棄

	void PreUpdate();  //更新を呼ぶ前の処理
	void Update();     //更新
	void Draw();       //描画
	void Init();       //初期化

	//オブジェクトのリストを取得
	std::vector<std::shared_ptr<BaseObject>> GetObjList()
	{
		return m_objList;
	}

	//オブジェクトリストにオブジェクトを追加
	void AddObject(std::shared_ptr<BaseObject> _obj)
	{
		//リストの末尾に引数で渡された１要素を追加
		m_objList.push_back(_obj);
	}

private:

	void Release();    //終了処理

	//Player* m_player = nullptr;      //派生クラスのポインタ 生ポインタ
	//BaseObject* m_player = nullptr;  //基底クラスのポインタ 生ポインタ
	//std::shared_ptr<Player> m_player = nullptr;    //スマートポインタ
	//std::shared_ptr<BaseObject> m_player = nullptr;  //スマートポインタ
	//std::shared_ptr<BaseObject>m_enemy = nullptr;

	//全オブジェクトを可変長配列で管理
	std::vector<std::shared_ptr<BaseObject>> m_objList;

};