#pragma once

#include <cassert>
#include <string>

#include "Boards/Board.h"
#include "Pieces/Piece.h"
#include "Positions/Position.h"

namespace chess {

class ChessBoard : public Board {
public:
    ChessBoard();
    ~ChessBoard();

    void printBoard() const override;
    void placePieces(const std::vector<Piece *> &v_pieces) override;

    std::set<Position> getParallelMoves(const Position &pos,
                                        const PlayerID player_id) const override;
    std::set<Position> getDiagonalMoves(const Position &pos,
                                        const PlayerID player_id) const override;
    std::set<Position> getLShapeMoves(const Position &pos, const PlayerID player_id,
                                      const std::vector<uint16_t> &deltas) const override;
    std::set<Position> getFordwardMoves(const Position &pos, const PlayerID player_id,
                                        const std::vector<int16_t> &forward_dir,
                                        bool first = false) const override;
    std::set<Position> getOneStepMoves(const Position &pos,
                                       const PlayerID player_id) const override;
    std::set<Position> getAllDirectionMoves(const Position &pos,
                                            const PlayerID player_id) const override;

    static const uint32_t N_ROW = 8;
    static const uint32_t N_COL = 8;

protected:
    void clearBoard();

    bool validIdxs(uint32_t r, uint32_t c) const { return r < N_ROW && c < N_COL; }
    bool validPos(const Position &pos) const { return validIdxs(pos[1], pos[0]); }

    Piece *getPiece(const Position &pos) override {
        if (!validPos(pos))
            throw std::invalid_argument("ChessBoard::getPiece - Invalid position");
        return pieces[pos[1]][pos[0]];
    }
    void setPiece(const Position &pos, Piece *piece) override {
        if (!validPos(pos))
            throw std::invalid_argument("ChessBoard::setPiece - Invalid position");
        // assert(pieces[pos[1]][pos[0]] == nullptr);

        if (piece != nullptr)
            piece->setPosition(pos);    // Update pos field on piece
        pieces[pos[1]][pos[0]] = piece; // Update pos on board representation
    }

private:
    Piece *pieces[N_ROW][N_COL];
};

} // namespace chess