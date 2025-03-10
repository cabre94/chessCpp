#include "Boards/ChessBoard.h"
#include "Boards/Utils.h"
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

// ChessBoard::ChessBoard(uint16_t nRow_, uint16_t nCol_) : nRow(nRow_), nCol(nCol_) {
ChessBoard::ChessBoard() : Board() {

#if 0
    switch (c){
        case 'n':
            initializePieces();
            break;
        case 'b':
            initializePiecesButterfly();
            break;
        case 'p':
            initializePiecesPawnGame();
            break;
        case 'c':
            initializePiecesChampionMagician();
            break;
        default:
            std::cout << "invalid input" << std::endl;  //! Deberia tirar una excepcion
            exit(1);
    }
#endif

    for (size_t r = 0; r < N_ROW; r++) {
        for (size_t c = 0; c < N_COL; c++) {
            pieces[r][c] = nullptr;
        }
    }
}

ChessBoard::~ChessBoard() {

    clearBoard();
    // delete [] positions;
}

void ChessBoard::printBoard() const {
    Piece *piece;

    // Row with letters indicating columns
    std::cout << "  ";
    for (char c = 'A'; c <= 'H'; ++c)
        std::cout << " " << c << "  ";
    std::cout << std::endl;

    // First line
    std::cout << " " << TOP_LEFT;
    for (uint32_t i = 0; i < N_COL - 1; ++i)
        std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << TOP_T;
    std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << TOP_RIGHT << std::endl;

    // Pieces
    for (uint32_t r = N_ROW; r >= 1; --r) {
        std::cout << r << VERTICAL;

        for (uint32_t c = 0; c < N_COL; ++c) {
            piece = pieces[r - 1][c];

            if (piece == nullptr)
                std::cout << "   " << VERTICAL;
            else
                std::cout << " " << *piece << " " << VERTICAL;
        }
        std::cout << r << std::endl;

        // print the grid lines
        if (r > 1) {
            std::cout << " " << LEFT_T;
            for (uint32_t i = 0; i < N_COL - 1; ++i)
                std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << CENTER;
            std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << RIGHT_T << std::endl;
        }
    }

    // Last line
    std::cout << " " << BOTTOM_LEFT;
    for (uint32_t i = 0; i < N_COL - 1; ++i)
        std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << BOTTOM_T;
    std::cout << HORIZONTAL << HORIZONTAL << HORIZONTAL << BOTTOM_RIGHT << std::endl;

    // Row with letters indicating columns
    std::cout << "  ";
    for (char c = 'A'; c <= 'H'; ++c)
        std::cout << " " << c << "  ";
    std::cout << std::endl;
}

std::set<Position> ChessBoard::getParallelMoves(const Position &pos,
                                                const PlayerID player_id) const {

    std::set<Position> moves;

    constexpr int32_t directions[4][2] = {
        {1, 0},  // Up
        {-1, 0}, // Down
        {0, 1},  // Right
        {0, -1}  // Left
    };

    // Get row and column of position (order of indexes are inverted on Position representation)
    uint32_t rr = pos[1];
    uint32_t cc = pos[0];

    int32_t dc, dr;
    uint32_t c, r;
    for (const auto &dir : directions) {
        dc = dir[0];
        dr = dir[1];

        c = cc + dc;
        r = rr + dr;

        while (validIdxs(r, c)) {
            // Check if there is a piece on position of idxs (r,c)
            if (pieces[r][c] != nullptr) {
                // check if the piece belongs to an opponent
                if (pieces[r][c]->getPlayerID() != player_id) {
                    moves.insert(Position(r, c));
                }
                break; // Stop searching at this direction, as a piece is found
            }

            // There is no piece on current position, so we keep moving on this direction
            moves.insert(Position(r, c));

            c += dc;
            r += dr;
        }
    }

    return moves;
}

std::set<Position> ChessBoard::getDiagonalMoves(const Position &pos,
                                                const PlayerID player_id) const {
    std::set<Position> moves;

    constexpr int32_t directions[4][2] = {
        {1, 1},  // Up - Right
        {1, -1}, // Up - Left
        {-1, 1}, // Down - Right
        {-1, -1} // Down - Left
    };

    // Get row and column of position (order of indexes are inverted on Position representation)
    uint32_t rr = pos[1];
    uint32_t cc = pos[0];

    int32_t dc, dr;
    uint32_t c, r;
    for (const auto &dir : directions) {
        dc = dir[0];
        dr = dir[1];

        c = cc + dc;
        r = rr + dr;

        while (validIdxs(r, c)) {
            // Check if there is a piece on position of idxs (r,c)
            if (pieces[r][c] != nullptr) {
                // check if the piece belongs to an opponent
                if (pieces[r][c]->getPlayerID() != player_id) {
                    moves.insert(Position(r, c));
                }
                break; // Stop searching at this direction, as a piece is found
            }

            // There is no piece on current position, so we keep moving on this direction
            moves.insert(Position(r, c));

            c += dc;
            r += dr;
        }
    }

    return moves;
}

