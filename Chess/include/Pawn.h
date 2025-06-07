#pragma once
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite, int row, int col);
    virtual bool isValidMove(int destRow, int destCol, const Board& board) const override;
    virtual char getSymbol() const override;
};