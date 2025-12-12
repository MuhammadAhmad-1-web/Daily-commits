// tictactoe.cpp
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

void printBoard(const vector<char>& b) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " " << b[3*i] << " | " << b[3*i+1] << " | " << b[3*i+2] << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isFull(const vector<char>& b) {
    for (char c : b) if (c == ' ') return false;
    return true;
}

char checkWinner(const vector<char>& b) {
    const int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diagonals
    };
    for (auto &w : wins) {
        int a = w[0], c = w[1], d = w[2];
        if (b[a] != ' ' && b[a] == b[c] && b[a] == b[d]) return b[a];
    }
    return 0; // no winner
}

int getMove(char player, const vector<char>& b) {
    while (true) {
        cout << "Player " << player << " — choose cell (1-9): ";
        string s;
        if (!getline(cin, s)) return -1;
        if (s.empty()) continue;
        // allow spaces, and take first visible digit
        int pos = -1;
        for (char ch : s) {
            if (isdigit((unsigned char)ch)) { pos = ch - '0'; break; }
        }
        if (pos < 1 || pos > 9) {
            cout << "Please enter a number from 1 to 9.\n";
            continue;
        }
        if (b[pos-1] != ' ') {
            cout << "Cell already taken. Pick another.\n";
            continue;
        }
        return pos-1;
    }
}

int main() {
    vector<char> board(9, ' ');
    char current = 'X';
    cout << "Tic-Tac-Toe — two players (X and O)\n";
    cout << "Cells are numbered 1 to 9 like this:\n";
    cout << " 1 | 2 | 3\n---+---+---\n 4 | 5 | 6\n---+---+---\n 7 | 8 | 9\n";

    while (true) {
        printBoard(board);
        int move = getMove(current, board);
        if (move < 0) {
            cout << "Input error. Exiting.\n";
            break;
        }
        board[move] = current;

        char winner = checkWinner(board);
        if (winner) {
            printBoard(board);
            cout << "Player " << winner << " wins! 🎉\n";
            break;
        }
        if (isFull(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }
        current = (current == 'X') ? 'O' : 'X';
    }

    return 0;
}
