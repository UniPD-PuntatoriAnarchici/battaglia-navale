#include <iostream>
#include <queue>

#include "./../include/board/attackboard.h"
#include "./../include/board/defenseboard.h"
#include "./../include/player/cpuplayer.h"
#include "./../include/player/humanplayer.h"

#include <chrono>
#include <thread>

#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>

#include <sstream>

using namespace std;

void test_dev_matteo_galiazzo() {
    cout << "=== dev-matteo-galiazzo ===" << endl;

    vector<pair<Coordinate, char>> occupied_positions;
    Submarine s1{};
    cout << s1 << endl;
    cout << "S1 occupies: ";
    occupied_positions = s1.positions();
    for (auto c: occupied_positions) {
        cout << c.first;
    }
    cout << endl;

    Submarine s2{Coordinate{3, 3}, Ship::Directions::VERTICAL};
    cout << s2 << endl;
    cout << "S2 occupies: ";
    occupied_positions = s2.positions();
    for (auto c: occupied_positions) {
        cout << c.first;
    }
    cout << endl;

    Battleship b1{Coordinate{3, 8}, Ship::Directions::VERTICAL};
    cout << b1 << endl;
    cout << "B1 occupies: ";
    occupied_positions = b1.positions();
    for (auto c: occupied_positions) {
        cout << c.first;
    }
    cout << endl;

    Defenseboard db;
    cout << db.place_ship(s1) << endl;
    cout << db.place_ship(s2) << endl;

    Humanplayer hp;
    hp.place_ship(Ship::Type::BATTLESHIP);
    hp.place_ship(Ship::Type::BATTLESHIP);
    hp.place_ship(Ship::Type::BATTLESHIP);

    hp.place_ship(Ship::Type::REPAIRSHIP);
    hp.place_ship(Ship::Type::REPAIRSHIP);
    hp.place_ship(Ship::Type::REPAIRSHIP);

    hp.place_ship(Ship::Type::SUBMARINE);
    hp.place_ship(Ship::Type::SUBMARINE);
    // hp.print_defense_board();

    Humanplayer hp2;
    hp2.place_ship(Ship::Type::BATTLESHIP);
    hp2.place_ship(Ship::Type::BATTLESHIP);
    hp2.place_ship(Ship::Type::BATTLESHIP);

    hp2.place_ship(Ship::Type::REPAIRSHIP);
    hp2.place_ship(Ship::Type::REPAIRSHIP);
    hp2.place_ship(Ship::Type::REPAIRSHIP);

    hp2.place_ship(Ship::Type::SUBMARINE);
    hp2.place_ship(Ship::Type::SUBMARINE);

    hp.turn(hp2);
    hp.turn(hp2);
    hp.turn(hp2);
    hp.turn(hp2);
}

