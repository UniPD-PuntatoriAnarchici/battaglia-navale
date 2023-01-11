#include <iostream>
#include <queue>

#include "./../include/board/attackboard.h"
#include "./../include/board/defenseboard.h"
#include "./../include/player/humanplayer.h"
#include "./../include/player/cpuplayer.h"


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
    hp.turn(hp2);
    hp.turn(hp2);
}

void test_dev_filippo_tiberio() {
#if defined(__linux__) || defined(__APPLE__)

#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

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

void test_dev_matteo_rampin() { cout << "=== dev-matteo-rampin ===" << endl;
Cpuplayer cp;
    Humanplayer hp;
    //hp.place_ship(Ship::Type::BATTLESHIP);
   //hp.print_boards();
    //hp.place_ship(Ship::Type::BATTLESHIP);
    cp.place_ship(Ship::Type::BATTLESHIP);
    //cp.place_ship(Ship::Type::BATTLESHIP);
    // cp.place_ship(Ship::Type::BATTLESHIP);
    cp.print_boards(); }

int main() {
    std::cout << "MAIN" << std::endl;
//    test_dev_matteo_galiazzo();
//     test_dev_filippo_tiberio();
    return 0;
}
