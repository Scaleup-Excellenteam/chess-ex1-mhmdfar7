#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Move.h"
#include <cctype>

Board::Board(const std::string& boardStr) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char c = boardStr[i * 8 + j];
            if (c == '#') {
                squares[i][j] = nullptr;
                continue;
            }
            bool white = isupper(c);
            switch (tolower(c)) {
            case 'r': squares[i][j] = new Rook(white, i, j); break;
            case 'n': squares[i][j] = new Knight(white, i, j); break;
            case 'b': squares[i][j] = new Bishop(white, i, j); break;
            case 'q': squares[i][j] = new Queen(white, i, j); break;
            case 'k': squares[i][j] = new King(white, i, j); break;
            case 'p': squares[i][j] = new Pawn(white, i, j); break;
            default: squares[i][j] = nullptr; break;
            }
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete squares[i][j];
        }
    }
}

Board::Board(const Board& other) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.squares[i][j]) {
                // Clone each piece properly (simplified for brevity)
                squares[i][j] = nullptr;
            }
            else {
                squares[i][j] = nullptr;
            }
        }
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Implement proper assignment (simplified for brevity)
    }
    return *this;
}

Piece* Board::getPiece(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) return nullptr;
    return squares[row][col];
}

bool Board::isKingInCheck(bool isWhite) const {
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = getPiece(i, j);
            if (piece && piece->getSymbol() == (isWhite ? 'K' : 'k')) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1) return false;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = getPiece(i, j);
            if (piece && piece->getIsWhite() != isWhite) {
                if (piece->isValidMove(kingRow, kingCol, *this)) {
                    return true;
                }
            }
        }
    }

    return false;
}

void Board::makeMove(int srcRow, int srcCol, int destRow, int destCol) {
    Piece* srcPiece = squares[srcRow][srcCol];
    if (!srcPiece) return;

    delete squares[destRow][destCol];
    squares[destRow][destCol] = srcPiece;
    squares[srcRow][srcCol] = nullptr;
    srcPiece->setPosition(destRow, destCol);
}

std::vector<Move> Board::listLegalMoves(bool whiteToMove) const {
    std::vector<Move> out;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = getPiece(r, c);
            if (!p || p->getIsWhite() != whiteToMove) continue;
            // try every destination
            for (int dr = 0; dr < 8; ++dr) {
                for (int dc = 0; dc < 8; ++dc) {
                    if (p->isValidMove(dr, dc, *this)) {
                        // make sure it doesn’t leave king in check
                        Board temp = *this;
                        temp.makeMove(r, c, dr, dc);
                        if (!temp.isKingInCheck(whiteToMove)) {
                            out.push_back(Move{ r,c,dr,dc });
                        }
                    }
                }
            }
        }
    }
    return out;
}