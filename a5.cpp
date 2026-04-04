#include <string>
#include <vector>
#include <iostream>


#include "a5.h"

using namespace std;


int main(){

    
    return 0;
}

// ==========================================
// PLAYER CLASS FUNCTION DEFINITIONS
// ==========================================

Player::Player(){};
Player::~Player(){};
bool Player::getHasAnvil() const{
    return hasAnvil;
} const;
std::string Player::getPlayerSymbol(bool isAnvil, int line) const{
    if(isAnvil && line == 1){
        return (playerSymbol + "A" + playerSymbol);
    } else{
        return (playerSymbol + playerSymbol + playerSymbol)
    }
} ;
std::string Player::getPlayerName() const{};
void Player::useAnvil() {};

// ==========================================
// GAMESTATE CLASS FUNCTION DEFINITIONS
// ==========================================

bool GameState::isValidMove() const{};

GameState::GameState() : board(ROWS, std::vector<Piece>(COLS, Piece::Empty)) {

};
GameState::GameState(string player1Symbol, string player2Symbol ,bool player2IsComputer) : GameState(), {

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
                    cout << player1.getPlayerSymbol(false, line);
                } if(board[r][c] == Piece::Player2){
                    cout << player2.getPlayerSymbol(false, line);
                } if(board[r][c] == Piece::Player1Anvil){
                    cout << player1.getPlayerSymbol(true, line);
                } if(board[r][c] == Piece::Player1Anvil){
                    cout << player1.getPlayerSymbol(true, line);
                } 
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
};
bool GameState::makeMove(int col, Piece piece){ //boolean so that isValidMove() can return to main

}; 
bool GameState::checkWin() const{};
bool GameState::checkTie() const{};