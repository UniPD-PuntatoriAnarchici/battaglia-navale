#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <sstream>

#include "player.h"

class Humanplayer : public Player {
   public:
    Humanplayer() = default;
    bool place_ship(const Ship::Type ship_type) override;
    bool turn(Player &other) override;
    bool check_ship_length(int n1, int n2, const Ship::Type ship_type);
    Coordinate get_ship_center(int row, int col, Ship::Directions direction, Ship::Type ship_type);
    std::vector<Coordinate> split_coordinates(const std::string &s);
    std::vector<std::string> split_string(const std::string &s);

   private:
};

// bool place_ships(); + overload
// place ships_ con le stringhe

#endif  // HUMANPLAYER_H
