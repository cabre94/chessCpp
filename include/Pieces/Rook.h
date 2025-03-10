#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Rook : public Piece {
public:
    Rook(PlayerID player_id_, Position pos_)
        : Piece(player_id_, ROOK_NAME,
                (player_id_ == WHITE) ? ROOK_WHITE_SYMBOL : ROOK_BLACK_SYMBOL, pos_) {}
    ~Rook() {}

    std::set<Position> getPossibleMoves(const Board *board) const override {
        (void) board;
        std::set<Position> validMoves;
        // validMoves = board->getValidMoves(from, ROOK); // TODO
        return validMoves;
    }
};

} // namespace chess