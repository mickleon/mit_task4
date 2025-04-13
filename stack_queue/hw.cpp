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
    if (!tail) head = tail = p;
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

// Ширина и высота шахматной доски
int n = 8;

// Принимает строку с клеткой, возвращает пару координат
pair<int, int> ceil_to_coord(string s) {
    pair <int, int> p;
    char c = s[0];
    if (65 <= c && c <= 72) p.first = c - 65;
    if (97 <= c && c <= 104) p.first = c - 97;
    p.second = s[1] - 49;
    return p;
}

// Принимает номер клетки, возвращает строку
// (всего 64 клетки, нумерация с 0 до 63 слева направо, снизу вверх)
string num_to_ceil(int c) {
    char x, y;
    x = c%n + 65;
    y = c/n + 49;
    string s;
    s += x;
    s += y;
    return s;
} 

// Принимает пару координат, возвращает номер клетки
int coord_to_num(pair<int, int> x) {
    return x.second*n + x.first;
}

// Проверяет, не вышел ли конь за границы шахматной доски
bool in(pair<int, int> x) {
    return 0 <= x.first && x.first < n && 
           0 <= x.second && x.second < n;
}

// Обход в ширину
void bfs(pair<int, int> x, pair<int, int> end, vector<int> &p) {
    // Матрица посещённых клеток
    vector<vector<bool>> a;
    a.assign(n, vector<bool>(n, 0));
    // Все возможные смещения ходов коня по осям
    int dx[]{-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[]{-1, 1, -2, 2, -2, 2, -1, 1};
    Queue<pair<int, int>> queue;
    a[x.first][x.second] = 1;
    queue.push(x);
    while (!queue.empty()) {
        x = queue.pop();
        // Перебираем все ходы
        for (int i = 0; i < 8; i++) {
            pair<int, int> y = {x.first + dx[i], x.second + dy[i]};
            if (in(y)) {
                if (a[y.first][y.second] == 0) {
                    p[coord_to_num(y)] = coord_to_num(x);
                    // Если дошли до нужной, завершаем обход
                    if (y == end) break;
                    a[y.first][y.second] = 1;
                    queue.push(y);
                }
            }
        }
    }
}

int main() {
    string s;
    cout << "Start: ";
    cin >> s;
    pair<int, int> start = ceil_to_coord(s);
    cout << "End: ";
    cin >> s;
    pair<int, int> end = ceil_to_coord(s);

    // Вектор вида: 
    // индекс - номер клетки,
    // значение - из которой в нее попали
    vector<int> p(n * n, -1);
    // Но так как начинаем обход с конца, то можно скзать
    // индекс - номер клетки,
    // значение - в которую из этой попадём
    bfs(end, start, p);

    // Находим следующую клетку по порядку движения, идём в нее, выводим,
    // повторяем пока не дойдем (конечной клетке не задана следущая, так как 
    // мы из неё начали обход)
    int x = coord_to_num(start);
    while (x != -1) {
        cout << num_to_ceil(x) << ' ';
        x = p[x];
    }
    cout << endl;
}
