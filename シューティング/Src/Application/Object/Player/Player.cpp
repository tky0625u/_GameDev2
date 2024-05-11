#include"Player.h"

#include"../../Scene/GameScene.h"
#include"../Bullet/Bullet.h"

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_pos.x -= 5;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += 5;
	if (GetAsyncKeyState(VK_UP) & 0x8000)m_pos.y += 5;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)m_pos.y -= 5;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		std::shared_ptr<Bullet> bullet;
		bullet = std::make_shared<Bullet>();
		bullet->Init();
		bullet->SetPos(m_pos);
		bullet->SetOwner(m_owner);
		m_owner->AddObject(bullet);
	}

	//プレイヤーと敵の当たり判定　・・・　敵の情報が必要
	//オブジェクトリストを全て見ていく
	for (auto& obj : m_owner->GetObjList())
	{
		//自分自身とは当たり判定しない
		if (obj->GetObjectType() == ObjectType::Player)continue;

		//敵だったら当たり判定を行う
		if (obj->GetObjectType() == ObjectType::Enemy)
		{
			//対象座標　-　自分座標　＝　対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			//弾判定　・・・　ベクトルの長さで判定
			if (v.Length()<64.0f)
			{
				//Hit時の処理を行う
				obj->OnHit();
			}
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Player::Draw()
{
	Math::Rectangle rc;
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);

	rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, 0, 0, 64, 64, &rc);
}

void Player::Init()
{
	m_Tex.Load("Asset/Textures/player.png");
	m_pos = {};                      //0,0で初期化
	m_mat = Math::Matrix::Identity;  //単位行列で初期化
	m_objType = ObjectType::Player;     //種類は「プレイヤー」

	//単位行列・・・拡大行列全て1.0、他の値は全て0
}

void Player::Release()
{
	//テクスチャはKdTexture型のデストラクタで
	//自動Releaseされるので必要なし
}
