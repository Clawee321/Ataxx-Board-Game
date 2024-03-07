#include "game.h"


Game::Game()
{
	this->bluePointCounter = 2;
	this->redPointCounter = 2;
	this->turn = 1;

}

void Game::BlueSetPoints(int bPoints)
{
	this->bluePointCounter = bPoints;
}

void Game::RedSetPoints(int rPoints)
{
	this->redPointCounter = rPoints;
}



void Game::ChangeTurn()
{
	if (this->turn == 0)
		this->turn = 1;
	else
		this->turn = 0;
}

int Game::Winner()
{
	if (bluePointCounter > redPointCounter)
		return 0;
	else
		return 1;
}

int Game::WhoseTurn()
{
	return this->turn;
}
int Game::BluePoints()
{
	return bluePointCounter;
}
int Game::RedPoints()
{
	return redPointCounter;
}