#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <ranges>
#include <vector>
#include "utils.h"

int main() {
    const auto data = read_file_split_by_spaces("1_1.txt", to_int);
    auto left = data | std::views::transform(nth(0)) | std::ranges::to<std::vector>();
    auto right = data | std::views::transform(nth(1)) | std::ranges::to<std::vector>();

    std::ranges::sort(left);
    std::ranges::sort(right);

    std::unordered_map<int, int> right_map;
    for (const auto& elem : right) {
        ++right_map[elem];
    }

    auto distance_sum = 0UL, similarity_sum = 0UL;
    for (const auto& [l, r] : std::views::zip(left, right)) {
        distance_sum += std::abs(l - r);
        similarity_sum += l * right_map[l];
    }

    std::cout << "distance: " << distance_sum << '\n' << "similarity: " << similarity_sum << '\n';
}
