#pragma once

// <���̓f�o�C�X>
class Input
{
private:
	static DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	static DirectX::Mouse::ButtonStateTracker m_mouseTracker;

public:
	enum class Buttons
	{
		MouseLeft,
		MouseRight,
		MouseMiddle,
		MouseXButton1,
		MouseXButton2,
	};

public:
	// �X�V
	static void Update();

	// Not implemented yet
	static float GetAxis(const std::string& axisName);
	static float GetAxisRaw(const std::string& axisName);
	static void ResetInputAxes();

	// Not implemented yet
	static bool GetButton(const std::string& buttonName);
	static bool GetButtonDown(const std::string& buttonName);
	static bool GetButtonUp(const std::string& buttonName);

	// �}�E�X
	static DirectX::Mouse::ButtonStateTracker::ButtonState GetMouseButtonState(Buttons button);
	static bool GetMouseButton(Buttons button);
	static bool GetMouseButtonDown(Buttons button);
	static bool GetMouseButtonUp(Buttons button);

	static DirectX::SimpleMath::Vector3 GetMousePosition();
	static DirectX::SimpleMath::Vector2 GetMouseScrollDelta();

	// �L�[�{�[�h
	static bool GetKey(DirectX::Keyboard::Keys button);
	static bool GetKeyUp(DirectX::Keyboard::Keys button);
	static bool GetKeyDown(DirectX::Keyboard::Keys button);

	static bool GetAnyKey();
	static bool GetAnyKeyDown();
};
