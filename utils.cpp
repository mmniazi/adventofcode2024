#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iterator>

namespace fs = std::filesystem;

std::vector<std::vector<std::string> > read_file_split_by_spaces(const std::string &filename) {
    std::vector<std::vector<std::string> > result;
    std::ifstream file(fs::path(PROJECT_ROOT_DIR) / "inputs" / filename);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> words{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };
        result.emplace_back(std::move(words));
    }

    return result;
}
