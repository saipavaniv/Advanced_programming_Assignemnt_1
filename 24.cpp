#include <iostream>
using namespace std;

class RatInMaze {
private:
    static const int SIZE = 4;

    int maze[SIZE][SIZE];
    int solution[SIZE][SIZE];

    // Check whether the cell is inside the maze,
    // open, and not already part of the current path
    bool isSafe(int row, int column) {
        if (row < 0 || row >= SIZE || column < 0 || column >= SIZE)
            return false;

        if (maze[row][column] == 0)
            return false;

        if (solution[row][column] == 1)
            return false;

        return true;
    }

    // Backtracking function to find a path
    bool solve(int row, int column) {

        // Check whether the current cell is safe
        if (!isSafe(row, column))
            return false;

        // Mark the current cell as part of the path
        solution[row][column] = 1;

        // Destination reached
        if (row == SIZE - 1 && column == SIZE - 1)
            return true;

        // Move Down
        if (solve(row + 1, column))
            return true;

        // Move Right
        if (solve(row, column + 1))
            return true;

        // Move Up
        if (solve(row - 1, column))
            return true;

        // Move Left
        if (solve(row, column - 1))
            return true;

        // No path found from this cell,
        // so backtrack and remove it from the solution
        solution[row][column] = 0;

        return false;
    }

public:
    // Constructor initializes the given maze
    RatInMaze() {

        int input[SIZE][SIZE] = {
            {1, 0, 0, 0},
            {1, 1, 0, 1},
            {0, 1, 0, 0},
            {1, 1, 1, 1}
        };

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                maze[i][j] = input[i][j];
                solution[i][j] = 0;
            }
        }
    }

    // Display the original maze
    void displayMaze() {
        cout << "Given Maze:\n";

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                cout << maze[i][j] << " ";

            cout << "\n";
        }
    }

    // Find and display a valid path
    void findPath() {

        if (!solve(0, 0)) {
            cout << "\nNo valid path exists from source to destination.\n";
            return;
        }

        cout << "\nValid Path:\n";

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                if (i == 0 && j == 0)
                    cout << "S ";

                else if (i == SIZE - 1 && j == SIZE - 1)
                    cout << "D ";

                else if (solution[i][j] == 1)
                    cout << "* ";

                else
                    cout << ". ";
            }

            cout << "\n";
        }
    }
};

int main() {

    RatInMaze maze;

    maze.displayMaze();
    maze.findPath();

    return 0;
}