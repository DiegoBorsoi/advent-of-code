// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
        for (char c : s) line.push_back(c);
        grid.push_back(line);
    }

    int m = grid.size();
    int n = grid[0].size();

    pair<int, int> start;
    pair<int, int> finish;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') start = make_pair(i, j);
            else if (grid[i][j] == 'E') finish = make_pair(i,j);
        }
    }

    vector<vector<unordered_set<int>>> visited(m, vector<unordered_set<int>>(n, unordered_set<int>()));

    // 0 = right, 1 = down, 2 = left, 3 = up
    vector<vector<int>> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    long res = 0;

    priority_queue<tuple<long, int, int, int>, vector<tuple<long, int, int, int>>, greater<tuple<long, int, int, int>>> q;
    q.push(make_tuple(0, start.first, start.second, 0));
    while (!q.empty()) {
        long score = get<0>(q.top());
        int row = get<1>(q.top());
        int col = get<2>(q.top());
        int dir = get<3>(q.top());
        q.pop();

        if (row == finish.first && col == finish.second) {
            res = score;
            break;
        }

        if (visited[row][col].count(dir) > 0) continue;
        visited[row][col].insert(dir);

        for (int i = 0; i < 4; ++i) {
            if (i == (dir + 2) % 4) continue; // skip the inverse of dir

            int new_row = row + dirs[i][0], new_col = col + dirs[i][1];
            if (grid[new_row][new_col] != '#') {
                if (i == dir) {
                    q.push(make_tuple(score + 1, new_row, new_col, i));
                }
                else {
                    q.push(make_tuple(score + 1001, new_row, new_col, i));
                }
            }
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << grid[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    std::cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<vector<char>> grid;
    for (string s : text_lines) {
        vector<char> line;
        for (char c : s) line.push_back(c);
        grid.push_back(line);
    }

    int m = grid.size();
    int n = grid[0].size();

    pair<int, int> start;
    pair<int, int> finish;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'S') start = make_pair(i, j);
            else if (grid[i][j] == 'E') finish = make_pair(i, j);
        }
    }

    vector<vector<unordered_set<int>>> visited(m, vector<unordered_set<int>>(n, unordered_set<int>()));

    // 0 = right, 1 = down, 2 = left, 3 = up
    vector<vector<int>> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    long best_score = 0;
    int end_dir = 0;

    priority_queue<tuple<long, int, int, int>, vector<tuple<long, int, int, int>>, greater<tuple<long, int, int, int>>> q;
    q.push(make_tuple(0, start.first, start.second, 0));
    while (!q.empty()) {
        long score = get<0>(q.top());
        int row = get<1>(q.top());
        int col = get<2>(q.top());
        int dir = get<3>(q.top());
        q.pop();

        if (row == finish.first && col == finish.second) {
            best_score = score;
            end_dir = dir;
            break;
        }

        if (visited[row][col].count(dir) > 0) continue;
        visited[row][col].insert(dir);

        for (int i = 0; i < 4; ++i) {
            if (i == (dir + 2) % 4) continue; // skip the inverse of dir

            int new_row = row + dirs[i][0], new_col = col + dirs[i][1];
            if (grid[new_row][new_col] != '#') {
                if (i == dir) {
                    q.push(make_tuple(score + 1, new_row, new_col, i));
                }
                else {
                    q.push(make_tuple(score + 1001, new_row, new_col, i));
                }
            }
        }
    }

    std::cout << best_score << endl;




    vector<vector<vector<int>>> scores(m, vector<vector<int>>(n, { -1,-1,-1,-1 }));
    visited = vector<vector<unordered_set<int>>>(m, vector<unordered_set<int>>(n, unordered_set<int>()));

    while (!q.empty()) q.pop();

    q.push(make_tuple(0, finish.first, finish.second, end_dir));
    while (!q.empty()) {
        long score = get<0>(q.top());
        int row = get<1>(q.top());
        int col = get<2>(q.top());
        int dir = get<3>(q.top());
        q.pop();

        if (visited[row][col].count(dir) > 0) continue;
        visited[row][col].insert(dir);
        scores[row][col][dir] = score;

        int new_row = row - dirs[dir][0], new_col = col - dirs[dir][1];

        if (grid[new_row][new_col] != '#') {
            for (int i = 0; i < 4; ++i) {
                if (i == (dir + 2) % 4) continue; // skip the inverse of dir

                if (dir == i) {
                    q.push(make_tuple(score + 1, new_row, new_col, i));
                }
                else {
                    q.push(make_tuple(score + 1001, new_row, new_col, i));
                }
            }
        }
    }




    while (!q.empty()) q.pop();
    visited = vector<vector<unordered_set<int>>>(m, vector<unordered_set<int>>(n, unordered_set<int>()));

    q.push(make_tuple(scores[start.first][start.second][0], start.first, start.second, 0));
    while (!q.empty()) {
        long score = get<0>(q.top());
        int row = get<1>(q.top());
        int col = get<2>(q.top());
        int dir = get<3>(q.top());
        q.pop();

        if (visited[row][col].count(dir) > 0) continue;
        visited[row][col].insert(dir);
        grid[row][col] = 'O';
        if (row == finish.first && col == finish.second) {
            best_score = score;
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            if (i == (dir + 2) % 4) continue; // skip the inverse of dir

            int new_row = row + dirs[i][0], new_col = col + dirs[i][1];
            if (grid[new_row][new_col] != '#') {
                if (i == dir) {
                    if(scores[new_row][new_col][i] == score - 1)
                        q.push(make_tuple(score - 1, new_row, new_col, i));
                }
                else {
                    if(scores[new_row][new_col][i] == score - 1001)
                        q.push(make_tuple(score - 1001, new_row, new_col, i));
                }
            }
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << grid[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    //cout << "-----------" << endl;
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << "{";
    //        for (int s : scores[i][j]) {
    //            if (s != -1) cout << s << ", ";
    //        }
    //        cout << "} ";
    //    }
    //    cout << endl;
    //}

    long res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'O') ++res;
        }
    }
    std::cout << "res: " << res << endl;
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