#include <iostream>
#include "Grid.hpp"
#include "Colors.hpp"

bool Grid::IsRowFull(int row)
{
    for (int col = 0; col < numberOfColumns; col++)
    {
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int col = 0; col < numberOfColumns; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowsDown(int startRow, int numRows)
{
    // Bounds check to prevent accessing out of bounds
    if (startRow < 0 || numRows <= 0)
    {
        return;
    }
    for (int row = startRow; row >= 0; row--)
    {
        for (int col = 0; col < numberOfColumns; col++)
        {
            // Ensure we don't write beyond grid bounds
            if (row + numRows < numberOfRows)
            {
                grid[row + numRows][col] = grid[row][col];
            }
            grid[row][col] = 0;
        }
    }
}

Grid::Grid()
{
    numberOfRows = 20;
    numberOfColumns = 10;
    cellSize = 30;
    colors = GetCellColors();
}

Grid::~Grid()
{
}

void Grid::Print() const
{
    for (size_t row = 0; row < numberOfRows; row++)
    {
        for (size_t column = 0; column < numberOfColumns; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() const
{
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            int cellValue = grid[row][column];
            // Bounds check: ensure cellValue is within valid color range
            if (cellValue < 0 || cellValue >= (int)colors.size())
            {
                cellValue = 0; // Default to first color if invalid
            }
            Color cellColor = colors[cellValue];

            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize, cellSize, cellColor);
            DrawRectangleLines(column * cellSize + 11, row * cellSize + 11, cellSize, cellSize, BLACK);
        }
    }
}

bool Grid::IsCellOutOfBounds(int row, int col) const
{
    if (row < 0 || row >= numberOfRows || col < 0 || col >= numberOfColumns)
    {
        return true;
    }
    return false;
}

bool Grid::IsCellOccupied(int row, int col)
{
    // Bounds check first
    if (row < 0 || row >= numberOfRows || col < 0 || col >= numberOfColumns)
    {
        return false;
    }
    if (grid[row][col] != 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int clearedRows = 0;

    for (int row = numberOfRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);

            // Shift all rows above the cleared row down by one position
            // Move from the cleared row upward to the top
            for (int r = row; r > 0; r--)
            {
                for (int col = 0; col < numberOfColumns; col++)
                {
                    grid[r][col] = grid[r - 1][col];
                }
            }

            // Clear the top row that is now empty
            for (int col = 0; col < numberOfColumns; col++)
            {
                grid[0][col] = 0;
            }

            clearedRows++;

            // Re-check the same row since new rows have shifted down into position
            row++;
        }
    }

    return clearedRows;
}
