#include "Player.h"

void Player::Update()
{
	//移動
	if (GetAsyncKeyState(VK_UP) & 0x8000)m_pos.z += m_speed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)m_pos.z -= m_speed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += m_speed;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_pos.x -= m_speed;


	m_polygon.SetUVRect(0);
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

	//アニメーション分割：（横、縦）
	m_polygon.SetSplit(4, 8);

	//ワールド行列
	m_mWorld = Math::Matrix::Identity;
}