void test_dev_filippo_tiberio() {
    cout << endl << "=== dev-filippo-tiberio ===" << endl;

    //    // region Coordinate
    //    Coordinate c1{};
    //    cout << c1;
    //
    //    Coordinate c2{"B4"};
    //    cout << c2;
    //
    //    //    try {
    //    //        Coordinate c3{"J4"};
    //    //        cout << c3;
    //    //    } catch (const std::exception &e) {
    //    //        cerr << e.what() << endl;
    //    //    }
    //    //
    //    //    try {
    //    //        Coordinate c4{"Z4"};
    //    //        cout << c4;
    //    //    } catch (const std::exception &e) {
    //    //        cerr << e.what() << endl;
    //    //    }
    //    //
    //    //    try {
    //    //        Coordinate c5{"4"};
    //    //        cout << c5;
    //    //    } catch (const std::exception &e) {
    //    //        cerr << e.what() << endl;
    //    //    }
    //    //
    //    //    try {
    //    //        Coordinate c6{"B14"};
    //    //        cout << c6;
    //    //    } catch (const std::exception &e) {
    //    //        cerr << e.what() << endl;
    //    //    }
    //
    //    Coordinate c7{"C7"};
    //    cout << c7;
    //
    //    cout << (c1 < c2);
    //
    //    Coordinate c8{"N12"};
    //    cout << c8;
    //
    //    // endregion
    //
    //    cout << endl << "----------------" << endl;
    //
    //    Battleship b1{};
    //    cout << b1 << endl;
    //    cout << "Battleship b1 positions: ";
    //    try {
    //        auto positions1 = b1.positions();
    //        for (auto p: positions1) {
    //            cout << p.first << " ";
    //        }
    //    } catch (const std::exception &e) {
    //        cout << e.what() << endl;
    //    }
    //    cout << endl;
    //
    //    Battleship b2{Coordinate{3, 3}, Ship::Directions::VERTICAL};
    //    cout << b2 << endl;
    //
    //    cout << "Battleship b2 positions: ";
    //    auto positions2 = b2.positions();
    //    for (auto p: positions2) {
    //        cout << p.first << " ";
    //    }
    //    cout << endl;

    Battleship b3{Coordinate{9, 4}, Ship::Directions::HORIZONTAL};
    cout << b3 << endl;

    Battleship b4{Coordinate{9, 4}, Ship::Directions::HORIZONTAL};
    cout << b4 << endl;

    Attackboard ab{};
    Defenseboard db{};

    int b = ab.num_elements();

    db.place_ship(b3);

    cout << b3.armor() << endl;

    db.ship_at(Coordinate{9, 4})->action(Coordinate{9, 4}, db, ab);

    Humanplayer hp;

    cout << Coordinate{4, 12}.to_string();

    //    hp.print_defense_board();
    //    hp.place_ship(Ship::Type::BATTLESHIP);
    //    hp.print_board(Board::Type::DEFENSEBOARD);
    //    hp.place_ship(Ship::Type::BATTLESHIP);
    //    hp.print_board(Board::Type::DEFENSEBOARD);
    //    hp.place_ship(Ship::Type::BATTLESHIP);
    //    hp.print_board(Board::Type::DEFENSEBOARD);

    //    while (true) {
    //        hp.turn(hp);
    //        hp.print_defense_board();
    //    }

    //    Humanplayer hp;

    //    b4.action(Coordinate{9, 4}, db, ab);

    //    int a = ab.num_elements();
    //    string test;
    //    getline(cin, test);
    //    auto i = 54;
    //    b3.hit(Coordinate{9, 4});
    //    cout << b3 << endl;
    //
    ////    b3.hit(Coordinate{11, 4});
    ////    cout << b3 << endl;
    //
    //    b3.hit(Coordinate{9, 6});
    //    cout << b3 << endl;
    //
    //    b3.heal(Coordinate{9, 4});
    //    cout << b3 << endl;

    //    cout << "Battleship b3 positions: ";
    //    auto positions3 = b3.positions();
    //    for (auto p: positions3) {
    //        cout << p.first << "- " << p.second << " ;";
    //    }
    //    cout << endl;

    //    struct minpQElements {
    //        Coordinate c;
    //        char toPrint{' '};
    //        bool isCenter{false};
    //
    //        explicit minpQElements(const Coordinate &c, char toPrint = ' ', bool isCenter = true)
    //                : c(c), toPrint(toPrint), isCenter(isCenter) {}
    //    };
    //
    //    auto lambda = [](minpQElements a, minpQElements b) { return !(a.c < b.c); };
    //    std::priority_queue<minpQElements, std::vector<minpQElements>, decltype(lambda)> pQ(lambda);

    //    for (auto p: positions2) {
    //        if (p == b2.center()) {
    //            pQ.push(minpQElements{p, 'a', true});
    //        } else {
    //            pQ.push(minpQElements{p, 'a', false});
    //        }
    //    }
    //
    //    for (auto p: positions3) {
    //        if (p == b3.center()) {
    //            pQ.push(minpQElements{p, 'b', true});
    //        } else {
    //            pQ.push(minpQElements{p, 'b', false});
    //        }
    //    }
    //
    //    minpQElements el = pQ.top();
    //    for (int i = 1; i <= 12; i++) {
    //        cout << (char) (i < 10 ? '@' + i : '@' + i + 2) << " |";
    //        for (int j = 1; j <= 12; j++) {
    //            if (el.c.equals(i, j)) {
    //                if (el.isCenter) {
    // #if defined(__linux__) || defined(__APPLE__)
    //                    cout << " \033[1;34m" << el.toPrint << "\033[0m |";
    // #else
    //                    SetConsoleTextAttribute(hConsole, 12);
    //                    cout << " " << el.toPrint;
    //                    SetConsoleTextAttribute(hConsole, 7);
    //                    cout << " |";
    // #endif
    //
    //                } else {
    //                    cout << " " << el.toPrint << " |";
    //                }
    //
    //                pQ.pop();
    //                el = pQ.top();
    //            } else {
    //                cout << "   |";
    //            }
    //        }
    //        cout << endl;
    //    }
    //    cout << "-> ";
    //    for (int j = 1; j <= 12; j++) {
    //        if (j < 10) {
    //            cout << "  " << j << " ";
    //        } else {
    //            cout << " " << j << " ";
    //        }
    //    }
    //    cout << endl;
    //
    //    Attackboard board1{};
    //    board1.hit(c7);
    //    board1.hit(c1);
    //    board1.miss(c1);
    //
    //    board1.hit(Coordinate{4, 4});
    //    board1.hit(Coordinate{4, 5});
    //    board1.hit(Coordinate{4, 6});
    //    Defenseboard board2{};
    //    board2.get_all();

    //    int sizeBefore = board1.num_elements();
    //    board1.clear_hits();
    //    int sizeAfter = board1.num_elements();
    //    board1.clear_misses();
    //    int sizeAfterAfter = board1.num_elements();
}

