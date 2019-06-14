#include "pch.h"
#include "CubeMap.h"
#include <Framework/GameContext.h>
#include <Framework/GameCamera.h>
#include <GeometricPrimitive.h>
#include <Utilities/Input.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CubeMap::Initialize(GameContext& context)
{
	auto device = context.GetDR().GetD3DDevice();
	auto ctx = context.GetDR().GetD3DDeviceContext();

	m_pGeometricPrimitive = DirectX::GeometricPrimitive::CreateBox(ctx, Vector3::One);
	m_pGeometricPrimitiveFloating = DirectX::GeometricPrimitive::CreateGeoSphere(ctx);

	m_boundingBox = BoundingBox(Vector3::Zero, Vector3(8.f, .18f, 8.f));
	m_othello = std::make_unique<Othello>(m_tiledStone.get());
	m_othello->Initialize();

	// BasicEffect
	{
		// ポリゴン用エフェクト作成
		m_pBasicEffect = std::make_unique<BasicEffect>(device);
		// テクスチャを有効化 (重要) !!!!
		m_pBasicEffect->SetTextureEnabled(true);
		// ライト有効
		m_pBasicEffect->SetLightingEnabled(true);
		// 頂点色
		//m_pBasicEffect->SetVertexColorEnabled(true);
		// 環境光の色を設定
		m_pBasicEffect->SetAmbientLightColor(SimpleMath::Vector3(0.2f, 0.2f, 0.2f));
		// 拡散反射光の素材色を設定
		m_pBasicEffect->SetDiffuseColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		// ライト０番を有効
		m_pBasicEffect->SetLightEnabled(0, true);
		// ライト０番の色設定
		m_pBasicEffect->SetLightDiffuseColor(0, SimpleMath::Vector3(0.8f, 0.8f, 0.8f));
		// ライト０番の向きを設定
		m_pBasicEffect->SetLightDirection(0, SimpleMath::Vector3(.5f, -1.f, .25f));

		//void const * shaderByteCode;
		//size_t byteCodeLength;
		//// シェーダー取得
		//m_pBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
		//// 入力レイアウトの作成（頂点データの定義する）
		//device->CreateInputLayout(VertexPositionNormalColorTexture::InputElements,
		//	VertexPositionNormalColorTexture::InputElementCount,
		//	shaderByteCode, byteCodeLength,
		//	m_pInputLayout.GetAddressOf());
		//device->CreateInputLayout(GeometricPrimitive::VertexType::InputElements,
		//	GeometricPrimitive::VertexType::InputElementCount,
		//	shaderByteCode, byteCodeLength,
		//	m_pInputLayout.GetAddressOf());
		// 入力レイアウトの作成（頂点データの定義する）
		m_pGeometricPrimitive->CreateInputLayout(m_pBasicEffect.get(), m_pInputLayout.GetAddressOf());
	}

	CreateWICTextureFromFile(device, L"Resources/Textures/white.png", nullptr, m_textures[-2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources/Textures/CorkBoard.png", nullptr, m_textures[-1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources/Textures/grass.png", nullptr, m_textures[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources/Textures/water.png", nullptr, m_textures[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources/Textures/concrete.png", nullptr, m_textures[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources/Textures/substance.png", nullptr, m_textures[3].GetAddressOf());
}

void CubeMap::Update(GameContext & context)
{
	m_othello->Update();
}

void CubeMap::Render(GameContext & context)
{
	auto ctx = context.GetDR().GetD3DDeviceContext();

	// BasicEffect
	{
		// ビュー行列設定
		m_pBasicEffect->SetView(context.GetCamera().view);
		// プロジェクション行列設定
		m_pBasicEffect->SetProjection(context.GetCamera().projection);
		// エフェクトの設定
		m_pBasicEffect->Apply(ctx);
		// 深度ステンシルステートの設定
		ctx->OMSetDepthStencilState(context.GetStates().DepthDefault(), 0);
		// ブレンドステートの設定
		ctx->OMSetBlendState(context.GetStates().AlphaBlend(), nullptr, 0xffffffff);
		// ラスタライザステートを設定
		ctx->RSSetState(context.GetStates().CullClockwise());
		// 入力レイアウトの設定
		ctx->IASetInputLayout(m_pInputLayout.Get());
	}

	auto trans = Matrix::CreateTranslation(Vector3(-4, 0, -4));
	auto mat = transform.GetMMatrix() * Matrix::CreateTranslation(Vector3(.5, 0, .5)) * trans * Matrix::CreateScale(Vector3(1.f, .2f, 1.f));

	//float floatingY = (std::sin(context.GetTimer().GetTotalSeconds()) + 1) / 2 * .2f;
	float floatingY = .2f;

	m_pBasicEffect->SetDiffuseColor(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	m_pBasicEffect->SetTexture(m_textures[-2].Get());
	//m_pBasicEffect->SetColorAndAlpha(Colors::White);
	m_pBasicEffect->SetWorld(Matrix::CreateScale(Vector3(8.f, .18f, 8.f)));
	m_pGeometricPrimitive->Draw(m_pBasicEffect.get(), m_pInputLayout.Get());

	{
		int row = m_tiledMap->GetRow();
		int column = m_tiledMap->GetColumn();
		auto& data = m_tiledMap->GetData();
		for (int iy = 0; iy < row; iy++)
		{
			for (int ix = 0; ix < column; ix++)
			{
				int& id = data[iy][ix];
				m_pBasicEffect->SetDiffuseColor(SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
				m_pBasicEffect->SetTexture(m_textures[id].Get());
				m_pBasicEffect->SetWorld(Matrix::CreateScale(.98f) * mat * Matrix::CreateTranslation(Vector3(float(ix), 0.f, float(iy))));
				m_pGeometricPrimitive->Draw(m_pBasicEffect.get(), m_pInputLayout.Get());
			}
		}
	}
	{
		int row = m_tiledStone->GetRow();
		int column = m_tiledStone->GetColumn();
		auto& data = m_tiledStone->GetData();
		for (int iy = 0; iy < row; iy++)
		{
			for (int ix = 0; ix < column; ix++)
			{
				int& id = data[iy][ix];
				if (id != 0)
				{
					m_pBasicEffect->SetDiffuseColor(id == 1 ? SimpleMath::Vector3(0.0f, 0.0f, 0.0f) : SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
					m_pBasicEffect->SetTexture(m_textures[-2].Get());
					m_pBasicEffect->SetWorld(Matrix::CreateScale(.98f) * mat * Matrix::CreateTranslation(Vector3(float(ix), floatingY, float(iy))));
					m_pGeometricPrimitiveFloating->Draw(m_pBasicEffect.get(), m_pInputLayout.Get());
				}
			}
		}
	}
	{
		auto mouse = Mouse::Get().GetState();
		auto point = Vector2(float(mouse.x), float(mouse.y));
		auto ray = context.GetCamera().ScreenPointToRay(Vector3(point));
		float dist;
		if (ray.Intersects(m_boundingBox, dist))
		{
			auto raypos = ray.position + ray.direction * dist;
			auto pos0 = Vector3::Transform(raypos, trans.Invert());
			auto stonePos = Othello::StonePosition{ int(std::floor(pos0.x)), int(std::floor(pos0.z)) };

			if (Input::GetMouseButtonDown(Input::Buttons::MouseLeft))
			{
				if (0 <= stonePos.x && stonePos.x < 8 && 0 <= stonePos.y && stonePos.y < 8)
					m_othello->Place(stonePos);
			}

			auto pos1 = Vector3(float(stonePos.x), raypos.y, float(stonePos.y));

			m_pBasicEffect->SetDiffuseColor(m_othello->m_turn == 1 ? SimpleMath::Vector3(0.0f, 0.0f, 0.0f) : SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
			m_pBasicEffect->SetTexture(m_textures[-2].Get());
			m_pBasicEffect->SetWorld(Matrix::CreateScale(.98f) * mat * Matrix::CreateTranslation(Vector3(pos1.x, floatingY, pos1.z)));
			m_pGeometricPrimitiveFloating->Draw(m_pBasicEffect.get(), m_pInputLayout.Get());
		}
	}
}
