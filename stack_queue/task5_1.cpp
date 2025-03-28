#include <iostream>
#include <climits>

using namespace std;

// Структура очереди
struct queue {
    int inf;
    queue *next;
};

// Добавление элемента в конец
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

// Удаления элемента из начала
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

    // Удаление первого и последнего минимального элемента
    queue *resh = nullptr, *rest = nullptr;
    int min_times = INT_MAX;
    queue *h1 = h;
    // Нахождение минимального
    while (h1) {
        min_times = min(h1->inf, min_times);
        h1 = h1->next;
    }
    // Нахождение первой и последней позиции
    int i = 0, first = -1, last = -1;
    h1 = h;
    while (h1) {
        if (h1->inf == min_times) {
            if (first == -1) first = i;
            last = i;
        }
        h1 = h1->next;
        i++;
    }
    // Запись результата
    i = 0;
    h1 = h;
    while (h1) {
        x = pop(h1, t);
        if (i != first && i != last) {
            push(resh, rest, x);
        }
        i++;
    }

    // Вывод результата
    while (resh) cout << pop(resh, rest) << ' ';
    cout << endl;
}
// 13
// 1 2 2 1 3 4 5 1 2 5 4 3 5
