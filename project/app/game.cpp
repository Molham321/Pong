
#include "game.h"
#include "application.h"

using namespace gfx;

void run()
{
	puts("\n\n\n\n\n");
	puts("					      Controll						");
	puts("					      --------						");
	puts("					Left  Player: W & S					");
	puts("					Right Player: O & L					");
	puts("\n");
	puts("					====================				");
	puts("				    ||  Press Space to Start  ||		");
	puts("					====================				");
	puts("\n\n\n\n\n");


	system("pause");
}

void CheckWinner(float m_BallPositionX)
{
	if (m_BallPositionX < CField::s_NullPointX1)
	{
		puts("right Player Won");
		StopApplication();
	}
	if (m_BallPositionX > CField::s_NullPointX2)
	{
		puts("left Player Won");
		StopApplication();
	}
}
