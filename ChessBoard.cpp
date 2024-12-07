#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <climits>
#include "Piece.cpp"

class ChessBoard {
private:
    static const int BOARD_SIZE = 8; // Define an 8x8 board
    std::vector<std::vector<std::shared_ptr<Piece>>> board; // 2D vector to represent the board
    int moveAttempts = 0;
    // Store move history for undo functionality
    struct Move {
        int oldRow, oldCol, newRow, newCol;
        std::shared_ptr<Piece> capturedPiece;
    };
    std::vector<Move> moveHistory;
public:
    struct Cell {
        int row;
        char col; // Column as a letter (e.g., A-H)
        std::shared_ptr<Piece> piece;
    };

public:
    ChessBoard() : board(BOARD_SIZE, std::vector<std::shared_ptr<Piece>>(BOARD_SIZE, nullptr)) {}

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
                if (cell) {
                    std::cout << cell->getSymbol() << " ";
                } else {
                    std::cout << "_ ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool placePiece(int row, int col, std::shared_ptr<Piece> piece) {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            if (!board[row][col]) {
                board[row][col] = piece;
                piece->setPosition(row, col);
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

    bool movePiece(int oldRow, int oldCol, int newRow, int newCol) {
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            if (!board[newRow][newCol]) {
                auto piece = board[oldRow][oldCol];
                if (piece && piece->isLegalMove(newRow, newCol)) {
                    board[newRow][newCol] = piece;
                    board[oldRow][oldCol] = nullptr;
                    piece->setPosition(newRow, newCol);
                    return true;
                } else {
                    std::cerr << "Illegal move!" << std::endl;
                    return false;
                }
            } else {
                std::cerr << "Target position occupied!" << std::endl;
                return false;
            }
        } else {
            std::cerr << "Invalid move!" << std::endl;
            return false;
        }
    }

    std::shared_ptr<Piece> getCell(int row, int col) const {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            return board[row][col];
        } else {
            return nullptr;
        }
    }

    Cell getCellObject(int row, int col) const {
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            char columnLetter = 'A' + col;
            return {row + 1, columnLetter, board[row][col]};
        } else {
            return {row + 1, 'X', nullptr}; // Invalid column marked as 'X'
        }
    }

    /// Get all legal moves for a player
   std::vector<std::pair<int, int>> getLegalMovesForPlayer(bool isMaximizing) const {
    std::vector<std::pair<int, int>> moves;
    std::string playerSymbol = isMaximizing ? "K" : "E";

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto piece = board[row][col];
            if (piece && piece->getSymbol() == playerSymbol) {
                auto pieceMoves = piece->getLegalMoves(BOARD_SIZE);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }

    return moves;
}


    void applyMove(int oldRow, int oldCol, int newRow, int newCol) {
        ++moveAttempts; // Increment the move attempt counter
        auto piece = board[oldRow][oldCol];
        if (piece && piece->isLegalMove(newRow, newCol)) {
            std::shared_ptr<Piece> capturedPiece = board[newRow][newCol];
            moveHistory.push_back({oldRow, oldCol, newRow, newCol, capturedPiece});
            board[newRow][newCol] = piece;
            board[oldRow][oldCol] = nullptr;
            piece->setPosition(newRow, newCol);
        } 
    }

    void undoMove() {
        if (!moveHistory.empty()) {
            Move lastMove = moveHistory.back();
            moveHistory.pop_back();
            auto piece = board[lastMove.newRow][lastMove.newCol];
            board[lastMove.oldRow][lastMove.oldCol] = piece;
            board[lastMove.newRow][lastMove.newCol] = lastMove.capturedPiece;
            piece->setPosition(lastMove.oldRow, lastMove.oldCol);
        } 
    }

    int evaluateBoard(const ChessBoard& board) {
        int score = 0;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                auto piece = board.getCell(row, col);
                if (piece) {
                    score += (piece->getSymbol() == "K" ? piece->getWeight() : -piece->getWeight());
                }
            }
        }
        return score;
    }

    void resetMoveAttempts() {
        moveAttempts = 0;
    }

    int getMoveAttempts() const {
        return moveAttempts;
    }

    
    
};

#endif // CHESSBOARD_H
