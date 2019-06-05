//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Game/BuildSettings.h"

#include <WICTextureLoader.h>

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
	// �f�o�C�X���\�[�X������
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);

	// �V�[���}�l�[�W���[
	m_sceneManager = std::make_unique<SceneManager>();
	// �V�[��
	m_pKeyboardStateTracker = std::make_unique<Keyboard::KeyboardStateTracker>();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// �}�E�X�̍쐬
	m_pMouse = std::make_unique<Mouse>();
	m_pMouse->SetWindow(window);

	// �L�[�{�[�h�̍쐬
	m_pKeyboard = std::make_unique<Keyboard>();

	// �ݒ�
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    m_deviceResources->CreateWindowSizeDependentResources();

	// �R�����X�e�[�g���쐬����
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
	// EffectFactory�I�u�W�F�N�g�𐶐�����
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_deviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	m_effectFactory->SetDirectory(L"Resources/Models");

    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	// ���`�b�N����
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

	// �`��
    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	// �L�[�{�[�h�X�e�[�g�g���b�J�[�X�V
	GetKeyboardStateTracker().Update(Keyboard::Get().GetState());
	// �V�[������
	GetSceneManager().ProcessScene(*this);
	// �X�V
	GetSceneManager().GetActiveScene().scene->Update(*this);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

	// �N���A
    Clear();

	// ��������`��
    m_deviceResources->PIXBeginEvent(L"Render");

    // TODO: Add your rendering code here.
	GetSceneManager().GetActiveScene().scene->Render(*this);

	// �����܂ŕ`��
    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    // TODO: Initialize device dependent objects here (independent of window size).

	// �쐬
	BuildSettings().Build(*this);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);
	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);
	// �ˉe�s����쐬����
	GetCamera().projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f
	);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	// �j��
	GetSceneManager().GetActiveScene().scene->Finalize(*this);
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
