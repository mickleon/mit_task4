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

int m = 37, m1 = m - 1;
vector<People*> hash_table(m);

// Вспомогательная хэш-функция (метод деления)
int h1(int x) {
    int k = x % m;
    return k;
}

// Вспомогательная хэш-функция (метод деления)
int h2(int x) {
    int k = 1 + (x % m1);
    return k;
}

// Основная хэш-функция (двойное хеширование)
int f(int h1, int h2, int i) {
    int k = (h1 + i*h2) % m;
    return k;
}

// Добавляет запись в хэш-таблицу
void add_people(People* people) {
    int k1 = h1(people->dateOfBirth.y); // По году рождения
    int k2 = h2(people->dateOfBirth.y);
    bool is_added = false;
    for (int j = 0; j < m; j++) {
        int p = f(k1, k2, j);
        if (!hash_table[p]) {
            is_added = true;
            hash_table[p] = people;
            break;
        }
    }
    if (!is_added) cout << "Hash table is overflowed\n";
}

// Возвращает созданную хэш-таблицу
void make_table() {
    ifstream in("input.txt");
    while (in.peek() != EOF) {
        People* people = new People;
        string date;
        in >> people->surname >> people->post >> date >> people->experience >> people->salary;
        people->dateOfBirth = strToDate(date);
        add_people(people);
    }
    in.close();
}

// Возвращает указатель на найденную запись
People* find_people(int x) {
    int k1 = h1(x);
    int k2 = h2(x);
    for (int j = 0; j < m; j++) {
        int p = f(k1, k2, j);
        if (hash_table[p]->dateOfBirth.y == x) { // По году рождения
            return hash_table[p];
            break;
        }
    }
    return nullptr;
}

// Выводит хэш-таблицу
void print_table() {
    for (int i = 0; i < m; i++) {
        cout << i << ": ";
        if (hash_table[i])
            cout << hash_table[i]->surname;
        cout << endl;
    }
}

// Вывод данных человека
void print_people(People p) {
    cout << p.surname << ' ' << p.post << ' ' << p.experience << ' ';
    cout << right << setw(2) << setfill('0') << p.dateOfBirth.d << '.';
    cout << setw(2) << p.dateOfBirth.m << '.';
    cout << setw(4) << p.dateOfBirth.y << ' ' << p.salary << endl;
}

int main() {
    make_table();
    print_table();
    cout << endl;

    while (true) {
        cout << "1) Add people\n2) Find people\n>> ";
        int c; cin >> c;
        switch (c) {
            case 1: {
                People* people = new People;
                string date;
                cout << "Input people\nSurname: "; cin >> people->surname;
                cout << "Post: "; cin >> people->post;
                cout << "Date of birth (dd.mm.yyyy): "; cin >> date;
                cout << "Experience: "; cin >> people->experience;
                cout << "Salary: "; cin >> people->salary;
                people->dateOfBirth = strToDate(date);
                add_people(people);
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
            default: {
                cout << "Unexpected command\n";
                break;
            }
        }
    }
}