#ifndef _tetrisPiece_
#define _tetrisPiece_

class tetrisPiece
{
	public:
		int getPieceType(int pPiece, int pRotate, int pX, int pY);
		int getXInitPos (int pPiece, int pRotate);
		int getYInitPos (int pPiece, int pRotate);
};

#endif
