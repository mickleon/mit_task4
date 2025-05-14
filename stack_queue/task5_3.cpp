#include <iostream>

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

// Запись первых вхождений в новую очередь
template<typename type>
Queue<type> result(Queue<type> queue) {  
    Queue<int> tmp, res;
    int x, y;
    while (!queue.empty()) {
        x = queue.pop();
        res.push(x);
        while (!queue.empty()) {
            y = queue.pop();
            if (x != y) tmp.push(y);
        }
        queue.setHead(tmp.getHead()); queue.setTail(tmp.getTail());
        tmp.setHead(nullptr); tmp.setTail(nullptr);
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
// 9
// 1 2 5 6 2 5 7 9 0
