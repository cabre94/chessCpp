#pragma once

#include <vector>

#include "Pieces/Piece.h"
#include "Types.h"

namespace chess {

class Player {
public:
    Player(PlayerID player_id_) : player_id(player_id_) {}
    virtual ~Player() {};

    Piece *selectPiece(const std::vector<Piece *> pieces);
    Position selectMove(const std::set<Position> &moves);

    PlayerID getPlayerID() const { return player_id; }

protected:
    virtual Position askPosition() const = 0;
    const PlayerID player_id;
};

} // namespace chess