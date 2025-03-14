#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include "Boards/Board.h"
#include "Boards/ChessBoard.h"
#include "ChessGame.h"
#include "Pieces/Utils.h"
#include "Positions/Position.h"

static const std::filesystem::path projectDir =
    std::filesystem::absolute(std::filesystem::path(__FILE__)).parent_path();

class TestChessGame : public chess::ChessGame {
public:
    chess::Piece *getPiece(const chess::Position &pos) { return board->getPiece(pos); }

    std::set<chess::Position> getPossibleMoves(const chess::Position &pos) {
        return getPiece(pos)->getPossibleMoves(board);
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
            chess::Position pos(r, c);

            EXPECT_EQ(game.getPiece(pos)->getPlayerID(), exp_player_id);
            EXPECT_EQ(game.getPiece(pos)->getPosition(), chess::Position(pos));
            EXPECT_EQ(game.getPossibleMoves(pos), getExpMovesOnNewBoard(r, c));

            if (r == 0 || r == 7) {
                EXPECT_EQ(game.getPiece(pos)->getName(), exp_names[c]);
            } else { // row of pawns
                EXPECT_EQ(game.getPiece(pos)->getName(), chess::PAWN_NAME);
            }
        }
    }
}

TEST(ChessGame, makeMove) {
    TestChessGame game;

    std::cout << "Initial board:" << std::endl;
    game.printBoard();

    // Get file with moves
    static const std::string movesFilePath = (projectDir / "data" / "moves.txt").lexically_normal();
    std::ifstream movesFile(movesFilePath);
    ASSERT_TRUE(movesFile.is_open()) << "Cannot open moves.txt";

    std::string fromStr, toStr;
    while (movesFile >> fromStr >> toStr) {
        chess::Position from(fromStr), to(toStr); // Create positions

        std::cout << "Move from" << fromStr << " to " << toStr << std::endl;

        game.makeMove(from, to);
        game.printBoard();
    }

    movesFile.close();
}

TEST(ChessGame, Kasparov_immortal) {
    TestChessGame game;

    std::cout << "Initial board:" << std::endl;
    game.printBoard();

    // Get file with moves
    static const std::string movesFilePath =
        (projectDir / "data" / "Kasparov's_immortal.txt").lexically_normal();
    std::ifstream movesFile(movesFilePath);
    ASSERT_TRUE(movesFile.is_open()) << "Cannot open moves.txt";

    std::string fromStr, toStr;
    while (movesFile >> fromStr >> toStr) {
        chess::Position from(fromStr), to(toStr); // Create positions

        std::cout << "Move from" << fromStr << " to " << toStr << std::endl;

        game.makeMove(from, to);
        game.printBoard();
    }

    movesFile.close();
}

//
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