#include "Enemy.h"
#include"../../Scene/SceneManager.h"
#include"../Player/Player.h"

void Enemy::Update()
{
	//追尾対象が一定範囲内にいるか？
	Math::Vector3 targetPos = {};

	if (m_target.expired() == false)
	{
		targetPos = m_target.lock()->GetPos();

		//対象との距離で判定　※距離判定
		Math::Vector3 v = targetPos - m_pos;

		//ベクトルの長さが一定値以下なら追尾モードへ
		if (v.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}

		//追尾フラグONの場合は追尾する
		if (m_chaseFlg)
		{
			//y軸を0にしておく　※空飛んで追いかけるの防止
			v.y = 0.0f;

			//対象へのベクトルの長さを１に
			v.Normalize();

			//方向確定
			m_dir = v;
		}
		else
		{
			//対象が居ない場合は動かない
			m_dir = {};
		}
	}

	//デバッグ用にサーチ範囲の球を追加
	Math::Color sphereColor = { 0,1,0,1 };
	m_pDebugWire->AddDebugSphere(m_pos+Math::Vector3(0,0.5f,0), m_searchArea,sphereColor);

	m_pos += m_dir * m_speed;
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	int Walk[] = { 3,4,3,5 };

	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 4)m_animeCnt = 0.0f;
	m_polygon->SetUVRect(Walk[(int)m_animeCnt]);

	KdCollider::RayInfo rayInfo;
	rayInfo.m_pos = m_pos;
	static const float enableStepHight = 0.2f;
	rayInfo.m_pos.y += enableStepHight;
	rayInfo.m_dir = { 0.0f,-1.0f,0.0f };
	rayInfo.m_range = m_gravity + enableStepHight;
	rayInfo.m_type = KdCollider::TypeGround;
	
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);

	std::list<KdCollider::CollisionResult> retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	bool isHit = false;
	float maxOverLap = 0.0f;
	Math::Vector3 groundPos;

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			isHit = true;
		}
	}

	if (isHit)
	{
		m_pos = groundPos;
		m_gravity = 0.0f;
	}
}

void Enemy::PostUpdate()
{
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Trans;
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Enemy::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Enemy.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(6, 6);
	m_pos = {};
	m_dir = {};
	m_speed = 0.05f;
	m_gravity = 0.0f;
	m_animeCnt = 0.0f;
	m_animeSpeed = 0.1f;
	m_searchArea = 3.0f;
	m_chaseFlg = false;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Enemy", m_polygon, KdCollider::TypeDamage);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::OnHit()
{
	//Hit時は即消滅
	m_isExpired = true;
}
