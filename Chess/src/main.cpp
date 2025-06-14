#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>

#include "Chess.h"
#include "Board.h"
#include "Move.h"
#include "MoveEvaluator.h"
#include "ThreadPool.h"
#include "SafePriorityQueue.h"

using namespace std;

struct ScoredMove {
    Move move;
    int score;
};

struct ScoreCompare {
    bool operator()(const ScoredMove& a, const ScoredMove& b) const {
        return a.score < b.score; // max-heap
    }
};

int main(int argc, char* argv[]) {
    cout << "Choose game mode:\n1. Player vs Player\n2. Player vs Computer\n> ";
    int mode;
    cin >> mode;

    bool vsComputer = (mode == 2);
    bool whiteToMove = true;
    int threadsCount = 8;
    int depth = 3;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--threads" && i + 1 < argc) threadsCount = atoi(argv[++i]);
        else if (arg == "--depth" && i + 1 < argc) depth = atoi(argv[++i]);
    }

    const string startFEN = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess cli(startFEN);
    Board board(startFEN);

    while (true) {
        cli.displayBoard();
        auto moves = board.listLegalMoves(whiteToMove);

        if (board.isCheckmate(whiteToMove)) {
            cout << (whiteToMove ? "White" : "Black") << " is checkmated!\n";
            break;
        }
        if (board.isStalemate(whiteToMove)) {
            cout << "Stalemate! It's a draw.\n";
            break;
        }

        if (!vsComputer || whiteToMove) {
            // --- Human player's move ---
            string input = cli.getInput();
            if (input == "exit") break;

            int codeResp = 0;
            if (input.size() != 4) {
                codeResp = 11; // invalid format
            }
            else {
                int sr = 'h' - input[0], sc = input[1] - '1';
                int dr = 'h' - input[2], dc = input[3] - '1';

                if (sr < 0 || sr > 7 || sc < 0 || sc > 7 || dr < 0 || dr > 7 || dc < 0 || dc > 7) {
                    codeResp = 11; // out of bounds
                }
                else {
                    Piece* p = board.getPiece(sr, sc);
                    if (!p) codeResp = 11;
                    else if (p->getIsWhite() != whiteToMove)        codeResp = 12;
                    else if (board.getPiece(dr, dc) && board.getPiece(dr, dc)->getIsWhite() == whiteToMove)
                        codeResp = 13;
                    else if (!p->isValidMove(dr, dc, board))        codeResp = 21;
                    else {
                        Board tmp = board;
                        tmp.makeMove(sr, sc, dr, dc);
                        if (tmp.isKingInCheck(whiteToMove))         codeResp = 31;
                        else {
                            bool oppChk = tmp.isKingInCheck(!whiteToMove);
                            codeResp = oppChk ? 41 : 42;
                        }
                    }
                }
            }

            cli.setCodeResponse(codeResp);
            if (codeResp == 41 || codeResp == 42) {
                board.makeMove('h' - input[0], input[1] - '1',
                    'h' - input[2], input[3] - '1');
                whiteToMove = !whiteToMove;
            }
        }
        else {
            // --- AI (computer) move ---
            cout << "Computer is thinking...\n";

            MoveEvaluator evaluator(depth);
            SafePriorityQueue<ScoredMove, ScoreCompare> pq;
            ThreadPool pool(threadsCount);

            for (const auto& mv : moves) {
                pool.enqueue([&pq, &board, &evaluator, mv]() {
                    int sc = evaluator.score(mv, board);
                    pq.push(ScoredMove{ mv, sc });
                    });
            }

            pool.shutdown();

            ScoredMove best;
            if (pq.tryPop(best)) {
                board.makeMove(best.move.srcRow, best.move.srcCol,
                    best.move.dstRow, best.move.dstCol);
                cout << "Computer played: " << best.move.toString() << "\n";
                whiteToMove = !whiteToMove;
            }
            else {
                cout << "Computer has no legal move.\n";
                break;
            }
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
