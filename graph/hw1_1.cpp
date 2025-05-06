#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
// Количество вершин графа
int n;
// Список смежности графа
vector<vector<int>> gr;

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

// Добавляет ребро
void add_edge(int a, int b) {
    gr[a].push_back(b);
    sort(gr[a].begin(), gr[a].end());
    gr[a].erase(unique(gr[a].begin(), gr[a].end()), gr[a].end());
    gr[b].push_back(a);
    sort(gr[b].begin(), gr[b].end());
    gr[b].erase(unique(gr[b].begin(), gr[b].end()), gr[b].end());
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

int main() {
    // Ввод
    cout << "Num of nodes: ";
    cin >> n;
    gr.resize(n);
    make_graph();
    print();
    // Находим вершины с нечетными степенями
    int v1 = -1, v2 = -1;
    for (int i = 0; i < n; i++) {
        if (gr[i].size() % 2) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            // Если больше двух нечетных вершин, Эйлерова пути нет
            else {
                cout << "There is none Eulerian path\n";
                return 0;
            }
        }
    }
    // Добавляем минмое ребро между нечетными вершинами
    if (v1 != -1) add_edge(v1, v2);
    // Обход с удалением ребер
    stack<int> s;
    vector<int> res;
    if (v1 != -1) s.push(v1);
    else s.push(0);
    while (!s.empty()) {
        int x = s.top();
        if (!gr[x].empty()) {
            s.push(gr[x][0]);
            del_edge(x, gr[x][0]);
        }
        else {
            res.push_back(x);
            s.pop();
        }
    }
    // Если ребра остались, граф несвязный, значит нет Эйлерова пути
    for (vector<int> &l : gr) {
        if (!l.empty()) {
            cout << "There is none Eulerian path\n";
            return 0;
        }
    }
    // Удаление мнимого ребра, если существует только путь
    if (v1 != -1) {
        for (int i = 0; i + 1 < res.size(); i++) {
            if (res[i] == v1 && res[i+1] == v2 ||
            res[i] == v2 && res[i+1] == v1) {
                vector<int> res1;
                res1.insert(res1.end(), res.begin() + i + 1, res.end());
                if (res[0] == *(res.end() - 1))
                    res1.insert(res1.end(), res.begin() + 1, res.begin() + i + 1);
                else res1.insert(res1.end(), res.begin(), res.begin() + i + 1);
                res = res1;
                break;
            }
        }
        cout << "Eulerian path: ";
    }
    else cout << "Eulerian cycle: ";
    for (int i : res) cout << i << ' ';
    cout << endl;
}
