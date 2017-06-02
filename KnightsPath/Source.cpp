// board size -> optimal moves
// 4 ->  5 moves
// 5 -> 10 moves
// 7 -> 24 moves
// 8 -> 35 moves

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// Linklist of linesegments
struct LineSegment{
	int x1;
	int y1;
	int x2;
	int y2;
	LineSegment *ptr;
};

int** create(int board_size);
void set(int** board, int boardsize);
void print_points();
void solve(int **board, int boardsize, int row, int col);
bool good_route(int **board, int boardsize, int row, int col, int direction);
LineSegment* mark(int **board, int tick, int row, int col, int direction);
bool non_intersecting(int X3, int Y3, int X4, int Y4);
LineSegment* add_linesegment(int x1, int y1, int x2, int y2);

// Globals
int HighestMoves;
int Moves;
int new_row;
int new_col;
// Head node
LineSegment *root;
LineSegment *nextnode;
ofstream outfile;
int main()
{
	HighestMoves = 0;
	Moves = 0;
	new_row = 0;
	new_col = 0;
	int boardsize = 5;
	root = NULL;
	outfile.open("points.txt");
	

	
	int** board = create(boardsize);
	set(board, boardsize);

	for (int i = 0; i < boardsize; i++)
	{
		for (int j = 0; j < boardsize; j++)
		{
			cout << "Highest move from: " << i << "," << j << " - " << endl;
			board[i][j] = 1;
			solve(board, boardsize, i, j);
			root = NULL;
			set(board, boardsize);
		}
	}
	
}
int** create(int board_size)
{
	int **temp = new int*[board_size];
	//[row][col]
	for (int i = 0; i < board_size; i++)
		temp[i] = new int[board_size];
	return temp;
}
void set(int** board,int boardsize)
{
	for (int i = 0; i < boardsize; i++)
		for (int j = 0; j < boardsize; j++)
			board[i][j] = 0;
}
void print_points()
{
	if (root == NULL)
		return;
	else{
		LineSegment *temp = root;
		outfile << "New Set of Points:" << endl;
		while (temp != NULL)
		{
			outfile << "( " << temp->x1 << " , " << temp->y1 << " )" << " ( " << temp->x2 << " , " << temp->y2 << " )" << endl;
			temp = temp->ptr;
		}
		outfile << "__________________" << endl;
	}
}
void solve(int **board,int boardsize, int row, int col)
{
	LineSegment *node;
	LineSegment *previous;
	for (int i = 1; i < 9; i++)
	{
		if (good_route(board,boardsize,row, col,i))
			{
				node = mark(board, 1, row, col, i);
				if (root == NULL)
				{
					root = node;
					nextnode = root;
					previous = root;
				}
				else{
					previous = nextnode;
					nextnode->ptr = node;
					nextnode = nextnode->ptr;
				}

				Moves++;
					solve(board, boardsize, new_row, new_col);
				// chop off old node
					if (previous == nextnode)
					{
						root = NULL;
						delete(nextnode);
						nextnode = mark(board, 0, row, col, i);;
						previous = NULL;
					}
					else{
						delete(nextnode);
						nextnode = previous;
						nextnode->ptr = mark(board, 0, row, col, i);
					}
				Moves--;
			}
	}//end for
	// Backtrack here
	if (Moves > HighestMoves)
	{
		HighestMoves = Moves;
		cout << HighestMoves << endl;
	}
}
bool good_route(int **board, int boardsize, int row, int col,int direction)
{
	// up 2/left 1
	switch (direction)
	{

	case 1:
		if ((row > 1 && col > 0)
			&& (board[row - 2][col - 1] != 1)
			&& non_intersecting(col, row, col - 1, row - 2))
		{
			new_col = col - 1;
			new_row = row - 2;
			return true;
		}
		break;
		// up 2/right 1
	case 2:
		if ((row > 1 && col < boardsize - 1)
			&& (board[row - 2][col + 1] != 1)
			&& non_intersecting(col, row, col + 1, row - 2))
		{
			new_col = col + 1;
			new_row = row - 2;
			return true;
		}
		break;
		// 2 right/1 up
	case 3:

		if ((row > 0 && col < boardsize - 2)
			&& (board[row - 1][col + 2] != 1)
			&& (non_intersecting(col, row, col + 2, row - 1)))
		{
			new_col = col + 2;
			new_row = row - 1;
			return true;
		}
		break;
		// 2 right/1 down
	case 4:
		if ((row < boardsize - 1 && col < boardsize - 2)
			&& (board[row + 1][col + 2] != 1)
			&& non_intersecting(col, row, col + 2, row + 1))
		{
			new_col = col + 2;
			new_row = row + 1;
			return true;
		}
		break;
		// down 2/over right 1
	case 5:
		if ((row < boardsize - 2 && col < boardsize - 1)
			&& (board[row + 2][col + 1] != 1)
			&& non_intersecting(col, row, col + 1, row + 2))
		{
			new_col = col + 1;
			new_row = row + 2;
			return true;
		}
		break;
	case 6:
		if ((row < boardsize - 2 && col > 0)
			&& (board[row + 2][col - 1] != 1)
			&& non_intersecting(col, row, col - 1, row + 2))
		{
			new_col = col - 1;
			new_row = row + 2;
			return true;
		}
		break;
		// 2 left/ down 1
	case 7:
		if ((row < boardsize - 1 && col > 1)
			&& (board[row + 1][col - 2] != 1)
			&& non_intersecting(col, row, col - 2, row + 1))
		{
			new_col = col - 2;
			new_row = row + 1;
			return true;
		}
		break;
		// 2 left/ up 1
	case 8:
		if ((row > 0 && col > 1)
			&& (board[row - 1][col - 2] != 1)
			&& non_intersecting(col, row, col - 2, row - 1))
		{
			new_col = col - 2;
			new_row = row - 1;
			return true;
		}
	}//end switch;
			return false;
}//end goodpath
LineSegment* mark(int **board, int tick, int row, int col, int direction)
{
	int x2;
	int y2;
	switch (direction)
	{
	case 1:
		board[row - 2][col - 1] = tick; x2 = row - 2; y2 = col - 1; break;
	case 2:
		board[row - 2][col + 1] = tick; x2 = row - 2; y2 = col + 1; break;
	case 3:
		board[row - 1][col + 2] = tick; x2 = row - 1; y2 = col + 2; break;
	case 4:
		board[row + 1][col + 2] = tick; x2 = row + 1; y2 = col + 2; break;
	case 5:
		board[row + 2][col + 1] = tick; x2 = row + 2; y2 = col + 1; break;
	case 6:
		board[row + 2][col - 1] = tick; x2 = row + 2; y2 = col - 1; break;
	case 7:
		board[row + 1][col - 2] = tick; x2 = row + 1; y2 = col - 2; break;
	case 8:
		board[row - 1][col - 2] = tick; x2 = row - 1; y2 = col - 2; break;
	}

	if (tick == 1)
		return add_linesegment(col, row, y2, x2);
	else
		return NULL;
}
bool non_intersecting(int X3, int Y3, int X4, int Y4)
{
	if (root == NULL)
		return true;
	
	LineSegment *temp = root;
	float x1;
	float y1;
	float x2;
	float y2;
	float x3 = static_cast<float>(X3);
	float y3 = static_cast<float>(Y3);
	float x4 = static_cast<float>(X4);
	float y4 = static_cast<float>(Y4);
	float x;
	float y;
	float d;
	float highX, highY;
	float lowX, lowY;
	float ThighX, ThighY;
	float TlowX, TlowY;
	bool check = true;
	bool canidate = true;
	
	if (x3 > x4)
	{
		ThighX = x3;
		TlowX = x4;
	}
	else
	{
		ThighX = x4;
		TlowX = x3;
	}
	if (y3 > y4)
	{
		ThighY = y3;
		TlowY = y4;
	}
	else
	{
		ThighY = y4;
		TlowY = y3;
	}

	while (temp != NULL)
	{
		x1 = static_cast<float>(temp->x1);
		y1 = static_cast<float>(temp->y1);
		x2 = static_cast<float>(temp->x2);
		y2 = static_cast<float>(temp->y2);
		
		if ( ((x3 == x1 && y3 == y1) || (x3 == x2 && y3 == y2))
			|| ((x4 == x1 && y4 == y1) || (x4 == x2 && y4 == y2))
		   )
			check = false;

		if (check){
			d = (((x1 - x2)*(y3 - y4)) - ((y1 - y2)*(x3 - x4)));
			if (d != 0){
				x = ((((x1*y2) - (y1*x2))*(x3 - x4)) - ((x1 - x2)*((x3*y4) - (y3*x4)))) / d;
				y = ((((x1*y2) - (y1*x2))*(y3 - y4)) - ((y1 - y2)*((x3*y4) - (y3*x4)))) / d;

				if (x1 > x2)
				{
					highX = x1;
					lowX = x2;
				}
				else
				{
					highX = x2;
					lowX = x1;
				}
				if (y1 > y2)
				{
					highY = y1;
					lowY = y2;
				}
				else
				{
					highY = y2;
					lowY = y1;
				}
				if (
					((lowX < x && highX > x) && (lowY < y && highY > y))
					&& ((TlowX < x && ThighX > x) && (TlowY < y && ThighY > y))
					)
					return false;
			}// d != 0
		}//check
		
		check = true;
		temp = temp->ptr;
	}
	return true;
}
LineSegment* add_linesegment(int x1, int y1, int x2, int y2)
{
	LineSegment *temp = new LineSegment;
	temp->x1 = x1;
	temp->x2 = x2;
	temp->y1 = y1;
	temp->y2 = y2;
	temp->ptr = NULL;
	return temp;
}
