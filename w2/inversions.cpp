#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>

// Implement a recursive inversions count algo.

std::vector<int> readInput() {
    std::vector<int> result;

    std::ifstream f("input.txt");
    for (std::string line; std::getline(f, line);) {
        result.emplace_back(std::stoi(line));
    }

    return result;
}

std::pair<std::vector<int>, uint> sortAndCountSplitInversions(std::vector<int> lhs, std::vector<int> rhs) {
    if (lhs.empty()) {
        std::sort(rhs.begin(), rhs.end());
        return {rhs, 0};
    }

    if (rhs.empty()) {
        std::sort(lhs.begin(), lhs.end());
        return {lhs, 0};
    }

    uint rr = 0;
    std::vector<int> result;
    auto lhs_it = lhs.begin();
    auto rhs_it = rhs.begin();
    while (!(lhs_it == lhs.end() && rhs_it == rhs.end())) {
        if (lhs_it == lhs.end()) { 
            result.emplace_back(*rhs_it);
            ++rhs_it;
            continue;
        }

        if (rhs_it == rhs.end()) {
            result.emplace_back(*lhs_it);
            ++lhs_it;
            continue;
        }

        if (*lhs_it <= *rhs_it) {
            result.emplace_back(*lhs_it);
            ++lhs_it;
        } else {
            result.emplace_back(*rhs_it);
            ++rhs_it;
            rr += std::distance(lhs_it, lhs.end());
        }
    }

    return {result, rr};
}

uint bruteInversions(std::vector<int> s) {
    uint result = 0;
    for (auto i = 0; i < s.size(); ++i) {
        for (auto j = i + 1; j < s.size(); ++j) {
            if (s[i] > s[j]) {
                ++result;
            }
        }
    }

    return result;
}

std::pair<std::vector<int>, uint> sortAndCount(std::vector<int> s) {
    if (s.size() < 2) {
        return {s, 0};
    }

    if (s.size() == 3) {
        const auto result = bruteInversions(s);
        std::sort(s.begin(), s.end());
        return {s, result};
    }

    const auto [lhs, a] = sortAndCount(std::vector<int>(s.begin(), s.begin() + s.size() / 2));
    const auto [rhs, b] = sortAndCount(std::vector<int>(s.begin() + s.size() / 2, s.end()));
    const auto [ss, c] = sortAndCountSplitInversions(lhs, rhs);
    return {ss, a + b + c};
}

uint countInversions(std::vector<int> s) {
    const auto [_, result] = sortAndCount(s);
    return result;
}
