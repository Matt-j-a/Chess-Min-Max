#include "ChessBoard.h"
#include "Piece.cpp"

#include <climits> // For INT_MIN and INT_MAX
#include <utility> // For std::pair

class MinMax {
private:
    static const int MAX_DEPTH = 3; // Depth for Min-Max

    // Evaluate the board state
    int evaluateBoard(const ChessBoard& board) const {
        int score = 0;
        // Example: Iterate through the board and calculate scores based on pieces
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                char cell = board.getCell(row, col); // Assume ChessBoard has getCell method
                if (cell == 'K') {
                    score += 10; // Example weight for King
                } else if (cell == 'E') {
                    score -= 10; // Example weight for Enemy King
                }
                // Add weights for other pieces as needed
            }
        }
        return score;
    }

public:
    // Min-Max algorithm
    int minMax(ChessBoard& board, int depth, bool isMaximizing) {
        if (depth == 0 /* or game over condition */) {
            return evaluateBoard(board);
        }

        if (isMaximizing) {
            int maxEval = INT_MIN;
            auto moves = board.getLegalMoves(isMaximizing); // Assume ChessBoard has getLegalMoves method
            for (const auto& move : moves) {
                int oldRow = move.first, oldCol = move.second;
                board.applyMove(oldRow, oldCol, move.first, move.second, "K"); // Apply move for 'K'
                int eval = minMax(board, depth - 1, false); // Minimize for the opponent
                board.undoMove(); // Undo the move
                maxEval = std::max(maxEval, eval);
            }
            return maxEval;
        } else {
            int minEval = INT_MAX;
            auto moves = board.getLegalMoves(isMaximizing); // Assume ChessBoard has getLegalMoves method
            for (const auto& move : moves) {
                int oldRow = move.first, oldCol = move.second;
                board.applyMove(oldRow, oldCol, move.first, move.second, "E"); // Apply move for 'E'
                int eval = minMax(board, depth - 1, true); // Maximize for the player
                board.undoMove(); // Undo the move
                minEval = std::min(minEval, eval);
            }
            return minEval;
        }
    }

    // Find the best move for the current player
    std::pair<int, int> findBestMove(ChessBoard& board, bool isMaximizing) {
        int bestScore = isMaximizing ? INT_MIN : INT_MAX;
        std::pair<int, int> bestMove;

        auto moves = board.getLegalMoves(isMaximizing);
        for (const auto& move : moves) {
            int oldRow = move.first, oldCol = move.second;
            board.applyMove(oldRow, oldCol, move.first, move.second, isMaximizing ? "K" : "E"); // Apply current move
            int moveScore = minMax(board, MAX_DEPTH - 1, !isMaximizing);
            board.undoMove(); // Undo the move

            if (isMaximizing && moveScore > bestScore) {
                bestScore = moveScore;
                bestMove = move;
            } else if (!isMaximizing && moveScore < bestScore) {
                bestScore = moveScore;
                bestMove = move;
            }
        }

        return bestMove;
    }
};
