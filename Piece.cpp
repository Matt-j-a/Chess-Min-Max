#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <utility> // For std::pair

class Piece {
protected:
    int row, col;         // Position on the board
    int weight;           // Weight of the piece
    std::string symbol;   // Visual representation of the piece

public:
    Piece(int r, int c, int w, const std::string& sym)
        : row(r), col(c), weight(w), symbol(sym) {}

    virtual ~Piece() = default;

    // Getters
    int getRow() const { return row; }
    int getCol() const { return col; }
    int getWeight() const { return weight; }
    std::string getSymbol() const { return symbol; }

    // Set position
    void setPosition(int r, int c) {
        row = r;
        col = c;
    }

    // Pure virtual function to check if a move is legal for the piece
    virtual bool isLegalMove(int targetRow, int targetCol) const = 0;

    // New: Get all legal moves for this piece
    virtual std::vector<std::pair<int, int>> getLegalMoves(int boardSize) const = 0;
};

// Example derived class: King
class King : public Piece {
public:
    King(int r, int c) : Piece(r, c, 10, "K") {}

    bool isLegalMove(int targetRow, int targetCol) const override {
        return abs(targetRow - row) <= 1 && abs(targetCol - col) <= 1;
    }

    std::vector<std::pair<int, int>> getLegalMoves(int boardSize) const override {
        std::vector<std::pair<int, int>> moves;
        for (int dRow = -1; dRow <= 1; ++dRow) {
            for (int dCol = -1; dCol <= 1; ++dCol) {
                int newRow = row + dRow;
                int newCol = col + dCol;
                if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize) {
                    moves.emplace_back(newRow, newCol);
                }
            }
        }
        return moves;
    }
};

// Example derived class: Bishop
class Bishop : public Piece {
public:
    Bishop(int r, int c) : Piece(r, c, 5, "B") {}

    bool isLegalMove(int targetRow, int targetCol) const override {
        return abs(targetRow - row) == abs(targetCol - col);
    }

    std::vector<std::pair<int, int>> getLegalMoves(int boardSize) const override {
        std::vector<std::pair<int, int>> moves;
        for (int dRow = -boardSize; dRow <= boardSize; ++dRow) {
            int newRow = row + dRow;
            int newCol = col + dRow;
            if (newRow >= 0 && newRow < boardSize && newCol >= 0 && newCol < boardSize) {
                moves.emplace_back(newRow, newCol);
            }
        }
        return moves;
    }
};

#endif // PIECE_H
