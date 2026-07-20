#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <raylib.h>

#include "Board.h"
#include "Block.h"

int main() {

	InitWindow(600, 800, "Jetris");
	SetTargetFPS(60);

	float falltimer = 0.0f;
	constexpr float fallInterval = 0.5f;

	while (!WindowShouldClose())
	{
		Board board;
		Block block{ BlockType::T };
		int bagCnt = 0;
		std::array<BlockType, 7> blockBag = Block::createBlockBag();

		falltimer += GetFrameTime();

		if (falltimer >= fallInterval) 
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
					std::cout << "Game Over\n";
					break;
				}
			}
		}
	}

	CloseWindow();
}