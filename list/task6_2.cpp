#include <iostream>

using namespace std;

// Структура узла
template<typename type>
struct Node {
    type inf;
    Node *next;
    Node *prev;
    Node(type value) : inf(value), next(nullptr), prev(nullptr) {}
};

// Структура списка
template<typename type>
class List {
    private:
        Node<type>* head;
        Node<type>* tail;
    public:
        List() : head(nullptr), tail(nullptr) {}
        void push_back(type value);
        void push_front(type value);
        Node<type> *find(type value);
        void insert_after(Node<type> *r, type value);
        void insert_before(Node<type> *r, type value);
        void del_node(Node<type> *r);
        bool empty() {return !head;}
        Node<type> *getHead() {return head;}
        Node<type> *getTail() {return tail;}
        void setHead(Node<type> *h) {head = h;}
        void setTail(Node<type> *t) {tail = t;}
        void print();
        ~List() {
            while (head) {
                Node<type>* p = head;
                head = head->next;
                delete p;
            }
        }
};

// Добавление элемента в конец списка
template<typename type>
void List<type>::push_back(type value) {
    Node<type>* p = new Node<type>(value);
    if (!head) head = tail = p;
    else {
        tail->next = p;
        p->prev = tail;
    }
    tail = p;
}

// Добавление элемента в начало списка
template<typename type>
void List<type>::push_front(type value) {
    Node<type>* p = new Node<type>(value);
    if (!head) head = tail = p;
    else {
        head->prev = p;
        p->next = head;
    }
    head = p;
}

// Поиск элемента в списке
template<typename type>
Node<type>* List<type>::find(type value) {
    Node<type> *p = head;
    while (p) {
        if (p->inf == value) break;
        p = p->next;
    }
    return p;
}

// Вставка элемнта после другого
template<typename type>
void List<type>::insert_after(Node<type> *r, type value) {
    if (!r) return;
    Node<type>* p = new Node<type>(value);
    p->inf = value;
    if (r == tail) {
        p->next = nullptr;
        p->prev = r;
        r->next = p;
        tail = p;
    }
    else {
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

// Вставка элемнта до другого
template<typename type>
void List<type>::insert_before(Node<type> *r, type value) {
    if (!r) return; 
    Node<type>* p = new Node<type>(value);
    p->inf = value;
    if (r == head) {
        p->prev = nullptr;
        p->next = r;
        r->prev = p;
        head = p;
    }
    else {
        r->prev->next = p;
        p->prev = r->prev;
        p->next = r;
        r->prev = p;
    }
}

// Удаление элемента
template<typename type>
void List<type>::del_node(Node<type> *r) {
    if (!r) return;
    if (r == head && r == tail) 
        head = tail = nullptr;
    else if (r == head) {
        head = head->next;
        head->prev = nullptr;
    }
    else if (r == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

// Вывод
template<typename type>
void List<type>::print() {
    Node<type>* h = head;
    while (h) {
        cout << h->inf << ' ';
        h = h->next;
    }
    cout << endl;
}

bool isPrime(int n) {
    bool f = true; 
    for(int j = 2; j * j <= n; j += 1) 
        if (n%j == 0){ 
            f = false;
            break;
        }
    return f;
}

// Циклический сдвиг до первого составного элемента
void result(List<int> &list, int n) {
    Node<int> *h = list.getHead();
    Node<int> *t = list.getTail();
    while (isPrime(h->inf)) {
        Node<int>* next = h->next; 
        // Расцепляем элемент и следующий за ним
        next->prev = nullptr;
        h->next = nullptr;
        // Сцепляем хвост и элемент
        h->prev = list.getTail();
        h->prev->next = h;
        // Заменяем хвост и голову списка
        list.setTail(h);
        list.setHead(next);

        if (h == t) break;
        h = list.getHead();
    }
}

int main() {
    List<int> list;
    // Ввод
    cout << "n = ";
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        list.push_back(x);
    }

    result(list, n);

    list.print();
}
// 11
// 2 3 5 4 8 6 9 1 4 5 7
