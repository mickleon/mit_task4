#include <iostream>
#include <vector>

using namespace std;

// Структура стека
struct stack {
    int inf;
    stack *next;
};

// Добавление элемента в стек
void push(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

// Удаление элемента из стека
int pop(stack *&h) {
    int x = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return x;
}

// Структура узла
template<typename type>
struct Node {
    type inf;
    Node *next;
    Node(type value) : inf(value), next(nullptr) {}
};

// Структура очереди
template<typename type>
class Queue {
    private:
        Node<type> *head;
        Node<type> *tail;
    public:
        Queue() : head(nullptr), tail(nullptr) {}
        void push(type value);
        type pop();
        bool empty() {return !head;}
};

// Добавление элемента в очередь
template<typename type>
void Queue<type>::push(type value) {
    Node<type> *p = new Node<type>(value);
    if (!tail) head = tail = p;
    else {
        tail->next = p;
        tail = p;
    }
}

// Удаление элемента из очереди
template<typename type>
type Queue<type>::pop() {
    type x = head->inf;
    Node<type> *p = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete p;
    return x;
}

// Обход в глубину
void dfs(int x, vector<vector<int>>gr, vector<bool> &a) {
    stack *head = nullptr;
    a[x] = 1;
    push(head, x);
    cout << x << ' ';
    while (head) {
        bool f = 0;
        x = head->inf;
        for (int i = 0; i < gr[x].size(); i++) {
            if (a[gr[x][i]] == 0) {
                int y = gr[x][i];
                f = 1;
                a[y] = 1;
                push(head, y);
                cout << y << ' ';
                break;
            }
        }
        if (!f) pop(head);
    }
}

// Обход в ширину
void bfs(int x, vector<vector<int>>gr, vector<bool> &a) {
    Queue<int> queue;
    a[x] = 1;
    queue.push(x);
    cout << x << ' ';    
    while (!queue.empty()) {
        x = queue.pop();
        for (int i = 0; i < gr[x].size(); i++) {
            if (a[gr[x][i]] == 0) {
                int y = gr[x][i];
                a[y] = 1;
                queue.push(y);
                cout << y << ' ';
            }
        }
    }
}

int main() {
    int n, m, x;
    cout << "Number of nodes: ";
    cin >> n;
    cout << "Number of edges: ";
    cin >> m;
    vector<vector<int>> gr;
    gr.assign(n, {});
    int u, v;
    cout << "Edges (from 0 index):\n";
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    cout << "Start from: ";
    cin >> x;

    vector<bool> a(n, 0);
    cout << "DFS: ";
    // Обходим с вершины x
    dfs(x, gr, a);
    // Дообходим, если остались непосещенные
    for (int i = 0; i < n; i++) {
        if (!a[i]) dfs(i, gr, a);
    }
    cout << endl;
    
    a.assign(n, 0);
    cout << "BFS: ";
    // Обходим с вершины x
    bfs(x, gr, a);
    // Дообходим, если остались непосещенные
    for (int i = 0; i < n; i++) {
        if (!a[i]) bfs(i, gr, a);
    }
    cout << endl;
}
// Граф из лекции
/*
7 8
0 1
0 2
0 4
0 5
1 3
2 5
4 6
5 6
*/
