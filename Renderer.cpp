#include "Renderer.h"

#include <algorithm>
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

    void drawPreviewBlock(const Block& block, int centerX, int centerY)
    {
        int minRow = static_cast<int>(Block::rows);
        int maxRow = -1;
        int minCol = static_cast<int>(Block::cols);
        int maxCol = -1;

        // 실제 블록이 차지하는 범위 계산
        for (int row = 0; row < static_cast<int>(Block::rows); row++)
        {
            for (int col = 0; col < static_cast<int>(Block::cols); col++)
            {
                if (block.cells_[row][col] == 0)
                    continue;

                minRow = std::min(minRow, row);
                maxRow = std::max(maxRow, row);
                minCol = std::min(minCol, col);
                maxCol = std::max(maxCol, col);
            }
        }

        if (maxRow == -1 || maxCol == -1)
            return;

        const int blockWidth = (maxCol - minCol + 1) * cellSize;
        const int blockHeight = (maxRow - minRow + 1) * cellSize;

        const int startX = centerX - blockWidth / 2;
        const int startY = centerY - blockHeight / 2;

        const Color color = getBlockColor(block.type);

        for (int row = minRow; row <= maxRow; row++)
        {
            for (int col = minCol; col <= maxCol; col++)
            {
                if (block.cells_[row][col] == 0)
                    continue;

                const int screenX = startX + (col - minCol) * cellSize;
                const int screenY = startY + (row - minRow) * cellSize;

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
                    GRAY
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

void Renderer::drawGame(int score,const Board& board, const Block& block, bool gameOver, const Block& nextBlock)
{
    constexpr int centerX = 500;
    constexpr int fontSize = 24;

    auto drawCenteredText = [](const char* text, int centerX, int y, int fontSize, Color color)
        {
            const int textWidth = MeasureText(text, fontSize);
            DrawText(text, centerX - textWidth / 2, y, fontSize, color);
        };
    BeginDrawing();

    ClearBackground(BLACK);

    drawBoard(board);
    drawBlock(block);

    drawCenteredText("JETRIS", centerX, 50, 32, SKYBLUE);

    drawCenteredText("SCORE", centerX, 100, fontSize, WHITE);
    drawCenteredText(TextFormat("%d", score), centerX, 150, fontSize, WHITE);

    drawCenteredText("NEXT", centerX, 200, fontSize, WHITE);
    Block previewBlock = nextBlock;
    previewBlock.x = 11; // 보드 칸 기준 좌표
    previewBlock.y = 6;
    drawPreviewBlock(previewBlock, centerX, 280);

    if (gameOver)
    {
        DrawRectangle(120, 300, 260, 100, Fade(BLACK, 0.8f));
        DrawText("GAME OVER", 145, 320, 36, RED);
        DrawText("Press R to restart", 160, 365, 18, WHITE);
    }

    EndDrawing();
}