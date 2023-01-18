/**
 * @author Galiazzo Matteo
 */

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>

#include "./../include/player/cpuplayer.h"
#include "./../include/player/humanplayer.h"

int manager(int argc, char *argv[]);
void test_dev_matteo_rampin() {
    std::cout << "=== dev-matteo-rampin ===" << std::endl;
    //Cpuplayer cp;
    //Humanplayer hp;
    // hp.place_ship(Ship::Type::BATTLESHIP);
    // hp.print_boards();
    // Coordinate a = Coordinate(1,1);
    // cout<<hp.get_defense_board().is_occupied(a);
    // hp.place_ship(Ship::Type::BATTLESHIP);
    Humanplayer hp;
    Humanplayer hp2;
    
    hp.place_ship(Ship::Type::REPAIRSHIP);
    hp.place_ship(Ship::Type::BATTLESHIP);
    //hp.place_ship(Ship::Type::SUBMARINE);
    hp.print_boards_inline();
    Coordinate a1 = Coordinate("A1");
    Coordinate a2 = Coordinate("E7");
    Coordinate a3 = Coordinate("H4");
    /*hp.get_defense_board().hit(a1);
    hp.get_defense_board().hit(a2);
    hp.get_defense_board().hit(a3);*/
    hp.turn(hp2);
    hp.print_boards_inline();
    /*hp.turn(hp2);
    hp.print_boards_inline();
    hp.turn(hp2);
    hp.print_boards_inline();*/
    /*
    std::vector<Coordinate> coordinate = hp.get_defense_board().ship_at(a3)->raw_positions();
    for (auto i = coordinate.begin(); i != coordinate.end(); i++)
    {
        std::cout<<i->to_string()<<" ";
    }*/
    hp.get_defense_board().hit(a3);
    hp.print_boards_inline();
    hp.turn(hp2);
    hp.print_boards_inline();
    hp.turn(hp2);
    hp.print_boards_inline();
    hp.turn(hp2);
    hp.print_boards_inline();
    hp.turn(hp2);
    hp.print_boards_inline();
    //std::cout<<hp.get_defense_board().ship_at(a2)->armor();
    
    /*Defenseboard db {};
    Attackboard ab {};
    Repairship b4{Coordinate{9, 4}, Ship::Directions::HORIZONTAL};
    Battleship b3{Coordinate{8, 4}, Ship::Directions::HORIZONTAL};
    db.place_ship(b4);
    db.place_ship(b3);
    Coordinate c {8,4};
    db.hit(c);
    std::vector<bool>a = db.ship_at(Coordinate{8, 4})->cells();
    for (auto i = a.begin(); i != a.end(); i++)
    {
        cout<<*i;
    }
    cout<<endl;
    db.ship_at(Coordinate{9, 4})->action(Coordinate{2, 4}, db, ab);
    std::vector<Coordinate> coordinate = db.ship_at(Coordinate{2, 4})->raw_positions();
    for (auto i = coordinate.begin(); i != coordinate.end(); i++)
    {
        cout<<i->to_string()<<" ";
    }
    cout<<endl;
    db.ship_at(Coordinate{2, 4})->action(Coordinate{9, 4}, db, ab);
    std::vector<bool>b = db.ship_at(Coordinate{8, 4})->cells();
    for (auto i = b.begin(); i != b.end(); i++)
    {
        cout<<*i;
    }
    cout<<endl;
    std::vector<Coordinate> coordinate2 = db.ship_at(Coordinate{9, 4})->raw_positions();
    for (auto i = coordinate2.begin(); i != coordinate2.end(); i++)
    {
        cout<<i->to_string()<<" ";
    }*/
}

int main(int argc, char *argv[]) {
    test_dev_matteo_rampin();
    /*
    try {
        manager(argc, argv);
    } catch (const std::exception &ex) {
        std::cerr << ex.what();
    }*/
    return 0;
}

