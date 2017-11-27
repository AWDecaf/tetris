#ifndef LINUX
#include <windows.h>
#endif
#include "game.h"#ifndef LINUX
#include <windows.h>
#endif
#include "game.h"

game::game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	// Game initialization
	InitGame ();
}

int game::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}

void game::InitGame()
{
	// Init random numbers
	srand ((unsigned int) time(NULL));

	// First piece
	mPiece			= GetRand (0, 6);
	mRotation		= GetRand (0, 3);
	mPosX 			= (Play_Field_Width / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	//  Next piece
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
	mNextPosX 		= Play_Field_Width + 5;
	mNextPosY 		= 5;	
}


void game::CreateNewPiece()
{
	// The new piece
	mPiece			= mNextPiece;
	mRotation		= mNextRotation;
	mPosX 			= (Play_Field_Width / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	// Random next piece
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
}

void game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
	color mColor;				// Color of the block 

	// Obtain the position in pixel in the screen of the block we want to draw
	int mPixelsX = mBoard->GetXPosInPixels (pX);
	int mPixelsY = mBoard->GetYPosInPixels (pY);

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < Tetris_Block; i++)
	{
		for (int j = 0; j < Tetris_Block; j++)
		{
			// Get the type of the block and draw it with the correct color
			switch (mPieces->GetBlockType (pPiece, pRotation, j, i))
			{
				case 1: mColor = GREEN; break;	// For each block of the piece except the pivot
				case 2: mColor = BLUE; break;	// For the pivot
			}
			
			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
				mIO->DrawRectangle	(mPixelsX + i * Max_Tetris_Square_Area, 
									mPixelsY + j * Max_Tetris_Square_Area, 
									(mPixelsX + i * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
									(mPixelsY + j * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
									mColor);
		}
	}
}


void game::DrawBoard ()
{
	// Calculate the limits of the board in pixels	
	int mX1 = Play_Field_Center - (Max_Tetris_Square_Area * (Play_Field_Width / 2)) - 1;
	int mX2 = Play_Field_Center + (Max_Tetris_Square_Area * (Play_Field_Width / 2));
	int mY = mScreenHeight - (Max_Tetris_Square_Area * Play_Field_Height);
	
	// Check that the vertical margin is not to small
	//assert (mY > MIN_VERTICAL_MARGIN);

	// Rectangles that delimits the board
	mIO->DrawRectangle (mX1 - Play_Field_Line_Width, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle (mX2, mY, mX2 + Play_Field_Line_Width, mScreenHeight - 1, BLUE);
	
	// Check that the horizontal margin is not to small
	//assert (mX1 > MIN_HORIZONTAL_MARGIN);

	// Drawing the blocks that are already stored in the board
	mX1 += 1;
	for (int i = 0; i < Play_Field_Width; i++)
	{
		for (int j = 0; j < Play_Field_Height; j++)
		{	
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeBlock(i, j))	
				mIO->DrawRectangle (	mX1 + i * Max_Tetris_Square_Area, 
										mY + j * Max_Tetris_Square_Area, 
										(mX1 + i * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
										(mY + j * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
										RED);
		}
	}	
}


/* 
======================================									
Draw scene

Draw all the objects of the scene
====================================== 
*/
void game::DrawScene ()
{
	DrawBoard ();													// Draw the delimitation lines and blocks stored in the board
	DrawPiece (mPosX, mPosY, mPiece, mRotation);					// Draw the playing piece
	DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);	// Draw the next piece
}


Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	// Game initialization
	InitGame ();
}


/* 
======================================									
Get a random int between to integers

Parameters:
>> pA: First number
>> pB: Second number
====================================== 
*/
int game::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}


/* 
======================================									
Initial parameters of the game
====================================== 
*/
void game::InitGame()
{
	// Init random numbers
	srand ((unsigned int) time(NULL));

	// First piece
	mPiece			= GetRand (0, 6);
	mRotation		= GetRand (0, 3);
	mPosX 			= (Play_Field_Width / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	//  Next piece
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
	mNextPosX 		= Play_Field_Width + 5;
	mNextPosY 		= 5;	
}


/* 
======================================									
Create a random piece
====================================== 
*/
void game::CreateNewPiece()
{
	// The new piece
	mPiece			= mNextPiece;
	mRotation		= mNextRotation;
	mPosX 			= (Play_Field_Width / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	// Random next piece
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
}


/* 
======================================									
Draw piece

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
>> pPiece:	Piece to draw
>> pRotation:	1 of the 4 possible rotations
====================================== 
*/
void game::DrawPiece (int pX, int pY, int pPiece, int pRotation)
{
	color mColor;				// Color of the block 

	// Obtain the position in pixel in the screen of the block we want to draw
	int mPixelsX = mBoard->GetXPosInPixels (pX);
	int mPixelsY = mBoard->GetYPosInPixels (pY);

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for (int i = 0; i < Tetris_Block; i++)
	{
		for (int j = 0; j < Tetris_Block; j++)
		{
			// Get the type of the block and draw it with the correct color
			switch (mPieces->GetBlockType (pPiece, pRotation, j, i))
			{
				case 1: mColor = GREEN; break;	// For each block of the piece except the pivot
				case 2: mColor = BLUE; break;	// For the pivot
			}
			
			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
				mIO->DrawRectangle	(mPixelsX + i * Max_Tetris_Square_Area, 
									mPixelsY + j * Max_Tetris_Square_Area, 
									(mPixelsX + i * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
									(mPixelsY + j * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
									mColor);
		}
	}
}


/* 
======================================									
Draw board

Draw the two lines that delimit the board
====================================== 
*/
void game::DrawBoard ()
{
	// Calculate the limits of the board in pixels	
	int mX1 = Play_Field_Center - (Max_Tetris_Square_Area * (Play_Field_Width / 2)) - 1;
	int mX2 = Play_Field_Center + (Max_Tetris_Square_Area * (Play_Field_Width / 2));
	int mY = mScreenHeight - (Max_Tetris_Square_Area * Play_Field_Height);
	
	// Check that the vertical margin is not to small
	//assert (mY > MIN_VERTICAL_MARGIN);

	// Rectangles that delimits the board
	mIO->DrawRectangle (mX1 - Play_Field_Line_Width, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle (mX2, mY, mX2 + Play_Field_Line_Width, mScreenHeight - 1, BLUE);
	
	// Check that the horizontal margin is not to small
	//assert (mX1 > MIN_HORIZONTAL_MARGIN);

	// Drawing the blocks that are already stored in the board
	mX1 += 1;
	for (int i = 0; i < Play_Field_Width; i++)
	{
		for (int j = 0; j < Play_Field_Height; j++)
		{	
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeBlock(i, j))	
				mIO->DrawRectangle (	mX1 + i * Max_Tetris_Square_Area, 
										mY + j * Max_Tetris_Square_Area, 
										(mX1 + i * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
										(mY + j * Max_Tetris_Square_Area) + Max_Tetris_Square_Area - 1, 
										RED);
		}
	}	
}


/* 
======================================									
Draw scene

Draw all the objects of the scene
====================================== 
*/
void game::DrawScene ()
{
	DrawBoard ();													// Draw the delimitation lines and blocks stored in the board
	DrawPiece (mPosX, mPosY, mPiece, mRotation);					// Draw the playing piece
	DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);	// Draw the next piece
}
