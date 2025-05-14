#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;
// Список посещенных вершин
vector<int> used; // 0 - непосещенные, 1 - серые, 2 - черные
// Порядок топологической сортировки
vector<int> order;

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
        }
    }
    for (vector<int> &line : gr) {
        sort(line.begin(), line.end());
        line.erase(unique(line.begin(), line.end()), line.end());
    }
}

// Выводит список смежности графа
void print() {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < gr[i].size(); j++)
            cout << gr[i][j] << ' ';
        cout << endl;
    }
}

// Обход с добавленем в массив в порядке сортировки
void dfs(int x) {
	used[x] = 1;
	for (int y : gr[x]) {
		if (!used[y]) dfs(y);
        // Проверка на наличие циклов
        else if (used[y] == 1) {
            cout << "Graph has a cycle\n";
			exit(0);
        }
	}
    used[x] = 2;
    order.push_back(x);
}

int main() {
    // Ввод
    cout << "Num of nodes: ";
    cin >> n;
    gr.resize(n);
    make_graph();
    print();
    // Вызов обхода для всех непосещенных вершин
    used.resize(n);
    for (int i = 0; i < n; i++)
		if (!used[i]) dfs(i);
    // Перезапись в обратном порядке
    reverse(order.begin(), order.end());
    cout << "Sorted: ";
    for (int i : order) cout << i << ' ';
    cout << endl;
}
/*
9
14
0 1
0 2
1 2
1 3
1 4
2 4
2 5
3 6
4 6
5 4
5 7
6 7
6 8
7 8
*/
