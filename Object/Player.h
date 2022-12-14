#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

#include "PlayerBullet.h"
#include "Item.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
  private:
	//	ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//レティクル用テクスチャ取得
	uint32_t textureReticle = TextureManager::Load("reticle2D.png");

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_ = nullptr;

	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	// カメラ座標用
	WorldTransform cameraWorldTransform_;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;
	// 2Dレティクル用スプライト
	std::unique_ptr<Sprite> sprite2DReticle_;

	int hp = 100;
	int point = 0;
	bool isDead = false;

	// プレイヤーのバフ状態
	const int initState = 0b0000;
	int playerState = 0b0000;

	enum Buff {
		POWERBUFF = 1 << 0,
		SPEEDBUFF = 1 << 1,
		TWOWAY = 1 << 2,
		THREEWAY = 1 << 3,
		POWERDEBUFF = 1 << 4,
		SPEEDDEBUFF = 1 << 5
	};

	int attackBuffTimer = 900;
	int sppedBuffTimer = 900;
	int powerBuffTimer = 900;

	int score;

  public:
	float r = 1.0f;
	int GetScore() { return score; }

  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(ViewProjection viewprojection, Model* model, Item* item);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 平行移動
	/// </summary>
	void Move();
	/// <summary>
	/// 回転移動
	/// </summary>
	void Rotate();

	/// <summary>
	/// 行列の計算
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(Model* model);

	/// <summary>
	/// 衝突を検知したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾の取得
	/// </summary>
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	WorldTransform GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 親オブジェクトの設定
	/// </summary>
	void SetParent(WorldTransform* worldTransform) { worldTransform_.parent_ = worldTransform; };

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	/// <summary>
	/// 自機のワールド座標から3Dレティクルのワールド座標を計算
	/// </summary>
	void WorldReticle();

	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	void Reticle(ViewProjection viewprojection);

	//  加算
	void AddPoint();

	/// <summary>
	/// point
	/// </summary>
	int GetPoint() { return point; }

	bool IsDead() const { return isDead; }

	void AddItem(int tribe);

	/// <summary>
	/// 状態異常のフラグを立てる,下げる
	/// </summary>
	int CheckPlayerFlag(int playerState, Item* item);
	bool CheckPlayerBuff(int playerState, int buff);
	int OnFlag(int playerState, int buff);
	int OffFlag(int playerState, int buff);
	int GetPlayerState() { return playerState; }
};
