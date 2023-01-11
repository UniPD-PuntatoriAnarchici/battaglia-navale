#include "./../../include/player/player.h"

std::vector<std::string> Player::history() {
    // TODO

    return std::vector<std::string>(1);
}

void Player::print_boards_inline() {
    int atk_coordinate_counter = 0;
    int def_coordinate_counter = 0;
    std::pair<Coordinate, char> atk_element_to_print;
    std::pair<Coordinate, char> def_element_to_print;
    std::vector<std::pair<Coordinate, char>> atk_occupied_positions = attack_board_.get_all();
    std::vector<std::pair<Coordinate, char>> def_occupied_positions = defense_board_.get_all();

    if (def_occupied_positions.size() > 0)
        def_element_to_print = def_occupied_positions.at(def_coordinate_counter++);
    else {
        // I have to print a dummy coordinate because i always check toprint.first
        def_element_to_print = std::pair<Coordinate, char>(Coordinate(), ' ');
        def_coordinate_counter++;
    }

    if (atk_occupied_positions.size() > 0)
        atk_element_to_print = atk_occupied_positions.at(atk_coordinate_counter++);
    else {
        // I have to print a dummy coordinate because i always check toprint.first
        atk_element_to_print = std::pair<Coordinate, char>(Coordinate(), ' ');
        atk_coordinate_counter++;
    }

    std::vector<std::string> atk_buffer;

    for (int i = 1; i <= 12; i++) {
        std::string line_buffer;
        line_buffer.push_back((char)(i < 10 ? '@' + i : '@' + i + 2));
        line_buffer += " |";
        for (int j = 1; j <= 12; j++) {
            // if position is occupied print
            if (atk_element_to_print.first == Coordinate(i, j)) {
                line_buffer += " ";
                line_buffer.push_back(atk_element_to_print.second);
                line_buffer += " |";
                if (atk_coordinate_counter < atk_occupied_positions.size()) {
                    atk_element_to_print = atk_occupied_positions.at(atk_coordinate_counter++);
                }
            } else {
                line_buffer += "   |";
            }
        }
        atk_buffer.push_back(line_buffer);
    }

    std::cout << "DEFENSE\t\t\t\t\t\t\tATTACK" << std::endl;

    for (int i = 1; i <= 12; i++) {
        std::cout << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |";
        for (int j = 1; j <= 12; j++) {
            // if position is occupied print
            if (def_element_to_print.first == Coordinate(i, j)) {
                std::cout << " " << def_element_to_print.second << " |";
                if (def_coordinate_counter < def_occupied_positions.size()) {
                    def_element_to_print = def_occupied_positions.at(def_coordinate_counter++);
                }
            } else {
                std::cout << "   |";
            }
        }
        std::cout << "\t" << atk_buffer.at(i - 1);
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
    std::cout << "\t";
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