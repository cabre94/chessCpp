#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "Pieces/Bishop.h"
#include "Pieces/Champion.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Magician.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Positions/Position.h"

static chess::Position getRandomValidPosition() {
    uint32_t r = rand() % 8;
    uint32_t c = rand() % 8;

    return chess::Position(r, c);
}

TEST(Pieces, Getters) {
    srand((unsigned int) time(0));

    std::vector<chess::PlayerID> exp_player_id;
    std::vector<chess::Position> exp_pos;
    std::string exp_names[] = {chess::BISHOP_NAME, chess::CHAMPION_NAME, chess::KING_NAME,
                               chess::KNIGHT_NAME, chess::MAGICIAN_NAME, chess::PAWN_NAME,
                               chess::QUEEN_NAME,  chess::ROOK_NAME};

    // Generate random expected variables
    for (size_t i = 0; i < 8; ++i) {
        exp_player_id.push_back((chess::PlayerID)(rand() & 1));
        exp_pos.push_back(getRandomValidPosition());
    }

    // Generate pieces with random params
    chess::Piece *piece[] = {new chess::Bishop(exp_player_id[0], exp_pos[0]),
                             new chess::Champion(exp_player_id[1], exp_pos[1]),
                             new chess::King(exp_player_id[2], exp_pos[2]),
                             new chess::Knight(exp_player_id[3], exp_pos[3]),
                             new chess::Magician(exp_player_id[4], exp_pos[4]),
                             new chess::Pawn(exp_player_id[5], exp_pos[5]),
                             new chess::Queen(exp_player_id[6], exp_pos[6]),
                             new chess::Rook(exp_player_id[7], exp_pos[7])};

    for (size_t i = 0; i < 8; ++i) {
        ASSERT_EQ(piece[i]->getPlayerID(), exp_player_id[i]);
        ASSERT_EQ(piece[i]->getName(), exp_names[i]);
        ASSERT_EQ(piece[i]->getPosition(), exp_pos[i]);
    }

    // Free memory
    for (size_t i = 0; i < 8; ++i)
        delete piece[i];
}