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

// Прямой обход
void preorder(Tree *tr) {
    if (tr) {
        cout << tr->inf << ' ';
        preorder(tr->left);
        preorder(tr->right);
    }
}

// Поиск узла по значению
Tree *find(Tree *&tr, int value) {
    if (!tr || tr->inf == value) return tr;
    if (value < tr->inf) return find(tr->left, value);
    return find(tr->right, value);
}

// Поиск минимального
Tree *min(Tree *&tr) {
    if (!tr->left) return tr;
    return min(tr->left);
}

// Поиск следующего по симметричному обходу
Tree *next(Tree *&x) {
    if (x->right) return min(x->right);
    Tree *y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Удаление элемента из дерева
void erase(Tree *&tr, Tree *&x) {
    Tree *p = x->parent;
    if (!p) tr = nullptr; // Дерево содержит 1 узел
    else if (!x->left && !x->right) { // Нет детей
        if (p->left == x) p->left = nullptr;
        if (p->right == x) p->right = nullptr;
        delete x;
    }
    else if (!x->left || !x->right) { // 1 ребенок
        if (!p) {
            if (x->right) tr = x->right;
            else tr = x->left;
            tr->parent = nullptr;
        }       
        else {
            if (x->right) {
                if (x == p->left) p->left = x->right;
                else p->right = x->right;
                x->right->parent = p;
            }
            else {
                if (x == p->left) p->left = x->left;
                else p->right = x->left;
                x->left->parent = p;
            }
        }
        delete x;
    }
    else { // 2 ребенка 
        Tree *succ = next(x);
        x->inf = succ->inf;
        if (succ->parent->left == succ) {
            succ->parent->left = succ->right;
            if (succ->right) succ->right->parent = succ->parent;
        }
        else {
            succ->parent->right = succ->right;
            if (succ->right) succ->right->parent = succ->parent;
        }
        delete succ;
    }
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

    // Удаление деда, если он существует
    if (y->parent) {
        y = y->parent;
        if (y->parent) {
            erase(tr, y->parent);
        }
    }
    
    preorder(tr);
    cout << endl;
}
// 10
// 5 3 7 1 9 4 2 8 6 0
