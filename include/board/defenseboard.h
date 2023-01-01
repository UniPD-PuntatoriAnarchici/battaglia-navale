#ifndef DEFENSEBOARD_H
#define DEFENSEBOARD_H

#include <memory>

#include "./../ship/battleship.h"
#include "./../ship/submarine.h"
#include "board.h"
// TODO: include other ships

class Defenseboard : public Board {
   public:
    class FULL_BOARD_EXCEPTION : public std::exception {
        const char *what() const noexcept override {
            return "Board is full, you can't add more ships";
        }
    };

    Defenseboard() {}

    std::vector<Coordinate> get_all() override { return std::vector<Coordinate>(1); }

    bool is_lost();

    bool place_ship(const Ship &ship);

   private:
    // declaring array of smart pointers (ships) with 7 ships:
    // battle (3) repair (3) and submarine (2)
    std::vector<std::unique_ptr<Ship>> ships;
};

#endif  // DEFENSEBOARD_H