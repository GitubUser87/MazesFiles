/*
	GPF Week 6 - Maze Start Code
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include "Framework.h"
#include <string>
using namespace std;

// Screen dimensions
int gScreenWidth{ 800 };
int gScreenHeight{ 600 };

// Delay to slow things down
int gTimeDelayMS{ 100 };

// Maze size as constants
constexpr int kMazeColumnsX{ 20 };
constexpr int kMazeRowsY{ 20 };

/*
	2 Dimensional Arrays
	You can think of these as being an array of arrays
	
	The maze has kMazeRowsY columns across (20 by default) represented by an array
	We then have kMazeColumnsX (20) of these arrays, one for each row
	
	Columns and rows can be confusing so we tend to prefer working with x and y
	x is the horizontal axis (columns) across and y is the vertical axis (rows) down.

	Each single item is called a cell. 
	
	E.g. to output the value of the cell at 16 X (column 16) and 1 Y (row 1) we would write:
	cout << map[1][16] << endl; // outputs G
*/

//char** map;
char map[kMazeColumnsX][kMazeRowsY];

//char map[kMazeColumnsX][kMazeRowsY] = {
//	// 20 columns (x axis) by 20 rows (y axis)
//	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
//	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
//	{ 'W', '.', '.', '.', 'F', 'W', 'I', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'G', '.', '.', 'W' },	//Y1
//	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W' },	//Y2
//	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', '.', 'W', 'W', 'I', 'W', 'F', '.', '.', '.', 'W' },	//Y3
//	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W' },	//Y4
//	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y5
//	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'F', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'I', 'W' },	//Y6
//	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y7
//	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', 'F', 'W', '.', '.', '.', 'W', '.', '.', '.', 'I', 'W' },	//Y8
//	{ 'W', '.', 'W', 'I', 'W', 'F', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W', 'W' },	//Y9
//	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W' },	//Y10
//	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'F', '.', '.', 'W' },	//Y11
//	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', '.', '.', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W' },	//Y12
//	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y13
//	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', 'I', 'W', '.', 'W', 'W', 'W', 'W' },	//Y14
//	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', 'W', '.', '.', '.', 'W', 'W' },	//Y15
//	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'I', 'W', 'W', '.', 'W', '.', '.', '.', 'W', 'I', '.', 'W' },	//Y16
//	{ 'W', '.', 'W', '.', 'W', 'I', 'W', 'W', 'W', 'W', '.', '.', 'W', 'W', 'W', '.', 'W', 'W', '.', 'W' },	//Y17
//	{ 'W', '.', '.', '.', '.', '.', '.', '.', 'F', 'W', 'F', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
//	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
//};

void DrawMaze()
{
	int widthofcell{ gScreenWidth / kMazeColumnsX };
	int heightofcell{ gScreenHeight / kMazeRowsY };

	int screenY{ 0 };
	for (size_t cellY = 0; cellY < kMazeRowsY; cellY++)
	{
		int screenX{ 0 };
		for (size_t cellX = 0; cellX < kMazeColumnsX; cellX++)
		{
			switch (map[cellY][cellX])
			{
			case '.':
				ChangeColour(255, 255, 255);
				break;
			case 'G':
				ChangeColour(255, 0, 0);
				break;
			case 'P': 
				ChangeColour(0, 0, 255);
				break;
			case 'F': //FirePit
				ChangeColour(255, 100, 0);
				break;
			case 'I': //IcePit
				ChangeColour(135, 206, 235);
				break;
			case 'E': //Enemy
				ChangeColour(128, 0, 128);
				break;
			default:
				ChangeColour(0, 0, 0);
				break;
			}
			DrawRectangle(screenX, screenY, widthofcell, heightofcell);

			screenX = screenX + widthofcell;
		}
		screenY = screenY + heightofcell;
	}
}
bool CanMoveThere(int x, int y)
{
	return map[y][x] != 'W';
}
bool EnemyCanMoveThere(int x, int y)
{
	return map[y][x] != 'W' && map[y][x] != 'F' && map[y][x] != 'I' && map[y][x] != 'G';
}


