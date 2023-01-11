#ifndef DEFENSEBOARD_H
#define DEFENSEBOARD_H

#include <memory>
#include <queue>

#include "./../ship/battleship.h"
#include "./../ship/repairship.h"
#include "./../ship/submarine.h"
#include "board.h"

class Defenseboard : public Board {
public:
    class FULL_BOARD_EXCEPTION : public std::exception {
        const char *what() const noexcept override {
            return "Board is full, you can't add more ships";
        }
    };

    Defenseboard() = default;

    std::vector<std::pair<Coordinate, char>> get_all() override;

    std::vector<Coordinate> get_all_raw() override;

    bool is_lost();

    bool place_ship(const Ship &ship);


    bool is_occupied(Coordinate &c) {
        std::vector<Coordinate> opponent_postions = get_all_raw();
        auto found = std::find(opponent_postions.begin(), opponent_postions.end(), c);

        return found != opponent_postions.end();
    }

    bool hit(Coordinate &c) {

        if (!is_occupied(c))
            return false;

        for (auto &ship: ships_) {
            std::vector<Coordinate> positions = ship->raw_positions();
            auto cell = std::find(positions.begin(), positions.end(), c);
            if (!(cell == positions.end())) {
                ship->hit(c);
                return true;
            }
        }
        return false;
    }

    //FT -> Da sistemare e discutere
    const std::unique_ptr<Ship> &ship_at(Coordinate c) {
        for (auto &ship: ships_) {
            if (ship->center() == c) {
                return ship;
            }
        }
        throw std::exception{};
        return NO_SHIP;
    }

    const std::unique_ptr<Ship> &ship_at_index(int i) {
        if (i > 7)
            throw std::invalid_argument("Only 8 ships!");

        return ships_.at(i);
    }

private:
    // declaring array of smart pointers (ships_) with 7 ships_:
    // battle (3) repair (3) and submarine (2)
    std::vector<std::unique_ptr<Ship>> ships_;
    const std::unique_ptr<Ship> NO_SHIP = nullptr;
};

#endif  // DEFENSEBOARD_H