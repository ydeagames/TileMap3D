#pragma once

// Transformクラス
class Transform
{
public:
	// コンストラクタ
	Transform::Transform();

public:
	// 座標取得
	DirectX::SimpleMath::Vector3 GetPosition() const;
	// 座標設定
	void SetPosition(const DirectX::SimpleMath::Vector3& value);

	// ローカル位置
	DirectX::SimpleMath::Vector3 LocalPosition;

	// 回転取得
	DirectX::SimpleMath::Vector3 GetEulerAngles() const;
	// 回転設定
	void SetEulerAngles(const DirectX::SimpleMath::Vector3& value);

	// ローカルオイラー角
	DirectX::SimpleMath::Vector3 LocalEulerAngles;

	// ローカルスケール
	DirectX::SimpleMath::Vector3 LocalScale;

public:
	// 親Transform
	const Transform* Parent;

	// 行列取得
	DirectX::SimpleMath::Matrix GetMMatrix() const;

	// ローカルスケール行列
	DirectX::SimpleMath::Matrix GetLocalScaleMatrix() const;
	// ローカル回転
	DirectX::SimpleMath::Matrix GetLocalRotateMatrix() const;
	// ローカル座標
	DirectX::SimpleMath::Matrix GetLocalPositionMatrix() const;
};