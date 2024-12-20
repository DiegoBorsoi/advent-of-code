// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int getComboVal(int val, vector<int>& regs) {
    if (val < 4) return val;
    else {
        val -= 4;
        return regs[val];
    }
}

static void first(vector<string>& text_lines)
{
    vector<int> regs;
    string s, num;

    for (int i = 0; i < 3; ++i) {
        s = text_lines[i];
        num = "";
        int j = 12;
        while (j < s.size()) num.push_back(s[j++]);
        regs.push_back(stoi(num));
    }

    vector<int> instr;
    s = text_lines[4];
    int j = 9;
    while (j < s.size()) {
        instr.push_back(s[j] - '0');
        j += 2;
    }

    cout << "regs: ";
    for (int t : regs) cout << t << " ";
    cout << endl;
    cout << "instr: ";
    for (int t : instr) cout << t << " ";
    cout << endl;


    string res = "";
    int pointer = 0;
    while (pointer < instr.size()) {
        int val;
        switch (instr[pointer]) {
            case 0: // division in A
                val = getComboVal(instr[pointer+1], regs);
                regs[0] = regs[0] / (1 << val);
                pointer += 2;
                break;
            case 1: // bitwise xor literal
                regs[1] = regs[1] ^ instr[pointer + 1];
                pointer += 2;
                break;
            case 2: // combo modulo
                val = getComboVal(instr[pointer + 1], regs);
                regs[1] = val % 8;
                pointer += 2;
                break;
            case 3: // jump jnz
                if (regs[0] != 0) {
                    pointer = instr[pointer + 1];
                }
                else {
                    pointer += 2;
                }
                break;
            case 4: // bitwise xor regs
                regs[1] = regs[1] ^ regs[2];
                pointer += 2;
                break;
            case 5: // out
                val = getComboVal(instr[pointer + 1], regs);
                val = val % 8;
                res.push_back('0' + val);
                res.push_back(',');
                pointer += 2;
                break;
            case 6: // division in B
                val = getComboVal(instr[pointer + 1], regs);
                regs[1] = regs[0] / (1 << val);
                pointer += 2;
                break;
            case 7: // division in C
                val = getComboVal(instr[pointer + 1], regs);
                regs[2] = regs[0] / (1 << val);
                pointer += 2;
                break;
        }
        //cout << "regs: ";
        //for (int t : regs) cout << t << " ";
        //cout << endl;
    }
    if (res.size() > 0) res.pop_back();

    cout << "res: " << res << endl;
}

vector<int> f(long long n) {
    std::vector<int> output;
    long long a = n;
    long long b = 0;
    long long c = 0;
    do {
        b = a % 8;
        b = b ^ 2;
        c = a / static_cast<long long>(std::pow(2, b));
        b = b ^ c;
        b = b ^ 3;
        output.push_back(b % 8);
        a = a / 8;
    } while (a != 0);
    return output;
}

bool util(long long n, vector<int>& instr) {
    vector<int> t = f(n);
    if (t.size() == instr.size() && t == instr) {
        std::cout << "res: " << n << '\n';
        return true;
    }
    n = n << 3;
    for (int i = 0; i < 8; ++i) {
        vector<int> output = f(n);
        bool same = true;
        for (int j = 0; j < output.size(); ++j) {
            same = same && output[j] == instr[instr.size() - output.size() + j];
        }
        if (same && util(n, instr)) return true;
        n++;
    }
    return false;
}

static void second(vector<string>& text_lines)
{
    vector<int> regs;
    string s, num;

    for (int i = 0; i < 3; ++i) {
        s = text_lines[i];
        num = "";
        int j = 12;
        while (j < s.size()) num.push_back(s[j++]);
        regs.push_back(stoi(num));
    }

    vector<int> instr;
    s = text_lines[4];
    int j = 9;
    while (j < s.size()) {
        instr.push_back(s[j] - '0');
        j += 2;
    }

    cout << "regs: ";
    for (int t : regs) cout << t << " ";
    cout << endl;
    cout << "instr: ";
    for (int t : instr) cout << t << " ";
    cout << endl;


    util(0, instr);
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
