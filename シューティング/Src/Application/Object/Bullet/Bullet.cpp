#include "Bullet.h"
#include"../../Scene/GameScene.h"

void Bullet::Update()
{
	if (m_bFlg)return;

	m_pos += m_movePow;

	//オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		//自分自身とは当たり判定しない
		//if (obj->GetObjectType() == ObjectType::Player || obj->GetObjectType() == ObjectType::Bullet)continue;

		//敵だったら当たり判定を行う
		if (obj->GetObjectType() == ObjectType::Enemy)
		{
			//対象座標　-　自分座標　＝　対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			//弾判定　・・・　ベクトルの長さで判定
			if (v.Length() < 32.0f + 18.5f)
			{
				//Hit時の処理を行う
				obj->OnHit();
				OnHit();
				break;
			}
		}
	}

	if (m_pos.y > 360)
	{
		m_bFlg = false;
		m_aliveFlg = false;
	}
	m_mat = Math::Matrix::CreateTranslation(m_pos);
}

void Bullet::Draw()
{
	if (m_bFlg = false)return;

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle rc = { 0,0,13,37 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, 0, 0, 13, 37, &rc);
}

void Bullet::Init()
{
	m_Tex.Load("Asset/Textures/bullet.png");
	m_bFlg = false;
	m_pos = {};                       //０,０で初期化
	m_mat = Math::Matrix::Identity;   //単位行列で初期化
	m_objType = ObjectType::Bullet;    //種類は「敵」
	m_movePow = { 0.0f,10.0f,0.0f };
}

void Bullet::OnHit()
{
	m_aliveFlg = false;
}

void Bullet::Release()
{
}
