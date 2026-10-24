#include <iostream>
using namespace std;

class BinaryTree {
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

    // Helper function to count nodes for safe queue dynamic allocation
    int countNodes(Node *node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void preorder(Node *node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node *node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node *node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void deleteTree(Node *node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        deleteTree(root);
    }

    // Constructs the exact binary tree from Question 10
    void createSampleTree() {
        root = new Node(10);
        root->left = new Node(5);
        root->right = new Node(15);
        root->left->left = new Node(2);
        root->left->right = new Node(7);
        root->right->left = new Node(12);
        root->right->right = new Node(20);
    }

    void preorderTraversal() {
        cout << "Preorder Traversal: ";
        preorder(root);
        cout << "\n";
    }

    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << "\n";
    }

    void postorderTraversal() {
        cout << "Postorder Traversal: ";
        postorder(root);
        cout << "\n";
    }

    // Level-Order traversal implemented manually without STL <queue>
    void levelOrderTraversal() {
        if (root == nullptr) return;

        int totalNodes = countNodes(root);
        Node **queue = new Node*[totalNodes]; // Safe dynamic allocation based on total tree nodes

        int front = 0;
        int rear = 0;

        queue[rear++] = root;

        cout << "Level-Order Traversal: ";
        while (front < rear) {
            Node *current = queue[front++];
            cout << current->data << " ";

            if (current->left != nullptr)
                queue[rear++] = current->left;

            if (current->right != nullptr)
                queue[rear++] = current->right;
        }
        cout << "\n";

        delete[] queue; // Clean up dynamic array
    }
};

int main() {
    BinaryTree tree;
    tree.createSampleTree();

    cout << "Given Binary Tree Structure:\n";
    cout << "        10\n";
    cout << "       /  \\\n";
    cout << "      5    15\n";
    cout << "     / \\  / \\\n";
    cout << "    2   7 12 20\n\n";

    tree.preorderTraversal();
    tree.inorderTraversal();
    tree.postorderTraversal();
    tree.levelOrderTraversal();

    return 0;
}