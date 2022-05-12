
#include "game.h"
#include "application.h"

using namespace gfx;

CApplication::CApplication()
	: m_AngleY(60.0f)
	, m_pCubeMesh(nullptr)
	, m_pBallMesh(nullptr)
	, m_pBatMesh(nullptr)
	, m_BallPosition(CBall::s_BallStartPositionX, CBall::s_BallStartPositionY)
	, m_BallSpeedPosition(0, 0)
	, m_BatPlayerOnePosition(CBat::s_BatStartWidthPositionX1, CBat::s_BatStartHeightPositionY1)
	, m_BatPlayerTowPosition(CBat::s_BatStartWidthPositionX2, CBat::s_BatStartHeightPositionY2)
	, m_BatMovementSpeedY(CBat::s_BatSpeed)
	, IsGameStarted(false)
	, m_GameBoard()
{
}

CApplication::~CApplication()
{
}

bool CApplication::InternOnStartup()
{

	/* the light in the center of the board */
	float LightPosition[3] = { CField::s_GameBoardWidth / 2, CField::s_GameBoardHeight / 2, -15.0f, };

	SetLightPosition(LightPosition);

	float LightAmbientColor[4] = { 0.3f, 0.3f, 0.3f, 1.0f, };
	float LightDiffuseColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f, };
	float LightSpecularColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f, };

	SetLightColor(LightAmbientColor, LightDiffuseColor, LightSpecularColor, 127);

	/* game board placeholder */
	for (int i = 0; i < CField::s_GameBoardWidth; i++)
	{
		for (int j = 0; j < CField::s_GameBoardHeight; j++)
		{
			if (j == 0 || j == CField::s_GameBoardHeight - 1)
			{
				m_GameBoard[i][j] = 999;
			}
		}
	}
	return true;
}

bool CApplication::InternOnShutdown()
{
	return true;
}

