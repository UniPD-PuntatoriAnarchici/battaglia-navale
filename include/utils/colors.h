/**
 * @author Rampin Matteo
 */

#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
#define BLACKONWHITE "\033[30;47m"
#define BLACKONYELLOW "\033[30;43m"

enum class MESSAGE_TYPE {
    MSG_WARNING,
    MSG_ERROR,
    MSG_INFO,
    MSG_INFO_BOLD,
    MSG_SUCCESS,
    MSG_PLAYER1,
    MSG_PLAYER2
};

/*
    from https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
    from https://en.wikipedia.org/wiki/ANSI_escape_code#Colors

            foreground background
    black        30         40
    red          31         41
    green        32         42
    yellow       33         43
    blue         34         44
    magenta      35         45
    cyan         36         46
    white        37         47

    reset             0  (everything back to normal)
    bold/bright       1  (often a brighter shade of the same colour)
    underline         4
    inverse           7  (swap foreground and background colours)
    bold/bright off  21
    underline off    24
    inverse off      27
*/
static std::ostream &colored_print(const std::string &str, MESSAGE_TYPE message_type,
                                   std::ostream &os = std::cout) {
#if defined(__linux__) || defined(__APPLE__)
    if (os.rdbuf() != std::cout.rdbuf() && os.rdbuf() != std::cerr.rdbuf()) {
        os << str;
    } else if (message_type == MESSAGE_TYPE::MSG_INFO_BOLD)
        os << BOLDBLUE << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_INFO)
        os << BLUE << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_WARNING)
        os << YELLOW << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_ERROR)
        os << RED << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_SUCCESS)
        os << GREEN << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_PLAYER1)
        os << BLACKONWHITE << str << RESET;
    else if (message_type == MESSAGE_TYPE::MSG_PLAYER2)
        os << BLACKONYELLOW << str << RESET;
    return os;
#else
    os << str;
    return os;  // credo
#endif
}

#endif