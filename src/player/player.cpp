#include "./../../include/player/player.h"

std::vector<std::string> Player::history() {
    // TODO

    return std::vector<std::string>(1);
}

void Player::print_defense_board() {
    std::cout << "Defense board" << std::endl;
    std::vector<Coordinate> occupied_positions = defense_board_.get_all();
    // std::cout << "Occupied positions: " << std::endl;
    // for (Coordinate c : occupied_positions) {
    //     std::cout << c << std::endl;
    // }

    for (int i = 1; i <= 12; i++) {
        std::cout << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |" << std::endl;
        for (int j = 0; j <= 12; j++) {
            // if position is occupied print
        }
    }

}