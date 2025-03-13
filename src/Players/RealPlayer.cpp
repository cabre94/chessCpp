#include "Players/RealPlayer.h"

namespace chess {

Position RealPlayer::askPosition() const {
    std::string input;

    std::cout << "Select position: \n";
    std::cin >> input;

    return Position(input);
}

} // namespace chess