void test_dev_matteo_rampin() {
    cout << "=== dev-matteo-rampin ===" << endl;
    //Cpuplayer cp;
    //Humanplayer hp;
    // hp.place_ship(Ship::Type::BATTLESHIP);
    // hp.print_boards();
    // Coordinate a = Coordinate(1,1);
    // cout<<hp.get_defense_board().is_occupied(a);
    // hp.place_ship(Ship::Type::BATTLESHIP);
    /*cp.place_ship(Ship::Type::BATTLESHIP);
    cp.place_ship(Ship::Type::BATTLESHIP);
    cp.place_ship(Ship::Type::BATTLESHIP);
    cp.print_boards_inline();
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.place_ship(Ship::Type::REPAIRSHIP);
    cp.print_boards_inline();
    cp.place_ship(Ship::Type::SUBMARINE);
    cp.place_ship(Ship::Type::SUBMARINE);
    cp.print_boards_inline();*/
    Humanplayer hp;
    hp.place_ship(Ship::Type::BATTLESHIP);
    hp.place_ship(Ship::Type::REPAIRSHIP);
    hp.place_ship(Ship::Type::BATTLESHIP);
    hp.print_boards_inline();
    Coordinate a1 = Coordinate("A1");
    Coordinate a2 = Coordinate("A2");
    Coordinate a3 = Coordinate("H1");
    hp.get_defense_board().hit(a1);
    hp.get_defense_board().hit(a2);
    hp.get_defense_board().hit(a3);
    hp.print_boards_inline();
    hp.get_defense_board().heal(a1);
    hp.print_boards_inline();
    
    //hp.print_boards_inline();
    
    //cout<<c.at(1).to_string();
    /*
    for (auto i = c.begin(); i != c.end(); i++)
    {
        hp.get_defense_board().heal(*i);
    }*/
    
    //hp.print_boards_inline();

    

}

