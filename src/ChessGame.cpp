#include <algorithm>

#include "Boards/Board.h"
#include "Boards/ChessBoard.h"
#include "Pieces/Bishop.h"
#include "Pieces/Champion.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Magician.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Positions/Position.h"

#include "ChessGame.h"

namespace chess {

ChessGame::ChessGame() {
    std::cout << "Choose chess variant\n";
    std::cout << "n: Normal Chess game\n";
    std::cout << "b: ButterflyChess - Normal board chess with butterfly distribution\n";
    std::cout << "p: PawnChess -Normal board chess with Pawn Game distribution\n";
    std::cout << "c: PawnChess -Normal board chess with Champion and Magician pieces\n";

    initializeGame();
}

ChessGame::~ChessGame() {
    // freePieces(w_pieces);
    // freePieces(b_pieces);
    for (auto &p : p_pieces)
        freePieces(p);

    delete board;
}

void ChessGame::play() {
    char c = 0;

    while (c != 'q') {
        // Print available pieces for current player

        // Ask player to choose a piece from options (consider potencial check)

        // Print available moves for selected piece

        // Ask player to choose a move from available moves

        // Check if selected move doesnt make self king check

        // make move

        // Check for check and checkmates

        //
        board->printBoard();

        std::cin >> c;
    }
}

void ChessGame::makeMove(const Position &from, const Position &to) {

    Piece *piece = board->makeMove(from, to);

    if (piece != nullptr)
        findFreePiece(piece);
}

void ChessGame::initializeGame() {
    createPieces();

    board = new ChessBoard();
    // board->placePieces(w_pieces);
    // board->placePieces(b_pieces);

    for (auto &p : p_pieces)
        board->placePieces(p);
    // freePieces(p);
}

void ChessGame::createPieces() {
    // Pawns
    for (uint32_t c = 0; c < ChessBoard::N_COL; ++c) {
        // w_pieces.push_back(new Pawn(PlayerID::WHITE, {1, c})); // White pawns
        // b_pieces.push_back(new Pawn(PlayerID::BLACK, {6, c})); // Black pawns

        p_pieces[WHITE].push_back(new Pawn(PlayerID::WHITE, {1, c})); // White pawns
        p_pieces[BLACK].push_back(new Pawn(PlayerID::BLACK, {6, c})); // Black pawns
    }

    // White pieces
    p_pieces[WHITE].push_back(new Rook(PlayerID::WHITE, {0, 0}));
    p_pieces[WHITE].push_back(new Knight(PlayerID::WHITE, {0, 1}));
    p_pieces[WHITE].push_back(new Bishop(PlayerID::WHITE, {0, 2}));
    p_pieces[WHITE].push_back(new Queen(PlayerID::WHITE, {0, 3}));
    p_pieces[WHITE].push_back(new King(PlayerID::WHITE, {0, 4}));
    p_pieces[WHITE].push_back(new Bishop(PlayerID::WHITE, {0, 5}));
    p_pieces[WHITE].push_back(new Knight(PlayerID::WHITE, {0, 6}));
    p_pieces[WHITE].push_back(new Rook(PlayerID::WHITE, {0, 7}));

    // Black p_pieces
    p_pieces[BLACK].push_back(new Rook(PlayerID::BLACK, {7, 0}));
    p_pieces[BLACK].push_back(new Knight(PlayerID::BLACK, {7, 1}));
    p_pieces[BLACK].push_back(new Bishop(PlayerID::BLACK, {7, 2}));
    p_pieces[BLACK].push_back(new Queen(PlayerID::BLACK, {7, 3}));
    p_pieces[BLACK].push_back(new King(PlayerID::BLACK, {7, 4}));
    p_pieces[BLACK].push_back(new Bishop(PlayerID::BLACK, {7, 5}));
    p_pieces[BLACK].push_back(new Knight(PlayerID::BLACK, {7, 6}));
    p_pieces[BLACK].push_back(new Rook(PlayerID::BLACK, {7, 7}));
}

void ChessGame::freePieces(std::vector<Piece *> &pieces) {
    for (Piece *p : pieces)
        delete p;
    pieces.clear();
}

void ChessGame::findFreePiece(Piece *piece) {
    // Try to remove from w_pieces or b_pieces
    // bool found = removeFromVector(w_pieces, piece) || removeFromVector(b_pieces, piece);

    bool found = false;
    for (auto &p : p_pieces)
        found |= removeFromVector(p, piece);

    if (!found)
        throw std::runtime_error("Error: piece not found in any of the vectors.");

    delete piece;
}

bool ChessGame::removeFromVector(std::vector<Piece *> &pieces, Piece *target) {
    auto it = std::find(pieces.begin(), pieces.end(), target);
    if (it != pieces.end()) {
        std::iter_swap(it, pieces.end() - 1);
        pieces.pop_back();
        return true;
    }
    return false;
}

} // namespace chess