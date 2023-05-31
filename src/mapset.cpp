#include <iostream>
#include <string>
#include <map>
#include <set>
#include <string>
#include <cctype>
#include <algorithm>

std::string to_lowercase(const std::string& str) {

    std::string result = str;
    std::transform(str.begin(), str.end(), result.begin(), [](unsigned char c) {return std::tolower(c);});
    return result;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {

    std::set<std::string> stopset;
    std::istream_iterator<std::string> iterator(stopwords);
    std::istream_iterator<std::string> end_iterator;
    std::transform(iterator, end_iterator, std::inserter(stopset, stopset.end()), [](std::string stopword) {
        std::transform(stopword.begin(), stopword.end(), stopword.begin(), [](unsigned char c) {return std::tolower(c);});
        return stopword;
    });
    return stopset;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {

    std::map<std::string, int> freqmap;
    std::for_each(std::istream_iterator<std::string>(document), std::istream_iterator<std::string>(), [&](const std::string& word) {
        std::string lowercase_word = to_lowercase(word);
        if (stopwords.find(lowercase_word) == stopwords.end())
            freqmap[lowercase_word]++;
    });
    return freqmap;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {

    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
