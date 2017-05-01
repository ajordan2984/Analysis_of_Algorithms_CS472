#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include<fstream>
#include<string>
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
void printM(int**, int);
double test(int,int);
int** createM(int);
void generate(int, int);
void fill(int**);
void findHULL(int**);
void deleteM(int**,int);
void deleteP(int**, int);

int **convexhull;
int **matrix_points;
int points_index;
int convexhull_index;

int main()
{
	points_index = 0;
	convexhull_index = 0;
	ofstream out;
	out.open("results.txt");
	if (!out)
	{
		cout << "Error->outfile not open." << endl;
		exit(1);
	}
	else{
		out << "Data Sets| Time for convex hull solving" << endl;
		out << "50        " << test(1000,50) << endl;
		cout << "Finished 50" << endl;
		out << "100       " << test(1000, 100) << endl;
		cout << "Finished 100" << endl;
		out << "250       " << test(1000,250) << endl;
		cout << "Finished 250." << endl;
		out << "500       " << test(1000,500) << endl;
		cout << "Finished 500." << endl;
		out << "750       " << test(1000, 750) << endl;
		cout << "Finished 750." << endl;
		out << "900       " << test(1000, 900) << endl;
		cout << "Finished 900." << endl;
		out << "1000      " << test(1000, 1000) << endl;
		cout << "Finished 1000." << endl;
		out << "2000      " << test(1000, 2000) << endl;
		cout << "Finished 2000." << endl;
		out << "2500      " << test(1000, 2500) << endl;
		cout << "Finished 2500." << endl;
		out << "4000      " << test(1000, 4000) << endl;
		cout << "Finished 4000." << endl;

	}
	cout << "Finished execution and writing file." << endl;
	return 0;
	
}
double test(int max,int datapoints)
{
	
	Timer tmr;
	// Create array to hold matrix points
	matrix_points = new int*[datapoints];
	// Create array to hold points in the hull
	convexhull = new int*[datapoints];
    
	// Create matrix for printing points
	int **A = createM(max);
	// Create matrix for printing hull points
	int **visited = createM(max);
	generate(max, datapoints);
	fill(A);
	//printM(A, max);
	// Reset timer
	tmr.reset();
	doSomething();
	// Find points that make the convex hull
	findHULL(visited);
	// Find endtime
	doSomeMoreWork();
	double t = tmr.elapsed();
	//cout << "Printing Hull." << endl;
	//printM(visited,max);
	deleteM(A, max);
	deleteM(visited, max);
	deleteM(matrix_points, datapoints);
	points_index = 0;
	convexhull_index = 0;
	return t;
}
void printM(int **matrix, int max)
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
int** createM(int max)
{
	int **temp = new int*[max];
	for (int i = 0; i < max; i++)
	{
		temp[i] = new int[max];
		for (int j = 0; j < max; j++)
			temp[i][j] = 0;
	}
	return temp;
}
void generate(int max,int dataset)
{
	ofstream outfile;
	outfile.open("points.txt");
	if (!outfile)
	{
		cout << "Error:No File opened" << endl;
		exit(1);
	}
	else
		for (int i = 0; i<dataset;i++)
			outfile << rand() % max << " " << rand() % max << endl;
	outfile.close();
}
void fill(int **A)
{
	//[row][column]
	string input;
	ifstream infile;
	int row, col;
	infile.open("points.txt");
	if (!infile)
	{
		cout << "Error:No File opened." << endl;
		exit(1);
	}
	else
	{
		while (infile >> row >> col)
		{
			A[row][col] = 1;
			matrix_points[points_index] = new int[2]{row, col};
			points_index++;
		}
	}
}//end void split
void findHULL(int **visited)
{
	// Data in order of [x][y]
	int maxpoints = points_index;
	int *A, *B, *C;
	int ax, ay, bx, by, cx, cy, answer;
	bool pointsleft = false;
	bool pointsright = false;

	for (int i = 0; i < maxpoints; i++)
	{
		A = matrix_points[i];
		ax = A[0];
		ay = A[1];
		
		for (int k = 0; k < maxpoints; k++)
		{
			B = matrix_points[k];
			bx = B[0];
			by = B[1];
			
			for (int j = 0; j < maxpoints; j++)
				{
					C = matrix_points[j];
					cx = C[0];
					cy = C[1];

					answer = ((ax - cx)*(by - cy)) - ((ay - cy)*(bx - cx));
					// points to the right,left,and on the line
					if (answer > 0)
						pointsright = true;
					if (answer < 0)
						pointsleft = true;

				}//end J for
				
				// There exist only points on the left of the line
				// but not on the right of the line
				if (pointsleft && !pointsright)
				{
					visited[bx][by] = 1;
					// Prevent shallow copy
					convexhull[i] = new int[2]{bx, by};
					convexhull_index++;

				}	
				// There exist only points on the right of the line
				// but not on the left of the line
				if (!pointsleft && pointsright)
				{
					visited[bx][by] = 1;
					// Prevent shallow copy
					convexhull[i] = new int[2]{bx, by};
					convexhull_index++;
				}
				// Reset values for detemining if hull point
				pointsright = false;
				pointsleft = false;
		}//end K for
	}// end I for
}
void deleteM(int** data, int S)
{
	for (int i = 0; i < S; i++)
		delete[] data[i];
	delete[] data;
	data = nullptr;
}
