#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "a5.h"

using namespace std;

// ==========================================
// FORWARD DECLARATIONS
// ==========================================
bool samePlayer(Piece a, Piece b);
void clearInput();
void titleScreen();

// ==========================================
// MAIN
// ==========================================

int main() {
    srand(time(nullptr));

    bool playAgain = true;
    while (playAgain) {
        titleScreen();

        // --- Game Mode Selection ---2
        int gameMode = 0;
        while (true) {
            cout << "Choose a game mode:" << endl;
            cout << "  1. Play against the Computer" << endl;
            cout << "  2. Play against another Player" << endl;
            cout << "Enter your choice (1 or 2): ";
            if (cin >> gameMode && (gameMode == 1 || gameMode == 2)) {
                clearInput();
                break;
            }
            cout << "Invalid choice. Please enter 1 or 2." << endl << endl;
            clearInput();
        }

        Player player1, player2;
        int firstTurn = 1;
        bool isPVPmode = (gameMode == 2);

        if (!isPVPmode) {
            // --- Computer Game Setup ---
            string name;
            cout << endl << "Enter your name: ";
            getline(cin, name);

            player1 = Player(name, "X");
            player2 = Player("Computer", "O");
            player2.setIsComputer(true);

            int turnChoice = 0;
            while (true) {
                cout << endl;
                cout << "Who should go first?" << endl;
                cout << "  1. " << player1.getPlayerName() << " goes first" << endl;
                cout << "  2. Computer goes first" << endl;
                cout << "  3. Randomly decide" << endl;
                cout << "Enter your choice (1-3): ";
                if (cin >> turnChoice && turnChoice >= 1 && turnChoice <= 3) {
                    clearInput();
                    break;
                }
                cout << "Invalid choice." << endl;
                clearInput();
            }

            if (turnChoice == 2) {
                firstTurn = 2;
            } else if (turnChoice == 3) {
                firstTurn = (rand() % 2) + 1;
                if (firstTurn == 1)
                    cout << endl << player1.getPlayerName() << " goes first!" << endl;
                else
                    cout << endl << "Computer goes first!" << endl;
            }

        } else {
            // --- PvP Setup ---
            string name1, name2;
            cout << endl << "Enter name for Player 1: ";
            getline(cin, name1);
            cout << "Enter name for Player 2: ";
            getline(cin, name2);

            player1 = Player(name1, "X");
            player2 = Player(name2, "O");
        }

        // Create the game and show initial board
        GameState game(player1, player2);
        game.setIsPVP(isPVPmode);
        game.setCurrentTurn(firstTurn);
        game.renderGame();

        // --- Main Game Loop ---
        bool gameOver = false;
        while (!gameOver) {
            Player& current = game.getCurrentPlayer();
            cout << endl << current.getPlayerName() << "'s turn." << endl;

            if (current.getIsComputer()) {
                // Computer: random valid column
                int col = game.getRandomMove();
                if (col == -1) break; // should never happen unless tied, which is handled
                Piece piece = game.getCurrentPiece(false);
                game.makeMove(col, piece);
                cout << "Computer drops in column " << (col + 1) << "." << endl;

            } else {
                // Human turn
                bool moveMade = false;
                while (!moveMade) {
                    cout << "Enter column (1-7)";
                    if (current.getHasAnvil()) cout << " or 'a' for anvil";
                    cout << ": ";

                    string input;
                    cin >> input;

                    if (input == "a" || input == "A") {
                        if (!current.getHasAnvil()) {
                            cout << "You already used your anvil!" << endl;
                            continue;
                        }
                        cout << "Anvil column (1-7): ";
                        int col;
                        if (!(cin >> col) || col < 1 || col > 7) {
                            cout << "Invalid column." << endl;
                            clearInput();
                            continue;
                        }
                        col--;
                        if (game.makeMove(col, game.getCurrentPiece(true))) {
                            current.useAnvil();
                            moveMade = true;
                        } else {
                            cout << "That column is full." << endl;
                        }
                    } else {
                        int col;
                        try {
                            col = stoi(input);
                        } catch (...) {
                            cout << "Invalid input. Enter a number 1-7." << endl;
                            continue;
                        }
                        if (col < 1 || col > 7) {
                            cout << "Invalid column. Enter 1-7." << endl;
                            continue;
                        }
                        col--;
                        if (game.makeMove(col, game.getCurrentPiece(false))) {
                            moveMade = true;
                        } else {
                            cout << "Column " << (col + 1) << " is full." << endl;
                        }
                    }
                }
            }

            game.renderGame();

            if (game.checkWin()) {
                cout << endl;
                cout << "============================================" << endl;
                cout << "  " << game.getCurrentPlayer().getPlayerName()
                     << " wins! Congratulations!" << endl;
                cout << "============================================" << endl;
                gameOver = true;
            } else if (game.checkTie()) {
                cout << endl;
                cout << "============================================" << endl;
                cout << "  It's a tie! The board is full." << endl;
                cout << "============================================" << endl;
                gameOver = true;
            } else {
                game.switchTurn();
            }
        }

        // Play again?
        char again;
        while (true) {
            cout << endl << "Play again? (y/n): ";
            if (cin >> again && (again == 'y' || again == 'Y'
                              || again == 'n' || again == 'N')) {
                clearInput();
                break;
            }
            cout << "Please enter y or n." << endl;
            clearInput();
        }
        playAgain = (again == 'y' || again == 'Y');
    }

    cout << endl << "Thanks for playing Connect Four Plus! Goodbye!" << endl;
    return 0;
}

