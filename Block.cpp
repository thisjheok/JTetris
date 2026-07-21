#include <algorithm>
#include <array>
#include <random>
#include <vector>

#include "Block.h"

Block::Block(BlockType blockType)
	: type{ blockType }
{
	switch (type)
	{
	case BlockType::I:
		cells_ = { {
			{{0,0,0,0}},
			{{1,1,1,1}},
			{{0,0,0,0}},
			{{0,0,0,0}}
		}};
		break;
	
	case BlockType::O:
		cells_ = { {
			{{0,0,0,0}},
			{{0,1,1,0}},
			{{0,1,1,0}},
			{{0,0,0,0}}
		} };
		break;
	case BlockType::T:
		cells_ = { {
			{{0,0,0,0}},
			{{1,1,1,0}},
			{{0,1,0,0}},
			{{0,0,0,0}}
		} };
		break;
	case BlockType::S:
		cells_ = { {
			{{0,0,0,0}},
			{{0,0,1,1}},
			{{0,1,1,0}},
			{{0,0,0,0}}
		} };
		break;
	case BlockType::Z:
		cells_ = { {
			{{0,0,0,0}},
			{{1,1,0,0}},
			{{0,1,1,0}},
			{{0,0,0,0}}
		} };
		break;
	case BlockType::J:
		cells_ = { {
			{{0,0,1,0}},
			{{0,0,1,0}},
			{{0,1,1,0}},
			{{0,0,0,0}}
		} };
		break;
	case BlockType::L:
		cells_ = { {
			{{0,0,1,0}},
			{{0,0,1,0}},
			{{0,0,1,1}},
			{{0,0,0,0}}
		} };
		break;
	}
}

std::array<BlockType, 7> Block::createBlockBag()
{
	std::array<BlockType, 7> bag = {
		BlockType::I,
		BlockType::J,
		BlockType::L,
		BlockType::O,
		BlockType::S,
		BlockType::T,
		BlockType::Z
	};

	static std::random_device rd;
	static std::mt19937 generator(rd());

	std::shuffle(bag.begin(), bag.end(), generator);

	return bag;
}

std::array<std::array<char, Block::cols>, Block::rows> Block::rotateCells(Block::Cells old_cells_)
{
	Block::Cells new_cells_{};

	for (int row = 0; row < Block::rows; row++)
	{
		for (int col = 0; col < Block::cols; col++)
		{
			// 2차원 행렬 90도 회전 변환
			new_cells_[col][Block::rows - 1 - row] = old_cells_[row][col];
		}
	}

	return new_cells_;
}