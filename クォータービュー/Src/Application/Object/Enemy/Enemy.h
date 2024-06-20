#pragma once

class Player;

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy()override{}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void OnHit()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetTarget(std::weak_ptr<Player> a_target) { m_target = a_target; }

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3					 m_pos;
	Math::Vector3					 m_dir;
	float							 m_speed;
	float							 m_gravity;
	float							 m_animeCnt;
	float							 m_animeSpeed;
	float                            m_searchArea;  //サーチ範囲
	bool                             m_chaseFlg;    //追尾フラグ

	//追尾対象(プレイヤー)のweak_ptr
	std::weak_ptr<Player>            m_target;
};