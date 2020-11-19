#pragma once

const int M = 6, N = 6, ships = 10;
const char BLANK = ' ';
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';
const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char board[M][N];

int numberOfHits;
int numberOfShots;
int maxNumberOfShots;

std::string CreatePassword(std::string fileName, std::vector<std::vector<char>> grid, std::vector<int> playerPosition);
std::string ReadPassword(std::string fileName);
void PrintGrid(std::vector<std::vector<char>>& grid, std::vector<int> playerPosition);
void SavePasswordToFile(std::string password, std::string fileName);

void Login(std::string passwordFile, std::vector<std::vector<char>> grid, std::vector<int> playerPosition);
void MainMenu(std::string passwordFile, std::vector<std::vector<char>> grid, std::vector<int> playerPosition);
void PrintMenu();

void PlayBattleship();
void MakeEmptyBoard();
void WriteLetters();
void PrintBoard();
void PrintPlayerBoard();
void MakeBoard(int numberOfBoats);
void Shoot();
bool IsGameOver();

int LetterToNumber(char letter)
{
	return static_cast<int>(letter) - 65;
}

char ToLowerCase(char c)
{
	return tolower(c);
}

char ToUpperCase(char c)
{
	return toupper(c);
}

int RandomRow(int max)
{
	int randomRow = rand() % max;
	return randomRow;
}

int RandomColumn(int max)
{
	int randomColumn = rand() % max;
	return randomColumn;
}