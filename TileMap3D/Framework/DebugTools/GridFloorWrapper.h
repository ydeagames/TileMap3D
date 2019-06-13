#include <Framework/GameObject.h>
#include "GridFloor.h"

class GridFloorWrapper : public GameObject
{
	// グリッド床
	std::unique_ptr<GridFloor> m_pGridFloor;
	// 生成
	void Initialize(GameContext& context);
	// 描画
	void Render(GameContext& context);
};
