#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include <sstream>
#include <random>
#include <ctime>

#include "player.h"

class Cpuplayer : public Player {
public:
    Cpuplayer() = default;

    bool place_ship(const Ship::Type ship_type) override;

    bool turn(Player &other) override;

private:
};


#endif  // CPUPLAYER_H