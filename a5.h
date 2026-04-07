#pragma once
#include <string>
#include <vector>
#include <iostream>

enum class Piece{
    Empty,
    Player1,
    Player2,
    Player1Anvil,
    Player2Anvil,
};

class Player{
    private:
        std::string playerName;
        std::string playerSymbol; // Will still enforce one letter, but string makes concatenation easier down the line
        bool hasAnvil;
        bool isComputer;
    public:
        Player(){};
        ~Player(){};
        bool getHasAnvil() const;
        std::string getPlayerSymbol() const;
        std::string getPlayerName() const;
        std::string getPlayerSymbolFormatted(bool isAnvil, int line) const;
        bool useAnvil();

};

class GameState{
    private:
        bool isPVP;
        Player player1;
        Player player2;
        
        const int ROWS = 6;
        const int COLS = 7;
        std::vector<std::vector<Piece>> board;

        

        bool isValidMove() const;
    public:
        GameState();
        GameState(Player player1, Player player2);
        ~GameState();
        void renderGame() const;
        bool makeMove(int col, Piece piece); //boolean so that isValidMove() can return to main
        bool checkWin() const;
        bool checkTie() const;
};