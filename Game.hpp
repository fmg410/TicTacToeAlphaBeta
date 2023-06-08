#ifndef GAME_HPP
#define GAME_HPP

#include <utility>
#include "Board.hpp"
#include <algorithm>
#include <limits>
#include <iostream>

using Move = std::pair<unsigned int, unsigned int>;

char verifyGameOver(Board board, Move lastMove, int winCondition);
std::pair<int, Move> minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth,
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

    Game(unsigned int N = 3)
    : board(N)
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

    void playerMove(unsigned int column, unsigned int row);

    void botMove();

    /* void verifyGameOver()
    {
        if(gameOver)
            return;

        unsigned char symbol = board.get(lastMove.first, lastMove.second);
        unsigned int count = 0;
        Move tempMove = lastMove;

        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.first;
            ++count;
        }
        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            --tempMove.first;
            ++count;
        }
        if(count >= winCondition)
        {
            gameOver = true;
            return;
        }

        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.first;
            ++count;
        }
        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            --tempMove.first;
            ++count;
        }
        if(count >= winCondition)
        {
            gameOver = true;
            return;
        }

        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.second;
            ++count;
        }
        tempMove = lastMove;

        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.second;
            ++count;
        }
        if(count >= winCondition)
        {
            gameOver = true;
            return;
        }

        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.first;
            ++tempMove.second;
            ++count;
        }
        tempMove = lastMove;

        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            --tempMove.first;
            --tempMove.second;
            ++count;
        }
        if(count >= winCondition)
        {
            gameOver = true;
            return;
        }

        tempMove = lastMove;
        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            ++tempMove.first;
            --tempMove.second;
            ++count;
        }
        tempMove = lastMove;

        while(board.get(tempMove.first, tempMove.second) == symbol)
        {
            --tempMove.first;
            ++tempMove.second;
            ++count;
        }
        if(count >= winCondition)
        {
            gameOver = true;
            return;
        }
    } */

    void play();
};

#endif // !GAME_HPP