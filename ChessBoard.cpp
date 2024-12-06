#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <memory> // For smart pointers
#include "Piece.cpp" // Include the Piece base class

class ChessBoard {
private:
    static const int BOARD_SIZE = 5; // Define a 5x5 board
    std::vector<std::vector<std::string>> board; // 2D vector to represent the board

public:
    ChessBoard() : board(BOARD_SIZE, std::vector<std::string>(BOARD_SIZE, "_")) {}

    // Display the board
    void displayBoard() const {
        std::cout << "  ";
        for (char col = 'A'; col < 'A' + BOARD_SIZE; ++col) {
            std::cout << col << " ";
        }
        std::cout << std::endl;

        for (int row = 0; row < BOARD_SIZE; ++row) {
            std::cout << (row + 1) << " ";
            for (const auto& cell : board[row]) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    // Place a piece on the board
    bool placePiece(int row, int col, const std::string& symbol) {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            if (board[row][col] == "_") { // Ensure the square is empty
                board[row][col] = symbol;
                return true;
            } else {
                std::cerr << "Position already occupied!" << std::endl;
                return false;
            }
        } else {
            std::cerr << "Invalid position for piece placement!" << std::endl;
            return false;
        }
    }

    // Move a piece on the board
    bool movePiece(int oldRow, int oldCol, int newRow, int newCol, const std::string& symbol) {
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            if (board[newRow][newCol] == "_") { // Ensure the target square is empty
                board[oldRow][oldCol] = "_";  // Clear old position
                board[newRow][newCol] = symbol; // Set new position
                return true;
            } else {
                std::cerr << "Target position occupied!" << std::endl;
                return false;
            }
        } else {
            std::cerr << "Invalid move!" << std::endl;
            return false;
        }
    }
};
