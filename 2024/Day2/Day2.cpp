// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    vector<vector<int>> reports;
    reports.resize(text_lines.size());

    for (int i = 0; i < text_lines.size(); ++i) {
        string s = "";
        for (int j = 0; j < text_lines[i].size(); ++j) {
            if (text_lines[i][j] == ' ') {
                reports[i].push_back(atoi(s.c_str()));
                s = "";
            }
            else {
                s.push_back(text_lines[i][j]);
            }
        }
        reports[i].push_back(atoi(s.c_str()));
    }

    int res = 0;
    for (int i = 0; i < reports.size(); ++i) {
        bool right_diff = true;
        for (int j = 0; j < reports[i].size() - 1; ++j) {
            if (reports[i][j] == reports[i][j + 1] || abs(reports[i][j] - reports[i][j + 1]) > 3) {
                right_diff = false;
                break;
            }
        }
        if (!right_diff) continue;


        bool right_order = true;
        if (reports[i][0] < reports[i][1]) {
            for (int j = 1; j < reports[i].size() - 1; ++j) {
                if (reports[i][j] > reports[i][j + 1]) {
                    right_order = false;
                    break;
                }
            }
        }
        else {
            for (int j = 1; j < reports[i].size() - 1; ++j) {
                if (reports[i][j] < reports[i][j + 1]) {
                    right_order = false;
                    break;
                }
            }
        }

        if (right_order) ++res;
    }

    std::cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<vector<int>> reports;
    reports.resize(text_lines.size());

    for (int i = 0; i < text_lines.size(); ++i) {
        string s = "";
        for (int j = 0; j < text_lines[i].size(); ++j) {
            if (text_lines[i][j] == ' ') {
                reports[i].push_back(atoi(s.c_str()));
                s = "";
            }
            else {
                s.push_back(text_lines[i][j]);
            }
        }
        reports[i].push_back(atoi(s.c_str()));
    }

    int res = 0;
    for (int i = 0; i < reports.size(); ++i) {
        bool right = true, error = false;
        // test descending
        for (int h=0, j = 1; j < reports[i].size(); ++h, ++j) {
            if (reports[i][h] <= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3) {
                if (!error) {
                    error = true;
                    ++j;
                    if (j < reports[i].size() && 
                        (reports[i][h] <= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3)) {
                        right = false;
                        break;
                    }
                    ++h;
                }
                else {
                    right = false;
                    break;
                }
            }
        }
        if (right == true) {
            ++res;
            continue;
        }

        right = true, error = true;
        // test descending (without first element)
        for (int h = 1, j = 2; j < reports[i].size(); ++h, ++j) {
            if (reports[i][h] <= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3) {
                right = false;
                break;
            }
        }
        if (right == true) {
            ++res;
            continue;
        }

        right = true, error = false;
        // test ascending
        for (int h = 0, j = 1; j < reports[i].size(); ++h, ++j) {
            if (reports[i][h] >= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3) {
                if (!error) {
                    error = true;
                    ++j;
                    if (j < reports[i].size() && (reports[i][h] >= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3)) {
                        right = false;
                        break;
                    }
                    ++h;
                }
                else {
                    right = false;
                    break;
                }
            }
        }
        if (right == true) {
            ++res;
            continue;
        }
        //else {
        //    for (int k = 0; k < reports[i].size(); ++k) cout << reports[i][k] << " - ";
        //    cout << endl;
        //}

        right = true, error = true;
        // test ascending (without first element)
        for (int h = 1, j = 2; j < reports[i].size(); ++h, ++j) {
            if (reports[i][h] >= reports[i][j] || abs(reports[i][h] - reports[i][j]) < 1 || abs(reports[i][h] - reports[i][j]) > 3) {
                right = false;
                break;
            }
        }
        if (right == true) {
            ++res;
        }
    }

    std::cout << "res: " << res << endl;
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
