// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    vector<string> patterns;
    int j = 0;
    while (j < text_lines[0].size()) {
        string s = "";
        while (j < text_lines[0].size() && text_lines[0][j] != ',') s.push_back(text_lines[0][j++]);
        j += 2;
        patterns.push_back(s);
    }
    //for (string s : patterns) cout << s << " ";
    //cout << endl;

    vector<string> designs;
    for (int i = 2; i < text_lines.size(); ++i) {
        designs.push_back(text_lines[i]);
    }

    sort(patterns.begin(), patterns.end());

    unordered_map<char, vector<string>> m_patt;
    for (string s : patterns) {
        m_patt[s[0]].push_back(s);
    }

    //vector<char> letters = { 'b', 'g', 'r', 'u', 'w'};

    int res = 0;
    for (string s : designs) {
        int n = s.size();
        vector<bool> visited(n, false);
        queue<int> q; // positions to check in the designs
        q.push(0);
        while (!q.empty()) {
            int pos = q.front();
            q.pop();

            bool ended = false;
            for (string s2 : m_patt[s[pos]]) {
                int j = pos;
                bool equal = true;
                for (char c : s2) {
                    if (j >= n) {
                        equal = false;
                        break;
                    }
                    if (c != s[j]) equal = false;
                    ++j;
                }
                if (equal) {
                    if (pos + s2.size() == n) {
                        ++res;
                        ended = true;
                        break;
                    }
                    else {
                        if (!visited[pos + s2.size()]) {
                            visited[pos + s2.size()] = true;
                            q.push(pos + s2.size());
                        }
                    }
                }
            }
            if (ended) break;
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<string> patterns;
    int j = 0;
    while (j < text_lines[0].size()) {
        string s = "";
        while (j < text_lines[0].size() && text_lines[0][j] != ',') s.push_back(text_lines[0][j++]);
        j += 2;
        patterns.push_back(s);
    }
    //for (string s : patterns) cout << s << " ";
    //cout << endl;

    vector<string> designs;
    for (int i = 2; i < text_lines.size(); ++i) {
        designs.push_back(text_lines[i]);
    }

    sort(patterns.begin(), patterns.end());

    unordered_map<char, vector<string>> m_patt;
    for (string s : patterns) {
        m_patt[s[0]].push_back(s);
    }

    //vector<char> letters = { 'b', 'g', 'r', 'u', 'w'};

    long long res = 0;
    for (string s : designs) {
        int n = s.size();
        vector<bool> visited(n+1, false);
        vector<long long> nums(n+1, 0);
        nums[0] = 1;
        priority_queue<int, vector<int>, greater<int>> q; // positions to check in the designs
        q.push(0);
        while (!q.empty()) {
            int pos = q.top();
            q.pop();

            for (string s2 : m_patt[s[pos]]) {
                int j = pos;
                bool equal = true;
                for (char c : s2) {
                    if (j >= n) {
                        equal = false;
                        break;
                    }
                    if (c != s[j]) equal = false;
                    ++j;
                }
                if (equal) {
                    int npos = pos + s2.size();
                    
                    nums[npos] += nums[pos];

                    if (npos < n && !visited[npos]) {
                        visited[npos] = true;
                        q.push(npos);
                    }
                }
            }
        }
        res += nums.back();
        //cout << nums.back() << " - ";
    }
    //cout << endl;
    cout << "res: " << res << endl;
}

int main()
{
    //ifstream f("test.txt");
    ifstream f("input.txt"); // 724388733465031

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
