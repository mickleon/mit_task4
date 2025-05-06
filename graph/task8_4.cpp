#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;
// Список посещенных вершин
vector<bool> used;
// Путь обхода в глубину
vector<int> path;
bool is_oriented = true;

// Создает граф по введенным ребрам
void make_graph() {
    cout << "Num of edges: ";
    int m;
    cin >> m;
    cout << "Edges: ";
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x < n && y < n) {
            gr[x].push_back(y);
            if (!is_oriented)
                gr[y].push_back(x);
        }
    }
    for (vector<int> &line : gr) {
        sort(line.begin(), line.end());
        line.erase(unique(line.begin(), line.end()), line.end());
    }
}

// Проверяет, есть ли вершина в пути обхода
bool in_path(int x, int y) {
    for (int v : path) {
        if (v == y) return 1;
    }
    return 0;
}

// Обход в глубину
void dfs(int x) {
    used[x] = 1;
    path.push_back(x);
    for (int u : gr[x]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}

// Выводит список смежности графа
void print() {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < gr[i].size(); j++) {
            cout << gr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // Ввод
    cout << "Num of nodes: ";
    cin >> n;
    gr.resize(n);
    make_graph();
    print();
    
    cout << "Node: ";
    int v;
    cin >> v;
    used.resize(n);
    dfs(v);
    // Выводит все вершины, не связные с данной
    cout << "Unreachable: ";
    for (int i = 0; i < n; i++) {
        if (!in_path(v, i))
            cout << i << ' ';
    }
    cout << endl;
}
