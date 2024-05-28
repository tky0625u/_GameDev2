#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	//カメラ　行列更新============================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));  //カメラの角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(0, 3, -3);                      //カメラの位置
	Math::Matrix Mat = RotX * Trans;                                                     //行列合成
	m_camera->SetCameraMatrix(Mat);                                                      //行列セット
	//============================================================================================================
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定====================================================================================
	m_camera = std::make_unique<KdCamera>();  //メモリ確保
	m_camera->SetProjectionMatrix(60);        //視野角設定
	//============================================================================================================
	
	//背景========================================================================================================
	std::shared_ptr<BackGround> back = std::make_shared<BackGround>();  //メモリ確保
	back->Init();                                                       //初期化
	m_objList.push_back(back);                                          //リストへ追加
	//============================================================================================================

	//地面========================================================================================================
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();  //メモリ確保
	ground->Init();												  //初期化
	m_objList.push_back(ground);								  //リストへ追加
	//============================================================================================================

	//プレイヤー==================================================================================================
	std::shared_ptr<Player> player = std::make_shared<Player>();  //メモリ確保
	player->Init();												  //初期化
	m_objList.push_back(player);								  //リストへ追加
	//============================================================================================================
}
