#ifndef BOARD_HPP
#define BOARD_HPP

#include <utility>
#include <vector>

class Board
{
    unsigned int _N{};

public:
    std::vector<unsigned char> board{};

    Board(unsigned int N);

    void set(unsigned int column, unsigned int row, unsigned char value);

    unsigned char get(unsigned int column, unsigned int row);

    unsigned int getBoardSize() const;

    void resize(unsigned int N);

    void reset();

    std::vector<std::pair<unsigned int, unsigned int>> getEmptyCells() const;

    bool isFull() const;

    void set(std::pair<unsigned int, unsigned int> move, unsigned char value);
};

#endif // !BOARD_HPP