void CApplication::CreateSphere(BHandle* _ppMesh, float _Radius)
{
	static const float s_Pi = 3.1415926535897932384626433832795f;
	static const int   s_Delta = 10;
	static const int   s_NumberOfVerticalVertices = 180 / s_Delta + 1;
	static const int   s_NumberOfHorizontalVertices = 360 / s_Delta + 1;
	static const int   s_NumberOfVertices = s_NumberOfVerticalVertices * s_NumberOfHorizontalVertices;
	static const int   s_NumberOfIndices = s_NumberOfVertices * 2 * 3;

	int   IndexOfVertex;
	int   IndexOfIndex;

	float RadiusOfSphere;
	float CenterOfSphere[3];
	float RadiusOfHorizontalCircle;
	float CenterOfHorizontalCircle[3];
	float FirstVertexOfHorizontalCircle[3];
	float Distance[3];

	int   Indices[s_NumberOfIndices];
	float Vertices[s_NumberOfVertices * 3];
	float TexCoords[s_NumberOfVertices * 2];

	RadiusOfSphere = _Radius;

	CenterOfSphere[0] = 0.0f;
	CenterOfSphere[1] = 0.0f;
	CenterOfSphere[2] = 0.0f;

	IndexOfVertex = 0;

	for (float Alpha = 90.0f; Alpha <= 270; Alpha += s_Delta)
	{
		FirstVertexOfHorizontalCircle[0] = CenterOfSphere[0] + RadiusOfSphere * cos(s_Pi * Alpha / 180.0f);
		FirstVertexOfHorizontalCircle[1] = CenterOfSphere[1] + RadiusOfSphere * sin(s_Pi * Alpha / 180.0f);
		FirstVertexOfHorizontalCircle[2] = CenterOfSphere[2];

		CenterOfHorizontalCircle[0] = CenterOfSphere[0];
		CenterOfHorizontalCircle[1] = FirstVertexOfHorizontalCircle[1];
		CenterOfHorizontalCircle[2] = CenterOfSphere[2];

		Distance[0] = FirstVertexOfHorizontalCircle[0] - CenterOfHorizontalCircle[0];
		Distance[1] = FirstVertexOfHorizontalCircle[1] - CenterOfHorizontalCircle[1];
		Distance[2] = FirstVertexOfHorizontalCircle[2] - CenterOfHorizontalCircle[2];

		RadiusOfHorizontalCircle = sqrtf(Distance[0] * Distance[0] + Distance[1] * Distance[1] + Distance[2] * Distance[2]);

		for (float Gamma = 0.0f; Gamma <= 360; Gamma += s_Delta)
		{
			Vertices[IndexOfVertex * 3 + 0] = CenterOfHorizontalCircle[0] + RadiusOfHorizontalCircle * cos(s_Pi * Gamma / 180.0f);
			Vertices[IndexOfVertex * 3 + 1] = CenterOfHorizontalCircle[1];
			Vertices[IndexOfVertex * 3 + 2] = CenterOfHorizontalCircle[2] + RadiusOfHorizontalCircle * sin(s_Pi * Gamma / 180.0f);

			TexCoords[IndexOfVertex * 2 + 0] = Gamma / 360.0f;
			TexCoords[IndexOfVertex * 2 + 1] = (Alpha - 90.0f) / 180.0f;

			++IndexOfVertex;
		}
	}

	IndexOfIndex = 0;

	for (int IndexOfCircle = 0; IndexOfCircle < s_NumberOfVerticalVertices; ++IndexOfCircle)
	{
		int FirstIndexOfCircle = IndexOfCircle * s_NumberOfHorizontalVertices;

		for (int IndexOfTriangle = 0; IndexOfTriangle < s_NumberOfHorizontalVertices; ++IndexOfTriangle)
		{
			int UpperLeft = FirstIndexOfCircle + 0 + IndexOfTriangle;
			int UpperRight = FirstIndexOfCircle + 0 + IndexOfTriangle + 1;
			int LowerLeft = FirstIndexOfCircle + s_NumberOfHorizontalVertices + IndexOfTriangle;
			int LowerRight = FirstIndexOfCircle + s_NumberOfHorizontalVertices + IndexOfTriangle + 1;

			Indices[IndexOfIndex + 0] = LowerLeft;
			Indices[IndexOfIndex + 1] = LowerRight;
			Indices[IndexOfIndex + 2] = UpperRight;

			Indices[IndexOfIndex + 3] = LowerLeft;
			Indices[IndexOfIndex + 4] = UpperRight;
			Indices[IndexOfIndex + 5] = UpperLeft;

			IndexOfIndex += 6;
		}
	}

	SMeshInfo MeshInfo;

	MeshInfo.m_pVertices = Vertices;
	MeshInfo.m_pNormals = nullptr;
	MeshInfo.m_pColors = nullptr;
	MeshInfo.m_pTexCoords = nullptr;
	MeshInfo.m_NumberOfVertices = s_NumberOfVertices;
	MeshInfo.m_NumberOfIndices = s_NumberOfIndices;
	MeshInfo.m_pIndices = Indices;
	MeshInfo.m_pTexture = nullptr;

	CreateMesh(MeshInfo, _ppMesh);
}

void CApplication::CreateCube(BHandle* _ppMesh, float _EdgeLength)
{
	float s_HalfEdgeLength = 0.5f * _EdgeLength;

	float s_CubeVertices[][3] =
	{
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
	};

	static float s_CubeNormals[][3] =
	{
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },

		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },

		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },

		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },

		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },

		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
	};

	float s_U[] =
	{
		0.0f / 4.0f,
		1.0f / 4.0f,
		2.0f / 4.0f,
		3.0f / 4.0f,
		4.0f / 4.0f,
	};

	float s_V[] =
	{
		3.0f / 3.0f,
		2.0f / 3.0f,
		1.0f / 3.0f,
		0.0f / 3.0f,
	};

	float s_CubeTexCoords[][2] =
	{
		{ s_U[1], s_V[1], },
		{ s_U[2], s_V[1], },
		{ s_U[2], s_V[2], },
		{ s_U[1], s_V[2], },

		{ s_U[2], s_V[1], },
		{ s_U[3], s_V[1], },
		{ s_U[3], s_V[2], },
		{ s_U[2], s_V[2], },

		{ s_U[3], s_V[1], },
		{ s_U[4], s_V[1], },
		{ s_U[4], s_V[2], },
		{ s_U[3], s_V[2], },

		{ s_U[0], s_V[1], },
		{ s_U[1], s_V[1], },
		{ s_U[1], s_V[2], },
		{ s_U[0], s_V[2], },

		{ s_U[1], s_V[2], },
		{ s_U[2], s_V[2], },
		{ s_U[2], s_V[3], },
		{ s_U[1], s_V[3], },

		{ s_U[1], s_V[0], },
		{ s_U[2], s_V[0], },
		{ s_U[2], s_V[1], },
		{ s_U[1], s_V[1], },
	};

	int s_CubeIndices[][3] =
	{
		{  0,  1,  2, },
		{  0,  2,  3, },

		{  4,  5,  6, },
		{  4,  6,  7, },

		{  8,  9, 10, },
		{  8, 10, 11, },

		{ 12, 13, 14, },
		{ 12, 14, 15, },

		{ 16, 17, 18, },
		{ 16, 18, 19, },

		{ 20, 21, 22, },
		{ 20, 22, 23, },
	};

	SMeshInfo MeshInfo;

	MeshInfo.m_pVertices = &s_CubeVertices[0][0];
	MeshInfo.m_pNormals = &s_CubeNormals[0][0];
	MeshInfo.m_pColors = nullptr;
	MeshInfo.m_pTexCoords = nullptr;
	MeshInfo.m_NumberOfVertices = 24;
	MeshInfo.m_NumberOfIndices = 36;
	MeshInfo.m_pIndices = &s_CubeIndices[0][0];
	MeshInfo.m_pTexture = nullptr;

	CreateMesh(MeshInfo, _ppMesh);
}

