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
        const char *what() const noexcept override { return "Board is full, you can't add more ships"; }
    };

    Defenseboard() = default;

    std::vector<std::pair<Coordinate, char>> get_all() const override;

    std::vector<Coordinate> get_all_raw() const override;

    bool is_lost() const;

    bool place_ship(const Ship &ship);

    bool is_full() const { return ships_.size() >= 8; }

    bool is_occupied(Coordinate &c) const ;

    bool is_alive(Coordinate &c) const;

    bool hit(Coordinate &c) {
        if (!is_occupied(c)) return false;

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
    bool heal(Coordinate &c) {
        if (!is_occupied(c)) return false;

        for (auto &ship: ships_) {
            std::vector<Coordinate> positions = ship->raw_positions();
            auto cell = std::find(positions.begin(), positions.end(), c);
            if (!(cell == positions.end())) {
                ship->heal(c);
                return true;
            }
        }
        return false;
    }

    // FT -> Da sistemare e discutere
    const std::unique_ptr<Ship> &ship_at(Coordinate c) const ;

    const std::unique_ptr<Ship> &ship_at_index(int i) const ;

    std::string to_log_format() const;

private:
    // declaring array of smart pointers (ships_) with 7 ships_:
    // battle (3) repair (3) and submarine (2)
    std::vector<std::unique_ptr<Ship>> ships_;
    const std::unique_ptr<Ship> NO_SHIP = nullptr;
};

#endif  // DEFENSEBOARD_H