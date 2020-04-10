// AI Project
// NCTU Artificial Intelligence, spring 2020
// Created by Alienn Cheng on 2020/4/3.

#ifndef BOARD_H
#define BOARD_H
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <random>

using namespace std;

struct Grid {
    bool who;
    bool occupied;
    bool ban;
    int value;
    int localSum;
};

class Board {
protected:
    int N;
    vector< vector<Grid> > board;
    multiset<int> p0, p1; // pieces
    default_random_engine rng;

public:
    Board() {}

    Board(Board &other) {
        rng = default_random_engine {};
        p0 = other.getPieces(0);
        p1 = other.getPieces(1);
        board = other.getBoard();
    }

    ~Board() {
        for (auto v : board) { v.clear(); }
        board.clear();
        p0.clear();
        p1.clear();
    }

    inline void placing(int i, int j, int value) {
        if (i < 0 || j < 0 || i > N-1 || j > N-1) return;
        board[i][j].localSum += value;
        if (i == 0) {
            if (j == 0) {
                board[i][j+1].localSum += value;
                board[i+1][j].localSum += value;
                board[i+1][j+1].localSum += value;
            } else if (j == N-1) {
                board[i][j-1].localSum += value;
                board[i+1][j-1].localSum += value;
                board[i+1][j].localSum += value;
            } else {
                board[i][j-1].localSum += value;
                board[i][j+1].localSum += value;
                board[i+1][j-1].localSum += value;
                board[i+1][j].localSum += value;
                board[i+1][j+1].localSum += value;
            }
        } else if (i == N-1) {
            if (j == 0) {
                board[i-1][j].localSum += value;
                board[i-1][j+1].localSum += value;
                board[i][j+1].localSum += value;
            } else if (j == N-1) {
                board[i-1][j-1].localSum += value;
                board[i-1][j].localSum += value;
                board[i][j-1].localSum += value;
            } else {
                board[i-1][j-1].localSum += value;
                board[i-1][j].localSum += value;
                board[i-1][j+1].localSum += value;
                board[i][j-1].localSum += value;
                board[i][j+1].localSum += value;
            }
        } else {
            if (j == 0) {
                board[i-1][j].localSum += value;
                board[i-1][j+1].localSum += value;
                board[i][j+1].localSum += value;
                board[i+1][j].localSum += value;
                board[i+1][j+1].localSum += value;
            } else if (j == N-1) {
                board[i-1][j-1].localSum += value;
                board[i-1][j].localSum += value;
                board[i][j-1].localSum += value;
                board[i+1][j-1].localSum += value;
                board[i+1][j].localSum += value;
            } else {
                board[i-1][j-1].localSum += value;
                board[i-1][j].localSum += value;
                board[i-1][j+1].localSum += value;
                board[i][j-1].localSum += value;
                board[i][j+1].localSum += value;
                board[i+1][j-1].localSum += value;
                board[i+1][j].localSum += value;
                board[i+1][j+1].localSum += value;
            }
        }
    }

    bool addPiece(bool who, int which, int i, int j) {
        if ((!who && p0.find(which) == p0.end()) || (who && p1.find(which) == p1.end()) || // play an used piece
                board[i][j].occupied ||  board[i][j].ban) { // occupied or banned
            printf("Illegal move by %d to play %d at (%d, %d)\n", who, which, i, j);
            return false;
        }
        
        multiset<int>::iterator it;
        if (!who) { it = p0.find(which); p0.erase(it); }
        else { it = p1.find(which); p1.erase(it); }

        board[i][j].who = who;
        board[i][j].occupied = true;
        board[i][j].value = which;
        placing(i, j, which);

        return true;
    }

    inline void falling(int i, int j) {
        int value = board[i][j].value;
        board[i][j].ban = true;
        board[i][j].value = 0;
        
        if (i == 0) {
            if (j == 0) {
                board[i][j+1].localSum -= value;
                board[i+1][j].localSum -= value;
                board[i+1][j+1].localSum -= value;
            } else if (j == N-1) {
                board[i][j-1].localSum -= value;
                board[i+1][j-1].localSum -= value;
                board[i+1][j].localSum -= value;
            } else {
                board[i][j-1].localSum -= value;
                board[i][j+1].localSum -= value;
                board[i+1][j-1].localSum -= value;
                board[i+1][j].localSum -= value;
                board[i+1][j+1].localSum -= value;
            }
        } else if (i == N-1) {
            if (j == 0) {
                board[i-1][j].localSum -= value;
                board[i-1][j+1].localSum -= value;
                board[i][j+1].localSum -= value;
            } else if (j == N-1) {
                board[i-1][j-1].localSum -= value;
                board[i-1][j].localSum -= value;
                board[i][j-1].localSum -= value;
            } else {
                board[i-1][j-1].localSum -= value;
                board[i-1][j].localSum -= value;
                board[i-1][j+1].localSum -= value;
                board[i][j-1].localSum -= value;
                board[i][j+1].localSum -= value;
            }
        } else {
            if (j == 0) {
                board[i-1][j].localSum -= value;
                board[i-1][j+1].localSum -= value;
                board[i][j+1].localSum -= value;
                board[i+1][j].localSum -= value;
                board[i+1][j+1].localSum -= value;
            } else if (j == N-1) {
                board[i-1][j-1].localSum -= value;
                board[i-1][j].localSum -= value;
                board[i][j-1].localSum -= value;
                board[i+1][j-1].localSum -= value;
                board[i+1][j].localSum -= value;
            } else {
                board[i-1][j-1].localSum -= value;
                board[i-1][j].localSum -= value;
                board[i-1][j+1].localSum -= value;
                board[i][j-1].localSum -= value;
                board[i][j+1].localSum -= value;
                board[i+1][j-1].localSum -= value;
                board[i+1][j].localSum -= value;
                board[i+1][j+1].localSum -= value;
            }
        }
    }
    
