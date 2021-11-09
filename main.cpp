#include "RBTree.h"
#include "iostream"
using namespace std;

/*
    Красно-черное дерево
    со счетчиком
    + Сравнение двух деревьев (два дерева равны, если содержат одинаковые элемены)

    Методы:
    addNode - добавить
    removeNode - удалить
    search - поиск, возвращает true/false
    compare - сравнение деревьев, возвращает true, если одинаковое число нодов и счетчики равны, иначе false
*/

int main() {

    const int size = 15;
    int a[size];
    srand( time(0) );

    for (int & i : a) {
        i = 1 + rand() % size;
    }

    cout << endl;


    RBTree tree1;
    RBTree tree2;

    for (int i = 0; i < size; i++) {
        tree1.addNode(a[i]);
        tree2.addNode(a[size - i - 1]);
    }

    tree1.addNode(5);

    tree1.print();
    cout << "=====================" << endl;
    tree2.print();


    cout << "tree1 == tree2: " << tree1.compare(tree2) << endl;
    cout << "tree2 == tree1: " << tree2.compare(tree1) << endl;

    return 0;
}
