#include <iostream>
#include <vector>
#include <ranges>
#include "utils.h"

int main() {
    const auto data = read_file_split_by_spaces("2_1.txt", to_int);
    auto day_1_valid = 0;
    for (const auto &row: data) {
        const auto decreasing = row[0] > row[1];
        bool valid = true;
        for (const auto &[prev, next]: std::views::zip(row, row | std::views::drop(1))) {
            if ((decreasing ? next >= prev : next <= prev) || std::abs(prev - next) > 3) {
                valid = false;
            }
        }
        day_1_valid += valid;
    }
    std::cout << "day 1 valid reports: " << day_1_valid << std::endl;

    auto day_2_valid = 0;
    for (const auto &row: data) {
        const auto decreasing = row[0] > row[1];
        auto level_to_skip = -1;
        auto valid = true;
        for (int curr = 0, next = 1; next < row.size();) {
            if (curr == level_to_skip) ++curr;
            else if (next == level_to_skip) ++next;
            if ((decreasing ? row[next] >= row[curr] : row[next] <= row[curr]) || std::abs(row[curr] - row[next]) > 3) {
                if (level_to_skip == -1) {
                    level_to_skip = next;
                    continue;
                }
                valid = false;
            }
            ++curr, ++next;
        }
        day_2_valid += valid;
    }
    std::cout << "day 2 valid reports: " << day_2_valid << std::endl;
}
