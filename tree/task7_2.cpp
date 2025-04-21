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

// Симметричный обход
void inorder(Tree *tr) {
    if (tr) {
        inorder(tr->left);
        // Вывести, если есть 2 ребенка
        if (tr->left && tr->right) cout << tr->inf << ' ';
        inorder(tr->right);
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

    inorder(tr);
    cout << endl;
}
// 10
// 5 3 7 1 9 4 2 8 6 0
