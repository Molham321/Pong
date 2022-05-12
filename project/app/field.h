
#pragma once

class CField
{
public:

	/* Field constants */

	static constexpr int s_GameBoardWidth = 15;
	static constexpr int s_GameBoardHeight = 10;

	static constexpr float s_CubeSize = 1.0f;
	static constexpr float s_NullPointX1 = 0.0f;
	static constexpr float s_NullPointX2 = s_GameBoardWidth;
	static constexpr float s_CollisionDistance = s_CubeSize * 0.5f;

};
