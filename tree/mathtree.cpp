#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Структура дерева
struct Tree {
    char inf;
    Tree *left, *right;
    Tree *parent;
    Tree (char value): 
        inf(value), left(nullptr), 
        right(nullptr), parent(nullptr) {}
};

// Прямой обход
void preorder(Tree *tr) {
    if (tr) {
        cout << tr->inf;
        preorder(tr->left);
        preorder(tr->right);
    }
}

// Обратынй обход (c подсчетом результата)
void postorder(Tree *tr, stack<int> &a) {
    if (tr) {
        postorder(tr->left, a);
        postorder(tr->right, a);
        cout << tr->inf;
        if (isdigit(tr->inf)){
            int n = tr->inf - '0';
            a.push(n);
        }
        else{
            int b = a.top();
            a.pop();
            int c = a.top();
            a.pop();
            if(tr->inf == '+') a.push((int)b + (int)c);
            if(tr->inf == '-') a.push((int)c - (int)b);
            if(tr->inf == '*') a.push((int)b * (int)c);
            if(tr->inf == '/') a.push((int)c / (int)b);
        }
    }
}

// Вставка элемента
void insert(Tree *&tr, char c) {
    Tree *n = new Tree(c);
    if (c == '-' || c == '+') {
        tr->parent = n;
        n->left = tr;
        tr = n;
    }
    else if (c == '/' || c == '*') {
        if (isdigit(tr->inf)) {
            tr->parent = n;
            n->left = tr;
            tr = n;
        }
        else {
            n->parent = tr;
            n->left = tr->right;
            tr->right->parent = n;
            tr->right = n;
        }
    }
    else {
        if (!tr) tr = n;
        else {
            if (!tr->right) {
                n->parent = tr;
                n->left = tr->right;
                tr->right = n;
            }
            else {
                Tree *x = tr->right;
                while (x->right) x = x->right;
                n->parent = x->parent;
                x->right = n;
            }
        }
    }
}

int main() {
    Tree *tr = nullptr;
    string str;
    cout << "Expression in infix form: ";
    getline(cin, str);
    string chars = "+-/*0123456789";
    for (string::iterator it = str.begin(); it !=str.end(); it++) {
        if (*it == ' ') continue;
        else if (chars.find_first_of(*it) == string::npos) {
            cout << "Unexpected char: " << *it;
            return 1;
        }
        insert(tr, *it);
    }
    stack<int> a;
    cout << "Prefix form:  ";
    preorder(tr);
    cout << "\nPostfix form: ";
    postorder(tr, a);
    cout << "\nResult: " << a.top();
    cout << endl;
    a.pop();
}
// 4*3 + 4*3/2 + 8/4 + 5