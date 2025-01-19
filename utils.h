#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

// Namespace alias for convenience
namespace fs = std::filesystem;

// Template function to read and convert file contents
template<typename Converter>
auto read_file_split_by_spaces(const std::string &filename, Converter converter) {
    using T = decltype(converter(std::string{}));
    fs::path filepath = fs::path(PROJECT_ROOT_DIR) / "inputs" / filename;
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Error opening file: " << filepath << '\n';
        return std::vector<std::vector<T>>{};
    }

    std::vector<std::vector<T>> result;
    std::string line, word;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<T> converted;
        while (iss >> word)
            converted.emplace_back(converter(word));
        result.emplace_back(std::move(converted));
    }
    return result;
}

inline auto read_file_lines(const std::string &filename) -> std::vector<std::string> {
    std::ifstream file(fs::path(PROJECT_ROOT_DIR) / "inputs" / filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Inline conversion lambdas
inline auto to_int = [](const std::string& s) { return std::stoi(s); };
inline auto nth(size_t n) {
    return [n](const auto& container) -> decltype(auto) {
        return container[n];
    };
}

#endif //UTILS_H
