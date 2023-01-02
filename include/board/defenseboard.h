#ifndef DEFENSEBOARD_H
#define DEFENSEBOARD_H

#include <memory>
#include <queue>

#include "./../ship/battleship.h"
#include "./../ship/submarine.h"
#include "board.h"
// TODO: include other ships_

class Defenseboard : public Board {
   public:
    class FULL_BOARD_EXCEPTION : public std::exception {
        const char *what() const noexcept override {
            return "Board is full, you can't add more ships";
        }
    };

    Defenseboard() {}

    std::vector<std::pair<Coordinate,char>>  get_all() override;

    bool is_lost();

    bool place_ship(const Ship &ship);

   private:
    // declaring array of smart pointers (ships_) with 7 ships_:
    // battle (3) repair (3) and submarine (2)
    std::vector<std::unique_ptr<Ship>> ships_;
};

#endif  // DEFENSEBOARD_H