// ==========================================
// HELPER FUNCTIONS
// ==========================================

// Returns true if two pieces belong to the same player (anvils count)
bool samePlayer(Piece a, Piece b) {
    if (a == Piece::Empty || b == Piece::Empty) return false;
    if ((a == Piece::Player1 || a == Piece::Player1Anvil) &&
        (b == Piece::Player1 || b == Piece::Player1Anvil)) return true;
    if ((a == Piece::Player2 || a == Piece::Player2Anvil) &&
        (b == Piece::Player2 || b == Piece::Player2Anvil)) return true;
    return false;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void titleScreen() {
    cout << endl;
    cout << "============================================" << endl;
    cout << "     C O N N E C T   F O U R   P L U S     " << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "  Welcome to Connect Four Plus!" << endl;
    cout << endl;
    cout << "  RULES:" << endl;
    cout << "  - Players take turns dropping pieces into" << endl;
    cout << "    a 7-column, 6-row grid." << endl;
    cout << "  - Pieces fall to the lowest available" << endl;
    cout << "    spot in the chosen column." << endl;
    cout << "  - First to connect FOUR in a row" << endl;
    cout << "    (horizontally, vertically, or" << endl;
    cout << "    diagonally) wins!" << endl;
    cout << "  - If the board fills up, it's a tie." << endl;
    cout << endl;
    cout << "  SPECIAL - THE ANVIL:" << endl;
    cout << "  - Each player gets ONE anvil per game." << endl;
    cout << "  - When dropped, the anvil DESTROYS all" << endl;
    cout << "    pieces in that column and lands at" << endl;
    cout << "    the bottom." << endl;
    cout << "  - The anvil counts as your piece for" << endl;
    cout << "    connecting four." << endl;
    cout << "  - Cannot drop an anvil into a full column." << endl;
    cout << endl;
    cout << "============================================" << endl;
    cout << endl;
}

// ==========================================
// PLAYER CLASS DEFINITIONS
// ==========================================

Player::Player() {}

Player::Player(string playerName, string playerSymbol)
    : playerName(playerName), playerSymbol(playerSymbol) {}

Player::~Player() {}

bool Player::getHasAnvil() const { return hasAnvil; }
string Player::getPlayerSymbol() const { return playerSymbol; }
string Player::getPlayerName() const { return playerName; }

string Player::getPlayerSymbolFormatted(bool isAnvil, int line) const {
    if (isAnvil && line == 1) {
        return playerSymbol + "A" + playerSymbol;
    }
    return playerSymbol + playerSymbol + playerSymbol;
}

bool Player::useAnvil() {
    if (hasAnvil) {
        hasAnvil = false;
        return true;
    }
    return false;
}

void Player::setIsComputer(bool val) { isComputer = val; }
bool Player::getIsComputer() const { return isComputer; }

// ==========================================
// GAMESTATE CLASS DEFINITIONS
// ==========================================

GameState::GameState()
    : board(ROWS, vector<Piece>(COLS, Piece::Empty)) {
    lastMove = {0, 0};
}

GameState::GameState(Player p1, Player p2) : GameState() {
    player1 = p1;
    player2 = p2;
}

GameState::~GameState() {}

bool GameState::isValidMove(int col) const {
    if (col < 0 || col >= COLS) return false;
    return board[0][col] == Piece::Empty;
}

void GameState::renderGame() const {
    cout << endl;

    // Column headers
    cout << "   ";
    for (int c = 0; c < COLS; c++) {
        cout << "  " << (c + 1) << "   ";
    }
    cout << endl;

    // Top border
    cout << "  +";
    for (int c = 0; c < COLS; c++) {
        cout << "-----+";
    }
    cout << endl;

    // Board rows (each row is 3 lines tall for "big" display)
    for (int r = 0; r < ROWS; r++) {
        for (int line = 0; line < 3; line++) {
            cout << "  |";
            for (int c = 0; c < COLS; c++) {
                if (board[r][c] == Piece::Empty) {
                    cout << "     ";
                } else if (board[r][c] == Piece::Player1) {
                    cout << " " << player1.getPlayerSymbolFormatted(false, line) << " ";
                } else if (board[r][c] == Piece::Player2) {
                    cout << " " << player2.getPlayerSymbolFormatted(false, line) << " ";
                } else if (board[r][c] == Piece::Player1Anvil) {
                    cout << " " << player1.getPlayerSymbolFormatted(true, line) << " ";
                } else if (board[r][c] == Piece::Player2Anvil) {
                    cout << " " << player2.getPlayerSymbolFormatted(true, line) << " ";
                }
                cout << "|";
            }
            cout << endl;
        }
        // Row separator
        cout << "  +";
        for (int c = 0; c < COLS; c++) {
            cout << "-----+";
        }
        cout << endl;
    }

    // Legend
    cout << endl;
    cout << "  " << player1.getPlayerName() << " = ["
         << player1.getPlayerSymbol() << "]";
    if (player1.getHasAnvil()) cout << " (anvil ready)";
    cout << "    " << player2.getPlayerName() << " = ["
         << player2.getPlayerSymbol() << "]";
    if (player2.getHasAnvil()) cout << " (anvil ready)";
    cout << endl;
}

bool GameState::checkWin() const {
    Piece currentPiece = board[lastMove.row][lastMove.col];
    if (currentPiece == Piece::Empty) return false;

    const int directions[4][2] = {
        {0, 1},   // Horizontal
        {1, 0},   // Vertical
        {1, 1},   // Diagonal (\)
        {1, -1}   // Diagonal (/)
    };

    for (int i = 0; i < 4; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        int count = 1;

        // Forward
        int r = lastMove.row + dRow;
        int c = lastMove.col + dCol;
        while (r >= 0 && r < ROWS && c >= 0 && c < COLS
               && samePlayer(board[r][c], currentPiece)) {
            count++;
            r += dRow;
            c += dCol;
        }

        // Backward
        r = lastMove.row - dRow;
        c = lastMove.col - dCol;
        while (r >= 0 && r < ROWS && c >= 0 && c < COLS
               && samePlayer(board[r][c], currentPiece)) {
            count++;
            r -= dRow;
            c -= dCol;
        }

        if (count >= 4) return true;
    }
    return false;
}

bool GameState::checkTie() const {
    for (int i = 0; i < COLS; i++) {
        if (board[0][i] == Piece::Empty) return false;
    }
    return true;
}

bool GameState::makeMove(int col, Piece piece) {
    if (!isValidMove(col)) return false;

    if (piece == Piece::Player1Anvil || piece == Piece::Player2Anvil) {
        // Anvil: destroy all pieces in column, land at bottom
        for (int row = 0; row < ROWS; row++) {
            board[row][col] = Piece::Empty;
        }
        board[ROWS - 1][col] = piece;
        lastMove.row = ROWS - 1;
        lastMove.col = col;
    } else {
        // Regular piece: drop to lowest empty slot
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == Piece::Empty) {
                board[row][col] = piece;
                lastMove.row = row;
                lastMove.col = col;
                break;
            }
        }
    }
    return true;
}

void GameState::switchTurn() {
    currentTurn = (currentTurn == 1) ? 2 : 1;
}

int GameState::getCurrentTurn() const { return currentTurn; }
void GameState::setCurrentTurn(int turn) { currentTurn = turn; }

Player& GameState::getCurrentPlayer() {
    return (currentTurn == 1) ? player1 : player2;
}

const Player& GameState::getPlayer1() const { return player1; }
const Player& GameState::getPlayer2() const { return player2; }

Piece GameState::getCurrentPiece(bool isAnvil) const {
    if (currentTurn == 1) {
        return isAnvil ? Piece::Player1Anvil : Piece::Player1;
    }
    return isAnvil ? Piece::Player2Anvil : Piece::Player2;
}

int GameState::getRandomMove() const {
    vector<int> valid = getValidColumns();
    if (valid.empty()) return -1;
    return valid[rand() % valid.size()];
}

vector<int> GameState::getValidColumns() const {
    vector<int> valid;
    for (int c = 0; c < COLS; c++) {
        if (isValidMove(c)) valid.push_back(c);
    }
    return valid;
}

bool GameState::getIsPVP() const { return isPVP; }
void GameState::setIsPVP(bool pvp) { isPVP = pvp; }
