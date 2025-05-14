#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;
bool is_oriented = false;
queue<int> q;
// Список посещенных вершин
vector<bool> used;
// Список вершин, из которой попали в i-ую при обходе в ширину
vector<int> previous;

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

// Обход в ширину
void bfs(int x) {
    used[x] = 1;
    q.push(x);
    while (!q.empty()) {
        int y = q.front();
        q.pop();
        for (int u : gr[y]) {
            if (!used[u]) {
                used[u] = 1;
                previous[u] = y;
                q.push(u);
            }
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
    
    int x, y;
    cout << "Node X: ";
    cin >> x;
    cout << "Node Y: ";
    cin >> y;
    used.resize(n);
    previous.resize(n, -1);
    // Идем из второй, чтобы был правильный порядок при выводе
    bfs(y);
    cout << "Path: ";
    // Гуляет по списку, пока не дойдет до -1 (из нее был обход)
    int p = x;
    while (p != -1) {
        cout << p << ' ';
        p = previous[p];
    }
    cout << endl;
}
