#include "ChessBoard.cpp"
#include "Piece.cpp"

int main() {
    // Create a chessboard
    ChessBoard board;

    // Create a player King at position (0, 0)
    King playerKing(0, 0);
    board.placePiece(playerKing.getRow(), playerKing.getCol(), playerKing.getSymbol());

    // Create an enemy King at position (4, 4)
    EnemyKing enemyKing(4, 4);
    board.placePiece(enemyKing.getRow(), enemyKing.getCol(), enemyKing.getSymbol());

    // Display the initial board
    std::cout << "Initial Board:" << std::endl;
    board.displayBoard();

    // Move the player King
    int newRow = 1, newCol = 1;
    if (playerKing.isLegalMove(newRow, newCol)) {
        if (board.movePiece(playerKing.getRow(), playerKing.getCol(), newRow, newCol, playerKing.getSymbol())) {
            playerKing.setPosition(newRow, newCol);
        }
    }

    // Display the board after moving the player King
    std::cout << "\nAfter Moving Player King:" << std::endl;
    board.displayBoard();

    // Move the enemy King
    newRow = 3, newCol = 3;
    if (enemyKing.isLegalMove(newRow, newCol)) {
        if (board.movePiece(enemyKing.getRow(), enemyKing.getCol(), newRow, newCol, enemyKing.getSymbol())) {
            enemyKing.setPosition(newRow, newCol);
        }
    }

    // Display the board after moving the enemy King
    std::cout << "\nAfter Moving Enemy King:" << std::endl;
    board.displayBoard();

    return 0;
}