#include <array>
#include <string>
#include <cstddef>
#include <raylib.h>

#include "Board.h"
#include "Block.h"
#include "Renderer.h"

constexpr int screenWidth = 600;
constexpr int screenHeight = 800;
constexpr int targetFps = 60;

constexpr float moveInterval = 0.1f;
constexpr float normalFallInterval = 0.5f;
constexpr float softDropInterval = 0.05f;

using BlockBag = std::array<BlockType, 7>;

namespace {
	Block createNextBlock(BlockBag& bag, std::size_t& bagIndex)
	{
		if (bagIndex >= bag.size())
		{
			bag = Block::createBlockBag();
			bagIndex = 0;
		}

		return Block{ bag[bagIndex++] };
	}
}

int main() {

	InitWindow(screenWidth, screenHeight, "Jetris");
	SetTargetFPS(targetFps);

	BlockBag blockBag = Block::createBlockBag();
	std::size_t bagIndex = 0;
	Block block = createNextBlock(blockBag, bagIndex);
	Block nextBlock = createNextBlock(blockBag, bagIndex);

	float falltimer = 0.0f;
	float moveTimer = 0.0f;
	bool gameOver = false;

	Board board;

	while (!WindowShouldClose())
	{
		if (gameOver && IsKeyPressed(KEY_R))
		{
			board = Board{};

			blockBag = Block::createBlockBag();
			bagIndex = 0;
			block = createNextBlock(blockBag, bagIndex);
			nextBlock = createNextBlock(blockBag, bagIndex);

			falltimer = 0.0f;
			moveTimer = 0.0f;
			gameOver = false;
		}
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

				block = nextBlock;
				nextBlock = createNextBlock(blockBag, bagIndex);

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
				if (board.canPlace(block, block.x, block.y + 1))
				{
					block.y++;
				}
				else
				{
					board.placeBlock(block, block.x, block.y);
					block = nextBlock;
					nextBlock = createNextBlock(blockBag, bagIndex);

					// 생성 위치에 놓을 수 없다면 게임 오버
					if (!board.canPlace(block, block.x, block.y))
					{
						gameOver = true;
					}
				}
			}
		}
		int currentScore = board.getScore();
		Renderer::drawGame(currentScore, board, block, gameOver, nextBlock);
	}
	CloseWindow();
}