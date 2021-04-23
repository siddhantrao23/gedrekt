#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

template<typename ptr_t, typename T, typename binop_t>
T levenshtein(const ptr_t& seq1, const ptr_t& seq2, T init, binop_t cost) {
    const int size1 = seq1.size();
    const int size2 = seq2.size();

    vector<int> curr(size2 + 1);
    vector<int> prev(size1 + 1);

    prev[0] = 0;
    for (int idx2 = 0; idx2 < size2; ++idx2) {
        prev[idx2 + 1] = prev[idx2] + cost(init, seq2[idx2]);
    }

    for (int idx1 = 0; idx1 < size1; ++idx1) {
        curr[0] = curr[0] + cost(init, seq1[idx1]);
        for (int idx2 = 0; idx2 < size2; ++idx2) {
            curr[idx2+1] = min(min(
                                   curr[idx2] + cost(init, seq2[idx2]),
                                   prev[idx2+1] + cost(init, seq1[idx1])
                               ),
                               prev[idx2] + cost(seq1[idx1], seq2[idx2]));
        }
        curr.swap(prev);
        curr[0] = prev[0];
    }
    return prev[size2];
}

template<typename T>
struct Cost {
    int operator()(const T& w1, const T& w2) {
        return w1 != w2 ? 1 : 0;
    }
};

int main() {
    string a1 = "cat";
    string b1 = "car";
    auto res1 = levenshtein(a1, b1, 0, Cost<char>());
    cout << "res1 : " << res1 << "\n";

    vector<int> v1{10, 20, 30, 40, 50};
    vector<int> v2{10, 22, 30, 40, 50};
    auto res2 = levenshtein(v1, v2, 0, Cost<int>());
    cout << "res2 : " << res2 << "\n";

    int a[] = {1, 2, 3, 4};
    int b[] = {1, 1, 2, 3};
    deque<int> d1(a, a + 4);
    deque<int> d2(b, b + 4);
    auto res3 = levenshtein(d1, d2, 0, Cost<int>());
    cout << "res3 : " << res3 << "\n";

    // doesn't work for lists

    return 0;
}
