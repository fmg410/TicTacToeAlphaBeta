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
        std::pair<int, Move> bestMove = minimax(winCondition, playerSymbol, botSymbol, 0, lastMove, true, tempBoard, availableMoves);

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
std::pair<int, Move> minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth, Move lastMove,
            bool maximizingPlayer,
            Board& board, std::vector<Move>& availableMoves, int alpha,
            int beta)
{
    std::cout << depth << '\n';
    // Terminating condition. i.e
    // leaf node is reached
    unsigned char winner = verifyGameOver(board, lastMove, winCondition);
    if (winner || board.isFull())
    {
        if(winner == botSymbol)
            return std::make_pair(std::max(10000 / (depth + 1), 1), lastMove);
        else if(winner == playerSymbol)
            return std::make_pair(std::min(-10000 / (depth + 1), -1), lastMove);
        else
            return std::make_pair(0, lastMove);
    }

    std::pair<int, Move> bestMove;
    if(maximizingPlayer)
        bestMove.first = std::numeric_limits<int>::min();
    else
        bestMove.first = std::numeric_limits<int>::max();
    for (auto&& currentMove : availableMoves)
    {
        if(board.isTaken(currentMove))
            continue;

        board.set(currentMove, maximizingPlayer ? botSymbol : playerSymbol);

        if (maximizingPlayer)
        {
            //int best = std::numeric_limits<int>::min();

            // Recur for left and
            // right children
            auto tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1, currentMove,
                            false, board, availableMoves, alpha, beta);
            bestMove = (bestMove.first < tempMove.first) ? tempMove : bestMove;
            //best = std::max(best, bestMove.first);
            alpha = std::max(alpha, bestMove.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
            {
                board.set(currentMove, '\0');
                break;
            }

        }
        else
        {
            //int best = std::numeric_limits<int>::max();

            // Recur for left and
            // right children
            auto tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1, currentMove,
                            true, board, availableMoves, alpha, beta);
            bestMove = (bestMove.first > tempMove.first) ? tempMove : bestMove;
            beta = std::min(beta, bestMove.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
            {
                board.set(currentMove, '\0');
                break;
            }
        }
        board.set(currentMove, '\0');
    }
    return bestMove;
}