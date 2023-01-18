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
    /**
     * INVALID_ACTION [Exception]
     * throwed when an action does not contain XYOrigin and XYTarget.
     * 
     */
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

    /**
     * Default Cpuplayer constructor
     * @details default, no need to initialize with a value
     */
    Cpuplayer() = default;

    /**
     * Places a ship on the defenseboard
     * @param ship_type enum of the class Ship, used to identify the type of ship to place down
     * @details the function member asks for the details of the ship and places it down on the board
     */
    void place_ship(const Ship::Type ship_type) override;

    /**
     * Executes the turn of a cpu player
     * @param other Player to execute action on his defenseboard
     * @details the function member asks for an action, processes it and save the result on the player history
     */
    void turn(Player &other) override;

    
    /**
     * Function that replay an action
     * @param  {Player} other       : other player
     * @param  {std::string} action : action to replay
     * @return {bool}               : true if the action was successful 
     */
    bool replay_turn(Player &other, const std::string &action);

    /**
     * Replace a board on Defenseboard
     * @param  {Ship::Type} ship_type : enum of the class Ship, used to identify the type of ship to place down
     * @param  {std::string} info     : the orientation of the ship and where to place
     * @return {bool}                 : true if the ship has been placed
     */
    bool replay_place_ship(const Ship::Type &ship_type, const std::string &info);

private:
};

#endif  // CPUPLAYER_H