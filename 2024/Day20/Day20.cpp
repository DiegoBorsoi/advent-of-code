// Day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    vector<vector<char>> grid;
    for (string s : text_lines) {
        vector<char> line;
        for (char c : s) {
            line.push_back(c);
        }
        grid.push_back(line);
    }

    int m = grid.size();
    int n = grid[0].size();

    pair<int, int> start;
    pair<int, int> finish;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') start = make_pair(i, j);
            if (grid[i][j] == 'E') finish = make_pair(i,j);
        }
    }

    vector<vector<int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} }; // right, down, left, up

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>> path(m, vector<int>(n, -1));
    pair<int, int> pos = start;
    int step = 0;
    while (true) {
        visited[pos.first][pos.second] = true;
        path[pos.first][pos.second] = step;

        if (pos.first == finish.first && pos.second == finish.second) break;

        ++step;

        for (vector<int> dir : dirs) {
            int nrow = pos.first + dir[0], ncol = pos.second + dir[1];

            if (grid[nrow][ncol] != '#' && !visited[nrow][ncol]) {
                pos = make_pair(nrow,ncol);
                break;
            }
        }
    }
    cout << "finish val: " << path[finish.first][finish.second] << endl;
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << path[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    int res = 0;
    visited = vector<vector<bool>>(m, vector<bool>(n, false));
    pos = start;
    while (true) {
        visited[pos.first][pos.second] = true;

        if (pos.first == finish.first && pos.second == finish.second) break;

        pair<int, int> next_pos;
        for (vector<int> dir : dirs) {
            int nrow = pos.first + dir[0], ncol = pos.second + dir[1];
            if (nrow == 0 || nrow == m - 1 || ncol == 0 || ncol == n - 1) continue;

            if (grid[nrow][ncol] != '#' && !visited[nrow][ncol]) {
                next_pos = make_pair(nrow, ncol);
            }
            else {
                // check for a possible cheat
                for (vector<int> dir2 : dirs) {
                    if (dir2[0] == (-1 * dir[0]) && dir2[1] == (-1 * dir[1])) continue; // skip going back

                    int nnrow = nrow + dir2[0], nncol = ncol + dir2[1];
                    if (grid[nnrow][nncol] != '#' && !visited[nnrow][nncol]) {
                        // found cheat
                        if (path[nnrow][nncol] - (2 + path[pos.first][pos.second]) >= 100) {
                            ++res;
                            //cout << nrow << " - " << ncol << endl;
                        }
                    }
                }
            }
        }
        pos = next_pos;
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<vector<char>> grid;
    for (string s : text_lines) {
        vector<char> line;
        for (char c : s) {
            line.push_back(c);
        }
        grid.push_back(line);
    }

    int m = grid.size();
    int n = grid[0].size();

    pair<int, int> start;
    pair<int, int> finish;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') start = make_pair(i, j);
            if (grid[i][j] == 'E') finish = make_pair(i, j);
        }
    }

    vector<vector<int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} }; // right, down, left, up

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>> path(m, vector<int>(n, -1));
    pair<int, int> pos = start;
    int step = 0;
    vector<pair<int, int>> cells;
    while (true) {
        visited[pos.first][pos.second] = true;
        path[pos.first][pos.second] = step;
        cells.push_back(pos);

        if (pos.first == finish.first && pos.second == finish.second) break;

        ++step;

        for (vector<int> dir : dirs) {
            int nrow = pos.first + dir[0], ncol = pos.second + dir[1];

            if (grid[nrow][ncol] != '#' && !visited[nrow][ncol]) {
                pos = make_pair(nrow, ncol);
                break;
            }
        }
    }
    cout << "finish val: " << path[finish.first][finish.second] << endl;

    long res = 0;
    visited = vector<vector<bool>>(m, vector<bool>(n, false));
    for (pair<int, int> pos : cells) {
        int row = pos.first, col = pos.second;
        visited[row][col] = true;
        
        int dist = -1;
        for (int i = max(row-20, 1); i <= min(row+20, m-2); ++i) {
            for (int j = max(col-20, 1); j <= min(col+20, n-2); ++j) {
                dist = abs(i - row) + abs(j - col);
                if (dist > 20) continue;

                if (grid[i][j] != '#' && !visited[i][j]) {
                    if (path[i][j] - path[row][col] - dist >= 100) ++res;
                }
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
