#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "player/cpuplayer.h"

std::vector<std::string> split_strings(const std::string &string, char delimiter = ' ');

void fill_player(Cpuplayer &player, const std::string &ships);

class INVALID_FILE_FORMAT : public std::exception {
private:
    std::string message_;

public:
    explicit INVALID_FILE_FORMAT(const std::string &message) : message_{message} {};

    const char *what() const noexcept override { return message_.c_str(); }
};

int main(int argc, char *argv[]) {
    bool to_file = false;
    bool a_starts = true;
    std::string buffer;

    std::ofstream file_out_stream;
    std::ifstream file_in_stream;

    Cpuplayer player1, player2;

    if (argc < 3) {
        throw std::invalid_argument("Insufficient arguments");
    }

    if (std::string{argv[1]} == "-f" || std::string{argv[1]} == "f") to_file = true;

    if (!to_file && (std::string{argv[1]} != "-v" && std::string{argv[1]} != "v"))
        throw std::invalid_argument("Invalid arguments no f/-f or v/-v found!");

    if (to_file && argc < 4)
        throw std::invalid_argument(
                "Insufficient arguments: file_in_stream argument need input and output file_in_stream names!");

    file_in_stream.open(std::string{argv[2]});

    if (!file_in_stream.is_open()) throw std::invalid_argument{"Can't open replay file_in_stream!"};

    if (to_file) {
        file_out_stream.open(std::string{argv[3]});
        if (!file_out_stream.is_open()) throw std::invalid_argument{"Can't open output file_in_stream!"};
    }

    std::ostream *output_general_stream;
    if (to_file) {
        output_general_stream = &file_out_stream;
    } else {
        output_general_stream = &std::cout;
    }

    std::getline(file_in_stream, buffer);
    fill_player(player1, buffer);

    std::getline(file_in_stream, buffer);
    fill_player(player2, buffer);

    colored_print("Initial Player 1 boards:", MESSAGE_TYPE::MSG_SUCCESS, *output_general_stream) << std::endl;
//    player1.print_boards_inline(std::cout);
    player1.print_boards_inline(*output_general_stream);
    *output_general_stream << std::endl;

    colored_print("Initial Player 2 boards:", MESSAGE_TYPE::MSG_SUCCESS, *output_general_stream) << std::endl;
//    player2.print_boards_inline(std::cout);
    player2.print_boards_inline(*output_general_stream);

    for (int i = 0; i < 110; i++) *output_general_stream << "=";
    *output_general_stream << std::endl << std::endl;

    std::getline(file_in_stream, buffer);

    if (buffer != "1" && buffer != "2") throw INVALID_FILE_FORMAT{"Starting player not defined!"};

    a_starts = (buffer == "1");

    if (!to_file) std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    bool last_a = !a_starts;
    while (!file_in_stream.eof()) {
        std::getline(file_in_stream, buffer);
        if (buffer.empty())
            break;

        try {
//            std::cout << buffer << std::endl;
            if (!last_a) {
//                for (Coordinate pos: player1.get_defense_board().get_all_raw()) {
//                    std::cout << pos.to_string() << " ";
//                }
//                std::cout << "===========" << std::endl << std::endl;
                player1.replay_turn(player2, buffer);
                last_a = true;
                colored_print("Player 1 Turn:", MESSAGE_TYPE::MSG_PLAYER1, *output_general_stream)
                        << std::endl;
                player1.print_boards_inline(*output_general_stream);
                *output_general_stream << std::endl;
            } else {
//                for (Coordinate pos: player2.get_defense_board().get_all_raw()) {
//                    std::cout << pos.to_string() << " ";
//                }
//                std::cout << "===========" << std::endl << std::endl;
                player2.replay_turn(player1, buffer);
                colored_print("Player 2 Turn:", MESSAGE_TYPE::MSG_PLAYER2, *output_general_stream)
                        << std::endl;
                last_a = false;
                player2.print_boards_inline(*output_general_stream);
                *output_general_stream << std::endl;
            }
            if (!to_file) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        } catch (const std::exception &e) {
            std::cerr << "Buffer: " << buffer << e.what();
            std::vector<Coordinate> coord = player1.get_defense_board().get_all_raw();
            throw;
        }
    }

    return 0;
}

void fill_player(Cpuplayer &player, const std::string &ships) {
    std::vector<std::string> ships_info = split_strings(ships);
    for (int i = 0; i < 3; i++) {
        player.replay_place_ship(Ship::Type::BATTLESHIP, ships_info[i]);
    }

    for (int i = 3; i < 6; i++) {
        player.replay_place_ship(Ship::Type::REPAIRSHIP, ships_info[i]);
    }

    for (int i = 6; i < 8; i++) {
        player.replay_place_ship(Ship::Type::SUBMARINE, ships_info[i]);
    }
}

std::vector<std::string> split_strings(const std::string &string, char delimiter) {
    std::vector<std::string> strings;
    std::istringstream iss(string);
    std::string item;
    while (std::getline(iss, item, delimiter)) strings.push_back(item);
    return strings;
}
