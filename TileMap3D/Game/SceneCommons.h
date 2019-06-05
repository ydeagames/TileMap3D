#pragma once
#include "Framework/GameObject.h"
#include "Framework/GameContext.h"

class GeometricObject : public GameObject
{
	// �W�I���g���v���~�e�B�u
	std::function<std::unique_ptr<DirectX::GeometricPrimitive>(GameContext& context)> m_geometricPrimitiveGenerator;
	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	// �F
	DirectX::SimpleMath::Color m_color;

public:
	// �R���X�g���N�^
	GeometricObject(const std::function<std::unique_ptr<DirectX::GeometricPrimitive>(GameContext& context)>& generator, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(DirectX::Colors::Gray))
		: m_geometricPrimitiveGenerator(generator)
		, m_color(color)
	{
	}
	// ����
	void Initialize(GameContext& context);
	// �`��
	void Render(GameContext& context);
};

class FontObject : public GameObject
{
	// �t�H���g�l�[��
	std::wstring m_fontName;
	// �t�H���g�l�[��
	std::wstring m_text;
	// �o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// �F
	DirectX::SimpleMath::Color m_color;

public:
	// �R���X�g���N�^
	FontObject(const std::wstring& fontName, const std::wstring& text, DirectX::SimpleMath::Color color = DirectX::SimpleMath::Color(DirectX::Colors::White))
		: m_fontName(fontName)
		, m_text(text)
		, m_color(color)
	{
	}
	// ����
	void Initialize(GameContext& context);
	// �`��
	void Render(GameContext& context);

public:
	inline void SetText(const std::wstring& text) { m_text = text; }
	inline const std::wstring GetText() const { return m_text; }
};
