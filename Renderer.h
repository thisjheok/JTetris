#pragma once

#include "Board.h"
#include "Block.h"

// namespace인 이유가 뭐임
namespace Renderer {
	void drawBoard(const Board& board);
	void drawBlock(const Block& block);
	void drawGame(const Board& board, const Block& block, bool gameOver);
}