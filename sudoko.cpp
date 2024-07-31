#include <iostream>
using namespace std;

// Size of the Sudoku grid
#define N 9

// Function to print the solved Sudoku grid with 3x3 squares
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+------+------" << endl;
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            if (col == 8) {
                cout << grid[row][col];
            } else {
                cout << grid[row][col] << " ";
            }
        }
        cout << endl;
    }
}


// Function to check if the current cell is safe to place the number
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number exists in the current row or column
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if the number exists in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Check for an empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    // If no empty cell is found, Sudoku is solved
    if (!isEmpty)
        return true;

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        // Check if it's safe to place the number
        if (isSafe(grid, row, col, num)) {
            // Place the number if it's safe
            grid[row][col] = num;

            // Recursively solve the Sudoku puzzle
            if (solveSudoku(grid))
                return true;

            // Backtrack if placing the number leads to an invalid solution
            grid[row][col] = 0;
        }
    }
    return false; // No valid number found, backtrack
}

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku puzzle (0 for empty cells):" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cin >> grid[row][col];
        }
    }

    // Solve Sudoku
    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
