#include <iostream>
#include <vector>
#include <string>

// Initialize the board with empty spaces
void setTable(std::vector<std::vector<char>>& table) {
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            table[i][j] = ' ';
        }
    }
}

// Check horizontal win
bool horizontalCheck(const std::vector<std::vector<char>>& table, const int i, const char symbol) {
    for (int k = 0; k < table.size(); k++) {
        if (table[i][k] != symbol)
            return false;
    }
    return true;
}

// Check vertical win
bool verticalCheck(const std::vector<std::vector<char>>& table, const int j, const char symbol) {
    for (int k = 0; k < table.size(); k++) {
        if (table[k][j] != symbol)
            return false;
    }
    return true;
}

// Check both diagonals
bool diagonalCheck(const std::vector<std::vector<char>>& table, const char symbol) {
    bool mainDiagonal = true;
    bool antiDiagonal = true;

    for (int i = 0; i < table.size(); i++) {
        if (table[i][i] != symbol)
            mainDiagonal = false;
        if (table[i][table.size() - i - 1] != symbol)
            antiDiagonal = false;
    }

    return mainDiagonal || antiDiagonal;
}

// Combine win conditions
bool winCondition(const std::vector<std::vector<char>>& table, const int i, const int j, const char symbol) {
    return (
        horizontalCheck(table, i, symbol) ||
        verticalCheck(table, j, symbol) ||
        diagonalCheck(table, symbol)
    );
}

// Display the board
void display(const std::vector<std::vector<char>>& table) {
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            std::cout << table[i][j];
            if (j < table[i].size() - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
        if (i < table.size() - 1)
            std::cout << "--+---+--" << std::endl;
    }
    std::cout << std::endl;
}

// Handle the game loop
void playGame(std::vector<std::vector<char>>& table) {
    char currentPlayer = 'X';
    int moves = 0;
    bool gameOver = false;

    std::cout << "Welcome to Tic-Tac-Toe!\n" << std::endl;

    while (!gameOver && moves < 9) {
        display(table);
        int row, col;
        std::cout << "Player " << currentPlayer << ", enter your move (row and column: 0 1 2): ";
        std::cin >> row >> col;

        // Input validation
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || table[row][col] != ' ') {
            std::cout << "Invalid move! Try again.\n" << std::endl;
            continue;
        }

        table[row][col] = currentPlayer;
        moves++;

        if (winCondition(table, row, col, currentPlayer)) {
            display(table);
            std::cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else {
            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    if (!gameOver) {
        display(table);
        std::cout << "It's a draw!\n";
    }
}

int main() {
    std::vector<std::vector<char>> table(3, std::vector<char>(3));
    setTable(table);
    playGame(table);
    return 0;
}
