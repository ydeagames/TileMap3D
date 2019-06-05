#pragma once

// Transform�N���X
class Transform
{
public:
	// �R���X�g���N�^
	Transform::Transform();

public:
	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPosition() const;
	// ���W�ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& value);

	// ���[�J���ʒu
	DirectX::SimpleMath::Vector3 LocalPosition;

	// ��]�擾
	DirectX::SimpleMath::Vector3 GetEulerAngles() const;
	// ��]�ݒ�
	void SetEulerAngles(const DirectX::SimpleMath::Vector3& value);

	// ���[�J���I�C���[�p
	DirectX::SimpleMath::Vector3 LocalEulerAngles;

	// ���[�J���X�P�[��
	DirectX::SimpleMath::Vector3 LocalScale;

public:
	// �eTransform
	const Transform* Parent;

	// �s��擾
	DirectX::SimpleMath::Matrix GetMMatrix() const;

	// ���[�J���X�P�[���s��
	DirectX::SimpleMath::Matrix GetLocalScaleMatrix() const;
	// ���[�J����]
	DirectX::SimpleMath::Matrix GetLocalRotateMatrix() const;
	// ���[�J�����W
	DirectX::SimpleMath::Matrix GetLocalPositionMatrix() const;
};