std::set<chess::Position> ChessBoard::getLShapeMoves(const Position &pos, const PlayerID player_id,
                                                     const std::vector<uint16_t> &deltas) const {
    if (deltas.size() != 2) {
        throw std::invalid_argument("getLShapeMoves requiere exactamente dos valores en deltas.");
    }

    std::set<chess::Position> moves;

    int32_t rr = pos[1];
    int32_t cc = pos[0];

    int32_t drr = static_cast<int32_t>(deltas[1]);
    int32_t dcc = static_cast<int32_t>(deltas[0]);

    // Generamos las 8 posibles orientaciones del movimiento
    std::vector<std::array<int32_t, 2>> directions = {{drr, dcc},   {dcc, drr},  {-drr, dcc},
                                                      {-dcc, drr},  {drr, -dcc}, {dcc, -drr},
                                                      {-drr, -dcc}, {-dcc, -drr}};

    int32_t dc, dr;
    uint32_t c, r;
    for (const auto &dir : directions) {
        dc = dir[0];
        dr = dir[1];

        c = cc + dc;
        r = rr + dr;

        if (validIdxs(r, c)) {
            if (pieces[r][c] == nullptr || pieces[r][c]->getPlayerID() != player_id)
                moves.insert(chess::Position(r, c));
        }
    }

    return moves;
}

std::set<Position> ChessBoard::getFordwardMoves(const Position &pos, const PlayerID player_id,
                                                const std::vector<int16_t> &forward_dir,
                                                bool first) const {

    std::set<chess::Position> moves;

    if (forward_dir.size() != 2)
        throw std::invalid_argument("getForwardMoves forward_dir size != 2");

    int32_t dr = static_cast<int32_t>(forward_dir[0]);
    int32_t dc = static_cast<int32_t>(forward_dir[1]);

    // Get row and column of current position
    uint32_t rr = pos[1];
    uint32_t cc = pos[0];

    // Forward movement (no capture)
    uint32_t max_steps = first ? 2 : 1;
    uint32_t r, c;
    for (uint32_t step = 1; step <= max_steps; ++step) {
        r = rr + step * dr;
        c = cc + step * dc;

        if (!validIdxs(r, c) || pieces[r][c] != nullptr) {
            break; // Cant move forward
        }

        moves.insert(Position(r, c));
    }

    // Diagonal Captures
    constexpr int32_t diagonal_offsets[2] = {-1, 1}; // Relative diagonal movements

    for (const int32_t &offset : diagonal_offsets) {
        r = rr + dr;
        c = cc + offset; // Move to the left or right

        if (validIdxs(r, c) && pieces[r][c] != nullptr) {
            if (pieces[r][c]->getPlayerID() != player_id)
                moves.insert(Position(r, c)); // Only if there is an enemy piece
        }
    }

    // TODO: Might have to complex logic if forward direction is on diagonal

    return moves;
}

std::set<Position> ChessBoard::getOneStepMoves(const Position &pos,
                                               const PlayerID player_id) const {

    std::set<chess::Position> moves;

    // Get row and column of current position
    uint32_t rr = pos[1];
    uint32_t cc = pos[0];

    uint32_t c, r;
    for (int32_t dc = -1; dc <= 1; ++dc) {
        for (int32_t dr = -1; dr <= 1; ++dr) {
            if (dc == 0 && dr == 0)
                continue;

            c = cc + dc;
            r = rr + dr;

            if (validIdxs(r, c)) {
                if (pieces[r][c] == nullptr || pieces[r][c]->getPlayerID() != player_id)
                    moves.insert(chess::Position(r, c));
            }
        }
    }

    return moves;
}

std::set<Position> ChessBoard::getAllDirectionMoves(const Position &pos,
                                                    const PlayerID player_id) const {
    std::set<Position> moves = getParallelMoves(pos, player_id);
    std::set<Position> diagonal_moves = getDiagonalMoves(pos, player_id);

    moves.insert(diagonal_moves.begin(), diagonal_moves.end());

    return moves;
}

