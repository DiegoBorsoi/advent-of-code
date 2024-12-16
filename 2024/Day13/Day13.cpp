// Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void first(vector<string>& text_lines, bool second)
{
    vector<pair<int, int>> btnA;
    vector<pair<int, int>> btnB;
    vector<pair<long long, long long>> prizes;
    for (int i = 0; i < text_lines.size(); i += 4) {
        string s = text_lines[i];
        int j = 0;
        while (s[j] != '+') ++j;
        ++j;
        string x = "";
        while (s[j] != ',') x.push_back(s[j++]);
        j += 4;
        string y = "";
        while (j < s.size()) y.push_back(s[j++]);
        btnA.push_back(make_pair(stoi(x), stoi(y)));

        s = text_lines[i+1];
        j = 0;
        while (s[j] != '+') ++j;
        ++j;
        x = "";
        while (s[j] != ',') x.push_back(s[j++]);
        j += 4;
        y = "";
        while (j < s.size()) y.push_back(s[j++]);
        btnB.push_back(make_pair(stoi(x), stoi(y)));
        
        s = text_lines[i + 2];
        j = 0;
        while (s[j] != '=') ++j;
        ++j;
        x = "";
        while (s[j] != ',') x.push_back(s[j++]);
        j += 4;
        y = "";
        while (j < s.size()) y.push_back(s[j++]);
        prizes.push_back(make_pair(stoll(x) + (second ? 10000000000000 : 0), stoll(y) + (second ? 10000000000000 : 0)));
    }
    int n = prizes.size();

    //for (int i = 0; i < n; ++i) cout << "(" << btnA[i].first << " - " << btnA[i].second << ") " << "(" << btnB[i].first << " - " << btnB[i].second << ") = " << "(" << prizes[i].first << " - " << prizes[i].second << ") " << endl;
    
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        long long k2 = (btnA[i].second * prizes[i].first - btnA[i].first * prizes[i].second) / (btnB[i].first * btnA[i].second - btnA[i].first * btnB[i].second);
        long long k1 = (prizes[i].second - k2 * btnB[i].second) / btnA[i].second;

        if (btnA[i].first * k1 + k2 * btnB[i].first == prizes[i].first && btnA[i].second * k1 + k2 * btnB[i].second == prizes[i].second) {
            res += k1 * 3 + k2;
            //cout << i << " -> " << k1 << " - " << k2 << endl;
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




    //first(text_lines, false);
    first(text_lines, true);



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
