#include "Block.hpp"
#include "Position.hpp"

class LBlock : public Block
{
public:
    LBlock()
    {
        id = 1; // Assuming 1 corresponds to the color for LBlock
        cells = {
            {0, {{0, 2}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 1}, {1, 1}, {2, 1}, {2, 2}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 0}}},
            {3, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};

class JBlock : public Block
{
public:
    JBlock()
    {
        id = 2; // Assuming 2 corresponds to the color for JBlock
        cells = {
            {0, {{0, 0}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 2}, {0, 1}, {1, 1}, {2, 1}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 2}}},
            {3, {{0, 1}, {1, 1}, {2, 1}, {2, 0}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 3; // Assuming 3 corresponds to the color for TBlock
        cells = {
            {0, {{0, 1}, {1, 0}, {1, 1}, {1, 2}}},
            {1, {{0, 1}, {1, 1}, {1, 2}, {2, 1}}},
            {2, {{1, 0}, {1, 1}, {1, 2}, {2, 1}}},
            {3, {{0, 1}, {1, 0}, {1, 1}, {2, 1}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = 4; // Assuming 4 corresponds to the color for IBlock
        cells = {
            {0, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
            {1, {{0, 1}, {1, 1}, {2, 1}, {3, 1}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        id = 5; // Assuming 5 corresponds to the color for OBlock
        cells = {
            {0, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}}};
        Move(0, 4); // Move the block to the center of the grid
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 6; // Assuming 6 corresponds to the color for SBlock
        cells = {
            {0, {{0, 1}, {0, 2}, {1, 0}, {1, 1}}},
            {1, {{0, 1}, {1, 1}, {1, 2}, {2, 2}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7; // Assuming 7 corresponds to the color for ZBlock
        cells = {
            {0, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
            {1, {{0, 2}, {1, 1}, {1, 2}, {2, 1}}}};
        Move(0, 3); // Move the block to the center of the grid
    }
};