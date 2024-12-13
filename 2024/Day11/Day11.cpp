// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include<math.h>

using namespace std;

static void first(vector<string>& text_lines, int blinks)
{
    using ull = unsigned long long;

    list<ull> nums;
    string s = "";
    for (int i = 0; i < text_lines[0].size(); ++i) {
        if (text_lines[0][i] == ' ') {
            nums.push_back(stoll(s));
            s = "";
        }
        else {
            s.push_back(text_lines[0][i]);
        }
    }
    nums.push_back(stoll(s));

    //cout << nums.size() << endl;
    //for (auto it = nums.begin(); it != nums.end(); ++it) cout << *it << " ";
    //cout << endl;

    ull res = 0;

    for (auto it1 = nums.begin(); it1 != nums.end(); ++it1) {
        unordered_map<ull, ull> m;
        m[*it1] = 1;

        for (int b = 0; b < blinks; ++b) {
            unordered_map<ull, ull> new_m;
            for (auto it = m.begin(); it != m.end(); ++it) {
                ull num = it->first, c = it->second;

                if (num == 0) {
                    new_m[1] += c;
                }
                else {
                    int digits = 0;
                    ull t = num;
                    while (t > 0) {
                        t = t / 10;
                        ++digits;
                    }
                    //cout << *it << " -> digits: " << digits << endl;
                    if (digits % 2 == 0) {
                        ull t2 = num, sep = (ull)(pow(10, (digits / 2)));
                        new_m[t2 % sep] += c;
                        new_m[t2 / sep] += c;
                    }
                    else {
                        new_m[num * 2024] += c;
                    }
                }
            }

            m = new_m;
        }

        for (auto it = m.begin(); it != m.end(); ++it) res += it->second;
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




    //first(text_lines, 25);
    first(text_lines, 75);



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
