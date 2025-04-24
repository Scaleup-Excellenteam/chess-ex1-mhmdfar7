#pragma once
#include "Piece.h"
#include <string>

class Board {
private:
    Piece* squares[8][8];

public:
    Board(const std::string& boardStr);
    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);

    Piece* getPiece(int row, int col) const;
    bool isKingInCheck(bool isWhite) const;
    void makeMove(int srcRow, int srcCol, int destRow, int destCol);
};