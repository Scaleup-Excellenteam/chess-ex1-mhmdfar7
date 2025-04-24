#pragma once
#include <string>

class Board; // Forward declaration

class Piece {
protected:
    bool isWhite;
    int row;
    int col;

public:
    Piece(bool isWhite, int row, int col);
    virtual ~Piece() {}

    virtual bool isValidMove(int destRow, int destCol, const Board& board) const = 0;
    virtual char getSymbol() const = 0;

    bool getIsWhite() const;
    int getRow() const;
    int getCol() const;
    void setPosition(int newRow, int newCol);

    bool isPathClear(int destRow, int destCol, const Board& board) const;
};