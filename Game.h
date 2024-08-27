
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Game {
private:
    static constexpr int DECK_SIZE = 52;
    static constexpr int JOKER = 15;

    // Set in init_game
    std::vector<int> card_deck;

    // Values set in the constructor
    int joker_amout;
    int decks_in_use;
    int games_to_play;
    bool equal_jokers;

    void init_game();

    void shuffle_vector(std::vector<int>& vec);
    void fill_player_decks();
    void distribute_jokers();


    // After sim stats
    std::vector<int> games_turns;
    int player_one_wins;
    int player_two_wins;

public:
    Game(int joker_amount_param, int decks_in_use_param, int games_to_play_param, bool equal_jokers_param);

    void start();

    std::vector<int> player_one_deck;
    std::vector<int> player_two_deck;

    static void print_vec(std::vector<int>& vec);

};



#endif //GAME_H
