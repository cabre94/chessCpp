#pragma once

#include <cstdlib>
#include <vector>

#include "Boards/Board.h"
#include "Pieces/Piece.h"

namespace chess {

class ChessGame {
public:
    ChessGame();
    ~ChessGame();

    ChessGame(const ChessGame &) = default;            // Copy constructor
    ChessGame &operator=(const ChessGame &) = default; // Copy assignment
    ChessGame(ChessGame &&) = default;                 // Move constructor
    ChessGame &operator=(ChessGame &&) = default;      // Move assignment

    void play();

protected:
    void initializeGame();
    void createPieces();

    void freePieces(std::vector<Piece *> &pieces);

    Board *board;

    std::vector<Piece *> w_pieces;
    std::vector<Piece *> b_pieces;
};

} // namespace chess