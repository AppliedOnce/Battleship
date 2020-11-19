#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>
#include "Battleship.h"


int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::vector<std::vector<char>> grid(4, std::vector<char>(4, 0));
	std::vector<int> playerPosition(2, 0);
	std::string password = "";
	std::string fileName = "passwordFile.txt";

	PrintGrid(grid, playerPosition);
	password = CreatePassword(fileName, grid, playerPosition);
	Login(fileName, grid, playerPosition);
}

void PrintGrid(std::vector<std::vector<char>>& grid, std::vector<int> playerPosition)
{
	int counter = 0;
	std::string gridTable = "ABCDEFGHIJKLMNOP";
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			grid[x][y] = gridTable[counter++];
			if (x == playerPosition[0] && y == playerPosition[1])
			{
				std::cout << "| " << "*" << " |";
			}
			else
			{
				std::cout << "| " << grid[x][y] << " |";
			}
			if (y % 4 == 3)
			{
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

std::string CreatePassword(std::string fileName, std::vector<std::vector<char>> grid, std::vector<int> playerPosition)
{
	char playerInput = ' ';
	bool invalidInput = false;
	bool confirmedPassword = false;
	std::string password = "A";

	std::cout << "Enter a password by moving on the grid (a,w,s,d) and press 'c' to confirm." << std::endl;

	do
	{
		do
		{
			playerInput = _getch();
			switch (ToLowerCase(playerInput))
			{
			case 'w':
				if (playerPosition[0] > 0)
				{
					invalidInput = false;
					playerPosition[0]--;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 's':
				if (playerPosition[0] < grid.size() - 1)
				{
					invalidInput = false;
					playerPosition[0]++;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'a':
				if (playerPosition[1] > 0)
				{
					invalidInput = false;
					playerPosition[1]--;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'd':
				if (playerPosition[1] < grid[0].size() - 1)
				{
					invalidInput = false;
					playerPosition[1]++;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'c':
				invalidInput = false;
				confirmedPassword = true;
				break;
			default:
				invalidInput = true;
				std::cout << "Invalid input, try again";
				break;
			}
		} while (invalidInput);

		if (!confirmedPassword)
		{
			PrintGrid(grid, playerPosition);
			password += grid[playerPosition[0]][playerPosition[1]];
		}
	} while (!confirmedPassword);

	std::cout << "Password sat to: " << password << std::endl;
	SavePasswordToFile(password, fileName);
	return password;
}

std::string EnterPassword(std::vector<std::vector<char>> grid, std::vector<int> playerPosition)
{
	char playerInput = ' ';
	bool invalidInput = false;
	bool confirmedPassword = false;
	std::string password = "A";

	std::cout << "Enter a password by moving on the grid (a,w,s,d) to login, press 'c' to confirm." << std::endl << std::endl;
	PrintGrid(grid, playerPosition);

	do
	{
		do
		{
			playerInput = _getch();
			switch (ToLowerCase(playerInput))
			{
			case 'w':
				if (playerPosition[0] > 0)
				{
					invalidInput = false;
					playerPosition[0]--;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 's':
				if (playerPosition[0] < grid.size() - 1)
				{
					invalidInput = false;
					playerPosition[0]++;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'a':
				if (playerPosition[1] > 0)
				{
					invalidInput = false;
					playerPosition[1]--;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'd':
				if (playerPosition[1] < grid[0].size() - 1)
				{
					invalidInput = false;
					playerPosition[1]++;
				}
				else
				{
					invalidInput = true;
				}
				break;
			case 'c':
				invalidInput = false;
				confirmedPassword = true;
				break;
			default:
				invalidInput = true;
				std::cout << "Invalid input, try again";
				break;
			}
		} while (invalidInput);

		if (!confirmedPassword)
		{
			PrintGrid(grid, playerPosition);
			password += grid[playerPosition[0]][playerPosition[1]];
		}
	} while (!confirmedPassword);

	std::cout << "You entered: " << password << std::endl;
	return password;
}

void SavePasswordToFile(std::string password, std::string fileName)
{
	std::ofstream outFile(fileName);

	outFile << password << std::endl;
	outFile.close();
}

std::string ReadPassword(std::string fileName)
{
	std::string readPassword = "";
	std::fstream readFile(fileName);

	readFile >> readPassword;

	readFile.close();
	return readPassword;
}

void Login(std::string passwordFile, std::vector<std::vector<char>> grid, std::vector<int> playerPosition)
{
	bool correct = false;
	do
	{
		if (EnterPassword(grid, playerPosition) == ReadPassword(passwordFile))
		{
			std::cout << "Correct password!" << std::endl;
			correct = true;
		}
		else
		{
			std::cout << "Inccorect password!" << std::endl;
			std::cout << "Try again." << std::endl;
			correct = false;
		}
	} while (!correct);
	std::cout << "\n\n";
	if (correct)
		MainMenu(passwordFile, grid, playerPosition);
}

void MainMenu(std::string passwordFile, std::vector<std::vector<char>> grid, std::vector<int> playerPosition)
{
	int playerInput = 0;
	bool invalidInput = false;
	bool running = true;

	do
	{
		PrintMenu();
		do
		{
			std::cin >> playerInput;
			switch (playerInput)
			{
			case 1:
				invalidInput = false;
				PrintGrid(grid, playerPosition);
				CreatePassword(passwordFile, grid, playerPosition);
				break;
			case 2:
				invalidInput = false;
				PlayBattleship();
				break;
			case 3:
				invalidInput = false;
				running = false;
				break;
			default:
				invalidInput = true;
				std::cout << "Invalid input, try again";
				break;
			}
		} while (invalidInput);
	} while (running);
}

void PrintMenu()
{
	std::cout << "1. Change the password" << std::endl;
	std::cout << "2. Play battleship" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "Select an option (1-3): ";
}

void PlayBattleship()
{
	std::cout << "\n\n";
	numberOfShots = 0;
	numberOfHits = 0;
	maxNumberOfShots = ships * 2;
	bool isPlaying = true;
	bool validChoice = false;
	char playAgain = ' ';

	do
	{
		MakeEmptyBoard();
		MakeBoard(ships);
		do
		{
			std::cout << "You have shot " << numberOfShots << " times, and hit " << numberOfHits << " out of " << ships << " ships.\n";
			std::cout << "You got " << maxNumberOfShots - numberOfShots << " shots left.\n\n";
			PrintPlayerBoard();
			Shoot();
		} while (!IsGameOver());

		PrintBoard();
		PrintPlayerBoard();

		std::cout << "Do you want to play again? (y/n)" << std::endl;
		std::cin >> playAgain;
		std::cin.ignore();
		std::cin.clear(256, '\n');
		do
		{
			switch (ToLowerCase(playAgain))
			{
			case 'y':
				validChoice = true;
				isPlaying = true;
				break;
			case 'n':
				validChoice = true;
				isPlaying = false;
				break;
			default:
				validChoice = false;
				break;
			}
		} while (!validChoice);
	} while (isPlaying);
}

void MakeEmptyBoard()
{
	for (int x = 0; x < M; x++)
	{
		for (int y = 0; y < N; y++)
		{
			board[x][y] = BLANK;
		}
	}
}

void MakeBoard(int numberOfShips)
{
	bool invalidSpot = false;
	int randomRow;
	int randomColumn;

	for (int i = 0; i < numberOfShips; i++)
	{
		do
		{
			randomRow = RandomRow(M);
			randomColumn = RandomColumn(N);
			if (board[randomRow][randomColumn] == BLANK)
			{
				board[randomRow][randomColumn] = SHIP;
				invalidSpot = false;
			}
			else
			{
				invalidSpot = true;
			}
		} while (invalidSpot);
	}
}

void PrintBoard()
{
	for (int i = 0; i < M; i++)
	{
		std::cout << "   " << M - i << "\t|";
		for (int j = 0; j < N; j++)
		{
			std::cout << board[i][j] << "|";
		}
		std::cout << std::endl;
	}
	WriteLetters();
}

void Shoot()
{
	int row = 0;
	int column = 0;
	char temp = ' ';

	std::cout << "Which cell do you want to shoot?" << std::endl;;
	std::cout << "Column: ";
	std::cin >> temp;
	std::cin.ignore();
	std::cin.clear(256, '\n');
	std::cout << "Row: ";
	std::cin >> row;
	std::cin.ignore();
	std::cin.clear(256, '\n');
	column = (LetterToNumber(ToUpperCase(temp)));
	
	if (board[M-row][column] == SHIP)
	{
		board[M-row][column] = HIT;
		numberOfHits++;
		numberOfShots++;
		std::cout << "That's a hit!" << std::endl;
	}
	else if (board[M-row][column] == MISS)
	{
		numberOfShots++;
		std::cout << "You already shot there!" << std::endl;
	}
	else
	{
		board[M - row][column] = MISS;
		numberOfShots++;
		std::cout << "That's a miss!" << std::endl;
	}
	std::cout << std::endl;
}

void PrintPlayerBoard()
{
	for (int i = 0; i < M; i++)
	{
		std::cout << "   " << M - i << "\t|";
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == SHIP)
				std::cout << BLANK << "|";
			else
				std::cout << board[i][j] << "|";
		}
		std::cout << std::endl;
	}
	WriteLetters();
}

void WriteLetters()
{
	std::cout << "\t";
	for (int i = 0; i < N * 2 + 1; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl << "\t|";
	for (int i = 0; i < N; i++)
	{
		std::cout << ALPHABET[i] << "|";
	}
	std::cout << "\n\n";
}

bool IsGameOver()
{
	if (numberOfShots >= maxNumberOfShots)
	{
		return true;
	}
	else if (numberOfHits == ships)
	{
		return true;
	}
	else
	{
		return false;
	}
}