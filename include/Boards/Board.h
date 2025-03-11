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

class Board {
public:
    Board();
    virtual ~Board() {}

    Board(const Board &) = default;            // Copy constructor
    Board &operator=(const Board &) = default; // Copy assignment
    Board(Board &&) = default;                 // Move constructor
    Board &operator=(Board &&) = default;      // Move assignment

    virtual void printBoard() const = 0;
    virtual void placePieces(const std::vector<Piece *> &v_pieces) = 0;

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
};

} // namespace chess