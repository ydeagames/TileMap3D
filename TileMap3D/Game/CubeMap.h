#pragma once
#include <Framework/GameObject.h>
#include "TiledMap.h"
#include "Othello.h"

class CubeMap : public GameObject
{
	// �}�b�v
	std::shared_ptr<TiledMap> m_tiledMap;
	std::shared_ptr<TiledMap> m_tiledStone;
	// �W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitiveFloating;
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	// �e�N�X�`��
	std::unordered_map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;
	// �R���C�_�[
	DirectX::BoundingBox m_boundingBox;
	// �I�Z��
	std::shared_ptr<Othello> m_othello;

public:
	CubeMap(const std::shared_ptr<TiledMap>& tiledMap, const std::shared_ptr<TiledMap>& tiledStone, const std::shared_ptr<Othello>& othello)
		: m_tiledMap(tiledMap)
		, m_tiledStone(tiledStone)
		, m_othello(othello) {}

public:
	// ����
	void Initialize(GameContext& context);
	// �X�V
	void Update(GameContext& context);
	// �`��
	void Render(GameContext& context);
};

