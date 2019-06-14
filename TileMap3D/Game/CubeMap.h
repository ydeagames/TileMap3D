#pragma once
#include <Framework/GameObject.h>
#include "TiledMap.h"
#include "Othello.h"

class CubeMap : public GameObject
{
	// マップ
	std::shared_ptr<TiledMap> m_tiledMap;
	std::shared_ptr<TiledMap> m_tiledStone;
	// ジオメトリプリミティブ
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitiveFloating;
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	// テクスチャ
	std::unordered_map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
	// コライダー
	DirectX::BoundingBox m_boundingBox;
	// オセロ
	std::shared_ptr<Othello> m_othello;

public:
	CubeMap(const std::shared_ptr<TiledMap>& tiledMap, const std::shared_ptr<TiledMap>& tiledStone, const std::shared_ptr<Othello>& othello)
		: m_tiledMap(tiledMap)
		, m_tiledStone(tiledStone)
		, m_othello(othello) {}

public:
	// 生成
	void Initialize(GameContext& context);
	// 更新
	void Update(GameContext& context);
	// 描画
	void Render(GameContext& context);
};

