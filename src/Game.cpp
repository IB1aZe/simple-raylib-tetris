#include <raylib.h>
#include "Game.hpp"
#include <iostream>

bool Game::IsBlockPositionValid()
{
    std::vector<Position> blockCells = currentBlock.GetCellsPositions();
    for (const Position &pos : blockCells)
    {
        if (grid.IsCellOutOfBounds(pos.row, pos.col))
        {
            return true;
        }
    }
    return false;
}

Game::Game()
{
    grid = Grid();
    blocks = {LBlock(), JBlock(), TBlock(), IBlock(), OBlock(), SBlock(), ZBlock()};
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;

    // Initialize flags
    musicLoaded = false;
    rotateSoundLoaded = false;
    gameOverSoundLoaded = false;
    pointSoundLoaded = false;
    clearSoundLoaded = false;

    // Load music with error checking
    music = LoadMusicStream("./sounds/music.mp3");
    if (IsMusicValid(music))
    {
        musicLoaded = true;
        SetMusicVolume(music, 0.4f);
        PlayMusicStream(music);
    }
    else
    {
        std::cerr << "Failed to load music.mp3" << std::endl;
    }

    // Load sound effects with error checking
    rotateSound = LoadSound("./sounds/rotate.mp3");
    if (IsSoundValid(rotateSound))
    {
        rotateSoundLoaded = true;
        SetSoundVolume(rotateSound, 0.2f);
    }

    gameOverSound = LoadSound("./sounds/game-over.mp3");
    if (IsSoundValid(gameOverSound))
    {
        gameOverSoundLoaded = true;
        SetSoundVolume(gameOverSound, 0.3f);
    }

    pointSound = LoadSound("./sounds/points.mp3");
    if (IsSoundValid(pointSound))
    {
        pointSoundLoaded = true;
        SetSoundVolume(pointSound, 0.3f);
    }

    clearSound = LoadSound("./sounds/clear.mp3");
    if (IsSoundValid(clearSound))
    {
        clearSoundLoaded = true;
        SetSoundVolume(clearSound, 0.3f);
    }
}

Game::~Game()
{
    if (musicLoaded && IsMusicValid(music))
    {
        UnloadMusicStream(music);
    }
    if (rotateSoundLoaded && IsSoundValid(rotateSound))
    {
        UnloadSound(rotateSound);
    }
    if (gameOverSoundLoaded && IsSoundValid(gameOverSound))
    {
        UnloadSound(gameOverSound);
    }
    if (pointSoundLoaded && IsSoundValid(pointSound))
    {
        UnloadSound(pointSound);
    }
    if (clearSoundLoaded && IsSoundValid(clearSound))
    {
        UnloadSound(clearSound);
    }
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = GetRandomValue(0, (int)blocks.size() - 1);
    return blocks[randomIndex];
}

std::vector<Block> Game::GetAllBlocks()
{
    return {LBlock(), JBlock(), TBlock(), IBlock(), OBlock(), SBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 4: // IBlock
        nextBlock.Draw(255, 285);
        break;
    case 5: // OBlock
        nextBlock.Draw(255, 275);
        break;

    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    // Handle ESC to pause/resume game (unless game is over)
    if (keyPressed == KEY_ESCAPE && !gameOver)
    {
        paused = !paused;
    }

    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }

    // Skip game logic if paused
    if (paused)
    {
        return;
    }

    // Immediate down movement while holding down key
    if (IsKeyDown(KEY_DOWN))
        MoveBlockDown();

    // Handle rotate on single key press
    if (keyPressed == KEY_SPACE)
    {
        RotateBlock();
    }

    // Handle left/right with single-press and hold-to-repeat behavior
    double now = GetTime();

    // LEFT
    bool leftDown = IsKeyDown(KEY_LEFT);
    if (leftDown && !leftKeyPrevDown)
    {
        // Key was just pressed
        MoveBlockLeft();
        leftLastMoveTime = now;
        leftRepeatInterval = 0.25; // initial delay before repeats
    }
    else if (leftDown && leftKeyPrevDown)
    {
        // Key is held
        if (now - leftLastMoveTime >= leftRepeatInterval)
        {
            MoveBlockLeft();
            leftLastMoveTime = now;
            leftRepeatInterval = 0.05; // subsequent repeats faster
        }
    }
    else if (!leftDown)
    {
        leftKeyPrevDown = false;
    }
    leftKeyPrevDown = leftDown;

    // RIGHT
    bool rightDown = IsKeyDown(KEY_RIGHT);
    if (rightDown && !rightKeyPrevDown)
    {
        // Key was just pressed
        MoveBlockRight();
        rightLastMoveTime = now;
        rightRepeatInterval = 0.25;
    }
    else if (rightDown && rightKeyPrevDown)
    {
        if (now - rightLastMoveTime >= rightRepeatInterval)
        {
            MoveBlockRight();
            rightLastMoveTime = now;
            rightRepeatInterval = 0.05;
        }
    }
    else if (!rightDown)
    {
        rightKeyPrevDown = false;
    }
    rightKeyPrevDown = rightDown;
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockPositionValid() || !BlockFitsInGrid())
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockPositionValid() || !BlockFitsInGrid())
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockPositionValid() || !BlockFitsInGrid())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockPositionValid() || !BlockFitsInGrid())
        {
            currentBlock.UndoRotation();
        }

        // Play rotate sound
        if (rotateSoundLoaded && IsSoundValid(rotateSound))
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> blockCells = currentBlock.GetCellsPositions();
    for (const Position &pos : blockCells)
    {
        if (!grid.IsCellOutOfBounds(pos.row, pos.col))
        {
            grid.grid[pos.row][pos.col] = currentBlock.id;
        }
    }
    currentBlock = nextBlock;
    if (!BlockFitsInGrid())
    {
        gameOver = true;

        // Pause music and play game over sound
        if (musicLoaded && IsMusicValid(music))
        {
            PauseMusicStream(music);
        }
        if (gameOverSoundLoaded && IsSoundValid(gameOverSound))
        {
            PlaySound(gameOverSound);
        }
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        // Play clear sound
        if (clearSoundLoaded && IsSoundValid(clearSound))
        {
            PlaySound(clearSound);
        }

        UpdateScore(rowsCleared, rowsCleared);
    }
}

bool Game::BlockFitsInGrid()
{
    std::vector<Position> blockCells = currentBlock.GetCellsPositions();
    for (const Position &pos : blockCells)
    {
        if (grid.IsCellOutOfBounds(pos.row, pos.col) || grid.IsCellOccupied(pos.row, pos.col))
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;

    // Resume music when restarting game
    if (musicLoaded && IsMusicValid(music))
    {
        PlayMusicStream(music);
    }
}

void Game::UpdateScore(int rowsCleared, int rowsClearedInARow)
{
    // Play points sound
    if (pointSoundLoaded && IsSoundValid(pointSound))
    {
        PlaySound(pointSound);
    }

    int baseScore = 100;
    score += baseScore * rowsCleared * rowsClearedInARow;
}
