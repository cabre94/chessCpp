#pragma once

#include <cstdlib>
#include <vector>

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Players/Player.h"

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
    void makeMove(const Position &from, const Position &to);

protected:
    void initializeGame();
    void createPieces();

    void freePieces(std::vector<Piece *> &pieces);
    void findFreePiece(Piece *piece);

    bool removeFromVector(std::vector<Piece *> &pieces, Piece *target);

    Board *board;

    // std::vector<Piece *> w_pieces;
    // std::vector<Piece *> b_pieces;

    std::vector<Piece *> p_pieces[MAX_NUM_PLAYERS];

private:
    void printPosOfPieces(const std::vector<Piece *> &pieces);

    Player *players[MAX_NUM_PLAYERS] = {0};
    uint32_t NUM_PLAYERS = MAX_NUM_PLAYERS;
};

} // namespace chess