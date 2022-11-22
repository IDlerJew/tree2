
#include <iostream>
#include "List.h"
using namespace std;

struct node {
    int height;
    int key;
    struct node* left, * right;
    node(int k) { key = k; left = right = 0; height = 1; }
};

int maxfind(List* j) {
    Node* p = new Node();
    int i = 0;
    p = j->Getfirst();
    while (p) {
        i++;
        p = p->next;
    }
    while (j->Getfirst()) {
        j->delete_first();
    }
    return i;
}
node* build2(int a[], node* root, int l, int r) {
    if (l > r) {
        return nullptr;
    }
    int mid = (l + r) / 2;
    node* p = new node(a[mid]);
    root = p;
    root->left=build2(a, root->left, l, mid - 1);
    root->right=build2(a, root->right, mid + 1, r);
    return p;
}
void build(Node * head,node *root,int l,int r ) {
    if (l > r) {
        return ;
    }
    int mid = (l + r) / 2;
    if (!root) {
        node* g = new node(0);
        root= g;
    }
    build(head,root->left, l, mid - 1);
    root->key = head->val;
    cout << head -> val<<endl;
    head = head->next;
    build(head, root->right, mid + 1,r );
    root->key = head->val;
    return;
}
void addlist(node* j,List *k) {
    if (!j)return;
    k->push_back(j->key);
    addlist(j->left, k);
    addlist(j->right, k);
}
void  max(node* p,List* j,int k ) {
    if (p == nullptr) {
        return;
    }
    if (k < p->key) {
        j->push_start(1);
    }
    max(p->left,  j,  k);
    max(p->right, j, k);
}
int height(node* p)
{
    return p ? p->height : 0;
}
int bfactor(node* p)
{
    return height(p->right) - height(p->left);
}
void fixheight(node* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}
node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}
node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    if (!p) {
        return nullptr;
}
    fixheight(p);
    if (bfactor(p) <= 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) >= -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна

}
void nodebalance(node* p) {
    if (!p) {
        return;
    }
    balance(p);
    nodebalance(p->left);
    nodebalance(p->right);
}
// Создаем узел
struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Отсортированный (inorder) обход
void inorder(struct node* root) {
    if (root != NULL) {
        // Обходим лево
        inorder(root->left);

        // Обходим корень
        cout << root->key << " -> ";

        // Обходим право
        inorder(root->right);
    }
}

// Вставка узла
struct node* insert(struct node* _node, int key) {
    // Возвращаем новый узел, если дерево пустое
    if (_node == NULL) {
        node* k = new node(key);
        return k;
    }

    // Проходим в нужное место и вставляет узел
    if (key < _node->key)
        _node->left = insert(_node->left, key);
    else
        _node->right = insert(_node->right, key);
    fixheight(_node);
    return _node;
}

// Поис inorder-преемника
struct node* minValueNode(struct node* node) {
    struct node* current = node;

    // Ищем крайний левый лист — он и будет inorder-преемником
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Удаление узла
struct node* deleteNode(struct node* root, int key) {
    // Возвращаем, если дерево пустое
    if (root == NULL) return root;

    // Ищем узел, который хотим удалить
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Если у узла один дочерний элемент или их нет
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // Если у узла два дочерних элемента
        struct node* temp = minValueNode(root->right);

        // Помещаем inorder-преемника на место узла, который хотим удалить
        root->key = temp->key;

        // Удаляем inorder-преемника
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Тестим функции
int main() {
    setlocale(0, "rus");
    struct node* root = NULL;
    
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 11);
    root = insert(root, 8);
    root = insert(root, 7);
    root = insert(root, 4);
    root = insert(root, 3);
    root = insert(root, 2);
    List* p=new List();
    List* y = new List();
    Node* h = new Node();
    struct node* root2 = NULL;
    cout << "Отсортированный обход: ";
    inorder(root);
    addlist(root, y);
    h = y->Getfirst();
    cout << endl;
    y->sort();
    y->print();
    int a[8];
    for (int i = 0; i < 8; i++) {
        a[i] = h->val;
        h = h->next;
    }
    for (int i = 0; i < 8; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    root2=build2(a, root2, 0, 7);
    //build(h, root, 0, 6);
    /*max(root, p, 4);
    int i = maxfind(p);
    cout << endl;
    cout << i << endl;
    cout << "Отсортированный обход: ";
    */
    inorder(root2);
    //inorder(root);
}