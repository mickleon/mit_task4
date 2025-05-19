#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <climits>

using namespace std;

int n; // Количество вершин
vector<vector<pair<int, long long>>> gr; // Список смежности графа
vector<long long> l; // Массив кратчайших длин
vector<int> p; // Массив соседей

// Заполняет список смежности по введенным ребрам и весам
void make_graph() {
    cout << "Num of nodes: ";
    cin >> n;
    gr.resize(n);
    cout << "Num of edges: ";
    int m;
    cin >> m;
    cout << "Edges: \n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < n && v < n) {
            gr[u].push_back({v, w});
            gr[v].push_back({u, w});
        }
    }
}

// Алгоритм Дейкстры (находит кратчайший путь от s до остальных)
void dijkstra(int s) {
    l.resize(n, LONG_LONG_MAX);
    l[s] = 0;
    p.resize(n);
    // set для поиска наименьшего l[u] (выбирается первый)
    set<pair<long long, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [u, w] : gr[v]) {
            // Если нашли длину короче
            if (l[u] > l[v] + w) {
                // Обновляем длину
                q.erase({l[u], u});
                l[u] = l[v] + w;
                q.insert({l[u], u});
                // Обновляем соседа
                p[u] = v;
            }
        }
    }
}

// Выводит кратчайшую длину и путь из s в i
void print_path(int s, int i) {
    stack<int> path; // Стек для разворота пути
    cout << s << "->" << i << " Min length: " << l[i] << " Path: ";
    int v = i;
    while (v != s) {
        path.push(v);
        v = p[v];
    }
    cout << s << ' ';
    while (!path.empty()) {
        cout << path.top() << ' ';
        path.pop();
    }
    cout << endl;
}

int main() {
    make_graph();
    int s;
    cout << "Start: ";
    cin >> s;
    dijkstra(s);
    for (int i = 0; i < n; i++)
        if (i != s) print_path(s, i);
}