#pragma once

#include <array>
#include <cstddef>
#include "Block.h"

class Board
{
public:
	static constexpr std::size_t rows = 20;
	static constexpr std::size_t cols = 10;
	bool canPlace(const Block& block, int x, int y);
	void placeBlock(const Block& block, int x, int y);
	bool isOccupied(int row, int col) const;
	bool isLineFull(int row) const;
	void clearRow(int row);
	void downRows(int clear_row);
private:
	std::array<std::array<char, cols>, rows> cells_{};
};