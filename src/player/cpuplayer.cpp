/**
 * @author Rampin Matteo
 */

#include "./../../include/player/cpuplayer.h"

/**
 * Executes the turn of a cpu player
 * @param other Player to execute action on his defenseboard
 * @details the function member asks for an action, processes it and save the result on the player history
 */
void Cpuplayer::turn(Player &other) {
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

        destination = Coordinate{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};//random generation of coordinate where to move and use action
        index = ship_distribution(random_engine);//random generation of the ship to use

        if ((defense_board_.ship_at_index(index)) == nullptr) {
            dead_ship = true;
            continue;
        }

        source = defense_board_.ship_at_index(index)->center();

        //        std::cout << source << destination;
    } while (dead_ship || !defense_board_.ship_at_index(index)->action(destination, defense_board_, attack_board_,
                                                                       other.get_defense_board()));

    //creating action to add in history
    std::string action = source.to_string() + " " + destination.to_string();
    add_to_player_history(action);
}

/**
 * Places a ship on the defenseboard
 * @param ship_type enum of the class Ship, used to identify the type of ship to place down
 * @details the function member asks for the details of the ship and places it down on the board
 */
void Cpuplayer::place_ship(const Ship::Type ship_type) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP && ship_type != Ship::Type::SUBMARINE)
        throw std::invalid_argument{"Invalid ship type"};

    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    std::uniform_int_distribution<int> coordinate_distribution(1, 12);
    std::uniform_int_distribution<int> ship_direction_distribution(0, 1);

    //set length of the ship to place
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
        Coordinate center{coordinate_distribution(random_engine), coordinate_distribution(random_engine)};//random generation of center of the ship

        //generating the direction of the ship
        if (ship_direction_distribution(random_engine) == 0)
            direction = Ship::Directions::HORIZONTAL;
        else
            direction = Ship::Directions::VERTICAL;

        valid_input = valid_ship_placement(center, length, direction);//checking if the ship can be placed

        //placing the ship
        if (valid_input) {
            if (ship_type == Ship::Type::BATTLESHIP)
                defense_board_.place_ship(Battleship(center, direction));
            else if (ship_type == Ship::Type::REPAIRSHIP)
                defense_board_.place_ship(Repairship(center, direction));
            else
                defense_board_.place_ship(Submarine(center, direction));
        }
    }
}

/**
 * Replace a board on Defenseboard
 * @param  {Ship::Type} ship_type : enum of the class Ship, used to identify the type of ship to place down
 * @param  {std::string} info     : the orientation of the ship and where to place
 * @return {bool}                 : true if the ship has been placed
 */
bool Cpuplayer::replay_place_ship(const Ship::Type &ship_type, const std::string &info) {
    if (ship_type != Ship::Type::BATTLESHIP && ship_type != Ship::Type::REPAIRSHIP && ship_type != Ship::Type::SUBMARINE)
        return false;

    if (defense_board_.is_full()) {
        colored_print("La griglia e' piena!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }

    if (info.length() < 3 || info.length() > 4) {
        colored_print("Informazioni sulla nave non valide!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }
    //checking orientation
    if (info.at(0) != 'H' && info.at(0) != 'V') {
        colored_print("Direzione della nave non valida!", MESSAGE_TYPE::MSG_ERROR, std::cerr) << std::endl;
        return false;
    }

    Coordinate center = Coordinate{info.substr(1, info.length())};
    Ship::Directions direction = (info.at(0) == 'H') ? Ship::Directions::HORIZONTAL : Ship::Directions::VERTICAL;//taking orientation

    if (ship_type == Ship::Type::BATTLESHIP)
        defense_board_.place_ship(Battleship(center, direction));
    else if (ship_type == Ship::Type::REPAIRSHIP)
        defense_board_.place_ship(Repairship(center, direction));
    else if (ship_type == Ship::Type::SUBMARINE)
        defense_board_.place_ship(Submarine(center, direction));

    return true;
}

/**
 * Function that replay an action
 * @param  {Player} other       : other player
 * @param  {std::string} action : action to replay
 * @return {bool}               : true if the action was successful 
 */
bool Cpuplayer::replay_turn(Player &other, const std::string &action) {
    if (defense_board_.is_lost()) return false;

    std::vector<Coordinate> action_coord = Coordinate::split_coordinates(action);//taking the action to do

    if (action_coord.size() != 2) throw INVALID_ACTION{"Action must contain XYOrigin and XYTarget"};

    try {
        defense_board_.ship_at(action_coord[0])
            ->action(action_coord[1], defense_board_, attack_board_, other.get_defense_board());

    } catch (const std::exception &ex) {
        throw INVALID_ACTION{"Wrong coordinates!"};
    }

    return true;
}

/**
     * @override
     *  Player pure virtual distructor
     * @related
     *  Player::~Player()
     *
     * @see documentation of pure virtual method
     *
     * @related Replay, HumanPlayer, Player
     */
Cpuplayer::~Cpuplayer() {}
