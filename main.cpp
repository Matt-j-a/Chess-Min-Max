#include "ChessBoard.cpp"
#include "Piece.cpp"
#include <iostream>

int main() {
    // Create a chessboard
    ChessBoard board;
    //Minmax minmaxm
    // Place pieces on the board
    std::cout << "Placing pieces on the board...\n";
    board.placePiece(0, 0, "K"); // Player's King
    board.placePiece(4, 4, "E"); // Enemy's King

    // Display the initial board
    std::cout << "Initial Board:\n";
    board.displayBoard();

    // Test getLegalMoves
    std::cout << "\nLegal moves for Player's King (K):\n";
    auto legalMoves = board.getLegalMoves(true);
    for (const auto& move : legalMoves) {
        std::cout << "(" << move.first + 1 << ", " << static_cast<char>(move.second + 'A') << ")\n";
    }

    // Test applyMove
   // Assuming you already have the logic for getLegalMoves...
if (!legalMoves.empty()) {
    std::cout << "\nApplying move for Player's King to first legal position...\n";
    int oldRow = 0, oldCol = 0; // Initial position of Player's King
    int newRow = legalMoves[0].first, newCol = legalMoves[0].second;

    // Apply the move
    board.applyMove(oldRow, oldCol, newRow, newCol, "K");  // Make sure to pass the symbol for the piece
    board.displayBoard();
}

// Test undo
std::cout << "\nUndoing the last move...\n";
board.undoMove();  // Simply call undoMove without parameters
board.displayBoard();

    return 0;
}
