#include "ladder.h"
#include <queue>

using namespace std;

void error(string word1, string word2, string msg) {

}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    
}

bool is_adjacent(const string& word1, const string& word2) {
    
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    /*
    ladder_queue = queue of vector of strings
    ladder_queue.push([begin_word])
    visited = set of strings
    visited.insert(begin_word)
    while ladder_queue is not empty:
        ladder = ladder_queue.pop_front()
        last_word = last element of ladder
        for word in word_list:
            if is_adjacent(last_word, word):
                if word not in visited:
                    visited.insert(word)
                    new_ladder = copy of ladder
                    new_ladder.push_back(word)
                    if word equals end_word:
                        return new_ladder
                    ladder_queue.push(new_ladder)
    return no ladder found
    */

}

void load_words(set<string> & word_list, const string& file_name) {
    
}

void print_word_ladder(const vector<string>& ladder) {
    for (string word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    
}