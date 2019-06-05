#include "pch.h"
#include "Transform.h"

// �R���X�g���N�^
Transform::Transform()
	: Parent(nullptr)
	, LocalPosition(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f))
	, LocalEulerAngles(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f))
	, LocalScale(DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f))
{
}

// ���W�擾
DirectX::SimpleMath::Vector3 Transform::GetPosition() const
{
	return LocalPosition + (Parent != nullptr ? Parent->GetPosition() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// ���W�ݒ�
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& value)
{
	LocalPosition = value - (Parent != nullptr ? Parent->GetPosition() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// ���[�J���ʒu
DirectX::SimpleMath::Vector3 Transform::GetEulerAngles() const
{
	return LocalEulerAngles + (Parent != nullptr ? Parent->GetEulerAngles() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// ��]�擾
void Transform::SetEulerAngles(const DirectX::SimpleMath::Vector3& value)
{
	LocalEulerAngles = value - (Parent != nullptr ? Parent->GetEulerAngles() : DirectX::SimpleMath::Vector3(0, 0, 0));
}

// ��]�ݒ�
DirectX::SimpleMath::Matrix Transform::GetMMatrix() const
{
	return (GetLocalScaleMatrix() * GetLocalRotateMatrix() * GetLocalPositionMatrix())
		* (Parent != nullptr ? Parent->GetMMatrix() : DirectX::SimpleMath::Matrix::Identity);
}

// ���[�J���I�C���[�p
DirectX::SimpleMath::Matrix Transform::GetLocalScaleMatrix() const
{
	return DirectX::SimpleMath::Matrix::CreateScale(LocalScale);
}

// ���[�J���X�P�[��
DirectX::SimpleMath::Matrix Transform::GetLocalRotateMatrix() const
{
	// X����]�s��
	auto localRotateXMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(1, 0, 0), LocalEulerAngles.x);
	// Y����]�s��
	auto localRotateYMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0, 1, 0), LocalEulerAngles.y);
	// Z����]�s��
	auto localRotateZMatrix = DirectX::SimpleMath::Matrix::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0, 0, 1), LocalEulerAngles.z);
	// ZXY�̏��Ōv�Z
	return localRotateZMatrix * localRotateXMatrix * localRotateYMatrix;
}

// �s��擾
DirectX::SimpleMath::Matrix Transform::GetLocalPositionMatrix() const
{
	return DirectX::SimpleMath::Matrix::CreateTranslation(LocalPosition);
}
