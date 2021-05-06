#include <iostream>
#include <vector>
#include "edit_distance.h"

template <typename T>
struct modulo_equal
{
    int val;
    modulo_equal(int v): val(v) {}
    bool operator() (T a, T b) const { return a % val == b % val; }
};

template <typename T>
void print_vector(std::vector<T> v)
{
    std::cout << "[";
    for (T item: v) {
        std::cout << item << " ";
    }
    std::cout << "\b]";
    std::cout << "\n";
}

int main()
{
    int ham, lev, osa;
    std::vector a1 {10, 11, 12, 13, 14, 15};
    std::vector b1 {10, 12, 22, 14, 13, 15};
    EditDistance d1(begin(a1), end(a1), begin(b1), end(b1),
                    Cost{}, modulo_equal<int>(10));
    ham = d1.hamming();
    lev = d1.lev();
    osa = d1.osa();
    std::cout << "Test Case 1\n";
    std::cout << "vectors:\n";
    print_vector(a1);
    print_vector(b1);
    std::cout << "Vector with modulo 10 equality\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming distance                  : " << ham << "\n";
    std::cout << "levenshtein distance              : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "------------------------------------------------------\n\n";

    return 0;
}
