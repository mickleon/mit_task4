#include <iostream>

using namespace std;

struct stack {
    string inf;
    stack *next;
};

void push(stack *&h, string x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

string pop(stack *&h) {
    string x = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return x;
}

// Запись в новый стек нужных строк
stack* result(stack* head, char letter) {
    string s;
    stack *tmp = nullptr;
    while (head) {
        s = pop(head);
        if (s[s.size() - 1] == letter) push(tmp, s);
    }
    return tmp;
}

int main() {
    stack *head = nullptr;
    // Ввод
    int n; string s; char letter;
    cout << "n = ";
    cin >> n;
    cout << "Letter: ";
    cin >> letter;
    for (int i = 0; i < n; i++) {
        cin >> s;
        push(head, s);
    }

    stack *res = result(head, letter);

    // Вывод результата
    while (res)
        cout << pop(res) << ' ';
    cout << endl;
}
// 6
// g
// abc dfr ghjkl sdfg dfg wert
