#include <iostream>
#include <random>
#include <cstdlib> 
#include <ctime>

using namespace std;

struct Node
{
    int data;
    int height_left, height_right;      // счетчик нового уровня в ветке 
    Node* left, * right;
};

typedef struct Node* tree;

struct Node* NewNode(int data)       //создание нового узла
{
    struct Node* pTree = new Node;
    pTree->data = data;
    pTree->height_left = pTree->height_right = 0;
    pTree->left = pTree->right = NULL;
    return pTree;
}

/* Добавление данных в  дерево*/
int AddNode(tree& pTree, int data)  //функция добавления узла в дерево, возвращается 1, если увеличивается высота дерева
{    
    if (!pTree) {                           // Если указатель равен нулю
        pTree = NewNode(data);
        return 1;    }
        
    if (data == pTree->data)  return 0;     //* Если добавляемый элемент уже существует */

    if (data < pTree->data)                 /* Добавление в левое поддерево */
    {
        if (AddNode(pTree->left, data))  {
            pTree->height_left++;
            if (pTree->height_left > pTree->height_right)
                return 1;
        }
        return 0;
    }

    /* Добавление в правое поддерево */
    if (AddNode(pTree->right, data)) {
        pTree->height_right++;
        if (pTree->height_right > pTree->height_left)
            return 1;
    }
    return 0;
}

// Удаление дерева
void DelTree(tree pTree)
{
    if (pTree->left)
        DelTree(pTree->left);
    if (pTree->right)
        DelTree(pTree->right);
    delete pTree;
}

void fillArr(int* arr, int SIZE) { //заполнение массива случайными числами
    for (int i = 0; i < SIZE; i++) 
        arr[i] = rand() % 100;
}

// печать дерева
void printTree(tree root) {
    if (root != NULL) {
        cout << root->data;
        if (root->height_left || root->height_right) {
            cout << "(";
            if (root->height_left != NULL)
                printTree(root->left);
            else cout << "NULL";
            cout << ", ";
            if (root->height_right)
                printTree(root->right);
            else cout << "NULL";
            cout << ")";
        }
    }
}

// поиск числа
bool findNumber(tree root, int a) {
    static int c = 0;
    if (root != NULL) {
        
        if (root->data == a) {
            c++;
            return 1;
        }
        else {
            findNumber(root->left, a);
            findNumber(root->right, a);
        };
        if (c > 0) return 1; else return 0;
    }    
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned int>(time(0)));
    int balans = 0;
    int disbalans = 0;
    const int SIZE = 10000;
    for (int i = 0; i < 50; i++)
    {

        tree pTree = NULL;
        int* mas = new int[SIZE];
        fillArr(mas, SIZE);
        for (int i = 0; i < SIZE; i++)
            AddNode(pTree, mas[i]);
        
        if (abs(pTree->height_left - pTree->height_right) <= 1) {
            cout << "сбалансированное дерево!" << endl;
            balans++;
        }
        else {
            cout << "НЕ сбалансированное дерево!" << endl;
            disbalans++;
        }
        DelTree(pTree);
    }
    cout << endl << ((balans * 100) / (balans + disbalans)) << " % сбаллансированных деревьев" << endl << endl;
    const int SIZE2 = 50;
    int* mas2 = new int[SIZE2];
    fillArr(mas2, SIZE2);
    tree dTree = NULL;
    for (int i = 0; i < SIZE2; i++)
        AddNode(dTree, mas2[i]);
    printTree(dTree);
    int a;
    cout << endl << " Введите чило для поиска в дереве " << endl;
    cin >> a;
    bool b = 0;
    b = findNumber(dTree, a);
    if (b) cout << "Число " << a << " есть в дереве!" << endl;
    else cout << "Числа " << a << " нет в дереве!" << endl;
    return 0;
}