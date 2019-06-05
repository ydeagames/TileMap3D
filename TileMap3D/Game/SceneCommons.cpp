#include "pch.h"
#include "SceneCommons.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void GeometricObject::Initialize(GameContext& context)
{
	// �W�I���g���쐬
	m_pGeometricPrimitive = m_geometricPrimitiveGenerator(context);
}

void GeometricObject::Render(GameContext& context)
{
	// �W�I���g���`��
	m_pGeometricPrimitive->Draw(transform.GetMMatrix(), context.GetCamera().view, context.GetCamera().projection, m_color);
}

void FontObject::Initialize(GameContext& context)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context.GetDR().GetD3DDeviceContext());
	m_spriteFont = std::make_unique<SpriteFont>(context.GetDR().GetD3DDevice(), m_fontName.c_str());
}

void FontObject::Render(GameContext& context)
{
	m_spriteBatch->Begin(SpriteSortMode_Deferred, context.GetStates().AlphaBlend());
	m_spriteFont->DrawString(m_spriteBatch.get(), m_text.c_str(), transform.GetPosition());
	m_spriteBatch->End();
}
