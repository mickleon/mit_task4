#include <iostream>
#include <vector>

using namespace std;

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

    // Обход в ширину
    Queue<int> queue;
    vector<int> a(n, 0);
    a[x] = 1;
    queue.push(x);
    cout << endl;
    cout << x;
    int y;
    while (!queue.empty()) {
        x = queue.pop();
        for (int i = 0; i < gr[x].size(); i++) {
            if (a[gr[x][i]] == 0) {
                y = gr[x][i];
                a[y] = 1;
                queue.push(y);
                cout << ", " << y;
            }
        }
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 0) {
            y = i;
            a[y] = 1;
            queue.push(y);
            cout << ", " << y;
        }
    }
    cout << endl;
}
