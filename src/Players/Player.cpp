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

Position Player::selectPiece(const std::vector<Piece *> pieces) {
    while (true) {
        Position pos = askPosition(); // Ask the user for a position.

        // Iterate through the vector to see if any piece has that position.
        for (const Piece *piece : pieces) {
            if (piece->getPosition() == pos)
                return pos;
        }

        std::cout << "No piece at that position. Please try again." << std::endl;
    }
}

} // namespace chess