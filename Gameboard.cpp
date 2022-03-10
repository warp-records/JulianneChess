
#include "Gameboard.hpp"


GameBoard::GameBoard() {

	for (auto const& piece : white.pieceList)
		board[piece->getPos().column][piece->getPos().row] = piece.get();

	for (auto const& piece : white.pieceList)
		board[piece->getPos().column][piece->getPos().row] = piece.get();

}


Bitboard GameBoard::genBitBoard() const {
	Bitboard bb = 0x00;
/*
	for (auto pc = black.pieceList.begin(); pc != black.pieceList.end(); pc++)
		bb |= (*pc)->getBBoard();

	for (auto pc = white.pieceList.begin(); pc != white.pieceList.end(); pc++)
		bb |= (*pc)->getBBoard();

*/
	return bb;
}

//GOD this is gonna be so slow
GameBoard::Team::Team(Color _color) {
	Color color = _color;

	uint8_t yPos = (color == White ? 0 : 7);
	teamBitBoard = 0x00000000000000FF;
	teamBitBoard <<= yPos;


	//Since we can't list initialize unqiue pointers
	std::array<Piece*, 8> tmpArr {{
		new Pieces::King({4, yPos}),
		new Pieces::Queen({3, yPos}),
		new Pieces::Rook({0, yPos}),
		new Pieces::Rook({7, yPos}),
		new Pieces::Bishop({2, yPos}),
		new Pieces::Bishop({5, yPos}),
		new Pieces::Knight({6, yPos}),
		new Pieces::Knight({1, yPos}),
	}};

	for (Piece* ptr : tmpArr)
		pieceList.push_back(PiecePtr(ptr));

	yPos = (color == White ? 1 : 6);
	for (uint8_t i = 0; i < 8; i++)
		pieceList.push_back(PiecePtr(new Pieces::Pawn({i, yPos})));

}