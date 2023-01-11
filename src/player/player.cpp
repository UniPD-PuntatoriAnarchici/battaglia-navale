#include "./../../include/player/player.h"

std::vector<std::string> Player::history() {
    // TODO

    return std::vector<std::string>(1);
}

void Player::print_boards() {
    print_board(Board::Type::DEFENSEBOARD);
    print_board(Board::Type::ATTACKBOARD);
}

void Player::print_board(const Board::Type boardtype) {
    int coordinate_counter = 0;
    std::pair<Coordinate, char> to_print;
    std::vector<std::pair<Coordinate, char>> occupied_positions;

    if (boardtype == Board::Type::DEFENSEBOARD) {
        std::cout << "DEFENSEBOARD" << std::endl;
        occupied_positions = defense_board_.get_all();
    } else {
        std::cout << "ATTACKBOARD" << std::endl;
        occupied_positions = attack_board_.get_all();
    }

    if (occupied_positions.size() > 0)
        to_print = occupied_positions.at(coordinate_counter++);
    else {
        // I have to print a dummy coordinate because i always check toprint.first
        to_print = std::pair<Coordinate, char>(Coordinate(), ' ');
        coordinate_counter++;
    }

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