#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(bool isWhite, int row, int col);
    virtual bool isValidMove(int destRow, int destCol, const Board& board) const override;
    virtual char getSymbol() const override;
};