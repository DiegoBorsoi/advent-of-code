// Day23.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    unordered_map<string, int> nodes;
    int c = 0;
    for (string s : text_lines) {
        string n1 = "";
        n1.push_back(s[0]);
        n1.push_back(s[1]);
        string n2 = "";
        n2.push_back(s[3]);
        n2.push_back(s[4]);

        if (nodes.count(n1) == 0) {
            nodes[n1] = c;
            ++c;
        }
        if (nodes.count(n2) == 0) {
            nodes[n2] = c;
            ++c;
        }
    }
    //for (auto it = nodes.begin(); it != nodes.end(); ++it) cout << it->first << " -> " << it->second << endl;

    int n = nodes.size();
    //cout << "size: " << n << endl;

    vector<vector<int>> edges(n);
    vector<string> node_names(n);
    for (string s : text_lines) {
        string n1 = "";
        n1.push_back(s[0]);
        n1.push_back(s[1]);
        string n2 = "";
        n2.push_back(s[3]);
        n2.push_back(s[4]);

        edges[nodes[n1]].push_back(nodes[n2]);
        edges[nodes[n2]].push_back(nodes[n1]);

        node_names[nodes[n1]] = n1;
        node_names[nodes[n2]] = n2;
    }

    //for (int i = 0; i < n; ++i) {
    //    cout << i << " -> [";
    //    for (int j = 0; j < edges[i].size(); ++j) cout << edges[i][j] << " ";
    //    cout << "]" << endl;
    //}

vector<int> order(n);
for (int i = 0; i < n; ++i) order[i] = i;

sort(order.begin(), order.end(), [&edges](int a, int b) { return edges[a].size() > edges[b].size(); });

int res = 0;
for (int i = 0; i < n; ++i) {
    int first = order[i];
    for (int j = 0; j < edges[first].size(); ++j) {
        int second = edges[first][j];
        if (second < first) {
            for (int k = 0; k < edges[second].size(); ++k) {
                int third = edges[second][k];
                if (third < second) {
                    for (int h = 0; h < edges[third].size(); ++h) {
                        if (edges[third][h] == first) {
                            // found a clique of 3
                            //cout << node_names[first] << "," << node_names[second] << "," << node_names[third] << endl;
                            if (node_names[first][0] == 't' || node_names[second][0] == 't' || node_names[third][0] == 't') ++res;
                        }
                    }
                }
            }
        }
    }
}
cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    unordered_map<string, int> nodes;
    int c = 0;
    for (string s : text_lines) {
        string n1 = "";
        n1.push_back(s[0]);
        n1.push_back(s[1]);
        string n2 = "";
        n2.push_back(s[3]);
        n2.push_back(s[4]);

        if (nodes.count(n1) == 0) {
            nodes[n1] = c;
            ++c;
        }
        if (nodes.count(n2) == 0) {
            nodes[n2] = c;
            ++c;
        }
    }
    //for (auto it = nodes.begin(); it != nodes.end(); ++it) cout << it->first << " -> " << it->second << endl;

    int n = nodes.size();
    //cout << "size: " << n << endl;

    vector<vector<int>> edges(n);
    vector<unordered_set<int>> edges_set(n);
    vector<string> node_names(n);
    for (string s : text_lines) {
        string n1 = "";
        n1.push_back(s[0]);
        n1.push_back(s[1]);
        string n2 = "";
        n2.push_back(s[3]);
        n2.push_back(s[4]);

        edges[nodes[n1]].push_back(nodes[n2]);
        edges[nodes[n2]].push_back(nodes[n1]);

        edges_set[nodes[n1]].insert(nodes[n2]);
        edges_set[nodes[n2]].insert(nodes[n1]);

        node_names[nodes[n1]] = n1;
        node_names[nodes[n2]] = n2;
    }

    //for (int i = 0; i < n; ++i) {
    //    cout << i << " -> [";
    //    for (int j = 0; j < edges[i].size(); ++j) cout << edges[i][j] << " ";
    //    cout << "]" << endl;
    //}


    //for (int i = 0; i < n; ++i) cout << node_names[i] << " -> " << edges[i].size() << endl;
    // the nodes of input all have 13 edges

    for (int i = 0; i < n; ++i) {
        sort(edges[i].begin(), edges[i].end());
    }
    
    //for (int i = 0; i < n; ++i) {
    //    cout << "node " << i << " -> ";
    //    for (int j = 0; j < edges[i].size(); ++j) cout << edges[i][j] << " - ";
    //    cout << endl;
    //}

    vector<int> res;

    for (int i = 0; i < n; ++i) {
        // check if the connected node are all connected
        for (int r1 = 0; r1 < edges[i].size(); ++r1) {
            bool missing = false;
            for (int j = 0; j < edges[i].size() - 1; ++j) {
                if (j == r1) continue;

                for (int k = j + 1; k < edges[i].size(); ++k) {
                    if (k == r1) continue;

                    if (edges_set[edges[i][j]].count(edges[i][k]) == 0) {
                        missing = true;
                        break;
                    }
                }
                if (missing) break;
            }

            if (!missing) res.push_back(i);
        }
    }

    vector<string> ress;
    for (int i = 0; i < res.size(); ++i) ress.push_back(node_names[res[i]]);

    sort(ress.begin(), ress.end());

    cout << "res: ";
    for (int i = 0; i < ress.size(); ++i) cout << ress[i] << ",";
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
