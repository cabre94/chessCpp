#pragma once

#include <vector>

#include "Pieces/Piece.h"
#include "Types.h"

namespace chess {

class Player {
public:
    Player(PlayerID player_id_) : player_id(player_id_) {}
    virtual ~Player() {};

    // std::vector<Piece *> &getPieces() { return pieces; }

    virtual Position askPosition() const = 0;

    Position selectPiece(const std::vector<Piece *> pieces);

    PlayerID getPlayerID() const { return player_id; }

protected:
    const PlayerID player_id;

    // std::vector<Piece *> pieces;
};

} // namespace chess