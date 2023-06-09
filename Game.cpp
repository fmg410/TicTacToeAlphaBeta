#include "Game.hpp"





void Game::playerMove(unsigned int column, unsigned int row)
    {
        if(gameOver)
            return;

        if(!playerTurn)
            return;

        if (board.get(column, row) == '\0')
        {
            board.set(column, row, 'X');
            lastMove = std::make_pair(column, row);
            playerTurn = false;
        }
    }

void Game::botMove()
    {
        if(gameOver)
            return;
        if(playerTurn)
            return;

        /* for (unsigned int i = 0; i < board.getBoardSize(); ++i)
        {
            for (unsigned int j = 0; j < board.getBoardSize(); ++j)
            {
                if (board.get(i, j) == '\0')
                {
                    board.set(i, j, 'O');
                    return;
                }
            }
        } */

        std::vector<Move> availableMoves = board.getEmptyCells();
        Board tempBoard = board;
        std::pair<int, Move> bestMove = minimax(winCondition, playerSymbol, botSymbol, 0, true, tempBoard, availableMoves);

        board.set(bestMove.second, 'O');

        std::cout << "Bot move: " << bestMove.first << " " << bestMove.second.first << " " << bestMove.second.second << '\n';

        playerTurn = true;
    }

 void Game::play()
    {
        if(!playerTurn)
        {
            if(verifyGameOver(board, lastMove, winCondition))
            {
                gameOver = true;
                return;
            }
            botMove();
            if(verifyGameOver(board, lastMove, winCondition))
            {
                gameOver = true;
                return;
            }
        }
        if(gameOver)
            return;
    }

char verifyGameOver(Board board, Move lastMove, int winCondition)
{
    if(board.isFull())
        return '\1';

    unsigned char symbol = board.get(lastMove.first, lastMove.second);
    unsigned int count = 0;
    Move tempMove = lastMove;

    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        ++tempMove.first;
        ++count;
    }
    tempMove = lastMove;
    --tempMove.first;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        --tempMove.first;
        ++count;
    }
    if(count >= winCondition)
    {
        return symbol;
    }

    count = 0;
    tempMove = lastMove;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        ++tempMove.second;
        ++count;
    }
    tempMove = lastMove;
    --tempMove.second;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        --tempMove.second;
        ++count;
    }
    if(count >= winCondition)
    {
        return symbol;
    }

    count = 0;
    tempMove = lastMove;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        ++tempMove.first;
        ++tempMove.second;
        ++count;
    }
    tempMove = lastMove;
    --tempMove.first;
    --tempMove.second;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        --tempMove.first;
        --tempMove.second;
        ++count;
    }
    if(count >= winCondition)
    {
        return symbol;
    }

    count = 0;
    tempMove = lastMove;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        ++tempMove.first;
        --tempMove.second;
        ++count;
    }
    tempMove = lastMove;
    --tempMove.first;
    ++tempMove.second;
    while(board.get(tempMove.first, tempMove.second) == symbol)
    {
        --tempMove.first;
        ++tempMove.second;
        ++count;
    }
    if(count >= winCondition)
    {
        return symbol;
    }
    return '\0';
}

/* int minimax(int depth, int nodeIndex,
            bool maximizingPlayer,
            int values[], int alpha = std::numeric_limits<int>::min(),
            int beta = std::numeric_limits<int>::max()) */
std::pair<int, Move> minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth,
            bool maximizingPlayer,
            Board& board, std::vector<Move> availableMoves, int alpha,
            int beta)
{
    static int i = 0;
    // Terminating condition. i.e
    // leaf node is reached

    Move currentMove = availableMoves.at(availableMoves.size() - 1 - depth);
    std::cout << "Current move: " << currentMove.first << " " << currentMove.second << " " << availableMoves.size() - 1 - depth << '\n';
    board.set(currentMove, maximizingPlayer ? botSymbol : playerSymbol);
    unsigned char winner = verifyGameOver(board, currentMove, winCondition);
    if (winner || board.isFull())
    {
        board.set(currentMove, '\0');

        if(winner == botSymbol)
            return std::make_pair(std::max(10000 / (depth + 1), 1), currentMove);
        else if(winner == playerSymbol)
            return std::make_pair(std::min(-10000 / (depth + 1), -1), currentMove);
        else
            return std::make_pair(0, currentMove);
    }

    if (maximizingPlayer)
    {
        //int best = std::numeric_limits<int>::min();
        std::pair<int, Move> bestMove;
        bestMove.first = std::numeric_limits<int>::min();
        // Recur for left and
        // right children
        do {
            auto tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1,
                              false, board, availableMoves, alpha, beta);
            bestMove = (bestMove.first < tempMove.first) ? tempMove : bestMove;
            //best = std::max(best, bestMove.first);
            alpha = std::max(alpha, bestMove.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        } while(std::next_permutation(availableMoves.begin(), availableMoves.end() - 1 - depth));
        board.set(currentMove, '\0');
        return bestMove;
    }
    else
    {
        //int best = std::numeric_limits<int>::max();
        std::pair<int, Move> bestMove;
        bestMove.first = std::numeric_limits<int>::max();

        // Recur for left and
        // right children
        do {
            auto tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1,
                              true, board, availableMoves, alpha, beta);
            bestMove = (bestMove.first > tempMove.first) ? tempMove : bestMove;
            beta = std::min(beta, bestMove.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        } while(std::next_permutation(availableMoves.begin(), availableMoves.end() - 1 - depth));
        board.set(currentMove, '\0');
        return bestMove;
    }
}