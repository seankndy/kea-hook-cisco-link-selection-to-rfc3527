#include "utils.h"

const string dotted_quad(vector<uint8_t> bytes) {
    if (bytes.size() == 4) {
        return to_string(bytes[0]) + "." + to_string(bytes[1]) + "." + to_string(bytes[2]) + "." + to_string(bytes[3]);
    }

    return "";
}
