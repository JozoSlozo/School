#pragma once

#include <vector>
#include <string>

class ModusCalculator {
private:
    std::vector<std::string> words;         // Vector to store the words
    std::vector<std::string> words_sorted;  // Sorted version of words

public:
    // Constructor: Reads words from a file and initializes words and words_sorted
    ModusCalculator(const std::string& file_path);

    // Method to compute modus of words
    void compute_modus_unsorted();

    // Method to compute modus of words_sorted
    void compute_modus_sorted();

    // Method to test both unsorted and sorted methods and measure time
    void test_both();
};


