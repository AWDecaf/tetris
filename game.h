#ifndef _Game_
#define _Game_

#include "Board.h"
#include "Pieces.h"
//#include "IO.h"
#include <time.h>

#define WAIT_TIME 700	// Number of milliseconds that the piece remains before going 1 block down */ 


class Game
{
public:

	Game(playField *pBoard, tetrisPiece *pPieces, IO *pIO, int pScreenHeight);

	void drawScene ();
	void createNewPiece ();

	int mPosX, mPosY;				// Position of the piece that is falling down
	int mPiece, mRotation;				// Kind and rotation the piece that is falling down

private:

	int mScreenHeight;				// Screen height in pixels
	int mNextPosX, mNextPosY;			// Position of the next piece
	int mNextPiece, mNextRotation;		// Kind and rotation of the next piece

	playField *mBoard;
	tetrisPiece *mPieces;
	IO *mIO;

	int getRand (int pA, int pB);
	void initGame();
	void drawPiece (int pX, int pY, int pPiece, int pRotation);
	void drawPiece();
};

#endif // _Game_