void SaveToFile(int playerX, int playerY) // Save
{
	ofstream output;
	output.open("Data/Save.txt", ios::out);
	if (output.fail())
	{
		cerr << "Failed to open file." << endl;
		return;
	}
	output << playerX << " " << playerY << endl;
	output.close();

}

void LoadFromFile(int& playerX, int& playerY) // Load
{
	ifstream input;
	input.open("Data/Save.txt", ios::in);
	if (input.fail())
	{
		cerr << "Failed to load file." << endl;
		return;
	}
	input >> playerX >> playerY;
	input.close();
}


void SaveMaze(string filename)
{
	ofstream output;
	output.open(filename, ios::out);
	if (output.fail())
	{
		cerr << "Failed to save maze." << endl;
		return;
	}
	for (size_t row = 0; row < kMazeRowsY; row++)
	{
		for (size_t column = 0; column < kMazeColumnsX; column++) 
		{
			output << map[row][column];// << " ";
		}
		output << endl;
	}
	output.close();
}

void LoadMaze(string filename)
{
	ifstream input;
	input.open(filename, ios::in);
	if (input.fail())
	{
		cerr << "Failed to load maze." << endl;
		return;
	}
	for (size_t row = 0; row < kMazeRowsY; row++)
	{
		//for (size_t column = 0; column < kMazeColumnsX; column++)
		//{
		//	input >> map[row][column];
		//}

		input.getline(map[row], kMazeColumnsX + 1);
		//cout << map[row] << endl;
	}
	input.close();
}

enum class Direction {
	dNorth,
	dSouth,
	dEast,
	dWest
};


void RelocateElement(char letter)
{
	// Declares the x and y values
	int x{ 0 };
	int y{ 0 };
	
	do
	{
		x = 1 + rand() % (kMazeColumnsX - 2);
		y =  1 + rand() % (kMazeRowsY - 2);
		// Gives us new values for x and y
	} while (map[y][x] != '.');
	map[y][x] = letter;
}



