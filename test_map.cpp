#include <iostream>
#include <type_traits>
#include <map>
#include <vector>
#include "edit_distance.h"

template <typename K, typename V>
void print_map(std::map<K, V> v)
{
    std::cout << "{ ";
    for (auto [key, value] : v) {
        std::cout << key << ": " << value << ", ";
    }
    std::cout << "\b\b }";
    std::cout << "\n";
}

int main()
{
    int ham, lev, osa;
    std::map<char, int> a1 { {'a', 1}, {'b', 2}, {'c', 3} };
    std::map<char, int> b1 { {'x', 1}, {'y', 3}, {'z', 4} };
    EditDistance d1(begin(a1), end(a1), begin(b1), end(b1), Cost{},
                    [](auto x, auto y) { return x.second == y.second; });
    ham = d1.hamming();
    lev = d1.lev();
    osa = d1.osa();
    std::cout << "Test Case 1\n";
    std::cout << "maps:\n";
    print_map(a1);
    print_map(b1);
    std::cout << "Map with equality check on the value\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming distance                  : " << ham << "\n";
    std::cout << "levenshtein distance              : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "------------------------------------------------------\n\n";

    return 0;
}
