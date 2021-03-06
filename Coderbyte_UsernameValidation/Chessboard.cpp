#include "Chessboard.h"
#include <cstring>
#include "Factorial.h"

using namespace std;

// Have the function ChessboardTraveling(str) read str which will be a string 
// consisting of the location of a space on a standard 8x8 chess board with 
// no pieces on the board along with another space on the chess board. The 
// structure of str will be the following: "(x y)(a b)" where (x y) represents 
// the position you are currently on with x and y ranging from 1 to 8 and 
// (a b) represents some other space on the chess board with a and b also 
// ranging from 1 to 8 where a > x and b > y. Your program should determine 
// how many ways there are of traveling from (x y) on the board to (a b) 
// moving only up and to the right. For example: if str is (1 1)(2 2) then your 
// program should output 2 because there are only two possible ways to travel 
// from space (1 1) on a chessboard to space (2 2) while making only moves up 
// and to the right.

int Chessboard::ChessboardTraveling(std::string str)
{
    int     result  = 0;
	int		x, y, a, b;

    // Str having the format of "(x y)(a b)"
    // parentheses are ignored
    sscanf_s(str.c_str(), "%*c %d %d %*c %*c %d %d %*c", &x, &y, &a, &b);

	int row = a - x;
	int col = b - y;

	result = ComputeUniqueWays(row, row + col);

    return result;
}

int Chessboard::ComputeUniqueWays(const int k, const int n)
{
    int result = 0;
    Factorial  f;

    auto nFact  = f.FirstFactorial(n);
    auto kFact  = f.FirstFactorial(k);
    auto nkFact = f.FirstFactorial(n - k);

    result = nFact / (kFact * nkFact);

    return result;
}

