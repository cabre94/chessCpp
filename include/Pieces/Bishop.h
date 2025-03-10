#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Bishop : public Piece {
public:
    Bishop(PlayerID player_id_, Position pos_)
        : Piece(player_id_, BISHOP_NAME,
                (player_id_ == WHITE) ? BISHOP_WHITE_SYMBOL : BISHOP_BLACK_SYMBOL, pos_) {}
    ~Bishop() {}

    std::set<Position> getPossibleMoves(const Board *board) override {
        // (void) board;
        // std::set<Position> validMoves;

        // // validMoves = board->getValidMoves(pos, BISHOP); // TODO

        // return validMoves;
        return board->getDiagonalMoves(pos, player_id);
    }
};

} // namespace chess