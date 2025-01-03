// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
/*
    +---+---+---+
    | 7 | 8 | 9 |
    +---+---+---+
    | 4 | 5 | 6 |
    +---+---+---+
    | 1 | 2 | 3 |
    +---+---+---+
        | 0 | A |
        +---+---+

        +---+---+
        | ^ | A |
    +---+---+---+
    | < | v | > |
    +---+---+---+

    best to have starting with <, then v, then ^ or >
*/

static void first(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = 4;
    vector<vector<char>> codes(m);
    for (int i = 0; i < text_lines.size(); ++i) {
        string s = text_lines[i];
        for (char c : s) codes[i].push_back(c);
    }
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << codes[i][j] << "";
    //    }
    //    cout << endl;
    //}

    // first robot: input -> movement
    unordered_map<char, pair<int, int>> nums_to_pos;
    nums_to_pos['7'] = make_pair(0, 0);
    nums_to_pos['8'] = make_pair(0, 1);
    nums_to_pos['9'] = make_pair(0, 2);
    nums_to_pos['4'] = make_pair(1, 0);
    nums_to_pos['5'] = make_pair(1, 1);
    nums_to_pos['6'] = make_pair(1, 2);
    nums_to_pos['1'] = make_pair(2, 0);
    nums_to_pos['2'] = make_pair(2, 1);
    nums_to_pos['3'] = make_pair(2, 2);
    nums_to_pos['0'] = make_pair(3, 1);
    nums_to_pos['A'] = make_pair(3, 2);
    pair<int, int> nums_avoid = make_pair(3,0);

    vector<vector<char>> moves(m);
    for (int i = 0; i < m; ++i) {
        pair<int, int> start = nums_to_pos['A'];

        for (int j = 0; j < n; ++j) {
            int rdiff = nums_to_pos[codes[i][j]].first - start.first;
            int cdiff = nums_to_pos[codes[i][j]].second - start.second;

            if (rdiff == 0) {
                while (cdiff != 0) {
                    moves[i].push_back(cdiff > 0 ? '>' : '<');
                    cdiff += cdiff > 0 ? -1 : 1;
                }
            }
            else if (cdiff < 0) {
                if (rdiff > 0) {
                    // left - down
                    if (start.first == nums_avoid.first && start.second + cdiff == nums_avoid.second) {
                        while (rdiff != 0) {
                            moves[i].push_back('v');
                            --rdiff;
                        }
                        while (cdiff != 0) {
                            moves[i].push_back('<');
                            ++cdiff;
                        }
                    }
                    else {
                        while (cdiff != 0) {
                            moves[i].push_back('<');
                            ++cdiff;
                        }
                        while (rdiff != 0) {
                            moves[i].push_back('v');
                            --rdiff;
                        }
                    }
                }
                else {
                    // left - up
                    if (start.first == nums_avoid.first && start.second + cdiff == nums_avoid.second) {
                        while (rdiff != 0) {
                            moves[i].push_back('^');
                            ++rdiff;
                        }
                        while (cdiff != 0) {
                            moves[i].push_back('<');
                            ++cdiff;
                        }
                    }
                    else {
                        while (cdiff != 0) {
                            moves[i].push_back('<');
                            ++cdiff;
                        }
                        while (rdiff != 0) {
                            moves[i].push_back('^');
                            ++rdiff;
                        }
                    }
                }
            }
            else if(cdiff > 0){
                if (rdiff > 0) {
                    // down - right
                    if (start.first + rdiff == nums_avoid.first && start.second == nums_avoid.second) {
                        while (cdiff != 0) {
                            moves[i].push_back('>');
                            --cdiff;
                        }
                        while (rdiff != 0) {
                            moves[i].push_back('v');
                            --rdiff;
                        }
                    }
                    else {
                        while (rdiff != 0) {
                            moves[i].push_back('v');
                            --rdiff;
                        }
                        while (cdiff != 0) {
                            moves[i].push_back('>');
                            --cdiff;
                        }
                    }
                }
                else {
                    // right - up
                    if (start.first + rdiff == nums_avoid.first && start.second == nums_avoid.second) {
                        while (cdiff != 0) {
                            moves[i].push_back('>');
                            --cdiff;
                        }
                        while (rdiff != 0) {
                            moves[i].push_back('^');
                            ++rdiff;
                        }
                    }
                    else {
                        while (rdiff != 0) {
                            moves[i].push_back('^');
                            ++rdiff;
                        }
                        while (cdiff != 0) {
                            moves[i].push_back('>');
                            --cdiff;
                        }
                    }
                }
            }
            else {
                while (rdiff != 0) {
                    moves[i].push_back(rdiff > 0 ? 'v' : '^');
                    rdiff += rdiff > 0 ? -1 : 1;
                }
            }

            moves[i].push_back('A');
            start = nums_to_pos[codes[i][j]];
        }
    }
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < moves[i].size(); ++j) {
    //        cout << moves[i][j] << "";
    //    }
    //    cout << endl;
    //}




    // the others robots
    unordered_map<char, pair<int, int>> arr_to_pos;
    arr_to_pos['^'] = make_pair(0, 1);
    arr_to_pos['A'] = make_pair(0, 2);
    arr_to_pos['<'] = make_pair(1, 0);
    arr_to_pos['v'] = make_pair(1, 1);
    arr_to_pos['>'] = make_pair(1, 2);
    pair<int, int> arr_avoid = make_pair(0,0);

    for (int k = 0; k < 2; ++k) {
        vector<vector<char>> new_moves(m);
        for (int i = 0; i < m; ++i) {
            pair<int, int> start = arr_to_pos['A'];

            for (int j = 0; j < moves[i].size(); ++j) {
                int rdiff = arr_to_pos[moves[i][j]].first - start.first;
                int cdiff = arr_to_pos[moves[i][j]].second - start.second;


                if (rdiff == 0) {
                    while (cdiff != 0) {
                        new_moves[i].push_back(cdiff > 0 ? '>' : '<');
                        cdiff += cdiff > 0 ? -1 : 1;
                    }
                }
                else if (cdiff < 0) {
                    if (rdiff > 0) {
                        // left - down
                        if (start.first == arr_avoid.first && start.second + cdiff == arr_avoid.second) {
                            while (rdiff != 0) {
                                new_moves[i].push_back('v');
                                --rdiff;
                            }
                            while (cdiff != 0) {
                                new_moves[i].push_back('<');
                                ++cdiff;
                            }
                        }
                        else {
                            while (cdiff != 0) {
                                new_moves[i].push_back('<');
                                ++cdiff;
                            }
                            while (rdiff != 0) {
                                new_moves[i].push_back('v');
                                --rdiff;
                            }
                        }
                    }
                    else {
                        // left - up
                        if (start.first == arr_avoid.first && start.second + cdiff == arr_avoid.second) {
                            while (rdiff != 0) {
                                new_moves[i].push_back('^');
                                ++rdiff;
                            }
                            while (cdiff != 0) {
                                new_moves[i].push_back('<');
                                ++cdiff;
                            }
                        }
                        else {
                            while (cdiff != 0) {
                                new_moves[i].push_back('<');
                                ++cdiff;
                            }
                            while (rdiff != 0) {
                                new_moves[i].push_back('^');
                                ++rdiff;
                            }
                        }
                    }
                }
                else if (cdiff > 0) {
                    if (rdiff > 0) {
                        // down - right
                        if (start.first + rdiff == arr_avoid.first && start.second == arr_avoid.second) {
                            while (cdiff != 0) {
                                new_moves[i].push_back('>');
                                --cdiff;
                            }
                            while (rdiff != 0) {
                                new_moves[i].push_back('v');
                                --rdiff;
                            }
                        }
                        else {
                            while (rdiff != 0) {
                                new_moves[i].push_back('v');
                                --rdiff;
                            }
                            while (cdiff != 0) {
                                new_moves[i].push_back('>');
                                --cdiff;
                            }
                        }
                    }
                    else {
                        // right - up
                        if (start.first + rdiff == arr_avoid.first && start.second == arr_avoid.second) {
                            while (cdiff != 0) {
                                new_moves[i].push_back('>');
                                --cdiff;
                            }
                            while (rdiff != 0) {
                                new_moves[i].push_back('^');
                                ++rdiff;
                            }
                        }
                        else {
                            while (rdiff != 0) {
                                new_moves[i].push_back('^');
                                ++rdiff;
                            }
                            while (cdiff != 0) {
                                new_moves[i].push_back('>');
                                --cdiff;
                            }
                        }
                    }
                }
                else {
                    while (rdiff != 0) {
                        new_moves[i].push_back(rdiff > 0 ? 'v' : '^');
                        rdiff += rdiff > 0 ? -1 : 1;
                    }
                }

                new_moves[i].push_back('A');
                start = arr_to_pos[moves[i][j]];
            }
        }
        moves = new_moves;
        //for (int i = 0; i < m; ++i) {
        //    for (int j = 0; j < moves[i].size(); ++j) {
        //        cout << moves[i][j] << "";
        //    }
        //    cout << endl;
        //}
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < moves[i].size(); ++j) {
    //        cout << moves[i][j] << "";
    //    }
    //    cout << endl;
    //}

    long long res = 0;
    for (int i = 0; i < m; ++i) {
        string s = "";
        for (int j = 0; j < 3; ++j) s.push_back(codes[i][j]);

        res += moves[i].size() * stoi(s);
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    int m = text_lines.size();
    int n = 4;
    vector<vector<char>> codes(m);
    for (int i = 0; i < text_lines.size(); ++i) {
        string s = text_lines[i];
        for (char c : s) codes[i].push_back(c);
    }
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        cout << codes[i][j] << "";
    //    }
    //    cout << endl;
    //}

    // first robot: input -> movement
    unordered_map<char, pair<int, int>> nums_to_pos;
    nums_to_pos['7'] = make_pair(0, 0);
    nums_to_pos['8'] = make_pair(0, 1);
    nums_to_pos['9'] = make_pair(0, 2);
    nums_to_pos['4'] = make_pair(1, 0);
    nums_to_pos['5'] = make_pair(1, 1);
    nums_to_pos['6'] = make_pair(1, 2);
    nums_to_pos['1'] = make_pair(2, 0);
    nums_to_pos['2'] = make_pair(2, 1);
    nums_to_pos['3'] = make_pair(2, 2);
    nums_to_pos['0'] = make_pair(3, 1);
    nums_to_pos['A'] = make_pair(3, 2);
    pair<int, int> nums_avoid = make_pair(3, 0);

    vector<unordered_map<string, long long>> moves_maps(m);
    for (int i = 0; i < m; ++i) {
        pair<int, int> start = nums_to_pos['A'];

        for (int j = 0; j < n; ++j) {
            int rdiff = nums_to_pos[codes[i][j]].first - start.first;
            int cdiff = nums_to_pos[codes[i][j]].second - start.second;

            string s = "";

            if (rdiff == 0) {
                while (cdiff != 0) {
                    s.push_back(cdiff > 0 ? '>' : '<');
                    cdiff += cdiff > 0 ? -1 : 1;
                }
            }
            else if (cdiff < 0) {
                if (rdiff > 0) {
                    // left - down
                    if (start.first == nums_avoid.first && start.second + cdiff == nums_avoid.second) {
                        while (rdiff != 0) {
                            s.push_back('v');
                            --rdiff;
                        }
                        while (cdiff != 0) {
                            s.push_back('<');
                            ++cdiff;
                        }
                    }
                    else {
                        while (cdiff != 0) {
                            s.push_back('<');
                            ++cdiff;
                        }
                        while (rdiff != 0) {
                            s.push_back('v');
                            --rdiff;
                        }
                    }
                }
                else {
                    // left - up
                    if (start.first == nums_avoid.first && start.second + cdiff == nums_avoid.second) {
                        while (rdiff != 0) {
                            s.push_back('^');
                            ++rdiff;
                        }
                        while (cdiff != 0) {
                            s.push_back('<');
                            ++cdiff;
                        }
                    }
                    else {
                        while (cdiff != 0) {
                            s.push_back('<');
                            ++cdiff;
                        }
                        while (rdiff != 0) {
                            s.push_back('^');
                            ++rdiff;
                        }
                    }
                }
            }
            else if (cdiff > 0) {
                if (rdiff > 0) {
                    // down - right
                    if (start.first + rdiff == nums_avoid.first && start.second == nums_avoid.second) {
                        while (cdiff != 0) {
                            s.push_back('>');
                            --cdiff;
                        }
                        while (rdiff != 0) {
                            s.push_back('v');
                            --rdiff;
                        }
                    }
                    else {
                        while (rdiff != 0) {
                            s.push_back('v');
                            --rdiff;
                        }
                        while (cdiff != 0) {
                            s.push_back('>');
                            --cdiff;
                        }
                    }
                }
                else {
                    // right - up
                    if (start.first + rdiff == nums_avoid.first && start.second == nums_avoid.second) {
                        while (cdiff != 0) {
                            s.push_back('>');
                            --cdiff;
                        }
                        while (rdiff != 0) {
                            s.push_back('^');
                            ++rdiff;
                        }
                    }
                    else {
                        while (rdiff != 0) {
                            s.push_back('^');
                            ++rdiff;
                        }
                        while (cdiff != 0) {
                            s.push_back('>');
                            --cdiff;
                        }
                    }
                }
            }
            else {
                while (rdiff != 0) {
                    s.push_back(rdiff > 0 ? 'v' : '^');
                    rdiff += rdiff > 0 ? -1 : 1;
                }
            }

            s.push_back('A');

            moves_maps[i][s] += 1;

            start = nums_to_pos[codes[i][j]];
        }
    }
    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < moves[i].size(); ++j) {
    //        cout << moves[i][j] << "";
    //    }
    //    cout << endl;
    //}




    // the others robots
    unordered_map<char, pair<int, int>> arr_to_pos;
    arr_to_pos['^'] = make_pair(0, 1);
    arr_to_pos['A'] = make_pair(0, 2);
    arr_to_pos['<'] = make_pair(1, 0);
    arr_to_pos['v'] = make_pair(1, 1);
    arr_to_pos['>'] = make_pair(1, 2);
    pair<int, int> arr_avoid = make_pair(0, 0);

    for (int k = 0; k < 25; ++k) {

        vector<unordered_map<string, long long>> new_moves_maps(m);
        for (int i = 0; i < m; ++i) {
            pair<int, int> start = arr_to_pos['A'];

            for(auto it=moves_maps[i].begin(); it != moves_maps[i].end(); ++it) {

                for (int j = 0; j < it->first.size(); ++j) {

                    int rdiff = arr_to_pos[it->first[j]].first - start.first;
                    int cdiff = arr_to_pos[it->first[j]].second - start.second;

                    string s = "";

                    if (rdiff == 0) {
                        while (cdiff != 0) {
                            s.push_back(cdiff > 0 ? '>' : '<');
                            cdiff += cdiff > 0 ? -1 : 1;
                        }
                    }
                    else if (cdiff < 0) {
                        if (rdiff > 0) {
                            // left - down
                            if (start.first == arr_avoid.first && start.second + cdiff == arr_avoid.second) {
                                while (rdiff != 0) {
                                    s.push_back('v');
                                    --rdiff;
                                }
                                while (cdiff != 0) {
                                    s.push_back('<');
                                    ++cdiff;
                                }
                            }
                            else {
                                while (cdiff != 0) {
                                    s.push_back('<');
                                    ++cdiff;
                                }
                                while (rdiff != 0) {
                                    s.push_back('v');
                                    --rdiff;
                                }
                            }
                        }
                        else {
                            // left - up
                            if (start.first == arr_avoid.first && start.second + cdiff == arr_avoid.second) {
                                while (rdiff != 0) {
                                    s.push_back('^');
                                    ++rdiff;
                                }
                                while (cdiff != 0) {
                                    s.push_back('<');
                                    ++cdiff;
                                }
                            }
                            else {
                                while (cdiff != 0) {
                                    s.push_back('<');
                                    ++cdiff;
                                }
                                while (rdiff != 0) {
                                    s.push_back('^');
                                    ++rdiff;
                                }
                            }
                        }
                    }
                    else if (cdiff > 0) {
                        if (rdiff > 0) {
                            // down - right
                            if (start.first + rdiff == arr_avoid.first && start.second == arr_avoid.second) {
                                while (cdiff != 0) {
                                    s.push_back('>');
                                    --cdiff;
                                }
                                while (rdiff != 0) {
                                    s.push_back('v');
                                    --rdiff;
                                }
                            }
                            else {
                                while (rdiff != 0) {
                                    s.push_back('v');
                                    --rdiff;
                                }
                                while (cdiff != 0) {
                                    s.push_back('>');
                                    --cdiff;
                                }
                            }
                        }
                        else {
                            // right - up
                            if (start.first + rdiff == arr_avoid.first && start.second == arr_avoid.second) {
                                while (cdiff != 0) {
                                    s.push_back('>');
                                    --cdiff;
                                }
                                while (rdiff != 0) {
                                    s.push_back('^');
                                    ++rdiff;
                                }
                            }
                            else {
                                while (rdiff != 0) {
                                    s.push_back('^');
                                    ++rdiff;
                                }
                                while (cdiff != 0) {
                                    s.push_back('>');
                                    --cdiff;
                                }
                            }
                        }
                    }
                    else {
                        while (rdiff != 0) {
                            s.push_back(rdiff > 0 ? 'v' : '^');
                            rdiff += rdiff > 0 ? -1 : 1;
                        }
                    }

                    s.push_back('A');

                    new_moves_maps[i][s] += it->second;

                    start = arr_to_pos[it->first[j]];
                }
            }
        }
        moves_maps = new_moves_maps;
        //for (int i = 0; i < m; ++i) {
        //    for (int j = 0; j < moves[i].size(); ++j) {
        //        cout << moves[i][j] << "";
        //    }
        //    cout << endl;
        //}
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < moves[i].size(); ++j) {
    //        cout << moves[i][j] << "";
    //    }
    //    cout << endl;
    //}

    long long res = 0;
    for (int i = 0; i < m; ++i) {
        string s = "";
        for (int j = 0; j < 3; ++j) s.push_back(codes[i][j]);

        long long sum = 0;
        for (auto it = moves_maps[i].begin(); it != moves_maps[i].end(); ++it) sum += it->first.size() * it->second;
        res += sum * stoi(s);
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
