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
    int   score;
};

struct ScoreCompare {
    bool operator()(const ScoredMove& a, const ScoredMove& b) const {
        return a.score < b.score;  // max-heap by score
    }
};

int main(int argc, char* argv[]) {
    int threadsCount = 4;
    bool autoPlay = false;
    int  depth = 3;
    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "--threads" && i + 1 < argc) threadsCount = atoi(argv[++i]);
        else if (a == "--auto")            autoPlay = true;
        else if (a == "--depth" && i + 1 < argc) depth = atoi(argv[++i]);
    }

    const string startFEN = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess cli(startFEN);
    Board board(startFEN);
    bool whiteToMove = true;

    // ---- Auto?play branch ----
    if (autoPlay) {
        MoveEvaluator evaluator(depth);
        SafePriorityQueue<ScoredMove, ScoreCompare> pq;
        ThreadPool pool(threadsCount);

        auto start = chrono::steady_clock::now();

        auto moves = board.listLegalMoves(whiteToMove);
        for (auto mv : moves) {
            pool.enqueue([&pq, &board, &evaluator, mv]() {
                int sc = evaluator.score(mv, board);
                pq.push(ScoredMove{ mv, sc });
                });
        }

        pool.shutdown();

        ScoredMove best;
        if (pq.tryPop(best)) {
            cout << "Auto-Chosen: " << best.move.toString()
                << " (score=" << best.score << ")\n";
        }

        auto end = chrono::steady_clock::now();
        cout << "Time: "
            << chrono::duration_cast<chrono::milliseconds>(end - start).count()
            << " ms\n";
        return 0;
    }

    // ---- Interactive branch (unchanged) ----
    string input = cli.getInput();
    while (input != "exit") {
        int codeResp = 0;
        if (input.size() != 4) {
            codeResp = 11;
        }
        else {
            int sr = 'h' - input[0], sc = input[1] - '1';
            int dr = 'h' - input[2], dc = input[3] - '1';
            if (sr < 0 || sr>7 || sc < 0 || sc>7 || dr < 0 || dr>7 || dc < 0 || dc>7) {
                codeResp = 11;
            }
            else {
                Piece* p = board.getPiece(sr, sc);
                if (!p) codeResp = 11;
                else if (p->getIsWhite() != whiteToMove)        codeResp = 12;
                else if (board.getPiece(dr, dc)
                    && board.getPiece(dr, dc)->getIsWhite() == whiteToMove)
                    codeResp = 13;
                else if (!p->isValidMove(dr, dc, board))         codeResp = 21;
                else {
                    Board tmp = board;
                    tmp.makeMove(sr, sc, dr, dc);
                    if (tmp.isKingInCheck(whiteToMove))            codeResp = 31;
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
        input = cli.getInput();
    }

    cout << "Goodbye!\n";
    return 0;
}
