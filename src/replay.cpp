#include <iostream>
#include "player/cpuplayer.h"

int main() {
    std::cout << "REPLAY" << std::endl;
    Cpuplayer cp;
    cp.place_ship(Ship::Type::BATTLESHIP);
    cp.place_ship(Ship::Type::BATTLESHIP);
    cp.place_ship(Ship::Type::BATTLESHIP);
    cp.print_boards();
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.print_boards();
    cp.place_ship(Ship::Type::SUBMARINE);
    cp.place_ship(Ship::Type::SUBMARINE);
    cp.print_boards();
    return 0;
}