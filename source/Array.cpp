#include "Array.h"
#include "iostream"

Array::Array()
{
	array = new Field *[10];
	for(int i = 0; i < 10; i++)
	{
		array[i] = new Field[10];
		for (int j = 0; j < 10; j++)
		{
			array[i][j].isShip = false;
			array[i][j].isShot = false;
		}
	}
}

bool Array::shoot(int x, int y)
{
	if ((x >= 0 && x<=9 && y >= 0 && y<=9)  && !array[x][y].isShot)
	{
		array[x][y].isShot = true;
		return true;
	}
	return false;
}


const Field Array::getFieldInfo(int x, int y)
{
	return array[x][y];
}

//zwraca wartosc bool czy mozna postawic statek
//x, y pozycja kursora
//orientacja statku 
//dlugosc statku

bool Array::setShip(int x, int y, int orientation, int length)
{
	//sprawdzamy czy statek znajduje sie w wyznaczonym miejscu
	int xx;
	int yy;
	switch (orientation)
	{
	case 0:
		xx = x + length;
		yy = y;
		break;
	case 1:
		xx = x;
		yy = y + length;
		break;
	case 2:
		xx = x - length + 1;
		yy = y;
		break;
	case 3:
		xx = x;
		yy = y - length + 1;
		break;
	}

	if (xx > 10 || xx < 0 || yy > 10 || yy < 0)
	{
		return false;
	}
	
	switch (orientation)
	{
	case 0:
		//sprawdzanie czy statek nie znajduje sie na innym statku
		for (int i = x; i < xx; i++)
		{
			if (array[i][y].isShip == true)
			{
				return false;
			}
		}
		//zapisywanie statku do tablicy
		for (int i = x; i < xx; i++)
		{
			array[i][y].isShip = true;
		}
		break;
	case 1:

		//sprawdzanie czy statek nie znajduje sie na innym statku
		for (int i = y; i < yy; i++)
		{
			if (array[x][i].isShip == true)
			{
				return false;
			}
		}
		//zapisywanie statku do tablicy
		for (int i = y; i < yy; i++)
		{
			array[x][i].isShip = true;
		}
		break;
	case 2:

		//sprawdzanie czy statek nie znajduje sie na innym statku
		for (int i = xx; i <= x; i++)
		{
			if (array[i][y].isShip == true)
			{
				return false;
			}
		}
		//zapisywanie statku do tablicy
		for (int i = xx; i <= x; i++)
		{
			array[i][y].isShip = true;
		}
		break;
	case 3:
		//sprawdzanie czy statek nie znajduje sie na innym statku
		for (int i = yy; i <= y; i++)
		{
			if (array[x][i].isShip == true)
			{
				return false;
			}
		}
		//zapisywanie statku do tablicy
		for (int i = yy; i <= y; i++)
		{
			array[x][i].isShip = true;
		}
	}

	return true;
}

bool Array::ifLose()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (array[i][j].isShip && !array[i][j].isShot)
			{
				return false;
			}
		}
	}
	return true;
}

void Array::reset()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			array[i][j].isShip = false;
			array[i][j].isShot = false;
		}
	}
}