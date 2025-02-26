// Day25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <queue>
#include <list>
#include <stack>

using namespace std;

static void first(vector<string>& text_lines)
{
    vector<vector<int>> locks;
    vector<vector<int>> keys;
    for (int r = 0; r < text_lines.size(); r += 8) {
        if (text_lines[r][0] == '#') { // it'a lock
            vector<int> new_lock = {0,0,0,0,0};
            for (int i = 1; i <= 5; ++i) {
                string line = text_lines[r + i];
                for (int j = 0; j < line.size(); ++j) {
                    if (line[j] == '#') ++new_lock[j];
                }
            }
            locks.push_back(new_lock);
        }
        else { // it's a key
            vector<int> new_key = { 0,0,0,0,0 };
            for (int i = 1; i <= 5; ++i) {
                string line = text_lines[r + i];
                for (int j = 0; j < line.size(); ++j) {
                    if (line[j] == '#') ++new_key[j];
                }
            }
            keys.push_back(new_key);
        }
    }

    int l = locks.size();
    int k = keys.size();

    //sort(locks.begin(), locks.end());
    //sort(keys.begin(), keys.end());

    //cout << "locks (" << l << "): " << endl;
    //for (vector<int> lock : locks) cout << "{" << lock[0] << " - " << lock[1] << " - " << lock[2] << " - " << lock[3] << " - " << lock[4] << "}" << endl;
    //cout << endl;
    //cout << "keys (" << k << "): " << endl;
    //for (vector<int> key : keys) cout << "{" << key[0] << " - " << key[1] << " - " << key[2] << " - " << key[3] << " - " << key[4] << "}" << endl;

    int res = 0;
    for (vector<int> key : keys) {
        for (vector<int> lock : locks) {
            // check for overlaps
            bool good = true;
            for (int i = 0; i < 5; ++i) if (key[i] + lock[i] > 5) good = false;
            if (good) ++res;
        }
    }
    cout << "res = " << res << endl;
}


int main()
{
    //ifstream f("test.txt");
    ifstream f("input.txt");

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    // String variable to store the read data
    vector<string> text_lines;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
    // completely read
    string s;
    while (getline(f, s)) {
        text_lines.push_back(s);
        //cout << s << endl;
    }
    // Close the file
    f.close();


    std::cout << text_lines.size() << endl;




    first(text_lines);
    //second(text_lines);



    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
