#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <regex>

using namespace std;

bool rightFormat(const string& cmd) {
    if (cmd.length() != 4) return false;
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]"); // regex for a valid move (e.g., e2e4)
        return regex_match(cmd,mouvmtpattern);
    
    }
    
    bool rightFormatCastling(const string& cmd) {
        if (cmd.length() != 3 && cmd.length() != 5) return false;
        regex pattern("^(O|o|0)-(O|o|0)(-(O|o|0))?$"); // regex for castling (e.g., O-O or O-O-O)
        return regex_match(cmd, pattern);
    }
    
#endif // UTILS_HPP