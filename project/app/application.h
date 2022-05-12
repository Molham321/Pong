
#pragma once

#include "yoshix_fix_function.h"
#include "field.h"
#include "ball.h"
#include "bat.h"
#include "position.h"

#include <math.h>
#include <conio.h>


class CApplication : public gfx::IApplication
{
public:

	CApplication();
	virtual ~CApplication();

private:

	using BHandle = gfx::BHandle;		/* namespase for BHandle */

	BHandle m_pCubeMesh;				/* A pointer to a YoshiX mesh, which represents a single cube */															
	BHandle m_pBatMesh;						
	BHandle m_pBallMesh;				/* A pointer to a YoshiX mesh, which represents a single sphere */

	SPosition m_BatPlayerOnePosition;	/* Bat coordination */												
	SPosition m_BatPlayerTowPosition;
	SPosition m_BallPosition;			/* Ball coordination */													
	SPosition m_BallSpeedPosition;		/* ball velocity on the x and y axis */													

	float const     m_BatMovementSpeedY;
	float			m_AngleY;
	float			m_GameBoard[CField::s_GameBoardWidth][CField::s_GameBoardHeight];		// Spielbrettmatrix

	bool            IsGameStarted;

private:

	void CreateCube(BHandle* _ppMesh, float _EdgeLength);		/* this is used to create walls and bat */
	void CreateSphere(BHandle* _ppMesh, float _Radius);			/* this is used to create ball */

	bool CheckCollision(int _xPosition, int _yPosition);		/* it is checked whether the ball position on the x and y axis has crossed a certain distance */

private:

	virtual bool InternOnStartup();
	virtual bool InternOnShutdown();
	virtual bool InternOnCreateMeshes();
	virtual bool InternOnReleaseMeshes();
	virtual bool InternOnResize(int _Width, int _Height);
	virtual bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
	virtual bool InternOnUpdate();
	virtual bool InternOnFrame();
};