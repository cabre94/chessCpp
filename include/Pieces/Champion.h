#pragma once

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

namespace chess {

class Champion : public Piece {
public:
    Champion(PlayerID player_id_, Position pos_)
        : Piece(player_id_, CHAMPION_NAME,
                (player_id_ == WHITE) ? CHAMPION_WHITE_SYMBOL : CHAMPION_BLACK_SYMBOL, pos_) {}
    ~Champion() {}

    std::set<Position> getPossibleMoves(const Board *board) override {
        (void) board;
        std::set<Position> validMoves;
        // validMoves = board->getValidMoves(pos, CHAMPION); // TODO
        return validMoves;
    }
};

} // namespace chess