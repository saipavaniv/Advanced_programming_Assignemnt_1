#include <iostream>
#include <cmath>
using namespace std;

class NQueens {
private:
    int n;
    int *col;
    int solutionCount;

    // Check whether a queen can be placed at (row, c)
    bool isSafe(int row, int c) {
        for (int r = 0; r < row; r++) {
            // Same column
            if (col[r] == c)
                return false;

            // Same diagonal
            if (abs(col[r] - c) == abs(r - row))
                return false;
        }

        return true;
    }

    // Display one complete solution
    void printBoard() {
        solutionCount++;

        cout << "\nSolution " << solutionCount << ":\n";

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (col[r] == c)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << "\n";
        }
    }

    // Backtracking function
    void solve(int row) {
        if (row == n) {
            printBoard();
            return;
        }

        for (int c = 0; c < n; c++) {
            if (isSafe(row, c)) {
                col[row] = c;

                solve(row + 1);

                // Backtrack
                col[row] = -1;
            }
        }
    }

public:
    NQueens(int size) {
        n = size;
        col = new int[n];

        for (int i = 0; i < n; i++)
            col[i] = -1;

        solutionCount = 0;
    }

    ~NQueens() {
        delete[] col;
    }

    void findSolutions() {
        solve(0);

        if (solutionCount == 0) {
            cout << "No solutions exist for N = " << n << "\n";
        }
        else {
            cout << "\nTotal solutions for N = "
                 << n << ": " << solutionCount << "\n";
        }
    }
};

int main() {
    int n;

    cout << "Enter board size (N): ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid board size.\n";
        return 0;
    }

    NQueens queens(n);
    queens.findSolutions();

    return 0;
}