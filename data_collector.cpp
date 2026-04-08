/*
 * Names: Shenghua Jin, Luke Choi
 * SFU IDs: 301659564, 301658198
 * Emails: sja204@sfu.ca, esc9@sfu.ca
 *
 * Statement of Originality:
 * All the code and comments below are my (our) own original work. For any non-
 * original work, I (we) have provided citations above and in the comments with
 * enough detail so that someone can see the exact source and extent of the
 * borrowed work.
 *
 * In addition, I (we) have not shared this work with anyone else, and I (we) have
 * not seen solutions from other students, tutors, websites, books, etc.
 */

#include "data_collector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void generateDataset(int numGames, int depth, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return;
    }
    
    // Header for CSV
    for(int i=0; i<42; i++) outFile << "cell_" << i << ",";
    outFile << "p2_has_anvil,p1_has_anvil,best_move\n";
    
    cout << "Generating dataset of " << numGames << " games at depth " << depth << "..." << endl;
    
    for (int g = 0; g < numGames; g++) {
        if (g % 10 == 0) cout << "Game " << g << "/" << numGames << "..." << endl;
        
        Player p1("RandomBot", "X");
        Player p2("MinimaxBot", "O");
        p1.setIsComputer(true);
        p2.setIsComputer(true);
        
        GameState game(p1, p2);
        game.setIsPVP(false);
        game.setCurrentTurn((rand() % 2) + 1); // Randomize who goes first
        
        bool gameOver = false;
        while (!gameOver) {
            Player& current = game.getCurrentPlayer();
            
            if (current.getPlayerName() == "RandomBot") {
                // Random move for P1
                vector<MoveOption> legalMoves = game.getAllLegalMoves();
                if (legalMoves.empty()) break;
                
                MoveOption move = legalMoves[rand() % legalMoves.size()];
                Piece piece = game.getCurrentPiece(move.useAnvil);
                game.makeMove(move.col, piece);
                if (move.useAnvil) current.useAnvil();
            } else {
                // Minimax move for P2
                MoveOption bestMove = game.getBestMove(depth);
                if (bestMove.col == -1) break;
                
                // Extract state before making the move
                const auto& board = game.getBoard();
                for (int r = 0; r < game.getRows(); r++) {
                    for (int c = 0; c < game.getCols(); c++) {
                        Piece p = board[r][c];
                        int val = 0;
                        if (p == Piece::Player2 || p == Piece::Player2Anvil) val = 1; // P2 is 1 (our perspective)
                        else if (p == Piece::Player1 || p == Piece::Player1Anvil) val = -1; // P1 is -1
                        outFile << val << ",";
                    }
                }
                outFile << (game.getPlayer2().getHasAnvil() ? 1 : 0) << ",";
                outFile << (game.getPlayer1().getHasAnvil() ? 1 : 0) << ",";
                
                int moveLabel = bestMove.col + (bestMove.useAnvil ? 7 : 0);
                outFile << moveLabel << "\n";
                
                // Apply move
                Piece piece = game.getCurrentPiece(bestMove.useAnvil);
                game.makeMove(bestMove.col, piece);
                if (bestMove.useAnvil) current.useAnvil();
            }
            
            if (game.checkWin() || game.checkTie()) {
                gameOver = true;
            } else {
                game.switchTurn();
            }
        }
    }
    outFile.close();
    cout << "Dataset generation complete: " << filename << endl;
}