bool CApplication::InternOnCreateMeshes()
{
	CreateCube(&m_pCubeMesh, CField::s_CubeSize);
	CreateSphere(&m_pBallMesh, 1.0f);
	CreateCube(&m_pBatMesh, 1.0f);

	return true;
}

bool CApplication::InternOnReleaseMeshes()
{
	ReleaseMesh(m_pCubeMesh);
	ReleaseMesh(m_pBallMesh);
	ReleaseMesh(m_pBatMesh);

	return true;
}

bool CApplication::InternOnResize(int _Width, int _Height)
{
	float ProjectionMatrix[16];

	GetProjectionMatrix(m_AngleY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 1000.0f, ProjectionMatrix);

	SetProjectionMatrix(ProjectionMatrix);

	return true;
}

bool CApplication::InternOnUpdate()
{
	float Eye[3];
	float At[3];
	float Up[3];

	float ViewMatrix[16];

	float height = CField::s_GameBoardHeight / 2;
	float width = CField::s_GameBoardWidth / 2;


	Eye[0] = width;        At[0] = width;      Up[0] = 0.0f;
	Eye[1] = height;       At[1] = height;     Up[1] = 1.0f;
	Eye[2] = -15.0f;        At[2] = 0.0f;       Up[2] = 0.0f;

	GetViewMatrix(Eye, At, Up, ViewMatrix);

	SetViewMatrix(ViewMatrix);

	return true;
}

