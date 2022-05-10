// FILE NAME: tour.cpp
// DATE MODIFIED: 05/09/22
// PURPOSE: C++ program to solve for Knight's tour problem
// DESCRIPTION: This program outputs a solution to a knight's tour using Warnsdorf's algorithm. Edits made to this file for the purpose of outputting the alphanumeric chess notation of a knight's 63 moves on a standard 8x8 board are indicated by the comments in the print function.
// ALGORITHM: Warnsdorff's Algorithm
// COMPILATION INSTRUCTIONS: g++ -o tour tour.cpp
// SYNOPSIS: ./tour
// INPUT: n/a
// BUGS: n/a
// EXTRAS: n/a
// ATTRIBUTION: a) Article Containing Source Code: https://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/
//              b) Author Profile: https://auth.geeksforgeeks.org/user/Uddalak%20Bhaduri/articles/

#include <bits/stdc++.h>
#include <string>
#define N 8
#define SINGLE_DIGITS 9
#define AREA 64
#define ADD_COLUMN 31

using namespace std;

// Move pattern on basis of the change of
// x coordinates and y coordinates respectively
static int cx[N] = {1,1,2,2,-1,-1,-2,-2};
static int cy[N] = {2,-2,1,-1,2,-2,1,-1};

// function restricts the knight to remain within
// the 8x8 chessboard
bool limits(int x, int y)
{
	return ((x >= 0 && y >= 0) && (x < N && y < N));
}

/* Checks whether a square is valid and empty or not */
bool isempty(int a[], int x, int y)
{
	return (limits(x, y)) && (a[y*N+x] < 0);
}

/* Returns the number of empty squares adjacent
to (x, y) */
int getDegree(int a[], int x, int y)
{
	int count = 0;
	for (int i = 0; i < N; ++i)
		if (isempty(a, (x + cx[i]), (y + cy[i])))
			count++;

	return count;
}

// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick
// next point.
bool nextMove(int a[], int *x, int *y)
{
	int min_deg_idx = -1, c, min_deg = (N+1), nx, ny;

	// Try all N adjacent of (*x, *y) starting
	// from a random adjacent. Find the adjacent
	// with minimum degree.
	int start = rand()%N;
	for (int count = 0; count < N; ++count)
	{
		int i = (start + count)%N;
		nx = *x + cx[i];
		ny = *y + cy[i];
		if ((isempty(a, nx, ny)) &&
		(c = getDegree(a, nx, ny)) < min_deg)
		{
			min_deg_idx = i;
			min_deg = c;
		}
	}

	// IF we could not find a next cell
	if (min_deg_idx == -1)
		return false;

	// Store coordinates of next point
	nx = *x + cx[min_deg_idx];
	ny = *y + cy[min_deg_idx];

	// Mark next move
	a[ny*N + nx] = a[(*y)*N + (*x)]+1;

	// Update next point
	*x = nx;
	*y = ny;

	return true;
}

/* Displays the chessboard with all the legal knight's moves: 
The following code has been modified by deleting code yielding the original output (an 8x8 matrix with moves 1 through 64) and building upon the print function to output the alphanumeric notation of the knight's moves in the format of a chess score sheet 
*/
void print(int a[])
{

	const char notation[SINGLE_DIGITS] = {'a','b','c','d','e','f','g','h'};
	char moveColumn[AREA+10];
	int moveRow[AREA+10];

	moveColumn[0] = ' ';
	
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j) {
			moveColumn[a[j*N+i]] = notation[j];
			moveRow[a[j*N+i]] = 8-i;
		}
	}

	cout << "+-------------------------------------+" << endl;
	cout << "| CHESS SCORE SHEET 		      |" << endl;
	cout << "+-------------------------------------+" << endl;
	for (int i = 1; i < AREA/2 + 1; i++) {
		cout << "| " << i;
		if (i > SINGLE_DIGITS) { 
			cout << " |    " << moveColumn[i] << moveRow[i] << "    |     ";
	    	}
	    	else 
			cout << "  |    " << moveColumn[i] << moveRow[i] << "    |     ";

		cout << "| "  << i + ADD_COLUMN << " |    " << moveColumn[i+ADD_COLUMN] << moveRow[i+ADD_COLUMN] << "    |" << endl;
		cout << endl;
	}
	cout << "+-------------------------------------+" << endl;

}

/* checks its neighbouring squares */
/* If the knight ends on a square that is one
knight's move from the beginning square,
then tour is closed */
bool neighbour(int x, int y, int xx, int yy)
{
	for (int i = 0; i < N; ++i)
		if (((x+cx[i]) == xx)&&((y + cy[i]) == yy))
			return true;

	return false;
}

/* Generates the legal moves using warnsdorff's
heuristics. Returns false if not possible */
bool findClosedTour()
{
	// Filling up the chessboard matrix with -1's
	int a[N*N];
	for (int i = 0; i< N*N; ++i)
		a[i] = -1;

	// Random initial position
	int sx = rand()%N;
	int sy = rand()%N;

	// Current points are same as initial points
	int x = sx, y = sy;
	a[y*N+x] = 1; // Mark first move.

	// Keep picking next points using
	// Warnsdorff's heuristic
	for (int i = 0; i < N*N-1; ++i)
		if (nextMove(a, &x, &y) == 0)
			return false;

	// Check if tour is closed (Can end
	// at starting point)
	if (!neighbour(x, y, sx, sy))
		return false;

	print(a);
	return true;
}

// Driver code
int main()
{
	// To make sure that different random
	// initial positions are picked.
	srand(time(NULL));

	// While we don't get a solution
	while (!findClosedTour())
	{
	;
	}

	return 0;
}

