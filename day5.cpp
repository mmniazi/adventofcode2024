#include <iostream>
#include "utils.h"
#include <unordered_set>
#include <unordered_map>
#include <charconv>

std::vector<int> split(const std::string &str, const char delimiter) {
    std::vector<int> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        int x;
        std::from_chars(token.data(), token.data() + token.size(), x);
        result.push_back(x);
    }
    return result;
}

std::optional<std::pair<int, int> > find_invalid_pair(const std::vector<int> &page_order,
                                                      const std::unordered_map<int, std::unordered_set<int> > &rules) {
    for (size_t i = 0; i < page_order.size(); ++i) {
        if (auto it = rules.find(page_order[i]); it != rules.end()) {
            for (size_t j = 0; j < i; ++j) {
                if (it->second.contains(page_order[j])) {
                    return std::make_pair(j, i);
                }
            }
        }
    }
    return std::nullopt;
}

void part1(const std::unordered_map<int, std::unordered_set<int> > &rules,
           const std::vector<std::vector<int> > &page_orders) {
    int result = 0;
    for (const auto &page_order: page_orders) {
        if (!find_invalid_pair(page_order, rules)) {
            result += page_order[page_order.size() / 2];
        }
    }

    std::cout << result << '\n';
}

void part2(const std::unordered_map<int, std::unordered_set<int> > &rules,
           const std::vector<std::vector<int> > &page_orders) {
    int result = 0;
    for (const auto &page_order: page_orders) {
        bool was_invalid = false;
        auto fixed_page_order = page_order;
        while (auto to_swap = find_invalid_pair(fixed_page_order, rules)) {
            was_invalid = true;
            auto [i, j] = *to_swap;
            std::swap(fixed_page_order[i], fixed_page_order[j]);
        }
        if (was_invalid) {
            result += fixed_page_order[page_order.size() / 2];
        }
    }

    std::cout << result << '\n';
}

int main() {
    const auto lines = read_file_lines(INPUT_FILE);

    std::unordered_map<int, std::unordered_set<int> > rules;
    std::vector<std::vector<int> > page_orders = {};
    bool parsing_rules = true;
    for (const auto &line: lines) {
        if (line.empty()) {
            parsing_rules = false;
            continue;
        }
        if (parsing_rules) {
            std::istringstream ss(line);
            char ignore;
            int before, after;

            ss >> before >> ignore >> after;
            rules[before].insert(after);
        } else {
            page_orders.push_back(split(line, ','));
        }
    }

    part1(rules, page_orders);
    part2(rules, page_orders);
}
