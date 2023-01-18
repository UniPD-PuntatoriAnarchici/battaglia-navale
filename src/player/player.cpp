/**
 * @author Rampin Matteo
 */

#include "./../../include/player/player.h"

/**
 * Function that return historical moves
 * @return {std::vector<std::string>}  : history of the invoking player 
 */
std::vector<std::string> Player::player_history() { return player_history_; }

 /**
 * 
 * @param  {std::string} action : add to player_history_ the action
 * @return {int}                : Returns the number of elements in the vector
 */
int Player::add_to_player_history(const std::string &action) {
    player_history_.push_back(action);
    // conversion from size_t to int, can't overflow because we have a maximum number of moves lower than int
    return static_cast<int>(player_history_.size());
}

/**
 * print the boards side by side
 * @param  {std::ostream} os : output stream object to print output operations
 */
void Player::print_boards_inline(std::ostream &os) {
    int atk_coordinate_counter = 0;
    int def_coordinate_counter = 0;
    std::pair<Coordinate, char> atk_element_to_print;
    std::pair<Coordinate, char> def_element_to_print;
    std::vector<std::pair<Coordinate, char>> atk_occupied_positions = attack_board_.get_all();
    std::vector<std::pair<Coordinate, char>> def_occupied_positions = defense_board_.get_all();

    if (!def_occupied_positions.empty())  // Changed to correct empty method
        def_element_to_print = def_occupied_positions.at(def_coordinate_counter++);
    else {
        // I have to print a dummy coordinate because i always check toprint.first
        def_element_to_print = std::pair<Coordinate, char>(Coordinate(), ' ');
        def_coordinate_counter++;
    }

    if (!atk_occupied_positions.empty())  // Changed to correct empty method
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

    colored_print("DEFENSE\t\t\t\t\t\t\tATTACK", MESSAGE_TYPE::MSG_INFO_BOLD, os) << std::endl;

    for (int i = 1; i <= 12; i++) {
        os << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |";
        for (int j = 1; j <= 12; j++) {
            // if position is occupied print
            if (def_element_to_print.first == Coordinate(i, j)) {
                os << " " << def_element_to_print.second << " |";
                if (def_coordinate_counter < def_occupied_positions.size()) {
                    def_element_to_print = def_occupied_positions.at(def_coordinate_counter++);
                }
            } else {
                os << "   |";
            }
        }
        os << "\t" << atk_buffer.at(i - 1);
        os << std::endl;
    }

    os << "-> ";
    for (int j = 1; j <= 12; j++) {
        if (j < 10) {
            os << "  " << j << " ";
        } else {
            os << " " << j << " ";
        }
    }
    os << "\t-> ";
    for (int j = 1; j <= 12; j++) {
        if (j < 10) {
            os << "  " << j << " ";
        } else {
            os << " " << j << " ";
        }
    }
    os << std::endl;
}

/**
 * Prints Defenseboard and Attackboard
 */
void Player::print_boards() {
    print_board(Board::Type::DEFENSEBOARD);
    print_board(Board::Type::ATTACKBOARD);
}

/**
 * print the board passed as parameter
 * @param  {Board::Type} boardtype : Type of board to be printed (DefenseBoard/Attackboard)
 * @param  {std::ostream} os       : Output stream object
 */
void Player::print_board(const Board::Type boardtype, std::ostream &os) {
    int coordinate_counter = 0;
    std::pair<Coordinate, char> to_print;
    std::vector<std::pair<Coordinate, char>> occupied_positions;

    if (boardtype == Board::Type::DEFENSEBOARD) {
        os << "DEFENSEBOARD" << std::endl;
        occupied_positions = defense_board_.get_all();
    } else {
        os << "ATTACKBOARD" << std::endl;
        occupied_positions = attack_board_.get_all();
    }

    if (!occupied_positions.empty())  // Changed to correct empty method
        to_print = occupied_positions.at(coordinate_counter++);
    else {
        // I have to print a dummy coordinate because i always check toprint.first
        to_print = std::pair<Coordinate, char>(Coordinate(), ' ');
        coordinate_counter++;
    }

    for (int i = 1; i <= 12; i++) {
        os << (char)(i < 10 ? '@' + i : '@' + i + 2) << " |";
        for (int j = 1; j <= 12; j++) {
            // if position is occupied print
            if (to_print.first == Coordinate(i, j)) {
                os << " " << to_print.second << " |";
                if (coordinate_counter < occupied_positions.size()) {
                    to_print = occupied_positions.at(coordinate_counter++);
                }
            } else {
                os << "   |";
            }
        }
        os << std::endl;
    }
    os << "-> ";
    for (int j = 1; j <= 12; j++) {
        if (j < 10) {
            os << "  " << j << " ";
        } else {
            os << " " << j << " ";
        }
    }
    os << std::endl;
}

/**
 * Pure virtual destructor
 * @details
 * We use 2 smart pointer of Player type in replay.
 * To avoid problems with destruction of object we decided to implement all the destructors
 *
 * @related Replay, HumanPlayer, CpuPlayer
 */
Player::~Player() {}

/**
 * checks if there are live ships
 * @return {bool}  : true if there are live ships,false otherwise
 */
bool Player::is_alive() const { return !defense_board_.is_lost(); }

/**
 * Function that place all ships
 */
void Player::place_all_ships() {
    place_ship(Ship::Type::BATTLESHIP);
    place_ship(Ship::Type::BATTLESHIP);
    place_ship(Ship::Type::BATTLESHIP);

    place_ship(Ship::Type::REPAIRSHIP);
    place_ship(Ship::Type::REPAIRSHIP);
    place_ship(Ship::Type::REPAIRSHIP);

    place_ship(Ship::Type::SUBMARINE);
    place_ship(Ship::Type::SUBMARINE);
}

/**
 * check if a ship goes beyond the board,check if the positions where the ship should be placed are occupied
 * @param  {Coordinate} center          : Ship's center
 * @param  {int} length                 : Ship's length
 * @param  {Ship::Directions} direction : Ship's direction (vertical/horizontal)
 * @return {bool}                       : true if it can be placed,false otherwise
 */
bool Player::valid_ship_placement(Coordinate center, int length, Ship::Directions direction) {
    bool valid_input = true;
    if (direction == Ship::Directions::HORIZONTAL) {
        if (!((center.col() + length / 2) > Defenseboard::side_length || center.col() - length / 2 <= 0)) {
            for (int i = center.col() - length / 2; i <= center.col() + length / 2; i++) {
                Coordinate coordinate_to_check{center.row(), i};
                if (defense_board_.is_occupied(coordinate_to_check)) {
                    valid_input = false;
                    break;
                } else {
                    valid_input = true;
                }
            }
        } else {
            valid_input = false;
        }
    } else {
        if (!(center.row() + length / 2 > Defenseboard::side_length || center.row() - length / 2 <= 0)) {
            for (int i = center.row() - length / 2; i <= center.row() + length / 2; i++) {
                Coordinate coordinate_to_check = Coordinate(i, center.col());
                if (defense_board_.is_occupied(coordinate_to_check)) {
                    valid_input = false;
                    break;
                } else {
                    valid_input = true;
                }
            }
        } else {
            valid_input = false;
        }
    }
    return valid_input;
}