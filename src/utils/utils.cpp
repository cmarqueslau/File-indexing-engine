#include "utils.hpp"

string Utils::trim(const string& s) {
    auto p = s.find_first_not_of(" \t\n\r");
    if (p == string::npos) return "";
    auto q = s.find_last_not_of(" \t\n\r");
    return s.substr(p, q - p + 1);
}