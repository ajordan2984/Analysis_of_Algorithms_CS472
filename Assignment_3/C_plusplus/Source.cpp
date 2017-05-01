#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include<fstream>
using namespace std;
class Timer{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}
private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1>> second_;
	std::chrono::time_point<clock_> beg_;
};
void mySleep(unsigned long timeInSeconds)
{
	std::chrono::milliseconds timeInMS(timeInSeconds);
	std::this_thread::sleep_for(timeInMS);
}
void doSomething() { mySleep(3); };
void doSomeMoreWork() { mySleep(4); };
//[row][col]
void printM(char**, int);
double test(int);
char** createM(int);
int pow2(int data);
int scan(char**,int*,int);
void mark(char**,int*,int,int);
void split(char**,int *,int max);
void deleteM(char**,int);
void deleteB(int*);
char **A;
char cell = 'A';

int main()
{
	ofstream out;
	out.open("results.txt");
	if (!out)
	{
		cout << "Error->outfile not open." << endl;
		exit(1);
	}
	else{
		out << "Data Sets| Time for puzzle solving" << endl;
		out << "16:     " << test(16)  << endl;
		out << "32:     " << test(32)  << endl;
		out << "128     " << test(128) << endl;
		out << "256     " << test(256) << endl;
		out << "512     " << test(512) << endl;
		out << "1,000   " << test(1000) << endl;
		out << "5,000   " << test(5000) << endl;
		out << "10,000  " << test(10000) << endl;
	}
	cout << "Finished execution and writing file." << endl;
	
	return 0;
}
double test(int input)
{
	int resized = pow2(input);
	Timer tmr;
	// 1st matrix
	A = createM(resized);
	int *corners = new int[2]{0, 0};
	// Reset timer
	tmr.reset();
	doSomething();
	// Start MM
	split(A, corners, resized);
	// find endtime
	doSomeMoreWork();
	double t = tmr.elapsed();

	//printM(A, resized);
	// clean up
	deleteB(corners);
	deleteM(A, resized);
	return t;
}
void printM(char **matrix, int max)
{
	//[row][col]
	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
		{
		cout << matrix[i][j] << " ";
		if ((j + 1) == max)
			cout << endl;
		}
}
char** createM(int msize)
{
	char **temp = new char*[msize];
	for (int i = 0; i < msize; i++)
	{
		temp[i] = new char[msize];
		for (int j = 0; j < msize; j++)
			temp[i][j] = '-';
	}
	temp[rand() % msize][rand() % msize] = 'x';
	return temp;
}
int pow2(int data)
{
	int i = 1;
	while (i < data)
		i = i*2;
	return i;
}
int scan(char **A,int *corners,int max)
{
	int start_row = corners[0];
	int start_col = corners[1];
	int tile;
	int row;
	int col;
	int half = max / 2;
	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
			if (A[i+start_row][j+start_col] != '-')
			{
				row = i;
				col = j;
				break;
			}
	// Tile in A11
	if (row < half && col < half)
		return 1;
	// Tile in A12
	if (row < half && col>= half)
		return 2;
	// Tile in A21
	if (row >= half && col < half)
		return 3;
	// Tile in A22
	if (row >= half && col >= half)
		return 4;

}
void mark(char **A,int *corners,int tile, int max)
{
	//[row][col]
	int half = max / 2;
	int row = corners[0];
	int col = corners[1];
	//A11
	if (tile == 1)
	{
		A[row+half-1][col+half] = cell;
		A[row+half][col+half] = cell;
		A[row+half][col+half-1] = cell;
	}
	//A12
	if (tile == 2)
	{
		A[row+half - 1][col+half-1] = cell;
		A[row+half][col+half] = cell;
		A[row+half][col+half - 1] = cell;
	}
	//
	if (tile == 3)
	{
		A[row+half - 1][col+half] = cell;
		A[row+half][col+half] = cell;
		A[row+half-1][col+half - 1] = cell;
	}
	if (tile == 4)
	{
		A[row+half - 1][col+half] = cell;
		A[row+half-1][col+half-1] = cell;
		A[row+half][col+half - 1] = cell;
	}
	cell++;
	if (cell >= 'z')
		cell = 'A';
}
void split(char **A,int *corners,int max)
{
			//[row][column]
	        int half = max / 2;
			int row = corners[0];
			int col = corners[1];
			
			int tile = scan(A,corners,max);
			mark(A,corners,tile,max);
			if (half > 1 )
			{
				int *A11 = new int[2]{row, col};
				int *A12 = new int[2]{row, col + half};
				int *A21 = new int[2]{row + half, col};
				int *A22 = new int[2]{row + half, col + half};
				split(A, A11, half);
				split(A, A12, half);
				split(A, A21, half);
				split(A, A22, half);
				// Clean up
				deleteB(A11);
				deleteB(A12);
				deleteB(A21);
				deleteB(A22);
			}
}//end void split
void deleteM(char** data, int S)
{
	for (int i = 0; i < S; i++)
		delete[] data[i];
	delete[] data;
	data = nullptr;
}
void deleteB(int*data)
{
	delete[] data;
	data = nullptr;
}