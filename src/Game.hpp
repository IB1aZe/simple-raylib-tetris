#pragma once
#include "Grid.hpp"
#include "Blocks.hpp"

class Game
{
private:
    bool IsBlockPositionValid();
    void LockBlock();
    bool BlockFitsInGrid();
    void Reset();
    void UpdateScore(int rowsCleared, int rowsClearedInARow);
    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
    // Key repeat state for smooth single-press and hold behavior
    double leftLastMoveTime = 0.0;
    double rightLastMoveTime = 0.0;
    double leftRepeatInterval = 0.25; // initial delay before repeating
    double rightRepeatInterval = 0.25;
    bool leftKeyPrevDown = false;
    bool rightKeyPrevDown = false;
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    Sound rotateSound;
    Sound gameOverSound;
    Sound pointSound;
    Sound clearSound;
    bool rotateSoundLoaded = false;
    bool gameOverSoundLoaded = false;
    bool pointSoundLoaded = false;
    bool clearSoundLoaded = false;

public:
    Game();
    ~Game();

    void Draw();
    void HandleInput();
    void MoveBlockDown();

    Music music;
    bool gameOver;
    bool paused = false;
    bool musicLoaded = false;
    int score;
};
