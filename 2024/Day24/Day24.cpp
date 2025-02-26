// Day24.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    unordered_map<string, int> wires; // 0 or 1, -1 means not value
    
    vector<string> gates_type; // AND, OR, XOR
    vector<vector<string>> gates_inputs;
    vector<string> gates_output;

    bool on_gates = false;
    for (string s : text_lines) {
        if (s == "") {
            on_gates = true;
            continue;
        }

        if (!on_gates) {
            // get x and y values
            int p = 0;
            string w = "";
            while (s[p] != ':') w.push_back(s[p++]);

            wires[w] = (s[5] == '1') ? 1 : 0;
        }
        else {
            // get a gate
            int p = 0;
            string w1 = "";
            while (s[p] != ' ') w1.push_back(s[p++]);
            ++p;
            string gt = "";
            while (s[p] != ' ') gt.push_back(s[p++]);
            ++p;
            string w2 = "";
            while (s[p] != ' ') w2.push_back(s[p++]);
            p += 4;
            string r = "";
            for (int i = 0; i < 3; ++i) r.push_back(s[p++]);

            gates_type.push_back(gt);
            gates_inputs.push_back({w1,w2});
            gates_output.push_back(r);
        }
    }

    int n = gates_type.size();

    //for (auto it = wires.begin(); it != wires.end(); ++it) cout << it->first << " = " << it->second << endl;
    //for (int i = 0; i < n; ++i) cout << gates_type[i] << ": " << gates_inputs[i][0] << " + " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;

    vector<int> gates_actives = vector<int>(n,0); // 0 <= val <= 2, if == 2 than it can be processed
    unordered_map<string, vector<int>> wire_to_gates;

    queue<int> gates_to_process;
    for (int i = 0; i < n; ++i) {
        wire_to_gates[gates_inputs[i][0]].push_back(i);
        if (gates_inputs[i][0][0] == 'x' || gates_inputs[i][0][0] == 'y') ++gates_actives[i];

        wire_to_gates[gates_inputs[i][1]].push_back(i);
        if (gates_inputs[i][1][0] == 'x' || gates_inputs[i][1][0] == 'y') ++gates_actives[i];

        if (gates_actives[i] == 2) gates_to_process.push(i);
    }

    while (!gates_to_process.empty()) {
        int gate = gates_to_process.front();
        gates_to_process.pop();

        string gt = gates_type[gate];
        if (gt == "AND") {
            int r = 0;
            if (wires[gates_inputs[gate][0]] == 1 && wires[gates_inputs[gate][1]] == 1) r = 1;
            
            wires[gates_output[gate]] = r;

            for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                ++gates_actives[gate_to_update];

                if(gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
            }
        }
        else if (gt == "OR") {
            int r = 0;
            if (wires[gates_inputs[gate][0]] == 1 || wires[gates_inputs[gate][1]] == 1) r = 1;

            wires[gates_output[gate]] = r;

            for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                ++gates_actives[gate_to_update];

                if (gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
            }
        }
        else if (gt == "XOR") {
            int r = 1;
            if (wires[gates_inputs[gate][0]] == wires[gates_inputs[gate][1]]) r = 0;

            wires[gates_output[gate]] = r;

            for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                ++gates_actives[gate_to_update];

                if (gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
            }
        }
        else {
            cout << "error: wrong gate type ------------------------------------------" << endl;
        }
    }

    int z_len = 0;
    unordered_map<int, int> z_set;
    for (auto it = wires.begin(); it != wires.end(); ++it) {
        if (it->first[0] == 'z') {
            string s = "  ";
            s[0] = it->first[1];
            s[1] = it->first[2];

            int val = stoi(s);
            z_set[val] = it->second;

            if (val > z_len) z_len = val;
        }
    }

    long long res = 0;
    while (z_len >= 0) {
        res = (res << 1) + z_set[z_len];
        --z_len;
    }
    cout << "res: " << res << endl;
}