bool CApplication::CheckCollision(int _X, int _Y)
{
	if (m_BallPosition.m_X > (_X - CField::s_CollisionDistance + 0.5f) &&
		m_BallPosition.m_X < (_X + CField::s_CollisionDistance + 0.5f) &&
		m_BallPosition.m_Y >(_Y - CField::s_CollisionDistance + 0.5f) &&
		m_BallPosition.m_Y < (_Y + CField::s_CollisionDistance + 0.5f))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CApplication::InternOnFrame()
{
	float WorldMatrix[16];
	float ScaleMatrix[16];
	float TranslationMatrix[16];

	//-----------Check Winner ----------- //

	CheckWinner(m_BallPosition.m_X);


	/* game board instead of placeholder */

	for (int column = 0; column < CField::s_GameBoardWidth; column++)
	{
		for (int row = 0; row < CField::s_GameBoardHeight; ++row)
		{
			if (m_GameBoard[column][row] == 999)
			{
				GetTranslationMatrix((float)column, (float)row + 0.5f, 0.0f, TranslationMatrix);
				GetScaleMatrix(CField::s_CubeSize, 0.5f, CField::s_CubeSize, ScaleMatrix);
				MulMatrix(ScaleMatrix, TranslationMatrix, WorldMatrix);
				SetWorldMatrix(WorldMatrix);
				DrawMesh(m_pCubeMesh);

				/* collision handling */

				if (CheckCollision(column, row))
				{
					if (row == CField::s_GameBoardHeight - 1)
					{
						m_BallPosition.m_Y = m_BallPosition.m_Y - m_BallSpeedPosition.m_Y;
						m_BallSpeedPosition.m_Y = -m_BallSpeedPosition.m_Y;
					}
					if (row == 0)
					{
						m_BallPosition.m_Y = m_BallPosition.m_Y - m_BallSpeedPosition.m_Y;
						m_BallSpeedPosition.m_Y = -m_BallSpeedPosition.m_Y;
					}
				}
			}
		}
	}

	//-----------Ball----------- //

	if (IsGameStarted)
	{
		GetScaleMatrix(CBall::s_BallSize, CBall::s_BallSize, CBall::s_BallSize, ScaleMatrix);
		GetTranslationMatrix(m_BallPosition.m_X, m_BallPosition.m_Y, 0.0f, TranslationMatrix);
		MulMatrix(ScaleMatrix, TranslationMatrix, WorldMatrix);

		SetWorldMatrix(WorldMatrix);
		DrawMesh(m_pBallMesh);

		m_BallPosition.m_X += m_BallSpeedPosition.m_X;
		m_BallPosition.m_Y += m_BallSpeedPosition.m_Y;

	}
	else
	{
		GetScaleMatrix(CBall::s_BallSize, CBall::s_BallSize, CBall::s_BallSize, ScaleMatrix);
		GetTranslationMatrix(m_BallPosition.m_X, m_BallPosition.m_Y, 0.0f, TranslationMatrix);

		MulMatrix(ScaleMatrix, TranslationMatrix, WorldMatrix);

		SetWorldMatrix(WorldMatrix);
		DrawMesh(m_pBallMesh);
	}

	/* Bat Collision */

	if ((abs(m_BallPosition.m_X - m_BatPlayerOnePosition.m_X) < CBat::s_BatCollisionBall) || (abs(m_BallPosition.m_X - m_BatPlayerTowPosition.m_X) < CBat::s_BatCollisionBall))
	{
		if ((m_BallPosition.m_Y > m_BatPlayerOnePosition.m_Y - CBat::s_BatSize / 2) &&
			(m_BallPosition.m_Y < m_BatPlayerOnePosition.m_Y + CBat::s_BatSize / 2) ||
			(m_BallPosition.m_Y > m_BatPlayerTowPosition.m_Y - CBat::s_BatSize / 2) &&
			(m_BallPosition.m_Y < m_BatPlayerTowPosition.m_Y + CBat::s_BatSize / 2))
		{
			m_BallSpeedPosition.m_X = -m_BallSpeedPosition.m_X;
		}
	}

	/* Bat Player one */

	GetTranslationMatrix(m_BatPlayerOnePosition.m_X, m_BatPlayerOnePosition.m_Y, 0.0f, TranslationMatrix);
	GetScaleMatrix(0.1f, CBat::s_BatSize, 0.1f, ScaleMatrix);
	MulMatrix(ScaleMatrix, TranslationMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);
	DrawMesh(m_pBatMesh);

	/* Bat Player tow */

	GetTranslationMatrix(m_BatPlayerTowPosition.m_X, m_BatPlayerTowPosition.m_Y, 0.0f, TranslationMatrix);
	GetScaleMatrix(0.1f, CBat::s_BatSize, 0.1f, ScaleMatrix);
	MulMatrix(ScaleMatrix, TranslationMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);
	DrawMesh(m_pBatMesh);


	return true;
}

/* Game Controller */

bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
{
	if (_Key == 'W' || _Key == 'w')
	{
		if (m_BatPlayerOnePosition.m_Y < CField::s_GameBoardHeight - CBat::s_BatSize)
		{
			m_BatPlayerOnePosition.m_Y += m_BatMovementSpeedY;
		}
	}
	if (_Key == 'S' || _Key == 's')
	{
		if (m_BatPlayerOnePosition.m_Y > CField::s_CubeSize * 2)
		{
			m_BatPlayerOnePosition.m_Y -= m_BatMovementSpeedY;
		}
	}

	if (_Key == 'O' || _Key == 'o')
	{
		if (m_BatPlayerTowPosition.m_Y < CField::s_GameBoardHeight - CBat::s_BatSize)
		{
			m_BatPlayerTowPosition.m_Y += m_BatMovementSpeedY;
		}
	}
	if (_Key == 'L' || _Key == 'l')
	{
		if (m_BatPlayerTowPosition.m_Y > CField::s_CubeSize * 2)
		{
			m_BatPlayerTowPosition.m_Y -= m_BatMovementSpeedY;
		}
	}

	if (_Key == ' ' && !IsGameStarted)
	{
		IsGameStarted = true;

		m_BallSpeedPosition.m_X = CBall::s_BallSpeedX;
		m_BallSpeedPosition.m_Y = CBall::s_BallSpeedY;
	}

	return true;
}
