#include <iostream>
#include "RLEParser.h"



RLEPattern RLEParser::parseFile(const string& filename) {
    RLEPattern* pattern;

    ifstream f(filename);
    string line;
    while (getline(f, line)) {
      if (strStartsWith(line, "#C")) {
          // Comment
          cout << "Comment: " << line << endl;
      } else if (strStartsWith(line, "x")) {
          // Pattern size
          const int w = firstNumber(line);
          const int h = lastNumber(line);
          pattern = new RLEPattern(w, h);
          cout << "Size of new pattern: " << w << ", " << h << endl;
      } else if (isdigit(line[0]) || line[0] == 'o' || line[0] == 'b' || line[0] == '$') {
          // Valid pattern line to decode
          // TODO
      }
    }

    return *pattern;
}

bool RLEParser::strStartsWith(const string& s, const string& sub) {
    return s.rfind(sub, 0) == 0;
}

int RLEParser::firstNumber(const string &s) {
    char const* digits = "0123456789";

    size_t const n = s.find_first_of(digits);
    if (n != string::npos) {
        size_t const m = s.find_first_not_of(digits, n);
        return stoi(s.substr(n, m != string::npos ? m-n : m));
    }

    return {};
}

int RLEParser::lastNumber(const string &s) {
    char const* digits = "0123456789";

    size_t const n = s.find_first_of(digits);
    if (n != string::npos) {
        size_t const m = s.find_last_not_of(digits, n);
        return stoi(s.substr(n, m != string::npos ? m-n : m));
    }

    return {};
}
