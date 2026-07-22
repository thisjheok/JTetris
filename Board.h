#pragma once

#include <array>
#include <cstddef>
#include "Block.h"

class Board
{
public:
	static constexpr std::size_t rows = 20;
	static constexpr std::size_t cols = 10;

	void placeBlock(const Block& block, int x, int y);
	void clearRow(int row);
	void downRows(int clear_row);
	void rotateCells(Block& block);

	bool isOccupied(int row, int col) const;
	bool isLineFull(int row) const;
	bool canPlace(const Block& block, int x, int y);

private:
	std::array<std::array<char, cols>, rows> cells_{};
};