#include "Board.h"
#include "Block.h"

bool Board::canPlace(const Block& block, int x, int y)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (block.cells_[r][c] == 0)
				continue;

			// board에 있는 블록 1칸 좌표
			int boardX = x + c;
			int boardY = y + r;

			// 계산한 좌표가 board 바깥이다. 
			if (boardX >= 10 || boardX < 0 || boardY >= 20 || boardY < 0)
			{
				return false;
			}

			// 해당 cells_에 이미 고정된 블록이 있다. 
			if (cells_[boardY][boardX]) 
			{
				return false;
			}
		}
	}
	return true;
}

void Board::printBoard(const Block& block, int x, int y)
{
	for (int row = 0; row < rows; ++row) 
	{
		for (int col = 0; col < cols; ++col) 
		{
			int blockRow = row - y;
			int blockCol = col - x;

			bool isFallingBlock = false;
			if (blockRow >= 0 && blockRow < 4 &&
				blockCol >= 0 && blockCol < 4)
			{
				isFallingBlock = block.cells_[blockRow][blockCol] != 0;
			}

			bool isFixedBlock = cells_[row][col] != 0;
			if(isFixedBlock || isFallingBlock)
			{
				std::cout << "[]";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << '\n';
	}
}

void Board::placeBlock(const Block& block, int x, int y)
{
	for (int row = 0; row < Block::rows; row++)
	{
		for(int col = 0; col < Block::cols; col++)
		{
			if (block.cells_[row][col] != 0)
			{
				cells_[row + y][col + x] = block.cells_[row][col];
			}
		}
	}
}