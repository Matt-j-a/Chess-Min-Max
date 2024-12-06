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

    // Store move history for undo functionality
    struct Move {
        int oldRow, oldCol, newRow, newCol;
        std::string capturedPiece;
    };
    std::vector<Move> moveHistory;



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

    // Get the piece at a specific position
    char getCell(int row, int col) const {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            return board[row][col][0]; // Assuming symbols are single characters
        } else {
            return '_'; // Return empty if out of bounds
        }
    }

    // Get all legal moves for a player
    std::vector<std::pair<int, int>> getLegalMoves(bool isMaximizing) const {
        std::vector<std::pair<int, int>> moves;
        char playerSymbol = isMaximizing ? 'K' : 'E';

        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if (board[row][col][0] == playerSymbol) {
                    // Example logic: Add all adjacent cells as legal moves
                    for (int dRow = -1; dRow <= 1; ++dRow) {
                        for (int dCol = -1; dCol <= 1; ++dCol) {
                            int newRow = row + dRow;
                            int newCol = col + dCol;
                            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE && board[newRow][newCol] == "_") {
                                moves.emplace_back(newRow, newCol);
                            }
                        }
                    }
                }
            }
        }

        return moves;
    }

    // Apply a move to the board
void applyMove(int oldRow, int oldCol, int newRow, int newCol, const std::string& symbol) {
    // Capture the piece at the new position (if any)
    std::string capturedPiece = board[newRow][newCol];
    
    // Track the move in history (old position, new position, and captured piece)
    moveHistory.push_back({oldRow, oldCol, newRow, newCol, capturedPiece});
    
    // Move the piece to the new position
    board[newRow][newCol] = symbol;  // Place the current piece at the new position
    board[oldRow][oldCol] = "_";     // Clear the old position
}

// Undo the last move
void undoMove() {
    if (!moveHistory.empty()) {
        // Get the last move from the history
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();  // Remove the last move from history

        // Revert the board to the previous state
        board[lastMove.oldRow][lastMove.oldCol] = board[lastMove.newRow][lastMove.newCol]; // Move the piece back to its old position
        board[lastMove.newRow][lastMove.newCol] = lastMove.capturedPiece; // Restore the captured piece
    } else {
        std::cerr << "No move to undo!" << std::endl;
    }
}
};
