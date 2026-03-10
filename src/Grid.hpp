#pragma once
#include <vector>
#include "raylib.h"

class Grid
{
private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowsDown(int startRow, int numRows);
    int numberOfRows;
    int numberOfColumns;
    int cellSize;
    std::vector<Color> colors;

public:
    Grid(/* args */);

    ~Grid();

    int grid[20][10] = {0};
    void Print() const;
    void Draw() const;
    bool IsCellOutOfBounds(int row, int col) const;
    bool IsCellOccupied(int row, int col);
    int ClearFullRows();
};