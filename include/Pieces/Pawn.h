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

    std::set<Position> getPossibleMoves(const Board *board) override {
        // (void) board;
        // std::set<Position> validMoves;
        // // validMoves = board->getValidMoves(from, PAWN); // TODO
        // return validMoves;
        std::vector<int16_t> forward_dir;
        if (player_id == WHITE)
            forward_dir = {1, 0};
        else
            forward_dir = {-1, 0};

        std::set<Position> validMoves =
            board->getFordwardMoves(pos, player_id, forward_dir, first_move);

        first_move = false;
        return validMoves;
    }

    bool first_move = true;
};

} // namespace chess