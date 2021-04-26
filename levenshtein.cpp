#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <string>
#include <deque>
#include <list>

struct InsertionCost { int i; InsertionCost(int temp = 1): i(temp){}; };
struct DeletionCost { int d; DeletionCost(int temp = 1): d(temp){}; };
struct SubstitutionCost { int s; SubstitutionCost(int temp = 1): s(temp){}; };

struct Cost
{
    InsertionCost ic;
    DeletionCost dc;
    SubstitutionCost sc;
    Cost():ic(1), dc(1), sc(1) {}
    Cost(InsertionCost i, DeletionCost d, SubstitutionCost s ):ic(i), dc(d), sc(s) {}
};

template<typename ptr_t, typename eq_pred_t = std::equal_to<typename ptr_t::value_type>>
int levenshtein(const ptr_t begin1, const ptr_t end1,
                const ptr_t begin2, const ptr_t end2,
                const Cost cost = Cost(),
                const eq_pred_t equals = eq_pred_t())
{
    int deletion_cost, insertion_cost, substitution_cost;

    // gets sizes of the collection
    // NOTE: Should we tradeoff memory for number of iterations?
    int size1 = std::distance(begin1, end1);
    int size2 = std::distance(begin2, end2);

    std::vector<int> prev(size2 + 1);
    std::vector<int> curr(size2 + 1);

    for (int i = 0; i < size2 + 1; i++) {
        prev[i] = i;
    }

    ptr_t b1 = begin1;
    for (int i = 0; i < size1; i++) {
        curr[0] = i + 1;
        ptr_t b2 = begin2;
        for (int j = 0; j < size2; j++) {
            deletion_cost = prev[j + 1] + cost.dc.d;
            insertion_cost = curr[j] + cost.ic.i;
            if (equals(*b1, *b2)) {
                substitution_cost = prev[j];
            } else {
                substitution_cost = prev[j] + cost.sc.s;
            }
            curr[j+1] = std::min({deletion_cost, insertion_cost, substitution_cost});
            b2++;
        }
        b1++;

        // Swapping instead of copying, because move semantics are more efficient
        curr.swap(prev);
    }
    return prev[size2];
}

int main() {
    std::string a1 = "car";
    std::string b1 = "cat";
    int res1 = levenshtein(begin(a1), end(a1), begin(b1), end(b1), Cost{}, [](auto x, auto y) { return x == y; });
    std::cout << "res1 : " << res1 << "\n";

    std::vector<int> v1{10, 20, 30, 40, 50};
    std::vector<int> v2{10, 22, 30, 40, 50};
    Cost c1{InsertionCost(2),DeletionCost(2),SubstitutionCost(2)};
    Cost c2(InsertionCost(2),DeletionCost(2),SubstitutionCost(2));
    auto res2 = levenshtein(begin(v1), end(v1), begin(v2), end(v2), c1);
    std::cout << "res2a : " << res2 << "\n";
    res2 = levenshtein(begin(v1), end(v1), begin(v2), end(v2), c2);
    std::cout << "res2b : " << res2 << "\n";

    int a[] = {1, 2, 3, 4};
    int b[] = {1, 1, 2, 3};
    std::deque<int> d1(a, a + 4);
    std::deque<int> d2(b, b + 4);
    auto res3 = levenshtein(begin(d1), end(d1), begin(d2), end(d2));
    std::cout << "res3 : " << res3 << "\n";

    std::list<std::pair<int, int>> l1{{0,1}, {1,0}, {3,4}};
    std::list<std::pair<int, int>> l2{{1,1}, {1,0}, {3,5}};
    auto res4 = levenshtein(begin(l1), end(l1), begin(l2), end(l2));
    std::cout << "res4 : " << res4 << "\n";

    return 0;
}
