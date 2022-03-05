project(Julianne)
add_executable(Julianne main.cpp)
add_executable(Julianne Bitboard.cpp)
add_executable(Julianne Gameboard.cpp)
add_executable(Julianne Pieces/Piece.cpp)
add_executable(Julianne Pieces/Queen.cpp)
add_executable(Julianne Pieces/Rook.cpp)
add_executable(Julianne Pieces/Bishop.cpp)
add_executable(Julianne Pieces/King.cpp)
add_executable(Julianne Pieces/Knight.cpp)
add_executable(Julianne Pieces/Pawn.cpp)
add_executable(Julianne Pieces/NonPieces.cpp)


set_property(TARGET Julianne PROPERTY CXX_STANDARD 17)




set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