static void second(vector<string>& text_lines)
{
    unordered_map<string, int> wires_base; // 0 or 1, -1 means not value

    vector<string> gates_type; // AND, OR, XOR
    vector<vector<string>> gates_inputs;
    vector<string> gates_output;

    bool on_gates = false;
    for (string s : text_lines) {
        if (s == "") {
            on_gates = true;
            continue;
        }

        if (!on_gates) {
            // get x and y values
            int p = 0;
            string w = "";
            while (s[p] != ':') w.push_back(s[p++]);

            wires_base[w] = (s[5] == '1') ? 1 : 0;
        }
        else {
            // get a gate
            int p = 0;
            string w1 = "";
            while (s[p] != ' ') w1.push_back(s[p++]);
            ++p;
            string gt = "";
            while (s[p] != ' ') gt.push_back(s[p++]);
            ++p;
            string w2 = "";
            while (s[p] != ' ') w2.push_back(s[p++]);
            p += 4;
            string r = "";
            for (int i = 0; i < 3; ++i) r.push_back(s[p++]);

            gates_type.push_back(gt);
            gates_inputs.push_back({ w1,w2 });
            gates_output.push_back(r);
        }
    }

    int n = gates_type.size();

    //for (auto it = wires.begin(); it != wires.end(); ++it) cout << it->first << " = " << it->second << endl;
    //for (int i = 0; i < n; ++i) cout << gates_type[i] << ": " << gates_inputs[i][0] << " + " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;

    // change x values
    //wires_base["y31"] = (wires_base["y31"] + 1) % 2;


    //calculate x
    int x_len = 0;
    unordered_map<int, int> x_set;
    for (auto it = wires_base.begin(); it != wires_base.end(); ++it) {
        if (it->first[0] == 'x') {
            string s = "  ";
            s[0] = it->first[1];
            s[1] = it->first[2];

            int val = stoi(s);
            x_set[val] = it->second;

            if (val > x_len) x_len = val;
        }
    }

    long long x_input = 0;
    while (x_len >= 0) {
        x_input = (x_input << 1) + x_set[x_len];
        --x_len;
    }
    cout << "x = " << x_input << endl;

    //calculate y
    int y_len = 0;
    unordered_map<int, int> y_set;
    for (auto it = wires_base.begin(); it != wires_base.end(); ++it) {
        if (it->first[0] == 'y') {
            string s = "  ";
            s[0] = it->first[1];
            s[1] = it->first[2];

            int val = stoi(s);
            y_set[val] = it->second;

            if (val > y_len) y_len = val;
        }
    }

    long long y_input = 0;
    while (y_len >= 0) {
        y_input = (y_input << 1) + y_set[y_len];
        --y_len;
    }
    cout << "y = " << y_input << endl;





    // find XOR gate not on output z**
    vector<int> wrong_xor;
    for (int i = 0; i < n; ++i) {
        if (gates_type[i] == "XOR") {
            if (!((gates_inputs[i][0][0] == 'x' && gates_inputs[i][1][0] == 'y') || (gates_inputs[i][0][0] == 'y' && gates_inputs[i][1][0] == 'x') || (gates_output[i][0] == 'z'))) {
                //cout << gates_inputs[i][0] << " " << gates_type[i] << " " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;
                wrong_xor.push_back(i);
            }
        }
    }
    cout << endl;
    for(int i : wrong_xor) cout << "gate " << i << " = " << gates_inputs[i][0] << " " << gates_type[i] << " " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;

    vector<int> wrong_z;
    // find output z** not on XOR (and not last gate z45)
    for (int i = 0; i < n; ++i) {
        if ((gates_output[i][0] == 'z') && (gates_type[i] != "XOR") && (gates_output[i] != "z45")) {
            //cout << gates_inputs[i][0] << " " << gates_type[i] << " " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;
            wrong_z.push_back(i);
        }
    }
    cout << endl;
    for (int i : wrong_z) cout << "gate " << i << " = " << gates_inputs[i][0] << " " << gates_type[i] << " " << gates_inputs[i][1] << " -> " << gates_output[i] << endl;
    cout << endl;


    vector<vector<vector<int>>> swap_poses = { {{0,0}, {1,1}, {2,2}}, {{0,0}, {1,2}, {2,1}}, 
                                               {{0,1}, {1,0}, {2,2}}, {{0,1}, {1,2}, {2,0}}, 
                                               {{0,2}, {1,0}, {2,1}}, {{0,2}, {1,1}, {2,0}} };

    // the right swap is {{0,1}, {1,2}, {2,0}}
    swap(gates_output[wrong_xor[0]], gates_output[wrong_z[1]]);
    swap(gates_output[wrong_xor[1]], gates_output[wrong_z[2]]);
    swap(gates_output[wrong_xor[2]], gates_output[wrong_z[0]]);

    // find the last swap
    // swap output wires
    for (int g1 = 0; g1 < n-1; ++g1) {
        for (int g2 = g1 + 1; g2 < n; ++g2) {
            if (gates_output[g1][0] == 'z' || gates_output[g2][0] == 'z') continue;

            swap(gates_output[g1], gates_output[g2]);



            unordered_map<string, int> wires;
            for (auto it = wires_base.begin(); it != wires_base.end(); ++it) {
                wires[it->first] = it->second;
            }

            vector<int> gates_actives = vector<int>(n, 0); // 0 <= val <= 2, if == 2 than it can be processed
            unordered_map<string, vector<int>> wire_to_gates;


            queue<int> gates_to_process;
            for (int i = 0; i < n; ++i) {
                wire_to_gates[gates_inputs[i][0]].push_back(i);
                if (gates_inputs[i][0][0] == 'x' || gates_inputs[i][0][0] == 'y') ++gates_actives[i];

                wire_to_gates[gates_inputs[i][1]].push_back(i);
                if (gates_inputs[i][1][0] == 'x' || gates_inputs[i][1][0] == 'y') ++gates_actives[i];

                if (gates_actives[i] == 2) gates_to_process.push(i);
            }


            while (!gates_to_process.empty()) {
                int gate = gates_to_process.front();
                gates_to_process.pop();


                string gt = gates_type[gate];
                if (gt == "AND") {
                    int r = 0;
                    if (wires[gates_inputs[gate][0]] == 1 && wires[gates_inputs[gate][1]] == 1) r = 1;

                    wires[gates_output[gate]] = r;

                    for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                        ++gates_actives[gate_to_update];

                        if (gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
                    }
                }
                else if (gt == "OR") {
                    int r = 0;
                    if (wires[gates_inputs[gate][0]] == 1 || wires[gates_inputs[gate][1]] == 1) r = 1;

                    wires[gates_output[gate]] = r;

                    for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                        ++gates_actives[gate_to_update];

                        if (gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
                    }
                }
                else if (gt == "XOR") {
                    int r = 1;
                    if (wires[gates_inputs[gate][0]] == wires[gates_inputs[gate][1]]) r = 0;

                    wires[gates_output[gate]] = r;

                    for (int gate_to_update : wire_to_gates[gates_output[gate]]) {
                        ++gates_actives[gate_to_update];

                        if (gates_actives[gate_to_update] == 2) gates_to_process.push(gate_to_update);
                    }
                }
                else {
                    cout << "error: wrong gate type ------------------------------------------" << endl;
                }
            }


            int z_len = 0;
            unordered_map<int, int> z_set;
            for (auto it = wires.begin(); it != wires.end(); ++it) {
                if (it->first[0] == 'z') {
                    string s = "  ";
                    s[0] = it->first[1];
                    s[1] = it->first[2];

                    int val = stoi(s);
                    z_set[val] = it->second;

                    if (val > z_len) z_len = val;
                }
            }

            long long res = 0;
            while (z_len >= 0) {
                res = (res << 1) + z_set[z_len];
                --z_len;
            }
            //cout << "res: " << res << endl;
            long long right_res = x_input + y_input;
            //cout << "rre: " << right_res << endl;

            if (res == right_res) {
                cout << "found the last wires: " << gates_output[g2] << " (" << gates_type[g1] << ") - " << gates_output[g1] << " (" << gates_type[g2] << ")" << endl;
            }




            // reset gate output swapped
            swap(gates_output[g1], gates_output[g2]);
        }
    }



    // possible last wires
    vector<string> wires_to_swap_res = {"rwq", "fvm", "cph", "jqn", "htg", "gjq"};

    /*
    found the last wires: jqn (AND) - cph (XOR) <- it's the right one, why? i don't know...
    found the last wires: fvm (XOR) - htg (AND)
    found the last wires: fvm (XOR) - gjq (AND)
    found the last wires: cph (XOR) - htg (AND)
    found the last wires: cph (XOR) - gjq (AND)
    */
}

static void aux()
{
    vector<string> res = {"kwb", "qkf", "tgr", "z24", "z12", "z16", "jqn", "cph" };

    sort(res.begin(), res.end());

    for (string s : res) {
        cout << s << ",";
    }
    cout << endl;
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
    //second(text_lines);
    aux();



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
