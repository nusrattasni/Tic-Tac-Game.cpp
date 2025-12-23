#include <iostream>
#include <algorithm>
using namespace std;
char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char player = 'X', computer = 'O';
void drawBoard() {
    cout << "\n-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}
int evaluate() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return (board[i][0] == computer) ? 10 : -10;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return (board[0][i] == computer) ? 10 : -10;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == computer) ? 10 : -10;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == computer) ? 10 : -10;
    return 0;
}
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return true;
    return false;
}
int minimax(int depth, bool isMax) {
    int score = evaluate();
    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = computer;
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = temp;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = player;
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = -1000, row = -1, col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = computer;
                int moveVal = minimax(0, false);
                board[i][j] = temp;
                if (moveVal > bestVal) {
                    row = i; col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = computer;
}
int main() {
    int choice;
    cout << "Tic Tac Toe\n1. vs Player\n2. vs AI\nChoice: ";
    cin >> choice;
    while (true) {
        drawBoard();
        int move;
        cout << "Player " << player << ", enter move (1-9): ";
        cin >> move;

        int r = (move - 1) / 3, c = (move - 1) % 3;
        if (move < 1 || move > 9 || board[r][c] == 'X' || board[r][c] == 'O') {
            cout << "Invalid move!\n"; continue;
        }
        board[r][c] = player;
        if (evaluate() == -10) { drawBoard(); cout << "You Win!\n"; break; }
        if (!isMovesLeft()) { drawBoard(); cout << "Draw!\n"; break; }
        if (choice == 2) {
            findBestMove();
            if (evaluate() == 10) { drawBoard(); cout << "AI Wins!\n"; break; }
        } else {
            player = (player == 'X') ? 'O' : 'X';
        }
        if (!isMovesLeft()) { drawBoard(); cout << "Draw!\n"; break; }
    }
    return 0;
}
