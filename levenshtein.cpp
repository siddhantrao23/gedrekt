#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename C>
int levenshtein(const T& seq1, const T& seq2, const C& cost,
                const typename T::value_type& empty = typename T::value_type()) {
    const int size1 = seq1.size();
    const int size2 = seq2.size();

    vector<int> curr(size2 + 1);
    vector<int> prev(size1 + 1);

    prev[0] = 0;
    for (int idx2 = 0; idx2 < size2; ++idx2) {
        prev[idx2 + 1] = prev[idx2] + cost(empty, seq2[idx2]);
    }

    for (int idx1 = 0; idx1 < size1; ++idx1) {
        curr[0] = curr[0] + cost(empty, seq1[idx1]);
        for (int idx2 = 0; idx2 < size2; ++idx2) {
            curr[idx2+1] = min(min(
                                   curr[idx2] + cost(empty, seq2[idx2]),
                                   prev[idx2+1] + cost(empty, seq1[idx1])
                               ),
                               prev[idx2] + cost(seq1[idx1], seq2[idx2]));
        }
        curr.swap(prev);
        curr[0] = prev[0];
    }
    return prev[size2];
}

template<typename T>
int cost(const T& w1, const T& w2) {
    return w1 != w2 ? 1 : 0;
}

int main() {
    int a = levenshtein("cat", "dog", &cost);
    return 0;
}
