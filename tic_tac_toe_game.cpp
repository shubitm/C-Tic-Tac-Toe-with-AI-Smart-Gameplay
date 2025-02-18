
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

char player = 'X', computer = 'O';
vector<vector<char>> board(3, vector<char>(3, ' '));  // 3x3 board

// Function to print the board
void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to check for a win or a draw
int checkWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return (board[i][0] == player) ? 1 : -1;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return (board[0][i] == player) ? 1 : -1;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return (board[0][0] == player) ? 1 : -1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return (board[0][2] == player) ? 1 : -1;
    }

    // Check for draw (board full)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;  // Game still ongoing
            }
        }
    }

    return 2;  // Draw
}

// Function to make a move
void makeMove(int row, int col, char playerSymbol) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = playerSymbol;
    }
}

// Minimax algorithm for AI
int minimax(int depth, bool isMaximizing) {
    int score = checkWinner();
    if (score == 1) return -10 + depth;  // Player wins
    if (score == -1) return 10 - depth;  // AI wins
    if (score == 2) return 0;  // Draw

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = computer;
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the AI
pair<int, int> bestMove() {
    int bestVal = INT_MIN;
    pair<int, int> move = {-1, -1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int moveVal = minimax(0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    move = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return move;
}

// Function to handle AI difficulty levels
void aiMove(int difficulty) {
    pair<int, int> move = {-1, -1};
    if (difficulty == 1) {  // Easy: Random move
        do {
            move.first = rand() % 3;
            move.second = rand() % 3;
        } while (board[move.first][move.second] != ' ');
    } else if (difficulty == 2) {  // Medium: Random move with some logic
        do {
            move.first = rand() % 3;
            move.second = rand() % 3;
        } while (board[move.first][move.second] != ' ');
        if (checkWinner() == 0) return;
    } else if (difficulty == 3) {  // Hard: Minimax
        move = bestMove();
    }
    makeMove(move.first, move.second, computer);
}

// Main game loop
void playGame(int difficulty) {
    int playerMoveRow, playerMoveCol;
    printBoard();
    while (true) {
        // Player's turn
        cout << "Enter your move (row and column): ";
        cin >> playerMoveRow >> playerMoveCol;
        makeMove(playerMoveRow, playerMoveCol, player);

        // Check for game over conditions
        int result = checkWinner();
        if (result == 1) {
            printBoard();
            cout << "You win!" << endl;
            break;
        } else if (result == -1) {
            printBoard();
            cout << "AI wins!" << endl;
            break;
        } else if (result == 2) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        // AI's turn
        aiMove(difficulty);
        result = checkWinner();
        if (result == 1) {
            printBoard();
            cout << "You win!" << endl;
            break;
        } else if (result == -1) {
            printBoard();
            cout << "AI wins!" << endl;
            break;
        } else if (result == 2) {
            printBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        printBoard();
    }
}

int main() {
    int difficulty;
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Select AI Difficulty (1=Easy, 2=Medium, 3=Hard): ";
    cin >> difficulty;

    cout << "You are X, AI is O.\n";
    playGame(difficulty);

    return 0;
}
