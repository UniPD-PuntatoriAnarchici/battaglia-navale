#include "./../../include/player/cpuplayer.h"

bool Cpuplayer::turn(Player &other) {
    if (defense_board_.is_lost()) return false;

    /*
     * Random device generates random seed for Mersenne Twister that pick random number from distribution
     */
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());

    std::uniform_int_distribution<int> coordinate_distribution(1, 12);
    std::uniform_int_distribution<int> ship_distribution(0, 7);

    Coordinate destination{coordinate_distribution(randomEngine), coordinate_distribution(randomEngine)};
    defense_board_.ship_at_index(ship_distribution(randomEngine))->action(destination, other.get_defense_board(),
                                                                          attack_board_);

    Coordinate source = defense_board_.ship_at_index(ship_distribution(randomEngine))->center();

    std::string action = source.to_string() + " " + destination.to_string();

    add_to_player_history(action);
    return true;
}


bool Cpuplayer::place_ship(const Ship::Type ship_type) {

    //TODO: implement this and test turn!
    return false;
}
