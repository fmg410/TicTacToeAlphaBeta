#include "Game.hpp"
#include <iostream>
//#include "Board.hpp"
#include "Test.hpp"
int main()
{
    //Test test;
    Game game;
    std::vector<unsigned char> cells ={
    '\0', 'O', '\0',
    '\0', '\0', '\0',
    '\0', 'O', 'X' };
    game.board.board = cells;
    game.playerTurn = true;
    game.playerMove(1, 1);
    game.play();
    int i = 0;
    for(auto&& cell : game.board.board)
    {
        std::cout << char((cell == 0 ? '_' : cell)) << " ";
        i++;
        if(i % 3 == 0)
            std::cout << '\n';
    }
    //game.playerMove(2, 0);
    //game.play();
    for(auto&& cell : game.board.board)
    {
        std::cout << char((cell == 0 ? '_' : cell)) << " ";
        i++;
        if(i % 3 == 0)
            std::cout << '\n';
    }
    /* std::vector<int> v = {1};
    if(std::next_permutation(v.begin(), v.end()))
        std::cout << "yes";
    else
        std::cout << "no"; */
    return 0;
}