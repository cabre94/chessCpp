#pragma once

#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Positions/Position.h"
#include "Types.h"

namespace chess {

class Board;

enum State { CHECK, CHECKMATE, NORMAL }; // TODO

class Piece {
public:
    Piece(PlayerID player_id_, std::string name_, std::string symbol_, Position pos_)
        : player_id(player_id_), name(name_), symbol(symbol_), pos(pos_) {}
    virtual ~Piece() {}

    Piece(const Piece &) = delete;            // Copy constructor
    Piece &operator=(const Piece &) = delete; // Copy assignment
    Piece(Piece &&) = delete;                 // Move constructor
    Piece &operator=(Piece &&) = delete;      // Move assignment

    PlayerID getPlayerID() const { return player_id; };
    std::string getName() const { return name; };
    Position getPosition() const { return pos; }

    void setPosition(const Position &pos_) { pos = pos_; }

    virtual std::set<Position> getPossibleMoves(const Board *board) = 0;

    friend std::ostream &operator<<(std::ostream &os, const Piece &piece) {
        os << piece.symbol;
        return os;
    }

protected:
    const PlayerID player_id;
    const std::string name;
    const std::string symbol;
    Position pos;
};

} // namespace chess