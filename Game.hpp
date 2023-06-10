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

    Game(unsigned int N = 3, unsigned int winCondition = 3, unsigned char playerSymbol = 'X', unsigned char botSymbol = 'O')
    : board(N)
    , winCondition(winCondition)
    , playerSymbol(playerSymbol)
    , botSymbol(botSymbol)
    {}

    void reset()
    {
        board.reset();
        gameOver = false;
        playerTurn = false;
    }

    void resizeBoard(unsigned int N)
    {
        board.resize(N);
    }

    bool isPlayerTurn() const
    {
        return playerTurn;
    }

    bool isGameOver() const
    {
        return gameOver;
    }

    bool playerMove(unsigned int column, unsigned int row);

    void botMove();

    void play();

    Move findBestMove();

    unsigned int getBoardSize() { return board.getBoardSize(); }

    void displayBoard();

    void setPlayerTurn(bool _playerTurn) { playerTurn = _playerTurn; }

    void setWinCondition(int _winCondition) { winCondition = _winCondition; }
};

#endif // !GAME_HPP