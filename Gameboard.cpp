
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

	uint8_t yPos = (color == Color::White ? 0 : 7);
	teamBitBoard = 0x00000000000000FF;
	teamBitBoard <<= yPos;


	//Since we can't list initialize unqiue pointers
	std::array<Piece*, 8> tmpArr {{
		new Pieces::King(color, {4, yPos}),
		new Pieces::Queen(color, {3, yPos}),
		new Pieces::Rook(color, {0, yPos}),
		new Pieces::Rook(color, {7, yPos}),
		new Pieces::Bishop(color, {2, yPos}),
		new Pieces::Bishop(color, {5, yPos}),
		new Pieces::Knight(color, {6, yPos}),
		new Pieces::Knight(color, {1, yPos}),
	}};

	for (Piece* ptr : tmpArr)
		pieceList.push_back(PiecePtr(ptr));

	yPos = (color == Color::White ? 1 : 6);
	for (uint8_t i = 0; i < 8; i++)
		pieceList.push_back(PiecePtr(new Pieces::Pawn(color, {i, yPos})));

}

Bitboard GameBoard::getColorBoard(Color color) const {
	return color == Color::Black ? black.teamBitBoard : white.teamBitBoard;
}

//Note: NEEDS to be changed
void GameBoard::movePiece(Pos start, Pos end) {
	Piece* piece = board[start.column][start.row];

	//Mark the square from the starting piece pos empty
	if (piece->color() == Color::Black) {
		black.teamBitBoard &= ~start.asBitBoard();
		black.teamBitBoard |= end.asBitBoard();

		white.teamBitBoard &= ~end.asBitBoard();
	} else {
		white.teamBitBoard &= ~start.asBitBoard();
		white.teamBitBoard |= end.asBitBoard();

		black.teamBitBoard &= ~end.asBitBoard();
	}


	board[end.column][end.row] = board[start.column][start.row];
	board[start.column][start.row] = nullptr;
}