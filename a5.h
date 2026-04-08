#pragma once
#include <string>
#include <vector>
#include <iostream>

enum class Piece {
    Empty,
    Player1,
    Player2,
    Player1Anvil,
    Player2Anvil,
};

struct Coordinate {
    int row;
    int col;
};

struct MoveOption {
    int col;
    bool useAnvil;
};


class Player {
private:
    std::string playerName;
    std::string playerSymbol;
    bool hasAnvil = true;
    bool isComputer = false;

public:
    Player();
    Player(std::string playerName, std::string playerSymbol);
    ~Player();

    bool getHasAnvil() const;
    std::string getPlayerSymbol() const;
    std::string getPlayerName() const;
    std::string getPlayerSymbolFormatted(bool isAnvil, int line) const;

    bool useAnvil();
    void setIsComputer(bool val);
    bool getIsComputer() const;
};

class GameState {
private:
    bool isPVP = true;
    Player player1;
    Player player2;
    int currentTurn = 1;

    const int ROWS = 6;
    const int COLS = 7;
    std::vector<std::vector<Piece>> board;

    Coordinate lastMove;

    bool isValidMove(int col) const;

public:
    GameState();
    GameState(Player player1, Player player2);
    ~GameState();

    void renderGame() const;
    bool checkWin() const;
    bool checkTie() const;
    bool makeMove(int col, Piece piece);

    void switchTurn();
    int getCurrentTurn() const;
    void setCurrentTurn(int turn);
    Player& getCurrentPlayer();
    const Player& getPlayer1() const;
    const Player& getPlayer2() const;
    Piece getCurrentPiece(bool isAnvil) const;
    int getRandomMove() const;
    std::vector<int> getValidColumns() const;
    std::vector<MoveOption> getAllLegalMoves() const;

    int evaluateWindow(const std::vector<Piece>& window) const;
    int evaluateBoard() const;
    int minimax(GameState state, int depth, int alpha, int beta, bool isMaximizingPlayer);
    MoveOption getBestMove(int depth);

    bool getIsPVP() const;
    void setIsPVP(bool pvp);
};