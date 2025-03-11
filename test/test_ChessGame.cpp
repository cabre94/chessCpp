#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "Boards/Board.h"
#include "Boards/ChessBoard.h"
#include "ChessGame.h"
#include "Pieces/Bishop.h"
#include "Pieces/Champion.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Magician.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Positions/Position.h"

// static chess::Position getRandomValidPosition() {
//     uint32_t r = rand() % 8;
//     uint32_t c = rand() % 8;

//     return chess::Position(r, c);
// }

class TestChessGame : public chess::ChessGame {
public:
    // void testInitializePieces() { initializePieces(); }
    chess::Piece *getPiece(uint32_t r, uint32_t c) { return board->getPiece(r, c); }

    std::set<chess::Position> getPossibleMoves(uint32_t r, uint32_t c) {
        return getPiece(r, c)->getPossibleMoves(board);
    }

    void printBoard() { board->printBoard(); }
};

static std::set<chess::Position> getExpMovesOnNewBoard(uint32_t r, uint32_t c);

TEST(ChessGame, initializeGame) {
    chess::PlayerID exp_player_id = chess::WHITE;
    std::string exp_names[] = {chess::ROOK_NAME,   chess::KNIGHT_NAME, chess::BISHOP_NAME,
                               chess::QUEEN_NAME,  chess::KING_NAME,   chess::BISHOP_NAME,
                               chess::KNIGHT_NAME, chess::ROOK_NAME};

    TestChessGame game;

    // Pawns
    for (uint32_t r : {0, 1, 6, 7}) {
        if (r == 6)
            exp_player_id = chess::BLACK;

        for (uint32_t c = 0; c < chess::ChessBoard::N_COL; ++c) {
            EXPECT_EQ(game.getPiece(r, c)->getPlayerID(), exp_player_id);
            EXPECT_EQ(game.getPiece(r, c)->getPosition(), chess::Position(r, c));
            EXPECT_EQ(game.getPossibleMoves(r, c), getExpMovesOnNewBoard(r, c));

            if (r == 0 || r == 7) {
                EXPECT_EQ(game.getPiece(r, c)->getName(), exp_names[c]);
            } else { // row of pawns
                EXPECT_EQ(game.getPiece(r, c)->getName(), chess::PAWN_NAME);
            }
        }
    }
}

TEST(ChessGame, printBoard) {
    TestChessGame game;

    game.printBoard();
}

static std::set<chess::Position> getExpMovesOnNewBoard(uint32_t r, uint32_t c) {
    std::set<chess::Position> moves;

    if (r == 1) { // White pawns
        moves.insert({2, c});
        moves.insert({3, c});
    } else if (r == 6) { // Black pawns
        moves.insert({5, c});
        moves.insert({4, c});
    }

    std::vector<chess::Position> possibleMoves;
    if ((r == 0) && (c == 1 || c == 6)) { // White Knights
        possibleMoves = {{r + 2, c + 1}, {r + 2, c - 1}};
    } else if ((r == 7) && (c == 1 || c == 6)) { // Black Knights
        possibleMoves = {{r - 2, c + 1}, {r - 2, c - 1}};
    }

    for (const auto &pos : possibleMoves) {
        if (pos[0] < chess::ChessBoard::N_COL && pos[1] < chess::ChessBoard::N_ROW) {
            moves.insert(pos);
        }
    }

    return moves;
}