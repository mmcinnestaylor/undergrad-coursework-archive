// Grid class

const int NORTH = 0;
const int WEST = 1;
const int SOUTH = 2;
const int EAST = 3;

class Grid
{

//friend const int GetRand(const int m);
public:
   Grid();			// build 1 x 1 grid with mover in only
				//  square, facing east
   Grid(int r, int c);		// build grid with r rows, c cols,
				//  blocks around edge with random exit
				//  and random mover position and direction

   Grid(int r, int c, int mr, int mc, int d);
			// build empty grid with r rows, c cols, and mover
                        //  at row mr, col mc, and facing direction d

   bool Move(int s);		// move forward s spaces, if possible
   void TogglePath();		// toggle whether or not moved path is shown
   void TurnLeft();		// turn the mover to the left
   void PutDown();		// put down an item at the mover's position
   bool PutDown(int r, int c);  // put down an item at (r,c), if possible
   bool PickUp();		// pick up item at current position
   bool PlaceBlock(int r, int c);	// put a block at (r,c), if possible
   void Grow(int gr, int gc);	// grow the grid by gr rows, gc columns


   void Display() const;	// display the grid on screen

   // Accessors
   bool FrontIsClear() const;	// check to see if space in front of 
				//  mover is clear
   bool RightIsClear() const;	// check to see if space to right of 
				//  mover is clear
   int GetRow() const;		// return row of the mover
   int GetCol() const;	// return column of the mover
   int GetNumRows() const;	// return number of rows in the grid
   int GetNumCols() const;	// return number of columns in the grid
   
private:
	const int GetRand(const int m) const;
	char GridArr[40][40];
	int rowSize;
	int columnSize;
	char mover;
	int moverRow;
	int moverColumn;
	int exitRow;
	int exitColumn;
	bool toggle;
};
