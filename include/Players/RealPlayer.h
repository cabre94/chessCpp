#pragma once

#include "Players/Player.h"

namespace chess {

class RealPlayer : public Player {
public:
    RealPlayer(PlayerID player_id_) : Player(player_id_) {}
    ~RealPlayer() {}

    Position askPosition() const override;
};

} // namespace chess