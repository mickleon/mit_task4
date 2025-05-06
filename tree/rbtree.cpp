#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>

using namespace std;

struct Tree {
    int inf;
    Tree *parent;
    Tree *left, *right;
    char color;
};

void left_rotate(Tree *&tr, Tree *x) {
    Tree *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;
    if (!y->parent) {
        tr = y;
        y->color = 'b';
    }
    else if (x == x->parent->left) 
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(Tree *&tr, Tree *x) {
    Tree *y = x->left;
    x->left = y->right;
    if (y->right) 
        y->right->parent = x;
    y->parent = x->parent;
    if (!y->parent) {
        tr = y;
        y->color = 'b';
    }
    else if (x == x->parent->right) 
        x->parent->right = y;
    else 
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

Tree *root(int x) {
    Tree *n = new Tree;
    n->inf = x;
    n->parent = nullptr;
    n->left = n->right = nullptr;
    n->color = 'b';
    return n;
}

Tree *node(Tree* prev, int x) {
    Tree *n = new Tree;
    n->inf = x;
    n->parent = prev;
    n->left = n->right = nullptr;
    n->color = 'r';
    return n;
}

Tree *grandparent(Tree *x) {
    if (!x || !x->parent) return nullptr;
    return x->parent->parent;  
}

Tree *uncle(Tree *x) {
    Tree *g = grandparent(x);
    if (!g) return nullptr;
    if (x->parent == g->left) return g->right;
    else return g->left;
}

Tree *sibling(Tree *x) {
    if (x && x->parent) {
        if (x == x->parent->left)
            return x->parent->right;
        else
            return x->parent->left;
    }
    return nullptr;
}

void insert_case_1(Tree *&tr, Tree *x); // x корень
void insert_case_2(Tree *&tr, Tree *x); // Родитель черный
void insert_case_3(Tree *&tr, Tree *x); // Родитель и дядя красные
void insert_case_4(Tree *&tr, Tree *x); // Родитель красный, дядя черный, родитель и ребенок противоположного цвета своих родителей
void insert_case_5(Tree *&tr, Tree *x); // Родитель красный, дядя черный, родитель и ребенок одинакового цвета своих родителей

void insert_case_1(Tree *&tr, Tree *x) {
    if (!x->parent) x->color = 'b';
    else insert_case_2(tr, x);
}

void insert_case_2(Tree *&tr, Tree *x) {
    if (x->parent->color == 'r') 
        insert_case_3(tr, x);
    else return;
}

void insert_case_3(Tree *&tr, Tree *x) {
    Tree *g = grandparent(x);
    Tree *u = uncle(x);
    if (u && u->color == 'r' && x->parent->color == 'r') {
        x->parent->color = 'b';
        u->color = 'b';
        g->color = 'r';
        insert_case_1(tr, g);
    }
    else insert_case_4(tr, x);
}

void insert_case_4(Tree *&tr, Tree *x) {
    Tree *g = grandparent(x);
    Tree *p = x->parent;
    if (x == p->right && p == g->left) {
        left_rotate(tr, p);
        x = x->left;
    }
    else if (x == p->left && p == g->right) {
        right_rotate(tr, p);
        x = x->right;
    }
    insert_case_5(tr, x);
}

void insert_case_5(Tree *&tr, Tree *x) {
    Tree *g = grandparent(x);
    Tree *p = x->parent;
    p->color = 'b';
    g->color = 'r';
    if (x == p->left && p == g->left)
        right_rotate(tr, g);
    else
        left_rotate(tr, g);
}

void insert(Tree *&tr, int x) {
    Tree *prev = nullptr;
    Tree *y = tr;
    while (y) {
        prev = y;
        if (x < y->inf) y = y->left;
        else if (x > y->inf) y = y->right;
        else return;
    }
    
    Tree *n;
    if (!prev) {
        n = root(x);
        tr = n;
    }
    else {
        n = node(prev, x);
        if (x < prev->inf) prev->left = n;
        else prev->right = n;
    }
    insert_case_1(tr, n);
}

void delete_case_1(Tree *&tr, Tree *x); // Корень
void delete_case_2(Tree *&tr, Tree *x); // Узел и родитель черные, брат красный
void delete_case_3(Tree *&tr, Tree *x); // Узел, родитель, брат, племянники черные
void delete_case_4(Tree *&tr, Tree *x); // Узел, брат, племянники черные, родитель красный
void delete_case_5(Tree *&tr, Tree *x); // Брат черный, прилежащий племянник красный, противолежащий черный
void delete_case_6(Tree *&tr, Tree *x); // Брат черный, прилежащий племянник черный, противолежащий красный

void delete_case_1(Tree *&tr, Tree *x) {
    if (!x->parent) {
        cout << 1 << endl;
        if (x->left) tr = x->left;
        else tr = x->right;
    }
    else delete_case_2(tr, x);
}

void delete_case_2(Tree *&tr, Tree *x) {
    Tree *s = sibling(x);
    if (s && s->color == 'r') {
        cout << 2 << endl;
        x->parent->color = 'r';
        s->color = 'b';
        if (x == x->parent->left)
            left_rotate(tr, x->parent);
        else right_rotate(tr, x->parent);
    }
    delete_case_3(tr, x);
}

void delete_case_3(Tree *&tr, Tree *x) {
    Tree *s = sibling(x);
    if (x->parent->color == 'b' && s && s->color == 'b' && (!s->left || s->left->color == 'b') && (!s->right || s->right->color == 'b')) {
        cout << 3 << endl;
        s->color = 'r';
        delete_case_1(tr, x);
    }
    else delete_case_4(tr, x);
}

void delete_case_4(Tree *&tr, Tree *x) {
    Tree *s = sibling(x);
    if (x->parent->color == 'r' && s && s->color == 'b' && (!s->left || s->left->color == 'b') && (!s->right || s->right->color == 'b')) {
        cout << 4 << endl;
        s->color = 'r';
        x->parent->color = 'b';
    }
    else delete_case_5(tr, x);
}

void delete_case_5(Tree *&tr, Tree *x) {
    Tree *s = sibling(x);
    if (s && s->color == 'b') {
        cout << 5 << endl;
        if (x->parent->left == x && (s->left && s->left->color == 'r') && (!s->right || s->right->color == 'b')) {
            s->color = 'r';
            s->left->color = 'b';
            right_rotate(tr, s);
        }
        else if (x->parent->right == x && (s->right && s->right->color == 'r') && (!s->left || s->left->color == 'b')) {
            s->color = 'r';
            s->right->color = 'b';
            left_rotate(tr, s);
        }
    }
    delete_case_6(tr, x);
}

void delete_case_6(Tree *&tr, Tree *x) {
    Tree *s = sibling(x);
    Tree *p = x->parent;
    s->color = p->color;
    p->color = 'b';
    if (x == p->left) {
        s->right->color = 'b';
        left_rotate(tr, p);
    }
    else {
        s->left->color = 'b';
        right_rotate(tr, p);
    }
    cout << 6 << endl;
}

void replace(Tree *&tr, Tree *x) {
    Tree *p = x->parent;
    Tree *ch = x->left ? x->left : x->right;
    if (ch) ch->parent = p;
    if (!p)
        tr = ch;
    else if (x == p->left)
        p->left = ch;
    else
        p->right = ch;
}

void delete_one(Tree *&tr, Tree *x) {
    if (x->left && x->right) {
        Tree *buf;
        if (x->inf <= tr->inf) {
            buf = x->left;
            while (buf->right) buf = buf->right;
        }
        else {
            buf = x->right;
            while (buf->left) buf = buf->left;
        }
        swap(x->inf, buf->inf);
        x = buf;
    }
    if (x->left || x->right) {
        Tree *ch;
        if (x->left && !x->right)
            ch = x->left;
        if (x->right && !x->left)
            ch = x->right;
        replace(tr, x);
        if (x->color == 'b') {
            if (ch->color == 'r') ch->color = 'b';
            else delete_case_1(tr, x);
        }
    }
    else {
        if (x->color == 'b') {
            delete_case_1(tr, x);
            cout << 7 << endl;
        }
        else {
            if (x == x->parent->left)
                x->parent->left = nullptr;
            else x->parent->right = nullptr;
        }
    }
    delete x;
}

Tree *find(Tree *&tr, int value) {
    if (!tr || tr->inf == value) return tr;
    if (value < tr->inf) return find(tr->left, value);
    return find(tr->right, value);
}

// Обход с подсчетом высоты дерева
void max_height(Tree *&x, int &max, int depth = 0) {
    if (depth > max) max = depth;
    if (x->left) max_height(x->left, max, depth + 1);
    if (x->right) max_height(x->right, max, depth + 1);
}

// Обход с подсчетом глубины и смещения узла от левого края уровня
void deepness(Tree *&x, vector<vector<pair<Tree*, int>>> &d, int deep = 0, int count = 1) {
    d[deep].push_back({x, count - (1<<deep)});
    if (x->left) deepness(x->left, d, deep + 1, count*2);
    if (x->right) deepness(x->right, d, deep + 1, count*2+1);
}

// Вывод символа n раз
void print(char c, int n){
    for (int i = 0; i < n; i++) cout << c;
}

// Вывод дерева
void print_tree(Tree *&tr, int r = 1){
    int height = 0;
    max_height(tr, height);
    vector<vector<pair<Tree*, int>>> d(height + 1);
    deepness(tr, d);
    int init_space = (r + 1)*(1<<(height - 1));
    for (int depth = 0; depth <= height; depth++) {
        print(' ', init_space - r);
        int prev_offset = 0;
        int space = init_space*2 - r;
        if (space == 0) space = 1;
        for (auto &node : d[depth]) {
            print(' ', (space + r)*(node.second - prev_offset));
            if (node.first->color == 'r')
                printf("\033[31m%*d\033[m", r, node.first->inf);
            else 
                printf("\033[32m%*d\033[m", r, node.first->inf);
            print(' ', space);
            prev_offset = node.second + 1;
        }
        cout << endl;
        // print(' ', init_space - r);
        // prev_offset = 0;
        // for (auto &node : d[depth]) {
        //     print(' ', (space + r)*(node.second - prev_offset));
        //     if (node.first->left) printf("%*d", r, node.first->left->inf);
        //     else cout << setw(r) << 'n';
        //     if (node.first->right) printf("%*d", r, node.first->right->inf);
        //     else cout << setw(r) << 'n';
        //     print(' ', space - r);
        //     prev_offset = node.second + 1;
        // }
        // cout << endl;
        init_space /= 2;
    }
}

int main() {
    Tree *tr = nullptr;
    int n, x, max = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x > max) max = x;
        insert(tr, x);
    }
    int r = log10(max) + 1;
    print_tree(tr, r);
    while (true) {
        cin >> x;
        delete_one(tr, find(tr, x));
        print_tree(tr, r);
    }
}
/*
18
9 6 17 3 8 16 20 1 4 7 12 19 21 2 5 11 14 18
*/
