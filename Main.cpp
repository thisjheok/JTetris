#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <raylib.h>

#include "Board.h"
#include "Block.h"
#include "Renderer.h"

int main() {

	InitWindow(600, 800, "Jetris");
	SetTargetFPS(60);

	float falltimer = 0.0f;

	constexpr float normalFallInterval = 0.5f;
	constexpr float softDropInterval = 0.05f;

	Board board;
	
	bool gameOver = false;

	int bagCnt = 0;
	std::array<BlockType, 7> blockBag = Block::createBlockBag();
	Block block{ blockBag[bagCnt++]};

	while (!WindowShouldClose())
	{
		if (!gameOver) 
		{
			if (IsKeyPressed(KEY_LEFT) &&
				board.canPlace(block, block.x - 1, block.y))
			{
				block.x--;
			}

			if (IsKeyPressed(KEY_RIGHT) &&
				board.canPlace(block, block.x + 1, block.y))
			{
				block.x++;
			}

			if (IsKeyPressed(KEY_UP))
			{
				board.rotateCells(block);
			}

			const float currentFallInterval =
				IsKeyDown(KEY_DOWN)
				? softDropInterval
				: normalFallInterval;

			falltimer += GetFrameTime();

			if (falltimer >= currentFallInterval)
			{
				falltimer = 0.0f;	
				if (bagCnt == 7) {
					blockBag = Block::createBlockBag();
					bagCnt = 0;
				}
				if (board.canPlace(block, block.x, block.y + 1))
				{
					block.y++;
				}
				else
				{
					board.placeBlock(block, block.x, block.y);
					
					BlockType nextBlock = blockBag[bagCnt];
					block = Block{ nextBlock };
					bagCnt++;

					// 생성 위치에 놓을 수 없다면 게임 오버
					if (!board.canPlace(block, block.x, block.y))
					{
						gameOver = true;
					}
				}
			}
			Renderer::drawGame(board, block, gameOver);
		}
	}

	CloseWindow();
}