int main()
{
	srand(time(NULL));
	LoadMaze("Maze1.txt");
	StartClock();
	RelocateElement('P');
	int playerX{ 0 };
	int playerY{ 0 };
	int enemyX{ 0 };
	int enemyY{ 0 };
	int level = 1;
	int score = 0;
	bool playerFound = false;
	bool enemyFound = false;
	for (size_t x = 0; x < kMazeColumnsX && !playerFound; x++)
	{
		for (size_t y = 0; y < kMazeRowsY; y++)
		{
			if (map[y][x] == 'P')
			{
				playerX = x;
				playerY = y;
				playerFound = true;
				break;
			}
		}
	}
	for (size_t x = 0; x < kMazeColumnsX && !enemyFound; x++)
	{
		for (size_t y = 0; y < kMazeRowsY; y++)
		{
			if (map[y][x] == 'E')
			{
				enemyX = x;
				enemyY = y;
				enemyFound = true;
				break;
			}
		}
	}
	int victories{ 0 };
	float TotalTime = 0.0f; //TotalTime will be how much time it took for the player to reach the goal.
	float TimeLimit = 300.0f;
	std::cout << "You have 5 minutes to reach the goals." << endl;
	std::cout << "You should try and take the shortest route for the least amount of steps." << endl;
	std::cout << "The lower the score the better." << endl;
	std::cout << "Reach the goal, watch out for traps, have fun." << endl;
	while (UpdateFramework())
	{
		EKeyPressed key = GetLastKeyPressed();
		map[playerY][playerX] = '.';
		switch (key)
		{
		case EKeyPressed::eNone:
			break;
		case EKeyPressed::eLeft:
			if (CanMoveThere(playerX - 1, playerY))
			{
				playerX--;
				score++;
			}
			break;
		case EKeyPressed::eRight:
			if (CanMoveThere(playerX + 1, playerY))
			{
				playerX++;
				score++;
			}
			break;
		case EKeyPressed::eUp:
			if (CanMoveThere(playerX, playerY - 1))
			{
				playerY--;
				score++;
			}
			break;
		case EKeyPressed::eDown:
			if (CanMoveThere(playerX, playerY + 1))
			{
				playerY++;
				score++;
			}
			break;
		case EKeyPressed::eSave:
			
		{
			SaveToFile(playerX, playerY);
			string filename;
			cout << "Please create a filename." << endl;
			cin >> filename;
			SaveMaze(filename);
		}
			break;
		case EKeyPressed::eLoad:
			
		{
			LoadFromFile(playerX, playerY);
			string filename;
			cout << "Please select a filename." << endl;
			cin >> filename;
			LoadMaze(filename);
			enemyFound = false;
			for (size_t x = 0; x < kMazeColumnsX && !enemyFound; x++)
			{
				for (size_t y = 0; y < kMazeRowsY; y++)
				{
					if (map[y][x] == 'E')
					{
						enemyX = x;
						enemyY = y;
						enemyFound = true;
						break;
					}
				}
			}
		}
			break;
		default:
			break;
		}
		if (map[playerY][playerX] == 'F')
		{
			system("cls");
			std::cout << "You lose!" << endl;
			std::cout << "You fell into the fire pit." << endl;
			break;
		}
		if (map[playerY][playerX] == 'I')
		{
			system("cls");
			std::cout << "You lose!" << endl;
			std::cout << "You slipped on the ice." << endl;
			break;
		}
		if (map[playerY][playerX] == 'E')
		{
			system("cls");
			std::cout << "You lose!" << endl;
			std::cout << "You were slain by the enemy." << endl;
			break;
		}
		if (GetElapsedTime() > TimeLimit)
		{
			system("cls");
			std::cout << "Time's up." << endl;
			break;
		}
		if (map[playerY][playerX] == 'G')
		{
			float seconds = GetElapsedTime();
			victories++;
			TotalTime += seconds;
			level++;
			system("cls");
			std::cout << "You have found the goal, well done!" << endl;
			std::cout << "You found the goal in " << seconds << " seconds this time." << endl;
			std::cout << "Time you have left: " << TimeLimit - TotalTime << endl;
			std::cout << "Your current score is: " << score << endl;
			string filename = "Maze" + to_string(level) + ".txt";
			LoadMaze(filename);
			if (level > 3)
			{
				break;
			}
			//'RelocateElement('G');
			StartClock();
		}

		map[playerY][playerX] = 'P';

		map[enemyY][enemyX] = '.';
		int direction = rand() % 4;
		switch (direction)
		{
		case 0:
			if (EnemyCanMoveThere(enemyX, enemyY - 1))
			{
				enemyY--;
			}
			break;
		case 1:
			if (EnemyCanMoveThere(enemyX, enemyY + 1))
			{
				enemyY++;
			}
			break;
		case 2:
			if (EnemyCanMoveThere(enemyX - 1, enemyY))
			{
				enemyX--;
			}
			break;
		case 3:
			if (EnemyCanMoveThere(enemyX + 1, enemyY))
			{
				enemyX++;
			}
			break;
		default:
			break;
		}
		if (map[enemyY][enemyX] == 'P')
		{
			system("cls");
			std::cout << "You lose!" << endl;
			std::cout << "You were slain by the enemy." << endl;
			break;
		}
		map[enemyY][enemyX] = 'E';

		DrawMaze();
		
		
	}
	float seconds = GetElapsedTime();
	TotalTime += seconds;
	system("cls");
	std::cout << "You amassed a total of " << victories << " victories." << endl;
	std::cout << "Total time played: " << TotalTime << endl;
	std::cout << "Your final score is: " << score << endl;
	std::cout << "Time you had left: " << TimeLimit - TotalTime << endl;
	std::cout << "Thanks for playing!" << endl;
	return 0;
}
