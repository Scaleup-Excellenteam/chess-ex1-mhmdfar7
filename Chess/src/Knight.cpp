#include "Knight.h"
#include "Board.h"

Knight::Knight(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool Knight::isValidMove(int destRow, int destCol, const Board& board) const {
    int rowDiff = abs(destRow - row);
    int colDiff = abs(destCol - col);
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) return false;
    Piece* destPiece = board.getPiece(destRow, destCol);
    return !(destPiece && destPiece->getIsWhite() == isWhite);
}

char Knight::getSymbol() const { return isWhite ? 'N' : 'n'; }

Piece* Knight::clone() const {
    return new Knight(*this);
}
