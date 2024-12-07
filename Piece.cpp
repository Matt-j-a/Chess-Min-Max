#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>

// The Piece class
class Piece {
protected:
    int row, col;         // Position on the board
    int weight;           // Weight of the piece
    std::string symbol;   // Visual representation of the piece

public:
    // Constructor
    Piece(int r, int c, int w, const std::string& sym)
        : row(r), col(c), weight(w), symbol(sym) {}

    // Virtual destructor
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
};

// Example derived class (e.g., King)
class King : public Piece {
public:
    King(int r, int c) : Piece(r, c, 10, "K") {}

    // Check if a move is legal
    bool isLegalMove(int targetRow, int targetCol) const override {
        return abs(targetRow - row) <= 1 && abs(targetCol - col) <= 1;
    }
};

class EnemyKing : public Piece {
public:
    EnemyKing(int r, int c) : Piece(r, c, 10, "E") {}

    // Check if a move is legal
    bool isLegalMove(int targetRow, int targetCol) const override {
        return abs(targetRow - row) <= 1 && abs(targetCol - col) <= 1;
    }
};

// The Piece class and other derived classes ...

class Bishop : public Piece {
public:
    Bishop(int r, int c) : Piece(r, c, 5, "B") {}

    // Check if a move is legal (diagonal moves)
    bool isLegalMove(int targetRow, int targetCol) const override {
        return abs(targetRow - row) == abs(targetCol - col);
    }
};



#endif // PIECE_H
