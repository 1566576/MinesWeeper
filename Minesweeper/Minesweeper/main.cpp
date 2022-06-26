#include<iostream>
#include "Tile.h"
#include <vector>
#include <limits>//analiza datos de cin
#include <string>
#include <stdio.h>      
#include <stdlib.h> 
#include <time.h>
bool check_Boundaries(int x, int y, int row, int col)
{
	if (row > x + 1 -97 || col > y + 1 - 97 || row < x - 1 - 97 || col < y - 1 - 97)
		return false;
	return true;
}
std::vector<std::vector<Tile>> Create_Grid(int N_Rows, int N_Columns, int Max_Mines,int x, int y)
{
	Tile tile;
	std::vector<Tile> row(N_Columns, tile);
	std::vector<std::vector<Tile>> Grid(N_Rows, row);
	srand(time(NULL));
	int aux, aux2;
	for (int i = 0; i < Max_Mines; i++)
	{
		aux = rand() % N_Rows;
		aux2 = rand() % N_Columns;
		if (Grid[aux][aux2].get_Mine() == false && check_Boundaries(x,y,aux,aux2)==false)
		{
			Grid[aux][aux2].set_Mine(true);
			Grid[aux][aux2].asign_Clicked('*');
		}
		else
			i--;
	}
	return Grid;
}
void Display_Grid(std::vector<std::vector<Tile>>& Grid, bool lost,bool first, int N_Rows,int  N_Columns)
{
	system("CLS");
	if (first==false)
	{
		std::cout << "  ";
		for (int j = 0; j < Grid[0].size(); j++)
			std::cout << (char)(j + 97) << " ";
		std::cout << std::endl;
		for (int i = 0; i < Grid.size(); i++)
		{
			std::cout << (char)(i + 97) << " ";
			for (int j = 0; j < Grid[i].size(); j++)
			{
				if (lost == true)
				{
					if (Grid[i][j].get_Mine() == true)
						std::cout << Grid[i][j].get_Clicked() << " ";
					else
						if (Grid[i][j].get_Square() == 'E' || Grid[i][j].get_Square() == '0')
							std::cout << " " << " ";
						else
							std::cout << Grid[i][j].get_Square() << " ";
				}
				else
					if (Grid[i][j].get_Square() == 'E' || Grid[i][j].get_Square() == '0')
						std::cout << " " << " ";
					else
						std::cout << Grid[i][j].get_Square() << " ";
			}
			std::cout << std::endl;
		}
	}
	else //se printea una grid vacia
	{
		char a = -2;
		std::cout << "  ";
		for (int j = 0; j < N_Columns; j++)
			std::cout << (char)(j + 97) << " ";
		std::cout << std::endl;
		for (int i = 0; i < N_Rows; i++)
		{
			std::cout << (char)(i + 97) << " ";
			for (int j = 0; j < N_Columns; j++)
				std::cout << a << " ";
			std::cout << std::endl;
		}
	}
}
bool check_Coord(char x, char y, std::vector<std::vector<Tile>>& Grid, int N_Rows, int N_Columns)
{
	Grid[x - 97][y - 97].set_Square(Grid[x - 97][y - 97].get_Clicked());
	if (Grid[x - 97][y - 97].get_Square() == '*')
		return true;
	int z, k;
	if (Grid[x - 97][y - 97].get_Square() == '0')
	{
		Grid[x - 97][y - 97].asign_Clicked('E');
		z = x - 1;
		k = y - 1;
		while (z < x + 2)
		{
			if (z == x && k == y)
				k++;
			if (z - 97 < N_Rows)
				if (k - 97 < N_Columns)
					if (z - 97 >= 0)
						if (k - 97 >= 0)
						{
							Grid[z - 97][k - 97].set_Square(Grid[z - 97][k - 97].get_Clicked());
							if (Grid[z - 97][k - 97].get_Square() == '0' && Grid[z - 97][k - 97].get_Clicked() != 'E')
								check_Coord(z, k, Grid, N_Rows, N_Columns);
						}
			k++;
			if (k > y + 1)
			{
				z++;
				k = y - 1;
			}
		}
	}
	return false;
}
void Options(char& x, char& y, std::vector<std::vector<Tile>> Grid, int first_try, int& N_Rows, int& N_Columns, int& Max_Mines)
{
	if (first_try != -1)
	{
		std::cout << "Row = ";
		std::cin >> x;
		std::cout << "Column = ";
		std::cin >> y;
		while (!std::cin.good() || x < 97 || x >= (N_Rows + 97) || y < 97 || y >= (N_Columns + 97))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");
			Display_Grid(Grid, false,false, N_Rows, N_Columns);
			std::cout << "Insert Correct data" << std::endl;
			std::cout << "Row = ";
			std::cin >> x;
			std::cout << "Column = ";
			std::cin >> y;
		}
	}
	else
	{
		std::cout << "Insert Data to create a Game:" << std::endl;
		std::cout << "Grid size:" << std::endl;
		std::cout << "Number of Rows (1-26)= ";
		std::cin >> N_Rows;
		std::cout << "Number of Columns (1-26)= ";
		std::cin >> N_Columns;

		std::cout << "Number of Mines (1-" << N_Rows * N_Columns << ", the optimal amount is " << (int)(N_Rows * N_Columns * 0.2) << ") = ";
		std::cin >> Max_Mines;

		while (!std::cin.good() || Max_Mines > N_Rows * N_Columns || Max_Mines <= 0 || N_Rows > 26 || N_Rows <= 0 || N_Columns > 26 || N_Columns <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");
			std::cout << "Insert CORRECT Data to create a Game:" << std::endl;
			std::cout << "Grid size:" << std::endl;
			std::cout << "Number of Rows (1-26)= ";
			std::cin >> N_Rows;
			std::cout << "Number of Columns (1-26)= ";
			std::cin >> N_Columns;

			std::cout << "Number of Mines (1-" << N_Rows * N_Columns << ", the optimal amount is " << (int)(N_Rows * N_Columns * 0.2) << ") = ";
			std::cin >> Max_Mines;
		}
	}
}
void Grid_Analysis(std::vector<std::vector<Tile>>& Grid, int N_Rows, int N_Columns)
{
	int x, y;
	int numero = 0;
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Columns; j++)
		{
			if (Grid[i][j].get_Mine() == false)
			{
				x = i - 1;
				y = j - 1;
				numero = 0;
				while (x < i + 2)
				{
					if (x == i && y == j)
						y++;
					if (x < N_Rows)
						if (y < N_Columns)
							if (x >= 0)
								if (y >= 0)
									if (Grid[x][y].get_Mine() == true)
										numero++;
					y++;
					if (y > j + 1)
					{
						x++;
						y = j - 1;
					}
				}
				std::string hi = std::to_string(numero);
				Grid[i][j].asign_Clicked(hi[0]);
			}
		}
	}
}
bool check_Win(std::vector<std::vector<Tile>> Grid, int N_Rows, int N_Columns, int Max_Mines)
{
	int a = 0;
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Columns; j++)
		{
			if (Grid[i][j].get_Square() == -2)
				a++;
			if (a > Max_Mines)
				return false;
		}
	}
	return true;
}
int main()
{
	char x, y;
	int N_Rows, N_Columns, Max_Mines;
	int first_try = -1;
	bool GameOver;
	std::vector<std::vector<Tile>> Grid;

	Options(x, y, Grid, first_try, N_Rows, N_Columns, Max_Mines);
	Display_Grid(Grid, false, true, N_Rows, N_Columns);
	first_try++;
	Options(x, y, Grid, first_try, N_Rows, N_Columns, Max_Mines);
	Grid = Create_Grid(N_Rows, N_Columns, Max_Mines,x, y);
	Grid_Analysis(Grid, N_Rows, N_Columns);
	GameOver = check_Coord(x, y, Grid, N_Rows, N_Columns);

	while (GameOver == false)
	{
		if (check_Win(Grid, N_Rows, N_Columns, Max_Mines) == true)
			goto win;
		Display_Grid(Grid, false, false, N_Rows, N_Columns);
		Options(x, y, Grid, first_try, N_Rows, N_Columns, Max_Mines);
		GameOver = check_Coord(x, y, Grid, N_Rows, N_Columns);
	}
	system("CLS");
	
	if (GameOver == true)
	{
		Display_Grid(Grid, true,false, N_Rows, N_Columns);
		std::cout << "Game Over , you lost :( " << std::endl;
		system("pause");
		return 0;
	}
win:
	Display_Grid(Grid, true,false, N_Rows, N_Columns);
	std::cout << "Game Over , You WOOOOOOOOOOON ;) " << std::endl;

	system("pause");

	return 0;
}