int manager(int argc, char *argv[]) {
    random_device random_device;
    mt19937 random_engine(random_device());

    bool human_computer_game = false;
    int turn_counter = 0;
    constexpr int MAX_TURNS = 1500;

    uniform_int_distribution<int> starting_player_distribution(0, 1);

    unique_ptr<Player> player1, player2;

    if (argc < 2) {
        throw std::invalid_argument("Insufficient arguments");
    }

    if (std::string{argv[1]} == "-pc" || std::string{argv[1]} == "pc") human_computer_game = true;

    if (!human_computer_game && (std::string{argv[1]} != "-cc" && std::string{argv[1]} != "cc"))
        throw std::invalid_argument("Invalid arguments no pc/-pc or cc/-cc found!");

    const bool a_starts = starting_player_distribution(random_engine) == 0;

    if (human_computer_game) {
        player1.reset(new Humanplayer{});
    } else {
        player1.reset(new Cpuplayer{});
    }
    player2.reset(new Cpuplayer{});

    player1->place_all_ships();
    player2->place_all_ships();

    bool last_a = !a_starts;
    colored_print(a_starts ? "Player 1 starts" : "Player 2 starts", MESSAGE_TYPE::MSG_INFO_BOLD);
    cout << endl;
    while (player1->is_alive() && player2->is_alive() && turn_counter < MAX_TURNS) {
        try {
            if (!last_a) {
//                if (!human_computer_game)
//                    this_thread::sleep_for(chrono::milliseconds(500));
                last_a = true;
                colored_print("Player 1 Turn:", MESSAGE_TYPE::MSG_PLAYER1)
                        << std::endl;
                player1->turn(*player2);
                player1->print_boards_inline();
                cout << "======================================================================" << std::endl;
            } else {
//                this_thread::sleep_for(chrono::milliseconds(500));
                last_a = false;
                colored_print("Player 2 Turn:", MESSAGE_TYPE::MSG_PLAYER1)
                        << std::endl;
                player2->turn(*player1);
                player2->print_boards_inline();
                cout << "======================================================================" << std::endl;
            }

            turn_counter++;
        } catch (const std::exception &e) {
            std::cerr << e.what();
        }
    }

    if (last_a && turn_counter < MAX_TURNS) {
        colored_print("Player 1 WIN!", MESSAGE_TYPE::MSG_INFO_BOLD);
    } else if (turn_counter < MAX_TURNS) {
        colored_print("Player 2 WIN!", MESSAGE_TYPE::MSG_INFO_BOLD);
    } else {
        colored_print("DRAW!", MESSAGE_TYPE::MSG_INFO_BOLD);
    }

    //region save log!
    /**
     * Mandadory cStyle before c++ 17
     */
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    stringstream s(string{});
    s << put_time(&tm, "%Y%m%d_%H%M%S");
    string date_string;
    s >> date_string;

    string file_name = string{"logs/log-"} + (human_computer_game ? "PC" : "CC") + "-" + date_string + string{".txt"};

#if defined(__linux__) || defined(__APPLE__)
    file_name.insert(0, "./");
#else
    file_name.insert(0, "../");
#endif

    ofstream file_out_stream;

//    cout << file_name;
    file_out_stream.open(file_name);

    if (!file_out_stream.is_open()) {
        throw std::invalid_argument{"Can't open output file_in_stream!"};
    }
    std::vector<std::string> player1_history = player1->player_history();
    std::vector<std::string> player2_history = player2->player_history();

    file_out_stream << player1->get_defense_board().to_log_format() << endl;
    file_out_stream << player2->get_defense_board().to_log_format() << endl;

    file_out_stream << (a_starts ? "1" : "2") << endl;

    for (int i = 0; i < (player1_history.size() + player2_history.size()); i++) {
        if (a_starts) {
            if (i % 2 == 0) {
                file_out_stream << player1_history[i / 2] << endl;
            } else {
                file_out_stream << player2_history[i / 2] << endl;
            }
        } else {
            if (i % 2 == 0) {
                file_out_stream << player2_history[i / 2] << endl;
            } else {
                file_out_stream << player1_history[i / 2] << endl;
            }
        }
    }


    file_out_stream.close();
    //endregion

    return 0;
}

int main(int argc, char *argv[]) {
    std::cout << "MAIN" << std::endl;
//    test_dev_matteo_galiazzo();
//    test_dev_filippo_tiberio();
    test_dev_matteo_rampin();
/*
    try {
        manager(argc, argv);
    }
    catch (const exception &ex) {
        cerr << ex.what();
    }
*/
    return 0;
}
