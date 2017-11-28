#ifndef _playField_
#define _playField_

#include "tetrisPiece.h" // Tetris Pieces


#define Play_Field_Line_Width 6		//BOARD_LINE_WIDTH	// Width of each of the two lines that delimit the board
#define Max_Tetris_Square_Area 16	//BLOCK_SIZE			// Width and Height of each block of a piece
#define Play_Field_Center 320		//BOARD_POSITION	// Center position of the board from the left of the screen
#define Play_Field_Width 10		//BOARD_WIDTH	// Board width in blocks 
#define Play_Field_Height 20		//BOARD_HEIGHT	// Board height in blocks
#define Min_Height_Margin 20		//MIN_VERTICAL_MARGIN	// Minimum vertical margin for the board limit 		
#define Min_Width_Margin 20		//MIN_HORIZONTAL_MARGIN // Minimum horizontal margin for the board limit
#define Tetris_Block 5			//PIECE_BLOCKS // Number of horizontal and vertical blocks of a matrix piece

class playField
{
public:

	playField(Pieces *pPieces, int pScreenHeight);

	int getXPos(int pPos);
	int getYPos(int pPos);
	bool isFree(int pX, int pY);
	bool isPossible(int pX, int pY, int pPiece, int pRotation);
	void storePiece(int pX, int pY, int pPiece, int pRotation);
	void checkFillLines();
	bool gameOverCheck();

private:

	enum { POS_FREE, POS_FILLED };				// POS_FREE = free position of the board; POS_FILLED = filled position of the board
	int mBoard [Play_Field_Width][Play_Field_Height];	// Board that contains the pieces
	Pieces *mPieces;
	int mScreenHeight;

	void initBoard();
	void deleteLine (int pY);
};

#endif // _playField_
