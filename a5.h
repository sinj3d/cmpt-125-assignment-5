#include <string>
#include <vector>
#include <iostream>

class Player{
    private:
        bool hasAnvil;
    public:
        Player(){};
        ~Player(){};
        bool getHasAnvil() const;
        void useAnvil();

};

class GameState{
    private:
        bool isPVP;
        std::vector<std::vector<char>> gameState;
    public:
        GameState();
        ~GameState();
        void renderGame() const;
};