int manager(int argc, char *argv[]) {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());

    bool human_computer_game = false;
    int turn_counter = 0;
    constexpr int MAX_TURNS = 150;

    std::uniform_int_distribution<int> starting_player_distribution(0, 1);

    // At this moment i don't know if the game is human/cpu or cpu/cpu
    std::unique_ptr<Player> player1, player2;

    // < 2 because first argument is executable name
    if (argc < 2) {
        throw std::invalid_argument("Insufficient arguments");
    }

    if (std::string{argv[1]} == "-pc" || std::string{argv[1]} == "pc") human_computer_game = true;

    if (!human_computer_game && (std::string{argv[1]} != "-cc" && std::string{argv[1]} != "cc"))
        throw std::invalid_argument("Invalid arguments no pc/-pc or cc/-cc found!");

    const bool player1_starts = starting_player_distribution(random_engine) == 0;

    if (human_computer_game) {
        player1.reset(new Humanplayer{});
    } else {
        player1.reset(new Cpuplayer{});
    }
    player2.reset(new Cpuplayer{});

    player1->place_all_ships();
    player2->place_all_ships();

    std::string player1_initial_board = {player1->get_defense_board().to_log_format()};
    std::string player2_initial_board = {player2->get_defense_board().to_log_format()};

    colored_print("Initial Player 1 boards:", MESSAGE_TYPE::MSG_SUCCESS) << std::endl;
    player1->print_boards_inline();
    std::cout << std::endl;
    colored_print("Initial Player 2 boards:", MESSAGE_TYPE::MSG_SUCCESS) << std::endl;
    player2->print_boards_inline();
    std::cout << std::endl;

    bool last_player_action_turn_flag = !player1_starts;  // true -> player 1 did last move, false -> player 2 did last move
    colored_print(player1_starts ? "Player 1 starts\n" : "Player 2 starts\n", MESSAGE_TYPE::MSG_INFO_BOLD);
    std::cout << std::endl;

    while (player1->is_alive() && player2->is_alive() && turn_counter < MAX_TURNS) {
        if (!last_player_action_turn_flag) {
            // if (!human_computer_game) std::this_thread::sleep_for(std::chrono::milliseconds(500));
            last_player_action_turn_flag = true;
            colored_print("Player 1 Turn:", MESSAGE_TYPE::MSG_PLAYER1) << std::endl;
            player1->turn(*player2);
            player1->print_boards_inline();
        } else {
            // std::this_thread::sleep_for(std::chrono::milliseconds(500));
            last_player_action_turn_flag = false;
            colored_print("Player 2 Turn:", MESSAGE_TYPE::MSG_PLAYER1) << std::endl;
            player2->turn(*player1);
            player2->print_boards_inline();
        }
        turn_counter++;
    }

    // win check
    if (last_player_action_turn_flag && turn_counter < MAX_TURNS) {
        colored_print("Player 1 WIN!", MESSAGE_TYPE::MSG_INFO_BOLD);
    } else if (turn_counter < MAX_TURNS) {
        colored_print("Player 2 WIN!", MESSAGE_TYPE::MSG_INFO_BOLD);
    } else {
        colored_print("DRAW!", MESSAGE_TYPE::MSG_INFO_BOLD);
    }

    /**
     * Mandadory cStyle before c++ 17 :(
     */
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    std::stringstream s(std::string{});
    s << std::put_time(&tm, "%Y%m%d_%H%M%S");
    std::string date_string;
    s >> date_string;

    std::string file_name =
        std::string{"log-"} + (human_computer_game ? "PC" : "CC") + "-" + date_string + std::string{".txt"};

#if defined(__linux__) || defined(__APPLE__)
    file_name.insert(0, "./");
#else
    file_name.insert(0, "../");
#endif

    std::ofstream file_out_stream;

    file_out_stream.open(file_name);

    if (!file_out_stream.is_open()) {
        throw std::invalid_argument{"Can't open output file_in_stream!"};
    }

    // saving player's histories
    std::vector<std::string> player1_history = player1->player_history();
    std::vector<std::string> player2_history = player2->player_history();

    // saving initial boards
    file_out_stream << player1_initial_board << std::endl;
    file_out_stream << player2_initial_board << std::endl;

    // printing who starts
    file_out_stream << (player1_starts ? "1" : "2") << std::endl;

    // printing to file the history vectors, with a runtime merge, using the fact that int / 2 is always floored
    for (int i = 0; i < (player1_history.size() + player2_history.size()); i++) {
        if (player1_starts) {
            if (i % 2 == 0) {
                file_out_stream << player1_history.at(i / 2) << std::endl;
            } else {
                file_out_stream << player2_history.at(i / 2) << std::endl;
            }
        } else {
            if (i % 2 == 0) {
                file_out_stream << player2_history.at(i / 2) << std::endl;
            } else {
                file_out_stream << player1_history.at(i / 2) << std::endl;
            }
        }
    }

    // closing the stream
    file_out_stream.close();

    return 0;
}