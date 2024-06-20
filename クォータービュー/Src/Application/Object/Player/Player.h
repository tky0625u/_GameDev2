#pragma once

class Player :public KdGameObject
{
public:

	enum DirType
	{
		Up     = 1 << 0,  //上
		Down   = 1 << 1,  //下
		Left   = 1 << 2,  //左
		Right  = 1 << 3,  //右
	};

	//アニメーション情報
	struct AnimationInfo
	{
		int start;    //開始コマ
		int end;      //終了コマ
		float count;  //現在のコマ数カウント
		float speed;  //アニメーションの速度
	};

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
	
	void ChangeAnimation();

	//板ポリゴン
	KdSquarePolygon m_polygon;

	//アニメーション情報
	AnimationInfo   m_animeInfo;

	//キャラが向いている方向種類 ビット管理
	UINT            m_dirType;

	//座標
	Math::Vector3   m_pos;

	//方向（ベクトルの向き）
	Math::Vector3   m_dir;

	//移動量
	float           m_speed;

	//攻撃方向
	Math::Vector3   m_attackDir;

	//重力
	float           m_gravity;

	//押しっぱ防止
	bool            m_keyFlg;
};