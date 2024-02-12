#include <iostream>
#include <ctime>
#include <cstdlib>
#include "grid.h"
#define BLOCK '#'
#define PATH ' '
#define EMPTY '.'
#define ONITEM '@'
#define ITEM '0'

using namespace std;

Grid::Grid()
{
	rowSize = 1;
	columnSize = 1;
	moverRow = rowSize - 1;
	moverColumn = columnSize - 1;
	mover = '>';
	GridArr[moverRow][moverColumn] = mover;
	toggle = true;
}

Grid::Grid(int r, int c)
{
	if(r < 3) rowSize = 3;
	else if(r > 40) rowSize = 40;
	else rowSize = r;

	if(c < 3) columnSize = 3;
	else if(c > 40) columnSize = 40;
	else columnSize = c;

	exitRow = this->GetRand(rowSize);
	if(exitRow == 0 || exitRow == rowSize - 1) exitColumn = (this->GetRand(columnSize - 2) + 1);
	else
	{
		switch(this->GetRand(2))
		{
			case 0: 
			{
				exitColumn = 0; break;
			}
			case 1:
			{
				exitColumn = columnSize - 1; break;
			}
		}
	} 

	moverRow = this->GetRand(rowSize - 2) + 1;
	moverColumn = this->GetRand(columnSize - 2) + 1;

	switch(this->GetRand(4))
	{
		case NORTH: mover = '^';
		case SOUTH: mover = 'V';
		case EAST: mover = '>';
		case WEST: mover = '<';
	}
		
	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < columnSize; j++)
		{
			if(i == 0 || i == rowSize - 1) GridArr[i][j] = BLOCK;
			else if(j == 0 || j == columnSize - 1) GridArr[i][j] = BLOCK;
			else GridArr[i][j] = EMPTY;
		}
	}
	
	GridArr[moverRow][moverColumn] = mover;
	GridArr[exitRow][exitColumn] = ' ';
	toggle = true;
}
 
Grid::Grid(int r, int c, int mr, int mc, int d)
{
	if(r < 1) rowSize = 1;
	else if(r > 40) rowSize = 40;
	else rowSize = r;

	if(c < 1) columnSize = 1;
	else if(c > 40) columnSize = 40;
	else columnSize = c;

	if(mr < 0) moverRow = 0;
	else if(mr > rowSize - 1) moverRow = rowSize - 1;
	else moverRow = mr;

	if(mc < 0) moverColumn = 0;
	else if(mc > columnSize - 1) moverColumn = columnSize - 1;
	else moverColumn = mc;

	switch(d)
	{
		case NORTH: mover = '^';
		case SOUTH: mover = 'V';
		case EAST: mover = '>';
		case WEST: mover = '<';
	}
	
	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < columnSize; j++)
			GridArr[i][j] = EMPTY;
	}
	
	
	GridArr[moverRow][moverColumn] = mover;
	toggle = true;
}

const int Grid::GetRand(const int m) const
{
	srand(time(0));
	return rand() % m;
}

void Grid::Display() const
{
	cout << "The Grid:" << endl;
	
	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < columnSize; j++)
		{
			if(toggle) cout << GridArr[i][j] << ' ';
			else 
			{
				if(GridArr[i][j] == ' ') cout << '.' << ' ';
				else cout << GridArr[i][j] << ' ';
			}
			if(j == columnSize - 1) cout << endl;
		}
	}
}

void Grid::TogglePath()
{
	if(toggle) toggle = false;
	else toggle = true;
}

int Grid::GetRow() const
{
	return moverRow;
}

int Grid::GetCol() const
{
	return moverColumn;
}

int Grid::GetNumRows() const
{
	return rowSize;
}

int Grid::GetNumCols() const
{
	return columnSize;
}

bool Grid::FrontIsClear() const
{
	switch(mover)
	{
		case '^':
		{
			if(GridArr[moverRow - 1][moverColumn] != BLOCK
                           && moverRow - 1 >= 0) return true;
			else return false;
			break;
		}
		case '>':
		{
			if(GridArr[moverRow][moverColumn + 1] != BLOCK 
                           && moverColumn + 1 < columnSize) return true;
			else return false;
			break; 
		}
		case 'V':
		{
			if(GridArr[moverRow + 1][moverColumn] != BLOCK
                           && moverRow + 1 < rowSize) return true;
			else return false;
			break;
		}
		case '<':
		{
			if(GridArr[moverRow][moverColumn - 1] != BLOCK
                           && moverColumn - 1 >= 0) return true;
			else return false;
			break;
		}
	}
}

bool Grid::RightIsClear() const
{
	switch(mover)
	{
		case '^':
		{
			if(GridArr[moverRow][moverColumn + 1] != BLOCK
                           && moverColumn + 1 < columnSize) return true;
			else return false;
			break;
		}
		case '>':
		{
			if(GridArr[moverRow + 1][moverColumn] != BLOCK 
                           && moverRow + 1 < rowSize) return true;
			else return false;
			break; 
		}
		case 'V':
		{
			if(GridArr[moverRow][moverColumn - 1] != BLOCK
                           && moverColumn - 1 >= 0) return true;
			else return false;
			break;
		}
		case '<':
		{
			if(GridArr[moverRow - 1][moverColumn] != BLOCK
                           && moverRow - 1 >= 0) return true;
			else return false;
			break;
		}
	}
}

void Grid::PutDown()
{
	if(GridArr[moverRow][moverColumn] != ONITEM) GridArr[moverRow][moverColumn] = ONITEM;
}

