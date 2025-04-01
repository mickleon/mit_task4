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
    if (tail == nullptr) head = tail = p;
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

int main() {
    // Инициализация графа
    int n = 7, x = 0;
    vector<vector<int>> gr(n);
    gr[0] = {1, 2, 4, 5};
    gr[1] = {0, 3};
    gr[2] = {0, 5};
    gr[3] = {1};
    gr[4] = {0, 6};
    gr[5] = {0, 2, 6};
    gr[6] = {4, 5};

    // Обход в глубину
    stack *head = nullptr;
    vector<int> a(n, 0);
    bool has_unvisited;
    cout << "DFS: ";
    do {
        a[x] = 1;
        push(head, x);
        cout << x << ' ';
        int y; bool f = false;
        while (head != nullptr) {
            x = head->inf;
            for (int i = 0; i < gr[x].size(); i++) {
                if (a[gr[x][i]] == 0) {
                    y = gr[x][i];
                    f = true;
                    break;
                }
            }
            if (f) {
                a[y] = 1;
                push(head, y);
                cout << y << ' ';
            }
            else pop(head);
            f = false;
        }
        has_unvisited = false;
        for (int i = 0; i < n; i++) {
            // Если остались непосещенные вершины
            if (a[i] == 0) {
                has_unvisited = true;
                x = i;
            }
        }
    } while(has_unvisited);
    cout << endl;

    // Обход в ширину
    Queue<int> queue;
    a.assign(n, 0);
    cout << "BFS: ";
    do {
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
        has_unvisited = false;
        for (int i = 0; i < n; i++) {
            // Если остались непосещенные вершины
            if (a[i] == 0) {
                has_unvisited = true;
                x = i;
            }
        }
    } while(has_unvisited);
    cout << endl;
}
