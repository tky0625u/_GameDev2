#pragma once

#include"../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	//プレイヤーの情報
	//必要な時だけ参照するのでweak_ptrで保持
	std::weak_ptr<Player> m_player;

	//スマートポインタの種類は３つ

	//shared_ptr ・・・ 参照カウントが増減する、アクセス可能

	//weak_ptr   ・・・ 参照カウントが増減しない、アドレスは保持できるがアクセスする権利はない

	//unique_ptr ・・・ １つのポインタでしか所有できない
};
