#include <iostream>
#include <fstream>
#include "player/cpuplayer.h"

#include <chrono>
#include <thread>

std::vector<std::string> split_strings(const std::string &string, char delimiter = ' ');

void fill_player(Cpuplayer &player, const std::string &ships);

int main() {
    std::cout << "REPLAY" << std::endl;
    Cpuplayer player1, player2;

    std::string buffer;
    std::ifstream file;
    file.open("../test_log.txt");

    if (!file.is_open())
        throw std::invalid_argument{"can't open file!"};

    std::getline(file, buffer);
    fill_player(player1, buffer);

    std::getline(file, buffer);
    fill_player(player2, buffer);


    std::cout << "Player 1:" << std::endl;
    player1.print_boards_inline();

    std::cout << "Player 2:" << std::endl;
    player2.print_boards_inline();

    std::cout << "============================================================================" << std::endl
              << std::endl;

    for (int i = 0; i < 150; i++) {
        player1.turn(player2);
        std::cout << "Player 1:" << std::endl;
        player1.print_boards_inline();

        player2.turn(player1);
        std::cout << "Player 2:" << std::endl;
        player2.print_boards_inline();


        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "============================================================================" << std::endl
                  << std::endl;
    }

    return 0;
}


void fill_player(Cpuplayer &player, const std::string &ships) {
    std::vector<std::string> ships_info = split_strings(ships);
    for (int i = 0; i < 3; i++) {
        player.replay_place_ship(Ship::Type::BATTLESHIP, ships_info[i]);
    }

    for (int i = 3; i < 6; i++) {
        player.replay_place_ship(Ship::Type::REPAIRSHIP, ships_info[i]);
    }

    for (int i = 6; i < 8; i++) {
        player.replay_place_ship(Ship::Type::SUBMARINE, ships_info[i]);
    }
}

std::vector<std::string> split_strings(const std::string &string, char delimiter) {
    std::vector<std::string> strings;
    std::istringstream iss(string);
    std::string item;
    while (std::getline(iss, item, delimiter)) strings.push_back(item);
    return strings;
}