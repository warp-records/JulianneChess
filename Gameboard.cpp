
#include "Gameboard.hpp"


GameBoard::GameBoard() {
	//get() just obtains the raw pointer value from the pointer wrapper
	for (auto pieceItr = white.pieceList.begin(); pieceItr != white.pieceList.end(); pieceItr++)
		board[(*pieceItr)->getPos().column][(*pieceItr)->getPos().row] = pieceItr->get();

	for (auto pieceItr = black.pieceList.begin(); pieceItr != black.pieceList.end(); pieceItr++)
		board[(*pieceItr)->getPos().column][(*pieceItr)->getPos().row] = pieceItr->get();

}


Bitboard GameBoard::genBitBoard() const {
	Bitboard bb = 0x00;

	for (auto pc = black.pieceList.begin(); pc != black.pieceList.end(); pc++)
		bb |= (*pc)->getBBoard();

	for (auto pc = white.pieceList.begin(); pc != white.pieceList.end(); pc++)
		bb |= (*pc)->getBBoard();


	return bb;
}

//GOD this is gonna be so slow
GameBoard::Team::Team(Color _color) {
	Color color = _color;

	uint8_t yPos = (color == White ? 0 : 7);
	teamBitBoard = 0x00000000000000FF;
	teamBitBoard <<= yPos;

	pieceList = std::initializer_list<PiecePtr> {
		new Pieces::King({4, yPos}),
		new Pieces::Queen({3, yPos}),
		new Pieces::Rook({0, yPos}),
		new Pieces::Rook({7, yPos}),
		new Pieces::Bishop({2, yPos}),
		new Pieces::Bishop({5, yPos}),
		new Pieces::Knight({6, yPos}),
		new Pieces::Knight({1, yPos}),
	};

	yPos = (color == White ? 1 : 6);
	for (uint8_t i = 0; i < 8; i++)
		pieceList.push_back(PiecePtr(new Pieces::Pawn({i, yPos})));

}