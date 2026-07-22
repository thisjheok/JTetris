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
	float moveTimer = 0.0f;

	constexpr float moveInterval = 0.1f;
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
			int movedir = 0;

			if (IsKeyDown(KEY_LEFT))
			{
				movedir = -1;
			}

			if (IsKeyDown(KEY_RIGHT))
			{
				movedir = 1;
			}

			const bool firstPress =
				IsKeyPressed(KEY_LEFT) ||
				IsKeyPressed(KEY_RIGHT);

			if (firstPress)
			{
				const int newX = block.x + movedir;

				if (board.canPlace(block, newX, block.y))
				{
					block.x = newX;
				}

				moveTimer = 0.0f;
			}
			else if (movedir != 0)
			{
				moveTimer += GetFrameTime();
				if (moveTimer >= moveInterval)
				{
					const int newX = block.x + movedir;
					if (board.canPlace(block, newX, block.y))
					{
						block.x = newX;
					}
					moveTimer = 0.0f;
				}
			}
			else
			{
				moveTimer = 0.0f;
			}

			if (IsKeyPressed(KEY_UP))
			{
				board.rotateCells(block);
			}

			if (IsKeyPressed(KEY_SPACE))
			{
				while (board.canPlace(block, block.x, block.y+1))
				{
					block.y++;
				}
				board.placeBlock(block, block.x, block.y);

				if (bagCnt == 7) {
					blockBag = Block::createBlockBag();
					bagCnt = 0;
				}

				block = Block{ blockBag[bagCnt++] };

				if (!board.canPlace(block, block.x, block.y))
				{
					gameOver = true;
				}

				falltimer = 0.0f;
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