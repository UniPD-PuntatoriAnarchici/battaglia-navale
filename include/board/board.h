//
// Created by Matteo Galiazzo on 25/12/2022
//

#ifndef BOARD_H

#include <vector>

#include "./../coordinate/coordinate.h"
#include "./../ship/battleship.h"
#include "./../ship/repairship.h"
#include "./../ship/ship.h"
#include "./../ship/submarine.h"

class Board {
   public:
    Board(){};
    virtual Coordinate get_all() = 0;
    bool is_valid(Coordinate c);
    bool is_occupied(Coordinate c);
    static constexpr int dim = 12;

   private:
    std::vector<Ship> ships;
};
#define BOARD_H

#endif  // BOARD_H