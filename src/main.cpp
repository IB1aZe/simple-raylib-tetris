#include "raylib.h"
#include "Game.hpp"
#include "Colors.hpp"

#include <iostream>

double lastUpdateTime = 0.0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    int width = 500;
    int height = 620;

    // Initialize the window FIRST
    InitWindow(width, height, "Raylib Tetris");

    // Then disable ESC as exit key - we'll handle it for pause instead
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);

    // Initialize audio device BEFORE loading any sounds
    InitAudioDevice();

    Font font = LoadFont("./fonts/PlaywriteNZBasic-VariableFont_wght.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    Game game = Game();
    bool pauseWasActive = false; // Track pause state change for audio control

    // Main game loop - ESC handled for pause, not for closing window
    while (true)
    {
        // Check if user clicked the window close button
        // Note: ESC is handled in game.HandleInput() for pause, SetExitKey(KEY_NULL) prevents it from closing
        if (WindowShouldClose())
        {
            break;
        }
        // Update music stream only if music was successfully loaded
        if (game.musicLoaded && IsMusicValid(game.music))
        {
            UpdateMusicStream(game.music);
        }

        game.HandleInput();

        // Update game logic only if not paused
        if (!game.paused)
        {
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }
            // Resume music if it was just unpaused
            if (pauseWasActive && game.musicLoaded && IsMusicValid(game.music))
            {
                ResumeMusicStream(game.music);
                pauseWasActive = false;
            }
        }
        else
        {
            // Pause music when game is paused
            if (!pauseWasActive && game.musicLoaded && IsMusicValid(game.music))
            {
                PauseMusicStream(game.music);
                pauseWasActive = true;
            }
        }

        BeginDrawing();

        ClearBackground(BLUE);

        DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {365, 175}, 38, 2, WHITE);
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 40, 2, WHITE);
            DrawTextEx(font, "PRESS ANY", {320, 490}, 40, 2, RED);
            DrawTextEx(font, "KEY", {380, 520}, 40, 2, RED);
        }

        DrawRectangleRounded({320, 55, 170, 60}, 0.3f, 6, lightBlue);
        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {(310 + (170 - textSize.x) / 2), 70}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3f, 6, lightBlue);

        game.Draw();

        // Display PAUSED message when paused
        if (game.paused && !game.gameOver)
        {
            DrawTextEx(font, "PAUSED", {170, 250}, 50, 2, YELLOW);
            DrawTextEx(font, "Press ESC to resume", {130, 320}, 30, 2, WHITE);
        }

        EndDrawing();
    }

    // Close the window and OpenGL context
    CloseAudioDevice();
    CloseWindow();

    return 0;
}