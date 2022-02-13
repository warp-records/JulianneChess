
#include "Gameboard.hpp"


GameBoard::GameBoard() {}

Bitboard GameBoard::genBitBoard() const {
	Bitboard board = 0x00;
	for (auto pc = black.pieceList.begin(); pc != black.pieceList.end(); pc++)
		board |= (*pc)->getBBoard();

	for (auto pc = white.pieceList.begin(); pc != white.pieceList.end(); pc++)
		board |= (*pc)->getBBoard();

	return board;
}

//GOD this is gonna be so slow
GameBoard::Team::Team(Color _color) {
	Color color = _color;

	uint8_t yPos = (color == White ? 0 : 7);


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

	king = { pieceList[0] };
	queens = { pieceList[1] };
	rooks = { pieceList[2], pieceList[3] };
	bishops = { pieceList[4], pieceList[5] };
	knights = { pieceList[6], pieceList[7] };
	pawns = std::vector<PiecePtr>(8);

	for (int i = 0; i < 8; i++)
		pawns.push_back(pieceList[i+8]);
}