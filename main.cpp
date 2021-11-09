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

    RBTree tree;
    tree.addNode(50);
    tree.addNode(30);
    tree.addNode(40);
    tree.addNode(35);
    tree.addNode(36);
    tree.addNode(37);
    tree.addNode(38);
    tree.addNode(39);
    cout << " ===================== " << endl;
    tree.print();
    cout << " ===================== " << endl;
    tree.addNode(39);
    tree.print();


    cout << " ===================== " << endl;
    tree.removeNode(39);
    tree.print();
    cout << " ===================== " << endl;
    tree.removeNode(39);
    tree.print();
    cout << " ===================== " << endl;
    tree.removeNode(37);
    tree.print();


    cout << " ===================== " << endl;
    cout << tree.search(51) << endl;

    RBTree tree1;
    tree1.addNode(4);
    tree1.addNode(5);
    tree1.addNode(6);
    tree1.addNode(7);

    RBTree tree2;
    tree2.addNode(7);
    tree2.addNode(6);
    tree2.addNode(5);
    tree2.addNode(4);
    tree2.addNode(4);


    cout << "tree1 == tree2: " << tree1.compare(tree2) << endl;
    cout << "tree2 == tree1: " << tree2.compare(tree1) << endl;

    return 0;
}
