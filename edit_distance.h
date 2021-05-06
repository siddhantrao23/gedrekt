#include <vector>
#include <iterator>
#include <functional>

#ifndef __EDIT_DISTANCE_H_
#define __EDIT_DISTANCE_H_

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

template <typename ptr1, typename ptr2, typename pred_t = std::equal_to<typename ptr1::value_type>>
class EditDistance
{
public:
    EditDistance(const ptr1 begin1, const ptr1 end1,
                 const ptr2 begin2, const ptr2 end2,
                 const Cost cost = Cost(),
                 const pred_t equals = pred_t()):
        _begin1(begin1), _end1(end1),
        _begin2(begin2), _end2(end2),
        _cost(cost), _equals(equals)
        {
            _size1 = std::distance(_begin1, _end1);
            _size2 = std::distance(_begin2, _end2);
        }
    int lev() const;
    int osa() const;
    int hamming() const;
private:
    int _size1;
    int _size2;
    ptr1 _begin1;
    ptr1 _end1;
    ptr2 _begin2;
    ptr2 _end2;
    Cost _cost;
    pred_t _equals;
};

template <typename ptr1, typename ptr2, typename pred_t>
int EditDistance<ptr1, ptr2, pred_t>::lev() const
{
    int deletion_cost, insertion_cost, substitution_cost;

    // gets sizes of the collection
    // NOTE: Should we tradeoff memory for number of iterations?
    std::vector<int> prev(_size2 + 1);
    std::vector<int> curr(_size2 + 1);

    for (int i = 0; i < _size2 + 1; i++) {
        prev[i] = i * _cost.ic.i;
    }

    auto b1 = _begin1;
    for (int i = 0; i < _size1; i++) {
        curr[0] = (i + 1) * _cost.dc.d;
        auto b2 = _begin2;
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

template <typename ptr1, typename ptr2, typename pred_t>
int EditDistance<ptr1, ptr2, pred_t>::osa() const
{
    int deletion_cost, insertion_cost, substitution_cost, transposition_cost;
    std::vector<int> prevprev(_size2 + 1);
    std::vector<int> prev(_size2 + 1);
    std::vector<int> curr(_size2 + 1);

    for (int i = 0; i < _size1 + 1; i++) {
        prev[i] = i * _cost.ic.i;
    }

    auto b1 = _begin1;
    for (int i = 0; i < _size1; i++) {
        curr[0] = (i + 1) * _cost.dc.d;
        auto b2 = _begin2;
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

template <typename ptr1, typename ptr2, typename pred_t>
int EditDistance<ptr1, ptr2, pred_t>::hamming() const
{
    if (_size1 != _size2)
        return -1;
    auto b1 = _begin1;
    auto e1 = _end1;
    auto b2 = _begin2;
    auto e2 = _end2;
    int res = 0;
    while (b1 != e1) {
        if (!_equals(*b1++, *b2++)) {
            res += _cost.sc.s;
        }
    }
    return res;
}

#endif // __EDIT_DISTANCE_H_
