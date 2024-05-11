#include "Enemy.h"

void Enemy::Update()
{
	m_pos += m_movePow;
	if (m_pos.y < -360)m_pos.y = 360;
	m_mat = Math::Matrix::CreateTranslation(m_pos);
}

void Enemy::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, 0, 0, 64, 64, &rc);
}

void Enemy::Init()
{
	m_Tex.Load("Asset/Textures/enemy.png");
	m_pos = {};                       //０,０で初期化
	m_mat = Math::Matrix::Identity;   //単位行列で初期化
	m_objType = ObjectType::Enemy;    //種類は「敵」
	m_movePow = { 0.0f,-2.0f,0.0f };
}

void Enemy::OnHit()
{
	m_aliveFlg = false;
}

void Enemy::Release()
{
}
