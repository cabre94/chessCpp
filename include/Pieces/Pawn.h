#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Pawn : public Piece {
public:
    Pawn(PlayerID player_id_, Position pos_)
        : Piece(player_id_, PAWN_NAME,
                (player_id_ == WHITE) ? PAWN_WHITE_SYMBOL : PAWN_BLACK_SYMBOL, pos_) {}
    ~Pawn() {}

    std::set<Position> getPossibleMoves(const Board *board) const override {
        (void) board;
        std::set<Position> validMoves;
        // validMoves = board->getValidMoves(from, PAWN); // TODO
        return validMoves;
    }
};

} // namespace chess