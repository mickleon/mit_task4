#include <iostream>

using namespace std;

struct stack {
    int inf;
    stack *next;
};

void push(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack *&h) {
    int x = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return x;
}

int count_dividers(int x) {
    int count = 0;
    for(int j = 2; j * j <= x; j++) {
        if (x % j == 0) {
            count++;
            if (j != x/j) count++;
        }
    }
    return count;
}

// Возвращает стек чисел с немаксимальным количеством делителей
stack* result(stack* head) {
    int x;
    // Подсчет максимального количества делителей 
    stack *tmp = head;
    int max_count = 0;
    while (tmp) {
        x = tmp->inf;
        max_count = max(count_dividers(x), max_count);
        tmp = tmp->next;
    }
    // Нахождение нужных элементов
    tmp = nullptr;
    while (head) {
        x = pop(head);
        if (count_dividers(x) != max_count)
            push(tmp, x);
    }
    return tmp;
}

int main() {
    stack *head = nullptr;
    // Ввод
    int n, x;
    cout << "n = ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        push(head, x);
    }
    
    stack *res = result(head);

    // Вывод результата
    while (res)
        cout << pop(res) << ' ';
    cout << endl;
}
// 9
// 1 2 3 4 5 6 7 8 9
