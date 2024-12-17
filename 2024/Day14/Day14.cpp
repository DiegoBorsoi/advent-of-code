// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void first(vector<string>& text_lines, pair<int,int> grid_size)
{
    vector<pair<int, int>> poss;
    vector<pair<int, int>> vels;
    for (string s : text_lines) {
        int j = 2;
        string col = "";
        while (s[j] != ',') col.push_back(s[j++]);
        ++j;
        string row = "";
        while (s[j] != ' ') row.push_back(s[j++]);
        poss.push_back(make_pair(stoi(row), stoi(col)));

        j += 3;
        col = "";
        while(s[j] != ',') col.push_back(s[j++]);
        ++j;
        row = "";
        while (j < s.size()) row.push_back(s[j++]);
        vels.push_back(make_pair(stoi(row), stoi(col)));
    }
    //for (auto p : poss) cout << p.first << " - " << p.second << endl;
    //for (auto p : vels) cout << p.first << " - " << p.second << endl;

    int m = grid_size.first;
    int n = grid_size.second;

    vector<vector<int>> grid(m, vector<int>(n, 0));
    for (int i = 0; i < poss.size(); ++i) ++grid[poss[i].first][poss[i].second];
    for (int k = 0; k < 100; ++k) {
        for (int i = 0; i < poss.size(); ++i) {
            --grid[poss[i].first][poss[i].second];

            poss[i].first = (poss[i].first + vels[i].first + m) % m;
            poss[i].second = (poss[i].second + vels[i].second + n) % n;

            ++grid[poss[i].first][poss[i].second];
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) cout << grid[i][j] << " ";
    //    cout << endl;
    //}

    vector<int> quadrants = {0,0,0,0};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == m / 2 || j == n / 2) continue;

            int idx = 0;
            if (i > m / 2) idx += 2;
            if (j > n / 2) idx += 1;
            quadrants[idx] += grid[i][j];
        }
    }

    long res = 1;
    for (int i = 0; i < 4; ++i) res *= quadrants[i];
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines, pair<int, int> grid_size)
{
    vector<pair<int, int>> poss;
    vector<pair<int, int>> vels;
    for (string s : text_lines) {
        int j = 2;
        string col = "";
        while (s[j] != ',') col.push_back(s[j++]);
        ++j;
        string row = "";
        while (s[j] != ' ') row.push_back(s[j++]);
        poss.push_back(make_pair(stoi(row), stoi(col)));

        j += 3;
        col = "";
        while (s[j] != ',') col.push_back(s[j++]);
        ++j;
        row = "";
        while (j < s.size()) row.push_back(s[j++]);
        vels.push_back(make_pair(stoi(row), stoi(col)));
    }
    //for (auto p : poss) cout << p.first << " - " << p.second << endl;
    //for (auto p : vels) cout << p.first << " - " << p.second << endl;

    int m = grid_size.first;
    int n = grid_size.second;

    vector<vector<int>> grid(m, vector<int>(n, 0));
    for (int i = 0; i < poss.size(); ++i) ++grid[poss[i].first][poss[i].second];
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) cout << grid[i][j] << " ";
    //    cout << endl;
    //}
    //cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    int cicle = 0;
    while(true) {
        for (int i = 0; i < poss.size(); ++i) {
            --grid[poss[i].first][poss[i].second];

            poss[i].first = (poss[i].first + vels[i].first + m) % m;
            poss[i].second = (poss[i].second + vels[i].second + n) % n;

            ++grid[poss[i].first][poss[i].second];
        }
        ++cicle;

        for (int i = 0; i < poss.size(); ++i) {
            bool line = true;
            pair<int, int> t = poss[i];
            for (int k = 0; k < 10; ++k) {
                t.first += 1;
                t.second += 1;
                if (t.first == m || t.second == n || grid[t.first][t.second] == 0) {
                    line = false;
                    break;
                }
            }
            if (line) {
                cout << "cicle: " << cicle << endl;
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) cout << grid[i][j] << " ";
                    cout << endl;
                }
                cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
                break;
            }
        }

        //for (int i = 0; i < m; ++i) {
        //    for (int j = 0; j < n; ++j) cout << grid[i][j] << " ";
        //    cout << endl;
        //}
        //cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

int main()
{
    //ifstream f("test.txt");
    //pair<int, int> grid_size = make_pair(7,11);
    ifstream f("input.txt");
    pair<int, int> grid_size = make_pair(103, 101);

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




    //first(text_lines, grid_size);
    second(text_lines, grid_size);



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
