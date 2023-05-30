#include <fstream>
#include <algorithm>
#include <iterator>

#include "process_numbers.hpp"

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {

    std::vector<int> numvector((std::istream_iterator<int>(numbers)), std::istream_iterator<int>());
    
    // Sort
    std::sort(numvector.begin(), numvector.end());
    
    // Output Odds
    std::copy_if(numvector.begin(), numvector.end(), std::ostream_iterator<int>(odds, " "), [](int num){return num % 2 != 0;});
    odds << '\n';

    // Output Evens
    std::copy_if(numvector.begin(), numvector.end(), std::ostream_iterator<int>(evens, "\n"), [](int num){return num % 2 == 0;});
}
