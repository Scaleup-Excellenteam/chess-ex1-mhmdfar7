#pragma once
#include "Piece.h"
#include <string>
#include <vector>
#include "Move.h"

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
    bool isCheckmate(bool whiteTurn);
    bool isStalemate(bool whiteTurn);
    bool canCastle(bool isWhite, bool kingSide) const;
    void makeMove(int srcRow, int srcCol, int destRow, int destCol);
    std::vector<Move> listLegalMoves(bool whiteToMove) const;
};