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

bool GameState::isValidMove() const{

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
bool GameState::makeMove(int col, Piece piece){ //boolean so that isValidMove() can return to main

}; 
bool GameState::checkWin() const{
    
};
bool GameState::checkTie() const{
    for(int i = 0; i < COLS; i++){
        if(board[0][i] == Piece::Empty){
            return true;
        }
    }
    return false;
};