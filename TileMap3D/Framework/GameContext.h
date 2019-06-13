#pragma once
#include <Common/StepTimer.h>
#include <Common/DeviceResources.h>

class Scene;
class GameObject;
class SceneManager;
class GameCamera;

// GameContext�C���^�[�t�F�C�X
class GameContext
{
public:
	GameContext() = default;
	virtual ~GameContext() = default;

public:
	// DeviceResource�擾
	virtual DX::DeviceResources& GetDR() = 0;
	// �^�C�}�[�擾
	virtual DX::StepTimer& GetTimer() = 0;
	// �J�����擾
	virtual GameCamera& GetCamera() = 0;
	// �R�����X�e�[�g�擾
	virtual DirectX::CommonStates& GetStates() = 0;
	// �G�t�F�N�g�t�@�N�g���[�擾
	virtual DirectX::EffectFactory& GetEffectFactory() = 0;
	// �L�[�{�[�h�X�e�[�g�g���b�J�[
	virtual DirectX::Keyboard::KeyboardStateTracker& GetKeyboardStateTracker() = 0;
	// �V�[�����擾
	virtual Scene& GetScene() = 0;
	// �V�[���ɃI�u�W�F�N�g��ǉ�
	virtual GameContext& operator<<(const std::shared_ptr<GameObject>& obj) = 0;
	// �V�[���}�l�[�W�����擾
	virtual SceneManager& GetSceneManager() = 0;
};
