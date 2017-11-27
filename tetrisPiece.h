#ifndef _tetrisPiece_
#define _tetrisPiece_

class tetrisPiece
{
	public:
		int GetPieceType(int pPiece, int pRotate, int pX, int pY);
		int GetXInitPos (int pPiece, int pRotate);
		int GetYInitPos (int pPiece, int pRotate);
};

#endif
