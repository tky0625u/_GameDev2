#pragma once

#include"../BaseObject.h"

class GameScene;

class Bullet :public BaseObject
{
public:
	Bullet() {};
	~Bullet() { Release(); };

	void Update()override;
	void Draw()override;
	void Init()override;

	void OnHit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetPos(float _x, float _y) { m_pos = { _x,_y,0.0f }; }  //SetPosのオーバーロード

	void SetMovePow(Math::Vector3 _movePow) { m_movePow = _movePow; }

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:

	Math::Vector3 m_movePow;

	GameScene* m_owner;

	void Release() override;
};