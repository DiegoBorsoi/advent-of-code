// Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using namespace std;

static void first(vector<string>& text_lines)
{
    int res = 0;
    bool ordering = true;
    unordered_map<int, vector<int>> rules;
    for (string s : text_lines) {
        if (s == "") {
            ordering = false;
            continue;
        }

        if (ordering) {
            // gets the ordering of the pages
            int pos = s.find('|');
            int a = atoi(s.substr(0, pos).c_str());
            int b = atoi(s.substr(pos+1).c_str());
            rules[a].push_back(b);
        }
        else {
            // get the update
            vector<int> update;
            string last = "";
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] == ',') {
                    update.push_back(atoi(last.c_str()));
                    last = "";
                }
                else {
                    last.push_back(s[i]);
                }
            }
            update.push_back(atoi(last.c_str()));
            // check the update
            bool right = true;
            unordered_set<int> found;
            found.insert(update[0]);
            for (int i = 1; i < update.size(); ++i) {
                for (int j = 0; j < rules[update[i]].size(); ++j) {
                    if (found.count(rules[update[i]][j]) > 0) right = false;
                }
                found.insert(update[i]);
            }
            if (right) res += update[update.size() / 2];
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int res = 0;
    bool ordering = true;
    unordered_map<int, unordered_set<int>> rules;
    for (string s : text_lines) {
        if (s == "") {
            ordering = false;
            continue;
        }

        if (ordering) {
            // gets the ordering of the pages
            int pos = s.find('|');
            int a = atoi(s.substr(0, pos).c_str());
            int b = atoi(s.substr(pos + 1).c_str());
            rules[a].insert(b);
        }
        else {
            // get the update
            vector<int> update;
            string last = "";
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] == ',') {
                    update.push_back(atoi(last.c_str()));
                    last = "";
                }
                else {
                    last.push_back(s[i]);
                }
            }
            update.push_back(atoi(last.c_str()));

            // check the update
            bool right = true;
            unordered_set<int> found;
            found.insert(update[0]);
            for (int i = 1; i < update.size(); ++i) {
                for (auto it = rules[update[i]].begin(); it != rules[update[i]].end(); ++it) {
                    if (found.count(*it) > 0) right = false;
                }
                found.insert(update[i]);
            }
            if (!right) {
                // order
                sort(update.begin(), update.end(), [&rules](int a, int b) { if(rules[b].count(a) > 0) return false; else return true; });

                //for (int i = 0; i < update.size(); ++i) cout << update[i] << " - ";
                //cout << endl;

                res += update[update.size() / 2];
            }
        }
    }
    cout << "res: " << res << endl;
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




    //first(text_lines);
    second(text_lines);



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
