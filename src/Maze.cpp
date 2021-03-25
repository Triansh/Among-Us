//
// Created by triansh on 24/03/21.
//
#include <iostream>
#include <stack>
#include <random>
#include "Maze.h"

Maze::Maze() {

    createMaze();

    glm::vec2 pos = glm::vec2(200.0f, 200.0f);
    glm::vec2 size = glm::vec2(200.0f, 150.0f);

    for (auto &i : pat) {
        pos.x = 0.0f;
        for (char j : i) {
            auto *tile = new Tile(j == '#' ? "skeld-wall" : "stone-tile", pos, size, j == '#');
            tiles.push_back(tile);
            if (j == 'S') {
                tiles.push_back(new Tile("start-tile", pos, size, false));
            } else if (j == 'E') {
                tiles.push_back(new Tile("trophy-tile", pos, size, false));
            }
            pos.x += size.x;

        }
        pos.y += size.y;
    }

}

int getIdx(int x, int y, vector<pair<int, pair<int, int> > > cell_list) {
    for (int i = 0; i < cell_list.size(); i++) {
        if (cell_list[i].second.first == x && cell_list[i].second.second == y)
            return cell_list[i].first;
    }
    cout << "getIdx() couldn't find the index!" << endl;
    return -1;
}

void Maze::createMaze() {

    int m = 5, n = 10;
    int M = 2 * m + 1;
    int N = 2 * n + 1;

    char maze[M][N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!(i & 1) || !(j & 1))
                maze[i][j] = '#';
            else
                maze[i][j] = ' ';

        }
    }

    for (int i = 1; i < M; i += 2) {
        for (int j = 1; j < N; j += 2) {
            maze[i][j] = ' ';
        }

    }

    vector<pair<int, pair<int, int> > > cell_list;
    vector<bool> visited(m * n, false);
    stack<pair<int, pair<int, int> >> m_stack;
    random_device rdev;
    mt19937 rng(rdev());
    uniform_int_distribution<mt19937::result_type> dist100(1, 100);

    int nVisited = 0;
    int k = 0;

    for (int i = 1; i < M; i += 2) {
        for (int j = 1; j < N; j += 2) {
            cell_list.emplace_back(k, make_pair(i, j));
            k++;
        }
    }

    int randIdx = (int) (dist100(rng) % m) * n;
    m_stack.push(cell_list[randIdx]);
    visited[randIdx] = true;
    nVisited++;

    // Algo
    while (nVisited < m * n) {

        vector<int> neighbours;
        // North
        if (m_stack.top().second.first > 1) {
            if (maze[m_stack.top().second.first - 2][m_stack.top().second.second + 0] &&
                !visited[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(0);
            }
        }
        // East
        if (m_stack.top().second.second < N - 2) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second + 2] &&
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2, cell_list)]) {
                neighbours.push_back(1);
            }
        }
        // South
        if (m_stack.top().second.first < M - 2) {
            if (maze[m_stack.top().second.first + 2][m_stack.top().second.second + 0] &&
                !visited[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(2);
            }
        }
        // West
        if (m_stack.top().second.second > 1) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second - 2] &&
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2, cell_list)]) {
                neighbours.push_back(3);
            }
        }
        // Neighbours available?
        if (!neighbours.empty()) {
            // Choose a random direction
            int next_cell_dir = neighbours[dist100(rng) % neighbours.size()];
            // Create a path between this cell and neighbour
            switch (next_cell_dir) {
                case 0: // North
                    maze[m_stack.top().second.first - 1][m_stack.top().second.second + 0] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0,
                                                  cell_list)]);
                    break;
                case 1: // East
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second + 1] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2,
                                                  cell_list)]);
                    break;
                case 2: // South
                    maze[m_stack.top().second.first + 1][m_stack.top().second.second + 0] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0,
                                                  cell_list)]);
                    break;
                case 3: // West
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second - 1] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2,
                                                  cell_list)]);
                    break;
            }

            visited[m_stack.top().first] = true;
            nVisited++;
        } else {
            m_stack.pop();
        }
    }

    maze[0][1] = 'S';
    maze[2 * m][2 * n - 1] = 'E';

    for (int i = 0; i < M; i++) {
        string s;
        for (int j = 0; j < N; j++) {
            s += maze[i][j];
        }
        pat.push_back(s);
    }
}