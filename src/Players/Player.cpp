#include <cassert>

#include "Players/Player.h"

namespace chess {

Piece *Player::selectPiece(const std::vector<Piece *> pieces) {
    assert(!pieces.empty()); // TODO: add msg

    while (true) {
        Position pos = askPosition();

        // Iterate through the vector to see if any piece has that position.
        for (Piece *piece : pieces) {
            if (piece->getPosition() == pos)
                return piece;
        }

        std::cout << "No piece at that position. Please try again." << std::endl;
    }
}

Position Player::selectMove(const std::set<Position> &moves) {
    if (moves.empty())
        throw std::runtime_error("Player::selectMove - No available moves");

    while (true) {
        Position pos = askPosition();

        for (const Position &move : moves) { // Search for the position in the set.
            if (move == pos)
                return move;
        }

        std::cout << "Invalid move. Please try again." << std::endl;
    }
}

} // namespace chess