bool Grid::PutDown(int r, int c)
{
	if(r >= 0 && r < rowSize && c >= 0 && c < columnSize 
           && GridArr[r][c] != BLOCK)
	{
		if(GridArr[r][c] == ITEM) return true;
		else if(GridArr[r][c] == ONITEM) return true;
		else
		{
			if(GridArr[r][c] == mover)
			{
				GridArr[r][c] = ONITEM;
				return true;
			}
			else
			{
				GridArr[r][c] = ITEM;
				return true;
			}
		}
	}
	else return false;
}

bool Grid::PlaceBlock(int r, int c)
{
	if(r >= 0 && r < rowSize && c >= 0 && c < columnSize 
           && GridArr[r][c] != BLOCK && GridArr[r][c] != ITEM 
           && GridArr[r][c] != ONITEM && GridArr[r][c] != mover)
	{
		GridArr[r][c] = BLOCK;
		return true;
	}
	else return false;
}

bool Grid::PickUp()
{
	if(GridArr[moverRow][moverColumn] == ONITEM)
	{
		GridArr[moverRow][moverColumn] = mover;
		return true;
	}
	else return false;
}

bool Grid::Move(int s)
{
	switch(mover)
	{
		case '^':
		{
			if(moverRow - s >= 0)
			{
				for(int i = moverRow; i >= moverRow - s; i--)
					if(GridArr[i][moverColumn] == BLOCK) return false;
				
				for(int i = moverRow; i >= moverRow - s; i--)
					if(GridArr[i][moverColumn] != ITEM 
					    && GridArr[i][moverColumn] != ONITEM) 
						GridArr[i][moverColumn] = PATH;

				if(GridArr[moverRow - s][moverColumn] == ITEM)
					GridArr[moverRow - s][moverColumn] = ONITEM;
				else GridArr[moverRow - s][moverColumn] = mover;

				if(GridArr[moverRow][moverColumn] == ONITEM) 
					GridArr[moverRow][moverColumn] = ITEM;
				
				moverRow = moverRow - s;
				return true;
			}
			else return false;
		}
		case '>':
		{
			if(moverColumn + s < columnSize)
			{
				for(int i = moverColumn; i <= moverColumn + s; i++)
					if(GridArr[moverRow][i] == BLOCK) return false;
				
				for(int i = moverColumn; i <= moverColumn + s; i++)
					if(GridArr[moverRow][i] != ITEM 
					    && GridArr[moverRow][i] != ONITEM) 
						GridArr[moverRow][i] = PATH;

				if(GridArr[moverRow][moverColumn + s] == ITEM)
					GridArr[moverRow][moverColumn + s] = ONITEM;
				else GridArr[moverRow][moverColumn + s] = mover;

				if(GridArr[moverRow][moverColumn] == ONITEM) 
					GridArr[moverRow][moverColumn] = ITEM;
				
				moverColumn = moverColumn + s;
				return true;
			}
			else return false;
		}
		case 'V':
		{
			if(moverRow + s < rowSize)
			{
				for(int i = moverRow; i <= moverRow + s; i++)
					if(GridArr[i][moverColumn] == BLOCK) return false;
				
				for(int i = moverRow; i <= moverRow + s; i++)
					if(GridArr[i][moverColumn] != ITEM 
					    && GridArr[i][moverColumn] != ONITEM) 
						GridArr[i][moverColumn] = PATH;

				if(GridArr[moverRow + s][moverColumn] == ITEM)
					GridArr[moverRow + s][moverColumn] = ONITEM;
				else GridArr[moverRow + s][moverColumn] = mover;

				if(GridArr[moverRow][moverColumn] == ONITEM) 
					GridArr[moverRow][moverColumn] = ITEM;
				
				moverRow = moverRow + s;
				return true;
			}
			else return false;
		}
		case '<':
		{
			if(moverColumn - s >= 0)
			{
				for(int i = moverColumn; i >= moverColumn - s; i--)
					if(GridArr[moverRow][i] == BLOCK) return false;
				
				for(int i = moverColumn; i >= moverColumn - s; i--)
					if(GridArr[moverRow][i] != ITEM 
					    && GridArr[moverRow][i] != ONITEM) 
						GridArr[moverRow][i] = PATH;

				if(GridArr[moverRow][moverColumn - s] == ITEM)
					GridArr[moverRow][moverColumn - s] = ONITEM;
				else GridArr[moverRow][moverColumn - s] = mover;

				if(GridArr[moverRow][moverColumn] == ONITEM) 
					GridArr[moverRow][moverColumn] = ITEM;
				
				moverColumn = moverColumn - s;
				return true;
			}
			else return false;
		}
	}
}

void Grid::TurnLeft()
{
	switch(mover)
	{
		case '^':
		{
			mover = '<'; break;
		}
		case '>':
		{
			mover = '^'; break;
		}
		case 'V':
		{
			mover = '>'; break;
		}
		case '<':
		{
			mover = 'V'; break;
		}
	}
}

void Grid::Grow(int gr, int gc)
{
	int newrowStart = rowSize;
	int newcolStart = columnSize;

	if(rowSize + gr > 40) rowSize = 40;
	else rowSize = rowSize + gr;
	
	if(columnSize + gc > 40) columnSize = 40;
	else columnSize = columnSize + gc;
	
	for(int i = 0; i < rowSize; i++)
	{
		if(i < newrowStart)
		{
			for(int j = newcolStart; j < columnSize; j++)
				GridArr[i][j] = EMPTY;
		}
		else
		{
			for(int j = 0; j < columnSize; j++)
				GridArr[i][j] = EMPTY;
		}
	}
} 
