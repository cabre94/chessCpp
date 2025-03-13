#include "Players/Player.h"

namespace chess {

// Player::~Player() {
//     Piece *piece;

//     while (!pieces.empty()) {
//         piece = pieces.back();
//         pieces.pop_back();
//         delete piece;
//     }
// }

Piece *Player::selectPiece(const std::vector<Piece *> pieces) {
    while (true) {
        Position pos = askPosition(); // Ask the user for a position.

        // Iterate through the vector to see if any piece has that position.
        for (Piece *piece : pieces) {
            if (piece->getPosition() == pos)
                return piece;
        }

        std::cout << "No piece at that position. Please try again." << std::endl;
    }
}

Position Player::selectMove(const std::set<Position> &moves) {
    while (true) {
        // Ask the user for a position.
        Position pos = askPosition(); // Assumes askPosition() returns a Position.

        for (const Position &move : moves) { // Search for the position in the set.
            if (move == pos)
                return move;
        }

        std::cout << "Invalid move. Please try again." << std::endl;
    }
}

} // namespace chess