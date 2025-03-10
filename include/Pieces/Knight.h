#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Knight : public Piece {
public:
    Knight(PlayerID player_id_, Position pos_)
        : Piece(player_id_, KNIGHT_NAME,
                (player_id_ == WHITE) ? KNIGHT_WHITE_SYMBOL : KNIGHT_BLACK_SYMBOL, pos_) {}
    ~Knight() {}

    std::set<Position> getPossibleMoves(const Board *board) const override {
        // (void) board;
        // std::set<Position> validMoves;
        // // validMoves = board->getValidMoves(pos_, KNIGHT); // TODO
        // return validMoves;
        return board->getLShapeMoves(pos, player_id, {1, 2});
    }
};

} // namespace chess