#include "ChessBoard.cpp"
#include <iostream>
#include <limits>

//Evaluation function
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

// // Minimax function
// int minimax(ChessBoard& board, int depth, bool isMaximizing) {
//     if (depth == 0) {
//         return evaluateBoard(board);
//     }

//     auto moves = board.getLegalMoves(isMaximizing);
//     int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

//     for (const auto& move : moves) {
//         board.applyMove(move.first, move.second, move.first, move.second);
//         int score = minimax(board, depth - 1, !isMaximizing);
//         board.undoMove();

//         if (isMaximizing) {
//             bestScore = std::max(bestScore, score);
//         } else {
//             bestScore = std::min(bestScore, score);
//         }
//     }

//     return bestScore;
// }

// std::pair<int, int> findBestMove(ChessBoard& board, bool isMaximizing, int depth, std::string& bestPieceSymbol, ChessBoard::Cell& bestCell) {
//     int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
//     std::pair<int, int> bestMove = {-1, -1}; // Default invalid move
//     bestPieceSymbol = ""; // Track the symbol of the piece making the best move

//     auto moves = board.getLegalMoves(isMaximizing);
//     for (const auto& move : moves) {
//         int oldRow = move.first;
//         int oldCol = move.second;
//         auto piece = board.getCell(oldRow, oldCol);

//         for (int dRow = -1; dRow <= 1; ++dRow) {
//             for (int dCol = -1; dCol <= 1; ++dCol) {
//                 int newRow = oldRow + dRow;
//                 int newCol = oldCol + dCol;

//                 // Apply move
//                 board.applyMove(oldRow, oldCol, newRow, newCol);

//                 // Evaluate using minimax
//                 int score = minimax(board, depth - 1, !isMaximizing);

//                 // Undo move
//                 board.undoMove();

//                 if ((isMaximizing && score > bestScore) || (!isMaximizing && score < bestScore)) {
//                     bestScore = score;
//                     bestMove = {newRow, newCol};
//                     bestPieceSymbol = piece ? piece->getSymbol() : ""; // Track the piece symbol
//                     bestCell = board.getCellObject(newRow, newCol); // Track the best cell
//                 }
//             }
//         }
//     }

//     return bestMove;
// }

int main() {
    ChessBoard board;

    // Add some pieces to the board
    board.placePiece(0, 0, std::make_shared<King>(0, 0));
    board.placePiece(4, 5, std::make_shared<Bishop>(4, 5));
    int board_eval =  evaluateBoard(board);
    std::cout << board_eval;
    board.displayBoard();

     

    // Iterate through the board and print moves for each piece
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            auto piece = board.getCell(row, col);
            if (piece) {
                std::cout << "Piece " << piece->getSymbol() << " at (" << row + 1 << ", " << char('A' + col) << ") can move to: ";
                auto moves = piece->getLegalMoves(8);
                for (const auto& move : moves) {
                    std::cout << "(" << move.first + 1 << ", " << char('A' + move.second) << ") ";
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}

