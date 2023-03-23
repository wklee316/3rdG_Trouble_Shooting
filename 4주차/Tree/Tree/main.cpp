#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() {
        root = NULL;
    }

    void insert(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL) {
            root = newNode;
        }
        else {
            Node* curr = root;
            while (true) {
                if (value < curr->data) {
                    if (curr->left == NULL) {
                        curr->left = newNode;
                        break;
                    }
                    curr = curr->left;
                }
                else {
                    if (curr->right == NULL) {
                        curr->right = newNode;
                        break;
                    }
                    curr = curr->right;
                }
            }
        }
    }

    void remove(int value) {
        if (root == NULL) {
            return;
        }

        Node* curr = root;
        Node* parent = NULL;
        bool isLeftChild = false;

        while (curr != NULL && curr->data != value) {
            parent = curr;
            if (value < curr->data) {
                curr = curr->left;
                isLeftChild = true;
            }
            else {
                curr = curr->right;
                isLeftChild = false;
            }
        }

        if (curr == NULL) {
            return;
        }

        if (curr->left == NULL && curr->right == NULL) {
            if (curr == root) {
                root = NULL;
            }
            else if (isLeftChild) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
            delete curr;
        }
        else if (curr->left == NULL) {
            if (curr == root) {
                root = curr->right;
            }
            else if (isLeftChild) {
                parent->left = curr->right;
            }
            else {
                parent->right = curr->right;
            }
            delete curr;
        }
        else if (curr->right == NULL) {
            if (curr == root) {
                root = curr->left;
            }
            else if (isLeftChild) {
                parent->left = curr->left;
            }
            else {
                parent->right = curr->left;
            }
            delete curr;
        }
        else {
            Node* successor = getSuccessor(curr);
            if (curr == root) {
                root = successor;
            }
            else if (isLeftChild) {
                parent->left = successor;
            }
            else {
                parent->right = successor;
            }
            successor->left = curr->left;
            delete curr;
        }
    }

    Node* getSuccessor(Node* delNode) {
        Node* successorParent = delNode;
        Node* successor = delNode;
        Node* curr = delNode->right;

        while (curr != NULL) {
            successorParent = successor;
            successor = curr;
            curr = curr->left;
        }

        if (successor != delNode->right) {
            successorParent->left = successor->right;
            successor->right = delNode->right;
        }

        return successor;
    }

    void printInOrder(Node* node) {
        if (node == NULL) {
            return;
        }

        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }

    void printInOrder() {
        printInOrder(root);
        cout << endl;
    }
};

int main() {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);
    tree.insert(6);
    tree.insert(9);

    cout << "In-order traversal: ";
    tree.printInOrder();

    tree.remove(8);

    cout << "In-order traversal after removing 8: ";
    tree.printInOrder();

    return 0;
}
