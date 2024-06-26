#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "Fbx.h"
#include "Transform.h"

//-----------------------------------------------------------
//3Dモデル（FBXファイル）を管理する
//-----------------------------------------------------------
namespace Model
{
	//モデル情報
	struct ModelData
	{
		//ファイル名
		std::string fileName;

		//ロードしたモデルデータのアドレス
		Fbx* pFbx;

		//行列
		Transform 	transform;

		//アニメーションのフレーム
		bool isAimeStop;
		float nowFrame, animSpeed;
		int startFrame, endFrame;

		// ブレンディング用フィールド
		bool isBlending;
		float blendNowFrame;
		int blendStartFrame;
		int blendEndFrame;
		float blendWeight;


		//初期化
		ModelData() : pFbx(nullptr), isAimeStop(false), nowFrame(0), startFrame(0), endFrame(0), animSpeed(0),
			isBlending(false), blendNowFrame(0.0f), blendStartFrame(0), blendEndFrame(0), blendWeight(0.0f)
		{
		}

		void SetAnimeStop(bool b) { isAimeStop = b; };

		//アニメーションのフレーム数をセット
		//引数：startFrame	開始フレーム
		//引数：endFrame	終了フレーム
		//引数：animSpeed	アニメーション速度
		void SetAnimFrame(int start, int end, float speed)
		{
			isBlending = false;

			nowFrame = (float)start;
			startFrame = start;
			endFrame = end;
			animSpeed = speed;
		}

		// ブレンディングアニメーションのパラメータを設定
		void SetBlendingAnimFrame(int _startFrame1, int _endFrame1, int _startFrame2, int _endFrame2, float _blendSpeed, float _blendWeight)
		{
			isBlending = true;

			nowFrame = (float)_startFrame1;
			blendNowFrame = (float)_startFrame2;
			blendStartFrame = _startFrame2;
			endFrame = _endFrame1;
			blendEndFrame = _endFrame2;
			animSpeed = _blendSpeed;
			blendWeight = _blendWeight;
		}
	};


	//初期化
	void Initialize();

	//モデルをロード
	//引数：fileName　ファイル名
	//戻値：そのモデルデータに割り当てられた番号
	int Load(std::string fileName, int _order = -1, int _type = 0);

	//描画
	//引数：handle	描画したいモデルの番号
	//引数：matrix	ワールド行列
	void Draw(int handle, int type = 0);

	void DrawOrder();

	//任意のモデルを開放
	//引数：handle	開放したいモデルの番号
	void Release(int handle);

	//全てのモデルを解放
	//（シーンが切り替わるときは必ず実行）
	void AllRelease();

	void SetAnimeStop(int handle, bool b);

	//ブレンディングする二つのフレーム数と影響度をセット
	//引数：handle		設定したいモデルの番号
	//引数：startFrame	開始フレーム1
	//引数：endFrame	終了フレーム1
	//引数：startFrame	開始フレーム2
	//引数：endFrame	終了フレーム2
	//引数：animSpeed	アニメーション速度
	//引数：blendWeight アニメーション２の影響度
	void SetBlendingAnimFrame(int handle, int startFrame1, int endFrame1, int startFrame2, int endFrame2, float animSpeed, float blendWeight);

	//アニメーションのフレーム数をセット
	//引数：handle		設定したいモデルの番号
	//引数：startFrame	開始フレーム
	//引数：endFrame	終了フレーム
	//引数：animSpeed	アニメーション速度
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	//現在のアニメーションのフレームを取得
	int GetAnimFrame(int handle);

	//任意のボーンの位置を取得
	//引数：handle		調べたいモデルの番号
	//引数：boneName	調べたいボーンの名前
	//戻値：ボーンの位置（ワールド座標）
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	XMFLOAT3 GetBoneAnimPosition(int handle, std::string boneName);

	//ワールド行列を設定
	//引数：handle	設定したいモデルの番号
	//引数：matrix	ワールド行列
	void SetTransform(int handle, Transform& transform);

	//ワールド行列の取得
	//引数：handle	知りたいモデルの番号
	//戻値：ワールド行列
	XMMATRIX GetMatrix(int handle);

	//レイキャスト（レイを飛ばして当たり判定）　※未実装
	//引数：handle	判定したいモデルの番号
	//引数：data	必要なものをまとめたデータ
	void RayCast(int handle, RayCastData* data);

	void StopDraw(int handle);

};