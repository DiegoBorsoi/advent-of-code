// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

using namespace std;

static void first(vector<string>& text_lines)
{
    //cout << text_lines[0].size() << endl;
    string s = text_lines[0];
    int n = s.size();
    vector<int> files;
    vector<int> voids;
    for (int i = 0; i < n; i += 2) {
        files.push_back(s[i] - '0');
        if(i < n-1) voids.push_back(s[i+1] - '0');
    }

    //for (int i = 0; i < files.size(); ++i) {
    //    cout << files[i] << " - ";
    //}
    //cout << endl;
    //for (int i = 0; i < voids.size(); ++i) {
    //    cout << voids[i] << " - ";
    //}
    //cout << endl;

    // pairs: (index, number)
    vector<pair<int, int>> compact;
    for (int i = 0, j = 0; i < voids.size() && j < files.size(); ++i, ++j) {
        if (files.back() == 0 || j+1 == files.size() - 1) break;

        compact.push_back(make_pair(j, files[j]));
        files[j] = 0;

        while (voids[i] > 0) {
            if (voids[i] >= files.back()) {
                compact.push_back(make_pair(files.size() - 1, files.back()));
                voids[i] -= files.back();
                files.pop_back();
            }
            else {
                compact.push_back(make_pair(files.size() - 1, voids[i]));
                files[files.size() - 1] -= voids[i];
                voids[i] = 0;
            }
        }
    }

    for (int i = 0; i < files.size(); ++i) {
        if(files[i] != 0) compact.push_back(make_pair(i, files[i]));
    }

    //for (auto p : compact) {
    //    cout << p.first << " -> " << p.second << endl;
    //}

    long long res = 0, i = 0;
    for (auto p : compact) {
        while (p.second > 0) {
            res += p.first * i;
            p.second -= 1;
            ++i;
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    //cout << text_lines[0].size() << endl;
    string s = text_lines[0];
    int n = s.size();

    list<pair<int, int>> spaces; // files and voids, if the first value is -1 it is a void
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        spaces.push_back(make_pair(j, s[i] - '0'));
        if (i < n - 1) spaces.push_back(make_pair(-1, s[i+1] - '0'));
    }

    //cout << spaces.size() << endl;

    for (auto rit = spaces.rbegin(); rit != spaces.rend(); ++rit) {
        if ((*rit).first != -1) {
            for (auto it = spaces.begin(); it != rit.base(); ++it) {
                if ((*it).first == -1 && (*it).second >= (*rit).second) {
                    (*it).second -= (*rit).second;
                    spaces.emplace(it, (*rit).first, (*rit).second);
                    (*rit).first = -1;
                    break;
                }
            }
        }
    }

    //for (auto it = spaces.begin(); it != spaces.end(); ++it) {
    //    cout << (*it).first << " -> " << (*it).second << endl;
    //}

    long long res = 0, i = 0;
    for (auto it = spaces.begin(); it != spaces.end(); ++it) {
        while ((*it).second > 0) {
            if ((*it).first != -1) res += (*it).first * i;
            ++i;
            (*it).second -= 1;
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
