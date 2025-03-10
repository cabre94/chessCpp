#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class King : public Piece {
public:
    King(PlayerID player_id_, Position pos_)
        : Piece(player_id_, KING_NAME,
                (player_id_ == WHITE) ? KING_WHITE_SYMBOL : KING_BLACK_SYMBOL, pos_) {}
    ~King() {}

    std::set<Position> getPossibleMoves(const Board *board) const override {
        (void) board;
        std::set<Position> validMoves;
        // validMoves = board->getValidMoves(pos, KING); // TODO
        return validMoves;
    }
};

} // namespace chess