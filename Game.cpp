
#include "Game.h"

Game::Game(const int joker_amount_param, const int decks_in_use_param, const int games_to_play_param, const bool equal_jokers_param)
{

    joker_amout = joker_amount_param;
    decks_in_use = decks_in_use_param;
    games_to_play = games_to_play_param;
    equal_jokers = equal_jokers_param;

}

void Game::start()
{
    init_game();
}


void Game::init_game()
{
    for(size_t k = 0; k < decks_in_use; k++)
    {
        int counter = 0;
        int current_card_value = 2;

        for(size_t i = 0; i < DECK_SIZE; i++)
        {
            // After inserting 4 same card values change the card
            if(counter == 4)
            {
                // Exit for-loop after emplacing 4 cards of 14 value
                if(current_card_value == 14)
                {
                    break;
                }
                current_card_value++;
                counter = 0;
            }
            card_deck.emplace_back(current_card_value);
            counter++;
        }
    }

    shuffle_vector(card_deck);

    // Give out card from the card deck to players
    fill_player_decks();
    distribute_jokers();

    shuffle_vector(player_one_deck);
    shuffle_vector(player_two_deck);

     //Tests
    print_vec(card_deck);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    print_vec(player_one_deck);
    std::cout << "\n P1 deck size: " << player_one_deck.size();
    std::cout << std::endl;
    std::cout << std::endl;
    print_vec(player_two_deck);
    std::cout << "\n P2 deck size: " << player_two_deck.size();


}


void Game::shuffle_vector(std::vector<int>& vec)
{
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vec.begin(), vec.end(), g);
}

void Game::fill_player_decks()
{
    for(size_t i = 0; i < card_deck.size(); i++)
    {
        if(i % 2 == 0)
        {
            player_one_deck.emplace_back(card_deck[i]);
        }
        else
        {
            player_two_deck.emplace_back(card_deck[i]);
        }
    }
}

void Game::distribute_jokers()
{
    if(joker_amout > 0)
    {
        // Seed the random number generator with the current time
        std::srand(std::time(0));

        if(equal_jokers && joker_amout % 2 == 0)
        {
            for(size_t i = 0; i < joker_amout; i++)
            {
                if(i % 2 == 0)
                {
                    player_one_deck.emplace_back(JOKER);
                }
                else
                {
                    player_two_deck.emplace_back(JOKER);
                }
            }
        }
        else if (equal_jokers)
        {
            // Generate a random number between 0 and 1
            int randomNumber = std::rand() % 2;

            if(randomNumber == 0)
            {
                player_one_deck.emplace_back(JOKER);
                joker_amout--;
            }
            else
            {
                player_two_deck.emplace_back(JOKER);
                joker_amout--;
            }

            for(size_t i = 0; i < joker_amout; i++)
            {
                if(i % 2 == 0)
                {
                    player_one_deck.emplace_back(JOKER);
                }
                else
                {
                    player_two_deck.emplace_back(JOKER);
                }
            }
        }
        else
        {
            for(size_t i = 0; i < joker_amout; i++)
            {
                // Generate a random number between 0 and 1
                int randomNumber = std::rand() % 2;

                if(randomNumber == 0)
                {
                    player_one_deck.emplace_back(JOKER);
                }
                else
                {
                    player_two_deck.emplace_back(JOKER);
                }
            }
        }
    }
}


void Game::print_vec(std::vector<int>& vec)
{
    for(auto value : vec)
    {
        std::cout << value << " ";
    }
}
