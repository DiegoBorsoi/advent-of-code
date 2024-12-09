// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <regex>

using namespace std;

static void first(vector<string>& text_lines)
{
    int res = 0;
    for (string s : text_lines) {
        smatch matches;
        regex my_regex("mul\\(\\d{1,3},\\d{1,3}\\)");

        while (regex_search(s, matches, my_regex)) {
            //cout << matches[0] << endl;
            string m = matches[0].str();
            int i = 0;
            while (m[i] != '(') ++i;
            ++i;
            string n1 = "";
            while (m[i] != ',') {
                n1.push_back(m[i]);
                ++i;
            }
            ++i;
            string n2 = "";
            while (m[i] != ')') {
                n2.push_back(m[i]);
                ++i;
            }

            //cout << n1 << " - " << n2 << endl;

            res += atoi(n1.c_str()) * atoi(n2.c_str());

            s = matches.suffix().str();
        }
    }

    std::cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    vector<pair<int, int>> muls;
    vector<int> does;
    vector<int> donts;
    int start_pos = 0;
    for (string s : text_lines) {
        string to_search = s;
        smatch matches;
        int position_shift = start_pos;

        // get mul operators with positions
        regex mul_regex("mul\\(\\d{1,3},\\d{1,3}\\)");

        while (regex_search(to_search, matches, mul_regex)) {
            //cout << matches[0] << endl;
            string m = matches[0].str();
            int i = 0;
            while (m[i] != '(') ++i;
            ++i;
            string n1 = "";
            while (m[i] != ',') {
                n1.push_back(m[i]);
                ++i;
            }
            ++i;
            string n2 = "";
            while (m[i] != ')') {
                n2.push_back(m[i]);
                ++i;
            }

            //cout << n1 << " - " << n2 << endl;

            muls.push_back(make_pair(position_shift + matches.position(), atoi(n1.c_str()) * atoi(n2.c_str())));

            position_shift += matches.position() + matches.length();

            to_search = matches.suffix().str();
        }

        to_search = s;
        position_shift = start_pos;
        // get do operators with positions
        regex do_regex("do\\(\\)");

        while (regex_search(to_search, matches, do_regex)) {
            does.push_back(position_shift + matches.position());

            position_shift += matches.position() + matches.length();

            to_search = matches.suffix().str();
        }

        to_search = s;
        position_shift = start_pos;
        // get don't operators with positions
        regex dont_regex("don't\\(\\)");

        while (regex_search(to_search, matches, dont_regex)) {
            donts.push_back(position_shift + matches.position());

            position_shift += matches.position() + matches.length();

            to_search = matches.suffix().str();
        }

        start_pos += s.size();
    }


    int a = 0, b = 0;
    vector<pair<int, int>> fact;
    while (a < does.size() && b < donts.size()) {
        if (does[a] < donts[b]) {
            fact.push_back(make_pair(does[a], 1));
            ++a;
        }
        else {
            fact.push_back(make_pair(donts[b], 0));
            ++b;
        }
    }

    if (a == does.size()) while (b < donts.size()) fact.push_back(make_pair(donts[b++], 0));
    else if(b == donts.size()) while(a < does.size()) fact.push_back(make_pair(does[a++], 1));

    //cout << does.size() << " - " << donts.size() << " - " << fact.size() << endl;

    int res = 0, factor = 1;
    for (int i = 0, j = 0; i < muls.size(); ++i) {
        while (j < fact.size() && fact[j].first < muls[i].first) {
            factor = fact[j].second;
            ++j;
        }
        //cout << factor << endl;
        res += factor * muls[i].second;
    }

    std::cout << "res: " << res << endl;
}

int main()
{
    //ifstream f("test1.txt");
    //ifstream f("test2.txt");
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
