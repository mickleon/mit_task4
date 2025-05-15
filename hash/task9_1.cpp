#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// Структура даты
struct Date {
    int d, m, y;
};

// Структура человека
struct People {
    string surname, post;
    Date dateOfBirth;
    int experience, salary;
};

// Перевод строки с в структуру Date
Date strToDate(string str) {
    Date d;
    string::size_type p, p1;
    p = str.find('.');
    p1 = str.find('.', p + 1);
    d.d = stoi(str.substr(0, p));
    d.m = stoi(str.substr(p + 1, p1 - p));
    d.y = stoi(str.substr(p1 + 1, str.size() - p1));
    return d;
}

// Структура узла списке
template<typename type>
struct Node {
    type inf;
    Node* next;
    Node* prev;
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
    void del_node(Node<type>* r);
    bool empty() { return !head; }
    Node<type>* getHead() { return head; }
    ~List() {
        while (head) {
            Node<type>* p = head;
            head = head->next;
            delete p->inf;
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

// Удаление элемента
template<typename type>
void List<type>::del_node(Node<type>* r) {
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
    delete r->inf;
    delete r;
}

int m = 8;
double a = (sqrt(5) - 1) / 2;
vector<List<People*>> hash_table(m);

// Хэш-функция (метод умножения)
int h(int x) {
    int k = m*(x*a - int(x*a));
    return k;
}

// Добавляет запись в хэш-таблицу
void add_people(People* p) {
    int k = h(p->dateOfBirth.y); // По году рождения
    hash_table[k].push_back(p);
}

// Возвращает созданную хэш-таблицу
void make_table() {
    ifstream in("input.txt");
    while (in.peek() != EOF) {
        People* p = new People;
        string date;
        in >> p->surname >> p->post >> date >> p->experience >> p->salary;
        p->dateOfBirth = strToDate(date);
        add_people(p);
    }
    in.close();
}

// Возвращает указатель на найденную запись
People* find_people(int x) {
    int k = h(x);
    Node<People*>* h = hash_table[k].getHead();
    while (h) {
        if (h->inf->dateOfBirth.y == x) // По году рождения
            return h->inf;
        h = h->next;
    }
    return nullptr;
}

// Удаляет записи с данным ключом
void delete_people(int x) {
    int k = h(x);
    Node<People*>* h = hash_table[k].getHead();
    while (h) {
        if (h->inf->dateOfBirth.y == x) { // По году рождения
            Node<People*>* p = h;
            h = h->next;
            hash_table[k].del_node(p);
        }
        else {
            h = h->next;
        }
    }
}

// Выводит хэш-таблицу
void print_table() {
    for (int i = 0; i < m; i++) {
        Node<People*>* h = hash_table[i].getHead();
        cout << i << ": ";
        while (h) {
            cout << h->inf->surname << ' ' << h->inf->dateOfBirth.y;
            if (h->next) {
                cout << ", ";
                h = h->next;
            }
            else {
                cout << '.';
                break;
            }
        }
        cout << endl;
    }
}

// Вывод данных человека
void print_people(People p) {
    cout << p.surname << ' ' << p.post << ' ';
    cout << right << setw(2) << setfill('0') << p.dateOfBirth.d << '.';
    cout << setw(2) << p.dateOfBirth.m << '.';
    cout << setw(4) << p.dateOfBirth.y << ' ';
    cout << p.experience << ' ' << p.salary << endl;
}

int main() {
    make_table();
    print_table();
    cout << endl;

    while (true) {
        cout << "1) Add people\n2) Find people\n3) Delete people\n>> ";
        int c; cin >> c;
        switch (c) {
            case 1: {
                People* p = new People;
                string date;
                cout << "Input people\nSurname: "; cin >> p->surname;
                cout << "Post: "; cin >> p->post;
                cout << "Date of birth (dd.mm.yyyy): "; cin >> date;
                cout << "Experience: "; cin >> p->experience;
                cout << "Salary: "; cin >> p->salary;
                p->dateOfBirth = strToDate(date);
                add_people(p);
                print_table();
                cout << endl;
                break;
            }
            case 2: {
                cout << "Input year to find: ";
                int y; cin >> y;
                People* p = find_people(y);
                if (p) {
                    print_people(*p);
                    cout << endl;
                }
                else cout << "People not found\n\n";
                break;
            }
            case 3: {
                cout << "Input year to delete: ";
                int y; cin >> y;
                delete_people(y);
                print_table();
                cout << endl;
                break;
            }
            default: {
                cout << "Unexpected command\n";
                break;
            }
        }
    }
}