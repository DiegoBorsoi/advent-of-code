// Day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

using namespace std;

static void first(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = text_lines[0].size();
    vector<vector<char>> map(m, vector<char>(n, '.'));
    unordered_map<char, vector<pair<int, int>>> ant;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (text_lines[i][j] != '.') {
                map[i][j] = text_lines[i][j];
                ant[text_lines[i][j]].push_back(make_pair(i,j));
            }
        }
    }

    //for (auto it = ant.begin(); it != ant.end(); ++it) {
    //    cout << it->first << " -> " << it->second.size() << endl;
    //}

    // calculate antinodes positions
    for (auto it = ant.begin(); it != ant.end(); ++it) {
        for (int i = 0; i < it->second.size()-1; ++i) {
            for (int j = i + 1; j < it->second.size(); ++j) {
                int vdiff = it->second[j].first - it->second[i].first;
                int hdiff = it->second[j].second - it->second[i].second;

                if(it->second[i].first - vdiff >= 0 && it->second[i].first - vdiff < m && it->second[i].second - hdiff >= 0 && it->second[i].second - hdiff < n)
                    map[it->second[i].first - vdiff][it->second[i].second - hdiff] = '#';

                if(it->second[j].first + vdiff >= 0 && it->second[j].first + vdiff < m && it->second[j].second + hdiff >= 0 && it->second[j].second + hdiff < n)
                    map[it->second[j].first + vdiff][it->second[j].second + hdiff] = '#';
            }
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << map[i][j] << " ";
    //    }
    //    cout << endl;
    //}


    // count '#'
    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] == '#') ++res;
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = text_lines[0].size();
    vector<vector<char>> map(m, vector<char>(n, '.'));
    unordered_map<char, vector<pair<int, int>>> ant;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (text_lines[i][j] != '.') {
                map[i][j] = text_lines[i][j];
                ant[text_lines[i][j]].push_back(make_pair(i, j));
            }
        }
    }

    //for (auto it = ant.begin(); it != ant.end(); ++it) {
    //    cout << it->first << " -> " << it->second.size() << endl;
    //}

    // calculate antinodes positions
    for (auto it = ant.begin(); it != ant.end(); ++it) {
        for (int i = 0; i < it->second.size() - 1; ++i) {
            for (int j = i + 1; j < it->second.size(); ++j) {
                int vdiff = it->second[j].first - it->second[i].first;
                int hdiff = it->second[j].second - it->second[i].second;

                if (vdiff == 0) {
                    for (int k = 0; k < n; ++k) map[it->second[j].first][k] = '#';
                }else if (hdiff == 0) {
                    for (int k = 0; k < m; ++k) map[k][it->second[j].second] = '#';
                }
                else {
                    int new_i = it->second[i].first;
                    int new_j = it->second[i].second;
                    while (true) {
                        if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) {
                            map[new_i][new_j] = '#';
                            new_i -= vdiff;
                            new_j -= hdiff;
                        }
                        else {
                            break;
                        }
                    }

                    new_i = it->second[j].first;
                    new_j = it->second[j].second;
                    while (true) {
                        if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) {
                            map[new_i][new_j] = '#';
                            new_i += vdiff;
                            new_j += hdiff;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << map[i][j] << " ";
    //    }
    //    cout << endl;
    //}


    // count '#'
    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] == '#') ++res;
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
