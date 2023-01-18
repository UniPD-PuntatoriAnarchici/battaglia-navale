/**
 * @author Galiazzo Matteo
 */

#include "./../../include/player/humanplayer.h"

void Humanplayer::turn(Player &other) {
    std::string buffer;
    std::vector<Coordinate> turn_coords;
    bool invalid_coordinates_flag = false;
    bool invalid_action_flag = false;
    bool invalid_ship_destination_flag = false;
    bool customAction = false;

    do {
        if (customAction)
            colored_print(std::string("Comando speciale eseguito!"), MESSAGE_TYPE::MSG_INFO) << std::endl;
        else if (invalid_coordinates_flag)
            colored_print(std::string("Coordinate non valide! Si prega di re-inserire."), MESSAGE_TYPE::MSG_ERROR)
                << std::endl;
        else if (invalid_action_flag)
            colored_print(std::string("Azione non valida! Si prega di re-inserire."),
                          MESSAGE_TYPE::MSG_ERROR)
                << std::endl;
        else if (invalid_ship_destination_flag)
            colored_print(std::string("Impossibile spostare la nave a questa coordinata"), MESSAGE_TYPE::MSG_ERROR)
                << std::endl;

        invalid_coordinates_flag = false;
        invalid_action_flag = false;
        invalid_ship_destination_flag = false;

        std::cout << "Inserisci le coordinate: XYOrigin XYTarget\n\tInserimento: ";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, buffer);
        std::cout << std::endl;

        customAction = true;
        if (buffer == "AA AA") {
            attack_board_.clear_reveals();
        } else if (buffer == "XX XX") {
            this->print_boards_inline();
        } else if (buffer == "BB BB") {
            attack_board_.clear_hits();
        } else if (buffer == "CC CC") {
            attack_board_.clear_misses();
        } else if (buffer == "DD DD") {
            attack_board_.clear_board();
        } else {
            customAction = false;
        }
        if (customAction) continue;

        try {
            turn_coords = split_coordinates(buffer);
        } catch (const std::exception &e) {
            invalid_coordinates_flag = true;
            continue;
        }

        if (defense_board_.ship_at(turn_coords[0]) == nullptr) {
            invalid_action_flag = true;
        } else if (!defense_board_.ship_at(turn_coords[0])
                        ->action(turn_coords[1], defense_board_, attack_board_, other.get_defense_board())) {
            invalid_action_flag = true;
        }
    } while (invalid_coordinates_flag || invalid_action_flag || customAction);
    add_to_player_history(buffer);
}

void Humanplayer::place_ship(const Ship::Type ship_type) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP && ship_type != Ship::Type::SUBMARINE)
        throw std::invalid_argument{"Invalid ship type"};

    std::string input;
    bool valid_input = false;
    Coordinate center;
    Ship::Directions direction;

    while (!valid_input) {
        std::cout << "Quali sono le coordinate per ";
        if (ship_type == Ship::Type::BATTLESHIP)
            std::cout << "la corazzata" << std::endl;
        else if (ship_type == Ship::Type::REPAIRSHIP)
            std::cout << "la nave di supporto" << std::endl;
        else if (ship_type == Ship::Type::SUBMARINE)
            std::cout << "il sottomarino" << std::endl;

        // get and split_coordinates coordinates
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
        std::vector<Coordinate> coordinates = split_coordinates(input);

        // if i don't have 2 coordinates i break out to get new coordinates
        if (coordinates.size() != 2) {
            colored_print("Devi inserire due coordinate!", MESSAGE_TYPE::MSG_ERROR) << std::endl;
            continue;
        }

        // set center and direction
        if (coordinates.at(0).col() == coordinates.at(1).col()) {
            // same column -> vertical
            direction = Ship::Directions::VERTICAL;
            // if vertical length is in the column (y2-y1)
            if (!check_ship_length(coordinates.at(1).row(), coordinates.at(0).row(), ship_type)) {
                colored_print("La lunghezza e il tipo di nave non corrispondono!", MESSAGE_TYPE::MSG_ERROR) << std::endl;
                continue;
            }
            center = get_ship_center(coordinates.at(0).row(), coordinates.at(0).col(), direction, ship_type);
        } else {
            // same row -> horizontal
            direction = Ship::Directions::HORIZONTAL;
            // if horizontal length is in the row (x2-x1)
            if (!check_ship_length(coordinates.at(1).col(), coordinates.at(0).col(), ship_type)) {
                colored_print("La lunghezza e il tipo di nave non corrispondono!", MESSAGE_TYPE::MSG_ERROR) << std::endl;
                continue;
            }
            center = get_ship_center(coordinates.at(0).row(), coordinates.at(0).col(), direction, ship_type);
        }

        // push Battleship(center, direction)
        if (ship_type == Ship::Type::BATTLESHIP)
            valid_input = defense_board_.place_ship(Battleship(center, direction));
        else if (ship_type == Ship::Type::REPAIRSHIP)
            valid_input = defense_board_.place_ship(Repairship(center, direction));
        else if (ship_type == Ship::Type::SUBMARINE)
            valid_input = defense_board_.place_ship(Submarine(center, direction));

        if (valid_input)
            colored_print("Nave inserita correttamente", MESSAGE_TYPE::MSG_SUCCESS) << std::endl;
        else
            colored_print("Errore nell'inserimento della nave!", MESSAGE_TYPE::MSG_ERROR) << std::endl;
    }
}

Coordinate Humanplayer::get_ship_center(int row, int col, Ship::Directions direction, Ship::Type ship_type) {
    int ship_center_distance = 0;
    if (ship_type == Ship::Type::BATTLESHIP)
        ship_center_distance = Battleship::LENGTH / 2;
    else if (ship_type == Ship::Type::REPAIRSHIP)
        ship_center_distance = Repairship::LENGTH / 2;
    else if (ship_type == Ship::Type::SUBMARINE)
        ship_center_distance = Submarine::LENGTH / 2;

    // if vertical center is on the same column (y2-y1), if horizontal on the same row (x2-x1)
    if (direction == Ship::Directions::VERTICAL)
        return Coordinate(row + ship_center_distance, col);
    else
        return Coordinate(row, col + ship_center_distance);
}

// true -> delta ok, false -> delta wrong, insert again
bool Humanplayer::check_ship_length(int n1, int n2, const Ship::Type ship_type) {
    if (n1 > n2) {
        int temp = n2;
        n2 = n1;
        n1 = temp;
    }
    if (ship_type == Ship::Type::BATTLESHIP)
        return (n2 - n1 + 1) == Battleship::LENGTH;
    else if (ship_type == Ship::Type::REPAIRSHIP)
        return (n2 - n1 + 1) == Repairship::LENGTH;
    else if (ship_type == Ship::Type::SUBMARINE)
        return (n2 - n1 + 1) == Submarine::LENGTH;
    return false;
}

std::vector<Coordinate> Humanplayer::split_coordinates(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) coordinates.emplace_back(item);
    return coordinates;
}

std::vector<std::string> Humanplayer::split_string(const std::string &s) {
    std::vector<std::string> strings;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) strings.push_back(item);
    return strings;
}

Humanplayer::~Humanplayer() {}
