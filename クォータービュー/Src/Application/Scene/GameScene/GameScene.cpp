#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/BackGround.h"

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
	m_camera = std::make_unique<KdCamera>();                                             //メモリ確保
	m_camera->SetProjectionMatrix(60);                                                   //視野角設定
	//============================================================================================================
	
	//背景========================================================================================================
	std::shared_ptr<BackGround> back = std::make_shared<BackGround>();  //メモリ確保
	back->Init();                                                       //初期化
	m_objList.push_back(back);                                          //リストへ追加
	//============================================================================================================
}
