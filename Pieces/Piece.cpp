#include <cstdint>
#include "Piece.hpp"

Color operator!(Color color) {
	return color == Color::Black ? Color::White : Color::Black;
}