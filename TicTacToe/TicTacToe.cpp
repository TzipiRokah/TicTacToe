// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define N 3

char board[N][N];
const char PLAYER = 'X';
const char COMPUTER = 'O';
int FreeSpaces = N * N;

void ResetBoard()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			board[i][j] = ' ';
		}
}

void PrintBoard()
{
	printf("  %c |  %c |  %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n----|----|----\n");
	printf("  %c |  %c |  %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n----|----|----\n");
	printf("  %c |  %c |  %c ", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}

int CheckFreeSpaces()
{
	FreeSpaces = N * N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (board[i][j] != ' ')
				FreeSpaces--;
	return FreeSpaces;
}

int* FindPair(char type)
{
	int j = 0;
	int i = 0;
	int ArrIndex[2] = { 9,9 };
	int* pointer = ArrIndex;
	//looking for in column
	while (j <= 2)
	{
		if (board[0][j] == type)
		{
			if (board[1][j] == type && board[2][j] == ' ')
				ArrIndex[0] = 2, ArrIndex[1] = j;
			else if (board[2][j] == type && board[1][j] == ' ')
				ArrIndex[0] = 1, ArrIndex[1] = j;
		}
		else if (board[1][j] == type && board[2][j] == type && board[0][j] == ' ')
			ArrIndex[0] = 0, ArrIndex[1] = j;
		if (ArrIndex[0] != 9)
			return pointer;
		else
			j++;
	}
	//looking for in rows 
	while (i <= 2)
	{
		if (board[i][0] == type)
		{
			if (board[i][1] == type && board[i][2] == ' ')
				ArrIndex[0] = i, ArrIndex[1] = 2;
			else if (board[i][2] == type && board[i][1] == ' ')
				ArrIndex[0] = i, ArrIndex[1] = 1;
		}
		else if (board[i][1] == type && board[i][2] == type && board[i][0] == ' ')
			ArrIndex[0] = i, ArrIndex[1] = 0;
		if (ArrIndex[0] != 9)
			return pointer;
		else
			i++;
	}
	//looking for in diagonals
	if (board[1][1] == type)
	{
		if (board[0][0] == type && board[2][2] == ' ')
			ArrIndex[0] = 2, ArrIndex[1] = 2;
		else if (board[2][2] == type && board[0][0] == ' ')
			ArrIndex[0] = 0, ArrIndex[1] = 0;
		else if (board[0][2] == type && board[2][0] == ' ')
			ArrIndex[0] = 2, ArrIndex[1] = 0;
		else if (board[2][0] == type && board[0][2] == ' ')
		{
			ArrIndex[0] = 0, ArrIndex[1] = 2;
			return pointer;
		}
	}
	else if (board[0][0] == PLAYER && board[2][2] == PLAYER || board[0][2] == PLAYER && board[2][0] == PLAYER)
	{
		if (board[1][2] == ' ')
			ArrIndex[0] = 1, ArrIndex[1] = 2;
		if (board[2][1] == ' ')
			ArrIndex[0] = 2, ArrIndex[1] = 1;
	}
	return pointer;
}

void Player()
{
	int x;
	int y;

	do
	{
		printf("YOU:\nEnter row:");
		scanf_s("%d", &x);
		x--;
		printf("Enter column:");
		scanf_s("%d", &y);
		y--;
		if (board[x][y] != ' ')
			printf("Invalid move!\n");
		else
		{
			board[x][y] = PLAYER;
			break;
		}
	} while (board[x][y] != ' ');
}

int Computer()
{
	int space = CheckFreeSpaces();
	if (space != 0)
	{
		if (board[1][1] == ' ')
		{
			board[1][1] = COMPUTER;
			return 0;
		}
		else
		{
			//lookin for free space after pair of computer
			int* PAIndex = FindPair(COMPUTER);
			if (PAIndex[0] != 9)
			{
				board[PAIndex[0]][PAIndex[1]] = COMPUTER;
				return 1;
			}
			else
				//looking for free space pair of player
			{
				PAIndex = FindPair(PLAYER);
				if (PAIndex[0] != 9)
				{
					board[PAIndex[0]][PAIndex[1]] = COMPUTER;
					return 0;
				}
				//if not found pair of player or computer looking for empty space
				else
					for (int i = 0; i < N; i++)
					{
						for (int j = 0; j < N; j++)
							if (board[i][j] == ' ')
							{
								board[i][j] = COMPUTER;
								break;
							}
						break;
					}
			}
		}
	}
	return 0;
}

int main()
{
	ResetBoard();
	PrintBoard();
	int space = CheckFreeSpaces();
	while (space != 0)
	{
		Player();
		PrintBoard();
		printf("COMPUTER:\n");
		if (Computer() == 1)
		{
			PrintBoard();
			printf("you lose,the computer won");
			break;
		}
		PrintBoard();
		space = CheckFreeSpaces();
		if (space == 0)
			printf("tiko");
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
