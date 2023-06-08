#include "Board.hpp"
#include <algorithm>

Board::Board(unsigned int N)
: _N(N)
{
    board.resize(N * N, '\0');
}

void Board::set(unsigned int column, unsigned int row, unsigned char value)
{
    board[column * _N + row] = value;
}

unsigned char Board::get(unsigned int column, unsigned int row)
{
    if(column >= _N || row >= _N)
        return '\1';
    return board[column * _N + row];
}

unsigned int Board::getBoardSize() const
{
    return _N;
}

void Board::resize(unsigned int N)
{
    _N = N;
    board.resize(N * N, '\0');
}

void Board::reset()
{
    std::fill(board.begin(), board.end(), '\0');
}

std::vector<std::pair<unsigned int, unsigned int>> Board::getEmptyCells() const
{
    std::vector<std::pair<unsigned int, unsigned int>> emptyCells;
    for(unsigned int i = 0; i < _N; ++i)
    {
        for(unsigned int j = 0; j < _N; ++j)
        {
            if(board[i * _N + j] == '\0')
                emptyCells.push_back(std::make_pair(i, j));
        }
    }
    return emptyCells;
}

bool Board::isFull() const
{
    for(unsigned int i = 0; i < _N; ++i)
    {
        for(unsigned int j = 0; j < _N; ++j)
        {
            if(board[i * _N + j] == '\0')
                return false;
        }
    }
    return true;
}

void Board::set(std::pair<unsigned int, unsigned int> move, unsigned char value)
{
    set(move.first, move.second, value);
}