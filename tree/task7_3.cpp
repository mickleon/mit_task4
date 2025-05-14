#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

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

// Поиск минимального
Tree *min(Tree *&tr) {
    if (!tr->left) return tr;
    return min(tr->left);
}

// Удаление элемента из дерева
void erase(Tree *&tr, Tree *&x) {
    Tree *p = x->parent;
    if (!x->left && !x->right) { // Нет детей
        if (!p) tr = nullptr; // Дерево из одного элемента
        else {
            if (p->left == x) p->left = nullptr;
            else if (p->right == x) p->right = nullptr;
        }
        delete x;
    }
    else if (!x->left || !x->right) { // 1 ребенок
        Tree *child = x->left ? x->left : x->right;
        if (!p) tr = child; // Корень
        else {
            if (p->left == x) p->left = child;
            else if (p->right == x) p->right = child;
        }
        child->parent = p;
        delete x;
    }
    else { // 2 ребенка 
        Tree *succ = min(x->right);
        x->inf = succ->inf;
        if (succ->parent->left == succ) 
            succ->parent->left = succ->right;
        else
            succ->parent->right = succ->right;
        if (succ->right)
            succ->right->parent = succ->parent;
        delete succ;
    }
}

// Обход с подсчетом высоты дерева
void max_height(Tree *&x, int &max, int depth = 0) {
    if (depth > max) max = depth;
    if (x->left) max_height(x->left, max, depth + 1);
    if (x->right) max_height(x->right, max, depth + 1);
}

// Обход с подсчетом глубины и смещения узла от левого края уровня
void deepness(Tree *&x, vector<vector<pair<int, int>>> &d, int deep = 0, int count = 1) {
    d[deep].push_back({x->inf, count - (1<<deep)});
    if (x->left) deepness(x->left, d, deep + 1, count*2);
    if (x->right) deepness(x->right, d, deep + 1, count*2+1);
}

// Вывод символа n раз
void print(char c, int n){
    for (int i = 0; i < n; i++) cout << c;
}

// Вывод дерева
void print_tree(Tree *&tr, int r = 1){
    // Высота дерева
    int height = 0;
    max_height(tr, height);
    // Подсчетом глубины и номера каждого узла
    vector<vector<pair<int, int>>> d(height + 1);
    deepness(tr, d);
    // Пробел в начале каждого уровня
    int init_space = (r + 1)*(1<<(height - 1));
    // Перебор уровней
    for (int depth = 0; depth <= height; depth++) {
        print(' ', init_space - r);
        int prev_offset = 0;
        // Пробел между узлами на этом уровне
        int space = init_space*2 - r;
        if (space == 0) space = 1;
        // Перебор узлов на уровне
        for (auto &node : d[depth]) {
            // Расчет отступа до узла, если дерево неполное
            print(' ', (space + r)*(node.second - prev_offset));
            // Вывод узла
            cout << setw(r) << setfill(' ') << node.first;
            // Пробел после узла
            print(' ', space);
            // Сохранение отсутпа для расчета полседующих
            prev_offset = node.second + 1;
        }
        cout << endl;
        init_space /= 2;
    }
}

// Прямой обход
void preorder(Tree *&tr) {
    if (tr) {
        cout << tr->inf << ' ';
        preorder(tr->left);
        preorder(tr->right);
    }
}

int main() {
    // Ввод
    Tree *tr = nullptr;
    int n;
    cout << "n = ";
    cin >> n;
    int x, max = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x > max) max = x;
        insert(tr, x);
    }
    // Максимальная разрядность узлов
    int r = log10(max) + 1;

    print_tree(tr, r);

    cout << "X = ";
    cin >> x;
    Tree *y = find(tr, x);

    // Удаление деда, если он существует
    if (y && y->parent) {
        y = y->parent;
        if (y->parent) {
            Tree *grandparent = y->parent;
            erase(tr, grandparent);
        }
    }
    print_tree(tr, r);
}
/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
