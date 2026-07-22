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

			// 계산한 board 좌표가 board 바깥이다. => 놓을 수 없음 
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

void Board::placeBlock(const Block& block, int x, int y)
{
	for (int row = 0; row < Block::rows; row++)
	{
		bool hasCell = false;

		for(int col = 0; col < Block::cols; col++)
		{
			if (block.cells_[row][col] != 0)
			{
				// 전부다 0인 행은 실행되지 않는다. 
				cells_[row + y][col + x] = block.cells_[row][col];
				hasCell = true;
			}
		}
		// 보드 상에서 블록이 놓인 row
		// boardRow가 cells_의 행 범위를 초과하는 것을 조심 0 < boardRow <= 20 
		const int boardRow = row + y;
		if (hasCell &&
			boardRow >= 0 && 
			isLineFull(boardRow) &&
			boardRow < static_cast<int>(Board::rows))
		{
			clearRow(boardRow);
			downRows(boardRow);
	    }
	}
}

// Cell 조회 API
bool Board::isOccupied(int row, int col) const
{
	return cells_[row][col] != 0;
}

bool Board::isLineFull(int row) const
{
	for (int col = 0; col < static_cast<int>(Board::cols); col++)
	{
		if (!isOccupied(row,col)) 
		{
			return false;
		}
	}
	return true;
}

void Board::clearRow(int row)
{
	for (int col = 0; col < static_cast<int>(Board::cols); col++)
	{
		cells_[row][col] = 0;
	}
}

void Board::downRows(int clear_row)
{
	for (int row = clear_row; row > 0; row--)
	{
		for (int col = 0; col < static_cast<int>(Board::cols); col++)
		{
			int prev_row = row - 1;
			cells_[row][col] = cells_[prev_row][col];
		}
	}
	for (int col = 0; col < static_cast<int>(Board::cols); col++)
	{
		cells_[0][col] = 0;
	}
}