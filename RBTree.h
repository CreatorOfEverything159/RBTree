#ifndef RB_TREE_REMASTER_RBTREE_H
#define RB_TREE_REMASTER_RBTREE_H

#include "iostream"
#include "vector"
#include <algorithm>

class RBTree {

    enum Color {
        BLACK,
        RED
    };

    struct TreeNode {
        int data;
        int counter;
        Color color;
        TreeNode *parent;
        TreeNode *leftChild;
        TreeNode *rightChild;
    };

    TreeNode *nullNode = new TreeNode {
            0,
            0,
            BLACK,
            nullptr,
            nullptr,
            nullptr
    };

private:
    TreeNode *root;

    void leftRotateSubTree(TreeNode *&node, TreeNode *subTree) {
        TreeNode *y = subTree->rightChild;
        subTree->rightChild = y->leftChild;

        if (y->leftChild != nullNode) {
            y->leftChild->parent = subTree;
        }

        y->parent = subTree->parent;

        if (subTree->parent == nullNode) {
            node = y;
        } else {
            if (subTree == subTree->parent->leftChild) {
                subTree->parent->leftChild = y;
            } else {
                subTree->parent->rightChild = y;
            }
        }

        y->leftChild = subTree;
        subTree->parent = y;
    }

    void rightRotateSubTree(TreeNode *&node, TreeNode *subTree) {
        TreeNode *y = subTree->leftChild;
        subTree->leftChild = y->rightChild;

        if (y->rightChild != nullNode) {
            y->rightChild->parent = subTree;
        }

        y->parent = subTree->parent;

        if (subTree->parent == nullNode) {
            node = y;
        } else {
            if (subTree == subTree->parent->rightChild) {
                subTree->parent->rightChild = y;
            } else {
                subTree->parent->leftChild = y;
            }
        }

        y->rightChild = subTree;
        subTree->parent = y;
    }

