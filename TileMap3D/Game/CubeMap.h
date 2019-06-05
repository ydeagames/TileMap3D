#pragma once
#include <Framework/GameObject.h>
#include "TiledMap.h"

class CubeMap : public GameObject
{
	// �}�b�v
	std::shared_ptr<TiledMap> m_tiledMap;
	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	// �e�N�X�`��
	std::unordered_map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

public:
	CubeMap(const std::shared_ptr<TiledMap>& tiledMap)
		: m_tiledMap(tiledMap) {}

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
};

