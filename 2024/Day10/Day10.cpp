// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    int m = text_lines.size();
    int n = text_lines[0].size();
    vector<vector<int>> map(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            map[i][j] = text_lines[i][j] - '0';
        }
    }

    vector<vector<int>> near = { {1,0}, {-1,0}, {0,1}, {0,-1}};

    int res = 0;
    vector<vector<bool>> visited(m, vector<bool>(n,false));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            // check a trail
            if (map[i][j] == 0) {
                int count = 0;
                queue<pair<int, int>> q;
                q.push(make_pair(i,j));
                while (!q.empty()) {
                    pair<int, int> pos = q.front();
                    int row = pos.first;
                    int col = pos.second;
                    q.pop();
                    for (vector<int> move : near) {
                        int nrow = row + move[0];
                        int ncol = col + move[1];
                        if (nrow < 0 || nrow >= m || ncol < 0 || ncol >= n) {
                            continue;
                        }
                        if (!visited[nrow][ncol] && map[nrow][ncol] == map[row][col] + 1) {
                            if (map[nrow][ncol] == 9) {
                                ++count;
                            }
                            else {
                                q.push(make_pair(nrow, ncol));
                            }
                            visited[nrow][ncol] = true;
                        }
                    }
                }


                res += count;
                // reset visited
                for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) visited[i][j] = false;
            }
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = text_lines[0].size();
    vector<vector<int>> map(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            map[i][j] = text_lines[i][j] - '0';
        }
    }

    vector<vector<int>> near = { {1,0}, {-1,0}, {0,1}, {0,-1} };

    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            // check a trail
            if (map[i][j] == 0) {
                int count = 0;
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                while (!q.empty()) {
                    pair<int, int> pos = q.front();
                    int row = pos.first;
                    int col = pos.second;
                    q.pop();
                    for (vector<int> move : near) {
                        int nrow = row + move[0];
                        int ncol = col + move[1];
                        if (nrow < 0 || nrow >= m || ncol < 0 || ncol >= n) {
                            continue;
                        }
                        if (map[nrow][ncol] == map[row][col] + 1) {
                            if (map[nrow][ncol] == 9) {
                                ++count;
                            }
                            else {
                                q.push(make_pair(nrow, ncol));
                            }
                        }
                    }
                }


                res += count;
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
