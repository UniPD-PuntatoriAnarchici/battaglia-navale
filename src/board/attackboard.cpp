/**
 * @author Tiberio Filippo
 */
#include "./../../include/board/attackboard.h"

Attackboard::Attackboard() = default;

std::vector<std::pair<Coordinate, char>> Attackboard::get_all() const {
    std::vector<std::pair<Coordinate, char>> vector{};

    for (auto el: cells_) {
        vector.emplace_back(el.first, el.second);
    }
    return vector;
}

std::vector<Coordinate> Attackboard::get_all_raw() const {
    std::vector<Coordinate> vector{};

    for (auto el: cells_) {
        vector.push_back(el.first);
    }
    return vector;
}

int Attackboard::num_elements() const { return static_cast<int>(cells_.size()); }

void Attackboard::hit(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    cells_[c] = 'X';
}

void Attackboard::miss(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};

    cells_[c] = 'O';
}

void Attackboard::reveal(Coordinate c, bool is_alive) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};
    cells_[c] = (is_alive) ? 'J' : 'X';
}

void Attackboard::clear(Coordinate c) {
    if (!c.is_valid()) throw Coordinate::INVALID_COORDINATE{};
    cells_.erase(c);
}

void Attackboard::clear_hits() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'X') {
            el = cells_.erase(el);
        } else {
            el++;
        }
    }
}

void Attackboard::clear_misses() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'O') {
            el = cells_.erase(el);
        } else {
            el++;
        }
    }
}

void Attackboard::clear_reveals() {
    for (auto el = cells_.begin(); el != cells_.end();) {
        if (el->second == 'J') {
            el = cells_.erase(el);
        } else {
            el++;
        }
    }
}
