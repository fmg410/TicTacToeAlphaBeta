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

    bool set(unsigned int column, unsigned int row, unsigned char value);

    unsigned char get(unsigned int column, unsigned int row);

    unsigned int getBoardSize() const;

    void resize(unsigned int N);

    void reset();

    std::vector<std::pair<unsigned int, unsigned int>> getEmptyCells() const;

    bool isFull() const;

    bool set(std::pair<unsigned int, unsigned int> move, unsigned char value);

    bool isTaken(unsigned int column, unsigned int row) const;

    bool isTaken(std::pair<unsigned int, unsigned int> move) const;
};

#endif // !BOARD_HPP