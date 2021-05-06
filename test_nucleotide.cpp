#include <iostream>
#include <vector>
#include <initializer_list>
#include "edit_distance.h"

struct DNABase
{
    DNABase(char b)
    {
        if (b == 'A' || b == 'T' || b == 'C' || b == 'G')
            base = b;
        else
            std::cerr << "Illegal base: " << b << "\n";
    }
    friend bool operator==(DNABase x, DNABase y);
    char base;
};

class Nucleotide
{
public:
    Nucleotide(std::initializer_list<DNABase> seq) : _seq(seq) {}
    std::vector<DNABase>::iterator begin() { return _seq.begin(); }
    std::vector<DNABase>::iterator end() { return _seq.end(); }
private:
    std::vector<DNABase> _seq;
};

bool operator==(DNABase x, DNABase y)
{
    if ((x.base == 'A' && y.base == 'T') || (x.base == 'T' && y.base == 'A') ||
        (x.base == 'C' && y.base == 'G') || (x.base == 'G' && y.base == 'C')) {
        return true;
    }
    return false;
}

void print_nuc(Nucleotide n)
{
    std::cout << "{ ";
    for (DNABase item: n) {
        std::cout << item.base << " ";
    }
    std::cout << "}";
    std::cout << "\n";
}

int main()
{
    int lev, osa;
    Nucleotide a1 {'A', 'G', 'C', 'T', 'G'};
    Nucleotide b1 {'C', 'T', 'A', 'G'};
    EditDistance d1(std::begin(a1), std::end(a1), std::begin(b1), std::end(b1));
    lev = d1.lev();
    osa = d1.osa();
    std::cout << "Test Case 1\n";
    std::cout << "Nucleotides:\n";
    print_nuc(a1);
    print_nuc(b1);
    std::cout << "User-defined object: Nucleotide\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "hamming distance                  : " << "NA" << "\n";
    std::cout << "levenshtein distance              : " << lev << "\n";
    std::cout << "optimal string alignment distance : " << osa << "\n";
    std::cout << "------------------------------------------------------\n\n";

    return 0;
}
