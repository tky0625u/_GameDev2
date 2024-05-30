#include "Player.h"

void Player::Update()
{
	//移動

	//移動関係をクリア
	m_dir = Math::Vector3::Zero;
	
	if (GetAsyncKeyState(VK_UP) & 0x8000)m_dir += {0, 0, 1};
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)m_dir += {0, 0, -1};
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_dir += {1, 0, 0};
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_dir += {-1, 0, 0};

	//向きを正規化（ベクトルの長さを１にする）
	m_dir.Normalize();

	//座標更新
	//座標＋＝ベクトルの方向（1.0f固定）＊ベクトルの量（向きに対して移動させたい量）
	m_pos += m_dir * m_speed;

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.0005f;

	//UV（切り取るコマ）を設定
	m_polygon.SetUVRect(12);

	//===========================================
	//当たり判定・・・レイ判定
	//===========================================

	//レイ判定用に必須パラメーターを設定する構造体宣言
	KdCollider::RayInfo rayInfo;

	//レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;

	//少し高いところから飛ばす
	rayInfo.m_pos.y = m_pos.y + 0.1f;  //中央下段が原点なので少し上から

	//レイの方向を設定
	rayInfo.m_dir = { 0.0f,-1.0f,0.0f };

	//レイの長さを設定

	//当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	//===========================================
	//===========================================
}

void Player::PostUpdate()
{
	//Updateで確定したパラメーターからワールド行列作成
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = trans;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::Init()
{
	//板ポリにテクスチャ（マテリアル）をセット
	m_polygon.SetMaterial("Asset/Textures/Player.png");

	//板ポリの原点（真ん中下段を指定）
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	
	//座標・移動量
	m_pos = { 0,0,0 };
	m_speed = 0.1f;

	//重力
	m_gravity = 0.0f;

	//ベクトル
	m_dir = Math::Vector3::Zero;

	//アニメーション分割：（横、縦）
	m_polygon.SetSplit(4, 8);

	//ワールド行列
	m_mWorld = Math::Matrix::Identity;
}