#include <iostream>
#include <ranges>

#include "utils.h"

namespace rg = std::ranges;
namespace vw = std::views;

constexpr auto width = 101;
constexpr auto height = 103;

struct robot {
    int x;
    int y;
    int dx;
    int dy;
};

void debug(const std::vector<robot> &robots) {
    // Create a 2D grid for counting robots at each position
    std::vector grid(height, std::vector(width, 0));

    // Count robots at each position
    for (const auto &robot: robots) {
        grid[robot.y][robot.x]++;
    }

    // Print the grid
    for (const auto &row: grid) {
        for (const auto &cell: row) {
            if (cell == 0) {
                std::cout << '.';
            } else {
                std::cout << cell;
            }
        }
        std::cout << '\n';
    }
}

inline auto tick(std::vector<robot>& robots) {
    for (auto &[x, y, dx, dy]: robots) {
        x = x + dx;
        x = x % width;
        if (x < 0) x = width + x;
        x = x % width;

        y = y + dy;
        y = y % height;
        if (y < 0) y = height + y;
        y = y % height;
    }
}

int main() {
    const auto lines = read_file_lines("14_1.txt");

    // parse a line into a robot struct
    auto parse = [](const std::string &s) {
        std::istringstream ss(s);
        char ignore;
        int x, y, dx, dy;

        ss >> ignore >> ignore >> x >> ignore >> y;
        ss >> ignore >> ignore >> dx >> ignore >> dy;

        return robot{x, y, dx, dy};
    };

    const auto robots = lines
                  | vw::transform(parse)
                  | rg::to<std::vector>();
    auto robots_part_1 = robots;
    for (auto i = 0; i < 100; i++) {
        tick(robots_part_1);
    }

    constexpr int horizontal_mid = width / 2;
    constexpr int vertical_mid = height / 2;
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (const auto &robot: robots_part_1) {
        if (robot.x < horizontal_mid && robot.y < vertical_mid) {
            q1++;
        } else if (robot.x > horizontal_mid && robot.y < vertical_mid) {
            q2++;
        } else if (robot.x < horizontal_mid && robot.y > vertical_mid) {
            q3++;
        } else if (robot.x > horizontal_mid && robot.y > vertical_mid) {
            q4++;
        }
    }

    std::cout << "part 1: " << q1 * q2 * q3 * q4 << std::endl;


}
