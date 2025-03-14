#include "Players/RealPlayer.h"

namespace chess {

Position RealPlayer::askPosition() const {
    std::string input;

    while (true) {
        try {
            std::cout << "Select position: \n";
            std::cin >> input;

            return Position(input);

        } catch (const std::invalid_argument &e) { std::cerr << "Invalid position. Try again.\n"; }
    }
}

} // namespace chess