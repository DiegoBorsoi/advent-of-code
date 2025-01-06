// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    int m = text_lines.size();
    int n = text_lines[0].size();

    vector<vector<int>> map(m, vector<int>(n,0)); // matrix of size m x n, values: 0 -> '.', 1 -> '#', 2 -> 'X'
    pair<int, int> pos;
    int dir;    // 0 -> up, 1 -> right, 2 -> down, 3 -> left

    // populate the map and find the starting pos
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (text_lines[i][j] == '#') {
                map[i][j] = 1;
            }
            else if (text_lines[i][j] == '^') {
                pos = make_pair(i, j);
                dir = 0;
                map[i][j] = 2;
            }
        }
    }
    //cout << "start: " << pos.first << " - " << pos.second << endl;

    bool exited = false;
    while (!exited) {
        switch (dir) {
            case 0:
                while (pos.first >= 0 && map[pos.first][pos.second] != 1) {
                    map[pos.first][pos.second] = 2;
                    pos.first -= 1;
                }
                if(pos.first == -1) exited = true;
                pos.first += 1;
                dir = 1;
                break;
            case 1:
                while (pos.second < n && map[pos.first][pos.second] != 1) {
                    map[pos.first][pos.second] = 2;
                    pos.second += 1;
                }
                if (pos.second == n) exited = true;
                pos.second -= 1;
                dir = 2;
                break;
            case 2:
                while (pos.first < m && map[pos.first][pos.second] != 1) {
                    map[pos.first][pos.second] = 2;
                    pos.first += 1;
                }
                if (pos.first == m) exited = true;
                pos.first -= 1;
                dir = 3;
                break;
            case 3:
                while (pos.second >= 0 && map[pos.first][pos.second] != 1) {
                    map[pos.first][pos.second] = 2;
                    pos.second -= 1;
                }
                if (pos.second == -1) exited = true;
                pos.second += 1;
                dir = 0;
                break;
        }
    }

    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] == 2) {
                ++res;
            }
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = text_lines[0].size();

    // matrix of size m x n, 
    // values: 0 -> '.', 1 -> '#', 2 -> from down, 3 -> from left, 4 -> from up, 5 -> from right
    vector<vector<unordered_set<int>>> map(m, vector<unordered_set<int>>(n));
    vector<vector<int>> guard(m, vector<int>(n, 0));

    pair<int, int> starting_pos;
    int dir;    // 0 -> up, 1 -> right, 2 -> down, 3 -> left
    vector<pair<int, int>> blocks;

    // populate the map and find the starting pos
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (text_lines[i][j] == '#') {
                guard[i][j] = 1;
                blocks.push_back(make_pair(i, j));
            }
            else if (text_lines[i][j] == '^') {
                starting_pos = make_pair(i, j);
                dir = 0;
            }
        }
    }
    //cout << "start: " << pos.first << " - " << pos.second << endl;
    pair<int, int> pos = starting_pos;


    bool exited = false;
    while (!exited) {
        switch (dir) {
        case 0:
            while (pos.first >= 0 && guard[pos.first][pos.second] != 1) {
                guard[pos.first][pos.second] = 2;
                pos.first -= 1;
            }
            if (pos.first == -1) exited = true;
            pos.first += 1;
            dir = 1;
            break;
        case 1:
            while (pos.second < n && guard[pos.first][pos.second] != 1) {
                guard[pos.first][pos.second] = 2;
                pos.second += 1;
            }
            if (pos.second == n) exited = true;
            pos.second -= 1;
            dir = 2;
            break;
        case 2:
            while (pos.first < m && guard[pos.first][pos.second] != 1) {
                guard[pos.first][pos.second] = 2;
                pos.first += 1;
            }
            if (pos.first == m) exited = true;
            pos.first -= 1;
            dir = 3;
            break;
        case 3:
            while (pos.second >= 0 && guard[pos.first][pos.second] != 1) {
                guard[pos.first][pos.second] = 2;
                pos.second -= 1;
            }
            if (pos.second == -1) exited = true;
            pos.second += 1;
            dir = 0;
            break;
        }
    }

    guard[starting_pos.first][starting_pos.second] = 0;

    int res = 0;

    //pair<int, int> pos;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (guard[i][j] != 2) continue;

            //cout << "trying: (" << i << " - " << j << ")" << endl;
            for (pair<int, int> b : blocks) {
                map[b.first][b.second].clear();
                map[b.first][b.second].insert(1);
            }
            
            map[i][j].insert(1);

            int status = 0; // 0 -> running, 1 -> exited, 2 -> looped

            dir = 0;
            pos = starting_pos;
            while (status == 0) {
                switch (dir) {
                    case 0:
                        while (pos.first >= 0 && map[pos.first][pos.second].empty()) {
                            pos.first -= 1;
                        }
                        if (pos.first == -1) status = 1;
                        else if (map[pos.first][pos.second].count(2) > 0) status = 2;
                        else {
                            map[pos.first][pos.second].insert(2);
                            pos.first += 1;
                            dir = 1;
                        }
                        break;
                    case 1:
                        while (pos.second < n && map[pos.first][pos.second].empty()) {
                            pos.second += 1;
                        }
                        if (pos.second == n) status = 1;
                        else if (map[pos.first][pos.second].count(3) > 0) status = 2;
                        else {
                            map[pos.first][pos.second].insert(3);
                            pos.second -= 1;
                            dir = 2;
                        }
                        break;
                    case 2:
                        while (pos.first < m && map[pos.first][pos.second].empty()) {
                            pos.first += 1;
                        }
                        if (pos.first == m) status = 1;
                        else if (map[pos.first][pos.second].count(4) > 0) status = 2;
                        else {
                            map[pos.first][pos.second].insert(4);
                            pos.first -= 1;
                            dir = 3;
                        }
                        break;
                    case 3:
                        while (pos.second >= 0 && map[pos.first][pos.second].empty()) {
                            pos.second -= 1;
                        }
                        if (pos.second == -1) status = 1;
                        else if (map[pos.first][pos.second].count(5) > 0) status = 2;
                        else {
                            map[pos.first][pos.second].insert(5);
                            pos.second += 1;
                            dir = 0;
                        }
                        break;
                }
            }

            if (status == 2) {
                ++res;
                //cout << "(" << i << " - " << j << ")" << endl;
            }

            map[i][j].clear();
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
