// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static void first(vector<string>& text_lines)
{
    vector<int> left;
    vector<int> right;

    for (int i = 0; i < text_lines.size(); ++i) {
        int pos = text_lines[i].find(' ');
        left.push_back(atoi(text_lines[i].substr(0, pos).c_str()));
        right.push_back(atoi(text_lines[i].substr(pos + 1).c_str()));
    }


    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int res = 0;

    for (int i = 0; i < left.size(); ++i) {
        res += abs(left[i] - right[i]);
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<int> left;
    vector<int> right;

    for (int i = 0; i < text_lines.size(); ++i) {
        int pos = text_lines[i].find(' ');
        left.push_back(atoi(text_lines[i].substr(0, pos).c_str()));
        right.push_back(atoi(text_lines[i].substr(pos + 1).c_str()));
    }


    unordered_map<int, int> l;
    unordered_map<int, int> r;

    for (int i = 0; i < left.size(); ++i) {
        ++l[left[i]];
        ++r[right[i]];
    }

    int res = 0;
    for (auto it = l.begin(); it != l.end(); ++it) {
        res += it->first * r[it->first] * it->second;
    }
    cout << "res: " << res << endl;
}

int main()
{
    //ifstream f("test.txt");
    ifstream f("input1.txt");

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
    while(getline(f, s)) {
        text_lines.push_back(s);
        //cout << s << endl;
    }
    // Close the file
    f.close();


    cout << text_lines.size() << endl;

    


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
