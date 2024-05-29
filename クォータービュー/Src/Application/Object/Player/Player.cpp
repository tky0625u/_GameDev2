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

	//UV（切り取るコマ）を設定
	m_polygon.SetUVRect(12);
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

	//ベクトル
	m_dir = Math::Vector3::Zero;

	//アニメーション分割：（横、縦）
	m_polygon.SetSplit(4, 8);

	//ワールド行列
	m_mWorld = Math::Matrix::Identity;
}