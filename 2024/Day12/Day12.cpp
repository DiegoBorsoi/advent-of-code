// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    vector<vector<char>> grid(m, vector<char>(n, 'a'));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = text_lines[i][j];
        }
    }
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    long long res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visited[i][j]) continue;

            // start expansion on near gardens with the same letter
            char c = grid[i][j];
            int area = 0;
            int perim = 0;

            queue<pair<int, int>> q;
            q.push(make_pair(i, j));
            visited[i][j] = true;
            while (!q.empty()) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                ++area;

                if (row == 0) {
                    ++perim;
                }
                else {
                    if (grid[row - 1][col] == c) {
                        if (!visited[row - 1][col]) {
                            q.push(make_pair(row - 1, col));
                            visited[row - 1][col] = true;
                        }
                    }
                    else {
                        ++perim;
                    }
                }

                if (row == m - 1) {
                    ++perim;
                }
                else {
                    if (grid[row + 1][col] == c) {
                        if (!visited[row + 1][col]) {
                            q.push(make_pair(row + 1, col));
                            visited[row + 1][col] = true;
                        }
                    }
                    else {
                        ++perim;
                    }
                }

                if (col == 0) {
                    ++perim;
                }
                else {
                    if (grid[row][col - 1] == c) {
                        if (!visited[row][col - 1]) {
                            q.push(make_pair(row, col - 1));
                            visited[row][col - 1] = true;
                        }
                    }
                    else {
                        ++perim;
                    }
                }

                if (col == n - 1) {
                    ++perim;
                }
                else {
                    if (grid[row][col + 1] == c) {
                        if (!visited[row][col + 1]) {
                            q.push(make_pair(row, col + 1));
                            visited[row][col + 1] = true;
                        }
                    }
                    else {
                        ++perim;
                    }
                }
            }
            //cout << c << " -> " << area << " * " << perim << endl;
            res += area * perim;
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = text_lines[0].size();
    vector<vector<char>> grid(m, vector<char>(n, 'a'));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = text_lines[i][j];
        }
    }
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>> gardens(m, vector<int>(n, -1));
    vector<int> areas;
    int garden_id = -1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visited[i][j]) continue;

            ++garden_id;
            // start expansion on near gardens with the same letter
            char c = grid[i][j];
            int area = 0;

            queue<pair<int, int>> q;
            q.push(make_pair(i, j));
            visited[i][j] = true;
            while (!q.empty()) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                gardens[row][col] = garden_id;
                ++area;

                if (row == 0) {
                    //++perim;
                }
                else {
                    if (grid[row - 1][col] == c) {
                        if (!visited[row - 1][col]) {
                            q.push(make_pair(row - 1, col));
                            visited[row - 1][col] = true;
                        }
                    }
                    else {
                        //++perim;
                    }
                }

                if (row == m - 1) {
                    //++perim;
                }
                else {
                    if (grid[row + 1][col] == c) {
                        if (!visited[row + 1][col]) {
                            q.push(make_pair(row + 1, col));
                            visited[row + 1][col] = true;
                        }
                    }
                    else {
                        //++perim;
                    }
                }

                if (col == 0) {
                    //++perim;
                }
                else {
                    if (grid[row][col - 1] == c) {
                        if (!visited[row][col - 1]) {
                            q.push(make_pair(row, col - 1));
                            visited[row][col - 1] = true;
                        }
                    }
                    else {
                        //++perim;
                    }
                }

                if (col == n - 1) {
                    //++perim;
                }
                else {
                    if (grid[row][col + 1] == c) {
                        if (!visited[row][col + 1]) {
                            q.push(make_pair(row, col + 1));
                            visited[row][col + 1] = true;
                        }
                    }
                    else {
                        //++perim;
                    }
                }
            }
            //cout << c << " -> " << area << " * " << perim << endl;
            //res += area * perim;
            areas.push_back(area);
        }
    }
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << gardens[i][j] << " ";
    //    }
    //    cout << endl;
    //} cout << endl;

    vector<int> sides(garden_id+1, 0);
    // 4 corners of the grid
    ++sides[gardens[0][0]];
    ++sides[gardens[m-1][0]];
    ++sides[gardens[0][n-1]];
    ++sides[gardens[m-1][n-1]];

    // 4 sides of the grid
    for (int i = 0; i < m-1; ++i) {
        if (gardens[i][0] != gardens[i + 1][0]) {
            ++sides[gardens[i][0]];
            ++sides[gardens[i+1][0]];
        }
        if (gardens[i][n-1] != gardens[i + 1][n - 1]) {
            ++sides[gardens[i][n - 1]];
            ++sides[gardens[i + 1][n - 1]];
        }
    }
    for (int j = 0; j < n - 1; ++j) {
        if (gardens[0][j] != gardens[0][j+1]) {
            ++sides[gardens[0][j]];
            ++sides[gardens[0][j+1]];
        }
        if (gardens[m-1][j] != gardens[m - 1][j + 1]) {
            ++sides[gardens[m - 1][j]];
            ++sides[gardens[m - 1][j + 1]];
        }
    }

    // corners inside grid
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            // check if it is a corner
            // normal corner
            if (i > 0 && j < n-1 && gardens[i][j] != gardens[i - 1][j] && gardens[i][j] != gardens[i][j + 1]) ++sides[gardens[i][j]];
            if (i > 0 && j > 0 && gardens[i][j] != gardens[i - 1][j] && gardens[i][j] != gardens[i][j - 1]) ++sides[gardens[i][j]];
            if (i < m-1 && j < n-1 && gardens[i][j] != gardens[i + 1][j] && gardens[i][j] != gardens[i][j + 1]) ++sides[gardens[i][j]];
            if (i < m-1 && j > 0 && gardens[i][j] != gardens[i + 1][j] && gardens[i][j] != gardens[i][j - 1]) ++sides[gardens[i][j]];
            
            // inside corner
            if (i > 0 && j < n-1 && gardens[i][j] != gardens[i - 1][j] && gardens[i - 1][j] == gardens[i - 1][j + 1] && gardens[i - 1][j + 1] == gardens[i][j + 1]) ++sides[gardens[i - 1][j]];
            if (i < m-1 && j < n-1 && gardens[i][j] != gardens[i][j + 1] && gardens[i][j + 1] == gardens[i + 1][j + 1] && gardens[i + 1][j + 1] == gardens[i + 1][j]) ++sides[gardens[i][j + 1]];
            if (i < m-1 && j > 0 && gardens[i][j] != gardens[i + 1][j] && gardens[i + 1][j] == gardens[i + 1][j - 1] && gardens[i + 1][j - 1] == gardens[i][j - 1]) ++sides[gardens[i + 1][j]];
            if (i > 0 && j > 0 && gardens[i][j] != gardens[i][j - 1] && gardens[i][j - 1] == gardens[i - 1][j - 1] && gardens[i - 1][j - 1] == gardens[i - 1][j]) ++sides[gardens[i][j - 1]];
        }
    }
    //for (int i = 0; i < garden_id + 1; ++i) cout << areas[i] << " * " << sides[i] << endl;

    long long res = 0;
    for (int i = 0; i < garden_id + 1; ++i) res += areas[i] * sides[i];
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
