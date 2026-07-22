#pragma once

#include <array>
#include <cstddef>
#include <iostream>

enum class BlockType
{
   I,
   O,
   T,
   S,
   Z,
   J,
   L
};

struct Block 
{
	static constexpr std::size_t rows = 4;
	static constexpr std::size_t cols = 4;

	int x = 3;
	int y = 0;

	BlockType type;
	using Cells = std::array<std::array<char, cols>, rows>;
	Cells cells_{};

	explicit Block(BlockType type);
	static std::array<BlockType,7> createBlockBag();
};

