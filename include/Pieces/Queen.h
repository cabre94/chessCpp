#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Queen : public Piece {
public:
    Queen(PlayerID player_id_, Position pos_)
        : Piece(player_id_, QUEEN_NAME,
                (player_id_ == WHITE) ? QUEEN_WHITE_SYMBOL : QUEEN_BLACK_SYMBOL, pos_) {}
    ~Queen() {}

    std::set<Position> getPossibleMoves(const Board *board) override {
        // (void) board;
        // std::set<Position> validMoves;
        // // validMoves = board->getValidMoves(from, QUEEN); // TODO
        // return validMoves;
        return board->getAllDirectionMoves(pos, player_id);
    }
};

} // namespace chess