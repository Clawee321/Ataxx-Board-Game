#pragma once
#include "Pion.h"

class Game
{
private:
	int bluePointCounter;
	int redPointCounter;
	int turn;
public:
	Game();
	void BlueSetPoints(int bPoints);	//ustawienie punkt�w
	void RedSetPoints(int rPoints);
	
	void ChangeTurn();	//zmiana stron
	int Winner();	//zwraca wygranego
	int WhoseTurn();	//daje zna� czyja kolej
	int BluePoints();	//zwraca punkty
	int RedPoints();
};

