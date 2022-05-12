
#pragma once

#include"field.h"

class CBall
{
public:

	/* ball constant */

	static constexpr float s_BallSize = 0.1f;
	static constexpr float s_BallSpeedX = 0.12f;
	static constexpr float s_BallSpeedY = 0.12f;
	static constexpr float s_BallStartPositionX = CField::s_GameBoardWidth / 2;
	static constexpr float s_BallStartPositionY = CField::s_GameBoardHeight / 2;

};