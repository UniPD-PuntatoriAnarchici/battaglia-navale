#include "./../../include/player/humanplayer.h"

// ritorna false se la partita e' persa
bool Humanplayer::turn(Player &other) {
    // if defenseboard.islost() return false
    // loop di gioco
    // chiedi input finche' coordinate non sono valide e che l'azione stia effettivamente partendo
    //          da una nave e non dall'acqua
    // processa input (anche i casi speciali di pulizia griglia)
    // esegui azione ship->action(coordinate dest, other.get_defenseboard(), self.get_attackboard())
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

        // get and split coordinates
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
        std::vector<Coordinate> coordinates = split(input);

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

std::vector<Coordinate> Humanplayer::split(const std::string &s) {
    std::vector<Coordinate> coordinates;
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, ' ')) {
        coordinates.emplace_back(item);
    }
    return coordinates;
}
