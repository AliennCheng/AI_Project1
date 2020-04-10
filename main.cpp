// AI Project
// NCTU Artificial Intelligence, spring 2020
// Created by Alienn Cheng on 2020/4/3.

#include <iostream>
#include "board.h"

using namespace std;

int main(int argc, char** argv) {

    string in;
    int mode;
    bool playfirst;
    cout << "Mode? (4)4x4 (6)6x6: ";
    while (cin >> in) {
        if (in == "4") { mode = 4; break; }
        else if (in == "6") { mode = 6; break; }
        else cout << "Invalid mode! QQ" << endl;
    }
    
    cout << "Who am I? Player(0) Player(1): ";
    while (cin >> in) {
        if (in == "0") { playfirst = 0; break; }
        else if (in == "1") { playfirst = 1; break; }
        else cout << "Invalid input! QQ" << endl;
    }

    Board board;
    if (mode == 4) board = Board4x4();
    else board = Board6x6();
    
    bool who = 0;
    int row, col, weight;
    while (true) {
        board.showBoard();
        cout << "Player" << who << "'s turn!" << endl;
        if (who == playfirst) {
            vector<int> move = board.getStupidPlay(who);
            cout << "I just play " << move[0] << " at (" << move[1] << ", " << move[2] << ")" << endl;
            if (board.addPiece(who, move[0], move[1], move[2])) {
                board.fallingCheck();
                who = !who;
            } else {
                cout << "Be serious. OK?" << endl;
            }
        } else {
            cout << "Input your play (row, col, weight): ";
            cin >> row >> col >> weight;
            if (row < 0 || row > mode-1 || col < 0 || col > mode-1) {
                cout << "Are you kidding me?" << endl;
                continue;
            }
            if (board.addPiece(who, weight, row, col)) {
                board.fallingCheck();
                who = !who;
            } else {
                cout << "Be serious. OK?" << endl;
            }
        }

        if (board.isTerminate()) {
            board.showBoard();
            cout << "GAMEOVER!" << endl;
            int winner = board.getWinner();
            if (winner < 0) cout << "We are both good, man!" << endl;
            else if (winner == playfirst) cout << "I think I am better than you, HA!" << endl;
            else cout << "Oh, no! You just beat me..." << endl;
            return 0;
        }
    }

    return 0;
}