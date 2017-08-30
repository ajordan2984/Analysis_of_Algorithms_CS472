/*
Clockwise Number Spiral:
- Spiral is NxN dimensions
- Outer Loop runs ((NX2)-1) times
- Inner Loop decreases with each pass
- Direction for the spiral is : Right-Down-Left-Up
- Lower Row bounds are moved up after Right completes
- Lower Col bounds are moved up after Up completes
- High Row bounds are moved up after Left completes
- High Col bounds are moved up after Down completes
*/
#include <iostream>
#include <fstream>
using namespace std;
int** create(int);
void fill(int**,int);
void print(int**, int);
ofstream out;

int main()
{
	out.open("results.txt");
	fill(create(4), 4);
	fill(create(5), 5);
}//end main
int** create(int board_size)
{
	int **temp = new int*[board_size];
	//[row][col]
	for (int i = 0; i < board_size; i++)
		temp[i] = new int[board_size];
	return temp;
}
void fill(int **board, int max)
{
	int row = 0;
	int col = 0;

	int counter = 1;
	int Row_Low_bound = -1;
	int Row_High_bound = 0;
	int Col_Low_bound = -1;
	int Col_High_bound = 0;
	char direction = 'R';

	int passes = (max * 2) - 1;
	Row_High_bound = max;
	Col_High_bound = max;
	
	for (int i = 0; i < passes; i++)
	{
		switch (direction)
		{
		case 'R':
			for (int j = col; j < Col_High_bound; j++)
			{
				col = j;
				board[row][col] = counter;
				counter++;
			}
			Row_Low_bound++;
			row++;
			direction = 'D';
			break;
		case 'D':
			for (int j = row; j < Row_High_bound; j++)
			{
				row = j;
				board[row][col] = counter;
				counter++;
			}
			Col_High_bound--;
			col--;
			direction = 'L';
			break;

		case 'L':
			for (int j = col; j > Col_Low_bound; j--)
			{
				col = j;
				board[row][col] = counter;
				counter++;
			}
			Row_High_bound--;
			row--;
			direction = 'U';
			break;

		case 'U':
			for (int j = row; j > Row_Low_bound; j--)
			{
				row = j;
				board[row][col] = counter;
				counter++;
			}
			Col_Low_bound++;
			col++;
			direction = 'R';
			break;
		}// end switch
	}// end for loop
	print(board, max);
	out << endl;
}//end fill
void print(int** board,int board_size)
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] < 10)
				out << " " << board[i][j] << " ";
			else
				out << board[i][j] << " ";
		}
		out << endl;
	}
}//end print