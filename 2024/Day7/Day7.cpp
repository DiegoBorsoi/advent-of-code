// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

using namespace std;

bool testOperations(vector<long long>& nums, int idx, long long result, long long acc)
{
    if (idx == nums.size()) return result == acc;

    return testOperations(nums, idx + 1, result, acc * nums[idx]) || testOperations(nums, idx + 1, result, acc + nums[idx]);
}

static void first(vector<string>& text_lines)
{
    long long res = 0;

    for (string s : text_lines) {
        string t = "";
        int i = 0;
        while (s[i] != ':') t.push_back(s[i++]);
        i += 2;

        long long op_res = stoll(t.c_str());
        vector<long long> terms;
        while (i < s.size()) {
            t = "";
            while(i < s.size() && s[i] != ' ') t.push_back(s[i++]);
            terms.push_back(stoll(t.c_str()));
            ++i;
        }

        //cout << " ------------------------------------------- " << endl;
        if (testOperations(terms, 1, op_res, terms[0])) {
            res += op_res;
            //cout << op_res << endl;
        }

    }

    cout << "res: " << res << endl;
}

bool testOperations2(vector<long long>& nums, int idx, long long result, long long acc)
{
    //cout << acc << endl;
    if (idx == nums.size()) return result == acc;
    else if (result < acc) return false;

    //cout << acc << " + " << nums[idx] << " -> " << endl; cout << stoll(to_string(acc) + to_string(nums[idx])) << endl;
    return testOperations2(nums, idx + 1, result, stoll(to_string(acc) + to_string(nums[idx])))
            || testOperations2(nums, idx + 1, result, acc * nums[idx])
            || testOperations2(nums, idx + 1, result, acc + nums[idx]);
}

static void second(vector<string>& text_lines)
{
    long long res = 0;

    for (string s : text_lines) {
        string t = "";
        int i = 0;
        while (s[i] != ':') t.push_back(s[i++]);
        i += 2;

        long long op_res = stoll(t);
        vector<long long> terms;
        while (i < s.size()) {
            t = "";
            while (i < s.size() && s[i] != ' ') t.push_back(s[i++]);
            terms.push_back(stoll(t));
            ++i;
        }

        //cout << " ------------------------------------------- " << endl;
        if (testOperations2(terms, 1, op_res, terms[0])) {
            res += op_res;
            //cout << res << endl;
            //cout << op_res << endl;
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
