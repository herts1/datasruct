#include <iostream>

// 定义节点颜色
enum Color { RED, BLACK };

// 定义节点结构
struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) : data(data), color(RED), left(NULL), right(NULL), parent(NULL) {}
};

// 定义红黑树类
class RedBlackTree {
private:
    Node *root;
    Node *TNULL;

    // 左旋操作
    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // 右旋操作
    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // 插入节点后的修复操作
    void insertFix(Node *k) {
        Node *u;
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // 叔父节点
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // 叔父节点
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    // 插入节点
    void insert(int key) {
        Node *node = new Node(key);
        node->parent = NULL;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED; // 新插入的节点默认为红色

        Node *y = NULL;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        // y是node的父节点
        node->parent = y;
        if (y == NULL) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // 如果新节点没有父节点，那么它就是根节点，直接涂成黑色
        if (node->parent == NULL) {
            node->color = BLACK;
            return;
        }

        // 如果新节点是根节点的孩子节点，直接调用修复函数
        if (node->parent->parent == NULL) {
            return;
        }

        insertFix(node);
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    // 插入接口
    void insertValue(int key) {
        insert(key);
    }

    // 打印树（中序遍历）
    void inorderHelper(Node *node) {
        if (node != TNULL) {
            inorderHelper(node->left);
            std::cout << node->data << " ";
            inorderHelper(node->right);
        }
    }

    void inorder() const {
        inorderHelper(root);
    }
};

int main() {
    RedBlackTree bst;
    bst.insertValue(55);
    bst.insertValue(40);
    bst.insertValue(65);
    bst.insertValue(60);
    bst.insertValue(75);
    bst.insertValue(57);

    std::cout << "Inorder traversal of the constructed Red-Black Tree is \n";
    bst.inorder();

    return 0;
}

