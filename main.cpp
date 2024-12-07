#include "ChessBoard.cpp"
#include <iostream>
#include <limits>

// Evaluation function
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

// Minimax function
int minimax(ChessBoard& board, int depth, bool isMaximizing) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    auto moves = board.getLegalMoves(isMaximizing);
    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (const auto& move : moves) {
        board.applyMove(move.first, move.second, move.first, move.second);
        int score = minimax(board, depth - 1, !isMaximizing);
        board.undoMove();

        if (isMaximizing) {
            bestScore = std::max(bestScore, score);
        } else {
            bestScore = std::min(bestScore, score);
        }
    }

    return bestScore;
}

int main() {
    // Create a ChessBoard instance
    ChessBoard board;

    // Place some pieces on the board for testing
    board.placePiece(0, 0, std::make_shared<King>(0, 0)); // King for maximizing player
    board.placePiece(7, 7, std::make_shared<EnemyKing>(7, 7)); // Enemy King
    board.placePiece(4, 4, std::make_shared<Bishop>(4, 4)); // Bishop for maximizing player

    // Display the board
    board.displayBoard();

    // Evaluate the board
    int score = evaluateBoard(board);
    std::cout << "Board evaluation score: " << score << std::endl;

    // Test the minimax algorithm
    int minimaxScore = minimax(board, 3, true);
    std::cout << "Minimax score: " << minimaxScore << std::endl;

    return 0;
}

