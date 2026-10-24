#include <iostream>
using namespace std;

class BST {
private:
    struct Node {
        int data;
        Node *left;
        Node *right;

        Node(int value) {
            data = value;
            left = nullptr;
            right = nullptr;
        }
    };

    Node *root;

    // Insert a value into the BST
    Node* insert(Node *node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    // Search for a value
    bool search(Node *node, int value) {
        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    // Find minimum node
    Node* findMinNode(Node *node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    // Find maximum node
    Node* findMaxNode(Node *node) {
        while (node != nullptr && node->right != nullptr)
            node = node->right;

        return node;
    }

    // Delete a node
    Node* deleteNode(Node *node, int value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        }
        else {
            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2a: Node has only a right child
            if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                return temp;
            }

            // Case 2b: Node has only a left child
            if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            Node *successor = findMinNode(node->right);

            node->data = successor->data;

            node->right = deleteNode(node->right, successor->data);
        }

        return node;
    }

    // Inorder: Left -> Root -> Right
    void inorder(Node *node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Preorder: Root -> Left -> Right
    void preorder(Node *node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Postorder: Left -> Right -> Root
    void postorder(Node *node) {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // Find height
    int height(Node *node) {
        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    // Delete all nodes
    void destroy(Node *node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    // Constructor
    BST() {
        root = nullptr;
    }

    // Destructor
    ~BST() {
        destroy(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    void inorder() {
        inorder(root);
        cout << "\n";
    }

    void preorder() {
        preorder(root);
        cout << "\n";
    }

    void postorder() {
        postorder(root);
        cout << "\n";
    }

    int minimum() {
        if (root == nullptr)
            return -1;

        return findMinNode(root)->data;
    }

    int maximum() {
        if (root == nullptr)
            return -1;

        return findMaxNode(root)->data;
    }

    int getHeight() {
        return height(root);
    }
};

int main() {
    BST tree;

    int n, value;

    // Create BST
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }

    // Traversals
    cout << "\n=== BST Traversals ===\n";

    cout << "Inorder: ";
    tree.inorder();

    cout << "Preorder: ";
    tree.preorder();

    cout << "Postorder: ";
    tree.postorder();

    // Minimum, Maximum and Height
    cout << "\n=== Tree Properties ===\n";

    cout << "Minimum: " << tree.minimum() << "\n";
    cout << "Maximum: " << tree.maximum() << "\n";
    cout << "Height: " << tree.getHeight() << "\n";

    // Search
    cout << "\nEnter value to search: ";
    cin >> value;

    if (tree.search(value))
        cout << "Element found\n";
    else
        cout << "Element not found\n";

    // Delete
    cout << "\nEnter value to delete: ";
    cin >> value;

    tree.deleteValue(value);

    cout << "Inorder after deletion: ";
    tree.inorder();

    return 0;
}