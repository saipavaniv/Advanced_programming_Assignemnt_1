#include <iostream>
#include <cstring>
using namespace std;

// Simple stack of chars, used internally by Expression
class CharStack {
    char *arr;
    int top, capacity;
public:
    CharStack(int size) { capacity = size; arr = new char[capacity]; top = -1; }
    ~CharStack() { delete[] arr; }
    bool isEmpty() { return top == -1; }
    void push(char c) { arr[++top] = c; }
    char pop() { return arr[top--]; }
    char peek() { return arr[top]; }
};

class Expression {
public:
    // 1) Parentheses Matching: push opening brackets, pop and match on closing
    bool isBalanced(string expr) {
        CharStack st(expr.length());
        for (char c : expr) {
            if (c == '(' || c == '[' || c == '{') st.push(c);
            else if (c == ')' || c == ']' || c == '}') {
                if (st.isEmpty()) return false;
                char top = st.pop();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) return false;
            }
        }
        return st.isEmpty();
    }

    // Operator precedence helper
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '%') return 2;
        return 0;
    }

    // 2) Infix to Postfix using a stack for operators
    string infixToPostfix(string infix) {
        CharStack st(infix.length());
        string postfix = "";
        for (char c : infix) {
            if (isalnum(c)) {
                postfix += c;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(')
                    postfix += st.pop();
                if (!st.isEmpty()) st.pop(); // remove '('
            } else { // operator
                while (!st.isEmpty() && st.peek() != '(' &&
                       precedence(st.peek()) >= precedence(c))
                    postfix += st.pop();
                st.push(c);
            }
        }
        while (!st.isEmpty()) postfix += st.pop();
        return postfix;
    }

    // Simple integer stack for evaluation
    int evalStackArr[100], evalTop = -1;
    void evalPush(int v) { evalStackArr[++evalTop] = v; }
    int evalPop() { return evalStackArr[evalTop--]; }

    // 3) Postfix Evaluation: push operands, apply operator on last two when found
    int evaluatePostfix(string postfix) {
        evalTop = -1;
        for (char c : postfix) {
            if (isdigit(c)) {
                evalPush(c - '0'); // assumes single-digit operands
            } else {
                int b = evalPop();
                int a = evalPop();
                switch (c) {
                    case '+': evalPush(a + b); break;
                    case '-': evalPush(a - b); break;
                    case '*': evalPush(a * b); break;
                    case '/': evalPush(a / b); break;
                    case '%': evalPush(a % b); break;
                }
            }
        }
        return evalPop();
    }
};

int main() {
    Expression e;
    string expr;

    cout << "Enter expression for parentheses check: ";
    cin >> expr;
    cout << (e.isBalanced(expr) ? "Balanced\n" : "Not Balanced\n");

    string infix;
    cout << "Enter infix expression (single letters/digits, e.g. A+B*C): ";
    cin >> infix;
    string postfix = e.infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    cout << "Enter a postfix expression with single-digit numbers (e.g. 231*+): ";
    string pf;
    cin >> pf;
    cout << "Evaluated result: " << e.evaluatePostfix(pf) << endl;

    return 0;
}