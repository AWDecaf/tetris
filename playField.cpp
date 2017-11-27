#include "playField.h"

playField::playField (tetrisPiece *pPieces, int pScreenHeight)
{
	// Get the screen height
	mScreenHeight = pScreenHeight;

	// Get the pointer to the pieces class
	mPieces = pPieces;

	//Init the board blocks with free positions
	InitBoard();
}


void playField::InitBoard()
{
	for (int i = 0; i < Play_Field_Width; i++)
		for (int j = 0; j < Play_Field_Height; j++)
			mBoard[i][j] = POS_FREE;
}

void playField::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	// Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + Tetris_Block; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + Tetris_Block; j1++, j2++)
		{	
			// Store only the blocks of the piece that are not holes
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)		
				mBoard[i1][j1] = POS_FILLED;	
		}
	}
}



bool playField::IsGameOver()
{
	//If the first line has blocks, then, game over
	for (int i = 0; i < Play_Field_Width; i++)
	{
		if (mBoard[i][0] == POS_FILLED) return true;
	}

	return false;
}


void playField::DeleteLine (int pY)
{
	// Moves all the upper lines one row down
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < Play_Field_Width; i++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}	
}


/* 
======================================									
Delete all the lines that should be removed
====================================== 
*/
void playField::DeletePossibleLines ()
{
	for (int j = 0; j < Play_Field_Height; j++)
	{
		int i = 0;
		while (i < Play_Field_Width)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == Play_Field_Width) DeleteLine (j);
	}
}

bool playField::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE) return true; else return false;
}


int playField::GetXPosInPixels (int pPos)
{
	return  ( ( Play_Field_Center - (Max_Tetris_Square_Area * (Play_Field_Width / 2)) ) + (pPos * Max_Tetris_Square_Area) );
}

int playField::GetYPosInPixels (int pPos)
{
	return ( (mScreenHeight - (Tetris_Block * Play_Field_Height)) + (pPos * Max_Tetris_Square_Area) );
}


bool playField::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropiate area in the board
	for (int i1 = pX, i2 = 0; i1 < pX + Tetris_Block; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + Tetris_Block; j1++, j2++)
		{	
			// Check if the piece is outside the limits of the board
			if (	i1 < 0 			|| 
				i1 > Play_Field_Width  - 1	||
				j1 > Play_Field_Height - 1)
			{
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)
					return 0;		
			}

			// Check if the piece have collisioned with a block already stored in the map
			if (j1 >= 0)	
			{
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock (i1, j1))	)
					return false;
			}
		}
	}

	// No collision
	return true;
}
