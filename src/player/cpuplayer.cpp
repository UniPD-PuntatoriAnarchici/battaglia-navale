#include "./../../include/player/cpuplayer.h"

bool Cpuplayer::turn(Player &other) {
    if (defense_board_.is_lost()) return false;

    /*
     * Random device generates random seed for Mersenne Twister that pick random number from distribution
     */
    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    std::uniform_int_distribution<int> coordinate_distribution(1, 12);
    std::uniform_int_distribution<int> ship_distribution(0, 7);

    Coordinate source;
    Coordinate destination{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};
    int index = ship_distribution(random_engine);
    while (true) {
        try {
//            std::cout << "Extracted " << defense_board_.ship_at_index(index)->center().to_string() << "->"
//                      << destination.to_string() << std::endl;

//          TODO: FIX THIS! WORKING BUT BRUTTO
            if (defense_board_.ship_at_index(index)->type() == Ship::Type::SUBMARINE) {
                if (defense_board_.is_occupied(destination))
                    throw std::invalid_argument("\"submarine error\"");
            }

            if (defense_board_.ship_at_index(index)->type() == Ship::Type::REPAIRSHIP) {
                std::vector<Coordinate> current_grid = defense_board_.get_all_but_one_raw(
                        defense_board_.ship_at_index(index)->center());

                Repairship tmp{destination,
                               defense_board_.ship_at_index(index)->direction()};

                for (auto position: tmp.raw_positions()) {
                    if (!defense_board_.is_valid(position))
                        throw std::invalid_argument("\"repairship position error\"");
                    if (std::find(current_grid.begin(), current_grid.end(), position) != current_grid.end())
                        throw std::invalid_argument("\"repairship error\"");
                }
            }


            source = defense_board_.ship_at_index(index)->center();

            defense_board_.ship_at_index(index)->action(destination, other.get_defense_board(),
                                                        attack_board_);

            break;
        } catch (const std::exception &e) {
            std::cout << e.what();
            index = ship_distribution(random_engine);
            destination = Coordinate{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};
        }
    }

    std::string action = source.to_string() + " " + destination.to_string();

//    std::cout << "Executed " << action << "==========" << std::endl << std::endl;

    add_to_player_history(action);
    return true;
}

bool Cpuplayer::place_ship(const Ship::Type ship_type) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP &&
        ship_type != Ship::Type::SUBMARINE)
        return 0;

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
        Coordinate center{rand() % 12 + 1, rand() % 12 + 1};
        //std::cout << center;

        int random = rand() % 2;
        // std::cout << random<<std::endl;

        if (random == 0)
            direction = Ship::Directions::HORIZONTAL;
        else
            direction = Ship::Directions::VERTICAL;

        //std::cout << direction << std::endl;

        if (direction == Ship::Directions::HORIZONTAL) {
            if ((center.col() + length / 2) > defense_board_.side_length || center.col() - length / 2 <= 0) {
                //std::cout << (center.col() + (int)(length / 2)) << std::endl<< center.col() - length / 2 << std::endl;

            } else {
                for (int i = center.col() - length / 2; i <= center.col() + length / 2; i++) {
                    Coordinate coordinate_to_check = Coordinate(center.row(), i);
                    if (defense_board_.is_occupied(coordinate_to_check) == true) {
                        break;
                    } else {
                        valid_input = true;
                    }
                }
            }
        } else {
            if (center.row() + length / 2 > defense_board_.side_length || center.row() - length / 2 <= 0) {
                //std::cout <<"limite alto "<< center.row() + length / 2 << std::endl << "limite basso "<< center.row() - length / 2 << std::endl;   
            } else {
                //std::cout <<"limite alto "<< center.row() + length / 2 << std::endl <<"limite basso "<< center.row() - length / 2 << std::endl;
                for (int i = center.row() - length / 2; i <= center.row() + length / 2; i++) {
                    Coordinate coordinate_to_check = Coordinate(i, center.col());
                    if (defense_board_.is_occupied(coordinate_to_check) == true) {
                        break;
                    } else {
                        valid_input = true;
                    }
                }

            }
        }
        //std::cout<<valid_input<<std::endl;
        if (valid_input == true) {
            if (ship_type == Ship::Type::BATTLESHIP)
                defense_board_.place_ship(Battleship(center, direction));
            else if (ship_type == Ship::Type::REPAIRSHIP)
                defense_board_.place_ship(Repairship(center, direction));
            else if (ship_type == Ship::Type::SUBMARINE)
                defense_board_.place_ship(Submarine(center, direction));
        }

        /*
         if (valid_input)
             std::cout << "Nave inserita correttamente" << std::endl;
         else
             std::cout << "Errore nell'inserimento della nave" << std::endl;*/
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
                ->action(action_coord[1], other.get_defense_board(), attack_board_);

    } catch (const std::exception &ex) {
        throw INVALID_ACTION{"Wrong coordinates!"};
    }

    return true;
}

Cpuplayer::~Cpuplayer() {

}
