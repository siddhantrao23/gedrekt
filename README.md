# Generic Edit Distance

Edit distance is generally used as a metric to measure the degree of dissimilarity between two strings. It is defined as the minimum number of operations required to transform one string to the other by using any subset of the operations insertion, deletion, substitution and transposition.

We provide a generic library for edit distance that provides an interface for calculating the following edit distances:
+ Levenshtein Distance: allows for insertion, deletion and substitution
+ Hamming Distance: only allows for substitutions on equal sized containers
+ Damerau–Levenshtein Distance (specifically the Optimal String Alignment algorithm): allows for insertion, deletion, substitution and transposition of two adjacent elements
    
This library can work on most STL containers, including arrays, vectors, lists, deques, sets and maps. It can also work for user defined types as long as the associated predicate is defined for that type.

This helps extends the application to other types of data, such as genome sequences, encoded query plans etc.

# Usage

``` c++
#include "edit_distance.h"

// create the edit distance object using the constructor
EditDistance d(std::begin(container1), std::end(container2),    // source container
                std:::begin(container2), std::end(container2),  // target container
                Cost{},                                         // cost for each operation
                [](auto x, auto y) { return x == y; });         // equality predicate
                
// call the required edit distance algorithm
d.hamming();
d.lev();
d.ost();
d.readers_digest();
```

# Building and Testing

Run the command:
``` sh
make
```

This will build the necessary files along with the example test file binaries.

As an example, to test the `test_nucleotide` test file, we would run:

``` sh
./test_nucleotide
```

