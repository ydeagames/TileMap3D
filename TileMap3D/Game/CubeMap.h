#pragma once
#include <Framework/GameObject.h>
#include "TiledMap.h"

class CubeMap : public GameObject
{
	// マップ
	std::shared_ptr<TiledMap> m_tiledMap;
	// ジオメトリプリミティブ
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	// テクスチャ
	std::unordered_map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

public:
	CubeMap(const std::shared_ptr<TiledMap>& tiledMap)
		: m_tiledMap(tiledMap) {}

public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
};

