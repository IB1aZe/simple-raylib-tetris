#pragma once
#include <vector>
#include <map>
#include "Position.hpp"
#include "Colors.hpp"

class Block
{
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

public:
    Block(/* args */);
    ~Block();

    void Draw(int offsetX, int offsetY);
    void Move(int rows, int cols);
    std::vector<Position> GetCellsPositions();
    void Rotate();
    void UndoRotation();

    int id;
    std::map<int, std::vector<Position>> cells;
    int rowOffset;
    int colOffset;
};
