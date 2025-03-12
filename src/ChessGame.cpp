#include "ChessGame.h"
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
    freePieces(w_pieces);
    freePieces(b_pieces);

    delete board;
}

void ChessGame::play() {
    char c = 0;

    while (c != 'q') {
        board->printBoard();

        std::cin >> c;
    }
}

void ChessGame::initializeGame() {
    createPieces();

    board = new ChessBoard();
    board->placePieces(w_pieces);
    board->placePieces(b_pieces);
}

void ChessGame::createPieces() {
    // Pawns
    for (uint32_t c = 0; c < ChessBoard::N_COL; ++c) {
        w_pieces.push_back(new Pawn(PlayerID::WHITE, {1, c})); // White pawns
        b_pieces.push_back(new Pawn(PlayerID::BLACK, {6, c})); // Black pawns
    }

    // White pieces
    w_pieces.push_back(new Rook(PlayerID::WHITE, {0, 0}));
    w_pieces.push_back(new Knight(PlayerID::WHITE, {0, 1}));
    w_pieces.push_back(new Bishop(PlayerID::WHITE, {0, 2}));
    w_pieces.push_back(new Queen(PlayerID::WHITE, {0, 3}));
    w_pieces.push_back(new King(PlayerID::WHITE, {0, 4}));
    w_pieces.push_back(new Bishop(PlayerID::WHITE, {0, 5}));
    w_pieces.push_back(new Knight(PlayerID::WHITE, {0, 6}));
    w_pieces.push_back(new Rook(PlayerID::WHITE, {0, 7}));

    // Black pieces
    b_pieces.push_back(new Rook(PlayerID::BLACK, {7, 0}));
    b_pieces.push_back(new Knight(PlayerID::BLACK, {7, 1}));
    b_pieces.push_back(new Bishop(PlayerID::BLACK, {7, 2}));
    b_pieces.push_back(new Queen(PlayerID::BLACK, {7, 3}));
    b_pieces.push_back(new King(PlayerID::BLACK, {7, 4}));
    b_pieces.push_back(new Bishop(PlayerID::BLACK, {7, 5}));
    b_pieces.push_back(new Knight(PlayerID::BLACK, {7, 6}));
    b_pieces.push_back(new Rook(PlayerID::BLACK, {7, 7}));
}

void ChessGame::freePieces(std::vector<Piece *> &pieces) {
    for (Piece *p : pieces)
        delete p;
    pieces.clear();
}

} // namespace chess