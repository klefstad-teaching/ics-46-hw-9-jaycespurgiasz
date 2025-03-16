#include "ladder.h"
#include <set>
#include <vector>
#include <iostream>

int main() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    std::cout << word_list.size();

    std::cout << (word_list.find("aback") == word_list.end()) << std::endl;

    vector<string> ladder = generate_word_ladder("aback", "abash", word_list);

    print_word_ladder(ladder);

    return 0;
}