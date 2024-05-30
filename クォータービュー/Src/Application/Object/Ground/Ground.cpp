#include "Ground.h"

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ground::Init()
{
	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	
	//モデル 読み込み
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	//ワールド行列 合成
	Math::Matrix Scale = Math::Matrix::CreateScale(100);            //拡大行列(Scale)
	Math::Matrix Rot = Math::Matrix::CreateRotationX(0);            //回転行列(Rotation)
	Math::Matrix Trans = Math::Matrix::CreateTranslation(0, 0, 0);  //座標行列(Translation)
	m_mWorld = Scale * Rot * Trans;                                 //行列合成(S*R*T)

	//コライダー(当たり判定情報)の初期化(登録)
	m_pCollider = std::make_unique<KdCollider>();                  //1,生成
	m_pCollider->RegisterCollisionShape                            //2,判定情報
	("Ground",                //登録名
	m_model,                  //モデルデータ
	KdCollider::TypeGround);  //衝突タイプ
}
