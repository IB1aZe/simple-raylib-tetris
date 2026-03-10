#include "Block.hpp"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
    id = 0; // Initialize to avoid garbage values
}

Block::~Block()
{
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellsPositions();

    for (const Position &pos : tiles)
    {
        DrawRectangle(pos.col * cellSize + offsetX, pos.row * cellSize + offsetY, cellSize, cellSize, colors[id]);
        DrawRectangleLines(pos.col * cellSize + offsetX, pos.row * cellSize + offsetY, cellSize, cellSize, BLACK);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::GetCellsPositions()
{
    std::vector<Position> currentCells;
    for (const Position &pos : cells[rotationState])
    {
        currentCells.push_back(Position(pos.row + rowOffset, pos.col + colOffset));
    }
    return currentCells;
}

void Block::Rotate()
{
    rotationState = (int)(rotationState + 1) % cells.size();
}

void Block::UndoRotation()
{
    rotationState = (int)(rotationState - 1 + cells.size()) % cells.size();
}
