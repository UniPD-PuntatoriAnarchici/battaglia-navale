#include "./../../include/player/player.h"

std::vector<std::string> Player::history() {
    // TODO

    return std::vector<std::string>(1);
}

void Player::print_defense_board() {
    std::cout << "Defense board" << std::endl;
    std::vector<std::pair<Coordinate, char>> occupied_positions = defense_board_.get_all();

    std::cout << "Occupied positions: " << std::endl;
    for (auto c : occupied_positions) {
        std::cout << c.first << std::endl;
    }

    int coordinate_counter = 0;
    auto to_print = occupied_positions.at(coordinate_counter++);

    for (int i = 1; i <= 12; i++) {
        std::cout << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |";
        for (int j = 1; j <= 12; j++) {
            // if position is occupied print
            if (to_print.first == Coordinate(i, j)) {
                std::cout << " " << to_print.second << " |";
                if (coordinate_counter < occupied_positions.size()) {
                    to_print = occupied_positions.at(coordinate_counter++);
                }
            } else {
                std::cout << "   |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-> ";
    for (int j = 1; j <= 12; j++) {
        if (j < 10) {
            std::cout << "  " << j << " ";
        } else {
            std::cout << " " << j << " ";
        }
    }
    std::cout << std::endl;
}