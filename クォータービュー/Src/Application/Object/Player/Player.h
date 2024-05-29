#pragma once

class Player :public KdGameObject
{
public:
	Player(){}
	~Player()override{}

	//更新
	void Update()override;
	void PostUpdate()override;
	
	//描画
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	//初期化
	void Init()override;

private:
	
	//板ポリゴン
	KdSquarePolygon m_polygon;

	//座標
	Math::Vector3   m_pos;

	//方向（ベクトルの向き）
	Math::Vector3   m_dir;

	//移動量
	float           m_speed;
};