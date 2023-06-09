#include "Game.hpp"
#include <iostream>
//#include "Board.hpp"
#include "Test.hpp"
int main()
{
    //Test test;
    Game game(4, 4);
    /* std::vector<unsigned char> cells ={
    '\0', 'O', '\0',
    '\0', '\0', '\0',
    '\0', 'O', 'X' }; */
    std::vector<unsigned char> cells ={
    'O', 'O', 'O', 'X',
    'O', 'X', 'O', 'O',
    'X', 'O', '\0', 'X',
    'X', '\0', 'X', 'X' };
    game.board.board = cells;
    game.playerTurn = false;
    int i = 0;
    for(auto&& cell : game.board.board)
    {
        std::cout << char((cell == 0 ? '_' : cell)) << " ";
        i++;
        if(i % game.board.getBoardSize() == 0)
            std::cout << '\n';
    }
    std::cout << '\n';
    unsigned int x, y;
    while(true)
    {
        game.play();
        for(auto&& cell : game.board.board)
        {
            std::cout << char((cell == 0 ? '_' : cell)) << " ";
            i++;
            if(i % game.board.getBoardSize() == 0)
                std::cout << '\n';
        }
        if(game.isGameOver())
            continue;
        std::cout << '\n';
        std::cin >> x >> y;
        game.playerMove(y, x);
    }
    /* game.playerMove(0, 2);
    game.play();
    for(auto&& cell : game.board.board)
    {
        std::cout << char((cell == 0 ? '_' : cell)) << " ";
        i++;
        if(i % 3 == 0)
            std::cout << '\n';
    } */
    /* std::vector<int> v = {1};
    if(std::next_permutation(v.begin(), v.end()))
        std::cout << "yes";
    else
        std::cout << "no"; */
    return 0;
}