//
// Created by Filippo Tiberio on 24/12/2022.
//

#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <ostream>

#include "./../coordinate/coordinate.h"

class Attackboard;

class Defenseboard;

class Ship {
public:
    enum class Directions {
        HORIZONTAL, VERTICAL
    };

    friend std::ostream &operator<<(std::ostream &os, const Ship::Directions &direction) {
        os << (((int) direction) == 0 ? "HORIZONTAL" : "VERTICAL");
        return os;
    }

    bool is_alive() const;

    /**
     * Virtual!
     */
    virtual ~Ship() = default;

    const Coordinate &center() const {
        return center_;
    }

    void set_center(const Coordinate &center) {
        center_ = center;
    }

    Directions direction() const {
        return direction_;
    }

    void set_direction(Directions direction) {
        direction_ = direction;
    }

    const std::vector<bool> &cells() const {
        return cells_;
    }

    void reset_cells() {
        for (auto &&cell: cells_) {
            cell = true;
        }
    }

    int armor() const {
        return armor_;
    }

    void set_armor(int armor) {
        armor_ = armor;
    }

    std::vector<Coordinate> positions() const {
        std::vector<Coordinate> positions;

        int length = (int) cells().size();

        std::pair<int, int> center = Coordinate::coordinates_to_indexes(center_);

        for (int i = 0; i < length; i++) {
            if (direction_ == Directions::HORIZONTAL) {
                positions.emplace_back(center.first, center.second - (length / 2) + i);
            } else {
                positions.emplace_back(center.first - (length / 2) + i, center.second);
            }
        }

        return positions;
    }

protected:
    static constexpr char CHARACTER = ' ';
    static constexpr int LENGTH = 0;

    Coordinate center_;
    Directions direction_;
    std::vector<bool> cells_;
    int armor_;

    virtual bool action(Coordinate dest, Defenseboard &opponent,
                        Attackboard &self) = 0;

private:

};


#endif  // SHIP_H
