//
// Game.h
//

#pragma once

#include <Common/DeviceResources.h>
#include <Common/StepTimer.h>
#include "Mouse.h"
#include "Keyboard.h"

#include "SpriteBatch.h"
#include "SimpleMath.h"

#include "GameObject.h"
#include "GameContext.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameCamera.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify, public GameContext
{
public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>	m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer							m_timer;

	// �J�����I�u�W�F�N�g
    GameCamera								m_camera;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_state;
	
	// �G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory>	m_effectFactory;

	// �V�[���}�l�[�W���[
	std::unique_ptr<SceneManager>			m_sceneManager;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse>			m_pMouse;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>		m_pKeyboard;

public:
	// DeviceResource�擾
	DX::DeviceResources& GetDR()
	{
		return *m_deviceResources;
	}

	// �^�C�}�[�擾
	DX::StepTimer& GetTimer()
	{
		return m_timer;
	}

	// �J�����擾
	GameCamera& GetCamera()
	{
		return m_camera;
	}

	// �R�����X�e�[�g
	DirectX::CommonStates& GetStates()
	{
		return *m_state;
	}

	// �R�����X�e�[�g
	DirectX::EffectFactory& GetEffectFactory()
	{
		return *m_effectFactory;
	}

	// �V�[��
	Scene& GetScene()
	{
		return *m_sceneManager->GetActiveScene().scene;
	}

	// �I�u�W�F�N�g�ǉ�
	GameContext& operator<<(const std::shared_ptr<GameObject>& obj)
	{
		GetScene().gameObjects.push_back(obj);
		return *this;
	}

	// �V�[��
	SceneManager& GetSceneManager()
	{
		return *m_sceneManager;
	}
};