    void addFix(TreeNode *&tree, TreeNode *node) {
        while (node->parent->color == RED) {
            if (node->parent == node->parent->parent->leftChild) {
                TreeNode *y = node->parent->parent->rightChild;
                if (y->color == RED) {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->rightChild) {
                        node = node->parent;
                        leftRotateSubTree(tree, node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotateSubTree(tree, node->parent->parent);
                }
            } else {
                TreeNode *y = node->parent->parent->leftChild;
                if (y->color == RED) {
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->leftChild) {
                        node = node->parent;
                        rightRotateSubTree(tree, node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotateSubTree(tree, node->parent->parent);
                }
            }
        }

        tree->color = BLACK;
    }

    void printTree(TreeNode *node, int level = 0) {
        if (node == nullNode) {
            if (level == 0) {
                std::cout << "Tree is empty";
            }
            return;
        }

        if (node) {
            printTree(node->rightChild, level + 1);

            for (int i = 0; i < level; i++) {
                std::cout << "       ";
            }

            if (node->color == RED) {
                std::cout << "\x1B[48;2;241;68;69m\x1B[1;38;2;255;255;255m " << node->data << "("
                          << node->counter << ") \033[0m" << std::endl;
            } else {
                std::cout << "\x1B[48;2;20;20;20m\x1B[1;38;2;255;255;255m " << node->data << "(" << node->counter
                          << ") \033[0m" << std::endl;
            }

            printTree(node->leftChild, level + 1);
        }
    }

    TreeNode *searchNode(int data) {
        TreeNode *runner = root;
        while (runner != nullNode && runner->data != data) {
            runner = (data < runner->data ? runner->leftChild : runner->rightChild);
        }

        return runner;
    }

    void removeFix(TreeNode *&tree, TreeNode *node) {
        while (node != tree && node->color == BLACK) {
            if (node == node->parent->leftChild) {
                TreeNode *w = node->parent->rightChild;

                if (w->color == RED) {
                    w->color = BLACK;
                    node->parent->color = RED;
                    leftRotateSubTree(tree, node->parent);
                    w = node->parent->rightChild;
                }

                if (w->leftChild->color == BLACK && w->rightChild->color == BLACK) {
                    w->color = RED;
                    node = node->parent;
                } else {
                    if (w->rightChild->color == BLACK) {
                        w->leftChild->color = BLACK;
                        w->color = RED;
                        rightRotateSubTree(tree, w);
                        w = node->parent->rightChild;
                    }

                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->rightChild->color = BLACK;
                    leftRotateSubTree(tree, node->parent);
                    node = tree;
                }
            } else {
                TreeNode *w = node->parent->leftChild;

                if (w->color == RED) {
                    w->color = BLACK;
                    node->parent->color = RED;
                    rightRotateSubTree(tree, node->parent);
                    w = node->parent->leftChild;
                }

                if (w->rightChild->color == BLACK && w->leftChild->color == BLACK) {
                    w->color = RED;
                    node = node->parent;
                } else {
                    if (w->leftChild->color == BLACK) {
                        w->rightChild->color = BLACK;
                        w->color = RED;
                        leftRotateSubTree(tree, w);
                        w = node->parent->leftChild;
                    }

                    w->color = node->parent->color;
                    node->parent->color = BLACK;
                    w->leftChild->color = BLACK;
                    rightRotateSubTree(tree, node->parent);
                    node = tree;
                }
            }
        }

        node->color = BLACK;
    }

    void nodeTransplant(TreeNode *&tree, TreeNode *first, TreeNode *second) {
        if (first->parent == nullNode) {
            tree = second;
        } else {
            if (first == first->parent->leftChild) {
                first->parent->leftChild = second;
            } else {
                first->parent->rightChild = second;
            }
        }

        second->parent = first->parent;
    }

    TreeNode *getMinFromSubtree(TreeNode *subTree) {
        while (subTree->leftChild != nullNode) {
            subTree = subTree->leftChild;
        }

        return subTree;
    }

    void removeTree(TreeNode *&tree) {
        TreeNode *runner = tree;
        TreeNode *delNode;

        while (tree->leftChild != nullNode || tree->rightChild != nullNode) {
            while (runner->leftChild != nullNode) {
                runner = runner->leftChild;
            }

            if (runner->rightChild == nullNode) {
                delNode = runner;
                runner = runner->parent;

                if (delNode == runner->leftChild) {
                    runner->leftChild = nullNode;
                } else {
                    runner->rightChild = nullNode;
                }

                delete delNode;
                /*printTree(tree, 0);
                std::cout << " ----- " << std::endl;*/
            } else {
                runner = runner->rightChild;
            }
        }

        delete tree;
        tree = nullNode;
    }

    bool runTree(TreeNode *a, RBTree &tree) {
        return !(a != nullNode
                 && a != nullptr)
                 || tree.search(a->data)
                 && runTree(a->leftChild, tree)
                 && runTree(a->rightChild, tree)
                 && a->counter == tree.searchNode(a->data)->counter;
    }


public:
    RBTree() {
        root = nullNode;
    }

    ~RBTree() {
        removeTree(root);
    }

    bool compare(RBTree &tree) {
        return runTree(root, tree) && tree.runTree(tree.root, *this);
    }

    bool search(int data) {
        TreeNode *runner = root;
        while (runner != nullNode && runner->data != data) {
            runner = (data < runner->data ? runner->leftChild : runner->rightChild);
        }
        if (runner == nullNode) {
            return false;
        }
        return true;
    }

    void addNode(int data) {
        TreeNode *x = root;
        TreeNode *y = nullNode;

        while (x != nullNode) {
            y = x;
            if (data < x->data) {
                x = x->leftChild;
            } else {
                if (x->data == data) {
                    x->counter++;
                    break;
                }
                x = x->rightChild;
            }
        }

        if (x == nullNode || data != x->data) {
            auto *newNode = new TreeNode{
                    data,
                    1,
                    RED,
                    y,
                    nullNode,
                    nullNode
            };

            if (y == nullNode) {
                root = newNode;
            } else if (data < y->data) {
                y->leftChild = newNode;
            } else {
                y->rightChild = newNode;
            }

            addFix(root, newNode);
        }


    }

    bool removeNode(int data) {
        TreeNode *&tree = root;
        TreeNode *node = searchNode(data);

        if (node == nullNode) {
            return false;
        }

        if (node->data == data && node->counter > 1) {
            node->counter--;
            return true;
        }

        TreeNode *y = node;
        TreeNode *x;
        Color yOriginalColor = y->color;

        if (node->leftChild == nullNode) {
            x = node->rightChild;
            nodeTransplant(tree, node, node->rightChild);
        } else {
            if (node->rightChild == nullNode) {
                x = node->leftChild;
                nodeTransplant(tree, node, node->leftChild);
            } else {
                y = getMinFromSubtree(node->rightChild);
                yOriginalColor = y->color;
                x = y->rightChild;
                if (y->parent == node) {
                    x->parent = y;
                } else {
                    nodeTransplant(tree, y, y->rightChild);
                    y->rightChild = node->rightChild;
                    y->rightChild->parent = y;
                }

                nodeTransplant(tree, node, y);
                y->leftChild = node->leftChild;
                y->leftChild->parent = y;
                y->color = node->color;
            }
        }

        if (yOriginalColor == BLACK) {
            removeFix(tree, x);
        }
    }

    void print() {
        printTree(root, 0);
    }
};

#endif //RB_TREE_REMASTER_RBTREE_H
