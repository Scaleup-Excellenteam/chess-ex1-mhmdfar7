#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(bool isWhite, int row, int col) : Piece(isWhite, row, col) {}

bool Pawn::isValidMove(int destRow, int destCol, const Board& board) const {
    int direction = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    if (destCol == col) {
        if (destRow == row + direction && !board.getPiece(destRow, destCol)) return true;
        if (row == startRow && destRow == row + 2 * direction && !board.getPiece(row + direction, col) && !board.getPiece(destRow, destCol)) return true;
    }
    else if (abs(destCol - col) == 1 && destRow == row + direction) {
        Piece* destPiece = board.getPiece(destRow, destCol);
        if (destPiece && destPiece->getIsWhite() != isWhite) return true;
    }

    return false;
}

char Pawn::getSymbol() const { return isWhite ? 'P' : 'p'; }

Piece* Pawn::clone() const {
    return new Pawn(*this);
}
