#pragma once

class Attack :public KdGameObject
{
public:
	Attack(){}
	~Attack()override{}

	void Update()override;
	void DrawUnLit()override;
	void Init()override;

	void OnHit()override { m_isExpired = true; }

private:

	//板ポリゴン
	KdSquarePolygon m_polygon;

	//アニメーション情報
	float	        m_animeCnt;
	float		    m_animeSpeed;
	
	//攻撃判定のエリア
	float           m_attackArea;

};