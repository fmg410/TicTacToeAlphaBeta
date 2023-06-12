#include "Game.hpp"

Game::Game(unsigned int N, unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol)
: board(N)
, winCondition(winCondition)
, playerSymbol(playerSymbol)
, botSymbol(botSymbol)
{}

void Game::reset()
{
    board.reset();
    gameOver = false;
    playerTurn = false;
}

void Game::resizeBoard(unsigned int N)
{
    board.resize(N);
}

bool Game::isPlayerTurn() const
{
    return playerTurn;
}

bool Game::isGameOver() const
{
    return gameOver;
}

unsigned int Game::getBoardSize()
{
    return board.getBoardSize();
}

void Game::setPlayerTurn(bool _playerTurn)
{
    playerTurn = _playerTurn;
}

void Game::setWinCondition(int _winCondition)
{
    winCondition = _winCondition;
}

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

int minimax(unsigned int winCondition, unsigned char playerSymbol, unsigned char botSymbol, int depth, Move lastMove,
            bool maximizingPlayer,
            Board& board, std::vector<Move>& availableMoves, int alpha,
            int beta)
{
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
            int tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1, currentMove,
                            false, board, availableMoves, alpha, beta);
            bestMove = std::max(bestMove, tempMove);
            alpha = std::max(alpha, bestMove);

            if (beta <= alpha)
            {
                board.set(currentMove, '\0');
                break;
            }

        }
        else
        {
            auto tempMove = minimax(winCondition, playerSymbol, botSymbol, depth + 1, currentMove,
                            true, board, availableMoves, alpha, beta);
            bestMove = std::min(bestMove, tempMove);
            beta = std::min(beta, bestMove);

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
    int bestVal = std::numeric_limits<int>::min();
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
    }

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

void Game::displayWinner()
{
    char winner = verifyGameOver(board, lastMove, winCondition);
    if(winner != '\1')
        std::cout << "Wygrywa " << (winner == botSymbol ? "komputer" : "gracz") << "!" << std::endl;
    else
        std::cout << "Remis!" << std::endl;
}