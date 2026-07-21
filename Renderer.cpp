#include "Renderer.h"

#include <raylib.h>

namespace
{
	constexpr int cellSize = 30;

	constexpr int boardScreenX = 100;
	constexpr int boardScreenY = 50;

    Color getBlockColor(BlockType type)
    {
        switch (type)
        {
        case BlockType::I:
            return SKYBLUE;

        case BlockType::O:
            return YELLOW;

        case BlockType::T:
            return PURPLE;

        case BlockType::S:
            return GREEN;

        case BlockType::Z:
            return RED;

        case BlockType::J:
            return BLUE;

        case BlockType::L:
            return ORANGE;
        }

        return WHITE;
    }
    void drawCell(int boardX, int boardY, Color color)
    {
        const int screenX = boardScreenX + boardX * cellSize;
        const int screenY = boardScreenY + boardY * cellSize;

        DrawRectangle(
            screenX + 1,
            screenY + 1,
            cellSize - 2,
            cellSize - 2,
            color
        );

        DrawRectangleLines(
            screenX,
            screenY,
            cellSize,
            cellSize,
            DARKGRAY
        );
    }
}

void Renderer::drawBoard(const Board& board) 
{
    for (int row = 0; row < static_cast<int>(Board::rows); row++)
    {
        for (int col = 0; col < static_cast<int>(Board::cols); col++)
        {
            const int screenX = boardScreenX + col * cellSize;
            const int screenY = boardScreenY + row * cellSize;
            
            if (board.isOccupied(row, col))
            {
                DrawRectangle(
                    screenX + 1,
                    screenY + 1,
                    cellSize - 2,
                    cellSize - 2,
                    BLUE
                );
            }

            DrawRectangleLines(
                screenX,
                screenY,
                cellSize,
                cellSize,
                DARKGRAY
            );
        }
    }
}

void Renderer::drawBlock(const Block& block)
{
    const Color color = getBlockColor(block.type);

    for(int row = 0; row < static_cast<int>(Block::rows); row++)
    {
        for (int col = 0; col < static_cast<int>(Block::cols); col++)
        {
            if(block.cells_[row][col]==0)
            {
                continue;
            }
            const int boardX = block.x + col;
            const int boardY = block.y + row;

            drawCell(boardX, boardY, color);
        }
    }
}

void Renderer::drawGame(const Board& board, const Block& block, bool gameOver)
{
    BeginDrawing();

    ClearBackground(BLACK);

    drawBoard(board);
    drawBlock(block);

    DrawText("JETRIS", 430, 50, 32, WHITE);

    if (gameOver)
    {
        DrawRectangle(120, 300, 260, 100, Fade(BLACK, 0.8f));
        DrawText("GAME OVER", 145, 320, 36, RED);
        DrawText("Press R to restart", 160, 365, 18, WHITE);
    }

    EndDrawing();
}