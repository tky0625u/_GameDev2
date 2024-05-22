#include "BackGround.h"

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void BackGround::Init()
{
	//板ポリにテクスチャ(マテリアル)をセット
	m_polygon.SetMaterial("Asset/Textures/BackGround.png");

	//板ポリのサイズを拡大
	m_polygon.SetScale(200.0f);

	//板ポリの原点(真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//奥側に座標(ワールド行列)を更新しておく
	m_mWorld = Math::Matrix::CreateTranslation(0.0f, 0.0f, 100.0f);
}
