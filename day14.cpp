#include <iostream>
#include <ranges>
#include <fstream>
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

auto to_grid(const std::vector<robot> &robots) {
    auto grid = std::vector(height, std::vector(width, 0));

    // Count robots at each position
    for (const auto &robot: robots) {
        grid[robot.y][robot.x]++;
    }

    return grid;
}

void debug(const std::vector<robot> &robots) {
    // print the grid
    for (const auto &row: to_grid(robots)) {
        for (const auto &cell: row) {
            if (cell == 0) {
                std::cout << '.';
            } else {
                std::cout << '*';
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;
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

bool has_horizontal_line(const std::vector<robot>& robots) {
    const auto grid = to_grid(robots);
    for (const auto robot: robots) {
        int neg_offset = -1;
        while (robot.x + neg_offset > 0 && grid[robot.y][robot.x + neg_offset] > 0) {
            neg_offset--;
        }
        int pos_offset = 1;
        while (robot.x + pos_offset < width && grid[robot.y][robot.x + pos_offset] > 0) {
            pos_offset++;
        }

        if (pos_offset - neg_offset - 1 >= 8) {
            return true;
        }
    }
    return false;
}

void part1(const std::vector<robot> &robots) {
    auto robots_mut = robots;
    for (auto i = 0; i < 100; i++) {
        tick(robots_mut);
    }

    constexpr int horizontal_mid = width / 2;
    constexpr int vertical_mid = height / 2;
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (const auto &robot: robots_mut) {
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

void part2(const std::vector<robot> &robots) {
    auto robots_mut = robots;
    for (auto i = 0; i < height * width; i++) {
        if (has_horizontal_line(robots_mut)) {
            debug(robots_mut);
            std::cout << "iteration: " << i << std::endl;
        }
        tick(robots_mut);
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
    part1(robots);
    part2(robots);
}
