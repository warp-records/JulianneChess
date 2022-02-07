
#include "Gameboard.hpp"

GameBoard::GameBoard() {

}


//GOD this is gonna be so slow
GameBoard::Team(Color _color) {
	color = _color;

	if (color == Black) {
		pieceList = PieceList(16) {
			new Pieces::King(4, 7),
			new Pieces::Queen(3, 7),
			new Pieces::Rook(0, 7),
			new Pieces::Rook(7, 7),
			new Pieces::Bishop(2, 7),
			new Pieces::Bishop(5, 7),
			new Pieces::Knight(5, 7),
			new Pieces::Knight(1, 7),
		}

		for (int i = 0; i < 8; i++)
			pieceList.push_back(PiecePtr(new Pieces::Pawn(i, 6)));

	} else {
			pieceList = PieceList(16) {
			new Pieces::King(4, 0),
			new Pieces::Queen(3, 0),
			new Pieces::Rook(0, 0),
			new Pieces::Rook(7, 0),
			new Pieces::Bishop(2, 0),
			new Pieces::Bishop(5, 0),
			new Pieces::Knight(5, 0),
			new Pieces::Knight(1, 0),
		}

		for (int i = 0; i < 8; i++)
			pieceList.push_back(PiecePtr(Pieces::Pawn(i, 1)));
	}

	king = { pieceList[0] };
	queens = { pieceList[1] };
	rooks = { pieceList[2], pieceList[3] };
	bishops = { pieceList[4], pieceList[5] };
	knights = { pieceList[6], pieceList[7] };
	pawns = PieceList(8);

	for (int i = 0; i < 8; i++)
		pawns.push_back(pieceList[i+8]);
}