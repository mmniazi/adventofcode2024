#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

std::vector<std::vector<std::string>> read_file_split_by_spaces(const std::string &filename);
inline auto to_int = [](const std::string& s) { return std::stoi(s); };

#endif //UTILS_H
