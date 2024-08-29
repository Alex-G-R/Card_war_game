
#include "Game.h"

Game::Game(const int joker_amount_param, const int decks_in_use_param, const int games_to_play_param, const bool equal_jokers_param, const int turn_limit_before_shuffle_param, const bool print_turns_param)
{

    joker_amout = joker_amount_param;
    decks_in_use = decks_in_use_param;
    games_to_play = games_to_play_param;
    equal_jokers = equal_jokers_param;
    turn_limit_before_shuffle = turn_limit_before_shuffle_param;
    print_turn_vector = print_turns_param;

    player_one_wins = 0;
    player_two_wins = 0;
    ties = 0;
    battles = 0;
    shuffles = 0;
}

void Game::start()
{
    for(size_t i =0; i < games_to_play; i++)
    {
        init_game();
    }

    std::cout << "\n _____________________________ \n";
    std::cout << "Player 1 wins: " << player_one_wins << "\n";
    std::cout << "Player 2 wins: " << player_two_wins << "\n";
    std::cout << "Ties: " << ties << "\n \n";
    std::cout << "Battles: " << battles << "\n";
    std::cout << "Shuffles: " << shuffles << "\n";
    const int sum = std::accumulate(games_turns.begin(), games_turns.end(), 0);
    const double avg = static_cast<double>(sum) / static_cast<double>(games_turns.size());
    std::cout << "Avg amount of turns per game: " << avg << "\n";
    if(print_turn_vector)
    {
        std::cout << "Games turn data: ";
        std::sort(games_turns.begin(), games_turns.end());
        print_vec(games_turns);
    }
}


void Game::init_game()
{
    player_one_deck.clear();
    player_two_deck.clear();
    card_deck.clear();

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

    /* //Tests
    print_vec(card_deck);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    print_vec(player_one_deck);
    std::cout << "\n P1 deck size: " << player_one_deck.size() << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
    print_vec(player_two_deck);
    std::cout << "\n P2 deck size: " << player_two_deck.size() << "\n";
    */

    game_loop();
}

void Game::game_loop()
{
    int turns = 0;
    int re_shuffles = 0;
    bool running = true;

    while(running)
    {
        check_for_loop(turns, re_shuffles);
        check_for_win(turns, running, re_shuffles);

        run_turn(turns, running, re_shuffles);

        turns++;
    }
}

void Game::run_turn(int& turns, bool& running, int& re_shuffles)
{
    if(running)
    {
        if(player_one_deck[0] > player_two_deck[0])
        { // Player 1 wins the turn
            // std::cout << "Player 1 won the clash \n";
            give_card(player_two_deck, player_one_deck);
        }
        else if(player_two_deck[0] > player_one_deck[0])
        { // Player 2 wins the turn
            // std::cout << "Player 2 won the clash \n";
            give_card(player_one_deck, player_two_deck);
        }
        else
        {
            battle(turns, running, re_shuffles);
        }
    }
}

void Game::battle(int& turns, bool& running, int& re_shuffles) {
    int index = 2;

    while(index < player_one_deck.size() && index < player_two_deck.size())
    {
        if(player_one_deck[index] > player_two_deck[index])
        {
            battles++;
            // std::cout << "Player 1 wins the battle \n";
            for(size_t i = index; i > 0; i--)
            {
                give_card(player_two_deck, player_one_deck);
            }
            return;
        }
        if(player_two_deck[index] > player_one_deck[index])
        {
            battles++;
            // std::cout << "Player 2 wins the battle \n";
            for(size_t i = index; i > 0; i--)
            {
                give_card(player_one_deck, player_two_deck);
            }
            return;
        }
        // Tie in a battle, increase the index
        index += 2;
    }

    if(index >= player_one_deck.size() && index >= player_two_deck.size())
    {
        // std::cout << "Both players ran out of the card for the battle \n";
        handle_win(0, turns, running, re_shuffles);
    }
    else if(index >= player_one_deck.size())
    {
        // std::cout << "Player 1 ran out of cards, Player 2 wins the game \n";
        handle_win(2, turns, running, re_shuffles);
    }
    else if(index >= player_two_deck.size())
    {
        // std::cout << "Player 2 ran out of cards, Player 1 wins the game \n";
        handle_win(1, turns, running, re_shuffles);
    }
}

void Game::give_card(std::vector<int> &from, std::vector<int> &to)
{
    // Copy the first card from P1 and P2 to the winners deck
    to.emplace_back(from[0]);
    to.emplace_back(to[0]);

    // Delete the copied cards from the beggining of the vectors
    from.erase(from.begin());
    to.erase(to.begin());

}

void Game::check_for_win(int& turns, bool& running, int& re_shuffles)
{
    if(player_one_deck.empty())
        handle_win(2, turns, running, re_shuffles);

    if(player_two_deck.empty())
        handle_win(1, turns, running, re_shuffles);
}

void Game::handle_win(const int winning_player,int& turns_param, bool& running,int& re_shuffles)
{
    int turns = turns_param + re_shuffles * turn_limit_before_shuffle;

    if(winning_player == 0)
    {
        std::cout << "Tie \n";
        games_turns.emplace_back(turns);
        ties++;
        running = false;

        return;
    }

    if(winning_player == 1)
    {
        std::cout << "Player one won a match in " << turns << " turns! \n";
        games_turns.emplace_back(turns);
        player_one_wins++;
        turns_param = 0;
        re_shuffles = 0;
        running = false;

        return;
    }

    if (winning_player == 2)
    {
        std::cout << "Player two won a match in " << turns << " turns! \n";
        games_turns.emplace_back(turns);
        player_two_wins++;
        running = false;

        return;
    }

    std::cerr << "Invalid winning player number \n";
}



void Game::check_for_loop(int& turns, int& re_shuffles)
{
    if(turns > turn_limit_before_shuffle)
    {
        std::cout << "Decks shuffled, loop detected... resuming the game. \n";
        shuffle_vector(player_one_deck);
        shuffle_vector(player_two_deck);

        turns = 0;
        re_shuffles++;
        shuffles++;
    }
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
