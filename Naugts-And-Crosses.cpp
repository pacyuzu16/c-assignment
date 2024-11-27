#include <iostream>
#include <vector> // dynamic array that can change size as needed.
using namespace std;

// Function declarations for modularity and readability
void displayBoard(const vector<char>& board);       // Display the game board
bool isValidMove(const vector<char>& board, int move); // Validate the player's move
bool checkWin(const vector<char>& board, char player); // Check if a player has won
bool isBoardFull(const vector<char>& board);        // Check if the board is full (draw condition)
void playGame();                                    // Main game logic
void displayInstructions();
int main() {
     displayInstructions();
    char playAgain = 'y'; // Option for replaying the game
    do {
        playGame(); // Start the game
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain; // Ask the player if they want to play again
    } while (playAgain == 'y' || playAgain == 'Y'); // Continue if the player says 'y'
    return 0;
}

// Function to display the Tic-Tac-Toe board
void displayBoard(const vector<char>& board) {
    // Display the 3x3 board layout using the values in the board vector
    cout << "\n";
    for (int i = 0; i < 9; i += 3) { // Iterate through rows (3 cells at a time)
        cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << "\n"; // Display a row
        if (i < 6) cout << "---|---|---\n"; // Add a separator after each row except the last
    }
    cout << "\n";
}

// Function to check if a move is valid
bool isValidMove(const vector<char>& board, int move) {
    // A valid move is within 1-9 and targets an unoccupied cell
    return move >= 1 && move <= 9 && board[move - 1] == '0' + move;
}

// Function to check if a player has won
bool checkWin(const vector<char>& board, char player) {
    // Define the 8 possible winning patterns: rows, columns, diagonals
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    // Check if any winning pattern matches the current player's marks
    for (auto& pattern : winPatterns) {
        if (board[pattern[0]] == player &&
            board[pattern[1]] == player &&
            board[pattern[2]] == player) {
            return true; // Player wins if all 3 cells in a pattern match their mark
        }
    }
    return false; // No winning pattern found
}

// Function to check if the board is full
bool isBoardFull(const vector<char>& board) {
    // If any cell is still a number (not 'X' or 'O'), the board is not full
    for (const char& cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true; // All cells are occupied
}

// Main game logic
void playGame() {
    // Initialize the game board with numbers 1-9
    vector<char> board(9);
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;

    char currentPlayer = 'X'; // 'X' always starts the game
    int move; // Variable to hold the player's move

    while (true) {
        displayBoard(board); // Show the current state of the board

        // Prompt the current player for their move
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        if (!(cin >> move)) { // Handle invalid input (e.g., non-integer values)
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            cin.clear();             // Clear the error flag
            cin.ignore(1000, '\n');  // Discard invalid input
            continue; // Skip to the next iteration to prompt again
        }

        // Validate the move
        if (!isValidMove(board, move)) {
            cout << "Invalid move. Please try again.\n";
            continue; // Skip to the next iteration if the move is invalid
        }

        // Make the move
        board[move - 1] = currentPlayer;

        // Check for a win condition
        if (checkWin(board, currentPlayer)) {
            displayBoard(board); // Display the final board state
            cout << "Player " << currentPlayer << " wins!\n";
            break; // Exit the game loop
        }

        // Check for a draw (board is full, no winner)
        if (isBoardFull(board)) {
            displayBoard(board); // Display the final board state
            cout << "It's a draw!\n";
            break; // Exit the game loop
        }

        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}
void displayInstructions() {
    cout << "Welcome to Noughts and Crosses (Tic-Tac-Toe)!" << endl;
    cout << "Instructions:" << endl;
    cout << "1. The game is played on a 3x3 grid." << endl;
    cout << "2. Player 1 is 'X' and Player 2 is 'O'." << endl;
    cout << "3. Take turns to place your mark on an empty cell." << endl;
    cout << "4. The first player to get three in a row wins!" << endl;
    cout << "5. If all cells are filled without a winner, it's a draw." << endl;
    cout << "Let's begin!\n" << endl;
}
