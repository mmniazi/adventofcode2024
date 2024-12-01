#include "utils.h"
#include <fstream>
#include <iterator>

std::vector<std::string> read_file_split_by_spaces(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file: " + filename);
    }

    return {
        std::istream_iterator<std::string>(file),
        std::istream_iterator<std::string>()
    };
}
