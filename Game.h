
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>
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
    int turn_limit_before_shuffle;

    void init_game();

    void shuffle_vector(std::vector<int>& vec);
    void fill_player_decks();
    void distribute_jokers();

    void game_loop();

    void check_for_loop(int& turns, int& re_shuffles);
    void check_for_win(int& turns, bool& running, int& re_shuffles);

    void handle_win(int winning_player, int& turns_param, bool& running, int& re_shuffles);

    void run_turn(int& turns, bool& running, int& re_shuffles);
    void give_card(std::vector<int>& from, std::vector<int>& to);
    void battle(int& turns, bool& running, int& re_shuffles);

    // After sim stats
    std::vector<int> games_turns;
    int player_one_wins;
    int player_two_wins;
    int ties;

    int battles;
    int shuffles;


public:
    Game(int joker_amount_param, int decks_in_use_param, int games_to_play_param, bool equal_jokers_param, int turn_limit_before_shuffle_param);

    void start();

    std::vector<int> player_one_deck;
    std::vector<int> player_two_deck;

    static void print_vec(std::vector<int>& vec);

};



#endif //GAME_H
