#include <iostream>
using namespace std;

class AVLTree {
private:
    struct Node {
        int data;
        int height;
        Node *left;
        Node *right;

        Node(int value) {
            data = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node *root;

    // Return height of a node
    int height(Node *node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    // Balance Factor = height(left) - height(right)
    // After rebalancing, an AVL tree maintains BF in [-1, 1].
    int getBalanceFactor(Node *node) {
        if (node == nullptr)
            return 0;

        return height(node->left) - height(node->right);
    }

    // Update height of a node
    void updateHeight(Node *node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        node->height = 1 +
                       (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    // LL Rotation: Right rotation
    Node* rotateLL(Node *node) {
        Node *child = node->left;
        Node *temp = child->right;

        child->right = node;
        node->left = temp;

        updateHeight(node);
        updateHeight(child);

        return child;
    }

    // RR Rotation: Left rotation
    Node* rotateRR(Node *node) {
        Node *child = node->right;
        Node *temp = child->left;

        child->left = node;
        node->right = temp;

        updateHeight(node);
        updateHeight(child);

        return child;
    }

    // LR Rotation: Left rotation followed by right rotation
    Node* rotateLR(Node *node) {
        node->left = rotateRR(node->left);
        return rotateLL(node);
    }

    // RL Rotation: Right rotation followed by left rotation
    Node* rotateRL(Node *node) {
        node->right = rotateLL(node->right);
        return rotateRR(node);
    }

    // Insert a value and rebalance the tree
    Node* insertHelper(Node *node, int value) {

        // Step 1: Normal BST insertion
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertHelper(node->left, value);

        else if (value > node->data)
            node->right = insertHelper(node->right, value);

        else
            return node;   // Duplicate values are not inserted

        // Step 2: Update height
        updateHeight(node);

        // Step 3: Calculate balance factor
        int balance = getBalanceFactor(node);

        // Step 4: Perform appropriate rotation

        // LL Case
        if (balance > 1 && value < node->left->data) {
            cout << "  [LL Rotation at Node "
                 << node->data << "]\n";

            return rotateLL(node);
        }

        // RR Case
        if (balance < -1 && value > node->right->data) {
            cout << "  [RR Rotation at Node "
                 << node->data << "]\n";

            return rotateRR(node);
        }

        // LR Case
        if (balance > 1 && value > node->left->data) {
            cout << "  [LR Rotation at Node "
                 << node->data << "]\n";

            return rotateLR(node);
        }

        // RL Case
        if (balance < -1 && value < node->right->data) {
            cout << "  [RL Rotation at Node "
                 << node->data << "]\n";

            return rotateRL(node);
        }

        return node;
    }

    // Inorder traversal with balance factor
    void inorderHelper(Node *node) {
        if (node == nullptr)
            return;

        inorderHelper(node->left);

        cout << node->data
             << "(BF=" << getBalanceFactor(node) << ") ";

        inorderHelper(node->right);
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
    AVLTree() {
        root = nullptr;
    }

    // Destructor
    ~AVLTree() {
        destroy(root);
    }

    // Insert a value
    void insert(int value) {
        root = insertHelper(root, value);
    }

    // Display inorder traversal
    void inorder() {
        inorderHelper(root);
        cout << "\n";
    }
};

int main() {

    cout << "=== Demonstrating All 4 AVL Rotations ===\n\n";

    // --------------------------------------------------
    // 1. LL Rotation
    // --------------------------------------------------
    AVLTree treeLL;

    cout << "1. Inserting 30, 20, 10 "
         << "(Triggers LL Rotation):\n";

    treeLL.insert(30);
    treeLL.insert(20);
    treeLL.insert(10);

    cout << "   Inorder: ";
    treeLL.inorder();


    // --------------------------------------------------
    // 2. RR Rotation
    // --------------------------------------------------
    AVLTree treeRR;

    cout << "\n2. Inserting 10, 20, 30 "
         << "(Triggers RR Rotation):\n";

    treeRR.insert(10);
    treeRR.insert(20);
    treeRR.insert(30);

    cout << "   Inorder: ";
    treeRR.inorder();


    // --------------------------------------------------
    // 3. LR Rotation
    // --------------------------------------------------
    AVLTree treeLR;

    cout << "\n3. Inserting 30, 10, 20 "
         << "(Triggers LR Rotation):\n";

    treeLR.insert(30);
    treeLR.insert(10);
    treeLR.insert(20);

    cout << "   Inorder: ";
    treeLR.inorder();


    // --------------------------------------------------
    // 4. RL Rotation
    // --------------------------------------------------
    AVLTree treeRL;

    cout << "\n4. Inserting 10, 30, 20 "
         << "(Triggers RL Rotation):\n";

    treeRL.insert(10);
    treeRL.insert(30);
    treeRL.insert(20);

    cout << "   Inorder: ";
    treeRL.inorder();


    return 0;
}