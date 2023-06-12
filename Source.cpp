#include "MyUtils.hpp"
#include "Game.hpp"
#include <iostream>

int main()
{
    Game game(3, 3);
    int x, y;
    int choice;
    while(true)
    {
        std::cout << "Ktory gracz ma zaczynac:\n1.Bot\n2.Gracz" << std::endl;
        readInt(choice, 1, 2);
        game.setPlayerTurn(choice == 1 ? false : true);
        std::cout << "Podaj rozmiar stolu: " << std::endl;
        readInt(choice, 3, 100);
        game.resizeBoard(choice);
        std::cout << "Podaj dlugosc wygrywajacego rzedu: " << std::endl;
        readInt(choice, 3, game.getBoardSize());
        game.setWinCondition(choice);
        while(true)
        {
            game.botMove();
            game.displayBoard();
            if(game.isGameOver())
                break;
            std::cout << "Podaj kolumne, liczac od 1: " << std::endl;
            readInt(x, 1, game.getBoardSize());
            std::cout << "Podaj wiersz, liczac od 1: " << std::endl;
            readInt(y, 1, game.getBoardSize());
            if(!game.playerMove(y - 1, x - 1))
                std::cout << "\nNiepoprawny ruch, podaj inny\n" << std::endl;
        }
        game.displayWinner();
        std::cout << "Resetowac gre:\n1.Tak\n2.Nie" << std::endl;
        readInt(choice, 1, 2);
        if(choice == 2)
            return 0;
        else
            game.reset();
    }
    return 0;
}