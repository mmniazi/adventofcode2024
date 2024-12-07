#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <ranges>
#include <vector>

using std::views::transform;
using std::vector;
using std::stoi;
using std::ranges::sort;
using std::abs;
using std::unordered_map;
using std::cout;
using std::endl;
using std::ranges::to;
using std::views::zip;

#include "utils.h"

int main() {
    const auto data = read_file_split_by_spaces("1_1.txt");
    auto left = data | transform([](const auto& v) { return stoi(v[0]); }) | to<vector>();
    auto right = data | transform([](const auto& v) { return stoi(v[1]); }) | to<vector>();
    const auto size = left.size();

    sort(left);
    sort(right);

    unordered_map<int, int> right_map(size);
    for (auto elem: right) {
        ++right_map[elem];
    }

    auto distance_sum = 0UL;
    auto similarity_sum = 0UL;
    for (const auto& [l, r] : zip(left, right)) {
        distance_sum += abs(l - r);
        similarity_sum += l * right_map[l];
    }

    cout << "distance: " << distance_sum << endl;
    cout << "similarity: " << similarity_sum << endl;
}
