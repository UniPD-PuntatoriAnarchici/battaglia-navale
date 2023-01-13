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

    Coordinate destination{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};
    defense_board_.ship_at_index(ship_distribution(random_engine))->action(destination, other.get_defense_board(), attack_board_);

    Coordinate source = defense_board_.ship_at_index(ship_distribution(random_engine))->center();

    std::string action = source.to_string() + " " + destination.to_string();

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
        std::cout << center;

        int random = rand() % 2;
        // std::cout << random<<std::endl;

        if (random == 0)
            direction = Ship::Directions::HORIZONTAL;
        else
            direction = Ship::Directions::VERTICAL;

        std::cout << direction << std::endl;

        if (direction == Ship::Directions::HORIZONTAL) {
            if ((center.col() + length / 2) > defense_board_.side_length || center.col() - length / 2 < 0) {
                std::cout << (center.col() + (int)(length / 2)) << std::endl
                          << center.col() - length / 2 << std::endl;
                valid_input = false;
            } else {
                valid_input = true;
            }
        } else {
            if (center.row() + length / 2 > defense_board_.side_length || center.row() - length / 2 < 0) {
                std::cout << center.row() + length / 2 << std::endl << center.row() - length / 2 << std::endl;
                valid_input = false;
            } else {
                valid_input = true;
            }
        }
        // std::cout<<valid_input<<std::endl;
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
