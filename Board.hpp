#ifndef BOARD_HPP
#define BOARD_HPP

#include <utility>
#include <vector>

using Move = std::pair<unsigned int, unsigned int>;

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

    std::vector<Move> getEmptyCells() const;

    bool isFull() const;

    bool set(Move move, unsigned char value);

    bool isTaken(unsigned int column, unsigned int row) const;

    bool isTaken(Move move) const;

    bool isEmpty() const;

    unsigned char get(Move move);
};

#endif // !BOARD_HPP