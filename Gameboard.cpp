
#include "Gameboard.hpp"


GameBoard::GameBoard() {}

Bitboard GameBoard::genBitBoard() const {
	/*for (auto pc = black.pieceList.begin(); pc != black.pieceList.end(); pc++)
		board |= (*pc)->getBBoard();

	for (auto pc = white.pieceList.begin(); pc != white.pieceList.end(); pc++)
		board |= (*pc)->getBBoard();*/

	for (auto pieceItr = white.pieceList.begin(); pieceItr != white.pieceList.end(); pieceItr++)
		board[(*pieceItr)->getPos().column][(*pieceItr)->getPos().row] = *pieceItr;

	for (auto pieceItr = black.pieceList.begin(); pieceItr != black.pieceList.end(); pieceItr++)
		board[(*pieceItr)->getPos().column][(*pieceItr)->getPos().row] = *pieceItr;


	return board;
}

//GOD this is gonna be so slow
GameBoard::Team::Team(Pieces::Color _color) {
	Pieces::Color color = _color;

	uint8_t yPos = (color == Pieces::White ? 0 : 7);
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