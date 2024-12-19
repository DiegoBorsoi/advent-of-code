// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

using namespace std;

static void first(vector<string>& text_lines)
{
    bool isgrid = true;
    vector<vector<char>> grid;
    vector<char> moves;
    for (string s : text_lines) {
        if (s == "") {
            isgrid = false;
            continue;
        }

        if (isgrid) {
            vector<char> line;
            for (char c : s) {
                line.push_back(c);
            }
            grid.push_back(line);
        }
        else {
            for (char c : s) moves.push_back(c);
        }
    }

    //cout << "grid: " << grid.size() << " x " << grid[0].size() << endl;
    //cout << "moves: " << moves.size() << endl;

    int m = grid.size();
    int n = grid[0].size();

    // get robot initial position
    pair<int, int> robot = make_pair(0,0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@') {
                robot = make_pair(i, j);
                break;
            }
        }
        if (robot.first != 0) break;
    }

    vector<vector<int>> dirs = { {1,0}, {-1,0}, {0,1} , {0,-1} };
    for (int m = 0; m < moves.size(); ++m) {
        // check if the move is possible
        int idx;
        switch (moves[m]) {
            case '^':
                idx = 1;
                break;
            case '>':
                idx = 2;
                break;
            case 'v':
                idx = 0;
                break;
            case '<':
                idx = 3;
                break;
        }
        pair<int, int> pos = robot;
        bool ispossible = false;
        while (grid[pos.first][pos.second] != '#') {
            if (grid[pos.first][pos.second] == '.') {
                ispossible = true;
                break;
            }
            pos.first += dirs[idx][0];
            pos.second += dirs[idx][1];
        }
        //cout << (ispossible ? "true" : "false") << " dir: " << idx << endl;
        //cout << pos.first << " - " << pos.second << endl;

        if (!ispossible) continue;


        // make the move (pos is the first '.')
        pair<int, int> to_move;
        while (pos.first != robot.first || pos.second != robot.second) {
            to_move = make_pair(pos.first - dirs[idx][0], pos.second - dirs[idx][1]);
            grid[pos.first][pos.second] = grid[to_move.first][to_move.second];
            pos = to_move;
        }
        grid[pos.first][pos.second] = '.';
        robot.first = pos.first + dirs[idx][0];
        robot.second = pos.second + dirs[idx][1];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    // calculate res
    long long res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if(grid[i][j] == 'O') res += 100 * i + j;
        }
    }
    cout << "res: " << res << endl;
}

