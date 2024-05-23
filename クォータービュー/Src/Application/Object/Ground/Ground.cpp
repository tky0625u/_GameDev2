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
	Math::Matrix Scale = Math::Matrix::CreateScale(100);
	Math::Matrix Rot = Math::Matrix::CreateRotationX(0);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = Scale * Rot * Trans;
}
