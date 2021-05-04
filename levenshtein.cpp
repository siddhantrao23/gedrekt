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
struct TranspositionCost { int t; TranspositionCost(int temp = 1): t(temp){}; };

struct Cost
{
    InsertionCost ic;
    DeletionCost dc;
    SubstitutionCost sc;
    TranspositionCost tc;
    Cost():ic(1), dc(1), sc(1), tc(1) {}
    Cost(InsertionCost i, DeletionCost d, SubstitutionCost s):ic(i), dc(d), sc(s) {}
    Cost(InsertionCost i, DeletionCost d, SubstitutionCost s, TranspositionCost t):ic(i), dc(d), sc(s), tc(t) {}
};

template<typename ptr_t, typename pred_t = std::equal_to<typename ptr_t::value_type>>
class EditDistance
{
public:
    EditDistance(const ptr_t begin1, const ptr_t end1,
                 const ptr_t begin2, const ptr_t end2,
                 const Cost cost = Cost(),
                 const pred_t equals = pred_t()):
        _begin1(begin1), _end1(end1),
        _begin2(begin2), _end2(end2),
        _cost(cost), _equals(equals)
        {
            _size1 = std::distance(_begin1, _end1);
            _size2 = std::distance(_begin2, _end2);
        }
    int lev();
    int osa();
private:
    int _size1;
    int _size2;
    ptr_t _begin1;
    ptr_t _end1;
    ptr_t _begin2;
    ptr_t _end2;
    Cost _cost;
    pred_t _equals;
};

template<typename ptr_t, typename pred_t>
int EditDistance<ptr_t, pred_t>::lev()
{
    int deletion_cost, insertion_cost, substitution_cost;

    // gets sizes of the collection
    // NOTE: Should we tradeoff memory for number of iterations?
    std::vector<int> prev(_size2 + 1);
    std::vector<int> curr(_size2 + 1);

    for (int i = 0; i < _size2 + 1; i++) {
        prev[i] = i * _cost.ic.i;
    }

    ptr_t b1 = _begin1;
    for (int i = 0; i < _size1; i++) {
        curr[0] = (i + 1) * _cost.dc.d;
        ptr_t b2 = _begin2;
        for (int j = 0; j < _size2; j++) {
            insertion_cost = curr[j] + _cost.ic.i;
            deletion_cost = prev[j + 1] + _cost.dc.d;
            if (_equals(*b1, *b2)) {
                substitution_cost = prev[j];
            } else {
                substitution_cost = prev[j] + _cost.sc.s;
            }
            curr[j+1] = std::min({deletion_cost, insertion_cost, substitution_cost});
            b2++;
        }
        b1++;

        // Swapping instead of copying, because move semantics are more efficient
        curr.swap(prev);
    }
    return prev[_size2];
}

template<typename ptr_t, typename pred_t>
int EditDistance<ptr_t, pred_t>::osa()
{
    int deletion_cost, insertion_cost, substitution_cost, transposition_cost;
    std::vector<int> prevprev(_size2 + 1);
    std::vector<int> prev(_size2 + 1);
    std::vector<int> curr(_size2 + 1);

    for (int i = 0; i < _size1 + 1; i++) {
        prev[i] = i * _cost.ic.i;
    }

    ptr_t b1 = _begin1;
    for (int i = 0; i < _size1; i++) {
        curr[0] = (i + 1) * _cost.dc.d;
        ptr_t b2 = _begin2;
        for (int j = 0; j < _size2; j++) {
            insertion_cost = curr[j] + _cost.ic.i;
            deletion_cost = prev[j+1] + _cost.dc.d;
            if (_equals(*b1, *b2)) {
                substitution_cost = prev[j];
            } else {
                substitution_cost = prev[j] + _cost.sc.s;
            }
            curr[j+1] = std::min({insertion_cost, deletion_cost, substitution_cost});
            if (i > 0 && j > 0) {
                bool left_diagonal_is_same = *b1 == *--b2;
                bool right_diagonal_is_same = *--b1 == *++b2;
                ++b1;
                bool is_transposed = left_diagonal_is_same && right_diagonal_is_same;
                if (is_transposed) {
                    transposition_cost = prevprev[j-1] + _cost.tc.t;
                    curr[j+1] = std::min({curr[j+1], transposition_cost});
                }
            }
            b2++;
        }
        b1++;
        prevprev.swap(prev);
        prev.swap(curr);
    }
    return prev[_size2];
}

int main() {
    std::string a1 = "car";
    std::string b1 = "cat";
    EditDistance d1(begin(a1), end(a1), begin(b1), end(b1), Cost{}, [](auto x, auto y) { return x == y; });
    int res1 = d1.lev();
    std::cout << "res1 : " << res1 << "\n";

    std::string a2 = "car";
    std::string b2 = "cra";

    EditDistance d2(begin(a2), end(a2), begin(b2), end(b2), Cost{}, [](auto x, auto y) { return x == y; });
    int res42 = d2.osa();
    std::cout << "res42 : " << res42 << "\n";

    std::vector<int> v1{10, 20, 30, 40, 50};
    std::vector<int> v2{10, 22, 30, 40, 50};
    Cost c1{InsertionCost(2),DeletionCost(2),SubstitutionCost(2)};
    EditDistance d3(begin(v1), end(v1), begin(v2), end(v2), c1);
    int res2 = d3.lev();
    std::cout << "res2a : " << res2 << "\n";

    std::vector<int> v3{10, 20, 30, 40, 50};
    std::vector<int> v4{10, 22, 40, 30, 50};
    Cost c2(InsertionCost(1),DeletionCost(1),SubstitutionCost(1));
    EditDistance d4(begin(v3), end(v3), begin(v4), end(v4), c2);
    int res43 = d4.osa();
    std::cout << "res43 : " << res43 << "\n";

    int a[] = {1, 2, 3, 4};
    int b[] = {1, 1, 2, 3};
    std::deque<int> dq1(a, a + 4);
    std::deque<int> dq2(b, b + 4);
    EditDistance d5(begin(dq1), end(dq1), begin(dq2), end(dq2));
    int res3 = d5.lev();
    std::cout << "res3 : " << res3 << "\n";

    // doesnt work for lists again wot
    std::list<std::pair<int, int>> l1{{0,1}, {1,0}, {3,4}};
    std::list<std::pair<int, int>> l2{{1,1}, {1,0}, {3,5}};
    EditDistance d6(begin(l1), end(l1), begin(l2), end(l2));
    int res4 = d6.lev();
    std::cout << "res4 : " << res4 << "\n";

    return 0;
}
