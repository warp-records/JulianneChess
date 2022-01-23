project(Julianne)
add_executable(Julianne main.cpp)
add_executable(Julianne Pieces/Piece.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
