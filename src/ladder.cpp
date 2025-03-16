#include "ladder.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << " " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    vector<vector<int>> costs(str1.length() + 1, vector<int>(str2.length() + 1, INF));

    for (int c = 0; c < str2.length() + 1; ++c) {
        costs[str1.length()][c] = str2.length() - c;
    }
    for (int r = 0; r < str1.length() + 1; ++r) {
        costs[r][str2.length()] = str1.length() - r;
    }

    for (int r = str1.length() - 1; r >= 0; --r) {
        for (int c = str2.length() - 1; c >= 0; --c) {
            if (str1[r] == str2[c]) {
                costs[r][c] = costs[r + 1][c + 1];
            }
            else {
                costs[r][c] = 1 + min(costs[r + 1][c], min(costs[r][c + 1], costs[r + 1][c + 1]));
            }
        }
    }

    return costs[0][0] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
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
    if (begin_word == end_word) {
        error(begin_word, end_word, "same word");
        vector<string> empty;
        return empty;
    }
    queue<vector<string>> ladder_queue;
    vector<string> begin;
    begin.push_back(begin_word);
    ladder_queue.push(begin);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    vector<string> empty;
    return empty;
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