/**
 * @author Rampin Matteo
 */

#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include <ctime>
#include <random>
#include <sstream>

#include "player.h"

class Cpuplayer : public Player {
public:
    class INVALID_ACTION : public std::exception {
    private:
        std::string message_;

    public:
        explicit INVALID_ACTION(const std::string &message) : message_{message} {};

        const char *what() const noexcept override { return message_.c_str(); }
    };

    /**
     * @override
     *  Player pure virtual distructor
     * @related
     *  Player::~Player()
     *
     * @see documentation of pure virtual method
     *
     * @related Replay, HumanPlayer, Player
     */
    ~Cpuplayer() override;

    Cpuplayer() = default;

    void place_ship(const Ship::Type ship_type) override;

    void turn(Player &other) override;

    bool replay_turn(Player &other, const std::string &action);

    bool replay_place_ship(const Ship::Type &ship_type, const std::string &info);

private:
};

#endif  // CPUPLAYER_H