#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;
bool is_oriented = false;

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

// Удаляет ребро
void del_edge(int a, int b) {
    gr[a].erase(remove(gr[a].begin(), gr[a].end(), b), gr[a].end());
    gr[b].erase(remove(gr[b].begin(), gr[b].end(), a), gr[b].end());
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
}

int main() {
    // Ввод
    cout << "Num of nodes: ";
    cin >> n;
    gr.resize(n);
    make_graph();

    cout << "Edge: ";
    int a, b;
    cin >> a >> b;
    // Удаляет ребро
    del_edge(a, b);
    print(); 
}
