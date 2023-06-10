#include "Game.hpp"

bool Game::playerMove(unsigned int column, unsigned int row)
{
    if(gameOver)
        return false;

    if(!playerTurn)
        return false;

    if (board.get(column, row) == '\0')
    {
        board.set(column, row, 'X');
        lastMove = std::make_pair(column, row);
        playerTurn = false;
        gameOver = verifyGameOver(board, lastMove, winCondition);
        return true;
    }
    return false;
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

    Move bestMove;
    if(board.isEmpty())
        bestMove = std::make_pair(0, 0);
    else
        bestMove =  findBestMove();

    if(board.get(bestMove) == '\0')
    {
        board.set(bestMove, 'O');
        lastMove = bestMove;
        playerTurn = true;
        gameOver = verifyGameOver(board, lastMove, winCondition);
    }
}

 void Game::play()
{
    if(gameOver)
    {
        reset();
    }
}

char verifyGameOver(Board board, Move lastMove, int winCondition)
{
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
    if(board.isFull())
        return '\1';
    return '\0';
}

/* int minimax(int depth, int nodeIndex,
            bool maximizingPlayer,
            int values[], int alpha = std::numeric_limits<int>::min(),
            int beta = std::numeric_limits<int>::max()) */
int minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth, Move lastMove,
            bool maximizingPlayer,
            Board& board, std::vector<Move>& availableMoves, int alpha,
            int beta)
{
    //std::cout << depth << '\n';
    // Terminating condition. i.e
    // leaf node is reached
    unsigned char winner = verifyGameOver(board, lastMove, winCondition);
    if (winner || board.isFull())
    {
        if(winner == botSymbol)
            return std::max(10000 - depth, 1);
        else if(winner == playerSymbol)
            return std::min(-10000 + depth, -1);
        else
            return 0;
    }

    int bestMove;
    if(maximizingPlayer)
        bestMove = std::numeric_limits<int>::min();
    else
        bestMove = std::numeric_limits<int>::max();
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
            int tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1, currentMove,
                            false, board, availableMoves, alpha, beta);
            bestMove = std::max(bestMove, tempMove);
            //best = std::max(best, bestMove.first);
            alpha = std::max(alpha, bestMove);

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
            bestMove = std::min(bestMove, tempMove);
            beta = std::min(beta, bestMove);

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

Move Game::findBestMove()
{
    int bestVal = std::numeric_limits<int>::min();;
    Move bestMove;
    bestMove.first = -1;
    bestMove.second = -1;

    std::vector<Move> availableMoves = board.getEmptyCells();
    Board tempBoard = board;

    for(auto&& currentMove : availableMoves)
    {
        tempBoard.set(currentMove, 'O');
        int move = minimax(winCondition, playerSymbol, botSymbol, 0, currentMove, false, tempBoard, availableMoves);
        if(move > bestVal)
        {
            bestVal = move;
            bestMove = currentMove;
        }
        tempBoard.set(currentMove, '\0');
        //std::cout << "Current move: " << currentMove.first << " " << currentMove.second << '\n';
    }


    //std::cout << "Bot move: " << bestMove.first << " " << bestMove.second << '\n';


    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.

    return bestMove;
}

void Game::displayBoard()
{
    int i = 0;
    for(auto&& cell : board.board)
    {
        std::cout << char((cell == 0 ? '_' : cell)) << " ";
        i++;
        if(i % board.getBoardSize() == 0)
            std::cout << '\n';
    }
}