void ChessBoard::clearBoard() {

    for (uint32_t r = 0; r < N_ROW; ++r) {
        for (uint32_t c = 0; c < N_COL; ++c) {
            if (pieces[r][c] != nullptr) {
                delete pieces[r][c];
                pieces[r][c] = nullptr;
            }
        }
    }
}

void ChessBoard::initializePieces() {

    // Pawns
    for (uint32_t c = 0; c < N_COL; ++c) {
        pieces[1][c] = new Pawn(PlayerID::WHITE, {1, c}); // White pawns
        pieces[6][c] = new Pawn(PlayerID::BLACK, {6, c}); // Black pawns
    }

    // White pieces
    pieces[0][0] = new Rook(PlayerID::WHITE, {0, 0});
    pieces[0][1] = new Knight(PlayerID::WHITE, {0, 1});
    pieces[0][2] = new Bishop(PlayerID::WHITE, {0, 2});
    pieces[0][3] = new Queen(PlayerID::WHITE, {0, 3});
    pieces[0][4] = new King(PlayerID::WHITE, {0, 4});
    pieces[0][5] = new Bishop(PlayerID::WHITE, {0, 5});
    pieces[0][6] = new Knight(PlayerID::WHITE, {0, 6});
    pieces[0][7] = new Rook(PlayerID::WHITE, {0, 7});

    // Black pieces
    pieces[7][0] = new Rook(PlayerID::BLACK, {7, 0});
    pieces[7][1] = new Knight(PlayerID::BLACK, {7, 1});
    pieces[7][2] = new Bishop(PlayerID::BLACK, {7, 2});
    pieces[7][3] = new Queen(PlayerID::BLACK, {7, 3});
    pieces[7][4] = new King(PlayerID::BLACK, {7, 4});
    pieces[7][5] = new Bishop(PlayerID::BLACK, {7, 5});
    pieces[7][6] = new Knight(PlayerID::BLACK, {7, 6});
    pieces[7][7] = new Rook(PlayerID::BLACK, {7, 7});
}

bool ChessBoard::validIdxs(uint32_t r, uint32_t c) const { return r < N_ROW && c < N_COL; }

bool ChessBoard::validPos(const Position &pos) const { return validIdxs(pos[1], pos[0]); }

// Position ChessBoard::pos2string(int x, int y){
Position ChessBoard::idx2Pos(const uint32_t r, const uint32_t c) const {
    if (validIdxs(r, c))
        throw std::out_of_range("ChessBoard::idx2Pos: Invalid indexes");

    return Position(r, c);
}

////////////////////////////////////////////////////////////////

#if 0
void ChessBoard::createPices(const char c) {
    switch (c) {
        case 'n':
            initializePieces();
            break;
        // case 'b':
        //     initializePiecesButterfly();
        //     break;
        // case 'p':
        //     initializePiecesPawnGame();
        //     break;
        // case 'c':
        //     initializePiecesChampionMagician();
        //     break;
        default:
            std::cout << "invalid input" << std::endl; //! Deberia tirar una excepcion
            exit(1);
    }
}
#endif

#if 0
void ChessBoard::initializePiecesButterfly(){
    for(int i=0; i < 8; ++i)
        for(int j=0; j < 8; ++j)
            pieces[i][j] = nullptr;
    // Agrego los peones con la distribucion mariposa
    pieces[1][0] = new Pawn(WHITE);
    pieces[2][1] = new Pawn(WHITE);
    pieces[3][2] = new Pawn(WHITE);
    pieces[4][3] = new Pawn(WHITE);
    pieces[4][4] = new Pawn(WHITE);
    pieces[3][5] = new Pawn(WHITE);
    pieces[2][6] = new Pawn(WHITE);
    pieces[1][7] = new Pawn(WHITE);

    pieces[6][0] = new Pawn(BLACK);
    pieces[5][1] = new Pawn(BLACK);
    pieces[4][2] = new Pawn(BLACK);
    pieces[3][3] = new Pawn(BLACK);
    pieces[3][4] = new Pawn(BLACK);
    pieces[4][5] = new Pawn(BLACK);
    pieces[5][6] = new Pawn(BLACK);
    pieces[6][7] = new Pawn(BLACK);
    

    // Agrego el resto de piezas blancas
    pieces[0][0] = new Rook(WHITE);
    pieces[0][1] = new Knight(WHITE);
    pieces[0][2] = new Bishop(WHITE);
    pieces[0][3] = new Queen(WHITE);
    pieces[0][4] = new King(WHITE);
    pieces[0][5] = new Bishop(WHITE);
    pieces[0][6] = new Knight(WHITE);
    pieces[0][7] = new Rook(WHITE);

    // Agrego las piezas negras
    pieces[7][0] = new Rook(BLACK);
    pieces[7][1] = new Knight(BLACK);
    pieces[7][2] = new Bishop(BLACK);
    pieces[7][3] = new Queen(BLACK);
    pieces[7][4] = new King(BLACK);
    pieces[7][5] = new Bishop(BLACK);
    pieces[7][6] = new Knight(BLACK);
    pieces[7][7] = new Rook(BLACK);

    whiteTurn = true;
    gameEnded = false;

    whiteKingPos = "E1";
    blackKingPos = "E8";

    updatePiecesPositions();

    updateAllValidMoves();

    updateGameState();
}
#endif

