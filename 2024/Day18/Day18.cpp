// Day18.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void first(vector<string>& text_lines, pair<int,int> dims)
{
    int m = dims.first, n = dims.second;
    vector<vector<char>> grid(m, vector<char>(n, '.'));
    vector<pair<int, int>> blocks;
    for (string s : text_lines) {
        int j = 0;
        string n1 = "";
        while (s[j] != ',') n1.push_back(s[j++]);
        ++j;
        string n2 = "";
        while (j < s.size()) n2.push_back(s[j++]);

        blocks.push_back(make_pair(stoi(n2), stoi(n1)));
    }

    for (int i = 0; i < 1024; ++i) {
        grid[blocks[i].first][blocks[i].second] = '#';
    }


    // A* search
    vector<vector<int>> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> nodes; // pair(dist_from_end, node)
    nodes.push(make_pair(m-1 + n-1, 0));
    unordered_map<int, int> came_from;
    vector<vector<int>> scores(m, vector<int>(n, INT32_MAX));
    scores[0][0] = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    visited[0][0] = true;
    while (!nodes.empty()) {
        pair<int,int> node = nodes.top();
        int row = node.second / n;
        int col = node.second % n;
        nodes.pop();

        if (row == m - 1 && col == n - 1) break;

        int nscore = scores[row][col] + 1;
        for (int i = 0; i < 4; ++i) {
            int nrow = row + dirs[i][0], ncol = col + dirs[i][1];
            if (nrow < 0 || nrow == m || ncol < 0 || ncol == n || grid[nrow][ncol] == '#' || visited[nrow][ncol]) continue;

            if (nscore < scores[nrow][ncol]) {
                int nnode = nrow * n + ncol;
                came_from[nnode] = node.second;
                scores[nrow][ncol] = nscore;
                visited[nrow][ncol] = true;
                nodes.push(make_pair(nscore + m-1 - nrow + n-1 - ncol, nnode));
            }
        }
    }
    
    int curr = (m - 1) * n + n - 1;
    while (curr != 0) {
        if (came_from.count(curr) > 0) {
            grid[curr / n][curr % n] = 'O';
            curr = came_from[curr];
        }
        else {
            cout << "path mancante" << endl;
            break;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }


    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'O') ++res;
        }
    }
    cout << "res: " << res << endl;
}


static void second(vector<string>& text_lines, pair<int, int> dims)
{
    int m = dims.first, n = dims.second;
    vector<vector<char>> grid(m, vector<char>(n, '.'));
    vector<pair<int, int>> blocks;
    for (string s : text_lines) {
        int j = 0;
        string n1 = "";
        while (s[j] != ',') n1.push_back(s[j++]);
        ++j;
        string n2 = "";
        while (j < s.size()) n2.push_back(s[j++]);

        blocks.push_back(make_pair(stoi(n2), stoi(n1)));
    }

    for (int i = 0; i < (m == 7 ? 12 : 1024); ++i) {
        grid[blocks[i].first][blocks[i].second] = '#';
    }


    // A* search
    vector<vector<int>> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };


    // optimized using binary search on the blocks
    int left = 1024, right = blocks.size(); // left and right excluded

    while (left < right) {
        // blocks are inserted up to left-1
        int mid = left + (right - left) / 2;

        for (int h = left; h <= mid; ++h) grid[blocks[h].first][blocks[h].second] = '#';

        bool there_is_a_path = true;

        // test for a path
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nodes; // pair(dist_from_end, node)
        nodes.push(make_pair(m - 1 + n - 1, 0));
        unordered_map<int, int> came_from;
        vector<vector<int>> scores(m, vector<int>(n, INT32_MAX));
        scores[0][0] = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[0][0] = true;
        while (!nodes.empty()) {
            pair<int, int> node = nodes.top();
            int row = node.second / n;
            int col = node.second % n;
            nodes.pop();

            if (row == m - 1 && col == n - 1) break;

            int nscore = scores[row][col] + 1;
            for (int i = 0; i < 4; ++i) {
                int nrow = row + dirs[i][0], ncol = col + dirs[i][1];
                if (nrow < 0 || nrow == m || ncol < 0 || ncol == n || grid[nrow][ncol] == '#' || visited[nrow][ncol]) continue;

                if (nscore < scores[nrow][ncol]) {
                    int nnode = nrow * n + ncol;
                    came_from[nnode] = node.second;
                    scores[nrow][ncol] = nscore;
                    visited[nrow][ncol] = true;
                    nodes.push(make_pair(nscore + m - 1 - nrow + n - 1 - ncol, nnode));
                }
            }
        }

        int curr = (m - 1) * n + n - 1;
        while (curr != 0) {
            if (came_from.count(curr) > 0) {
                //grid[curr / n][curr % n] = 'O';
                curr = came_from[curr];
            }
            else {
                //cout << "path mancante" << endl;
                //for (int i = 0; i < m; ++i) {
                //    for (int j = 0; j < n; ++j) {
                //        cout << grid[i][j] << " ";
                //    }
                //    cout << endl;
                //}
                there_is_a_path = false;
                break;
            }
        }

        if (there_is_a_path) {
            left = mid + 1;
        }
        else {
            for(int h=left; h <= mid; ++h) grid[blocks[h].first][blocks[h].second] = '.';
            right = mid - 1;
        }
    }
    cout << "res: " << left << " -> " << blocks[left].second << "," << blocks[left].first << endl;
}


int main()
{
    //ifstream f("test.txt");
    //pair<int, int> dims = make_pair(7,7);
    ifstream f("input.txt");
    pair<int, int> dims = make_pair(71, 71); // 34,40

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




    //first(text_lines, dims);
    second(text_lines, dims);



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
