// Day22.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

long long calculateNextSecret(long long s) {
    s = s ^ (s << 6);
    s = s % (1 << 24);
    s = s ^ (s >> 5);
    s = s % (1 << 24);
    s = s ^ (s << 11);
    s = s % (1 << 24);
    return s;
}

static void first(vector<string>& text_lines)
{
    int n = text_lines.size();
    vector<long long> initial_secrets;
    for (string s : text_lines) initial_secrets.push_back(stoll(s));

    //for (int i = 0; i < n; ++i) cout << initial_secrets[i] << endl;

    vector<long long> secrets(n);
    for (int i = 0; i < n; ++i) secrets[i] = initial_secrets[i];

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < 2000; ++k) secrets[i] = calculateNextSecret(secrets[i]);
    }

    //for (int i = 0; i < n; ++i) {
    //    cout << initial_secrets[i] << " -> " << secrets[i] << endl;
    //}

    long long res = 0;
    for (int i = 0; i < n; ++i) res += secrets[i];
    cout << "res: " << res << endl;
}

char translateForMap(int num) {
    if (num < 0) {
        return 'a' + (-num - 1);
    }
    else {
        return '0' + num;
    }
}

static void second(vector<string>& text_lines)
{
    int loops = 2000;
    int n = text_lines.size();
    vector<long long> initial_secrets;
    for (string s : text_lines) initial_secrets.push_back(stoll(s));

    //for (int i = 0; i < n; ++i) cout << initial_secrets[i] << endl;

    vector<long long> secrets(n);
    for (int i = 0; i < n; ++i) secrets[i] = initial_secrets[i];

    vector<unordered_map<string, int>> changes(n);
    for (int i = 0; i < n; ++i) {
        vector<long long> ss(loops+1);
        ss[0] = initial_secrets[i] % 10;
        for (int k = 0; k < loops; ++k) {
            secrets[i] = calculateNextSecret(secrets[i]);
            ss[k + 1] = secrets[i] % 10;
        }

        for (int k = 0; k + 4 < loops+1; ++k) {
            //cout << ss[k];
            //if (k != 0) cout << " " << ss[k] - ss[k-1];
            //cout << endl;

            string val = "0000";

            for (int h = 0; h < 4; ++h) val[h] = translateForMap(ss[k+1 + h] - ss[k + h]);
            
            if (changes[i].count(val) == 0) changes[i][val] = ss[k+4];
        }

        //for(auto it=changes[i].begin(); it != changes[i].end(); ++it) cout << it->first << " -> " << it->second << endl;
    }

    cout << "fusing" << endl;
    for (int i = 1; i < n; ++i) {
        for (auto it = changes[i].begin(); it != changes[i].end(); ++it) {
            changes[0][it->first] += it->second;
        }
    }

    string max_s;
    int max_val = 0;
    for (auto it = changes[0].begin(); it != changes[0].end(); ++it) {
        if (it->second > max_val) {
            max_val = it->second;
            max_s = it->first;
        }
    }

    cout << "res: " << max_val << " <- " << max_s << endl;
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
