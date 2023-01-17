/**
 * @author Galiazzo Matteo
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class Humanplayer : public Player {
   public:
    ~Humanplayer() override;

    Humanplayer() = default;

    void place_ship(const Ship::Type ship_type) override;

    void turn(Player &other) override;

    bool check_ship_length(int n1, int n2, const Ship::Type ship_type);

    Coordinate get_ship_center(int row, int col, Ship::Directions direction, Ship::Type ship_type);

    std::vector<Coordinate> split_coordinates(const std::string &s);

    std::vector<std::string> split_string(const std::string &s);

   private:
};

#endif  // HUMANPLAYER_H
