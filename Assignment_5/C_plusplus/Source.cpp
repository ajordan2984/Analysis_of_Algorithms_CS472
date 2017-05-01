#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void read_in(int[][9],string);
void print_puzzle(int [][9]);
bool solve_puzzle(int[][9],int row,int col);
bool good_number(int[][9], int, int, int);
ofstream out;
int main()
{
	string p1 = "puzzle1.txt";
	string p2 = "puzzle2.txt";
	out.open("results.txt");
	int puzzle[9][9];
	
	read_in(puzzle,p1);
	if (solve_puzzle(puzzle, 0, 0))
		cout << "Finished puzzle 1." << endl;
	else
		cout << "Error.Bad Puzzle" << endl;
	out << "Solved:" << endl;
	print_puzzle(puzzle);

	out << "---------------------" << endl;
	read_in(puzzle, p2);
	if (solve_puzzle(puzzle, 0, 0))
		cout << "Finished puzzle 2." << endl;
	else
		cout << "Error.Bad Puzzle" << endl;
	out << "Solved:" << endl;
	print_puzzle(puzzle);
}
void read_in(int puzzle[][9],string myfile)
{
	ifstream in;
	in.open(myfile);

	//[row][col]
	for (int i = 0; i < 9; i++)	
		for (int j = 0; j < 9; j++)
			in >> puzzle[i][j];

	print_puzzle(puzzle);
}
void print_puzzle(int puzzle[][9])
{
	//[row][col]
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			out << puzzle[i][j];
			if ((j + 1) % 3 == 0)
				out << " ";
		}
		out << endl;
		if ((i + 1) % 3 == 0)
			out << endl;
	}
}
bool solve_puzzle(int puzzle[][9],int row,int col)
{
	if (col == 9)
	{
		col = 0;
		row++;
	}
	if (row == 9)
		return true;
	

	for (int i = 1; i < 10; i++)
	{
		if (puzzle[row][col] == 0)
		{
			if (good_number(puzzle, i, row, col))
			{
				puzzle[row][col] = i;
				if (solve_puzzle(puzzle, row, col+1))
					return true;
				puzzle[row][col] = 0;
			}
		}//end if valid position
		if (puzzle[row][col] != 0)
			return solve_puzzle(puzzle, row, col+1);

	}//end for
	// Back track here
	return false;

}
bool good_number(int puzzle[][9],int number,int row,int col)
{
	// check row
	for (int i = 0; i < 9; i++)
		if (number == puzzle[row][i])
			return false;
	// check col	
	for (int j = 0; j < 9; j++)
		if (number == puzzle[j][col])
			return false;
	// row and col are good, check small puzzle
	int Srow = row - row % 3;
	int Scol = col - col % 3;
	
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (puzzle[i + Srow][j + Scol] == number)
				return false;

	return true;
}