    void fallingCheck() {
        vector< pair<int, int> > overweighted;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j].occupied && board[i][j].localSum > 15)
                    overweighted.push_back(make_pair(i, j));
            }
        }
        for (auto p : overweighted)
            falling(p.first, p.second);
    }

    vector< vector<int> > genLegalMove(bool who) {
        vector< vector<int> > ret;
        int last = 0;
        if (who) { // p1
            for (int piece : p1) {
                if (piece != last) {
                    last = piece;
                    for (int i = 0; i < N; ++i) {
                        for (int j = 0; j < N; ++j) {
                            if (!board[i][j].ban && !board[i][j].occupied) {
                                ret.push_back({piece, i, j});
                            }
                        }
                    }
                }
            }
        } else { // p0
            for (int piece : p0) {
                if (piece != last) {
                    last = piece;
                    for (int i = 0; i < N; ++i) {
                        for (int j = 0; j < N; ++j) {
                            if (!board[i][j].ban && !board[i][j].occupied) {
                                ret.push_back({piece, i, j});
                            }
                        }
                    }
                }
            }
        }
        if (ret.size() > 1)
            shuffle(begin(ret), end(ret), rng);
        return ret;
    }

    vector<int> getStupidPlay(bool who) {
        vector< vector<int> > legalMoves = genLegalMove(who);
        return legalMoves[0];
    }

    vector< vector<Grid> > getBoard() {
        return board;
    }

    int getGrid(int i, int j) {
        return board[i][j].value;
    }

    multiset<int> getPieces(bool whose) {
        return whose ? p1 : p0;
    }

    bool isTerminate() {
        return p0.empty() && p1.empty();
    }

    int getWinner() {
        int score0 = 0, score1 = 0, mx0 = 0, mx1 = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j].occupied && !board[i][j].ban) {
                    if (!board[i][j].who) {
                        score0 += board[i][j].value;
                        if (score0 > mx0) mx0 = score0;
                    } else {
                        score1 += board[i][j].value;
                        if (score1 > mx1) mx1 = score1;
                    }
                }
            }
        }

        if (score0 == score1) {
            if (mx0 == mx1) return -1;
            else if (mx0 > mx1) return 0;
            else return 1;
        } else {
            if (score0 > score1) return 0;
            else return 1;
        }
    }

    void showBoard() {
        printf("\n=============================\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j].ban) printf(RED "  0" RESET);
                else if (board[i][j].occupied) {
                    if (board[i][j].who == false)
                        printf(YELLOW "%3d" RESET, board[i][j].value);
                    else
                        printf(CYAN "%3d" RESET, board[i][j].value);
                } else {
                    printf("  0", board[i][j].value);
                }
            }
            printf("\n");
        }
        printf("\nPlayer0: ");
        for (int i : p0) printf("%d ", i);
        printf("\nPlayer1: ");
        for (int i : p1) printf("%d ", i);
        printf("\n=============================\n\n");
    }
};

class Board4x4 : public Board {
public:
    Board4x4() {
        N = 4;
        rng = default_random_engine {};
        p0.insert(2); p0.insert(3); p0.insert(5); p0.insert(8); p0.insert(13);
        p1.insert(2); p1.insert(3); p1.insert(5); p1.insert(8); p1.insert(13);
        board.resize(N, vector<Grid>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                board[i][j].occupied = false;
                board[i][j].ban = false;
                board[i][j].value = 0;
                board[i][j].localSum = 0;
            }
        }
    }
};

class Board6x6 : public Board {
public:
    Board6x6() {
        N = 6;
        rng = default_random_engine {};
        p0.insert(2); p0.insert(2); p0.insert(3); p0.insert(3); p0.insert(5); p0.insert(5);
        p0.insert(8); p0.insert(8); p0.insert(8); p0.insert(13); p0.insert(13);
        p1.insert(2); p1.insert(2); p1.insert(3); p1.insert(3); p1.insert(5); p1.insert(5);
        p1.insert(8); p1.insert(8); p1.insert(8); p1.insert(13); p1.insert(13);
        board.resize(N, vector<Grid>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                board[i][j].occupied = false;
                board[i][j].ban = false;
                board[i][j].value = 0;
                board[i][j].localSum = 0;
            }
        }
    }
};

#endif