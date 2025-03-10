#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "Pieces/Piece.h"
#include "Positions/Position.h"
#include "Types.h"

namespace chess {

class Piece;

class Board {
public:
    Board();
    virtual ~Board() {}

    Board(const Board &) = default;            // Copy constructor
    Board &operator=(const Board &) = default; // Copy assignment
    Board(Board &&) = default;                 // Move constructor
    Board &operator=(Board &&) = default;      // Move assignment

    virtual void printBoard() const = 0;
    // virtual void printPosAndPieces() const = 0;
    // virtual std::set<Position> getValidMoves(Position pos) const = 0; // TODO Sacar esto

    // Aca deberian poner los metodos que dan las posiciones validas
    virtual std::set<Position> getDiagonalMoves(const Position &pos,
                                                const PlayerID player_id) const = 0;
    virtual std::set<Position> getParallelMoves(const Position &pos,
                                                const PlayerID player_id) const = 0;
    virtual std::set<Position> getLShapeMoves(const Position &pos, const PlayerID player_id,
                                              const std::vector<uint16_t> &deltas) const = 0;
    virtual std::set<Position> getFordwardMoves(const Position &pos, const PlayerID player_id,
                                                const std::vector<int16_t> &forward_dir,
                                                bool first = false) const = 0;
    virtual std::set<Position> getOneStepMoves(const Position &pos,
                                               const PlayerID player_id) const = 0;
    virtual std::set<Position> getAllDirectionMoves(const Position &pos,
                                                    const PlayerID player_id) const = 0;

    // virtual bool makeMove(Position from, Position to) = 0;

    // virtual void createPices(const char c = 'n') = 0;

#if 0
    bool askWinner() const { return gameEnded; }         // TODO move to Game class
    bool isWhiteInCheck() const { return whiteInCheck; } // TODO move to Game class
    bool isBlackInCheck() const { return blackInCheck; } // TODO move to Game class

    void addPlayerPieces(std::vector<Piece *> &player_pieces);
#endif

protected:
#if 0
    bool stringInSet(const std::set<std::string> &set, const std::string &str) const;

    // Necesito acceso a las piezas de todos para chequear
    std::vector<std::vector<Piece *> *> all_pieces;

    std::map<Position, Piece *> whitePieces; // TODO move to Game class
    std::map<Position, Piece *> blackPieces; // TODO move to Game class

    std::set<Position> allWhiteMoves; // TODO move to Game class
    std::set<Position> allBlackMoves; // TODO move to Game class

    // Position whiteKingPos, blackKingPos; // TODO: Sacar esto

    uint64_t turn = 0;               // TODO move to Game class
    bool gameEnded;                  // TODO move to Game class
    bool whiteInCheck, blackInCheck; // TODO: Sacar esto
#endif
};

} // namespace chess