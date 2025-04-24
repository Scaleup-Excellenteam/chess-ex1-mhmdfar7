#include "Board.h"
#include <iostream>
#include <string>
#include <Chess.h>

using namespace std;

int main() {
    string boardStr = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(boardStr);
    Board myBoard(boardStr);
    bool currentTurn = true; // true for white's turn

    int codeResponse = 0;
    string res = a.getInput();
    while (res != "exit") {
        codeResponse = 0;

        if (res.length() != 4) {
            codeResponse = 11;
            a.setCodeResponse(codeResponse);
            res = a.getInput();
            continue;
        }

        char srcFile = res[0];
        char srcRank = res[1];
        char destFile = res[2];
        char destRank = res[3];

        int srcRow = 'h' - srcFile;
        int srcCol = srcRank - '1';
        int destRow = 'h' - destFile;
        int destCol = destRank - '1';

        if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 ||
            destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
            codeResponse = 11;
        }
        else {
            Piece* srcPiece = myBoard.getPiece(srcRow, srcCol);
            if (!srcPiece) {
                codeResponse = 11;
            }
            else if (srcPiece->getIsWhite() != currentTurn) {
                codeResponse = 12;
            }
            else {
                Piece* destPiece = myBoard.getPiece(destRow, destCol);
                if (destPiece && destPiece->getIsWhite() == currentTurn) {
                    codeResponse = 13;
                }
                else if (!srcPiece->isValidMove(destRow, destCol, myBoard)) {
                    codeResponse = 21;
                }
                else {
                    Board tempBoard = myBoard;
                    tempBoard.makeMove(srcRow, srcCol, destRow, destCol);
                    if (tempBoard.isKingInCheck(currentTurn)) {
                        codeResponse = 31;
                    }
                    else {
                        bool opponentInCheck = tempBoard.isKingInCheck(!currentTurn);
                        codeResponse = opponentInCheck ? 41 : 42;
                    }
                }
            }
        }

        a.setCodeResponse(codeResponse);

        if (codeResponse == 41 || codeResponse == 42) {
            myBoard.makeMove(srcRow, srcCol, destRow, destCol);
            currentTurn = !currentTurn;
        }

        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}