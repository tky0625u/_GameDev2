#include "Player.h"
#include"../../Scene/SceneManager.h"

void Player::Update()
{
	//移動

	//移動関係をクリア
	m_dir = Math::Vector3::Zero;
	m_dirType = 0;  //ビット列をクリア

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir += {0, 0, 1};
		m_dirType = DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir += {0, 0, -1};
		m_dirType = DirType::Down;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir += {1, 0, 0};
		m_dirType = m_dirType | DirType::Right;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir += {-1, 0, 0};
		m_dirType = m_dirType | DirType::Left;
	}
	ChangeAnimation();

	//ジャンプ処理
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	//向きを正規化（ベクトルの長さを１にする）
	m_dir.Normalize();

	//座標更新
	//座標＋＝ベクトルの方向（1.0f固定）＊ベクトルの量（向きに対して移動させたい量）
	m_pos += m_dir * m_speed;

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//アニメーション更新
	int animeCnt;

	animeCnt = m_animeInfo.count + m_animeInfo.start;
	m_animeInfo.count += m_animeInfo.speed;
	if (animeCnt >= m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.count = 0;
	}

	//UV（切り取るコマ）を設定
	m_polygon.SetUVRect(animeCnt);

	//===========================================
	//当たり判定・・・レイ判定
	//===========================================

	//レイ判定用に必須パラメーターを設定する構造体宣言
	KdCollider::RayInfo rayInfo;

	//レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;

	//少し高いところから飛ばす
	//rayInfo.m_pos.y = m_pos.y + 0.1f;  //中央下段が原点なので少し上から

	//段差許容範囲を設定
	static const float enableStepHight = 0.2f;  //0.2までの高さなら登れる
	rayInfo.m_pos.y += enableStepHight;

	//レイの方向を設定
	rayInfo.m_dir = { 0.0f,-1.0f,0.0f };

	//レイの長さを設定
	rayInfo.m_range = m_gravity + enableStepHight;

	//当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	//デバッグ用の情報としてライン描画を設定
	m_pDebugWire->AddDebugLine
	(
		rayInfo.m_pos,   //線の開始位置
		rayInfo.m_dir,   //線の方向
		rayInfo.m_range  //線の長さ
	);

	//レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	//作成したレイ情報でオブジェクトリストと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}

	//レイに当たった結果リストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};  //レイがsy団された(Hitした)座標

	for (auto& ret : retRayList)
	{
		//レイが当たった場合の貫通した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}
	//当たっていたら
	if (hit)
	{
		m_pos = groundPos;
		m_gravity = 0;
	}

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
	
	//アニメーション分割：横、縦
	m_polygon.SetSplit(4, 8);

	//初期アニメーション情報
	m_animeInfo.start = 4;     //開始コマ
	m_animeInfo.end = 7;       //終了コマ
	m_animeInfo.count = 0;     //現在のコマ数カウント
	m_animeInfo.speed = 0.2f;  //アニメーション速度

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

	//デバッグワイヤー作成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::ChangeAnimation()
{
	//各方向を判別
	switch (m_dirType)
	{
	case 1:
		m_animeInfo.start = 24;
		m_animeInfo.end = 27;
		break;
	case 2:
		m_animeInfo.start = 4;
		m_animeInfo.end = 7;
		break;
	case 4:
		m_animeInfo.start = 12;
		m_animeInfo.end = 15;
		break;
	case 5:
		m_animeInfo.start = 20;
		m_animeInfo.end = 23;
		break;
	case 6:
		m_animeInfo.start = 0;
		m_animeInfo.end = 3;
		break;
	case 8:
		m_animeInfo.start = 16;
		m_animeInfo.end = 19;
		break;
	case 9:
		m_animeInfo.start = 28;
		m_animeInfo.end = 31;
		break;
	case 10:
		m_animeInfo.start = 8;
		m_animeInfo.end = 11;
		break;
	default:
		break;
	}

	//カウントとスピード初期化
	m_animeInfo.count = 0;
	m_animeInfo.speed = 0.2f;
}
