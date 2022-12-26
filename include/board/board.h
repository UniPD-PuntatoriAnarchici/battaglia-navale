//
// Created by Matteo Galiazzo on 25/12/2022
//

#ifndef BOARD_H

#include "./../coordinate/coordinate.h"
class Board {
   public:
    virtual Coordinate get_all() = 0;
    static constexpr int dim = 12;

   private:
};
#define BOARD_H

#endif  // BOARD_H