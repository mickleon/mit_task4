#include <iostream>

using namespace std;

// Структура стека
struct stack {
    char inf;
    stack *next;
};

// Добавляет элемент в стек
void push(stack *&h, char x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

// Удаляет элемент из стека и возвращает его 
char pop(stack *&h) {
    char x = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return x;
}

// Возвращяет приоритет операции
int prior(char c) {
    if (c == '(') return 1;
    if (c == '+' || c == '-') return 2;
    if (c == '*' || c == '/') return 3;
    return 0;
}

int main() {
    stack *head = nullptr;
    // Ввод
    string str, res;
    cout << "Expression in infix form: ";
    getline(cin, str);

    // Удаление пробелов
    string::size_type i = str.find_first_of(" ");
    while (i < string::npos) {
        str = str.replace(i, 1, "");
        i = str.find_first_of(" ", i);
    }
    
    // Запись в результирующую строку
    string operators = "+-*/"; 
    i = 0; char c, d;
    while (i < str.length()) {
        c = str[i];
        // Если цифра или переменная
        if (isdigit(c) || isalpha(c)) res += c;
        // Если открывающаяся скобка
        else if (c == '(') push(head, '(');
        // Если оператор
        else if (operators.find(c) != string::npos) {
            while (head != nullptr && prior(c) <= prior(head->inf)) {
                d = pop(head);
                res += d;
            }
            push(head, c);
        }
        // Если закрывающая скобка
        if (c == ')') {
            while (head != nullptr && head->inf != '(') {
                d = pop(head);
                res += d;
            }
            // Обработка некорректного ввода
            if (head == nullptr) {
                cout << "Error: excess \")\"" << endl;
                return 1;
            }
            pop(head);
        }
        i++;
    }
    while (head != nullptr) {
        d = pop(head);
        // Обработка некорректного ввода
        if (d == '(') {
            cout << "Error: excess \"(\"" << endl;
            return 1;
        }
        res += d;
    }

    // Вывод
    cout << "Postfix form: " << res << endl;
}
// (2 + (2 + 1)) * (3 + 2)
