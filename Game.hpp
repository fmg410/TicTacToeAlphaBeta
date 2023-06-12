#ifndef GAME_HPP
#define GAME_HPP

#include <utility>
#include "Board.hpp"
#include <algorithm>
#include <limits>
#include <iostream>

using Move = std::pair<unsigned int, unsigned int>;

char verifyGameOver(Board board, Move lastMove, int winCondition);
int minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth, Move lastMove,
            bool maximizingPlayer,
            Board& board, std::vector<Move>& availableMoves, int alpha = std::numeric_limits<int>::min(),
            int beta = std::numeric_limits<int>::max());

class Game
{
    public:
    Move lastMove;
    unsigned int winCondition = 3;
    unsigned char playerSymbol = 'X';
    unsigned char botSymbol = 'O';
    bool gameOver = false;
    bool playerTurn = false;

public:
    Board board;

    Game(unsigned int N = 3, unsigned int winCondition = 3, unsigned char playerSymbol = 'X', unsigned char botSymbol = 'O');

    void reset();

    void resizeBoard(unsigned int N);

    bool isPlayerTurn() const;

    bool isGameOver() const;

    void botMove();

    unsigned int getBoardSize();

    void displayBoard();

    void setPlayerTurn(bool _playerTurn);

    void setWinCondition(int _winCondition);

    void displayWinner();

    Move findBestMove();

    bool playerMove(unsigned int column, unsigned int row);
};

#endif // !GAME_HPP