#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;
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

// Проверяет, есть ли такое ребро
bool is_edge(int x, int y) {
    for (int v : gr[x]) {
        if (v == y) return 1;
    }
    return 0;
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
    cout << "No edge: ";
    // Выводит вершины, которые не смежные с данной
    for (int i = 0; i < n; i++) {
        if (!is_edge(v, i) && !is_edge(i, v))
            cout << i << ' ';
    }
    cout << endl;
}
