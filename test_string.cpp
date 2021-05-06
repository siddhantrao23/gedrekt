#include <iostream>
#include <string>
#include "edit_distance.h"

int main()
{
    int ham, lev, osa;
    std::string a1 = "car";
    std::string b1 = "cat";
    EditDistance d1(begin(a1), end(a1), begin(b1), end(b1),
                    Cost{}, [](auto x, auto y) { return x == y; });
    ham = d1.hamming();
    lev = d1.lev();
    osa = d1.osa();
    std::cout << "Test Case 1\n";
    std::cout << "strings:\n" << a1 << "\n" << b1 << "\n";
    std::cout << "String with default cost and explicit lambda predicate\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming distance                  : " << ham << "\n";
    std::cout << "levenshtein distance              : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "------------------------------------------------------\n\n";

    std::string a2 = "abcdefg";
    std::string b2 = "acbdf";
    EditDistance d2(begin(a2), end(a2), begin(b2), end(b2),
                    Cost(InsertionCost(1), DeletionCost(3), SubstitutionCost(1)));
    ham = d2.hamming();
    lev = d2.lev();
    osa = d2.osa();
    std::cout << "Test Case 2\n";
    std::cout << "strings:\n" << a2 << "\n" << b2 << "\n";
    std::cout << "String of different lengths;\n";
    std::cout << "Deletion cost = 3, rest are 1\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming                           : " << ham << " (N/A)" << "\n";
    std::cout << "levenshtein                       : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "------------------------------------------------------\n";

    return 0;
}
