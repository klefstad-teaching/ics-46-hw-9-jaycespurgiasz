#include "ladder.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>

using namespace std;

constexpr int INF = numeric_limits<int>::max();

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << " " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs((int)(str1.length() - str2.length())) > d) {
        return false;
    }

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
    if (abs((int)(word1.length() - word2.length())) > 1) {
        return false;
    }
    if (abs((int)(word1.length() - word2.length())) == 1) {
        int i = 0;
        int j = 0;
        bool iLonger = (word1.length() > word2.length());
        bool diff = false;
        while (i < word1.length() && j < word2.length()) {
            if (word1[i] != word2[j]) {
                if (diff) {
                    return false;
                }
                diff = true;
                if (iLonger) {
                    ++i;
                }
                else {
                    ++j;
                }
            }
            else {
                ++i;
                ++j;
            }
        }
        return true;
    }
    bool diff = false;
    for (int i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            diff = !diff;
            if (!diff) {
                return false;
            }
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "same word");
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "end word not in dictionary");
        return {};
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
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; (in >> word);) {
        for (char& c : word) {
            c = tolower(c);
        }
        if (word == "aback") {
            cout << word;
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    }
    else {
        cout << "Word ladder found: ";
        for (string word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}