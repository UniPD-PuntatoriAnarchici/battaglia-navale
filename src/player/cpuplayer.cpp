/**
 * @author Rampin Matteo
 */

#include "./../../include/player/cpuplayer.h"

bool Cpuplayer::turn(Player &other) {
    if (defense_board_.is_lost()) return false;

    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    std::uniform_int_distribution<int> coordinate_distribution(1, 12);
    std::uniform_int_distribution<int> ship_distribution(0, 7);

    Coordinate source;
    Coordinate destination;
    int index;
    std::vector<Coordinate> def;

    bool dead_ship;

    do {
        dead_ship = false;
        def = defense_board_.get_all_raw();

        destination = Coordinate{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};
        index = ship_distribution(random_engine);

        if ((defense_board_.ship_at_index(index)) == nullptr) {
            dead_ship = true;
            continue;
        }

        source = defense_board_.ship_at_index(index)->center();

//        std::cout << source << destination;
    } while (dead_ship || !defense_board_.ship_at_index(index)->action(destination, defense_board_, attack_board_,
                                                                       other.get_defense_board()));

    std::string action = source.to_string() + " " + destination.to_string();
    add_to_player_history(action);
    return true;
}

bool Cpuplayer::place_ship(const Ship::Type ship_type) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP &&
        ship_type != Ship::Type::SUBMARINE)
        return false;

    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    std::uniform_int_distribution<int> coordinate_distribution(1, 12);
    std::uniform_int_distribution<int> ship_direction_distribution(0, 1);

    int length;
    if (ship_type == Ship::Type::BATTLESHIP) {
        length = Battleship::LENGTH;
    } else if (ship_type == Ship::Type::REPAIRSHIP) {
        length = Repairship::LENGTH;
    } else {
        length = Submarine::LENGTH;
    }

    bool valid_input = false;

    Ship::Directions direction;
    while (!valid_input) {
        Coordinate center{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};

        if (ship_direction_distribution(random_engine) == 0)
            direction = Ship::Directions::HORIZONTAL;
        else
            direction = Ship::Directions::VERTICAL;

        //std::cout << direction << std::endl;

        //  1 2 3 4 5
        //F C C C C C

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
        if (valid_input) {
            if (ship_type == Ship::Type::BATTLESHIP)
                defense_board_.place_ship(Battleship(center, direction));
            else if (ship_type == Ship::Type::REPAIRSHIP)
                defense_board_.place_ship(Repairship(center, direction));
            else defense_board_.place_ship(Submarine(center, direction));
        }
    }
    // TODO: implement this and test turn!
    return false;
}

bool Cpuplayer::replay_place_ship(const Ship::Type &ship_type, const std::string &info) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP &&
        ship_type != Ship::Type::SUBMARINE)
        return false;

    if (defense_board_.is_full()) {
        colored_print("La griglia e' piena!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }

    if (info.length() < 3 || info.length() > 4) {
        colored_print("Informazioni sulla nave non valide!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }

    if (info.at(0) != 'H' && info.at(0) != 'V') {
        colored_print("Direzione della nave non valida!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }

    Coordinate center = Coordinate{info.substr(1, info.length())};
    Ship::Directions direction = (info.at(0) == 'H') ? Ship::Directions::HORIZONTAL : Ship::Directions::VERTICAL;

    if (ship_type == Ship::Type::BATTLESHIP)
        defense_board_.place_ship(Battleship(center, direction));
    else if (ship_type == Ship::Type::REPAIRSHIP)
        defense_board_.place_ship(Repairship(center, direction));
    else if (ship_type == Ship::Type::SUBMARINE)
        defense_board_.place_ship(Submarine(center, direction));

    return true;
}

bool Cpuplayer::replay_turn(Player &other, const std::string &action) {
    if (defense_board_.is_lost()) return false;

    std::vector<Coordinate> action_coord = Coordinate::split_coordinates(action);

    if (action_coord.size() != 2)
        throw INVALID_ACTION{"Action must contain XYOrigin and XYTarget"};

    try {
        defense_board_.ship_at(action_coord[0])
                ->action(action_coord[1], defense_board_, attack_board_, other.get_defense_board());

    } catch (const std::exception &ex) {
        throw INVALID_ACTION{"Wrong coordinates!"};
    }

    return true;
}

Cpuplayer::~Cpuplayer() {

}
