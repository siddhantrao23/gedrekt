#include <iostream>
#include <set>
#include <string>
#include "edit_distance.h"

template <typename T>
void print_collection(T v)
{
    std::cout << "[";
    for (auto item: v) {
        std::cout << item << " ";
    }
    std::cout << "\b]";
}

int main()
{
    int ham, lev, osa;
    std::string a1 = "hit";
    std::string b1 = "cog";
    EditDistance d1(begin(a1), end(a1), begin(b1), end(b1),
                    Cost{}, [](auto x, auto y) { return x == y; });
    ham = d1.hamming();
    lev = d1.lev();
    osa = d1.osa();
    std::set<char> alphabet;
    for (char a = 'a'; a <= 'z'; a++) {
         alphabet.insert(a);
    }
    std::set<std::string> dict{{"hit", "cog", "hot", "dog", "log", "dot", "lot"}};
    auto words = d1.readersdigest<std::string>(a1, b1, dict, alphabet);
    std::cout << "Test Case 1\n";
    std::cout << "strings:\n" << a1 << "\n" << b1 << "\n";
    std::cout << "String with default cost and explicit lambda predicate\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming distance                  : " << ham << "\n";
    std::cout << "levenshtein distance              : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "word substitutions for dictionary: ";
    print_collection(dict);
    std::cout << "\nPossible shortest paths:\n";
    for (auto x: words.first) {
         std::cout << "\t\t";
         for (auto word: x) {
              std::cout << word << " ";
         }
         std::cout << "(cost: " << words.second << ")\n";
    }
    std::cout << "------------------------------------------------------\n\n";

    std::vector<int> a2 {5, 2};
    std::vector<int> b2 {9, 1};
    std::set<std::vector<int>> dict2{ {5, 2}, {9, 1}, {7, 2}, {8, 1}, {7, 1}, {6, 2}, {6, 1} };
    std::set<int> digits {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EditDistance d2(begin(a2), end(a2), begin(b2), end(b2),
                    Cost(InsertionCost(1), DeletionCost(3), SubstitutionCost(1)));
    ham = d2.hamming();
    lev = d2.lev();
    osa = d2.osa();
    auto intseq = d2.readersdigest<std::vector<int>>(a2, b2, dict2, digits);
    std::cout << "\nTest Case 2\n";
    std::cout << "Vectors\n";
    print_collection(a2);
    std::cout << "\n";
    print_collection(b2);
    std::cout << "\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming                           : " << ham << "\n";
    std::cout << "levenshtein                       : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "word substitutions for dictionary: ";
    std::cout << "{ ";
    for (auto d: dict2) {
         print_collection(d);
         std::cout << " ";
    }
    std::cout << "}";
    std::cout << "\nPossible shortest paths:\n";
    for (auto x: intseq.first) {
         for (auto vec: x) {
              std::cout << "\t";
              print_collection(vec);
              std::cout << " ";
         }
         std::cout << "(cost: " << intseq.second << ")\n";
    }
    std::cout << "------------------------------------------------------\n";

    return 0;
}
