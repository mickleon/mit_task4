#include <iostream>

using namespace std;

struct Tree {
    int inf;
    Tree *left, *right;
    Tree *parent;
    Tree (int value): 
        inf(value), left(nullptr), 
        right(nullptr), parent(nullptr) {}
};

// Вставка элемента
void insert(Tree *&tr, int value) {
    Tree *n = new Tree(value);
    if (!tr) tr = n;
    else {
        Tree *y = tr;
        while (y) {
            if (n->inf > y->inf) {
                if (y->right) y = y->right;
                else {
                    y->right = n;
                    n->parent = y;
                    break;
                }
            }
            else if (n->inf < y->inf) {
                if (y->left) y = y->left;
                else {
                    y->left = n;
                    n->parent = y;
                    break;
                }
            }
            else break;
        }
    }
}

// Поиск узла по значению
Tree *find(Tree *&tr, int value) {
    if (!tr || tr->inf == value) return tr;
    if (value < tr->inf) return find(tr->left, value);
    return find(tr->right, value);
}

// Вывод и подсчет детей заданного узла
int print_children(Tree *&y) {
    int c = 0;
    if (y->left) {
        cout << y->left->inf << ' ';
        c++;
    }
    if (y->right) {
        cout << y->right->inf << ' ';
        c++;
    }
    return c;
}

int main() {
    // Ввод
    Tree *tr = nullptr;
    int n;
    cout << "n = ";
    cin >> n;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        insert(tr, x);
    }

    cout << "X = ";
    cin >> x;
    Tree *y = find(tr, x);

    // Поиск внуков
    if (y) {
        int c = 0;
        cout << "Grandcildren: ";
        if (y->left) c += print_children(y->left);
        if (y->right) c += print_children(y->right);
        if (!c) cout << "none";
    }
    else cout << "There is no node " << x << " in tree";
    cout << endl;
}
// 10
// 5 3 7 1 9 4 2 8 6 0
