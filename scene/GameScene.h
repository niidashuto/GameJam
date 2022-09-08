﻿#pragma once

#include "Audio.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
//#include "WorldTransform.h"

#include "DebugCamera.h"
#include "Enemy.h"
#include "Player.h"
#include "RailCamera.h"
#include "Skydome.h"
#include <sstream>

enum stage {
	TITLE,
	INFO,
	GAME,
	END
};



/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(GameScene* gameScene);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire(Vector3 trans, float W);

	/// <summary>
	/// 敵弾
	/// </summary>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	// リセット
	void Reset();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;

	//値を表示したい変数
	uint32_t value_ = 0;

	//スプライト
	Sprite* sprite_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelBullet_ = nullptr;

	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	//サウンドデーターハンドル
	uint32_t soundDataHandle_ = 0;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t eneTextureHandle_ = 0u;

	//  object
	std::unique_ptr<RailCamera> railCamera_;
	// 天球
	std::unique_ptr<Skydome> skydome_;

	// キャラ
	Player* player_ = nullptr;

	// 敵
	std::list<std::unique_ptr<Enemy>> enemy_;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	GameScene* gameScene_ = nullptr;
	std::stringstream enemyPopCommands;
	bool enemyPop = true;
	float enemyPopTime = true;

	//ワールドトランスフォーム
	// WorldTransform worldTransform_;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//カメラ上方向の角度
	float viewAngle = 0.0f;
	//デバックカメラ有効
	bool isDebugcameraActive_ = false;

	// ステージ
	int stage = 0;
	int time=0;

	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};