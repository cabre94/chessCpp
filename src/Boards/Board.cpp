#include "Boards/Board.h"

namespace chess {

Piece *Board::makeMove(const Position &from, const Position &to) {

    Piece *p_from = getPiece(from); // Get piece in "from" position
    Piece *p_to = getPiece(to);     // Get piece in "to" position

    setPiece(to, p_from);    // Set piece in "from" position to "to" position
    setPiece(from, nullptr); // Set nullptr in "from" Position

    return p_to; // Return piece originally in "to" position
}

} // namespace chess