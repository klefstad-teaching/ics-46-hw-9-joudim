#include "ladder.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

void error(string word1, string word2, string msg){
    cout << "Error: " << word1 << " " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
     int n = str1.size();
    int m = str2.size();
    if (abs(n - m) > d)
        return false;
    vector<vector<int>> d_table(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i)
        d_table[i][0] = i;
    for (int j = 0; j <= m; ++j)
        d_table[0][j] = j;
    
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            if (str1[i - 1] == str2[j - 1])
                d_table[i][j] = d_table[i - 1][j - 1];
            else
                d_table[i][j] = 1 + min({d_table[i - 1][j - 1], d_table[i - 1][j], d_table[i][j - 1]});
        }
    }
    return d_table[n][m] <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    if (word1 == word2)
        return false;
    
   string w1 = word1;
    string w2 = word2;
    for (auto& c : w1)
        c = tolower(c);
    for (auto& c : w2)
        c = tolower(c);
    
    return edit_distance_within(w1, w2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    
    string start = begin_word;
    string end = end_word;
    for (auto& c : start)
        c = tolower(c);
    for (auto& c : end)
        c = tolower(c);
    
    if (start == end) {
        error(begin_word, end_word, "Start and end words must be different.");
        return {};
    }

    if (word_list.find(end) == word_list.end()){
        error(begin_word, end_word, "End word is not in the dictionary.");
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({start});
    
    set<string> visited;
    visited.insert(start);
    
    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const string& word : word_list){
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in){
        cout << "Error: Unable to open file " << file_name << endl;
        return;
    }
    
    string word;
    while (in >> word){
        for (auto& c : word)
            c = tolower(c);
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
    } else{
        for (size_t i = 0; i < ladder.size(); ++i){
            cout << ladder[i];
            if (i != ladder.size() - 1)
                cout << " -> ";
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