#pragma once

class GameCamera
{
public:
	// �r���[�s��
	DirectX::SimpleMath::Matrix view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix projection;
	// �r���[�|�[�g���W
	DirectX::SimpleMath::Matrix viewport;

public:
	// �ʒu�擾
	DirectX::SimpleMath::Vector3 GetPosition() const;

	// �X�N���[�����W����Ray�ɕϊ�
	DirectX::SimpleMath::Ray ScreenPointToRay(const DirectX::SimpleMath::Vector3& point) const;
	// �X�N���[�����W����Ray�ɕϊ�
	DirectX::SimpleMath::Ray ViewportPointToRay(const DirectX::SimpleMath::Vector3& point) const;

	// ���[���h���W����X�N���[�����W�ɕϊ�
	DirectX::SimpleMath::Vector3 WorldToScreenPoint(const DirectX::SimpleMath::Vector3& point) const;
	// ���[���h���W����r���[�|�[�g���W�ɕϊ�
	DirectX::SimpleMath::Vector3 WorldToViewportPoint(const DirectX::SimpleMath::Vector3& point) const;
	// �r���[�|�[�g���W���烏�[���h���W�ɕϊ�
	DirectX::SimpleMath::Vector3 ViewportToWorldPoint(const DirectX::SimpleMath::Vector3& point) const;
	// �X�N���[�����W���烏�[���h���W�ɕϊ�
	DirectX::SimpleMath::Vector3 ScreenToWorldPoint(const DirectX::SimpleMath::Vector3& point) const;
	// �X�N���[�����W����r���[�|�[�g���W�ɕϊ�
	DirectX::SimpleMath::Vector3 ScreenToViewportPoint(const DirectX::SimpleMath::Vector3& point) const;
	// �r���[�|�[�g���W����X�N���[�����W�ɕϊ�
	DirectX::SimpleMath::Vector3 ViewportToScreenPoint(const DirectX::SimpleMath::Vector3& point) const;
};