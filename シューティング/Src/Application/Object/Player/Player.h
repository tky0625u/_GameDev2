#pragma once

//基本的にヘッダーファイルの中で
//別のヘッダーファイルをインクルードするのはNG
//継承元クラスのヘッダーのみインクルードが必須なので可とする
#include"../BaseObject.h"

class GameScene;
class Bullet;

class Player:public BaseObject
{
public:
	Player() { Init(); }
	~Player() { Release(); }

	//基底クラスの仮想関数をオーバーライド
	//override指定子は無くてもオーバーライドはされるが
	//override可能かどうかを判別する目的でつけるべき（可読性の問題もある）
	void Update()override;
	void Draw()override;
	void Init()override;

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:

	GameScene* m_owner = nullptr;

	void Release()override;

};