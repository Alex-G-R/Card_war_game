#include "Game.h"

int main()
{
    int jkrs, decks, games, lim, eql, prnt;

    std::cout << "Joker amount: \n";
    std::cin >> jkrs;

    std::cout << "Decks in use: \n";
    std::cin >> decks;

    std::cout << "Games to simulate: \n";
    std::cin >> games;

    std::cout << "Give-out the Jokers equally (1 = true/yes | 0 = false/no ): \n";
    if(jkrs%2 != 0)
    {
        std::cout << "WARNING: Choosing 'no' with an un-even amonut of Jokers leads to a great amount of loops. \n";
    }
    std::cin >> eql;

    std::cout << "Turn limit before shuffle (recommended 10,000): \n";
    std::cin >> lim;

    std::cout << "Do you want to print the turns it took for each game to finish? \n";
    std::cout << "WARNING: This can take a while in the end with bigger simulations. \n";
    std::cout << "WARNING: Not recommended for simulations bigger than a few k. \n";
    std::cout << "(1 = true/yes | 0 = false/no ): \n";
    std::cin >> prnt;

    Game game(jkrs, decks, games, eql, lim, prnt);

    game.start();

    int end;
    std::cin >> end;

    return 0;
}
