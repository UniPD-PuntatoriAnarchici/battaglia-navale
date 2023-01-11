#include "./../../include/player/humanplayer.h"

void colored_print(std::string &s);

// returns false if game is lost
bool Humanplayer::turn(Player &other) {
    if (defense_board_.is_lost()) return false;

    std::string buffer;
    std::vector<Coordinate> turn_coords;
    bool invalid_coordinates_flag = false;
    bool invalid_ship_flag = false;
    bool customAction = false;

    do {
        if (customAction) {
            // std::cout << "Comando speciale eseguito!\n";
            std::string to_print = "Comando speciale eseguito!\n";
            colored_print(to_print);
        } else if (invalid_coordinates_flag) {
            std::cout << "Coordinate non valide! Si prega di re-inserire.\n";
        }

        if (invalid_ship_flag) {
            std::cout << "Nessuna nave presente a queste coordinate! Si prega di re-inserire.\n";
        }

        invalid_coordinates_flag = false;
        invalid_ship_flag = false;

        std::cout << "Inserisci le coordinate: XYOrigin XYTarget\n\tInserimento: ";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, buffer);
        std::cout << std::endl;

        customAction = true;
        if (buffer == "AA AA") {
            attack_board_.clear_reveals();
        } else if (buffer == "XX XX") {
            // print grids!
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

        try {
            defense_board_.ship_at(turn_coords[0])
                ->action(turn_coords[1], other.get_defense_board(), attack_board_);

        } catch (const std::exception &ex) {
            invalid_ship_flag = true;
        }
    } while (invalid_coordinates_flag || invalid_ship_flag || customAction);
    return true;
}

bool Humanplayer::place_ship(const Ship::Type ship_type) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP &&
        ship_type != Ship::Type::SUBMARINE)
        return 0;

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
            std::cout << "Devi inserire due coordinate!" << std::endl;
            continue;
        }

        // set center and direction
        if (coordinates.at(0).col() == coordinates.at(1).col()) {
            // same column -> vertical
            direction = Ship::Directions::VERTICAL;
            // if vertical length is in the column (y2-y1)
            if (!check_ship_length(coordinates.at(1).row(), coordinates.at(0).row(), ship_type)) {
                std::cout << "La lunghezza e il tipo di nave non corrispondono" << std::endl;
                continue;
            }
            center = get_ship_center(coordinates.at(0).row(), coordinates.at(0).col(), direction, ship_type);
        } else {
            // same row -> horizontal
            direction = Ship::Directions::HORIZONTAL;
            // if horizontal length is in the row (x2-x1)
            if (!check_ship_length(coordinates.at(1).col(), coordinates.at(0).col(), ship_type)) {
                std::cout << "La lunghezza e il tipo di nave non corrispondono" << std::endl;
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
            std::cout << "Nave inserita correttamente" << std::endl;
        else
            std::cout << "Errore nell'inserimento della nave" << std::endl;
    }
    return true;
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

/*
    from https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
    from https://en.wikipedia.org/wiki/ANSI_escape_code#Colors

            foreground background
    black        30         40
    red          31         41
    green        32         42
    yellow       33         43
    blue         34         44
    magenta      35         45
    cyan         36         46
    white        37         47

    reset             0  (everything back to normal)
    bold/bright       1  (often a brighter shade of the same colour)
    underline         4
    inverse           7  (swap foreground and background colours)
    bold/bright off  21
    underline off    24
    inverse off      27
*/
void colored_print(std::string &s) {
#if defined(__linux__) || defined(__APPLE__)
    std::cout << "\033[1;93m" << s << "\033[0m";
#else
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << s;
    SetConsoleTextAttribute(hConsole, 7);
#endif
}