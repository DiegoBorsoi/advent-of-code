// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    // text_lines = m x n
    int m = text_lines.size();
    int n = text_lines[0].size();

    int res = 0;

    // horizzontal
    for (int i = 0; i < m; ++i) {
        // search for XMAS
        string search = "XMAS";
        int k = 0;
        bool found = false;
        for (int j = 0; j < n; ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAMX
        search = "SAMX";
        k = 0;
        found = false;
        for (int j = 0; j < n; ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
    }

    // vertical
    for (int j = 0; j < n; ++j) {
        // search for XMAS
        string search = "XMAS";
        int k = 0;
        bool found = false;
        for (int i = 0; i < m; ++i) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAMX
        search = "SAMX";
        k = 0;
        found = false;
        for (int i = 0; i < m; ++i) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
    }

    // diagonal (top left - bottom right)
    for (int d = 0; d < m + n - 1; ++d) {
        // search for XMAS
        string search = "XMAS";
        int k = 0;
        bool found = false;
        for (int i = max(0, m-1 - d), j = max(0, d - m + 1); i < m && j < n; ++i, ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAMX
        search = "SAMX";
        k = 0;
        found = false;
        for (int i = max(0, m - 1 - d), j = max(0, d - m + 1); i < m && j < n; ++i, ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
    }

    // diagonal (top right - bottom left)
    for (int d = 0; d < m + n - 1; ++d) {
        // search for XMAS
        string search = "XMAS";
        int k = 0;
        bool found = false;
        for (int i = max(0, m - 1 - d), j = min(n - 1, m + n - 2 - d); i < m && j >= 0; ++i, --j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    ++j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAMX
        search = "SAMX";
        k = 0;
        found = false;
        for (int i = max(0, m - 1 - d), j = min(n - 1, m + n - 2 - d); i < m && j >= 0; ++i, --j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    ++j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
    }

    cout << "res: " << res << endl;

}

static void second(vector<string>& text_lines)
{
    // text_lines = m x n
    int m = text_lines.size();
    int n = text_lines[0].size();

    int res = 0;
    unordered_set<int> diag;

    // diagonal (top left - bottom right)
    for (int d = 0; d < m + n - 1; ++d) {
        // search for MAS
        string search = "MAS";
        int k = 0;
        bool found = false;
        for (int i = max(0, m - 1 - d), j = max(0, d - m + 1); i < m && j < n; ++i, ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        diag.insert((i-1)*n + j-1);
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAM
        search = "SAM";
        k = 0;
        found = false;
        for (int i = max(0, m - 1 - d), j = max(0, d - m + 1); i < m && j < n; ++i, ++j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        diag.insert((i - 1) * n + j - 1);
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    --j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
    }

    // diagonal (top right - bottom left)
    for (int d = 0; d < m + n - 1; ++d) {
        // search for MAS
        string search = "MAS";
        int k = 0;
        bool found = false;
        for (int i = max(0, m - 1 - d), j = min(n - 1, m + n - 2 - d); i < m && j >= 0; ++i, --j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        if (diag.count((i-1)*n + j+1) > 0) ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    ++j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
                }
            }
        }
        // search for SAM
        search = "SAM";
        k = 0;
        found = false;
        for (int i = max(0, m - 1 - d), j = min(n - 1, m + n - 2 - d); i < m && j >= 0; ++i, --j) {
            if (found) {
                if (text_lines[i][j] == search[k]) {
                    ++k;

                    if (k == search.size()) {
                        found = false;
                        k = 0;
                        if (diag.count((i - 1) * n + j + 1) > 0) ++res;
                    }
                }
                else {
                    found = false;
                    k = 0;
                    --i;
                    ++j;
                }
            }
            else {
                if (text_lines[i][j] == search[0]) {
                    found = true;
                    ++k;
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
