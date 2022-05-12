
#pragma once

#include "field.h"

class CBat
{
public:

	/* bat constant */

	static constexpr float s_BatSize = 2.0f;
	static constexpr float s_BatSpeed = 0.4f;
	static constexpr float s_BatCollisionBall = 0.1f;

	static constexpr float s_BatStartHeightPositionY1 = CField::s_GameBoardHeight / 2;
	static constexpr float s_BatStartHeightPositionY2 = CField::s_GameBoardHeight / 2;

	static constexpr float s_BatStartWidthPositionX1 = 0.0f;
	static constexpr float s_BatStartWidthPositionX2 = CField::s_GameBoardWidth - 1;

};