#if 0
void ChessBoard::initializePiecesPawnGame(){
    for(int i=0; i < 8; ++i)
        for(int j=0; j < 8; ++j)
            pieces[i][j] = nullptr;
    // Agrego los peones
    for(int j=0; j < 8; ++j){
        pieces[1][j] = new Pawn(WHITE);
        pieces[6][j] = new Pawn(BLACK);
    }

    // Agrego los peones extra para las blancas en esta distribucion
    pieces[2][1] = new Pawn(WHITE);
    pieces[2][2] = new Pawn(WHITE);
    pieces[2][5] = new Pawn(WHITE);
    pieces[2][6] = new Pawn(WHITE);

    pieces[3][2] = new Pawn(WHITE);
    pieces[3][3] = new Pawn(WHITE);
    pieces[3][4] = new Pawn(WHITE);
    pieces[3][5] = new Pawn(WHITE);

    // Agrego el resto de piezas blancas
    pieces[0][0] = new Rook(WHITE);
    pieces[0][1] = new Knight(WHITE);
    pieces[0][2] = new Bishop(WHITE);
    // pieces[0][3] = new Queen(WHITE);     // Saco la reina blanca
    pieces[0][4] = new King(WHITE);
    pieces[0][5] = new Bishop(WHITE);
    pieces[0][6] = new Knight(WHITE);
    pieces[0][7] = new Rook(WHITE);

    // Agrego las piezas negras
    pieces[7][0] = new Rook(BLACK);
    pieces[7][1] = new Knight(BLACK);
    pieces[7][2] = new Bishop(BLACK);
    pieces[7][3] = new Queen(BLACK);
    pieces[7][4] = new King(BLACK);
    pieces[7][5] = new Bishop(BLACK);
    pieces[7][6] = new Knight(BLACK);
    pieces[7][7] = new Rook(BLACK);

    whiteTurn = true;
    gameEnded = false;

    whiteKingPos = "E1";
    blackKingPos = "E8";

    updatePiecesPositions();

    updateAllValidMoves();

    updateGameState();
}
#endif

#if 0
void ChessBoard::initializePiecesChampionMagician(){
    for(int i=0; i < 8; ++i)
        for(int j=0; j < 8; ++j)
            pieces[i][j] = nullptr;
    // Agrego los peones
    for(int j=0; j < 8; ++j){
        pieces[1][j] = new Pawn(WHITE);
        pieces[6][j] = new Pawn(BLACK);
    }

    // Agrego el resto de piezas blancas
    pieces[0][0] = new Champion(WHITE);
    pieces[0][1] = new Magician(WHITE);
    pieces[0][2] = new Bishop(WHITE);
    pieces[0][3] = new Queen(WHITE);
    pieces[0][4] = new King(WHITE);
    pieces[0][5] = new Bishop(WHITE);
    pieces[0][6] = new Magician(WHITE);
    pieces[0][7] = new Champion(WHITE);

    // Agrego las piezas negras
    pieces[7][0] = new Champion(BLACK);
    pieces[7][1] = new Magician(BLACK);
    pieces[7][2] = new Bishop(BLACK);
    pieces[7][3] = new Queen(BLACK);
    pieces[7][4] = new King(BLACK);
    pieces[7][5] = new Bishop(BLACK);
    pieces[7][6] = new Magician(BLACK);
    pieces[7][7] = new Champion(BLACK);

    whiteTurn = true;
    gameEnded = false;

    whiteKingPos = "E1";
    blackKingPos = "E8";

    updatePiecesPositions();

    updateAllValidMoves();

    updateGameState();
}
#endif

} // namespace chess