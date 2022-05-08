
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
		pieceList.push_back(PiecePtr(ptr));

	yPos = (color == Color::Black ? 6 : 1);
	for (uint8_t i = 0; i < 8; i++)
		pieceList.push_back(PiecePtr(new Pieces::Pawn(color, {i, yPos})));

}

Bitboard GameBoard::getColorBoard(Color color) const {
	return color == Color::Black ? black.teamBitBoard : white.teamBitBoard;
}

//Note: NEEDS to be changed
void GameBoard::movePiece(Pos start, Pos end) {
	Piece* piece = board[start.column][start.row];

	piece->setPos(end);

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


	board[end.column][end.row] = board[start.column][start.row];
	board[start.column][start.row] = nullptr;
}

/*
std::ostream& operator<<(std::ostream& os, GameBoard const& gameBoard) {
	std::string buff(64, ' ');

	std::unordered_map<PieceType, char> const pieceSymbolMap {
		{ PieceType::King, 'k' },
		{ PieceType::Queen, 'q'},
		{ PieceType::Rook, 'r' },
		{ PieceType::Bishop, 'b' },
		{ PieceType::Knight, 'n' },
		{ PieceType::Pawn, 'p' }
	};

	for (auto peice : black.pieceList) {
		buff[piece->getPos().column + 
			piece->getPos().row * 8] = pieceSymbolMap[peice->type];
	}

	for (auto peice : white.pieceList) {
		buff[piece->getPos().column + 
			piece->getPos().row * 8] = std::toupper(pieceSymbolMap[peice->type]);
	}

	return os << buff;
}*/

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

			if (gameBoard.squareOccupied({col, row})) {
				Piece const* piece = &gameBoard.getPiece({col, row});
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