#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "utils.h"

int main() {
    const auto strings = read_file_split_by_spaces("./inputs/1_1.txt");
    const size_t size = strings.size() / 2;
    std::vector<int> right(size), left(size);

    for (int i = 0; i < size; ++i) {
        left[i] = std::stoi(strings[i * 2]);
        right[i] = std::stoi(strings[i * 2 + 1]);
    }

    std::ranges::sort(left);
    std::ranges::sort(right);

    unsigned long distance_sum = 0;
    for (int i = 0; i < size; ++i) {
        distance_sum += std::abs(left[i] - right[i]);
    }

    std::cout << "distance: " << distance_sum << std::endl;

    std::unordered_map<int, int> right_map(size);
    for (auto elem: right) {
        ++right_map[elem];
    }

    unsigned long similarity_sum = 0;
    for (auto num: left) {
        if (right_map.contains(num)) {
            similarity_sum += num * right_map[num];
        }
    }

    std::cout << "similarity: " << similarity_sum << std::endl;
}
