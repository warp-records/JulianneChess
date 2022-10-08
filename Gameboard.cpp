
#include "Gameboard.hpp"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <cassert>

GameBoard::GameBoard() {
	board.fill({});

	for (auto const& piece : black.pieceList)
		board[piece->getPos().column][piece->getPos().row] = piece.get();
	for (auto const& piece : white.pieceList)
		board[piece->getPos().column][piece->getPos().row] = piece.get();
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

	teamBitBoard = color == Color::Black ? 
			0xFFFF000000000000 : 0x000000000000FFFF;

	uint8_t yPos = (color == Color::Black ? 7 : 0);
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
		pieceList.push_back(std::unique_ptr<Piece>(ptr));

	yPos = (color == Color::Black ? 6 : 1);
	for (uint8_t i = 0; i < 8; i++)
		pieceList.push_back(std::unique_ptr<Piece>(new Pieces::Pawn(color, {i, yPos})));
}

Bitboard GameBoard::getColorBoard(Color color) const {
	return color == Color::Black ? black.teamBitBoard : white.teamBitBoard;
}

//For some reason, this is getting called with
//the same start and end position somewhere...
void GameBoard::movePiece(Pos start, Pos end) {
	//Invalidate future moves if a move was undone
	//and a new move was made from that position
	bool repeatMove = moveHistory.size() > 0 &&
		(start == currMove->start || end == currMove->end);

	if (!repeatMove && currMove != moveHistory.end()) {

		moveHistory.erase(currMove+1, moveHistory.end());
	}

	//currMove++;

	Piece* piece = getSquare(start);

	//Handle castle
	if (piece->getType() == PieceType::King && 
		std::abs(start.column - end.column) > 1) {

		//Kingside castle if king goes to column 6
		if (end.column == 6)
			movePiece({7, start.row}, {5, start.row});
		else
			movePiece({0, start.row}, {3, start.row});
	}

	//Castle must move King last so that undoMove() can
	//detect castling
	MoveData moveData { start, end, piece->hasMoved, std::nullopt };

	//Handle en passe
	if (piece->getType() == PieceType::Pawn && 
		std::abs(start.column - end.column) == 1 && !squareOccupied(end)) {
		bool movesUp = piece->getColor() == Color::White;

		Pos capturedSquare = movesUp ? 
			Pos{end.column, uint8_t (end.row - 1)} : Pos{end.column, uint8_t (end.row + 1)};

		moveData.removedPiece.emplace(getSquare(capturedSquare));
		getSquare(capturedSquare) = nullptr;
	}


	if (squareOccupied(end)) 
		moveData.removedPiece.emplace(getSquare(end));

	bool futureHistory = currMove != moveHistory.end();

	if (!repeatMove)	
		moveHistory.push_back(moveData);

	currMove = (futureHistory ? currMove+1 : moveHistory.end());

	piece->setPos(end);
	piece->hasMoved = true;

	//Mark the square from the starting piece pos empty
	if (piece->getColor() == Color::Black) {
		black.teamBitBoard &= ~start.asBitBoard();
		black.teamBitBoard |= end.asBitBoard();

		white.teamBitBoard &= ~end.asBitBoard();
	} else {
		white.teamBitBoard &= ~start.asBitBoard();
		white.teamBitBoard |= end.asBitBoard();

		black.teamBitBoard &= ~end.asBitBoard();
	}

	getSquare(end) = getSquare(start);
	getSquare(start) = nullptr;
}

//TODO: add support for pawn promotions
void GameBoard::undoMove() {

	if (moveHistory.size() == 0)
		throw std::exception();

	currMove--;

	MoveData lastMove = *currMove;

	Piece* piece = getSquare(lastMove.end);
	getSquare(lastMove.start) = piece;
	getSquare(lastMove.end) = nullptr;

	piece->setPos(lastMove.start);
	piece->hasMoved = lastMove.hasMoved;

	Team& teamData = piece->getColor() == Color::Black ? black : white;

	teamData.teamBitBoard &= ~lastMove.end.asBitBoard();
	teamData.teamBitBoard |= lastMove.start.asBitBoard();

	//You gotta alter this pawn promotions
	if (lastMove.removedPiece.has_value()) {
		Piece* capturedPiece = lastMove.removedPiece.value();
		getSquare(capturedPiece->getPos()) = capturedPiece;

		Team& enemyData = piece->getColor() == Color::Black ? white : black;
		enemyData.teamBitBoard |= capturedPiece->getPos().asBitBoard();
	}

	if (piece->getType() == PieceType::King &&
		std::abs(lastMove.start.column - lastMove.end.column) > 1) {

		undoMove();
	}
}

void GameBoard::redoMove() {
	if (currMove == moveHistory.end())
		throw std::exception();

	movePiece(currMove->start, currMove->end);
}

bool squareOccupied(Pos pos);

std::ostream& operator<<(std::ostream& os, GameBoard const& gameBoard) {
	std::unordered_map<PieceType, char> pieceSymbolMap {
		{ PieceType::King, 'k' },
		{ PieceType::Queen, 'q'},
		{ PieceType::Rook, 'r' },
		{ PieceType::Bishop, 'b' },
		{ PieceType::Knight, 'n' },
		{ PieceType::Pawn, 'p' }
	};

	for (int row = 7; row >= 0; row--) {
		os << std::to_string(row + 1) << "    ";

		for (int col = 0; col <= 7; col++) {
			char symbol;

			if (gameBoard.squareOccupied({(uint8_t) col, (uint8_t) row})) {
				Piece const* piece = &gameBoard.getPiece({(uint8_t) col, (uint8_t) row});
				symbol = pieceSymbolMap[piece->getType()];

				if (piece->getColor() == Color::White) 
					symbol = std::toupper(symbol);
			} else {
				symbol = '0';
			}

			os << symbol << ' ';
		}

		os << '\n';
	}

	os << "\n     ";

	for (int col = 0; col <= 7; col++)
		os << char ('A' + col) << ' ';

	os << '\n';

	return os;
}