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
			{{0,1,0,0}},
			{{0,1,0,0}},
			{{0,1,1,0}},
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