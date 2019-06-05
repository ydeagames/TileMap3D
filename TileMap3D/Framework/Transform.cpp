#include "pch.h"
#include "Transform.h"

// コンストラクタ
Transform::Transform()
	: Parent(nullptr)
	, LocalPosition(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f))
	, LocalEulerAngles(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f))
	, LocalScale(DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f))
{
}

// 座標取得
DirectX::SimpleMath::Vector3 Transform::GetPosition() const
{
	return LocalPosition + (Parent != nullptr ? Parent->GetPosition() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// 座標設定
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& value)
{
	LocalPosition = value - (Parent != nullptr ? Parent->GetPosition() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// ローカル位置
DirectX::SimpleMath::Vector3 Transform::GetEulerAngles() const
{
	return LocalEulerAngles + (Parent != nullptr ? Parent->GetEulerAngles() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// 回転取得
void Transform::SetEulerAngles(const DirectX::SimpleMath::Vector3& value)
{
	LocalEulerAngles = value - (Parent != nullptr ? Parent->GetEulerAngles() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// 回転設定
DirectX::SimpleMath::Matrix Transform::GetMMatrix() const
{
	return (GetLocalScaleMatrix() * GetLocalRotateMatrix() * GetLocalPositionMatrix())
		* (Parent != nullptr ? Parent->GetMMatrix() : DirectX::SimpleMath::Matrix::Identity);
}

// ローカルオイラー角
DirectX::SimpleMath::Matrix Transform::GetLocalScaleMatrix() const
{
	return DirectX::SimpleMath::Matrix::CreateScale(LocalScale);
}

// ローカルスケール
DirectX::SimpleMath::Matrix Transform::GetLocalRotateMatrix() const
{
	// X軸回転行列
	auto localRotateXMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(1, 0, 0), LocalEulerAngles.x);
	// Y軸回転行列
	auto localRotateYMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0, 1, 0), LocalEulerAngles.y);
	// Z軸回転行列
	auto localRotateZMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0, 0, 1), LocalEulerAngles.z);
	// ZXYの順で計算
	return localRotateZMatrix * localRotateXMatrix * localRotateYMatrix;
}

// 行列取得
DirectX::SimpleMath::Matrix Transform::GetLocalPositionMatrix() const
{
	return DirectX::SimpleMath::Matrix::CreateTranslation(LocalPosition);
}
