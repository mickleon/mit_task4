#include <iostream>

using namespace std;

struct queue {
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x) {
    queue *r = new queue;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t) h = t = r;
    else {
        t->next = r;
        t = r;
    }

}

int pop(queue *&h, queue *&t) {
    int x = h->inf;
    queue *r = h;
    h = h->next;
    if (!h) t = NULL;
    delete r;
    return x;
}

int main() {
    queue *h = nullptr, *t = nullptr;
    // Ввод
    cout << "n = ";
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(h, t, x);
    }

    // Запись первых вхождений в новый массив   
    queue *h1 = nullptr, *t1 = nullptr;
    queue *resh = nullptr, *rest = nullptr;
    int y;
    while (h) {
        x = pop(h, t);
        push(resh, rest, x);
        while (h) {
            y = pop(h, t);
            if (x != y) push(h1, t1, y);
        }
        h = h1; h1 = nullptr;
        t = t1; t1 = nullptr;
    }
    h = resh; t = rest;

    // Вывод результата
    while (resh)
        cout << pop(resh, rest) << ' ';
    cout << endl;
}
// 9
// 1 2 5 6 2 5 7 9 0
