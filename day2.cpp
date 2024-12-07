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
using std::views::drop;

#include "utils.h"

int main() {
    const auto data = read_file_split_by_spaces("2_1.txt");
    auto valid = 0;
    for (const auto &row_raw: data) {
        const auto row = row_raw | transform(to_int) | to<vector<int>>();
        const auto decreasing = row[0] > row[1];
        bool inc_or_dec = true, max_diff_valid = true;
        for (const auto& [prev, next]: zip(row, row | drop(1))) {
            inc_or_dec = inc_or_dec && decreasing ? prev > next : prev < next;
            max_diff_valid = max_diff_valid && abs(prev - next) < 4;
        }
        valid += inc_or_dec && max_diff_valid;
    }
    cout << "day 1 valid reports: " << valid << endl;
}
