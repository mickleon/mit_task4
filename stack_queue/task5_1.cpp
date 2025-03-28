#include <iostream>
#include <climits>

using namespace std;

template<typename type>
struct Node {
    type inf;
    Node *next;
    Node(type value) : inf(value), next(nullptr) {}
};

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
        Node<type> *getHead() {return head;}
        Node<type> *getTail() {return tail;}
        void setHead(Node<type> *h) {head = h;}
        void setTail(Node<type> *t) {tail = t;}
};

template<typename type>
void Queue<type>::push(type value) {
    Node<type> *p = new Node<type>(value);
    if (tail == nullptr) head = tail = p;
    else {
        tail->next = p;
        tail = p;
    }
}

template<typename type>
type Queue<type>::pop() {
    type x = head->inf;
    Node<type> *p = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete p;
    return x;
}

// Удаление первого и последнего минимальных элементов
Queue<int> result(Queue<int> queue) {
    // Нахождение минимального
    Node<int> *head = queue.getHead();
    int min_el = INT_MAX;
    while (head) {
        min_el = min(head->inf, min_el);
        head = head->next;
    }

    // Запись в новую очередь
    Queue<int> tmp, res;
    bool f = false;
    int x, y;
    while (!queue.empty()) {
        x = queue.pop();
        if (x == min_el) {
            if (!f) f = true;
            else if (tmp.empty()) tmp.push(x);
            else {
                while (!tmp.empty()) {
                    y = tmp.pop();
                    res.push(y);
                }
                tmp.push(x);
            }
        }
        else if (tmp.empty()) res.push(x);
        else tmp.push(x);
    }
    tmp.pop();
    while (!tmp.empty()) {
        y = tmp.pop();
        res.push(y);
    }
    return res;
}

int main() {
    Queue<int> queue;
    // Ввод
    cout << "n = ";
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        queue.push(x);
    }
    
    Queue<int> res = result(queue);

    // Вывод результата
    while (!res.empty()) cout << res.pop() << ' ';
    cout << endl;
}
// 13
// 1 2 2 1 3 4 5 1 2 5 4 3 5
