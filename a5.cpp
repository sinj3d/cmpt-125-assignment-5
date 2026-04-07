#include <string>
#include <vector>
#include <iostream>


#include "a5.h"

using namespace std;




int main(){
    
   bool playAgain = true;

    while (playAgain) {
        string player1;
        string player2;
        int gameMode;
        int turnChoice;

        // Title screen: game name, rules, anvil explanation
        titleScreen();

        // Ask for game mode
        cout << "Choose a game mode:\n";
        cout << "1. Play against the computer\n";
        cout << "2. Play against another player\n";
        cout << "Enter your choice: ";
        cin >> gameMode;

        if (gameMode == 1) {
            // Computer mode
            cout << "Enter your name: ";
            cin >> player1;

            player2 = "Computer";

            // Ask if player wants to go first, second, or random
            cout << "\nWho should go first?\n";
            cout << "1. " << player1 << " goes first\n";
            cout << "2. Computer goes first\n";
            cout << "3. Randomly decide\n";
            cout << "Enter your choice: ";
            cin >> turnChoice;

            // You can handle the actual setup inside this function later
            setupComputerGame(player1, player2, turnChoice);
        }
        else if (gameMode == 2) {
            // Player vs player mode
            cout << "Enter name for Player 1: ";
            cin >> player1;

            cout << "Enter name for Player 2: ";
            cin >> player2;

            // You can handle turn setup inside here if needed
            setupPlayerGame(player1, player2);
        }
        else {
            cout << "Invalid game mode. Restarting...\n\n";
            continue;
        }

        // Print starting board + legend
        printBoard();

        // Main game loop
        while (true) {
            // This function should later:
            // - ask for a move in an easy way (ex: choose a column)
            // - re-ask if the move is invalid
            // - handle full columns / bad input / invalid column numbers
            makeMove();

            // Print board after every move
            printBoard();

            if (checkWin()) {
                announceWinner();
                break;
            }

            if (checkTie()) {
                announceTie();
                break;
            }
        }

        // Ask if user wants to play again
        playAgain = askPlayAgain();
    }

 
    return 0;
}

// ==========================================
// HELPER FUNCTION DEFINITIONS
// ==========================================

void titleScreen();
void printBoard();

void setupComputerGame(string& playerName, string& computerName, int& turnChoice);
void setupPlayerGame(string& player1Name, string& player2Name);

void makeMove();
bool checkWin();
bool checkTie();

void announceWinner();
void announceTie();

bool askPlayAgain();

// ==========================================
// PLAYER CLASS FUNCTION DEFINITIONS
// ==========================================

Player::Player(){};
Player::~Player(){};
bool Player::getHasAnvil() const{
    return hasAnvil;
};
std::string Player::getPlayerSymbol() const{
    return playerSymbol;
};
std::string Player::getPlayerName() const{
    return playerName;
};
std::string Player::getPlayerSymbolFormatted(bool isAnvil, int line) const{
    if(isAnvil && line == 1){
        return (playerSymbol + "A" + playerSymbol);
    } else{
        return (playerSymbol + playerSymbol + playerSymbol);
    }
};
bool Player::useAnvil() {
    if(hasAnvil){
        hasAnvil = false;
        return true;
    
    }else{
        return false;
    }
    
};

// ==========================================
// GAMESTATE CLASS FUNCTION DEFINITIONS
// ==========================================

bool GameState::isValidMove(int col) const{
    return board[0][col] == Piece::Empty;
    
};

GameState::GameState() : board(ROWS, std::vector<Piece>(COLS, Piece::Empty)) {

};
GameState::GameState(Player player1, Player player2) : GameState() {

}

GameState::~GameState(){

};

void GameState::renderGame() const{
    for(int r = 0; r < ROWS; r++){
        for(int line = 0; line < 3; line ++){
            for(int c = 0; c < COLS; c++){
                if(board[r][c] == Piece::Empty){
                    cout << "   ";
                } if(board[r][c] == Piece::Player1){
                    cout << player1.getPlayerSymbolFormatted(false, line);
                } if(board[r][c] == Piece::Player2){
                    cout << player2.getPlayerSymbolFormatted(false, line);
                } if(board[r][c] == Piece::Player1Anvil){
                    cout << player1.getPlayerSymbolFormatted(true, line);
                } if(board[r][c] == Piece::Player1Anvil){
                    cout << player1.getPlayerSymbolFormatted(true, line);
                } 
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
};

bool GameState::checkWin() const{ // check 4 axes around the last piece. We use an array of directions to improve readability
    Piece currentPiece = board[lastMove.row][lastMove.col];
    if (currentPiece == Piece::Empty) return false;

    const int directions[4][2] = {
        {0, 1},   // Horizontal (Right)
        {1, 0},   // Vertical (Down)
        {1, 1},   // Diagonal (\)
        {1, -1}   // Diagonal (/)
    };

    for (int i = 0; i < size(directions); i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        
        int count = 1; // Start at 1 to include the piece that was just dropped

        // Check FORWARD along the vector
        int r = lastMove.row + dRow;
        int c = lastMove.col + dCol;
        while (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == currentPiece) {
            count++;
            r += dRow; // Move one step further forward
            c += dCol;
        }

        // Check BACKWARD along the vector
        r = lastMove.row - dRow;
        c = lastMove.col - dCol;
        while (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == currentPiece) {
            count++;
            r -= dRow; // Move one step further backward
            c -= dCol;
        }

        if (count >= 4) {
            return true;
        }
    }

    return false;

};

bool GameState::checkTie() const{ // check top row. If full, then tie
    for(int i = 0; i < COLS; i++){
        if(board[0][i] == Piece::Empty){
            return true;
        }
    }
    return false;
};

bool GameState::makeMove(int col, Piece piece){ //boolean so that isValidMove() can return to main
    
}; 
