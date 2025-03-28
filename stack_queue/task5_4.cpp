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
    
    // Подсчет максимального количества делителей 
    stack *res = head;
    int count = 0, max_count = 0;
    while (res) {
        x = res->inf;
        max_count = max(count_dividers(x), max_count);
        res = res->next;
    }
    // Нахождение нужных элементов
    res = nullptr;
    while (head) {
        x = pop(head);
        if (count_dividers(x) != max_count)
            push(res, x);
    }

    // Вывод результата
    while (res)
        cout << pop(res) << ' ';
    cout << endl;
}
// 9
// 1 2 3 4 5 6 7 8 9