static void second(vector<string>& text_lines)
{
    bool isgrid = true;
    vector<vector<char>> grid;
    vector<char> moves;
    for (string s : text_lines) {
        if (s == "") {
            isgrid = false;
            continue;
        }

        if (isgrid) {
            vector<char> line;
            for (char c : s) {
                line.push_back(c);
            }
            grid.push_back(line);
        }
        else {
            for (char c : s) moves.push_back(c);
        }
    }

    //cout << "grid: " << grid.size() << " x " << grid[0].size() << endl;
    //cout << "moves: " << moves.size() << endl;

    int m = grid.size();
    int n = grid[0].size();

    vector<vector<char>> double_grid(m, vector<char>(2*n, '.'));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') {
                double_grid[i][2 * j] = '#';
                double_grid[i][2 * j + 1] = '#';
            }
            else if (grid[i][j] == 'O') {
                double_grid[i][2 * j] = '[';
                double_grid[i][2 * j + 1] = ']';
            }
            else if (grid[i][j] == '@') {
                double_grid[i][2 * j] = '@';
            }
        }
    }

    //for (int i = 0; i < m; ++i) {
    //    for (int j = 0; j < 2 * n; ++j) {
    //        cout << double_grid[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    

    // get robot initial position
    pair<int, int> robot = make_pair(0, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if (double_grid[i][j] == '@') {
                robot = make_pair(i, j);
                break;
            }
        }
        if (robot.first != 0) break;
    }


    vector<vector<int>> dirs = { {1,0}, {-1,0}, {0,1} , {0,-1} };
    for (int k = 0; k < moves.size(); ++k) {
        //cout << "move: " << moves[k] << endl;
        //for (int i = 0; i < m; ++i) {
        //    for (int j = 0; j < 2 * n; ++j) {
        //        cout << double_grid[i][j] << " ";
        //    }
        //    cout << endl;
        //}
        // check if the move is possible
        int idx;
        switch (moves[k]) {
        case '^':
            idx = 1;
            break;
        case '>':
            idx = 2;
            break;
        case 'v':
            idx = 0;
            break;
        case '<':
            idx = 3;
            break;
        }

        if (idx == 2 || idx == 3) { // horiz movement, same as the first part
            pair<int, int> pos = robot;
            bool ispossible = false;
            while (double_grid[pos.first][pos.second] != '#') {
                if (double_grid[pos.first][pos.second] == '.') {
                    ispossible = true;
                    break;
                }
                pos.first += dirs[idx][0];
                pos.second += dirs[idx][1];
            }
            //cout << (ispossible ? "true" : "false") << " dir: " << idx << endl;
            //cout << pos.first << " - " << pos.second << endl;

            if (!ispossible) continue;


            // make the move (pos is the first '.')
            pair<int, int> to_move;
            while (pos.first != robot.first || pos.second != robot.second) {
                to_move = make_pair(pos.first - dirs[idx][0], pos.second - dirs[idx][1]);
                double_grid[pos.first][pos.second] = double_grid[to_move.first][to_move.second];
                pos = to_move;
            }
            double_grid[pos.first][pos.second] = '.';
            robot.first = pos.first + dirs[idx][0];
            robot.second = pos.second + dirs[idx][1];
        }
        else { // vector of position to check if we can move

            vector<pair<int, int>> pos_to_check;
            pos_to_check.push_back(robot);
            bool ispossible = true;

            while (ispossible && pos_to_check.size() > 0) {
                vector<pair<int, int>> new_poses;
                for (int i = 0; i < pos_to_check.size(); ++i) {
                    pair<int, int> p = pos_to_check[i];
                    if (i == 0 && i == pos_to_check.size() - 1) {
                        if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1] - 1));
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1] + 1));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '#'){
                            ispossible = false;
                            break;
                        }
                    }
                    else if (i == 0 || pos_to_check[i-1].second +1 != p.second) {
                        if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1] - 1));
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '#') {
                            ispossible = false;
                            break;
                        }
                    }
                    else if (i == pos_to_check.size() - 1 || pos_to_check[i + 1].second - 1 != p.second) {
                        if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1] + 1));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '#') {
                            ispossible = false;
                            break;
                        }
                    }
                    else {
                        if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == ']' || 
                            double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_pair(p.first + dirs[idx][0], p.second + dirs[idx][1]));
                        }
                        else if (double_grid[p.first + dirs[idx][0]][p.second + dirs[idx][1]] == '#') {
                            ispossible = false;
                            break;
                        }
                    }
                }
                pos_to_check = new_poses;
            }


            //cout << (ispossible ? "true" : "false") << " dir: " << idx << endl;

            if (!ispossible) continue;


            vector<tuple<int, int, char>> pos_to_move;
            pos_to_move.push_back(make_tuple(robot.first, robot.second, '@'));
            double_grid[robot.first][robot.second] = '.';

            while (pos_to_move.size() > 0) {
                vector<tuple<int, int, char>> new_poses;
                for (int i = 0; i < pos_to_move.size(); ++i) {
                    tuple<int, int, char> p = pos_to_move[i];
                    if (i == 0 && i == pos_to_move.size() - 1) {
                        if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1] - 1, '['));
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], ']'));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1] - 1] = '.';
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], '['));
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1] + 1, ']'));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1] + 1] = '.';
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else {
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                    }
                    else if (i == 0 || get<1>(pos_to_move[i-1]) + 1 != get<1>(p)) {
                        if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1] - 1, '['));
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], ']'));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1] - 1] = '.';
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], '['));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else {
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                    }
                    else if (i == pos_to_move.size() - 1 || get<1>(pos_to_move[i + 1]) - 1 != get<1>(p)) {
                        if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == '[') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], '['));
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1] + 1, ']'));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1] + 1] = '.';
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] == ']') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0], get<1>(p) + dirs[idx][1], ']'));
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                        else {
                            double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                        }
                    }
                    else {
                        if (double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] != '.') {
                            new_poses.push_back(make_tuple(get<0>(p) + dirs[idx][0],
                                get<1>(p) + dirs[idx][1],
                                double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]]));
                        }
                        double_grid[get<0>(p) + dirs[idx][0]][get<1>(p) + dirs[idx][1]] = get<2>(p);
                    }
                }
                pos_to_move = new_poses;
            }



            robot.first += dirs[idx][0];
            robot.second += dirs[idx][1];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            cout << double_grid[i][j] << " ";
        }
        cout << endl;
    }

    // calculate res
    long long res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if (double_grid[i][j] == '[') res += 100 * i + j;
        }
    }
    cout << "res: " << res << endl;
}

int main()
{
    //ifstream f("test.txt");
    ifstream f("input.txt"); // 1522215

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
